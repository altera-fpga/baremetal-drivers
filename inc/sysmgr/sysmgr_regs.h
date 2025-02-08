#ifndef SYSMGR_REGS_H__
#define SYSMGR_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "hps_address_map.h"

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t siliconid1;                      /* SILICONID1 */
    volatile uint32_t siliconid2;                      /* SILICONID2 */
    volatile uint32_t wddbg;                           /* WDDBG */
    volatile uint32_t _pad_0xc_0xf;                    /* *UNDEFINED* */
    volatile uint32_t mpu_status;                      /* MPU_STATUS */
    volatile uint32_t _pad_0x14_0x2b[6];               /* *UNDEFINED* */
    volatile uint32_t sdmmc_l3master;                  /* SDMMC_L3MASTER */
    volatile uint32_t _pad_0x30_0x33;                  /* *UNDEFINED* */
    volatile uint32_t nand_l3master;                   /* NAND_L3MASTER */
    volatile uint32_t usb0_l3master;                   /* USB0_L3MASTER */
    volatile uint32_t usb1_l3master;                   /* USB1_L3MASTER */
    volatile uint32_t tsn_global;                      /* TSN_GLOBAL */
    volatile uint32_t tsn0;                            /* TSN0 */
    volatile uint32_t tsn1;                            /* TSN1 */
    volatile uint32_t tsn2;                            /* TSN2 */
    volatile uint32_t tsn0_ace;                        /* TSN0_ACE */
    volatile uint32_t tsn1_ace;                        /* TSN1_ACE */
    volatile uint32_t tsn2_ace;                        /* TSN2_ACE */
    volatile uint32_t fpga_bridge_ctrl;                /* FPGA_BRIDGE_CTRL */
    volatile uint32_t _pad_0x60_0x67[2];               /* *UNDEFINED* */
    volatile uint32_t fpgaintf_en_1;                   /* FPGAINTF_EN_1 */
    volatile uint32_t fpgaintf_en_2;                   /* FPGAINTF_EN_2 */
    volatile uint32_t fpgaintf_en_3;                   /* FPGAINTF_EN_3 */
    volatile uint32_t dmac0_l3master;                  /* DMAC0_L3MASTER */
    volatile uint32_t etr_l3master;                    /* ETR_L3MASTER */
    volatile uint32_t dmac1_l3master;                  /* DMAC1_L3MASTER */
    volatile uint32_t sec_ctrl_slt;                    /* SEC_CTRL_SLT */
    volatile uint32_t osc_trim;                        /* OSC_TRIM */
    volatile uint32_t dmac0_ctrl_status_reg;           /* DMAC0_CTRL_STATUS_REG */
    volatile uint32_t dmac1_ctrl_status_reg;           /* DMAC1_CTRL_STATUS_REG */
    volatile uint32_t ecc_intmask_value;               /* ECC_INTMASK_VALUE */
    volatile uint32_t ecc_intmask_set;                 /* ECC_INTMASK_SET */
    volatile uint32_t ecc_intmask_clr;                 /* ECC_INTMASK_CLR */
    volatile uint32_t ecc_intstatus_serr;              /* ECC_INTSTATUS_SERR */
    volatile uint32_t ecc_intstatus_derr;              /* ECC_INTSTATUS_DERR */
    volatile uint32_t _pad_0xa4_0xbf[7];               /* *UNDEFINED* */
    volatile uint32_t noc_timeout;                     /* NOC_TIMEOUT */
    volatile uint32_t _pad_0xc4_0xd3[4];               /* *UNDEFINED* */
    volatile uint32_t noc_idlestatus;                  /* NOC_IDLESTATUS */
    volatile uint32_t fpga2soc_ctrl;                   /* FPGA2SOC_CTRL */
    volatile uint32_t fpga_config;                     /* FPGA_CONFIG */
    volatile uint32_t _pad_0xe0_0xe3;                  /* *UNDEFINED* */
    volatile uint32_t gpo;                             /* GPO */
    volatile uint32_t gpi;                             /* GPI */
    volatile uint32_t _pad_0xec_0xef;                  /* *UNDEFINED* */
    volatile uint32_t mpu;                             /* MPU */
    volatile uint32_t sdm_hps_spare;                   /* SDM_HPS_SPARE */
    volatile uint32_t hps_sdm_spare;                   /* HPS_SDM_SPARE */
    volatile uint32_t dfi_interface_cfg;               /* DFI_INTERFACE_CFG */
    volatile uint32_t nand_dd_ctrl;                    /* NAND_DD_CTRL */
    volatile uint32_t nand_phy_ctrl_reg;               /* NAND_PHY_CTRL_REG */
    volatile uint32_t nand_phy_tsel_reg;               /* NAND_PHY_TSEL_REG */
    volatile uint32_t nand_phy_dq_timing_reg;          /* NAND_PHY_DQ_TIMING_REG */
    volatile uint32_t nand_phy_dqs_timing_reg;         /* PHY_DQS_TIMING_REG */
    volatile uint32_t nand_phy_gate_lpbk_ctrl_reg;     /* NAND_PHY_GATE_LPBK_CTRL_REG */
    volatile uint32_t nand_phy_dll_master_ctrl_reg;    /* NAND_PHY_DLL_MASTER_CTRL_REG */
    volatile uint32_t nand_phy_dll_slave_ctrl_reg;     /* NAND_PHY_DLL_SLAVE_CTRL_REG */
    volatile uint32_t nand_dd_default_setting_reg0;    /* NAND_DD_DEFAULT_SETTING_REG0 */
    volatile uint32_t nand_dd_default_setting_reg1;    /* NAND_DD_DEFAULT_SETTING_REG1 */
    volatile uint32_t nand_dd_status_reg;              /* NAND_DD_STATUS_REG */
    volatile uint32_t nand_dd_id_low_reg;              /* NAND_DD_ID_LOW_REG */
    volatile uint32_t nand_dd_id_high_reg;             /* NAND_DD_ID_HIGH_REG */
    volatile uint32_t nand_write_prot_en_reg;          /* NAND_WRITE_PROT_EN_REG */
    volatile uint32_t sdmmc_cmd_queue_setting_reg;     /* SDMMC_CMD_QUEUE_SETTING_REG */
    volatile uint32_t i3c_slv_pid_low;                 /* I3C_SLV_PID_LOW */
    volatile uint32_t i3c_slv_pid_high;                /* I3C_SLV_PID_HIGH */
    volatile uint32_t i3c_slv_ctrl_0;                  /* I3C_SLV_CTRL_0 */
    volatile uint32_t i3c_slv_ctrl_1;                  /* I3C_SLV_CTRL_1 */
    volatile uint32_t f2s_bridge_ctrl;                 /* F2S_BRIDGE_CTRL */
    volatile uint32_t dma_tbu_stash_ctrl_reg_0_dma0;   /* DMA_TBU_STASH_CTRL_REG_0_DMA0 */
    volatile uint32_t dma_tbu_stash_ctrl_reg_0_dma1;   /* DMA_TBU_STASH_CTRL_REG_0_DMA1 */
    volatile uint32_t sdm_tbu_stash_ctrl_reg_1_sdm;    /* SDM_TBU_STASH_CTRL_REG_1_SDM */
    volatile uint32_t io_tbu_stash_ctrl_reg_2_usb2;    /* IO_TBU_STASH_CTRL_REG_2_USB2 */
    volatile uint32_t io_tbu_stash_ctrl_reg_2_usb3;    /* IO_TBU_STASH_CTRL_REG_2_USB3 */
    volatile uint32_t io_tbu_stash_ctrl_reg_2_sdmmc;   /* IO_TBU_STASH_CTRL_REG_2_SDMMC */
    volatile uint32_t io_tbu_stash_ctrl_reg_2_nand;    /* IO_TBU_STASH_CTRL_REG_2_NAND */
    volatile uint32_t io_tbu_stash_ctrl_reg_2_etr;     /* IO_TBU_STASH_CTRL_REG_2_ETR */
    volatile uint32_t tsn_tbu_stash_ctrl_reg_3_tsn0;   /* TSN_TBU_STASH_CTRL_REG_3_TSN0 */
    volatile uint32_t tsn_tbu_stash_ctrl_reg_3_tsn1;   /* TSN_TBU_STASH_CTRL_REG_3_TSN1 */
    volatile uint32_t tsn_tbu_stash_ctrl_reg_3_tsn2;   /* TSN_TBU_STASH_CTRL_REG_3_TSN2 */
    volatile uint32_t dma_tbu_stream_ctrl_reg_0_dma0;  /* DMA_TBU_STREAM_CTRL_REG_0_DMA0 */
    volatile uint32_t dma_tbu_stream_ctrl_reg_0_dma1;  /* DMA_TBU_STREAM_CTRL_REG_0_DMA1 */
    volatile uint32_t sdm_tbu_stream_ctrl_reg_1_sdm;   /* SDM_TBU_STREAM_CTRL_REG_1_SDM */
    volatile uint32_t io_tbu_stream_ctrl_reg_2_usb2;   /* IO_TBU_STREAM_CTRL_REG_2_USB2 */
    volatile uint32_t io_tbu_stream_ctrl_reg_2_usb3;   /* IO_TBU_STREAM_CTRL_REG_2_USB3 */
    volatile uint32_t io_tbu_stream_ctrl_reg_2_sdmmc;  /* IO_TBU_STREAM_CTRL_REG_2_SDMMC */
    volatile uint32_t io_tbu_stream_ctrl_reg_2_nand;   /* IO_TBU_STREAM_CTRL_REG_2_NAND */
    volatile uint32_t io_tbu_stream_ctrl_reg_2_etr;    /* IO_TBU_STREAM_CTRL_REG_2_ETR */
    volatile uint32_t tsn_tbu_stream_ctrl_reg_3_tsn0;  /* TSN_TBU_STREAM_CTRL_REG_3_TSN0 */
    volatile uint32_t tsn_tbu_stream_ctrl_reg_3_tsn1;  /* TSN_TBU_STREAM_CTRL_REG_3_TSN1 */
    volatile uint32_t tsn_tbu_stream_ctrl_reg_3_tsn2;  /* TSN_TBU_STREAM_CTRL_REG_3_TSN2 */
    volatile uint32_t dma_tbu_stream_id_ax_reg_0_dma0; /* DMA_TBU_STREAM_ID_ax_REG_0_DMA0 */
    volatile uint32_t dma_tbu_stream_id_ax_reg_0_dma1; /* DMA_TBU_STREAM_ID_ax_REG_0_DMA1 */
    volatile uint32_t sdm_tbu_stream_id_ax_reg_1_sdm;  /* SDM_TBU_STREAM_ID_ax_REG_1_SDM */
    volatile uint32_t io_tbu_stream_id_ax_reg_2_usb2;  /* IO_TBU_STREAM_ID_ax_REG_2_USB2 */
    volatile uint32_t io_tbu_stream_id_ax_reg_2_usb3;  /* IO_TBU_STREAM_ID_ax_REG_2_USB3 */
    volatile uint32_t io_tbu_stream_id_ax_reg_2_sdmmc; /* IO_TBU_STREAM_ID_ax_REG_2_SDMMC */
    volatile uint32_t io_tbu_stream_id_ax_reg_2_nand;  /* IO_TBU_STREAM_ID_ax_REG_2_NAND */
    volatile uint32_t io_tbu_stream_id_ax_reg_2_etr;   /* IO_TBU_STREAM_ID_ax_REG_2_ETR */
    volatile uint32_t tsn_tbu_stream_id_ax_reg_3_tsn0; /* TSN_TBU_STREAM_ID_ax_REG_3_TSN0 */
    volatile uint32_t tsn_tbu_stream_id_ax_reg_3_tsn1; /* TSN_TBU_STREAM_ID_ax_REG_3_TSN1 */
    volatile uint32_t tsn_tbu_stream_id_ax_reg_3_tsn2; /* TSN_TBU_STREAM_ID_ax_REG_3_TSN2 */
    volatile uint32_t _pad_0x1d4_0x1ef[7];             /* *UNDEFINED* */
    volatile uint32_t usb3_misc_ctrl_reg0;             /* USB3_MISC_CTRL_REG0 */
    volatile uint32_t usb3_misc_ctrl_reg1;             /* USB3_MISC_CTRL_REG1 */
    volatile uint32_t _pad_0x1f8_0x1ff[2];             /* *UNDEFINED* */
    volatile uint32_t boot_scratch_cold0;              /* BOOT_SCRATCH_COLD0 */
    volatile uint32_t boot_scratch_cold1;              /* BOOT_SCRATCH_COLD1 */
    volatile uint32_t boot_scratch_cold2;              /* BOOT_SCRATCH_COLD2 */
    volatile uint32_t boot_scratch_cold3;              /* BOOT_SCRATCH_COLD3 */
    volatile uint32_t boot_scratch_cold4;              /* BOOT_SCRATCH_COLD4 */
    volatile uint32_t boot_scratch_cold5;              /* BOOT_SCRATCH_COLD5 */
    volatile uint32_t boot_scratch_cold6;              /* BOOT_SCRATCH_COLD6 */
    volatile uint32_t boot_scratch_cold7;              /* BOOT_SCRATCH_COLD7 */
    volatile uint32_t boot_scratch_cold8;              /* BOOT_SCRATCH_COLD8 */
    volatile uint32_t boot_scratch_cold9;              /* BOOT_SCRATCH_COLD9 */
    volatile uint32_t mpfe_config;                     /* MPFE_CONFIG */
    volatile uint32_t mpfe_status;                     /* MPFE_STATUS */
    volatile uint32_t boot_scratch_warm0;              /* BOOT_SCRATCH_WARM0 */
    volatile uint32_t boot_scratch_warm1;              /* BOOT_SCRATCH_WARM1 */
    volatile uint32_t boot_scratch_warm2;              /* BOOT_SCRATCH_WARM2 */
    volatile uint32_t boot_scratch_warm3;              /* BOOT_SCRATCH_WARM3 */
    volatile uint32_t boot_scratch_warm4;              /* BOOT_SCRATCH_WARM4 */
    volatile uint32_t boot_scratch_warm5;              /* BOOT_SCRATCH_WARM5 */
    volatile uint32_t boot_scratch_warm6;              /* BOOT_SCRATCH_WARM6 */
    volatile uint32_t boot_scratch_warm7;              /* BOOT_SCRATCH_WARM7 */
    volatile uint32_t boot_scratch_warm8;              /* BOOT_SCRATCH_WARM8 */
    volatile uint32_t boot_scratch_warm9;              /* BOOT_SCRATCH_WARM9 */
    volatile uint32_t boot_scratch_por0;               /* BOOT_SCRATCH_POR0 */
    volatile uint32_t boot_scratch_por1;               /* BOOT_SCRATCH_POR1 */
    volatile uint32_t boot_scratch_por2;               /* BOOT_SCRATCH_POR2 */
    volatile uint32_t boot_scratch_por3;               /* BOOT_SCRATCH_POR3 */
    volatile uint32_t boot_scratch_por4;               /* BOOT_SCRATCH_POR4 */
    volatile uint32_t boot_scratch_por5;               /* BOOT_SCRATCH_POR5 */
    volatile uint32_t boot_scratch_por6;               /* BOOT_SCRATCH_POR6 */
    volatile uint32_t boot_scratch_por7;               /* BOOT_SCRATCH_POR7 */
    volatile uint32_t boot_scratch_por8;               /* BOOT_SCRATCH_POR8 */
    volatile uint32_t boot_scratch_por9;               /* BOOT_SCRATCH_POR9 */
    volatile uint32_t sdm_be_awaddr_remap;             /* SDM_BE_AWADDR_REMAP */
    volatile uint32_t sdm_be_araddr_remap;             /* SDM_BE_ARADDR_REMAP */
} sysmgr_regs_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSMGR_REGS_H__
