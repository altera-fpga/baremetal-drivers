/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: platform_def.h
 *
 * Agilex5 platform integration interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <stdint.h>

/* Platform umbrella includes: keep per-IP register definitions split by domain. */
#include "socfpga_peripheral_reg_plat.h"
#include "socfpga_gic_reg_plat.h"
#include "socfpga_rst_mngr_reg_plat.h"
#include "socfpga_dma_reg_plat.h"
#include "socfpga_bridge_reg_plat.h"

/* UART registers and pinmux addresses (Agilex5 silicon) */
#define ALT_UART_CSR_UART0_OFST     0x10C02000UL
#define ALT_HPS_UART_BASE           ALT_UART_CSR_UART0_OFST
/* System Manager pinmux block */
#define ALT_HPS_PINMUX_BASE         0x10D13000
/* Reset Manager PER1MODRST */
#define ALT_HPS_PER1MODRST_REG      0x10D11028

/* UART instance limit */
#define UART_MAX_INSTANCE 1

/* 100 MHz (L4_SP/UART clock target) */
#define HPS_PERIP_UART_CLK          100000000

/* UART registers */
extern volatile uint32_t *uart_rbr;
extern volatile uint32_t *uart_thr;
extern volatile uint32_t *uart_dll;
extern volatile uint32_t *uart_dlm;
extern volatile uint32_t *uart_ier;
extern volatile uint32_t *uart_fcr;
extern volatile uint32_t *uart_lcr;
extern volatile uint32_t *uart_mcr;
extern volatile uint32_t *uart_lsr;

/* Pinmux */
extern volatile uint32_t *pinmux_pin2sel;
extern volatile uint32_t *pinmux_pin3sel;
extern volatile uint32_t *pinmux_io2ctrl;
extern volatile uint32_t *pinmux_io3ctrl;
extern volatile uint32_t *pinmux_uart0_usefpga;
extern volatile uint32_t *per1modrst;

/* Agilex5 timer instance base addresses */
#define SPTIMER0_BASE_ADDR          0x10C03000U
#define SPTIMER1_BASE_ADDR          0x10C03100U
#define OSC1_TIMER0_BASE_ADDR       0x10D00000U
#define OSC1_TIMER1_BASE_ADDR       0x10D00100U

/* Function: platform_uart_init
 *
 * Queries the current Agilex5 state and reports the result to the caller.
 *
 * Parameters:
 *
 *    baudrate - UART baud rate.
 *    clock_freq - Clock frequency or frequency output value in hertz.
 *
 * Returns:
 *
 *    None.
 */
void platform_uart_init(uint32_t baudrate, uint32_t clock_freq);
/* Function: platform_print_info
 *
 * Performs a Agilex5 operation exposed by this layer.
 *
 * Returns:
 *
 *    None.
 */
void platform_print_info(void);
/* Function: platform_clk_init
 *
 * Initializes the Agilex5 block or software context for use.
 *
 * Returns:
 *
 *    None.
 */
void platform_clk_init(void);

/* Function: platform_pll_init
 *
 * Agilex5 PLL bring-up for the standalone OCRAM/FSBL boot, ported from ATF
 * BL2's config_clkmgr_handoff(). Consumes the bitstream HPS clock handoff and
 * locks the main + peripheral PLLs so the L4_SP/UART clock reaches its 100 MHz
 * target.
 *
 * Returns:
 *
 *    0 on success (both PLLs locked), -1 if the PLLs did not lock.
 */
int platform_pll_init(void);

/* Function: platform_get_l4sp_clk
 *
 * Computes the live L4_SP (UART) clock from the clock-manager divider chain,
 * mirroring ATF get_l4_sp_clk(). Yields the real 100 MHz once the PLLs are
 * locked, or the SDM boot clock otherwise.
 *
 * Returns:
 *
 *    The L4_SP clock frequency in Hz.
 */
uint32_t platform_get_l4sp_clk(void);

#endif /* PLATFORM_DEF_H */
