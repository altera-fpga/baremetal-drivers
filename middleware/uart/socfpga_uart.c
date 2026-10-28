/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_uart.c
 *
 * UART source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: middleware
 * Component: UART
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "errno.h"
#include "socfpga_interrupt.h"
#include "socfpga_uart.h"
#include "socfpga_uart_ll.h"
#include "socfpga_uart_reg.h"
#include "platform_def.h"

#define GET_INT_ID(instance)    (((instance) == 1U) ? UART1IRQ: UART0IRQ)
struct uart_descriptor
{
	/* State flags */
	uint8_t is_open;       /* 0 = closed, 1 = open */
	uint8_t tx_is_busy;    /* transmit busy flag */
	uint8_t rx_is_busy;    /* receive busy flag */
	uint8_t tx_is_async;   /* async transmit flag */
	uint8_t rx_is_async;   /* async receive flag */

	/* Hardware info */
	uint32_t instance;     /* UART instance number */
	uint32_t base_address; /* UART base address */

	/* Transmit/receive bookkeeping */
	size_t tx_bytes_left;
	size_t rx_bytes_left;
	size_t tx_size;
	size_t rx_size;
	uint8_t *tx_buf;
	uint8_t *rx_buf;

	size_t tx_count;   // <--- add this
	size_t rx_count;   // optional if you want symmetry

	/* Callback for async mode */
	uart_callback_t callback_fn;
	void *cb_user_context;
};


uint32_t uart_mw_read_reg(uint32_t base, uint32_t offset)
{
	return *((volatile uint32_t *)(uintptr_t)(base + offset));
}

void uart_mw_write_reg(uint32_t base, uint32_t offset, uint32_t value)
{
	*((volatile uint32_t *)(uintptr_t)(base + offset)) = value;
}

int uart_mw_is_handle_valid(uart_handle_t huart)
{
	return (huart != NULL) && (huart->is_open != 0);
}


void uart_mw_write(uart_handle_t huart, uint8_t *const buffer, uint32_t nbytes)
{
	uint16_t byte_count = 0U;
	huart->tx_bytes_left = nbytes;

	byte_count = uart_write_fifo(huart->base_address, buffer, nbytes);

	huart->tx_bytes_left = huart->tx_bytes_left - byte_count;
	huart->tx_buf += byte_count;

	uart_enable_interrupt(huart->base_address, INTERRUPT_TX);
}


int32_t uart_mw_read(uart_handle_t huart, uint8_t *const buffer, uint32_t nbytes)
{
	uint16_t byte_count = 0U;

	if (!uart_mw_is_handle_valid(huart) || (buffer == NULL) || (nbytes == 0U))
	{
		return -EINVAL;
	}

	huart->rx_bytes_left = nbytes;
	huart->rx_buf = buffer;

	byte_count = uart_read_fifo(huart->base_address, buffer, nbytes);

	huart->rx_bytes_left -= byte_count;
	huart->rx_buf += byte_count;

	if (huart->rx_bytes_left > 0U)
	{
		uart_enable_interrupt(huart->base_address, INTERRUPT_RX);
	}
	else
	{
		if (huart->rx_is_async)
		{
			if (huart->callback_fn != NULL)
			{
				huart->callback_fn(UART_RD_DONE, huart->cb_user_context);
			}
			huart->rx_is_async = false;
			huart->rx_is_busy = false;
		}
		else
		{
			// synchronous read is done immediately, nothing else needed
			huart->rx_is_busy = false;
		}
	}

	return 0;
}


int32_t uart_mw_write_async(uart_handle_t huart, uint8_t *buf, uint32_t nbytes)
{
	if (!huart || !buf || nbytes == 0U)
	{
		return -EINVAL;
	}

	if (!huart->is_open)
	{
		return -EINVAL;
	}

	if (huart->tx_is_busy)
	{
		return -EBUSY;
	}

	// Mark as busy and async
	huart->tx_is_busy = true;
	huart->tx_is_async = true;

	// Save buffer info for ISR or polling
	huart->tx_buf = buf;
	huart->tx_size = nbytes;
	huart->tx_count = 0;

	// Start transmitting first byte immediately
	if (nbytes > 0)
	{
		// Wait for THR empty
		while (!(uart_mw_read_reg(huart->base_address, UART_LSR) & UART_LSR_THRE_MASK));

		uart_mw_write_reg(huart->base_address, UART_THR, buf[0]);
		huart->tx_count = 1;
	}

	// Rest of the transmission handled in uart ISR or next poll
	return 0;
}


int32_t uart_mw_write_sync(uart_handle_t huart, uint8_t *buf, uint32_t nbytes)
{
	if (!huart || !buf || nbytes == 0U)
	{
		return -EINVAL;
	}

	if (!huart->is_open)
	{
		return -EINVAL;
	}

	if (huart->tx_is_busy)
	{
		return -EBUSY;
	}

	// Mark UART as busy and synchronous
	huart->tx_is_busy = true;
	huart->tx_is_async = false;

	// Send bytes one by one
	for (uint32_t i = 0; i < nbytes; i++)
	{
		// Wait until THR (Transmit Holding Register) is empty
		while (!(uart_mw_read_reg(huart->base_address, UART_LSR) & UART_LSR_THRE_MASK));

		uart_mw_write_reg(huart->base_address, UART_THR, buf[i]);
	}

	// Transmission done
	huart->tx_is_busy = false;

	return 0;
}


int32_t uart_mw_read_async(uart_handle_t huart, uint8_t *buf, uint32_t nbytes)
{
	if (!huart || !buf || nbytes == 0U)
	{
		return -EINVAL;
	}

	if (!huart->is_open)
	{
		return -EINVAL;
	}

	if (huart->rx_is_busy)
	{
		return -EBUSY;
	}

	// Mark UART as busy and async
	huart->rx_is_busy = true;
	huart->rx_is_async = true;

	huart->rx_buf = buf;
	huart->rx_size = nbytes;

	// Polling read: fill buffer one byte at a time
	for (uint32_t i = 0; i < nbytes; i++)
	{
		// Wait until data ready
		while (!(uart_mw_read_reg(huart->base_address, UART_LSR) & UART_LSR_DR_MASK));

		buf[i] = (uint8_t)uart_mw_read_reg(huart->base_address, UART_RBR);
	}

	huart->rx_is_busy = false; // done

	return 0;
}


int32_t uart_mw_read_sync(uart_handle_t huart, uint8_t *buf, uint32_t nbytes)
{
	if (!huart || !buf || nbytes == 0U)
	{
		return -EINVAL;
	}

	if (!huart->is_open)
	{
		return -EINVAL;
	}

	if (huart->rx_is_busy)
	{
		return -EBUSY;
	}

	huart->rx_is_busy = true;
	huart->rx_is_async = false;

	huart->rx_buf = buf;
	huart->rx_size = nbytes;

	// Polling read: wait for each byte
	for (uint32_t i = 0; i < nbytes; i++)
	{
		while (!(uart_mw_read_reg(huart->base_address, UART_LSR) & UART_LSR_DR_MASK)); // wait until data ready

		buf[i] = (uint8_t)uart_mw_read_reg(huart->base_address, UART_RBR);
	}

	huart->rx_is_busy = false;

	return 0;
}


int32_t uart_mw_cancel(uart_handle_t const huart)
{
	if ((huart == NULL) || !uart_mw_is_handle_valid(huart))
	{
		return -EINVAL;
	}
	return -ENOSYS;
}


int32_t uart_mw_close(uart_handle_t huart)
{
	if ((huart == NULL) || (huart->is_open == 0))
	{
		return -EINVAL;
	}

	// Mark handle as closed
	huart->is_open = 0;
	huart->tx_is_busy = false;
	huart->rx_is_busy = false;
	huart->tx_is_async = false;
	huart->rx_is_async = false;

	return 0;
}


void uart_mw_isr(void *param)
{
	uart_handle_t huart = (uart_handle_t)param; // huart is already a pointer
	uint32_t id;
	uint16_t rx_byte_count;
	uint16_t tx_byte_count;

	if (!uart_mw_is_handle_valid(huart))
	{
		return;
	}

	id = get_int_status(huart->base_address);

	switch (id)
	{
		case UART_RXBUF_RDY_INT:
			if (huart->rx_bytes_left > 0U)
			{
				rx_byte_count = uart_read_fifo(huart->base_address,
												huart->rx_buf,
												huart->rx_bytes_left);

				huart->rx_bytes_left -= rx_byte_count;
				huart->rx_buf += rx_byte_count;
			}

			if (huart->rx_bytes_left == 0U)
			{
				uart_disable_interrupt(huart->base_address, INTERRUPT_RX);

				if (huart->rx_is_async)
				{
					if (huart->callback_fn != NULL)
					{
						huart->callback_fn(UART_RD_DONE, huart->cb_user_context);
					}
					huart->rx_is_async = false;
					huart->rx_is_busy = false;
			}
			}
			break;

		case UART_TXBUF_EMPTY_INT:
			if (huart->tx_bytes_left > 0U)
			{
				tx_byte_count = uart_write_fifo(huart->base_address,
												huart->tx_buf,
												huart->tx_bytes_left);

				huart->tx_bytes_left -= tx_byte_count;
				huart->tx_buf += tx_byte_count;
			}
			else
			{
				uart_disable_interrupt(huart->base_address, INTERRUPT_TX);

				if (huart->tx_is_async)
				{
					if (huart->callback_fn != NULL)
					{
						huart->callback_fn(UART_WR_DONE, huart->cb_user_context);
					}
					huart->tx_is_async = false;
					huart->tx_is_busy = false;
				}
			}
			break;

		case UART_HW_ERR_INT:
			// Optional: handle hardware errors
			break;

		default:
			break;
	}
}

int32_t uart_mw_console_putc(uint32_t base_address, char c)
{
	uint8_t ch;

	if (base_address == 0U) {
		return -EINVAL;
	}

	if (c == '\n') {
		ch = '\r';
		while (uart_write_fifo(base_address, &ch, 1U) == 0U) { }
	}

	ch = (uint8_t)c;
	while (uart_write_fifo(base_address, &ch, 1U) == 0U) { }

	return 0;
}

int32_t uart_mw_console_getc(uint32_t base_address, char *c)
{
	uint8_t ch;

	if ((base_address == 0U) || (c == NULL)) {
		return -EINVAL;
	}

	while (uart_read_fifo(base_address, &ch, 1U) == 0U) { }
	*c = (char)ch;

	return 0;
}

void uart_mw_console_disable_all_interrupts(uint32_t base_address)
{
	uart_disable_interrupt(base_address, INTERRUPT_RX);
	uart_disable_interrupt(base_address, INTERRUPT_TX);
	uart_disable_interrupt(base_address, INTERRUPT_HW);
}

void uart_mw_console_shutdown(uint32_t instance)
{
	uart_assert_reset(instance);
	uart_disable_clock(instance);
}

