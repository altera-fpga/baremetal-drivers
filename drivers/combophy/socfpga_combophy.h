/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_combophy.h
 *
 * Combo PHY hardware abstraction driver interface for the SoCFPGA bare-metal 
 * software stack.
 *
 * The Combo PHY driver provides the interface for querying PHY capabilities 
 * and performing low-level register configuration. These accessors allow the 
 * driver to identify specific PHY hardware revisions and features, and 
 * perform the fine-grained register manipulations required for lane calibration 
 * and protocol-specific signaling adjustments.
 *
 */

#ifndef SOCFPGA_COMBOPHY_H
#define SOCFPGA_COMBOPHY_H

#include <stdint.h>
#include "errno.h"

/* Function: socfpga_combophy_get_version
 *
 * Queries the IP version register to identify the hardware revision of the 
 * Combo PHY block. 
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the Combo PHY instance.
 * version      - Pointer to store the 32-bit version identifier.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the register cannot be read.
 */
int32_t socfpga_combophy_get_version(uint32_t base_address, uint32_t *version);

/* Function: socfpga_combophy_get_features
 *
 * Retrieves the hardware feature register, exposing capabilities such as 
 * supported data rates, available lanes, and enabled protocol support (e.g., 
 * PCIe, USB, or SATA) for the current silicon implementation.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the Combo PHY instance.
 * features     - Pointer to store the 32-bit feature bitmask.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_combophy_get_features(uint32_t base_address, uint32_t *features);

/* Function: socfpga_combophy_read_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from an arbitrary 
 * register offset within the Combo PHY instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the Combo PHY instance.
 * offset       - The 32-bit aligned register offset.
 * value        - Pointer to store the retrieved hardware value.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_combophy_read_reg(uint32_t base_address, uint32_t offset, uint32_t *value);

/* Function: socfpga_combophy_write_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to an arbitrary 
 * register offset within the Combo PHY instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the Combo PHY instance.
 * offset       - The 32-bit aligned register offset.
 * value        - The 32-bit data payload to commit.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_combophy_write_reg(uint32_t base_address, uint32_t offset, uint32_t value);

#endif /* SOCFPGA_COMBOPHY_H */
