/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_timer.h
 *
 * Timer hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_TIMER_H__
#define __SOCFPGA_TIMER_H__

#include "mmio.h"

/* Constant: TIMER_NUM_INSTANCE
 * Defines the maximum number of hardware timer instances available on the 
 * SoCFPGA platform (typically combinations of System Timers and SP Timers).
 */
#define TIMER_NUM_INSTANCE    4


struct timer_context;

/* Type: timer_handle_t
 *
 * An opaque software handle representing an active connection to a specific 
 * hardware timer instance. This handle encapsulates the internal state, 
 * including the computed MMIO base address, current clock frequency, 
 * and registered interrupt service routines.
 */
typedef struct timer_context *timer_handle_t;

/* Type: timer_callback_t
 *
 * Callback function signature used by the Timer's Interrupt Service Routine (ISR). 
 * This is executed when the timer hardware reaches zero (in user-defined mode) 
 * or rolls over (in free-running mode), triggering a hardware interrupt.
 *
 * Parameters:
 *
 * buf - An opaque pointer provided by the application during callback registration, 
 * typically used to pass application context back to the interrupt handler.
 */
typedef void (*timer_callback_t)(void *buf);

/* Enum: timer_instance_t
 *
 * Enumerates the physical timer instances available on the SoCFPGA system.
 *
 * Values:
 *
 * TIMER_SYS0       - System Timer 0. Often used for OS ticks or global timekeeping.
 * TIMER_SYS1       - System Timer 1.
 * TIMER_SP0        - SP (System Peripheral) Timer 0. General-purpose timer.
 * TIMER_SP1        - SP (System Peripheral) Timer 1. General-purpose timer.
 * TIMER_N_INSTANCE - The total number of addressable timer instances.
 */
typedef enum
{
    TIMER_SYS0 = 0,
    TIMER_SYS1,
    TIMER_SP0,
    TIMER_SP1,
    TIMER_N_INSTANCE
} timer_instance_t;


/* Function: timer_drv_hw_open
 *
 * Initializes the hardware mapping for a specific timer instance. It resolves 
 * the MMIO base address, interfaces with the System Manager to ensure the 
 * peripheral clock is ungated, and asserts/deasserts the hardware reset line 
 * via the Reset Manager to ensure a clean operational state.
 *
 * Parameters:
 *
 * instance - The physical hardware identifier from <timer_instance_t>.
 *
 * Returns:
 *
 * A valid <timer_handle_t> on success; NULL if the instance is invalid, 
 * already in use, or the hardware clock fails to enable.
 */
timer_handle_t timer_drv_hw_open(timer_instance_t instance);

/* Function: timer_ll_open
 *
 * Allocates and initializes the software context required to manage the timer. 
 * This functions similarly to <timer_drv_hw_open> but is specifically tailored 
 * for the low-level abstraction layer, setting up internal descriptors before 
 * hardware configuration begins.
 *
 * Parameters:
 *
 * instance - The physical hardware identifier from <timer_instance_t>.
 *
 * Returns:
 *
 * A valid <timer_handle_t> on success; NULL on failure.
 */
timer_handle_t timer_ll_open(timer_instance_t instance);

/* Function: timer_get_value_raw
 *
 * Performs a direct read of the hardware's Current Value Register (CVR). 
 * This returns the exact number of clock ticks remaining before the timer 
 * hits zero or rolls over, without any software-level conversion.
 *
 * Parameters:
 *
 * htimer      - The active timer handle.
 * counter_val - Pointer to a 32-bit variable where the raw hardware tick 
 * count will be stored.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if the handle or pointer is NULL.
 * -EPERM if the timer is currently stopped and the register is inactive.
 */
int32_t timer_get_value_raw(timer_handle_t const htimer, uint32_t *counter_val);

/* Function: timer_ll_start
 *
 * Asserts the Enable bit in the timer's Control Register. This unmasks the 
 * timer's output line, allowing it to begin actively decrementing the value 
 * loaded from the Load Count Register on every peripheral clock edge.
 *
 * Parameters:
 *
 * htimer - The active timer handle to start.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if the handle is NULL.
 * -EBUSY if the timer is already running.
 */
int32_t timer_ll_start(timer_handle_t const htimer);

/* Function: timer_ll_stop
 *
 * Clears the Enable bit in the timer's Control Register. This instantly halts 
 * the hardware counter and masks its interrupt output to the system's Generic 
 * Interrupt Controller (GIC), effectively pausing the timer.
 *
 * Parameters:
 *
 * htimer - The active timer handle to stop.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if the handle is NULL.
 * -EPERM if the timer is already stopped.
 * -EFAULT if the driver fails to mask the hardware interrupt.
 */
int32_t timer_ll_stop(timer_handle_t const htimer);

/* Function: timer_ll_close
 *
 * Safely deconstructs the software context for a timer. It stops the hardware 
 * counter (if running), clears pending interrupts, unregisters the ISR, and 
 * frees the handle memory.
 *
 * Parameters:
 *
 * htimer - The active timer handle to close.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the handle is NULL.
 */
int32_t timer_ll_close(timer_handle_t const htimer);

/* Function: timer_set_period_us
 *
 * Configures the timer's operational mode and duration. The driver calculates 
 * the required hardware ticks by factoring the requested microseconds against 
 * the SoC's active peripheral clock rate, and writes this value into the 
 * Load Count Register. 
 *
 * If a finite period is requested, the timer operates in User-Defined 
 * (Auto-Reload) Mode, meaning it will automatically reload the count and 
 * fire an interrupt every time it hits zero. If the requested period is 
 * 0xFFFFFFFF, the timer is configured in Free-Running Mode, utilizing its 
 * maximum 32-bit span.
 *
 * Parameters:
 *
 * htimer - The active timer handle.
 * period - The desired period in microseconds. (Pass 0xFFFFFFFF for free-running).
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if the handle is NULL or the requested period exceeds the 32-bit hardware limit.
 * -EBUSY if the timer is currently running and must be stopped before reconfiguration.
 */
int32_t timer_set_period_us(timer_handle_t const htimer, uint32_t period);

/* Function: timer_get_value_us
 *
 * Reads the hardware's Current Value Register (CVR) and converts the raw tick 
 * count back into a human-readable microsecond format. In User-Defined mode, 
 * this represents the time remaining until the next interrupt fires. In 
 * Free-Running mode, this represents the time until a 32-bit rollover occurs.
 *
 * Parameters:
 *
 * htimer  - The active timer handle.
 * time_us - Pointer to a variable where the remaining time in microseconds will be stored.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if the handle or output pointer is NULL.
 * -EPERM if the timer is stopped.
 */
int32_t timer_get_value_us(timer_handle_t const htimer, uint32_t *time_us);

/* Function: timer_set_callback
 *
 * Registers a user-defined function to be executed by the Interrupt Service 
 * Routine (ISR) when the hardware timer reaches zero. In auto-reload mode, 
 * this callback will be triggered periodically.
 *
 * Parameters:
 *
 * htimer   - The active timer handle.
 * callback - The function pointer to invoke upon timer expiry.
 * param    - An opaque pointer to user context that will be passed directly 
 * to the callback function.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the handle or callback pointer is NULL.
 */
int32_t timer_set_callback(timer_handle_t const htimer, timer_callback_t callback, 
                           void *param);

#endif /* __SOCFPGA_TIMER_H__ */