/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_spi_ll.h
 *
 * SPI low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SPI_LL_H__
#define __SOCFPGA_SPI_LL_H__

#include <stdbool.h>
#include <stdint.h>
#include "errno.h"

#include "socfpga_spi.h"
#include "socfpga_spi_reg.h"

/* Macro: SPI_GET_INT_ID
 * Resolves the system-level hardware interrupt request (IRQ) number assigned 
 * to a specific SPI instance by the SoC's Generic Interrupt Controller (GIC).
 */
#define SPI_GET_INT_ID(instance)    (((instance) == 1U) ? SPI1IRQ : SPI0IRQ)

/* Constants: DesignWare transfer modes (TMOD)
 *
 * Values written to the transfer-mode field of CTRLR0.
 *
 * SPI_TX_RX_MOD - Send and receive at the same time. This is the mode
 *                 set during init.
 * SPI_TX_MOD    - Transmit only. Incoming receive data is discarded.
 * SPI_RX_MOD    - Receive only. The controller generates the clock.
 *                 No transmit data is required.
 */
#define SPI_TX_RX_MOD    0x00U /* Full-duplex: Transmit and Receive simultaneously. */
#define SPI_TX_MOD       0x01U /* Transmit-only: Discards incoming RX data. */
#define SPI_RX_MOD       0x02U /* Receive-only: Generates clock to pull data, no TX data required. */

/* Constants: Hardware tuning and timeouts
 *
 * FIFO limits, the default bus speed, and the poll limit used by the
 * driver.
 *
 * SPI_TX_FIFO_THRESHOLD - Transmit FIFO threshold written to TXFTLR
 *                         during init.
 * SPI_RX_FIFO_THRESHOLD - Receive FIFO threshold written to RXFTLR
 *                         during init.
 * SPI_POLL_TIMEOUT      - Number of idle poll loops before a polled
 *                         transfer gives up.
 * SPI_DEFAULT_SPEED_HZ  - Bus speed, in Hz, programmed during init.
 * SPI_FIFO_SAFE_TX_GAP  - Most bytes a polled transfer may send ahead
 *                         of the bytes it has read back.
 */
#define SPI_TX_FIFO_THRESHOLD    0U
#define SPI_RX_FIFO_THRESHOLD    0U
#define SPI_POLL_TIMEOUT         1000000U
#define SPI_DEFAULT_SPEED_HZ     500000U
#define SPI_FIFO_SAFE_TX_GAP     32U

/* Constants: Interrupt masking definitions
 *
 * Values passed to the interrupt status, enable, and disable calls.
 *
 * SPI_NO_INTERRUPT   - No FIFO interrupt is pending.
 * SPI_TX_EMPTY_INT   - Transmit FIFO empty. Selects that bit in the
 *                      interrupt mask.
 * SPI_RX_FULL_INT    - Receive FIFO full. Selects that bit in the
 *                      interrupt mask.
 * SPI_ALL_INTERRUPTS - Every interrupt mask the driver changes.
 */
#define SPI_NO_INTERRUPT      0x00U
#define SPI_TX_EMPTY_INT      0x01U
#define SPI_RX_FULL_INT       0x02U
#define SPI_ALL_INTERRUPTS    0x03U

/* Constants: Status flags
 *
 * Status values for the transmit and receive FIFOs.
 *
 * TX_EMPTY - Transmit FIFO empty flag.
 * RX_FULL  - Receive FIFO full flag.
 */
#define TX_EMPTY    0x01U
#define RX_FULL     0x10U


/* Function: spi_init
 *
 * Performs foundational hardware initialization for the target SPI controller. 
 * This involves interacting with the SoC System Manager to un-gate the peripheral 
 * clock and the Reset Manager to transition the IP out of its power-on reset state.
 *
 * Parameters:
 *
 * instance - The zero-indexed hardware instance (e.g., 0 for SPI0).
 */
void spi_init(uint32_t instance);

/* Function: spi_deinit
 *
 * Reverses the initialization process, asserting the hardware reset line and 
 * gating the peripheral clock to eliminate dynamic power consumption when the 
 * SPI block is no longer needed.
 *
 * Parameters:
 *
 * instance - The hardware instance index.
 */
void spi_deinit(uint32_t instance);

/* Function: spi_select_chip
 *
 * Writes to the Slave Enable Register (SER) to assert a specific hardware 
 * Chip Select (NSS) line. The DesignWare IP can natively drive multiple slaves 
 * depending on hardware configuration.
 *
 * Parameters:
 *
 * instance - The hardware instance index.
 * slave    - The one-based chip-select number to assert (1, 2, 3, etc.). 
 * Passing 0 explicitly clears the SER, de-asserting all lines.
 */
void spi_select_chip(uint32_t instance, uint32_t slave);

/* Function: spi_set_config
 *
 * Configures the master clock divisor and the bus framing parameters. This safely 
 * disables the controller (SPIENR), calculates the necessary Baud Rate Select 
 * (BAUDR) register divisor based on the peripheral clock, configures the SCPOL 
 * and SCPH bits in CTRLR0, and then re-enables the block.
 *
 * Parameters:
 *
 * base_address - The computed MMIO base address of the SPI instance.
 * freq         - The target serial clock (SCK) frequency in Hertz.
 * mode         - The framing mode (CPOL/CPHA) from <spi_mode_t>.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if freq is 0; -EIO if CLOCK_SSPI cannot be resolved.
 */
int32_t spi_set_config(uint32_t base_address, uint32_t freq, spi_mode_t mode);

/* Function: spi_get_config
 *
 * Interrogates the hardware's BAUDR and CTRLR0 registers to extract the currently 
 * active clock frequency and framing mode settings.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * freq         - Pointer to store the resolved active frequency in Hertz.
 * mode         - Pointer to store the resolved <spi_mode_t>.
 */
void spi_get_config(uint32_t base_address, uint32_t *freq, spi_mode_t *mode);

/* Function: spi_set_transfermode
 *
 * Modifies the TMOD (Transfer Mode) field within CTRLR0. This dictates whether 
 * the hardware will enforce full-duplex transfers or optimize for transmit-only/
 * receive-only data paths. The controller must be disabled prior to this call.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * mode         - The transfer mode constant (e.g., SPI_TX_RX_MOD).
 */
void spi_set_transfermode(uint32_t base_address, uint32_t mode);

/* Function: spi_set_loopback
 *
 * Toggles the Shift Register Loop (SRL) bit in CTRLR0. When enabled, the hardware 
 * internally routes the TX serial output directly back into the RX serial input, 
 * bypassing the physical external pins. Extremely useful for driver diagnostics.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * enable       - true to enable internal loopback; false for normal operation.
 */
void spi_set_loopback(uint32_t base_address, bool enable);

/* Function: spi_enable
 *
 * Writes to the SPI Enable Register (SPIENR) to activate the controller. This 
 * commits all configuration changes in CTRLR0/BAUDR and readies the FIFOs for data.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 */
void spi_enable(uint32_t base_address);

/* Function: spi_disable
 *
 * Writes to the SPI Enable Register (SPIENR) to halt the controller. Ongoing 
 * transfers will be aborted. This is a mandatory step before modifying primary 
 * configuration registers.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 */
void spi_disable(uint32_t base_address);

/* Function: spi_get_freq
 *
 * Extracts the current divisor from the BAUDR register and applies the reverse 
 * calculation against the SoC's reference peripheral clock to determine the 
 * actual SCK frequency.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 *
 * Returns:
 *
 * The physical SCK frequency in Hertz, or 0 if it cannot be resolved.
 */
uint32_t spi_get_freq(uint32_t base_address);

/* Function: spi_get_version
 *
 * Reads the read-only Component Version Register (SSI_COMP_VERSION) baked into 
 * the silicon by Synopsys to identify the exact IP revision of the controller.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 *
 * Returns:
 *
 * The raw 32-bit hardware version string/code.
 */
uint32_t spi_get_version(uint32_t base_address);

/* Function: spi_write_fifo
 *
 * Pushes a contiguous block of data into the Data Register (DR). The hardware 
 * automatically shifts this into the TX FIFO. The function checks the TX FIFO 
 * Level Register (TXFLR) to avoid overflow and stops when the FIFO is full or 
 * the requested bytes are written.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * buffer       - Pointer to the source data.
 * bytes        - Number of bytes to attempt to write.
 *
 * Returns:
 *
 * The actual number of bytes successfully accepted by the TX FIFO.
 */
uint16_t spi_write_fifo(uint32_t base_address, const uint8_t *buffer, uint16_t bytes);

/* Function: spi_read_fifo
 *
 * Pulls available data out of the Data Register (DR), draining the hardware 
 * RX FIFO into software memory. It checks the RX FIFO Level Register (RXFLR) 
 * to ensure it does not attempt to read from an empty FIFO.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * buffer       - Pointer to the destination memory.
 * bytes        - Maximum number of bytes to attempt to read.
 *
 * Returns:
 *
 * The actual number of bytes extracted from the RX FIFO.
 */
uint16_t spi_read_fifo(uint32_t base_address, uint8_t *buffer, uint16_t bytes);

/* Function: spi_transfer_poll
 *
 * Orchestrates a complete, blocking SPI transfer without relying on hardware 
 * interrupts. It utilizes a busy-wait loop, repeatedly calling <spi_write_fifo> 
 * and <spi_read_fifo>, while polling the Status Register (SR) for completion 
 * or a timeout threshold.
 *
 * Parameters:
 *
 * base_address  - The MMIO base address of the SPI block.
 * txbuf         - Pointer to the transmission payload (or dummy bytes).
 * rxbuf         - Pointer to the destination buffer (or NULL if discarding).
 * nbytes        - The total number of bytes to shift.
 * timeout_polls - The maximum number of busy-wait iterations before aborting.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT or other negative errno code on failure.
 */
int32_t spi_transfer_poll(uint32_t base_address,
                          const uint8_t *txbuf,
                          uint8_t *rxbuf,
                          uint16_t nbytes,
                          uint32_t timeout_polls);

/* Function: spi_wait_idle
 *
 * Actively polls the BUSY bit in the hardware Status Register (SR). Returns 
 * only when the SPI master is completely idle, meaning the TX FIFO is empty 
 * and the final bit has been shifted out over the physical pins.
 *
 * Parameters:
 *
 * base_address  - The MMIO base address of the SPI block.
 * timeout_polls - The maximum number of polling iterations before aborting.
 *
 * Returns:
 *
 * 0 if the hardware reached idle; -ETIMEDOUT if it remained busy.
 */
int32_t spi_wait_idle(uint32_t base_address, uint32_t timeout_polls);

/* Function: spi_flush_rx_fifo
 *
 * Forcefully clears the Receive FIFO. It polls the RX FIFO Level Register (RXFLR) 
 * and executes dummy reads from the Data Register (DR) until the FIFO is entirely empty.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 */
void spi_flush_rx_fifo(uint32_t base_address);

/* Function: spi_get_interrupt_status
 *
 * Reads the consolidated Interrupt Status Register (ISR) to determine what 
 * conditions (e.g., TX Empty, RX Full, Overrun) are currently requesting 
 * service from the processor.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 *
 * Returns:
 *
 * An 8-bit mask representing the active, unmasked interrupt sources.
 */
uint8_t spi_get_interrupt_status(uint32_t base_address);

/* Function: spi_enable_interrupt
 *
 * Sets bits in the Interrupt Mask Register (IMR) to unmask specific hardware 
 * events, allowing them to propagate to the SoC's Generic Interrupt Controller.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * ir_id        - The bitmask of interrupts to enable.
 */
void spi_enable_interrupt(uint32_t base_address, uint32_t ir_id);

/* Function: spi_disable_interrupt
 *
 * Clears bits in the Interrupt Mask Register (IMR) to mask specific hardware 
 * events, silencing them from triggering external processor interrupts.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the SPI block.
 * ir_id        - The bitmask of interrupts to disable.
 */
void spi_disable_interrupt(uint32_t base_address, uint32_t ir_id);

#endif /* __SOCFPGA_SPI_LL_H__ */
