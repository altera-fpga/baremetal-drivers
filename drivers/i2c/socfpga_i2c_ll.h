/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_i2c_ll.h
 *
 * I2C low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_I2C_LL_H
#define SOCFPGA_I2C_LL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "errno.h"

#include "mmio.h"

/* Constant: SOCFPGA_I2C_DEFAULT_TIMEOUT
 * The standard active-polling limit in microseconds for low-level synchronous 
 * FIFO and status operations before yielding a hardware timeout fault.
 */
#define SOCFPGA_I2C_DEFAULT_TIMEOUT 100000U

/* Constant: SOCFPGA_I2C_FALLBACK_SPINS_PER_US
 * Loop bound used in place of a microsecond deadline when CNTFRQ_EL0 reads zero, 
 * which happens in host unit builds and during pre-PLL bring-up.
 */
#define SOCFPGA_I2C_FALLBACK_SPINS_PER_US 32U

/* Constants: I2C speed modes
 *
 * Speed class chosen from the requested bus rate. The SCL counts and
 * the controller speed field are set from this class.
 *
 * SOCFPGA_I2C_SPEED_STANDARD - Standard mode, 100 kbit/s. Chosen when
 *                              the bus rate is at most 100000 Hz.
 * SOCFPGA_I2C_SPEED_FAST     - Fast mode, 400 kbit/s. Chosen when the
 *                              bus rate is above 100000 Hz and at most
 *                              400000 Hz.
 * SOCFPGA_I2C_SPEED_FASTPLUS - Fast-mode Plus, 1000 kbit/s. Chosen when
 *                              the bus rate is above 400000 Hz.
 */
#define SOCFPGA_I2C_SPEED_STANDARD 1U /* 100 kbit/s */
#define SOCFPGA_I2C_SPEED_FAST     2U /* 400 kbit/s */
#define SOCFPGA_I2C_SPEED_FASTPLUS 3U /* 1000 kbit/s (1 Mbit/s) */

/* Function: socfpga_i2c_ll_probe_controller
 *
 * Reads IC_COMP_TYPE to confirm a DesignWare I2C controller is present, clocked 
 * and out of reset at the supplied base address. This distinguishes an absent or 
 * unclocked instance from a healthy controller whose bus has no target on it.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * version      - Optional output for the IC_COMP_VERSION value; may be NULL.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a null base address, or -ENODEV when the component 
 * signature does not match.
 */
int32_t socfpga_i2c_ll_probe_controller(uint32_t base_address,
                                        uint32_t *version);

/* Function: socfpga_i2c_ll_get_fifo_depth
 *
 * Reads the synthesis parameters in IC_COMP_PARAM_1 to report the TX and RX FIFO 
 * depths configured into this instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * tx_depth     - Optional output for the TX FIFO depth in bytes; may be NULL.
 * rx_depth     - Optional output for the RX FIFO depth in bytes; may be NULL.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a null base address.
 */
int32_t socfpga_i2c_ll_get_fifo_depth(uint32_t base_address,
                                      uint32_t *tx_depth, uint32_t *rx_depth);

/* Function: socfpga_i2c_ll_enable
 *
 * Directly manipulates the IC_ENABLE register to assert or deassert the primary 
 * enable bit of the I2C Master controller.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * enable       - true to enable the core logic and bus drivers; false to disable.
 * timeout      - Maximum time in microseconds to wait for the IC_ENABLE_STATUS 
 * register to reflect the change before aborting.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the hardware state machine fails to transition.
 */
int32_t socfpga_i2c_ll_enable(uint32_t base_address, bool enable,
                              uint32_t timeout);

/* Function: socfpga_i2c_ll_configure_master
 *
 * Configures the foundational operational mode of the I2C IP block. This writes 
 * to the IC_CON (Control) and IC_TAR (Target Address) registers to set the bus 
 * speed, addressing format, and RESTART capabilities. The controller must be 
 * disabled prior to calling this function.
 *
 * Parameters:
 *
 * base_address    - The physical MMIO base address of the target I2C instance.
 * target_address  - The 7-bit or 10-bit address of the slave device to communicate with.
 * speed_mode      - The SCL speed mode (1=Standard, 2=Fast, 3=Fast Plus).
 * ten_bit_address - true to configure the master for 10-bit addressing mode.
 * restart_enable  - true to allow the hardware to generate repeated START conditions.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_i2c_ll_configure_master(uint32_t base_address,
                                        uint16_t target_address,
                                        uint32_t speed_mode,
                                        bool ten_bit_address,
                                        bool restart_enable);

/* Function: socfpga_i2c_ll_set_scl_count
 *
 * Manually overrides the calculated hardware clock divisors for the Serial Clock 
 * (SCL) line. This writes directly to the IC_SS_SCL_HCNT/LCNT or IC_FS_SCL_HCNT/LCNT 
 * registers depending on the active speed mode.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * speed_mode   - The SCL speed mode currently targeted for adjustment.
 * high_count   - The number of `ic_clk` cycles the SCL line will remain high.
 * low_count    - The number of `ic_clk` cycles the SCL line will remain low.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a null base address or a zero count.
 */
int32_t socfpga_i2c_ll_set_scl_count(uint32_t base_address,
                                     uint32_t speed_mode,
                                     uint16_t high_count,
                                     uint16_t low_count);

/* Function: socfpga_i2c_ll_set_timing
 *
 * Derives and programs the SCL high/low counts and the SDA hold time for the 
 * requested bus frequency from the controller input clock. Without this the 
 * counts keep their synthesis reset values and the resulting SCL frequency is 
 * undefined. IC_CON is not touched; the resolved speed mode is reported through 
 * speed_mode so the caller can program IC_CON.SPEED to match.
 *
 * The count equations match the U-Boot and Linux DesignWare drivers:
 * SCL high = (HCNT + 3) * ic_clk period + fall time
 * SCL low  = (LCNT + 1) * ic_clk period - fall time + rise time
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * ic_clk_hz    - The controller input clock frequency in hertz.
 * bus_hz       - The requested SCL frequency in hertz.
 * speed_mode   - Output for the resulting <SOCFPGA_I2C_SPEED_STANDARD> class 
 * speed mode; may be NULL.
 *
 * Returns:
 *
 * 0 on success; -EINVAL when a clock or frequency is zero, or -ERANGE when the 
 * input clock is too slow to meet the timing minimums of the requested speed.
 */
int32_t socfpga_i2c_ll_set_timing(uint32_t base_address, uint32_t ic_clk_hz,
                                  uint32_t bus_hz, uint32_t *speed_mode);

/* Function: socfpga_i2c_ll_set_target_address
 *
 * Retargets the master at a different device without re-initializing the 
 * controller. IC_TAR is only writable while the controller is disabled, so this 
 * disables it, updates IC_TAR and IC_CON, and re-enables it.
 *
 * Parameters:
 *
 * base_address    - The physical MMIO base address of the target I2C instance.
 * target_address  - The 7-bit or 10-bit address of the device to address next.
 * ten_bit_address - true when target_address is a 10-bit address.
 * timeout         - Maximum time in microseconds for the disable/enable handshake.
 *
 * Returns:
 *
 * 0 on success; -EINVAL for a bad address, or -ETIMEDOUT on a stuck controller.
 */
int32_t socfpga_i2c_ll_set_target_address(uint32_t base_address,
                                          uint16_t target_address,
                                          bool ten_bit_address,
                                          uint32_t timeout);

/* Function: socfpga_i2c_ll_probe_address
 *
 * Performs a single-byte read against the currently programmed target address 
 * purely to observe whether the device acknowledges, which is the bus scan 
 * primitive behind i2cdetect. The byte read is discarded.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * timeout      - Maximum time in microseconds for the probe transaction.
 * abort_source - Optional output for IC_TX_ABRT_SOURCE on failure; may be NULL.
 *
 * Returns:
 *
 * 0 when the target acknowledges; -ENXIO when it does not; -ETIMEDOUT when the 
 * bus does not respond at all.
 */
int32_t socfpga_i2c_ll_probe_address(uint32_t base_address, uint32_t timeout,
                                     uint32_t *abort_source);

/* Function: socfpga_i2c_ll_recover_bus
 *
 * Attempts to return a wedged bus to idle. An in-flight transfer is cancelled 
 * with IC_ENABLE.ABORT, then the controller is cycled through disable and enable 
 * to flush both FIFOs and re-arm the master state machine.
 *
 * This recovers the controller, not the wire. A target holding SDA low needs SCL 
 * pulsed through pinmuxed GPIO, which this driver does not own.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * timeout      - Maximum time in microseconds for each recovery step.
 *
 * Returns:
 *
 * 0 when the bus returns to idle; -ETIMEDOUT when it stays busy.
 */
int32_t socfpga_i2c_ll_recover_bus(uint32_t base_address, uint32_t timeout);

/* Function: socfpga_i2c_ll_write_sync
 *
 * Orchestrates a low-level, polling-based write sequence. This function pushes 
 * data bytes into the Transmit (TX) FIFO by writing directly to the IC_DATA_CMD 
 * register, spin-polling the IC_STATUS register to avoid FIFO overflow, and 
 * waiting for the TX FIFO to fully drain.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * buffer       - Pointer to the payload buffer.
 * length       - Number of bytes to push to the TX FIFO.
 * timeout      - Maximum time in microseconds to wait for FIFO space or completion.
 * abort_source - Optional output for IC_TX_ABRT_SOURCE on failure; may be NULL. The 
 * register is cleared as it is read, so this is the only chance to capture it.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the bus hangs, or -EIO if a hardware NACK occurs.
 */
int32_t socfpga_i2c_ll_write_sync(uint32_t base_address, const uint8_t *buffer,
                                  size_t length, uint32_t timeout,
                                  uint32_t *abort_source);

/* Function: socfpga_i2c_ll_read_sync
 *
 * Orchestrates a low-level, polling-based read sequence. This function issues 
 * read requests by writing the CMD bit to the IC_DATA_CMD register. It then 
 * polls the IC_STATUS register to ensure the Receive (RX) FIFO is not empty 
 * before extracting the incoming bytes.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * buffer       - Pointer to the destination buffer.
 * length       - Number of bytes to read from the target.
 * timeout      - Maximum time in microseconds to wait for the RX FIFO to populate.
 * abort_source - Optional output for IC_TX_ABRT_SOURCE on failure; may be NULL.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT if the target fails to return the requested bytes.
 */
int32_t socfpga_i2c_ll_read_sync(uint32_t base_address, uint8_t *buffer,
                                 size_t length, uint32_t timeout,
                                 uint32_t *abort_source);

/* Function: socfpga_i2c_ll_write_then_read_sync
 *
 * Executes a raw, combined format transaction utilizing a hardware RESTART 
 * condition. 
 *
 * This function packs the TX phase into the IC_DATA_CMD register, sets the 
 * RESTART bit on the final TX byte, and seamlessly transitions into pushing 
 * read requests (CMD bit set) for the RX phase. This guarantees the bus is 
 * not relinquished between the write and read operations.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * tx_buffer    - Pointer to the data to transmit (e.g., register offset).
 * tx_length    - Number of bytes to transmit before the RESTART.
 * rx_buffer    - Pointer to the destination buffer for the incoming data.
 * rx_length    - Number of bytes to read after the RESTART.
 * timeout      - Maximum time in microseconds for the combined transaction.
 * abort_source - Optional output for IC_TX_ABRT_SOURCE on failure; may be NULL.
 *
 * Returns:
 *
 * 0 on success; -ETIMEDOUT or -EIO on bus failure.
 */
int32_t socfpga_i2c_ll_write_then_read_sync(uint32_t base_address,
                                            const uint8_t *tx_buffer,
                                            size_t tx_length,
                                            uint8_t *rx_buffer,
                                            size_t rx_length,
                                            uint32_t timeout,
                                            uint32_t *abort_source);

/* Function: socfpga_i2c_ll_get_status
 *
 * Samples the live IC_STATUS register. This provides immediate, physical hardware 
 * telemetry regarding Master Activity, TX/RX FIFO levels, and bus idleness.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 *
 * Returns:
 *
 * The raw 32-bit value of the IC_STATUS register.
 */
uint32_t socfpga_i2c_ll_get_status(uint32_t base_address);

/* Function: socfpga_i2c_ll_get_intr_status
 *
 * Samples the IC_INTR_STAT register. This identifies which internal hardware 
 * events (e.g., TX_ABRT, RX_FULL, TX_EMPTY) are currently active and unmasked, 
 * signaling the need for software intervention.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 *
 * Returns:
 *
 * The raw 32-bit value representing the active interrupts.
 */
uint32_t socfpga_i2c_ll_get_intr_status(uint32_t base_address);

/* Function: socfpga_i2c_ll_get_tx_abort_source
 *
 * Reads the IC_TX_ABRT_SOURCE register. If an operation fails (indicated by the 
 * TX_ABRT interrupt), this register provides the specific root cause, such as 
 * a 7-bit Address NACK, Data NACK, or Arbitration Lost.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 *
 * Returns:
 *
 * The raw 32-bit diagnostic value containing the abort flags.
 */
uint32_t socfpga_i2c_ll_get_tx_abort_source(uint32_t base_address);

/* Function: socfpga_i2c_ll_abort_to_errno
 *
 * Translates an IC_TX_ABRT_SOURCE bitmap into the errno that describes it, so
 * every caller reports an absent target, a data NACK, lost arbitration and a
 * protocol error the same way.
 *
 * Parameters:
 *
 * abort_source - A value read from IC_TX_ABRT_SOURCE.
 *
 * Returns:
 *
 * -ENXIO for an address NACK, -EIO for a data NACK, -EAGAIN for lost
 * arbitration, or -EPROTO for a request the current IC_CON forbids.
 */
int32_t socfpga_i2c_ll_abort_to_errno(uint32_t abort_source);

/* Function: socfpga_i2c_ll_mask_all_interrupts
 *
 * Writes 0x0 to the IC_INTR_MASK register, effectively silencing all hardware 
 * interrupt generation from this I2C instance to the system GIC.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 *
 * Returns:
 *
 * None.
 */
void socfpga_i2c_ll_mask_all_interrupts(uint32_t base_address);

/* Function: socfpga_i2c_ll_clear_interrupts
 *
 * Performs a dummy read of the IC_CLR_INTR register. By hardware design, reading 
 * this specific register automatically clears all combined and individual software-
 * clearable interrupts across the IP block.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 *
 * Returns:
 *
 * None.
 */
void socfpga_i2c_ll_clear_interrupts(uint32_t base_address);

/* Function: socfpga_i2c_ll_read_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from an arbitrary 
 * register offset within the I2C instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * offset       - The exact 32-bit aligned register offset to read.
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
uint32_t socfpga_i2c_ll_read_reg(uint32_t base_address, uint32_t offset);

/* Function: socfpga_i2c_ll_write_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to an arbitrary 
 * register offset within the I2C instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target I2C instance.
 * offset       - The exact 32-bit aligned register offset to write.
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
void socfpga_i2c_ll_write_reg(uint32_t base_address, uint32_t offset,
                              uint32_t value);

#endif /* SOCFPGA_I2C_LL_H */
