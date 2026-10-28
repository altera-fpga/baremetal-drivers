/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: reboot_mngr_selftest.c
 *
 * Reboot Mngr Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Reboot Mngr Example
 */

#include <stdint.h>
#include <stdio.h>
#include "../api/console/console_api.h"
#include "../api/reboot_mngr/reboot_mngr_api.h"
#include "example_register.h"

/* forward declaration */
void cmd_reboot(const char *args);

/* ---------------- Callback example ---------------- */

static void before_reboot(void *arg)
{
	(void)arg;

	printf("Preparing for reboot...\n");

	/* Example actions */
	printf("Saving logs...\n");
	printf("Stopping peripherals...\n");
}

/* ---------------- Command handler ---------------- */

void cmd_reboot(const char *args)
{
	int32_t ret;
	(void)args;

	printf("Reboot Manager Demo Start\n");

	/* ---------------- Simple reboot ---------------- */
	printf("Triggering cold reboot (no callback)...\n");

	// ret = reboot(REBOOT_COLD, NULL, NULL);
	// if (ret != 0) {
		// printf("Cold reboot failed (rc=%d)\n", ret);
	// }

	/* NOTE:
	 * If reboot succeeds, system will reset here
	 * Code below is only reached if reboot fails
	 */

	/* ---------------- Advanced reboot ---------------- */
	printf("Triggering warm reboot (with callback)...\n");

	ret = reboot(REBOOT_WARM, before_reboot, NULL);
	if (ret != 0) {
		printf("Warm reboot failed (rc=%d)\n", ret);
	}

	printf("Reboot Manager Example Done\n");
}

/* ---------------- CLI registration ---------------- */

void register_reboot_demo(void)
{
	cli_register_command("reboot_mngr_selftest", cmd_reboot);
}

APP_REGISTER(register_reboot_demo);

