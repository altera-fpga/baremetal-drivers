/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge.h
 *
 * Bridge hardware abstraction driver interface for the SoCFPGA bare-metal 
 * software stack.
 *
 * This header provides legacy, static entry points for controlling the four 
 * primary AXI interconnect bridges that connect the HPS and the FPGA fabric.
 *
 * Note: New development should utilize the handle-based APIs found in 
 * `bridge_api.h`, as those interfaces support advanced features like routing 
 * configuration, flow-control handshaking, and multi-threaded state management.
 *
 */

#ifndef __SOCFPGA_BRIDGE_H__
#define __SOCFPGA_BRIDGE_H__

#include <stdint.h>
#include "errno.h"

/* Function: enable_hps2fpga_bridge
 *
 * Enables the HPS-to-FPGA (AXI) master bridge.
 *
 * This bridge provides the HPS with high-bandwidth, memory-mapped access to 
 * the FPGA fabric. It is typically used for large-scale data transfers and 
 * high-speed communication from the HPS to FPGA-based custom IP cores. 
 * Enabling this bridge activates the AXI master ports and allows transactions 
 * from the HPS interconnect into the FPGA memory space.
 *
 * Returns:
 *
 * 0 on success; -EIO if the Secure Interface Platform (SiP) call to the 
 * Trusted Firmware/SDM layer fails.
 */
int32_t enable_hps2fpga_bridge(void);

/* Function: disable_hps2fpga_bridge
 *
 * Disables the HPS-to-FPGA (AXI) master bridge.
 *
 * Disabling this bridge effectively isolates the FPGA from HPS-originated 
 * traffic. This is a critical step during FPGA reconfiguration to prevent 
 * illegal bus transactions while the FPGA fabric is inactive or resetting.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t disable_hps2fpga_bridge(void);

/* Function: enable_lwhps2fpga_bridge
 *
 * Enables the Light-Weight (LW) HPS-to-FPGA bridge.
 *
 * Unlike the standard HPS2FPGA bridge, this interface is optimized for low-bandwidth, 
 * latency-sensitive control-plane traffic. It is the primary path for the HPS 
 * to access FPGA-based configuration registers, status bits, and control 
 * state machines. 
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t enable_lwhps2fpga_bridge(void);

/* Function: disable_lwhps2fpga_bridge
 *
 * Disables the Light-Weight (LW) HPS-to-FPGA bridge.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t disable_lwhps2fpga_bridge(void);

/* Function: enable_fpga2hps_bridge
 *
 * Enables the FPGA-to-HPS bridge.
 *
 * This slave bridge allows FPGA-based masters (such as accelerators or 
 * custom DMA engines) to initiate transactions directed toward the HPS 
 * memory map, including peripheral registers and system-level status blocks.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t enable_fpga2hps_bridge(void);

/* Function: disable_fpga2hps_bridge
 *
 * Disables the FPGA-to-HPS bridge.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t disable_fpga2hps_bridge(void);

/* Function: enable_fpga2sdram_bridge
 *
 * Enables the FPGA-to-SDRAM bridge.
 *
 * This provides the FPGA fabric with high-performance, low-latency access 
 * directly to the HPS DDR controller. This bridge bypasses the standard 
 * system interconnect, providing a direct pipeline for massive data movement, 
 * essential for high-throughput applications like frame buffers or signal 
 * processing chains.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t enable_fpga2sdram_bridge(void);

/* Function: disable_fpga2sdram_bridge
 *
 * Disables the FPGA-to-SDRAM bridge.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SiP call fails.
 */
int32_t disable_fpga2sdram_bridge(void);

#endif /* __SOCFPGA_BRIDGE_H__ */
