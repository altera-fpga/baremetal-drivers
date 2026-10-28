/*
 * Copyright (c) 2024, Altera Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Ported to the SoCFPGA bare-metal software stack from arm-trusted-firmware
 * (plat/intel/soc/agilex5/include/agilex5_ddr.h). Platform dependencies are
 * satisfied by ddr_platform_compat.h.
 */

/* File: socfpga_ddr.h
 *
 * Public types for the bare-metal DDR driver, and the ddr_init() entry point.
 */
#ifndef SOCFPGA_DDR_H
#define SOCFPGA_DDR_H

#include <stdint.h>
#include <stdio.h>

#include "ddr_platform_compat.h"

/* Constants: DRAM bank count
 *
 * How many DRAM banks the driver records.
 *
 * CONFIG_NR_DRAM_BANKS - Value 1. Size of the bank table filled by ddr_init().
 */
#define CONFIG_NR_DRAM_BANKS	1

/* Type: phys_addr_t
 *
 * A physical address. Stored as an unsigned long long.
 */
typedef unsigned long long phys_addr_t;

/* Type: phys_size_t
 *
 * A memory size, in bytes. Stored as an unsigned long long.
 */
typedef unsigned long long phys_size_t;

/* Type: fdt_addr_t
 *
 * An address. This is another name for phys_addr_t.
 */
typedef phys_addr_t fdt_addr_t;

/* Struct: ddr_info
 *
 * One DRAM bank. ddr_init() fills bank 0.
 *
 * start - First byte of the bank. Bring-up stores DRAM_BASE here.
 * size  - Length of the bank, in bytes. Bring-up stores the size reported by the controller.
 */
struct ddr_info {
	phys_addr_t start;
	phys_size_t size;
};

/* Function: ddr_init
 *
 * Entry point for DDR setup. Examples and application code call this.
 *
 * On an Agilex 5 OCRAM build, runs bring-up with DDR_PLATFORM_CONFIG
 * as the handoff ddr_config value. On any other build, returns 0 and
 * does not program the controller.
 *
 * Returns:
 *   0 on success, or a negative error code from bring-up.
 */
int ddr_init(void);

#endif /* SOCFPGA_DDR_H */
