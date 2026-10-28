/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: gic_api.h
 *
 * Configure the Generic Interrupt Controller (GIC), register interrupt callbacks, enable or disable interrupts, and send software-generated interrupts (SGIs).
 *
 * Interrupt IDs are software-generated (SGI, 0 through 15), private peripheral (PPI), or shared peripheral (SPI). The legacy functions return socfpga_interrupt_err_t. The *_std functions are the same operations with an integer status: 0 on success and -EINVAL when the driver rejects the request. The current driver does not return any other status from these calls.
 */

#ifndef __GIC_API_H__
#define __GIC_API_H__

#include <stdint.h>
#include "errno.h"
#include "socfpga_interrupt.h"

/*
 * Preferred user call flow:
 * 1) gic_api_init_std()
 * 2) gic_api_register_isr_std(...)
 * 3) gic_api_enable_std(...)
 * 4) gic_api_disable_std(...) as needed
 *
 * The *_std functions return 0 or -EINVAL. The legacy enum-returning functions remain available.
 */

/* Function: gic_api_init
 *
 * Initialize the Generic Interrupt Controller through interrupt_init_gic().
 */
void gic_api_init(void);

/* Function: gic_api_enable
 *
 * Enable one software-generated, private, or shared peripheral interrupt and apply priority.
 *
 * Parameters:
 *
 *    irq - Interrupt ID to enable. 0 through 15 are software-generated interrupts.
 *    priority - Interrupt priority passed to the controller.
 *
 * Returns:
 *
 *    ERR_OK on success. ERR_SGI_ID when a software-generated interrupt cannot be enabled. ERR_PPI_ID when a private peripheral interrupt cannot be enabled. ERR_SPI_ID when a shared peripheral interrupt cannot be enabled.
 */
socfpga_interrupt_err_t gic_api_enable(uint32_t irq, uint8_t priority);

/* Function: gic_api_disable
 *
 * Disable an interrupt. Unlike gic_api_enable(), this call does not take a priority and does not select the current CPU's redistributor. Software-generated and private interrupts are disabled on redistributor 0. Interrupt ID 31 is rejected.
 *
 * Parameters:
 *
 *    irq - Interrupt ID to disable.
 *
 * Returns:
 *
 *    ERR_OK on success. ERR_SPI_ID when the controller rejects the ID, including interrupt 31.
 */
socfpga_interrupt_err_t gic_api_disable(uint32_t irq);

/* Function: gic_api_register_isr
 *
 * Registers a callback and caller context for the requested interrupt ID.
 *
 * Parameters:
 *
 *    irq - Interrupt ID to associate with the callback.
 *    callback - ISR callback function.
 *    user_data - Opaque pointer passed to callback when the interrupt fires.
 *
 * Returns:
 *
 *    ERR_OK on success; ERR_SPI_ID for an out-of-range ID; ERR_INTERRUPT_CALLBACK when callback is NULL.
 */
socfpga_interrupt_err_t gic_api_register_isr(uint32_t irq,
        socfpga_interrupt_callback_t callback, void *user_data);

/* Function: gic_api_trigger_sgi
 *
 * Sends a software-generated interrupt to the CPUs selected by cpu_mask.
 *
 * Parameters:
 *
 *    sgi_id - Software-generated interrupt ID, 0 through 15.
 *    cpu_mask - Bit mask selecting target CPUs.
 *
 * Returns:
 *
 *    ERR_OK on success; ERR_SGI_ID when sgi_id is invalid or the SGI cannot be issued.
 */
socfpga_interrupt_err_t gic_api_trigger_sgi(uint32_t sgi_id, uint8_t cpu_mask);

/*
 * Integer-status forms of the calls above.
 *
 * Each returns 0 when the legacy call returns ERR_OK, and -EINVAL when the
 * legacy call returns a rejected-ID or rejected-callback status.
 */
/* Function: gic_api_init_std
 *
 * Initialize the Generic Interrupt Controller and return an integer status for callers using the _std interface.
 *
 * Returns:
 *
 *    0 after gic_api_init() returns.
 */
int32_t gic_api_init_std(void);
/* Function: gic_api_enable_std
 *
 * Enable one interrupt and apply priority. Same operation as gic_api_enable().
 *
 * Parameters:
 *
 *    irq - Interrupt ID to enable. 0 through 15 are software-generated interrupts.
 *    priority - Interrupt priority passed to the controller.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when gic_api_enable() rejects the ID.
 */
int32_t gic_api_enable_std(uint32_t irq, uint8_t priority);
/* Function: gic_api_disable_std
 *
 * Disable an interrupt. Same operation as gic_api_disable().
 *
 * Parameters:
 *
 *    irq - Interrupt ID to disable.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when gic_api_disable() rejects the ID.
 */
int32_t gic_api_disable_std(uint32_t irq);
/* Function: gic_api_register_isr_std
 *
 * Register a callback and caller context for an interrupt. Same operation as gic_api_register_isr().
 *
 * Parameters:
 *
 *    irq - Interrupt ID to associate with the callback.
 *    callback - Function called when the interrupt fires. NULL is rejected.
 *    user_data - Pointer passed to callback. May be NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when the ID is out of range or callback is NULL.
 */
int32_t gic_api_register_isr_std(uint32_t irq,
        socfpga_interrupt_callback_t callback, void *user_data);
/* Function: gic_api_trigger_sgi_std
 *
 * Send a software-generated interrupt to the CPUs selected by cpu_mask. Same operation as gic_api_trigger_sgi().
 *
 * Parameters:
 *
 *    sgi_id - Software-generated interrupt ID, 0 through 15.
 *    cpu_mask - Bit mask selecting target CPUs.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when sgi_id is greater than 15.
 */
int32_t gic_api_trigger_sgi_std(uint32_t sgi_id, uint8_t cpu_mask);
#endif /* __GIC_API_H__ */