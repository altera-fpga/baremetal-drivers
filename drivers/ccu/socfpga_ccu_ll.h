/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ccu_ll.h
 *
 * Cache Coherency Unit (CCU) low-level driver interface for the SoCFPGA bare-metal 
 * software stack.
 *
 * This header defines the primitive MMIO (Memory-Mapped I/O) accessors used to 
 * interact with the CCU hardware. Because these registers are memory-mapped, 
 * these functions rely on volatile pointer casting to ensure the compiler does 
 * not optimize out read/write operations or reorder them, ensuring that the 
 * hardware state is updated precisely when the driver intends.
 *
 */

#ifndef SOCFPGA_CCU_LL_H
#define SOCFPGA_CCU_LL_H

#include <stdint.h>
#include "errno.h"
#include "mmio.h"

/* Function: socfpga_ccu_ll_read
 *
 * Performs a synchronous, volatile 32-bit Memory-Mapped I/O (MMIO) read 
 * operation from the CCU peripheral's address space.
 *
 * This function calculates the effective address by adding the `offset` to the 
 * provided `base_address`. It then performs a direct load instruction, 
 * guaranteeing that the value is fetched from the actual hardware register 
 * rather than a cached or register-optimized value.
 *
 * Parameters:
 *
 * base_address - The physical base address assigned to the CCU IP block.
 * offset       - The 32-bit aligned register offset to read from.
 *
 * Returns:
 *
 * The raw 32-bit value retrieved from the specified hardware register.
 */
uint32_t socfpga_ccu_ll_read(uint32_t base_address, uint32_t offset);

/* Function: socfpga_ccu_ll_write
 *
 * Performs a synchronous, volatile 32-bit Memory-Mapped I/O (MMIO) write 
 * operation to the CCU peripheral's address space.
 *
 * This function calculates the effective address by adding the `offset` to the 
 * provided `base_address`. It performs a direct store instruction, 
 * guaranteeing that the write transaction reaches the hardware interface 
 * immediately, which is essential for triggering control logic (such as 
 * starting a cache flush or updating a filter mask).
 *
 * Parameters:
 *
 * base_address - The physical base address assigned to the CCU IP block.
 * offset       - The 32-bit aligned register offset to write to.
 * value        - The 32-bit data payload to commit to the hardware.
 */
void socfpga_ccu_ll_write(uint32_t base_address, uint32_t offset, uint32_t value);

#endif /* SOCFPGA_CCU_LL_H */
