/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_watchdog_reg.h
 *
 * Watchdog register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_WATCHDOG_REG_H__
#define __SOCFPGA_WATCHDOG_REG_H__


/*Get base address*/
#define GET_WDT_BASE_ADDRESS(instance)    ((uint32_t)(0x10D00200U + \
    ((instance) * 0x100U)))

/*Maximum watchdog instances*/
#define MAX_WATCHDOG_INSTANCES                     5U

/*Reset Manager*/
#define SOCFPGA_RESET_MANAGER_BASE                 0x10D11000U
#define WDT_PER1MODRST_OFFSET                      0x28U
#define WDT0_RESET_BIT                             0U
#define WDT1_RESET_BIT                             1U
#define WDT2_RESET_BIT                             2U
#define WDT3_RESET_BIT                             3U
#define WDT4_RESET_BIT                             26U

/* Control Register */
#define WDT_CR                                     0x0000U
/* Timeout Range Register */
#define WDT_TORR                                   0x0004U
/* Current Counter Value Register */
#define WDT_CCVR                                   0x0008U
/* Counter Restart Register */
#define WDT_CRR                                    0x000CU
/* Interrupt Status Register */
#define WDT_STAT                                   0x0010U
/* Interrupt Clear Register */
#define WDT_EOI                                    0x0014U
/* Component Parameters Register 1 */
#define WDT_COMP_PARAM_1                           0x00F4U
/* Component Version Register */
#define WDT_COMP_VERSION                           0x00F8U
/* Component Type Register */
#define WDT_COMP_TYPE                              0x00FCU

/* Bit fields of WDT_CR register */
#define WDT_CR_RPL_MASK                            0x0000001CU
#define WDT_CR_RPL_POS                             2U
#define WDT_CR_RMOD_MASK                           0x00000002U
#define WDT_CR_RMOD_POS                            1U
#define WDT_CR_WDT_EN_MASK                         0x00000001U
#define WDT_CR_WDT_EN_POS                          0U

/* Bit fields of WDT_TORR register */
#define WDT_TORR_TOP_INIT_MASK                     0x000000F0U
#define WDT_TORR_TOP_INIT_POS                      4U
#define WDT_TORR_TOP_MASK                          0x0000000FU
#define WDT_TORR_TOP_POS                           0U

/* Bit fields of WDT_CCVR register */
#define WDT_CCVR_WDT_CCVR_MASK                     0xFFFFFFFFU
#define WDT_CCVR_WDT_CCVR_POS                      0U

/* Bit fields of WDT_CRR register */
#define WDT_CRR_WDT_CRR_MASK                       0x000000FFU
#define WDT_CRR_WDT_CRR_POS                        0U

/*WDT Restart command*/
#define WDT_CRR_RESTART_VAL                        0x76U

/* Bit fields of WDT_STAT register */
#define WDT_STAT_WDT_STAT_MASK                     0x00000001U
#define WDT_STAT_WDT_STAT_POS                      0U

/* Bit fields of WDT_EOI register */
#define WDT_EOI_WDT_EOI_MASK                       0x00000001U
#define WDT_EOI_WDT_EOI_POS                        0U

/* Bit fields of WDT_COMP_PARAM_1 register */
#define WDT_COMP_PARAM_1_WDT_CNT_WIDTH_MASK        0x1F000000U
#define WDT_COMP_PARAM_1_WDT_CNT_WIDTH_POS         24U
#define WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT_MASK    0x00F00000U
#define WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT_POS     20U
#define WDT_COMP_PARAM_1_WDT_DFLT_TOP_MASK         0x000F0000U
#define WDT_COMP_PARAM_1_WDT_DFLT_TOP_POS          16U
#define WDT_COMP_PARAM_1_WDT_DFLT_RPL_MASK         0x00001C00U
#define WDT_COMP_PARAM_1_WDT_DFLT_RPL_POS          10U
#define WDT_COMP_PARAM_1_APB_DATA_WIDTH_MASK       0x00000300U
#define WDT_COMP_PARAM_1_APB_DATA_WIDTH_POS        8U
#define WDT_COMP_PARAM_1_WDT_PAUSE_MASK            0x00000080U
#define WDT_COMP_PARAM_1_WDT_PAUSE_POS             7U
#define WDT_COMP_PARAM_1_WDT_USE_FIX_TOP_MASK      0x00000040U
#define WDT_COMP_PARAM_1_WDT_USE_FIX_TOP_POS       6U
#define WDT_COMP_PARAM_1_WDT_HC_TOP_MASK           0x00000020U
#define WDT_COMP_PARAM_1_WDT_HC_TOP_POS            5U
#define WDT_COMP_PARAM_1_WDT_HC_RPL_MASK           0x00000010U
#define WDT_COMP_PARAM_1_WDT_HC_RPL_POS            4U
#define WDT_COMP_PARAM_1_WDT_HC_RMOD_MASK          0x00000008U
#define WDT_COMP_PARAM_1_WDT_HC_RMOD_POS           3U
#define WDT_COMP_PARAM_1_WDT_DUAL_TOP_MASK         0x00000004U
#define WDT_COMP_PARAM_1_WDT_DUAL_TOP_POS          2U
#define WDT_COMP_PARAM_1_WDT_DFLT_RMOD_MASK        0x00000002U
#define WDT_COMP_PARAM_1_WDT_DFLT_RMOD_POS         1U
#define WDT_COMP_PARAM_1_WDT_ALWAYS_EN_MASK        0x00000001U
#define WDT_COMP_PARAM_1_WDT_ALWAYS_EN_POS         0U

/* Bit fields of WDT_COMP_VERSION register */
#define WDT_COMP_VERSION_WDT_COMP_VERSION_MASK     0xFFFFFFFFU
#define WDT_COMP_VERSION_WDT_COMP_VERSION_POS      0U

/* Bit fields of WDT_COMP_TYPE register */
#define WDT_COMP_TYPE_WDT_COMP_TYPE_MASK           0xFFFFFFFFU
#define WDT_COMP_TYPE_WDT_COMP_TYPE_POS            0U

#endif
