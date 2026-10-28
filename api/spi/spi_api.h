/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: spi_api.h
 *
 * Open and configure a Serial Peripheral Interface (SPI) controller, perform
 * blocking transfers, query configuration or IP version, and run loopback test.
 */

#ifndef SPI_API_H
#define SPI_API_H

#include <stddef.h>
#include <stdint.h>

#include "socfpga_spi.h"
/* Constant: SPI_API_DEFAULT_INSTANCE
 * SPI controller instance used when spi_api_open() receives a NULL configuration.
 */

#define SPI_API_DEFAULT_INSTANCE     0U
/* Constant: SPI_API_DEFAULT_SLAVE
 * One-based chip-select used by the default SPI configuration.
 */
#define SPI_API_DEFAULT_SLAVE        1U
/* Constant: SPI_API_DEFAULT_SPEED_HZ
 * Default SPI serial clock request in hertz.
 */
#define SPI_API_DEFAULT_SPEED_HZ     500000U
/* Constant: SPI_API_LOOPBACK_MAX_LEN
 * Maximum transfer length accepted by spi_api_loopback_test().
 */
#define SPI_API_LOOPBACK_MAX_LEN     256U

/* Struct: spi_api_config_t
 *
 * Configuration passed to spi_api_open().
 *
 * Fields:
 *
 *    instance - SPI controller instance, 0 or 1.
 *    slave - One-based chip-select number, 1 through 4.
 *    speed_hz - Requested serial clock frequency in hertz. Zero is rejected.
 *    mode - Transfer mode, SPI_MODE0 through SPI_MODE3.
 */
typedef struct {
    uint32_t instance;
    uint32_t slave;
    uint32_t speed_hz;
    spi_mode_t mode;
} spi_api_config_t;

/* Function: spi_api_open
 *
 * Opens and configures the selected SPI instance.
 *
 * Parameters:
 *
 *    config - SPI configuration. A NULL pointer selects the default configuration.
 *
 * Returns:
 *
 *    0 on success. -EINVAL for an unsupported instance, chip-select, mode, or
 *    zero clock request. -EBUSY if an instance is already open. -EIO if the
 *    controller cannot be opened or its input clock cannot be resolved. If
 *    chip-select selection or clock programming fails, the instance is closed
 *    before that error is returned.
 */
int32_t spi_api_open(const spi_api_config_t *config);

/* Function: spi_api_close
 *
 * Closes the active SPI instance, if one is open.
 *
 * Returns:
 *
 *    0 if no instance is open or the active instance closes successfully;
 *    -EINVAL for an invalid driver handle; -EBUSY if a transfer is active.
 */
int32_t spi_api_close(void);

/* Function: spi_api_transfer
 *
 * Performs a blocking SPI transfer on the active SPI instance.
 *
 * Parameters:
 *
 *    txbuf - Buffer containing bytes to transmit.
 *    rxbuf - Optional output buffer for received bytes.
 *    nbytes - Number of bytes to transfer.
 *
 * Returns:
 *
 *    0 on success; -ENODEV if no SPI instance is open; -EINVAL for a NULL
 *    transmit buffer, zero length, or length greater than UINT16_MAX; -EBUSY if
 *    a transfer is already active; -EIO on a controller error; -ETIMEDOUT if
 *    polling does not complete.
 */
int32_t spi_api_transfer(const uint8_t *txbuf, uint8_t *rxbuf, size_t nbytes);

/* Function: spi_api_get_config
 *
 * Returns the active SPI configuration.
 *
 * Parameters:
 *
 *    config - Output storage for the active configuration.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if config is NULL; -ENODEV if no SPI instance is
 *    open; otherwise returns the status from spi_ioctl(SPI_GET_CONFIG).
 */
int32_t spi_api_get_config(spi_api_config_t *config);

/* Function: spi_api_get_version
 *
 * Reads the DesignWare SPI version register for an instance.
 *
 * Parameters:
 *
 *    instance - SPI instance index.
 *    version - Output storage for the version register.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for an unsupported instance or NULL version pointer;
 *    -EBUSY if another SPI instance is already open. If the function opens the
 *    requested instance temporarily, it propagates spi_api_open() or
 *    spi_api_close() errors.
 */
int32_t spi_api_get_version(uint32_t instance, uint32_t *version);

/* Function: spi_api_loopback_test
 *
 * Runs an internal-controller loopback test using serial-loopback mode.
 *
 * Parameters:
 *
 *    instance - SPI instance index.
 *    slave - One-based chip-select number.
 *    nbytes - Number of bytes to test.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for a zero length, a length above
 *    SPI_API_LOOPBACK_MAX_LEN, or an invalid SPI configuration; -EIO if the
 *    received data does not match or the controller reports an error; -EBUSY or
 *    -ETIMEDOUT when reported by the open or transfer path.
 */
int32_t spi_api_loopback_test(uint32_t instance, uint32_t slave, size_t nbytes);

#endif /* SPI_API_H */
