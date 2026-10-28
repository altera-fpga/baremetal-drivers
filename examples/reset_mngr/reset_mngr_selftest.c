/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: reset_mngr_selftest.c
 *
 * Rst Mngr Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Rst Mngr Example
 */

/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Reset Manager demonstration.
 */

#include <stdint.h>
#include <stdio.h>
#include "../api/console/console_api.h"
#include "../api/rst_mngr/rst_mngr_api.h"
#include "example_register.h"

/* forward declaration (FIX) */
void cmd_reset_mngr(const char *args);

/* ---------------- Safety policy ---------------- */

static int is_safe_to_reset(rst_device_t dev)
{
	/* UART0 is console -> protect it */
	if (dev == RST_DEV_UART0)
		return 0;

	return 1;
}

static void print_reset_status(const char *label, rst_device_t dev)
{
	uint8_t status = 0U;
	int rc = reset_get_device_status(dev, &status);

	if (rc != 0) {
		printf("    %s: FAIL (rc=%d)\n", label, rc);
	} else {
		printf("    %s: %s\n", label, status ? "IN RESET" : "RELEASED");
	}
}

void cmd_reset_mngr(const char *args)
{
	(void)args;
	int32_t ret;

	printf("Reset Manager Demo Start\n");

	/* ---------------- UART0 (protected) ---------------- */
	if (is_safe_to_reset(RST_DEV_UART0)) {
		ret = reset_device(RST_DEV_UART0);
		if (ret != 0)
			printf("UART0 reset failed (rc=%d)\n", ret);
	} else {
		printf("UART0 reset SKIPPED (console in use)\n");
	}

	/* ---------------- SDMMC ---------------- */
	printf("Resetting SDMMC...\n");
	ret = reset_device(RST_DEV_SDMMC);
	if (ret != 0)
		printf("SDMMC reset failed (rc=%d)\n", ret);

	printf("All resets done\n");

	/* ---------------- status check ---------------- */
	print_reset_status("UART0", RST_DEV_UART0);
	print_reset_status("SDMMC", RST_DEV_SDMMC);

	printf("Reset Manager Example Done\n");
}

void register_reset_mngr(void)
{
	cli_register_command("reset_mngr_selftest", cmd_reset_mngr);
}

APP_REGISTER(register_reset_mngr);

