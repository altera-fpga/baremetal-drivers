/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT
 */

/* File: socfpga_spi.h
 *
 * SPI hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
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
 * Modified for SoC FPGA
 */

#ifndef __SOCFPGA_SPI_H__
#define __SOCFPGA_SPI_H__

#include <stdint.h>
#include <stddef.h>
#include "errno.h"

/* Enum: spi_xfer_status_t
 *
 * Defines the standard return and completion status codes for SPI driver operations, 
 * particularly used to indicate hardware states during asynchronous callback execution.
 *
 * Values:
 *
 * SPI_SUCCESS    - The full-duplex SPI transaction completed without any hardware faults.
 * SPI_WR_ERROR   - A hardware error occurred while pushing data to the Transmit FIFO (TXFIFO).
 * SPI_RD_ERROR   - A hardware error occurred while pulling data from the Receive FIFO (RXFIFO), such as an underflow/overflow.
 * SPI_XFER_ERROR - A general bus error or timeout occurred during the transaction.
 */
typedef enum
{
    SPI_SUCCESS,
    SPI_WR_ERROR,
    SPI_RD_ERROR,
    SPI_XFER_ERROR,
} spi_xfer_status_t;

/* Enum: spi_mode_t
 *
 * Defines the physical SPI bus clock framing formats, dictating the Clock Polarity (CPOL) 
 * and Clock Phase (CPHA) used by the master to shift and sample data bits.
 *
 * Values:
 *
 * SPI_MODE0 - CPOL = 0 (Clock idles low), CPHA = 0 (Data sampled on leading edge).
 * SPI_MODE1 - CPOL = 0 (Clock idles low), CPHA = 1 (Data sampled on trailing edge).
 * SPI_MODE2 - CPOL = 1 (Clock idles high), CPHA = 0 (Data sampled on leading edge).
 * SPI_MODE3 - CPOL = 1 (Clock idles high), CPHA = 1 (Data sampled on trailing edge).
 */
typedef enum
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
} spi_mode_t;

/* Enum: spi_ioctl_t
 *
 * Input/Output Control commands used to modify or retrieve the internal state 
 * and configuration of the SPI Master controller dynamically at runtime.
 *
 * Values:
 *
 * SPI_SET_CONFIG    - Programs the hardware baud rate divisor and clock phase/polarity. Expects a pointer to <spi_cfg_t>.
 * SPI_GET_CONFIG    - Reads the current active baud rate and mode from the hardware registers. Expects a pointer to <spi_cfg_t>.
 * SPI_GET_TX_NBYTES - Retrieves the exact number of bytes successfully pushed to the TXFIFO in the last operation. Expects a uint16_t pointer.
 * SPI_GET_RX_NBYTES - Retrieves the exact number of bytes successfully pulled from the RXFIFO in the last operation. Expects a uint16_t pointer.
 */
typedef enum
{
    SPI_SET_CONFIG,
    SPI_GET_CONFIG,
    SPI_GET_TX_NBYTES,
    SPI_GET_RX_NBYTES,
} spi_ioctl_t;

/* Struct: spi_cfg_t
 *
 * Configuration structure used with the SPI_SET_CONFIG and SPI_GET_CONFIG IOCTLs 
 * to define the primary electrical and timing characteristics of the SPI bus.
 */
typedef struct
{
    uint32_t clk;    /* The requested SPI master clock (SCK) frequency in Hz. The driver will calculate the nearest hardware divisor. */
    spi_mode_t mode; /* The Clock Polarity and Phase setting (Modes 0-3). */
} spi_cfg_t;

struct spi_handle;

/* Type: spi_handle_t
 *
 * An opaque software handle representing an active connection to a specific SPI 
 * Master hardware instance. It encapsulates the base MMIO address, current buffer 
 * pointers, transfer sizes, and synchronization primitives required for driver state.
 */
typedef struct spi_handle *spi_handle_t;

/* Type: spi_callback_t
 *
 * Function pointer signature for the application-level interrupt service routine 
 * (ISR) callback. This is invoked when an asynchronous SPI transfer completes, 
 * or when the hardware flags a critical FIFO error.
 *
 * Parameters:
 *
 * status - The hardware completion status of the background transfer.
 * pparam - An opaque user context pointer registered via <spi_set_callback>.
 */
typedef void (*spi_callback_t)(spi_xfer_status_t status, void *pparam);


/* Function: spi_open
 *
 * Initializes a specific SPI Master hardware block. This function un-gates the 
 * peripheral clock via the SoC Clock Manager, brings the IP out of reset via 
 * the Reset Manager, and prepares the internal software descriptor for use. 
 *
 * Parameters:
 *
 * instance - The zero-indexed hardware instance number (e.g., 0 for SPI0, 1 for SPI1).
 *
 * Returns:
 *
 * A valid <spi_handle_t> on success; NULL if the instance is out of bounds or 
 * the hardware fails to initialize.
 */
spi_handle_t spi_open(uint32_t instance);

/* Function: spi_set_callback
 *
 * Registers a user-defined function to be executed upon the completion of 
 * asynchronous SPI transfers (<spi_transfer_async>). 
 *
 * Parameters:
 *
 * hspi     - The active SPI instance handle.
 * callback - The function pointer to invoke upon transfer completion or error.
 * pcntxt   - An opaque pointer to user context that will be passed directly to the callback.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the handle is invalid.
 */
int32_t spi_set_callback(spi_handle_t const hspi, spi_callback_t callback,
                         void *pcntxt);

/* Function: spi_ioctl
 *
 * Provides a standardized interface for configuring hardware parameters or 
 * querying the state of the SPI controller without needing specialized functions.
 *
 * Parameters:
 *
 * hspi - The active SPI instance handle.
 * cmd  - The specific control command from <spi_ioctl_t>.
 * buf  - Pointer to the data payload associated with the command (e.g., <spi_cfg_t> 
 * for configuration, or a uint16_t for reading byte counts).
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if arguments are invalid or pointers are NULL.
 * -EBUSY if a hardware transfer is currently active and the configuration cannot be changed safely.
 */
int32_t spi_ioctl(spi_handle_t const hspi, spi_ioctl_t cmd, void *const buf);

/* Function: spi_transfer_sync
 *
 * Initiates a blocking, full-duplex SPI transaction. The driver writes data into 
 * the Transmit FIFO (TXFIFO) and polls the Receive FIFO (RXFIFO) to read the 
 * incoming shifted data. Because SPI is fundamentally full-duplex, the hardware 
 * master clock is driven for exactly `nbytes`. 
 *
 * If only a write is desired, the user must pass a valid `txbuf` and NULL for `rxbuf` 
 * (the driver will silently discard incoming bytes). If only a read is desired, 
 * `txbuf` should contain dummy bytes (usually 0xFF) and `rxbuf` must be valid.
 *
 * Parameters:
 *
 * hspi   - The active SPI instance handle.
 * txbuf  - Pointer to the transmission payload buffer (or dummy data for a read).
 * rxbuf  - Pointer to the destination buffer to hold incoming data.
 * nbytes - The exact number of bytes to shift across the bus.
 *
 * Returns:
 *
 * 0 on success.
 * -EINVAL if arguments are invalid.
 * -EBUSY if another operation is actively occupying the bus.
 * -EIO on a hardware timeout or FIFO fault.
 */
int32_t spi_transfer_sync(spi_handle_t const hspi, uint8_t *const txbuf,
                          uint8_t *const rxbuf, uint16_t nbytes);

/* Function: spi_transfer_async
 *
 * Initiates a non-blocking, full-duplex SPI transaction utilizing hardware 
 * interrupts. The driver primes the internal state machines and writes the first 
 * chunk of data into the TXFIFO. Control is immediately returned to the caller. 
 * The internal ISR handles refilling the TXFIFO and draining the RXFIFO as 
 * hardware watermark interrupts fire.
 *
 * Parameters:
 *
 * hspi   - The active SPI instance handle.
 * txbuf  - Pointer to the transmission payload buffer. Must remain valid in memory until the callback fires.
 * rxbuf  - Pointer to the destination buffer. Must remain valid in memory until the callback fires.
 * nbytes - The exact number of bytes to shift across the bus.
 *
 * Returns:
 *
 * 0 if the transfer was successfully queued and hardware started.
 * -EINVAL if arguments are invalid.
 * -EBUSY if the bus or internal state machine is currently locked by another transfer.
 */
int32_t spi_transfer_async(spi_handle_t const hspi, uint8_t *const txbuf,
                           uint8_t *const rxbuf, uint16_t nbytes);

/* Function: spi_close
 *
 * Safely deconstructs the software context for an active SPI controller. This 
 * disables the Master Enable bit in the hardware, masks all interrupts, clears 
 * pending FIFOs, and releases the handle memory.
 *
 * Parameters:
 *
 * hspi - The active SPI instance handle to shut down.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the handle is invalid or already closed.
 */
int32_t spi_close(spi_handle_t const hspi);

/* Function: spi_cancel
 *
 * Attempts to halt an ongoing asynchronous operation. Note: Aborting an active 
 * SPI transaction mid-shift can corrupt bus states and leave slave devices 
 * desynchronized. For this bare-metal driver implementation, cancellation 
 * is unsupported.
 *
 * Parameters:
 *
 * hspi - The active SPI instance handle.
 *
 * Returns:
 *
 * Always returns -ENOSYS (Function not implemented).
 */
int32_t spi_cancel(spi_handle_t const hspi);

/* Function: spi_select_slave
 *
 * Configures the Slave Select Enable Register (SER). The SPI master hardware 
 * can natively control multiple distinct Slave Select (NSS) output lines. This 
 * function routes the active master output to a specific physical slave pin.
 *
 * Parameters:
 *
 * hspi - The active SPI instance handle.
 * ss   - The zero-indexed hardware slave select line to assert (e.g., 0, 1, 2).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the requested slave select line exceeds hardware capabilities.
 */
int32_t spi_select_slave(spi_handle_t const hspi, uint32_t ss);

#endif /* _SOCFPGA_SPI_H_ */
