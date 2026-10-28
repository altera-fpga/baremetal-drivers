/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: noc_firewall_selftest.c
 *
 * Noc Firewall Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Noc Firewall Example
 */

#include <stdint.h>
#include <stdio.h>
#include "console_api.h"
#include "example_register.h"
#include "noc_firewall_api.h"

static void noc_fw_print_result(const char *name, int32_t ret)
{
    if (ret == -ENOSYS) {
        printf("NOC firewall base is not defined for this platform build.\n");
        return;
    }
    if (ret != 0) {
        printf("NOC firewall %s failed: %d\n", name, ret);
        return;
    }
    printf("NOC firewall %s PASS\n", name);
}

int32_t noc_fw_run_uart0(void)
{
    int32_t ret;

    /*
     * U-Boot programs firewall SCRs using write-only writel() operations.  Do
     * not read these registers back in bare-metal because some firewall
     * apertures can stall on reads depending on security/clock state.
     */
    ret = noc_firewall_api_allow_nonsecure(SOCFPGA_NOC_FW_UART0);
    noc_fw_print_result("UART0 allow-nonsecure", ret);
    return ret;
}

int32_t noc_fw_run_probe(void)
{
    int32_t ret;

    ret = noc_firewall_api_allow_nonsecure(SOCFPGA_NOC_FW_L4_NOC_PROBES);
    noc_fw_print_result("NOC probe allow-nonsecure", ret);
    return ret;
}

int32_t noc_fw_run_i2c0(void)
{
    int32_t ret;

    /*
     * U-Boot-style flow: write-only firewall programming.
     * Do not read back the I2C0 firewall SCR in bare-metal because some
     * firewall apertures can stall on reads depending on security/clock state.
     *
     * This command only opens I2C0 for non-secure access. It does not touch
     * the I2C controller registers and does not intentionally create a
     * firewall violation.
     */
    ret = noc_firewall_api_allow_nonsecure(SOCFPGA_NOC_FW_I2C0);
    noc_fw_print_result("I2C0 allow-nonsecure", ret);
    return ret;
}

static void register_noc_fw_commands(void)
{
    /* NOC self-test command is owned by noc_selftest.c. */
}

APP_REGISTER(register_noc_fw_commands)

