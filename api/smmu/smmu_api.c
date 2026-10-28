/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "smmu_api.h"
#include "socfpga_smmu.h"
#include "socfpga_smmu_reg.h"
#include "mmio.h"

int32_t smmu_api_enable(void)
{
    return smmu_enable();
}

int32_t smmu_api_disable(void)
{
    return smmu_disable();
}

int32_t smmu_api_deinit(void)
{
    return smmu_deinit();
}

int32_t smmu_api_is_enabled(bool *enabled)
{
    uint32_t value;

    if (enabled == NULL) {
        return -EINVAL;
    }

    value = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0);
    *enabled = ((value & SMMU_CR0_SMMUEN_MASK) != 0U);
    return 0;
}

int32_t smmu_api_read_reg(uint32_t offset, uint32_t *value)
{
    if (value == NULL) {
        return -EINVAL;
    }

    *value = RD_REG32(SMMU_BASE_ADDR + offset);
    return 0;
}

int32_t smmu_api_write_reg(uint32_t offset, uint32_t value)
{
    WR_REG32(SMMU_BASE_ADDR + offset, value);
    return 0;
}
