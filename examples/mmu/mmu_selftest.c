/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: mmu_selftest.c
 *
 * Mmu Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Mmu Example
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "console_api.h"
#include "example_register.h"
#include "mmu_api.h"

static void cmd_mmu_status(const char *args)
{
    uint32_t el = 1U;
    bool enabled = false;
    int32_t ret;

    if ((args != NULL) && (*args != '\0')) {
        el = parse_dec(args);
    }

    ret = mmu_api_is_enabled(el, &enabled);
    if (ret == -ENOSYS) {
        printf("MMU status requires AArch64 target build.\n");
        return;
    }
    if (ret != 0) {
        printf("MMU EL%u status failed: %d\n", el, ret);
        return;
    }
    printf("MMU EL%u: %s\n", el, enabled ? "enabled" : "disabled");
}

static void register_mmu_commands(void)
{
    cli_register_command("mmu_selftest", cmd_mmu_status);
}

APP_REGISTER(register_mmu_commands)

