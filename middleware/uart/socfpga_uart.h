/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT
 */

/* File: socfpga_uart.h
 *
 * UART middleware service interface for the SoCFPGA bare-metal software stack.
 *
 */

/*
 * Common IO - basic V1.0.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * Modified function names and other definitions for SoC FPGA
 */

#ifndef __SOCFPGA_UART_H__
#define __SOCFPGA_UART_H__

/*
 * File: socfpga_uart.h
 * SoC FPGA UART HAL driver
 */

#include "mmio.h"

/*
 * uart UART
 * APIs for SoC FPGA UART driver.
 * Details: This is the UART driver implementation for SoC FPGA.
 * It provides APIs for reading and writing data over UART
 * in synchronous and asynchronous modes. Basic configuration includes
 * baud rate, parity, stop bits, and word length. For example usage,
 * see uart_sample "UART sample application".
 * 
 */

/*
 * uart_fns Functions
 * UART HAL APIs
 */

/*
 * uart_structs Structures
 * UART Specific Structures
 */

/*
 * uart_enums Enumerations
 * UART Specific Enumerations
 */

/*
 * uart_macros Macros
 * UART Specific Macros
 */

/*
 * uart_macros
 * 
 */

/*
 * The default baud rate for a given UART port.
 */
#define UART_BAUD_RATE_DEFAULT    (115200U)

/*
 * 
 */
/* end of group uart_macros */

/*
 * UART read/write operation status values
 */
/* Enum: uart_op_status_t
 *
 * Enumerates UART options, states, commands, or status values.
 *
 * Values:
 *
 *    UART_WR_DONE - uart wr done value.
 *    UART_RD_DONE - uart rd done value.
 *    UART_LAST_WR_FAILED - uart last wr failed value.
 *    UART_LAST_RD_FAILED - uart last rd failed value.
 */
typedef enum
{
    UART_WR_DONE, /*!< write completed successfully. */
    UART_RD_DONE, /*!< read completed successfully. */
    UART_LAST_WR_FAILED, /*!< error while performing write operation. */
    UART_LAST_RD_FAILED, /*!< error while performing read operation. */
} uart_op_status_t;

/*
 * UART parity mode
 */
/* Enum: uart_partity_t
 *
 * Enumerates UART options, states, commands, or status values.
 *
 * Values:
 *
 *    UART_PARITY_NONE - uart parity none value.
 *    UART_PARITY_ODD - uart parity odd value.
 *    UART_PARITY_EVEN - uart parity even value.
 */
typedef enum
{
    UART_PARITY_NONE, /*!< No parity. */
    UART_PARITY_ODD, /*!< Odd parity. */
    UART_PARITY_EVEN, /*!< Even parity. */
} uart_partity_t;

/*
 * UART stop bits
 */
/* Enum: uart_stop_bits_t
 *
 * Enumerates UART options, states, commands, or status values.
 *
 * Values:
 *
 *    UART_STOP_BITS_1 - uart stop bits 1 value.
 *    UART_STOP_BITS_2 - uart stop bits 2 value.
 */
typedef enum
{
    UART_STOP_BITS_1, /*!< One stop bit. */
    UART_STOP_BITS_2, /*!< Two stop bits. */
} uart_stop_bits_t;

/*
 * The callback function for completion of UART operation.
 *
 * status - UART asynchronous operation status.
 * param - User Context passed when setting the callback.
 * This is not used or modified by the driver. The context
 * is provided by the caller when setting the callback, and is
 * passed back to the caller in the callback.
 */
/* Callback: uart_callback_t
 *
 * Callback signature used by the UART module.
 *
 * Parameters:
 *
 *    See the typedef prototype for callback argument order and meaning.
 */
typedef void (*uart_callback_t)(uart_op_status_t status, void *param);

/*
 * The UART descriptor type defined in the source file.
 */
struct uart_descriptor;

/*
 * uart_handle_t is the handle type returned by calling uart_open().
 * This is initialized in open and returned to caller. The caller must pass
 * this pointer to the rest of APIs.
 */
/* Type: uart_handle_t
 *
 * Opaque UART handle type used to preserve module state between calls.
 */
typedef struct uart_descriptor *uart_handle_t;

/*
 * uart_structs
 * 
 */
/*
 * Configuration parameters for the UART.
 *
 * The application will send the user configuration in the form of the
 * following structure in ioctl.
 *
 */
/* Struct: uart_config_t
 *
 * Describes UART configuration, state, or transfer information.
 */
typedef struct
{
    uint32_t baud; /*!< Desired baud rate. */
    uart_partity_t parity; /*!< Desired parity option. Defined in uart_partity_t. */
    uart_stop_bits_t stop_bits; /*!< Desired stop bits options. Defined in uart_stop_bits_t. */
    uint32_t wlen; /*!< Desired word length. Valid values are from 5 to 8 */
} uart_config_t;

/*
 * 
 */
/* end of group uart_structs */


/*
 * Starts receiving the data from UART synchronously.
 *
 * This function attempts to read certain number of bytes from transmitter device to a pre-allocated buffer, in synchronous way.
 * Partial read might happen.
 * And the number of bytes that have been actually read can be obtained by calling uart_ioctl.
 *
 * Note: If the number of bytes is not known, it is recommended that the application reads one byte at a time.
 *
 * huart - The peripheral handle returned in the open() call.
 * buf - The buffer to store the received data. Allocated by the caller.
 * nbytes - The number of bytes to read.
 *
 * Returns: * - UART_SUCCESS: on success (all the requested bytes have been read)
 * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 *     - pucBuffer is NULL
 *     - nbytes is 0
 * - -EIO:    if there is unknown driver error
 * - -EBUSY:  if another read is in progress.
 */
/* Function: uart_mw_read_sync
 *
 * Reads UART state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *    buf - Caller-provided data buffer.
 *    nbytes - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_read_sync(uart_handle_t const huart, uint8_t *const buf,
        uint32_t nbytes);

/*
 * Starts the transmission of data from UART synchronously.
 *
 * This function attempts to write certain number of bytes from a pre-allocated buffer to a receiver device, in synchronous way.
 * Partial write might happen.
 * And the number of bytes that have been actually written can be obtained by calling uart_ioctl.
 *
 * huart - The peripheral handle returned in the open() call.
 * buf - The buffer with data to transmit.
 * nbytes - The number of bytes to send.
 *
 * Returns: * - UART_SUCCESS: on success (all the requested bytes have been written)
 * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 *     - pucBuffer is NULL
 *     - nbytes is 0
 * - -EIO:    if there is unknown driver error
 * - -EBUSY:  if another write is in progress
 */
/* Function: uart_mw_write_sync
 *
 * Writes or configures UART state, data, or register content.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *    buf - Caller-provided data buffer.
 *    nbytes - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_write_sync(uart_handle_t const huart, uint8_t *const buf,
        uint32_t nbytes);

/*
 * Starts receiving the data from UART asynchronously.
 *
 * This function attempts to read certain number of bytes from a pre-allocated buffer, in asynchronous way.
 * It returns immediately when the operation is started and the status can be checked by calling uart_ioctl.
 * Once the operation completes, successful or not, the user callback will be invoked.
 *
 * Partial read might happen.
 * And the number of bytes that have been actually read can be obtained by calling uart_ioctl.
 *
 * Note: In order to get notification when the asynchronous call is completed, uart_set_callback must be called prior to this.
 * Warning: pucBuffer must be valid before callback is invoked.
 *
 * huart - The peripheral handle returned in the open() call.
 * buf - The buffer to store the received data.
 * nbytes - The number of bytes to read.
 *
 * Returns: * - UART_SUCCESS: on success
 * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 *     - pucBuffer is NULL
 *     - nbytes is 0
 * - -EIO:    if there is unknown driver error
 */
/* Function: uart_mw_read_async
 *
 * Reads UART state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *    buf - Caller-provided data buffer.
 *    nbytes - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_read_async(uart_handle_t const huart, uint8_t *const buf,
        uint32_t nbytes);

/*
 * Starts the transmission of data from UART asynchronously.
 *
 * This function attempts to write certain number of bytes from a pre-allocated buffer to a receiver device, in asynchronous way.
 * It returns immediately when the operation is started and the status can be checked by calling uart_ioctl.
 * Once the operation completes, successful or not, the user callback will be invoked.
 *
 * Partial write might happen.
 * And the number of bytes that have been actually written can be obtained by calling uart_ioctl.
 *
 * Note: In order to get notification when the asynchronous call is completed, uart_set_callback must be called prior to this.
 *
 *
 * huart - The peripheral handle returned in the open() call.
 * buf - The buffer with data to transmit.
 * nbytes - The number of bytes to send.
 *
 * Returns: * - UART_SUCCESS: on success
 * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 *     - pucBuffer is NULL
 *     - nbytes is 0
 * - -EIO:   if there is unknown driver error
 */
/* Function: uart_mw_write_async
 *
 * Writes or configures UART state, data, or register content.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *    buf - Caller-provided data buffer.
 *    nbytes - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_write_async(uart_handle_t const huart, uint8_t *const buf,
        uint32_t nbytes);

/*
 * Aborts the operation on the UART port if any underlying driver allows
 * cancellation of the operation.
 *
 * The application should call this function to stop the ongoing operation.
 *
 * huart - The peripheral handle returned in the open() call.
 *
 * Returns: * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 * - -ENOSYS: if this board doesn't support this operation.
 */
/* Function: uart_mw_cancel
 *
 * Performs a UART operation exposed by this layer.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_cancel(uart_handle_t const huart);

/*
 * Stops the operation and de-initializes the UART peripheral.
 *
 *
 * huart - The peripheral handle returned in the open() call.
 *
 * Returns: * - UART_SUCCESS: on success
 * - -EINVAL: if
 *     - huart is NULL
 *     - huart is not opened yet
 */
/* Function: uart_mw_close
 *
 * Closes the UART handle or instance and returns it to the inactive state.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t uart_mw_close(uart_handle_t const huart);

/* Console-facing wrappers to keep api/uart decoupled from LL headers. */
int32_t uart_mw_console_putc(uint32_t base_address, char c);
int32_t uart_mw_console_getc(uint32_t base_address, char *c);
void uart_mw_console_disable_all_interrupts(uint32_t base_address);
void uart_mw_console_shutdown(uint32_t instance);

/* Function: uart_mw_read_reg
 *
 * Reads UART state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    base - Base address or base identifier used by the operation.
 *    offset - Register or memory offset from the selected base address.
 *
 * Returns:
 *
 *    The requested value, count, address, or status flag.
 */
uint32_t uart_mw_read_reg(uint32_t base, uint32_t offset);

/* Function: uart_mw_write_reg
 *
 * Writes or configures UART state, data, or register content.
 *
 * Parameters:
 *
 *    base - Base address or base identifier used by the operation.
 *    offset - Register or memory offset from the selected base address.
 *    value - Value to write or storage for a value read by the function.
 *
 * Returns:
 *
 *    None.
 */
void uart_mw_write_reg(uint32_t base, uint32_t offset, uint32_t value);

/* Function: uart_mw_is_handle_valid
 *
 * Queries the current UART state and reports the result to the caller.
 *
 * Parameters:
 *
 *    huart - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int uart_mw_is_handle_valid(uart_handle_t huart);

/* Function: uart_mw_isr
 *
 * Queries the current UART state and reports the result to the caller.
 *
 * Parameters:
 *
 *    param - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    None.
 */
void uart_mw_isr(void *param);

/* Backward-compatible aliases for legacy callers. */
#define uart_read_sync       uart_mw_read_sync
#define uart_write_sync      uart_mw_write_sync
#define uart_read_async      uart_mw_read_async
#define uart_write_async     uart_mw_write_async
#define uart_cancel          uart_mw_cancel
#define uart_close           uart_mw_close
#define uart_read_reg        uart_mw_read_reg
#define uart_write_reg       uart_mw_write_reg
#define uart_is_handle_valid uart_mw_is_handle_valid
#define uart_isr             uart_mw_isr
#endif /* __SOCFPGA_UART_H__ */
