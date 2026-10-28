/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_clk_mngr_reg_plat.h
 *
 * Agilex5 platform Clock Manager register definitions for the SoCFPGA
 * bare-metal software stack.
 *
 */

#ifndef SOCFPGA_CLK_MNGR_REG_PLAT_H
#define SOCFPGA_CLK_MNGR_REG_PLAT_H


/* =========================================================================
 * Agilex5 Clock Manager base address
 * ========================================================================= */
#define CLK_MNGR_BASE_ADDR                           0x10D10000U

/* =========================================================================
 * Agilex5 internal oscillator rate (used when VCO source = CBINTOSC)
 * ========================================================================= */
#define CLKMGR_INTOSC_CLOCK_RATE_HZ                  460000000U

/* =========================================================================
 * Top-level control / status registers  (offset from CLK_MNGR_BASE_ADDR)
 * ========================================================================= */

/* Control Register */
#define CLK_MNGR_CTRL                                0x0000U
/* Status Register */
#define CLK_MNGR_STAT                                0x0004U
/* Test IO Control Register */
#define CLK_MNGR_TESTIOCTRL                          0x0008U
/* Interrupt Generate Register */
#define CLK_MNGR_INTRGEN                             0x000CU
/* Interrupt Mask Register */
#define CLK_MNGR_INTRMSK                             0x0010U
/* Interrupt Clear Register */
#define CLK_MNGR_INTRCLR                             0x0014U
/* Interrupt Status Register */
#define CLK_MNGR_INTRSTS                             0x0018U
/* Interrupt Status Sticky Register */
#define CLK_MNGR_INTRSTK                             0x001CU
/* Interrupt Raw Register */
#define CLK_MNGR_INTRRAW                             0x0020U

/* =========================================================================
 * Main PLL group registers  (offset from CLK_MNGR_BASE_ADDR)
 * ========================================================================= */

/* Main PLL Enable Register */
#define MAINPLL_CLK_MNGR_EN                          0x0024U
/* Main PLL Enable Set Register */
#define MAINPLL_CLK_MNGR_ENS                         0x0028U
/* Main PLL Enable Reset Register */
#define MAINPLL_CLK_MNGR_ENR                         0x002CU
/* Main PLL Bypass Register */
#define MAINPLL_CLK_MNGR_BYPASS                      0x0030U
/* Main PLL Bypass Set Register */
#define MAINPLL_CLK_MNGR_BYPASSS                     0x0034U
/* Main PLL Bypass Reset Register */
#define MAINPLL_CLK_MNGR_BYPASSR                     0x0038U
/* Main PLL NOC Clock Control Register */
#define MAINPLL_CLK_MNGR_NOCCLK                      0x0040U
/* Main PLL NOC Clock Divider Register */
#define MAINPLL_CLK_MNGR_NOCDIV                      0x0044U

/*
 * Agilex5: all PLL configuration registers are fully mapped.
 * (Uses the complete hardware register window for this platform.)
 */
/* Main PLL Global Register */
#define MAINPLL_CLK_MNGR_PLLGLOB                     0x0048U
/* Main PLL Feedback Divider Register */
#define MAINPLL_CLK_MNGR_FDBCK                       0x004CU
/* Main PLL Memory Bus Register */
#define MAINPLL_CLK_MNGR_MEM                         0x0050U
/* Main PLL Memory Status Register */
#define MAINPLL_CLK_MNGR_MEMSTAT                     0x0054U
/* Main PLL VCO Calibration Register */
#define MAINPLL_CLK_MNGR_VCOCALIB                    0x0058U
/* Main PLL Output Clock 0 Register */
#define MAINPLL_CLK_MNGR_PLLC0                       0x005CU
/* Main PLL Output Clock 1 Register */
#define MAINPLL_CLK_MNGR_PLLC1                       0x0060U
/* Main PLL Output Clock 2 Register */
#define MAINPLL_CLK_MNGR_PLLC2                       0x0064U
/* Main PLL Output Clock 3 Register */
#define MAINPLL_CLK_MNGR_PLLC3                       0x0068U
/* Main PLL M-Divider Register */
#define MAINPLL_CLK_MNGR_PLLM                        0x006CU
/* Main PLL Frequency Hop Register */
#define MAINPLL_CLK_MNGR_FHOP                        0x0070U
/* Main PLL Spread-Spectrum Control Register */
#define MAINPLL_CLK_MNGR_SSC                         0x0074U
/* Main PLL Lost-Lock Register */
#define MAINPLL_CLK_MNGR_LOSTLOCK                    0x0078U

/* =========================================================================
 * Peripheral PLL group registers  (offset from CLK_MNGR_BASE_ADDR)
 * ========================================================================= */

/* Peripheral PLL Enable Register */
#define PERPLL_CLK_MNGR_EN                           0x007CU
/* Peripheral PLL Enable Set Register */
#define PERPLL_CLK_MNGR_ENS                          0x0080U
/* Peripheral PLL Enable Reset Register */
#define PERPLL_CLK_MNGR_ENR                          0x0084U
/* Peripheral PLL Bypass Register */
#define PERPLL_CLK_MNGR_BYPASS                       0x0088U
/* Peripheral PLL Bypass Set Register */
#define PERPLL_CLK_MNGR_BYPASSS                      0x008CU
/* Peripheral PLL Bypass Reset Register */
#define PERPLL_CLK_MNGR_BYPASSR                      0x0090U
/* Peripheral PLL EMAC Control Register */
#define PERPLL_CLK_MNGR_EMACCTL                      0x0094U
/* Peripheral PLL GPIO Debounce Divider Register */
#define PERPLL_CLK_MNGR_GPIODIV                      0x0098U
/* Peripheral PLL Global Register */
#define PERPLL_CLK_MNGR_PLLGLOB                      0x009CU
/* Peripheral PLL Feedback Divider Register */
#define PERPLL_CLK_MNGR_FDBCK                        0x00A0U
/* Peripheral PLL Memory Bus Register */
#define PERPLL_CLK_MNGR_MEM                          0x00A4U
/* Peripheral PLL Memory Status Register */
#define PERPLL_CLK_MNGR_MEMSTAT                      0x00A8U
/* Peripheral PLL VCO Calibration Register */
#define PERPLL_CLK_MNGR_VCOCALIB                     0x00ACU
/* Peripheral PLL Output Clock 0 Register */
#define PERPLL_CLK_MNGR_PLLC0                        0x00B0U
/* Peripheral PLL Output Clock 1 Register */
#define PERPLL_CLK_MNGR_PLLC1                        0x00B4U
/* Peripheral PLL Output Clock 2 Register */
#define PERPLL_CLK_MNGR_PLLC2                        0x00B8U
/* Peripheral PLL Output Clock 3 Register */
#define PERPLL_CLK_MNGR_PLLC3                        0x00BCU
/* Peripheral PLL M-Divider Register */
#define PERPLL_CLK_MNGR_PLLM                         0x00C0U
/* Peripheral PLL Frequency Hop Register */
#define PERPLL_CLK_MNGR_FHOP                         0x00C4U
/* Peripheral PLL Spread-Spectrum Control Register */
#define PERPLL_CLK_MNGR_SSC                          0x00C8U
/* Peripheral PLL Lost-Lock Register */
#define PERPLL_CLK_MNGR_LOSTLOCK                     0x00CCU

/* =========================================================================
 * Altera (counter) group registers  (offset from CLK_MNGR_BASE_ADDR)
 * ========================================================================= */

/* JTAG Clock Register */
#define CLK_MNGR_JTAG                                0x00D0U
/* EMAC A Free-Running Clock Counter Register */
#define CLK_MNGR_EMACACTR                            0x00D4U
/* EMAC B Free-Running Clock Counter Register */
#define CLK_MNGR_EMACBCTR                            0x00D8U
/* EMAC PTP Free-Running Clock Counter Register */
#define CLK_MNGR_EMACPTPCTR                          0x00DCU
/* GPIO Debounce Free-Running Clock Counter Register */
#define CLK_MNGR_GPIODBCTR                           0x00E0U
/* S2F User 0 Free-Running Clock Counter Register */
#define CLK_MNGR_S2FUSER0CTR                         0x00E8U
/* S2F User 1 Free-Running Clock Counter Register */
#define CLK_MNGR_S2FUSER1CTR                         0x00ECU
/* PSI Reference Free-Running Clock Counter Register */
#define CLK_MNGR_PSIREFCTR                           0x00F0U
/* External Counter Reset Control Register */
#define CLK_MNGR_EXTCNTRST                           0x00F4U
/* USB 3.1 Clock Counter Register */
#define CLK_MNGR_USB31CTR                            0x00F8U
/* DSU Clock Counter Register */
#define CLK_MNGR_DSUCTR                              0x00FCU
/* Core 0/1 Clock Counter Register */
#define CLK_MNGR_CORE01CTR                           0x0100U
/* Core 2/3 Clock Source Register */
#define CLK_MNGR_CORE23CTR                           0x0104U
/* Core 2 Clock Counter Register */
#define CLK_MNGR_CORE2CTR                            0x0108U
/* Core 3 Clock Counter Register */
#define CLK_MNGR_CORE3CTR                            0x010CU
/* Serial Consolidation PLL Control Register */
#define CLK_MNGR_SERIAL_CON_PLL_CTR                  0x0110U

/* =========================================================================
 * Bit fields  ctrl register
 * ========================================================================= */
#define CLK_MNGR_CTRL_SWCTRLBTCLKSEL_MASK            0x00000200U
#define CLK_MNGR_CTRL_SWCTRLBTCLKSEL_POS             9U
#define CLK_MNGR_CTRL_SWCTRLBTCLKEN_MASK             0x00000100U
#define CLK_MNGR_CTRL_SWCTRLBTCLKEN_POS              8U
#define CLK_MNGR_CTRL_BOOTMODE_MASK                  0x00000001U
#define CLK_MNGR_CTRL_BOOTMODE_POS                   0U

/* =========================================================================
 * Bit fields  stat register
 * ========================================================================= */
#define CLK_MNGR_STAT_BOOTCLKSRC_MASK                0x02000000U
#define CLK_MNGR_STAT_BOOTCLKSRC_POS                 25U
#define CLK_MNGR_STAT_BOOTMODE_MASK                  0x01000000U
#define CLK_MNGR_STAT_BOOTMODE_POS                   24U
#define CLK_MNGR_STAT_PERF_TRANS_MASK                0x00020000U
#define CLK_MNGR_STAT_PERF_TRANS_POS                 17U
#define CLK_MNGR_STAT_PERPLLLOCKED_MASK              0x00010000U
#define CLK_MNGR_STAT_PERPLLLOCKED_POS               16U
#define CLK_MNGR_STAT_MAIN_TRANS_MASK                0x00000200U
#define CLK_MNGR_STAT_MAIN_TRANS_POS                 9U
#define CLK_MNGR_STAT_MAINPLLLOCKED_MASK             0x00000100U
#define CLK_MNGR_STAT_MAINPLLLOCKED_POS              8U
#define CLK_MNGR_STAT_BUSY_MASK                      0x00000001U
#define CLK_MNGR_STAT_BUSY_POS                       0U

/* All-PLL-locked convenience mask (Main + Peripheral) */
#define CLK_MNGR_STAT_ALLPLL_LOCKED_MASK             (CLK_MNGR_STAT_MAINPLLLOCKED_MASK | \
                                                       CLK_MNGR_STAT_PERPLLLOCKED_MASK)

/* =========================================================================
 * Bit fields  testioctrl register
 * ========================================================================= */
#define CLK_MNGR_TESTIOCTRL_DEBUGCLKSEL_MASK         0x00010000U
#define CLK_MNGR_TESTIOCTRL_DEBUGCLKSEL_POS          16U
#define CLK_MNGR_TESTIOCTRL_PERICLKSEL_MASK          0x00000300U
#define CLK_MNGR_TESTIOCTRL_PERICLKSEL_POS           8U
#define CLK_MNGR_TESTIOCTRL_MAINCLKSEL_MASK          0x00000003U
#define CLK_MNGR_TESTIOCTRL_MAINCLKSEL_POS           0U

/* =========================================================================
 * Bit fields  intrgen / intrmsk / intrclr / intrsts / intrstk / intrraw
 * ========================================================================= */
#define CLK_MNGR_INTRGEN_EN_MASK                     0x00000001U
#define CLK_MNGR_INTRGEN_EN_POS                      0U

#define CLK_MNGR_INTRMSK_PERLOCKLOST_MASK            0x00000008U
#define CLK_MNGR_INTRMSK_PERLOCKLOST_POS             3U
#define CLK_MNGR_INTRMSK_MAINLOCKLOST_MASK           0x00000004U
#define CLK_MNGR_INTRMSK_MAINLOCKLOST_POS            2U
#define CLK_MNGR_INTRMSK_PERLOCKACHIEVED_MASK        0x00000002U
#define CLK_MNGR_INTRMSK_PERLOCKACHIEVED_POS         1U
#define CLK_MNGR_INTRMSK_MAINLOCKACHIEVED_MASK       0x00000001U
#define CLK_MNGR_INTRMSK_MAINLOCKACHIEVED_POS        0U

#define CLK_MNGR_INTRCLR_PERLOCKLOST_MASK            0x00000008U
#define CLK_MNGR_INTRCLR_PERLOCKLOST_POS             3U
#define CLK_MNGR_INTRCLR_MAINLOCKLOST_MASK           0x00000004U
#define CLK_MNGR_INTRCLR_MAINLOCKLOST_POS            2U
#define CLK_MNGR_INTRCLR_PERLOCKACHIEVED_MASK        0x00000002U
#define CLK_MNGR_INTRCLR_PERLOCKACHIEVED_POS         1U
#define CLK_MNGR_INTRCLR_MAINLOCKACHIEVED_MASK       0x00000001U
#define CLK_MNGR_INTRCLR_MAINLOCKACHIEVED_POS        0U

#define CLK_MNGR_INTRSTS_PERLOCKLOST_MASK            0x00000008U
#define CLK_MNGR_INTRSTS_PERLOCKLOST_POS             3U
#define CLK_MNGR_INTRSTS_MAINLOCKLOST_MASK           0x00000004U
#define CLK_MNGR_INTRSTS_MAINLOCKLOST_POS            2U
#define CLK_MNGR_INTRSTS_PERLOCKACHIEVED_MASK        0x00000002U
#define CLK_MNGR_INTRSTS_PERLOCKACHIEVED_POS         1U
#define CLK_MNGR_INTRSTS_MAINLOCKACHIEVED_MASK       0x00000001U
#define CLK_MNGR_INTRSTS_MAINLOCKACHIEVED_POS        0U

#define CLK_MNGR_INTRSTK_PERLOCKLOST_MASK            0x00000008U
#define CLK_MNGR_INTRSTK_PERLOCKLOST_POS             3U
#define CLK_MNGR_INTRSTK_MAINLOCKLOST_MASK           0x00000004U
#define CLK_MNGR_INTRSTK_MAINLOCKLOST_POS            2U
#define CLK_MNGR_INTRSTK_PERLOCKACHIEVED_MASK        0x00000002U
#define CLK_MNGR_INTRSTK_PERLOCKACHIEVED_POS         1U
#define CLK_MNGR_INTRSTK_MAINLOCKACHIEVED_MASK       0x00000001U
#define CLK_MNGR_INTRSTK_MAINLOCKACHIEVED_POS        0U

#define CLK_MNGR_INTRRAW_PERLOCKLOST_MASK            0x00000008U
#define CLK_MNGR_INTRRAW_PERLOCKLOST_POS             3U
#define CLK_MNGR_INTRRAW_MAINLOCKLOST_MASK           0x00000004U
#define CLK_MNGR_INTRRAW_MAINLOCKLOST_POS            2U
#define CLK_MNGR_INTRRAW_PERLOCKACHIEVED_MASK        0x00000002U
#define CLK_MNGR_INTRRAW_PERLOCKACHIEVED_POS         1U
#define CLK_MNGR_INTRRAW_MAINLOCKACHIEVED_MASK       0x00000001U
#define CLK_MNGR_INTRRAW_MAINLOCKACHIEVED_POS        0U

/* =========================================================================
 * Bit fields  MAINPLL en / ens / enr
 * ========================================================================= */
#define CLK_MNGR_EN_CORE3EN_MASK                     0x00000800U
#define CLK_MNGR_EN_CORE3EN_POS                      11U
#define CLK_MNGR_EN_CORE2EN_MASK                     0x00000400U
#define CLK_MNGR_EN_CORE2EN_POS                      10U
#define CLK_MNGR_EN_CORE1EN_MASK                     0x00000200U
#define CLK_MNGR_EN_CORE1EN_POS                      9U
#define CLK_MNGR_EN_CORE0EN_MASK                     0x00000100U
#define CLK_MNGR_EN_CORE0EN_POS                      8U
#define CLK_MNGR_EN_S2FUSER0CLKEN_MASK               0x00000040U
#define CLK_MNGR_EN_S2FUSER0CLKEN_POS                6U
#define CLK_MNGR_EN_CSCLKEN_MASK                     0x00000010U
#define CLK_MNGR_EN_CSCLKEN_POS                      4U
#define CLK_MNGR_EN_L4SPCLKEN_MASK                   0x00000008U
#define CLK_MNGR_EN_L4SPCLKEN_POS                    3U
#define CLK_MNGR_EN_L4MPCLKEN_MASK                   0x00000004U
#define CLK_MNGR_EN_L4MPCLKEN_POS                    2U
#define CLK_MNGR_EN_L4MAINCLKEN_MASK                 0x00000002U
#define CLK_MNGR_EN_L4MAINCLKEN_POS                  1U

#define CLK_MNGR_ENS_CORE3EN_MASK                    0x00000800U
#define CLK_MNGR_ENS_CORE3EN_POS                     11U
#define CLK_MNGR_ENS_CORE2EN_MASK                    0x00000400U
#define CLK_MNGR_ENS_CORE2EN_POS                     10U
#define CLK_MNGR_ENS_CORE1EN_MASK                    0x00000200U
#define CLK_MNGR_ENS_CORE1EN_POS                     9U
#define CLK_MNGR_ENS_CORE0EN_MASK                    0x00000100U
#define CLK_MNGR_ENS_CORE0EN_POS                     8U
#define CLK_MNGR_ENS_S2FUSER0CLKEN_MASK              0x00000040U
#define CLK_MNGR_ENS_S2FUSER0CLKEN_POS               6U
#define CLK_MNGR_ENS_CSCLKEN_MASK                    0x00000010U
#define CLK_MNGR_ENS_CSCLKEN_POS                     4U
#define CLK_MNGR_ENS_L4SPCLKEN_MASK                  0x00000008U
#define CLK_MNGR_ENS_L4SPCLKEN_POS                   3U
#define CLK_MNGR_ENS_L4MPCLKEN_MASK                  0x00000004U
#define CLK_MNGR_ENS_L4MPCLKEN_POS                   2U
#define CLK_MNGR_ENS_L4MAINCLKEN_MASK                0x00000002U
#define CLK_MNGR_ENS_L4MAINCLKEN_POS                 1U

#define CLK_MNGR_ENR_CORE3EN_MASK                    0x00000800U
#define CLK_MNGR_ENR_CORE3EN_POS                     11U
#define CLK_MNGR_ENR_CORE2EN_MASK                    0x00000400U
#define CLK_MNGR_ENR_CORE2EN_POS                     10U
#define CLK_MNGR_ENR_CORE1EN_MASK                    0x00000200U
#define CLK_MNGR_ENR_CORE1EN_POS                     9U
#define CLK_MNGR_ENR_CORE0EN_MASK                    0x00000100U
#define CLK_MNGR_ENR_CORE0EN_POS                     8U
#define CLK_MNGR_ENR_S2FUSER0CLKEN_MASK              0x00000040U
#define CLK_MNGR_ENR_S2FUSER0CLKEN_POS               6U
#define CLK_MNGR_ENR_CSCLKEN_MASK                    0x00000010U
#define CLK_MNGR_ENR_CSCLKEN_POS                     4U
#define CLK_MNGR_ENR_L4SPCLKEN_MASK                  0x00000008U
#define CLK_MNGR_ENR_L4SPCLKEN_POS                   3U
#define CLK_MNGR_ENR_L4MPCLKEN_MASK                  0x00000004U
#define CLK_MNGR_ENR_L4MPCLKEN_POS                   2U
#define CLK_MNGR_ENR_L4MAINCLKEN_MASK                0x00000002U
#define CLK_MNGR_ENR_L4MAINCLKEN_POS                 1U

/* =========================================================================
 * Bit fields  MAINPLL bypass / bypasss / bypassr
 * ========================================================================= */
#define CLK_MNGR_BYPASS_CORE3_MASK                   0x00000080U
#define CLK_MNGR_BYPASS_CORE3_POS                    7U
#define CLK_MNGR_BYPASS_CORE2_MASK                   0x00000040U
#define CLK_MNGR_BYPASS_CORE2_POS                    6U
#define CLK_MNGR_BYPASS_CORE01_MASK                  0x00000020U
#define CLK_MNGR_BYPASS_CORE01_POS                   5U
#define CLK_MNGR_BYPASS_DSU_MASK                     0x00000010U
#define CLK_MNGR_BYPASS_DSU_POS                      4U
#define CLK_MNGR_BYPASS_S2FUSER0_MASK                0x00000004U
#define CLK_MNGR_BYPASS_S2FUSER0_POS                 2U
#define CLK_MNGR_BYPASS_NOC_MASK                     0x00000002U
#define CLK_MNGR_BYPASS_NOC_POS                      1U

/* Bypass-all value for Main PLL (from ATF: CLKMGR_MAINPLL_BYPASS_ALL) */
#define CLK_MNGR_MAINPLL_BYPASS_ALL                  0xF6U

#define CLK_MNGR_BYPASSS_CORE3_MASK                  0x00000080U
#define CLK_MNGR_BYPASSS_CORE3_POS                   7U
#define CLK_MNGR_BYPASSS_CORE2_MASK                  0x00000040U
#define CLK_MNGR_BYPASSS_CORE2_POS                   6U
#define CLK_MNGR_BYPASSS_CORE01_MASK                 0x00000020U
#define CLK_MNGR_BYPASSS_CORE01_POS                  5U
#define CLK_MNGR_BYPASSS_DSU_MASK                    0x00000010U
#define CLK_MNGR_BYPASSS_DSU_POS                     4U
#define CLK_MNGR_BYPASSS_S2FUSER0_MASK               0x00000004U
#define CLK_MNGR_BYPASSS_S2FUSER0_POS                2U
#define CLK_MNGR_BYPASSS_NOC_MASK                    0x00000002U
#define CLK_MNGR_BYPASSS_NOC_POS                     1U

#define CLK_MNGR_BYPASSR_CORE3_MASK                  0x00000080U
#define CLK_MNGR_BYPASSR_CORE3_POS                   7U
#define CLK_MNGR_BYPASSR_CORE2_MASK                  0x00000040U
#define CLK_MNGR_BYPASSR_CORE2_POS                   6U
#define CLK_MNGR_BYPASSR_CORE01_MASK                 0x00000020U
#define CLK_MNGR_BYPASSR_CORE01_POS                  5U
#define CLK_MNGR_BYPASSR_DSU_MASK                    0x00000010U
#define CLK_MNGR_BYPASSR_DSU_POS                     4U
#define CLK_MNGR_BYPASSR_S2FUSER0_MASK               0x00000004U
#define CLK_MNGR_BYPASSR_S2FUSER0_POS                2U
#define CLK_MNGR_BYPASSR_NOC_MASK                    0x00000002U
#define CLK_MNGR_BYPASSR_NOC_POS                     1U

/* =========================================================================
 * Bit fields  nocclk register
 * ========================================================================= */
#define CLK_MNGR_NOCCLK_SRC_MASK                     0x00070000U
#define CLK_MNGR_NOCCLK_SRC_POS                      16U

/* =========================================================================
 * Bit fields  nocdiv register
 * ========================================================================= */
#define CLK_MNGR_NOCDIV_CSPDBGCLK_MASK               0x30000000U
#define CLK_MNGR_NOCDIV_CSPDBGCLK_POS                28U
#define CLK_MNGR_NOCDIV_CSTRACECLK_MASK              0x0C000000U
#define CLK_MNGR_NOCDIV_CSTRACECLK_POS               26U
#define CLK_MNGR_NOCDIV_CSCLK_MASK                   0x03000000U
#define CLK_MNGR_NOCDIV_CSCLK_POS                    24U
#define CLK_MNGR_NOCDIV_MPUPERIPHDIV_MASK            0x00300000U
#define CLK_MNGR_NOCDIV_MPUPERIPHDIV_POS             20U
#define CLK_MNGR_NOCDIV_CCUDIV_MASK                  0x000C0000U
#define CLK_MNGR_NOCDIV_CCUDIV_POS                   18U
#define CLK_MNGR_NOCDIV_SOFTPHYDIV_MASK              0x00030000U
#define CLK_MNGR_NOCDIV_SOFTPHYDIV_POS               16U
#define CLK_MNGR_NOCDIV_L4SPCLK_MASK                 0x000000C0U
#define CLK_MNGR_NOCDIV_L4SPCLK_POS                  6U
#define CLK_MNGR_NOCDIV_L4MPCLK_MASK                 0x00000030U
#define CLK_MNGR_NOCDIV_L4MPCLK_POS                  4U
#define CLK_MNGR_NOCDIV_L4SYSFREECLK_MASK            0x0000000CU
#define CLK_MNGR_NOCDIV_L4SYSFREECLK_POS             2U

/*
 * Convenience GET macros for NOCDIV sub-fields
 * (mirrors ATF GET_CLKMGR_MAINPLL_NOCDIV_* family)
 */
#define GET_CLK_MNGR_NOCDIV_L4MP(x)    (((x) & CLK_MNGR_NOCDIV_L4MPCLK_MASK)    >> CLK_MNGR_NOCDIV_L4MPCLK_POS)
#define GET_CLK_MNGR_NOCDIV_L4SP(x)    (((x) & CLK_MNGR_NOCDIV_L4SPCLK_MASK)    >> CLK_MNGR_NOCDIV_L4SPCLK_POS)
#define GET_CLK_MNGR_NOCDIV_L4SYSFREE(x) (((x) & CLK_MNGR_NOCDIV_L4SYSFREECLK_MASK) >> CLK_MNGR_NOCDIV_L4SYSFREECLK_POS)
#define GET_CLK_MNGR_NOCDIV_SPHY(x)    (((x) & CLK_MNGR_NOCDIV_SOFTPHYDIV_MASK) >> CLK_MNGR_NOCDIV_SOFTPHYDIV_POS)

/* =========================================================================
 * Bit fields  pllglob register  (shared layout, Main and Peripheral PLL)
 * ========================================================================= */
#define CLK_MNGR_PLLGLOB_CLR_LOSTLOCK_BYPASS_MASK    0x20000000U
#define CLK_MNGR_PLLGLOB_CLR_LOSTLOCK_BYPASS_POS     29U
#define CLK_MNGR_PLLGLOB_LOSTLOCK_BYPASS_EN_MASK     0x10000000U
#define CLK_MNGR_PLLGLOB_LOSTLOCK_BYPASS_EN_POS      28U
#define CLK_MNGR_PLLGLOB_MODCLKDIV_MASK              0x0F000000U
#define CLK_MNGR_PLLGLOB_MODCLKDIV_POS               24U
#define CLK_MNGR_PLLGLOB_FASTREFCLK_MASK             0x00200000U
#define CLK_MNGR_PLLGLOB_FASTREFCLK_POS              21U
#define CLK_MNGR_PLLGLOB_DISCTRL_MASK                0x00100000U
#define CLK_MNGR_PLLGLOB_DISCTRL_POS                 20U
#define CLK_MNGR_PLLGLOB_CLKSYNC_MASK                0x00080000U
#define CLK_MNGR_PLLGLOB_CLKSYNC_POS                 19U
#define CLK_MNGR_PLLGLOB_PWRGATECTRL_MASK            0x00040000U
#define CLK_MNGR_PLLGLOB_PWRGATECTRL_POS             18U
#define CLK_MNGR_PLLGLOB_PSRC_MASK                   0x00030000U
#define CLK_MNGR_PLLGLOB_PSRC_POS                    16U
#define CLK_MNGR_PLLGLOB_DREFCLKDIV_MASK             0x00003000U
#define CLK_MNGR_PLLGLOB_DREFCLKDIV_POS              12U
#define CLK_MNGR_PLLGLOB_AREFCLKDIV_MASK             0x00000F00U
#define CLK_MNGR_PLLGLOB_AREFCLKDIV_POS              8U
#define CLK_MNGR_PLLGLOB_RST_N_MASK                  0x00000002U
#define CLK_MNGR_PLLGLOB_RST_N_POS                   1U
#define CLK_MNGR_PLLGLOB_PD_N_MASK                   0x00000001U
#define CLK_MNGR_PLLGLOB_PD_N_POS                    0U

/* VCO reference clock source values (PLLGLOB.PSRC field) */
#define PSRC_EOSC1_CLK                               0U  /**< External osc (EOSC1) */
#define PSRC_CBINTOSC_CLK                            1U  /**< Internal callback osc */
#define PSRC_F2S_FREE_CLK                            2U  /**< FPGA-to-HPS free clock */

/* Peripheral clock output source values (CTR.SRC field, 3-bit) */
#define CLKSRC_MAIN                                  0U  /**< Main PLL */
#define CLKSRC_PER                                   1U  /**< Peripheral PLL */
#define CLKSRC_OSC1                                  2U  /**< EOSC1 */
#define CLKSRC_INTOSC                                3U  /**< Internal osc */
#define CLKSRC_FPGA                                  4U  /**< FPGA clock */

#define CLK_MNGR_CLKSRC_MASK                         0x00070000U
#define CLK_MNGR_CLKSRC_POS                          16U
#define GET_CLK_MNGR_CLKSRC(x)  (((x) & CLK_MNGR_CLKSRC_MASK) >> CLK_MNGR_CLKSRC_POS)

/* =========================================================================
 * Bit fields  fdbck register
 * ========================================================================= */
#define CLK_MNGR_FDBCK_FDIV_MASK                     0x00FFFFFFU
#define CLK_MNGR_FDBCK_FDIV_POS                      0U

/* =========================================================================
 * Bit fields  mem register (PLL memory bus)
 * ========================================================================= */
#define CLK_MNGR_MEM_ERR_MASK                        0x04000000U
#define CLK_MNGR_MEM_ERR_POS                         26U
#define CLK_MNGR_MEM_WR_MASK                         0x02000000U
#define CLK_MNGR_MEM_WR_POS                          25U
#define CLK_MNGR_MEM_REQ_MASK                        0x01000000U
#define CLK_MNGR_MEM_REQ_POS                         24U
#define CLK_MNGR_MEM_WDAT_MASK                       0x00FF0000U
#define CLK_MNGR_MEM_WDAT_POS                        16U
#define CLK_MNGR_MEM_ADDR_MASK                       0x0000FFFFU
#define CLK_MNGR_MEM_ADDR_POS                        0U

/* Start address for PLL mem-bus accesses (from ATF: CLKMGR_MEM_ADDR_START) */
#define CLK_MNGR_MEM_ADDR_START                      0x00004000U

/* =========================================================================
 * Bit fields  memstat register
 * ========================================================================= */
#define CLK_MNGR_MEMSTAT_RDATA_MASK                  0x000000FFU
#define CLK_MNGR_MEMSTAT_RDATA_POS                   0U

/* =========================================================================
 * Bit fields  vcocalib register
 * ========================================================================= */
#define CLK_MNGR_VCOCALIB_CLR_MASK                   0x08000000U
#define CLK_MNGR_VCOCALIB_CLR_POS                    27U
#define CLK_MNGR_VCOCALIB_BANKSEL_MASK               0x06000000U
#define CLK_MNGR_VCOCALIB_BANKSEL_POS                25U
#define CLK_MNGR_VCOCALIB_MSCNT_MASK                 0x00FF0000U
#define CLK_MNGR_VCOCALIB_MSCNT_POS                  16U
#define CLK_MNGR_VCOCALIB_HSCNT_MASK                 0x000003FFU
#define CLK_MNGR_VCOCALIB_HSCNT_POS                  0U

/* VCO calibration constant values (from ATF) */
#define CLK_MNGR_VCOCALIB_MSCNT_CONST                100U
#define CLK_MNGR_VCOCALIB_HSCNT_CONST                4U

/* =========================================================================
 * Bit fields  pllc0 / pllc1 / pllc2 / pllc3 registers
 * ========================================================================= */
#define CLK_MNGR_PLLCX_STAT_MASK                     0x20000000U
#define CLK_MNGR_PLLCX_STAT_POS                      29U
#define CLK_MNGR_PLLCX_MUTE_MASK                     0x10000000U
#define CLK_MNGR_PLLCX_MUTE_POS                      28U
#define CLK_MNGR_PLLCX_EN_MASK                       0x08000000U
#define CLK_MNGR_PLLCX_EN_POS                        27U
#define CLK_MNGR_PLLCX_BYPAS_MASK                    0x04000000U
#define CLK_MNGR_PLLCX_BYPAS_POS                     26U
#define CLK_MNGR_PLLCX_DIV_MASK                      0x000007FFU
#define CLK_MNGR_PLLCX_DIV_POS                       0U

/* Individual aliases (for code that references a specific PLLCx) */
#define CLK_MNGR_PLLC0_STAT_MASK                     CLK_MNGR_PLLCX_STAT_MASK
#define CLK_MNGR_PLLC0_STAT_POS                      CLK_MNGR_PLLCX_STAT_POS
#define CLK_MNGR_PLLC0_MUTE_MASK                     CLK_MNGR_PLLCX_MUTE_MASK
#define CLK_MNGR_PLLC0_MUTE_POS                      CLK_MNGR_PLLCX_MUTE_POS
#define CLK_MNGR_PLLC0_EN_MASK                       CLK_MNGR_PLLCX_EN_MASK
#define CLK_MNGR_PLLC0_EN_POS                        CLK_MNGR_PLLCX_EN_POS
#define CLK_MNGR_PLLC0_BYPAS_MASK                    CLK_MNGR_PLLCX_BYPAS_MASK
#define CLK_MNGR_PLLC0_BYPAS_POS                     CLK_MNGR_PLLCX_BYPAS_POS
#define CLK_MNGR_PLLC0_DIV_MASK                      CLK_MNGR_PLLCX_DIV_MASK
#define CLK_MNGR_PLLC0_DIV_POS                       CLK_MNGR_PLLCX_DIV_POS

#define CLK_MNGR_PLLC1_STAT_MASK                     CLK_MNGR_PLLCX_STAT_MASK
#define CLK_MNGR_PLLC1_STAT_POS                      CLK_MNGR_PLLCX_STAT_POS
#define CLK_MNGR_PLLC1_MUTE_MASK                     CLK_MNGR_PLLCX_MUTE_MASK
#define CLK_MNGR_PLLC1_MUTE_POS                      CLK_MNGR_PLLCX_MUTE_POS
#define CLK_MNGR_PLLC1_EN_MASK                       CLK_MNGR_PLLCX_EN_MASK
#define CLK_MNGR_PLLC1_EN_POS                        CLK_MNGR_PLLCX_EN_POS
#define CLK_MNGR_PLLC1_BYPAS_MASK                    CLK_MNGR_PLLCX_BYPAS_MASK
#define CLK_MNGR_PLLC1_BYPAS_POS                     CLK_MNGR_PLLCX_BYPAS_POS
#define CLK_MNGR_PLLC1_DIV_MASK                      CLK_MNGR_PLLCX_DIV_MASK
#define CLK_MNGR_PLLC1_DIV_POS                       CLK_MNGR_PLLCX_DIV_POS

#define CLK_MNGR_PLLC2_STAT_MASK                     CLK_MNGR_PLLCX_STAT_MASK
#define CLK_MNGR_PLLC2_STAT_POS                      CLK_MNGR_PLLCX_STAT_POS
#define CLK_MNGR_PLLC2_MUTE_MASK                     CLK_MNGR_PLLCX_MUTE_MASK
#define CLK_MNGR_PLLC2_MUTE_POS                      CLK_MNGR_PLLCX_MUTE_POS
#define CLK_MNGR_PLLC2_EN_MASK                       CLK_MNGR_PLLCX_EN_MASK
#define CLK_MNGR_PLLC2_EN_POS                        CLK_MNGR_PLLCX_EN_POS
#define CLK_MNGR_PLLC2_BYPAS_MASK                    CLK_MNGR_PLLCX_BYPAS_MASK
#define CLK_MNGR_PLLC2_BYPAS_POS                     CLK_MNGR_PLLCX_BYPAS_POS
#define CLK_MNGR_PLLC2_DIV_MASK                      CLK_MNGR_PLLCX_DIV_MASK
#define CLK_MNGR_PLLC2_DIV_POS                       CLK_MNGR_PLLCX_DIV_POS

#define CLK_MNGR_PLLC3_STAT_MASK                     CLK_MNGR_PLLCX_STAT_MASK
#define CLK_MNGR_PLLC3_STAT_POS                      CLK_MNGR_PLLCX_STAT_POS
#define CLK_MNGR_PLLC3_MUTE_MASK                     CLK_MNGR_PLLCX_MUTE_MASK
#define CLK_MNGR_PLLC3_MUTE_POS                      CLK_MNGR_PLLCX_MUTE_POS
#define CLK_MNGR_PLLC3_EN_MASK                       CLK_MNGR_PLLCX_EN_MASK
#define CLK_MNGR_PLLC3_EN_POS                        CLK_MNGR_PLLCX_EN_POS
#define CLK_MNGR_PLLC3_BYPAS_MASK                    CLK_MNGR_PLLCX_BYPAS_MASK
#define CLK_MNGR_PLLC3_BYPAS_POS                     CLK_MNGR_PLLCX_BYPAS_POS
#define CLK_MNGR_PLLC3_DIV_MASK                      CLK_MNGR_PLLCX_DIV_MASK
#define CLK_MNGR_PLLC3_DIV_POS                       CLK_MNGR_PLLCX_DIV_POS

/* =========================================================================
 * Bit fields  pllm register
 * ========================================================================= */
#define CLK_MNGR_PLLM_MDIV_MASK                      0x000003FFU
#define CLK_MNGR_PLLM_MDIV_POS                       0U

/* =========================================================================
 * Bit fields  fhop register
 * ========================================================================= */
#define CLK_MNGR_FHOP_ACK_MASK                       0x00010000U
#define CLK_MNGR_FHOP_ACK_POS                        16U
#define CLK_MNGR_FHOP_REQ_MASK                       0x00000100U
#define CLK_MNGR_FHOP_REQ_POS                        8U
#define CLK_MNGR_FHOP_DIR_MASK                       0x00000003U
#define CLK_MNGR_FHOP_DIR_POS                        0U

/* =========================================================================
 * Bit fields  ssc register
 * ========================================================================= */
#define CLK_MNGR_SSC_STAT_MASK                       0x00000100U
#define CLK_MNGR_SSC_STAT_POS                        8U
#define CLK_MNGR_SSC_EN_MASK                         0x00000001U
#define CLK_MNGR_SSC_EN_POS                          0U

/* =========================================================================
 * Bit fields  lostlock register
 * ========================================================================= */
#define CLK_MNGR_LOSTLOCK_BYPASS_CLEARED_MASK        0x00000001U
#define CLK_MNGR_LOSTLOCK_BYPASS_CLEARED_POS         0U

/* =========================================================================
 * Bit fields  PERPLL en / ens / enr
 * ========================================================================= */
#define CLK_MNGR_EN_I2C_EMAC2_CLKEN_MASK             0x08000000U
#define CLK_MNGR_EN_I2C_EMAC2_CLKEN_POS              27U
#define CLK_MNGR_EN_SOFTPHYCLKEN_MASK                0x04000000U
#define CLK_MNGR_EN_SOFTPHYCLKEN_POS                 26U
#define CLK_MNGR_EN_USB31CLKEN_MASK                  0x02000000U
#define CLK_MNGR_EN_USB31CLKEN_POS                   25U
#define CLK_MNGR_EN_SPTIMER_1_CLKEN_MASK             0x01000000U
#define CLK_MNGR_EN_SPTIMER_1_CLKEN_POS              24U
#define CLK_MNGR_EN_SPTIMER_0_CLKEN_MASK             0x00800000U
#define CLK_MNGR_EN_SPTIMER_0_CLKEN_POS              23U
#define CLK_MNGR_EN_I2C_EMAC1_CLKEN_MASK             0x00400000U
#define CLK_MNGR_EN_I2C_EMAC1_CLKEN_POS              22U
#define CLK_MNGR_EN_UART_1_CLKEN_MASK                0x00200000U
#define CLK_MNGR_EN_UART_1_CLKEN_POS                 21U
#define CLK_MNGR_EN_UART_0_CLKEN_MASK                0x00100000U
#define CLK_MNGR_EN_UART_0_CLKEN_POS                 20U
#define CLK_MNGR_EN_I3C_1_CLKEN_MASK                 0x00080000U
#define CLK_MNGR_EN_I3C_1_CLKEN_POS                  19U
#define CLK_MNGR_EN_I3C_0_CLKEN_MASK                 0x00040000U
#define CLK_MNGR_EN_I3C_0_CLKEN_POS                  18U
#define CLK_MNGR_EN_I2C_EMAC0_CLKEN_MASK             0x00020000U
#define CLK_MNGR_EN_I2C_EMAC0_CLKEN_POS              17U
#define CLK_MNGR_EN_I2C_1_CLKEN_MASK                 0x00010000U
#define CLK_MNGR_EN_I2C_1_CLKEN_POS                  16U
#define CLK_MNGR_EN_I2C_0_CLKEN_MASK                 0x00008000U
#define CLK_MNGR_EN_I2C_0_CLKEN_POS                  15U
#define CLK_MNGR_EN_DMACLKEN_MASK                    0x00004000U
#define CLK_MNGR_EN_DMACLKEN_POS                     14U
#define CLK_MNGR_EN_SPIS_1_CLKEN_MASK                0x00002000U
#define CLK_MNGR_EN_SPIS_1_CLKEN_POS                 13U
#define CLK_MNGR_EN_SPIS_0_CLKEN_MASK                0x00001000U
#define CLK_MNGR_EN_SPIS_0_CLKEN_POS                 12U
#define CLK_MNGR_EN_SPIM_1_CLKEN_MASK                0x00000800U
#define CLK_MNGR_EN_SPIM_1_CLKEN_POS                 11U
#define CLK_MNGR_EN_NANDCLKEN_MASK                   0x00000400U
#define CLK_MNGR_EN_NANDCLKEN_POS                    10U
#define CLK_MNGR_EN_SPIM_0_CLKEN_MASK                0x00000200U
#define CLK_MNGR_EN_SPIM_0_CLKEN_POS                 9U
#define CLK_MNGR_EN_USB2CLKEN_MASK                   0x00000100U
#define CLK_MNGR_EN_USB2CLKEN_POS                    8U
#define CLK_MNGR_EN_PSICLKEN_MASK                    0x00000080U
#define CLK_MNGR_EN_PSICLKEN_POS                     7U
#define CLK_MNGR_EN_S2FUSER1CLKEN_MASK               0x00000040U
#define CLK_MNGR_EN_S2FUSER1CLKEN_POS                6U
#define CLK_MNGR_EN_SDMMCCLKEN_MASK                  0x00000020U
#define CLK_MNGR_EN_SDMMCCLKEN_POS                   5U
#define CLK_MNGR_EN_GPIODBEN_MASK                    0x00000010U
#define CLK_MNGR_EN_GPIODBEN_POS                     4U
#define CLK_MNGR_EN_EMACPTPEN_MASK                   0x00000008U
#define CLK_MNGR_EN_EMACPTPEN_POS                    3U
#define CLK_MNGR_EN_EMAC2EN_MASK                     0x00000004U
#define CLK_MNGR_EN_EMAC2EN_POS                      2U
#define CLK_MNGR_EN_EMAC1EN_MASK                     0x00000002U
#define CLK_MNGR_EN_EMAC1EN_POS                      1U
#define CLK_MNGR_EN_EMAC0EN_MASK                     0x00000001U
#define CLK_MNGR_EN_EMAC0EN_POS                      0U

/* ENS mirrors */
#define CLK_MNGR_ENS_I2C_EMAC2_CLKEN_MASK            CLK_MNGR_EN_I2C_EMAC2_CLKEN_MASK
#define CLK_MNGR_ENS_I2C_EMAC2_CLKEN_POS             CLK_MNGR_EN_I2C_EMAC2_CLKEN_POS
#define CLK_MNGR_ENS_SOFTPHYCLKEN_MASK               CLK_MNGR_EN_SOFTPHYCLKEN_MASK
#define CLK_MNGR_ENS_SOFTPHYCLKEN_POS                CLK_MNGR_EN_SOFTPHYCLKEN_POS
#define CLK_MNGR_ENS_USB31CLKEN_MASK                 CLK_MNGR_EN_USB31CLKEN_MASK
#define CLK_MNGR_ENS_USB31CLKEN_POS                  CLK_MNGR_EN_USB31CLKEN_POS
#define CLK_MNGR_ENS_SPTIMER_1_CLKEN_MASK            CLK_MNGR_EN_SPTIMER_1_CLKEN_MASK
#define CLK_MNGR_ENS_SPTIMER_1_CLKEN_POS             CLK_MNGR_EN_SPTIMER_1_CLKEN_POS
#define CLK_MNGR_ENS_SPTIMER_0_CLKEN_MASK            CLK_MNGR_EN_SPTIMER_0_CLKEN_MASK
#define CLK_MNGR_ENS_SPTIMER_0_CLKEN_POS             CLK_MNGR_EN_SPTIMER_0_CLKEN_POS
#define CLK_MNGR_ENS_UART_1_CLKEN_MASK               CLK_MNGR_EN_UART_1_CLKEN_MASK
#define CLK_MNGR_ENS_UART_1_CLKEN_POS                CLK_MNGR_EN_UART_1_CLKEN_POS
#define CLK_MNGR_ENS_UART_0_CLKEN_MASK               CLK_MNGR_EN_UART_0_CLKEN_MASK
#define CLK_MNGR_ENS_UART_0_CLKEN_POS                CLK_MNGR_EN_UART_0_CLKEN_POS
#define CLK_MNGR_ENS_I2C_1_CLKEN_MASK                CLK_MNGR_EN_I2C_1_CLKEN_MASK
#define CLK_MNGR_ENS_I2C_1_CLKEN_POS                 CLK_MNGR_EN_I2C_1_CLKEN_POS
#define CLK_MNGR_ENS_I2C_0_CLKEN_MASK                CLK_MNGR_EN_I2C_0_CLKEN_MASK
#define CLK_MNGR_ENS_I2C_0_CLKEN_POS                 CLK_MNGR_EN_I2C_0_CLKEN_POS
#define CLK_MNGR_ENS_SDMMCCLKEN_MASK                 CLK_MNGR_EN_SDMMCCLKEN_MASK
#define CLK_MNGR_ENS_SDMMCCLKEN_POS                  CLK_MNGR_EN_SDMMCCLKEN_POS
#define CLK_MNGR_ENS_EMAC0EN_MASK                    CLK_MNGR_EN_EMAC0EN_MASK
#define CLK_MNGR_ENS_EMAC0EN_POS                     CLK_MNGR_EN_EMAC0EN_POS
#define CLK_MNGR_ENS_EMAC1EN_MASK                    CLK_MNGR_EN_EMAC1EN_MASK
#define CLK_MNGR_ENS_EMAC1EN_POS                     CLK_MNGR_EN_EMAC1EN_POS
#define CLK_MNGR_ENS_EMAC2EN_MASK                    CLK_MNGR_EN_EMAC2EN_MASK
#define CLK_MNGR_ENS_EMAC2EN_POS                     CLK_MNGR_EN_EMAC2EN_POS

/* ENR mirrors */
#define CLK_MNGR_ENR_I2C_EMAC2_CLKEN_MASK            CLK_MNGR_EN_I2C_EMAC2_CLKEN_MASK
#define CLK_MNGR_ENR_I2C_EMAC2_CLKEN_POS             CLK_MNGR_EN_I2C_EMAC2_CLKEN_POS
#define CLK_MNGR_ENR_SOFTPHYCLKEN_MASK               CLK_MNGR_EN_SOFTPHYCLKEN_MASK
#define CLK_MNGR_ENR_SOFTPHYCLKEN_POS                CLK_MNGR_EN_SOFTPHYCLKEN_POS
#define CLK_MNGR_ENR_USB31CLKEN_MASK                 CLK_MNGR_EN_USB31CLKEN_MASK
#define CLK_MNGR_ENR_USB31CLKEN_POS                  CLK_MNGR_EN_USB31CLKEN_POS
#define CLK_MNGR_ENR_SPTIMER_1_CLKEN_MASK            CLK_MNGR_EN_SPTIMER_1_CLKEN_MASK
#define CLK_MNGR_ENR_SPTIMER_1_CLKEN_POS             CLK_MNGR_EN_SPTIMER_1_CLKEN_POS
#define CLK_MNGR_ENR_SPTIMER_0_CLKEN_MASK            CLK_MNGR_EN_SPTIMER_0_CLKEN_MASK
#define CLK_MNGR_ENR_SPTIMER_0_CLKEN_POS             CLK_MNGR_EN_SPTIMER_0_CLKEN_POS
#define CLK_MNGR_ENR_UART_1_CLKEN_MASK               CLK_MNGR_EN_UART_1_CLKEN_MASK
#define CLK_MNGR_ENR_UART_1_CLKEN_POS                CLK_MNGR_EN_UART_1_CLKEN_POS
#define CLK_MNGR_ENR_UART_0_CLKEN_MASK               CLK_MNGR_EN_UART_0_CLKEN_MASK
#define CLK_MNGR_ENR_UART_0_CLKEN_POS                CLK_MNGR_EN_UART_0_CLKEN_POS
#define CLK_MNGR_ENR_I2C_1_CLKEN_MASK                CLK_MNGR_EN_I2C_1_CLKEN_MASK
#define CLK_MNGR_ENR_I2C_1_CLKEN_POS                 CLK_MNGR_EN_I2C_1_CLKEN_POS
#define CLK_MNGR_ENR_I2C_0_CLKEN_MASK                CLK_MNGR_EN_I2C_0_CLKEN_MASK
#define CLK_MNGR_ENR_I2C_0_CLKEN_POS                 CLK_MNGR_EN_I2C_0_CLKEN_POS
#define CLK_MNGR_ENR_SDMMCCLKEN_MASK                 CLK_MNGR_EN_SDMMCCLKEN_MASK
#define CLK_MNGR_ENR_SDMMCCLKEN_POS                  CLK_MNGR_EN_SDMMCCLKEN_POS
#define CLK_MNGR_ENR_EMAC0EN_MASK                    CLK_MNGR_EN_EMAC0EN_MASK
#define CLK_MNGR_ENR_EMAC0EN_POS                     CLK_MNGR_EN_EMAC0EN_POS
#define CLK_MNGR_ENR_EMAC1EN_MASK                    CLK_MNGR_EN_EMAC1EN_MASK
#define CLK_MNGR_ENR_EMAC1EN_POS                     CLK_MNGR_EN_EMAC1EN_POS
#define CLK_MNGR_ENR_EMAC2EN_MASK                    CLK_MNGR_EN_EMAC2EN_MASK
#define CLK_MNGR_ENR_EMAC2EN_POS                     CLK_MNGR_EN_EMAC2EN_POS

/* =========================================================================
 * Bit fields  PERPLL bypass / bypasss / bypassr
 * ========================================================================= */
#define CLK_MNGR_BYPASS_USB31_MASK                   0x00000080U
#define CLK_MNGR_BYPASS_USB31_POS                    7U
#define CLK_MNGR_BYPASS_PSIREF_MASK                  0x00000040U
#define CLK_MNGR_BYPASS_PSIREF_POS                   6U
#define CLK_MNGR_BYPASS_S2FUSER1_MASK                0x00000020U
#define CLK_MNGR_BYPASS_S2FUSER1_POS                 5U
#define CLK_MNGR_BYPASS_GPIODB_MASK                  0x00000008U
#define CLK_MNGR_BYPASS_GPIODB_POS                   3U
#define CLK_MNGR_BYPASS_EMACPTP_MASK                 0x00000004U
#define CLK_MNGR_BYPASS_EMACPTP_POS                  2U
#define CLK_MNGR_BYPASS_EMACB_MASK                   0x00000002U
#define CLK_MNGR_BYPASS_EMACB_POS                    1U
#define CLK_MNGR_BYPASS_EMACA_MASK                   0x00000001U
#define CLK_MNGR_BYPASS_EMACA_POS                    0U

/* Bypass-all value for Peripheral PLL (from ATF: CLKMGR_PERPLL_BYPASS_ALL) */
#define CLK_MNGR_PERPLL_BYPASS_ALL                   0xEFU

#define CLK_MNGR_BYPASSS_USB31_MASK                  0x00000080U
#define CLK_MNGR_BYPASSS_USB31_POS                   7U
#define CLK_MNGR_BYPASSS_PSIREF_MASK                 0x00000040U
#define CLK_MNGR_BYPASSS_PSIREF_POS                  6U
#define CLK_MNGR_BYPASSS_S2FUSER1_MASK               0x00000020U
#define CLK_MNGR_BYPASSS_S2FUSER1_POS                5U
#define CLK_MNGR_BYPASSS_GPIODB_MASK                 0x00000008U
#define CLK_MNGR_BYPASSS_GPIODB_POS                  3U
#define CLK_MNGR_BYPASSS_EMACPTP_MASK                0x00000004U
#define CLK_MNGR_BYPASSS_EMACPTP_POS                 2U
#define CLK_MNGR_BYPASSS_EMACB_MASK                  0x00000002U
#define CLK_MNGR_BYPASSS_EMACB_POS                   1U
#define CLK_MNGR_BYPASSS_EMACA_MASK                  0x00000001U
#define CLK_MNGR_BYPASSS_EMACA_POS                   0U

#define CLK_MNGR_BYPASSR_USB31_MASK                  0x00000080U
#define CLK_MNGR_BYPASSR_USB31_POS                   7U
#define CLK_MNGR_BYPASSR_PSIREF_MASK                 0x00000040U
#define CLK_MNGR_BYPASSR_PSIREF_POS                  6U
#define CLK_MNGR_BYPASSR_S2FUSER1_MASK               0x00000020U
#define CLK_MNGR_BYPASSR_S2FUSER1_POS                5U
#define CLK_MNGR_BYPASSR_GPIODB_MASK                 0x00000008U
#define CLK_MNGR_BYPASSR_GPIODB_POS                  3U
#define CLK_MNGR_BYPASSR_EMACPTP_MASK                0x00000004U
#define CLK_MNGR_BYPASSR_EMACPTP_POS                 2U
#define CLK_MNGR_BYPASSR_EMACB_MASK                  0x00000002U
#define CLK_MNGR_BYPASSR_EMACB_POS                   1U
#define CLK_MNGR_BYPASSR_EMACA_MASK                  0x00000001U
#define CLK_MNGR_BYPASSR_EMACA_POS                   0U

/* =========================================================================
 * Bit fields  emacctl register (Peripheral PLL)
 * ========================================================================= */
#define CLK_MNGR_EMACCTL_EMAC2SEL_MASK               0x10000000U
#define CLK_MNGR_EMACCTL_EMAC2SEL_POS                28U
#define CLK_MNGR_EMACCTL_EMAC1SEL_MASK               0x08000000U
#define CLK_MNGR_EMACCTL_EMAC1SEL_POS                27U
#define CLK_MNGR_EMACCTL_EMAC0SEL_MASK               0x04000000U
#define CLK_MNGR_EMACCTL_EMAC0SEL_POS                26U

/* Convenience accessor: which EMAC A clock source is active */
#define GET_CLK_MNGR_EMACCTL_EMAC0SEL(x) \
    (((x) & CLK_MNGR_EMACCTL_EMAC0SEL_MASK) >> CLK_MNGR_EMACCTL_EMAC0SEL_POS)

/* =========================================================================
 * Bit fields  gpiodiv register (Peripheral PLL)
 * ========================================================================= */
#define CLK_MNGR_GPIODIV_GPIODBCLK_MASK              0x0000FFFFU
#define CLK_MNGR_GPIODIV_GPIODBCLK_POS               0U

/* =========================================================================
 * Bit fields  jtag register
 * ========================================================================= */
#define CLK_MNGR_JTAG_RST_MASK                       0x00000100U
#define CLK_MNGR_JTAG_RST_POS                        8U
#define CLK_MNGR_JTAG_ID_MASK                        0x000000FFU
#define CLK_MNGR_JTAG_ID_POS                         0U

/* =========================================================================
 * Bit fields  counter registers (emacactr, emacbctr, emacptpctr, )
 * All share the same SRC[18:16] and CNT[10:0] layout.
 * ========================================================================= */
#define CLK_MNGR_CTR_SRC_MASK                        0x00070000U
#define CLK_MNGR_CTR_SRC_POS                         16U
#define CLK_MNGR_CTR_CNT_MASK                        0x000007FFU
#define CLK_MNGR_CTR_CNT_POS                         0U

/* Individual aliases kept for source-level compatibility */
#define CLK_MNGR_EMACACTR_SRC_MASK                   CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_EMACACTR_SRC_POS                    CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_EMACACTR_CNT_MASK                   CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_EMACACTR_CNT_POS                    CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_EMACBCTR_CNT_MASK                   CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_EMACBCTR_CNT_POS                    CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_EMACPTPCTR_SRC_MASK                 CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_EMACPTPCTR_SRC_POS                  CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_EMACPTPCTR_CNT_MASK                 CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_EMACPTPCTR_CNT_POS                  CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_GPIODBCTR_SRC_MASK                  CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_GPIODBCTR_SRC_POS                   CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_GPIODBCTR_CNT_MASK                  CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_GPIODBCTR_CNT_POS                   CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_S2FUSER0CTR_SRC_MASK                CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_S2FUSER0CTR_SRC_POS                 CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_S2FUSER0CTR_CNT_MASK                CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_S2FUSER0CTR_CNT_POS                 CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_S2FUSER1CTR_SRC_MASK                CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_S2FUSER1CTR_SRC_POS                 CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_S2FUSER1CTR_CNT_MASK                CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_S2FUSER1CTR_CNT_POS                 CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_PSIREFCTR_SRC_MASK                  CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_PSIREFCTR_SRC_POS                   CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_PSIREFCTR_CNT_MASK                  CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_PSIREFCTR_CNT_POS                   CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_USB31CTR_SRC_MASK                   CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_USB31CTR_SRC_POS                    CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_USB31CTR_CNT_MASK                   CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_USB31CTR_CNT_POS                    CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_DSUCTR_SRC_MASK                     CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_DSUCTR_SRC_POS                      CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_DSUCTR_CNT_MASK                     CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_DSUCTR_CNT_POS                      CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_CORE01CTR_SRC_MASK                  CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_CORE01CTR_SRC_POS                   CLK_MNGR_CTR_SRC_POS
#define CLK_MNGR_CORE01CTR_CNT_MASK                  CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_CORE01CTR_CNT_POS                   CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_CORE23CTR_SRC_MASK                  CLK_MNGR_CTR_SRC_MASK
#define CLK_MNGR_CORE23CTR_SRC_POS                   CLK_MNGR_CTR_SRC_POS

#define CLK_MNGR_CORE2CTR_CNT_MASK                   CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_CORE2CTR_CNT_POS                    CLK_MNGR_CTR_CNT_POS

#define CLK_MNGR_CORE3CTR_CNT_MASK                   CLK_MNGR_CTR_CNT_MASK
#define CLK_MNGR_CORE3CTR_CNT_POS                    CLK_MNGR_CTR_CNT_POS

/* =========================================================================
 * Bit fields  extcntrst register
 * ========================================================================= */
#define CLK_MNGR_EXTCNTRST_CORE3CNTRST_MASK          0x00002000U
#define CLK_MNGR_EXTCNTRST_CORE3CNTRST_POS           13U
#define CLK_MNGR_EXTCNTRST_CORE2CNTRST_MASK          0x00001000U
#define CLK_MNGR_EXTCNTRST_CORE2CNTRST_POS           12U
#define CLK_MNGR_EXTCNTRST_CORE01CNTRST_MASK         0x00000800U
#define CLK_MNGR_EXTCNTRST_CORE01CNTRST_POS          11U
#define CLK_MNGR_EXTCNTRST_DSUCNTRST_MASK            0x00000400U
#define CLK_MNGR_EXTCNTRST_DSUCNTRST_POS             10U
#define CLK_MNGR_EXTCNTRST_USB31REFCNTRST_MASK       0x00000100U
#define CLK_MNGR_EXTCNTRST_USB31REFCNTRST_POS        8U
#define CLK_MNGR_EXTCNTRST_PSIREFCNTRST_MASK         0x00000080U
#define CLK_MNGR_EXTCNTRST_PSIREFCNTRST_POS          7U
#define CLK_MNGR_EXTCNTRST_S2FUSER1CNTRST_MASK       0x00000040U
#define CLK_MNGR_EXTCNTRST_S2FUSER1CNTRST_POS        6U
#define CLK_MNGR_EXTCNTRST_S2FUSER0CNTRST_MASK       0x00000020U
#define CLK_MNGR_EXTCNTRST_S2FUSER0CNTRST_POS        5U
#define CLK_MNGR_EXTCNTRST_GPIODBCNTRST_MASK         0x00000008U
#define CLK_MNGR_EXTCNTRST_GPIODBCNTRST_POS          3U
#define CLK_MNGR_EXTCNTRST_EMACPTPCNTRST_MASK        0x00000004U
#define CLK_MNGR_EXTCNTRST_EMACPTPCNTRST_POS         2U
#define CLK_MNGR_EXTCNTRST_EMACBCNTRST_MASK          0x00000002U
#define CLK_MNGR_EXTCNTRST_EMACBCNTRST_POS           1U
#define CLK_MNGR_EXTCNTRST_EMACACNTRST_MASK          0x00000001U
#define CLK_MNGR_EXTCNTRST_EMACACNTRST_POS           0U

/* Reset all external counters (from ATF: CLKMGR_ALTERA_EXTCNTRST_ALLCNTRST) */
#define CLK_MNGR_EXTCNTRST_ALLCNTRST                 (CLK_MNGR_EXTCNTRST_EMACACNTRST_MASK   | \
                                                       CLK_MNGR_EXTCNTRST_EMACBCNTRST_MASK   | \
                                                       CLK_MNGR_EXTCNTRST_EMACPTPCNTRST_MASK | \
                                                       CLK_MNGR_EXTCNTRST_GPIODBCNTRST_MASK  | \
                                                       CLK_MNGR_EXTCNTRST_S2FUSER0CNTRST_MASK| \
                                                       CLK_MNGR_EXTCNTRST_S2FUSER1CNTRST_MASK| \
                                                       CLK_MNGR_EXTCNTRST_PSIREFCNTRST_MASK  | \
                                                       CLK_MNGR_EXTCNTRST_USB31REFCNTRST_MASK| \
                                                       CLK_MNGR_EXTCNTRST_DSUCNTRST_MASK     | \
                                                       CLK_MNGR_EXTCNTRST_CORE01CNTRST_MASK  | \
                                                       CLK_MNGR_EXTCNTRST_CORE2CNTRST_MASK   | \
                                                       CLK_MNGR_EXTCNTRST_CORE3CNTRST_MASK)

/* =========================================================================
 * Bit fields  serial_con_pll_ctr register
 * ========================================================================= */
#define CLK_MNGR_SERIAL_CON_PLL_CTR_EN_MASK          0x00000001U
#define CLK_MNGR_SERIAL_CON_PLL_CTR_EN_POS           0U

/* =========================================================================
 * Agilex5-specific PLL membus configuration values
 * (from ATF agilex5_clock_manager.h)
 * ========================================================================= */
/* Sync mode configuration value for PLL membus */
#define CLK_MNGR_PLLCFG_SRC_SYNC_MODE               0x27U
/* Overshoot frequency lock configuration for PLL membus */
#define CLK_MNGR_PLLCFG_OVRSHOOT_FREQ_LOCK          0xB3U
/* Lock settle time configuration for PLL membus */
#define CLK_MNGR_PLLCFG_LOCK_SETTLE_TIME            0xE6U
/* Duty cycle configuration for clock slice 0 */
#define CLK_MNGR_PLLCFG_DUTYCYCLE_CLKSLICE0         0x03U
/* Duty cycle configuration for clock slice 1 */
#define CLK_MNGR_PLLCFG_DUTYCYCLE_CLKSLICE1         0x07U

/* Maximum retry count for PLL lock polling */
#define CLK_MNGR_MAX_RETRY_COUNT                     1000U

#endif /* SOCFPGA_CLK_MNGR_REG_PLAT_H */
