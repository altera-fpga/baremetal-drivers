/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: bridge_api.h
 *
 * Open, enable, and disable a Hard Processor System (HPS)-FPGA bridge through the secure monitor.
 *
 * bridge_api_enable() and bridge_api_disable() program the bridge.
 * bridge_api_get_status() returns the enable flag those calls store; it
 * does not read the device. bridge_api_set_route() and
 * bridge_api_get_route() only store the request in software. Flow-control,
 * pause, and resume update software state; pause and resume also disable
 * or enable the bridge. They do not program flow-control registers.
 *
 * Call bridge_api_open(), then bridge_api_enable(), then the operations
 * you need, then bridge_api_disable() and bridge_api_close_handle().
 * bridge_api_close() releases the handle and does not disable the bridge.
 */

#ifndef __BRIDGE_API_H__
#define __BRIDGE_API_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * Preferred user call flow (handle-based):
 * 1) bridge_api_open(bridge_id)
 * 2) bridge_api_enable(handle)
 * 3) bridge_api_set_* / bridge_api_get_*
 * 4) bridge_api_disable(handle)
 * 5) bridge_api_close_handle(handle)
 *
 * Legacy close-by-id is kept for compatibility during migration.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Type: bridge_handle_t
 *
 * Opaque handle returned by bridge_api_open(). Pass the handle unchanged to the handle-based bridge operations.
 */
typedef void *bridge_handle_t;

/*
 * Bridge identifiers (mirror bridge_ll_id_t numerically; kept separate so
 * application code does not need to include the LL header).
 */
/* Constant: BRIDGE_API_HPS2FPGA
 * Bridge identifier for the HPS-to-FPGA bridge.
 */
#define BRIDGE_API_HPS2FPGA      0U
/* Constant: BRIDGE_API_LWHPS2FPGA
 * Bridge identifier for the lightweight HPS-to-FPGA bridge.
 */
#define BRIDGE_API_LWHPS2FPGA    1U
/* Constant: BRIDGE_API_FPGA2HPS
 * Bridge identifier for the FPGA-to-HPS bridge.
 */
#define BRIDGE_API_FPGA2HPS      2U
/* Constant: BRIDGE_API_FPGA2SDRAM
 * Bridge identifier for the FPGA-to-SDRAM bridge.
 */
#define BRIDGE_API_FPGA2SDRAM    3U

/* Result codes returned by API functions */
/* Constant: BRIDGE_API_OP_OK
 * Successful bridge API status value.
 */
#define BRIDGE_API_OP_OK         0     /* Success                            */
/* Negative values are errno-style: -EINVAL, -EIO, ...                       */

/* Routing */

/* Enum: bridge_api_dir_t
 *
 * Direction stored by bridge_api_set_route(). The current middleware stores this value in software; it does not program routing hardware.
 *
 * Values:
 *
 *    BRIDGE_API_DIR_HPS_TO_FPGA - Hard Processor System (HPS) to FPGA.
 *    BRIDGE_API_DIR_FPGA_TO_HPS - FPGA to HPS.
 *    BRIDGE_API_DIR_BIDIR - Both directions.
 */
typedef enum
{
    BRIDGE_API_DIR_HPS_TO_FPGA = 0,
    BRIDGE_API_DIR_FPGA_TO_HPS = 1,
    BRIDGE_API_DIR_BIDIR       = 2
} bridge_api_dir_t;

/* Struct: bridge_api_route_t
 *
 * Route record stored by bridge_api_set_route().
 *
 * Fields:
 *
 *    direction - Requested traffic direction. HPS-to-FPGA bridges reject FPGA-to-HPS-only routing, and the FPGA-to-HPS bridge rejects HPS-to-FPGA-only routing.
 *    base_addr - Base address retained in software with the route record. The current middleware does not program it into hardware.
 *    window_size - Window size retained in software with the route record. The current middleware does not program it into hardware.
 */
typedef struct
{
    bridge_api_dir_t direction;
    uint64_t         base_addr;
    uint64_t         window_size;
} bridge_api_route_t;

/* Flow control */

/* Enum: bridge_api_flow_ctrl_t
 *
 * Flow-control value stored by bridge_api_set_flow_ctrl(). Not programmed into a flow-control register.
 *
 * Values:
 *
 *    BRIDGE_API_FLOW_NONE - No flow control.
 *    BRIDGE_API_FLOW_BACKPRESSURE - Ready/valid backpressure.
 *    BRIDGE_API_FLOW_CREDIT - Credit-based flow control.
 */
typedef enum
{
    BRIDGE_API_FLOW_NONE         = 0,  /* No flow control                    */
    BRIDGE_API_FLOW_BACKPRESSURE = 1,  /* Honour AXI ready/valid backpressure */
    BRIDGE_API_FLOW_CREDIT       = 2   /* Credit-based flow control          */
} bridge_api_flow_ctrl_t;

/* -------------------------------------------------------------------------
 * Lifecycle
 * ------------------------------------------------------------------------- */

/* Function: bridge_api_open
 *
 * Open one bridge instance and return its middleware handle.
 *
 * Parameters:
 *
 *    bridge_id - BRIDGE_API_HPS2FPGA, BRIDGE_API_LWHPS2FPGA, BRIDGE_API_FPGA2HPS, or BRIDGE_API_FPGA2SDRAM.
 *
 * Returns:
 *
 *    A handle on success. NULL when bridge_id is invalid or that bridge instance is already open.
 */
bridge_handle_t bridge_api_open(uint32_t bridge_id);

/* Function: bridge_api_close_handle
 *
 * Release an opened bridge handle. This call does not disable the bridge; disable it first if it must be left disabled.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL or does not refer to a bridge context. -EIO when the referenced bridge is not open.
 */
int32_t bridge_api_close_handle(bridge_handle_t handle);

/* Function: bridge_api_close
 *
 * Release an opened bridge by identifier. This call does not disable the bridge; disable it first if it must be left disabled.
 *
 * Parameters:
 *
 *    bridge_id - Identifier originally passed to bridge_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when bridge_id is invalid. -EIO when that bridge is not open.
 */
int32_t bridge_api_close(uint32_t bridge_id);

/* -------------------------------------------------------------------------
 * Enable / status
 * ------------------------------------------------------------------------- */

/* Function: bridge_api_enable
 *
 * Enable traffic across an opened bridge.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the handle is not open or the low-level bridge enable request fails.
 */
int32_t bridge_api_enable(bridge_handle_t handle);

/* Function: bridge_api_disable
 *
 * Disable traffic across an opened bridge.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the handle is not open or the low-level bridge disable request fails.
 */
int32_t bridge_api_disable(bridge_handle_t handle);

/* Function: bridge_api_get_status
 *
 * Return the enable state stored for an opened bridge.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    1 when enabled and 0 when disabled. -EINVAL when handle is NULL. -EIO when the handle is not open.
 */
int32_t bridge_api_get_status(bridge_handle_t handle);

/* Routing */

/* Function: bridge_api_set_route
 *
 * Store a route in the bridge context. The current middleware does not program the route into hardware.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *    route - Route to store. Must not be NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL for a NULL argument, an unknown direction, or a direction that conflicts with the selected bridge. -EIO when the handle is not open.
 */
int32_t bridge_api_set_route(bridge_handle_t handle, const bridge_api_route_t *route);

/* Function: bridge_api_get_route
 *
 * Copy the route previously stored in the bridge context. This call does not read routing hardware.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *    route - Receives the stored route. Must not be NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle or route is NULL. -EIO when the handle is not open.
 */
int32_t bridge_api_get_route(bridge_handle_t handle, bridge_api_route_t *route);

/* Flow control */

/* Function: bridge_api_set_flow_ctrl
 *
 * Store the flow-control mode in the bridge context. The current middleware does not program a flow-control register.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *    mode - BRIDGE_API_FLOW_NONE, BRIDGE_API_FLOW_BACKPRESSURE, or BRIDGE_API_FLOW_CREDIT.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL or mode is invalid. -EIO when the handle is not open.
 */
int32_t bridge_api_set_flow_ctrl(bridge_handle_t handle, bridge_api_flow_ctrl_t mode);

/* Function: bridge_api_pause
 *
 * Pause an opened bridge by issuing the same low-level disable operation used by bridge_api_disable(), while retaining route and flow-control state for bridge_api_resume(). A bridge already marked paused is left unchanged.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 on success or when already paused. -EINVAL when handle is NULL. -EIO when the handle is not open or the low-level disable request fails.
 */
int32_t bridge_api_pause(bridge_handle_t handle);

/* Function: bridge_api_resume
 *
 * Re-enable a bridge that was paused by bridge_api_pause(). A bridge that is not marked paused is left unchanged.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 on success or when the bridge is not paused. -EINVAL when handle is NULL. -EIO when the handle is not open or the low-level enable request fails.
 */
int32_t bridge_api_resume(bridge_handle_t handle);

/* Function: bridge_api_get_backpressure
 *
 * Report the middleware backpressure state derived from the stored enable and pause flags.
 *
 * Parameters:
 *
 *    handle - Handle returned by bridge_api_open().
 *
 * Returns:
 *
 *    0 when the bridge is enabled and not paused; 1 when it is disabled or paused. -EINVAL when handle is NULL. -EIO when the handle is not open.
 */
int32_t bridge_api_get_backpressure(bridge_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __BRIDGE_API_H__ */
