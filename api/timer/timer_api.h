/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: timer_api.h
 *
 * Open, start, stop, and read one timer.
 *
 * After timer_open(), configure the period with timer_set_period_us(),
 * declared in the socfpga_timer.h driver header included below. Set it again
 * after timer_stop(), which clears the configuration. Starting without a
 * configured period returns -EINVAL.
 */

#ifndef __TIMER_API_H__
#define __TIMER_API_H__

#include <stdint.h>

#include "socfpga_timer.h"

/* Function: timer_open
 *
 * Open one timer and release its reset if the block is held in reset.
 *
 * Parameters:
 *
 *    instance - TIMER_SYS0, TIMER_SYS1, TIMER_SP0, or TIMER_SP1.
 *
 * Returns:
 *
 *    A handle on success. NULL when instance is out of range, already open, reset status cannot be read or released, or the timer clock rate cannot be resolved.
 */
timer_handle_t timer_open(timer_instance_t instance);

/* Function: timer_start
 *
 * Start a timer that has already been configured.
 *
 * timer_open() does not set a period. Call timer_set_period_us(), declared in
 * the socfpga_timer.h driver header included above, before each start.
 * Starting without a configured period returns -EINVAL. timer_stop() clears
 * that configuration, so set the period again before restarting.
 *
 * Parameters:
 *
 *    htimer - Handle from timer_open(). NULL is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when htimer is NULL or the timer is not configured. -EBUSY when it is already running.
 */
int32_t timer_start(timer_handle_t htimer);

/* Function: timer_stop
 *
 * Stop a running timer. Stopping clears the configured state.
 *
 * Parameters:
 *
 *    htimer - Handle from timer_open(). NULL is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when htimer is NULL. -EPERM when the timer is not running.
 */
int32_t timer_stop(timer_handle_t htimer);

/* Function: timer_close
 *
 * Closes a timer handle and releases the underlying timer instance.
 *
 * Parameters:
 *
 *    htimer - Handle returned by timer_open().
 *
 * Returns:
 *
 *    0 on success; -EINVAL if htimer is NULL or does not identify an open timer;
 *    -EFAULT if the timer instance cannot be released from the driver table.
 */
int32_t timer_close(timer_handle_t htimer);

/* Function: timer_deinit
 *
 * Provides the deinitialization alias for timer_close().
 *
 * Parameters:
 *
 *    htimer - Handle returned by timer_open().
 *
 * Returns:
 *
 *    The same status returned by timer_close().
 */
int32_t timer_deinit(timer_handle_t htimer);

/* Function: timer_get_time_us
 *
 * Reads the current timer value in microseconds.
 *
 * Parameters:
 *
 *    htimer - Handle returned by timer_open().
 *    time_us - Receives the current timer value in microseconds.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if htimer or time_us is NULL or the timer clock rate
 *    is unavailable; -EPERM if the timer is not running.
 */
int32_t timer_get_time_us(timer_handle_t htimer, uint32_t *time_us);


#endif /* __TIMER_API_H__ */
