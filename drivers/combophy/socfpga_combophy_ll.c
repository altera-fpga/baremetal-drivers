/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_combophy_ll.c
 *
 * Combo PHY source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_combophy_ll.h"
uint32_t socfpga_combophy_ll_read(uint32_t base_address, uint32_t offset)
{
    return RD_REG32(base_address + offset);
}
void socfpga_combophy_ll_write(uint32_t base_address, uint32_t offset, uint32_t value)
{
    WR_REG32(base_address + offset, value);
}
