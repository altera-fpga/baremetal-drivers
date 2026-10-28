/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge.h
 *
 * Bridge middleware service interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_BRIDGE_MW_H__
#define __SOCFPGA_BRIDGE_MW_H__

#include <stdint.h>
#include <stdbool.h>

#include "socfpga_bridge_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Status / event flag macros (re-exported for upper layers)
 */
#define BRIDGE_MW_OP_SUCCESS        0     /* Operation completed successfully */
#define BRIDGE_MW_OP_FAILED        -1     /* Generic failure                  */

/*
 * Direction of data movement across a bridge.
 *
 * Pure software state today: the underlying SiP only enables/disables
 * a bridge, but the middleware tracks intended direction so the API
 * can validate set_route calls and so flow-control logic can react to
 * the active route.
 */
/* Enum: bridge_mw_dir_t
 *
 * Enumerates Bridge options, states, commands, or status values.
 *
 * Values:
 *
 *    BRIDGE_MW_DIR_HPS_TO_FPGA - bridge mw dir hps to fpga value.
 *    BRIDGE_MW_DIR_FPGA_TO_HPS - bridge mw dir fpga to hps value.
 *    BRIDGE_MW_DIR_BIDIR - bridge mw dir bidir value.
 */
typedef enum
{
    BRIDGE_MW_DIR_HPS_TO_FPGA = 0,
    BRIDGE_MW_DIR_FPGA_TO_HPS = 1,
    BRIDGE_MW_DIR_BIDIR       = 2
} bridge_mw_dir_t;

/*
 * Flow-control mode applied to a bridge.
 */
/* Enum: bridge_mw_flow_ctrl_t
 *
 * Enumerates Bridge options, states, commands, or status values.
 *
 * Values:
 *
 *    BRIDGE_MW_FLOW_NONE - bridge mw flow none value.
 *    BRIDGE_MW_FLOW_BACKPRESSURE - bridge mw flow backpressure value.
 *    BRIDGE_MW_FLOW_CREDIT - bridge mw flow credit value.
 */
typedef enum
{
    BRIDGE_MW_FLOW_NONE         = 0,  /* No flow control                      */
    BRIDGE_MW_FLOW_BACKPRESSURE = 1,  /* Honour AXI ready/valid backpressure  */
    BRIDGE_MW_FLOW_CREDIT       = 2   /* Credit-based flow control            */
} bridge_mw_flow_ctrl_t;

/*
 * Routing configuration for a bridge instance.
 */
/* Struct: bridge_mw_route_t
 *
 * Describes Bridge configuration, state, or transfer information.
 */
typedef struct
{
    bridge_mw_dir_t direction;     /* Intended traffic direction              */
    uint64_t        base_addr;     /* Base address of the routed window       */
    uint64_t        window_size;   /* Window size in bytes (0 = unrestricted) */
} bridge_mw_route_t;

/*
 * Per-bridge context, returned by bridge_mw_open.
 *
 * Treat as opaque from outside the bridge driver/middleware/API stack.
 */
/* Struct: bridge_mw_ctx_t
 *
 * Describes Bridge configuration, state, or transfer information.
 */
typedef struct
{
    bridge_ll_id_t        id;          /* Which physical bridge this is        */
    bool                  is_open;     /* True between open() and close()      */
    bool                  is_enabled;  /* Last enable/disable state            */
    bool                  is_paused;   /* Tracks pause/resume state            */
    bridge_mw_flow_ctrl_t flow_ctrl;   /* Active flow-control mode             */
    bridge_mw_route_t     route;       /* Active routing configuration         */
} bridge_mw_ctx_t;

/*
 * Open a bridge instance.
 *
 * id - Physical bridge identifier (see bridge_ll_id_t).
 * Returns: Pointer to the instance context on success, NULL on failure
 *         (bad id or already open).
 */
/* Function: bridge_mw_open
 *
 * Opens a Bridge instance and prepares it for subsequent operations.
 *
 * Parameters:
 *
 *    id - Input value used by the operation.
 *
 * Returns:
 *
 *    A valid handle or pointer on success; NULL when the operation cannot be completed.
 */
bridge_mw_ctx_t *bridge_mw_open(bridge_ll_id_t id);

/*
 * Release a bridge instance context.
 *
 * Software-state operation only: this does NOT touch the silicon.
 * Callers that want a clean shutdown must call bridge_mw_disable()
 * before bridge_mw_close() and check its return value. If close()
 * is called while the bridge is still enabled in hardware, a warning
 * is printed but the context is still released.
 *
 * id - Physical bridge identifier passed to bridge_mw_open().
 * Returns: 0 on success, -EINVAL for an unknown id, -EIO if not opened.
 */
/* Function: bridge_mw_close
 *
 * Closes the Bridge handle or instance and returns it to the inactive state.
 *
 * Parameters:
 *
 *    id - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_close(bridge_ll_id_t id);

/* Function: bridge_mw_close_ctx
 *
 * Closes a Bridge instance using a middleware context pointer.
 *
 * Parameters:
 *
 *    ctx - Context returned by bridge_mw_open().
 *
 * Returns:
 *
 *    0 on success; negative errno on failure.
 */
int32_t bridge_mw_close_ctx(const bridge_mw_ctx_t *ctx);

/*
 * Enable the bridge associated with ctx.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 0 on success, negative errno on failure.
 */
/* Function: bridge_mw_enable
 *
 * Enables the requested Bridge feature, path, interrupt, or hardware block.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_enable(bridge_mw_ctx_t *ctx);

/*
 * Disable the bridge associated with ctx.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 0 on success, negative errno on failure.
 */
/* Function: bridge_mw_disable
 *
 * Disables the requested Bridge feature, path, interrupt, or hardware block.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_disable(bridge_mw_ctx_t *ctx);

/*
 * Report the current enable state of the bridge.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 1 when enabled, 0 when disabled, negative errno on failure.
 */
/* Function: bridge_mw_get_status
 *
 * Reads Bridge state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_get_status(const bridge_mw_ctx_t *ctx);

/*
 * Apply a routing configuration to the bridge.
 *
 * The configuration is validated and stored in the context. Window setup
 * at the silicon level (when supported) happens here; until the SiP grows
 * a configuration command this is a state-only operation that is still
 * checked by bridge_api_get_route() round-trips.
 *
 * ctx - Context returned by bridge_mw_open().
 * route - Desired routing configuration.
 * Returns: 0 on success, -EINVAL for invalid arguments.
 */
/* Function: bridge_mw_set_route
 *
 * Writes or configures Bridge state, data, or register content.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *    route - Input pointer supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_set_route(bridge_mw_ctx_t *ctx, const bridge_mw_route_t *route);

/*
 * Read back the active routing configuration.
 *
 * ctx - Context returned by bridge_mw_open().
 * route - Populated with the current configuration on success.
 * Returns: 0 on success, -EINVAL on bad arguments.
 */
/* Function: bridge_mw_get_route
 *
 * Reads Bridge state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    route - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_get_route(const bridge_mw_ctx_t *ctx, bridge_mw_route_t *route);

/*
 * Set the flow-control mode for the bridge.
 *
 * ctx - Context returned by bridge_mw_open().
 * mode - Desired flow-control mode.
 * Returns: 0 on success, -EINVAL on bad arguments.
 */
/* Function: bridge_mw_set_flow_ctrl
 *
 * Writes or configures Bridge state, data, or register content.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *    mode - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_set_flow_ctrl(bridge_mw_ctx_t *ctx, bridge_mw_flow_ctrl_t mode);

/*
 * Pause traffic across the bridge.
 *
 * Implemented as a disable that preserves the route/flow_ctrl state so a
 * subsequent bridge_mw_resume() restores the previous configuration.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 0 on success, negative errno on failure.
 */
/* Function: bridge_mw_pause
 *
 * Performs a Bridge operation exposed by this layer.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_pause(bridge_mw_ctx_t *ctx);

/*
 * Resume traffic on a previously paused bridge.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 0 on success, negative errno on failure.
 */
/* Function: bridge_mw_resume
 *
 * Performs a Bridge operation exposed by this layer.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_resume(bridge_mw_ctx_t *ctx);

/*
 * Query whether the bridge is currently asserting backpressure.
 *
 * Today this returns 0 (not asserted) when the bridge is enabled and
 * unpaused, and 1 (asserted) when paused or disabled. It will gain real
 * register inspection once the underlying SiP exposes that telemetry.
 *
 * ctx - Context returned by bridge_mw_open().
 * Returns: 0 / 1 on success, negative errno on failure.
 */
/* Function: bridge_mw_get_backpressure
 *
 * Reads Bridge state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t bridge_mw_get_backpressure(const bridge_mw_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* __SOCFPGA_BRIDGE_MW_H__ */
