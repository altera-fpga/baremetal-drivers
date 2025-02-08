#include "noc_probe_internal.h"
#include "noc_probe_regs.h"

#include <stddef.h>
#include <stdint.h>

int32_t noc_probe_read_internal(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(noc_probe_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(noc_probe_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_write_internal(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(noc_probe_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(noc_probe_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_atbendpoint_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->atbendpoint.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_atbendpoint_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->atbendpoint.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_atbendpoint_atbid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->atbendpoint.atbid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_atbendpoint_atbid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->atbendpoint.atbid = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_atbendpoint_atben_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->atbendpoint.atben;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_atbendpoint_atben_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->atbendpoint.atben = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_faulten_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.faulten;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_errorlogger_0_faulten_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->errorlogger_0.faulten = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errvld_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errvld;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_errorlogger_0_errclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->errorlogger_0.errclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog0_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog1_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog3_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog3;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog4_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog4;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog5_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog5;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog6_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog6;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_errlog7_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.errlog7;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_errorlogger_0_stallen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->errorlogger_0.stallen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_errorlogger_0_stallen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->errorlogger_0.stallen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_stpv2converter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->stpv2converter.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_stpv2converter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->stpv2converter.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_stpv2converter_asyncperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->stpv2converter.asyncperiod;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_stpv2converter_asyncperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->stpv2converter.asyncperiod = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_stpv2converter_stpv2en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->stpv2converter.stpv2en;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_stpv2converter_stpv2en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->stpv2converter.stpv2en = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.mainctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.mainctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.cfgctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.cfgctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filterlut;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filterlut = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.tracealarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.tracealarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.tracealarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.tracealarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.statperiod;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statperiod = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statgo = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.statalarmmin;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statalarmmin = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.statalarmmax;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statalarmmax = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.statalarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statalarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.statalarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.statalarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[0].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[0].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.filters[1].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.filters[1].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[0].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[0].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[0].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[0].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[0].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[1].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[1].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[1].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[1].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[1].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[2].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[2].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[2].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[2].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[2].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[3].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[3].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[3].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_probe.counters[3].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_probe.counters[3].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.mainctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.mainctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.cfgctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.cfgctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filterlut;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filterlut = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.tracealarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.tracealarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.tracealarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.tracealarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.statperiod;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statperiod = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statgo = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.statalarmmin;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statalarmmin = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.statalarmmax;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statalarmmax = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.statalarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statalarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.statalarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.statalarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[0].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[0].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.filters[1].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.filters[1].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[0].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[0].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[0].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[0].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[0].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[1].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[1].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[1].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[1].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[1].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[2].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[2].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[2].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[2].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[2].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[3].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[3].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[3].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_probe.counters[3].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_probe.counters[3].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.mainctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.mainctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.cfgctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.cfgctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filterlut;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filterlut = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.tracealarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.tracealarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.tracealarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.tracealarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.statperiod;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statperiod = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statgo = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.statalarmmin;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statalarmmin = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.statalarmmax;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statalarmmax = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.statalarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statalarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.statalarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.statalarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[0].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[0].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.filters[1].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.filters[1].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[0].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[0].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[0].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[0].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[0].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[1].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[1].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[1].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[1].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[1].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[2].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[2].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[2].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[2].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[2].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[3].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[3].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[3].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_soc2fpga_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->soc2fpga_probe.counters[3].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_soc2fpga_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->soc2fpga_probe.counters[3].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.en;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.en = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.thresholds_0[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.thresholds_0[0] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.thresholds_0[1];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.thresholds_0[1] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.thresholds_0[2];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.thresholds_0[2] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_overflowstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.overflowstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_overflowreset_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.overflowreset = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.pendingeventmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.pendingeventmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatprofiler.prescaler;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatprofiler.prescaler = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.mainctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.mainctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.cfgctl;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.cfgctl = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filterlut;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filterlut = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.tracealarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.tracealarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.tracealarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.tracealarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.statperiod;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statperiod = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statgo = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.statalarmmin;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statalarmmin = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.statalarmmax;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statalarmmax = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.statalarmstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statalarmclr = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.statalarmen;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.statalarmen = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[0].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[0].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].routeidbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].routeidbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].routeidmask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].routeidmask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].windowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].windowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].status;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].status = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].length;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].length = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.filters[1].urgency;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.filters[1].urgency = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[0].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[0].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[0].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[0].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[0].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[1].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[1].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[1].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[1].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[1].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[2].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[2].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[2].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[2].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[2].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[3].src;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[3].src = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[3].alarmmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_probe.counters[3].alarmmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_probe.counters[3].val;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.en;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.en = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.thresholds_0[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.thresholds_0[0] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.thresholds_0[1];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.thresholds_0[1] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.thresholds_0[2];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.thresholds_0[2] = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_overflowstatus_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.overflowstatus;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_overflowreset_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.overflowreset = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.pendingeventmode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.pendingeventmode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatprofiler.prescaler;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatprofiler.prescaler = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.priority;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_qosgenerator.priority = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_qosgenerator.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.bandwidth;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_qosgenerator.bandwidth = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.saturation;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_qosgenerator.saturation = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_ccu_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->ccu_qosgenerator.extcontrol;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_ccu_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->ccu_qosgenerator.extcontrol = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.priority;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_dma_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_qosgenerator.priority = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_dma_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_qosgenerator.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.bandwidth;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_dma_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_qosgenerator.bandwidth = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.saturation;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_dma_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_qosgenerator.saturation = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_dma_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->dma_qosgenerator.extcontrol;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_dma_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->dma_qosgenerator.extcontrol = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.priority;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_qosgenerator.priority = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_qosgenerator.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.bandwidth;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_qosgenerator.bandwidth = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.saturation;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_qosgenerator.saturation = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_qosgenerator.extcontrol;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_qosgenerator.extcontrol = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.priority;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_qosgenerator.priority = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_qosgenerator.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.bandwidth;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_qosgenerator.bandwidth = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.saturation;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_qosgenerator.saturation = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_qosgenerator.extcontrol;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_qosgenerator.extcontrol = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.priority;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_sdm_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_qosgenerator.priority = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_sdm_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_qosgenerator.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.bandwidth;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_sdm_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_qosgenerator.bandwidth = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.saturation;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_sdm_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_qosgenerator.saturation = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_sdm_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->sdm_qosgenerator.extcontrol;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_sdm_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->sdm_qosgenerator.extcontrol = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.addrwindowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.addrwindowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.userbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.userbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.usermask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.usermask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.userbasehigh;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.userbasehigh = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_emac_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->emac_transactionstatfilter.usermaskhigh;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_emac_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->emac_transactionstatfilter.usermaskhigh = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.id_coreid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.id_revisionid;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.mode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.mode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.addrbase_low;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.addrbase_low = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.addrbase_high;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.addrbase_high = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.addrwindowsize;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.addrwindowsize = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.opcode;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.opcode = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.userbase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.userbase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.usermask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.usermask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.securitybase;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.securitybase = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.securitymask;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.securitymask = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.userbasehigh;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.userbasehigh = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_get_io_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->io_transactionstatfilter.usermaskhigh;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_probe_set_io_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)buffer;
    noc_probe_regs_t *base = (noc_probe_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->io_transactionstatfilter.usermaskhigh = buf[0];
        return_value = 0;
    }
    return return_value;
}
