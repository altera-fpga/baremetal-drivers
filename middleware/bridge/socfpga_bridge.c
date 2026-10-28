/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge.c
 *
 * Bridge source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: middleware
 * Component: Bridge
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "socfpga_bridge.h"

static bridge_mw_ctx_t s_bridge_ctx[BRIDGE_LL_ID_MAX];

static int32_t bridge_mw_check_ctx(const bridge_mw_ctx_t *ctx)
{
    if (ctx == NULL)
    {
        return -EINVAL;
    }
    if (!ctx->is_open)
    {
        return -EIO;
    }
    return 0;
}

static int32_t bridge_mw_apply_enable(bridge_mw_ctx_t *ctx, bool enable)
{
    int32_t rc = bridge_ll_set(ctx->id, enable);
    if (rc != BRIDGE_LL_OP_OK)
    {
        return -EIO;
    }
    ctx->is_enabled = enable;
    return 0;
}

bridge_mw_ctx_t *bridge_mw_open(bridge_ll_id_t id)
{
    bridge_mw_ctx_t *ctx;

    if ((unsigned)id >= (unsigned)BRIDGE_LL_ID_MAX)
    {
        printf("BRIDGE MW: invalid bridge id %u\n", (unsigned)id);
        return NULL;
    }

    ctx = &s_bridge_ctx[id];

    if (ctx->is_open)
    {
        printf("BRIDGE MW: %s already open\n", bridge_ll_name(id));
        return NULL;
    }

    (void)memset(ctx, 0, sizeof(*ctx));
    ctx->id        = id;
    ctx->is_open   = true;
    ctx->flow_ctrl = BRIDGE_MW_FLOW_NONE;

    return ctx;
}

int32_t bridge_mw_close(bridge_ll_id_t id)
{
    bridge_mw_ctx_t *ctx;

    if ((unsigned)id >= (unsigned)BRIDGE_LL_ID_MAX)
    {
        printf("BRIDGE MW: invalid bridge id %u\n", (unsigned)id);
        return -EINVAL;
    }

    ctx = &s_bridge_ctx[id];

    if (!ctx->is_open)
    {
        printf("BRIDGE MW: %s not opened\n", bridge_ll_name(id));
        return -EIO;
    }

    /* Intentionally do NOT touch the silicon here.  Releasing the context
     * is a software-state operation; SiP enable/disable belongs to the
     * caller via bridge_mw_disable().  This avoids:
     *   - a duplicate SiP call when the caller has already disabled;
     *   - a misleading "close OK" when an internal disable retry fails
     *     (e.g. ATF rejects FPGA2HPS disable when no FPGA design is
     *     loaded and returns SIP_SMC_STATUS_ERROR).
     * The bridge enable bit is a hardware state, not a context state. */
    if (ctx->is_enabled)
    {
        printf("BRIDGE MW: %s closed while still enabled in hardware\n",
               bridge_ll_name(ctx->id));
    }

    ctx->is_open = false;
    return 0;
}

int32_t bridge_mw_close_ctx(const bridge_mw_ctx_t *ctx)
{
    if (ctx == NULL)
    {
        return -EINVAL;
    }

    if ((ctx < &s_bridge_ctx[0]) || (ctx >= &s_bridge_ctx[BRIDGE_LL_ID_MAX]))
    {
        return -EINVAL;
    }

    return bridge_mw_close(ctx->id);
}

int32_t bridge_mw_enable(bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    rc = bridge_mw_apply_enable(ctx, true);
    if (rc == 0)
    {
        ctx->is_paused = false;
    }
    return rc;
}

int32_t bridge_mw_disable(bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    return bridge_mw_apply_enable(ctx, false);
}

int32_t bridge_mw_get_status(const bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    return ctx->is_enabled ? 1 : 0;
}

int32_t bridge_mw_set_route(bridge_mw_ctx_t *ctx, const bridge_mw_route_t *route)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    if (route == NULL)
    {
        return -EINVAL;
    }

    if ((route->direction != BRIDGE_MW_DIR_HPS_TO_FPGA) &&
        (route->direction != BRIDGE_MW_DIR_FPGA_TO_HPS) &&
        (route->direction != BRIDGE_MW_DIR_BIDIR))
    {
        return -EINVAL;
    }

    /* HPS2FPGA / LWHPS2FPGA are inherently HPS->FPGA traffic; FPGA2HPS is
     * the reverse. Catch obvious mismatches early so callers don't program
     * a route the silicon cannot honour. */
    switch (ctx->id)
    {
        case BRIDGE_LL_ID_HPS2FPGA:
        case BRIDGE_LL_ID_LWHPS2FPGA:
            if (route->direction == BRIDGE_MW_DIR_FPGA_TO_HPS)
            {
                return -EINVAL;
            }
            break;
        case BRIDGE_LL_ID_FPGA2HPS:
            if (route->direction == BRIDGE_MW_DIR_HPS_TO_FPGA)
            {
                return -EINVAL;
            }
            break;
        case BRIDGE_LL_ID_FPGA2SDRAM:
        default:
            break;
    }

    ctx->route = *route;
    return 0;
}

int32_t bridge_mw_get_route(const bridge_mw_ctx_t *ctx, bridge_mw_route_t *route)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }
    if (route == NULL)
    {
        return -EINVAL;
    }

    *route = ctx->route;
    return 0;
}

int32_t bridge_mw_set_flow_ctrl(bridge_mw_ctx_t *ctx, bridge_mw_flow_ctrl_t mode)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    if ((mode != BRIDGE_MW_FLOW_NONE) &&
        (mode != BRIDGE_MW_FLOW_BACKPRESSURE) &&
        (mode != BRIDGE_MW_FLOW_CREDIT))
    {
        return -EINVAL;
    }

    ctx->flow_ctrl = mode;
    return 0;
}

int32_t bridge_mw_pause(bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    if (ctx->is_paused)
    {
        return 0;
    }

    rc = bridge_mw_apply_enable(ctx, false);
    if (rc == 0)
    {
        ctx->is_paused = true;
    }
    return rc;
}

int32_t bridge_mw_resume(bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    if (!ctx->is_paused)
    {
        return 0;
    }

    rc = bridge_mw_apply_enable(ctx, true);
    if (rc == 0)
    {
        ctx->is_paused = false;
    }
    return rc;
}

int32_t bridge_mw_get_backpressure(const bridge_mw_ctx_t *ctx)
{
    int32_t rc = bridge_mw_check_ctx(ctx);
    if (rc != 0)
    {
        return rc;
    }

    return (ctx->is_enabled && !ctx->is_paused) ? 0 : 1;
}
