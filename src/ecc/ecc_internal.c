#include "ecc_internal.h"
#include "ecc_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls the ecc for an Altera Agilex5e HPS
*/

int32_t ecc_regs_read(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(ecc_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(ecc_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t ecc_regs_write(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(ecc_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(ecc_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ip_rev_id(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->IP_REV_ID;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ip_rev_id2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->IP_REV_ID2;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->CTRL;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_initstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->INITSTAT;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_initstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->INITSTAT = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_errinten(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ERRINTEN;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_errinten(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ERRINTEN = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_errintens(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ERRINTENS;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_errintens(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ERRINTENS = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_errintenr(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ERRINTENR;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_errintenr(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ERRINTENR = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_intmode(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->INTMODE;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_intmode(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->INTMODE = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_intstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->INTSTAT;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_intstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->INTSTAT = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_inttest(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->INTTEST;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_inttest(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->INTTEST = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_modstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->MODSTAT;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_modstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->MODSTAT = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_derraddra(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->DERRADDRA;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_serraddra(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->SERRADDRA;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_derraddrb(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->DERRADDRB;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_serraddrb(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->SERRADDRB;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_serrcntreg(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->SERRCNTREG;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_serrcntreg(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->SERRCNTREG = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_addrbus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_Addrbus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_addrbus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_Addrbus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdata0bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RData0bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdata1bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RData1bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdata2bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RData2bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdata3bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RData3bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdata0bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WData0bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdata1bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WData1bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdata2bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WData2bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdata3bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WData3bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdataecc0bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RDataecc0bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_rdataecc1bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_RDataecc1bus;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdataecc0bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WDataecc0bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdataecc1bus(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_WDataecc1bus = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_dbytectrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_dbytectrl;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_dbytectrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_dbytectrl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_accctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_accctrl;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_accctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_accctrl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_startacc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_startacc;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_startacc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_startacc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_wdctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_wdctrl;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_wdctrl(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_wdctrl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_ecc_decoderstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->ECC_DECODERSTAT;
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_ecc_decoderstat(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->ECC_DECODERSTAT = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_serrlkupa0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->SERRLKUPA0[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_serrlkupa0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->SERRLKUPA0[0] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_get_serrlkupb0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        buf[0] = ecc_reg->SERRLKUPB0[0];
        return_value = 0;
    }
    return return_value;
}

int32_t ecc_set_serrlkupb0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    ecc_regs_t *ecc_reg = (ecc_regs_t *)base_address;
    if (length >= sizeof(uint32_t)) {
        ecc_reg->SERRLKUPB0[0] = buf[0];
        return_value = 0;
    }
    return return_value;
}
