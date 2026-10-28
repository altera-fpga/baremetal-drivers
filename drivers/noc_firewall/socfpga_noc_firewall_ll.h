/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_noc_firewall_ll.h
 *
 * NoC Firewall low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_NOC_FIREWALL_LL_H
#define SOCFPGA_NOC_FIREWALL_LL_H

#include <stdint.h>
#include "errno.h"
#include "mmio.h"

/* Function: socfpga_noc_firewall_ll_read
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from the specified 
 * register offset within a NoC Firewall hardware block. 
 *
 * This function bypasses all high-level abstractions to extract raw hardware 
 * states, such as active ARM TrustZone security policies or pending transaction 
 * fault logs.
 *
 * Parameters:
 *
 * base_address - The absolute physical MMIO base address of the target NoC Firewall instance.
 * offset       - The specific 32-bit aligned register offset to read from.
 *
 * Returns:
 *
 * The raw 32-bit hardware value read from the register.
 *
 * Notes:
 *
 * This is an intentionally thin, lockless helper function. It expects the caller 
 * to have already validated the `base_address` and `offset` bounds to prevent 
 * precise bus exceptions during the transaction.
 */
uint32_t socfpga_noc_firewall_ll_read(uint32_t base_address, uint32_t offset);

/* Function: socfpga_noc_firewall_ll_write
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to the specified 
 * register offset within a NoC Firewall hardware block.
 *
 * This function is used to physically commit new transaction filtering policies 
 * or clear active fault latches within the interconnect.
 *
 * Parameters:
 *
 * base_address - The absolute physical MMIO base address of the target NoC Firewall instance.
 * offset       - The specific 32-bit aligned register offset to write to.
 * value        - The 32-bit data payload to commit to the hardware.
 *
 * Returns:
 *
 * None.
 *
 * Notes:
 *
 * This is an intentionally thin, lockless helper function. It expects the caller 
 * to handle any necessary Read-Modify-Write (RMW) logic or memory synchronization 
 * barriers (e.g., `DSB`, `DMB`) before and after issuing the write to ensure 
 * policy changes propagate through the interconnect correctly.
 */
void socfpga_noc_firewall_ll_write(uint32_t base_address, uint32_t offset,
                                   uint32_t value);

#endif /* SOCFPGA_NOC_FIREWALL_LL_H */
