/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "errno.h"
#include "crt0.h"
#include "socfpga_uart.h"
#include "lib_printf.h"
#include "platform_def.h"
#include "uart_api.h"

/* UART instance being used */
static uint32_t uart_instance = 0U;
static uint32_t uart_base_address = 0U;
static bool uart_initialized = false;

static uint32_t uart_api_get_base_address(uint32_t instance)
{
	return (uint32_t)(ALT_HPS_UART_BASE + (instance * 0x1000U));
}

/*
 * Initialize UART for baremetal operation
 */
int uart_init(uint32_t instance, uint32_t baudrate, uint32_t clock_freq) {
	if (instance >= UART_MAX_INSTANCE) {
		return -EINVAL;
	}

	uart_instance = instance;
	uart_base_address = uart_api_get_base_address(instance);

	/* Initialize UART via platform hook. */
	platform_uart_init(baudrate, clock_freq);

	uart_initialized = true;

	return 0;
}


/*
 * De-initialize the active bare-metal console UART instance.
 */
int32_t uart_deinit(void)
{
	if (!uart_initialized) {
		return -EINVAL;
	}

	uart_mw_console_disable_all_interrupts(uart_base_address);
	uart_mw_console_shutdown(uart_instance);

	uart_instance = 0U;
	uart_base_address = 0U;
	uart_initialized = false;

	return 0;
}


/*
 * Check whether the bare-metal console UART API is initialized.
 */
bool uart_is_initialized(void)
{
	return uart_initialized;
}


/*
 * Write a single character to UART
 */
void uart_putc(char c) {
	if (!uart_initialized) {
		return;
	}

	(void)uart_mw_console_putc(uart_base_address, c);
}

/*
 * Read a character from UART
 */
char uart_getc(void) {
	char c = '\0';

	if (!uart_initialized) {
		return c;
	}

	(void)uart_mw_console_getc(uart_base_address, &c);
	return c;
}

static void uart_api_putc_adapter(char c, void *ctx)
{
	(void)ctx;
	uart_putc(c);
}

int printf(const char *fmt, ...) {
	va_list args;
	int count;

	va_start(args, fmt);
	count = lib_vprintf(uart_api_putc_adapter, NULL, fmt, args);
	va_end(args);
	return count;
}
