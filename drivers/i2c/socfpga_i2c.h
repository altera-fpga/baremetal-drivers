/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_i2c.h
 *
 * I2C hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_I2C_H
#define SOCFPGA_I2C_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

#include "socfpga_i2c_ll.h"
#include "socfpga_rst_mngr.h"

/* Constant: SOCFPGA_I2C_RESET_NONE
 * A sentinel value passed to the configuration structure to indicate that the 
 * driver should bypass interacting with the Reset Manager during initialization.
 */
#define SOCFPGA_I2C_RESET_NONE 0xFFFFFFFFU


struct socfpga_i2c_descriptor;

/* Type: socfpga_i2c_handle_t
 *
 * An opaque software handle representing an active connection to an I2C Master 
 * hardware instance. It encapsulates the MMIO base address, active buffer pointers, 
 * transaction state machines, and remaining byte counts.
 */
typedef struct socfpga_i2c_descriptor *socfpga_i2c_handle_t;

/* Type: socfpga_i2c_callback_t
 *
 * Function signature invoked by the I2C Interrupt Service Routine (ISR) when 
 * an asynchronous background transfer completes or encounters a fatal bus fault 
 * (e.g., Target NACK or Arbitration Lost).
 *
 * Parameters:
 *
 * handle  - The active I2C instance handle.
 * status  - Hardware completion status (0 for success, negative for bus faults).
 * context - Opaque user pointer passed back to the caller.
 */
typedef void (*socfpga_i2c_callback_t)(socfpga_i2c_handle_t handle,
                                       int32_t status, void *context);

/* Struct: socfpga_i2c_config_t
 *
 * Defines the initial hardware state and timing parameters for the I2C controller.
 */
typedef struct {
    uint32_t base_address;    /* The MMIO base address of the I2C controller. */
    uint16_t target_address;  /* The default 7-bit or 10-bit address of the slave device to communicate with. */
    uint32_t speed_mode;      /* The SCL speed mode (Standard, Fast, or Fast Plus). Ignored when bus_hz is set. */
    uint32_t bus_hz;          /* Requested SCL frequency in hertz (0 to derive it from speed_mode). */
    uint32_t input_clock_hz;  /* Controller input clock in hertz (0 to query the Clock Manager). */
    uint32_t timeout;         /* Bus timeout in microseconds for polling loops. */
    uint32_t reset_id;        /* The Reset Manager peripheral ID (or <SOCFPGA_I2C_RESET_NONE>). */
    uint16_t scl_high_count;  /* Optional manual override for the SCL High Clock Count register (0 to calculate it). */
    uint16_t scl_low_count;   /* Optional manual override for the SCL Low Clock Count register. */
    bool ten_bit_address;     /* True to configure the master for 10-bit addressing mode. */
    bool restart_enable;      /* True to allow the hardware to generate repeated START conditions. */
} socfpga_i2c_config_t;

/* Struct: socfpga_i2c_info_t
 *
 * Reports what the driver established about a controller during initialization.
 */
typedef struct {
    uint32_t component_version; /* IC_COMP_VERSION signature of the instance. */
    uint32_t input_clock_hz;    /* Input clock the SCL counts were derived from. */
    uint32_t bus_hz;            /* Requested SCL frequency. */
    uint32_t speed_mode;        /* Resulting speed mode class. */
    uint32_t scl_high_count;    /* Programmed SCL high count. */
    uint32_t scl_low_count;     /* Programmed SCL low count. */
    uint32_t tx_fifo_depth;     /* TX FIFO depth reported by IC_COMP_PARAM_1. */
    uint32_t rx_fifo_depth;     /* RX FIFO depth reported by IC_COMP_PARAM_1. */
} socfpga_i2c_info_t;


/* Function: socfpga_i2c_init
 *
 * Initializes the I2C Master controller. This un-gates the peripheral clock, 
 * cycles the hardware reset line via the Reset Manager, and configures the 
 * IC_CON (Control) and IC_TAR (Target Address) registers based on the provided 
 * parameters.
 *
 * Parameters:
 *
 * config - Pointer to the hardware configuration parameters.
 * handle - Pointer to store the resulting opaque active instance handle.
 *
 * Returns:
 *
 * 0 on success; -EBUSY if no descriptor is free or the instance is already open;
 * -EINVAL for bad config; -ENODEV when no controller answers at base_address;
 * -ERANGE when the input clock cannot produce the requested bus frequency.
 */
int32_t socfpga_i2c_init(const socfpga_i2c_config_t *config,
                         socfpga_i2c_handle_t *handle);

/* Function: socfpga_i2c_get_info
 *
 * Reports the controller identity, input clock, programmed SCL counts and FIFO
 * depths established at initialization. Useful for bring-up, where the question
 * is usually whether the controller is reachable and clocked at all.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * info   - Output storage for the controller description.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a NULL handle or output pointer.
 */
int32_t socfpga_i2c_get_info(socfpga_i2c_handle_t handle,
                             socfpga_i2c_info_t *info);

/* Function: socfpga_i2c_set_target_address
 *
 * Retargets an open handle at a different device address without tearing down
 * and re-initializing the controller.
 *
 * Parameters:
 *
 * handle         - The active I2C instance handle.
 * target_address - The 7-bit or 10-bit address to address next.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a bad handle or address; -EBUSY during a transfer.
 */
int32_t socfpga_i2c_set_target_address(socfpga_i2c_handle_t handle,
                                      uint16_t target_address);

/* Function: socfpga_i2c_probe
 *
 * Addresses a device and reports whether it acknowledges, without interpreting
 * any data it returns. This is the primitive a bus scan is built from.
 *
 * The handle is left targeting target_address, so a scan does not have to restore
 * the previous target between probes.
 *
 * Parameters:
 *
 * handle         - The active I2C instance handle.
 * target_address - The 7-bit or 10-bit address to test.
 *
 * Returns:
 *
 * 0 when the device acknowledges; -ENXIO when it does not; -ETIMEDOUT when the
 * bus itself does not respond.
 */
int32_t socfpga_i2c_probe(socfpga_i2c_handle_t handle, uint16_t target_address);

/* Function: socfpga_i2c_recover_bus
 *
 * Cancels any in-flight transfer, flushes both FIFOs and returns the master to
 * idle after a transfer left the bus wedged.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 *
 * Returns:
 *
 * 0 when the bus returns to idle; -ETIMEDOUT when it stays busy.
 */
int32_t socfpga_i2c_recover_bus(socfpga_i2c_handle_t handle);

/* Function: socfpga_i2c_get_abort_source
 *
 * Returns the IC_TX_ABRT_SOURCE value captured from the most recent failed
 * transfer, so a caller can distinguish an address NACK from a data NACK, lost
 * arbitration, or a protocol error.
 *
 * The value is latched by the transfer itself because reading IC_CLR_TX_ABRT to
 * release the TX FIFO also clears the source register.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * source - Output storage for the abort source bitmap.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a NULL handle or output pointer.
 */
int32_t socfpga_i2c_get_abort_source(socfpga_i2c_handle_t handle,
                                    uint32_t *source);

/* Constant: SOCFPGA_I2C_ABORT_ADDR_NACK
 * Mirrors the IC_TX_ABRT_SOURCE bit that reports a 7-bit address going 
 * unacknowledged, so an application can test for an absent device without 
 * including the register header.
 */
#define SOCFPGA_I2C_ABORT_ADDR_NACK 0x00000001U

/* Function: socfpga_i2c_abort_source_str
 *
 * Names the dominant cause in an IC_TX_ABRT_SOURCE value so a log line is
 * readable without a register reference. The flushed-byte count in the upper bits
 * is ignored.
 *
 * Parameters:
 *
 * source - A value obtained from <socfpga_i2c_get_abort_source>.
 *
 * Returns:
 *
 * A static string describing the cause, never NULL.
 */
const char *socfpga_i2c_abort_source_str(uint32_t source);

/* Function: socfpga_i2c_abort_flush_count
 *
 * Extracts the number of bytes the abort discarded from the TX FIFO, which tells
 * a caller how much of its payload never reached the bus.
 *
 * Parameters:
 *
 * source - A value obtained from <socfpga_i2c_get_abort_source>.
 *
 * Returns:
 *
 * The flushed byte count.
 */
uint32_t socfpga_i2c_abort_flush_count(uint32_t source);

/* Function: socfpga_i2c_deinit
 *
 * Safely halts the I2C Master controller. This masks all interrupts, disables 
 * the IP block (aborting any ongoing bus transactions), and frees the software 
 * descriptor memory.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle to shut down.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_deinit(socfpga_i2c_handle_t handle);

/* Function: socfpga_i2c_close
 *
 * Halts the I2C software context without asserting the physical hardware reset 
 * line or destroying the active bus configuration.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_close(socfpga_i2c_handle_t handle);

/* Function: socfpga_i2c_write_sync
 *
 * Executes a blocking write transaction. The driver formats the data and pushes 
 * it into the Transmit (TX) FIFO by writing to the IC_DATA_CMD register. It 
 * spin-polls the IC_STATUS register until the TX FIFO is empty and the bus 
 * returns to an idle state.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * buffer - Pointer to the byte array payload to transmit.
 * length - The number of bytes to push to the bus.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT or -EIO if the target NACKs the address or data.
 */
int32_t socfpga_i2c_write_sync(socfpga_i2c_handle_t handle,
                               const uint8_t *buffer, size_t length);

/* Function: socfpga_i2c_read_sync
 *
 * Executes a blocking read transaction. The driver issues read requests to the 
 * IC_DATA_CMD register (which drives the SCL line to clock data in from the target) 
 * and spin-polls the Receive (RX) FIFO to extract the incoming bytes.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * buffer - Pointer to the destination memory buffer.
 * length - The exact number of bytes to clock in from the target.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the target fails to supply data.
 */
int32_t socfpga_i2c_read_sync(socfpga_i2c_handle_t handle,
                              uint8_t *buffer, size_t length);

/* Function: socfpga_i2c_write_then_read_sync
 *
 * Executes a blocking, combined format transaction utilizing a repeated START 
 * condition. 
 *
 * This is the standard mechanism for reading from EEPROMs or I2C sensors: the 
 * master writes the internal register/memory address, issues a repeated START 
 * (preventing other masters from claiming the bus), and then immediately reads 
 * back the requested data payload.
 *
 * Parameters:
 *
 * handle    - The active I2C instance handle.
 * tx_buffer - Pointer to the data to transmit (usually the internal register address).
 * tx_length - Number of bytes to transmit.
 * rx_buffer - Pointer to the destination buffer for the incoming data.
 * rx_length - Number of bytes to clock in from the target.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_write_then_read_sync(socfpga_i2c_handle_t handle,
                                         const uint8_t *tx_buffer,
                                         size_t tx_length,
                                         uint8_t *rx_buffer,
                                         size_t rx_length);

/* Function: socfpga_i2c_write_async
 *
 * Initiates an interrupt-driven write transaction. The driver primes the TX FIFO 
 * and enables the TX_EMPTY interrupt mask before returning control to the caller.
 *
 * Parameters:
 *
 * handle   - The active I2C instance handle.
 * buffer   - Pointer to the payload. Must remain valid until the callback fires.
 * length   - Number of bytes to transmit.
 * callback - Function to invoke upon completion or fault.
 * context  - Opaque user pointer passed back to the callback.
 *
 * Returns:
 *
 * 0 if the transfer successfully queues; -EBUSY if the controller is already active.
 */
int32_t socfpga_i2c_write_async(socfpga_i2c_handle_t handle,
                                const uint8_t *buffer, size_t length,
                                socfpga_i2c_callback_t callback,
                                void *context);

/* Function: socfpga_i2c_read_async
 *
 * Initiates an interrupt-driven read transaction. The driver pushes read requests 
 * to the command FIFO and enables the RX_FULL interrupt mask.
 *
 * Parameters:
 *
 * handle   - The active I2C instance handle.
 * buffer   - Pointer to the destination array. Must remain valid.
 * length   - Number of bytes to read.
 * callback - Function to invoke upon completion or fault.
 * context  - Opaque user pointer passed back to the callback.
 *
 * Returns:
 *
 * 0 if successfully queued.
 */
int32_t socfpga_i2c_read_async(socfpga_i2c_handle_t handle,
                               uint8_t *buffer, size_t length,
                               socfpga_i2c_callback_t callback,
                               void *context);

/* Function: socfpga_i2c_write_then_read_async
 *
 * Initiates an interrupt-driven, combined format transaction with a repeated START. 
 * The internal state machine handles the transition from pushing the TX phase 
 * to pulling the RX phase seamlessly in the background.
 *
 * Parameters:
 *
 * handle    - The active I2C instance handle.
 * tx_buffer - Pointer to the transmit payload.
 * tx_length - Number of bytes to transmit.
 * rx_buffer - Pointer to the receive buffer.
 * rx_length - Number of bytes to read.
 * callback  - Function to invoke upon completion.
 * context   - Opaque user pointer passed back to the callback.
 *
 * Returns:
 *
 * 0 if successfully queued.
 */
int32_t socfpga_i2c_write_then_read_async(socfpga_i2c_handle_t handle,
                                          const uint8_t *tx_buffer,
                                          size_t tx_length,
                                          uint8_t *rx_buffer,
                                          size_t rx_length,
                                          socfpga_i2c_callback_t callback,
                                          void *context);

/* Function: socfpga_i2c_isr
 *
 * The primary Interrupt Service Routine for the I2C controller. This function 
 * reads the IC_INTR_STAT register, manages the TX/RX FIFOs, and handles fatal 
 * errors (TX_ABRT). It invokes user callbacks when background state machines 
 * reach terminal states.
 *
 * Parameters:
 *
 * param - The opaque <socfpga_i2c_handle_t> context passed from the Exception vector.
 */
void socfpga_i2c_isr(void *param);

/* Function: socfpga_i2c_wait_async_complete
 *
 * Drives an outstanding asynchronous transfer to completion by servicing the 
 * controller from the calling context, so the asynchronous engine can be used on 
 * a system that has not routed the I2C interrupt to the GIC.
 *
 * This does not prove interrupt delivery; it exercises the same state machine the 
 * ISR runs.
 *
 * Parameters:
 *
 * handle  - The active I2C instance handle.
 * timeout - Maximum time in microseconds to wait, or 0 to use the handle's own.
 *
 * Returns:
 *
 * 0 once no transfer is outstanding; -ETIMEDOUT if one is still in flight. The 
 * transfer's own status is reported through its completion callback.
 */
int32_t socfpga_i2c_wait_async_complete(socfpga_i2c_handle_t handle,
                                       uint32_t timeout);

/* Function: socfpga_i2c_get_status
 *
 * Queries the hardware IC_STATUS register to provide the live, physical state 
 * of the controller (e.g., Master Activity, RX FIFO Not Empty, TX FIFO Completely 
 * Empty).
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * status - Pointer to store the raw 32-bit status register value.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_get_status(socfpga_i2c_handle_t handle, uint32_t *status);

/* Function: socfpga_i2c_read_reg
 *
 * Performs a direct, absolute offset read within the I2C MMIO space. 
 * Intended for diagnostics and low-level hardware debugging.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * offset - The specific 32-bit aligned register offset to read.
 * value  - Pointer to store the retrieved value.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_read_reg(socfpga_i2c_handle_t handle, uint32_t offset,
                             uint32_t *value);

/* Function: socfpga_i2c_write_reg
 *
 * Performs a direct, absolute offset write within the I2C MMIO space.
 *
 * Parameters:
 *
 * handle - The active I2C instance handle.
 * offset - The specific 32-bit aligned register offset to write.
 * value  - The 32-bit data payload to commit.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_write_reg(socfpga_i2c_handle_t handle, uint32_t offset,
                              uint32_t value);

#endif /* SOCFPGA_I2C_H */
