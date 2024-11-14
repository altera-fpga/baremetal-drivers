#ifdef __cplusplus
extern "C" {
#endif

#include "sysmgr_internal.h"
#include "sysmgr_regs.h"

int32_t sysmgr_regs_read(int32_t fd, uintptr_t buf, size_t length) {
    int32_t return_value = -1;
    uint32_t *base = (uint32_t *)fd;
    uint32_t *buf32 = (uint32_t *)buf;
    if (length < sizeof(sysmgr_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(sysmgr_regs_t) / 4UL); i++) {
            buf32[i] = base[i];
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
            base[i] = buf32[i];
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