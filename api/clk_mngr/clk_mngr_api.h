/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: clk_mngr_api.h
 *
 * Initialize the clock manager, query clock frequencies, and read or program
 * supported clock divisors.
 */

#ifndef CLK_MNGR_API_H
#define CLK_MNGR_API_H

#include <stdint.h>

/* Clock block identifiers used by clk_mngr_api_get_freq(). */
/* Constant: CLK_MNGR_BLOCK_MPU
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the MPU core clock.
 */
#define CLK_MNGR_BLOCK_MPU        0U  /**< MPU core clock */
/* Constant: CLK_MNGR_BLOCK_SDMMC
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the SD/MMC clock.
 */
#define CLK_MNGR_BLOCK_SDMMC      1U  /**< SDMMC clock */
/* Constant: CLK_MNGR_BLOCK_SP_TIMER
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the peripheral timer clock.
 */
#define CLK_MNGR_BLOCK_SP_TIMER   3U  /**< Peripheral timer clock */
/* Constant: CLK_MNGR_BLOCK_OSC1TIMER
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the OSC1 timer clock.
 */
#define CLK_MNGR_BLOCK_OSC1TIMER  4U  /**< OSC1 timer clock */
/* Constant: CLK_MNGR_BLOCK_SSPI
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the SPI clock.
 */
#define CLK_MNGR_BLOCK_SSPI       5U  /**< SPI clock */
/* Constant: CLK_MNGR_BLOCK_L4MAIN
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the L4 Main clock.
 */
#define CLK_MNGR_BLOCK_L4MAIN     6U  /**< L4 Main clock */
/* Constant: CLK_MNGR_BLOCK_UART
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the UART clock.
 */
#define CLK_MNGR_BLOCK_UART       7U  /**< UART clock */
/* Constant: CLK_MNGR_BLOCK_WDT
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the watchdog timer clock.
 */
#define CLK_MNGR_BLOCK_WDT        8U  /**< Watchdog timer clock */
/* Constant: CLK_MNGR_BLOCK_I2C
 * Clock-block identifier passed to clk_mngr_api_get_freq() for the I2C clock.
 */
#define CLK_MNGR_BLOCK_I2C        9U  /**< I2C clock */

/* Divisor identifiers used by clk_mngr_api_set_divisor()/get_divisor(). */
/* Constant: CLK_MNGR_DIV_L4_SYS_FREE
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for L4_SYS_FREE_CLK.
 */
#define CLK_MNGR_DIV_L4_SYS_FREE  0U  /**< L4_SYS_FREE_CLK divisor */
/* Constant: CLK_MNGR_DIV_L4_MP
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for L4_MP_CLK.
 */
#define CLK_MNGR_DIV_L4_MP        1U  /**< L4_MP_CLK divisor */
/* Constant: CLK_MNGR_DIV_L4_SP
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for L4_SP_CLK.
 */
#define CLK_MNGR_DIV_L4_SP        2U  /**< L4_SP_CLK divisor */
/* Constant: CLK_MNGR_DIV_SOFT_PHY
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for SOFT_PHY_CLK.
 */
#define CLK_MNGR_DIV_SOFT_PHY     3U  /**< SOFT_PHY_CLK divisor */
/* Constant: CLK_MNGR_DIV_CCU
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for CCU_CLK.
 */
#define CLK_MNGR_DIV_CCU          4U  /**< CCU_CLK divisor */
/* Constant: CLK_MNGR_DIV_MPU_PERIPH
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for MPU_PERIPH_CLK.
 */
#define CLK_MNGR_DIV_MPU_PERIPH   5U  /**< MPU_PERIPH_CLK divisor */
/* Constant: CLK_MNGR_DIV_CS
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for CS_CLK.
 */
#define CLK_MNGR_DIV_CS           6U  /**< CS_CLK divisor */
/* Constant: CLK_MNGR_DIV_CS_TRACE
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for CS_TRACE_CLK.
 */
#define CLK_MNGR_DIV_CS_TRACE     7U  /**< CS_TRACE_CLK divisor */
/* Constant: CLK_MNGR_DIV_CS_PDBG
 * Divisor selector used by clk_mngr_api_set_divisor() and clk_mngr_api_get_divisor() for CS_PDBG_CLK.
 */
#define CLK_MNGR_DIV_CS_PDBG      8U  /**< CS_PDBG_CLK divisor */

/* Function: clk_mngr_api_init
 *
 * Initializes the platform Clock Manager settings used by this bare-metal build.
 * Call this during platform bring-up before querying clock frequencies or
 * changing NOCDIV divisors.
 *
 * Returns:
 *
 *    0 on success; otherwise returns the status from clk_mngr_platform_init().
 *    Current platform implementations can return -ETIMEDOUT while waiting for
 *    clock-manager state changes.
 */
int clk_mngr_api_init(void);

/* Function: clk_mngr_api_get_freq
 *
 * Returns the current frequency of one supported clock block.
 *
 * Parameters:
 *
 *    clock_block_id - One of the CLK_MNGR_BLOCK_* identifiers.
 *    freq_hz - Output location for the frequency in hertz.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if freq_hz is NULL or clock_block_id is not supported;
 *    otherwise returns the status from clk_mngr_ll_get_clk().
 */
int clk_mngr_api_get_freq(uint32_t clock_block_id, uint32_t *freq_hz);

/* Function: clk_mngr_api_set_divisor
 *
 * Programs one NOCDIV control-clock divisor.
 *
 * Parameters:
 *
 *    clock_type - One of the CLK_MNGR_DIV_* identifiers.
 *    divisor - Divisor to program. Supported values are 1, 2, or 4; the CS
 *    divider types also support 8.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when the clock type or divisor is not supported.
 */
int clk_mngr_api_set_divisor(uint32_t clock_type, uint8_t divisor);

/* Function: clk_mngr_api_get_divisor
 *
 * Reads the currently programmed NOCDIV divisor for one control clock.
 *
 * Parameters:
 *
 *    clock_type - One of the CLK_MNGR_DIV_* identifiers.
 *    divisor - Output location for the current divisor.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for a NULL output pointer or an unsupported clock
 *    type.
 */
int clk_mngr_api_get_divisor(uint32_t clock_type, uint8_t *divisor);

/* Function: clk_mngr_platform_init
 *
 * Platform integration hook used by clk_mngr_api_init(). Applications normally
 * call clk_mngr_api_init() rather than this function directly.
 *
 * Returns:
 *
 *    0 on success; -ETIMEDOUT where the selected platform implementation times
 *    out while waiting for a clock-manager state transition; otherwise returns
 *    that platform implementation's status.
 */
int clk_mngr_platform_init(void);

#endif /* CLK_MNGR_API_H */
