/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_clk_mngr_ll.h
 *
 * Low-level clock manager interface. It reads clock rates and gets or
 * sets clock dividers.
 */

#ifndef __SOCFPGA_CLK_MNGR_LL_H__
#define __SOCFPGA_CLK_MNGR_LL_H__

#include "mmio.h"

/* Constants: Clock type identifiers
 *
 * Values passed as the clock type to the divisor get and set calls.
 *
 * L4_SYS_FREE_CLK - L4 system free clock.
 * L4_MP_CLK       - L4 MP clock.
 * L4_SP_CLK       - L4 SP clock.
 * SOFT_PHY_DIV    - Soft PHY clock.
 * CCU_DIV         - CCU clock.
 * MPU_PERIPH_DIV  - MPU peripheral clock.
 * CS_CLK          - CS clock.
 * CS_TRACE_CLK    - CS trace clock.
 * CS_PDBG_CLK     - CS PDBG clock.
 */
#define L4_SYS_FREE_CLK    0U
#define L4_MP_CLK          1U
#define L4_SP_CLK          2U
#define SOFT_PHY_DIV       3U
#define CCU_DIV            4U
#define MPU_PERIPH_DIV     5U
#define CS_CLK             6U
#define CS_TRACE_CLK       7U
#define CS_PDBG_CLK        8U

/* Constants: PLL clock sources
 *
 * Values compared with the clock source field. A match selects which
 * PLL the driver reads.
 *
 * MAIN_PLL_CLK_SRC - Main PLL.
 * PERI_PLL_CLK_SRC - Peripheral PLL.
 * OSC1_CLK_SRC     - OSC1 clock source.
 * INTOSC_CLK_SRC   - Internal oscillator clock source.
 * FPGA_CLK_SRC     - FPGA clock source.
 * INVALID_CLK_SRC  - Clock source is not valid.
 */
#define MAIN_PLL_CLK_SRC   0U
#define PERI_PLL_CLK_SRC   1U
#define OSC1_CLK_SRC       3U
#define INTOSC_CLK_SRC     4U
#define FPGA_CLK_SRC       5U
#define INVALID_CLK_SRC    6U

/* Constants: VCO clock sources
 *
 * Values of the PLL source field. The driver uses them to pick the
 * reference clock.
 *
 * PSRC_EOSC1_CLK    - EOSC1 clock. Read from boot scratch. If that
 *                     read is 0, the driver uses 25000000 Hz.
 * PSRC_CBINTOSC_CLK - Internal oscillator. The rate is
 *                     CLKMGR_INTOSC_CLOCK_RATE_HZ.
 * PSRC_F2S_FREE_CLK - F2S free clock. Read from boot scratch.
 */
#define PSRC_EOSC1_CLK     0U
#define PSRC_CBINTOSC_CLK  1U
#define PSRC_F2S_FREE_CLK  2U

/* Constants: Clock rate constants
 *
 * Fixed numbers used while a clock rate is computed.
 *
 * CLKMGR_INTOSC_CLOCK_RATE_HZ - Internal oscillator frequency, in Hz.
 * QSPI_CLOCK_MULTIPLIER             - Scale factor applied to the QSPI
 *                                     clock read from boot scratch.
 */
#define CLKMGR_INTOSC_CLOCK_RATE_HZ    460000000U /* Internal oscillator frequency in Hz */
#define QSPI_CLOCK_MULTIPLIER          1000U      /* Multiplier factor for QSPI source calculation */


/* Enum: clock_block_t
 *
 * Enumerates the supported peripheral hardware blocks managed by the 
 * Clock Manager.
 */
typedef enum
{
    CLOCK_MPU     = 0, /* MPU subsystem clock */
    CLOCK_SDMMC,       /* SDMMC controller clock */
    CLOCK_QSPI,        /* QSPI controller clock */
    CLOCK_SP_TIMER,    /* Peripheral Timer clock */
    CLOCK_OSC1TIMER,   /* OSC1 Timer clock */
    CLOCK_SSPI,        /* SPI controller clock */
    CLOCK_L4MAIN,      /* L4 Main bus clock */
    CLOCK_UART,        /* UART controller clock */
    CLOCK_WDT,         /* Watchdog Timer clock */
    CLOCK_I2C,         /* I2C controller clock */
    CLOCK_INVALID      /* Invalid or unsupported clock block */
} clock_block_t;


/* Function: clk_mngr_ll_get_clk
 *
 * Resolves and calculates the operating frequency for a specified clock block.
 *
 * Parameters:
 *
 * clock_block_name - The peripheral clock block ID (<clock_block_t>).
 * pclock_rate      - Pointer to store the calculated frequency in Hertz.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the block identifier is invalid.
 */
int32_t clk_mngr_ll_get_clk(clock_block_t clock_block_name, uint32_t *pclock_rate);

/* Function: clk_mngr_ll_set_divisor
 *
 * Programs the hardware divider register for a specific clock control type.
 *
 * Parameters:
 *
 * clock_type - The control clock type identifier.
 * divisor    - The divisor value to write to the hardware register.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the clock type is invalid.
 */
int32_t clk_mngr_ll_set_divisor(uint32_t clock_type, uint8_t divisor);

/* Function: clk_mngr_ll_get_divisor
 *
 * Retrieves the currently programmed divisor value for a given clock type.
 *
 * Parameters:
 *
 * clock_type - The control clock type identifier.
 * divisor    - Pointer to store the retrieved divisor value.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the clock type is invalid.
 */
int32_t clk_mngr_ll_get_divisor(uint32_t clock_type, uint8_t *divisor);

#endif /* __SOCFPGA_CLK_MNGR_LL_H__ */