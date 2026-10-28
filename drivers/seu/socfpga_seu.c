/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_seu.c
 *
 * SEU source implementation for the SoCFPGA bare-metal software stack.
 */

/*
 * This driver implements the APIs to exercise the SEU features.
 * Single event upsets (SEUs) are rare and unintended changes in the internal memory
 * elements of an FPGA caused by cosmic radiation. The memory state change is a soft
 * error with no permanent damage but the FPGA may operate erroneously until
 * background scrubbing fixes the upset.
 *
 * The SEU driver supports error injection. The below diagram shows the
 * SEU Error Injection Flow (via SDM Mailbox):
 *
 * +------------------------------+
 * |  Prepare Injection Params    |
 * |  (Sector, CRAM, Cycles)      |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * |  Send Command via Mailbox    |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * | Injection Triggered Securely |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * |  Receive interrupt Callback  |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * | Check Stats for              |
 * | Error Detection & Correction |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * |  review Timestamps & Status  |
 * +--------------+---------------+
 *                |
 *                v
 * +------------------------------+
 * |     End of Injection Flow    |
 * +------------------------------+
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "errno.h"
#include "socfpga_seu.h"
#include "socfpga_sip_handler.h"
#include "cache.h"
#include "lib_time.h"

#define SEU_READ_ERR_CMD                0x3cU
#define SEU_READ_ERR_RESP_BYTES         12U
#define SEU_INJECT_FPGA_RAM_ERR_CMD     0x42U
#define SEU_INJECT_FPGA_RAM_ERR_BYTES   4U
#define SEU_INSERT_SAFE_ERR_CMD         0x41U
#define SEU_INSERT_SAFE_ERR_BYTES        8U
#define SEU_READ_STATS                  0x40U
#define SEU_READ_STATS_CMD_BYTES        4U
#define SEU_READ_STAT_RESP_BYTES        24U

/*
 * V1 SiP mailbox transport: INTEL_SIP_SMC_MBOX_SEND_CMD (0xC200003C).
 * ATF performs a synchronous mailbox_send_cmd() and returns immediately with
 * the SDM status code.  This bypasses the V3 GEN_MBOX allowlist while still
 * routing through BL31 to SDM.
 *
 * SMC ABI (baremetal smc_call register_val[] -> X1..X6):
 *   [0] mbox opcode
 *   [1] cmd buffer pointer (DDR, or 0)
 *   [2] cmd length in 32-bit words
 *   [3] urgent flag (0 = casual)
 *   [4] response buffer pointer (DDR, or 0)
 *   [5] response length in 32-bit words
 *
 * Returns: X0 = SiP status, X1 = SDM err code, X2 = response words returned.
 */
#define SIP_SMC_MBOX_SEND_CMD           0xC200003CU
#define SIP_SMC_STATUS_OK               0U
#define SIP_SMC_STATUS_ERROR            4U

/* Common SDM response codes (see firmware mbox_common.h / mbox_cmd_error.h) */
#define SEU_SDM_RESP_STATOK                0x000U
#define SEU_SDM_RESP_INVALID_COMMAND       0x001U
#define SEU_SDM_RESP_INVALID_COMMAND_PARAMS 0x004U
#define SEU_SDM_RESP_INVALID_ADDR          0x009U
#define SEU_SDM_RESP_TIMEOUT               0x00BU
#define SEU_SDM_RESP_ERROR_INJECT_FAIL     0x080U
#define SEU_SDM_RESP_NOT_CONFIGURED        0x100U
#define SEU_SDM_RESP_DEVICE_BUSY           0x1FFU
#define SEU_SDM_RESP_ERROR                 0x3FFU

/*
 * SDM returns 0x1FF while the SEU engine / mailbox is still settling after
 * config. ATF VAB already retries this; without a delay the sector probe
 * burns all indices as hard failures. Match VAB: 50 ms * N retries.
 */
#define SEU_MBOX_BUSY_RETRY_MAX            40U
#define SEU_MBOX_BUSY_RETRY_DELAY_US       50000U

#define SEU_BUFFER_SIZE    16

/*
 * SiP mailbox cmd/resp payloads must be >= platform BL31_LIMIT or ATF rejects
 * them via is_address_in_ddr_range().
 *
 *   Agilex3 BL31_LIMIT = 0x800F0000
 *   Agilex5/72 BL31_LIMIT = 0x82000000
 *
 * Use the shared mailbox scratch window at 0x821xxxxx (same region as
 * mailbox_selftest). Hardcoding deeper into DDR (e.g. 0x83800000) blows up on
 * Simics configs that only back the low DRAM window: the access becomes an
 * async SError, and the next SMC trips ATF's reflect_pending_async_ea panic
 * at sync_exception_aarch64 (PC 0x8000cc20).
 */
#define SEU_DDR_CMD_ADDR          0x82100400UL
#define SEU_DDR_RESP_ADDR         0x82100500UL
#define SEU_OPS_BUFFER_BYTES      ((size_t)SEU_BUFFER_SIZE * sizeof(uint32_t))

static uint32_t *const seu_cmd_buffer = (uint32_t *)SEU_DDR_CMD_ADDR;
static uint32_t *const seu_resp_buffer = (uint32_t *)SEU_DDR_RESP_ADDR;

typedef struct {
    volatile int count;
} seu_semphr_t;

struct seu_context
{
    seu_semphr_t seu_semphr;
    bool initialized;
    seu_call_back_t seu_call_back;
};

static inline seu_semphr_t osal_semaphore_create(int init_val)
{
    seu_semphr_t sem = { .count = init_val };
    return sem;
}

static struct seu_context seu_descriptor;

static const char *seu_resp_str(uint64_t code)
{
    switch (code)
    {
    case SEU_SDM_RESP_STATOK:                return "STATOK";
    case SEU_SDM_RESP_INVALID_COMMAND:       return "INVALID_COMMAND";
    case SEU_SDM_RESP_INVALID_COMMAND_PARAMS:return "INVALID_COMMAND_PARAMS";
    case SEU_SDM_RESP_INVALID_ADDR:          return "INVALID_ADDR";
    case SEU_SDM_RESP_TIMEOUT:               return "TIMEOUT";
    case SEU_SDM_RESP_ERROR_INJECT_FAIL:     return "ERROR_INJECT_FAIL "
                                                    "(SEU fault-inject feature "
                                                    "not enabled in bitstream "
                                                    "main descriptor)";
    case SEU_SDM_RESP_NOT_CONFIGURED:        return "NOT_CONFIGURED "
                                                    "(FPGA not in user mode)";
    case SEU_SDM_RESP_DEVICE_BUSY:           return "DEVICE_BUSY";
    case SEU_SDM_RESP_ERROR:                 return "ERROR";
    default:                                 return "UNKNOWN";
    }
}

static int32_t seu_mbox_send_v1(uint32_t cmd,
                               uint32_t *args, uint32_t arg_bytes,
                               uint32_t *resp, uint32_t resp_bytes,
                               const char *cmd_name)
{
    uint64_t smc_args[SMC_CALL_REG_COUNT] = { 0 };
    int sip_status;
    uint32_t arg_words = 0U;
    uint32_t resp_words = 0U;
    uint32_t busy_try;

    if (!seu_descriptor.initialized)
    {
        return -EIO;
    }

    if ((args != NULL) && (arg_bytes != 0U))
    {
        if ((arg_bytes % 4U) != 0U)
        {
            return -EINVAL;
        }
        arg_words = arg_bytes / 4U;
        cache_force_write_back(args, arg_bytes);
    }

    if ((resp != NULL) && (resp_bytes != 0U))
    {
        if ((resp_bytes % 4U) != 0U)
        {
            return -EINVAL;
        }
        resp_words = resp_bytes / 4U;
    }

    for (busy_try = 0U; busy_try <= SEU_MBOX_BUSY_RETRY_MAX; busy_try++)
    {
        if ((resp != NULL) && (resp_bytes != 0U))
        {
            cache_force_invalidate(resp, resp_bytes);
        }

        smc_args[0] = cmd;
        smc_args[1] = (uint64_t)(uintptr_t)args;
        smc_args[2] = arg_words;
        smc_args[3] = 0U;
        smc_args[4] = (uint64_t)(uintptr_t)resp;
        smc_args[5] = resp_words;

        sip_status = smc_call(SIP_SMC_MBOX_SEND_CMD, smc_args);

        /* SiP ERROR with SDM err in X1, or SiP OK with non-zero SDM status. */
        if (((sip_status == SIP_SMC_STATUS_ERROR) ||
             (sip_status == SIP_SMC_STATUS_OK)) &&
            (smc_args[0] == SEU_SDM_RESP_DEVICE_BUSY))
        {
            if (busy_try < SEU_MBOX_BUSY_RETRY_MAX)
            {
                udelay(SEU_MBOX_BUSY_RETRY_DELAY_US);
                continue;
            }
            printf("[SEU] %s: SDM still busy after %u retries (0x1FF)\n",
                   cmd_name, SEU_MBOX_BUSY_RETRY_MAX);
            return -EIO;
        }

        if ((sip_status == SIP_SMC_STATUS_ERROR) && (smc_args[0] != 0UL))
        {
            printf("[SEU] %s: SDM rejected (err_code=0x%lx %s)\n",
                   cmd_name,
                   (unsigned long)smc_args[0],
                   seu_resp_str(smc_args[0]));
            return -EIO;
        }
        if (sip_status != SIP_SMC_STATUS_OK)
        {
            printf("[SEU] %s: SiP rejected (status=%d)\n",
                   cmd_name, sip_status);
            return -EIO;
        }
        if (smc_args[0] != 0UL)
        {
            printf("[SEU] %s: SDM rejected (err_code=0x%lx %s)\n",
                   cmd_name,
                   (unsigned long)smc_args[0],
                   seu_resp_str(smc_args[0]));
            return -EIO;
        }

        if ((resp != NULL) && (resp_bytes != 0U))
        {
            cache_force_invalidate(resp, resp_bytes);
        }
        return 0;
    }

    return -EIO;
}

void seu_set_call_back(seu_call_back_t call_back)
{
    seu_descriptor.seu_call_back = call_back;
}

int32_t seu_init(void)
{
    volatile uint32_t probe;

    seu_descriptor.seu_semphr = osal_semaphore_create(1);
    seu_descriptor.initialized = true;

    /*
     * Touch the SiP scratch window once up front.  An unmapped address
     * here becomes an async SError that only surfaces later as ATF
     * "PANIC at PC : 0x8000cc20" on the first SMC — fail loudly instead.
     */
    seu_cmd_buffer[0] = 0xA5A5A5A5U;
    seu_resp_buffer[0] = 0x5A5A5A5AU;
    probe = seu_cmd_buffer[0];
    if (probe != 0xA5A5A5A5U) {
        printf("[SEU] scratch probe failed at 0x%lx (read 0x%x)\n",
               (unsigned long)SEU_DDR_CMD_ADDR, probe);
        seu_descriptor.initialized = false;
        return -EIO;
    }
    (void)memset(seu_cmd_buffer, 0, SEU_OPS_BUFFER_BYTES);
    (void)memset(seu_resp_buffer, 0, SEU_OPS_BUFFER_BYTES);
    printf("[SEU] SiP scratch cmd=0x%lx resp=0x%lx\n",
           (unsigned long)SEU_DDR_CMD_ADDR,
           (unsigned long)SEU_DDR_RESP_ADDR);

    /*
     * NOTE: Interrupt-driven SEU notifications are intentionally not enabled.
     *       The SEU example exercises driver APIs synchronously via the SDM
     *       mailbox; SDM completion is reported in the mailbox response.
     */
    return 0;
}

int32_t seu_insert_safe_err(seu_err_params_t err_params)
{
    int32_t ret;

    (void)memset(seu_cmd_buffer, 0, SEU_OPS_BUFFER_BYTES);
    if (!seu_descriptor.initialized)
    {
        printf("Error: SEU driver not initialized\n");
        return -EIO;
    }
    /*
     * Per SDM mbox_insert_safe_seu_error_hdlr (firmware error_reporting.c):
     *   cmd_buf[1] b[3:0]   = inject count   (max MAX_SEU_INJECT_COUNT == 1 ==> 2 errors)
     *   cmd_buf[1] b[5:4]   = inject mode    (0=immediate, 1=before, 2=after detect)
     *   cmd_buf[1] b[23:16] = sector index   (into cnoc_topography)
     *   cmd_buf[2] b[3:0]   = cram_sel0      (< MAX_SEU_INJECT_LOC_ENTRY)
     *   cmd_buf[2] b[7:4]   = cram_sel1      (< MAX_SEU_INJECT_LOC_ENTRY,
     *                                         must differ from cram_sel0 if
     *                                         inject_count == 1)
     */
    if ((err_params.injection_cycle > 2U) ||
            (err_params.no_of_injection > 1U) ||
            (err_params.cram_sel0 > 0xFU) ||
            (err_params.cram_sel1 > 0xFU))
    {
        printf("Invalid parameters: injection_cycle (0..2), no_of_injection "
               "(0=1 err, 1=2 errs), cram_sel0/1 (<=0xF)\n");
        return -EINVAL;
    }

    if ((err_params.no_of_injection == 1U) &&
            (err_params.cram_sel0 == err_params.cram_sel1))
    {
        printf("Invalid parameters: cram_sel0 must differ from cram_sel1 "
               "when no_of_injection == 1 (= 2 errors)\n");
        return -EINVAL;
    }

    seu_cmd_buffer[0] = ((uint32_t)err_params.sector_addr << 16) |
            ((uint32_t)err_params.injection_cycle << 4) |
            ((uint32_t)err_params.no_of_injection);
    seu_cmd_buffer[1] = ((uint32_t)err_params.cram_sel0) |
            ((uint32_t)err_params.cram_sel1 << 4);

    ret = seu_mbox_send_v1(SEU_INSERT_SAFE_ERR_CMD,
                           seu_cmd_buffer, SEU_INSERT_SAFE_ERR_BYTES,
                           NULL, 0U, "seu_insert_safe_err");
    return ret;
}

read_err_data_t seu_read_err(void)
{
    int32_t ret;
    read_err_data_t err_data;

    (void)memset(seu_resp_buffer, 0, SEU_OPS_BUFFER_BYTES);
    (void)memset(&err_data, 0, sizeof(read_err_data_t));
    if (!seu_descriptor.initialized)
    {
        printf("Error: SEU driver not initialized\n");
        err_data.op_state = -EIO;
        return err_data;
    }

    ret = seu_mbox_send_v1(SEU_READ_ERR_CMD,
                           NULL, 0U,
                           seu_resp_buffer, SEU_READ_ERR_RESP_BYTES,
                           "seu_read_err");
    if (ret != 0)
    {
        err_data.op_state = -EIO;
        return err_data;
    }

    err_data.op_state = 0;
    err_data.err_cnt = seu_resp_buffer[0];
    err_data.sector_addr = (uint8_t)((seu_resp_buffer[1] >> 16) & 0xFFU);
    err_data.err_type = (uint8_t)((seu_resp_buffer[2] >> 29) & 0x7U);
    err_data.node_specific_status = (uint16_t)(seu_resp_buffer[2] & 0x7FFU);
    err_data.correction_status = ((seu_resp_buffer[2] & (1UL << 28)) != 0U);

    return err_data;
}

seu_stat_t seu_read_stat(uint8_t sec_addr)
{
    int32_t ret;
    seu_stat_t seu_read_stats;

    (void)memset(seu_resp_buffer, 0, SEU_OPS_BUFFER_BYTES);
    (void)memset(seu_cmd_buffer, 0, SEU_OPS_BUFFER_BYTES);
    (void)memset(&seu_read_stats, 0, sizeof(seu_stat_t));
    if (!seu_descriptor.initialized)
    {
        printf("Error: SEU driver not initialized\n");
        seu_read_stats.op_state = -EIO;
        return seu_read_stats;
    }

    seu_cmd_buffer[0] = (uint32_t)sec_addr << 16;

    ret = seu_mbox_send_v1(SEU_READ_STATS,
                           seu_cmd_buffer, SEU_READ_STATS_CMD_BYTES,
                           seu_resp_buffer, SEU_READ_STAT_RESP_BYTES,
                           "seu_read_stat");
    if (ret != 0)
    {
        seu_read_stats.op_state = -EIO;
        return seu_read_stats;
    }

    seu_read_stats.op_state = 0;
    seu_read_stats.t_seu_cycle = seu_resp_buffer[0];
    seu_read_stats.t_seu_detect = seu_resp_buffer[1];
    seu_read_stats.t_seu_correct = seu_resp_buffer[2];
    seu_read_stats.t_seu_inject_detect = seu_resp_buffer[3];
    seu_read_stats.t_sdm_seu_poll_interval = seu_resp_buffer[4];

    return seu_read_stats;
}

int32_t seu_insert_fpga_ram_err(uint8_t err_mode, uint8_t ram_id, uint8_t
        sector_addr)
{
    int32_t ret;

    (void)memset(seu_cmd_buffer, 0, SEU_OPS_BUFFER_BYTES);

    if (!seu_descriptor.initialized)
    {
        printf("Error: SEU driver not initialized\n");
        return -EIO;
    }

    if ((err_mode < 1U) || (err_mode > 2U) || (ram_id > 0x1FU))
    {
        printf("Invalid parameters: err_mode must be 1 (single-bit) or 2 "
               "(double-bit); ram_id <= 0x1F\n");
        return -EINVAL;
    }

    seu_cmd_buffer[0] = ((uint32_t)sector_addr << 16) | ((uint32_t)ram_id << 2) |
            ((uint32_t)err_mode);

    ret = seu_mbox_send_v1(SEU_INJECT_FPGA_RAM_ERR_CMD,
                           seu_cmd_buffer, SEU_INJECT_FPGA_RAM_ERR_BYTES,
                           NULL, 0U, "seu_insert_fpga_ram_err");
    return ret;
}

int32_t seu_get_first_lsm_sector(uint8_t max_idx, uint8_t *out_sector)
{
    if ((out_sector == NULL) || (max_idx == 0U))
    {
        return -EINVAL;
    }

    for (uint8_t idx = 0U; idx < max_idx; idx++)
    {
        seu_stat_t s = seu_read_stat(idx);
        if (s.op_state == 0U)
        {
            *out_sector = idx;
            return 0;
        }
    }

    return -ENODEV;
}

int32_t seu_deinit(void)
{
    (void)memset(&seu_descriptor, 0, sizeof(seu_descriptor));
    return 0;
}
