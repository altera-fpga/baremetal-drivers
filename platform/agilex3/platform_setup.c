/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: platform_setup.c
 *
 * Agilex3 source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: platform
 * Component: Agilex3
 */

#include "../include/crt0.h"
#include "../api/console/command.h"
#include "../api/uart/uart_api.h"
#include "../api/clk_mngr/clk_mngr_api.h"
#include "platform_def.h"

#ifndef GIT_COMMIT_ID
#define GIT_COMMIT_ID "unknown"
#endif

__attribute__((used))
const char git_commit_id[] = GIT_COMMIT_ID;

/* Map registers */
volatile uint32_t *pinmux_pin2sel = (volatile uint32_t *)(ALT_HPS_PINMUX_BASE + 0x08);
volatile uint32_t *pinmux_pin3sel = (volatile uint32_t *)(ALT_HPS_PINMUX_BASE + 0x0C);
volatile uint32_t *pinmux_io2ctrl = (volatile uint32_t *)(ALT_HPS_PINMUX_BASE + 0x138);
volatile uint32_t *pinmux_io3ctrl = (volatile uint32_t *)(ALT_HPS_PINMUX_BASE + 0x13C);
volatile uint32_t *pinmux_uart0_usefpga = (volatile uint32_t *)(ALT_HPS_PINMUX_BASE + 0x338);
volatile uint32_t *per1modrst = (volatile uint32_t *)(ALT_HPS_PER1MODRST_REG);

volatile uint32_t *uart_rbr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x00);
volatile uint32_t *uart_thr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x00);
volatile uint32_t *uart_dll = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x00);
volatile uint32_t *uart_dlm = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x04);
volatile uint32_t *uart_ier = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x04);
volatile uint32_t *uart_fcr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x08);
volatile uint32_t *uart_lcr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x0C);
volatile uint32_t *uart_mcr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x10);
volatile uint32_t *uart_lsr = (volatile uint32_t *)(ALT_HPS_UART_BASE + 0x14);

/* Initializes Agilex3 platform clocks. */
void platform_clk_init(void)
{
    int rc = clk_mngr_api_init();
    if (rc != 0)
    {
        printf("Platform clock init failed (rc=%d)\n", rc);
    }
}

void platform_print_info(void)
{
    printf("Welcome to SoCFPGA Baremetal World for Agilex3 Platform\n");
    printf("Built: %s %s\n", __TIME__, __DATE__);
    printf("Commit: %s\n", git_commit_id);
    printf("Running on Core %u\n", (uint32_t)((read_mpidr_el1() >> 8) & 0xFFU));
    printf("Type 'help' for commands.\n");
}

/* Platform-specific UART init */
void platform_uart_init(uint32_t baudrate, uint32_t clock_freq)
{
#if defined(PLAT_AGILEX3) && defined(BUILD_MODE_OCRAM)
    /*
     * Standalone OCRAM boot on Agilex3 silicon: no prior boot stage has
     * configured the console, so bring UART0 up from scratch (pinmux,
     * reset de-assert, line config, baud divisor).
     *
     * In DDR mode the app is loaded by ATF/U-Boot which already set up the
     * UART/pinmux/clocks, so this re-init is intentionally skipped there.
     */
    if (baudrate == 0U) {
        return;
    }

    uint32_t divisor = clock_freq / (16U * baudrate);
    if (divisor == 0U) {
        divisor = 1U;
    }

    /* Pinmux configuration: route UART0 TX/RX to HPS dedicated I/O. */
    *pinmux_pin2sel = 0x5;
    *pinmux_pin3sel = 0x5;
    *pinmux_io2ctrl = 0x36;
    *pinmux_uart0_usefpga = 0x00;

    /* Reset de-assertion for UART0. */
    *per1modrst = 0xfffeffff;

    /* UART register initialization. */
    *uart_ier = 0x0;
    dsb();
    *uart_mcr = 0x3;
    dsb();
    *uart_fcr = 0x7;
    dsb();
    *uart_lcr = 0x3;
    dsb();
    *uart_lcr = 0x83;
    dsb();
    *uart_dll = divisor;
    *uart_dlm = 0x0;
    *uart_lcr = 0x03;
    dsb();
#else
    (void)baudrate;
    (void)clock_freq;
#endif
}
