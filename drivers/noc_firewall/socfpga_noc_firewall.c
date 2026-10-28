/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_noc_firewall.c
 *
 * NoC Firewall source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_noc_firewall_reg.h"
#include "socfpga_noc_firewall_ll.h"
#include "socfpga_noc_firewall.h"


static uint32_t noc_fw_allow_nonsecure_value(socfpga_noc_firewall_target_t target)
{
    switch (target) {
    case SOCFPGA_NOC_FW_SOC2FPGA:
    case SOCFPGA_NOC_FW_LWSOC2FPGA:
        return NOC_FW_BRIDGE_DISABLE_ALL_POLICY;
    default:
        return NOC_FW_L4_DISABLE_ALL_POLICY;
    }
}

static int32_t noc_fw_validate(uint32_t base_address, uint32_t offset)
{
    if ((base_address == 0U) || (offset > NOC_FIREWALL_TCU_BASE_OFST)) {
        return -EINVAL;
    }
    return 0;
}

int32_t socfpga_noc_firewall_get(uint32_t base_address,
                                 socfpga_noc_firewall_target_t target,
                                 uint32_t *value)
{
    return socfpga_noc_firewall_read_reg(base_address, (uint32_t)target, value);
}

int32_t socfpga_noc_firewall_set(uint32_t base_address,
                                 socfpga_noc_firewall_target_t target,
                                 uint32_t value)
{
    return socfpga_noc_firewall_write_reg(base_address, (uint32_t)target, value);
}

int32_t socfpga_noc_firewall_read_reg(uint32_t base_address, uint32_t offset,
                                      uint32_t *value)
{
    int32_t ret;

    if (value == NULL) {
        return -EINVAL;
    }
    ret = noc_fw_validate(base_address, offset);
    if (ret != 0) {
        return ret;
    }
    *value = socfpga_noc_firewall_ll_read(base_address, offset);
    return 0;
}

int32_t socfpga_noc_firewall_write_reg(uint32_t base_address, uint32_t offset,
                                       uint32_t value)
{
    int32_t ret = noc_fw_validate(base_address, offset);
    if (ret != 0) {
        return ret;
    }
    socfpga_noc_firewall_ll_write(base_address, offset, value);
    return 0;
}

int32_t socfpga_noc_firewall_allow_nonsecure(uint32_t base_address,
                                             socfpga_noc_firewall_target_t target)
{
    return socfpga_noc_firewall_write_reg(base_address,
                                          (uint32_t)target,
                                          noc_fw_allow_nonsecure_value(target));
}
