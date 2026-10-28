/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: iossm_selftest.c
 *
 * Iossm Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Iossm Example
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "errno.h"

#include "../api/console/console_api.h"
#include "../api/iossm/iossm_api.h"
#include "example_register.h"

/*
 * Demo constants
 */
#define IOSSM_DEMO_LOAD_ADDR     0x0000000090000000ULL
#define IOSSM_DEMO_IMAGE_SIZE    64U
#define IOSSM_DEMO_INJ_ADDR      0x00000000A0000000ULL

/*
 * Synthetic firmware image
 */
static const uint64_t demo_image[IOSSM_DEMO_IMAGE_SIZE / sizeof(uint64_t)] =
{
    0xAA55AA55AA55AA55ULL,
    0x0102030405060708ULL,
    0xDEADBEEFDEADBEEFULL,
    0x0000000000001000ULL,
    0x0000000080008000ULL,
    0x1122334455667788ULL,
    0xCAFEBABECAFEBABEULL,
    0x0000000000000000ULL,
};

/*
 * Internal helpers
 */
static void print_result(const char *label, int rc)
{
    if (rc == 0)
        printf("  [PASS] %s\n", label);
    else
        printf("  [FAIL] %s (rc=%d)\n", label, rc);
}

static int demo_load_image(uint64_t base)
{
    int      rc        = 0;
    uint32_t num_words = (uint32_t)(IOSSM_DEMO_IMAGE_SIZE / sizeof(uint64_t));

    printf("  Loading %u-byte image to 0x%llx ...\n",
           IOSSM_DEMO_IMAGE_SIZE, (unsigned long long)base);

    for (uint32_t i = 0U; i < num_words; i++)
    {
        uint64_t addr = base + ((uint64_t)i * sizeof(uint64_t));
        int32_t  wr   = iossm_api_mem_write64(addr, demo_image[i]);
        if (wr != IOSSM_API_MEM_OK)
        {
            printf("  [FAIL] safe_mem_write64 word %u (addr=0x%llx rc=%d)\n",
                   i, (unsigned long long)addr, wr);
            rc = wr;
            break;
        }
    }
    return rc;
}

static int demo_verify_image(uint64_t base)
{
    int      rc         = 0;
    uint32_t num_words  = (uint32_t)(IOSSM_DEMO_IMAGE_SIZE / sizeof(uint64_t));
    uint32_t mismatches = 0U;

    printf("  Verifying image at 0x%llx ...\n", (unsigned long long)base);

    for (uint32_t i = 0U; i < num_words; i++)
    {
        uint64_t addr      = base + ((uint64_t)i * sizeof(uint64_t));
        uint64_t read_back = 0ULL;

        int32_t rd = iossm_api_mem_read64(addr, &read_back);
        if (rd != IOSSM_API_MEM_OK)
        {
            printf("  [FAIL] safe_mem_read64 word %u (addr=0x%llx rc=%d)\n",
                   i, (unsigned long long)addr, rd);
            rc = rd;
            break;
        }

        if (read_back != demo_image[i])
        {
            printf("  [MISMATCH] word %u: expected 0x%016llx got 0x%016llx\n",
                   i,
                   (unsigned long long)demo_image[i],
                   (unsigned long long)read_back);
            mismatches++;
        }
    }

    if ((rc == 0) && (mismatches == 0U))
        printf("  All %u words match.\n", num_words);
    else if (mismatches > 0U)
    {
        printf("  %u mismatch(es) detected.\n", mismatches);
        rc = -1;
    }
    return rc;
}

/*
 * Main demo command
 */
void cmd_iossm_demo(const char *args)
{
    (void)args;

    int            rc;
    int32_t        ecc_count;
    iossm_handle_t handle;

    printf("\n=== IOSSM Image Load to DDR Demo ===\n\n");

    printf("[Step 1] Open IOSSM instance 0\n");
    handle = iossm_api_open(IOSSM_API_INSTANCE_0);
    if (handle == NULL)
    {
        printf("  [FAIL] iossm_api_open returned NULL\n");
        return;
    }
    printf("  [PASS] Instance opened\n");

    rc = iossm_api_enable_ecc(handle);
    print_result("Enable ECC", rc);
    if (rc != 0)
        goto demo_cleanup;

    printf("\n[Step 2] Load image to DDR (0x%llx)\n",
           (unsigned long long)IOSSM_DEMO_LOAD_ADDR);
    rc = demo_load_image(IOSSM_DEMO_LOAD_ADDR);
    print_result("Image load", rc);
    if (rc != 0)
        goto demo_cleanup;

    printf("\n[Step 3] Verify image\n");
    rc = demo_verify_image(IOSSM_DEMO_LOAD_ADDR);
    print_result("Image verify", rc);

    printf("\n[Step 4] ECC status after image load\n");
    ecc_count = iossm_api_get_ecc_status(handle);
    if (ecc_count < 0)
        printf("  [FAIL] get_ecc_status returned %d\n", ecc_count);
    else if (ecc_count == 0)
        printf("  [PASS] ECC error count = 0 (no errors during load)\n");
    else
        printf("  [WARN] ECC error count = %d after load\n", ecc_count);

    printf("\n[Step 5] Inject single-bit (correctable) ECC error\n");
    printf("  Target address: 0x%llx\n", (unsigned long long)IOSSM_DEMO_INJ_ADDR);
    rc = iossm_api_inject_sbe(handle, IOSSM_DEMO_INJ_ADDR);
    print_result("Inject SBE", rc);
    if (rc == 0)
    {
        ecc_count = iossm_api_get_ecc_status(handle);
        printf("  ECC error count after SBE injection: %d\n", ecc_count);
        (void)iossm_api_ack_interrupt(handle, IOSSM_API_INT_CRCT_EVENT |
                                              IOSSM_API_INT_RD_SIN_BIT |
                                              IOSSM_API_INT_WR_SIN_BIT);
        printf("  Interrupt acknowledged\n");
    }

    printf("\n[Step 6] Inject double-bit (uncorrectable) ECC error\n");
    printf("  Target address: 0x%llx\n",
           (unsigned long long)(IOSSM_DEMO_INJ_ADDR + 8ULL));
    rc = iossm_api_inject_dbe(handle, IOSSM_DEMO_INJ_ADDR + 8ULL);
    print_result("Inject DBE", rc);
    if (rc == 0)
    {
        ecc_count = iossm_api_get_ecc_status(handle);
        printf("  ECC error count after DBE injection: %d\n", ecc_count);
        (void)iossm_api_ack_interrupt(handle, IOSSM_API_INT_UNCRCT_EVENT |
                                              IOSSM_API_INT_RD_DBL_BIT  |
                                              IOSSM_API_INT_WR_DBL_BIT);
        printf("  Interrupt acknowledged\n");
    }

    printf("\n[Step 7] Clear ECC error buffer\n");
    rc = iossm_api_clear_ecc_errors(handle);
    print_result("Clear error buffer", rc);
    ecc_count = iossm_api_get_ecc_status(handle);
    printf("  ECC error count after clear: %d\n", ecc_count);

demo_cleanup:
    printf("\n[Cleanup] Closing IOSSM instance 0\n");
    rc = iossm_api_close(IOSSM_API_INSTANCE_0);
    print_result("Close instance", rc);
    printf("\n=== IOSSM Demo complete ===\n\n");
}

/*
 * CLI registration
 */
void register_iossm_example(void)
{
    cli_register_command("iossm_demo", cmd_iossm_demo);
}

APP_REGISTER(register_iossm_example)


