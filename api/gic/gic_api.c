/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "socfpga_interrupt.h"
#include "errno.h"
#include "gic_api.h"

static int32_t gic_api_err_to_errno(socfpga_interrupt_err_t err)
{
    switch (err) {
    case ERR_OK:
        return 0;
    case ERR_SPI_ID:
    case ERR_SPI_TYPE:
    case ERR_SPI_MODE:
    case ERR_SPI_TARGET:
    case ERR_INTERRUPT_CALLBACK:
    case ERR_PPI_ID:
    case ERR_SGI_ID:
        return -EINVAL;
    default:
        return -EIO;
    }
}


/* Wrapper around socfpga_interrupt.c */

void gic_api_init(void)
{
    interrupt_init_gic();
}

socfpga_interrupt_err_t gic_api_enable(uint32_t irq, uint8_t priority)
{
    return interrupt_enable((socfpga_hpu_interrupt_t)irq, priority);
}

socfpga_interrupt_err_t gic_api_disable(uint32_t irq)
{
    return interrupt_spi_disable((socfpga_hpu_interrupt_t)irq);
}

socfpga_interrupt_err_t gic_api_register_isr(uint32_t irq,
        socfpga_interrupt_callback_t callback, void *user_data)
{
    return interrupt_register_isr((socfpga_hpu_interrupt_t)irq, callback, user_data);
}

socfpga_interrupt_err_t gic_send_sgi(uint32_t sgi_id, uint8_t target_cpu_mask);
socfpga_interrupt_err_t gic_api_trigger_sgi(uint32_t sgi_id, uint8_t cpu_mask)
{
    return gic_send_sgi(sgi_id, cpu_mask);
}

int32_t gic_api_init_std(void)
{
    gic_api_init();
    return 0;
}

int32_t gic_api_enable_std(uint32_t irq, uint8_t priority)
{
    return gic_api_err_to_errno(gic_api_enable(irq, priority));
}

int32_t gic_api_disable_std(uint32_t irq)
{
    return gic_api_err_to_errno(gic_api_disable(irq));
}

int32_t gic_api_register_isr_std(uint32_t irq,
        socfpga_interrupt_callback_t callback, void *user_data)
{
    return gic_api_err_to_errno(gic_api_register_isr(irq, callback, user_data));
}

int32_t gic_api_trigger_sgi_std(uint32_t sgi_id, uint8_t cpu_mask)
{
    return gic_api_err_to_errno(gic_api_trigger_sgi(sgi_id, cpu_mask));
}
