/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic.h
 *
 * GIC hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_GIC_H__
#define __SOCFPGA_GIC_H__

#include <stdint.h>
#include "socfpga_gic_reg_plat.h"

/* Constants: GICv3 security and grouping
 *
 * Group values passed to gic_set_int_group. They choose which GIC group
 * an interrupt belongs to.
 *
 * GICV3_GROUP0            - Secure Group 0. Typically FIQ.
 * GICV3_GROUP1_SECURE     - Secure Group 1. Typically IRQ in Secure EL1.
 * GICV3_GROUP1_NON_SECURE - Non-secure Group 1. Typically IRQ in
 *                           Non-secure EL1 or EL2.
 */
#define GICV3_GROUP0                (0U) /* Secure Group 0 (typically FIQ) */
#define GICV3_GROUP1_SECURE         (1U) /* Secure Group 1 (typically IRQ in Secure EL1) */
#define GICV3_GROUP1_NON_SECURE     (2U) /* Non-Secure Group 1 (typically IRQ in Non-Secure EL1/EL2) */

/* Constants: Interrupt configuration
 *
 * Trigger type passed to gic_set_int_type.
 *
 * GICV3_CONFIG_LEVEL - Level-sensitive trigger.
 * GICV3_CONFIG_EDGE  - Edge-sensitive trigger. The edge direction
 *                      depends on the source.
 */
#define GICV3_CONFIG_LEVEL          (0U) /* Level-sensitive trigger */
#define GICV3_CONFIG_EDGE           (2U) /* Edge-triggered (rising or falling depending on source) */

/* Constants: SPI routing modes
 *
 * Values ORed into the route word written to GICD_IROUTER.
 *
 * GICV3_ROUTE_MODE_ANY        - Any core. Bit 31 of the route word is set.
 * GICV3_ROUTE_MODE_COORDINATE - One core, chosen by the affinity value.
 */
#define GICV3_ROUTE_MODE_ANY        (0x80000000U) /* 1-of-N routing: target any available core (IRM bit set) */
#define GICV3_ROUTE_MODE_COORDINATE (0U)          /* Target a specific core based on affinity coordinates */

/* Constants: Return codes
 *
 * Values the GIC functions return.
 *
 * INTERRUPT_RETURN_SUCCESS           - The call worked.
 * INTERRUPT_RETURN_ERROR             - The distributor or redistributor
 *                                      address is NULL.
 * INTERRUPT_RETURN_INVALID_PRIORITY  - The priority is in the range
 *                                      0xF0 to 0xFF on a platform that
 *                                      rejects that range.
 * INTERRUPT_RETURN_INVALID_RDIST     - The redistributor index is past
 *                                      the last redistributor.
 * INTERRUPT_RETURN_INVALID_ID        - The interrupt number is not supported.
 * INTERRUPT_RETURN_INVALID_GROUP     - The group value is not one of the
 *                                      three group constants.
 * INTERRUPT_RETURN_INVALID_SPI       - The interrupt number is not a valid
 *                                      shared peripheral interrupt.
 */
#define INTERRUPT_RETURN_SUCCESS             0
#define INTERRUPT_RETURN_ERROR              -1
#define INTERRUPT_RETURN_INVALID_PRIORITY   -2
#define INTERRUPT_RETURN_INVALID_RDIST      -3
#define INTERRUPT_RETURN_INVALID_ID         -4
#define INTERRUPT_RETURN_INVALID_GROUP      -5
#define INTERRUPT_RETURN_INVALID_SPI        -6


/* Function: gic_enable_gic
 *
 * Initializes the global GIC Distributor (GICD). This function enables Affinity 
 * Routing (ARE) and globally unmasks Group 0 and Group 1 interrupts at the 
 * distributor level by configuring the GICD_CTLR register.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the distributor fails to initialize.
 */
int32_t gic_enable_gic(void);

/* Function: gic_get_redist_id
 *
 * Resolves the logical Redistributor ID (GICR) for a given physical CPU affinity.
 * The GICv3 architecture requires specific redistributor bases to configure 
 * Software Generated Interrupts (SGIs) and Private Peripheral Interrupts (PPIs) 
 * for individual cores.
 *
 * Parameters:
 *
 * affinity - The MPIDR_EL1 format affinity coordinates of the target CPU.
 *
 * Returns:
 *
 * The resolved logical Redistributor ID on success; <INTERRUPT_RETURN_INVALID_RDIST> 
 * if no matching redistributor is found.
 */
int32_t gic_get_redist_id(uint32_t affinity);

/* Function: gic_wakeup_redist
 *
 * Transitions a specific core's Redistributor from sleep to an active state. 
 * This manipulates the GICR_WAKER register, clearing the ProcessorSleep bit 
 * and polling until the ChildrenAsleep bit acknowledges the wake-up.
 *
 * Parameters:
 *
 * rd - The logical Redistributor ID to awaken.
 *
 * Returns:
 *
 * 0 on success; <INTERRUPT_RETURN_ERROR> if the redistributor times out during wake-up.
 */
int32_t gic_wakeup_redist(uint32_t rd);

/* Function: gic_set_int_priority
 *
 * Programs the priority level for a specific interrupt. Lower values represent 
 * higher priorities. This writes to the GICD_IPRIORITYR array for SPIs, or 
 * the GICR_IPRIORITYR array for SGIs/PPIs.
 *
 * Parameters:
 *
 * id       - The hardware Interrupt ID (INTID).
 * rd       - The Redistributor ID (ignored if the INTID is an SPI).
 * priority - The 8-bit priority value.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID or priority is invalid.
 */
int32_t gic_set_int_priority(uint32_t id, uint32_t rd, uint8_t priority);

/* Function: gic_set_int_group
 *
 * Assigns a specific interrupt to an ARM TrustZone security group (Group 0, 
 * Secure Group 1, or Non-Secure Group 1). This dictates which CPU execution 
 * states and exception levels are permitted to handle the interrupt.
 *
 * Parameters:
 *
 * id       - The hardware Interrupt ID (INTID).
 * rd       - The Redistributor ID (ignored if the INTID is an SPI).
 * security - The target group classification (e.g., <GICV3_GROUP1_NON_SECURE>).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID or group is invalid.
 */
int32_t gic_set_int_group(uint32_t id, uint32_t rd, uint32_t security);

/* Function: gic_set_int_route
 *
 * Configures the multiprocessor routing policy for a Shared Peripheral Interrupt (SPI).
 * This programs the GICD_IROUTER register to direct the interrupt either to a 
 * specific CPU core (using affinity coordinates) or allows the GIC to route 
 * it to any available core (1-of-N routing).
 *
 * Parameters:
 *
 * id       - The hardware Interrupt ID (must be an SPI, INTID >= 32).
 * mode     - The routing mode (<GICV3_ROUTE_MODE_ANY> or <GICV3_ROUTE_MODE_COORDINATE>).
 * affinity - The target CPU affinity (ignored if mode is ANY).
 *
 * Returns:
 *
 * 0 on success; <INTERRUPT_RETURN_INVALID_SPI> if the ID is an SGI or PPI.
 */
int32_t gic_set_int_route(uint32_t id, uint32_t mode, uint32_t affinity);

/* Function: gic_enable_int
 *
 * Unmasks a specific interrupt, allowing it to be forwarded to the CPU interface. 
 * This sets the corresponding bit in the GICD_ISENABLER (for SPIs) or 
 * GICR_ISENABLER0 (for SGIs/PPIs) registers.
 *
 * Parameters:
 *
 * id - The hardware Interrupt ID (INTID).
 * rd - The Redistributor ID (ignored if the INTID is an SPI).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID is invalid.
 */
int32_t gic_enable_int(uint32_t id, uint32_t rd);

/* Function: gic_disable_int
 *
 * Masks a specific interrupt, preventing it from being forwarded to the CPU interface. 
 * This sets the corresponding bit in the GICD_ICENABLER or GICR_ICENABLER0 registers.
 *
 * Parameters:
 *
 * id - The hardware Interrupt ID (INTID).
 * rd - The Redistributor ID (ignored if the INTID is an SPI).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID is invalid.
 */
int32_t gic_disable_int(uint32_t id, uint32_t rd);

/* Function: gic_set_int_type
 *
 * Configures the physical trigger sensitivity (level-sensitive or edge-triggered) 
 * for a specific interrupt by programming the GICD_ICFGR or GICR_ICFGR registers.
 *
 * Parameters:
 *
 * id   - The hardware Interrupt ID (INTID).
 * rd   - The Redistributor ID (ignored if the INTID is an SPI).
 * type - The trigger configuration (<GICV3_CONFIG_LEVEL> or <GICV3_CONFIG_EDGE>).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID is invalid.
 */
int32_t gic_set_int_type(uint32_t id, uint32_t rd, uint32_t type);

/* Function: gic_clear_int_pending
 *
 * Forcibly clears the pending state of an interrupt. This writes to the 
 * GICD_ICPENDR or GICR_ICPENDR0 registers, dropping the interrupt before the 
 * CPU acknowledges it.
 *
 * Parameters:
 *
 * id - The hardware Interrupt ID (INTID).
 * rd - The Redistributor ID (ignored if the INTID is an SPI).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID is invalid.
 */
int32_t gic_clear_int_pending(uint32_t id, uint32_t rd);

/* Function: gic_set_int_pending
 *
 * Forcibly asserts the pending state of an interrupt via software. This writes 
 * to the GICD_ISPENDR or GICR_ISPENDR0 registers, simulating a hardware trigger.
 *
 * Parameters:
 *
 * id - The hardware Interrupt ID (INTID).
 * rd - The Redistributor ID (ignored if the INTID is an SPI).
 *
 * Returns:
 *
 * 0 on success; a negative error code if the INTID is invalid.
 */
int32_t gic_set_int_pending(uint32_t id, uint32_t rd);

/* Function: gic_enable_interrupts
 *
 * Triggers the low-level CPU interface initialization. This routine typically 
 * configures the system control registers (e.g., ICC_IGRPEN1_EL1, ICC_PMR_EL1) 
 * to allow the processor core to begin accepting interrupts from the GIC hardware.
 *
 * Returns:
 *
 * None.
 */
void gic_enable_interrupts(void);

#endif /* __SOCFPGA_GIC_H__ */