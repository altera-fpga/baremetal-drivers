/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: gpio_selftest.c
 *
 * Gpio Control source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Gpio Control
 */

#include <stdio.h>
#include "example_register.h"
#include "../api/console/console_api.h"
#include "../api/gpio/gpio_api.h"

static void gpio_control_main(const char *args)
{
    (void)args;
    gpio_handle_t gpio = NULL;

    gpio_ioctl(gpio, GPIO_CMD_SET_DIRECTION, (void*)GPIO_OUTPUT);
    gpio_write_sync(gpio, 1);

    uint8_t value;
    gpio_read_sync(gpio, &value);
    printf("GPIO value: %d\n", value);

    gpio_close(gpio);
}

/* Registration function for CLI */
void register_gpio_control(void)
{
    cli_register_command("gpio_selftest", gpio_control_main);
}

/* Auto-register into special section for boot-time registration */
APP_REGISTER(register_gpio_control)

