/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include "errno.h"
#include "noc_firewall_api.h"
#include "socfpga_peripheral_reg_plat.h"

static uint32_t noc_firewall_api_base(void)
{
#ifdef SOCFPGA_NOC_FIREWALL_BASE
    return SOCFPGA_NOC_FIREWALL_BASE;
#else
    return 0U;
#endif
}

int32_t noc_firewall_api_get(socfpga_noc_firewall_target_t target,
                             uint32_t *value)
{
    uint32_t base = noc_firewall_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_firewall_get(base, target, value);
}

int32_t noc_firewall_api_set(socfpga_noc_firewall_target_t target,
                             uint32_t value)
{
    uint32_t base = noc_firewall_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_firewall_set(base, target, value);
}

int32_t noc_firewall_api_get_with_base(uint32_t base_address,
                                       socfpga_noc_firewall_target_t target,
                                       uint32_t *value)
{
    return socfpga_noc_firewall_get(base_address, target, value);
}

int32_t noc_firewall_api_set_with_base(uint32_t base_address,
                                       socfpga_noc_firewall_target_t target,
                                       uint32_t value)
{
    return socfpga_noc_firewall_set(base_address, target, value);
}

int32_t noc_firewall_api_allow_nonsecure(socfpga_noc_firewall_target_t target)
{
    uint32_t base = noc_firewall_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_firewall_allow_nonsecure(base, target);
}

int32_t noc_firewall_api_allow_nonsecure_with_base(uint32_t base_address,
                                                  socfpga_noc_firewall_target_t target)
{
    return socfpga_noc_firewall_allow_nonsecure(base_address, target);
}

