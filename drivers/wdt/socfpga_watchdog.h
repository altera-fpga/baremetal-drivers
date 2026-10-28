/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT
 */

/* File: socfpga_watchdog.h
 *
 * Watchdog hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

/*
 * Common IO - basic V1.0.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * Modified for SoC FPGA
 */

#ifndef __SOCFPGA_WATCHDOG_H__
#define __SOCFPGA_WATCHDOG_H__

#include "mmio.h"

struct wdt_descriptor;

/* Type: wdt_handle_t
 *
 * wdt_handle_t type is the WatchDog handle returned by calling wdt_open().
 * This is initialized in open and returned to the caller. The caller must pass 
 * this pointer to the rest of the APIs.
 */
typedef struct wdt_descriptor *wdt_handle_t;

/* Enum: wdt_status_t
 *
 * WatchDog timer status values.
 *
 * Values:
 *
 * WDT_STOPPED - WatchDog is stopped
 * WDT_RUNNING - WatchDog is running
 * WDT_EXPIRED - WatchDog timeout timer expired
 */
typedef enum
{
    WDT_STOPPED,
    WDT_RUNNING,
    WDT_EXPIRED
} wdt_status_t;

/* Enum: wdt_timeout_config_t
 *
 * WatchDog timer timeout behavior setting.
 *
 * Values:
 *
 * WDT_TIMEOUT_RST  - Reset the device when WatchDog timeout timer expires
 * WDT_TIMEOUT_INTR - Generate Interrupt when WatchDog timeout timer expires
 */
typedef enum
{
    WDT_TIMEOUT_RST,
    WDT_TIMEOUT_INTR
} wdt_timeout_config_t;

/* Enum: wdt_ioctl_t
 *
 * Ioctl request types. 
 *
 * InitTimeoutTime is the initial timeout duration for the watchdog timer immediately 
 * after it is enabled. TimeoutTime specifies the duration for the watchdog timer. 
 * The timer begins counting after the initial timeout period is triggered. 
 * The InitTimeoutTime must be greater than or equal to the TimeoutTime. Not all 
 * platforms may support interrupt generation.
 *
 * Values:
 *
 * WDT_SET_INIT_TIMEOUT      - Set the WatchDog initial timeout value. Time shall be in milliseconds
 * WDT_GET_INIT_TIMEOUT      - Get the WatchDog initial timeout value. Returned values are in milliseconds
 * WDT_SET_TIMEOUT           - Set the WatchDog expire time (timeout value). Time shall be in milliseconds
 * WDT_GET_TIMEOUT           - Get the WatchDog expire time (timeout value). Returned values are in milliseconds
 * WDT_GET_STATUS            - Returns the WatchDog timer status of type wdt_status_t
 * WDT_SET_TIMEOUT_BEHAVIOUR - Set the WatchDog timeout behavior. Takes wdt_timeout_config_t type
 */
typedef enum
{
    WDT_SET_INIT_TIMEOUT,
    WDT_GET_INIT_TIMEOUT,
    WDT_SET_TIMEOUT,
    WDT_GET_TIMEOUT,
    WDT_GET_STATUS,
    WDT_SET_TIMEOUT_BEHAVIOUR
} wdt_ioctl_t;

/* Type: wdt_callback_t
 *
 * WatchDog notification callback type. This callback is passed to the driver by 
 * using the wdt_set_callback API. This callback is used for warning notification 
 * when the watchdog timer expires. This callback will be called only if WatchdogTimeout 
 * behavior is set to interrupt.
 *
 * Parameters:
 *
 * param - User Context passed when setting the callback. This is not used by the 
 * driver, but just passed back to the user in the callback.
 */
typedef void (*wdt_callback_t)(void *param);


/* Function: wdt_open
 *
 * wdt_open is used to initialize the WatchDog. This function will stop the timer 
 * if it was started and resets the timer if any was configured earlier.
 *
 * Parameters:
 *
 * instance - The instance of the WatchDog to initialize.
 *
 * Returns:
 *
 * Handle to wdt_handle_t on success.
 * NULL if invalid instance or instance is already open.
 */
wdt_handle_t wdt_open(uint32_t instance);

/* Function: wdt_start
 *
 * wdt_start is used to start the WatchDog timer counter. WatchDog expiry (timeout) 
 * time must be set before starting the WatchDog counter. Use the WDT_SET_INIT_TIMEOUT 
 * IOCTL to set the initial timeout period and the WDT_SET_TIMEOUT IOCTL to define 
 * the regular timeout duration.
 *
 * Parameters:
 *
 * hwdt - Handle to the WatchDog interface returned in wdt_open.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if hwdt is NULL.
 * -ENODATA if init_timeout or timeout time has not been set.
 */
int32_t wdt_start(const wdt_handle_t hwdt);

/* Function: wdt_stop
 *
 * wdt_stop is used to stop and reset the WatchDog timer counter. 
 * After stopping the timer and before starting the timer again, 
 * the expire time must be set.
 *
 * Parameters:
 *
 * hwdt - Handle to the WatchDog interface returned in wdt_open.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if hwdt is NULL.
 */
int32_t wdt_stop(const wdt_handle_t hwdt);

/* Function: wdt_restart
 *
 * wdt_restart is used to restart the WatchDog timer to the originally programmed 
 * values. This function should be called periodically from a thread or the main 
 * loop to refresh the watchdog timer and prevent it from expiring. Failure to call 
 * this function within the configured timeout window may result in a system reset.
 *
 * Ensure that the interval between calls is shorter than the configured watchdog timeout.
 * The main difference b/w wdt_start and wdt_restart APIs are, the former requires 
 * the time values are set using the IOCTLs and the latter re-uses the already 
 * programmed values and re-programs them. If restart is used without first setting 
 * the timers, it will return an error.
 *
 * Parameters:
 *
 * hwdt - Handle to the WatchDog interface returned in wdt_open.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if hwdt is NULL.
 * -ENODATA if watchdog init_timeout or timeout time have not been set.
 */
int32_t wdt_restart(const wdt_handle_t hwdt);

/* Function: wdt_set_callback
 *
 * wdt_set_callback is used to set the callback to be called when init_timeout 
 * time reaches the WatchDog counter or if the timeout time is configured to 
 * generate interrupt. The caller must set the timers using IOCTL and start the 
 * timer for the callback to be called back. 
 *
 * A single callback is assigned per instance when interrupt behavior is configured. 
 * Newly set callback overrides the one previously set. If input handle or if 
 * callback function is NULL, this function silently takes no action.
 *
 * Parameters:
 *
 * hwdt     - Handle to the WatchDog interface returned in wdt_open.
 * callback - The callback function to be called.
 * param    - The user context to be passed when callback is called.
 *
 * Returns:
 *
 * None.
 */
void wdt_set_callback(const wdt_handle_t hwdt, wdt_callback_t callback, void *param);

/* Function: wdt_ioctl
 *
 * wdt_ioctl is used to configure the WatchDog timer properties like the WatchDog 
 * timeout value, WatchDog timeout behaviour etc.
 *
 * Parameters:
 *
 * hwdt - Handle to the WatchDog interface returned in wdt_open.
 * cmd  - Configuration request of type wdt_ioctl_t.
 * buf  - The configuration buffer to hold the request or response of IOCTL.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if hwdt is NULL, cmd is invalid, buf is NULL, or error in timeout behavior set.
 */
int32_t wdt_ioctl(const wdt_handle_t hwdt, wdt_ioctl_t cmd, void *const buf);

/* Function: wdt_close
 *
 * wdt_close is used to de-initialize the WatchDog, stops the timer if it was 
 * started and resets the timer value.
 *
 * Parameters:
 *
 * hwdt - Handle to the WatchDog interface returned in wdt_open.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if hwdt is NULL, hwdt is not open (previously closed), or failed to stop wdt.
 */
int32_t wdt_close(const wdt_handle_t hwdt);

#endif /* __SOCFPGA_WATCHDOG_H__ */