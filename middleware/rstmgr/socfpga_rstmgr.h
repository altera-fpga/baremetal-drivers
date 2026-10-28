/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rstmgr.h
 *
 * Reset Manager middleware service interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_RST_MNGR_MW_H
#define SOCFPGA_RST_MNGR_MW_H

#include <stdint.h>
#include "socfpga_rst_mngr.h"
#include "../api/rst_mngr/rst_mngr_api.h"

/* Middleware sequences */
/* Function: mw_reset_sdmmc
 *
 * Writes or configures Reset Manager state, data, or register content.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t mw_reset_sdmmc(void);
/* Function: mw_reset_uart0
 *
 * Writes or configures Reset Manager state, data, or register content.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t mw_reset_uart0(void);
/* Function: rstmgr_mw_reset_device
 *
 * Writes or configures Reset Manager state, data, or register content.
 *
 * Parameters:
 *
 *    dev - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t rstmgr_mw_reset_device(rst_device_t dev);
/* Function: rstmgr_mw_reset_get_status
 *
 * Reads Reset Manager state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    dev - Input value used by the operation.
 *    status - Output storage for the requested status value.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t rstmgr_mw_reset_get_status(rst_device_t dev, uint8_t *status);

#endif /* SOCFPGA_RST_MNGR_MW_H */
