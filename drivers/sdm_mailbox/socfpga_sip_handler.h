/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sip_handler.h
 *
 * SDM Mailbox hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SIP_HANDLER_H__
#define __SOCFPGA_SIP_HANDLER_H__

#include <stdint.h>
#include <stddef.h>

/*
 * smc_call always loads/stores X1..X11 (11 GP registers).
 * Every buffer passed as register_val must provide at least this many uint64_t.
 */
#define SMC_CALL_REG_COUNT    (11U)

/* Function: smc_call
 *
 * Performs a Secure Monitor Call (SMC) to transition from the current Exception
 * Level (e.g., EL1 or EL2) into the Secure Monitor (EL3), where the Secure Device
 * Manager (SDM) firmware resides.
 *
 * This function handles the low-level assembly sequence required to load the
 * function ID into the X0 register and register arguments into the X1-X11
 * registers. It then executes the `smc` instruction and captures the resulting
 * return values from the CPU registers back into the provided memory array.
 *
 * Parameters:
 *
 * function_id  - The unique identifier for the SiP (Silicon-in-Package) service
 * requested (e.g., mailboxes or security services).
 * register_val - Pointer to an array of at least SMC_CALL_REG_COUNT (11)
 * uint64_t elements representing X1-X11. On entry, this array populates the
 * call arguments; on return, the array is updated with the values returned by
 * the EL3 monitor. Passing a shorter array is undefined behaviour (stack smash).
 *
 * Returns:
 *
 * The value contained in the X0 register post-SMC (typically 0 for success,
 * or a specific error status code as defined by the SiP service).
 */
int smc_call(uint64_t function_id, uint64_t *register_val);

#endif /* __SOCFPGA_SIP_HANDLER_H__ */
