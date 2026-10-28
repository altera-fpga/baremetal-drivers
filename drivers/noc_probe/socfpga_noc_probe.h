/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_noc_probe.h
 *
 * NoC Probe hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_NOC_PROBE_H
#define SOCFPGA_NOC_PROBE_H

#include <stdbool.h>
#include <stdint.h>
#include "errno.h"

/* Enum: socfpga_noc_probe_block_t
 *
 * Identifies the specific hardware subsystem or bridge targeted by the NoC Probe. 
 * The System-on-Chip interconnect uses distributed probes to monitor distinct 
 * traffic domains independently.
 *
 * Values:
 *
 * SOCFPGA_NOC_PROBE_CCU      - Cache Coherent Unit. Monitors MPU/CPU cluster traffic.
 * SOCFPGA_NOC_PROBE_SOC2FPGA - HPS-to-FPGA bridge. Monitors transactions crossing into the fabric.
 * SOCFPGA_NOC_PROBE_IO       - General IO block. Monitors standard peripheral traffic.
 */
typedef enum {
    SOCFPGA_NOC_PROBE_CCU = 0U,
    SOCFPGA_NOC_PROBE_SOC2FPGA = 2U,
    SOCFPGA_NOC_PROBE_IO = 3U
} socfpga_noc_probe_block_t;

/* Struct: socfpga_noc_probe_error_log_t
 *
 * A raw capture of the Network-on-Chip error logging registers. When the NoC 
 * detects a firewall violation or unmapped address decode fault, it freezes 
 * the offending AXI transaction packet header into these registers for software 
 * diagnosis.
 *
 * The fields map directly to the hardware ERRLOG registers, which contain 
 * packet metadata such as the exact AXI Address, Burst Length, Transaction ID, 
 * Opcode, and Route ID.
 */
typedef struct {
    uint32_t errlog0; /* Target Address [31:0] */
    uint32_t errlog1; /* Target Address [63:32] (if applicable) */
    uint32_t errlog3; /* Transaction Opcode and Size */
    uint32_t errlog4; /* Route ID / Source Master ID */
    uint32_t errlog5; /* Security/Privilege attributes (AxPROT) */
    uint32_t errlog6; /* AXI Burst type and length */
    uint32_t errlog7; /* Advanced QoS or interconnect-specific flags */
} socfpga_noc_probe_error_log_t;


/* Function: socfpga_noc_probe_read_id
 *
 * Performs a diagnostic read of the NoC Probe's Core ID register. This is used 
 * to verify that the target IP block is present on the bus, clocked, and out 
 * of reset before attempting further configuration.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC probe instance.
 * core_id      - Pointer to store the 32-bit hardware identification code.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL.
 */
int32_t socfpga_noc_probe_read_id(uint32_t base_address, uint32_t *core_id);

/* Function: socfpga_noc_probe_error_logger_enable
 *
 * Configures the Main Control register of the NoC probe to arm or disarm the 
 * error capture hardware. When enabled, the probe actively snoops AXI traffic 
 * and will latch the first faulted packet it encounters into the ERRLOG registers.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 * enable       - true to arm the error logger; false to bypass.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_noc_probe_error_logger_enable(uint32_t base_address,
                                              bool enable);

/* Function: socfpga_noc_probe_error_is_valid
 *
 * Reads the Main Status register to determine if the hardware has trapped a 
 * faulted packet. If the valid bit is set, the ERRLOG registers contain frozen, 
 * uncorrupted data about the failing transaction.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 * valid        - Pointer to a boolean that will be set to true if an error 
 * is currently latched by the hardware.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL.
 */
int32_t socfpga_noc_probe_error_is_valid(uint32_t base_address, bool *valid);

/* Function: socfpga_noc_probe_error_read
 *
 * Extracts the complete frozen packet header from the ERRLOG registers. This 
 * should only be called after <socfpga_noc_probe_error_is_valid> confirms a 
 * fault has been trapped.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 * log          - Pointer to the struct where the raw register contents will be written.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL.
 */
int32_t socfpga_noc_probe_error_read(uint32_t base_address,
                                     socfpga_noc_probe_error_log_t *log);

/* Function: socfpga_noc_probe_error_clear
 *
 * Clears the valid latch in the Main Status register. This acknowledges the 
 * current fault to the hardware, clearing the ERRLOG registers and re-arming 
 * the probe to capture the next interconnect error.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_noc_probe_error_clear(uint32_t base_address);

/* Function: socfpga_noc_probe_counter_set_source
 *
 * Multiplexes a specific interconnect event (such as byte transfer counts, 
 * idle cycles, or read/write transaction ticks) into one of the hardware's 
 * Performance Monitoring Unit (PMU) counters. 
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 * block        - The specific interconnect block to monitor.
 * counter      - The hardware index of the PMU counter to configure (e.g., 0, 1).
 * source       - The hardware-specific event mask or route ID to track.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the counter index or block is out of bounds.
 */
int32_t socfpga_noc_probe_counter_set_source(uint32_t base_address,
                                             socfpga_noc_probe_block_t block,
                                             uint32_t counter,
                                             uint32_t source);

/* Function: socfpga_noc_probe_counter_get_value
 *
 * Reads the live, accumulating value of the specified PMU counter. This is 
 * used to calculate bus utilization, bandwidth, or latency metrics over a 
 * specific software profiling window.
 *
 * Parameters:
 *
 * base_address - The MMIO base address of the target NoC probe instance.
 * block        - The specific interconnect block being monitored.
 * counter      - The hardware index of the active PMU counter.
 * value        - Pointer to store the current 32-bit tick/event count.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL or the counter index is invalid.
 */
int32_t socfpga_noc_probe_counter_get_value(uint32_t base_address,
                                            socfpga_noc_probe_block_t block,
                                            uint32_t counter,
                                            uint32_t *value);

#endif /* SOCFPGA_NOC_PROBE_H */
