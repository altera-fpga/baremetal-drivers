/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_i3c.h
 *
 * I3C hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_I3C_H
#define SOCFPGA_I3C_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

#include "socfpga_rst_mngr.h"

/* Constant: SOCFPGA_I3C_RESET_NONE
 * A sentinel value passed to the configuration structure to indicate that the 
 * driver should bypass interacting with the Reset Manager during initialization.
 */
#define SOCFPGA_I3C_RESET_NONE 0xFFFFFFFFU

/* Constant: SOCFPGA_I3C_MAX_DATA_WORDS
 * The maximum number of 32-bit words that can be pushed to or pulled from the 
 * hardware TX/RX FIFOs in a single contiguous burst.
 */
#define SOCFPGA_I3C_MAX_DATA_WORDS 64U

/* Constant: SOCFPGA_I3C_DEFAULT_TIMEOUT
 * The default polling threshold for synchronous operations before the driver 
 * assumes the I3C bus is hung or a target device is unresponsive.
 */
#define SOCFPGA_I3C_DEFAULT_TIMEOUT 1000000U


struct socfpga_i3c_descriptor;

/* Type: socfpga_i3c_handle_t
 *
 * An opaque software handle representing an active connection to an I3C Master 
 * hardware instance. It encapsulates the MMIO base address, active buffer pointers, 
 * and internal state machines necessary for handling asynchronous interrupts.
 */
typedef struct socfpga_i3c_descriptor *socfpga_i3c_handle_t;

/* Type: socfpga_i3c_callback_t
 *
 * Callback function signature invoked by the I3C Interrupt Service Routine (ISR) 
 * when an asynchronous transfer completes, or when the bus encounters a fault 
 * (such as a NACK or parity error).
 *
 * Parameters:
 *
 * handle  - The active I3C instance handle.
 * status  - The hardware completion status (0 for success, negative for faults).
 * context - An opaque user pointer registered during the async transfer request.
 */
typedef void (*socfpga_i3c_callback_t)(socfpga_i3c_handle_t handle,
                                       int32_t status, void *context);

/* Enum: socfpga_i3c_msg_type_t
 *
 * Defines the architectural message types pushed into the Command Queue (CQ). 
 * These dictate how the I3C Master hardware formats the bus transaction.
 *
 * Values:
 *
 * SOCFPGA_I3C_MSG_REGULAR                - Standard Private I3C or Legacy I2C transfer.
 * SOCFPGA_I3C_MSG_IMMEDIATE              - A high-priority transfer that bypasses standard queue scheduling.
 * SOCFPGA_I3C_MSG_ADDR_ASSIGN            - Broadcast ENTDAA (Enter Dynamic Address Assignment) command to assign 7-bit dynamic addresses to targets.
 * SOCFPGA_I3C_MSG_WRITE_FOLLOWED_BY_READ - A combined format transaction (e.g., writing a register address followed by a repeated START to read the value).
 * SOCFPGA_I3C_MSG_INTERNAL_CONTROL       - Internal driver command to manipulate the controller state rather than emitting bus traffic.
 */
typedef enum {
    SOCFPGA_I3C_MSG_REGULAR = 0U,
    SOCFPGA_I3C_MSG_IMMEDIATE = 1U,
    SOCFPGA_I3C_MSG_ADDR_ASSIGN = 2U,
    SOCFPGA_I3C_MSG_WRITE_FOLLOWED_BY_READ = 3U,
    SOCFPGA_I3C_MSG_INTERNAL_CONTROL = 7U
} socfpga_i3c_msg_type_t;

/* Struct: socfpga_i3c_config_t
 *
 * Initialization parameters for the I3C controller. This dictates the IP's 
 * behavior regarding legacy protocols and bus-management features.
 */
typedef struct {
    uint32_t base_address;             /* The MMIO base address of the I3C controller. */
    uint32_t reset_id;                 /* The Reset Manager peripheral ID (or <SOCFPGA_I3C_RESET_NONE>). */
    uint32_t timeout;                  /* Bus timeout threshold. */
    bool enable_i2c_compatibility;     /* If true, configures the SCL timing to accommodate legacy I2C devices on the same bus. */
    bool enable_hot_join;              /* If true, enables the hardware to ACK Hot-Join requests from newly attached I3C targets. */
} socfpga_i3c_config_t;

/* Struct: socfpga_i3c_transfer_t
 *
 * A raw hardware transfer descriptor. This structure maps directly to the 
 * physical Command, TX, and RX queues of the I3C controller.
 */
typedef struct {
    uint32_t command;          /* The formatted 32-bit descriptor for the Command Queue (CQ). */
    const uint32_t *tx_words;  /* Pointer to the data payload to push to the TX FIFO. */
    uint32_t tx_word_count;    /* Number of 32-bit words in the TX payload. */
    uint32_t *rx_words;        /* Pointer to the buffer to receive the RX FIFO data. */
    uint32_t rx_word_count;    /* Number of 32-bit words expected from the RX FIFO. */
    uint32_t response;         /* Output field populated with the hardware Response Queue (RQ) descriptor upon completion. */
} socfpga_i3c_transfer_t;


/* Function: socfpga_i3c_build_command
 *
 * Bitwise packs a 32-bit instruction for the I3C hardware Command Queue (CQ). 
 * This packs the transaction type, target device index, read/write direction, 
 * and interrupt policies into a single descriptor that the hardware state 
 * machine parses to drive the SCL/SDA lines.
 *
 * Parameters:
 *
 * msg_type               - The format of the message from <socfpga_i3c_msg_type_t>.
 * transaction_id         - An arbitrary tag (typically 0-255) returned in the Response Queue to match asynchronous completions.
 * command_code           - The specific CCC (Common Command Code) or transaction parameter.
 * device_index           - The hardware DAT (Device Address Table) index for the target.
 * write                  - True to assert a write transaction; false for a read.
 * response_on_completion - True to instruct the hardware to push a status word to the Response Queue when done.
 *
 * Returns:
 *
 * The fully formatted 32-bit Command Queue descriptor.
 */
uint32_t socfpga_i3c_build_command(uint32_t msg_type, uint32_t transaction_id,
                                   uint32_t command_code, uint32_t device_index,
                                   bool write, bool response_on_completion);

/* Function: socfpga_i3c_init
 *
 * Initializes the I3C Master controller. This un-gates the peripheral clock, 
 * optionally cycles the hardware reset line via the Reset Manager, initializes 
 * the Device Address Table (DAT), and configures the bus timing registers based 
 * on whether legacy I2C compatibility is required.
 *
 * Parameters:
 *
 * config - Pointer to the hardware configuration parameters.
 * handle - Pointer to store the resulting opaque active instance handle.
 *
 * Returns:
 *
 * 0 on success; -ENOMEM if descriptor allocation fails, or -EINVAL for bad config.
 */
int32_t socfpga_i3c_init(const socfpga_i3c_config_t *config,
                         socfpga_i3c_handle_t *handle);

/* Function: socfpga_i3c_deinit
 *
 * Disables the I3C Master controller and safely returns it to a reset state. 
 * This aborts any ongoing bus transactions, gates the clock, and frees the 
 * software handle.
 *
 * Parameters:
 *
 * handle - The active I3C instance handle to shut down.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_deinit(socfpga_i3c_handle_t handle);

/* Function: socfpga_i3c_close
 *
 * Halts the I3C software context without asserting the physical hardware reset 
 * line. This is useful if the controller state needs to be preserved for handoff 
 * to a subsequent boot stage (e.g., passing control from bare-metal to an OS).
 *
 * Parameters:
 *
 * handle - The active I3C instance handle.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_close(socfpga_i3c_handle_t handle);

/* Function: socfpga_i3c_transfer_sync
 *
 * Issues a low-level, raw transfer descriptor directly to the hardware FIFOs. 
 * The driver pushes the `command` word to the Command Queue, fills the TX FIFO 
 * if applicable, and then spin-polls the Response Queue and RX FIFO until the 
 * hardware signals completion or times out.
 *
 * Parameters:
 *
 * handle   - The active I3C instance handle.
 * transfer - Pointer to the transfer descriptor containing the pre-built command and buffers.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT or -EIO on bus errors (like NACKs).
 */
int32_t socfpga_i3c_transfer_sync(socfpga_i3c_handle_t handle,
                                  socfpga_i3c_transfer_t *transfer);

/* Function: socfpga_i3c_write_sync
 *
 * A specialized synchronous wrapper for raw Command Queue write operations. 
 * Pushes data to the TX FIFO and executes the provided command.
 *
 * Parameters:
 *
 * handle     - The active I3C instance handle.
 * data_words - Pointer to the 32-bit payload to transmit.
 * word_count - The number of 32-bit words to push.
 * command    - The pre-built Command Queue instruction.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_write_sync(socfpga_i3c_handle_t handle,
                               const uint32_t *data_words,
                               uint32_t word_count,
                               uint32_t command);

/* Function: socfpga_i3c_read_sync
 *
 * A specialized synchronous wrapper for raw Command Queue read operations. 
 * Executes the provided command and drains the resulting data from the RX FIFO.
 *
 * Parameters:
 *
 * handle     - The active I3C instance handle.
 * data_words - Pointer to the buffer to store incoming 32-bit words.
 * word_count - The number of 32-bit words to pull.
 * command    - The pre-built Command Queue instruction.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_read_sync(socfpga_i3c_handle_t handle,
                              uint32_t *data_words,
                              uint32_t word_count,
                              uint32_t command);

/* Function: socfpga_i3c_transfer_async
 *
 * Initiates an interrupt-driven bus transaction. The driver primes the TX FIFO 
 * and Command Queue, then immediately returns control to the caller. The internal 
 * ISR handles FIFO draining/filling and will invoke the provided callback when 
 * the Response Queue flags completion.
 *
 * Parameters:
 *
 * handle   - The active I3C instance handle.
 * transfer - Pointer to the transfer descriptor. Must remain valid in memory until the callback fires.
 * callback - The function pointer to invoke upon completion.
 * context  - Opaque user pointer passed back to the callback.
 *
 * Returns:
 *
 * 0 if successfully queued; -EBUSY if the controller is already occupied.
 */
int32_t socfpga_i3c_transfer_async(socfpga_i3c_handle_t handle,
                                   socfpga_i3c_transfer_t *transfer,
                                   socfpga_i3c_callback_t callback,
                                   void *context);

/* Function: socfpga_i3c_i2c_legacy_read
 *
 * Translates standard byte-oriented read requests into I3C hardware commands 
 * targeting a legacy I2C device. The controller automatically negotiates the 
 * bus speed down to standard/fast-mode limits required by I2C targets.
 *
 * Parameters:
 *
 * handle      - The active I3C instance handle.
 * i2c_address - The static 7-bit I2C device address.
 * buffer      - Pointer to store the read bytes.
 * length      - The number of bytes to read.
 * response    - Pointer to store the hardware Response Queue completion status.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_i2c_legacy_read(socfpga_i3c_handle_t handle,
                                    uint8_t i2c_address,
                                    uint8_t *buffer,
                                    uint32_t length,
                                    uint32_t *response);

/* Function: socfpga_i3c_i2c_legacy_write
 *
 * Translates standard byte-oriented write requests into I3C hardware commands 
 * targeting a legacy I2C device.
 *
 * Parameters:
 *
 * handle      - The active I3C instance handle.
 * i2c_address - The static 7-bit I2C device address.
 * buffer      - Pointer to the bytes to transmit.
 * length      - The number of bytes to transmit.
 * response    - Pointer to store the hardware Response Queue completion status.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_i2c_legacy_write(socfpga_i3c_handle_t handle,
                                     uint8_t i2c_address,
                                     const uint8_t *buffer,
                                     uint32_t length,
                                     uint32_t *response);

/* Function: socfpga_i3c_private_read
 *
 * Executes a high-speed Private I3C read. This uses the 7-bit Dynamic Address 
 * previously assigned to the target device during ENTDAA. The bus operates at 
 * full push-pull SDR (Single Data Rate) speeds.
 *
 * Parameters:
 *
 * handle          - The active I3C instance handle.
 * dynamic_address - The dynamically assigned 7-bit I3C target address.
 * buffer          - Pointer to store the read bytes.
 * length          - The number of bytes to read.
 * response        - Pointer to store the hardware Response Queue completion status.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_private_read(socfpga_i3c_handle_t handle,
                                 uint8_t dynamic_address,
                                 uint8_t *buffer,
                                 uint32_t length,
                                 uint32_t *response);

/* Function: socfpga_i3c_private_write
 *
 * Executes a high-speed Private I3C write using the 7-bit Dynamic Address.
 *
 * Parameters:
 *
 * handle          - The active I3C instance handle.
 * dynamic_address - The dynamically assigned 7-bit I3C target address.
 * buffer          - Pointer to the bytes to transmit.
 * length          - The number of bytes to transmit.
 * response        - Pointer to store the hardware Response Queue completion status.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_private_write(socfpga_i3c_handle_t handle,
                                  uint8_t dynamic_address,
                                  const uint8_t *buffer,
                                  uint32_t length,
                                  uint32_t *response);

/* Function: socfpga_i3c_isr
 *
 * The primary Interrupt Service Routine for the I3C controller. This function 
 * reads the Interrupt Status Register to determine the event (e.g., TX Buffer 
 * Empty, RX Buffer Full, Response Ready, or Bus Error). It drains/fills FIFOs 
 * for active async transfers and invokes user callbacks when operations complete.
 *
 * Parameters:
 *
 * param - The opaque <socfpga_i3c_handle_t> context passed from the OS/Exception vector.
 */
void socfpga_i3c_isr(void *param);

/* Function: socfpga_i3c_get_status
 *
 * Queries the controller's main Interrupt Status Register. This provides the 
 * raw, unmasked hardware status flags for diagnostic or polling purposes.
 *
 * Parameters:
 *
 * handle - The active I3C instance handle.
 * status - Pointer to store the 32-bit register state.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_get_status(socfpga_i3c_handle_t handle, uint32_t *status);

/* Function: socfpga_i3c_get_hw_capability
 *
 * Reads the read-only Hardware Capability Register baked into the IP block. 
 * This reveals physical synthesis parameters like FIFO depths, supported speed 
 * modes (HDR-DDR, HDR-TSP), and maximum addressable devices.
 *
 * Parameters:
 *
 * handle     - The active I3C instance handle.
 * capability - Pointer to store the 32-bit hardware parameter block.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_get_hw_capability(socfpga_i3c_handle_t handle,
                                      uint32_t *capability);

/* Function: socfpga_i3c_read_reg
 *
 * Performs a direct, absolute offset read within the I3C MMIO space. Intended 
 * for diagnostics and retrieving specialized configuration registers not 
 * otherwise abstracted by the driver.
 *
 * Parameters:
 *
 * handle - The active I3C instance handle.
 * offset - The specific 32-bit aligned register offset to read.
 * value  - Pointer to store the retrieved value.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_read_reg(socfpga_i3c_handle_t handle, uint32_t offset,
                             uint32_t *value);

/* Function: socfpga_i3c_write_reg
 *
 * Performs a direct, absolute offset write within the I3C MMIO space.
 *
 * Parameters:
 *
 * handle - The active I3C instance handle.
 * offset - The specific 32-bit aligned register offset to write.
 * value  - The 32-bit data payload to commit.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i3c_write_reg(socfpga_i3c_handle_t handle, uint32_t offset,
                              uint32_t value);

#endif /* SOCFPGA_I3C_H */
