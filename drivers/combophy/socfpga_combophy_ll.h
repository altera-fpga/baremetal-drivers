/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_combophy_ll.h
 *
 * Combo PHY low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 * This header provides low-level primitives for accessing the Memory-Mapped I/O 
 * (MMIO) registers of the Combo PHY controller. These helpers are used to perform 
 * direct register-level configuration of the PHY's physical lane settings and 
 * status registers.
 *
 */

#ifndef SOCFPGA_COMBOPHY_LL_H
#define SOCFPGA_COMBOPHY_LL_H

#include <stdint.h>
#include "errno.h"
#include "mmio.h"

/* Function: socfpga_combophy_ll_read
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from an arbitrary 
 * register offset within the Combo PHY instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target Combo PHY instance.
 * offset       - The exact 32-bit aligned register offset to read.
 *
 * Returns:
 *
 * The raw 32-bit hardware value at the specified address.
 */
uint32_t socfpga_combophy_ll_read(uint32_t base_address, uint32_t offset);

/* Function: socfpga_combophy_ll_write
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to an arbitrary 
 * register offset within the Combo PHY instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target Combo PHY instance.
 * offset       - The exact 32-bit aligned register offset to write.
 * value        - The 32-bit data payload to commit to the register.
 */
void socfpga_combophy_ll_write(uint32_t base_address, uint32_t offset, uint32_t value);

#endif /* SOCFPGA_COMBOPHY_LL_H */
