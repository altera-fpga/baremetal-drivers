/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ccu.h
 *
 * Cache Coherency Unit (CCU) hardware abstraction driver interface for the 
 * SoCFPGA bare-metal software stack.
 *
 * The CCU manages the system-level interconnect cache, providing mechanisms 
 * to ensure data coherency between the HPS (Hard Processor System), the FPGA 
 * fabric, and the system memory (DDR). This driver facilitates the flushing of 
 * L3 system cache lines, the monitoring of interconnect error status, and 
 * raw register access for advanced diagnostic and configuration tasks.
 *
 */

#ifndef SOCFPGA_CCU_H
#define SOCFPGA_CCU_H

#include <stdint.h>
#include "errno.h"

/* Function: socfpga_ccu_get_id
 *
 * Retrieves the hardware peripheral identification and revision code from 
 * the CCU's component ID registers.
 *
 * This is primarily used during driver initialization to verify that the 
 * memory-mapped base address corresponds to the expected CCU hardware revision.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the CCU block.
 * id           - Pointer to store the 32-bit hardware identification value.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is null or the address is invalid.
 */
int32_t socfpga_ccu_get_id(uint32_t base_address, uint32_t *id);

/* Function: socfpga_ccu_get_error_status
 *
 * Reads the CCU Uncorrected Error Status register.
 *
 * This register tracks fatal interconnect fault events, such as bus protocol 
 * violations, slave access errors, or memory-mapped coherency faults. 
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the CCU block.
 * status       - Pointer to store the 32-bit error status bitmask.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is null.
 */
int32_t socfpga_ccu_get_error_status(uint32_t base_address, uint32_t *status);

/* Function: socfpga_ccu_flush_l3_cache
 *
 * Performs a global flush of the L3 system-memory cache entries.
 *
 * This function is critical for maintaining system coherency before DMA 
 * transfers or system resets. It iterates through the enabled DMI (Direct 
 * Memory Interface) ports, issuing maintenance commands to force data 
 * synchronization between the L3 cache and the underlying DDR memory.
 *
 * Parameters:
 *
 * base_address  - The physical MMIO base address of the CCU block.
 * timeout_polls - The maximum number of iterations to poll the hardware status 
 * register while waiting for the flush operation to confirm completion.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if input parameters are out of range; -ETIMEDOUT if 
 * the maintenance operation fails to acknowledge completion within the 
 * allotted polling count.
 */
int32_t socfpga_ccu_flush_l3_cache(uint32_t base_address, uint32_t timeout_polls);

/* Function: socfpga_ccu_read_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from an arbitrary 
 * register offset within the CCU instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the CCU block.
 * offset       - The 32-bit aligned register offset to query.
 * value        - Pointer to store the 32-bit hardware register value.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the provided pointer is null.
 */
int32_t socfpga_ccu_read_reg(uint32_t base_address, uint32_t offset, uint32_t *value);

/* Function: socfpga_ccu_write_reg
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to an arbitrary 
 * register offset within the CCU instance.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the CCU block.
 * offset       - The 32-bit aligned register offset.
 * value        - The 32-bit data payload to commit to the register.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_ccu_write_reg(uint32_t base_address, uint32_t offset, uint32_t value);

#endif /* SOCFPGA_CCU_H */
