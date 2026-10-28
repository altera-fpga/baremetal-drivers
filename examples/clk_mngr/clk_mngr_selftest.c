/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: clk_mngr_selftest.c
 *
 * Clk Mngr Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Clk Mngr Example
 */

#include <stdint.h>
#include <stdio.h>
#include "../api/console/console_api.h"
#include "../api/clk_mngr/clk_mngr_api.h"
#include "example_register.h"

static void print_clk_freq(const char *label, uint32_t clk_id)
{
    uint32_t rate = 0U;
    int rc = clk_mngr_api_get_freq(clk_id, &rate);

    if (rc != 0)
        printf("    %s: FAIL (rc=%d)\n", label, rc);
    else
        printf("    %s: %u Hz\n", label, rate);
}

static void print_divisor(const char *label, uint32_t clock_type)
{
    uint8_t div = 0U;
    int rc = clk_mngr_api_get_divisor(clock_type, &div);

    if (rc != 0)
        printf("    %s: error (rc=%d)\n", label, rc);
    else if (div == 0U)
        printf("    %s: disabled\n", label);
    else
        printf("    %s: div=%u\n", label, div);
}

void cmd_clk_mngr(const char *args)
{
    (void)args;

    printf("Clock Manager Example\n");

    /* --- Step 1: show current divisors (as left by ATF / Simics reset) --- */
    printf("  [NOCDIV before init]\n");
    print_divisor("L4_SYS_FREE ", CLK_MNGR_DIV_L4_SYS_FREE);
    print_divisor("L4_MP       ", CLK_MNGR_DIV_L4_MP);
    print_divisor("L4_SP       ", CLK_MNGR_DIV_L4_SP);
    print_divisor("SOFT_PHY    ", CLK_MNGR_DIV_SOFT_PHY);
    print_divisor("CCU         ", CLK_MNGR_DIV_CCU);
    print_divisor("MPU_PERIPH  ", CLK_MNGR_DIV_MPU_PERIPH);
    print_divisor("CS_CLK      ", CLK_MNGR_DIV_CS);
    print_divisor("CS_TRACE    ", CLK_MNGR_DIV_CS_TRACE);
    print_divisor("CS_PDBG     ", CLK_MNGR_DIV_CS_PDBG);

    /* --- Step 2: apply platform default configuration --- */
    printf("  [clk_mngr_api_init]\n");
    int rc = clk_mngr_api_init();
    printf("    init: %s\n", (rc == 0) ? "OK" : "FAILED");

    /* --- Step 3: confirm divisors after init --- */
    printf("  [NOCDIV after init]\n");
    print_divisor("L4_SYS_FREE ", CLK_MNGR_DIV_L4_SYS_FREE);
    print_divisor("L4_MP       ", CLK_MNGR_DIV_L4_MP);
    print_divisor("L4_SP       ", CLK_MNGR_DIV_L4_SP);
    print_divisor("SOFT_PHY    ", CLK_MNGR_DIV_SOFT_PHY);
    print_divisor("CCU         ", CLK_MNGR_DIV_CCU);
    print_divisor("MPU_PERIPH  ", CLK_MNGR_DIV_MPU_PERIPH);
    print_divisor("CS_CLK      ", CLK_MNGR_DIV_CS);
    print_divisor("CS_TRACE    ", CLK_MNGR_DIV_CS_TRACE);
    print_divisor("CS_PDBG     ", CLK_MNGR_DIV_CS_PDBG);

    /* --- Step 4: set_divisor input validation --- */
    printf("  [set_divisor validation]\n");
    rc = clk_mngr_api_set_divisor(CLK_MNGR_DIV_L4_SP, 4U);
    printf("    L4_SP div=4 (valid)   : %s\n", (rc == 0) ? "OK" : "ERR");

    rc = clk_mngr_api_set_divisor(CLK_MNGR_DIV_L4_SP, 99U);
    printf("    L4_SP div=99 (invalid): %s\n", (rc != 0) ? "OK" : "ERR");

    /* --- Step 5: get_clk frequency check -----------*/
    printf("  [get_clk frequency]\n");
    printf("    (HW: actual PLL-derived values)\n");
    print_clk_freq("UART       ", CLK_MNGR_BLOCK_UART);
    print_clk_freq("WDT        ", CLK_MNGR_BLOCK_WDT);
    print_clk_freq("I2C        ", CLK_MNGR_BLOCK_I2C);
    print_clk_freq("SP_TIMER   ", CLK_MNGR_BLOCK_SP_TIMER);
    print_clk_freq("OSC1TIMER  ", CLK_MNGR_BLOCK_OSC1TIMER);
    print_clk_freq("SDMMC      ", CLK_MNGR_BLOCK_SDMMC);
    print_clk_freq("MPU        ", CLK_MNGR_BLOCK_MPU);
    print_clk_freq("SSPI       ", CLK_MNGR_BLOCK_SSPI);
    print_clk_freq("L4MAIN     ", CLK_MNGR_BLOCK_L4MAIN);

    printf("Clock Manager Example Done\n");
}

void register_clk_mngr(void)
{
    cli_register_command("clk_mngr_selftest", cmd_clk_mngr);
}

APP_REGISTER(register_clk_mngr)

