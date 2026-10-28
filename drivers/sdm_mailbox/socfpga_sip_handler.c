/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sip_handler.c
 *
 * SDM Mailbox source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_sip_handler.h"

int smc_call(uint64_t function_id, uint64_t *register_val)
{
    /* Bind C variables directly to specific ARM64 registers (X1..X11). */
    register uint64_t x0 __asm__("x0") = function_id;
    register uint64_t x1 __asm__("x1") = register_val[0];
    register uint64_t x2 __asm__("x2") = register_val[1];
    register uint64_t x3 __asm__("x3") = register_val[2];
    register uint64_t x4 __asm__("x4") = register_val[3];
    register uint64_t x5 __asm__("x5") = register_val[4];
    register uint64_t x6 __asm__("x6") = register_val[5];
    register uint64_t x7 __asm__("x7") = register_val[6];
    register uint64_t x8 __asm__("x8") = register_val[7];
    register uint64_t x9 __asm__("x9") = register_val[8];
    register uint64_t x10 __asm__("x10") = register_val[9];
    register uint64_t x11 __asm__("x11") = register_val[10];

    /*
     * Perform the SMC call in a single block.
     * "+r" means the register is used as both an input and an output.
     */
    __asm__ volatile (
        "smc #0\n"
        : "+r" (x0), "+r" (x1), "+r" (x2), "+r" (x3),
          "+r" (x4), "+r" (x5), "+r" (x6), "+r" (x7),
          "+r" (x8), "+r" (x9), "+r" (x10), "+r" (x11)
        :
        : "x12", "x13", "x14", "x15", "x16", "x17", "cc", "memory"
    );

    /* Store the response values back into the array (must be SMC_CALL_REG_COUNT). */
    register_val[0] = x1;
    register_val[1] = x2;
    register_val[2] = x3;
    register_val[3] = x4;
    register_val[4] = x5;
    register_val[5] = x6;
    register_val[6] = x7;
    register_val[7] = x8;
    register_val[8] = x9;
    register_val[9] = x10;
    register_val[10] = x11;

    return (int)x0;
}
