/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: seu_selftest.c
 *
 * Seu Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Seu Example
 */

#include <stdint.h>
#include <stdio.h>
#include "console_api.h"
#include "example_register.h"
#include "seu_api.h"

/* ---------------------------------------------------------------------- */
/* Demo parameters                                                         */
/* ---------------------------------------------------------------------- */
/* SEU driver uses V1 INTEL_SIP_SMC_MBOX_SEND_CMD (sync BL31 path). */
#define SEU_DEMO_PROBE_MAX                   8U
#define SEU_DEMO_CRAM_SEL0                   0U
#define SEU_DEMO_CRAM_SEL1                   1U
#define SEU_DEMO_INJECTION_CYCLE             0U   /* 0=immediate, 1=before-detect, 2=after-detect */
#define SEU_DEMO_COUNT                       1U   /* errors to inject: 1 or 2 */

/* Parameters for FPGA-fabric LSM NIOS RAM error injection. */
#define SEU_DEMO_FPGA_RAM_ERR_MODE           SEU_API_FPGA_RAM_ERR_MODE_SBE
#define SEU_DEMO_FPGA_RAM_ID                 0U   /* target RAM channel (0..31) */

#define SEU_DEMO_POLL_ATTEMPTS               4U
#define SEU_DEMO_FPGA_RAM_VERIFY_ATTEMPTS    2U
#define SEU_DEMO_POLL_DELAY_LOOPS            2000000U

/* ---------------------------------------------------------------------- */
/* Optional notification callback                                          */
/* ---------------------------------------------------------------------- */
static void seu_demo_callback(void)
{
    printf("[SEU] notification callback invoked\n");
}

/* ---------------------------------------------------------------------- */
/* Helpers: print API data types                                           */
/* ---------------------------------------------------------------------- */
static const char *seu_err_type_str(uint8_t t)
{
    switch (t)
    {
    case SEU_API_ERR_TYPE_NONE:           return "none";
    case SEU_API_ERR_TYPE_SINGLE_BIT:     return "single-bit";
    case SEU_API_ERR_TYPE_DOUBLE_BIT:     return "double-bit";
    case SEU_API_ERR_TYPE_MULTI_BIT:      return "multi-bit";
    case SEU_API_ERR_TYPE_CRAM_INTEGRITY: return "CRAM integrity";
    default:                              return "unknown";
    }
}

static void print_err_data(const seu_api_err_data_t *d)
{
    printf("  sector  : 0x%02x\n",  (unsigned int)d->sector_addr);
    printf("  type    : %s\n",       seu_err_type_str(d->err_type));
    printf("  count   : %u\n",       (unsigned int)d->err_cnt);
    printf("  status  : %s\n",       d->corrected ? "corrected" : "not corrected");
}

static void print_stat(const seu_api_stat_t *s)
{
    printf("  t_seu_cycle         : %u\n",  (unsigned int)s->t_seu_cycle);
    printf("  t_seu_detect        : %u\n",  (unsigned int)s->t_seu_detect);
    printf("  t_seu_correct       : %u\n",  (unsigned int)s->t_seu_correct);
    printf("  t_seu_inject_detect : %u\n",  (unsigned int)s->t_seu_inject_detect);
    printf("  t_poll_interval     : %u\n",  (unsigned int)s->t_poll_interval);
}

/* ---------------------------------------------------------------------- */
/* Helper: busy-wait between mailbox polls                                 */
/* ---------------------------------------------------------------------- */
static void seu_demo_busy_wait(uint32_t loops)
{
    volatile uint32_t i;
    for (i = 0U; i < loops; i++)
    {
        __asm__ volatile ("nop");
    }
}

/* ---------------------------------------------------------------------- */
/* Helper: poll seu_api_read_err() until SDM reports detection or stops.  */
/*                                                                         */
/* Returns 0 and populates *out_last on success.                          */
/* Returns -EIO and populates *out_attempts if transport fails.           */
/* When the queue stays empty for all attempts, returns 0 with            */
/* out_last->err_cnt == 0.                                                 */
/* ---------------------------------------------------------------------- */
static int seu_demo_poll_for_detection(uint32_t            max_attempts,
                                       seu_api_err_data_t *out_last,
                                       uint32_t           *out_attempts)
{
    seu_api_err_data_t err = { 0 };
    int      ret = 0;
    uint32_t i;

    for (i = 0U; i < max_attempts; i++)
    {
        ret = seu_api_read_err(&err);
        if (ret != 0)
        {
            break;
        }
        if ((err.err_cnt > 0U) || err.corrected)
        {
            i++;
            break;
        }
        seu_demo_busy_wait(SEU_DEMO_POLL_DELAY_LOOPS);
    }

    if (out_attempts != NULL)
    {
        *out_attempts = i;
    }
    if (out_last != NULL)
    {
        *out_last = err;
    }
    return ret;
}

/* ---------------------------------------------------------------------- */
/* Main demo command                                                        */
/* ---------------------------------------------------------------------- */
static void seu_demo_main(const char *args)
{
    (void)args;
    int ret;

    printf("\n==== SEU Demo Start ====\n\n");

    /* -------------------------------------------------------------- */
    /* Step 1: Initialise SEU driver (no GIC/IRQ in this sample).       */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 1: Initialise driver\n");
    ret = seu_api_init();
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_init rc=%d\n", ret);
        return;
    }
    printf("[SEU][PASS] seu_api_init\n\n");

    /* -------------------------------------------------------------- */
    /* Step 2: Register notification callback.                         */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 2: Register callback "
           "(notification path not active in this sample)\n\n");
    (void)seu_api_set_callback(seu_demo_callback);

    /* -------------------------------------------------------------- */
    /* Step 3: Discover a valid LSM sector index.                      */
    /* -------------------------------------------------------------- */
    uint8_t sector = 0U;
    printf("[SEU] Step 3: Discover valid LSM sector "
           "(probing up to %u indices)\n", SEU_DEMO_PROBE_MAX);
    ret = seu_api_get_first_valid_sector(SEU_DEMO_PROBE_MAX, &sector);
    if (ret != 0)
    {
        printf("[SEU][FAIL] No valid sector found (rc=%d) - "
               "check FPGA is in user mode / SEU not stuck DEVICE_BUSY\n",
               ret);
        (void)seu_api_deinit();
        return;
    }
    printf("[SEU][PASS] Found sector 0x%02x\n\n", sector);

    /* -------------------------------------------------------------- */
    /* Step 4: Read baseline SEU statistics and error queue.           */
    /* The baseline error snapshot lets later steps illustrate how    */
    /* err_cnt / err_type / corrected change after injection.         */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 4: Read baseline statistics and error queue "
           "(sector 0x%02x)\n", sector);

    seu_api_stat_t stats = { 0 };
    ret = seu_api_read_stat(sector, &stats);
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_read_stat rc=%d\n", ret);
    }
    else
    {
        print_stat(&stats);
    }

    seu_api_err_data_t baseline_err = { 0 };
    ret = seu_api_read_err(&baseline_err);
    if (ret != 0)
    {
        printf("[SEU][WARN] seu_api_read_err rc=%d\n", ret);
    }
    else
    {
        printf("  -- baseline error queue --\n");
        print_err_data(&baseline_err);
    }
    printf("\n");

    /* -------------------------------------------------------------- */
    /* Step 5: Inject a safe (non-destructive) CRAM SEU error.        */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 5: Inject safe CRAM SEU error "
           "(sector=0x%02x, cram_sel=%u/%u, count=%u)\n",
           sector, SEU_DEMO_CRAM_SEL0, SEU_DEMO_CRAM_SEL1, SEU_DEMO_COUNT);

    seu_api_inj_params_t inj = {
        .cram_sel0       = SEU_DEMO_CRAM_SEL0,
        .cram_sel1       = SEU_DEMO_CRAM_SEL1,
        .injection_cycle = SEU_DEMO_INJECTION_CYCLE,
        .count           = SEU_DEMO_COUNT,
    };
    ret = seu_api_insert_safe_err(sector, &inj);
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_insert_safe_err rc=%d\n", ret);
    }
    else
    {
        printf("[SEU][PASS] seu_api_insert_safe_err\n");
    }
    printf("\n");

    /* -------------------------------------------------------------- */
    /* Step 6: Poll for SEU detection (and correction if available).  */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 6: Poll for SEU detection/correction "
           "(up to %u attempts)\n", SEU_DEMO_POLL_ATTEMPTS);

    seu_api_err_data_t err_data = { 0 };
    uint32_t attempts = 0U;
    ret = seu_demo_poll_for_detection(SEU_DEMO_POLL_ATTEMPTS,
                                      &err_data, &attempts);
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_read_err failed (rc=%d) "
               "after attempt %u\n", ret, attempts);
    }
    else if (err_data.err_cnt == 0U)
    {
        printf("[SEU][WARN] No SEU reported after %u attempts "
               "(check FPGA user mode and FAULT_INJECT bitstream flag)\n",
               attempts);
    }
    else
    {
        printf("[SEU][PASS] SEU %s after %u attempt(s)\n",
               err_data.corrected ? "detected and corrected" : "detected",
               attempts);
        print_err_data(&err_data);
    }
    printf("\n");

    /* -------------------------------------------------------------- */
    /* Step 7: Post-injection statistics.                              */
    /* t_seu_detect and t_seu_inject_detect should differ from Step 4 */
    /* confirming the SDM observed the injected event.                */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 7: Post-injection statistics (sector 0x%02x)\n",
           sector);
    seu_api_stat_t stats_post = { 0 };
    ret = seu_api_read_stat(sector, &stats_post);
    if (ret != 0)
    {
        printf("[SEU][WARN] seu_api_read_stat rc=%d\n", ret);
    }
    else
    {
        print_stat(&stats_post);
    }
    printf("\n");

    /* -------------------------------------------------------------- */
    /* Step 8: Inject error into FPGA-fabric LSM NIOS RAM.            */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 8: Inject FPGA-fabric LSM NIOS RAM error "
           "(sector=0x%02x, mode=%s, ram_id=%u)\n",
           sector,
           (SEU_DEMO_FPGA_RAM_ERR_MODE == SEU_API_FPGA_RAM_ERR_MODE_SBE) ?
               "single-bit" : "double-bit",
           SEU_DEMO_FPGA_RAM_ID);

    ret = seu_api_inject_fpga_ram_err(sector, SEU_DEMO_FPGA_RAM_ERR_MODE,
                                      SEU_DEMO_FPGA_RAM_ID);
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_inject_fpga_ram_err rc=%d\n", ret);
        printf("\n");
    }
    else
    {
        printf("[SEU][PASS] seu_api_inject_fpga_ram_err\n\n");

        /* ---------------------------------------------------------- */
        /* Step 9: Verify the event appeared in the SDM error queue.  */
        /* ---------------------------------------------------------- */
        printf("[SEU] Step 9: Verify LSM NIOS RAM error in SDM queue "
               "(up to %u attempts)\n", SEU_DEMO_FPGA_RAM_VERIFY_ATTEMPTS);

        seu_api_err_data_t fpga_ram_err = { 0 };
        uint32_t fpga_ram_attempts = 0U;
        ret = seu_demo_poll_for_detection(SEU_DEMO_FPGA_RAM_VERIFY_ATTEMPTS,
                                          &fpga_ram_err, &fpga_ram_attempts);
        if (ret != 0)
        {
            printf("[SEU][FAIL] seu_api_read_err failed (rc=%d)\n", ret);
        }
        else if (fpga_ram_err.err_cnt == 0U)
        {
            printf("[SEU][WARN] LSM NIOS RAM error not yet in SDM queue "
                   "after %u attempts (event may arrive after demo ends)\n",
                   fpga_ram_attempts);
        }
        else
        {
            printf("[SEU][PASS] LSM NIOS RAM error confirmed after "
                   "%u attempt(s)\n", fpga_ram_attempts);
            print_err_data(&fpga_ram_err);
        }
        printf("\n");
    }

    /* -------------------------------------------------------------- */
    /* Step 10: Deinitialise.                                          */
    /* -------------------------------------------------------------- */
    printf("[SEU] Step 10: Deinitialise driver\n");
    ret = seu_api_deinit();
    if (ret != 0)
    {
        printf("[SEU][FAIL] seu_api_deinit rc=%d\n", ret);
    }
    else
    {
        printf("[SEU][PASS] seu_api_deinit\n");
    }

    printf("\n==== SEU Demo End ====\n\n");
}

/* ---------------------------------------------------------------------- */
/* CLI registration                                                        */
/* ---------------------------------------------------------------------- */
void register_seu_demo(void)
{
    cli_register_command("seu_selftest", seu_demo_main);
}

APP_REGISTER(register_seu_demo)

