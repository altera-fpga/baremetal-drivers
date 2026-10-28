/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: smmu_selftest.c
 *
 * Smmu Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Smmu Example
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "console_api.h"
#include "example_register.h"
#include "smmu_api.h"

static void cmd_smmu_status(const char *args)
{
    bool enabled = false;
    int32_t ret;

    (void)args;

    ret = smmu_api_is_enabled(&enabled);
    if (ret != 0) {
        printf("SMMU status failed: %d\n", ret);
        return;
    }

    printf("SMMU: %s\n", enabled ? "enabled" : "disabled");
}

static void register_smmu_commands(void)
{
    cli_register_command("smmu_selftest", cmd_smmu_status);
}

APP_REGISTER(register_smmu_commands)

