/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_iossm_ll.c
 *
 * IOSSM source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "errno.h"
#include "socfpga_iossm_ll.h"
#include "mmio.h"
#include "cache.h"

/*
 * Internal constants
 */
#define IOSSM_LL_DDR_ALIGN_BYTES    8U  /* Required alignment for 64-bit DDR access */
#define IOSSM_LL_RESP_READY_BIT     1U  /* Bit 0: response-ready flag in RESP_STAT  */
#define IOSSM_LL_CMD_BUSY_BIT       1U  /* Bit 0: command-busy flag in CMD_REQ      */
#define IOSSM_LL_MAX_INSTANCE       2U  /* Maximum number of IOSSM instances        */

/*
 * Memory barrier
 * Ensures all prior memory accesses are globally observed before the next
 * instruction (used around error-injection write sequences).
 */
#define IOSSM_LL_SYSTEM_BARRIER()                     \
    __asm__ volatile (                                 \
        "dmb sy\n"                                     \
        "isb\n"                                        \
        :                                              \
        :                                              \
        : "memory"                                     \
    )

/*
 * Module-level command formatter state
 * One formatter is sufficient because the LL driver is not re-entrant by
 * design (bare-metal).
 */
static iossm_ll_req_payload_t s_req_format;

/*
 * Logic to create a delay of 40us without using DDR
 * This means using no stack/heap/data sections and only CPU registers
 * This logic is not portable as this might cause register clobering
 * If some one wants to reuse this logic, please inspect the assembly
 * and make sure no clobering is happening
 */
__attribute__((always_inline)) static inline void iossm_ll_wait_40us(void)
{
    __asm__ volatile (
        "mrs    x1, CNTFRQ_EL0          \n"  /* timer frequency              */
        "mov    x2, #40                 \n"  /* 40 microseconds              */
        "mul    x2, x1, x2              \n"  /* freq * 40                    */
        "movz   x3, #0x4240             \n"
        "movk   x3, #0xF, lsl #16       \n"  /* x3 = 1 000 000               */
        "udiv   x2, x2, x3              \n"  /* ticks for 40 s              */
        "mrs    x4, CNTVCT_EL0          \n"  /* capture start count          */
        "1:                             \n"
        "mrs    x5, CNTVCT_EL0          \n"
        "sub    x6, x5, x4              \n"
        "cmp    x6, x2                  \n"
        "blo    1b                      \n"
        :
        :
        : "x1", "x2", "x3", "x4", "x5", "x6", "cc"
    );
}

/*
 * Populate an iossm_ll_req_payload_t for a given opcode.
 *
 * Sets the param_type register offset and cmd_type field used to build
 * the CMD_REQ word.
 */
static void iossm_ll_format_command(iossm_ll_req_payload_t *fmt)
{
    switch (fmt->opcode)
    {
        case IOSSM_LL_GET_SYS_INFO:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_SYSTEM_INFO;
            break;

        case IOSSM_LL_ECC_EN:
            fmt->param_type = CMD_PARAM0_REG_OFFSET;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_EN_STAT:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_INT_STAT:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_INT_ACK:
            fmt->param_type = CMD_PARAM0_REG_OFFSET;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_INT_MASK:
            fmt->param_type = CMD_PARAM0_REG_OFFSET;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_GET_SBE_INFO:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_GET_DBE_INFO:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_WRBK_EN:
            fmt->param_type = CMD_PARAM0_REG_OFFSET;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_ERR_INJ:
            fmt->param_type = CMD_PARAM0_REG_OFFSET;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        case IOSSM_LL_ECC_CLEAR_ERR:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;

        default:
            fmt->param_type = IOSSM_LL_NO_PARAM;
            fmt->cmd_type   = IOSSM_LL_TRIG_CNTRL_OP;
            break;
    }
}

uint32_t iossm_ll_read_reg32(uint32_t base_addr, uint32_t reg_offset)
{
    return RD_REG32(base_addr + reg_offset);
}

void iossm_ll_write_reg32(uint32_t base_addr, uint32_t reg_offset, uint32_t value)
{
    WR_REG32((base_addr + reg_offset), value);
}

/*
 * Safe memory write-protection
 */
int32_t iossm_ll_safe_mem_write64(uint64_t ddr_addr, uint64_t value)
{
    /* Bounds check: address range must be entirely within the DDR window */
    if ((ddr_addr < IOSSM_DDR_BASE_ADDR) ||
        (ddr_addr > (IOSSM_DDR_END_ADDR - (IOSSM_LL_DDR_ALIGN_BYTES - 1ULL))))
    {
        return IOSSM_LL_MEM_ERANGE;
    }

    /* Alignment check: must be 8-byte aligned */
    if ((ddr_addr & (IOSSM_LL_DDR_ALIGN_BYTES - 1ULL)) != 0ULL)
    {
        return IOSSM_LL_MEM_EALIGN;
    }

    volatile uint64_t *ptr = (volatile uint64_t *)(uintptr_t)ddr_addr;
    *ptr = value;

    return IOSSM_LL_MEM_OK;
}

int32_t iossm_ll_safe_mem_read64(uint64_t ddr_addr, uint64_t *out_value)
{
    if (out_value == NULL)
    {
        return -EINVAL;
    }

    if ((ddr_addr < IOSSM_DDR_BASE_ADDR) ||
        (ddr_addr > (IOSSM_DDR_END_ADDR - (IOSSM_LL_DDR_ALIGN_BYTES - 1ULL))))
    {
        return IOSSM_LL_MEM_ERANGE;
    }

    if ((ddr_addr & (IOSSM_LL_DDR_ALIGN_BYTES - 1ULL)) != 0ULL)
    {
        return IOSSM_LL_MEM_EALIGN;
    }

    volatile const uint64_t *ptr = (volatile const uint64_t *)(uintptr_t)ddr_addr;
    *out_value = *ptr;

    return IOSSM_LL_MEM_OK;
}

int32_t iossm_ll_get_base_addr(uint32_t instance, uint32_t *base_addr)
{
    static const uint32_t base_table[IOSSM_LL_MAX_INSTANCE] =
    {
        IOSSM0_BASE_ADDR,
        IOSSM1_BASE_ADDR,
    };

    if ((instance >= IOSSM_LL_MAX_INSTANCE) || (base_addr == NULL))
    {
        return -EINVAL;
    }

    *base_addr = base_table[instance];
    return 0;
}

iossm_ll_response_t iossm_ll_send_command(const iossm_ll_desc_t *desc,
                                          uint32_t request,
                                          uint32_t param)
{
    uint32_t volatile status  = 0U;
    uint32_t volatile cmd_req = 0U;
    uint32_t volatile reg_val = 0U;
    iossm_ll_response_t response;

    (void)memset(&response, 0, sizeof(response));

    s_req_format.opcode = request;
    iossm_ll_format_command(&s_req_format);

    /* Wait until any previous command has been consumed (CMD_REQ busy clear) */
    do {
        status = iossm_ll_read_reg32(desc->base_addr, CMD_REQ_REG_OFFSET);
    } while ((status & IOSSM_LL_CMD_BUSY_BIT) == IOSSM_LL_CMD_BUSY_BIT);

    /* Write parameter register if the opcode requires one */
    if (s_req_format.param_type != IOSSM_LL_NO_PARAM)
    {
        iossm_ll_write_reg32(desc->base_addr, s_req_format.param_type, param);
    }

    /* Build and submit CMD_REQ word */
    cmd_req = (request                  <<  0U) |
              (s_req_format.cmd_type    << 16U) |
              (desc->instance_id        << 24U) |
              (desc->ip_type            << 29U);

    iossm_ll_write_reg32(desc->base_addr, CMD_REQ_REG_OFFSET, cmd_req);

    /* Poll until the response-ready bit is set */
    do {
        status = iossm_ll_read_reg32(desc->base_addr, RESP_STAT_REG_OFF);
    } while ((status & IOSSM_LL_RESP_READY_BIT) != IOSSM_LL_RESP_READY_BIT);

    /* Clear the response-ready bit */
    reg_val  = iossm_ll_read_reg32(desc->base_addr, RESP_STAT_REG_OFF);
    reg_val &= ~(1U << 0U);
    iossm_ll_write_reg32(desc->base_addr, RESP_STAT_REG_OFF, reg_val);

    /* Capture response words */
    response.status = status;
    response.resp0  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP0_REG_OFF);
    response.resp1  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP1_REG_OFF);
    response.resp2  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP2_REG_OFF);

    return response;
}

iossm_ll_response_t iossm_ll_err_inject_command(const iossm_ll_desc_t *desc,
                                                uint64_t ddr_addr,
                                                uint32_t param)
{
    uint32_t volatile status  = 0U;
    uint32_t volatile cmd_req = 0U;
    uint32_t volatile reg_val = 0U;
    iossm_ll_response_t response;
    uint64_t read_back = 0ULL;
    int32_t  mem_ret;

    (void)memset(&response, 0, sizeof(response));

    /* Validate DDR address before any memory touch */
    mem_ret = iossm_ll_safe_mem_write64(ddr_addr, 0ULL);
    if (mem_ret != IOSSM_LL_MEM_OK)
    {
        /* Return empty response; caller inspects response.status == 0 */
        return response;
    }

    s_req_format.opcode = IOSSM_LL_ECC_ERR_INJ;
    iossm_ll_format_command(&s_req_format);

    /* Wait for previous command to complete */
    do {
        status = iossm_ll_read_reg32(desc->base_addr, CMD_REQ_REG_OFFSET);
    } while ((status & IOSSM_LL_CMD_BUSY_BIT) == IOSSM_LL_CMD_BUSY_BIT);

    /* Write injection parameter */
    if (s_req_format.param_type != IOSSM_LL_NO_PARAM)
    {
        iossm_ll_write_reg32(desc->base_addr, s_req_format.param_type, param);
    }

    /* Build CMD_REQ */
    cmd_req = (IOSSM_LL_ECC_ERR_INJ       <<  0U) |
              (s_req_format.cmd_type       << 16U) |
              (desc->instance_id           << 24U) |
              (desc->ip_type               << 29U);

    IOSSM_LL_SYSTEM_BARRIER();
    iossm_ll_write_reg32(desc->base_addr, CMD_REQ_REG_OFFSET, cmd_req);
    IOSSM_LL_SYSTEM_BARRIER();

    /* Allow the ECC engine to arm before the fault-trigger write */
    iossm_ll_wait_40us();

    /* Write sentinel data to trigger the error, then read back to propagate */
    (void)iossm_ll_safe_mem_write64(ddr_addr, IOSSM_LL_ERROR_DATA_VALUE);
    (void)iossm_ll_safe_mem_read64 (ddr_addr, &read_back);
    (void)read_back;
    IOSSM_LL_SYSTEM_BARRIER();

    /* Poll for response */
    do {
        status = iossm_ll_read_reg32(desc->base_addr, RESP_STAT_REG_OFF);
    } while ((status & IOSSM_LL_RESP_READY_BIT) != IOSSM_LL_RESP_READY_BIT);

    /* Clear response-ready bit */
    reg_val  = iossm_ll_read_reg32(desc->base_addr, RESP_STAT_REG_OFF);
    reg_val &= ~(1U << 0U);
    iossm_ll_write_reg32(desc->base_addr, RESP_STAT_REG_OFF, reg_val);

    response.status = status;
    response.resp0  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP0_REG_OFF);
    response.resp1  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP1_REG_OFF);
    response.resp2  = iossm_ll_read_reg32(desc->base_addr, CMD_RESP2_REG_OFF);

    return response;
}

