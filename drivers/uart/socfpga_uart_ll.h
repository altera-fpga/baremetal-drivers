/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_uart_ll.h
 *
 * UART low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_UART_LL_H__
#define __SOCFPGA_UART_LL_H__

#include <stdint.h>

#include "../middleware/uart/socfpga_uart.h"

/* Constants: UART interrupt identification status codes
 *
 * Values from the interrupt identification register.
 * Each one names the highest-priority interrupt that is waiting.
 *
 * MODEM_STATUS   - Modem status. The driver reports this as a hardware error.
 * NO_INTERRUPT   - No interrupt is waiting.
 * THR_EMPTY      - The transmit holding register is empty.
 * RX_DATA_RDY    - Receive data is ready.
 * RX_LINE_STATUS - Receive line status. The driver reports this as a hardware error.
 * BUSY_DETECT    - Busy-detect interrupt. The driver reports this as a hardware error.
 * CHAR_TIMEOUT   - A character timed out. The driver treats this as receive data ready.
 */
#define MODEM_STATUS      0x0U
#define NO_INTERRUPT      0x1U
#define THR_EMPTY         0x2U
#define RX_DATA_RDY       0x4U
#define RX_LINE_STATUS    0x6U
#define BUSY_DETECT       0x7U
#define CHAR_TIMEOUT      0xCU

/* Constants: Interrupt priority mapping
 *
 * IDs that get_int_status returns.
 *
 * UART_NO_INT          - No interrupt is waiting.
 * UART_TXBUF_EMPTY_INT - The transmit buffer can take more data.
 * UART_RXBUF_RDY_INT   - Receive data is ready, or a character timed out.
 * UART_HW_ERR_INT      - Any other identification code, including line errors, modem status, and busy detect.
 */
#define UART_NO_INT             0U
#define UART_TXBUF_EMPTY_INT    0x1U
#define UART_RXBUF_RDY_INT      0x2U
#define UART_HW_ERR_INT         0x3U

/* Constants: UART configuration status codes
 *
 * Values that uart_set_baud returns.
 *
 * UART_CFG_STATUS_FAIL - The baud rate is 0, so the call failed.
 * UART_CFG_STATUS_OK   - The baud divisor was written.
 */
#define UART_CFG_STATUS_FAIL     0U
#define UART_CFG_STATUS_OK       1U


/* Enum: uart_interrupt_id_t
 *
 * Maps hardware-specific interrupt events to categorical identifiers used 
 * throughout the software stack.
 *
 * Values:
 *
 * INTERRUPT_RX - Triggered when the RX FIFO reaches the threshold or a character timeout occurs.
 * INTERRUPT_TX - Triggered when the TX FIFO is empty and ready for more data.
 * INTERRUPT_HW - Triggered by hardware line errors (parity, framing, break, or overrun).
 */
typedef enum
{
    INTERRUPT_RX, INTERRUPT_TX, INTERRUPT_HW
} uart_interrupt_id_t;


/* Function: uart_enable_clock
 *
 * Interfaces with the System Manager to enable the clock gate for the specified 
 * UART instance. This must be invoked before any MMIO register access to avoid 
 * bus errors or reading stale register states.
 *
 * Parameters:
 *
 * instance - The hardware instance index (e.g., 0 for UART0, 1 for UART1).
 *
 * Returns:
 *
 * None.
 */
void uart_enable_clock(uint32_t instance);

/* Function: uart_disable_clock
 *
 * Interfaces with the System Manager to gate off the clock for the specified 
 * UART instance. This reduces dynamic power consumption when the peripheral 
 * is no longer in use.
 *
 * Parameters:
 *
 * instance - The hardware instance index.
 *
 * Returns:
 *
 * None.
 */
void uart_disable_clock(uint32_t instance);

/* Function: uart_assert_reset
 *
 * Triggers a hardware reset for the specified UART instance by writing to the 
 * Reset Manager. This forces the UART register map and internal state machines 
 * back to their power-on default state.
 *
 * Parameters:
 *
 * instance - The hardware instance index.
 *
 * Returns:
 *
 * None.
 */
void uart_assert_reset(uint32_t instance);

/* Function: uart_deassert_reset
 *
 * Releases the reset signal in the Reset Manager for the specified UART instance, 
 * allowing the 16550 controller to begin normal operation and accept MMIO writes.
 *
 * Parameters:
 *
 * instance - The hardware instance index.
 *
 * Returns:
 *
 * None.
 */
void uart_deassert_reset(uint32_t instance);

/* Function: uart_write_fifo
 *
 * Pushes raw byte data into the UART's Transmit Holding Register (THR) FIFO. 
 * This function handles the low-level MMIO loop required to move user data from 
 * the memory buffer directly into the UART peripheral for serialization.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * buffer       - Pointer to the source data buffer.
 * bytes        - The maximum number of bytes to attempt to write.
 *
 * Returns:
 *
 * The exact number of bytes successfully accepted by the hardware FIFO.
 */
uint16_t uart_write_fifo(uint32_t base_address, uint8_t *const buffer,
        uint32_t bytes);

/* Function: uart_read_fifo
 *
 * Extracts available bytes from the UART's Receive Buffer Register (RBR) FIFO. 
 * This function quickly drains the hardware RX FIFO into the provided software 
 * memory buffer.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * buffer       - Pointer to the destination data buffer.
 * bytes        - The maximum number of bytes to attempt to read.
 *
 * Returns:
 *
 * The exact number of bytes successfully retrieved from the hardware FIFO.
 */
uint16_t uart_read_fifo(uint32_t base_address, uint8_t *const buffer,
        uint32_t bytes);

/* Function: uart_enable_interrupt
 *
 * Configures the Interrupt Enable Register (IER) to allow specific UART events 
 * (such as RX Data Available, TX Holding Register Empty, or Line Status Errors) 
 * to actively assert the hardware interrupt line to the processor.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * id           - The categorized interrupt event to enable.
 *
 * Returns:
 *
 * None.
 */
void uart_enable_interrupt(uint32_t base_address, uart_interrupt_id_t id);

/* Function: uart_disable_interrupt
 *
 * Modifies the Interrupt Enable Register (IER) to mask the specific UART 
 * event, preventing it from firing an IRQ to the processor while preserving 
 * other enabled interrupts.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * id           - The categorized interrupt event to disable.
 *
 * Returns:
 *
 * None.
 */
void uart_disable_interrupt(uint32_t base_address, uart_interrupt_id_t id);

/* Function: get_int_status
 *
 * Reads the Interrupt Identification Register (IIR). This register prioritizes 
 * pending interrupts. It is heavily utilized by the ISR to determine exactly 
 * why the UART hardware triggered an IRQ (e.g., distinguishing between a 
 * character timeout and a full RX FIFO).
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 *
 * Returns:
 *
 * The pending interrupt status code directly from the hardware.
 */
uint32_t get_int_status(uint32_t base_address);

/* Function: uart_config_fifo
 *
 * Writes to the FIFO Control Register (FCR) to explicitly enable the 16550-style 
 * TX and RX hardware FIFOs, clear their current contents, and configure the 
 * DMA/interrupt watermark trigger levels.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 *
 * Returns:
 *
 * None.
 */
void uart_config_fifo(uint32_t base_address);

/* Function: uart_set_config
 *
 * Configures the Line Control Register (LCR). This defines the foundational 
 * framing format for asynchronous serial communication: parity mode, number of 
 * stop bits, and the word length (bits per character).
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * parity       - The desired parity configuration (None, Odd, Even).
 * stopbit      - The desired number of stop bits (1 or 2).
 * wordlen      - The word length in bits (typically 5 to 8).
 *
 * Returns:
 *
 * None.
 */
void uart_set_config(uint32_t base_address, uart_partity_t parity,
        uart_stop_bits_t stopbit, uint32_t wordlen);

/* Function: uart_set_baud
 *
 * Sets the UART communication speed. This sequence requires setting the Divisor 
 * Latch Access Bit (DLAB) in the LCR, calculating the baud rate divisor against 
 * the reference clock, programming the High and Low Divisor Latches (DLH/DLL), 
 * and clearing the DLAB to restore standard read/write access to the FIFOs.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * baud         - The target baud rate (e.g., 115200, 9600).
 *
 * Returns:
 *
 * UART_CFG_STATUS_OK when divisor programming succeeds, UART_CFG_STATUS_FAIL
 * when the requested baud is invalid.
 */
uint32_t uart_set_baud(uint32_t base_address, uint32_t baud);

/* Function: uart_get_config
 *
 * Reads current frame format settings (baud, parity, stop bits, word length) 
 * directly from the hardware registers. This is useful for verifying configurations 
 * or inheriting settings applied by an earlier bootloader.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 * baud         - Pointer to store the current baud rate.
 * parity       - Pointer to store the current parity mode.
 * stopbit      - Pointer to store the current stop bit setting.
 * wordlen      - Pointer to store the current word length.
 *
 * Returns:
 *
 * None.
 */
void uart_get_config(uint32_t base_address, uint32_t *baud,
		uart_partity_t *parity, uart_stop_bits_t *stopbit,
		uint32_t *wordlen);

/* Function: uart_get_baud
 *
 * Calculates the currently active baud rate. It asserts the DLAB bit, reads 
 * the Divisor Latch registers (DLL and DLH), and applies the reverse clock 
 * division formula against the hardware reference clock.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target UART hardware block.
 *
 * Returns:
 *
 * The currently active baud rate.
 */
uint32_t uart_get_baud(uint32_t base_address);

#endif /* __SOCFPGA_UART_LL_H__ */