/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic_reg.c
 *
 * GIC source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdint.h>
#include <stdio.h>
#include "socfpga_gic_reg.h"
#include "socfpga_gic_registers.h"

#define GIC_REG_WRITE(reg, val)    __asm__ __volatile__ ("MSR " #reg ", %0\n\tDSB SY\n\tISB" : : "r" (val))
#define GIC_REG_READ(reg)         ({uint64_t val; __asm__ __volatile__ ("MRS %0, " #reg "\n\tDSB SY\n\tISB" : "=r" (val)); val;})

void gic_reg_enable_group0_interrupts(void)
{
    /* At all exception levels (EL1/EL2/EL3), use ICC_IGRPEN0_EL1.
     * The _EL1 suffix is just the register name; it's accessible at EL3. */
    GIC_REG_WRITE(s3_0_c12_c12_6, (uint64_t)1);
}

void gic_reg_enable_group1_interrupts(void)
{
    /* At all exception levels (EL1/EL2/EL3), use ICC_IGRPEN1_EL1.
     * The _EL1 suffix is just the register name; it's accessible at EL3. */
    GIC_REG_WRITE(s3_0_c12_c12_7, (uint64_t)1);
}

void gic_reg_write_group1_end_of_interrupt(uint32_t interrupt_id)
{
    /* REQUIRED FOR BAREMETAL GICv3: Signals completion to the CPU interface */
    GIC_REG_WRITE(ICC_EOIR1_EL1, (uint64_t)interrupt_id);
}

void gic_reg_set_priority_mask(uint32_t interrupt_id)
{
    /* Write ICC_PMR_EL1 multiple times with barriers to overcome hardware masking */
    for (int i = 0; i < 3; i++)
    {
        GIC_REG_WRITE(s3_0_c4_c6_0, (uint64_t)interrupt_id);
        __asm__ volatile ("isb sy" ::: "memory");
    }
}

uint64_t gic_reg_get_cpu_affinity(void)
{
    uint64_t affinity = 0U;
    __asm__ volatile (
        "MRS x0, MPIDR_EL1 \n\t"
        "UBFX x1, x0, #32, #8 \n\t"
        "BFI w0, w1, #24, #8 \r\n"
        "MOV %0, x0" : "=r" (affinity));
    return affinity;
}
