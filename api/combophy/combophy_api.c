/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include "errno.h"
#include "combophy_api.h"
#include "socfpga_peripheral_reg_plat.h"
static uint32_t combophy_api_base(void)
{
#ifdef SOCFPGA_COMBOPHY_BASE
    return SOCFPGA_COMBOPHY_BASE;
#else
    return 0U;
#endif
}
int32_t combophy_api_get_version(uint32_t *version)
{
    uint32_t base = combophy_api_base();
    if (base == 0U) { return -ENOSYS; }
    return socfpga_combophy_get_version(base, version);
}
int32_t combophy_api_get_features(uint32_t *features)
{
    uint32_t base = combophy_api_base();
    if (base == 0U) { return -ENOSYS; }
    return socfpga_combophy_get_features(base, features);
}

