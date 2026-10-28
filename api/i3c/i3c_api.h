/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: i3c_api.h
 *
 * Configure and use the I3C controller for private transfers and device access.
 * The API exposes controller initialization, transfer, status, and teardown calls.
 */

#ifndef I3C_API_H
#define I3C_API_H

#include <stdint.h>
#include "errno.h"

#include "socfpga_i3c.h"

/* Function: i3c_api_init
 *
 * Initializes a platform I3C instance with legacy-I2C compatibility enabled and hot-join disabled.
 *
 * Parameters:
 *
 *    instance - Platform I3C instance index.
 *
 * Returns:
 *
 *    0 on success; -ENOSYS when the instance has no platform base; -EBUSY when
 *    another instance is already open; otherwise returns the status from
 *    socfpga_i3c_init().
 */
int32_t i3c_api_init(uint32_t instance);
/* Function: i3c_api_init_with_base
 *
 * Initializes the singleton I3C API using an explicit MMIO base address.
 *
 * Parameters:
 *
 *    base_address - MMIO base address of the I3C controller.
 *
 * Returns:
 *
 *    0 on success; -EBUSY when another instance is already open; otherwise
 *    returns the status from socfpga_i3c_init().
 */
int32_t i3c_api_init_with_base(uint32_t base_address);
/* Function: i3c_api_close
 *
 * Deinitializes the active I3C instance and clears the singleton handle after a successful close.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no instance is open; otherwise the I3C driver deinitialization status.
 */
int32_t i3c_api_close(void);
/* Function: i3c_api_deinit
 *
 * Alias of i3c_api_close() for callers using init/deinit naming.
 *
 * Returns:
 *
 *    The status returned by i3c_api_close().
 */
int32_t i3c_api_deinit(void);
/* Function: i3c_api_get_status
 *
 * Reads the status value from the active I3C controller.
 *
 * Parameters:
 *
 *    status - Receives the controller status value.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or the driver rejects the output pointer.
 */
int32_t i3c_api_get_status(uint32_t *status);
/* Function: i3c_api_get_hw_capability
 *
 * Reads the hardware-capability value reported by the active I3C controller.
 *
 * Parameters:
 *
 *    capability - Receives the hardware-capability value.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or the driver rejects the output pointer.
 */
int32_t i3c_api_get_hw_capability(uint32_t *capability);

/* Function: i3c_api_i2c_legacy_read
 *
 * Reads bytes from a legacy I2C target through the active I3C controller.
 *
 * Parameters:
 *
 *    i2c_address - Legacy I2C target address.
 *    buffer - Destination buffer.
 *    length - Number of bytes to read.
 *    response - Receives the controller response/status word.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or arguments are invalid; -EIO or -ETIMEDOUT may be returned by the transfer path.
 */
int32_t i3c_api_i2c_legacy_read(uint8_t i2c_address,
                                uint8_t *buffer,
                                uint32_t length,
                                uint32_t *response);
/* Function: i3c_api_i2c_legacy_write
 *
 * Writes bytes to a legacy I2C target through the active I3C controller.
 *
 * Parameters:
 *
 *    i2c_address - Legacy I2C target address.
 *    buffer - Bytes to transmit.
 *    length - Number of bytes to write.
 *    response - Receives the controller response/status word.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or arguments are invalid; -EIO or -ETIMEDOUT may be returned by the transfer path.
 */
int32_t i3c_api_i2c_legacy_write(uint8_t i2c_address,
                                 const uint8_t *buffer,
                                 uint32_t length,
                                 uint32_t *response);
/* Function: i3c_api_private_read
 *
 * Performs an I3C private read from a target identified by its dynamic address.
 *
 * Parameters:
 *
 *    dynamic_address - I3C target dynamic address.
 *    buffer - Destination buffer.
 *    length - Number of bytes to read.
 *    response - Receives the controller response/status word.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or arguments are invalid; -EIO or -ETIMEDOUT may be returned by the transfer path.
 */
int32_t i3c_api_private_read(uint8_t dynamic_address,
                             uint8_t *buffer,
                             uint32_t length,
                             uint32_t *response);
/* Function: i3c_api_private_write
 *
 * Performs an I3C private write to a target identified by its dynamic address.
 *
 * Parameters:
 *
 *    dynamic_address - I3C target dynamic address.
 *    buffer - Bytes to transmit.
 *    length - Number of bytes to write.
 *    response - Receives the controller response/status word.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or arguments are invalid; -EIO or -ETIMEDOUT may be returned by the transfer path.
 */
int32_t i3c_api_private_write(uint8_t dynamic_address,
                              const uint8_t *buffer,
                              uint32_t length,
                              uint32_t *response);

/* Function: i3c_api_raw_transfer
 *
 * Executes a caller-supplied I3C transfer synchronously on the active controller.
 *
 * Parameters:
 *
 *    transfer - Transfer descriptor passed to the I3C driver.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when no I3C instance is open or the descriptor is invalid; -EBUSY, -EIO, or -ETIMEDOUT may be returned by the transfer path.
 */
int32_t i3c_api_raw_transfer(socfpga_i3c_transfer_t *transfer);

#endif /* I3C_API_H */

