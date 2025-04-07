#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "rstmgr.h"
#include "rstmgr_regs.h"

#include "clkmgr.h"
#include "clkmgr_internal.h"
#include "clkmgr_regs.h"

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

const uint32_t clkmgr_regs_expected[] = {
    0x00000003, // ctrl, bootmode = 1
    0x031C1C00, // stat, bootmode = 1
    0x00100808, // testioctrl
    0x00000000, // intrgen
    0x00000000, // intrmsk
    0x00000000, // intrclr
    0x00000000, // intrsts
    0x00000000, // intrstk
    0x00000000  // intrraw
};

const uint32_t clkmgr_mainpll_regs_expected[] = {
    0x00000FFF, // en
    0x00000FDE, // ens, clock gate is enabled when bootmode
    0x00000FDE, // enr, clock gate is enabled when bootmode
    0x000000FF, // bypass
    0x000000FF, // bypasss
    0x000000FF, // bypassr
    0x00000000, // _pad_0x18_0x1b
    0x00000000, // nocclk
    0x20260198, // nocdiv
    0x16000101, // pllglob
    0x2A000000, // fdbck
    0x00000000, // mem
    0x00000000, // memstat
    0x0001087C, // vcocalib
    0x00000005, // pllc0
    0x00000004, // pllc1
    0x00000007, // pllc2
    0x00000008, // pllc3
    0x00000080, // pllm
    0x00000000, // fhop
    0x00000000, // ssc
    0x00000000  // lostlock
};

const uint32_t clkmgr_perpll_regs_expected[] = {
    0x3FFFFFFF, // en
    0x0FFFFFFF, // ens, clock gate is enabled when bootmode
    0x0FFFFFFF, // enr, clock gate is enabled when bootmode
    0x000000FF, // bypass
    0x000000FF, // bypasss
    0x000000FF, // bypassr
    0x00000000, // emacctl
    0x00000001, // gpiodiv
    0x15000101, // pllglob
    0x00000000, // fdbck
    0x00000000, // mem
    0x00000000, // memstat
    0x00010874, // vcocalib
    0x00000005, // pllc0
    0x00000005, // pllc1
    0x0000007D, // pllc2
    0x00000006, // pllc3
    0x00000078, // pllm
    0x00000000, // fhop
    0x00000000, // ssc
    0x00000000  // lostlock
};

const uint32_t clkmgr_ctlgrp_regs_expected[] = {
    0x00000180, // jtag
    0x00010001, // emacactr
    0x00010009, // emacbctr
    0x00000000, // emacptpctr
    0x00000001, // gpiodbctr
    0x00000000, // _pad_0x14_0x17 (padding, typically set to 0)
    0x00010000, // s2fuser0ctr
    0x00010000, // s2fuser1ctr
    0x00010000, // psirefctr
    0x00003CE4, // extcntrst
    0x00000013, // usb31ctr
    0x00000000, // dsuctr
    0x00010000, // core01ctr
    0x00000000, // core23ctr
    0x00000000, // core2ctr
    0x00000000, // core3ctr
    0x00000000  // serial_con_pll_ctr
};

void bit_diff_print(uint32_t expect, uint32_t actual) {

    uint32_t bit_diff = (expect ^ actual);
    printf("bit diff location: ");
    for (uint32_t j = 0; j < 32; j++) {
        if (bit_diff & 0x1) {
            printf("%d, ", j);
        }
        bit_diff >>= 1;
    }
    printf("\n");
}

int main(void) {
    int32_t return_value = 0;

#ifdef FSBL_EXECUTION
    fsbl_configuration();
#endif

    int32_t clkmgr_handle = clkmgr_open("/dev/clkmgr", 0);
    hps_clkmgr_regs_t value = {0};
    hps_clkmgr_mainpll_regs_t value_mainpll = {0};
    hps_clkmgr_perpll_regs_t value_perpll = {0};
    hps_clkmgr_ctlgrp_regs_t value_ctlgrp = {0};

    uint32_t *value_array = (uint32_t *)&value;

    if (clkmgr_handle < 0)
        return clkmgr_handle;

    // Verify the default values based on the register map and the CLKMGR HAS document
    // Any discrepany is shown as warnings in the test, all shall  be reserved bitfield added by Magillem
    // Provide the bit location for user to check

    if (clkmgr_ioctl(clkmgr_handle, IOCTL_CLKMGR_REGS_READ, (uintptr_t)(&value)) != 0) {
        printf("[Error] IOCTL_CLKMGR_REGS_READ failed!\n");
        return_value = -1;
    } else {
        for (size_t i = 0; i < sizeof(clkmgr_regs_expected) / sizeof(uint32_t); i++) {
            if (value_array[i] != clkmgr_regs_expected[i]) {
                printf("[Warning] IOCTL_CLKMGR_REGS_READ at offset 0x%x: expected: 0x%x, actual: 0x%x. ",
                       (uint32_t)(i << 2), clkmgr_regs_expected[i], value_array[i]);
                bit_diff_print(clkmgr_regs_expected[i], value_array[i]);
            }
        }
    }

    value_array = (uint32_t *)&value_mainpll;
    if (clkmgr_ioctl(clkmgr_handle, IOCTL_CLKMGR_MAINPLL_REGS_READ, (uintptr_t)(&value_mainpll)) != 0) {
        printf("[Error] IOCTL_CLKMGR_MAINPLL_REGS_READ failed!\n");
        return_value = -1;
    } else {
        for (size_t i = 0; i < sizeof(clkmgr_mainpll_regs_expected) / sizeof(uint32_t); i++) {
            if (value_array[i] != clkmgr_mainpll_regs_expected[i]) {
                printf("[Warning] IOCTL_CLKMGR_MAINPLL_REGS_READ at offset 0x%x: expected: 0x%x, actual: 0x%x. ",
                       (uint32_t)(i << 2), clkmgr_mainpll_regs_expected[i], value_array[i]);
                bit_diff_print(clkmgr_mainpll_regs_expected[i], value_array[i]);
            }
        }
    }

    value_array = (uint32_t *)&value_perpll;
    if (clkmgr_ioctl(clkmgr_handle, IOCTL_CLKMGR_PERPLL_REGS_READ, (uintptr_t)(&value_perpll)) != 0) {
        printf("[Error] IOCTL_CLKMGR_PERPLL_REGS_READ failed!\n");
        return_value = -1;
    } else {
        for (size_t i = 0; i < sizeof(clkmgr_perpll_regs_expected) / sizeof(uint32_t); i++) {
            if (value_array[i] != clkmgr_perpll_regs_expected[i]) {
                printf("[Warning] IOCTL_CLKMGR_PERPLL_REGS_READ at offset 0x%x: expected: 0x%x, actual: 0x%x. ",
                       (uint32_t)(i << 2), clkmgr_perpll_regs_expected[i], value_array[i]);
                bit_diff_print(clkmgr_perpll_regs_expected[i], value_array[i]);
            }
        }
    }

    value_array = (uint32_t *)&value_ctlgrp;
    if (clkmgr_ioctl(clkmgr_handle, IOCTL_CLKMGR_CTLGRP_REGS_READ, (uintptr_t)(&value_ctlgrp)) != 0) {
        printf("[Error] IOCTL_CLKMGR_CTLGRP_REGS_READ failed!\n");
        return_value = -1;
    } else {
        for (size_t i = 0; i < sizeof(clkmgr_ctlgrp_regs_expected) / sizeof(uint32_t); i++) {
            if (value_array[i] != clkmgr_ctlgrp_regs_expected[i]) {
                printf("[Warning] IOCTL_CLKMGR_CTLGRP_REGS_READ at offset 0x%x: expected: 0x%x, actual: 0x%x. ",
                       (uint32_t)(i << 2), clkmgr_ctlgrp_regs_expected[i], value_array[i]);
                bit_diff_print(clkmgr_ctlgrp_regs_expected[i], value_array[i]);
            }
        }
    }

    clkmgr_close(clkmgr_handle);

    return return_value;
}

#ifdef __cplusplus
}
#endif
