/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_noc_firewall_reg.h
 *
 * NoC Firewall register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_NOC_FIREWALL_REG_H
#define SOCFPGA_NOC_FIREWALL_REG_H

#define NOC_FIREWALL_L4_PER_BASE_OFST       0x0000U
#define NOC_FIREWALL_L4_SYS_BASE_OFST       0x0100U
#define NOC_FIREWALL_HPS2FPGA_BASE_OFST     0x0200U
#define NOC_FIREWALL_LWHPS2FPGA_BASE_OFST   0x0300U
#define NOC_FIREWALL_TCU_BASE_OFST          0x0400U

#define NOC_FW_TARGET_NAND                  0x0000U
#define NOC_FW_TARGET_SPI_MASTER0           0x001CU
#define NOC_FW_TARGET_SPI_MASTER1           0x0020U
#define NOC_FW_TARGET_SPI_SLAVE0            0x0024U
#define NOC_FW_TARGET_SPI_SLAVE1            0x0028U
#define NOC_FW_TARGET_SDMMC                 0x0040U
#define NOC_FW_TARGET_GPIO0                 0x0044U
#define NOC_FW_TARGET_GPIO1                 0x0048U
#define NOC_FW_TARGET_I2C0                  0x0050U
#define NOC_FW_TARGET_I2C1                  0x0054U
#define NOC_FW_TARGET_I2C2                  0x0058U
#define NOC_FW_TARGET_I2C3                  0x005CU
#define NOC_FW_TARGET_I2C4                  0x0060U
#define NOC_FW_TARGET_SP_TIMER0             0x0064U
#define NOC_FW_TARGET_SP_TIMER1             0x0068U
#define NOC_FW_TARGET_UART0                 0x006CU
#define NOC_FW_TARGET_UART1                 0x0070U
#define NOC_FW_TARGET_I3C0                  0x0074U
#define NOC_FW_TARGET_I3C1                  0x0078U
#define NOC_FW_TARGET_DMA0                  0x007CU
#define NOC_FW_TARGET_DMA1                  0x0080U
#define NOC_FW_TARGET_COMBO_PHY             0x0084U
#define NOC_FW_TARGET_DMA_ECC               0x0108U
#define NOC_FW_TARGET_RESET_MANAGER         0x0158U
#define NOC_FW_TARGET_SYSTEM_MANAGER        0x015CU
#define NOC_FW_TARGET_L4_NOC_PROBES         0x0190U
#define NOC_FW_TARGET_SOC2FPGA              0x0200U
#define NOC_FW_TARGET_LWSOC2FPGA            0x0300U
#define NOC_FW_TARGET_TCU                   0x0400U


#define NOC_FW_L4_DISABLE_ALL_POLICY         ((1U << 0) | (1U << 16) | (1U << 24))
#define NOC_FW_BRIDGE_DISABLE_ALL_POLICY     0xFFFFFFFFU

#define NOC_FW_REGISTER_VALUE_MASK          0xFFFFFFFFU
#define NOC_FW_REGISTER_VALUE_POS           0U

#endif /* SOCFPGA_NOC_FIREWALL_REG_H */
