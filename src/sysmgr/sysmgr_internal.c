#ifdef __cplusplus
extern "C" {
#endif

#include "sysmgr_internal.h"
#include "sysmgr_regs.h"
// Array denoting the access level for each parameter
// clang-format off
const uint32_t sysmgr_regs_rw_status[sizeof(sysmgr_regs_t)/sizeof(uint32_t)] = {
    REGISTER_READ_ONLY,                     /* SILICONID1 */
    REGISTER_READ_ONLY,                     /* SILICONID2 */
    REGISTER_RW,                            /* WDDBG */
    REGISTER_UNUSED,                        /* *UNDEFINED* */
    REGISTER_READ_ONLY,                     /* MPU_STATUS */
    REGISTER_UNUSED,                        /* *UNDEFINED* */
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_RW,                            /* SDMMC_L3MASTER */
    REGISTER_UNUSED,                        /* *UNDEFINED* */
    REGISTER_RW,                            /* NAND_L3MASTER */
    REGISTER_RW,                            /* USB0_L3MASTER */
    REGISTER_RW,                            /* USB1_L3MASTER */
    REGISTER_RW,                            /* TSN_GLOBAL */
    REGISTER_RW,                            /* TSN0 */
    REGISTER_RW,                            /* TSN1 */
    REGISTER_RW,                            /* TSN2 */
    REGISTER_RW,                            /* TSN0_ACE */
    REGISTER_RW,                            /* TSN1_ACE */
    REGISTER_RW,                            /* TSN2_ACE */
    REGISTER_RW,                            /* FPGA_BRIDGE_CTRL */
    REGISTER_UNUSED,                        /* *UNDEFINED* */
    REGISTER_UNUSED,
    REGISTER_RW,                            /* FPGAINTF_EN_1 */
    REGISTER_RW,                            /* FPGAINTF_EN_2 */
    REGISTER_RW,                            /* FPGAINTF_EN_3 */
    REGISTER_RW,                            /* DMAC0_L3MASTER */
    REGISTER_RW,                            /* ETR_L3MASTER */
    REGISTER_RW,                            /* DMAC1_L3MASTER */
    REGISTER_READ_ONLY,                     /* SEC_CTRL_SLT */
    REGISTER_READ_ONLY,                     /* OSC_TRIM */
    REGISTER_RW,                            /* DMAC0_CTRL_STATUS_REG */
    REGISTER_RW,                            /* DMAC1_CTRL_STATUS_REG */
    REGISTER_RW,                            /* ECC_INTMASK_VALUE */
    REGISTER_WRITE_ONLY,                    /* ECC_INTMASK_SET */
    REGISTER_WRITE_ONLY,                    /* ECC_INTMASK_CLR */
    REGISTER_READ_ONLY,                     /* ECC_INTSTATUS_SERR */
    REGISTER_READ_ONLY,                     /* ECC_INTSTATUS_DERR */
    REGISTER_UNUSED,                        /* *UNDEFINED* 0xa4 - 0xbf */
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_RW,                            /* NOC_TIMEOUT */
    REGISTER_UNUSED,                        /* *UNDEFINED* 0xc4 - 0xd3*/
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_READ_ONLY,                     /* NOC_IDLESTATUS */
    REGISTER_RW,                            /* FPGA2SOC_CTRL */
    REGISTER_READ_ONLY,                     /* FPGA_CONFIG */
    REGISTER_UNUSED,                        /* *UNDEFINED* */
    REGISTER_RW,                            /* GPO */
    REGISTER_READ_ONLY,                     /* GPI */
    REGISTER_UNUSED,                        /* *UNDEFINED* 0xec - 0ef */
    REGISTER_RW,                            /* MPU */
    REGISTER_RW,                            /* SDM_HPS_SPARE */
    REGISTER_RW,                            /* HPS_SDM_SPARE */
    REGISTER_RW,                            /* DFI_INTERFACE_CFG */
    REGISTER_RW,                            /* NAND_DD_CTRL */
    REGISTER_RW,                            /* NAND_PHY_CTRL_REG */
    REGISTER_RW,                            /* NAND_PHY_TSEL_REG */
    REGISTER_RW,                            /* NAND_PHY_DQ_TIMING_REG */
    REGISTER_RW,                            /* PHY_DQS_TIMING_REG */
    REGISTER_RW,                            /* NAND_PHY_GATE_LPBK_CTRL_REG */
    REGISTER_RW,                            /* NAND_PHY_DLL_MASTER_CTRL_REG */
    REGISTER_RW,                            /* NAND_PHY_DLL_SLAVE_CTRL_REG */
    REGISTER_RW,                            /* NAND_DD_DEFAULT_SETTING_REG0 */
    REGISTER_RW,                            /* NAND_DD_DEFAULT_SETTING_REG1 */
    REGISTER_READ_ONLY,                     /* NAND_DD_STATUS_REG */
    REGISTER_READ_ONLY,                     /* NAND_DD_ID_LOW_REG */
    REGISTER_READ_ONLY,                     /* NAND_DD_ID_HIGH_REG */
    REGISTER_RW,                            /* NAND_WRITE_PROT_EN_REG */
    REGISTER_RW,                            /* SDMMC_CMD_QUEUE_SETTING_REG */
    REGISTER_RW,                            /* I3C_SLV_PID_LOW */
    REGISTER_RW,                            /* I3C_SLV_PID_HIGH */
    REGISTER_RW,                            /* I3C_SLV_CTRL_0 */
    REGISTER_RW,                            /* I3C_SLV_CTRL_1 */
    REGISTER_RW,                            /* F2S_BRIDGE_CTRL */
    REGISTER_RW,                            /* DMA_TBU_STASH_CTRL_REG_0_DMA0 */
    REGISTER_RW,                            /* DMA_TBU_STASH_CTRL_REG_0_DMA1 */
    REGISTER_RW,                            /* SDM_TBU_STASH_CTRL_REG_1_SDM */
    REGISTER_RW,                            /* IO_TBU_STASH_CTRL_REG_2_USB2 */
    REGISTER_RW,                            /* IO_TBU_STASH_CTRL_REG_2_USB3 */
    REGISTER_RW,                            /* IO_TBU_STASH_CTRL_REG_2_SDMMC */
    REGISTER_RW,                            /* IO_TBU_STASH_CTRL_REG_2_NAND */
    REGISTER_RW,                            /* IO_TBU_STASH_CTRL_REG_2_ETR */
    REGISTER_RW,                            /* TSN_TBU_STASH_CTRL_REG_3_TSN0 */
    REGISTER_RW,                            /* TSN_TBU_STASH_CTRL_REG_3_TSN1 */
    REGISTER_RW,                            /* TSN_TBU_STASH_CTRL_REG_3_TSN2 */
    REGISTER_RW,                            /* DMA_TBU_STREAM_CTRL_REG_0_DMA0 */
    REGISTER_RW,                            /* DMA_TBU_STREAM_CTRL_REG_0_DMA1 */
    REGISTER_RW,                            /* SDM_TBU_STREAM_CTRL_REG_1_SDM */
    REGISTER_RW,                            /* IO_TBU_STREAM_CTRL_REG_2_USB2 */
    REGISTER_RW,                            /* IO_TBU_STREAM_CTRL_REG_2_USB3 */
    REGISTER_RW,                            /* IO_TBU_STREAM_CTRL_REG_2_SDMMC */
    REGISTER_RW,                            /* IO_TBU_STREAM_CTRL_REG_2_NAND */
    REGISTER_RW,                            /* IO_TBU_STREAM_CTRL_REG_2_ETR */
    REGISTER_RW,                            /* TSN_TBU_STREAM_CTRL_REG_3_TSN0 */
    REGISTER_RW,                            /* TSN_TBU_STREAM_CTRL_REG_3_TSN1 */
    REGISTER_RW,                            /* TSN_TBU_STREAM_CTRL_REG_3_TSN2 */
    REGISTER_RW,                            /* DMA_TBU_STREAM_ID_ax_REG_0_DMA0 */
    REGISTER_RW,                            /* DMA_TBU_STREAM_ID_ax_REG_0_DMA1 */
    REGISTER_RW,                            /* SDM_TBU_STREAM_ID_ax_REG_1_SDM */
    REGISTER_RW,                            /* IO_TBU_STREAM_ID_ax_REG_2_USB2 */
    REGISTER_RW,                            /* IO_TBU_STREAM_ID_ax_REG_2_USB3 */
    REGISTER_RW,                            /* IO_TBU_STREAM_ID_ax_REG_2_SDMMC */
    REGISTER_RW,                            /* IO_TBU_STREAM_ID_ax_REG_2_NAND */
    REGISTER_RW,                            /* IO_TBU_STREAM_ID_ax_REG_2_ETR */
    REGISTER_RW,                            /* TSN_TBU_STREAM_ID_ax_REG_3_TSN0 */
    REGISTER_RW,                            /* TSN_TBU_STREAM_ID_ax_REG_3_TSN1 */
    REGISTER_RW,                            /* TSN_TBU_STREAM_ID_ax_REG_3_TSN2 */
    REGISTER_UNUSED,                        /* *UNDEFINED* 0x1df - 0x1ef */
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_UNUSED,
    REGISTER_RW,                            /* USB3_MISC_CTRL_REG0 */
    REGISTER_RW,                            /* USB3_MISC_CTRL_REG1 */
    REGISTER_UNUSED,                        /* *UNDEFINED* 0x1f8 - 0x1ff */
    REGISTER_UNUSED,
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD0 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD1 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD2 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD3 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD4 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD5 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD6 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD7 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD8 */
    REGISTER_RW,                            /* BOOT_SCRATCH_COLD9 */
    REGISTER_RW,                            /* MPFE_CONFIG */
    REGISTER_READ_ONLY,                     /* MPFE_STATUS */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM0 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM1 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM2 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM3 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM4 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM5 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM6 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM7 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM8 */
    REGISTER_RW,                            /* BOOT_SCRATCH_WARM9 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR0 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR1 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR2 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR3 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR4 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR5 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR6 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR7 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR8 */
    REGISTER_RW,                            /* BOOT_SCRATCH_POR9 */
    REGISTER_RW,                            /* SDM_BE_AWADDR_REMAP */
    REGISTER_RW,                            /* SDM_BE_ARADDR_REMAP */
};
// clang-format on

int32_t sysmgr_regs_read(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    uint32_t *base = (uint32_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(sysmgr_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(sysmgr_regs_t) / 4UL); i++) {

            // If this register can be read from allow it otherwise skip reading
            if ((sysmgr_regs_rw_status[i] & REGISTER_READ_ONLY) == REGISTER_READ_ONLY) {
                buf32[i] = base[i];
            }
        }
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_regs_write(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    uint32_t *base = (uint32_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(sysmgr_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(sysmgr_regs_t) / 4UL); i++) {

            // If this register can be written to allow it otherwise skip writing
            if ((sysmgr_regs_rw_status[i] & REGISTER_WRITE_ONLY) == REGISTER_WRITE_ONLY) {
                base[i] = buf32[i];
            }
        }
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_silicon_id1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->siliconid1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_silicon_id2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->siliconid2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_wddbg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->wddbg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_wddbg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->wddbg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_mpu_status(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->mpu_status;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdmmc_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdmmc_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdmmc_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdmmc_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_usb0_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->usb0_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_usb0_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->usb0_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_usb1_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->usb1_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_usb1_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->usb1_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_global(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_global;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_global(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_global = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn0_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn0_ace;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn0_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn0_ace = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn1_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn1_ace;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn1_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn1_ace = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn2_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn2_ace;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn2_ace(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn2_ace = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga_bridge_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpga_bridge_ctrl;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_fpga_bridge_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->fpga_bridge_ctrl = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga_intf_en1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpgaintf_en_1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_fpga_intf_en1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->fpgaintf_en_1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga_intf_en2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpgaintf_en_2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_fpga_intf_en2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->fpgaintf_en_2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga_intf_en3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpgaintf_en_3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_fpga_intf_en3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->fpgaintf_en_3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dmac0_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dmac0_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dmac0_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dmac0_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_etr_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->etr_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_etr_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->etr_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dmac1_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dmac1_l3master;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dmac1_l3_master(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dmac1_l3master = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sec_ctrl_select(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sec_ctrl_slt;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sec_ctrl_select(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sec_ctrl_slt = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_osc_trim(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->osc_trim;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dmac0_ctrl_status_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dmac0_ctrl_status_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dmac0_ctrl_status_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dmac0_ctrl_status_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dmac1_ctrl_status_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dmac1_ctrl_status_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dmac1_ctrl_status_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dmac1_ctrl_status_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_ecc_intmask_value(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->ecc_intmask_value;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_ecc_intmask_value(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ecc_intmask_value = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_ecc_intmask_setbits(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ecc_intmask_value |= buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_ecc_intmask_clrbits(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ecc_intmask_value &= ~buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_ecc_intstatus_serr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->ecc_intstatus_serr;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_ecc_intstatus_derr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->ecc_intstatus_derr;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_noc_timeout(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->noc_timeout;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_noc_timeout(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->noc_timeout = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_noc_idlestatus(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->noc_idlestatus;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga2soc_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpga2soc_ctrl;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_fpga2soc_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->fpga2soc_ctrl = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_fpga_config(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->fpga_config;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_gpo(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->gpo = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_gpi(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->gpi;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_mpu(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->mpu;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_mpu(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->mpu = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_hps_spare(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_hps_spare = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_hps_sdm_spare(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->hps_sdm_spare;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_hps_sdm_spare(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->hps_sdm_spare = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dfi_interface_cfg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dfi_interface_cfg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dfi_interface_cfg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dfi_interface_cfg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_ctrl;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_dd_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_dd_ctrl = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_ctrl_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_tsel_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_tsel_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_tsel_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_tsel_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_dq_timing_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_dq_timing_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_dq_timing_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_dq_timing_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_dqs_timing_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_dqs_timing_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_dqs_timing_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_dqs_timing_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_gate_lpbk_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_gate_lpbk_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_gate_lpbk_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_gate_lpbk_ctrl_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_dll_master_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_dll_master_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_dll_master_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_dll_master_ctrl_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_phy_dll_slave_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_phy_dll_slave_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_phy_dll_slave_ctrl_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_phy_dll_slave_ctrl_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_default_setting_reg0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_default_setting_reg0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_dd_default_setting_reg0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_dd_default_setting_reg0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_default_setting_reg1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_default_setting_reg1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_dd_default_setting_reg1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_dd_default_setting_reg1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_status_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_status_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_id_low_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_id_low_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_dd_id_high_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_dd_id_high_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_nand_write_prot_en_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->nand_write_prot_en_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_nand_write_prot_en_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->nand_write_prot_en_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdmmc_cmd_queue_setting_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdmmc_cmd_queue_setting_reg;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdmmc_cmd_queue_setting_reg(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdmmc_cmd_queue_setting_reg = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_i3c_slv_pid_low(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->i3c_slv_pid_low;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_i3c_slv_pid_low(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->i3c_slv_pid_low = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_i3c_slv_pid_high(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->i3c_slv_pid_high;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_i3c_slv_pid_high(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->i3c_slv_pid_high = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_i3c_slv_ctrl0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->i3c_slv_ctrl_0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_i3c_slv_ctrl0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->i3c_slv_ctrl_0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_i3c_slv_ctrl1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->i3c_slv_ctrl_1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_i3c_slv_ctrl1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->i3c_slv_ctrl_1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_f2s_bridge_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->f2s_bridge_ctrl;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_f2s_bridge_ctrl(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->f2s_bridge_ctrl = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stash_ctrl_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stash_ctrl_reg_0_dma0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stash_ctrl_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stash_ctrl_reg_0_dma0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stash_ctrl_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stash_ctrl_reg_0_dma1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stash_ctrl_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stash_ctrl_reg_0_dma1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdm_tbu_stash_ctrl_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdm_tbu_stash_ctrl_reg_1_sdm;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_tbu_stash_ctrl_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_tbu_stash_ctrl_reg_1_sdm = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stash_ctrl_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stash_ctrl_reg_2_usb2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stash_ctrl_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stash_ctrl_reg_2_usb2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stash_ctrl_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stash_ctrl_reg_2_usb3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stash_ctrl_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stash_ctrl_reg_2_usb3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stash_ctrl_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stash_ctrl_reg_2_sdmmc;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stash_ctrl_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stash_ctrl_reg_2_sdmmc = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stash_ctrl_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stash_ctrl_reg_2_nand;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stash_ctrl_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stash_ctrl_reg_2_nand = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stash_ctrl_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stash_ctrl_reg_2_etr;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stash_ctrl_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stash_ctrl_reg_2_etr = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stash_ctrl_reg_3_tsn0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stash_ctrl_reg_3_tsn0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stash_ctrl_reg_3_tsn1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stash_ctrl_reg_3_tsn1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stash_ctrl_reg_3_tsn2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stash_ctrl_reg_3_tsn2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stream_ctrl_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stream_ctrl_reg_0_dma0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stream_ctrl_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stream_ctrl_reg_0_dma0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stream_ctrl_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stream_ctrl_reg_0_dma1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stream_ctrl_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stream_ctrl_reg_0_dma1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdm_tbu_stream_ctrl_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdm_tbu_stream_ctrl_reg_1_sdm;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_tbu_stream_ctrl_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_tbu_stream_ctrl_reg_1_sdm = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_ctrl_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_ctrl_reg_2_usb2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_ctrl_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_ctrl_reg_2_usb2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_ctrl_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_ctrl_reg_2_usb3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_ctrl_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_ctrl_reg_2_usb3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_ctrl_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_ctrl_reg_2_sdmmc;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_ctrl_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_ctrl_reg_2_sdmmc = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_ctrl_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_ctrl_reg_2_nand;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_ctrl_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_ctrl_reg_2_nand = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_ctrl_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_ctrl_reg_2_etr;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_ctrl_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_ctrl_reg_2_etr = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_ctrl_reg_3_tsn0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_ctrl_reg_3_tsn0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_ctrl_reg_3_tsn1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_ctrl_reg_3_tsn1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_ctrl_reg_3_tsn2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_ctrl_reg_3_tsn2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stream_id_ax_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stream_id_ax_reg_0_dma0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stream_id_ax_reg0_dma0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stream_id_ax_reg_0_dma0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_dma_tbu_stream_id_ax_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->dma_tbu_stream_id_ax_reg_0_dma1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_dma_tbu_stream_id_ax_reg0_dma1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_tbu_stream_id_ax_reg_0_dma1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdm_tbu_stream_id_ax_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdm_tbu_stream_id_ax_reg_1_sdm;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_tbu_stream_id_ax_reg1_sdm(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_tbu_stream_id_ax_reg_1_sdm = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_id_ax_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_id_ax_reg_2_usb2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_id_ax_reg2_usb2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_id_ax_reg_2_usb2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_id_ax_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_id_ax_reg_2_usb3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_id_ax_reg2_usb3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_id_ax_reg_2_usb3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_id_ax_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_id_ax_reg_2_sdmmc;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_id_ax_reg2_sdmmc(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_id_ax_reg_2_sdmmc = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_id_ax_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_id_ax_reg_2_nand;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_id_ax_reg2_nand(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_id_ax_reg_2_nand = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_io_tbu_stream_id_ax_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->io_tbu_stream_id_ax_reg_2_etr;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_io_tbu_stream_id_ax_reg2_etr(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_tbu_stream_id_ax_reg_2_etr = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_id_ax_reg_3_tsn0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_id_ax_reg_3_tsn0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_id_ax_reg_3_tsn1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_id_ax_reg_3_tsn1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->tsn_tbu_stream_id_ax_reg_3_tsn2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->tsn_tbu_stream_id_ax_reg_3_tsn2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_usb3_misc_ctrl_reg0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->usb3_misc_ctrl_reg0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_usb3_misc_ctrl_reg0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->usb3_misc_ctrl_reg0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_usb3_misc_ctrl_reg1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->usb3_misc_ctrl_reg1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_usb3_misc_ctrl_reg1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->usb3_misc_ctrl_reg1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold4;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold4 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold5;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold5 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold6;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold6 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold7;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold7 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold8;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold8 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_cold9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_cold9;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_cold9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_cold9 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_mpfe_config(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->mpfe_config;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_mpfe_config(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->mpfe_config = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_mpfe_status(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->mpfe_status;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm4;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm4 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm5;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm5 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm6;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm6 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm7;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm7 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm8;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm8 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_warm9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_warm9;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_warm9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_warm9 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por0;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por0(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por0 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por1;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por1(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por1 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por2;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por2(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por2 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por3;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por3(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por3 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por4;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por4(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por4 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por5;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por5(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por5 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por6;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por6(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por6 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por7;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por7(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por7 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por8;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por8(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por8 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_boot_scratch_por9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->boot_scratch_por9;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_boot_scratch_por9(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->boot_scratch_por9 = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdm_be_awaddr_remap(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdm_be_awaddr_remap;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_be_awaddr_remap(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_be_awaddr_remap = buf32[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_get_sdm_be_araddr_remap(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf32[0] = base->sdm_be_araddr_remap;
        return_value = 0;
    }
    return return_value;
}
int32_t sysmgr_set_sdm_be_araddr_remap(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    sysmgr_regs_t *base = (sysmgr_regs_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_be_araddr_remap = buf32[0];
        return_value = 0;
    }
    return return_value;
}

#ifdef __cplusplus
}
#endif // __cplusplus
