/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include "errno.h"

#include "bridge_api.h"
#include "socfpga_bridge.h"        /* middleware header */
#include "socfpga_bridge_ll.h"     /* bridge_ll_id_t    */

/*
 * Translate an API-level bridge id into the LL identifier. Returns
 * BRIDGE_LL_ID_MAX (an invalid value) when the input is out of range.
 */
static bridge_ll_id_t api_id_to_ll(uint32_t bridge_id)
{
    switch (bridge_id)
    {
        case BRIDGE_API_HPS2FPGA:    return BRIDGE_LL_ID_HPS2FPGA;
        case BRIDGE_API_LWHPS2FPGA:  return BRIDGE_LL_ID_LWHPS2FPGA;
        case BRIDGE_API_FPGA2HPS:    return BRIDGE_LL_ID_FPGA2HPS;
        case BRIDGE_API_FPGA2SDRAM:  return BRIDGE_LL_ID_FPGA2SDRAM;
        default:                     return BRIDGE_LL_ID_MAX;
    }
}

bridge_handle_t bridge_api_open(uint32_t bridge_id)
{
    bridge_ll_id_t id = api_id_to_ll(bridge_id);

    if (id == BRIDGE_LL_ID_MAX)
    {
        return NULL;
    }
    return (bridge_handle_t)bridge_mw_open(id);
}

int32_t bridge_api_close(uint32_t bridge_id)
{
    bridge_ll_id_t id = api_id_to_ll(bridge_id);

    if (id == BRIDGE_LL_ID_MAX)
    {
        return -EINVAL;
    }
    return bridge_mw_close(id);
}

int32_t bridge_api_close_handle(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }

    return bridge_mw_close_ctx((const bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_enable(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_enable((bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_disable(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_disable((bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_get_status(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_get_status((const bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_set_route(bridge_handle_t handle, const bridge_api_route_t *route)
{
    bridge_mw_route_t mw_route;

    if ((handle == NULL) || (route == NULL))
    {
        return -EINVAL;
    }

    mw_route.direction   = (bridge_mw_dir_t)route->direction;
    mw_route.base_addr   = route->base_addr;
    mw_route.window_size = route->window_size;

    return bridge_mw_set_route((bridge_mw_ctx_t *)handle, &mw_route);
}

int32_t bridge_api_get_route(bridge_handle_t handle, bridge_api_route_t *route)
{
    bridge_mw_route_t mw_route;
    int32_t           rc;

    if ((handle == NULL) || (route == NULL))
    {
        return -EINVAL;
    }

    rc = bridge_mw_get_route((const bridge_mw_ctx_t *)handle, &mw_route);
    if (rc != 0)
    {
        return rc;
    }

    route->direction   = (bridge_api_dir_t)mw_route.direction;
    route->base_addr   = mw_route.base_addr;
    route->window_size = mw_route.window_size;
    return 0;
}

int32_t bridge_api_set_flow_ctrl(bridge_handle_t handle, bridge_api_flow_ctrl_t mode)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_set_flow_ctrl((bridge_mw_ctx_t *)handle,
                                   (bridge_mw_flow_ctrl_t)mode);
}

int32_t bridge_api_pause(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_pause((bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_resume(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_resume((bridge_mw_ctx_t *)handle);
}

int32_t bridge_api_get_backpressure(bridge_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return bridge_mw_get_backpressure((const bridge_mw_ctx_t *)handle);
}

