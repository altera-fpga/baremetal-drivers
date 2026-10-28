/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rst_mngr_ll.c
 *
 * Reset Manager source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdint.h>
#include "errno.h"

#include "mmio.h"
#include "socfpga_rst_mngr_ll.h"

#define RSTMGR_LL_MAX_BIT_POS 31U

static int32_t rstmgr_ll_check_bit_pos(uint8_t bit_pos)
{
    if (bit_pos > RSTMGR_LL_MAX_BIT_POS)
    {
        return -EINVAL;
    }

    return 0;
}

int32_t rstmgr_ll_assert(uint32_t reg_address, uint8_t bit_pos)
{
    uint32_t value;

    if (rstmgr_ll_check_bit_pos(bit_pos) != 0)
    {
        return -EINVAL;
    }

    value = RD_REG32(reg_address);
    value |= ((uint32_t)1U << bit_pos);
    WR_REG32(reg_address, value);

    return 0;
}

int32_t rstmgr_ll_deassert(uint32_t reg_address, uint8_t bit_pos)
{
    uint32_t value;

    if (rstmgr_ll_check_bit_pos(bit_pos) != 0)
    {
        return -EINVAL;
    }

    value = RD_REG32(reg_address);
    value &= ~((uint32_t)1U << bit_pos);
    WR_REG32(reg_address, value);

    return 0;
}

int32_t rstmgr_ll_get_status(uint32_t reg_address, uint8_t bit_pos, uint8_t *status)
{
    if ((status == NULL) || (rstmgr_ll_check_bit_pos(bit_pos) != 0))
    {
        return -EINVAL;
    }

    *status = (uint8_t)((RD_REG32(reg_address) >> bit_pos) & 1U);

    return 0;
}

