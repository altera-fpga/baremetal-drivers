/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_peripheral_reg_plat.h
 *
 * Agilex5 platform peripheral base address definitions.
 */

#ifndef SOCFPGA_PERIPHERAL_REG_PLAT_H
#define SOCFPGA_PERIPHERAL_REG_PLAT_H

#include <stdint.h>

#define SOCFPGA_PLATFORM_HAS_FIXED_PERIPHERAL_BASES 1U

#define SOCFPGA_I2C0_BASE          0x10C02800U
#define SOCFPGA_I2C1_BASE          0x10C02900U
#define SOCFPGA_I2C2_BASE          0x10C02A00U
#define SOCFPGA_I2C3_BASE          0x10C02B00U
#define SOCFPGA_I2C4_BASE          0x10C02C00U
#define SOCFPGA_I3C0_BASE          0x10DA0000U
#define SOCFPGA_I3C1_BASE          0x10DA1000U
#define SOCFPGA_SMMU_BASE          0x16000000U
#define SOCFPGA_NOC_FIREWALL_BASE  0x10D21000U
#define SOCFPGA_NOC_PROBE_BASE     0x10D22000U
#define SOCFPGA_CCU_BASE           0x1C000000U
#define SOCFPGA_COMBOPHY_BASE      0x10B92000U

#endif /* SOCFPGA_PERIPHERAL_REG_PLAT_H */
