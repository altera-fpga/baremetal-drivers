/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_noc_probe_ll.h
 *
 * NoC Probe low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_NOC_PROBE_LL_H
#define SOCFPGA_NOC_PROBE_LL_H

#include <stdint.h>
#include "errno.h"
#include "mmio.h"

/* Function: socfpga_noc_probe_ll_read
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from the specified 
 * register offset within a NoC Probe hardware block.
 *
 * Parameters:
 *
 * base_address - The absolute physical MMIO base address of the target NoC probe instance.
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
 * precise bus exceptions.
 */
uint32_t socfpga_noc_probe_ll_read(uint32_t base_address, uint32_t offset);

/* Function: socfpga_noc_probe_ll_write
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to the specified 
 * register offset within a NoC Probe hardware block.
 *
 * Parameters:
 *
 * base_address - The absolute physical MMIO base address of the target NoC probe instance.
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
 * to handle any necessary Read-Modify-Write (RMW) logic or synchronization barriers 
 * before issuing the write.
 */
void socfpga_noc_probe_ll_write(uint32_t base_address, uint32_t offset,
                                uint32_t value);

#endif /* SOCFPGA_NOC_PROBE_LL_H */
