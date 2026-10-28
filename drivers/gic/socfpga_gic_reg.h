/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic_reg.h
 *
 * GIC register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_GIC_REG_H__
#define __SOCFPGA_GIC_REG_H__

#include <stdint.h>

/* Function: gic_reg_enable_group0_interrupts
 *
 * Enables the signaling of Group 0 interrupts to the executing Processing Element (PE).
 *
 * In the ARM GIC architecture, Group 0 interrupts are typically reserved for 
 * Secure interrupts and are signaled as FIQs. This function performs a direct 
 * write to the `ICC_IGRPEN0_EL1` system register to assert the enable bit, 
 * allowing the CPU interface to forward pending Group 0 interrupts to the core.
 *
 * Returns:
 *
 * None.
 */
void gic_reg_enable_group0_interrupts(void);

/* Function: gic_reg_enable_group1_interrupts
 *
 * Enables the signaling of Group 1 interrupts to the executing Processing Element (PE).
 *
 * Group 1 interrupts are typically used for Non-Secure general-purpose interrupts 
 * (signaled as IRQs). This function writes to the `ICC_IGRPEN1_EL1` system 
 * register to unmask Group 1 delivery at the CPU interface level.
 *
 * Returns:
 *
 * None.
 */
void gic_reg_enable_group1_interrupts(void);

/* Function: gic_reg_write_group1_end_of_interrupt
 *
 * Signals the completion of the active Group 1 interrupt handling routine.
 *
 * This function writes the specified interrupt ID to the End of Interrupt (EOI) 
 * register (`ICC_EOIR1_EL1`). This critical action informs the GIC hardware 
 * that the processor has finished servicing the interrupt, causing the GIC to 
 * perform a priority drop and transition the interrupt state from Active to 
 * Inactive (or Pending if another edge was detected).
 *
 * Parameters:
 *
 * interrupt_id - The hardware INTID of the serviced interrupt (read previously 
 * from the Interrupt Acknowledge Register, `ICC_IAR1_EL1`).
 *
 * Returns:
 *
 * None.
 */
void gic_reg_write_group1_end_of_interrupt(uint32_t interrupt_id);

/* Function: gic_reg_set_priority_mask
 *
 * Sets the priority threshold for forwarding interrupts to the CPU.
 *
 * This function writes directly to the Priority Mask Register (`ICC_PMR_EL1`). 
 * The GIC CPU interface will only signal pending interrupts that have a higher 
 * priority (a strictly lower value) than this mask. Setting this to 0xFF 
 * effectively allows all configured interrupts to be serviced.
 *
 * Parameters:
 *
 * priority_mask - The 8-bit priority threshold value.
 *
 * Returns:
 *
 * None.
 */
void gic_reg_set_priority_mask(uint32_t priority_mask);

/* Function: gic_reg_get_cpu_affinity
 *
 * Retrieves the hardware routing identification for the currently executing core.
 *
 * This function reads the Multiprocessor Affinity Register (`MPIDR_EL1`) to 
 * extract the Aff0, Aff1, Aff2, and Aff3 fields. These hierarchical affinity 
 * levels are used by the GICv3 distributor (via the `IROUTER` registers) to 
 * route specific Shared Peripheral Interrupts (SPIs) to this exact CPU core.
 *
 * Returns:
 *
 * The 64-bit affinity descriptor containing the hierarchical cluster and 
 * core IDs.
 */
uint64_t gic_reg_get_cpu_affinity(void);

void gic_debug_print_registers(void);

void gic_debug_print_redist_power(void *redist_base);

#endif /* __SOCFPGA_GIC_REG_H__ */