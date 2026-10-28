/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: main.c
 *
 * Main source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: src
 * Component: Main
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include "../api/console/console_api.h"
#include "../api/uart/uart_api.h"
#include "../examples/example_register.h"
#include "platform_def.h"

void main(void)
{
#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
	/* OCRAM/FSBL boot: lock the PLLs to 100 MHz, then set the console baud
	 * from the live L4_SP clock (no hardcoded rate). */
	platform_pll_init();
	uart_init(0, 115200, platform_get_l4sp_clk());
#else
	/* Loaded by ATF/U-Boot (DDR/BL33): clocks already established. */
	uart_init(0, 115200, HPS_PERIP_UART_CLK);
	platform_clk_init();
	uart_init(0, 115200, HPS_PERIP_UART_CLK);
#endif

	/* Print platform inform */
	platform_print_info();

	/* auto-register all examples */
	app_register();

	/* Start CLI loop */
	cli_run();
}
