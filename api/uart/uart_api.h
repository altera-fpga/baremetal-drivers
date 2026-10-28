/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: uart_api.h
 *
 * Initialize one UART instance and provide polling character transmit, receive,
 * and initialization-state helpers.
 */

#ifndef __UART_API_H__
#define __UART_API_H__

#include <stdint.h>
#include <stdbool.h>
#include "errno.h"

/* Function: uart_init
 *
 * Initializes one UART instance for the bare-metal console path.
 *
 * Agilex5 and Agilex3 OCRAM builds configure the port using baudrate and
 * clock_freq. DDR builds retain the earlier firmware's UART configuration;
 * both arguments are ignored by those platform initialization hooks.
 *
 * Parameters:
 *
 *    instance - UART instance index. The value must be smaller than
 *    UART_MAX_INSTANCE for the selected platform.
 *    baudrate - Requested UART baud rate.
 *    clock_freq - UART input clock frequency in hertz.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when the instance index is out of range.
 */
int uart_init(uint32_t instance, uint32_t baudrate, uint32_t clock_freq);

/* Function: uart_deinit
 *
 * Disables the active console UART and clears the API's initialized state.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if the UART API is not initialized.
 */
int32_t uart_deinit(void);

/* Function: uart_is_initialized
 *
 * Reports whether the UART API has been initialized.
 *
 * Returns:
 *
 *    true after a successful uart_init(); false otherwise.
 */
bool uart_is_initialized(void);

/* Function: uart_putc
 *
 * Writes one character to the active console UART. If the UART API is not
 * initialized, the call returns without transmitting data. Otherwise it waits
 * for transmit FIFO space; there is no timeout. A newline is sent as CRLF.
 *
 * Parameters:
 *
 *    c - Character to transmit.
 */
void uart_putc(char c);

/* Function: uart_getc
 *
 * Reads one character from the active console UART. If the UART API is not
 * initialized, the function returns the NUL character ('\0'). After
 * initialization, it polls until a byte arrives and can block indefinitely.
 * There is no receive timeout or 'no byte available' return. Check
 * uart_is_initialized() before using a returned NUL as received data.
 *
 * Returns:
 *
 *    The received character, or '\0' when the UART API is not initialized.
 */
char uart_getc(void);

/* Function: printf
 *
 * Formats text with the repository's lightweight printf implementation and
 * sends it to the active console UART.
 *
 * Parameters:
 *
 *    fmt - Format string.
 *    ... - Values referenced by the format string.
 *
 * Returns:
 *
 *    The character count produced by the lightweight formatter, even if the
 *    UART is uninitialized and drops the output. This is not an errno status
 *    or confirmation of delivery to the terminal.
 */
int printf(const char *fmt, ...);

#endif /* __UART_API_H__ */
