/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_noc_firewall.h
 *
 * NoC Firewall hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_NOC_FIREWALL_H
#define SOCFPGA_NOC_FIREWALL_H

#include <stdint.h>
#include "errno.h"
#include "socfpga_noc_firewall_reg.h"

/* Enum: socfpga_noc_firewall_target_t
 *
 * Identifies the specific hardware peripheral or interconnect bridge protected 
 * by the NoC Firewall. These targets correspond to individual security policy 
 * registers within the L4 interconnect that dictate whether a peripheral can 
 * be accessed by Non-Secure bus masters.
 *
 * Values:
 *
 * SOCFPGA_NOC_FW_I2C0          - Firewall target for I2C instance 0.
 * SOCFPGA_NOC_FW_I2C1          - Firewall target for I2C instance 1.
 * SOCFPGA_NOC_FW_I2C2          - Firewall target for I2C instance 2.
 * SOCFPGA_NOC_FW_I2C3          - Firewall target for I2C instance 3.
 * SOCFPGA_NOC_FW_I2C4          - Firewall target for I2C instance 4.
 * SOCFPGA_NOC_FW_I3C0          - Firewall target for I3C instance 0.
 * SOCFPGA_NOC_FW_I3C1          - Firewall target for I3C instance 1.
 * SOCFPGA_NOC_FW_UART0         - Firewall target for UART instance 0.
 * SOCFPGA_NOC_FW_UART1         - Firewall target for UART instance 1.
 * SOCFPGA_NOC_FW_DMA0          - Firewall target for DMA controller 0.
 * SOCFPGA_NOC_FW_DMA1          - Firewall target for DMA controller 1.
 * SOCFPGA_NOC_FW_SOC2FPGA      - Firewall target for the primary HPS-to-FPGA bridge.
 * SOCFPGA_NOC_FW_LWSOC2FPGA    - Firewall target for the Lightweight HPS-to-FPGA bridge.
 * SOCFPGA_NOC_FW_L4_NOC_PROBES - Firewall target for the interconnect diagnostic probes.
 * SOCFPGA_NOC_FW_TCU           - Firewall target for the Translation Control Unit.
 */
typedef enum {
    SOCFPGA_NOC_FW_I2C0 = NOC_FW_TARGET_I2C0,
    SOCFPGA_NOC_FW_I2C1 = NOC_FW_TARGET_I2C1,
    SOCFPGA_NOC_FW_I2C2 = NOC_FW_TARGET_I2C2,
    SOCFPGA_NOC_FW_I2C3 = NOC_FW_TARGET_I2C3,
    SOCFPGA_NOC_FW_I2C4 = NOC_FW_TARGET_I2C4,
    SOCFPGA_NOC_FW_I3C0 = NOC_FW_TARGET_I3C0,
    SOCFPGA_NOC_FW_I3C1 = NOC_FW_TARGET_I3C1,
    SOCFPGA_NOC_FW_UART0 = NOC_FW_TARGET_UART0,
    SOCFPGA_NOC_FW_UART1 = NOC_FW_TARGET_UART1,
    SOCFPGA_NOC_FW_DMA0 = NOC_FW_TARGET_DMA0,
    SOCFPGA_NOC_FW_DMA1 = NOC_FW_TARGET_DMA1,
    SOCFPGA_NOC_FW_SOC2FPGA = NOC_FW_TARGET_SOC2FPGA,
    SOCFPGA_NOC_FW_LWSOC2FPGA = NOC_FW_TARGET_LWSOC2FPGA,
    SOCFPGA_NOC_FW_L4_NOC_PROBES = NOC_FW_TARGET_L4_NOC_PROBES,
    SOCFPGA_NOC_FW_TCU = NOC_FW_TARGET_TCU
} socfpga_noc_firewall_target_t;


/* Function: socfpga_noc_firewall_get
 *
 * Reads the current ARM TrustZone security policy configured for a specific 
 * peripheral firewall target.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC Firewall block.
 * target       - The specific peripheral firewall register to query.
 * value        - Pointer to store the 32-bit policy value (e.g., indicating 
 * whether Secure, Non-Secure, or both accesses are permitted).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the target is invalid or the pointer is NULL.
 */
int32_t socfpga_noc_firewall_get(uint32_t base_address,
                                 socfpga_noc_firewall_target_t target,
                                 uint32_t *value);

/* Function: socfpga_noc_firewall_set
 *
 * Enforces a new ARM TrustZone security policy for a specific peripheral 
 * firewall target. This dictates how the interconnect responds to transactions 
 * based on their AxPROT (protection) bus signals.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC Firewall block.
 * target       - The specific peripheral firewall register to configure.
 * value        - The 32-bit policy payload to write to the register.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the target is invalid.
 */
int32_t socfpga_noc_firewall_set(uint32_t base_address,
                                 socfpga_noc_firewall_target_t target,
                                 uint32_t value);

/* Function: socfpga_noc_firewall_read_reg
 *
 * Performs a direct, absolute offset read within the NoC Firewall MMIO space. 
 * This is primarily intended for driver diagnostics or reading interconnect 
 * status registers not explicitly mapped by the target enum.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC Firewall block.
 * offset       - The exact 32-bit aligned register offset to read.
 * value        - Pointer to store the resulting 32-bit hardware value.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the pointer is NULL.
 */
int32_t socfpga_noc_firewall_read_reg(uint32_t base_address, uint32_t offset,
                                      uint32_t *value);

/* Function: socfpga_noc_firewall_write_reg
 *
 * Performs a direct, absolute offset write within the NoC Firewall MMIO space. 
 * This is primarily intended for driver diagnostics or initializing global 
 * firewall control registers.
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC Firewall block.
 * offset       - The exact 32-bit aligned register offset to write.
 * value        - The 32-bit data payload to commit to the hardware.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_noc_firewall_write_reg(uint32_t base_address, uint32_t offset,
                                       uint32_t value);

/* Function: socfpga_noc_firewall_allow_nonsecure
 *
 * A specialized macro-level helper that configures the target firewall to allow 
 * Non-Secure bus transactions. By default, peripherals boot in Secure-Only mode. 
 * This function clears the secure-access restrictions, effectively handing 
 * ownership of the peripheral over to Non-Secure operating systems (like U-Boot 
 * or Linux operating in EL1/EL2).
 *
 * Parameters:
 *
 * base_address - The base MMIO address of the target NoC Firewall block.
 * target       - The specific peripheral firewall to unlock.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the target is invalid.
 */
int32_t socfpga_noc_firewall_allow_nonsecure(uint32_t base_address,
                                             socfpga_noc_firewall_target_t target);

#endif /* SOCFPGA_NOC_FIREWALL_H */
