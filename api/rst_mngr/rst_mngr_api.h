/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: rst_mngr_api.h
 *
 * Pulse reset on UART0 or SDMMC, and read whether that block is held in reset.
 * Any other rst_device_t value returns -EINVAL. The pulse is assert, a short
 * delay, then deassert. The delay length depends on the device.
 */

#ifndef RST_MNGR_API_H
#define RST_MNGR_API_H

#include <stdint.h>

/* Enum: rst_device_t
 *
 * Peripherals this API can reset.
 *
 * Values:
 *
 *    RST_DEV_UART0 - UART 0.
 *    RST_DEV_SDMMC - SD/MMC controller.
 *    RST_DEV_MAX - Count of named devices. Not a valid target.
 */
typedef enum {
	RST_DEV_UART0,
	RST_DEV_SDMMC,
	RST_DEV_MAX
} rst_device_t;

/* Function: reset_device
 *
 * Assert reset, wait, then deassert it.
 *
 * Parameters:
 *
 *    dev - RST_DEV_UART0 or RST_DEV_SDMMC.
 *
 * Returns:
 *
 *    0 on success. -EINVAL for any other dev. Otherwise the reset-manager status from assert or deassert.
 */
int32_t reset_device(rst_device_t dev);

/* Function: reset_get_device_status
 *
 * Report whether dev is currently held in reset.
 *
 * Parameters:
 *
 *    dev - RST_DEV_UART0 or RST_DEV_SDMMC.
 *    status - Receives the reset-manager status byte. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL for an unknown dev or a NULL status pointer. Otherwise the reset-manager status.
 */
int32_t reset_get_device_status(rst_device_t dev, uint8_t *status);

#endif /* RST_MNGR_API_H */
