/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: gpio_api.c
 *
 * GPIO source implementation for the SoCFPGA bare-metal software stack.
 *
 * Implements GPIO pin open/close, direction control, and polled reads and
 * writes. The public declarations in gpio_api.h are not yet aligned with
 * this implementation; do not use this interface until they are reconciled.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "socfpga_gpio.h"
#include "socfpga_interrupt.h"
#include "socfpga_gpio_reg.h"
#include "mmio.h"
#include "socfpga_rst_mngr.h"


gpio_handle_t gpio_open(gpio_pin_t pin)
{
    gpio_handle_t handle;
    reset_periphrl_t rst_instance;
    uint8_t reset_status;
    int32_t status;

    if ((pin >= GPIO_NUM_PINS) || (pin < GPIO0_PIN0))
    {
        return NULL;
    }
    if (!is_pin_gpio((uint32_t)pin))
    {
        printf(
                "The pin trying to open is allocated for different interface in Pinmux REG");
        return NULL;
    }

    handle = &(gpio_descriptors[pin]);
    if (handle->is_open == true)
    {
        return NULL;
    }
    rst_instance = gpio_get_rst_instance(pin);
    status = rstmgr_get_reset_status(rst_instance, &reset_status);
    if (status != 0)
    {
        printf("Failed to get GPIO reset status. ");
        return NULL;
    }
    if (reset_status != 0U)
    {
        status = rstmgr_toggle_reset(rst_instance);
        if (status != 0)
        {
            printf("Failed to reset release GPIO block. ");
            return NULL;
        }
    }

    (void)memset(handle, 0, sizeof(struct gpio_descriptor));
    handle->is_open = 1;
    handle->instance = pin;
    return handle;
}

int32_t gpio_ioctl(gpio_handle_t const hgpio, gpio_ioctl_t cmd, void *const buf)
{
    gpio_dir_t dir_config;
    gpio_int_t intr_config;
    int32_t ret = 0;

    if (hgpio == NULL)
    {
        return -EINVAL;
    }
    if (buf == NULL)
    {
        return -EINVAL;
    }
    switch (cmd)
    {
        case SET_GPIO_DIR:
            dir_config = *(gpio_dir_t *)buf;
            gpio_set_direction(hgpio->instance, dir_config);
            break;
        case SET_GPIO_INT:
            intr_config = *(gpio_int_t *)buf;
            if (gpio_set_interrupt(hgpio->instance, intr_config) == false)
            {
                ret = -EINVAL;
            }
            break;
        case GET_GPIO_DIRECTION:
            *(uint8_t *)buf = gpio_get_direction(hgpio->instance);
            break;
        case GET_GPIO_INT:
            *(gpio_int_t *)buf = gpio_get_interrupt(hgpio->instance);
            break;
        default:
            ret = -EINVAL;
            break;
    }
    return ret;
}

void gpio_set_callback(gpio_handle_t const hgpio, gpio_callback_t gpio_callback, void *param)
{
    if (hgpio == NULL)
    {
        return;
    }
    hgpio->callback_fn = gpio_callback;
    hgpio->cb_usercontext = param;
}

int32_t gpio_read_sync(gpio_handle_t const hgpio, uint8_t *pstate)
{
    if ((hgpio == NULL) || (pstate == NULL))
    {
        return -EINVAL;
    }
    if (!(hgpio->is_open))
    {
        return -EINVAL;
    }
    *pstate = gpio_read_state(hgpio->instance);
    return 0;
}

int32_t gpio_write_sync(gpio_handle_t const hgpio, uint8_t state)
{
    if (hgpio == NULL)
    {
        return -EINVAL;
    }
    if (!(hgpio->is_open))
    {
        return -EINVAL;
    }
    gpio_write_state(hgpio->instance, state);
    return 0;
}

int32_t gpio_close(gpio_handle_t const hgpio)
{
    if ((hgpio == NULL) || (hgpio->is_open == 0))
    {
        return -EINVAL;
    }
    if (gpio_get_interrupt(hgpio->instance) != GPIO_INT_NONE)
    {
        if (gpio_set_interrupt(hgpio->instance, GPIO_INT_NONE) == false)
        {
            return -EINVAL;
        }
        hgpio->callback_fn = NULL;
    }
    hgpio->is_open = 0;

    return 0;
}
