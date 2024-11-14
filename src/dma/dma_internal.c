#include "dma_internal.h"
#include "dma_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence DMA controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t dma_read_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(dma_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(dma_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t dma_write_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(dma_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(dma_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t dma_get_id_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->IDREG;

    return return_value;
}
int32_t dma_get_comp_ver_no_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->COMPVERREG;

    return return_value;
}

int32_t dma_set_cfg_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->CFGREG = buf[0];

    return return_value;
}
int32_t dma_get_cfg_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->CFGREG;

    return return_value;
}

int32_t dma_set_chen_enable_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->CHENREG = buf[0];

    return return_value;
}

int32_t dma_get_chen_enable_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->CHENREG;

    return return_value;
}
int32_t dma_get_int_status_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->INTSTATUSREG;

    return return_value;
}
int32_t dma_set_common_int_clear_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->COMMONREG_INTCLEARREG = buf[0];

    return return_value;
}
int32_t dma_set_common_int_sts_en_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->COMMONREG_INTSTATUS_ENABLEREG = buf[0];

    return return_value;
}

int32_t dma_get_common_int_sts_en_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->COMMONREG_INTSTATUS_ENABLEREG;

    return return_value;
}
int32_t dma_set_common_int_sig_en_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->COMMONREG_INTSIGNAL_ENABLEREG = buf[0];

    return return_value;
}
int32_t dma_get_common_int_sig_en_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->COMMONREG_INTSIGNAL_ENABLEREG;

    return return_value;
}
int32_t dma_get_common_int_status_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->COMMONREG_INTSTATUSREG;

    return return_value;
}
int32_t dma_set_reset_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->RESETREG = buf[0];

    return return_value;
}
int32_t dma_get_reset_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->RESETREG;

    return return_value;
}
int32_t dma_set_low_power_cfg_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->LOWPOWER_CFGREG = buf[0];

    return return_value;
}

int32_t dma_get_low_power_cfg_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->LOWPOWER_CFGREG;

    return return_value;
}
int32_t dma_ch_set_src_addr_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].SAR = buf[0];

    return return_value;
}
int32_t dma_ch_get_src_addr_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].SAR;

    return return_value;
}
int32_t dma_ch_set_dst_addr_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].DAR = buf[0];

    return return_value;
}
int32_t dma_ch_get_dst_addr_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].DAR;

    return return_value;
}
int32_t dma_ch_set_blk_tran_size_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].BLOCK_TS = buf[0];

    return return_value;
}
int32_t dma_ch_get_blk_tran_size_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].BLOCK_TS;

    return return_value;
}

int32_t dma_ch_set_trans_ctl_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].CTL = buf[0];

    return return_value;
}
int32_t dma_ch_get_trans_ctl_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].CTL;

    return return_value;
}
int32_t dma_ch_set_trans_cfg2_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].CFG2 = buf[0];

    return return_value;
}
int32_t dma_ch_get_trans_cfg2_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].CFG2;

    return return_value;
}
int32_t dma_ch_set_linked_list_point_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].LLP |= buf[0];

    return return_value;
}
int32_t dma_ch_get_linked_list_point_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].LLP;

    return return_value;
}
int32_t dma_ch_get_status_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].STATUSREG;

    return return_value;
}

int32_t dma_ch_get_sw_hsk_src_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].SWHSSRCREG;

    return return_value;
}
int32_t dma_ch_set_sw_hsk_src_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].SWHSSRCREG = buf[0];

    return return_value;
}
int32_t dma_ch_get_sw_hsk_dst_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].SWHSDSTREG;

    return return_value;
}
int32_t dma_ch_set_sw_hsk_dst_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].SWHSDSTREG = buf[0];

    return return_value;
}
int32_t dma_ch_set_blk_tfr_resume_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].BLK_TFR_RESUMEREQREG = buf[0];

    return return_value;
}
int32_t dma_ch_set_axi_id_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].AXI_IDREG = buf[0];

    return return_value;
}
int32_t dma_ch_get_axi_id_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].AXI_IDREG;

    return return_value;
}
int32_t dma_ch_set_axi_qos_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].AXI_QOSREG = buf[0];

    return return_value;
}
int32_t dma_ch_get_axi_qos_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].AXI_QOSREG;

    return return_value;
}
int32_t dma_ch_set_int_status_en_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].INTSTATUS_ENABLEREG = buf[0];

    return return_value;
}
int32_t dma_ch_get_int_status_en_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].INTSTATUS_ENABLEREG;

    return return_value;
}
int32_t dma_ch_get_int_status_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].INTSTATUS;

    return return_value;
}
int32_t dma_ch_set_int_signal_en_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].INTSIGNAL_ENABLEREG = buf[0];

    return return_value;
}
int32_t dma_ch_get_int_signal_en_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    buf[0] = base->dma_ch[channel].INTSIGNAL_ENABLEREG;

    return return_value;
}
int32_t dma_ch_set_int_clear_reg(int32_t fd, uintptr_t args, int32_t channel) {
    int32_t return_value = 0;
    uint64_t *buf = (uint64_t *)args;
    dma_regs_t *base = (dma_regs_t *)fd;

    base->dma_ch[channel].INTCLEARREG = buf[0];

    return return_value;
}