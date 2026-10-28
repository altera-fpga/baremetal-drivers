/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sys_mngr_reg_plat.h
 *
 * Agilex3 platform System Manager register definitions for the SoCFPGA
 * bare-metal software stack.
 *
 */

#ifndef SOCFPGA_SYS_MNGR_REG_PLAT_H
#define SOCFPGA_SYS_MNGR_REG_PLAT_H

/* Agilex3 System Manager base address. */
#define SOCFPGA_SYS_MNGR_BASE_ADDR 0x10D12000U

/* Backward-compatible alias. */
#define SYS_MNGR_BASE_ADDR SOCFPGA_SYS_MNGR_BASE_ADDR


/* Silicon ID1 Register */
#define SYS_MNGR_SILICONID1 \
                                                                             0x0000
/* Silicon ID2 Register */
#define SYS_MNGR_SILICONID2 \
                                                                             0x0004
/* L4 Watchdog Debug Register */
#define SYS_MNGR_WDDBG \
                                                                             0x0008
/* mpu_status */
#define SYS_MNGR_MPU_STATUS \
                                                                             0x0010
/* sdmmc_l3master */
#define SYS_MNGR_SDMMC_L3MASTER \
                                                                             0x002C
/* NAND L3 Master AxCACHE Register */
#define SYS_MNGR_NAND_L3MASTER \
                                                                             0x0034
/* USB L3 Master HPROT AHB-Lite Register */
#define SYS_MNGR_USB0_L3MASTER \
                                                                             0x0038
/* usb1_l3master */
#define SYS_MNGR_USB1_L3MASTER \
                                                                             0x003C
/* TSN L3 Master AxCACHE Register */
#define SYS_MNGR_TSN_GLOBAL \
                                                                             0x0040
/* Control Register */
#define SYS_MNGR_TSN0 \
                                                                             0x0044
/* Control Register */
#define SYS_MNGR_TSN1 \
                                                                             0x0048
/* Control Register */
#define SYS_MNGR_TSN2 \
                                                                             0x004C
/* tsn0_ace */
#define SYS_MNGR_TSN0_ACE \
                                                                             0x0050
/* tsn1_ace */
#define SYS_MNGR_TSN1_ACE \
                                                                             0x0054
/* tsn2_ace */
#define SYS_MNGR_TSN2_ACE \
                                                                             0x0058
/* fpga_bridge_ctrl */
#define SYS_MNGR_FPGA_BRIDGE_CTRL \
                                                                             0x005C
/* FPGA interface Individual Enable Register */
#define SYS_MNGR_FPGAINTF_EN_1 \
                                                                             0x0068
/* FPGA interface Individual Enable Register */
#define SYS_MNGR_FPGAINTF_EN_2 \
                                                                             0x006C
/* FPGA interface Individual Enable Register */
#define SYS_MNGR_FPGAINTF_EN_3 \
                                                                             0x0070
/* dmac0_l3master */
#define SYS_MNGR_DMAC0_L3MASTER \
                                                                             0x0074
/* etr_l3master */
#define SYS_MNGR_ETR_L3MASTER \
                                                                             0x0078
/* dmac1_l3master */
#define SYS_MNGR_DMAC1_L3MASTER \
                                                                             0x007C
/* sec_ctrl_slt */
#define SYS_MNGR_SEC_CTRL_SLT \
                                                                             0x0080
/* osc_trim */
#define SYS_MNGR_OSC_TRIM \
                                                                             0x0084
/* dmac0_ctrl_status_reg */
#define SYS_MNGR_DMAC0_CTRL_STATUS_REG \
                                                                             0x0088
/* dmac1_ctrl_status_reg */
#define SYS_MNGR_DMAC1_CTRL_STATUS_REG \
                                                                             0x008C
/* ecc_intmask_value */
#define SYS_MNGR_ECC_INTMASK_VALUE \
                                                                             0x0090
/* ECC interrupt mask Set register */
#define SYS_MNGR_ECC_INTMASK_SET \
                                                                             0x0094
/* ECC interrupt mask Clear register */
#define SYS_MNGR_ECC_INTMASK_CLR \
                                                                             0x0098
/* ecc_intstatus_serr */
#define SYS_MNGR_ECC_INTSTATUS_SERR \
                                                                             0x009C
/* ecc_intstatus_derr */
#define SYS_MNGR_ECC_INTSTATUS_DERR \
                                                                             0x00A0
/* noc_timeout */
#define SYS_MNGR_NOC_TIMEOUT \
                                                                             0x00C0
/* noc_idlestatus */
#define SYS_MNGR_NOC_IDLESTATUS \
                                                                             0x00D4
/* fpga2soc_ctrl */
#define SYS_MNGR_FPGA2SOC_CTRL \
                                                                             0x00D8
/* fpga_config */
#define SYS_MNGR_FPGA_CONFIG \
                                                                             0x00DC
/* gpo */
#define SYS_MNGR_GPO \
                                                                             0x00E4
/* gpi */
#define SYS_MNGR_GPI \
                                                                             0x00E8
/* mpu */
#define SYS_MNGR_MPU \
                                                                             0x00F0
/* sdm_hps_spare */
#define SYS_MNGR_SDM_HPS_SPARE \
                                                                             0x00F4
/* hps_sdm_spare */
#define SYS_MNGR_HPS_SDM_SPARE \
                                                                             0x00F8
/* dfi_interface_cfg */
#define SYS_MNGR_DFI_INTERFACE_CFG \
                                                                             0x00FC
/* nand_dd_ctrl */
#define SYS_MNGR_NAND_DD_CTRL \
                                                                             0x0100
/* nand_phy_ctrl_reg */
#define SYS_MNGR_NAND_PHY_CTRL_REG \
                                                                             0x0104
/* nand_phy_tsel_reg */
#define SYS_MNGR_NAND_PHY_TSEL_REG \
                                                                             0x0108
/* nand_phy_dq_timing_reg */
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG \
                                                                             0x010C
/* phy_dqs_timing_reg */
#define SYS_MNGR_PHY_DQS_TIMING_REG \
                                                                             0x0110
/* nand_phy_gate_lpbk_ctrl_reg */
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG \
                                                                             0x0114
/* nand_phy_dll_master_ctrl_reg */
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG \
                                                                             0x0118
/* nand_phy_dll_slave_ctrl_reg */
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG \
                                                                             0x011C
/* nand_dd_default_setting_reg0 */
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG0 \
                                                                             0x0120
/* nand_dd_default_setting_reg1 */
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1 \
                                                                             0x0124
/* nand_dd_status_reg */
#define SYS_MNGR_NAND_DD_STATUS_REG \
                                                                             0x0128
/* nand_dd_id_low_reg */
#define SYS_MNGR_NAND_DD_ID_LOW_REG \
                                                                             0x012C
/* nand_dd_id_high_reg */
#define SYS_MNGR_NAND_DD_ID_HIGH_REG \
                                                                             0x0130
/* nand_write_prot_en_reg */
#define SYS_MNGR_NAND_WRITE_PROT_EN_REG \
                                                                             0x0134
/* sdmmc_cmd_queue_setting_reg */
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG \
                                                                             0x0138
/* i3c_slv_pid_low */
#define SYS_MNGR_I3C_SLV_PID_LOW \
                                                                             0x013C
/* i3c_slv_pid_high */
#define SYS_MNGR_I3C_SLV_PID_HIGH \
                                                                             0x0140
/* i3c_slv_ctrl_0 */
#define SYS_MNGR_I3C_SLV_CTRL_0 \
                                                                             0x0144
/* i3c_slv_ctrl_1 */
#define SYS_MNGR_I3C_SLV_CTRL_1 \
                                                                             0x0148
/* f2s_bridge_ctrl */
#define SYS_MNGR_F2S_BRIDGE_CTRL \
                                                                             0x014C
/* dma_tbu_stash_ctrl_reg_0_dma0 */
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0 \
                                                                             0x0150
/* dma_tbu_stash_ctrl_reg_0_dma1 */
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1 \
                                                                             0x0154
/* sdm_tbu_stash_ctrl_reg_1_sdm */
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM \
                                                                             0x0158
/* io_tbu_stash_ctrl_reg_2_usb2 */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2 \
                                                                             0x015C
/* io_tbu_stash_ctrl_reg_2_usb3 */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3 \
                                                                             0x0160
/* io_tbu_stash_ctrl_reg_2_sdmmc */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC \
                                                                             0x0164
/* io_tbu_stash_ctrl_reg_2_nand */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND \
                                                                             0x0168
/* io_tbu_stash_ctrl_reg_2_etr */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR \
                                                                             0x016C
/* tsn_tbu_stash_ctrl_reg_3_tsn0 */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0 \
                                                                             0x0170
/* tsn_tbu_stash_ctrl_reg_3_tsn1 */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1 \
                                                                             0x0174
/* tsn_tbu_stash_ctrl_reg_3_tsn2 */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2 \
                                                                             0x0178
/* dma_tbu_stream_ctrl_reg_0_dma0 */
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0 \
                                                                             0x017C
/* dma_tbu_stream_ctrl_reg_0_dma1 */
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1 \
                                                                             0x0180
/* sdm_tbu_stream_ctrl_reg_1_sdm */
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM \
                                                                             0x0184
/* io_tbu_stream_ctrl_reg_2_usb2 */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2 \
                                                                             0x0188
/* io_tbu_stream_ctrl_reg_2_usb3 */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3 \
                                                                             0x018C
/* io_tbu_stream_ctrl_reg_2_sdmmc */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC \
                                                                             0x0190
/* io_tbu_stream_ctrl_reg_2_nand */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND \
                                                                             0x0194
/* io_tbu_stream_ctrl_reg_2_etr */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR \
                                                                             0x0198
/* tsn_tbu_stream_ctrl_reg_3_tsn0 */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0 \
                                                                             0x019C
/* tsn_tbu_stream_ctrl_reg_3_tsn1 */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1 \
                                                                             0x01A0
/* tsn_tbu_stream_ctrl_reg_3_tsn2 */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2 \
                                                                             0x01A4
/* dma_tbu_stream_id_Ax_reg_0_dma0 */
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA0 \
                                                                             0x01A8
/* dma_tbu_stream_id_Ax_reg_0_dma1 */
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA1 \
                                                                             0x01AC
/* sdm_tbu_stream_id_Ax_reg_1_sdm */
#define SYS_MNGR_SDM_TBU_STREAM_ID_AX_REG_1_SDM \
                                                                             0x01B0
/* io_tbu_stream_id_Ax_reg_2_usb2 */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB2 \
                                                                             0x01B4
/* io_tbu_stream_id_Ax_reg_2_usb3 */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB3 \
                                                                             0x01B8
/* io_tbu_stream_id_Ax_reg_2_sdmmc */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_SDMMC \
                                                                             0x01BC
/* io_tbu_stream_id_Ax_reg_2_nand */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_NAND \
                                                                             0x01C0
/* io_tbu_stream_id_Ax_reg_2_etr */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_ETR \
                                                                             0x01C4
/* tsn_tbu_stream_id_Ax_reg_3_tsn0 */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN0 \
                                                                             0x01C8
/* tsn_tbu_stream_id_Ax_reg_3_tsn1 */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN1 \
                                                                             0x01CC
/* tsn_tbu_stream_id_Ax_reg_3_tsn2 */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN2 \
                                                                             0x01D0
/* usb3_misc_ctrl_reg0 */
#define SYS_MNGR_USB3_MISC_CTRL_REG0 \
                                                                             0x01F0
/* usb3_misc_ctrl_reg1 */
#define SYS_MNGR_USB3_MISC_CTRL_REG1 \
                                                                             0x01F4
/* boot_scratch_cold0 */
#define SYS_MNGR_BOOT_SCRATCH_COLD0 \
                                                                             0x0200
/* boot_scratch_cold1 */
#define SYS_MNGR_BOOT_SCRATCH_COLD1 \
                                                                             0x0204
/* boot_scratch_cold2 */
#define SYS_MNGR_BOOT_SCRATCH_COLD2 \
                                                                             0x0208
/* boot_scratch_cold3 */
#define SYS_MNGR_BOOT_SCRATCH_COLD3 \
                                                                             0x020C
/* boot_scratch_cold4 */
#define SYS_MNGR_BOOT_SCRATCH_COLD4 \
                                                                             0x0210
/* boot_scratch_cold5 */
#define SYS_MNGR_BOOT_SCRATCH_COLD5 \
                                                                             0x0214
/* boot_scratch_cold6 */
#define SYS_MNGR_BOOT_SCRATCH_COLD6 \
                                                                             0x0218
/* boot_scratch_cold7 */
#define SYS_MNGR_BOOT_SCRATCH_COLD7 \
                                                                             0x021C
/* boot_scratch_cold8 */
#define SYS_MNGR_BOOT_SCRATCH_COLD8 \
                                                                             0x0220
/* boot_scratch_cold9 */
#define SYS_MNGR_BOOT_SCRATCH_COLD9 \
                                                                             0x0224
/* mpfe_config */
#define SYS_MNGR_MPFE_CONFIG \
                                                                             0x0228
/* mpfe_status */
#define SYS_MNGR_MPFE_STATUS \
                                                                             0x022C
/* boot_scratch_warm0 */
#define SYS_MNGR_BOOT_SCRATCH_WARM0 \
                                                                             0x0230
/* boot_scratch_warm1 */
#define SYS_MNGR_BOOT_SCRATCH_WARM1 \
                                                                             0x0234
/* boot_scratch_warm2 */
#define SYS_MNGR_BOOT_SCRATCH_WARM2 \
                                                                             0x0238
/* boot_scratch_warm3 */
#define SYS_MNGR_BOOT_SCRATCH_WARM3 \
                                                                             0x023C
/* boot_scratch_warm4 */
#define SYS_MNGR_BOOT_SCRATCH_WARM4 \
                                                                             0x0240
/* boot_scratch_warm5 */
#define SYS_MNGR_BOOT_SCRATCH_WARM5 \
                                                                             0x0244
/* boot_scratch_warm6 */
#define SYS_MNGR_BOOT_SCRATCH_WARM6 \
                                                                             0x0248
/* boot_scratch_warm7 */
#define SYS_MNGR_BOOT_SCRATCH_WARM7 \
                                                                             0x024C
/* boot_scratch_warm8 */
#define SYS_MNGR_BOOT_SCRATCH_WARM8 \
                                                                             0x0250
/* boot_scratch_warm9 */
#define SYS_MNGR_BOOT_SCRATCH_WARM9 \
                                                                             0x0254
/* boot_scratch_por0 */
#define SYS_MNGR_BOOT_SCRATCH_POR0 \
                                                                             0x0258
/* boot_scratch_por1 */
#define SYS_MNGR_BOOT_SCRATCH_POR1 \
                                                                             0x025C
/* boot_scratch_por2 */
#define SYS_MNGR_BOOT_SCRATCH_POR2 \
                                                                             0x0260
/* boot_scratch_por3 */
#define SYS_MNGR_BOOT_SCRATCH_POR3 \
                                                                             0x0264
/* boot_scratch_por4 */
#define SYS_MNGR_BOOT_SCRATCH_POR4 \
                                                                             0x0268
/* boot_scratch_por5 */
#define SYS_MNGR_BOOT_SCRATCH_POR5 \
                                                                             0x026C
/* boot_scratch_por6 */
#define SYS_MNGR_BOOT_SCRATCH_POR6 \
                                                                             0x0270
/* boot_scratch_por7 */
#define SYS_MNGR_BOOT_SCRATCH_POR7 \
                                                                             0x0274
/* boot_scratch_por8 */
#define SYS_MNGR_BOOT_SCRATCH_POR8 \
                                                                             0x0278
/* boot_scratch_por9 */
#define SYS_MNGR_BOOT_SCRATCH_POR9 \
                                                                             0x027C
/* sdm_be_awaddr_remap */
#define SYS_MNGR_SDM_BE_AWADDR_REMAP \
                                                                             0x0280
/* sdm_be_araddr_remap */
#define SYS_MNGR_SDM_BE_ARADDR_REMAP \
                                                                             0x0284

/* Bit fields of siliconid1 register */
#define SYS_MNGR_SILICONID1_ID_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_SILICONID1_ID_POS \
                                                                             16
#define SYS_MNGR_SILICONID1_REV_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_SILICONID1_REV_POS                                          0

/* Bit fields of siliconid2 register */
#define SYS_MNGR_SILICONID2_RSV_MASK \
                                                                             0xFFFFFFF0
#define SYS_MNGR_SILICONID2_RSV_POS                                          4
#define SYS_MNGR_SILICONID2_DEVICE_REVISION_MASK \
                                                                             0x0000000F
#define SYS_MNGR_SILICONID2_DEVICE_REVISION_POS                              0

/* Bit fields of wddbg register */
#define SYS_MNGR_WDDBG_MODE_4_MASK \
                                                                             0xF0000000
#define SYS_MNGR_WDDBG_MODE_4_POS \
                                                                             28
#define SYS_MNGR_WDDBG_MODE_3_MASK \
                                                                             0x0F000000
#define SYS_MNGR_WDDBG_MODE_3_POS \
                                                                             24
#define SYS_MNGR_WDDBG_MODE_2_MASK \
                                                                             0x000F0000
#define SYS_MNGR_WDDBG_MODE_2_POS \
                                                                             16
#define SYS_MNGR_WDDBG_MODE_1_MASK \
                                                                             0x00000F00
#define SYS_MNGR_WDDBG_MODE_1_POS                                            8
#define SYS_MNGR_WDDBG_MODE_0_MASK \
                                                                             0x0000000F
#define SYS_MNGR_WDDBG_MODE_0_POS                                            0

/* Bit fields of mpu_status register */
#define SYS_MNGR_MPU_STATUS_UNCORRERR_MASK \
                                                                             0x0000001F
#define SYS_MNGR_MPU_STATUS_UNCORRERR_POS                                    0

/* Bit fields of sdmmc_l3master register */
#define SYS_MNGR_SDMMC_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_SDMMC_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_SDMMC_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0000C000
#define SYS_MNGR_SDMMC_L3MASTER_ARDOMAIN_POS \
                                                                             14
#define SYS_MNGR_SDMMC_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00003000
#define SYS_MNGR_SDMMC_L3MASTER_AWDOMAIN_POS \
                                                                             12
#define SYS_MNGR_SDMMC_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_SDMMC_L3MASTER_AWUSER_POS                                   0

/* Bit fields of nand_l3master register */
#define SYS_MNGR_NAND_L3MASTER_ARCACHE_0_MASK \
                                                                             0xF0000000
#define SYS_MNGR_NAND_L3MASTER_ARCACHE_0_POS \
                                                                             28
#define SYS_MNGR_NAND_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0C000000
#define SYS_MNGR_NAND_L3MASTER_ARDOMAIN_POS \
                                                                             26
#define SYS_MNGR_NAND_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_NAND_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_NAND_L3MASTER_AWCACHE_0_MASK \
                                                                             0x0000F000
#define SYS_MNGR_NAND_L3MASTER_AWCACHE_0_POS \
                                                                             12
#define SYS_MNGR_NAND_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00000C00
#define SYS_MNGR_NAND_L3MASTER_AWDOMAIN_POS \
                                                                             10
#define SYS_MNGR_NAND_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_NAND_L3MASTER_AWUSER_POS                                    0

/* Bit fields of usb0_l3master register */
#define SYS_MNGR_USB0_L3MASTER_HAUSER22_13_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_USB0_L3MASTER_HAUSER22_13_POS \
                                                                             16
#define SYS_MNGR_USB0_L3MASTER_HAUSER7_6_MASK \
                                                                             0x00003000
#define SYS_MNGR_USB0_L3MASTER_HAUSER7_6_POS \
                                                                             12
#define SYS_MNGR_USB0_L3MASTER_HAUSER_1_MASK \
                                                                             0x00000200
#define SYS_MNGR_USB0_L3MASTER_HAUSER_1_POS                                  9
#define SYS_MNGR_USB0_L3MASTER_HAUSER_0_MASK \
                                                                             0x00000100
#define SYS_MNGR_USB0_L3MASTER_HAUSER_0_POS                                  8
#define SYS_MNGR_USB0_L3MASTER_HPROT_MASK \
                                                                             0x0000000F
#define SYS_MNGR_USB0_L3MASTER_HPROT_POS                                     0

/* Bit fields of usb1_l3master register */
#define SYS_MNGR_USB1_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_USB1_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_USB1_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0000C000
#define SYS_MNGR_USB1_L3MASTER_ARDOMAIN_POS \
                                                                             14
#define SYS_MNGR_USB1_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00003000
#define SYS_MNGR_USB1_L3MASTER_AWDOMAIN_POS \
                                                                             12
#define SYS_MNGR_USB1_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_USB1_L3MASTER_AWUSER_POS                                    0

/* Bit fields of tsn_global register */
#define SYS_MNGR_TSN_GLOBAL_PTP_CLK_SEL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_GLOBAL_PTP_CLK_SEL_POS                                  0

/* Bit fields of tsn0 register */
#define SYS_MNGR_TSN0_AXI_DISABLE_MASK \
                                                                             0x80000000
#define SYS_MNGR_TSN0_AXI_DISABLE_POS \
                                                                             31
#define SYS_MNGR_TSN0_SBD_DATA_ENDIANNESS_MASK \
                                                                             0x40000000
#define SYS_MNGR_TSN0_SBD_DATA_ENDIANNESS_POS \
                                                                             30
#define SYS_MNGR_TSN0_EMAC0_DBGBUS_SEL_MASK \
                                                                             0x00070000
#define SYS_MNGR_TSN0_EMAC0_DBGBUS_SEL_POS \
                                                                             16
#define SYS_MNGR_TSN0_PTP_REF_SEL_MASK \
                                                                             0x00000100
#define SYS_MNGR_TSN0_PTP_REF_SEL_POS                                        8
#define SYS_MNGR_TSN0_PPSTRIG_SEL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN0_PPSTRIG_SEL_POS                                        4
#define SYS_MNGR_TSN0_PHY_INTF_SEL_MASK \
                                                                             0x00000003
#define SYS_MNGR_TSN0_PHY_INTF_SEL_POS                                       0

/* Bit fields of tsn1 register */
#define SYS_MNGR_TSN1_AXI_DISABLE_MASK \
                                                                             0x80000000
#define SYS_MNGR_TSN1_AXI_DISABLE_POS \
                                                                             31
#define SYS_MNGR_TSN1_SBD_DATA_ENDIANNESS_MASK \
                                                                             0x40000000
#define SYS_MNGR_TSN1_SBD_DATA_ENDIANNESS_POS \
                                                                             30
#define SYS_MNGR_TSN1_EMAC1_DBGBUS_SEL_MASK \
                                                                             0x00070000
#define SYS_MNGR_TSN1_EMAC1_DBGBUS_SEL_POS \
                                                                             16
#define SYS_MNGR_TSN1_PTP_REF_SEL_MASK \
                                                                             0x00000100
#define SYS_MNGR_TSN1_PTP_REF_SEL_POS                                        8
#define SYS_MNGR_TSN1_PPSTRIG_SEL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN1_PPSTRIG_SEL_POS                                        4
#define SYS_MNGR_TSN1_PHY_INTF_SEL_MASK \
                                                                             0x00000003
#define SYS_MNGR_TSN1_PHY_INTF_SEL_POS                                       0

/* Bit fields of tsn2 register */
#define SYS_MNGR_TSN2_AXI_DISABLE_MASK \
                                                                             0x80000000
#define SYS_MNGR_TSN2_AXI_DISABLE_POS \
                                                                             31
#define SYS_MNGR_TSN2_SBD_DATA_ENDIANNESS_MASK \
                                                                             0x40000000
#define SYS_MNGR_TSN2_SBD_DATA_ENDIANNESS_POS \
                                                                             30
#define SYS_MNGR_TSN2_EMAC2_DBGBUS_SEL_MASK \
                                                                             0x00070000
#define SYS_MNGR_TSN2_EMAC2_DBGBUS_SEL_POS \
                                                                             16
#define SYS_MNGR_TSN2_PTP_REF_SEL_MASK \
                                                                             0x00000100
#define SYS_MNGR_TSN2_PTP_REF_SEL_POS                                        8
#define SYS_MNGR_TSN2_PPSTRIG_SEL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN2_PPSTRIG_SEL_POS                                        4
#define SYS_MNGR_TSN2_PHY_INTF_SEL_MASK \
                                                                             0x00000003
#define SYS_MNGR_TSN2_PHY_INTF_SEL_POS                                       0

/* Bit fields of tsn0_ace register */
#define SYS_MNGR_TSN0_ACE_AWSID_MASK \
                                                                             0x3FF00000
#define SYS_MNGR_TSN0_ACE_AWSID_POS \
                                                                             20
#define SYS_MNGR_TSN0_ACE_ARSID_MASK \
                                                                             0x0003FF00
#define SYS_MNGR_TSN0_ACE_ARSID_POS                                          8

/* Bit fields of tsn1_ace register */
#define SYS_MNGR_TSN1_ACE_AWSID_MASK \
                                                                             0x3FF00000
#define SYS_MNGR_TSN1_ACE_AWSID_POS \
                                                                             20
#define SYS_MNGR_TSN1_ACE_ARSID_MASK \
                                                                             0x0003FF00
#define SYS_MNGR_TSN1_ACE_ARSID_POS                                          8

/* Bit fields of tsn2_ace register */
#define SYS_MNGR_TSN2_ACE_AWSID_MASK \
                                                                             0x3FF00000
#define SYS_MNGR_TSN2_ACE_AWSID_POS \
                                                                             20
#define SYS_MNGR_TSN2_ACE_ARSID_MASK \
                                                                             0x0003FF00
#define SYS_MNGR_TSN2_ACE_ARSID_POS                                          8

/* Bit fields of fpga_bridge_ctrl register */
#define SYS_MNGR_FPGA_BRIDGE_CTRL_LWSOC2FPGA_READY_LATENCY_ENABLE_MASK \
                                                                             0x00000002
#define SYS_MNGR_FPGA_BRIDGE_CTRL_LWSOC2FPGA_READY_LATENCY_ENABLE_POS        1
#define SYS_MNGR_FPGA_BRIDGE_CTRL_SOC2FPGA_READY_LATENCY_ENABLE_MASK \
                                                                             0x00000001
#define SYS_MNGR_FPGA_BRIDGE_CTRL_SOC2FPGA_READY_LATENCY_ENABLE_POS          0

/* Bit fields of fpgaintf_en_1 register */
#define SYS_MNGR_FPGAINTF_EN_1_CTMTRIGGER_MASK \
                                                                             0x01000000
#define SYS_MNGR_FPGAINTF_EN_1_CTMTRIGGER_POS \
                                                                             24
#define SYS_MNGR_FPGAINTF_EN_1_STMEVENT_MASK \
                                                                             0x00010000
#define SYS_MNGR_FPGAINTF_EN_1_STMEVENT_POS \
                                                                             16
#define SYS_MNGR_FPGAINTF_EN_1_DBGAPB_MASK \
                                                                             0x00000100
#define SYS_MNGR_FPGAINTF_EN_1_DBGAPB_POS                                    8
#define SYS_MNGR_FPGAINTF_EN_1_TRACEOUT_MASK \
                                                                             0x00000010
#define SYS_MNGR_FPGAINTF_EN_1_TRACEOUT_POS                                  4
#define SYS_MNGR_FPGAINTF_EN_1_TRACEIN_MASK \
                                                                             0x00000001
#define SYS_MNGR_FPGAINTF_EN_1_TRACEIN_POS                                   0

/* Bit fields of fpgaintf_en_2 register */
#define SYS_MNGR_FPGAINTF_EN_2_SPIM_1_MASK \
                                                                             0x01000000
#define SYS_MNGR_FPGAINTF_EN_2_SPIM_1_POS \
                                                                             24
#define SYS_MNGR_FPGAINTF_EN_2_SPIM_0_MASK \
                                                                             0x00010000
#define SYS_MNGR_FPGAINTF_EN_2_SPIM_0_POS \
                                                                             16
#define SYS_MNGR_FPGAINTF_EN_2_SDMMC_MASK \
                                                                             0x00000100
#define SYS_MNGR_FPGAINTF_EN_2_SDMMC_POS                                     8
#define SYS_MNGR_FPGAINTF_EN_2_NAND_MASK \
                                                                             0x00000010
#define SYS_MNGR_FPGAINTF_EN_2_NAND_POS                                      4

/* Bit fields of fpgaintf_en_3 register */
#define SYS_MNGR_FPGAINTF_EN_3_TSN_2_MASK \
                                                                             0x00010000
#define SYS_MNGR_FPGAINTF_EN_3_TSN_2_POS \
                                                                             16
#define SYS_MNGR_FPGAINTF_EN_3_TSN_1_MASK \
                                                                             0x00000100
#define SYS_MNGR_FPGAINTF_EN_3_TSN_1_POS                                     8
#define SYS_MNGR_FPGAINTF_EN_3_TSN_0_MASK \
                                                                             0x00000001
#define SYS_MNGR_FPGAINTF_EN_3_TSN_0_POS                                     0

/* Bit fields of dmac0_l3master register */
#define SYS_MNGR_DMAC0_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_DMAC0_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_DMAC0_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0000C000
#define SYS_MNGR_DMAC0_L3MASTER_ARDOMAIN_POS \
                                                                             14
#define SYS_MNGR_DMAC0_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00003000
#define SYS_MNGR_DMAC0_L3MASTER_AWDOMAIN_POS \
                                                                             12
#define SYS_MNGR_DMAC0_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_DMAC0_L3MASTER_AWUSER_POS                                   0

/* Bit fields of etr_l3master register */
#define SYS_MNGR_ETR_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_ETR_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_ETR_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0000C000
#define SYS_MNGR_ETR_L3MASTER_ARDOMAIN_POS \
                                                                             14
#define SYS_MNGR_ETR_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00003000
#define SYS_MNGR_ETR_L3MASTER_AWDOMAIN_POS \
                                                                             12
#define SYS_MNGR_ETR_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_ETR_L3MASTER_AWUSER_POS                                     0

/* Bit fields of dmac1_l3master register */
#define SYS_MNGR_DMAC1_L3MASTER_ARUSER_MASK \
                                                                             0x03FF0000
#define SYS_MNGR_DMAC1_L3MASTER_ARUSER_POS \
                                                                             16
#define SYS_MNGR_DMAC1_L3MASTER_ARDOMAIN_MASK \
                                                                             0x0000C000
#define SYS_MNGR_DMAC1_L3MASTER_ARDOMAIN_POS \
                                                                             14
#define SYS_MNGR_DMAC1_L3MASTER_AWDOMAIN_MASK \
                                                                             0x00003000
#define SYS_MNGR_DMAC1_L3MASTER_AWDOMAIN_POS \
                                                                             12
#define SYS_MNGR_DMAC1_L3MASTER_AWUSER_MASK \
                                                                             0x000003FF
#define SYS_MNGR_DMAC1_L3MASTER_AWUSER_POS                                   0

/* Bit fields of sec_ctrl_slt register */
#define SYS_MNGR_SEC_CTRL_SLT_VAL_MASK \
                                                                             0x00000001
#define SYS_MNGR_SEC_CTRL_SLT_VAL_POS                                        0

/* Bit fields of osc_trim register */
#define SYS_MNGR_OSC_TRIM_VAL_MASK \
                                                                             0x000000FF
#define SYS_MNGR_OSC_TRIM_VAL_POS                                            0

/* Bit fields of dmac0_ctrl_status_reg register */
#define SYS_MNGR_DMAC0_CTRL_STATUS_REG_MODE_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMAC0_CTRL_STATUS_REG_MODE_POS                              0

/* Bit fields of dmac1_ctrl_status_reg register */
#define SYS_MNGR_DMAC1_CTRL_STATUS_REG_MODE_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMAC1_CTRL_STATUS_REG_MODE_POS                              0

/* Bit fields of ecc_intmask_value register */
#define SYS_MNGR_ECC_INTMASK_VALUE_DMA1_MASK \
                                                                             0x00040000
#define SYS_MNGR_ECC_INTMASK_VALUE_DMA1_POS \
                                                                             18
#define SYS_MNGR_ECC_INTMASK_VALUE_DDR1_MASK \
                                                                             0x00020000
#define SYS_MNGR_ECC_INTMASK_VALUE_DDR1_POS \
                                                                             17
#define SYS_MNGR_ECC_INTMASK_VALUE_DDR0_MASK \
                                                                             0x00010000
#define SYS_MNGR_ECC_INTMASK_VALUE_DDR0_POS \
                                                                             16
#define SYS_MNGR_ECC_INTMASK_VALUE_SDMMCB_MASK \
                                                                             0x00008000
#define SYS_MNGR_ECC_INTMASK_VALUE_SDMMCB_POS \
                                                                             15
#define SYS_MNGR_ECC_INTMASK_VALUE_SDMMCA_MASK \
                                                                             0x00004000
#define SYS_MNGR_ECC_INTMASK_VALUE_SDMMCA_POS \
                                                                             14
#define SYS_MNGR_ECC_INTMASK_VALUE_NAND_RD_MASK \
                                                                             0x00002000
#define SYS_MNGR_ECC_INTMASK_VALUE_NAND_RD_POS \
                                                                             13
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM2_MASK \
                                                                             0x00001000
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM2_POS \
                                                                             12
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM1_MASK \
                                                                             0x00000800
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM1_POS \
                                                                             11
#define SYS_MNGR_ECC_INTMASK_VALUE_DMA0_MASK \
                                                                             0x00000400
#define SYS_MNGR_ECC_INTMASK_VALUE_DMA0_POS \
                                                                             10
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN2_TX_MASK \
                                                                             0x00000200
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN2_TX_POS                               9
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN2_RX_MASK \
                                                                             0x00000100
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN2_RX_POS                               8
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN1_TX_MASK \
                                                                             0x00000080
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN1_TX_POS                               7
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN1_RX_MASK \
                                                                             0x00000040
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN1_RX_POS                               6
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN0_TX_MASK \
                                                                             0x00000020
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN0_TX_POS                               5
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN0_RX_MASK \
                                                                             0x00000010
#define SYS_MNGR_ECC_INTMASK_VALUE_TSN0_RX_POS                               4
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM0_MASK \
                                                                             0x00000008
#define SYS_MNGR_ECC_INTMASK_VALUE_USB31_RAM0_POS                            3
#define SYS_MNGR_ECC_INTMASK_VALUE_USB0_MASK \
                                                                             0x00000004
#define SYS_MNGR_ECC_INTMASK_VALUE_USB0_POS                                  2
#define SYS_MNGR_ECC_INTMASK_VALUE_OCRAM_MASK \
                                                                             0x00000002
#define SYS_MNGR_ECC_INTMASK_VALUE_OCRAM_POS                                 1

/* Bit fields of ecc_intmask_set register */
#define SYS_MNGR_ECC_INTMASK_SET_DMA1_MASK \
                                                                             0x00040000
#define SYS_MNGR_ECC_INTMASK_SET_DMA1_POS \
                                                                             18
#define SYS_MNGR_ECC_INTMASK_SET_DDR1_MASK \
                                                                             0x00020000
#define SYS_MNGR_ECC_INTMASK_SET_DDR1_POS \
                                                                             17
#define SYS_MNGR_ECC_INTMASK_SET_DDR0_MASK \
                                                                             0x00010000
#define SYS_MNGR_ECC_INTMASK_SET_DDR0_POS \
                                                                             16
#define SYS_MNGR_ECC_INTMASK_SET_SDMMCB_MASK \
                                                                             0x00008000
#define SYS_MNGR_ECC_INTMASK_SET_SDMMCB_POS \
                                                                             15
#define SYS_MNGR_ECC_INTMASK_SET_SDMMCA_MASK \
                                                                             0x00004000
#define SYS_MNGR_ECC_INTMASK_SET_SDMMCA_POS \
                                                                             14
#define SYS_MNGR_ECC_INTMASK_SET_NAND_RD_MASK \
                                                                             0x00002000
#define SYS_MNGR_ECC_INTMASK_SET_NAND_RD_POS \
                                                                             13
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM2_MASK \
                                                                             0x00001000
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM2_POS \
                                                                             12
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM1_MASK \
                                                                             0x00000800
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM1_POS \
                                                                             11
#define SYS_MNGR_ECC_INTMASK_SET_DMA0_MASK \
                                                                             0x00000400
#define SYS_MNGR_ECC_INTMASK_SET_DMA0_POS \
                                                                             10
#define SYS_MNGR_ECC_INTMASK_SET_TSN2_TX_MASK \
                                                                             0x00000200
#define SYS_MNGR_ECC_INTMASK_SET_TSN2_TX_POS                                 9
#define SYS_MNGR_ECC_INTMASK_SET_TSN2_RX_MASK \
                                                                             0x00000100
#define SYS_MNGR_ECC_INTMASK_SET_TSN2_RX_POS                                 8
#define SYS_MNGR_ECC_INTMASK_SET_TSN1_TX_MASK \
                                                                             0x00000080
#define SYS_MNGR_ECC_INTMASK_SET_TSN1_TX_POS                                 7
#define SYS_MNGR_ECC_INTMASK_SET_TSN1_RX_MASK \
                                                                             0x00000040
#define SYS_MNGR_ECC_INTMASK_SET_TSN1_RX_POS                                 6
#define SYS_MNGR_ECC_INTMASK_SET_TSN0_TX_MASK \
                                                                             0x00000020
#define SYS_MNGR_ECC_INTMASK_SET_TSN0_TX_POS                                 5
#define SYS_MNGR_ECC_INTMASK_SET_TSN0_RX_MASK \
                                                                             0x00000010
#define SYS_MNGR_ECC_INTMASK_SET_TSN0_RX_POS                                 4
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM0_MASK \
                                                                             0x00000008
#define SYS_MNGR_ECC_INTMASK_SET_USB31_RAM0_POS                              3
#define SYS_MNGR_ECC_INTMASK_SET_USB0_MASK \
                                                                             0x00000004
#define SYS_MNGR_ECC_INTMASK_SET_USB0_POS                                    2
#define SYS_MNGR_ECC_INTMASK_SET_OCRAM_MASK \
                                                                             0x00000002
#define SYS_MNGR_ECC_INTMASK_SET_OCRAM_POS                                   1

/* Bit fields of ecc_intmask_clr register */
#define SYS_MNGR_ECC_INTMASK_CLR_DMA1_MASK \
                                                                             0x00040000
#define SYS_MNGR_ECC_INTMASK_CLR_DMA1_POS \
                                                                             18
#define SYS_MNGR_ECC_INTMASK_CLR_DDR1_MASK \
                                                                             0x00020000
#define SYS_MNGR_ECC_INTMASK_CLR_DDR1_POS \
                                                                             17
#define SYS_MNGR_ECC_INTMASK_CLR_DDR0_MASK \
                                                                             0x00010000
#define SYS_MNGR_ECC_INTMASK_CLR_DDR0_POS \
                                                                             16
#define SYS_MNGR_ECC_INTMASK_CLR_SDMMCB_MASK \
                                                                             0x00008000
#define SYS_MNGR_ECC_INTMASK_CLR_SDMMCB_POS \
                                                                             15
#define SYS_MNGR_ECC_INTMASK_CLR_SDMMCA_MASK \
                                                                             0x00004000
#define SYS_MNGR_ECC_INTMASK_CLR_SDMMCA_POS \
                                                                             14
#define SYS_MNGR_ECC_INTMASK_CLR_NAND_RD_MASK \
                                                                             0x00002000
#define SYS_MNGR_ECC_INTMASK_CLR_NAND_RD_POS \
                                                                             13
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM2_MASK \
                                                                             0x00001000
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM2_POS \
                                                                             12
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM1_MASK \
                                                                             0x00000800
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM1_POS \
                                                                             11
#define SYS_MNGR_ECC_INTMASK_CLR_DMA0_MASK \
                                                                             0x00000400
#define SYS_MNGR_ECC_INTMASK_CLR_DMA0_POS \
                                                                             10
#define SYS_MNGR_ECC_INTMASK_CLR_TSN2_TX_MASK \
                                                                             0x00000200
#define SYS_MNGR_ECC_INTMASK_CLR_TSN2_TX_POS                                 9
#define SYS_MNGR_ECC_INTMASK_CLR_TSN2_RX_MASK \
                                                                             0x00000100
#define SYS_MNGR_ECC_INTMASK_CLR_TSN2_RX_POS                                 8
#define SYS_MNGR_ECC_INTMASK_CLR_TSN1_TX_MASK \
                                                                             0x00000080
#define SYS_MNGR_ECC_INTMASK_CLR_TSN1_TX_POS                                 7
#define SYS_MNGR_ECC_INTMASK_CLR_TSN1_RX_MASK \
                                                                             0x00000040
#define SYS_MNGR_ECC_INTMASK_CLR_TSN1_RX_POS                                 6
#define SYS_MNGR_ECC_INTMASK_CLR_TSN0_TX_MASK \
                                                                             0x00000020
#define SYS_MNGR_ECC_INTMASK_CLR_TSN0_TX_POS                                 5
#define SYS_MNGR_ECC_INTMASK_CLR_TSN0_RX_MASK \
                                                                             0x00000010
#define SYS_MNGR_ECC_INTMASK_CLR_TSN0_RX_POS                                 4
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM0_MASK \
                                                                             0x00000008
#define SYS_MNGR_ECC_INTMASK_CLR_USB31_RAM0_POS                              3
#define SYS_MNGR_ECC_INTMASK_CLR_USB0_MASK \
                                                                             0x00000004
#define SYS_MNGR_ECC_INTMASK_CLR_USB0_POS                                    2
#define SYS_MNGR_ECC_INTMASK_CLR_OCRAM_MASK \
                                                                             0x00000002
#define SYS_MNGR_ECC_INTMASK_CLR_OCRAM_POS                                   1

/* Bit fields of ecc_intstatus_serr register */
#define SYS_MNGR_ECC_INTSTATUS_SERR_DMA1_MASK \
                                                                             0x00040000
#define SYS_MNGR_ECC_INTSTATUS_SERR_DMA1_POS \
                                                                             18
#define SYS_MNGR_ECC_INTSTATUS_SERR_DDR1_MASK \
                                                                             0x00020000
#define SYS_MNGR_ECC_INTSTATUS_SERR_DDR1_POS \
                                                                             17
#define SYS_MNGR_ECC_INTSTATUS_SERR_DDR0_MASK \
                                                                             0x00010000
#define SYS_MNGR_ECC_INTSTATUS_SERR_DDR0_POS \
                                                                             16
#define SYS_MNGR_ECC_INTSTATUS_SERR_SDMMCB_MASK \
                                                                             0x00008000
#define SYS_MNGR_ECC_INTSTATUS_SERR_SDMMCB_POS \
                                                                             15
#define SYS_MNGR_ECC_INTSTATUS_SERR_SDMMCA_MASK \
                                                                             0x00004000
#define SYS_MNGR_ECC_INTSTATUS_SERR_SDMMCA_POS \
                                                                             14
#define SYS_MNGR_ECC_INTSTATUS_SERR_NAND_RD_MASK \
                                                                             0x00002000
#define SYS_MNGR_ECC_INTSTATUS_SERR_NAND_RD_POS \
                                                                             13
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM2_MASK \
                                                                             0x00001000
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM2_POS \
                                                                             12
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM1_MASK \
                                                                             0x00000800
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM1_POS \
                                                                             11
#define SYS_MNGR_ECC_INTSTATUS_SERR_DMA0_MASK \
                                                                             0x00000400
#define SYS_MNGR_ECC_INTSTATUS_SERR_DMA0_POS \
                                                                             10
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN2_TX_MASK \
                                                                             0x00000200
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN2_TX_POS                              9
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN2_RX_MASK \
                                                                             0x00000100
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN2_RX_POS                              8
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN1_TX_MASK \
                                                                             0x00000080
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN1_TX_POS                              7
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN1_RX_MASK \
                                                                             0x00000040
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN1_RX_POS                              6
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN0_TX_MASK \
                                                                             0x00000020
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN0_TX_POS                              5
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN0_RX_MASK \
                                                                             0x00000010
#define SYS_MNGR_ECC_INTSTATUS_SERR_TSN0_RX_POS                              4
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM0_MASK \
                                                                             0x00000008
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB31_RAM0_POS                           3
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB0_MASK \
                                                                             0x00000004
#define SYS_MNGR_ECC_INTSTATUS_SERR_USB0_POS                                 2
#define SYS_MNGR_ECC_INTSTATUS_SERR_OCRAM_MASK \
                                                                             0x00000002
#define SYS_MNGR_ECC_INTSTATUS_SERR_OCRAM_POS                                1

/* Bit fields of ecc_intstatus_derr register */
#define SYS_MNGR_ECC_INTSTATUS_DERR_DMA1_MASK \
                                                                             0x00040000
#define SYS_MNGR_ECC_INTSTATUS_DERR_DMA1_POS \
                                                                             18
#define SYS_MNGR_ECC_INTSTATUS_DERR_DDR1_MASK \
                                                                             0x00020000
#define SYS_MNGR_ECC_INTSTATUS_DERR_DDR1_POS \
                                                                             17
#define SYS_MNGR_ECC_INTSTATUS_DERR_DDR0_MASK \
                                                                             0x00010000
#define SYS_MNGR_ECC_INTSTATUS_DERR_DDR0_POS \
                                                                             16
#define SYS_MNGR_ECC_INTSTATUS_DERR_SDMMCB_MASK \
                                                                             0x00008000
#define SYS_MNGR_ECC_INTSTATUS_DERR_SDMMCB_POS \
                                                                             15
#define SYS_MNGR_ECC_INTSTATUS_DERR_SDMMCA_MASK \
                                                                             0x00004000
#define SYS_MNGR_ECC_INTSTATUS_DERR_SDMMCA_POS \
                                                                             14
#define SYS_MNGR_ECC_INTSTATUS_DERR_NAND_RD_MASK \
                                                                             0x00002000
#define SYS_MNGR_ECC_INTSTATUS_DERR_NAND_RD_POS \
                                                                             13
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM2_MASK \
                                                                             0x00001000
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM2_POS \
                                                                             12
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM1_MASK \
                                                                             0x00000800
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM1_POS \
                                                                             11
#define SYS_MNGR_ECC_INTSTATUS_DERR_DMA0_MASK \
                                                                             0x00000400
#define SYS_MNGR_ECC_INTSTATUS_DERR_DMA0_POS \
                                                                             10
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN2_TX_MASK \
                                                                             0x00000200
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN2_TX_POS                              9
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN2_RX_MASK \
                                                                             0x00000100
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN2_RX_POS                              8
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN1_TX_MASK \
                                                                             0x00000080
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN1_TX_POS                              7
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN1_RX_MASK \
                                                                             0x00000040
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN1_RX_POS                              6
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN0_TX_MASK \
                                                                             0x00000020
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN0_TX_POS                              5
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN0_RX_MASK \
                                                                             0x00000010
#define SYS_MNGR_ECC_INTSTATUS_DERR_TSN0_RX_POS                              4
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM0_MASK \
                                                                             0x00000008
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB31_RAM0_POS                           3
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB0_MASK \
                                                                             0x00000004
#define SYS_MNGR_ECC_INTSTATUS_DERR_USB0_POS                                 2
#define SYS_MNGR_ECC_INTSTATUS_DERR_OCRAM_MASK \
                                                                             0x00000002
#define SYS_MNGR_ECC_INTSTATUS_DERR_OCRAM_POS                                1

/* Bit fields of noc_timeout register */
#define SYS_MNGR_NOC_TIMEOUT_EN_MASK \
                                                                             0x00000001
#define SYS_MNGR_NOC_TIMEOUT_EN_POS                                          0

/* Bit fields of noc_idlestatus register */
#define SYS_MNGR_NOC_IDLESTATUS_LWSOC2FPGA_MASK \
                                                                             0x00000010
#define SYS_MNGR_NOC_IDLESTATUS_LWSOC2FPGA_POS                               4
#define SYS_MNGR_NOC_IDLESTATUS_SOC2FPGA_MASK \
                                                                             0x00000001
#define SYS_MNGR_NOC_IDLESTATUS_SOC2FPGA_POS                                 0

/* Bit fields of fpga2soc_ctrl register */
#define SYS_MNGR_FPGA2SOC_CTRL_ALLOW_SECURE_MASK \
                                                                             0x00000001
#define SYS_MNGR_FPGA2SOC_CTRL_ALLOW_SECURE_POS                              0

/* Bit fields of fpga_config register */
#define SYS_MNGR_FPGA_CONFIG_EARLY_USERMODE_MASK \
                                                                             0x00000002
#define SYS_MNGR_FPGA_CONFIG_EARLY_USERMODE_POS                              1
#define SYS_MNGR_FPGA_CONFIG_FPGA_COMPLETE_MASK \
                                                                             0x00000001
#define SYS_MNGR_FPGA_CONFIG_FPGA_COMPLETE_POS                               0

/* Bit fields of gpo register */
#define SYS_MNGR_GPO_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_GPO_VAL_POS                                                 0

/* Bit fields of gpi register */
#define SYS_MNGR_GPI_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_GPI_VAL_POS                                                 0

/* Bit fields of mpu register */
#define SYS_MNGR_MPU_MPU_CFGSDISABLE_MASK \
                                                                             0x00000001
#define SYS_MNGR_MPU_MPU_CFGSDISABLE_POS                                     0

/* Bit fields of sdm_hps_spare register */
#define SYS_MNGR_SDM_HPS_SPARE_BIT_11_MASK \
                                                                             0x00000800
#define SYS_MNGR_SDM_HPS_SPARE_BIT_11_POS \
                                                                             11
#define SYS_MNGR_SDM_HPS_SPARE_BIT_10_MASK \
                                                                             0x00000400
#define SYS_MNGR_SDM_HPS_SPARE_BIT_10_POS \
                                                                             10
#define SYS_MNGR_SDM_HPS_SPARE_BIT_9_MASK \
                                                                             0x00000200
#define SYS_MNGR_SDM_HPS_SPARE_BIT_9_POS                                     9
#define SYS_MNGR_SDM_HPS_SPARE_BIT_8_MASK \
                                                                             0x00000100
#define SYS_MNGR_SDM_HPS_SPARE_BIT_8_POS                                     8
#define SYS_MNGR_SDM_HPS_SPARE_BIT_7_MASK \
                                                                             0x00000080
#define SYS_MNGR_SDM_HPS_SPARE_BIT_7_POS                                     7
#define SYS_MNGR_SDM_HPS_SPARE_BIT_6_MASK \
                                                                             0x00000040
#define SYS_MNGR_SDM_HPS_SPARE_BIT_6_POS                                     6
#define SYS_MNGR_SDM_HPS_SPARE_BIT_5_MASK \
                                                                             0x00000020
#define SYS_MNGR_SDM_HPS_SPARE_BIT_5_POS                                     5
#define SYS_MNGR_SDM_HPS_SPARE_BIT_4_MASK \
                                                                             0x00000010
#define SYS_MNGR_SDM_HPS_SPARE_BIT_4_POS                                     4
#define SYS_MNGR_SDM_HPS_SPARE_BIT_3_MASK \
                                                                             0x00000008
#define SYS_MNGR_SDM_HPS_SPARE_BIT_3_POS                                     3
#define SYS_MNGR_SDM_HPS_SPARE_BIT_2_MASK \
                                                                             0x00000004
#define SYS_MNGR_SDM_HPS_SPARE_BIT_2_POS                                     2
#define SYS_MNGR_SDM_HPS_SPARE_BIT_1_MASK \
                                                                             0x00000002
#define SYS_MNGR_SDM_HPS_SPARE_BIT_1_POS                                     1
#define SYS_MNGR_SDM_HPS_SPARE_BIT_0_MASK \
                                                                             0x00000001
#define SYS_MNGR_SDM_HPS_SPARE_BIT_0_POS                                     0

/* Bit fields of hps_sdm_spare register */
#define SYS_MNGR_HPS_SDM_SPARE_VAL_MASK \
                                                                             0x0007FFFF
#define SYS_MNGR_HPS_SDM_SPARE_VAL_POS                                       0

/* Bit fields of dfi_interface_cfg register */
#define SYS_MNGR_DFI_INTERFACE_CFG_DFI_CTRL_SEL_MASK \
                                                                             0x00000001
#define SYS_MNGR_DFI_INTERFACE_CFG_DFI_CTRL_SEL_POS                          0

/* Bit fields of nand_dd_ctrl register */
#define SYS_MNGR_NAND_DD_CTRL_RB_VALID_TIME_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_NAND_DD_CTRL_RB_VALID_TIME_POS \
                                                                             16
#define SYS_MNGR_NAND_DD_CTRL_DISCOVERY_IGNORE_CRC_MASK \
                                                                             0x00000010
#define SYS_MNGR_NAND_DD_CTRL_DISCOVERY_IGNORE_CRC_POS                       4
#define SYS_MNGR_NAND_DD_CTRL_DISCOVERY_INHIBIT_MASK \
                                                                             0x00000001
#define SYS_MNGR_NAND_DD_CTRL_DISCOVERY_INHIBIT_POS                          0

/* Bit fields of nand_phy_ctrl_reg register */
#define SYS_MNGR_NAND_PHY_CTRL_REG_PU_PD_POLARITY_MASK \
                                                                             0x00200000
#define SYS_MNGR_NAND_PHY_CTRL_REG_PU_PD_POLARITY_POS \
                                                                             21
#define SYS_MNGR_NAND_PHY_CTRL_REG_LOW_FREQ_SEL_MASK \
                                                                             0x00100000
#define SYS_MNGR_NAND_PHY_CTRL_REG_LOW_FREQ_SEL_POS \
                                                                             20
#define SYS_MNGR_NAND_PHY_CTRL_REG_SDR_DQS_VALUE_MASK \
                                                                             0x00004000
#define SYS_MNGR_NAND_PHY_CTRL_REG_SDR_DQS_VALUE_POS \
                                                                             14
#define SYS_MNGR_NAND_PHY_CTRL_REG_PHONY_DQS_TIMING_MASK \
                                                                             0x000003F0
#define SYS_MNGR_NAND_PHY_CTRL_REG_PHONY_DQS_TIMING_POS                      4
#define SYS_MNGR_NAND_PHY_CTRL_REG_CTRL_CLKPERIOD_DELAY_MASK \
                                                                             0x00000001
#define SYS_MNGR_NAND_PHY_CTRL_REG_CTRL_CLKPERIOD_DELAY_POS                  0

/* Bit fields of nand_phy_tsel_reg register */
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_OFF_VALUE_DATA_MASK \
                                                                             0x00F00000
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_OFF_VALUE_DATA_POS \
                                                                             20
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_RD_VALUE_DATA_MASK \
                                                                             0x000F0000
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_RD_VALUE_DATA_POS \
                                                                             16
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_OFF_VALUE_DQS_MASK \
                                                                             0x0000F000
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_OFF_VALUE_DQS_POS \
                                                                             12
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_RD_VALUE_DQS_MASK \
                                                                             0x00000F00
#define SYS_MNGR_NAND_PHY_TSEL_REG_TSEL_RD_VALUE_DQS_POS                     8

/* Bit fields of nand_phy_dq_timing_reg register */
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_CLKPERIOD_DELAY_MASK \
                                                                             0x00FF0000
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_CLKPERIOD_DELAY_POS \
                                                                             16
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_TSEL_START_MASK \
                                                                             0x0000F000
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_TSEL_START_POS \
                                                                             12
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_TSEL_END_MASK \
                                                                             0x00000F00
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_TSEL_END_POS             8
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_OE_START_MASK \
                                                                             0x00000070
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_OE_START_POS             4
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_OE_END_MASK \
                                                                             0x00000007
#define SYS_MNGR_NAND_PHY_DQ_TIMING_REG_DATA_SELECT_OE_END_POS               0

/* Bit fields of phy_dqs_timing_reg register */
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_CLKPERIOD_DELAY_MASK \
                                                                             0x00800000
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_CLKPERIOD_DELAY_POS \
                                                                             23
#define SYS_MNGR_PHY_DQS_TIMING_REG_USE_PHONY_DQS_MASK \
                                                                             0x00100000
#define SYS_MNGR_PHY_DQS_TIMING_REG_USE_PHONY_DQS_POS \
                                                                             20
#define SYS_MNGR_PHY_DQS_TIMING_REG_PHONY_DQS_SEL_MASK \
                                                                             0x00010000
#define SYS_MNGR_PHY_DQS_TIMING_REG_PHONY_DQS_SEL_POS \
                                                                             16
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_TSEL_START_MASK \
                                                                             0x0000F000
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_TSEL_START_POS \
                                                                             12
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_TSEL_END_MASK \
                                                                             0x00000F00
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_TSEL_END_POS                  8
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_OE_START_MASK \
                                                                             0x000000F0
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_OE_START_POS                  4
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_OE_END_MASK \
                                                                             0x0000000F
#define SYS_MNGR_PHY_DQS_TIMING_REG_DQS_SELECT_OE_END_POS                    0

/* Bit fields of nand_phy_gate_lpbk_ctrl_reg register */
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SYNC_METHOD_MASK \
                                                                             0x80000000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SYNC_METHOD_POS \
                                                                             31
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SW_DQS_PHASE_BYPASS_MASK \
                                                                             0x40000000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SW_DQS_PHASE_BYPASS_POS \
                                                                             30
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_EN_SW_HALF_CYCLE_MASK \
                                                                             0x20000000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_EN_SW_HALF_CYCLE_POS \
                                                                             29
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SW_HALF_CYCLE_SHIFT_MASK \
                                                                             0x10000000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_SW_HALF_CYCLE_SHIFT_POS \
                                                                             28
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_PARAM_PHASE_DETECT_SEL_OE_MASK \
                                                                             0x0E000000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_PARAM_PHASE_DETECT_SEL_OE_POS \
                                                                             25
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_RD_DEL_SEL_MASK \
                                                                             0x01F80000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_RD_DEL_SEL_POS \
                                                                             19
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_UNDERRUN_SUPPRESS_MASK \
                                                                             0x00040000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_UNDERRUN_SUPPRESS_POS \
                                                                             18
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_RD_DEL_SEL_EMPTY_MASK \
                                                                             0x00010000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_RD_DEL_SEL_EMPTY_POS \
                                                                             16
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_ERR_CHECK_TIMING_MASK \
                                                                             0x0000E000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_ERR_CHECK_TIMING_POS \
                                                                             13
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_FAIL_MUXSEL_MASK \
                                                                             0x00001000
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_FAIL_MUXSEL_POS \
                                                                             12
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LOOPBACK_CONTROL_MASK \
                                                                             0x00000C00
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LOOPBACK_CONTROL_POS \
                                                                             10
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_INTERNAL_MASK \
                                                                             0x00000200
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_INTERNAL_POS               9
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_EN_MASK \
                                                                             0x00000100
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_LPBK_EN_POS                     8
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_GATE_CFG_CLOSE_MASK \
                                                                             0x00000030
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_GATE_CFG_CLOSE_POS              4
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_GATE_CFG_MASK \
                                                                             0x0000000F
#define SYS_MNGR_NAND_PHY_GATE_LPBK_CTRL_REG_GATE_CFG_POS                    0

/* Bit fields of nand_phy_dll_master_ctrl_reg register */
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_BYPASS_MODE_MASK \
                                                                             0x00800000
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_BYPASS_MODE_POS \
                                                                             23
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_PHASE_DETECT_SEL_MASK \
                                                                             0x00700000
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_PHASE_DETECT_SEL_POS \
                                                                             20
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_LOCK_NUM_MASK \
                                                                             0x00070000
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_LOCK_NUM_POS \
                                                                             16
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_START_POINT_MASK \
                                                                             0x000000FF
#define SYS_MNGR_NAND_PHY_DLL_MASTER_CTRL_REG_PARAM_DLL_START_POINT_POS      0

/* Bit fields of nand_phy_dll_slave_ctrl_reg register */
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_CLK_WRDQS_DELAY_MASK \
                                                                             0x00FF0000
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_CLK_WRDQS_DELAY_POS \
                                                                             16
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_CLK_WR_DELAY_MASK \
                                                                             0x0000FF00
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_CLK_WR_DELAY_POS                8
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_READ_DQS_DELAY_MASK \
                                                                             0x000000FF
#define SYS_MNGR_NAND_PHY_DLL_SLAVE_CTRL_REG_READ_DQS_DELAY_POS              0

/* Bit fields of nand_dd_default_setting_reg0 register */
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG0_DD_PAGES_PER_BLOCK_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG0_DD_PAGES_PER_BLOCK_POS \
                                                                             16
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG0_DD_PAGE_SIZE_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG0_DD_PAGE_SIZE_POS               0

/* Bit fields of nand_dd_default_setting_reg1 register */
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_ACK_MASK \
                                                                             0x00000100
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_ACK_POS                     8
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_LUN_NUMBER_MASK \
                                                                             0x000000F0
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_LUN_NUMBER_POS              4
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_ROW_ADDR_WIDTH_MASK \
                                                                             0x00000006
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_ROW_ADDR_WIDTH_POS          1
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_SUPPORT_16_BIT_MASK \
                                                                             0x00000001
#define SYS_MNGR_NAND_DD_DEFAULT_SETTING_REG1_DD_SUPPORT_16_BIT_POS          0

/* Bit fields of nand_dd_status_reg register */
#define SYS_MNGR_NAND_DD_STATUS_REG_DD_REQ_MASK \
                                                                             0x00000008
#define SYS_MNGR_NAND_DD_STATUS_REG_DD_REQ_POS                               3
#define SYS_MNGR_NAND_DD_STATUS_REG_INIT_COMP_MASK \
                                                                             0x00000004
#define SYS_MNGR_NAND_DD_STATUS_REG_INIT_COMP_POS                            2
#define SYS_MNGR_NAND_DD_STATUS_REG_INIT_FAIL_MASK \
                                                                             0x00000002
#define SYS_MNGR_NAND_DD_STATUS_REG_INIT_FAIL_POS                            1
#define SYS_MNGR_NAND_DD_STATUS_REG_CTRL_BUSY_MASK \
                                                                             0x00000001
#define SYS_MNGR_NAND_DD_STATUS_REG_CTRL_BUSY_POS                            0

/* Bit fields of nand_dd_id_low_reg register */
#define SYS_MNGR_NAND_DD_ID_LOW_REG_DD_ID_VALUE_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_NAND_DD_ID_LOW_REG_DD_ID_VALUE_POS                          0

/* Bit fields of nand_dd_id_high_reg register */
#define SYS_MNGR_NAND_DD_ID_HIGH_REG_DD_ID_VALUE_MASK \
                                                                             0x000000FF
#define SYS_MNGR_NAND_DD_ID_HIGH_REG_DD_ID_VALUE_POS                         0

/* Bit fields of nand_write_prot_en_reg register */
#define SYS_MNGR_NAND_WRITE_PROT_EN_REG_WRE_PROT_EN_1_MASK \
                                                                             0x00000010
#define SYS_MNGR_NAND_WRITE_PROT_EN_REG_WRE_PROT_EN_1_POS                    4
#define SYS_MNGR_NAND_WRITE_PROT_EN_REG_WRE_PROT_EN_0_MASK \
                                                                             0x00000001
#define SYS_MNGR_NAND_WRITE_PROT_EN_REG_WRE_PROT_EN_0_POS                    0

/* Bit fields of sdmmc_cmd_queue_setting_reg register */
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCMFMUL_MASK \
                                                                             0x000F0000
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCMFMUL_POS \
                                                                             16
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCMFVAL_MASK \
                                                                             0x00007FE0
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCMFVAL_POS                    5
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCFSEL_MASK \
                                                                             0x0000001F
#define SYS_MNGR_SDMMC_CMD_QUEUE_SETTING_REG_ITCFSEL_POS                     0

/* Bit fields of i3c_slv_pid_low register */
#define SYS_MNGR_I3C_SLV_PID_LOW_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_I3C_SLV_PID_LOW_VAL_POS                                     0

/* Bit fields of i3c_slv_pid_high register */
#define SYS_MNGR_I3C_SLV_PID_HIGH_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_I3C_SLV_PID_HIGH_VAL_POS                                    0

/* Bit fields of i3c_slv_ctrl_0 register */
#define SYS_MNGR_I3C_SLV_CTRL_0_WAKEUP_MASK \
                                                                             0x80000000
#define SYS_MNGR_I3C_SLV_CTRL_0_WAKEUP_POS \
                                                                             31
#define SYS_MNGR_I3C_SLV_CTRL_0_I2C_GLITCH_FILTER_EN_MASK \
                                                                             0x40000000
#define SYS_MNGR_I3C_SLV_CTRL_0_I2C_GLITCH_FILTER_EN_POS \
                                                                             30
#define SYS_MNGR_I3C_SLV_CTRL_0_PENDING_IN_MASK \
                                                                             0x000000F0
#define SYS_MNGR_I3C_SLV_CTRL_0_PENDING_IN_POS                               4
#define SYS_MNGR_I3C_SLV_CTRL_0_STATIC_ADDR_EN_MASK \
                                                                             0x00000008
#define SYS_MNGR_I3C_SLV_CTRL_0_STATIC_ADDR_EN_POS                           3
#define SYS_MNGR_I3C_SLV_CTRL_0_ACT_MODE_MASK \
                                                                             0x00000006
#define SYS_MNGR_I3C_SLV_CTRL_0_ACT_MODE_POS                                 1
#define SYS_MNGR_I3C_SLV_CTRL_0_MODE_I2C_MASK \
                                                                             0x00000001
#define SYS_MNGR_I3C_SLV_CTRL_0_MODE_I2C_POS                                 0

/* Bit fields of i3c_slv_ctrl_1 register */
#define SYS_MNGR_I3C_SLV_CTRL_1_STATIC_ADDR_MASK \
                                                                             0x7F000000
#define SYS_MNGR_I3C_SLV_CTRL_1_STATIC_ADDR_POS \
                                                                             24
#define SYS_MNGR_I3C_SLV_CTRL_1_INST_ID_MASK \
                                                                             0x00F00000
#define SYS_MNGR_I3C_SLV_CTRL_1_INST_ID_POS \
                                                                             20
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_CLK_DATA_TURN_TIME_MASK \
                                                                             0x00070000
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_CLK_DATA_TURN_TIME_POS \
                                                                             16
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_MAX_WR_SPEED_MASK \
                                                                             0x00007000
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_MAX_WR_SPEED_POS \
                                                                             12
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_MAX_RD_SPEED_MASK \
                                                                             0x00000700
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_MAX_RD_SPEED_POS                         8
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_DCR_MASK \
                                                                             0x000000FF
#define SYS_MNGR_I3C_SLV_CTRL_1_SLV_DCR_POS                                  0

/* Bit fields of f2s_bridge_ctrl register */
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_FORCE_DRAIN_MASK \
                                                                             0x00000004
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_FORCE_DRAIN_POS                       2
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_READY_LATENCY_ENABLE_MASK \
                                                                             0x00000002
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_READY_LATENCY_ENABLE_POS              1
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_ENABLE_MASK \
                                                                             0x00000001
#define SYS_MNGR_F2S_BRIDGE_CTRL_F2SOC_ENABLE_POS                            0

/* Bit fields of dma_tbu_stash_ctrl_reg_0_dma0 register */
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA0_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of dma_tbu_stash_ctrl_reg_0_dma1 register */
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMA_TBU_STASH_CTRL_REG_0_DMA1_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of sdm_tbu_stash_ctrl_reg_1_sdm register */
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WSNOOP_REG_VAL_POS             8
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_RDOAMINEN_REG_VAL_POS          6
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WDOAMINEN_REG_VAL_POS          4
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_RDOAMINEN_REG_CTRL_POS         3
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_WDOAMINEN_REG_CTRL_POS         2
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHLPIDEN_REG_CTRL_POS       1
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_SDM_TBU_STASH_CTRL_REG_1_SDM_STASHNIDEN_REG_CTRL_POS        0

/* Bit fields of io_tbu_stash_ctrl_reg_2_usb2 register */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WSNOOP_REG_VAL_POS             8
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_RDOAMINEN_REG_VAL_POS          6
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WDOAMINEN_REG_VAL_POS          4
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_RDOAMINEN_REG_CTRL_POS         3
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_WDOAMINEN_REG_CTRL_POS         2
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHLPIDEN_REG_CTRL_POS       1
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB2_STASHNIDEN_REG_CTRL_POS        0

/* Bit fields of io_tbu_stash_ctrl_reg_2_usb3 register */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WSNOOP_REG_VAL_POS             8
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_RDOAMINEN_REG_VAL_POS          6
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WDOAMINEN_REG_VAL_POS          4
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_RDOAMINEN_REG_CTRL_POS         3
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_WDOAMINEN_REG_CTRL_POS         2
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHLPIDEN_REG_CTRL_POS       1
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_USB3_STASHNIDEN_REG_CTRL_POS        0

/* Bit fields of io_tbu_stash_ctrl_reg_2_sdmmc register */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_SDMMC_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of io_tbu_stash_ctrl_reg_2_nand register */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WSNOOP_REG_VAL_POS             8
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_RDOAMINEN_REG_VAL_POS          6
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WDOAMINEN_REG_VAL_POS          4
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_RDOAMINEN_REG_CTRL_POS         3
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_WDOAMINEN_REG_CTRL_POS         2
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHLPIDEN_REG_CTRL_POS       1
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_NAND_STASHNIDEN_REG_CTRL_POS        0

/* Bit fields of io_tbu_stash_ctrl_reg_2_etr register */
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WSNOOP_REG_VAL_POS              8
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_RDOAMINEN_REG_VAL_POS           6
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WDOAMINEN_REG_VAL_POS           4
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_RDOAMINEN_REG_CTRL_POS          3
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_WDOAMINEN_REG_CTRL_POS          2
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHLPIDEN_REG_CTRL_POS        1
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STASH_CTRL_REG_2_ETR_STASHNIDEN_REG_CTRL_POS         0

/* Bit fields of tsn_tbu_stash_ctrl_reg_3_tsn0 register */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN0_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of tsn_tbu_stash_ctrl_reg_3_tsn1 register */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN1_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of tsn_tbu_stash_ctrl_reg_3_tsn2 register */
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHLPID_REG_VAL_MASK \
                                                                             0x1F000000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHLPID_REG_VAL_POS \
                                                                             24
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHNID_REG_VAL_MASK \
                                                                             0x001F0000
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHNID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WSNOOP_REG_VAL_MASK \
                                                                             0x00000F00
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WSNOOP_REG_VAL_POS            8
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_RDOAMINEN_REG_VAL_MASK \
                                                                             0x000000C0
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_RDOAMINEN_REG_VAL_POS         6
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WDOAMINEN_REG_VAL_MASK \
                                                                             0x00000030
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WDOAMINEN_REG_VAL_POS         4
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_RDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_RDOAMINEN_REG_CTRL_POS        3
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WDOAMINEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_WDOAMINEN_REG_CTRL_POS        2
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHLPIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHLPIDEN_REG_CTRL_POS      1
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHNIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STASH_CTRL_REG_3_TSN2_STASHNIDEN_REG_CTRL_POS       0

/* Bit fields of dma_tbu_stream_ctrl_reg_0_dma0 register */
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_SPARE_CTRL_POS               6
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA0_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of dma_tbu_stream_ctrl_reg_0_dma1 register */
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_SPARE_CTRL_POS               6
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_DMA_TBU_STREAM_CTRL_REG_0_DMA1_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of sdm_tbu_stream_ctrl_reg_1_sdm register */
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_SPARE_CTRL_POS                6
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RMMUSECSID_REG_VAL_POS        5
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WMMUSECSID_REG_VAL_POS        4
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RSTREAMSIDEN_REG_CTRL_POS     3
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WSTREAMSIDEN_REG_CTRL_POS     2
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_RSTREAMIDEN_REG_CTRL_POS      1
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_SDM_TBU_STREAM_CTRL_REG_1_SDM_WSTREAMIDEN_REG_CTRL_POS      0

/* Bit fields of io_tbu_stream_ctrl_reg_2_usb2 register */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_SPARE_CTRL_POS                6
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RMMUSECSID_REG_VAL_POS        5
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WMMUSECSID_REG_VAL_POS        4
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RSTREAMSIDEN_REG_CTRL_POS     3
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WSTREAMSIDEN_REG_CTRL_POS     2
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_RSTREAMIDEN_REG_CTRL_POS      1
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB2_WSTREAMIDEN_REG_CTRL_POS      0

/* Bit fields of io_tbu_stream_ctrl_reg_2_usb3 register */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_SPARE_CTRL_POS                6
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RMMUSECSID_REG_VAL_POS        5
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WMMUSECSID_REG_VAL_POS        4
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RSTREAMSIDEN_REG_CTRL_POS     3
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WSTREAMSIDEN_REG_CTRL_POS     2
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_RSTREAMIDEN_REG_CTRL_POS      1
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_USB3_WSTREAMIDEN_REG_CTRL_POS      0

/* Bit fields of io_tbu_stream_ctrl_reg_2_sdmmc register */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_SPARE_CTRL_POS               6
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_SDMMC_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of io_tbu_stream_ctrl_reg_2_nand register */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_SPARE_CTRL_POS                6
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RMMUSECSID_REG_VAL_POS        5
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WMMUSECSID_REG_VAL_POS        4
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RSTREAMSIDEN_REG_CTRL_POS     3
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WSTREAMSIDEN_REG_CTRL_POS     2
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_RSTREAMIDEN_REG_CTRL_POS      1
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_NAND_WSTREAMIDEN_REG_CTRL_POS      0

/* Bit fields of io_tbu_stream_ctrl_reg_2_etr register */
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_SPARE_CTRL_POS                 6
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RMMUSECSID_REG_VAL_POS         5
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WMMUSECSID_REG_VAL_POS         4
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RSTREAMSIDEN_REG_CTRL_POS      3
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WSTREAMSIDEN_REG_CTRL_POS      2
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_RSTREAMIDEN_REG_CTRL_POS       1
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_IO_TBU_STREAM_CTRL_REG_2_ETR_WSTREAMIDEN_REG_CTRL_POS       0

/* Bit fields of tsn_tbu_stream_ctrl_reg_3_tsn0 register */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_SPARE_CTRL_POS               6
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN0_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of tsn_tbu_stream_ctrl_reg_3_tsn1 register */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_SPARE_CTRL_POS               6
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN1_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of tsn_tbu_stream_ctrl_reg_3_tsn2 register */
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_SPARE_CTRL_MASK \
                                                                             0xFFFFFFC0
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_SPARE_CTRL_POS               6
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RMMUSECSID_REG_VAL_MASK \
                                                                             0x00000020
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RMMUSECSID_REG_VAL_POS       5
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WMMUSECSID_REG_VAL_MASK \
                                                                             0x00000010
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WMMUSECSID_REG_VAL_POS       4
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000008
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RSTREAMSIDEN_REG_CTRL_POS    3
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WSTREAMSIDEN_REG_CTRL_MASK \
                                                                             0x00000004
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WSTREAMSIDEN_REG_CTRL_POS    2
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000002
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_RSTREAMIDEN_REG_CTRL_POS     1
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WSTREAMIDEN_REG_CTRL_MASK \
                                                                             0x00000001
#define SYS_MNGR_TSN_TBU_STREAM_CTRL_REG_3_TSN2_WSTREAMIDEN_REG_CTRL_POS     0

/* Bit fields of dma_tbu_stream_id_Ax_reg_0_dma0 register */
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA0_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA0_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA0_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA0_WMMUSID_REG_VAL_POS         0

/* Bit fields of dma_tbu_stream_id_Ax_reg_0_dma1 register */
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA1_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA1_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA1_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_DMA_TBU_STREAM_ID_AX_REG_0_DMA1_WMMUSID_REG_VAL_POS         0

/* Bit fields of sdm_tbu_stream_id_Ax_reg_1_sdm register */
#define SYS_MNGR_SDM_TBU_STREAM_ID_AX_REG_1_SDM_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_SDM_TBU_STREAM_ID_AX_REG_1_SDM_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_SDM_TBU_STREAM_ID_AX_REG_1_SDM_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_SDM_TBU_STREAM_ID_AX_REG_1_SDM_WMMUSID_REG_VAL_POS          0

/* Bit fields of io_tbu_stream_id_Ax_reg_2_usb2 register */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB2_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB2_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB2_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB2_WMMUSID_REG_VAL_POS          0

/* Bit fields of io_tbu_stream_id_Ax_reg_2_usb3 register */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB3_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB3_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB3_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_USB3_WMMUSID_REG_VAL_POS          0

/* Bit fields of io_tbu_stream_id_Ax_reg_2_sdmmc register */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_SDMMC_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_SDMMC_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_SDMMC_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_SDMMC_WMMUSID_REG_VAL_POS         0

/* Bit fields of io_tbu_stream_id_Ax_reg_2_nand register */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_NAND_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_NAND_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_NAND_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_NAND_WMMUSID_REG_VAL_POS          0

/* Bit fields of io_tbu_stream_id_Ax_reg_2_etr register */
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_ETR_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_ETR_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_ETR_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_IO_TBU_STREAM_ID_AX_REG_2_ETR_WMMUSID_REG_VAL_POS           0

/* Bit fields of tsn_tbu_stream_id_Ax_reg_3_tsn0 register */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN0_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN0_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN0_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN0_WMMUSID_REG_VAL_POS         0

/* Bit fields of tsn_tbu_stream_id_Ax_reg_3_tsn1 register */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN1_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN1_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN1_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN1_WMMUSID_REG_VAL_POS         0

/* Bit fields of tsn_tbu_stream_id_Ax_reg_3_tsn2 register */
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN2_RMMUSID_REG_VAL_MASK \
                                                                             0xFFFF0000
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN2_RMMUSID_REG_VAL_POS \
                                                                             16
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN2_WMMUSID_REG_VAL_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_TSN_TBU_STREAM_ID_AX_REG_3_TSN2_WMMUSID_REG_VAL_POS         0

/* Bit fields of usb3_misc_ctrl_reg0 register */
#define SYS_MNGR_USB3_MISC_CTRL_REG0_BIGENDIAN_GS_MASK \
                                                                             0x80000000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_BIGENDIAN_GS_POS \
                                                                             31
#define SYS_MNGR_USB3_MISC_CTRL_REG0_DEVSPD_OVRD_MASK \
                                                                             0x78000000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_DEVSPD_OVRD_POS \
                                                                             27
#define SYS_MNGR_USB3_MISC_CTRL_REG0_BUS_FILTER_BYPASS_MASK \
                                                                             0x07800000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_BUS_FILTER_BYPASS_POS \
                                                                             23
#define SYS_MNGR_USB3_MISC_CTRL_REG0_FLADJ_30MHZ_REG_MASK \
                                                                             0x007E0000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_FLADJ_30MHZ_REG_POS \
                                                                             17
#define SYS_MNGR_USB3_MISC_CTRL_REG0_PORT_PERM_ATTACH_MASK \
                                                                             0x00018000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_PORT_PERM_ATTACH_POS \
                                                                             15
#define SYS_MNGR_USB3_MISC_CTRL_REG0_PORT_OVERCURRENT_MASK \
                                                                             0x00006000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_PORT_OVERCURRENT_POS \
                                                                             13
#define SYS_MNGR_USB3_MISC_CTRL_REG0_RESET_PULSE_OVRD_MASK \
                                                                             0x00001000
#define SYS_MNGR_USB3_MISC_CTRL_REG0_RESET_PULSE_OVRD_POS \
                                                                             12
#define SYS_MNGR_USB3_MISC_CTRL_REG0_XHC_BME_MASK \
                                                                             0x00000800
#define SYS_MNGR_USB3_MISC_CTRL_REG0_XHC_BME_POS \
                                                                             11
#define SYS_MNGR_USB3_MISC_CTRL_REG0_FORCE_GEN1_SPEED_MASK \
                                                                             0x00000400
#define SYS_MNGR_USB3_MISC_CTRL_REG0_FORCE_GEN1_SPEED_POS \
                                                                             10
#define SYS_MNGR_USB3_MISC_CTRL_REG0_U3_DISABLE_PORT_MASK \
                                                                             0x00000200
#define SYS_MNGR_USB3_MISC_CTRL_REG0_U3_DISABLE_PORT_POS                     9
#define SYS_MNGR_USB3_MISC_CTRL_REG0_U2_DISABLE_PORT_MASK \
                                                                             0x00000100
#define SYS_MNGR_USB3_MISC_CTRL_REG0_U2_DISABLE_PORT_POS                     8
#define SYS_MNGR_USB3_MISC_CTRL_REG0_NUM_U3_PORT_MASK \
                                                                             0x000000F0
#define SYS_MNGR_USB3_MISC_CTRL_REG0_NUM_U3_PORT_POS                         4
#define SYS_MNGR_USB3_MISC_CTRL_REG0_NUM_U2_PORT_MASK \
                                                                             0x0000000F
#define SYS_MNGR_USB3_MISC_CTRL_REG0_NUM_U2_PORT_POS                         0

/* Bit fields of usb3_misc_ctrl_reg1 register */
#define SYS_MNGR_USB3_MISC_CTRL_REG1_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_USB3_MISC_CTRL_REG1_VAL_POS                                 0

/* Bit fields of boot_scratch_cold0 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD0_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD0_VAL_POS                                  0

/* Bit fields of boot_scratch_cold1 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD1_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD1_VAL_POS                                  0

/* Bit fields of boot_scratch_cold2 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD2_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD2_VAL_POS                                  0

/* Bit fields of boot_scratch_cold3 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD3_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD3_VAL_POS                                  0

/* Bit fields of boot_scratch_cold4 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD4_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD4_VAL_POS                                  0

/* Bit fields of boot_scratch_cold5 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD5_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD5_VAL_POS                                  0

/* Bit fields of boot_scratch_cold6 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD6_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD6_VAL_POS                                  0

/* Bit fields of boot_scratch_cold7 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD7_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD7_VAL_POS                                  0

/* Bit fields of boot_scratch_cold8 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD8_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD8_VAL_POS                                  0

/* Bit fields of boot_scratch_cold9 register */
#define SYS_MNGR_BOOT_SCRATCH_COLD9_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_COLD9_VAL_POS                                  0

/* Bit fields of mpfe_config register */
#define SYS_MNGR_MPFE_CONFIG_MPFE_CONFIG_SPARE_MASK \
                                                                             0x0000FE00
#define SYS_MNGR_MPFE_CONFIG_MPFE_CONFIG_SPARE_POS                           9
#define SYS_MNGR_MPFE_CONFIG_MPFE_LITE_ACTIVE_MASK \
                                                                             0x00000100
#define SYS_MNGR_MPFE_CONFIG_MPFE_LITE_ACTIVE_POS                            8
#define SYS_MNGR_MPFE_CONFIG_MPFE_F2SDRAM_ACTIVE_MASK \
                                                                             0x00000080
#define SYS_MNGR_MPFE_CONFIG_MPFE_F2SDRAM_ACTIVE_POS                         7
#define SYS_MNGR_MPFE_CONFIG_MPFE_F2SOC_ACTIVE_MASK \
                                                                             0x00000040
#define SYS_MNGR_MPFE_CONFIG_MPFE_F2SOC_ACTIVE_POS                           6
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_CSR_CLK_ENABLE_MASK \
                                                                             0x00000020
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_CSR_CLK_ENABLE_POS                   5
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_P1_CLK_ENABLE_MASK \
                                                                             0x00000010
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_P1_CLK_ENABLE_POS                    4
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_P0_CLK_ENABLE_MASK \
                                                                             0x00000008
#define SYS_MNGR_MPFE_CONFIG_MPFE_IO96B_P0_CLK_ENABLE_POS                    3
#define SYS_MNGR_MPFE_CONFIG_MPFE_LITE_INTFCSEL_MASK \
                                                                             0x00000004
#define SYS_MNGR_MPFE_CONFIG_MPFE_LITE_INTFCSEL_POS                          2
#define SYS_MNGR_MPFE_CONFIG_F2SDRAM_INTFCSEL_MASK \
                                                                             0x00000002
#define SYS_MNGR_MPFE_CONFIG_F2SDRAM_INTFCSEL_POS                            1
#define SYS_MNGR_MPFE_CONFIG_F2SOC_INTFCSEL_MASK \
                                                                             0x00000001
#define SYS_MNGR_MPFE_CONFIG_F2SOC_INTFCSEL_POS                              0

/* Bit fields of mpfe_status register */
#define SYS_MNGR_MPFE_STATUS_MPFEINTFC_STAT_SPARE_IN_MASK \
                                                                             0x0000FFFF
#define SYS_MNGR_MPFE_STATUS_MPFEINTFC_STAT_SPARE_IN_POS                     0

/* Bit fields of boot_scratch_warm0 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM0_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM0_VAL_POS                                  0

/* Bit fields of boot_scratch_warm1 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM1_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM1_VAL_POS                                  0

/* Bit fields of boot_scratch_warm2 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM2_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM2_VAL_POS                                  0

/* Bit fields of boot_scratch_warm3 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM3_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM3_VAL_POS                                  0

/* Bit fields of boot_scratch_warm4 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM4_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM4_VAL_POS                                  0

/* Bit fields of boot_scratch_warm5 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM5_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM5_VAL_POS                                  0

/* Bit fields of boot_scratch_warm6 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM6_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM6_VAL_POS                                  0

/* Bit fields of boot_scratch_warm7 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM7_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM7_VAL_POS                                  0

/* Bit fields of boot_scratch_warm8 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM8_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_WARM8_VAL_POS                                  0

/* Bit fields of boot_scratch_warm9 register */
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL2_MASK \
                                                                             0xFFFFF000
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL2_POS \
                                                                             12
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL1_MASK \
                                                                             0x00000F00
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL1_POS                                 8
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL0_MASK \
                                                                             0x000000FF
#define SYS_MNGR_BOOT_SCRATCH_WARM9_VAL0_POS                                 0

/* Bit fields of boot_scratch_por0 register */
#define SYS_MNGR_BOOT_SCRATCH_POR0_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR0_VAL_POS                                   0

/* Bit fields of boot_scratch_por1 register */
#define SYS_MNGR_BOOT_SCRATCH_POR1_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR1_VAL_POS                                   0

/* Bit fields of boot_scratch_por2 register */
#define SYS_MNGR_BOOT_SCRATCH_POR2_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR2_VAL_POS                                   0

/* Bit fields of boot_scratch_por3 register */
#define SYS_MNGR_BOOT_SCRATCH_POR3_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR3_VAL_POS                                   0

/* Bit fields of boot_scratch_por4 register */
#define SYS_MNGR_BOOT_SCRATCH_POR4_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR4_VAL_POS                                   0

/* Bit fields of boot_scratch_por5 register */
#define SYS_MNGR_BOOT_SCRATCH_POR5_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR5_VAL_POS                                   0

/* Bit fields of boot_scratch_por6 register */
#define SYS_MNGR_BOOT_SCRATCH_POR6_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR6_VAL_POS                                   0

/* Bit fields of boot_scratch_por7 register */
#define SYS_MNGR_BOOT_SCRATCH_POR7_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR7_VAL_POS                                   0

/* Bit fields of boot_scratch_por8 register */
#define SYS_MNGR_BOOT_SCRATCH_POR8_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR8_VAL_POS                                   0

/* Bit fields of boot_scratch_por9 register */
#define SYS_MNGR_BOOT_SCRATCH_POR9_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_BOOT_SCRATCH_POR9_VAL_POS                                   0

/* Bit fields of sdm_be_awaddr_remap register */
#define SYS_MNGR_SDM_BE_AWADDR_REMAP_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_SDM_BE_AWADDR_REMAP_VAL_POS                                 0

/* Bit fields of sdm_be_araddr_remap register */
#define SYS_MNGR_SDM_BE_ARADDR_REMAP_VAL_MASK \
                                                                             0xFFFFFFFF
#define SYS_MNGR_SDM_BE_ARADDR_REMAP_VAL_POS                                 0


#endif /* SOCFPGA_SYS_MNGR_REG_PLAT_H */
