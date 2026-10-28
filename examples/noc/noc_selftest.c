/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: noc_selftest.c
 *
 * Noc Probe Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Noc Probe Example
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "console_api.h"
#include "example_register.h"
#include "noc_probe_api.h"

extern int32_t noc_fw_run_uart0(void);
extern int32_t noc_fw_run_probe(void);
extern int32_t noc_fw_run_i2c0(void);

static void noc_probe_print_base_error(int32_t ret)
{
    if (ret == -ENOSYS) {
        printf("NOC probe base is not defined for this platform build.\n");
    } else {
        printf("NOC probe access failed: %d\n", ret);
    }
}

static int32_t noc_probe_run_id(void)
{
    uint32_t core_id = 0U;
    int32_t ret;

    ret = noc_probe_api_read_id(&core_id);
    if (ret != 0) {
        noc_probe_print_base_error(ret);
        return ret;
    }

    printf("NOC probe core/id: 0x%08X\n", core_id);
    return 0;
}

static int32_t noc_probe_run_error_clear(void)
{
    int32_t ret;

    ret = noc_probe_api_error_clear();
    if (ret != 0) {
        noc_probe_print_base_error(ret);
        return ret;
    }

    printf("NOC error logger clear PASS\n");
    return 0;
}

static int32_t noc_probe_run_error(void)
{
    bool valid = false;
    int32_t ret;

    ret = noc_probe_api_error_logger_enable(true);
    if (ret != 0) {
        noc_probe_print_base_error(ret);
        return ret;
    }

    ret = noc_probe_api_error_is_valid(&valid);
    if (ret != 0) {
        noc_probe_print_base_error(ret);
        return ret;
    }

    printf("NOC error valid: %u\n", valid ? 1U : 0U);
    if (valid) {
        socfpga_noc_probe_error_log_t log;

        ret = noc_probe_api_error_read(&log);
        if (ret != 0) {
            noc_probe_print_base_error(ret);
            return ret;
        }

        printf("ERRLOG0: 0x%08X\n", log.errlog0);
        printf("ERRLOG1: 0x%08X\n", log.errlog1);
        printf("ERRLOG3: 0x%08X\n", log.errlog3);
        printf("ERRLOG4: 0x%08X\n", log.errlog4);
        printf("ERRLOG5: 0x%08X\n", log.errlog5);
        printf("ERRLOG6: 0x%08X\n", log.errlog6);
        printf("ERRLOG7: 0x%08X\n", log.errlog7);
    } else {
        printf("NOC probe is accessible; no captured error is currently latched.\n");
    }

    return 0;
}

static void cmd_noc_selftest(const char *args)
{
    uint32_t passed = 0U;
    uint32_t total = 6U;
    int32_t ret;
    (void)args;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  NOC SELF-TEST                             |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Test 1 of 6 : NOC FIREWALL UART0\n");
    printf("------------------------------------------------------------\n");
    ret = noc_fw_run_uart0();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    printf("Test 2 of 6 : NOC FIREWALL PROBE\n");
    printf("------------------------------------------------------------\n");
    ret = noc_fw_run_probe();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    printf("Test 3 of 6 : NOC FIREWALL I2C0\n");
    printf("------------------------------------------------------------\n");
    ret = noc_fw_run_i2c0();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    printf("Test 4 of 6 : NOC PROBE ID\n");
    printf("------------------------------------------------------------\n");
    ret = noc_probe_run_id();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    printf("Test 5 of 6 : NOC ERROR\n");
    printf("------------------------------------------------------------\n");
    ret = noc_probe_run_error();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    printf("Test 6 of 6 : NOC ERROR CLEAR\n");
    printf("------------------------------------------------------------\n");
    ret = noc_probe_run_error_clear();
    if (ret == 0) {
        printf("PASS\n");
        passed++;
    } else {
        printf("FAIL (ret=%d)\n", ret);
    }
    printf("\n");

    if (passed == total) {
        printf("RESULT : %u of %u tests passed  -  SELF-TEST PASSED\n", passed, total);
    } else {
        printf("RESULT : %u of %u tests passed  -  SELF-TEST FAILED\n", passed, total);
    }
    printf("\n");
}

static void register_noc_probe_commands(void)
{
    cli_register_command("noc_selftest", cmd_noc_selftest);
}

APP_REGISTER(register_noc_probe_commands)

