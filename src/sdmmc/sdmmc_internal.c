#include "sdmmc_internal.h"
#include "sdmmc_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence SDMMC controller for an Altera Agilex5e HPS
*/
int32_t sdmmc_read_internal(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(sdmmc_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(sdmmc_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_write_internal(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(sdmmc_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(sdmmc_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t sdmmc_get_hrs00(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS00;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs00(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS00 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs00_swr(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS00 = (buf[0] << SDMMC_HRS_HRS00_SWR_SET_OFST) & SDMMC_HRS_HRS00_SWR_SET_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs01(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS01;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs01(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS01 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS02;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS02 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS03;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS03 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs04(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS04;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs04(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS04 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs05(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS05;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs05(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS05 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs06(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS06;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs06(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS06 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs07(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS07;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs07(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS07 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS08;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS08 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs08_phy_dll_updreq(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS08 = (buf[0] << SDMMC_HRS_HRS08_PHY_DLL_UPDREQ_OFST) & SDMMC_HRS_HRS08_PHY_DLL_UPDREQ_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs09(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS09;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_phy_sw_reset(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_PHY_SW_RESET_OFST) & SDMMC_HRS_HRS09_PHY_SW_RESET_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_extended_rd_mode(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_EXTENDED_RD_MODE_OFST) & SDMMC_HRS_HRS09_EXTENDED_RD_MODE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_extended_wr_mode(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_EXTENDED_WR_MODE_OFST) & SDMMC_HRS_HRS09_EXTENDED_WR_MODE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_rdcmd_en(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_RDCMD_EN_OFST) & SDMMC_HRS_HRS09_RDCMD_EN_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_rddata_en(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_RDDATA_EN_OFST) & SDMMC_HRS_HRS09_RDDATA_EN_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_lvsi_tcksel(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_LVSI_TCKSEL_OFST) & SDMMC_HRS_HRS09_LVSI_TCKSEL_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs09_lvsi_cnt(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS09 = (buf[0] << SDMMC_HRS_HRS09_LVSI_CNT_OFST) & SDMMC_HRS_HRS09_LVSI_CNT_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS10;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS10 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs12(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS12;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs12(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS12 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs13(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS13;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs13(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS13 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS14;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS14 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs16(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS16;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs16(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS16 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs29(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS29;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs30(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS30;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs31(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS31;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs32(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS32;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs32(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS32 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs32_addr(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS32 = (buf[0] << SDMMC_HRS_HRS32_ADDR_OFST) & SDMMC_HRS_HRS32_ADDR_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_hrs32_load(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->HRS32 = (buf[0] << SDMMC_HRS_HRS32_LOAD_OFST) & SDMMC_HRS_HRS32_LOAD_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs33(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS33;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_hrs34(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_hrs_regs_words_t *sdmmc_reg = (sdmmc_hrs_regs_words_t *)(base_address + SDMMC_HRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->HRS34;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs00(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS00;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs00(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS00 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs01(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS01;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs01(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS01 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS02;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS02 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS03;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS03 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs04(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS04;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs05(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS05;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs06(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS06;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs07(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS07;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS08;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS08 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs09(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS09;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS10;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS10 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs11(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS11;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11_ice(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_ICE_OFST) & SDMMC_SRS_SRS11_ICE_MASK;
        return_value = 0;
    }
    return return_value;
}

int32_t sdmmc_set_srs11_sdce(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SDCE_OFST) & SDMMC_SRS_SRS11_SDCE_MASK;
        return_value = 0;
    }
    return return_value;
}

int32_t sdmmc_set_srs11_sdcfsh(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SDCFSH_OFST) & SDMMC_SRS_SRS11_SDCFSH_MASK;
        return_value = 0;
    }
    return return_value;
}

int32_t sdmmc_set_srs11_sdcfsl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SDCFSL_OFST) & SDMMC_SRS_SRS11_SDCFSL_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11_dtcv(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_DTCV_OFST) & SDMMC_SRS_SRS11_DTCV_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11_srfa(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SRFA_OFST) & SDMMC_SRS_SRS11_SRFA_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11_srcmd(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SRCMD_OFST) & SDMMC_SRS_SRS11_SRCMD_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs11_srdat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS11 = (buf[0] << SDMMC_SRS_SRS11_SRDAT_OFST) & SDMMC_SRS_SRS11_SRDAT_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs12(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS12;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs12(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS12 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs13(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS13;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs13(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS13 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS14;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS14 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs15(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS15;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_ums(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_UMS_OFST) & SDMMC_SRS_SRS15_UMS_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_v18se(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_V18SE_OFST) & SDMMC_SRS_SRS15_V18SE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_dss(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_DSS_OFST) & SDMMC_SRS_SRS15_DSS_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_extng(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_EXTNG_OFST) & SDMMC_SRS_SRS15_EXTNG_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_scs(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_SCS_OFST) & SDMMC_SRS_SRS15_SCS_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_lvsiexec(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_LVSIEXEC_OFST) & SDMMC_SRS_SRS15_LVSIEXEC_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_adma2lm(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_ADMA2LM_OFST) & SDMMC_SRS_SRS15_ADMA2LM_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_cmd23e(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_CMD23E_OFST) & SDMMC_SRS_SRS15_CMD23E_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_hv4e(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_HV4E_OFST) & SDMMC_SRS_SRS15_HV4E_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_a64b(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_A64B_OFST) & SDMMC_SRS_SRS15_A64B_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs15_pve(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS15 = (buf[0] << SDMMC_SRS_SRS15_PVE_OFST) & SDMMC_SRS_SRS15_PVE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs16(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS16;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs17(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS17;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs18(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS18;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs19(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS19;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs20(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS20;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs20(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS20 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs21(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS21;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs22(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS22;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs22(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS22 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs23(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS23;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs23(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS22 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs24(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS24;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs25(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS25;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs26(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS26;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs27(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS27;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs30(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS30;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs30(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS30 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_srs31(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->SRS31;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_srs31(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_srs_regs_words_t *sdmmc_reg = (sdmmc_srs_regs_words_t *)(base_address + SDMMC_SRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->SRS31 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_crs63(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_crs_regs_words_t *sdmmc_reg = (sdmmc_crs_regs_words_t *)(base_address + SDMMC_CRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CRS63;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs00(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS00;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs01(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS01;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS02;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs02(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS02 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS03;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs03(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS03 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs04(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS04;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs04(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS04 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs05(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS05;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs05(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS05 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs06(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS06;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs06(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS06 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs07(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS07;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqictoval(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICTOVAL_OFST) & SDMMC_CQRS_CQRS07_CQICTOVAL_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqictovalen(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICTOVALEN_OFST) & SDMMC_CQRS_CQRS07_CQICTOVALEN_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqiccth(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICCTH_OFST) & SDMMC_CQRS_CQRS07_CQICCTH_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqiccthwen(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICCTHWEN_OFST) & SDMMC_CQRS_CQRS07_CQICCTHWEN_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqicctr(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICCTR_OFST) & SDMMC_CQRS_CQRS07_CQICCTR_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs07_cqiced(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS07 = (buf[0] << SDMMC_CQRS_CQRS07_CQICED_OFST) & SDMMC_CQRS_CQRS07_CQICED_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS08;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs08(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS08 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs09(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS09;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs09(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS09 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS10;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs10(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS10 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs11(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS11;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs11(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS11 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs12(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS12;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs13(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS13;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS14;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs14(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS14 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs16(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS16;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs16(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS16 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs17(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS17;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs17(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS17 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs18(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS18;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs20(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS20;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_set_cqrs20(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        sdmmc_reg->CQRS20 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs21(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS21;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs22(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS22;
        return_value = 0;
    }
    return return_value;
}
int32_t sdmmc_get_cqrs23(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    sdmmc_cqrs_regs_words_t *sdmmc_reg = (sdmmc_cqrs_regs_words_t *)(base_address + SDMMC_CQRS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = sdmmc_reg->CQRS23;
        return_value = 0;
    }
    return return_value;
}