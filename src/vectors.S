/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: vectors.S
 *
 * Exception vector table implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: src
 * Component: Vectors
 */

    .section .text.vectors
    .align 11           // VBAR requires 2048-byte alignment
    .global vector_table
    .extern interrupt_irq_handler

vector_table:
    /* Current EL with SP0 (fallback - should not normally be reached at EL3) */
    .align 7; b unhandled_exception
    .align 7; b irq_wrapper         // IRQ fallback
    .align 7; b irq_wrapper         // FIQ fallback
    .align 7; b unhandled_exception

    /* Current EL with SPx (Bare-metal flat execution) */
    .align 7; b unhandled_exception
    .align 7; b irq_wrapper         // IRQ Handler
    .align 7; b irq_wrapper         // FIQ Handler for Group0/EL3 routed interrupts
    .align 7; b unhandled_exception

    /* Lower EL using AArch64 */
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception

    /* Lower EL using AArch32 */
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception
    .align 7; b unhandled_exception

irq_wrapper:
    /* Save caller-saved registers */
    stp     x0, x1, [sp, #-16]!
    stp     x2, x3, [sp, #-16]!
    stp     x4, x5, [sp, #-16]!
    stp     x6, x7, [sp, #-16]!
    stp     x8, x9, [sp, #-16]!
    stp     x10, x11, [sp, #-16]!
    stp     x12, x13, [sp, #-16]!
    stp     x14, x15, [sp, #-16]!
    stp     x16, x17, [sp, #-16]!
    stp     x18, x30, [sp, #-16]!

    /* Acknowledge the interrupt on the interface that matches the active
     * group. On Agilex5 the group depends on the Exception Level: Group0 (FIQ)
     * at EL3 (secure OCRAM boot) and Group1 (IRQ) at EL2/EL1 (non-secure ATF
     * handoff). Other platforms always use Group1.
     * x1 records the acknowledged group so EOI targets the same interface. */
#if defined(PLAT_AGILEX5)
    mrs     x1, CurrentEL
    cmp     x1, #0xC
    b.ne    .Lirq_ack_g1
    mrs     x0, icc_iar0_el1
    mov     x1, #0
    b       .Lirq_acked
.Lirq_ack_g1:
    mrs     x0, icc_iar1_el1
    mov     x1, #1
.Lirq_acked:
#else
    mrs     x0, icc_iar1_el1
    mov     x1, #1
#endif

    /* Preserve INTID (x0) and group marker (x1) across the C call. */
    stp     x0, x1, [sp, #-16]!

    /* Call C handler: void interrupt_irq_handler(unsigned int interrupt_id) */
    bl      interrupt_irq_handler

    /* Restore INTID and group marker for EOI. */
    ldp     x0, x1, [sp], #16

    /* Write EOI to the interface that matches the acknowledged group. */
    cbz     x1, .Lirq_eoi_g0
    msr     icc_eoir1_el1, x0
    b       .Lirq_eoi_done
.Lirq_eoi_g0:
    msr     icc_eoir0_el1, x0
.Lirq_eoi_done:
    isb

    /* Restore registers */
    ldp     x18, x30, [sp], #16
    ldp     x16, x17, [sp], #16
    ldp     x14, x15, [sp], #16
    ldp     x12, x13, [sp], #16
    ldp     x10, x11, [sp], #16
    ldp     x8, x9,  [sp], #16
    ldp     x6, x7,  [sp], #16
    ldp     x4, x5,  [sp], #16
    ldp     x2, x3,  [sp], #16
    ldp     x0, x1,  [sp], #16

    eret

unhandled_exception:
    wfe
    b unhandled_exception