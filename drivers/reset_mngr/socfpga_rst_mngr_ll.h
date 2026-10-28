/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rst_mngr_ll.h
 *
 * Reset Manager low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_RST_MNGR_LL_H
#define SOCFPGA_RST_MNGR_LL_H

#include <stdint.h>
#include "errno.h"

/* Function: rstmgr_ll_assert
 *
 * Performs a direct Memory-Mapped I/O (MMIO) read-modify-write operation to set 
 * a specific bit within a Reset Manager register. Setting this bit actively 
 * drives the hardware reset line high for the associated peripheral, instantly 
 * halting its internal clocks, clearing its FIFOs, and freezing its state machines.
 *
 * Parameters:
 *
 * reg_address - The absolute physical MMIO address of the target Reset Manager register.
 * bit_pos     - The exact bit index (0-31) corresponding to the target peripheral's reset line.
 *
 * Returns:
 *
 * 0 on success; a negative error code (such as -EINVAL) if the address is invalid 
 * or the bit position exceeds the 32-bit register width.
 */
int32_t rstmgr_ll_assert(uint32_t reg_address, uint8_t bit_pos);

/* Function: rstmgr_ll_deassert
 *
 * Performs a direct MMIO read-modify-write operation to clear a specific bit 
 * within a Reset Manager register. Clearing this bit releases the hardware reset 
 * line, allowing the peripheral's internal logic to initialize and resume normal 
 * execution using the active system clock.
 *
 * Parameters:
 *
 * reg_address - The absolute physical MMIO address of the target Reset Manager register.
 * bit_pos     - The exact bit index (0-31) corresponding to the target peripheral's reset line.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the parameters are out of bounds.
 */
int32_t rstmgr_ll_deassert(uint32_t reg_address, uint8_t bit_pos);

/* Function: rstmgr_ll_get_status
 *
 * Samples the live, physical state of a specific Reset Manager register bit. 
 * This bypasses higher-level software state tracking to provide the absolute 
 * hardware truth regarding whether a peripheral is currently being held in reset.
 *
 * Parameters:
 *
 * reg_address - The absolute physical MMIO address of the target Reset Manager register.
 * bit_pos     - The exact bit index (0-31) to sample.
 * status      - Pointer to an 8-bit variable where the masked state will be written 
 * (1 if the reset line is asserted, 0 if it is deasserted/active).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the status pointer is NULL or parameters are invalid.
 */
int32_t rstmgr_ll_get_status(uint32_t reg_address, uint8_t bit_pos, uint8_t *status);

#endif /* SOCFPGA_RST_MNGR_LL_H */
