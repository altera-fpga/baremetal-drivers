/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: startup.S
 *
 * Startup sequence implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: src
 * Component: Startup
 */

    .section .text.start
    .global _start
    .extern vector_table
    .extern crt0_init
    .extern main

_start:
    // Load stack top address into x0 first
    ldr     x0, =_stack_top

    // Switch to SP_ELx (SP_EL3 at EL3) so exceptions use the Current EL SPx
    // vector table entries (VBAR+0x200). With SPSEL=0 (reset default), FIQ/IRQ
    // at EL3 would go to the SP_EL0 table entries which are unhandled.
    msr     spsel, #1
    isb

    // Now set SP_EL3 (SP is SP_ELx after SPSEL=1)
    // Align to 16-byte boundary using temp register (SP can't be used directly with AND imm)
    and     x0, x0, #~0xF
    mov     sp, x0

    // Initialize Vector Base Address Register for current EL
    ldr     x0, =vector_table
    mrs     x2, CurrentEL
    cmp     x2, #0xC                   // EL3
    b.eq    1f
    cmp     x2, #0x8                   // EL2
    b.eq    2f
    msr     vbar_el1, x0               // Default to EL1
    b       3f
1:
    msr     vbar_el3, x0
    b       3f
2:
    msr     vbar_el2, x0
3:
    isb

    // Call main()
    bl      crt0_init
    bl      main

    // If main returns, loop forever
1:  wfe
    b       1b