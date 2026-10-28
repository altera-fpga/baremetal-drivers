/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_combophy_reg.h
 *
 * Combo PHY register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_COMBOPHY_REG_H
#define SOCFPGA_COMBOPHY_REG_H
#define COMBOPHY_PHY_DQ_TIMING          0x0000U
#define COMBOPHY_PHY_DQS_TIMING         0x0004U
#define COMBOPHY_PHY_DLL_MASTER_CTRL    0x000CU
#define COMBOPHY_PHY_DLL_SLAVE_CTRL     0x0010U
#define COMBOPHY_PHY_OBS0               0x0018U
#define COMBOPHY_PHY_DLL_OBS0           0x001CU
#define COMBOPHY_PHY_STATIC_TOGG        0x0028U
#define COMBOPHY_PHY_VERSION            0x0070U
#define COMBOPHY_PHY_FEATURES           0x0074U
#define COMBOPHY_CTB_CTRL               0x0080U
#define COMBOPHY_CTB_TSEL               0x0084U
#define COMBOPHY_REGISTER_VALUE_MASK    0xFFFFFFFFU
#define COMBOPHY_REGISTER_VALUE_POS     0U
#endif /* SOCFPGA_COMBOPHY_REG_H */
