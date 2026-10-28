/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_mmu.c
 *
 * MMU source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_mmu.h"
#include "socfpga_mmu_ll.h"

uint64_t socfpga_mmu_make_block_descriptor(uint64_t physical_address,
                                           uint32_t attr_index,
                                           uint32_t shareability,
                                           uint32_t access_permission,
                                           bool execute_never)
{
    return socfpga_mmu_ll_make_block_descriptor(physical_address, attr_index,
                                                shareability, access_permission,
                                                execute_never);
}

int32_t socfpga_mmu_enable(uint32_t exception_level, uint64_t ttbr0,
                           uint64_t tcr, uint64_t mair)
{
    socfpga_mmu_ll_invalidate_tlb();
    return socfpga_mmu_ll_enable_el(exception_level, ttbr0, tcr, mair);
}

int32_t socfpga_mmu_disable(uint32_t exception_level)
{
    int32_t ret = socfpga_mmu_ll_disable_el(exception_level);
    socfpga_mmu_ll_invalidate_tlb();
    return ret;
}

int32_t socfpga_mmu_is_enabled(uint32_t exception_level, bool *enabled)
{
    return socfpga_mmu_ll_is_enabled(exception_level, enabled);
}
