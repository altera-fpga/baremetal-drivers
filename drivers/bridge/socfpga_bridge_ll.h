/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge_ll.h
 *
 * Low-level FPGA bridge interface. Enable and disable requests are sent
 * to the Secure Interface Platform (SiP) with a Secure Monitor Call.
 */

#ifndef __SOCFPGA_BRIDGE_LL_H__
#define __SOCFPGA_BRIDGE_LL_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Enum: bridge_ll_id_t
 *
 * Identifiers for the available FPGA-HPS bridge instances. 
 * Note: These values are part of the public ABI and must remain stable.
 *
 * Values:
 *
 * BRIDGE_LL_ID_HPS2FPGA   - Standard HPS-to-FPGA AXI master bridge.
 * BRIDGE_LL_ID_LWHPS2FPGA - Light-Weight HPS-to-FPGA AXI master bridge.
 * BRIDGE_LL_ID_FPGA2HPS   - FPGA-to-HPS AXI slave bridge.
 * BRIDGE_LL_ID_FPGA2SDRAM - FPGA-to-SDRAM AXI slave bridge.
 * BRIDGE_LL_ID_MAX        - Sentinel value indicating the end of the ID list.
 */
typedef enum
{
    BRIDGE_LL_ID_HPS2FPGA   = 0,
    BRIDGE_LL_ID_LWHPS2FPGA = 1,
    BRIDGE_LL_ID_FPGA2HPS   = 2,
    BRIDGE_LL_ID_FPGA2SDRAM = 3,
    BRIDGE_LL_ID_MAX        = 4
} bridge_ll_id_t;


/* Constants: Status codes
 *
 * Values the bridge calls return.
 *
 * BRIDGE_LL_OP_OK     - The call worked.
 * BRIDGE_LL_OP_EINVAL - The bridge id is not a known bridge.
 * BRIDGE_LL_OP_EIO    - The SiP service did not return success.
 */
#define BRIDGE_LL_OP_OK       0    /* Operation completed successfully */
#define BRIDGE_LL_OP_EINVAL   -22  /* Invalid argument provided */
#define BRIDGE_LL_OP_EIO      -5   /* Hardware or SiP service failure */


/* Function: bridge_ll_set
 *
 * Issues a Secure Monitor Call (SMC) to toggle the state of an FPGA bridge.
 *
 * This function triggers the `SIP_SMC_HPS_SET_BRIDGES` command, communicating 
 * directly with the secure monitor to enable or disable the specified bridge. 
 * This is the lowest-level control point in the stack.
 *
 * Parameters:
 *
 * id     - The bridge identifier (<bridge_ll_id_t>).
 * enable - Boolean indicating the desired state (true to enable, false to disable).
 *
 * Returns:
 *
 * <BRIDGE_LL_OP_OK> on success; <BRIDGE_LL_OP_EINVAL> for invalid IDs; 
 * <BRIDGE_LL_OP_EIO> if the SiP service reports a fault.
 */
int32_t bridge_ll_set(bridge_ll_id_t id, bool enable);

/* Function: bridge_ll_name
 *
 * Resolves the hardware bridge identifier into a human-readable string.
 *
 * Parameters:
 *
 * id - The bridge identifier.
 *
 * Returns:
 *
 * A pointer to a static, NUL-terminated string representing the bridge name.
 */
const char *bridge_ll_name(bridge_ll_id_t id);

#ifdef __cplusplus
}
#endif

#endif /* __SOCFPGA_BRIDGE_LL_H__ */