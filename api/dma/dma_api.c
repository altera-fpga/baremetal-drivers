/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "errno.h"
#include <stdio.h>
#include "dma_api.h"
#include "socfpga_dma.h"
#include "cache.h"
#include "socfpga_dma_reg_plat.h"

/* Static handle for simple single-channel API */
static dma_handle_t g_dma_handle = NULL;
static volatile bool g_transfer_done = false;
static void (*g_user_callback)(void) = NULL;
/* Destination and size stored for post-transfer cache invalidation (async path) */
static void     *g_async_dst  = NULL;
static uint32_t  g_async_size = 0U;

/*
 * Static descriptor pool for dma_memcpy_async chunked transfers.
 * Size must match MAX_LLI_PER_CHANNEL in middleware/dma/socfpga_dma.c.
 */
#define DMA_ASYNC_MAX_DESCRIPTORS  128U
static dma_xfer_cfg_t g_async_xfer_pool[DMA_ASYNC_MAX_DESCRIPTORS];

/*
 * Default blocking timeout for dma_memcpy() expressed as a loop iteration
 * count.  Each iteration is approximately one register read (~10 ns at 400 MHz),
 * so 50 000 000  500 ms.  Adjust DMA_MEMCPY_TIMEOUT_ITERS if your clock
 * frequency differs significantly.
 */
#define DMA_MEMCPY_TIMEOUT_MS   5000U

/*
 * Iterations-per-millisecond scale for dma_wait().
 * Approximate: ~10 000 loop iterations  1 ms at typical ARM frequencies.
 * Increase this value if timeouts trigger too early on faster cores.
 */
#define DMA_WAIT_ITERS_PER_MS   10000U

/* Internal DMA completion callback; not part of the public API. */
static void dma_callback(dma_handle_t hdma)
{
    (void)hdma;

    /* Invalidate dst cache lines so the CPU reads DMA-written data from DRAM,
     * not any speculatively-loaded stale lines that the prefetcher may have
     * brought in while the DMA was running.  The DSB inside cache_force_invalidate
     * also guarantees all DMA AXI writes are globally visible before the CPU read. */
    if (g_async_dst != NULL)
    {
        cache_force_invalidate(g_async_dst, g_async_size);
        g_async_dst  = NULL;
        g_async_size = 0U;
    }

    g_transfer_done = true;

    if (g_user_callback != NULL)
    {
        g_user_callback();
    }
}

/*
 * Initialize DMA controller and channel
 */
/*
 * Initialize DMA controller and channel
 */
int dma_init(uint32_t instance, uint32_t channel)
{
    if (g_dma_handle != NULL)
    {
        return -EBUSY;
    }

    g_dma_handle = dma_mw_open(instance, channel);
    if (g_dma_handle == NULL)
    {
        return -ENODEV;
    }

    return 0;
}

/*
 * Perform a synchronous memory-to-memory copy using DMA
 *
 * Large transfers are split into chunks of DMA_MAX_CHUNK_BYTES, which the
 * platform header sets within the hardware BLOCK_TS field limit.
 */
int dma_memcpy(void *dst, const void *src, uint32_t size)
{
    dma_config_t config;
    dma_xfer_cfg_t xfer;
    int ret;
    uint8_t *src_ptr = (uint8_t *)(uintptr_t)src;
    uint8_t *dst_ptr = (uint8_t *)(uintptr_t)dst;
    uint32_t remaining = size;
    uint32_t chunk;

    if (g_dma_handle == NULL)
    {
        return -ENODEV;
    }

    if (dst == NULL || src == NULL || size == 0)
    {
        return -EINVAL;
    }

    config.ch_dir  = DMA_MEM_TO_MEM_DMAC;
    config.ch_prio = 0;
    config.peri_id = 0;
    config.callback = dma_callback;

    ret = dma_mw_config(g_dma_handle, &config);
    if (ret != 0)
    {
        return ret;
    }

    /* Flush the entire src region and clean+invalidate the entire dst region
     * once up-front so all chunks see coherent memory. */
    cache_force_write_back((void *)(uintptr_t)src, size);
    cache_flush(dst, size);

    while (remaining > 0U)
    {
        /* Compute a safe chunk by predicting the AXI transfer width the middleware
         * will select (mirrors dma_get_transfer_width()), then cap to DMA_MAX_BLOCK_TS
         * beats.  This ensures the middleware never sees a beat count that exceeds
         * the hardware BLOCK_TS field width (22 bits on Agilex5). */
        uint32_t width_bytes;
        if ((remaining & 0x7U) == 0U)      width_bytes = 8U;
        else if ((remaining & 0x3U) == 0U) width_bytes = 4U;
        else if ((remaining & 0x1U) == 0U) width_bytes = 2U;
        else                               width_bytes = 1U;
        chunk = (remaining > (DMA_MAX_BLOCK_TS * width_bytes)) ?
                (DMA_MAX_BLOCK_TS * width_bytes) : remaining;

        xfer.src             = (uint64_t)(uintptr_t)src_ptr;
        xfer.dst             = (uint64_t)(uintptr_t)dst_ptr;
        xfer.blk_size        = chunk;
        xfer.next_trnsfr_cfg = NULL;

        g_async_dst  = dst_ptr;
        g_async_size = chunk;

        ret = dma_mw_setup_transfer(g_dma_handle, &xfer, 1);
        if (ret != 0)
        {
            g_async_dst = NULL;
            return ret;
        }

        g_transfer_done = false;
        ret = dma_mw_start_transfer(g_dma_handle);
        if (ret != 0)
        {
            g_async_dst = NULL;
            return ret;
        }

        ret = dma_wait(DMA_MEMCPY_TIMEOUT_MS);
        if (ret != 0)
        {
            (void)dma_stop();
            return ret;
        }

        if (dma_mw_get_channel_status(g_dma_handle) == DMA_CH_ERROR)
        {
            return -EIO;
        }

        src_ptr   += chunk;
        dst_ptr   += chunk;
        remaining -= chunk;
    }

    return 0;
}

/*
 * Perform an asynchronous memory-to-memory copy using DMA
 *
 * Large transfers are automatically split into descriptor-sized chunks
 * (respecting the hardware BLOCK_TS limit) and submitted as a single
 * hardware LLI chain.  The DMA walks all descriptors autonomously and
 * fires one completion interrupt at the end.  The user callback, if any,
 * is invoked from dma_callback() after the final transfer completes.
 */
int dma_memcpy_async(void *dst, const void *src, uint32_t size, void (*callback)(void))
{
    dma_config_t config;
    uint8_t *src_ptr = (uint8_t *)(uintptr_t)src;
    uint8_t *dst_ptr = (uint8_t *)(uintptr_t)dst;
    uint32_t remaining = size;
    uint32_t n = 0U;
    int ret;

    if (g_dma_handle == NULL)
    {
        return -ENODEV;
    }

    if (dst == NULL || src == NULL || size == 0)
    {
        return -EINVAL;
    }

    g_user_callback = callback;

    config.ch_dir  = DMA_MEM_TO_MEM_DMAC;
    config.ch_prio = 0;
    config.peri_id = 0;
    config.callback = dma_callback;

    ret = dma_mw_config(g_dma_handle, &config);
    if (ret != 0)
    {
        return ret;
    }

    /* Cache maintenance for the entire region up-front */
    cache_force_write_back((void *)(uintptr_t)src, size);
    cache_flush(dst, size);

    /* Build the LLI descriptor chain, each entry <= DMA_MAX_BLOCK_TS beats.
     * Mirrors the chunking logic in dma_memcpy() and ATF dw_dma_prep_h2d_multiblock(). */
    while (remaining > 0U)
    {
        uint32_t width_bytes;
        uint32_t chunk;

        if (n >= DMA_ASYNC_MAX_DESCRIPTORS)
        {
            printf("dma_memcpy_async: transfer too large (>%u descriptors)\\n",
                   DMA_ASYNC_MAX_DESCRIPTORS);
            return -EINVAL;
        }

        if ((remaining & 0x7U) == 0U)      width_bytes = 8U;
        else if ((remaining & 0x3U) == 0U) width_bytes = 4U;
        else if ((remaining & 0x1U) == 0U) width_bytes = 2U;
        else                               width_bytes = 1U;
        chunk = (remaining > (DMA_MAX_BLOCK_TS * width_bytes)) ?
                (DMA_MAX_BLOCK_TS * width_bytes) : remaining;

        g_async_xfer_pool[n].src             = (uint64_t)(uintptr_t)src_ptr;
        g_async_xfer_pool[n].dst             = (uint64_t)(uintptr_t)dst_ptr;
        g_async_xfer_pool[n].blk_size        = chunk;
        g_async_xfer_pool[n].next_trnsfr_cfg = NULL;
        if (n > 0U)
        {
            g_async_xfer_pool[n - 1U].next_trnsfr_cfg = &g_async_xfer_pool[n];
        }

        src_ptr   += chunk;
        dst_ptr   += chunk;
        remaining -= chunk;
        n++;
    }

    /* Register full dst region: dma_callback() invalidates it in one shot
     * after the hardware completes all LLI entries and fires TFR_DONE. */
    g_async_dst  = dst;
    g_async_size = size;

    ret = dma_mw_setup_transfer(g_dma_handle, &g_async_xfer_pool[0], n);
    if (ret != 0)
    {
        g_async_dst = NULL;
        return ret;
    }

    g_transfer_done = false;
    return dma_mw_start_transfer(g_dma_handle);
}

/*
 * Wait for DMA transfer to complete
 *
 * Uses an iteration-count-based timeout.  Pass DMA_WAIT_FOREVER (0) to
 * wait without a time limit.
 */
int dma_wait(uint32_t timeout_ms)
{
    if (timeout_ms == DMA_WAIT_FOREVER)
    {
        while (!g_transfer_done)
        {
            /* Wait indefinitely */
        }
        return 0;
    }

    /*
     * Approximate busy-wait timeout.
     * Each loop iteration  DMA_WAIT_ITERS_PER_MS^(-1) ms.
     * Overflow guard: cap at UINT32_MAX.
     */
    volatile uint32_t max_count;
    if (timeout_ms > (UINT32_MAX / DMA_WAIT_ITERS_PER_MS))
    {
        max_count = UINT32_MAX;
    }
    else
    {
        max_count = timeout_ms * DMA_WAIT_ITERS_PER_MS;
    }

    while (!g_transfer_done)
    {
        (void)dma_mw_check_transfer(g_dma_handle);
        if (max_count == 0U)
        {
            return -ETIMEDOUT;
        }
        max_count--;
    }

    return 0;
}

/*
 * Check if DMA transfer is in progress
 */
bool dma_is_busy(void)
{
    return !g_transfer_done;
}

/*
 * Stop current DMA transfer (graceful suspend + disable)
 */
int dma_stop(void)
{
    if (g_dma_handle == NULL)
    {
        return -ENODEV;
    }

    return dma_mw_stop_transfer(g_dma_handle);
}

/*
 * Retrieve raw error interrupt bits from the last failed transfer
 * (Not applicable in GIC interrupt mode; always returns 0.)
 */
uint64_t dma_get_error(void)
{
    return 0U;
}

/*
 * Close and cleanup DMA resources
 */
void dma_deinit(void)
{
    if (g_dma_handle != NULL)
    {
        (void)dma_mw_close(g_dma_handle);
        g_dma_handle = NULL;
    }
    g_transfer_done = false;
    g_user_callback = NULL;
}

int dma_api_init(uint32_t instance, uint32_t channel)
{
    return dma_init(instance, channel);
}

int dma_api_memcpy(void *dst, const void *src, uint32_t size)
{
    return dma_memcpy(dst, src, size);
}

int dma_api_memcpy_async(void *dst, const void *src, uint32_t size, void (*callback)(void))
{
    return dma_memcpy_async(dst, src, size, callback);
}

int dma_api_wait(uint32_t timeout_ms)
{
    return dma_wait(timeout_ms);
}

bool dma_api_is_busy(void)
{
    return dma_is_busy();
}

int dma_api_stop(void)
{
    return dma_stop();
}

uint64_t dma_api_get_error(void)
{
    return dma_get_error();
}

void dma_api_deinit(void)
{
    dma_deinit();
}

