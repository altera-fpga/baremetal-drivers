#include "rstmgr_internal.h"
#include "rstmgr_regs.h"
#include <string.h>

const uint32_t rstmgr_valid_indices[] = {
    0 /* stat */,
    2 /* miscstat */,
    4 /*  hdsken */,
    7 /* hdskreq */,
    6 /* hdskack */,
    7 /* hdskstall */,
    9 /* per0modrst */,
    10 /* per1modrst */,
    11 /* brgmodrst */,
    15 /* dbgmodrst */,
    19 /* brgwarmmask */,
    23 /* tststa */,
    25 /* hdsktimeout */,
    27 /* dbghdsktimeout */,
    28 /* dbgrstcmplt */,
    32 /* hpsrstcmplt */,
    36 /* cpuinreset */,
    37 /* cpurstrelease */,
    38 /* cpu0_reset_base_low */,
    39 /* cpu0_reset_base_high */,
    40 /* cpu1_reset_base_low */,
    41 /* cpu1_reset_base_high */,
    42 /* cpu2_reset_base_low */,
    43 /* cpu2_reset_base_high */,
    44 /* cpu3_reset_base_low */,
    45 /* cpu3_reset_base_high */,
};

static bool rstmgr_offset_is_valid(size_t index) {
    bool return_value = false;
    for (size_t i = 0; i < (sizeof(rstmgr_valid_indices) / sizeof(uint32_t)); i++) {
        if (rstmgr_valid_indices[i] == index) {
            return_value = true;
        }
    }
    return return_value;
}
int32_t rstmgr_regs_read(int32_t fd, uintptr_t arg, size_t size) {
    uint32_t *base = (uint32_t *)((uintptr_t)fd);
    int32_t return_value = -1;
    if (size < sizeof(hps_rstmgr_regs_t)) {
        return_value = -1;
    } else {
        for (size_t i = 0; i < (sizeof(hps_rstmgr_regs_t) / sizeof(uint32_t)); i++) {
            if (rstmgr_offset_is_valid(i)) {
                ((uint32_t *)arg)[i] = base[i];
            }
        }
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_regs_write(int32_t fd, uintptr_t arg, size_t size) {
    uint32_t *base = (uint32_t *)((uintptr_t)fd);
    int32_t return_value = -1;
    if (size < sizeof(hps_rstmgr_regs_t)) {
        return_value = -1;
    } else {
        for (size_t i = 0; i < (sizeof(hps_rstmgr_regs_t) / sizeof(uint32_t)); i++) {
            if (rstmgr_offset_is_valid(i)) {
                base[i] = ((uint32_t *)arg)[i];
            }
        }
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_stat(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->stat;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_stat(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // Behavior of stat reg is 'write 1 to clear'
        regs->stat = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_miscstat(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->miscstat;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_miscstat(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // Behavior of miscstat reg is 'write 1 to clear'
        regs->miscstat = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_hdsk_en(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hdsken;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_hdsk_en(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->hdsken = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_hdsk_req(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hdskreq;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_hdsk_req(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->hdskreq = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_hdsk_ack(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hdskack;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_hdsk_ack(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // behavior of hdskack reg is 'write 1 to set'
        regs->hdskack = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_hdsk_stall(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hdskstall;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_hdsk_stall(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // behavior of hdskstall reg is 'write 1 to clear'
        regs->hdskstall = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_per0_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->per0modrst;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_per0_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->per0modrst = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_per1_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->per1modrst;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_per1_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->per1modrst = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_brg_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->brgmodrst;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_brg_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->brgmodrst = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_dbg_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->dbgmodrst;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_dbg_modrst(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->dbgmodrst = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_brg_warmmask(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->brgwarmmask;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_brg_warmmask(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->brgwarmmask = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_tst_sta(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->tststa;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hdsktimeout;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->hdsktimeout = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_dbg_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->dbghdsktimeout;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_dbg_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->dbghdsktimeout = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_dbg_rst_cmplt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->dbgrstcmplt;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_dbg_rst_cmplt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // behavior of dbgrstcmplt reg is 'write 1 to clear'
        regs->dbgrstcmplt = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_get_hps_rst_cmplt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->hpsrstcmplt;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_hps_rst_cmplt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // behavior of hpsrstcmplt reg is 'write 1 to clear'
        regs->hpsrstcmplt = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu_in_reset(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpuinreset;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu_rst_release(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpurstrelease;
        return_value = 0;
    }
    return return_value;
}

int32_t rstmgr_set_cpu_rst_release(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        // behavior of cpurstrelease reg is 'write 1 to set'
        regs->cpurstrelease = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu0_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu0_reset_base_low;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu0_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu0_reset_base_low = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu0_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu0_reset_base_high;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu0_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu0_reset_base_high = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu1_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu1_reset_base_low;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu1_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu1_reset_base_low = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu1_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu1_reset_base_high;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu1_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu1_reset_base_high = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu2_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu2_reset_base_low;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu2_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu2_reset_base_low = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu2_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu2_reset_base_high;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu2_reset_base_high(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu2_reset_base_high = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_get_cpu3_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = regs->cpu3_reset_base_low;
        return_value = 0;
    }
    return return_value;
}
int32_t rstmgr_set_cpu3_reset_base_low(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_rstmgr_regs_t *regs = (hps_rstmgr_regs_t *)((uintptr_t)fd);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->cpu3_reset_base_low = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}