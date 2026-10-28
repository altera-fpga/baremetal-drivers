/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: dma_selftest.c
 *
 * Dma Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Dma Example
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "errno.h"

#include "../api/console/console_api.h"
#include "../api/dma/dma_api.h"
#include "cache.h"
#include "example_register.h"

/* -------------------------------------------------------------------------
 * Demo parameters
 * ---------------------------------------------------------------------- */
#define DMA_DEMO_INSTANCE       0U       /* DMAC instance 0 */
#define DMA_DEMO_CHANNEL        0U       /* Channel 0 */
#define DMA_DEMO_SYNC_SIZE      256U     /* Bytes for synchronous transfer */
#define DMA_DEMO_ASYNC_SIZE     1024U    /* Bytes for asynchronous transfer */
#define DMA_DEMO_FILL_BYTE      0xA5U    /* Pattern for Step 2 */
#define DMA_DEMO_ASYNC_TIMEOUT  2000U    /* dma_wait() timeout in ms */

/*
 * Static DMA buffers, 64-byte aligned to match DMA LLI alignment requirements
 * and to prevent split cache-line issues during cache maintenance.
 */
static uint8_t demo_src[DMA_DEMO_ASYNC_SIZE] __attribute__((aligned(64)));
static uint8_t demo_dst[DMA_DEMO_ASYNC_SIZE] __attribute__((aligned(64)));

/* Set to 1 by the async completion callback */
static volatile int g_async_done;

/* -------------------------------------------------------------------------
 * Internal helpers
 * ---------------------------------------------------------------------- */
static void print_result(const char *label, int rc)
{
    if (rc == 0)
        printf("  [PASS] %s\n", label);
    else
        printf("  [FAIL] %s (rc=%d)\n", label, rc);
}

/* Verifies that every byte in buf[0..count-1] equals expected.
 * Returns: 0 on full match, -EIO on first mismatch.
 */
static int verify_uniform_byte(const uint8_t *buf, uint32_t count, uint8_t expected)
{
    for (uint32_t i = 0U; i < count; i++)
    {
        if (buf[i] != expected)
        {
            printf("  [MISMATCH] byte[%u]: expected 0x%02x got 0x%02x\n",
                   i, expected, buf[i]);
            return -EIO;
        }
    }
    return 0;
}

/** Completion callback invoked from interrupt context when the async DMA finishes. */
static void async_done_callback(void)
{
    g_async_done = 1;
}

/* -------------------------------------------------------------------------
 * Demo entry point
 * ---------------------------------------------------------------------- */
static void cmd_dma_demo(const char *args)
{
    (void)args;
    int rc;

    printf("\n=== DMA Memory-to-Memory Transfer Demo ===\n\n");

    /* ------------------------------------------------------------------
     * Step 1: Initialise DMA
     * ---------------------------------------------------------------- */
    printf("[Step 1] Initialise DMA (instance %u, channel %u)\n",
           DMA_DEMO_INSTANCE, DMA_DEMO_CHANNEL);

    rc = dma_init(DMA_DEMO_INSTANCE, DMA_DEMO_CHANNEL);
    print_result("dma_init", rc);
    if (rc != 0)
        return;

    /* ------------------------------------------------------------------
     * Step 2: Synchronous 256-byte transfer
     *
     * Cache discipline:
     *   cache_force_write_back(src)  - push CPU-cached writes to RAM so the
     *                                  DMA bus-master sees up-to-date data.
     *   cache_force_invalidate(dst)  - drop stale CPU cache lines for dst so
     *                                  the CPU reads DMA-written data after.
     * ---------------------------------------------------------------- */
    printf("\n[Step 2] Synchronous transfer (%u bytes, pattern 0x%02x)\n",
           DMA_DEMO_SYNC_SIZE, DMA_DEMO_FILL_BYTE);

    memset(demo_src, (int)DMA_DEMO_FILL_BYTE, DMA_DEMO_SYNC_SIZE);
    memset(demo_dst, 0x00,                    DMA_DEMO_SYNC_SIZE);

    cache_force_write_back(demo_src, DMA_DEMO_SYNC_SIZE);
    cache_force_invalidate(demo_dst, DMA_DEMO_SYNC_SIZE);

    rc = dma_memcpy(demo_dst, demo_src, DMA_DEMO_SYNC_SIZE);
    print_result("dma_memcpy (sync)", rc);
    if (rc != 0)
        goto demo_cleanup;

    rc = verify_uniform_byte(demo_dst, DMA_DEMO_SYNC_SIZE, DMA_DEMO_FILL_BYTE);
    print_result("Sync data verification", rc);
    if (rc != 0)
        goto demo_cleanup;

    printf("  All %u bytes match 0x%02x\n", DMA_DEMO_SYNC_SIZE, DMA_DEMO_FILL_BYTE);

    /* ------------------------------------------------------------------
     * Step 3: Asynchronous 1 KiB transfer
     *   - Fill source with incrementing pattern (0x00, 0x01, ..., 0xFF,
     *     0x00, ...).
     *   - Start async copy; the callback raises g_async_done.
     *   - Block on dma_wait() with a 2-second timeout.
     *   - Verify the destination.
     * ---------------------------------------------------------------- */
    printf("\n[Step 3] Asynchronous transfer (%u bytes, incrementing pattern)\n",
           DMA_DEMO_ASYNC_SIZE);

    for (uint32_t i = 0U; i < DMA_DEMO_ASYNC_SIZE; i++)
        demo_src[i] = (uint8_t)(i & 0xFFU);
    memset(demo_dst, 0x00, DMA_DEMO_ASYNC_SIZE);

    cache_force_write_back(demo_src, DMA_DEMO_ASYNC_SIZE);
    cache_force_invalidate(demo_dst, DMA_DEMO_ASYNC_SIZE);

    g_async_done = 0;
    rc = dma_memcpy_async(demo_dst, demo_src, DMA_DEMO_ASYNC_SIZE,
                          async_done_callback);
    print_result("dma_memcpy_async (start)", rc);
    if (rc != 0)
        goto demo_cleanup;

    rc = dma_wait(DMA_DEMO_ASYNC_TIMEOUT);
    print_result("dma_wait (async timeout = 2000 ms)", rc);
    if (rc != 0)
    {
        (void)dma_stop();
        goto demo_cleanup;
    }

    printf("  Callback fired : %s\n", g_async_done ? "yes" : "no");

    {
        uint32_t mismatches = 0U;
        for (uint32_t i = 0U; i < DMA_DEMO_ASYNC_SIZE; i++)
        {
            uint8_t expected = (uint8_t)(i & 0xFFU);
            if (demo_dst[i] != expected)
            {
                if (mismatches < 5U)
                    printf("  [MISMATCH] byte[%u]: expected 0x%02x got 0x%02x\n",
                           i, expected, demo_dst[i]);
                mismatches++;
            }
        }
        if (mismatches == 0U)
            printf("  [PASS] Async data verification (%u bytes matched)\n",
                   DMA_DEMO_ASYNC_SIZE);
        else
            printf("  [FAIL] Async data verification (%u mismatch(es))\n", mismatches);
    }

    /* ------------------------------------------------------------------
     * Step 4: Error status
     * ---------------------------------------------------------------- */
    printf("\n[Step 4] Error status\n");
    {
        uint64_t err = dma_get_error();
        if (err == 0U)
            printf("  [PASS] No transfer errors (CH_INTSTATUS error flags = 0x%08lx)\n",
                   (unsigned long)err);
        else
            printf("  [WARN] Transfer error flags = 0x%016llx  "
                   "(see DMA_ERROR_INT_MASK in socfpga_dma_reg.h)\n",
                   (unsigned long long)err);
    }

demo_cleanup:
    /* ------------------------------------------------------------------
     * Step 5: Deinitialise
     * ---------------------------------------------------------------- */
    printf("\n[Step 5] Deinitialise DMA\n");
    dma_deinit();
    printf("  Done.\n");
}

/* -------------------------------------------------------------------------
 * CLI registration
 * ---------------------------------------------------------------------- */
static void register_dma_demo(void)
{
    cli_register_command("dma_selftest", cmd_dma_demo);
}

APP_REGISTER(register_dma_demo)

