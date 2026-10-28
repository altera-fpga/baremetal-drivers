/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include "mmu_api.h"

int32_t mmu_api_is_enabled(uint32_t exception_level, bool *enabled)
{
    return socfpga_mmu_is_enabled(exception_level, enabled);
}

uint64_t mmu_api_make_block_descriptor(uint64_t physical_address,
                                       uint32_t attr_index,
                                       uint32_t shareability,
                                       uint32_t access_permission,
                                       bool execute_never)
{
    return socfpga_mmu_make_block_descriptor(physical_address, attr_index,
                                             shareability, access_permission,
                                             execute_never);
}
