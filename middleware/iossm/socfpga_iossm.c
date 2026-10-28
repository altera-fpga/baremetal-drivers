/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_iossm.c
 *
 * IOSSM source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: middleware
 * Component: IOSSM
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>

#include "socfpga_iossm.h"
#include "socfpga_iossm_ll.h"
#include "socfpga_interrupt.h"
#include "cache.h"

static iossm_mw_ctx_t s_iossm_ctx[IOSSM_MW_MAX_INSTANCE];

/* Validate a context pointer and check that the instance is open.
 * Returns 0 when valid and open, -EINVAL for NULL, and -EIO when not open. */
static int32_t iossm_mw_check_ctx(const iossm_mw_ctx_t *ctx)
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

/* Build an iossm_ll_desc_t descriptor from a middleware context. */
static void iossm_mw_fill_desc(const iossm_mw_ctx_t *ctx, iossm_ll_desc_t *desc)
{
    desc->base_addr   = ctx->base_addr;
    desc->ip_type     = ctx->ip_type;
    desc->instance_id = ctx->instance_id;
}

iossm_mw_ctx_t *iossm_mw_open(uint32_t instance)
{
    iossm_ll_response_t resp;
    iossm_ll_desc_t     desc;
    socfpga_interrupt_err_t int_ret;
    iossm_mw_ctx_t *ctx;

    if (instance >= IOSSM_MW_MAX_INSTANCE)
    {
        printf("IOSSM MW: invalid instance %u\n", instance);
        return NULL;
    }

    ctx = &s_iossm_ctx[instance];

    if (ctx->is_open)
    {
        printf("IOSSM MW: instance %u already open\n", instance);
        return NULL;
    }

    (void)memset(ctx, 0, sizeof(*ctx));

    /* Resolve base address for this instance */
    if (iossm_ll_get_base_addr(instance, &ctx->base_addr) != 0)
    {
        printf("IOSSM MW: base address lookup failed for instance %u\n", instance);
        return NULL;
    }

    /* Register IRQ handler and enable the GIC SPI line.
     * GIC wiring is optional: if the GIC is not yet initialised the driver
     * still functions fully in polling mode (ECC status, mailbox commands,
     * safe memory access).  IRQ-driven ECC notification is simply unavailable
     * until the GIC is set up and the instance is re-opened.           */
    int_ret = interrupt_register_isr(IO96B0_DBE_IRQ, iossm_mw_irq_handler, ctx);
    if (int_ret != ERR_OK)
    {
        printf("IOSSM MW: IRQ register failed (%d) - polling mode only\n", (int)int_ret);
        ctx->irq_enabled = false;
    }
    else
    {
        int_ret = interrupt_spi_enable(IO96B0_DBE_IRQ,
                                       SPI_INTERRUPT_TYPE_EDGE,
                                       SPI_INTERRUPT_MODE_TARGET,
                                       GIC_INTERRUPT_PRIORITY_IOSSM);
        if (int_ret != ERR_OK)
        {
            printf("IOSSM MW: IRQ enable failed (%d) - polling mode only\n", (int)int_ret);
            ctx->irq_enabled = false;
        }
        else
        {
            ctx->irq_enabled = true;
        }
    }

    /* Query system info to learn ip_type and instance_id */
    desc.base_addr   = ctx->base_addr;
    desc.ip_type     = 0U;
    desc.instance_id = 0U;

    resp = iossm_ll_send_command(&desc, IOSSM_LL_GET_SYS_INFO, IOSSM_LL_NO_PARAM);

    ctx->instance_id = (uint8_t)(resp.resp0 & 0xE1FFFFFFu);
    ctx->ip_type     = 1U;
    ctx->is_open     = true;

    return ctx;
}

int32_t iossm_mw_close(uint32_t instance)
{
    if (instance >= IOSSM_MW_MAX_INSTANCE)
    {
        printf("IOSSM MW: invalid instance %u\n", instance);
        return -EINVAL;
    }
    if (!s_iossm_ctx[instance].is_open)
    {
        printf("IOSSM MW: instance %u not opened\n", instance);
        return -EIO;
    }
    s_iossm_ctx[instance].is_open = false;
    return 0;
}

int32_t iossm_mw_close_ctx(const iossm_mw_ctx_t *ctx)
{
    if (ctx == NULL)
    {
        return -EINVAL;
    }

    if ((ctx < &s_iossm_ctx[0]) || (ctx >= &s_iossm_ctx[IOSSM_MW_MAX_INSTANCE]))
    {
        return -EINVAL;
    }

    return iossm_mw_close(ctx->instance_id);
}

int32_t iossm_mw_enable_ecc(const iossm_mw_ctx_t *ctx, uint32_t enable)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_send_command(&desc, IOSSM_LL_ECC_EN, enable);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return 0;
}

int32_t iossm_mw_read_ecc_status(const iossm_mw_ctx_t *ctx)
{
    uint32_t status;
    int32_t  ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    status  = iossm_ll_read_reg32(ctx->base_addr, IOSSM_ECC_ERROR_STATUS);
    status &= IOSSM_ECC_COUNT_MASK;

    return (int32_t)status;
}

int32_t iossm_mw_clear_ecc_buffer(const iossm_mw_ctx_t *ctx)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_send_command(&desc, IOSSM_LL_ECC_CLEAR_ERR, IOSSM_LL_NO_PARAM);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return (int32_t)((resp.status >> 16U) & 0x7U);
}

int32_t iossm_mw_mask_interrupt(const iossm_mw_ctx_t *ctx, uint32_t interrupts)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_send_command(&desc, IOSSM_LL_ECC_INT_MASK, interrupts);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return 0;
}

int32_t iossm_mw_ack_interrupt(const iossm_mw_ctx_t *ctx, uint32_t interrupts)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_send_command(&desc, IOSSM_LL_ECC_INT_ACK, interrupts);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return 0;
}

int32_t iossm_mw_get_err_type(const iossm_mw_ctx_t *ctx, uint32_t index)
{
    uint32_t status;
    int32_t  ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    status = iossm_ll_read_reg32(ctx->base_addr, IOSSM_ECC_GET_ERR_TYPE(index));
    return (int32_t)IOSSM_ECC_ERR_TYP_FIELD(status);
}

int32_t iossm_mw_get_err_addr_offset(const iossm_mw_ctx_t *ctx, uint32_t index)
{
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    return (int32_t)iossm_ll_read_reg32(ctx->base_addr, IOSSM_ECC_GET_ERR_OFFSET(index));
}

int32_t iossm_mw_inject_sbit_err(const iossm_mw_ctx_t *ctx, uint64_t ddr_addr)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_err_inject_command(&desc, ddr_addr, IOSSM_LL_SING_BIT_ERR_PARAM);

    /* Invalidate the cache line covering the injection address so any
     * subsequent read exercises the ECC correction path.                 */
    cache_force_invalidate((void *)(uintptr_t)ddr_addr, 8);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return 0;
}

int32_t iossm_mw_inject_dbit_err(const iossm_mw_ctx_t *ctx, uint64_t ddr_addr)
{
    iossm_ll_desc_t     desc;
    iossm_ll_response_t resp;
    int32_t ret;

    ret = iossm_mw_check_ctx(ctx);
    if (ret != 0)
    {
        return ret;
    }

    iossm_mw_fill_desc(ctx, &desc);
    resp = iossm_ll_err_inject_command(&desc, ddr_addr, IOSSM_LL_DBL_BIT_ERR_PARAM);

    cache_force_invalidate((void *)(uintptr_t)ddr_addr, 8);

    if ((resp.status & 1U) != 1U)
    {
        return -EIO;
    }
    return 0;
}

void iossm_mw_set_callback(iossm_mw_ctx_t *ctx, void (*handler)(void))
{
    if (ctx != NULL)
    {
        ctx->cb_handler = handler;
    }
}

void iossm_mw_irq_handler(void *pparam)
{
    iossm_mw_ctx_t *ctx = (iossm_mw_ctx_t *)pparam;

    if ((ctx != NULL) && (ctx->cb_handler != NULL))
    {
        ctx->cb_handler();
    }
}
