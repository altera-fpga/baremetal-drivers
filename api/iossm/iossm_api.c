/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include "errno.h"
#include "iossm_api.h"
#include "socfpga_iossm.h"
#include "socfpga_iossm_ll.h"

iossm_handle_t iossm_api_open(uint32_t instance)
{
    return (iossm_handle_t)iossm_mw_open(instance);
}

int32_t iossm_api_close(uint32_t instance)
{
    return iossm_mw_close(instance);
}

int32_t iossm_api_close_handle(iossm_handle_t handle)
{
    return iossm_mw_close_ctx((const iossm_mw_ctx_t *)handle);
}

int32_t iossm_api_enable_ecc(iossm_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_enable_ecc((const iossm_mw_ctx_t *)handle, 1U);
}

int32_t iossm_api_disable_ecc(iossm_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_enable_ecc((const iossm_mw_ctx_t *)handle, 0U);
}

int32_t iossm_api_get_ecc_status(iossm_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_read_ecc_status((const iossm_mw_ctx_t *)handle);
}

int32_t iossm_api_clear_ecc_errors(iossm_handle_t handle)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_clear_ecc_buffer((const iossm_mw_ctx_t *)handle);
}

int32_t iossm_api_mask_interrupt(iossm_handle_t handle, uint32_t int_flags)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_mask_interrupt((const iossm_mw_ctx_t *)handle, int_flags);
}

int32_t iossm_api_ack_interrupt(iossm_handle_t handle, uint32_t int_flags)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_ack_interrupt((const iossm_mw_ctx_t *)handle, int_flags);
}

int32_t iossm_api_inject_sbe(iossm_handle_t handle, uint64_t ddr_addr)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_inject_sbit_err((const iossm_mw_ctx_t *)handle, ddr_addr);
}

int32_t iossm_api_inject_dbe(iossm_handle_t handle, uint64_t ddr_addr)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_inject_dbit_err((const iossm_mw_ctx_t *)handle, ddr_addr);
}

int32_t iossm_api_get_err_type(iossm_handle_t handle, uint32_t index)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_get_err_type((const iossm_mw_ctx_t *)handle, index);
}

int32_t iossm_api_get_err_addr(iossm_handle_t handle, uint32_t index)
{
    if (handle == NULL)
    {
        return -EINVAL;
    }
    return iossm_mw_get_err_addr_offset((const iossm_mw_ctx_t *)handle, index);
}

void iossm_api_set_callback(iossm_handle_t handle, void (*handler)(void))
{
    if (handle != NULL)
    {
        iossm_mw_set_callback((iossm_mw_ctx_t *)handle, handler);
    }
}

int32_t iossm_api_mem_write64(uint64_t ddr_addr, uint64_t value)
{
    return iossm_ll_safe_mem_write64(ddr_addr, value);
}

int32_t iossm_api_mem_read64(uint64_t ddr_addr, uint64_t *out_value)
{
    return iossm_ll_safe_mem_read64(ddr_addr, out_value);
}

