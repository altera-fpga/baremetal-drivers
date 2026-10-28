/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: mmu_api.h
 *
 * Query whether Arm stage-1 address translation is enabled at a requested
 * exception level, and construct a translation-table block descriptor.
 * These functions do not install translation tables or enable or disable
 * address translation.
 */

#ifndef MMU_API_H
#define MMU_API_H

#include <stdbool.h>
#include <stdint.h>
#include "socfpga_mmu.h"

/* Function: mmu_api_is_enabled
 *
 * Reports whether stage-1 address translation is enabled at the requested exception level.
 *
 * Parameters:
 *
 *    exception_level - ARM exception level to query: EL1, EL2, or EL3.
 *    enabled - Receives true when SCTLR_ELx.M is set, or false otherwise.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for an invalid level or output pointer; -ENOSYS when the build cannot read the ARM system register.
 */
int32_t mmu_api_is_enabled(uint32_t exception_level, bool *enabled);
/* Function: mmu_api_make_block_descriptor
 *
 * Builds a 64-bit ARMv8 translation-table block descriptor from the supplied address and memory attributes.
 *
 * Parameters:
 *
 *    physical_address - Aligned physical base address for the mapped block.
 *    attr_index - MAIR attribute index used by the descriptor.
 *    shareability - Shareability field written into the descriptor.
 *    access_permission - Access-permission field written into the descriptor.
 *    execute_never - When true, sets the execute-never attribute.
 *
 * Returns:
 *
 *    The formatted 64-bit block descriptor.
 */
uint64_t mmu_api_make_block_descriptor(uint64_t physical_address,
                                       uint32_t attr_index,
                                       uint32_t shareability,
                                       uint32_t access_permission,
                                       bool execute_never);

#endif /* MMU_API_H */
