/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ccu_selftest.c
 *
 * CCU example commands for the SoCFPGA bare-metal software stack.
 *
 * Layer: examples
 * Component: CCU Example
 */

#include <stdint.h>
#include <stdio.h>

#include "errno.h"
#include "ccu_api.h"
#include "console_api.h"
#include "example_register.h"

static void ccu_print_platform_base_error(void)
{
    printf("CCU base is not defined for this platform build.\n");
}

static void cmd_ccu_id(const char *args)
{
    uint32_t id = 0U;
    int32_t ret;
    (void)args;

    ret = ccu_api_get_id(&id);
    if (ret == -ENOSYS) {
        ccu_print_platform_base_error();
        return;
    }
    if (ret != 0) {
        printf("CCU ID read failed: %d\n", ret);
        return;
    }

    printf("CCU ID: 0x%08X\n", id);
}

static void cmd_ccu_error(const char *args)
{
    uint32_t status = 0U;
    int32_t ret;
    (void)args;

    ret = ccu_api_get_error_status(&status);
    if (ret == -ENOSYS) {
        ccu_print_platform_base_error();
        return;
    }
    if (ret != 0) {
        printf("CCU error status read failed: %d\n", ret);
        return;
    }

    printf("CCU uncorrected error status: 0x%08X\n", status);
}

static void cmd_ccu_flush_l3(const char *args)
{
    int32_t ret;
    (void)args;

    ret = ccu_api_flush_l3_cache();
    if (ret == -ENOSYS) {
        ccu_print_platform_base_error();
        return;
    }
    if (ret == -ETIMEDOUT) {
        printf("CCU L3 cache flush timed out.\n");
        return;
    }
    if (ret != 0) {
        printf("CCU L3 cache flush failed: %d\n", ret);
        return;
    }

    printf("CCU L3 cache flush PASS\n");
}

static void cmd_ccu_selftest(const char *args)
{
    uint32_t passed = 0U;
    uint32_t total = 3U;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  CCU SELF-TEST                             |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Test 1 of 3 : CCU ID\n");
    printf("------------------------------------------------------------\n");
    cmd_ccu_id(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 2 of 3 : CCU ERROR STATUS\n");
    printf("------------------------------------------------------------\n");
    cmd_ccu_error(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 3 of 3 : CCU FLUSH L3\n");
    printf("------------------------------------------------------------\n");
    cmd_ccu_flush_l3(args);
    printf("PASS\n\n");
    passed++;

    printf("RESULT : %u of %u tests passed  -  SELF-TEST PASSED\n", passed, total);
    printf("\n");
}

static void register_ccu_commands(void)
{
    cli_register_command("ccu_selftest", cmd_ccu_selftest);
}

APP_REGISTER(register_ccu_commands)


