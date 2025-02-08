#include "ccu_internal.h"
#include "ccu_regs.h"

#include <stddef.h>
#include <stdint.h>

#include <stdio.h>

/*
This code controls a cadence CCU controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t ccu_read_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(ccu_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(ccu_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t ccu_write_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(ccu_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(ccu_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

// CAIU0 registers (DSU)
int32_t ccu_dsu_get_caiuidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuidr;
    return return_value;
}

int32_t ccu_dsu_get_caiufuidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiufuidr;
    return return_value;
}

int32_t ccu_dsu_get_caiutcr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutcr;
    return return_value;
}

int32_t ccu_dsu_set_caiutcr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutcr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutar;
    return return_value;
}

int32_t ccu_dsu_get_caiuuedr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuedr;
    return return_value;
}

int32_t ccu_dsu_set_caiuuedr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuuedr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuueir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuueir;
    return return_value;
}

int32_t ccu_dsu_set_caiuueir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuueir = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuuesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuesr;
    return return_value;
}

int32_t ccu_dsu_set_caiuuesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuuesr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuuelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuelr0;
    return return_value;
}

int32_t ccu_dsu_set_caiuuelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuuelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuelr1;
    return return_value;
}

int32_t ccu_dsu_set_caiuuelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuuesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuesar;
    return return_value;
}

int32_t ccu_dsu_set_caiuuesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuuesar = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucrtr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucrtr;
    return return_value;
}

int32_t ccu_dsu_set_caiucrtr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucrtr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutocr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutocr;
    return return_value;
}

int32_t ccu_dsu_set_caiutocr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutocr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuqoscr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuqoscr;
    return return_value;
}

int32_t ccu_dsu_set_caiuqoscr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuqoscr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuqossr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuqossr;
    return return_value;
}

int32_t ccu_dsu_set_caiuqossr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuqossr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_nrsbar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.nrsbar;
    return return_value;
}

int32_t ccu_dsu_set_nrsbar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.nrsbar = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_nrsbhr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.nrsbhr;
    return return_value;
}

int32_t ccu_dsu_set_nrsbhr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.nrsbhr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_nrsblr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.nrsblr;
    return return_value;
}

int32_t ccu_dsu_set_nrsblr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.nrsblr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiubrar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiubrar;
    return return_value;
}

int32_t ccu_dsu_set_caiubrar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiubrar = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiubrblr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiubrblr;
    return return_value;
}

int32_t ccu_dsu_set_caiubrblr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiubrblr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiubrbhr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiubrbhr;
    return return_value;
}

int32_t ccu_dsu_set_caiubrbhr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiubrbhr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuamigr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuamigr;
    return return_value;
}

int32_t ccu_dsu_set_caiuamigr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiuamigr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiumifsr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiumifsr;
    return return_value;
}

int32_t ccu_dsu_set_caiumifsr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiumifsr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprar0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprar0;
    return return_value;
}

int32_t ccu_dsu_set_caiugprar0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprar0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprblr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprblr0;
    return return_value;
}

int32_t ccu_dsu_set_caiugprblr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprblr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprbhr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprbhr0;
    return return_value;
}

int32_t ccu_dsu_set_caiugprbhr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprbhr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprar1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprar1;
    return return_value;
}

int32_t ccu_dsu_set_caiugprar1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprar1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprblr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprblr1;
    return return_value;
}

int32_t ccu_dsu_set_caiugprblr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprblr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprbhr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprbhr1;
    return return_value;
}

int32_t ccu_dsu_set_caiugprbhr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprbhr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprar2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprar2;
    return return_value;
}

int32_t ccu_dsu_set_caiugprar2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprar2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprblr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprblr2;
    return return_value;
}

int32_t ccu_dsu_set_caiugprblr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprblr2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprbhr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprbhr2;
    return return_value;
}

int32_t ccu_dsu_set_caiugprbhr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprbhr2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprar11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprar11;
    return return_value;
}

int32_t ccu_dsu_set_caiugprar11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprar11 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprblr11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprblr11;
    return return_value;
}

int32_t ccu_dsu_set_caiugprblr11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprblr11 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiugprbhr11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiugprbhr11;
    return return_value;
}

int32_t ccu_dsu_set_caiugprbhr11_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiugprbhr11 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucctrlr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucctrlr;
    return return_value;
}

int32_t ccu_dsu_set_caiucctrlr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucctrlr = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutctrlr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutctrlr0;
    return return_value;
}

int32_t ccu_dsu_set_caiutctrlr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutctrlr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutbalr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutbalr0;
    return return_value;
}

int32_t ccu_dsu_set_caiutbalr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutbalr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutbahr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutbahr0;
    return return_value;
}

int32_t ccu_dsu_set_caiutbahr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutbahr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutopcr00_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutopcr00;
    return return_value;
}

int32_t ccu_dsu_set_caiutopcr00_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutopcr00 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutopcr10_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutopcr10;
    return return_value;
}

int32_t ccu_dsu_set_caiutopcr10_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutopcr10 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutubr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutubr0;
    return return_value;
}

int32_t ccu_dsu_set_caiutubr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutubr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiutubmr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiutubmr0;
    return return_value;
}

int32_t ccu_dsu_set_caiutubmr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiutubmr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntcr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntcr0;
    return return_value;
}

int32_t ccu_dsu_set_caiucntcr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntcr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntvr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntvr0;
    return return_value;
}

int32_t ccu_dsu_set_caiucntvr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntvr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntsr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntsr0;
    return return_value;
}

int32_t ccu_dsu_set_caiucntsr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntsr0 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntcr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntcr1;
    return return_value;
}

int32_t ccu_dsu_set_caiucntcr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntcr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntvr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntvr1;
    return return_value;
}

int32_t ccu_dsu_set_caiucntvr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntvr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntsr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntsr1;
    return return_value;
}

int32_t ccu_dsu_set_caiucntsr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntsr1 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntcr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntcr2;
    return return_value;
}

int32_t ccu_dsu_set_caiucntcr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntcr2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntvr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntvr2;
    return return_value;
}

int32_t ccu_dsu_set_caiucntvr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntvr2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntsr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntsr2;
    return return_value;
}

int32_t ccu_dsu_set_caiucntsr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntsr2 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntcr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntcr3;
    return return_value;
}

int32_t ccu_dsu_set_caiucntcr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntcr3 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntvr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntvr3;
    return return_value;
}

int32_t ccu_dsu_set_caiucntvr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntvr3 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiucntsr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiucntsr3;
    return return_value;
}

int32_t ccu_dsu_set_caiucntsr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiucntsr3 = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiunrsar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiunrsar;
    return return_value;
}

int32_t ccu_dsu_set_caiunrsar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dsu.caiunrsar = buf[0];
    return return_value;
}

int32_t ccu_dsu_get_caiuuevir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuuevir;
    return return_value;
}

int32_t ccu_dsu_get_caiuinfor_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dsu.caiuinfor;
    return return_value;
}

// NCAIUx registers (FPGA2SOC, GIC_M, TCU, and CCU_IOM)

int32_t ccu_ncaiu_get_xaiuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuidr;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiufuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiufuidr;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutcr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutcr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutar;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuuedr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuuedr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuueir;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuueir = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuuesr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuuesr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuuelr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuuelr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuuesar;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuuesar = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucecr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucecr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucesr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucesr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucelr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucelr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucelr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucelr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucesar;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucesar = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucrtr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucrtr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucrtr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucrtr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutocr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutocr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuqoscr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuqoscr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuqoscr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuqoscr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuqossr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuqossr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuqossr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuqossr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiunrsbar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiunrsbar;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiunrsbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiunrsbhr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiunrsbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiunrsbhr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiunrsblr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiunrsblr;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiubrar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiubrar;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiubrar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiubrar = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiubrblr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiubrblr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiubrblr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiubrblr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiubrbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiubrbhr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiubrbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiubrbhr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuamigr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuamigr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuamigr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuamigr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiumifsr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiumifsr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiumifsr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiumifsr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar4;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar4 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr4;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr4 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr4;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr4 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar5;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar5 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr5;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr5 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr5;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr5 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar6;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar6 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr6;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr6 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr6;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr6 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar7;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar7 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr7;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr7 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr7;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr7 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar8;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar8 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr8;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr8 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr8;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr8 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar9;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar9 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr9;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr9 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr9;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr9 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar10;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar10 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr10;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr10 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr10;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr10 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprar11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprar11;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprar11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprar11 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprblr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprblr11;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprblr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprblr11 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiugprbhr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiugprbhr11;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiugprbhr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiugprbhr11 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutbalr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutbalr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutbalr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutbalr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutbahr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutbahr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutbahr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutbahr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutopcr00_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutopcr00;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutopcr00_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutopcr00 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutopcr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutopcr10;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutopcr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutopcr10 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutubr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutubr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutubr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutubr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutubmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutubmr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutubmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutubmr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucctrlr;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucctrlr = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiutctrlr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiutctrlr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiutctrlr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiutctrlr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr4;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr4 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr5;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr5 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr6;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr6 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuedr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuedr7;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiuedr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiuedr7 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntcr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntcr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntvr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntvr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntsr0;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntsr0 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntcr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntcr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntvr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntvr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntsr1;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntsr1 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntcr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntcr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntvr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntvr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntsr2;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntsr2 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntcr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntcr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntvr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntvr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiucntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiucntsr3;
    return return_value;
}

int32_t ccu_ncaiu_set_xaiucntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->ncaiu[reg_offset].xaiucntsr3 = buf[0];
    return return_value;
}

int32_t ccu_ncaiu_get_xaiunrsar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiunrsar;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuengidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuengidr;
    return return_value;
}

int32_t ccu_ncaiu_get_xaiuinfor_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->ncaiu[reg_offset].xaiuinfor;
    return return_value;
}

// DCE registers

int32_t ccu_dce_get_dceuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuidr;
    return return_value;
}

int32_t ccu_dce_get_dceufuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceufuidr;
    return return_value;
}

int32_t ccu_dce_get_dceutcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceutcr;
    return return_value;
}

int32_t ccu_dce_set_dceutcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceutcr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceutar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceutar;
    return return_value;
}

int32_t ccu_dce_get_dceuser0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuser0;
    return return_value;
}

int32_t ccu_dce_set_dceuser0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuser0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceucecr;
    return return_value;
}

int32_t ccu_dce_set_dceucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceucecr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceucesr;
    return return_value;
}

int32_t ccu_dce_set_dceucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceucesr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceucelr0;
    return return_value;
}

int32_t ccu_dce_set_dceucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceucelr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceucelr1;
    return return_value;
}

int32_t ccu_dce_set_dceucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceucelr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceucesar;
    return return_value;
}

int32_t ccu_dce_set_dceucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceucesar = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuuedr;
    return return_value;
}

int32_t ccu_dce_set_dceuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuuedr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuueir;
    return return_value;
}

int32_t ccu_dce_set_dceuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuueir = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuuesr;
    return return_value;
}

int32_t ccu_dce_set_dceuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuuesr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuuelr0;
    return return_value;
}

int32_t ccu_dce_set_dceuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuuelr1;
    return return_value;
}

int32_t ccu_dce_set_dceuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuuesar;
    return return_value;
}

int32_t ccu_dce_set_dceuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuuesar = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceutocr;
    return return_value;
}

int32_t ccu_dce_set_dceutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceutocr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuqoscr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuqoscr0;
    return return_value;
}

int32_t ccu_dce_set_dceuqoscr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuqoscr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceusfmcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceusfmcr;
    return return_value;
}

int32_t ccu_dce_set_dceusfmcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceusfmcr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceusfmar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceusfmar;
    return return_value;
}

int32_t ccu_dce_get_dceubrar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceubrar;
    return return_value;
}

int32_t ccu_dce_set_dceubrar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceubrar = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceubrblr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceubrblr;
    return return_value;
}

int32_t ccu_dce_set_dceubrblr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceubrblr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceubrbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceubrbhr;
    return return_value;
}

int32_t ccu_dce_set_dceubrbhr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceubrbhr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuamigr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuamigr;
    return return_value;
}

int32_t ccu_dce_set_dceuamigr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuamigr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceumifsr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceumifsr;
    return return_value;
}

int32_t ccu_dce_set_dceumifsr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceumifsr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar0;
    return return_value;
}

int32_t ccu_dce_set_dceugprar0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr0;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr0;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar1;
    return return_value;
}

int32_t ccu_dce_set_dceugprar1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr1;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr1;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar2;
    return return_value;
}

int32_t ccu_dce_set_dceugprar2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr2;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr2;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar3;
    return return_value;
}

int32_t ccu_dce_set_dceugprar3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr3;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr3;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar4;
    return return_value;
}

int32_t ccu_dce_set_dceugprar4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar4 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr4;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr4 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr4;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr4_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr4 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar5;
    return return_value;
}

int32_t ccu_dce_set_dceugprar5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar5 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr5;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr5 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr5;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr5_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr5 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar6;
    return return_value;
}

int32_t ccu_dce_set_dceugprar6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar6 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr6;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr6 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr6;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr6_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr6 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar7;
    return return_value;
}

int32_t ccu_dce_set_dceugprar7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar7 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr7;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr7 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr7;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr7_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr7 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar8;
    return return_value;
}

int32_t ccu_dce_set_dceugprar8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar8 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr8;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr8 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr8;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr8_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr8 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar9;
    return return_value;
}

int32_t ccu_dce_set_dceugprar9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar9 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr9;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr9 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr9;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr9_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr9 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar10;
    return return_value;
}

int32_t ccu_dce_set_dceugprar10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar10 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr10;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr10 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr10;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr10_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr10 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprar11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprar11;
    return return_value;
}

int32_t ccu_dce_set_dceugprar11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprar11 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprblr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprblr11;
    return return_value;
}

int32_t ccu_dce_set_dceugprblr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprblr11 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceugprbhr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceugprbhr11;
    return return_value;
}

int32_t ccu_dce_set_dceugprbhr11_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceugprbhr11 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuedr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuedr0;
    return return_value;
}

int32_t ccu_dce_set_dceuedr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuedr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntcr0;
    return return_value;
}

int32_t ccu_dce_set_dcecntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntcr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntvr0;
    return return_value;
}

int32_t ccu_dce_set_dcecntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntvr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntsr0;
    return return_value;
}

int32_t ccu_dce_set_dcecntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntsr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntcr1;
    return return_value;
}

int32_t ccu_dce_set_dcecntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntcr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntvr1;
    return return_value;
}

int32_t ccu_dce_set_dcecntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntvr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntsr1;
    return return_value;
}

int32_t ccu_dce_set_dcecntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntsr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntcr2;
    return return_value;
}

int32_t ccu_dce_set_dcecntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntcr2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntvr2;
    return return_value;
}

int32_t ccu_dce_set_dcecntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntvr2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntsr2;
    return return_value;
}

int32_t ccu_dce_set_dcecntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntsr2 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntcr3;
    return return_value;
}

int32_t ccu_dce_set_dcecntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntcr3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntvr3;
    return return_value;
}

int32_t ccu_dce_set_dcecntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntvr3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcecntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcecntsr3;
    return return_value;
}

int32_t ccu_dce_set_dcecntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcecntsr3 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuccr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuccr0;
    return return_value;
}

int32_t ccu_dce_set_dceuccr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuccr0 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceuccr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuccr1;
    return return_value;
}

int32_t ccu_dce_set_dceuccr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dceuccr1 = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dcemcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dcemcntcr;
    return return_value;
}

int32_t ccu_dce_set_dcemcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dce[reg_offset].dcemcntcr = buf[0];
    return return_value;
}

int32_t ccu_dce_get_dceusbsir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceusbsir;
    return return_value;
}

int32_t ccu_dce_get_dceuengidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuengidr;
    return return_value;
}

int32_t ccu_dce_get_dceuinfor_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dce[reg_offset].dceuinfor;
    return return_value;
}

// DMI registers

int32_t ccu_dmi_get_dmiuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuidr;
    return return_value;
}

int32_t ccu_dmi_get_dmiufuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiufuidr;
    return return_value;
}

int32_t ccu_dmi_get_dmiutar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiutar;
    return return_value;
}

int32_t ccu_dmi_get_dmiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuuedr;
    return return_value;
}

int32_t ccu_dmi_set_dmiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuuedr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuueir;
    return return_value;
}

int32_t ccu_dmi_set_dmiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuueir = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuuesr;
    return return_value;
}

int32_t ccu_dmi_set_dmiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuuesr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuuelr0;
    return return_value;
}

int32_t ccu_dmi_set_dmiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuuelr1;
    return return_value;
}

int32_t ccu_dmi_set_dmiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuuesar;
    return return_value;
}

int32_t ccu_dmi_set_dmiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuuesar = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiucecr;
    return return_value;
}

int32_t ccu_dmi_set_dmiucecr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiucecr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiucesr;
    return return_value;
}

int32_t ccu_dmi_set_dmiucesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiucesr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiucelr0;
    return return_value;
}

int32_t ccu_dmi_set_dmiucelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiucelr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiucelr1;
    return return_value;
}

int32_t ccu_dmi_set_dmiucelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiucelr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiucesar;
    return return_value;
}

int32_t ccu_dmi_set_dmiucesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiucesar = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiutocr;
    return return_value;
}

int32_t ccu_dmi_set_dmiutocr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiutocr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiuqoscr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuqoscr0;
    return return_value;
}

int32_t ccu_dmi_set_dmiuqoscr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiuqoscr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmctcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmctcr;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmctcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmctcr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmctar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmctar;
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcapr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcapr;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmcapr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmcapr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcisr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcisr;
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcmcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcmcr;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmcmcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmcmcr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcmar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcmar;
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcmlr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcmlr0;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmcmlr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmcmlr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcmlr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcmlr1;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmcmlr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmcmlr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcmdr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcmdr;
    return return_value;
}

int32_t ccu_dmi_set_dmiusmcmdr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmiusmcmdr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicctrlr;
    return return_value;
}

int32_t ccu_dmi_set_dmicctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicctrlr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntcr0;
    return return_value;
}

int32_t ccu_dmi_set_dmicntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntcr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntvr0;
    return return_value;
}

int32_t ccu_dmi_set_dmicntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntvr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntsr0;
    return return_value;
}

int32_t ccu_dmi_set_dmicntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntsr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntcr1;
    return return_value;
}

int32_t ccu_dmi_set_dmicntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntcr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntvr1;
    return return_value;
}

int32_t ccu_dmi_set_dmicntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntvr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntsr1;
    return return_value;
}

int32_t ccu_dmi_set_dmicntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntsr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntcr2;
    return return_value;
}

int32_t ccu_dmi_set_dmicntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntcr2 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntvr2;
    return return_value;
}

int32_t ccu_dmi_set_dmicntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntvr2 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntsr2;
    return return_value;
}

int32_t ccu_dmi_set_dmicntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntsr2 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntcr3;
    return return_value;
}

int32_t ccu_dmi_set_dmicntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntcr3 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntvr3;
    return return_value;
}

int32_t ccu_dmi_set_dmicntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntvr3 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmicntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmicntsr3;
    return return_value;
}

int32_t ccu_dmi_set_dmicntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmicntsr3 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntfr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntfr0;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntfr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntfr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntmr0;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntmr0 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntfr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntfr1;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntfr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntfr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntmr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntmr1;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntmr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntmr1 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntfr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntfr2;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntfr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntfr2 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntmr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntmr2;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntmr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntmr2 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntfr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntfr3;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntfr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntfr3 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmibcntmr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmibcntmr3;
    return return_value;
}

int32_t ccu_dmi_set_dmibcntmr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmibcntmr3 = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmilcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmilcntcr;
    return return_value;
}

int32_t ccu_dmi_set_dmilcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmilcntcr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_dmimcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmimcntcr;
    return return_value;
}

int32_t ccu_dmi_set_dmimcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dmi[reg_offset].dmimcntcr = buf[0];
    return return_value;
}

int32_t ccu_dmi_get_mrdsbsir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].mrdsbsir;
    return return_value;
}

int32_t ccu_dmi_get_cmdsbsir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].cmdsbsir;
    return return_value;
}

int32_t ccu_dmi_get_dmiuevidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuevidr;
    return return_value;
}

int32_t ccu_dmi_get_dmiusmcifr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiusmcifr;
    return return_value;
}

int32_t ccu_dmi_get_dmiuinfor_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dmi[reg_offset].dmiuinfor;
    return return_value;
}

int32_t ccu_dii_get_diiuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuidr;
    return return_value;
}

int32_t ccu_dii_get_diiufuidr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiufuidr;
    return return_value;
}

int32_t ccu_dii_get_diiutar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiutar;
    return return_value;
}

int32_t ccu_dii_get_diiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuedr;
    return return_value;
}

int32_t ccu_dii_set_diiuuedr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuuedr = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuueir;
    return return_value;
}

int32_t ccu_dii_set_diiuueir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuueir = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuesr;
    return return_value;
}

int32_t ccu_dii_set_diiuuesr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuuesr = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuelr0;
    return return_value;
}

int32_t ccu_dii_set_diiuuelr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuelr1;
    return return_value;
}

int32_t ccu_dii_set_diiuuelr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuesar;
    return return_value;
}

int32_t ccu_dii_set_diiuuesar_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diiuuesar = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicctrlr;
    return return_value;
}

int32_t ccu_dii_set_diicctrlr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicctrlr = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntcr0;
    return return_value;
}

int32_t ccu_dii_set_diicntcr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntcr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntvr0;
    return return_value;
}

int32_t ccu_dii_set_diicntvr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntvr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntsr0;
    return return_value;
}

int32_t ccu_dii_set_diicntsr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntsr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntcr1;
    return return_value;
}

int32_t ccu_dii_set_diicntcr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntcr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntvr1;
    return return_value;
}

int32_t ccu_dii_set_diicntvr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntvr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntsr1;
    return return_value;
}

int32_t ccu_dii_set_diicntsr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntsr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntcr2;
    return return_value;
}

int32_t ccu_dii_set_diicntcr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntcr2 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntvr2;
    return return_value;
}

int32_t ccu_dii_set_diicntvr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntvr2 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntsr2;
    return return_value;
}

int32_t ccu_dii_set_diicntsr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntsr2 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntcr3;
    return return_value;
}

int32_t ccu_dii_set_diicntcr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntcr3 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntvr3;
    return return_value;
}

int32_t ccu_dii_set_diicntvr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntvr3 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diicntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diicntsr3;
    return return_value;
}

int32_t ccu_dii_set_diicntsr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diicntsr3 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntfr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntfr0;
    return return_value;
}

int32_t ccu_dii_set_diibcntfr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntfr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntmr0;
    return return_value;
}

int32_t ccu_dii_set_diibcntmr0_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntmr0 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntfr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntfr1;
    return return_value;
}

int32_t ccu_dii_set_diibcntfr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntfr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntmr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntmr1;
    return return_value;
}

int32_t ccu_dii_set_diibcntmr1_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntmr1 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntfr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntfr2;
    return return_value;
}

int32_t ccu_dii_set_diibcntfr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntfr2 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntmr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntmr2;
    return return_value;
}

int32_t ccu_dii_set_diibcntmr2_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntmr2 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntfr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntfr3;
    return return_value;
}

int32_t ccu_dii_set_diibcntfr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntfr3 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diibcntmr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diibcntmr3;
    return return_value;
}

int32_t ccu_dii_set_diibcntmr3_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diibcntmr3 = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diilcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diilcntcr;
    return return_value;
}

int32_t ccu_dii_set_diilcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diilcntcr = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diimcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diimcntcr;
    return return_value;
}

int32_t ccu_dii_set_diimcntcr_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dii[reg_offset].diimcntcr = buf[0];
    return return_value;
}

int32_t ccu_dii_get_diiusbsir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiusbsir;
    return return_value;
}

int32_t ccu_dii_get_diiuuevir_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuuevir;
    return return_value;
}

int32_t ccu_dii_get_diiuinfor_reg(int32_t fd, uintptr_t args, int32_t reg_offset) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dii[reg_offset].diiuinfor;
    return return_value;
}

int32_t ccu_dve_get_dveuidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuidr;
    return return_value;
}

int32_t ccu_dve_get_dveufuidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveufuidr;
    return return_value;
}

int32_t ccu_dve_get_dveutar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveutar;
    return return_value;
}

int32_t ccu_dve_get_dvececr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvececr;
    return return_value;
}

int32_t ccu_dve_set_dvececr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvececr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecesr;
    return return_value;
}

int32_t ccu_dve_set_dvecesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecesr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecelr0;
    return return_value;
}

int32_t ccu_dve_set_dvecelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecelr0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecelr1;
    return return_value;
}

int32_t ccu_dve_set_dvecelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecelr1 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecesar;
    return return_value;
}

int32_t ccu_dve_set_dvecesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecesar = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuuedr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuuedr;
    return return_value;
}

int32_t ccu_dve_set_dveuuedr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuuedr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuueir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuueir;
    return return_value;
}

int32_t ccu_dve_set_dveuueir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuueir = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuuesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuuesr;
    return return_value;
}

int32_t ccu_dve_set_dveuuesr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuuesr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuuelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuuelr0;
    return return_value;
}

int32_t ccu_dve_set_dveuuelr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuuelr0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuuelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuuelr1;
    return return_value;
}

int32_t ccu_dve_set_dveuuelr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuuelr1 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuesar;
    return return_value;
}

int32_t ccu_dve_set_dveuesar_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuesar = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveucrtr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveucrtr;
    return return_value;
}

int32_t ccu_dve_set_dveucrtr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveucrtr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuser0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuser0;
    return return_value;
}

int32_t ccu_dve_set_dveuser0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuser0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvetascr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetascr;
    return return_value;
}

int32_t ccu_dve_set_dvetascr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvetascr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvetadhr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetadhr;
    return return_value;
}

int32_t ccu_dve_get_dvetadtsr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetadtsr;
    return return_value;
}

int32_t ccu_dve_get_dvetad0r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad0r;
    return return_value;
}

int32_t ccu_dve_get_dvetad1r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad1r;
    return return_value;
}

int32_t ccu_dve_get_dvetad2r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad2r;
    return return_value;
}

int32_t ccu_dve_get_dvetad3r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad3r;
    return return_value;
}

int32_t ccu_dve_get_dvetad4r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad4r;
    return return_value;
}

int32_t ccu_dve_get_dvetad5r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad5r;
    return return_value;
}

int32_t ccu_dve_get_dvetad6r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad6r;
    return return_value;
}

int32_t ccu_dve_get_dvetad7r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad7r;
    return return_value;
}

int32_t ccu_dve_get_dvetad8r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad8r;
    return return_value;
}

int32_t ccu_dve_get_dvetad9r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad9r;
    return return_value;
}

int32_t ccu_dve_get_dvetad10r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad10r;
    return return_value;
}

int32_t ccu_dve_get_dvetad11r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad11r;
    return return_value;
}

int32_t ccu_dve_get_dvetad12r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad12r;
    return return_value;
}

int32_t ccu_dve_get_dvetad13r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad13r;
    return return_value;
}

int32_t ccu_dve_get_dvetad14r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad14r;
    return return_value;
}

int32_t ccu_dve_get_dvetad15r_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvetad15r;
    return return_value;
}

int32_t ccu_dve_get_dvecntcr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntcr0;
    return return_value;
}

int32_t ccu_dve_set_dvecntcr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntcr0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntvr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntvr0;
    return return_value;
}

int32_t ccu_dve_set_dvecntvr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntvr0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntsr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntsr0;
    return return_value;
}

int32_t ccu_dve_set_dvecntsr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntsr0 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntcr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntcr1;
    return return_value;
}

int32_t ccu_dve_set_dvecntcr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntcr1 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntvr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntvr1;
    return return_value;
}

int32_t ccu_dve_set_dvecntvr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntvr1 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntsr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntsr1;
    return return_value;
}

int32_t ccu_dve_set_dvecntsr1_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntsr1 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntcr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntcr2;
    return return_value;
}

int32_t ccu_dve_set_dvecntcr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntcr2 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntvr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntvr2;
    return return_value;
}

int32_t ccu_dve_set_dvecntvr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntvr2 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntsr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntsr2;
    return return_value;
}

int32_t ccu_dve_set_dvecntsr2_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntsr2 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntcr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntcr3;
    return return_value;
}

int32_t ccu_dve_set_dvecntcr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntcr3 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntvr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntvr3;
    return return_value;
}

int32_t ccu_dve_set_dvecntvr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntvr3 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvecntsr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvecntsr3;
    return return_value;
}

int32_t ccu_dve_set_dvecntsr3_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvecntsr3 = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dvemcntcr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dvemcntcr;
    return return_value;
}

int32_t ccu_dve_set_dvemcntcr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dvemcntcr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuengdbr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuengdbr;
    return return_value;
}

int32_t ccu_dve_set_dveuengdbr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    base->dve.dveuengdbr = buf[0];
    return return_value;
}

int32_t ccu_dve_get_dveuengidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuengidr;
    return return_value;
}

int32_t ccu_dve_get_dveuinfor_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->dve.dveuinfor;
    return return_value;
}

int32_t ccu_sys_global_get_grbucssfidr0_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->sys_global_register_blk.grbucssfidr0;
    return return_value;
}

int32_t ccu_sys_global_get_grbunrrir_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->sys_global_register_blk.grbunrrir;
    return return_value;
}

int32_t ccu_sys_global_get_grbuengidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->sys_global_register_blk.grbuengidr;
    return return_value;
}

int32_t ccu_sys_global_get_grbunrrucr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->sys_global_register_blk.grbunrrucr;
    return return_value;
}

int32_t ccu_sys_global_get_grbunsidr_reg(int32_t fd, uintptr_t args) {
    int32_t return_value = 0;
    uint32_t *buf = (uint32_t *)args;
    ccu_regs_t *base = (ccu_regs_t *)fd;
    buf[0] = base->sys_global_register_blk.grbunsidr;
    return return_value;
}
