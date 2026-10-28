/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_i3c_ll.h
 *
 * I3C low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_I3C_LL_H
#define SOCFPGA_I3C_LL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

#include "mmio.h"

/* Constant: SOCFPGA_I3C_DEFAULT_TIMEOUT
 * The standard active-polling limit for low-level synchronous FIFO and Queue 
 * operations before yielding a hardware timeout fault.
 */
#define SOCFPGA_I3C_DEFAULT_TIMEOUT 1000000U


/* Function: socfpga_i3c_ll_enable
 *
 * Directly manipulates the Device Control Register to assert or deassert the 
 * primary enable bit of the I3C Master controller.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * enable       - true to enable the core logic and bus drivers; false to disable.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the base address is invalid.
 */
int32_t socfpga_i3c_ll_enable(uint32_t base_address, bool enable);

/* Function: socfpga_i3c_ll_soft_reset
 *
 * Triggers a localized soft reset of the I3C Master controller via the hardware 
 * Reset Control Register. This flushes the TX/RX FIFOs, clears the Command and 
 * Response queues, and resets internal state machines without requiring a full 
 * system-level peripheral reset.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * reset_mask   - A hardware-specific bitmask dictating which sub-blocks to reset 
 * (e.g., FIFOs only vs. entire controller).
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_ll_soft_reset(uint32_t base_address, uint32_t reset_mask);

/* Function: socfpga_i3c_ll_enable_interrupts
 *
 * Modifies the Interrupt Mask Register to selectively route internal hardware 
 * events (such as RX Buffer Full, TX Buffer Empty, or Response Queue Ready) 
 * to the system's Generic Interrupt Controller (GIC).
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * mask         - The specific interrupt status bits to modify.
 * signal       - true to unmask (enable) the interrupt generation; false to mask (disable).
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_ll_enable_interrupts(uint32_t base_address, uint32_t mask,
                                         bool signal);

/* Function: socfpga_i3c_ll_send_command
 *
 * Orchestrates a low-level enqueue operation. This function writes a fully 
 * formatted 32-bit instruction into the hardware Command Queue (CQ), and 
 * subsequently pushes the associated payload into the Transmit (TX) FIFO.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * command      - The 32-bit encoded I3C command descriptor.
 * data_words   - Pointer to the payload buffer.
 * word_count   - Number of 32-bit words to push to the TX FIFO.
 * timeout      - Maximum polling iterations to wait for FIFO space before aborting.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the hardware FIFOs remain full and cannot accept data.
 */
int32_t socfpga_i3c_ll_send_command(uint32_t base_address, uint32_t command,
                                    const uint32_t *data_words,
                                    uint32_t word_count,
                                    uint32_t timeout);

/* Function: socfpga_i3c_ll_read_response
 *
 * Actively polls the Response Queue (RQ) for a transaction completion descriptor. 
 * This 32-bit word contains the final status of a bus transfer, including data 
 * lengths and error flags (e.g., NACK, Parity Error).
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * response     - Pointer to a 32-bit variable where the response descriptor will be written.
 * timeout      - Maximum polling iterations to wait for the RQ to flag ready.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the controller fails to produce a response.
 */
int32_t socfpga_i3c_ll_read_response(uint32_t base_address, uint32_t *response,
                                     uint32_t timeout);

/* Function: socfpga_i3c_ll_read_data
 *
 * Drains incoming 32-bit words from the hardware Receive (RX) FIFO. The driver 
 * monitors the RX Buffer Level register to ensure it only reads valid data 
 * shifted in from the I3C bus.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * data_words   - Pointer to the destination buffer.
 * word_count   - The number of 32-bit words to extract from the FIFO.
 * timeout      - Maximum polling iterations to wait for data to become available.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the expected data does not arrive.
 */
int32_t socfpga_i3c_ll_read_data(uint32_t base_address, uint32_t *data_words,
                                 uint32_t word_count, uint32_t timeout);

/* Function: socfpga_i3c_ll_program_dat_entry
 *
 * Configures a specific slot within the controller's Device Address Table (DAT). 
 * The hardware uses this table to resolve the `device_index` supplied in Command 
 * Queue descriptors to actual 7-bit bus addresses and protocol rules.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * device_index - The hardware DAT slot to program (typically 0-15).
 * address      - The 7-bit static I2C or dynamically assigned I3C device address.
 * legacy_i2c   - true if the device lacks I3C support, forcing the hardware to 
 * use standard I2C timing and protocols for this index.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the device index exceeds hardware limits.
 */
int32_t socfpga_i3c_ll_program_dat_entry(uint32_t base_address,
                                         uint32_t device_index,
                                         uint8_t address,
                                         bool legacy_i2c);

/* Function: socfpga_i3c_ll_private_transfer
 *
 * A monolithic helper function to execute a complete, synchronous read or write 
 * transaction. It formats the Command Queue descriptor, manages the TX/RX FIFOs, 
 * and waits for the Response Queue to confirm completion, returning the result 
 * to the caller.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * device_index - The DAT index identifying the target peripheral.
 * read         - true for a read transaction; false for a write transaction.
 * tx_buffer    - Pointer to the data to send (ignored if `read` is true).
 * tx_length    - Number of bytes to send.
 * rx_buffer    - Pointer to the buffer for receiving data (ignored if `read` is false).
 * rx_length    - Number of bytes to receive.
 * timeout      - Maximum polling iterations for the entire transaction.
 * response     - Pointer to store the final Response Queue hardware descriptor.
 *
 * Returns:
 *
 * 0 on success; -EIO or -ETIMEDOUT on a bus failure.
 */
int32_t socfpga_i3c_ll_private_transfer(uint32_t base_address,
                                        uint32_t device_index,
                                        bool read,
                                        const uint8_t *tx_buffer,
                                        uint32_t tx_length,
                                        uint8_t *rx_buffer,
                                        uint32_t rx_length,
                                        uint32_t timeout,
                                        uint32_t *response);

/* Function: socfpga_i3c_ll_get_status
 *
 * Reads the raw, unmasked Interrupt Status Register. This reveals the immediate 
 * physical state of the controller, indicating events such as Bus Errors, 
 * Hot-Join Requests, or FIFO thresholds.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 *
 * Returns:
 *
 * The raw 32-bit hardware status value.
 */
uint32_t socfpga_i3c_ll_get_status(uint32_t base_address);

/* Function: socfpga_i3c_ll_get_hw_capability
 *
 * Extracts the read-only synthesis parameters from the Hardware Capability 
 * register. This provides the driver with immutable IP block properties, such 
 * as the maximum supported DAT entries, FIFO depths, and HDR mode support.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 *
 * Returns:
 *
 * The 32-bit hardware capability identifier block.
 */
uint32_t socfpga_i3c_ll_get_hw_capability(uint32_t base_address);

/* Function: socfpga_i3c_ll_read_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from an arbitrary 
 * register offset within the I3C instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * offset       - The exact 32-bit aligned register offset.
 *
 * Returns:
 *
 * The raw 32-bit hardware value.
 *
 * Notes:
 *
 * This is an intentionally thin, lockless helper. It expects the caller to 
 * validate the address and offset.
 */
uint32_t socfpga_i3c_ll_read_reg(uint32_t base_address, uint32_t offset);

/* Function: socfpga_i3c_ll_write_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to an arbitrary 
 * register offset within the I3C instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I3C instance.
 * offset       - The exact 32-bit aligned register offset.
 * value        - The 32-bit data payload to commit.
 *
 * Returns:
 *
 * None.
 *
 * Notes:
 *
 * This is an intentionally thin, lockless helper. It expects the caller to 
 * validate the address and handle any required memory synchronization barriers.
 */
void socfpga_i3c_ll_write_reg(uint32_t base_address, uint32_t offset,
                              uint32_t value);

#endif /* SOCFPGA_I3C_LL_H */
