/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic_reg_plat.h
 *
 * Agilex3 platform GIC register platform definitions.
 */

#ifndef SOCFPGA_GIC_REG_PLAT_H
#define SOCFPGA_GIC_REG_PLAT_H

/* Agilex3 GIC base addresses. */
#define SOCFPGA_GIC_DISTRIBUTOR_BASE_ADDR   0x1D000000U
#define SOCFPGA_GIC_REDISTRIBUTOR_BASE_ADDR 0x1D060000U

/* Backward-compatible aliases. */
#define REGISTER_SOCFPGA_DIST_BASE_ADDR SOCFPGA_GIC_DISTRIBUTOR_BASE_ADDR
#define REGISTER_SOCFPGA_RD_BASE_ADDR   SOCFPGA_GIC_REDISTRIBUTOR_BASE_ADDR

#endif /* SOCFPGA_GIC_REG_PLAT_H */
