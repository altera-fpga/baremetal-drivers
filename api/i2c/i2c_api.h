/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: i2c_api.h
 *
 * Inter-Integrated Circuit (I2C) controller API. One open instance is supported. Call i2c_api_init() or
 * i2c_api_init_with_base() before any transfer, and i2c_api_close() when finished.
 *
 * bus_hz selects the speed mode: 100 kHz or below is standard mode, 400 kHz or
 * below is fast mode, and any higher request is fast-mode plus. The driver
 * computes serial clock (SCL) counts from the live input clock. A target_address above 0x7F
 * selects 10-bit addressing. Repeated START is enabled.
 */

#ifndef I2C_API_H
#define I2C_API_H

#include <stddef.h>
#include <stdint.h>
#include "errno.h"

#include "socfpga_i2c.h"

/* Function: i2c_api_init
 *
 * Open the singleton I2C controller for a platform instance and select its target.
 *
 * Parameters:
 *
 *    instance - Controller index 0 through 4. An index with no platform base returns -ENOSYS.
 *    target_address - 7-bit or 10-bit target address. Values above 0x3FF are rejected by the driver.
 *    bus_hz - Requested bus frequency in hertz. See the file comment for the speed-mode split.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when instance has no platform base. -EBUSY when an instance is already open, or when the driver has no free descriptor. -EINVAL when the driver rejects the configuration. Other failures are the status returned by socfpga_i2c_init(), including timing-setup failures.
 */
int32_t i2c_api_init(uint32_t instance, uint16_t target_address,
                     uint32_t bus_hz);

/* Function: i2c_api_init_with_base
 *
 * Open the singleton I2C controller at an explicit base address.
 *
 * Does not apply a reset. The caller must release reset before calling.
 *
 * Parameters:
 *
 *    base_address - Controller MMIO base. Zero is rejected by the driver with -EINVAL.
 *    target_address - 7-bit or 10-bit target address. Values above 0x3FF are rejected.
 *    bus_hz - Requested bus frequency in hertz. See the file comment for the speed-mode split.
 *
 * Returns:
 *
 *    0 on success. -EBUSY when an instance is already open or the driver has no free descriptor. -EINVAL for a rejected configuration. Other failures are the status returned by socfpga_i2c_init().
 */
int32_t i2c_api_init_with_base(uint32_t base_address, uint16_t target_address,
                               uint32_t bus_hz);

/* Function: i2c_api_close
 *
 * Close the open I2C instance and drop the API handle.
 *
 * If the driver is still busy, the handle is kept so a later close can release it.
 * Any other deinit failure still drops the handle, so the singleton does not stay stuck open.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open. -EBUSY when a transfer is still active. Any other deinitialization status is returned after the API releases the singleton handle.
 */
int32_t i2c_api_close(void);

/* Function: i2c_api_deinit
 *
 * Alias of i2c_api_close().
 *
 * Returns:
 *
 *    The status returned by i2c_api_close().
 */
int32_t i2c_api_deinit(void);

/* Function: i2c_api_write
 *
 * Blocking write to the current target.
 *
 * Parameters:
 *
 *    buffer - Bytes to transmit. Must be non-NULL.
 *    length - Number of bytes. Zero is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open, buffer is NULL, or length is 0. -EBUSY when a transfer is already active. Otherwise the controller transfer status.
 */
int32_t i2c_api_write(const uint8_t *buffer, size_t length);

/* Function: i2c_api_read
 *
 * Blocking read from the current target.
 *
 * Parameters:
 *
 *    buffer - Destination. Must be non-NULL.
 *    length - Number of bytes. Zero is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open, buffer is NULL, or length is 0. -EBUSY when a transfer is already active. Otherwise the controller transfer status.
 */
int32_t i2c_api_read(uint8_t *buffer, size_t length);

/* Function: i2c_api_write_then_read
 *
 * Blocking write followed by a read, holding the bus with a repeated START.
 *
 * Parameters:
 *
 *    tx_buffer - Bytes to transmit. Must be non-NULL.
 *    tx_length - Number of bytes to transmit. Zero is rejected.
 *    rx_buffer - Destination. Must be non-NULL.
 *    rx_length - Number of bytes to read. Zero is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open or any buffer or length is invalid. -EBUSY when a transfer is already active. Otherwise the controller transfer status.
 */
int32_t i2c_api_write_then_read(const uint8_t *tx_buffer, size_t tx_length,
                                uint8_t *rx_buffer, size_t rx_length);

/* Function: i2c_api_get_status
 *
 * Read the controller status register of the open instance.
 *
 * Parameters:
 *
 *    status - Receives the raw status word. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open or status is NULL.
 */
int32_t i2c_api_get_status(uint32_t *status);

/* Function: i2c_api_get_info
 *
 * Report identity, input clock, programmed SCL counts, and FIFO depths.
 *
 * Parameters:
 *
 *    info - Output storage. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open or info is rejected by the driver.
 */
int32_t i2c_api_get_info(socfpga_i2c_info_t *info);

/* Function: i2c_api_set_target
 *
 * Change the target address of the open instance without a full re-init.
 *
 * Parameters:
 *
 *    target_address - 7-bit or 10-bit address used by later transfers.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open. -EBUSY when a transfer is active. Any other failure is the status from programming the target address.
 */
int32_t i2c_api_set_target(uint16_t target_address);

/* Function: i2c_api_probe
 *
 * Check whether a device acknowledges the given address.
 *
 * The probe replaces the current target address.
 *
 * Parameters:
 *
 *    target_address - 7-bit or 10-bit address to test.
 *
 * Returns:
 *
 *    0 when the address acknowledges. -EINVAL when nothing is open. -EBUSY when a transfer is active. -ENXIO when the address does not acknowledge. -ETIMEDOUT when the bus does not finish. Other controller errors are returned unchanged.
 */
int32_t i2c_api_probe(uint16_t target_address);

/* Function: i2c_api_recover
 *
 * Recover the controller when no transfer is marked in progress.
 *
 * A busy handle returns -EBUSY and is left running. Otherwise the driver aborts the controller if it is enabled, flushes the receive FIFO, and enables the controller again.
 *
 * Returns:
 *
 *    0 when the bus is idle afterwards. -EINVAL when nothing is open. -EBUSY when a transfer is marked in progress. Otherwise the driver recovery status, including -ETIMEDOUT if the bus does not go idle.
 */
int32_t i2c_api_recover(void);

/* Function: i2c_api_get_abort_source
 *
 * Read the abort-source bitmap latched by the most recent failed transfer.
 *
 * Parameters:
 *
 *    source - Receives the IC_TX_ABRT_SOURCE value. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when nothing is open or source is NULL.
 */
int32_t i2c_api_get_abort_source(uint32_t *source);

/* Function: i2c_api_write_async
 *
 * Queue an interrupt-driven write. Returns when the transfer is accepted, not when it finishes.
 *
 * buffer must stay valid until the completion callback runs. The callback receives the transfer result.
 *
 * Parameters:
 *
 *    buffer - Bytes to transmit. Must be non-NULL and stay live until the callback.
 *    length - Number of bytes. Zero is rejected.
 *    callback - Called from the interrupt or wait path on completion. May be NULL.
 *    context - Pointer passed back to callback.
 *
 * Returns:
 *
 *    0 once the transfer is queued. -EINVAL when nothing is open, buffer is NULL, or length is 0. -EBUSY when a transfer is active or the bus is not idle.
 */
int32_t i2c_api_write_async(const uint8_t *buffer, size_t length,
                            socfpga_i2c_callback_t callback, void *context);

/* Function: i2c_api_read_async
 *
 * Queue an interrupt-driven read. Returns when the transfer is accepted, not when it finishes.
 *
 * buffer must stay valid until the completion callback runs.
 *
 * Parameters:
 *
 *    buffer - Destination. Must be non-NULL and stay live until the callback.
 *    length - Number of bytes. Zero is rejected.
 *    callback - Called on completion. May be NULL.
 *    context - Pointer passed back to callback.
 *
 * Returns:
 *
 *    0 once the transfer is queued. -EINVAL when nothing is open, buffer is NULL, or length is 0. -EBUSY when a transfer is active or the bus is not idle.
 */
int32_t i2c_api_read_async(uint8_t *buffer, size_t length,
                           socfpga_i2c_callback_t callback, void *context);

/* Function: i2c_api_write_then_read_async
 *
 * Queue a write-then-read that holds the bus across a repeated START.
 *
 * Returns when the transfer is accepted. Both buffers must stay valid until the callback runs.
 *
 * Parameters:
 *
 *    tx_buffer - Bytes to transmit. Must be non-NULL.
 *    tx_length - Number of bytes to transmit. Zero is rejected.
 *    rx_buffer - Destination. Must be non-NULL.
 *    rx_length - Number of bytes to read. Zero is rejected.
 *    callback - Called on completion. May be NULL.
 *    context - Pointer passed back to callback.
 *
 * Returns:
 *
 *    0 once the transfer is queued. -EINVAL when nothing is open or any buffer or length is invalid. -EBUSY when a transfer is active or the bus is not idle. Public init always enables repeated START, so this call does not return -EPROTO for a disabled repeated START.
 */
int32_t i2c_api_write_then_read_async(const uint8_t *tx_buffer,
                                      size_t tx_length, uint8_t *rx_buffer,
                                      size_t rx_length,
                                      socfpga_i2c_callback_t callback,
                                      void *context);

/* Function: i2c_api_wait_async
 *
 * Poll the open controller from this context until the queued transfer finishes.
 *
 * Use this when the I2C interrupt is not routed. The transfer result is still delivered through the callback. A 0 return means no transfer is outstanding; it does not by itself mean the transfer succeeded.
 *
 * Parameters:
 *
 *    timeout_us - Wait limit in microseconds when a counter clock is available. 0 selects the timeout stored at init. If no counter clock is available, the limit is turned into a proportional spin loop.
 *
 * Returns:
 *
 *    0 when no transfer remains outstanding. -EINVAL when nothing is open. -ETIMEDOUT when the limit expires while a transfer is still active.
 */
int32_t i2c_api_wait_async(uint32_t timeout_us);

#endif /* I2C_API_H */
