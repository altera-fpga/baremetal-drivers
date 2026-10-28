/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ecc.h
 *
 * ECC hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 * The ECC driver provides a low-level interface to manage Error Correction Code 
 * controllers across the SoCFPGA HPS. It handles the enable/disable sequences, 
 * fault injection (for both MMIO-based and SiP-managed blocks), and interrupt 
 * tracking for SBE (Single-Bit Error) and DBE (Double-Bit Error) events.
 *
 */

#ifndef __SOCFPGA_ECC_H__
#define __SOCFPGA_ECC_H__

#include <stdint.h>
#include <stdbool.h>

/* Enum: socfpga_ecc_block_t
 *
 * Identifiers for every ECC-protected memory block within the HPS subsystem.
 *
 * Values:
 *
 * SOCFPGA_ECC_BLOCK_NONE      - No block selected.
 * SOCFPGA_ECC_BLOCK_OCRAM     - On-chip RAM ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_USB0_RAM0 - USB0 RAM0 ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_USB1_RAM2 - USB1 RAM2 ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC0_RX  - EMAC0 RX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC0_TX  - EMAC0 TX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC1_RX  - EMAC1 RX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC1_TX  - EMAC1 TX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC2_RX  - EMAC2 RX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_EMAC2_TX  - EMAC2 TX buffer ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_QSPI      - QSPI ECC block (Accessed via Secure SiP SMC).
 * SOCFPGA_ECC_BLOCK_USB1_RAM1 - USB1 RAM1 ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_USB1_RAM0 - USB1 RAM0 ECC block (MMIO).
 * SOCFPGA_ECC_BLOCK_DDR       - DDR IO96B ECC block (Accessed via Secure SiP SMC).
 */
typedef enum {
    SOCFPGA_ECC_BLOCK_NONE       = 0U,
    SOCFPGA_ECC_BLOCK_OCRAM      = 1U,
    SOCFPGA_ECC_BLOCK_USB0_RAM0  = 2U,
    SOCFPGA_ECC_BLOCK_USB1_RAM2  = 3U,
    SOCFPGA_ECC_BLOCK_EMAC0_RX   = 4U,
    SOCFPGA_ECC_BLOCK_EMAC0_TX   = 5U,
    SOCFPGA_ECC_BLOCK_EMAC1_RX   = 6U,
    SOCFPGA_ECC_BLOCK_EMAC1_TX   = 7U,
    SOCFPGA_ECC_BLOCK_EMAC2_RX   = 8U,
    SOCFPGA_ECC_BLOCK_EMAC2_TX   = 9U,
    SOCFPGA_ECC_BLOCK_QSPI       = 10U,
    SOCFPGA_ECC_BLOCK_USB1_RAM1  = 11U,
    SOCFPGA_ECC_BLOCK_USB1_RAM0  = 12U,
    SOCFPGA_ECC_BLOCK_DDR        = 13U,
    SOCFPGA_ECC_BLOCK_MAX
} socfpga_ecc_block_t;

/* Enum: socfpga_ecc_err_type_t
 *
 * Defines the classification of the ECC fault detected by the controller.
 */
typedef enum {
    SOCFPGA_ECC_ERR_SBE = 1U, /* Single-bit error (Correctable) */
    SOCFPGA_ECC_ERR_DBE = 2U  /* Double-bit error (Uncorrectable) */
} socfpga_ecc_err_type_t;

/* Type: socfpga_ecc_callback_t
 *
 * ISR callback function signature.
 *
 * Parameters:
 *
 * block    - The <socfpga_ecc_block_t> where the error occurred.
 * err_type - The type of error (<socfpga_ecc_err_type_t>).
 */
typedef void (*socfpga_ecc_callback_t)(uint32_t block, uint32_t err_type);

/* Constant: SOCFPGA_ECC_BLOCK_MASK_ALL_HPS
 * A convenience bitmask representing all HPS-side ECC blocks (excluding DDR).
 */
#define SOCFPGA_ECC_BLOCK_MASK_ALL_HPS \
    ((1U << SOCFPGA_ECC_BLOCK_OCRAM)      | \
     (1U << SOCFPGA_ECC_BLOCK_USB0_RAM0)  | \
     (1U << SOCFPGA_ECC_BLOCK_USB1_RAM0)  | \
     (1U << SOCFPGA_ECC_BLOCK_USB1_RAM1)  | \
     (1U << SOCFPGA_ECC_BLOCK_USB1_RAM2)  | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC0_RX)   | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC0_TX)   | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC1_RX)   | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC1_TX)   | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC2_RX)   | \
     (1U << SOCFPGA_ECC_BLOCK_EMAC2_TX)   | \
     (1U << SOCFPGA_ECC_BLOCK_QSPI))


/* Function: socfpga_ecc_init
 *
 * Initializes the ECC driver context. This routine resolves the base addresses 
 * for all peripheral blocks, masks the global System Manager ECC interrupts 
 * (to prevent spurious triggers during init), and registers the SERR/DERR 
 * ISRs with the GIC.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the initialization fails (e.g., duplicate init).
 */
int32_t socfpga_ecc_init(void);

/* Function: socfpga_ecc_deinit
 *
 * Deinitializes the ECC driver. This masks all ECC interrupts in the System 
 * Manager and clears the registered user callback.
 *
 * Returns:
 *
 * 0 on success; negative on error.
 */
int32_t socfpga_ecc_deinit(void);

/* Function: socfpga_ecc_enable_blocks
 *
 * Enables ECC checking and correction for the specified blocks.
 *
 * This performs a safe enable sequence: disabling interrupts, resetting the 
 * ECC engine and its associated memory, enabling detection/correction logic, 
 * and unmasking the SERR lines in the System Manager.
 *
 * Parameters:
 *
 * block_mask - Bitmask of blocks to enable (using `1U << SOCFPGA_ECC_BLOCK_...`).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the mask is invalid; -EIO if hardware fails to acknowledge reset.
 */
int32_t socfpga_ecc_enable_blocks(uint32_t block_mask);

/* Function: socfpga_ecc_disable_blocks
 *
 * Disables ECC checking and correction for the specified blocks.
 *
 * Parameters:
 *
 * block_mask - Bitmask of blocks to disable.
 *
 * Returns:
 *
 * 0 on success; negative on error.
 */
int32_t socfpga_ecc_disable_blocks(uint32_t block_mask);

/* Function: socfpga_ecc_inject_block_err
 *
 * Injects a synthetic ECC error into an MMIO-accessible HPS block for 
 * validation testing. This writes to the per-block `ECC_INT_TEST` register.
 *
 * Parameters:
 *
 * block    - The target <socfpga_ecc_block_t> ID.
 * err_type - The error type to inject (<SOCFPGA_ECC_ERR_SBE> or <SOCFPGA_ECC_ERR_DBE>).
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the block is unsupported or invalid.
 */
int32_t socfpga_ecc_inject_block_err(uint32_t block, uint32_t err_type);

/* Function: socfpga_ecc_inject_ddr_err
 *
 * Triggers a synthetic ECC error in DDR memory via the IO96B controller. 
 * This issues an `INTEL_SIP_SMC_INJECT_IO96B_ECC_ERR` call to the Secure 
 * Monitor (ATF), which handles the interaction with the IO96B controller.
 *
 * Parameters:
 *
 * syndrome - The syndrome value encoding bit positions for the synthetic error.
 * command  - The specific trigger/control op-code as defined by the SiP documentation.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the SiP call fails.
 */
int32_t socfpga_ecc_inject_ddr_err(uint32_t syndrome, uint32_t command);

/* Function: socfpga_ecc_get_sbe_count
 *
 * Retrieves the software-tracked cumulative Single-Bit Error (SBE) count for 
 * a specific block, maintained by the driver's ISR.
 *
 * Parameters:
 *
 * block - The block ID.
 *
 * Returns:
 *
 * The error count (>= 0); -EINVAL on invalid block ID.
 */
int32_t socfpga_ecc_get_sbe_count(uint32_t block);

/* Function: socfpga_ecc_get_dbe_count
 *
 * Retrieves the software-tracked cumulative Double-Bit Error (DBE) count for 
 * a specific block, maintained by the driver's ISR.
 *
 * Parameters:
 *
 * block - The block ID.
 *
 * Returns:
 *
 * The error count (>= 0); -EINVAL on invalid block ID.
 */
int32_t socfpga_ecc_get_dbe_count(uint32_t block);

/* Function: socfpga_ecc_get_hw_sbe_count
 *
 * Reads the hardware-accumulated SBE counter (ECC_S_ERR_CNT) directly from the 
 * memory controller of the specified block. This is useful for polling status 
 * if interrupts are not available.
 *
 * Parameters:
 *
 * block - The block ID.
 *
 * Returns:
 *
 * The current hardware counter value; -EINVAL on invalid or disabled block.
 */
int32_t socfpga_ecc_get_hw_sbe_count(uint32_t block);

/* Function: socfpga_ecc_poll_status
 *
 * Manually polls the System Manager SERR/DERR status bits. This is primarily 
 * intended for diagnostic CLI commands or systems where GIC interrupts are 
 * not available. 
 *
 * This function clears the status bits (Write-1-to-Clear) and updates the 
 * software counters. Note: User callbacks are NOT invoked during this polling 
 * cycle as it operates in a non-interrupt context.
 *
 * Parameters:
 *
 * out_serr_bits - Pointer to receive the raw SERR status word handled during the poll.
 * out_derr_bits - Pointer to receive the raw DERR status word handled during the poll.
 *
 * Returns:
 *
 * The number of total events handled (count of set bits cleared).
 */
int32_t socfpga_ecc_poll_status(uint32_t *out_serr_bits,
                                uint32_t *out_derr_bits);

/* Function: socfpga_ecc_clear_counters
 *
 * Resets the software-tracked SBE and DBE counters for a specific block to zero.
 *
 * Parameters:
 *
 * block - The block ID, or <SOCFPGA_ECC_BLOCK_NONE> to clear all blocks.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the block ID is invalid.
 */
int32_t socfpga_ecc_clear_counters(uint32_t block);

/* Function: socfpga_ecc_set_callback
 *
 * Registers a user-defined ISR callback function. This will be invoked by the 
 * internal ISR after the driver has finished processing a block's SBE/DBE event.
 *
 * Parameters:
 *
 * callback - Function pointer to the ISR handler; pass NULL to unregister.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t socfpga_ecc_set_callback(socfpga_ecc_callback_t callback);

/* Function: socfpga_ecc_get_sysmgr_serr_status
 *
 * Returns the raw 32-bit System Manager SERR status bitmap.
 *
 * Returns:
 *
 * The raw SERR register value.
 */
uint32_t socfpga_ecc_get_sysmgr_serr_status(void);

/* Function: socfpga_ecc_get_sysmgr_derr_status
 *
 * Returns the raw 32-bit System Manager DERR status bitmap.
 *
 * Returns:
 *
 * The raw DERR register value.
 */
uint32_t socfpga_ecc_get_sysmgr_derr_status(void);

#endif /* __SOCFPGA_ECC_H__ */