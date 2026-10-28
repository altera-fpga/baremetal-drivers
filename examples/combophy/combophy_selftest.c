/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: combophy_selftest.c
 *
 * Combophy Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Combophy Example
 */

#include <stdint.h>
#include <stdio.h>
#include "combophy_api.h"
#include "console_api.h"
#include "example_register.h"
static void cmd_combophy_info(const char *args)
{
    uint32_t version = 0U;
    uint32_t features = 0U;
    int32_t ret;
    (void)args;
    ret = combophy_api_get_version(&version);
    if (ret == -ENOSYS) { printf("Combo PHY base is not defined for this platform build.\n"); return; }
    if (ret != 0) { printf("Combo PHY version read failed: %d\n", ret); return; }
    (void)combophy_api_get_features(&features);
    printf("Combo PHY version=0x%08X features=0x%08X\n", version, features);
}
static void register_combophy_commands(void)
{
    cli_register_command("combophy_selftest", cmd_combophy_info);
}
APP_REGISTER(register_combophy_commands)

