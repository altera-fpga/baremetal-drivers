/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_rst_mngr.h
 *
 * Reset Manager hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_RST_MNGR_H__
#define __SOCFPGA_RST_MNGR_H__

#include <stdint.h>
#include "errno.h"

/* Enum: reset_periphrl_t
 *
 * Maps hardware-specific peripheral identifiers to continuous indices. The driver 
 * uses these indices to calculate the exact MMIO register offset (e.g., per0modrst, 
 * per1modrst, brgmodrst) and the specific bit position required to assert or 
 * deassert the reset line for the target IP block.
 */
typedef enum
{
    RST_PERIPHERAL_START = 0,   /* Starting boundary of hardware peripheral IDs */
    RST_TSN0 = 0,               /* Hardware peripheral ID for XGMAC0 */
    RST_TSN1,                   /* Hardware peripheral ID for XGMAC1 */
    RST_TSN2,                   /* Hardware peripheral ID for XGMAC2 */
    RST_USB0,                   /* Hardware peripheral ID for USB instance 0 */
    RST_USB1,                   /* Hardware peripheral ID for USB instance 1 */
    RST_NAND,                   /* Hardware peripheral ID for NAND Flash */
    RST_SOFTPHY,                /* Hardware peripheral ID for Soft PHY */
    RST_SDMMC,                  /* Hardware peripheral ID for SDMMC */
    RST_TSN0ECC,                /* Hardware peripheral ID for XGMAC0 ECC diagnostics */
    RST_TSN1ECC,                /* Hardware peripheral ID for XGMAC1 ECC diagnostics */
    RST_TSN2ECC,                /* Hardware peripheral ID for XGMAC2 ECC diagnostics */
    RST_USB0ECC,                /* Hardware peripheral ID for USB2.0 ECC diagnostics */
    RST_USB1ECC,                /* Hardware peripheral ID for USB3.1 ECC diagnostics */
    RST_NANDECC,                /* Hardware peripheral ID for NAND Flash ECC diagnostics */
    RST_RSRVD1,                 /* Reserved */
    RST_SDMMCECC,               /* Hardware peripheral ID for SDMMC ECC diagnostics */
    RST_DMA,                    /* Hardware peripheral ID for DMA */
    RST_SPIM0,                  /* Hardware peripheral ID for SPI Master 0 */
    RST_SPIM1,                  /* Hardware peripheral ID for SPI Master 1 */
    RST_SPIS0,                  /* Hardware peripheral ID for SPI Slave 0 */
    RST_SPIS1,                  /* Hardware peripheral ID for SPI Slave 1 */
    RST_DMAECC,                 /* Hardware peripheral ID for DMA ECC diagnostics */
    RST_EMACPTP,                /* Hardware peripheral ID for XGMAC PTP block */
    RST_RSRVD2,                 /* Reserved */
    RST_DMAIF0,                 /* Hardware peripheral ID for DMA Interface 0 for FPGA block */
    RST_DMAIF1,                 /* Hardware peripheral ID for DMA Interface 1 for FPGA block */
    RST_DMAIF2,                 /* Hardware peripheral ID for DMA Interface 2 for FPGA block */
    RST_DMAIF3,                 /* Hardware peripheral ID for DMA Interface 3 for FPGA block */
    RST_DMAIF4,                 /* Hardware peripheral ID for DMA Interface 4 for FPGA block */
    RST_DMAIF5,                 /* Hardware peripheral ID for DMA Interface 5 for FPGA block */
    RST_DMAIF6,                 /* Hardware peripheral ID for DMA Interface 6 for FPGA block */
    RST_DMAIF7,                 /* Hardware peripheral ID for DMA Interface 7 for FPGA block */
    RST_WATCHDOG0,              /* Hardware peripheral ID for Watchdog 0 */
    RST_WATCHDOG1,              /* Hardware peripheral ID for Watchdog 1 */
    RST_WATCHDOG2,              /* Hardware peripheral ID for Watchdog 2 */
    RST_WATCHDOG3,              /* Hardware peripheral ID for Watchdog 3 */
    RST_L4SYSTIMER0,            /* Hardware peripheral ID for System Timer 0 */
    RST_L4SYSTIMER1,            /* Hardware peripheral ID for System Timer 1 */
    RST_SPTIMER0,               /* Hardware peripheral ID for Timer instance 0 */
    RST_SPTIMER1,               /* Hardware peripheral ID for Timer instance 1 */
    RST_I2C0,                   /* Hardware peripheral ID for I2C instance 0 */
    RST_I2C1,                   /* Hardware peripheral ID for I2C instance 1 */
    RST_I2C2,                   /* Hardware peripheral ID for I2C instance 2 */
    RST_I2C3,                   /* Hardware peripheral ID for I2C instance 3 */
    RST_I2C4,                   /* Hardware peripheral ID for I2C instance 4 */
    RST_I3C0,                   /* Hardware peripheral ID for I3C instance 0 */
    RST_I3C1,                   /* Hardware peripheral ID for I3C instance 1 */
    RST_RSRVD3,                 /* Reserved */
    RST_UART0,                  /* Hardware peripheral ID for UART instance 0 */
    RST_UART1,                  /* Hardware peripheral ID for UART instance 1 */
    RST_RSRVD4,                 /* Reserved */
    RST_RSRVD5,                 /* Reserved */
    RST_RSRVD6,                 /* Reserved */
    RST_RSRVD7,                 /* Reserved */
    RST_RSRVD8,                 /* Reserved */
    RST_RSRVD9,                 /* Reserved */
    RST_GPIO0,                  /* Hardware peripheral ID for GPIO instance 0 */
    RST_GPIO1,                  /* Hardware peripheral ID for GPIO instance 1 */
    RST_WATCHDOG4,              /* Hardware peripheral ID for Watchdog 4 */
    RST_RSRVD10,                /* Reserved */
    RST_RSRVD11,                /* Reserved */
    RST_RSRVD12,                /* Reserved */
    RST_RSRVD13,                /* Reserved */
    RST_RSRVD14,                /* Reserved */
    RST_SOC2FPGA_BRIDGE,        /* Hardware peripheral ID for SOC to FPGA Bridge */
    RST_LWSOC2FPGA_BRIDGE,      /* Hardware peripheral ID for Low Power SOC to FPGA Bridge */
    RST_FPGA2SOC_BRIDGE,        /* Hardware peripheral ID for FPGA to SOC Bridge */
    RST_FPGA2SDRAM_BRIDGE = 67, /* Hardware peripheral ID for FPGA to SDRAM Bridge */
    RST_PERIPHERAL_END = 67     /* End boundary of the hardware peripheral IDs */
} reset_periphrl_t;


/* Function: rstmgr_assert_reset
 *
 * Asserts the hard reset signal for a specific SoC peripheral. This is 
 * accomplished by mapping the `reset_periphrl_t` ID to the correct Reset Manager 
 * register (e.g., `per0modrst`) and setting the target bit to '1'. The hardware 
 * block will remain parked in a quiescent, un-clocked reset state until explicitly 
 * deasserted.
 *
 * Parameters:
 *
 * per - The target peripheral identifier from <reset_periphrl_t>.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the provided peripheral ID is out of bounds.
 */
int32_t rstmgr_assert_reset(reset_periphrl_t per);

/* Function: rstmgr_deassert_reset
 *
 * Releases the hard reset signal for a specific SoC peripheral. This clears the 
 * corresponding bit in the Reset Manager's MMIO register, allowing the hardware 
 * IP block's internal state machines to begin operating using the active peripheral 
 * clock.
 *
 * Parameters:
 *
 * per - The target peripheral identifier from <reset_periphrl_t>.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the provided peripheral ID is out of bounds.
 */
int32_t rstmgr_deassert_reset(reset_periphrl_t per);

/* Function: rstmgr_toggle_reset
 *
 * Performs a complete reset cycle (assertion immediately followed by deassertion) 
 * on the specified peripheral. This guarantees the internal FIFOs, logic, and 
 * state machines of the IP block are thoroughly flushed and returned to a clean 
 * power-on state without requiring two separate driver calls.
 *
 * Parameters:
 *
 * per - The target peripheral identifier from <reset_periphrl_t>.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the provided peripheral ID is out of bounds.
 */
int32_t rstmgr_toggle_reset(reset_periphrl_t per);

/* Function: rstmgr_get_reset_status
 *
 * Polls the Reset Manager's status registers to determine if a specific peripheral 
 * is currently being held in a reset state. This is useful for diagnostics or 
 * ensuring a driver does not attempt to configure an inactive block.
 *
 * Parameters:
 *
 * per    - The target peripheral identifier from <reset_periphrl_t>.
 * status - Pointer to an 8-bit variable where the state will be written 
 * (1 if currently in reset, 0 if active/deasserted).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the peripheral ID is out of bounds or the status pointer is NULL.
 */
int32_t rstmgr_get_reset_status(reset_periphrl_t per, uint8_t *status);

#endif /* __SOCFPGA_RST_MNGR_H__ */
