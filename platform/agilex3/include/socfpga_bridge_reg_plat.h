/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge_reg_plat.h
 *
 * Agilex3 platform bridge demo windows and FPGA2HPS verify defaults.
 */

#ifndef SOCFPGA_BRIDGE_REG_PLAT_H
#define SOCFPGA_BRIDGE_REG_PLAT_H

/*
 * HPS-visible demo routing windows used by bridge_selftest loopback /
 * control-plane flows. Agilex3 shares the Agilex5 GHRD fabric map.
 */
#define SOCFPGA_BRIDGE_HPS2FPGA_BASE        0x00000000C0000000ULL
#define SOCFPGA_BRIDGE_FPGA2HPS_BASE        0x00000000D0000000ULL
#define SOCFPGA_BRIDGE_WINDOW_SIZE          0x10000000ULL  /* 256 MB */

/*
 * FPGA2HPS data-plane verify defaults match the Agilex5 U-Boot
 * fpga2hps_rw / System Console case until an Agilex3-specific GHRD
 * offset is published.
 */
#define SOCFPGA_BRIDGE_F2H_VERIFY_ADDR      0x0000000082000020ULL
#define SOCFPGA_BRIDGE_F2H_VERIFY_PATTERN   0x0000A5A5U
#define SOCFPGA_BRIDGE_F2H_VERIFY_WORDS     4U
#define SOCFPGA_BRIDGE_F2H_VERIFY_MAX_WORDS 1024U

/* SiP enable/disable of bridges is available on Agilex3. */
#define SOCFPGA_BRIDGE_SIP_SUPPORTED        1U

#endif /* SOCFPGA_BRIDGE_REG_PLAT_H */
