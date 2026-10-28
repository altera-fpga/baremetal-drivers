/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rstmgr.c
 *
 * Reset Manager source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: middleware
 * Component: Reset Manager
 */

#include "socfpga_rstmgr.h"
#include "../api/rst_mngr/rst_mngr_api.h"
#include "errno.h"

static int32_t rstmgr_reset_common(uint32_t hw, int delay)
{
	int32_t ret;

	ret = rstmgr_assert_reset(hw);
	if (ret != 0)
		return ret;

	for (volatile int i = 0; i < delay; i++) { }

	return rstmgr_deassert_reset(hw);
}

/* API-facing layer mapping */
int32_t rstmgr_mw_reset_device(rst_device_t dev)
{
    switch (dev) {
    case RST_DEV_UART0:
        return rstmgr_reset_common(RST_UART0, 500);

    case RST_DEV_SDMMC:
        return rstmgr_reset_common(RST_SDMMC, 1000);

    default:
        return -EINVAL;
    }
}

int32_t rstmgr_mw_reset_get_status(rst_device_t dev, uint8_t *status)
{
    uint32_t hw;

    switch (dev) {
    case RST_DEV_UART0: hw = RST_UART0; break;
    case RST_DEV_SDMMC: hw = RST_SDMMC; break;
    default:
        return -EINVAL;
    }

    return rstmgr_get_reset_status(hw, status);
}
