/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_mmu.h
 *
 * MMU hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_MMU_H
#define SOCFPGA_MMU_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

/* Function: socfpga_mmu_make_block_descriptor
 *
 * Constructs a 64-bit ARMv8 Translation Table Block Descriptor. 
 *
 * This function packs the physical base address and various VMSA memory attributes 
 * (cacheability, shareability, access permissions) into a single 64-bit entry 
 * suitable for insertion into an L1 or L2 translation table. This maps a large, 
 * contiguous block of memory (e.g., 2MB or 1GB) directly to a physical address space.
 *
 * Parameters:
 *
 * physical_address  - The 64-bit aligned physical base address for the memory block.
 * attr_index        - The index (0-7) into the Memory Attribute Indirection Register (MAIR_ELx) 
 * defining the caching policies (e.g., Device-nGnRE, Normal Write-Back).
 * shareability      - The shareability domain (0 = Non-shareable, 2 = Outer Shareable, 
 * 3 = Inner Shareable).
 * access_permission - The AP[2:1] bits determining read/write access and privilege level 
 * requirements.
 * execute_never     - Set to true to assert the XN/PXN (Execute Never) bit, preventing 
 * instruction fetches from this memory region (crucial for device IO).
 *
 * Returns:
 *
 * The fully formatted 64-bit block descriptor ready to be written to page table memory.
 */
uint64_t socfpga_mmu_make_block_descriptor(uint64_t physical_address,
                                           uint32_t attr_index,
                                           uint32_t shareability,
                                           uint32_t access_permission,
                                           bool execute_never);

/* Function: socfpga_mmu_enable
 *
 * Configures and activates the Memory Management Unit for the specified ARMv8 
 * Exception Level. 
 *
 * This routine writes the caller-supplied translation table boundaries and caching 
 * definitions into the TCR_ELx and MAIR_ELx system registers. It then sets the 
 * TTBR0_ELx register to point to the base of the page tables in memory, issues 
 * the necessary TLB invalidations and barrier instructions (DSB, ISB), and finally 
 * sets the 'M' bit in the SCTLR_ELx register to enable address translation.
 *
 * Parameters:
 *
 * exception_level - The target processor privilege level (1 for EL1, 2 for EL2, 3 for EL3).
 * ttbr0           - The 64-bit physical address pointing to the base of the L0/L1 translation tables.
 * tcr             - The pre-formatted 64-bit value for the Translation Control Register (TCR_ELx), 
 * defining granule size, physical address size, and region bounds.
 * mair            - The pre-formatted 64-bit value for the Memory Attribute Indirection Register 
 * (MAIR_ELx), establishing the 8 available caching/memory types.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if an unsupported exception level is requested.
 */
int32_t socfpga_mmu_enable(uint32_t exception_level, uint64_t ttbr0,
                           uint64_t tcr, uint64_t mair);

/* Function: socfpga_mmu_disable
 *
 * Safely deactivates address translation for the specified Exception Level.
 *
 * This function clears the 'M' (MMU Enable) and 'C' (Cache Enable) bits in the 
 * System Control Register (SCTLR_ELx). It performs necessary data synchronization 
 * barriers to ensure outstanding memory transactions complete, then invalidates 
 * the Translation Lookaside Buffers (TLBs) to guarantee no stale mappings remain 
 * cached by the processor.
 *
 * Parameters:
 *
 * exception_level - The target processor privilege level (1 for EL1, 2 for EL2, 3 for EL3).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if an unsupported exception level is requested.
 */
int32_t socfpga_mmu_disable(uint32_t exception_level);

/* Function: socfpga_mmu_is_enabled
 *
 * Queries the hardware System Control Register (SCTLR_ELx) to determine if 
 * Stage 1 memory address translation is currently active for the specified 
 * Execution Level.
 *
 * Parameters:
 *
 * exception_level - The target processor privilege level to query (1, 2, or 3).
 * enabled         - Pointer to a boolean that will be set to true if the SCTLR_ELx.M 
 * bit is asserted, or false otherwise.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL or the exception level is out of bounds.
 */
int32_t socfpga_mmu_is_enabled(uint32_t exception_level, bool *enabled);

#endif /* SOCFPGA_MMU_H */
