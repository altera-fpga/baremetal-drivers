/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "clk_mngr_api.h"
#include "socfpga_clk_mngr_ll.h"
#include "errno.h"

int clk_mngr_api_init(void)
{
    return clk_mngr_platform_init();
}

int clk_mngr_api_get_freq(uint32_t clock_block_id, uint32_t *freq_hz)
{
    if (!freq_hz)
    {
        return -EINVAL;
    }
    /* Not exposed through this API. */
    if ((clock_block_t)clock_block_id == CLOCK_QSPI)
    {
        return -EINVAL;
    }

    return clk_mngr_ll_get_clk((clock_block_t)clock_block_id, freq_hz);
}

int clk_mngr_api_set_divisor(uint32_t clock_type, uint8_t divisor)
{
    return clk_mngr_ll_set_divisor(clock_type, divisor);
}

int clk_mngr_api_get_divisor(uint32_t clock_type, uint8_t *divisor)
{
    if (!divisor)
    {
        return -EINVAL;
    }

    return clk_mngr_ll_get_divisor(clock_type, divisor);
}
