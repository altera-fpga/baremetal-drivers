#include "combophy_internal.h"
#include "combophy_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence combophy controller for an Altera Agilex5e HPS
*/
int32_t combophy_read_regs(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(combophy_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(combophy_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_write_regs(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(combophy_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(combophy_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dq_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dq_timing_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_dq_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_dq_timing_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dqs_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dqs_timing_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_dqs_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_dqs_timing_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_gate_lpbk_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_gate_lpbk_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_gate_lpbk_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_gate_lpbk_ctrl_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dll_master_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dll_master_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_dll_master_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_dll_master_ctrl_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dll_slave_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dll_slave_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_dll_slave_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_dll_slave_ctrl_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_ie_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_ie_timing_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_ie_timing(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_ie_timing_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_obs_reg_0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_obs_reg_0;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dll_obs_reg0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dll_obs_reg_0;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dll_obs_reg1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dll_obs_reg_1;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_dll_obs_reg2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_dll_obs_reg_2;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_static_togg(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_static_togg_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_static_togg(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_static_togg_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_wr_deskew(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_wr_deskew_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_wr_deskew(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_wr_deskew_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_wr_rd_deskew_cmd(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_wr_rd_deskew_cmd_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_wr_rd_deskew_cmd(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_wr_rd_deskew_cmd_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_wr_deskew_pd_ctrl0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_wr_deskew_pd_ctrl_0_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_wr_deskew_pd_ctrl0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_wr_deskew_pd_ctrl_0_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_wr_deskew_pd_ctrl1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_wr_deskew_pd_ctrl_1_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_wr_deskew_pd_ctrl1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_wr_deskew_pd_ctrl_1_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_rd_deskew(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_rd_deskew_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_rd_deskew(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_rd_deskew_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_version(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_version_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_features(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_dataslice_regs_words_t *combophy_reg =
        (combophy_dataslice_regs_words_t *)(base_address + COMBOPHY_DATASLICE_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_features_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_ctb_reg_words_t *combophy_reg = (combophy_ctb_reg_words_t *)(base_address + COMBOPHY_CTB_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_ctrl_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_ctb_reg_words_t *combophy_reg = (combophy_ctb_reg_words_t *)(base_address + COMBOPHY_CTB_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_ctrl_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_get_tsel(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    combophy_ctb_reg_words_t *combophy_reg = (combophy_ctb_reg_words_t *)(base_address + COMBOPHY_CTB_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = combophy_reg->phy_tsel_reg;
        return_value = 0;
    }
    return return_value;
}

int32_t combophy_set_tsel(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;

    combophy_ctb_reg_words_t *combophy_reg = (combophy_ctb_reg_words_t *)(base_address + COMBOPHY_CTB_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        combophy_reg->phy_tsel_reg = buf[0];
        return_value = 0;
    }
    return return_value;
}