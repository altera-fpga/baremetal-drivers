/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "gic_api.h"

/* Initialize once before calling this helper. Unmask IRQs at the CPU after
 * registration and enable. Keep callback and context alive while enabled. */
int32_t example_gic_enable(uint32_t irq, uint8_t priority,
                           socfpga_interrupt_callback_t callback, void *context)
{
    int32_t rc = gic_api_register_isr_std(irq, callback, context);
    if (rc != 0) {
        return rc;
    }
    rc = gic_api_enable_std(irq, priority);
    return rc;
}
