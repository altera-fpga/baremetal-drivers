/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_mmu_ll.h
 *
 * MMU low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_MMU_LL_H
#define SOCFPGA_MMU_LL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

/* Function: socfpga_mmu_ll_make_block_descriptor
 *
 * Performs the bitwise composition of an ARMv8 VMSA Translation Table block 
 * descriptor. 
 *
 * This function handles the low-level bit shifting required to pack the physical 
 * base address together with its associated memory attributes (MAIR index, 
 * Shareability, Access Permissions, and Execute Never flags) into a single 
 * 64-bit value required by the hardware page table walker.
 *
 * Parameters:
 *
 * physical_address  - The absolute 64-bit physical address.
 * attr_index        - The index into the MAIR_ELx register for cache policies.
 * shareability      - The shareability domain (SH[1:0] bits).
 * access_permission - The access permission attributes (AP[2:1] bits).
 * execute_never     - True to assert the XN/PXN bits; false to allow execution.
 *
 * Returns:
 *
 * The fully formatted 64-bit hardware descriptor.
 *
 * Notes:
 *
 * This is an intentionally thin helper. It does not validate if the physical 
 * address is properly aligned to the block size boundaries (e.g., 2MB or 1GB).
 */
uint64_t socfpga_mmu_ll_make_block_descriptor(uint64_t physical_address,
                                              uint32_t attr_index,
                                              uint32_t shareability,
                                              uint32_t access_permission,
                                              bool execute_never);

/* Function: socfpga_mmu_ll_invalidate_tlb
 *
 * Executes the low-level ARM assembly instructions required to broadcast a 
 * Translation Lookaside Buffer (TLB) invalidation across the inner shareable domain.
 *
 * It invokes the `tlbi` instruction (e.g., `tlbi alle1` or `tlbi alle3`) depending 
 * on the current execution context, and guarantees completion by executing a 
 * Data Synchronization Barrier (`dsb`) followed by an Instruction Synchronization 
 * Barrier (`isb`).
 *
 * Returns:
 *
 * None.
 *
 * Notes:
 *
 * Must be called whenever page table descriptors are updated in memory to prevent 
 * the processor from using stale cached translations.
 */
void socfpga_mmu_ll_invalidate_tlb(void);

/* Function: socfpga_mmu_ll_enable_el
 *
 * Executes the precise ARM assembly sequence to initialize the MMU hardware for 
 * a specific Exception Level (EL1, EL2, or EL3).
 *
 * This function loads the provided configuration directly into the CPU's system 
 * registers (`TTBR0_ELx`, `TCR_ELx`, and `MAIR_ELx`). It then issues the required 
 * synchronization barriers before physically asserting the 'M' (MMU Enable) and 
 * 'C' (Cache Enable) bits within the System Control Register (`SCTLR_ELx`).
 *
 * Parameters:
 *
 * exception_level - The target Exception Level (1, 2, or 3).
 * ttbr0           - The 64-bit formatted Translation Table Base Register value.
 * tcr             - The 64-bit formatted Translation Control Register value.
 * mair            - The 64-bit formatted Memory Attribute Indirection Register value.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the requested Exception Level is invalid or not 
 * supported by the current processor state.
 *
 * Notes:
 *
 * Extreme care must be taken to ensure that the code executing this function 
 * resides in an identity-mapped memory region, otherwise the processor will 
 * immediately instruction-fault upon setting the 'M' bit.
 */
int32_t socfpga_mmu_ll_enable_el(uint32_t exception_level, uint64_t ttbr0,
                                 uint64_t tcr, uint64_t mair);

/* Function: socfpga_mmu_ll_disable_el
 *
 * Executes the ARM assembly sequence to tear down the MMU for a specific 
 * Exception Level.
 *
 * This function clears the 'M' and 'C' bits in the System Control Register 
 * (`SCTLR_ELx`), issues a `dsb` and `isb` to ensure all pending memory operations 
 * are drained, and then flushes the TLBs so no translations persist after the 
 * MMU is disabled.
 *
 * Parameters:
 *
 * exception_level - The target Exception Level (1, 2, or 3).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the requested Exception Level is invalid.
 *
 * Notes:
 *
 * Similar to enablement, the processor must be executing from a memory region 
 * where the physical address matches the virtual address to prevent an abort 
 * when translation is turned off.
 */
int32_t socfpga_mmu_ll_disable_el(uint32_t exception_level);

/* Function: socfpga_mmu_ll_is_enabled
 *
 * Performs a direct read of the System Control Register (`SCTLR_ELx`) for the 
 * requested Exception Level to determine the raw hardware status of the MMU.
 *
 * Parameters:
 *
 * exception_level - The Exception Level to query (1, 2, or 3).
 * enabled         - Pointer to a boolean where the masked state of the 'M' bit 
 * (bit 0) will be written.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL or the Exception Level is invalid.
 */
int32_t socfpga_mmu_ll_is_enabled(uint32_t exception_level, bool *enabled);

#endif /* SOCFPGA_MMU_LL_H */
