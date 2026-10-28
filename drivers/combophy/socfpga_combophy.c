/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_combophy.c
 *
 * Combo PHY source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_combophy.h"
#include "socfpga_combophy_ll.h"
#include "socfpga_combophy_reg.h"
int32_t socfpga_combophy_get_version(uint32_t base_address, uint32_t *version)
{
    return socfpga_combophy_read_reg(base_address, COMBOPHY_PHY_VERSION, version);
}
int32_t socfpga_combophy_get_features(uint32_t base_address, uint32_t *features)
{
    return socfpga_combophy_read_reg(base_address, COMBOPHY_PHY_FEATURES, features);
}
int32_t socfpga_combophy_read_reg(uint32_t base_address, uint32_t offset, uint32_t *value)
{
    if ((base_address == 0U) || (value == NULL)) { return -EINVAL; }
    *value = socfpga_combophy_ll_read(base_address, offset);
    return 0;
}
int32_t socfpga_combophy_write_reg(uint32_t base_address, uint32_t offset, uint32_t value)
{
    if (base_address == 0U) { return -EINVAL; }
    socfpga_combophy_ll_write(base_address, offset, value);
    return 0;
}
