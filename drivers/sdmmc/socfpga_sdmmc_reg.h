/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sdmmc_reg.h
 *
 * SDMMC register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SDMMC_REG_H__
#define __SDMMC_REG_H__

#define SRS_BASE_ADDR    0x10808000U
#define HRS_BASE_ADDR    0x10808000U


/* HRS00 */
#define SDMMC_HRS00                             0x0000U
/* HRS01 */
#define SDMMC_HRS01                             0x0004U
/* HRS02 */
#define SDMMC_HRS02                             0x0008U
/* HRS03 */
#define SDMMC_HRS03                             0x000CU
/* HRS04 */
#define SDMMC_HRS04                             0x0010U
/* HRS05 */
#define SDMMC_HRS05                             0x0014U
/* HRS06 */
#define SDMMC_HRS06                             0x0018U
/* HRS07 */
#define SDMMC_HRS07                             0x001CU
/* HRS08 */
#define SDMMC_HRS08                             0x0020U
/* HRS09 */
#define SDMMC_HRS09                             0x0024U
/* HRS10 */
#define SDMMC_HRS10                             0x0028U
/* HRS11 */
#define SDMMC_HRS11                             0x002CU
/* HRS12 */
#define SDMMC_HRS12                             0x0030U
/* HRS13 */
#define SDMMC_HRS13                             0x0034U
/* HRS14 */
#define SDMMC_HRS14                             0x0038U
/* HRS16 */
#define SDMMC_HRS16                             0x0040U
/* HRS29 */
#define SDMMC_HRS29                             0x0074U
/* HRS30 */
#define SDMMC_HRS30                             0x0078U
/* HRS31 */
#define SDMMC_HRS31                             0x007CU
/* HRS32 */
#define SDMMC_HRS32                             0x0080U
/* HRS33 */
#define SDMMC_HRS33                             0x0084U
/* HRS34 */
#define SDMMC_HRS34                             0x0088U
/* HRS36 */
#define SDMMC_HRS36                             0x0090U
/* HRS40 */
#define SDMMC_HRS40                             0x00A0U
/* HRS41 */
#define SDMMC_HRS41                             0x00A4U
/* HRS42 */
#define SDMMC_HRS42                             0x00A8U
/* HRS43 */
#define SDMMC_HRS43                             0x00ACU
/* SRS00 */
#define SDMMC_SRS00                             0x0200U
/* SRS01 */
#define SDMMC_SRS01                             0x0204U
/* SRS02 */
#define SDMMC_SRS02                             0x0208U
/* SRS03 */
#define SDMMC_SRS03                             0x020CU
/* SRS04 */
#define SDMMC_SRS04                             0x0210U
/* SRS05 */
#define SDMMC_SRS05                             0x0214U
/* SRS06 */
#define SDMMC_SRS06                             0x0218U
/* SRS07 */
#define SDMMC_SRS07                             0x021CU
/* SRS08 */
#define SDMMC_SRS08                             0x0220U
/* SRS09 */
#define SDMMC_SRS09                             0x0224U
/* SRS10 */
#define SDMMC_SRS10                             0x0228U
/* SRS11 */
#define SDMMC_SRS11                             0x022CU
/* SRS12 */
#define SDMMC_SRS12                             0x0230U
/* SRS13 */
#define SDMMC_SRS13                             0x0234U
/* SRS14 */
#define SDMMC_SRS14                             0x0238U
/* SRS15 */
#define SDMMC_SRS15                             0x023CU
/* SRS16 */
#define SDMMC_SRS16                             0x0240U
/* SRS17 */
#define SDMMC_SRS17                             0x0244U
/* SRS18 */
#define SDMMC_SRS18                             0x0248U
/* SRS19 */
#define SDMMC_SRS19                             0x024CU
/* SRS20 */
#define SDMMC_SRS20                             0x0250U
/* SRS21 */
#define SDMMC_SRS21                             0x0254U
/* SRS22 */
#define SDMMC_SRS22                             0x0258U
/* SRS23 */
#define SDMMC_SRS23                             0x025CU
/* SRS24 */
#define SDMMC_SRS24                             0x0260U
/* SRS25 */
#define SDMMC_SRS25                             0x0264U
/* SRS26 */
#define SDMMC_SRS26                             0x0268U
/* SRS27 */
#define SDMMC_SRS27                             0x026CU
/* SRS30 */
#define SDMMC_SRS30                             0x0278U
/* SRS31 */
#define SDMMC_SRS31                             0x027CU
/* CRS63 */
#define SDMMC_CRS63                             0x02FCU
/* CQRS00 */
#define SDMMC_CQRS00                            0x0400U
/* CQRS01 */
#define SDMMC_CQRS01                            0x0404U
/* CQRS02 */
#define SDMMC_CQRS02                            0x0408U
/* CQRS03 */
#define SDMMC_CQRS03                            0x040CU
/* CQRS04 */
#define SDMMC_CQRS04                            0x0410U
/* CQRS05 */
#define SDMMC_CQRS05                            0x0414U
/* CQRS06 */
#define SDMMC_CQRS06                            0x0418U
/* CQRS07 */
#define SDMMC_CQRS07                            0x041CU
/* CQRS08 */
#define SDMMC_CQRS08                            0x0420U
/* CQRS09 */
#define SDMMC_CQRS09                            0x0424U
/* CQRS10 */
#define SDMMC_CQRS10                            0x0428U
/* CQRS11 */
#define SDMMC_CQRS11                            0x042CU
/* CQRS12 */
#define SDMMC_CQRS12                            0x0430U
/* CQRS13 */
#define SDMMC_CQRS13                            0x0434U
/* CQRS14 */
#define SDMMC_CQRS14                            0x0438U
/* CQRS16 */
#define SDMMC_CQRS16                            0x0440U
/* CQRS17 */
#define SDMMC_CQRS17                            0x0444U
/* CQRS18 */
#define SDMMC_CQRS18                            0x0448U
/* CQRS20 */
#define SDMMC_CQRS20                            0x0450U
/* CQRS21 */
#define SDMMC_CQRS21                            0x0454U
/* CQRS22 */
#define SDMMC_CQRS22                            0x0458U
/* CQRS23 */
#define SDMMC_CQRS23                            0x045CU

/* Bit fields of HRS00 register */
#define SDMMC_HRS00_SAV_MASK                    0x00FF0000U
#define SDMMC_HRS00_SAV_POS                     16U
#define SDMMC_HRS00_SWR_MASK                    0x00000001U
#define SDMMC_HRS00_SWR_POS                     0U

/* Bit fields of HRS01 register */
#define SDMMC_HRS01_DP_MASK                     0x00FFFFFFU
#define SDMMC_HRS01_DP_POS                      0U

/* Bit fields of HRS02 register */
#define SDMMC_HRS02_OTN_MASK                    0x00030000U
#define SDMMC_HRS02_OTN_POS                     16U
#define SDMMC_HRS02_PBL_MASK                    0x0000000FU
#define SDMMC_HRS02_PBL_POS                     0U

/* Bit fields of HRS03 register */
#define SDMMC_HRS03_AER_IEBS_MASK               0x00080000U
#define SDMMC_HRS03_AER_IEBS_POS                19U
#define SDMMC_HRS03_AER_IEBD_MASK               0x00040000U
#define SDMMC_HRS03_AER_IEBD_POS                18U
#define SDMMC_HRS03_AER_IERS_MASK               0x00020000U
#define SDMMC_HRS03_AER_IERS_POS                17U
#define SDMMC_HRS03_AER_IERD_MASK               0x00010000U
#define SDMMC_HRS03_AER_IERD_POS                16U
#define SDMMC_HRS03_AER_SENBS_MASK              0x00000800U
#define SDMMC_HRS03_AER_SENBS_POS               11U
#define SDMMC_HRS03_AER_SENBD_MASK              0x00000400U
#define SDMMC_HRS03_AER_SENBD_POS               10U
#define SDMMC_HRS03_AER_SENRS_MASK              0x00000200U
#define SDMMC_HRS03_AER_SENRS_POS               9U
#define SDMMC_HRS03_AER_SENRD_MASK              0x00000100U
#define SDMMC_HRS03_AER_SENRD_POS               8U
#define SDMMC_HRS03_AER_BS_MASK                 0x00000008U
#define SDMMC_HRS03_AER_BS_POS                  3U
#define SDMMC_HRS03_AER_BD_MASK                 0x00000004U
#define SDMMC_HRS03_AER_BD_POS                  2U
#define SDMMC_HRS03_AER_RS_MASK                 0x00000002U
#define SDMMC_HRS03_AER_RS_POS                  1U
#define SDMMC_HRS03_AER_RD_MASK                 0x00000001U
#define SDMMC_HRS03_AER_RD_POS                  0U

/* Bit fields of HRS04 register */
#define SDMMC_HRS04_PHYREGADDR_MASK             0x0000FFFFU
#define SDMMC_HRS04_PHYREGADDR_POS              0U

/* Bit fields of HRS05 register */
#define SDMMC_HRS05_PHYREGDATA_MASK             0xFFFFFFFFU
#define SDMMC_HRS05_PHYREGDATA_POS              0U

/* Bit fields of HRS06 register */
#define SDMMC_HRS06_EMM_MASK                    0x00000007U
#define SDMMC_HRS06_EMM_POS                     0U

/* Bit fields of HRS07 register */
#define SDMMC_HRS07_RW_COMPENSATE_MASK          0x001F0000U
#define SDMMC_HRS07_RW_COMPENSATE_POS           16U
#define SDMMC_HRS07_IDELAY_VAL_MASK             0x0000001FU
#define SDMMC_HRS07_IDELAY_VAL_POS              0U

/* Bit fields of HRS08 register */
#define SDMMC_HRS08_PHY_DLL_UPDACK_MASK         0x00000002U
#define SDMMC_HRS08_PHY_DLL_UPDACK_POS          1U
#define SDMMC_HRS08_PHY_DLL_UPDREQ_MASK         0x00000001U
#define SDMMC_HRS08_PHY_DLL_UPDREQ_POS          0U

/* Bit fields of HRS09 register */
#define SDMMC_HRS09_LVSI_CNT_MASK               0xF0000000U
#define SDMMC_HRS09_LVSI_CNT_POS                28U
#define SDMMC_HRS09_LVSI_TCKSEL_MASK            0x0FC00000U
#define SDMMC_HRS09_LVSI_TCKSEL_POS             22U
#define SDMMC_HRS09_RDDATA_EN_MASK              0x00010000U
#define SDMMC_HRS09_RDDATA_EN_POS               16U
#define SDMMC_HRS09_RDCMD_EN_MASK               0x00008000U
#define SDMMC_HRS09_RDCMD_EN_POS                15U
#define SDMMC_HRS09_EXTENDED_WR_MODE_MASK       0x00000008U
#define SDMMC_HRS09_EXTENDED_WR_MODE_POS        3U
#define SDMMC_HRS09_EXTENDED_RD_MODE_MASK       0x00000004U
#define SDMMC_HRS09_EXTENDED_RD_MODE_POS        2U
#define SDMMC_HRS09_PHY_INIT_COMPLETE_MASK      0x00000002U
#define SDMMC_HRS09_PHY_INIT_COMPLETE_POS       1U
#define SDMMC_HRS09_PHY_SW_RESET_MASK           0x00000001U
#define SDMMC_HRS09_PHY_SW_RESET_POS            0U

/* Bit fields of HRS10 register */
#define SDMMC_HRS10_RDDATA_SWAP_MASK            0x00400000U
#define SDMMC_HRS10_RDDATA_SWAP_POS             22U
#define SDMMC_HRS10_HCSDCLKADJ_MASK             0x000F0000U
#define SDMMC_HRS10_HCSDCLKADJ_POS              16U

/* Bit fields of HRS11 register */
#define SDMMC_HRS11_EMMC_RST_MASK               0x00000001U
#define SDMMC_HRS11_EMMC_RST_POS                0U

/* Bit fields of HRS12 register */
#define SDMMC_HRS12_PHYDATOF_MASK               0x00000008U
#define SDMMC_HRS12_PHYDATOF_POS                3U
#define SDMMC_HRS12_PHYDATUR_MASK               0x00000004U
#define SDMMC_HRS12_PHYDATUR_POS                2U
#define SDMMC_HRS12_PHYCMDOF_MASK               0x00000002U
#define SDMMC_HRS12_PHYCMDOF_POS                1U
#define SDMMC_HRS12_PHYCMDUR_MASK               0x00000001U
#define SDMMC_HRS12_PHYCMDUR_POS                0U

/* Bit fields of HRS13 register */
#define SDMMC_HRS13_PHYDATOF_SE_MASK            0x00000008U
#define SDMMC_HRS13_PHYDATOF_SE_POS             3U
#define SDMMC_HRS13_PHYDATUR_SE_MASK            0x00000004U
#define SDMMC_HRS13_PHYDATUR_SE_POS             2U
#define SDMMC_HRS13_PHYCMDOF_SE_MASK            0x00000002U
#define SDMMC_HRS13_PHYCMDOF_SE_POS             1U
#define SDMMC_HRS13_PHYCMDUR_SE_MASK            0x00000001U
#define SDMMC_HRS13_PHYCMDUR_SE_POS             0U

/* Bit fields of HRS14 register */
#define SDMMC_HRS14_PHYDATOF_IE_MASK            0x00000008U
#define SDMMC_HRS14_PHYDATOF_IE_POS             3U
#define SDMMC_HRS14_PHYDATUR_IE_MASK            0x00000004U
#define SDMMC_HRS14_PHYDATUR_IE_POS             2U
#define SDMMC_HRS14_PHYCMDOF_IE_MASK            0x00000002U
#define SDMMC_HRS14_PHYCMDOF_IE_POS             1U
#define SDMMC_HRS14_PHYCMDUR_IE_MASK            0x00000001U
#define SDMMC_HRS14_PHYCMDUR_IE_POS             0U

/* Bit fields of HRS16 register */
#define SDMMC_HRS16_WRDATA1_SDCLK_DLY_MASK      0xF0000000U
#define SDMMC_HRS16_WRDATA1_SDCLK_DLY_POS       28U
#define SDMMC_HRS16_WRDATA0_SDCLK_DLY_MASK      0x0F000000U
#define SDMMC_HRS16_WRDATA0_SDCLK_DLY_POS       24U
#define SDMMC_HRS16_WRCMD1_SDCLK_DLY_MASK       0x00F00000U
#define SDMMC_HRS16_WRCMD1_SDCLK_DLY_POS        20U
#define SDMMC_HRS16_WRCMD0_SDCLK_DLY_MASK       0x000F0000U
#define SDMMC_HRS16_WRCMD0_SDCLK_DLY_POS        16U
#define SDMMC_HRS16_WRDATA1_DLY_MASK            0x0000F000U
#define SDMMC_HRS16_WRDATA1_DLY_POS             12U
#define SDMMC_HRS16_WRDATA0_DLY_MASK            0x00000F00U
#define SDMMC_HRS16_WRDATA0_DLY_POS             8U
#define SDMMC_HRS16_WRCMD1_DLY_MASK             0x000000F0U
#define SDMMC_HRS16_WRCMD1_DLY_POS              4U
#define SDMMC_HRS16_WRCMD0_DLY_MASK             0x0000000FU
#define SDMMC_HRS16_WRCMD0_DLY_POS              0U

/* Bit fields of HRS29 register */
#define SDMMC_HRS29_SDMAGICNUM_MASK             0xFFFFFFFFU
#define SDMMC_HRS29_SDMAGICNUM_POS              0U

/* Bit fields of HRS30 register */
#define SDMMC_HRS30_HS400ESSUP_MASK             0x00000002U
#define SDMMC_HRS30_HS400ESSUP_POS              1U
#define SDMMC_HRS30_CQSUP_MASK                  0x00000001U
#define SDMMC_HRS30_CQSUP_POS                   0U

/* Bit fields of HRS31 register */
#define SDMMC_HRS31_HOSTCTRLVER_MASK            0x0FFF0000U
#define SDMMC_HRS31_HOSTCTRLVER_POS             16U
#define SDMMC_HRS31_HOSTFIXVER_MASK             0x000000FFU
#define SDMMC_HRS31_HOSTFIXVER_POS              0U

/* Bit fields of HRS32 register */
#define SDMMC_HRS32_LOAD_MASK                   0x80000000U
#define SDMMC_HRS32_LOAD_POS                    31U
#define SDMMC_HRS32_ADDR_MASK                   0x7FFF0000U
#define SDMMC_HRS32_ADDR_POS                    16U
#define SDMMC_HRS32_DATA_MASK                   0x0000FFFFU
#define SDMMC_HRS32_DATA_POS                    0U

/* Bit fields of HRS33 register */
#define SDMMC_HRS33_STAT0_MASK                  0xFFFFFFFFU
#define SDMMC_HRS33_STAT0_POS                   0U

/* Bit fields of HRS34 register */
#define SDMMC_HRS34_STAT1_MASK                  0x000000FFU
#define SDMMC_HRS34_STAT1_POS                   0U

/* Bit fields of HRS36 register */
#define SDMMC_HRS36_BOOT_EDM_MASK               0x00000040U
#define SDMMC_HRS36_BOOT_EDM_POS                6U
#define SDMMC_HRS36_BOOT_EDE_MASK               0x00000020U
#define SDMMC_HRS36_BOOT_EDE_POS                5U
#define SDMMC_HRS36_BOOT_EDC_MASK               0x00000010U
#define SDMMC_HRS36_BOOT_EDC_POS                4U
#define SDMMC_HRS36_BOOT_EDT_MASK               0x00000008U
#define SDMMC_HRS36_BOOT_EDT_POS                3U
#define SDMMC_HRS36_BOOT_EAI_MASK               0x00000004U
#define SDMMC_HRS36_BOOT_EAI_POS                2U
#define SDMMC_HRS36_BOOT_EAT_MASK               0x00000002U
#define SDMMC_HRS36_BOOT_EAT_POS                1U
#define SDMMC_HRS36_BOOT_ACT_MASK               0x00000001U
#define SDMMC_HRS36_BOOT_ACT_POS                0U

/* Bit fields of HRS40 register */
#define SDMMC_HRS40_BASE_ADDR0_MASK             0xFFFFFFFFU
#define SDMMC_HRS40_BASE_ADDR0_POS              0U

/* Bit fields of HRS41 register */
#define SDMMC_HRS41_BASE_ADDR1_MASK             0xFFFFFFFFU
#define SDMMC_HRS41_BASE_ADDR1_POS              0U

/* Bit fields of HRS42 register */
#define SDMMC_HRS42_DESCMECH_TM_MASK            0x0000001EU
#define SDMMC_HRS42_DESCMECH_TM_POS             1U
#define SDMMC_HRS42_DESCMECH_EN_MASK            0x00000001U
#define SDMMC_HRS42_DESCMECH_EN_POS             0U

/* Bit fields of HRS43 register */
#define SDMMC_HRS43_ERROR_VAL_MASK              0x0000000EU
#define SDMMC_HRS43_ERROR_VAL_POS               1U
#define SDMMC_HRS43_ERROR_ST_MASK               0x00000001U
#define SDMMC_HRS43_ERROR_ST_POS                0U

/* Bit fields of SRS00 register */
#define SDMMC_SRS00_SAAR_MASK                   0xFFFFFFFFU
#define SDMMC_SRS00_SAAR_POS                    0U

/* Bit fields of SRS01 register */
#define SDMMC_SRS01_BCCT_MASK                   0xFFFF0000U
#define SDMMC_SRS01_BCCT_POS                    16U
#define SDMMC_SRS01_SDMABB_MASK                 0x00007000U
#define SDMMC_SRS01_SDMABB_POS                  12U
#define SDMMC_SRS01_TBS_MASK                    0x00000FFFU
#define SDMMC_SRS01_TBS_POS                     0U

/* Bit fields of SRS02 register */
#define SDMMC_SRS02_ARG1_MASK                   0xFFFFFFFFU
#define SDMMC_SRS02_ARG1_POS                    0U

/* Bit fields of SRS03 register */
#define SDMMC_SRS03_CIDX_MASK                   0x3F000000U
#define SDMMC_SRS03_CIDX_POS                    24U
#define SDMMC_SRS03_CT_MASK                     0x00C00000U
#define SDMMC_SRS03_CT_POS                      22U
#define SDMMC_SRS03_DPS_MASK                    0x00200000U
#define SDMMC_SRS03_DPS_POS                     21U
#define SDMMC_SRS03_CICE_MASK                   0x00100000U
#define SDMMC_SRS03_CICE_POS                    20U
#define SDMMC_SRS03_CRCCE_MASK                  0x00080000U
#define SDMMC_SRS03_CRCCE_POS                   19U
#define SDMMC_SRS03_SCF_MASK                    0x00040000U
#define SDMMC_SRS03_SCF_POS                     18U
#define SDMMC_SRS03_RTS_MASK                    0x00030000U
#define SDMMC_SRS03_RTS_POS                     16U
#define SDMMC_SRS03_RID_MASK                    0x00000100U
#define SDMMC_SRS03_RID_POS                     8U
#define SDMMC_SRS03_RECE_MASK                   0x00000080U
#define SDMMC_SRS03_RECE_POS                    7U
#define SDMMC_SRS03_RECT_MASK                   0x00000040U
#define SDMMC_SRS03_RECT_POS                    6U
#define SDMMC_SRS03_MSBS_MASK                   0x00000020U
#define SDMMC_SRS03_MSBS_POS                    5U
#define SDMMC_SRS03_DTDS_MASK                   0x00000010U
#define SDMMC_SRS03_DTDS_POS                    4U
#define SDMMC_SRS03_ACE_MASK                    0x0000000CU
#define SDMMC_SRS03_ACE_POS                     2U
#define SDMMC_SRS03_BCE_MASK                    0x00000002U
#define SDMMC_SRS03_BCE_POS                     1U
#define SDMMC_SRS03_DMAE_MASK                   0x00000001U
#define SDMMC_SRS03_DMAE_POS                    0U

/* Bit fields of SRS04 register */
#define SDMMC_SRS04_RESP0_MASK                  0xFFFFFFFFU
#define SDMMC_SRS04_RESP0_POS                   0U

/* Bit fields of SRS05 register */
#define SDMMC_SRS05_RESP1_MASK                  0xFFFFFFFFU
#define SDMMC_SRS05_RESP1_POS                   0U

/* Bit fields of SRS06 register */
#define SDMMC_SRS06_RESP2_MASK                  0xFFFFFFFFU
#define SDMMC_SRS06_RESP2_POS                   0U

/* Bit fields of SRS07 register */
#define SDMMC_SRS07_RESP3_MASK                  0xFFFFFFFFU
#define SDMMC_SRS07_RESP3_POS                   0U

/* Bit fields of SRS08 register */
#define SDMMC_SRS08_BDP_MASK                    0xFFFFFFFFU
#define SDMMC_SRS08_BDP_POS                     0U

/* Bit fields of SRS09 register */
#define SDMMC_SRS09_SCMDS_MASK                  0x10000000U
#define SDMMC_SRS09_SCMDS_POS                   28U
#define SDMMC_SRS09_CNIBE_MASK                  0x08000000U
#define SDMMC_SRS09_CNIBE_POS                   27U
#define SDMMC_SRS09_LVSIRSLT_MASK               0x04000000U
#define SDMMC_SRS09_LVSIRSLT_POS                26U
#define SDMMC_SRS09_CMDSL_MASK                  0x01000000U
#define SDMMC_SRS09_CMDSL_POS                   24U
#define SDMMC_SRS09_DATSL1_MASK                 0x00F00000U
#define SDMMC_SRS09_DATSL1_POS                  20U
#define SDMMC_SRS09_WPSL_MASK                   0x00080000U
#define SDMMC_SRS09_WPSL_POS                    19U
#define SDMMC_SRS09_CDSL_MASK                   0x00040000U
#define SDMMC_SRS09_CDSL_POS                    18U
#define SDMMC_SRS09_CSS_MASK                    0x00020000U
#define SDMMC_SRS09_CSS_POS                     17U
#define SDMMC_SRS09_CI_MASK                     0x00010000U
#define SDMMC_SRS09_CI_POS                      16U
#define SDMMC_SRS09_BRE_MASK                    0x00000800U
#define SDMMC_SRS09_BRE_POS                     11U
#define SDMMC_SRS09_BWE_MASK                    0x00000400U
#define SDMMC_SRS09_BWE_POS                     10U
#define SDMMC_SRS09_RTA_MASK                    0x00000200U
#define SDMMC_SRS09_RTA_POS                     9U
#define SDMMC_SRS09_WTA_MASK                    0x00000100U
#define SDMMC_SRS09_WTA_POS                     8U
#define SDMMC_SRS09_DATSL2_MASK                 0x000000F0U
#define SDMMC_SRS09_DATSL2_POS                  4U
#define SDMMC_SRS09_DLA_MASK                    0x00000004U
#define SDMMC_SRS09_DLA_POS                     2U
#define SDMMC_SRS09_CIDAT_MASK                  0x00000002U
#define SDMMC_SRS09_CIDAT_POS                   1U
#define SDMMC_SRS09_CICMD_MASK                  0x00000001U
#define SDMMC_SRS09_CICMD_POS                   0U

/* Bit fields of SRS10 register */
#define SDMMC_SRS10_WORM_MASK                   0x04000000U
#define SDMMC_SRS10_WORM_POS                    26U
#define SDMMC_SRS10_WOIS_MASK                   0x02000000U
#define SDMMC_SRS10_WOIS_POS                    25U
#define SDMMC_SRS10_WOIQ_MASK                   0x01000000U
#define SDMMC_SRS10_WOIQ_POS                    24U
#define SDMMC_SRS10_IBG_MASK                    0x00080000U
#define SDMMC_SRS10_IBG_POS                     19U
#define SDMMC_SRS10_RWC_MASK                    0x00040000U
#define SDMMC_SRS10_RWC_POS                     18U
#define SDMMC_SRS10_CREQ_MASK                   0x00020000U
#define SDMMC_SRS10_CREQ_POS                    17U
#define SDMMC_SRS10_SBGR_MASK                   0x00010000U
#define SDMMC_SRS10_SBGR_POS                    16U
#define SDMMC_SRS10_BVS_MASK                    0x00000E00U
#define SDMMC_SRS10_BVS_POS                     9U
#define SDMMC_SRS10_BP_MASK                     0x00000100U
#define SDMMC_SRS10_BP_POS                      8U
#define SDMMC_SRS10_CDSS_MASK                   0x00000080U
#define SDMMC_SRS10_CDSS_POS                    7U
#define SDMMC_SRS10_CDTL_MASK                   0x00000040U
#define SDMMC_SRS10_CDTL_POS                    6U
#define SDMMC_SRS10_EDTW_MASK                   0x00000020U
#define SDMMC_SRS10_EDTW_POS                    5U
#define SDMMC_SRS10_DMASEL_MASK                 0x00000018U
#define SDMMC_SRS10_DMASEL_POS                  3U
#define SDMMC_SRS10_HSE_MASK                    0x00000004U
#define SDMMC_SRS10_HSE_POS                     2U
#define SDMMC_SRS10_DTW_MASK                    0x00000002U
#define SDMMC_SRS10_DTW_POS                     1U
#define SDMMC_SRS10_LEDC_MASK                   0x00000001U
#define SDMMC_SRS10_LEDC_POS                    0U

/* Bit fields of SRS11 register */
#define SDMMC_SRS11_SRDAT_MASK                  0x04000000U
#define SDMMC_SRS11_SRDAT_POS                   26U
#define SDMMC_SRS11_SRCMD_MASK                  0x02000000U
#define SDMMC_SRS11_SRCMD_POS                   25U
#define SDMMC_SRS11_SRFA_MASK                   0x01000000U
#define SDMMC_SRS11_SRFA_POS                    24U
#define SDMMC_SRS11_DTCV_MASK                   0x000F0000U
#define SDMMC_SRS11_DTCV_POS                    16U
#define SDMMC_SRS11_SDCFSL_MASK                 0x0000FF00U
#define SDMMC_SRS11_SDCFSL_POS                  8U
#define SDMMC_SRS11_SDCFSH_MASK                 0x000000C0U
#define SDMMC_SRS11_SDCFSH_POS                  6U
#define SDMMC_SRS11_SDCE_MASK                   0x00000004U
#define SDMMC_SRS11_SDCE_POS                    2U
#define SDMMC_SRS11_ICS_MASK                    0x00000002U
#define SDMMC_SRS11_ICS_POS                     1U
#define SDMMC_SRS11_ICE_MASK                    0x00000001U
#define SDMMC_SRS11_ICE_POS                     0U

/* Bit fields of SRS12 register */
#define SDMMC_SRS12_ERSP_MASK                   0x08000000U
#define SDMMC_SRS12_ERSP_POS                    27U
#define SDMMC_SRS12_EADMA_MASK                  0x02000000U
#define SDMMC_SRS12_EADMA_POS                   25U
#define SDMMC_SRS12_EAC_MASK                    0x01000000U
#define SDMMC_SRS12_EAC_POS                     24U
#define SDMMC_SRS12_ECL_MASK                    0x00800000U
#define SDMMC_SRS12_ECL_POS                     23U
#define SDMMC_SRS12_EDEB_MASK                   0x00400000U
#define SDMMC_SRS12_EDEB_POS                    22U
#define SDMMC_SRS12_EDCRC_MASK                  0x00200000U
#define SDMMC_SRS12_EDCRC_POS                   21U
#define SDMMC_SRS12_EDT_MASK                    0x00100000U
#define SDMMC_SRS12_EDT_POS                     20U
#define SDMMC_SRS12_ECI_MASK                    0x00080000U
#define SDMMC_SRS12_ECI_POS                     19U
#define SDMMC_SRS12_ECEB_MASK                   0x00040000U
#define SDMMC_SRS12_ECEB_POS                    18U
#define SDMMC_SRS12_ECCRC_MASK                  0x00020000U
#define SDMMC_SRS12_ECCRC_POS                   17U
#define SDMMC_SRS12_ECT_MASK                    0x00010000U
#define SDMMC_SRS12_ECT_POS                     16U
#define SDMMC_SRS12_EINT_MASK                   0x00008000U
#define SDMMC_SRS12_EINT_POS                    15U
#define SDMMC_SRS12_CQINT_MASK                  0x00004000U
#define SDMMC_SRS12_CQINT_POS                   14U
#define SDMMC_SRS12_FXE_MASK                    0x00002000U
#define SDMMC_SRS12_FXE_POS                     13U
#define SDMMC_SRS12_CINT_MASK                   0x00000100U
#define SDMMC_SRS12_CINT_POS                    8U
#define SDMMC_SRS12_CR_MASK                     0x00000080U
#define SDMMC_SRS12_CR_POS                      7U
#define SDMMC_SRS12_CIN_MASK                    0x00000040U
#define SDMMC_SRS12_CIN_POS                     6U
#define SDMMC_SRS12_BRR_MASK                    0x00000020U
#define SDMMC_SRS12_BRR_POS                     5U
#define SDMMC_SRS12_BWR_MASK                    0x00000010U
#define SDMMC_SRS12_BWR_POS                     4U
#define SDMMC_SRS12_DMAINT_MASK                 0x00000008U
#define SDMMC_SRS12_DMAINT_POS                  3U
#define SDMMC_SRS12_BGE_MASK                    0x00000004U
#define SDMMC_SRS12_BGE_POS                     2U
#define SDMMC_SRS12_TC_MASK                     0x00000002U
#define SDMMC_SRS12_TC_POS                      1U
#define SDMMC_SRS12_CC_MASK                     0x00000001U
#define SDMMC_SRS12_CC_POS                      0U

/* Bit fields of SRS13 register */
#define SDMMC_SRS13_ERSP_SE_MASK                0x08000000U
#define SDMMC_SRS13_ERSP_SE_POS                 27U
#define SDMMC_SRS13_EADMA_SE_MASK               0x02000000U
#define SDMMC_SRS13_EADMA_SE_POS                25U
#define SDMMC_SRS13_EAC_SE_MASK                 0x01000000U
#define SDMMC_SRS13_EAC_SE_POS                  24U
#define SDMMC_SRS13_ECL_SE_MASK                 0x00800000U
#define SDMMC_SRS13_ECL_SE_POS                  23U
#define SDMMC_SRS13_EDEB_SE_MASK                0x00400000U
#define SDMMC_SRS13_EDEB_SE_POS                 22U
#define SDMMC_SRS13_EDCRC_SE_MASK               0x00200000U
#define SDMMC_SRS13_EDCRC_SE_POS                21U
#define SDMMC_SRS13_EDT_SE_MASK                 0x00100000U
#define SDMMC_SRS13_EDT_SE_POS                  20U
#define SDMMC_SRS13_ECI_SE_MASK                 0x00080000U
#define SDMMC_SRS13_ECI_SE_POS                  19U
#define SDMMC_SRS13_ECEB_SE_MASK                0x00040000U
#define SDMMC_SRS13_ECEB_SE_POS                 18U
#define SDMMC_SRS13_ECCRC_SE_MASK               0x00020000U
#define SDMMC_SRS13_ECCRC_SE_POS                17U
#define SDMMC_SRS13_ECT_SE_MASK                 0x00010000U
#define SDMMC_SRS13_ECT_SE_POS                  16U
#define SDMMC_SRS13_CQINT_SE_MASK               0x00004000U
#define SDMMC_SRS13_CQINT_SE_POS                14U
#define SDMMC_SRS13_FXE_SE_MASK                 0x00002000U
#define SDMMC_SRS13_FXE_SE_POS                  13U
#define SDMMC_SRS13_CINT_SE_MASK                0x00000100U
#define SDMMC_SRS13_CINT_SE_POS                 8U
#define SDMMC_SRS13_CR_SE_MASK                  0x00000080U
#define SDMMC_SRS13_CR_SE_POS                   7U
#define SDMMC_SRS13_CIN_SE_MASK                 0x00000040U
#define SDMMC_SRS13_CIN_SE_POS                  6U
#define SDMMC_SRS13_BRR_SE_MASK                 0x00000020U
#define SDMMC_SRS13_BRR_SE_POS                  5U
#define SDMMC_SRS13_BWR_SE_MASK                 0x00000010U
#define SDMMC_SRS13_BWR_SE_POS                  4U
#define SDMMC_SRS13_DMAINT_SE_MASK              0x00000008U
#define SDMMC_SRS13_DMAINT_SE_POS               3U
#define SDMMC_SRS13_BGE_SE_MASK                 0x00000004U
#define SDMMC_SRS13_BGE_SE_POS                  2U
#define SDMMC_SRS13_TC_SE_MASK                  0x00000002U
#define SDMMC_SRS13_TC_SE_POS                   1U
#define SDMMC_SRS13_CC_SE_MASK                  0x00000001U
#define SDMMC_SRS13_CC_SE_POS                   0U

/* Bit fields of SRS14 register */
#define SDMMC_SRS14_ERSP_IE_MASK                0x08000000U
#define SDMMC_SRS14_ERSP_IE_POS                 27U
#define SDMMC_SRS14_EADMA_IE_MASK               0x02000000U
#define SDMMC_SRS14_EADMA_IE_POS                25U
#define SDMMC_SRS14_EAC_IE_MASK                 0x01000000U
#define SDMMC_SRS14_EAC_IE_POS                  24U
#define SDMMC_SRS14_ECL_IE_MASK                 0x00800000U
#define SDMMC_SRS14_ECL_IE_POS                  23U
#define SDMMC_SRS14_EDEB_IE_MASK                0x00400000U
#define SDMMC_SRS14_EDEB_IE_POS                 22U
#define SDMMC_SRS14_EDCRC_IE_MASK               0x00200000U
#define SDMMC_SRS14_EDCRC_IE_POS                21U
#define SDMMC_SRS14_EDT_IE_MASK                 0x00100000U
#define SDMMC_SRS14_EDT_IE_POS                  20U
#define SDMMC_SRS14_ECI_IE_MASK                 0x00080000U
#define SDMMC_SRS14_ECI_IE_POS                  19U
#define SDMMC_SRS14_ECEB_IE_MASK                0x00040000U
#define SDMMC_SRS14_ECEB_IE_POS                 18U
#define SDMMC_SRS14_ECCRC_IE_MASK               0x00020000U
#define SDMMC_SRS14_ECCRC_IE_POS                17U
#define SDMMC_SRS14_ECT_IE_MASK                 0x00010000U
#define SDMMC_SRS14_ECT_IE_POS                  16U
#define SDMMC_SRS14_CQINT_IE_MASK               0x00004000U
#define SDMMC_SRS14_CQINT_IE_POS                14U
#define SDMMC_SRS14_FXE_IE_MASK                 0x00002000U
#define SDMMC_SRS14_FXE_IE_POS                  13U
#define SDMMC_SRS14_CINT_IE_MASK                0x00000100U
#define SDMMC_SRS14_CINT_IE_POS                 8U
#define SDMMC_SRS14_CR_IE_MASK                  0x00000080U
#define SDMMC_SRS14_CR_IE_POS                   7U
#define SDMMC_SRS14_CIN_IE_MASK                 0x00000040U
#define SDMMC_SRS14_CIN_IE_POS                  6U
#define SDMMC_SRS14_BRR_IE_MASK                 0x00000020U
#define SDMMC_SRS14_BRR_IE_POS                  5U
#define SDMMC_SRS14_BWR_IE_MASK                 0x00000010U
#define SDMMC_SRS14_BWR_IE_POS                  4U
#define SDMMC_SRS14_DMAINT_IE_MASK              0x00000008U
#define SDMMC_SRS14_DMAINT_IE_POS               3U
#define SDMMC_SRS14_BGE_IE_MASK                 0x00000004U
#define SDMMC_SRS14_BGE_IE_POS                  2U
#define SDMMC_SRS14_TC_IE_MASK                  0x00000002U
#define SDMMC_SRS14_TC_IE_POS                   1U
#define SDMMC_SRS14_CC_IE_MASK                  0x00000001U
#define SDMMC_SRS14_CC_IE_POS                   0U

/* Bit fields of SRS15 register */
#define SDMMC_SRS15_PVE_MASK                    0x80000000U
#define SDMMC_SRS15_PVE_POS                     31U
#define SDMMC_SRS15_A64B_MASK                   0x20000000U
#define SDMMC_SRS15_A64B_POS                    29U
#define SDMMC_SRS15_HV4E_MASK                   0x10000000U
#define SDMMC_SRS15_HV4E_POS                    28U
#define SDMMC_SRS15_CMD23E_MASK                 0x08000000U
#define SDMMC_SRS15_CMD23E_POS                  27U
#define SDMMC_SRS15_ADMA2LM_MASK                0x04000000U
#define SDMMC_SRS15_ADMA2LM_POS                 26U
#define SDMMC_SRS15_LVSIEXEC_MASK               0x01000000U
#define SDMMC_SRS15_LVSIEXEC_POS                24U
#define SDMMC_SRS15_SCS_MASK                    0x00800000U
#define SDMMC_SRS15_SCS_POS                     23U
#define SDMMC_SRS15_EXTNG_MASK                  0x00400000U
#define SDMMC_SRS15_EXTNG_POS                   22U
#define SDMMC_SRS15_DSS_MASK                    0x00300000U
#define SDMMC_SRS15_DSS_POS                     20U
#define SDMMC_SRS15_V18SE_MASK                  0x00080000U
#define SDMMC_SRS15_V18SE_POS                   19U
#define SDMMC_SRS15_UMS_MASK                    0x00070000U
#define SDMMC_SRS15_UMS_POS                     16U
#define SDMMC_SRS15_CNIACE_MASK                 0x00000080U
#define SDMMC_SRS15_CNIACE_POS                  7U
#define SDMMC_SRS15_ACRE_MASK                   0x00000020U
#define SDMMC_SRS15_ACRE_POS                    5U
#define SDMMC_SRS15_ACIE_MASK                   0x00000010U
#define SDMMC_SRS15_ACIE_POS                    4U
#define SDMMC_SRS15_ACEBE_MASK                  0x00000008U
#define SDMMC_SRS15_ACEBE_POS                   3U
#define SDMMC_SRS15_ACCE_MASK                   0x00000004U
#define SDMMC_SRS15_ACCE_POS                    2U
#define SDMMC_SRS15_ACTE_MASK                   0x00000002U
#define SDMMC_SRS15_ACTE_POS                    1U
#define SDMMC_SRS15_ACNE_MASK                   0x00000001U
#define SDMMC_SRS15_ACNE_POS                    0U

/* Bit fields of SRS16 register */
#define SDMMC_SRS16_SLT_MASK                    0xC0000000U
#define SDMMC_SRS16_SLT_POS                     30U
#define SDMMC_SRS16_AIS_MASK                    0x20000000U
#define SDMMC_SRS16_AIS_POS                     29U
#define SDMMC_SRS16_A64SV3_MASK                 0x10000000U
#define SDMMC_SRS16_A64SV3_POS                  28U
#define SDMMC_SRS16_A64SV4_MASK                 0x08000000U
#define SDMMC_SRS16_A64SV4_POS                  27U
#define SDMMC_SRS16_VS18_MASK                   0x04000000U
#define SDMMC_SRS16_VS18_POS                    26U
#define SDMMC_SRS16_VS30_MASK                   0x02000000U
#define SDMMC_SRS16_VS30_POS                    25U
#define SDMMC_SRS16_VS33_MASK                   0x01000000U
#define SDMMC_SRS16_VS33_POS                    24U
#define SDMMC_SRS16_SRS_MASK                    0x00800000U
#define SDMMC_SRS16_SRS_POS                     23U
#define SDMMC_SRS16_DMAS_MASK                   0x00400000U
#define SDMMC_SRS16_DMAS_POS                    22U
#define SDMMC_SRS16_HSS_MASK                    0x00200000U
#define SDMMC_SRS16_HSS_POS                     21U
#define SDMMC_SRS16_ADMA1S_MASK                 0x00100000U
#define SDMMC_SRS16_ADMA1S_POS                  20U
#define SDMMC_SRS16_ADMA2S_MASK                 0x00080000U
#define SDMMC_SRS16_ADMA2S_POS                  19U
#define SDMMC_SRS16_EDS8_MASK                   0x00040000U
#define SDMMC_SRS16_EDS8_POS                    18U
#define SDMMC_SRS16_MBL_MASK                    0x00030000U
#define SDMMC_SRS16_MBL_POS                     16U
#define SDMMC_SRS16_BCSDCLK_MASK                0x0000FF00U
#define SDMMC_SRS16_BCSDCLK_POS                 8U
#define SDMMC_SRS16_TCU_MASK                    0x00000080U
#define SDMMC_SRS16_TCU_POS                     7U
#define SDMMC_SRS16_TCF_MASK                    0x0000003FU
#define SDMMC_SRS16_TCF_POS                     0U

/* Bit fields of SRS17 register */
#define SDMMC_SRS17_LVSH_MASK                   0x80000000U
#define SDMMC_SRS17_LVSH_POS                    31U
#define SDMMC_SRS17_VDD2S_MASK                  0x10000000U
#define SDMMC_SRS17_VDD2S_POS                   28U
#define SDMMC_SRS17_ADMA3SUP_MASK               0x08000000U
#define SDMMC_SRS17_ADMA3SUP_POS                27U
#define SDMMC_SRS17_CLKMPR_MASK                 0x00FF0000U
#define SDMMC_SRS17_CLKMPR_POS                  16U
#define SDMMC_SRS17_RTNGM_MASK                  0x0000C000U
#define SDMMC_SRS17_RTNGM_POS                   14U
#define SDMMC_SRS17_UTSM50_MASK                 0x00002000U
#define SDMMC_SRS17_UTSM50_POS                  13U
#define SDMMC_SRS17_RTNGCNT_MASK                0x00000F00U
#define SDMMC_SRS17_RTNGCNT_POS                 8U
#define SDMMC_SRS17_DRVD_MASK                   0x00000040U
#define SDMMC_SRS17_DRVD_POS                    6U
#define SDMMC_SRS17_DRVC_MASK                   0x00000020U
#define SDMMC_SRS17_DRVC_POS                    5U
#define SDMMC_SRS17_DRVA_MASK                   0x00000010U
#define SDMMC_SRS17_DRVA_POS                    4U
#define SDMMC_SRS17_UHSII_MASK                  0x00000008U
#define SDMMC_SRS17_UHSII_POS                   3U
#define SDMMC_SRS17_DDR50_MASK                  0x00000004U
#define SDMMC_SRS17_DDR50_POS                   2U
#define SDMMC_SRS17_SDR104_MASK                 0x00000002U
#define SDMMC_SRS17_SDR104_POS                  1U
#define SDMMC_SRS17_SDR50_MASK                  0x00000001U
#define SDMMC_SRS17_SDR50_POS                   0U

/* Bit fields of SRS18 register */
#define SDMMC_SRS18_MC18_MASK                   0x00FF0000U
#define SDMMC_SRS18_MC18_POS                    16U
#define SDMMC_SRS18_MC30_MASK                   0x0000FF00U
#define SDMMC_SRS18_MC30_POS                    8U
#define SDMMC_SRS18_MC33_MASK                   0x000000FFU
#define SDMMC_SRS18_MC33_POS                    0U

/* Bit fields of SRS19 register */
#define SDMMC_SRS19_MC18V2_MASK                 0x000000FFU
#define SDMMC_SRS19_MC18V2_POS                  0U

/* Bit fields of SRS20 register */
#define SDMMC_SRS20_ERESP_FE_MASK               0x08000000U
#define SDMMC_SRS20_ERESP_FE_POS                27U
#define SDMMC_SRS20_ETUNE_FE_MASK               0x04000000U
#define SDMMC_SRS20_ETUNE_FE_POS                26U
#define SDMMC_SRS20_EADMA_FE_MASK               0x02000000U
#define SDMMC_SRS20_EADMA_FE_POS                25U
#define SDMMC_SRS20_EAC_FE_MASK                 0x01000000U
#define SDMMC_SRS20_EAC_FE_POS                  24U
#define SDMMC_SRS20_ECL_FE_MASK                 0x00800000U
#define SDMMC_SRS20_ECL_FE_POS                  23U
#define SDMMC_SRS20_EDEB_FE_MASK                0x00400000U
#define SDMMC_SRS20_EDEB_FE_POS                 22U
#define SDMMC_SRS20_EDCRC_FE_MASK               0x00200000U
#define SDMMC_SRS20_EDCRC_FE_POS                21U
#define SDMMC_SRS20_EDT_FE_MASK                 0x00100000U
#define SDMMC_SRS20_EDT_FE_POS                  20U
#define SDMMC_SRS20_ECI_FE_MASK                 0x00080000U
#define SDMMC_SRS20_ECI_FE_POS                  19U
#define SDMMC_SRS20_ECEB_FE_MASK                0x00040000U
#define SDMMC_SRS20_ECEB_FE_POS                 18U
#define SDMMC_SRS20_ECCRC_FE_MASK               0x00020000U
#define SDMMC_SRS20_ECCRC_FE_POS                17U
#define SDMMC_SRS20_ECT_FE_MASK                 0x00010000U
#define SDMMC_SRS20_ECT_FE_POS                  16U
#define SDMMC_SRS20_CNIACE_FE_MASK              0x00000080U
#define SDMMC_SRS20_CNIACE_FE_POS               7U
#define SDMMC_SRS20_ACIE_FE_MASK                0x00000010U
#define SDMMC_SRS20_ACIE_FE_POS                 4U
#define SDMMC_SRS20_ACEBE_FE_MASK               0x00000008U
#define SDMMC_SRS20_ACEBE_FE_POS                3U
#define SDMMC_SRS20_ACCE_FE_MASK                0x00000004U
#define SDMMC_SRS20_ACCE_FE_POS                 2U
#define SDMMC_SRS20_ACTE_FE_MASK                0x00000002U
#define SDMMC_SRS20_ACTE_FE_POS                 1U
#define SDMMC_SRS20_ACNE_FE_MASK                0x00000001U
#define SDMMC_SRS20_ACNE_FE_POS                 0U

/* Bit fields of SRS21 register */
#define SDMMC_SRS21_EADMAL_MASK                 0x00000004U
#define SDMMC_SRS21_EADMAL_POS                  2U
#define SDMMC_SRS21_EADMAS_MASK                 0x00000003U
#define SDMMC_SRS21_EADMAS_POS                  0U

/* Bit fields of SRS22 register */
#define SDMMC_SRS22_DMASA1_MASK                 0xFFFFFFFFU
#define SDMMC_SRS22_DMASA1_POS                  0U

/* Bit fields of SRS23 register */
#define SDMMC_SRS23_DMASA2_MASK                 0xFFFFFFFFU
#define SDMMC_SRS23_DMASA2_POS                  0U

/* Bit fields of SRS24 register */
#define SDMMC_SRS24_SRS24_DSSPV_31_30_MASK      0xC0000000U
#define SDMMC_SRS24_SRS24_DSSPV_31_30_POS       30U
#define SDMMC_SRS24_SRS24_SDCFSPV_25_16_MASK    0x03FF0000U
#define SDMMC_SRS24_SRS24_SDCFSPV_25_16_POS     16U

/* Bit fields of SRS25 register */
#define SDMMC_SRS25_SRS25_DSSPV_31_30_MASK      0xC0000000U
#define SDMMC_SRS25_SRS25_DSSPV_31_30_POS       30U
#define SDMMC_SRS25_SRS25_SDCFSPV_25_16_MASK    0x03FF0000U
#define SDMMC_SRS25_SRS25_SDCFSPV_25_16_POS     16U
#define SDMMC_SRS25_SRS25_DSSPV_15_14_MASK      0x0000C000U
#define SDMMC_SRS25_SRS25_DSSPV_15_14_POS       14U
#define SDMMC_SRS25_SRS25_SDCFSPV_09_00_MASK    0x000003FFU
#define SDMMC_SRS25_SRS25_SDCFSPV_09_00_POS     0U

/* Bit fields of SRS26 register */
#define SDMMC_SRS26_SRS26_DSSPV_31_30_MASK      0xC0000000U
#define SDMMC_SRS26_SRS26_DSSPV_31_30_POS       30U
#define SDMMC_SRS26_SRS26_SDCFSPV_25_16_MASK    0x03FF0000U
#define SDMMC_SRS26_SRS26_SDCFSPV_25_16_POS     16U
#define SDMMC_SRS26_SRS26_DSSPV_15_14_MASK      0x0000C000U
#define SDMMC_SRS26_SRS26_DSSPV_15_14_POS       14U
#define SDMMC_SRS26_SRS26_CGSPV_10_MASK         0x00000400U
#define SDMMC_SRS26_SRS26_CGSPV_10_POS          10U
#define SDMMC_SRS26_SRS26_SDCFSPV_09_00_MASK    0x000003FFU
#define SDMMC_SRS26_SRS26_SDCFSPV_09_00_POS     0U

/* Bit fields of SRS27 register */
#define SDMMC_SRS27_SRS27_DSSPV_31_30_MASK      0xC0000000U
#define SDMMC_SRS27_SRS27_DSSPV_31_30_POS       30U
#define SDMMC_SRS27_SRS27_SDCFSPV_25_16_MASK    0x03FF0000U
#define SDMMC_SRS27_SRS27_SDCFSPV_25_16_POS     16U
#define SDMMC_SRS27_SRS27_DSSPV_15_14_MASK      0x0000C000U
#define SDMMC_SRS27_SRS27_DSSPV_15_14_POS       14U
#define SDMMC_SRS27_SRS27_SDCFSPV_09_00_MASK    0x000003FFU
#define SDMMC_SRS27_SRS27_SDCFSPV_09_00_POS     0U

/* Bit fields of SRS30 register */
#define SDMMC_SRS30_ADMA3ID1_MASK               0xFFFFFFFFU
#define SDMMC_SRS30_ADMA3ID1_POS                0U

/* Bit fields of SRS31 register */
#define SDMMC_SRS31_ADMA3ID2_MASK               0xFFFFFFFFU
#define SDMMC_SRS31_ADMA3ID2_POS                0U

/* Bit fields of CRS63 register */
#define SDMMC_CRS63_SVN_MASK                    0x00FF0000U
#define SDMMC_CRS63_SVN_POS                     16U
#define SDMMC_CRS63_ISES_MASK                   0x00000001U
#define SDMMC_CRS63_ISES_POS                    0U

/* Bit fields of CQRS00 register */
#define SDMMC_CQRS00_CQVN1_MASK                 0x00000F00U
#define SDMMC_CQRS00_CQVN1_POS                  8U
#define SDMMC_CQRS00_CQVN2_MASK                 0x000000F0U
#define SDMMC_CQRS00_CQVN2_POS                  4U
#define SDMMC_CQRS00_CQVN3_MASK                 0x0000000FU
#define SDMMC_CQRS00_CQVN3_POS                  0U

/* Bit fields of CQRS01 register */
#define SDMMC_CQRS01_ITCFMUL_MASK               0x0000F000U
#define SDMMC_CQRS01_ITCFMUL_POS                12U
#define SDMMC_CQRS01_ITCFVAL_MASK               0x000003FFU
#define SDMMC_CQRS01_ITCFVAL_POS                0U

/* Bit fields of CQRS02 register */
#define SDMMC_CQRS02_CQDCE_MASK                 0x00001000U
#define SDMMC_CQRS02_CQDCE_POS                  12U
#define SDMMC_CQRS02_CQTDS_MASK                 0x00000100U
#define SDMMC_CQRS02_CQTDS_POS                  8U
#define SDMMC_CQRS02_CQE_MASK                   0x00000001U
#define SDMMC_CQRS02_CQE_POS                    0U

/* Bit fields of CQRS03 register */
#define SDMMC_CQRS03_CQCAT_MASK                 0x00000100U
#define SDMMC_CQRS03_CQCAT_POS                  8U
#define SDMMC_CQRS03_CQHLT_MASK                 0x00000001U
#define SDMMC_CQRS03_CQHLT_POS                  0U

/* Bit fields of CQRS04 register */
#define SDMMC_CQRS04_CQTCL_MASK                 0x00000008U
#define SDMMC_CQRS04_CQTCL_POS                  3U
#define SDMMC_CQRS04_CQREDI_MASK                0x00000004U
#define SDMMC_CQRS04_CQREDI_POS                 2U
#define SDMMC_CQRS04_CQTCC_MASK                 0x00000002U
#define SDMMC_CQRS04_CQTCC_POS                  1U
#define SDMMC_CQRS04_CQHAC_MASK                 0x00000001U
#define SDMMC_CQRS04_CQHAC_POS                  0U

/* Bit fields of CQRS05 register */
#define SDMMC_CQRS05_CQTCLST_MASK               0x00000008U
#define SDMMC_CQRS05_CQTCLST_POS                3U
#define SDMMC_CQRS05_CQREDST_MASK               0x00000004U
#define SDMMC_CQRS05_CQREDST_POS                2U
#define SDMMC_CQRS05_CQTCCST_MASK               0x00000002U
#define SDMMC_CQRS05_CQTCCST_POS                1U
#define SDMMC_CQRS05_CQHACST_MASK               0x00000001U
#define SDMMC_CQRS05_CQHACST_POS                0U

/* Bit fields of CQRS06 register */
#define SDMMC_CQRS06_CQTCLSI_MASK               0x00000008U
#define SDMMC_CQRS06_CQTCLSI_POS                3U
#define SDMMC_CQRS06_CQREDSI_MASK               0x00000004U
#define SDMMC_CQRS06_CQREDSI_POS                2U
#define SDMMC_CQRS06_CQTCCSI_MASK               0x00000002U
#define SDMMC_CQRS06_CQTCCSI_POS                1U
#define SDMMC_CQRS06_CQHACSI_MASK               0x00000001U
#define SDMMC_CQRS06_CQHACSI_POS                0U

/* Bit fields of CQRS07 register */
#define SDMMC_CQRS07_CQICED_MASK                0x80000000U
#define SDMMC_CQRS07_CQICED_POS                 31U
#define SDMMC_CQRS07_CQICSB_MASK                0x00100000U
#define SDMMC_CQRS07_CQICSB_POS                 20U
#define SDMMC_CQRS07_CQICCTR_MASK               0x00010000U
#define SDMMC_CQRS07_CQICCTR_POS                16U
#define SDMMC_CQRS07_CQICCTHWEN_MASK            0x00008000U
#define SDMMC_CQRS07_CQICCTHWEN_POS             15U
#define SDMMC_CQRS07_CQICCTH_MASK               0x00001F00U
#define SDMMC_CQRS07_CQICCTH_POS                8U
#define SDMMC_CQRS07_CQICTOVALEN_MASK           0x00000080U
#define SDMMC_CQRS07_CQICTOVALEN_POS            7U
#define SDMMC_CQRS07_CQICTOVAL_MASK             0x0000007FU
#define SDMMC_CQRS07_CQICTOVAL_POS              0U

/* Bit fields of CQRS08 register */
#define SDMMC_CQRS08_CQTDLBA_MASK               0xFFFFFFFFU
#define SDMMC_CQRS08_CQTDLBA_POS                0U

/* Bit fields of CQRS09 register */
#define SDMMC_CQRS09_CQTDLBAU_MASK              0xFFFFFFFFU
#define SDMMC_CQRS09_CQTDLBAU_POS               0U

/* Bit fields of CQRS10 register */
#define SDMMC_CQRS10_CQTD31_MASK                0x80000000U
#define SDMMC_CQRS10_CQTD31_POS                 31U
#define SDMMC_CQRS10_CQTD30_MASK                0x40000000U
#define SDMMC_CQRS10_CQTD30_POS                 30U
#define SDMMC_CQRS10_CQTD29_MASK                0x20000000U
#define SDMMC_CQRS10_CQTD29_POS                 29U
#define SDMMC_CQRS10_CQTD28_MASK                0x10000000U
#define SDMMC_CQRS10_CQTD28_POS                 28U
#define SDMMC_CQRS10_CQTD27_MASK                0x08000000U
#define SDMMC_CQRS10_CQTD27_POS                 27U
#define SDMMC_CQRS10_CQTD26_MASK                0x04000000U
#define SDMMC_CQRS10_CQTD26_POS                 26U
#define SDMMC_CQRS10_CQTD25_MASK                0x02000000U
#define SDMMC_CQRS10_CQTD25_POS                 25U
#define SDMMC_CQRS10_CQTD24_MASK                0x01000000U
#define SDMMC_CQRS10_CQTD24_POS                 24U
#define SDMMC_CQRS10_CQTD23_MASK                0x00800000U
#define SDMMC_CQRS10_CQTD23_POS                 23U
#define SDMMC_CQRS10_CQTD22_MASK                0x00400000U
#define SDMMC_CQRS10_CQTD22_POS                 22U
#define SDMMC_CQRS10_CQTD21_MASK                0x00200000U
#define SDMMC_CQRS10_CQTD21_POS                 21U
#define SDMMC_CQRS10_CQTD20_MASK                0x00100000U
#define SDMMC_CQRS10_CQTD20_POS                 20U
#define SDMMC_CQRS10_CQTD19_MASK                0x00080000U
#define SDMMC_CQRS10_CQTD19_POS                 19U
#define SDMMC_CQRS10_CQTD18_MASK                0x00040000U
#define SDMMC_CQRS10_CQTD18_POS                 18U
#define SDMMC_CQRS10_CQTD17_MASK                0x00020000U
#define SDMMC_CQRS10_CQTD17_POS                 17U
#define SDMMC_CQRS10_CQTD16_MASK                0x00010000U
#define SDMMC_CQRS10_CQTD16_POS                 16U
#define SDMMC_CQRS10_CQTD15_MASK                0x00008000U
#define SDMMC_CQRS10_CQTD15_POS                 15U
#define SDMMC_CQRS10_CQTD14_MASK                0x00004000U
#define SDMMC_CQRS10_CQTD14_POS                 14U
#define SDMMC_CQRS10_CQTD13_MASK                0x00002000U
#define SDMMC_CQRS10_CQTD13_POS                 13U
#define SDMMC_CQRS10_CQTD12_MASK                0x00001000U
#define SDMMC_CQRS10_CQTD12_POS                 12U
#define SDMMC_CQRS10_CQTD11_MASK                0x00000800U
#define SDMMC_CQRS10_CQTD11_POS                 11U
#define SDMMC_CQRS10_CQTD10_MASK                0x00000400U
#define SDMMC_CQRS10_CQTD10_POS                 10U
#define SDMMC_CQRS10_CQTD09_MASK                0x00000200U
#define SDMMC_CQRS10_CQTD09_POS                 9U
#define SDMMC_CQRS10_CQTD08_MASK                0x00000100U
#define SDMMC_CQRS10_CQTD08_POS                 8U
#define SDMMC_CQRS10_CQTD07_MASK                0x00000080U
#define SDMMC_CQRS10_CQTD07_POS                 7U
#define SDMMC_CQRS10_CQTD06_MASK                0x00000040U
#define SDMMC_CQRS10_CQTD06_POS                 6U
#define SDMMC_CQRS10_CQTD05_MASK                0x00000020U
#define SDMMC_CQRS10_CQTD05_POS                 5U
#define SDMMC_CQRS10_CQTD04_MASK                0x00000010U
#define SDMMC_CQRS10_CQTD04_POS                 4U
#define SDMMC_CQRS10_CQTD03_MASK                0x00000008U
#define SDMMC_CQRS10_CQTD03_POS                 3U
#define SDMMC_CQRS10_CQTD02_MASK                0x00000004U
#define SDMMC_CQRS10_CQTD02_POS                 2U
#define SDMMC_CQRS10_CQTD01_MASK                0x00000002U
#define SDMMC_CQRS10_CQTD01_POS                 1U
#define SDMMC_CQRS10_CQTD00_MASK                0x00000001U
#define SDMMC_CQRS10_CQTD00_POS                 0U

/* Bit fields of CQRS11 register */
#define SDMMC_CQRS11_CQTCN31_MASK               0x80000000U
#define SDMMC_CQRS11_CQTCN31_POS                31U
#define SDMMC_CQRS11_CQTCN30_MASK               0x40000000U
#define SDMMC_CQRS11_CQTCN30_POS                30U
#define SDMMC_CQRS11_CQTCN29_MASK               0x20000000U
#define SDMMC_CQRS11_CQTCN29_POS                29U
#define SDMMC_CQRS11_CQTCN28_MASK               0x10000000U
#define SDMMC_CQRS11_CQTCN28_POS                28U
#define SDMMC_CQRS11_CQTCN27_MASK               0x08000000U
#define SDMMC_CQRS11_CQTCN27_POS                27U
#define SDMMC_CQRS11_CQTCN26_MASK               0x04000000U
#define SDMMC_CQRS11_CQTCN26_POS                26U
#define SDMMC_CQRS11_CQTCN25_MASK               0x02000000U
#define SDMMC_CQRS11_CQTCN25_POS                25U
#define SDMMC_CQRS11_CQTCN24_MASK               0x01000000U
#define SDMMC_CQRS11_CQTCN24_POS                24U
#define SDMMC_CQRS11_CQTCN23_MASK               0x00800000U
#define SDMMC_CQRS11_CQTCN23_POS                23U
#define SDMMC_CQRS11_CQTCN22_MASK               0x00400000U
#define SDMMC_CQRS11_CQTCN22_POS                22U
#define SDMMC_CQRS11_CQTCN21_MASK               0x00200000U
#define SDMMC_CQRS11_CQTCN21_POS                21U
#define SDMMC_CQRS11_CQTCN20_MASK               0x00100000U
#define SDMMC_CQRS11_CQTCN20_POS                20U
#define SDMMC_CQRS11_CQTCN19_MASK               0x00080000U
#define SDMMC_CQRS11_CQTCN19_POS                19U
#define SDMMC_CQRS11_CQTCN18_MASK               0x00040000U
#define SDMMC_CQRS11_CQTCN18_POS                18U
#define SDMMC_CQRS11_CQTCN17_MASK               0x00020000U
#define SDMMC_CQRS11_CQTCN17_POS                17U
#define SDMMC_CQRS11_CQTCN16_MASK               0x00010000U
#define SDMMC_CQRS11_CQTCN16_POS                16U
#define SDMMC_CQRS11_CQTCN15_MASK               0x00008000U
#define SDMMC_CQRS11_CQTCN15_POS                15U
#define SDMMC_CQRS11_CQTCN14_MASK               0x00004000U
#define SDMMC_CQRS11_CQTCN14_POS                14U
#define SDMMC_CQRS11_CQTCN13_MASK               0x00002000U
#define SDMMC_CQRS11_CQTCN13_POS                13U
#define SDMMC_CQRS11_CQTCN12_MASK               0x00001000U
#define SDMMC_CQRS11_CQTCN12_POS                12U
#define SDMMC_CQRS11_CQTCN11_MASK               0x00000800U
#define SDMMC_CQRS11_CQTCN11_POS                11U
#define SDMMC_CQRS11_CQTCN10_MASK               0x00000400U
#define SDMMC_CQRS11_CQTCN10_POS                10U
#define SDMMC_CQRS11_CQTCN09_MASK               0x00000200U
#define SDMMC_CQRS11_CQTCN09_POS                9U
#define SDMMC_CQRS11_CQTCN08_MASK               0x00000100U
#define SDMMC_CQRS11_CQTCN08_POS                8U
#define SDMMC_CQRS11_CQTCN07_MASK               0x00000080U
#define SDMMC_CQRS11_CQTCN07_POS                7U
#define SDMMC_CQRS11_CQTCN06_MASK               0x00000040U
#define SDMMC_CQRS11_CQTCN06_POS                6U
#define SDMMC_CQRS11_CQTCN05_MASK               0x00000020U
#define SDMMC_CQRS11_CQTCN05_POS                5U
#define SDMMC_CQRS11_CQTCN04_MASK               0x00000010U
#define SDMMC_CQRS11_CQTCN04_POS                4U
#define SDMMC_CQRS11_CQTCN03_MASK               0x00000008U
#define SDMMC_CQRS11_CQTCN03_POS                3U
#define SDMMC_CQRS11_CQTCN02_MASK               0x00000004U
#define SDMMC_CQRS11_CQTCN02_POS                2U
#define SDMMC_CQRS11_CQTCN01_MASK               0x00000002U
#define SDMMC_CQRS11_CQTCN01_POS                1U
#define SDMMC_CQRS11_CQTCN00_MASK               0x00000001U
#define SDMMC_CQRS11_CQTCN00_POS                0U

/* Bit fields of CQRS12 register */
#define SDMMC_CQRS12_CQDQS_MASK                 0xFFFFFFFFU
#define SDMMC_CQRS12_CQDQS_POS                  0U

/* Bit fields of CQRS13 register */
#define SDMMC_CQRS13_CQDPT31_MASK               0x80000000U
#define SDMMC_CQRS13_CQDPT31_POS                31U
#define SDMMC_CQRS13_CQDPT30_MASK               0x40000000U
#define SDMMC_CQRS13_CQDPT30_POS                30U
#define SDMMC_CQRS13_CQDPT29_MASK               0x20000000U
#define SDMMC_CQRS13_CQDPT29_POS                29U
#define SDMMC_CQRS13_CQDPT28_MASK               0x10000000U
#define SDMMC_CQRS13_CQDPT28_POS                28U
#define SDMMC_CQRS13_CQDPT27_MASK               0x08000000U
#define SDMMC_CQRS13_CQDPT27_POS                27U
#define SDMMC_CQRS13_CQDPT26_MASK               0x04000000U
#define SDMMC_CQRS13_CQDPT26_POS                26U
#define SDMMC_CQRS13_CQDPT25_MASK               0x02000000U
#define SDMMC_CQRS13_CQDPT25_POS                25U
#define SDMMC_CQRS13_CQDPT24_MASK               0x01000000U
#define SDMMC_CQRS13_CQDPT24_POS                24U
#define SDMMC_CQRS13_CQDPT23_MASK               0x00800000U
#define SDMMC_CQRS13_CQDPT23_POS                23U
#define SDMMC_CQRS13_CQDPT22_MASK               0x00400000U
#define SDMMC_CQRS13_CQDPT22_POS                22U
#define SDMMC_CQRS13_CQDPT21_MASK               0x00200000U
#define SDMMC_CQRS13_CQDPT21_POS                21U
#define SDMMC_CQRS13_CQDPT20_MASK               0x00100000U
#define SDMMC_CQRS13_CQDPT20_POS                20U
#define SDMMC_CQRS13_CQDPT19_MASK               0x00080000U
#define SDMMC_CQRS13_CQDPT19_POS                19U
#define SDMMC_CQRS13_CQDPT18_MASK               0x00040000U
#define SDMMC_CQRS13_CQDPT18_POS                18U
#define SDMMC_CQRS13_CQDPT17_MASK               0x00020000U
#define SDMMC_CQRS13_CQDPT17_POS                17U
#define SDMMC_CQRS13_CQDPT16_MASK               0x00010000U
#define SDMMC_CQRS13_CQDPT16_POS                16U
#define SDMMC_CQRS13_CQDPT15_MASK               0x00008000U
#define SDMMC_CQRS13_CQDPT15_POS                15U
#define SDMMC_CQRS13_CQDPT14_MASK               0x00004000U
#define SDMMC_CQRS13_CQDPT14_POS                14U
#define SDMMC_CQRS13_CQDPT13_MASK               0x00002000U
#define SDMMC_CQRS13_CQDPT13_POS                13U
#define SDMMC_CQRS13_CQDPT12_MASK               0x00001000U
#define SDMMC_CQRS13_CQDPT12_POS                12U
#define SDMMC_CQRS13_CQDPT11_MASK               0x00000800U
#define SDMMC_CQRS13_CQDPT11_POS                11U
#define SDMMC_CQRS13_CQDPT10_MASK               0x00000400U
#define SDMMC_CQRS13_CQDPT10_POS                10U
#define SDMMC_CQRS13_CQDPT09_MASK               0x00000200U
#define SDMMC_CQRS13_CQDPT09_POS                9U
#define SDMMC_CQRS13_CQDPT08_MASK               0x00000100U
#define SDMMC_CQRS13_CQDPT08_POS                8U
#define SDMMC_CQRS13_CQDPT07_MASK               0x00000080U
#define SDMMC_CQRS13_CQDPT07_POS                7U
#define SDMMC_CQRS13_CQDPT06_MASK               0x00000040U
#define SDMMC_CQRS13_CQDPT06_POS                6U
#define SDMMC_CQRS13_CQDPT05_MASK               0x00000020U
#define SDMMC_CQRS13_CQDPT05_POS                5U
#define SDMMC_CQRS13_CQDPT04_MASK               0x00000010U
#define SDMMC_CQRS13_CQDPT04_POS                4U
#define SDMMC_CQRS13_CQDPT03_MASK               0x00000008U
#define SDMMC_CQRS13_CQDPT03_POS                3U
#define SDMMC_CQRS13_CQDPT02_MASK               0x00000004U
#define SDMMC_CQRS13_CQDPT02_POS                2U
#define SDMMC_CQRS13_CQDPT01_MASK               0x00000002U
#define SDMMC_CQRS13_CQDPT01_POS                1U
#define SDMMC_CQRS13_CQDPT00_MASK               0x00000001U
#define SDMMC_CQRS13_CQDPT00_POS                0U

/* Bit fields of CQRS14 register */
#define SDMMC_CQRS14_CQTC31_MASK                0x80000000U
#define SDMMC_CQRS14_CQTC31_POS                 31U
#define SDMMC_CQRS14_CQTC30_MASK                0x40000000U
#define SDMMC_CQRS14_CQTC30_POS                 30U
#define SDMMC_CQRS14_CQTC29_MASK                0x20000000U
#define SDMMC_CQRS14_CQTC29_POS                 29U
#define SDMMC_CQRS14_CQTC28_MASK                0x10000000U
#define SDMMC_CQRS14_CQTC28_POS                 28U
#define SDMMC_CQRS14_CQTC27_MASK                0x08000000U
#define SDMMC_CQRS14_CQTC27_POS                 27U
#define SDMMC_CQRS14_CQTC26_MASK                0x04000000U
#define SDMMC_CQRS14_CQTC26_POS                 26U
#define SDMMC_CQRS14_CQTC25_MASK                0x02000000U
#define SDMMC_CQRS14_CQTC25_POS                 25U
#define SDMMC_CQRS14_CQTC24_MASK                0x01000000U
#define SDMMC_CQRS14_CQTC24_POS                 24U
#define SDMMC_CQRS14_CQTC23_MASK                0x00800000U
#define SDMMC_CQRS14_CQTC23_POS                 23U
#define SDMMC_CQRS14_CQTC22_MASK                0x00400000U
#define SDMMC_CQRS14_CQTC22_POS                 22U
#define SDMMC_CQRS14_CQTC21_MASK                0x00200000U
#define SDMMC_CQRS14_CQTC21_POS                 21U
#define SDMMC_CQRS14_CQTC20_MASK                0x00100000U
#define SDMMC_CQRS14_CQTC20_POS                 20U
#define SDMMC_CQRS14_CQTC19_MASK                0x00080000U
#define SDMMC_CQRS14_CQTC19_POS                 19U
#define SDMMC_CQRS14_CQTC18_MASK                0x00040000U
#define SDMMC_CQRS14_CQTC18_POS                 18U
#define SDMMC_CQRS14_CQTC17_MASK                0x00020000U
#define SDMMC_CQRS14_CQTC17_POS                 17U
#define SDMMC_CQRS14_CQTC16_MASK                0x00010000U
#define SDMMC_CQRS14_CQTC16_POS                 16U
#define SDMMC_CQRS14_CQTC15_MASK                0x00008000U
#define SDMMC_CQRS14_CQTC15_POS                 15U
#define SDMMC_CQRS14_CQTC14_MASK                0x00004000U
#define SDMMC_CQRS14_CQTC14_POS                 14U
#define SDMMC_CQRS14_CQTC13_MASK                0x00002000U
#define SDMMC_CQRS14_CQTC13_POS                 13U
#define SDMMC_CQRS14_CQTC12_MASK                0x00001000U
#define SDMMC_CQRS14_CQTC12_POS                 12U
#define SDMMC_CQRS14_CQTC11_MASK                0x00000800U
#define SDMMC_CQRS14_CQTC11_POS                 11U
#define SDMMC_CQRS14_CQTC10_MASK                0x00000400U
#define SDMMC_CQRS14_CQTC10_POS                 10U
#define SDMMC_CQRS14_CQTC09_MASK                0x00000200U
#define SDMMC_CQRS14_CQTC09_POS                 9U
#define SDMMC_CQRS14_CQTC08_MASK                0x00000100U
#define SDMMC_CQRS14_CQTC08_POS                 8U
#define SDMMC_CQRS14_CQTC07_MASK                0x00000080U
#define SDMMC_CQRS14_CQTC07_POS                 7U
#define SDMMC_CQRS14_CQTC06_MASK                0x00000040U
#define SDMMC_CQRS14_CQTC06_POS                 6U
#define SDMMC_CQRS14_CQTC05_MASK                0x00000020U
#define SDMMC_CQRS14_CQTC05_POS                 5U
#define SDMMC_CQRS14_CQTC04_MASK                0x00000010U
#define SDMMC_CQRS14_CQTC04_POS                 4U
#define SDMMC_CQRS14_CQTC03_MASK                0x00000008U
#define SDMMC_CQRS14_CQTC03_POS                 3U
#define SDMMC_CQRS14_CQTC02_MASK                0x00000004U
#define SDMMC_CQRS14_CQTC02_POS                 2U
#define SDMMC_CQRS14_CQTC01_MASK                0x00000002U
#define SDMMC_CQRS14_CQTC01_POS                 1U
#define SDMMC_CQRS14_CQTC00_MASK                0x00000001U
#define SDMMC_CQRS14_CQTC00_POS                 0U

/* Bit fields of CQRS16 register */
#define SDMMC_CQRS16_CQSSCBC_MASK               0x000F0000U
#define SDMMC_CQRS16_CQSSCBC_POS                16U
#define SDMMC_CQRS16_CQSSCIT_MASK               0x0000FFFFU
#define SDMMC_CQRS16_CQSSCIT_POS                0U

/* Bit fields of CQRS17 register */
#define SDMMC_CQRS17_CQSQSR_MASK                0x0000FFFFU
#define SDMMC_CQRS17_CQSQSR_POS                 0U

/* Bit fields of CQRS18 register */
#define SDMMC_CQRS18_CQDCLR_MASK                0xFFFFFFFFU
#define SDMMC_CQRS18_CQDCLR_POS                 0U

/* Bit fields of CQRS20 register */
#define SDMMC_CQRS20_CQRMEM_MASK                0xFFFFFFFFU
#define SDMMC_CQRS20_CQRMEM_POS                 0U

/* Bit fields of CQRS21 register */
#define SDMMC_CQRS21_CQDTEFV_MASK               0x80000000U
#define SDMMC_CQRS21_CQDTEFV_POS                31U
#define SDMMC_CQRS21_CQDTETID_MASK              0x1F000000U
#define SDMMC_CQRS21_CQDTETID_POS               24U
#define SDMMC_CQRS21_CQDTECI_MASK               0x003F0000U
#define SDMMC_CQRS21_CQDTECI_POS                16U
#define SDMMC_CQRS21_CQRMEFV_MASK               0x00008000U
#define SDMMC_CQRS21_CQRMEFV_POS                15U
#define SDMMC_CQRS21_CQRMETID_MASK              0x00001F00U
#define SDMMC_CQRS21_CQRMETID_POS               8U
#define SDMMC_CQRS21_CQRMECI_MASK               0x0000003FU
#define SDMMC_CQRS21_CQRMECI_POS                0U

/* Bit fields of CQRS22 register */
#define SDMMC_CQRS22_CQLCRI_MASK                0x0000003FU
#define SDMMC_CQRS22_CQLCRI_POS                 0U

/* Bit fields of CQRS23 register */
#define SDMMC_CQRS23_CQLCRA_MASK                0xFFFFFFFFU
#define SDMMC_CQRS23_CQLCRA_POS                 0U

#endif
