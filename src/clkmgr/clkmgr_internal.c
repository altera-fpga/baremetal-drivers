#include "clkmgr_internal.h"
#include "clkmgr_regs.h"
#include <string.h>

int32_t clkmgr_regs_read(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_regs_t) / sizeof(uint32_t)); i++) {
        regs[i] = base[i];
    }
    return 0;
}

int32_t clkmgr_regs_write(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_regs_t) / sizeof(uint32_t)); i++) {
        base[i] = regs[i];
    }
    return 0;
}

int32_t clkmgr_mainpll_regs_read(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_MAINPLL_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_mainpll_regs_t) / sizeof(uint32_t)); i++) {
        // Skip the pad location at 0x18 (index 6)
        if (i != 6UL /* _pad_0x18_0x1b */) {
            regs[i] = base[i];
        }
    }
    return 0;
}

int32_t clkmgr_mainpll_regs_write(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_MAINPLL_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_mainpll_regs_t) / sizeof(uint32_t)); i++) {
        // Skip the pad location at 0x18 (index 6)
        if (i != 6UL /* _pad_0x18_0x1b */) {
            base[i] = regs[i];
        }
    }
    return 0;
}

int32_t clkmgr_perpll_regs_read(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_PERPLL_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_perpll_regs_t) / sizeof(uint32_t)); i++) {
        regs[i] = base[i];
    }
    return 0;
}

int32_t clkmgr_perpll_regs_write(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_PERPLL_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_perpll_regs_t) / sizeof(uint32_t)); i++) {
        base[i] = regs[i];
    }
    return 0;
}

int32_t clkmgr_ctlgrp_regs_read(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_CTLGRP_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_ctlgrp_regs_t) / sizeof(uint32_t)); i++) {
        // skip the pad location at 0x14 (index 5)
        if (i != 5UL /* _pad_0x14_0x17 */) {
            regs[i] = base[i];
        }
    }
    return 0;
}

int32_t clkmgr_ctlgrp_regs_write(uintptr_t arg) {
    uint32_t *regs = (uint32_t *)arg;
    uint32_t *base = (uint32_t *)HPS_CLKMGR_CTLGRP_REGS_BASE;
    for (uint32_t i = 0; i < (sizeof(hps_clkmgr_ctlgrp_regs_t) / sizeof(uint32_t)); i++) {
        // skip the pad loaction at 0x14 (index 5)
        if (i != 5UL /* _pad_0x14_0x17 */) {
            base[i] = regs[i];
        }
    }
    return 0;
}
