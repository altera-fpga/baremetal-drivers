/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "rst_mngr_api.h"

/* middleware */
extern int32_t rstmgr_mw_reset_device(rst_device_t dev);
extern int32_t rstmgr_mw_reset_get_status(rst_device_t dev, uint8_t *status);

int32_t reset_device(rst_device_t dev)
{
    return rstmgr_mw_reset_device(dev);
}

int32_t reset_get_device_status(rst_device_t dev, uint8_t *status)
{
    return rstmgr_mw_reset_get_status(dev, status);
}