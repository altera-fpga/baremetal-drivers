/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_spi_reg.h
 *
 * SPI register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SPI_REG_H__
#define __SOCFPGA_SPI_REG_H__

#define GET_BASE_ADDRESS(instance)    ((uint32_t)(0x10DA4000U + \
    (instance * 0x1000U)))

#define CLK_PERPLL                                  0x10D1007CU
#define CLK_PERPLL_EN                               (0x0U + CLK_PERPLL)
#define CLK_SPIM0_SHIFT                             9U
#define CLK_SPIM1_SHIFT                             11U

#define RST_PER0                                    0x10D11024U
#define RST_SPI_SHIFT                               17U

/* Control Register 0U */
#define SPI_CTRLR0                                  0x0000U
/* Control Register 1U */
#define SPI_CTRLR1                                  0x0004U
/* SSI Enable Register */
#define SPI_SSIENR                                  0x0008U
/* Microwire Control Register */
#define SPI_MWCR                                    0x000CU
/* Slave Enable Register */
#define SPI_SER                                     0x0010U
/* Baud Rate Select */
#define SPI_BAUDR                                   0x0014U
/* Transmit FIFO Threshold Level */
#define SPI_TXFTLR                                  0x0018U
/* Receive FIFO Threshold Level */
#define SPI_RXFTLR                                  0x001CU
/* Transmit FIFO Level Register */
#define SPI_TXFLR                                   0x0020U
/* Receive FIFO Level Register */
#define SPI_RXFLR                                   0x0024U
/* Status Register */
#define SPI_SR                                      0x0028U
/* Interrupt Mask Register */
#define SPI_IMR                                     0x002CU
/* Interrupt Status Register */
#define SPI_ISR                                     0x0030U
/* Raw Interrupt Status Register */
#define SPI_RISR                                    0x0034U
/* Transmit FIFO Overflow Interrupt Clear Register Register */
#define SPI_TXOICR                                  0x0038U
/* Receive FIFO Overflow Interrupt Clear Register */
#define SPI_RXOICR                                  0x003CU
/* Receive FIFO Underflow Interrupt Clear Register */
#define SPI_RXUICR                                  0x0040U
/* Multi-Master Interrupt Clear Register */
#define SPI_MSTICR                                  0x0044U
/* Interrupt Clear Register */
#define SPI_ICR                                     0x0048U
/* DMA Control Register */
#define SPI_DMACR                                   0x004CU
/* DMA Transmit Data Level */
#define SPI_DMATDLR                                 0x0050U
/* DMA Receive Data Level */
#define SPI_DMARDLR                                 0x0054U
/* Identification Register */
#define SPI_IDR                                     0x0058U
/* SSI_VERSION_ID */
#define SPI_SSI_VERSION_ID                          0x005CU
/* DW_apb_ssi Data Register */
#define SPI_DR0                                     0x0060U
/* DW_apb_ssi Data Register */
#define SPI_DR1                                     0x0064U
/* DW_apb_ssi Data Register */
#define SPI_DR2                                     0x0068U
/* DW_apb_ssi Data Register */
#define SPI_DR3                                     0x006CU
/* DW_apb_ssi Data Register */
#define SPI_DR4                                     0x0070U
/* DW_apb_ssi Data Register */
#define SPI_DR5                                     0x0074U
/* DW_apb_ssi Data Register */
#define SPI_DR6                                     0x0078U
/* DW_apb_ssi Data Register */
#define SPI_DR7                                     0x007CU
/* DW_apb_ssi Data Register */
#define SPI_DR8                                     0x0080U
/* DW_apb_ssi Data Register */
#define SPI_DR9                                     0x0084U
/* DW_apb_ssi Data Register */
#define SPI_DR10                                    0x0088U
/* DW_apb_ssi Data Register */
#define SPI_DR11                                    0x008CU
/* DW_apb_ssi Data Register */
#define SPI_DR12                                    0x0090U
/* DW_apb_ssi Data Register */
#define SPI_DR13                                    0x0094U
/* DW_apb_ssi Data Register */
#define SPI_DR14                                    0x0098U
/* DW_apb_ssi Data Register */
#define SPI_DR15                                    0x009CU
/* DW_apb_ssi Data Register */
#define SPI_DR16                                    0x00A0U
/* DW_apb_ssi Data Register */
#define SPI_DR17                                    0x00A4U
/* DW_apb_ssi Data Register */
#define SPI_DR18                                    0x00A8U
/* DW_apb_ssi Data Register */
#define SPI_DR19                                    0x00ACU
/* DW_apb_ssi Data Register */
#define SPI_DR20                                    0x00B0U
/* DW_apb_ssi Data Register */
#define SPI_DR21                                    0x00B4U
/* DW_apb_ssi Data Register */
#define SPI_DR22                                    0x00B8U
/* DW_apb_ssi Data Register */
#define SPI_DR23                                    0x00BCU
/* DW_apb_ssi Data Register */
#define SPI_DR24                                    0x00C0U
/* DW_apb_ssi Data Register */
#define SPI_DR25                                    0x00C4U
/* DW_apb_ssi Data Register */
#define SPI_DR26                                    0x00C8U
/* DW_apb_ssi Data Register */
#define SPI_DR27                                    0x00CCU
/* DW_apb_ssi Data Register */
#define SPI_DR28                                    0x00D0U
/* DW_apb_ssi Data Register */
#define SPI_DR29                                    0x00D4U
/* DW_apb_ssi Data Register */
#define SPI_DR30                                    0x00D8U
/* DW_apb_ssi Data Register */
#define SPI_DR31                                    0x00DCU
/* DW_apb_ssi Data Register */
#define SPI_DR32                                    0x00E0U
/* DW_apb_ssi Data Register */
#define SPI_DR33                                    0x00E4U
/* DW_apb_ssi Data Register */
#define SPI_DR34                                    0x00E8U
/* DW_apb_ssi Data Register */
#define SPI_DR35                                    0x00ECU
/* RX Sample Delay */
#define SPI_RX_SAMPLE_DLY                           0x00F0U
/* RSVD_1 - Reserved address location */
#define SPI_RSVD_1                                  0x00F8U
/* RSVD_2 - Reserved address location */
#define SPI_RSVD_2                                  0x00FCU

/* Bit fields of CTRLR0 register */
#define SPI_CTRLR0_SPI_FRF_MASK                     0x00600000U
#define SPI_CTRLR0_SPI_FRF_POS                      21U
#define SPI_CTRLR0_DFS_32_MASK                      0x001F0000U
#define SPI_CTRLR0_DFS_32_POS                       16U
#define SPI_CTRLR0_CFS_MASK                         0x0000F000U
#define SPI_CTRLR0_CFS_POS                          12U
#define SPI_CTRLR0_SRL_MASK                         0x00000800U
#define SPI_CTRLR0_SRL_POS                          11U
#define SPI_CTRLR0_TMOD_MASK                        0x00000300U
#define SPI_CTRLR0_TMOD_POS                         8U
#define SPI_CTRLR0_SCPOL_MASK                       0x00000080U
#define SPI_CTRLR0_SCPOL_POS                        7U
#define SPI_CTRLR0_SCPH_MASK                        0x00000040U
#define SPI_CTRLR0_SCPH_POS                         6U
#define SPI_CTRLR0_FRF_MASK                         0x00000030U
#define SPI_CTRLR0_FRF_POS                          4U
#define SPI_CTRLR0_DFS_MASK                         0x0000000FU
#define SPI_CTRLR0_DFS_POS                          0U

/* Bit fields of CTRLR1 register */
#define SPI_CTRLR1_NDF_MASK                         0x0000FFFFU
#define SPI_CTRLR1_NDF_POS                          0U

/* Bit fields of SSIENR register */
#define SPI_SSIENR_SSI_EN_MASK                      0x00000001U
#define SPI_SSIENR_SSI_EN_POS                       0U

/* Bit fields of MWCR register */
#define SPI_MWCR_MHS_MASK                           0x00000004U
#define SPI_MWCR_MHS_POS                            2U
#define SPI_MWCR_MDD_MASK                           0x00000002U
#define SPI_MWCR_MDD_POS                            1U
#define SPI_MWCR_MWMOD_MASK                         0x00000001U
#define SPI_MWCR_MWMOD_POS                          0U

/* Bit fields of SER register */
#define SPI_SER_SER_MASK                            0x0000000FU
#define SPI_SER_SER_POS                             0U

/* Bit fields of BAUDR register */
#define SPI_BAUDR_SCKDV_MASK                        0x0000FFFFU
#define SPI_BAUDR_SCKDV_POS                         0U

/* Bit fields of TXFTLR register */
#define SPI_TXFTLR_TFT_MASK                         0x000000FFU
#define SPI_TXFTLR_TFT_POS                          0U

/* Bit fields of RXFTLR register */
#define SPI_RXFTLR_RFT_MASK                         0x000000FFU
#define SPI_RXFTLR_RFT_POS                          0U

/* Bit fields of TXFLR register */
#define SPI_TXFLR_TXTFL_MASK                        0x000001FFU
#define SPI_TXFLR_TXTFL_POS                         0U

/* Bit fields of RXFLR register */
#define SPI_RXFLR_RXTFL_MASK                        0x000001FFU
#define SPI_RXFLR_RXTFL_POS                         0U

/* Bit fields of SR register */
#define SPI_SR_DCOL_MASK                            0x00000040U
#define SPI_SR_DCOL_POS                             6U
#define SPI_SR_RFF_MASK                             0x00000010U
#define SPI_SR_RFF_POS                              4U
#define SPI_SR_RFNE_MASK                            0x00000008U
#define SPI_SR_RFNE_POS                             3U
#define SPI_SR_TFE_MASK                             0x00000004U
#define SPI_SR_TFE_POS                              2U
#define SPI_SR_TFNF_MASK                            0x00000002U
#define SPI_SR_TFNF_POS                             1U
#define SPI_SR_BUSY_MASK                            0x00000001U
#define SPI_SR_BUSY_POS                             0U

/* Bit fields of IMR register */
#define SPI_IMR_MSTIM_MASK                          0x00000020U
#define SPI_IMR_MSTIM_POS                           5U
#define SPI_IMR_RXFIM_MASK                          0x00000010U
#define SPI_IMR_RXFIM_POS                           4U
#define SPI_IMR_RXOIM_MASK                          0x00000008U
#define SPI_IMR_RXOIM_POS                           3U
#define SPI_IMR_RXUIM_MASK                          0x00000004U
#define SPI_IMR_RXUIM_POS                           2U
#define SPI_IMR_TXOIM_MASK                          0x00000002U
#define SPI_IMR_TXOIM_POS                           1U
#define SPI_IMR_TXEIM_MASK                          0x00000001U
#define SPI_IMR_TXEIM_POS                           0U

/* Bit fields of ISR register */
#define SPI_ISR_MSTIS_MASK                          0x00000020U
#define SPI_ISR_MSTIS_POS                           5U
#define SPI_ISR_RXFIS_MASK                          0x00000010U
#define SPI_ISR_RXFIS_POS                           4U
#define SPI_ISR_RXOIS_MASK                          0x00000008U
#define SPI_ISR_RXOIS_POS                           3U
#define SPI_ISR_RXUIS_MASK                          0x00000004U
#define SPI_ISR_RXUIS_POS                           2U
#define SPI_ISR_TXOIS_MASK                          0x00000002U
#define SPI_ISR_TXOIS_POS                           1U
#define SPI_ISR_TXEIS_MASK                          0x00000001U
#define SPI_ISR_TXEIS_POS                           0U

/* Bit fields of RISR register */
#define SPI_RISR_MSTIR_MASK                         0x00000020U
#define SPI_RISR_MSTIR_POS                          5U
#define SPI_RISR_RXFIR_MASK                         0x00000010U
#define SPI_RISR_RXFIR_POS                          4U
#define SPI_RISR_RXOIR_MASK                         0x00000008U
#define SPI_RISR_RXOIR_POS                          3U
#define SPI_RISR_RXUIR_MASK                         0x00000004U
#define SPI_RISR_RXUIR_POS                          2U
#define SPI_RISR_TXOIR_MASK                         0x00000002U
#define SPI_RISR_TXOIR_POS                          1U
#define SPI_RISR_TXEIR_MASK                         0x00000001U
#define SPI_RISR_TXEIR_POS                          0U

/* Bit fields of TXOICR register */
#define SPI_TXOICR_TXOICR_MASK                      0x00000001U
#define SPI_TXOICR_TXOICR_POS                       0U

/* Bit fields of RXOICR register */
#define SPI_RXOICR_RXOICR_MASK                      0x00000001U
#define SPI_RXOICR_RXOICR_POS                       0U

/* Bit fields of RXUICR register */
#define SPI_RXUICR_RXUICR_MASK                      0x00000001U
#define SPI_RXUICR_RXUICR_POS                       0U

/* Bit fields of MSTICR register */
#define SPI_MSTICR_MSTICR_MASK                      0x00000001U
#define SPI_MSTICR_MSTICR_POS                       0U

/* Bit fields of ICR register */
#define SPI_ICR_ICR_MASK                            0x00000001U
#define SPI_ICR_ICR_POS                             0U

/* Bit fields of DMACR register */
#define SPI_DMACR_TDMAE_MASK                        0x00000002U
#define SPI_DMACR_TDMAE_POS                         1U
#define SPI_DMACR_RDMAE_MASK                        0x00000001U
#define SPI_DMACR_RDMAE_POS                         0U

/* Bit fields of DMATDLR register */
#define SPI_DMATDLR_DMATDL_MASK                     0x000000FFU
#define SPI_DMATDLR_DMATDL_POS                      0U

/* Bit fields of DMARDLR register */
#define SPI_DMARDLR_DMARDL_MASK                     0x000000FFU
#define SPI_DMARDLR_DMARDL_POS                      0U

/* Bit fields of IDR register */
#define SPI_IDR_IDCODE_MASK                         0xFFFFFFFFU
#define SPI_IDR_IDCODE_POS                          0U

/* Bit fields of SSI_VERSION_ID register */
#define SPI_SSI_VERSION_ID_SSI_COMP_VERSION_MASK    0xFFFFFFFFU
#define SPI_SSI_VERSION_ID_SSI_COMP_VERSION_POS     0U

/* Bit fields of DR0 register */
#define SPI_DR0_DR0_MASK                            0xFFFFFFFFU
#define SPI_DR0_DR0_POS                             0U

/* Bit fields of DR1 register */
#define SPI_DR1_DR1_MASK                            0xFFFFFFFFU
#define SPI_DR1_DR1_POS                             0U

/* Bit fields of DR2 register */
#define SPI_DR2_DR2_MASK                            0xFFFFFFFFU
#define SPI_DR2_DR2_POS                             0U

/* Bit fields of DR3 register */
#define SPI_DR3_DR3_MASK                            0xFFFFFFFFU
#define SPI_DR3_DR3_POS                             0U

/* Bit fields of DR4 register */
#define SPI_DR4_DR4_MASK                            0xFFFFFFFFU
#define SPI_DR4_DR4_POS                             0U

/* Bit fields of DR5 register */
#define SPI_DR5_DR5_MASK                            0xFFFFFFFFU
#define SPI_DR5_DR5_POS                             0U

/* Bit fields of DR6 register */
#define SPI_DR6_DR6_MASK                            0xFFFFFFFFU
#define SPI_DR6_DR6_POS                             0U

/* Bit fields of DR7 register */
#define SPI_DR7_DR7_MASK                            0xFFFFFFFFU
#define SPI_DR7_DR7_POS                             0U

/* Bit fields of DR8 register */
#define SPI_DR8_DR8_MASK                            0xFFFFFFFFU
#define SPI_DR8_DR8_POS                             0U

/* Bit fields of DR9 register */
#define SPI_DR9_DR9_MASK                            0xFFFFFFFFU
#define SPI_DR9_DR9_POS                             0U

/* Bit fields of DR10 register */
#define SPI_DR10_DR10_MASK                          0xFFFFFFFFU
#define SPI_DR10_DR10_POS                           0U

/* Bit fields of DR11 register */
#define SPI_DR11_DR11_MASK                          0xFFFFFFFFU
#define SPI_DR11_DR11_POS                           0U

/* Bit fields of DR12 register */
#define SPI_DR12_DR12_MASK                          0xFFFFFFFFU
#define SPI_DR12_DR12_POS                           0U

/* Bit fields of DR13 register */
#define SPI_DR13_DR13_MASK                          0xFFFFFFFFU
#define SPI_DR13_DR13_POS                           0U

/* Bit fields of DR14 register */
#define SPI_DR14_DR14_MASK                          0xFFFFFFFFU
#define SPI_DR14_DR14_POS                           0U

/* Bit fields of DR15 register */
#define SPI_DR15_DR15_MASK                          0xFFFFFFFFU
#define SPI_DR15_DR15_POS                           0U

/* Bit fields of DR16 register */
#define SPI_DR16_DR16_MASK                          0xFFFFFFFFU
#define SPI_DR16_DR16_POS                           0U

/* Bit fields of DR17 register */
#define SPI_DR17_DR17_MASK                          0xFFFFFFFFU
#define SPI_DR17_DR17_POS                           0U

/* Bit fields of DR18 register */
#define SPI_DR18_DR18_MASK                          0xFFFFFFFFU
#define SPI_DR18_DR18_POS                           0U

/* Bit fields of DR19 register */
#define SPI_DR19_DR19_MASK                          0xFFFFFFFFU
#define SPI_DR19_DR19_POS                           0U

/* Bit fields of DR20 register */
#define SPI_DR20_DR20_MASK                          0xFFFFFFFFU
#define SPI_DR20_DR20_POS                           0U

/* Bit fields of DR21 register */
#define SPI_DR21_DR21_MASK                          0xFFFFFFFFU
#define SPI_DR21_DR21_POS                           0U

/* Bit fields of DR22 register */
#define SPI_DR22_DR22_MASK                          0xFFFFFFFFU
#define SPI_DR22_DR22_POS                           0U

/* Bit fields of DR23 register */
#define SPI_DR23_DR23_MASK                          0xFFFFFFFFU
#define SPI_DR23_DR23_POS                           0U

/* Bit fields of DR24 register */
#define SPI_DR24_DR24_MASK                          0xFFFFFFFFU
#define SPI_DR24_DR24_POS                           0U

/* Bit fields of DR25 register */
#define SPI_DR25_DR25_MASK                          0xFFFFFFFFU
#define SPI_DR25_DR25_POS                           0U

/* Bit fields of DR26 register */
#define SPI_DR26_DR26_MASK                          0xFFFFFFFFU
#define SPI_DR26_DR26_POS                           0U

/* Bit fields of DR27 register */
#define SPI_DR27_DR27_MASK                          0xFFFFFFFFU
#define SPI_DR27_DR27_POS                           0U

/* Bit fields of DR28 register */
#define SPI_DR28_DR28_MASK                          0xFFFFFFFFU
#define SPI_DR28_DR28_POS                           0U

/* Bit fields of DR29 register */
#define SPI_DR29_DR29_MASK                          0xFFFFFFFFU
#define SPI_DR29_DR29_POS                           0U

/* Bit fields of DR30 register */
#define SPI_DR30_DR30_MASK                          0xFFFFFFFFU
#define SPI_DR30_DR30_POS                           0U

/* Bit fields of DR31 register */
#define SPI_DR31_DR31_MASK                          0xFFFFFFFFU
#define SPI_DR31_DR31_POS                           0U

/* Bit fields of DR32 register */
#define SPI_DR32_DR32_MASK                          0xFFFFFFFFU
#define SPI_DR32_DR32_POS                           0U

/* Bit fields of DR33 register */
#define SPI_DR33_DR33_MASK                          0xFFFFFFFFU
#define SPI_DR33_DR33_POS                           0U

/* Bit fields of DR34 register */
#define SPI_DR34_DR34_MASK                          0xFFFFFFFFU
#define SPI_DR34_DR34_POS                           0U

/* Bit fields of DR35 register */
#define SPI_DR35_DR35_MASK                          0xFFFFFFFFU
#define SPI_DR35_DR35_POS                           0U

/* Bit fields of RX_SAMPLE_DLY register */
#define SPI_RX_SAMPLE_DLY_RSD_MASK                  0x000000FFU
#define SPI_RX_SAMPLE_DLY_RSD_POS                   0U

/* Bit fields of RSVD_1 register */

/* Bit fields of RSVD_2 register */



#endif /* __SOCFPGA_SPI_REG_H__ */
