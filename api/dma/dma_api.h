/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: dma_api.h
 *
 * Direct memory access (DMA) memory-to-memory transfers using one opened controller/channel pair. The API supports blocking copies and queued asynchronous copies.
 */

#ifndef __DMA_API_H__
#define __DMA_API_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * Preferred user call flow (singleton DMA API):
 * 1) dma_api_init(instance, channel)
 * 2) dma_api_memcpy(...) or dma_api_memcpy_async(...)
 * 3) dma_api_wait(...) / dma_api_is_busy() as needed
 * 4) dma_api_stop() if abort is needed
 * 5) dma_api_deinit()
 */

/* Constant: DMA_WAIT_FOREVER
 * Timeout value for dma_wait() and dma_api_wait() that disables the finite timeout.
 *
 * Warning: this wait does not poll the DMA channel; only the completion interrupt can end it. Unless gic_api_init() has been called and interrupts are unmasked, the wait never returns, and no warning is printed. A stalled or misconfigured transfer also hangs the caller. Prefer a finite timeout.
 */
#define DMA_WAIT_FOREVER    0U

/* Function: dma_init
 *
 * Open the selected DMA controller and channel for the singleton DMA API.
 *
 * Parameters:
 *
 *    instance - DMA controller instance passed to dma_mw_open().
 *    channel - DMA channel passed to dma_mw_open().
 *
 * Returns:
 *
 *    0 on success. -EBUSY when the singleton DMA handle is already open. -ENODEV when dma_mw_open() cannot open the requested controller/channel.
 */
int dma_init(uint32_t instance, uint32_t channel);

/* Function: dma_memcpy
 *
 * Copy a memory range with DMA and block until all transfer chunks complete.
 *
 * Parameters:
 *
 *    dst - Destination buffer. Must not be NULL.
 *    src - Source buffer. Must not be NULL.
 *    size - Number of bytes to copy. Must be greater than zero.
 *
 * Returns:
 *
 *    0 on completion. -ENODEV when DMA is not initialized. -EINVAL for a NULL buffer or zero size. -ETIMEDOUT if the internal wait expires. -EIO if the channel reports an error after a transfer. Errors from dma_mw_config(), dma_mw_setup_transfer(), or dma_mw_start_transfer() are propagated.
 */
int dma_memcpy(void *dst, const void *src, uint32_t size);

/* Function: dma_memcpy_async
 *
 * Start a memory-to-memory DMA copy and return after the transfer has been queued to the DMA middleware. A zero return value means the transfer started; it does not mean the copy completed.
 *
 * Parameters:
 *
 *    dst - Destination buffer. Must remain valid until the transfer completes.
 *    src - Source buffer. Must remain valid until the transfer completes.
 *    size - Number of bytes to copy. Must be greater than zero and fit in the fixed descriptor pool.
 *    callback - Optional function invoked by the API callback path after the final transfer completes.
 *
 * Returns:
 *
 *    0 when the transfer is started. -ENODEV when DMA is not initialized. -EINVAL for a NULL buffer, zero size, or a transfer requiring more descriptors than the fixed pool. Errors from dma_mw_config(), dma_mw_setup_transfer(), or dma_mw_start_transfer() are propagated.
 */
int dma_memcpy_async(void *dst, const void *src, uint32_t size, void (*callback)(void));

/* Function: dma_wait
 *
 * Poll the current DMA transfer until its completion flag is set or the wait expires.
 *
 * Parameters:
 *
 *    timeout_ms - Maximum wait in milliseconds. DMA_WAIT_FOREVER (0) waits without a timeout and without polling the channel, so it can hang forever if the completion interrupt is not delivered. See DMA_WAIT_FOREVER.
 *
 * Returns:
 *
 *    0 when the completion flag is set, including when the channel finished with an error. This call does not return that channel error. -ETIMEDOUT when a finite timeout expires first.
 */
int dma_wait(uint32_t timeout_ms);

/* Function: dma_is_busy
 *
 * Report whether the singleton DMA transfer is still in progress.
 *
 * Returns:
 *
 *    true before the first transfer completes, while a transfer is pending, and after dma_deinit(). false only after a transfer's completion flag has been set.
 */
bool dma_is_busy(void);

/* Function: dma_stop
 *
 * Stop the current DMA transfer.
 *
 * Returns:
 *
 *    0 on success. -ENODEV when DMA is not initialized. -EIO when the channel is already idle. -ETIMEDOUT when the channel does not disable in time.
 */
int dma_stop(void);

/* Function: dma_get_error
 *
 * Return the error word exposed by the singleton DMA API.
 *
 * Returns:
 *
 *    0. This function does not report controller error bits. Use the status from dma_memcpy() or dma_stop() instead.
 */
uint64_t dma_get_error(void);

/* Function: dma_deinit
 *
 * Close the singleton DMA handle, if open, and clear API-side transfer state.
 */
void dma_deinit(void);

/*
 * Standardized naming aliases (dma_api_*) for new call sites.
 * Existing dma_* symbols remain the canonical implementation entry points.
 */
/* Function: dma_api_init
 *
 * Open DMA controller instance and channel for memory-to-memory copies. Same behavior as dma_init().
 *
 * Parameters:
 *
 *    instance - DMA controller instance passed to dma_init().
 *    channel - DMA channel passed to dma_init().
 *
 * Returns:
 *
 *    The status returned by dma_init().
 */
int dma_api_init(uint32_t instance, uint32_t channel);
/* Function: dma_api_memcpy
 *
 * Copy size bytes from src to dst and wait until the copy finishes. Same behavior and return codes as dma_memcpy().
 *
 * Parameters:
 *
 *    dst - Destination buffer.
 *    src - Source buffer.
 *    size - Transfer size in bytes.
 *
 * Returns:
 *
 *    The status returned by dma_memcpy().
 */
int dma_api_memcpy(void *dst, const void *src, uint32_t size);
/* Function: dma_api_memcpy_async
 *
 * Queue a memory-to-memory copy and return after it starts. Same behavior and return codes as dma_memcpy_async(). A zero return does not mean the copy finished.
 *
 * Parameters:
 *
 *    dst - Destination buffer.
 *    src - Source buffer.
 *    size - Transfer size in bytes.
 *    callback - Optional completion callback.
 *
 * Returns:
 *
 *    The status returned by dma_memcpy_async().
 */
int dma_api_memcpy_async(void *dst, const void *src, uint32_t size, void (*callback)(void));
/* Function: dma_api_wait
 *
 * Wait until the active transfer's completion flag is set or the wait expires. Same behavior and return codes as dma_wait().
 *
 * Parameters:
 *
 *    timeout_ms - Maximum wait in milliseconds, or DMA_WAIT_FOREVER. DMA_WAIT_FOREVER can hang forever if the completion interrupt is not delivered; see DMA_WAIT_FOREVER.
 *
 * Returns:
 *
 *    The status returned by dma_wait().
 */
int dma_api_wait(uint32_t timeout_ms);
/* Function: dma_api_is_busy
 *
 * Report whether the singleton DMA transfer is still in progress. Same result as dma_is_busy().
 *
 * Returns:
 *
 *    true before the first transfer completes, while a transfer is pending, and after dma_api_deinit(). false only after a transfer's completion flag has been set.
 */
bool dma_api_is_busy(void);
/* Function: dma_api_stop
 *
 * Stop the active DMA transfer. Same behavior and return codes as dma_stop().
 *
 * Returns:
 *
 *    The status returned by dma_stop().
 */
int dma_api_stop(void);
/* Function: dma_api_get_error
 *
 * Return the DMA error word exposed by dma_get_error().
 *
 * Returns:
 *
 *    0. This function does not report controller error bits.
 */
uint64_t dma_api_get_error(void);
/* Function: dma_api_deinit
 *
 * Releases the singleton DMA handle and clears API-side transfer state.
 *
 * Returns:
 *
 *    None.
 */
void dma_api_deinit(void);

#endif /* __DMA_API_H__ */
