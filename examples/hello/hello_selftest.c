/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: hello_selftest.c
 *
 * Hello World source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Hello World
 */

#include <stdio.h>
#include "../api/console/console_api.h"
#include "example_register.h"

// The actual command function
void cmd_hello_world(const char *args) {
	(void)args; // unused
	printf("Hello, Baremetal World!\n");
}

void register_hello_world(void) {
	cli_register_command("hello_selftest", cmd_hello_world);
}

// Auto-register into special section
APP_REGISTER(register_hello_world)

