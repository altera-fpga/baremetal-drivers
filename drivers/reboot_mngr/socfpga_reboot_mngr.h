/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_reboot_mngr.h
 *
 * Reboot Manager hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_REBOOT_MNGR_H__
#define __SOCFPGA_REBOOT_MNGR_H__

#include "errno.h"

/* Constant: REBOOT_WARM
 * Identifier to initiate a Warm Reboot. A warm reboot asserts the HPS warm reset 
 * request, allowing the Secure Device Manager (SDM) to gracefully reset the CPU 
 * subsystem while preserving certain FPGA and system states.
 */
#define REBOOT_WARM    1U

/* Constant: REBOOT_COLD
 * Identifier to initiate a Cold Reboot. A cold reboot triggers a hard reset of 
 * the entire system, equivalent to a physical power cycle. All volatile states 
 * across the HPS, SDM, and FPGA will be lost.
 */
#define REBOOT_COLD    0U


/* Type: reboot_callback_t
 *
 * Callback function signature used by the Reboot Manager module. This allows 
 * the application to register a shutdown hook that will be executed immediately 
 * before the hardware reset is triggered. It is critical for flushing caches, 
 * unmounting filesystems, or parking external peripherals safely.
 *
 * Parameters:
 *
 * param - An opaque pointer to user context that will be passed directly 
 * to the callback function when invoked.
 */
typedef void (*reboot_callback_t)(void *param);


/* Function: reboot_mngr_set_callback
 *
 * Registers a user-defined function to be executed as a pre-reset hook. The 
 * application should use this to ensure software state is saved or hardware 
 * is safely halted before the physical reboot line is asserted.
 *
 * Parameters:
 *
 * callback - The function pointer to invoke before the reboot occurs.
 * event    - The target reset type for this callback (<REBOOT_WARM> or <REBOOT_COLD>).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the event identifier is unrecognized.
 */
int32_t reboot_mngr_set_callback(reboot_callback_t callback, uint32_t event);

/* Function: reboot_mngr_do_reboot
 *
 * Initiates the physical reboot sequence. This function first checks for and 
 * executes any registered <reboot_callback_t> for the specified event type. 
 * Once the callback completes, it writes to the hardware Reset Manager or SDM 
 * Mailbox to assert the physical reset line.
 *
 * Parameters:
 *
 * event - The desired reset sequence to trigger (<REBOOT_WARM> or <REBOOT_COLD>).
 *
 * Returns:
 *
 * If successful, this function will never return as the system will reset. 
 * It returns -EINVAL if the argument is invalid, or -ENOTSUP if the specific 
 * reboot type is not supported by the underlying hardware configuration.
 */
int32_t reboot_mngr_do_reboot(uint32_t event);

#endif /* __SOCFPGA_REBOOT_MNGR_H__ */
