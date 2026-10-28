/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge.c
 *
 * Bridge source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_bridge.h"
#include "socfpga_bridge_ll.h"

static int32_t bridge_legacy_set(bridge_ll_id_t id, bool enable)
{
    int32_t rc = bridge_ll_set(id, enable);
    return (rc == BRIDGE_LL_OP_OK) ? 0 : -EIO;
}

int32_t enable_hps2fpga_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_HPS2FPGA, true);
}

int32_t disable_hps2fpga_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_HPS2FPGA, false);
}

int32_t enable_lwhps2fpga_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_LWHPS2FPGA, true);
}

int32_t disable_lwhps2fpga_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_LWHPS2FPGA, false);
}

int32_t enable_fpga2hps_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_FPGA2HPS, true);
}

int32_t disable_fpga2hps_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_FPGA2HPS, false);
}

int32_t enable_fpga2sdram_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_FPGA2SDRAM, true);
}

int32_t disable_fpga2sdram_bridge(void)
{
    return bridge_legacy_set(BRIDGE_LL_ID_FPGA2SDRAM, false);
}
