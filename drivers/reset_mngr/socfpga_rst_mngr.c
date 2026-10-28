/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rst_mngr.c
 *
 * Reset Manager source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdint.h>
#include <stddef.h>
#include "errno.h"

#include "socfpga_rst_mngr.h"
#include "socfpga_rst_mngr_ll.h"
#include "socfpga_rst_mngr_reg.h"

#define RSTMGR_TOGGLE_DELAY_COUNT 1000U

static int32_t rstmgr_validate_peripheral(reset_periphrl_t per)
{
    if ((per < RST_PERIPHERAL_START) || (per > RST_PERIPHERAL_END))
    {
        return -EINVAL;
    }

    return 0;
}

static void rstmgr_delay(uint32_t loop_count)
{
    volatile uint32_t count = loop_count;

    while (count > 0U)
    {
        count--;
    }
}

int32_t rstmgr_assert_reset(reset_periphrl_t per)
{
    if (rstmgr_validate_peripheral(per) != 0)
    {
        return -EINVAL;
    }

    return rstmgr_ll_assert(RSTMGR_GET_BASE_ADDR((uint32_t)per),
                            RSTMGR_GET_BIT_POS((uint32_t)per));
}

int32_t rstmgr_deassert_reset(reset_periphrl_t per)
{
    if (rstmgr_validate_peripheral(per) != 0)
    {
        return -EINVAL;
    }

    return rstmgr_ll_deassert(RSTMGR_GET_BASE_ADDR((uint32_t)per),
                              RSTMGR_GET_BIT_POS((uint32_t)per));
}

int32_t rstmgr_toggle_reset(reset_periphrl_t per)
{
    int32_t ret;

    if (rstmgr_validate_peripheral(per) != 0)
    {
        return -EINVAL;
    }

    ret = rstmgr_assert_reset(per);
    if (ret != 0)
    {
        return ret;
    }

    rstmgr_delay(RSTMGR_TOGGLE_DELAY_COUNT);

    return rstmgr_deassert_reset(per);
}

int32_t rstmgr_get_reset_status(reset_periphrl_t per, uint8_t *status)
{
    if ((status == NULL) || (rstmgr_validate_peripheral(per) != 0))
    {
        return -EINVAL;
    }

    return rstmgr_ll_get_status(RSTMGR_GET_BASE_ADDR((uint32_t)per),
                                RSTMGR_GET_BIT_POS((uint32_t)per),
                                status);
}

