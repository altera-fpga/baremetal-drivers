/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rst_mngr_reg.h
 *
 * Reset Manager register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_RST_MNGR_REG_H__
#define __SOCFPGA_RST_MNGR_REG_H__

#include <stdint.h>
#include "socfpga_rst_mngr_reg_plat.h"

#define  RSTMGR_GET_BASE_ADDR(p)    rstmgr_get_base_addr(p)
#define  RSTMGR_GET_BIT_POS(p)      rstmgr_get_bit_pos(p)

/* Reset Status Register */
#define RESET_STAT                                          0x0000U
/* Timeout Status Register */
#define RESET_MISCSTAT                                      0x0008U
/* Handshake Enable */
#define RESET_HDSKEN                                        0x0010U
/* Handshake Request Register */
#define RESET_HDSKREQ                                       0x0014U
/* Handshake Acknowledge Register */
#define RESET_HDSKACK                                       0x0018U
/* ETR Stall Status Register */
#define RESET_HDSKSTALL                                     0x001CU
/* Peripheral 0 Module Reset Register */
#define RESET_PER0MODRST                                    0x0024U
/* Peripheral Module Reset Register */
#define RESET_PER1MODRST                                    0x0028U
/* Bridge Reset Register */
#define RESET_BRGMODRST                                     0x002CU
/* Debug Module Reset Register */
#define RESET_DBGMODRST                                     0x003CU
/* Bridge Warm Mask Register */
#define RESET_BRGWARMMASK                                   0x004CU
/* Test Status */
#define RESET_TSTSTA                                        0x005CU
/* Hand Shake Time Out Value  */
#define RESET_HDSKTIMEOUT                                   0x0064U
/* L3NOC Debug CS_DAP Handshake Time Out Value  */
#define RESET_DBGHDSKTIMEOUT                                0x006CU
/* dbgrstcmplt */
#define RESET_DBGRSTCMPLT                                   0x0070U
/* hpsrstcmplt */
#define RESET_HPSRSTCMPLT                                   0x0080U
/* cpuinreset */
#define RESET_CPUINRESET                                    0x0090U
/* On Chip RAM load done */
#define RESET_CPURSTRELEASE                                 0x0094U
/* cpu0_reset_base_low */
#define RESET_CPU0_RESET_BASE_LOW                           0x0098U
/* cpu0_reset_base_high */
#define RESET_CPU0_RESET_BASE_HIGH                          0x009CU
/* cpu1_reset_base_low */
#define RESET_CPU1_RESET_BASE_LOW                           0x00A0U
/* cpu1_reset_base_high */
#define RESET_CPU1_RESET_BASE_HIGH                          0x00A4U
/* cpu2_reset_base_low */
#define RESET_CPU2_RESET_BASE_LOW                           0x00A8U
/* cpu2_reset_base_high */
#define RESET_CPU2_RESET_BASE_HIGH                          0x00ACU
/* cpu3_reset_base_low */
#define RESET_CPU3_RESET_BASE_LOW                           0x00B0U
/* cpu3_reset_base_high */
#define RESET_CPU3_RESET_BASE_HIGH                          0x00B4U

/* Bit fields of stat register */
#define RESET_STAT_CSDAPRST_MASK                            0x02000000U
#define RESET_STAT_CSDAPRST_POS                             25U
#define RESET_STAT_DEBUGRST_MASK                            0x01000000U
#define RESET_STAT_DEBUGRST_POS                             24U
#define RESET_STAT_L4WD4RST_MASK                            0x00100000U
#define RESET_STAT_L4WD4RST_POS                             20U
#define RESET_STAT_L4WD3RST_MASK                            0x00080000U
#define RESET_STAT_L4WD3RST_POS                             19U
#define RESET_STAT_L4WD2RST_MASK                            0x00040000U
#define RESET_STAT_L4WD2RST_POS                             18U
#define RESET_STAT_L4WD1RST_MASK                            0x00020000U
#define RESET_STAT_L4WD1RST_POS                             17U
#define RESET_STAT_L4WD0RST_MASK                            0x00010000U
#define RESET_STAT_L4WD0RST_POS                             16U
#define RESET_STAT_SDMLASTPORRST_MASK                       0x00000004U
#define RESET_STAT_SDMLASTPORRST_POS                        2U
#define RESET_STAT_SDMWARMRST_MASK                          0x00000002U
#define RESET_STAT_SDMWARMRST_POS                           1U
#define RESET_STAT_SDMCOLDRST_MASK                          0x00000001U
#define RESET_STAT_SDMCOLDRST_POS                           0U

/* Bit fields of miscstat register */
#define RESET_MISCSTAT_DEBUGL3NOCTIMEOUT_MASK               0x00020000U
#define RESET_MISCSTAT_DEBUGL3NOCTIMEOUT_POS                17U
#define RESET_MISCSTAT_L3NOCDBGTIMEOUT_MASK                 0x00010000U
#define RESET_MISCSTAT_L3NOCDBGTIMEOUT_POS                  16U
#define RESET_MISCSTAT_F2STIMEOUT_MASK                      0x00001000U
#define RESET_MISCSTAT_F2STIMEOUT_POS                       12U
#define RESET_MISCSTAT_F2SDRAMTIMEOUT_MASK                  0x00000800U
#define RESET_MISCSTAT_F2SDRAMTIMEOUT_POS                   11U
#define RESET_MISCSTAT_SOC2FPGATIMEOUT_MASK                 0x00000400U
#define RESET_MISCSTAT_SOC2FPGATIMEOUT_POS                  10U
#define RESET_MISCSTAT_LWSOC2FPGATIMEOUT_MASK               0x00000200U
#define RESET_MISCSTAT_LWSOC2FPGATIMEOUT_POS                9U
#define RESET_MISCSTAT_ETRSTALLTIMEOUT_MASK                 0x00000008U
#define RESET_MISCSTAT_ETRSTALLTIMEOUT_POS                  3U
#define RESET_MISCSTAT_FPGAHSTIMEOUT_MASK                   0x00000004U
#define RESET_MISCSTAT_FPGAHSTIMEOUT_POS                    2U
#define RESET_MISCSTAT_EMIFTIMEOUT_MASK                     0x00000001U
#define RESET_MISCSTAT_EMIFTIMEOUT_POS                      0U

/* Bit fields of hdsken register */
#define RESET_HDSKEN_DEBUG_L3NOC_MASK                       0x00020000U
#define RESET_HDSKEN_DEBUG_L3NOC_POS                        17U
#define RESET_HDSKEN_L3NOC_DBG_MASK                         0x00010000U
#define RESET_HDSKEN_L3NOC_DBG_POS                          16U
#define RESET_HDSKEN_F2SOC_FLUSH_MASK                       0x00001000U
#define RESET_HDSKEN_F2SOC_FLUSH_POS                        12U
#define RESET_HDSKEN_F2SDRAM_FLUSH_MASK                     0x00000800U
#define RESET_HDSKEN_F2SDRAM_FLUSH_POS                      11U
#define RESET_HDSKEN_SOC2FPGA_FLUSH_MASK                    0x00000400U
#define RESET_HDSKEN_SOC2FPGA_FLUSH_POS                     10U
#define RESET_HDSKEN_LWSOC2FPGA_FLUSH_MASK                  0x00000200U
#define RESET_HDSKEN_LWSOC2FPGA_FLUSH_POS                   9U
#define RESET_HDSKEN_ETRSTALLEN_MASK                        0x00000008U
#define RESET_HDSKEN_ETRSTALLEN_POS                         3U
#define RESET_HDSKEN_FPGAHSEN_MASK                          0x00000004U
#define RESET_HDSKEN_FPGAHSEN_POS                           2U
#define RESET_HDSKEN_EMIF_FLUSH_MASK                        0x00000001U
#define RESET_HDSKEN_EMIF_FLUSH_POS                         0U

/* Bit fields of hdskreq register */
#define RESET_HDSKREQ_DEBUG_L3NOC_REQ_MASK                  0x00020000U
#define RESET_HDSKREQ_DEBUG_L3NOC_REQ_POS                   17U
#define RESET_HDSKREQ_L3NOC_DBG_REQ_MASK                    0x00010000U
#define RESET_HDSKREQ_L3NOC_DBG_REQ_POS                     16U
#define RESET_HDSKREQ_F2S_FLUSH_REQ_MASK                    0x00001000U
#define RESET_HDSKREQ_F2S_FLUSH_REQ_POS                     12U
#define RESET_HDSKREQ_F2SDRAM_FLUSH_REQ_MASK                0x00000800U
#define RESET_HDSKREQ_F2SDRAM_FLUSH_REQ_POS                 11U
#define RESET_HDSKREQ_SOC2FPGA_FLUSH_REQ_MASK               0x00000400U
#define RESET_HDSKREQ_SOC2FPGA_FLUSH_REQ_POS                10U
#define RESET_HDSKREQ_LWSOC2FPGA_FLUSH_REQ_MASK             0x00000200U
#define RESET_HDSKREQ_LWSOC2FPGA_FLUSH_REQ_POS              9U
#define RESET_HDSKREQ_ETRSTALLREQ_MASK                      0x00000008U
#define RESET_HDSKREQ_ETRSTALLREQ_POS                       3U
#define RESET_HDSKREQ_FPGAHSREQ_MASK                        0x00000004U
#define RESET_HDSKREQ_FPGAHSREQ_POS                         2U
#define RESET_HDSKREQ_EMIF_FLUSH_REQ_MASK                   0x00000001U
#define RESET_HDSKREQ_EMIF_FLUSH_REQ_POS                    0U

/* Bit fields of hdskack register */
#define RESET_HDSKACK_DEBUG_L3NOC_ACK_MASK                  0x00020000U
#define RESET_HDSKACK_DEBUG_L3NOC_ACK_POS                   17U
#define RESET_HDSKACK_L3NOC_DBG_ACK_MASK                    0x00010000U
#define RESET_HDSKACK_L3NOC_DBG_ACK_POS                     16U
#define RESET_HDSKACK_F2S_FLUSH_ACK_MASK                    0x00001000U
#define RESET_HDSKACK_F2S_FLUSH_ACK_POS                     12U
#define RESET_HDSKACK_F2SDRAM_FLUSH_ACK_MASK                0x00000800U
#define RESET_HDSKACK_F2SDRAM_FLUSH_ACK_POS                 11U
#define RESET_HDSKACK_SOC2FPGA_FLUSH_ACK_MASK               0x00000400U
#define RESET_HDSKACK_SOC2FPGA_FLUSH_ACK_POS                10U
#define RESET_HDSKACK_LWSOC2FPGA_FLUSH_ACK_MASK             0x00000200U
#define RESET_HDSKACK_LWSOC2FPGA_FLUSH_ACK_POS              9U
#define RESET_HDSKACK_ETRSTALLACK_MASK                      0x00000008U
#define RESET_HDSKACK_ETRSTALLACK_POS                       3U
#define RESET_HDSKACK_FPGAHSACK_MASK                        0x00000004U
#define RESET_HDSKACK_FPGAHSACK_POS                         2U
#define RESET_HDSKACK_EMIF_FLUSH_ACK_MASK                   0x00000001U
#define RESET_HDSKACK_EMIF_FLUSH_ACK_POS                    0U

/* Bit fields of hdskstall register */
#define RESET_HDSKSTALL_ETRSTALLWARMRST_MASK                0x00000001U
#define RESET_HDSKSTALL_ETRSTALLWARMRST_POS                 0U

/* Bit fields of per0modrst register */
#define RESET_PER0MODRST_DMAIF7_MASK                        0x80000000U
#define RESET_PER0MODRST_DMAIF7_POS                         31U
#define RESET_PER0MODRST_DMAIF6_MASK                        0x40000000U
#define RESET_PER0MODRST_DMAIF6_POS                         30U
#define RESET_PER0MODRST_DMAIF5_MASK                        0x20000000U
#define RESET_PER0MODRST_DMAIF5_POS                         29U
#define RESET_PER0MODRST_DMAIF4_MASK                        0x10000000U
#define RESET_PER0MODRST_DMAIF4_POS                         28U
#define RESET_PER0MODRST_DMAIF3_MASK                        0x08000000U
#define RESET_PER0MODRST_DMAIF3_POS                         27U
#define RESET_PER0MODRST_DMAIF2_MASK                        0x04000000U
#define RESET_PER0MODRST_DMAIF2_POS                         26U
#define RESET_PER0MODRST_DMAIF1_MASK                        0x02000000U
#define RESET_PER0MODRST_DMAIF1_POS                         25U
#define RESET_PER0MODRST_DMAIF0_MASK                        0x01000000U
#define RESET_PER0MODRST_DMAIF0_POS                         24U
#define RESET_PER0MODRST_EMACPTP_MASK                       0x00400000U
#define RESET_PER0MODRST_EMACPTP_POS                        22U
#define RESET_PER0MODRST_DMAECC_MASK                        0x00200000U
#define RESET_PER0MODRST_DMAECC_POS                         21U
#define RESET_PER0MODRST_SPIS1_MASK                         0x00100000U
#define RESET_PER0MODRST_SPIS1_POS                          20U
#define RESET_PER0MODRST_SPIS0_MASK                         0x00080000U
#define RESET_PER0MODRST_SPIS0_POS                          19U
#define RESET_PER0MODRST_SPIM1_MASK                         0x00040000U
#define RESET_PER0MODRST_SPIM1_POS                          18U
#define RESET_PER0MODRST_SPIM0_MASK                         0x00020000U
#define RESET_PER0MODRST_SPIM0_POS                          17U
#define RESET_PER0MODRST_DMA_MASK                           0x00010000U
#define RESET_PER0MODRST_DMA_POS                            16U
#define RESET_PER0MODRST_SDMMCECC_MASK                      0x00008000U
#define RESET_PER0MODRST_SDMMCECC_POS                       15U
#define RESET_PER0MODRST_NANDECC_MASK                       0x00002000U
#define RESET_PER0MODRST_NANDECC_POS                        13U
#define RESET_PER0MODRST_USB1ECC_MASK                       0x00001000U
#define RESET_PER0MODRST_USB1ECC_POS                        12U
#define RESET_PER0MODRST_USB0ECC_MASK                       0x00000800U
#define RESET_PER0MODRST_USB0ECC_POS                        11U
#define RESET_PER0MODRST_TSN2ECC_MASK                       0x00000400U
#define RESET_PER0MODRST_TSN2ECC_POS                        10U
#define RESET_PER0MODRST_TSN1ECC_MASK                       0x00000200U
#define RESET_PER0MODRST_TSN1ECC_POS                        9U
#define RESET_PER0MODRST_TSN0ECC_MASK                       0x00000100U
#define RESET_PER0MODRST_TSN0ECC_POS                        8U
#define RESET_PER0MODRST_SDMMC_MASK                         0x00000080U
#define RESET_PER0MODRST_SDMMC_POS                          7U
#define RESET_PER0MODRST_SOFTPHY_MASK                       0x00000040U
#define RESET_PER0MODRST_SOFTPHY_POS                        6U
#define RESET_PER0MODRST_NAND_MASK                          0x00000020U
#define RESET_PER0MODRST_NAND_POS                           5U
#define RESET_PER0MODRST_USB1_MASK                          0x00000010U
#define RESET_PER0MODRST_USB1_POS                           4U
#define RESET_PER0MODRST_USB0_MASK                          0x00000008U
#define RESET_PER0MODRST_USB0_POS                           3U
#define RESET_PER0MODRST_TSN2_MASK                          0x00000004U
#define RESET_PER0MODRST_TSN2_POS                           2U
#define RESET_PER0MODRST_TSN1_MASK                          0x00000002U
#define RESET_PER0MODRST_TSN1_POS                           1U
#define RESET_PER0MODRST_TSN0_MASK                          0x00000001U
#define RESET_PER0MODRST_TSN0_POS                           0U

/* Bit fields of per1modrst register */
#define RESET_PER1MODRST_WATCHDOG4_MASK                     0x04000000U
#define RESET_PER1MODRST_WATCHDOG4_POS                      26U
#define RESET_PER1MODRST_GPIO1_MASK                         0x02000000U
#define RESET_PER1MODRST_GPIO1_POS                          25U
#define RESET_PER1MODRST_GPIO0_MASK                         0x01000000U
#define RESET_PER1MODRST_GPIO0_POS                          24U
#define RESET_PER1MODRST_UART1_MASK                         0x00020000U
#define RESET_PER1MODRST_UART1_POS                          17U
#define RESET_PER1MODRST_UART0_MASK                         0x00010000U
#define RESET_PER1MODRST_UART0_POS                          16U
#define RESET_PER1MODRST_I3C1_MASK                          0x00004000U
#define RESET_PER1MODRST_I3C1_POS                           14U
#define RESET_PER1MODRST_I3C0_MASK                          0x00002000U
#define RESET_PER1MODRST_I3C0_POS                           13U
#define RESET_PER1MODRST_I2C4_MASK                          0x00001000U
#define RESET_PER1MODRST_I2C4_POS                           12U
#define RESET_PER1MODRST_I2C3_MASK                          0x00000800U
#define RESET_PER1MODRST_I2C3_POS                           11U
#define RESET_PER1MODRST_I2C2_MASK                          0x00000400U
#define RESET_PER1MODRST_I2C2_POS                           10U
#define RESET_PER1MODRST_I2C1_MASK                          0x00000200U
#define RESET_PER1MODRST_I2C1_POS                           9U
#define RESET_PER1MODRST_I2C0_MASK                          0x00000100U
#define RESET_PER1MODRST_I2C0_POS                           8U
#define RESET_PER1MODRST_SPTIMER1_MASK                      0x00000080U
#define RESET_PER1MODRST_SPTIMER1_POS                       7U
#define RESET_PER1MODRST_SPTIMER0_MASK                      0x00000040U
#define RESET_PER1MODRST_SPTIMER0_POS                       6U
#define RESET_PER1MODRST_L4SYSTIMER1_MASK                   0x00000020U
#define RESET_PER1MODRST_L4SYSTIMER1_POS                    5U
#define RESET_PER1MODRST_L4SYSTIMER0_MASK                   0x00000010U
#define RESET_PER1MODRST_L4SYSTIMER0_POS                    4U
#define RESET_PER1MODRST_WATCHDOG3_MASK                     0x00000008U
#define RESET_PER1MODRST_WATCHDOG3_POS                      3U
#define RESET_PER1MODRST_WATCHDOG2_MASK                     0x00000004U
#define RESET_PER1MODRST_WATCHDOG2_POS                      2U
#define RESET_PER1MODRST_WATCHDOG1_MASK                     0x00000002U
#define RESET_PER1MODRST_WATCHDOG1_POS                      1U
#define RESET_PER1MODRST_WATCHDOG0_MASK                     0x00000001U
#define RESET_PER1MODRST_WATCHDOG0_POS                      0U

/* Bit fields of brgmodrst register */
#define RESET_BRGMODRST_MPFE_MASK                           0x00000040U
#define RESET_BRGMODRST_MPFE_POS                            6U
#define RESET_BRGMODRST_FPGA2SDRAM_MASK                     0x00000008U
#define RESET_BRGMODRST_FPGA2SDRAM_POS                      3U
#define RESET_BRGMODRST_FPGA2SOC_MASK                       0x00000004U
#define RESET_BRGMODRST_FPGA2SOC_POS                        2U
#define RESET_BRGMODRST_LWSOC2FPGA_MASK                     0x00000002U
#define RESET_BRGMODRST_LWSOC2FPGA_POS                      1U
#define RESET_BRGMODRST_SOC2FPGA_MASK                       0x00000001U
#define RESET_BRGMODRST_SOC2FPGA_POS                        0U

/* Bit fields of dbgmodrst register */
#define RESET_DBGMODRST_DBG_RST_MASK                        0x00000001U
#define RESET_DBGMODRST_DBG_RST_POS                         0U

/* Bit fields of brgwarmmask register */
#define RESET_BRGWARMMASK_MPFE_MASK                         0x00000040U
#define RESET_BRGWARMMASK_MPFE_POS                          6U
#define RESET_BRGWARMMASK_FPGA2SDRAM_MASK                   0x00000008U
#define RESET_BRGWARMMASK_FPGA2SDRAM_POS                    3U
#define RESET_BRGWARMMASK_FPGA2SOC_MASK                     0x00000004U
#define RESET_BRGWARMMASK_FPGA2SOC_POS                      2U
#define RESET_BRGWARMMASK_LWSOC2FPGA_MASK                   0x00000002U
#define RESET_BRGWARMMASK_LWSOC2FPGA_POS                    1U
#define RESET_BRGWARMMASK_SOC2FPGA_MASK                     0x00000001U
#define RESET_BRGWARMMASK_SOC2FPGA_POS                      0U

/* Bit fields of tststa register */
#define RESET_TSTSTA_RSTST_MASK                             0x0000001FU
#define RESET_TSTSTA_RSTST_POS                              0U

/* Bit fields of hdsktimeout register */
#define RESET_HDSKTIMEOUT_VAL_MASK                          0xFFFFFFFFU
#define RESET_HDSKTIMEOUT_VAL_POS                           0U

/* Bit fields of dbghdsktimeout register */
#define RESET_DBGHDSKTIMEOUT_VAL_MASK                       0xFFFFFFFFU
#define RESET_DBGHDSKTIMEOUT_VAL_POS                        0U

/* Bit fields of dbgrstcmplt register */
#define RESET_DBGRSTCMPLT_SWDBGRSTCMPLT_MASK                0x00000001U
#define RESET_DBGRSTCMPLT_SWDBGRSTCMPLT_POS                 0U

/* Bit fields of hpsrstcmplt register */
#define RESET_HPSRSTCMPLT_HPSRSTCMPLT_MASK                  0x00000001U
#define RESET_HPSRSTCMPLT_HPSRSTCMPLT_POS                   0U

/* Bit fields of cpuinreset register */
#define RESET_CPUINRESET_CPU3_IN_RESET_MASK                 0x00000008U
#define RESET_CPUINRESET_CPU3_IN_RESET_POS                  3U
#define RESET_CPUINRESET_CPU2_IN_RESET_MASK                 0x00000004U
#define RESET_CPUINRESET_CPU2_IN_RESET_POS                  2U
#define RESET_CPUINRESET_CPU1_IN_RESET_MASK                 0x00000002U
#define RESET_CPUINRESET_CPU1_IN_RESET_POS                  1U
#define RESET_CPUINRESET_CPU0_IN_RESET_MASK                 0x00000001U
#define RESET_CPUINRESET_CPU0_IN_RESET_POS                  0U

/* Bit fields of cpurstrelease register */
#define RESET_CPURSTRELEASE_CPU3_RELEASE_MASK               0x00000008U
#define RESET_CPURSTRELEASE_CPU3_RELEASE_POS                3U
#define RESET_CPURSTRELEASE_CPU2_RELEASE_MASK               0x00000004U
#define RESET_CPURSTRELEASE_CPU2_RELEASE_POS                2U
#define RESET_CPURSTRELEASE_CPU1_RELEASE_MASK               0x00000002U
#define RESET_CPURSTRELEASE_CPU1_RELEASE_POS                1U
#define RESET_CPURSTRELEASE_CPU0_RELEASE_MASK               0x00000001U
#define RESET_CPURSTRELEASE_CPU0_RELEASE_POS                0U

/* Bit fields of cpu0_reset_base_low register */
#define RESET_CPU0_RESET_BASE_LOW_VECTOR_BASE_LOW_MASK      0x3FFFFFFFU
#define RESET_CPU0_RESET_BASE_LOW_VECTOR_BASE_LOW_POS       0U

/* Bit fields of cpu0_reset_base_high register */
#define RESET_CPU0_RESET_BASE_HIGH_VECTOR_BASE_HIGH_MASK    0x000000FFU
#define RESET_CPU0_RESET_BASE_HIGH_VECTOR_BASE_HIGH_POS     0U

/* Bit fields of cpu1_reset_base_low register */
#define RESET_CPU1_RESET_BASE_LOW_VECTOR_BASE_LOW_MASK      0x3FFFFFFFU
#define RESET_CPU1_RESET_BASE_LOW_VECTOR_BASE_LOW_POS       0U

/* Bit fields of cpu1_reset_base_high register */
#define RESET_CPU1_RESET_BASE_HIGH_VECTOR_BASE_HIGH_MASK    0x000000FFU
#define RESET_CPU1_RESET_BASE_HIGH_VECTOR_BASE_HIGH_POS     0U

/* Bit fields of cpu2_reset_base_low register */
#define RESET_CPU2_RESET_BASE_LOW_VECTOR_BASE_LOW_MASK      0x3FFFFFFFU
#define RESET_CPU2_RESET_BASE_LOW_VECTOR_BASE_LOW_POS       0U

/* Bit fields of cpu2_reset_base_high register */
#define RESET_CPU2_RESET_BASE_HIGH_VECTOR_BASE_HIGH_MASK    0x000000FFU
#define RESET_CPU2_RESET_BASE_HIGH_VECTOR_BASE_HIGH_POS     0U

/* Bit fields of cpu3_reset_base_low register */
#define RESET_CPU3_RESET_BASE_LOW_VECTOR_BASE_LOW_MASK      0x3FFFFFFFU
#define RESET_CPU3_RESET_BASE_LOW_VECTOR_BASE_LOW_POS       0U

/* Bit fields of cpu3_reset_base_high register */
#define RESET_CPU3_RESET_BASE_HIGH_VECTOR_BASE_HIGH_MASK    0x000000FFU
#define RESET_CPU3_RESET_BASE_HIGH_VECTOR_BASE_HIGH_POS     0U

static inline uint32_t rstmgr_get_base_addr(uint32_t p)
{
    if (p < 32U)
    {
        return RESET_PER0MODRST + RESET_MANAGER_BASE_ADDR;
    }
    else if (p < 64U)
    {
        return RESET_PER1MODRST + RESET_MANAGER_BASE_ADDR;
    }
    else
    {
        return RESET_BRGMODRST + RESET_MANAGER_BASE_ADDR;
    }
}

static inline uint8_t rstmgr_get_bit_pos(uint32_t p)
{
    if (p < 32U)
    {
        return (uint8_t)p;
    }
    else if (p < 64U)
    {
        return (uint8_t)(p - 32U);
    }
    else
    {
        return (uint8_t)(p - 64U);
    }
}

#endif /* __SOCFPGA_RST_MNGR_REG_H__ */
