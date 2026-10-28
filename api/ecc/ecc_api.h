/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ecc_api.h
 *
 * Error-correcting code (ECC) control: enable blocks, read counts, and inject test errors.
 */

#ifndef __ECC_API_H__
#define __ECC_API_H__

#include <stdint.h>

/* Public block IDs. Values match socfpga_ecc_block_t; IDs that this release does not expose are not defined here. */
/* Constant: ECC_API_BLOCK_NONE
 * No specific ECC block; ecc_api_clear_counters() uses this value to clear all software counters.
 */
#define ECC_API_BLOCK_NONE         0U
/* Constant: ECC_API_BLOCK_OCRAM
 * ECC block identifier for on-chip RAM.
 */
#define ECC_API_BLOCK_OCRAM        1U
/* Constant: ECC_API_BLOCK_DDR
 * ECC block identifier for DDR. DDR injection uses the dedicated DDR injection functions rather than ecc_api_inject_block().
 */
#define ECC_API_BLOCK_DDR          13U
/* Constant: ECC_API_BLOCK_MAX
 * Sentinel one greater than the last ECC block identifier; not a valid block argument.
 */
#define ECC_API_BLOCK_MAX          14U   /*!< sentinel; one past last */
/*  */

/* Constant: ECC_API_BLOCK_MASK_ALL_HPS_MMIO
 * Convenience mask for the HPS-side ECC blocks this API supports: on-chip RAM only. DDR is excluded because it uses the DDR injection functions.
 */
#define ECC_API_BLOCK_MASK_ALL_HPS_MMIO \
    (1U << ECC_API_BLOCK_OCRAM)

/* Constant: ECC_API_BLOCK_MASK_ALL_HPS
 * Convenience mask for all HPS-side blocks this API supports. In this release it equals ECC_API_BLOCK_MASK_ALL_HPS_MMIO.
 */
#define ECC_API_BLOCK_MASK_ALL_HPS \
    ECC_API_BLOCK_MASK_ALL_HPS_MMIO

/* Error type passed to ecc_api_inject_block().  */
/* Constant: ECC_API_ERR_SBE
 * Error-injection selector for a single-bit correctable ECC event.
 */
#define ECC_API_ERR_SBE    1U   /*!< Single-bit (correctable)   */
/* Constant: ECC_API_ERR_DBE
 * Error-injection selector for a double-bit uncorrectable ECC event.
 */
#define ECC_API_ERR_DBE    2U   /*!< Double-bit (uncorrectable) */
/*  */

/* API return codes.  */
/* Constant: ECC_API_OK
 * Successful ECC API status.
 */
#define ECC_API_OK            (0)
/* Constant: ECC_API_ERROR
 * ECC API failure not mapped to a more specific public status.
 */
#define ECC_API_ERROR         (-1)
/* Constant: ECC_API_EINVAL
 * ECC API status for an invalid argument or invalid API state mapped from driver -EINVAL.
 */
#define ECC_API_EINVAL        (-2)
/* Constant: ECC_API_ETIMEOUT
 * ECC API status used when the lower-level ECC driver returns -EIO.
 */
#define ECC_API_ETIMEOUT      (-3)
/* Callback: ecc_api_callback_t
 *
 * Receive an ECC event after the driver updates its per-block counters. The callback executes from the ECC interrupt-dispatch path.
 *
 * Parameters:
 *
 *    block - ECC block identifier associated with the event. Other values than the ECC_API_BLOCK_* constants can appear if earlier firmware enabled ECC on other blocks; ecc_api_block_name() returns "UNKNOWN" for them.
 *    err_type - ECC_API_ERR_SBE or ECC_API_ERR_DBE.
 */
typedef void (*ecc_api_callback_t)(uint32_t block, uint32_t err_type);

/* Function: ecc_api_init
 *
 * Initialize ECC driver state, mask pending ECC interrupts, and register the available ECC interrupt handlers. Interrupt-registration failures are tolerated by the driver where polling remains possible.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL when the driver is already initialized.
 */
int32_t ecc_api_init(void);

/* Function: ecc_api_deinit
 *
 * Mask the tracked ECC interrupts, clear the registered user callback, and release initialized driver state.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL when the ECC driver is not initialized.
 */
int32_t ecc_api_deinit(void);

/* Function: ecc_api_enable
 *
 * Enable ECC checking and correction for the requested HPS-side blocks. Each requested block is attempted independently; the call succeeds when at least one requested block is enabled.
 *
 * Parameters:
 *
 *    block_mask - Bitwise OR of 1U shifted by ECC_API_BLOCK_* identifiers.
 *
 * Returns:
 *
 *    ECC_API_OK when at least one requested block is enabled. ECC_API_EINVAL when ECC is not initialized, the mask is 0, or the mask sets a bit outside ECC_API_BLOCK_MASK_ALL_HPS. ECC_API_ETIMEOUT when all requested blocks fail through the driver's -EIO path.
 */
int32_t ecc_api_enable(uint32_t block_mask);

/* Function: ecc_api_disable
 *
 * Disable ECC checking and correction for the requested HPS-side blocks that are currently enabled.
 *
 * Parameters:
 *
 *    block_mask - Bitwise OR of 1U shifted by ECC_API_BLOCK_* identifiers.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL when ECC is not initialized, the mask sets a bit outside ECC_API_BLOCK_MASK_ALL_HPS, or a driver argument check fails. ECC_API_ETIMEOUT if the driver returns -EIO. ECC_API_ERROR for any other nonzero driver status.
 */
int32_t ecc_api_disable(uint32_t block_mask);

/* Function: ecc_api_inject_block
 *
 * Program a synthetic single-bit or double-bit ECC test event for an enabled HPS-side block.
 *
 * Parameters:
 *
 *    block - ECC_API_BLOCK_OCRAM, which must be enabled. DDR is not accepted by this function.
 *    err_type - ECC_API_ERR_SBE or ECC_API_ERR_DBE.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL when ECC is not initialized, block is unsupported or disabled, or err_type is invalid.
 */
int32_t ecc_api_inject_block(uint32_t block, uint32_t err_type);

/* Function: ecc_api_inject_ddr
 *
 * Request an ECC error injection through the DDR I/O subsystem path.
 *
 * Parameters:
 *
 *    syndrome - Error syndrome passed to the lower-level DDR injection service.
 *    command - Trigger/control value passed to the lower-level DDR injection service.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL when ECC is not initialized or the lower layer returns -EINVAL. ECC_API_ETIMEOUT when the lower layer returns -EIO. ECC_API_ERROR for any other nonzero lower-layer status.
 */
int32_t ecc_api_inject_ddr(uint32_t syndrome, uint32_t command);

/* Function: ecc_api_inject_ddr_sbe
 *
 * Inject a single-bit DDR ECC error using the API's predefined syndrome and trigger values.
 *
 * Returns:
 *
 *    The status returned by ecc_api_inject_ddr().
 */
int32_t ecc_api_inject_ddr_sbe(void);

/* Function: ecc_api_inject_ddr_dbe
 *
 * Inject a double-bit DDR ECC error using the API's predefined syndrome and trigger values.
 *
 * Returns:
 *
 *    The status returned by ecc_api_inject_ddr().
 */
int32_t ecc_api_inject_ddr_dbe(void);

/* Function: ecc_api_get_sbe_count
 *
 * Read the cumulative SBE counter for a block.
 *
 * Parameters:
 *
 *    block - ECC_API_BLOCK_OCRAM or ECC_API_BLOCK_DDR.
 *
 * Returns:
 *
 *    Counter value (>= 0), or ECC_API_EINVAL on any other block.
 */
int32_t ecc_api_get_sbe_count(uint32_t block);

/* Function: ecc_api_get_dbe_count
 *
 * Read the cumulative DBE counter for a block.
 *
 * Parameters:
 *
 *    block - ECC_API_BLOCK_OCRAM or ECC_API_BLOCK_DDR.
 *
 * Returns:
 *
 *    Counter value (>= 0), or ECC_API_EINVAL on any other block.
 */
int32_t ecc_api_get_dbe_count(uint32_t block);

/* Function: ecc_api_get_hw_sbe_count
 *
 * Read the per-block hardware SBE counter (ECC_S_ERR_CNT).
 *
 * Useful when the single-bit error interrupt is not delivered. The block controller keeps its own counter.
 *
 * Parameters:
 *
 *    block - ECC_API_BLOCK_OCRAM; must be enabled.
 *
 * Returns:
 *
 *    Counter value (>= 0), or ECC_API_EINVAL on bad/disabled block.
 */
int32_t ecc_api_get_hw_sbe_count(uint32_t block);

/* Function: ecc_api_poll_status
 *
 * Read the current single-bit and double-bit ECC status and dispatch the bits this layer recognises.
 *
 * Either pointer may be NULL. A NULL pointer skips that output. When ECC has not been initialised, both outputs are set to 0 if non-NULL and the call returns 0.
 *
 * Parameters:
 *
 *    out_serr_bits - Receives the single-bit status bits that were handled.
 *    out_derr_bits - Receives the double-bit status bits that were handled.
 *
 * Returns:
 *
 *    The number of handled status bits, counting single-bit and double-bit bits separately. Zero when ECC is not initialised or nothing was handled. This call does not return a negative code.
 */
int32_t ecc_api_poll_status(uint32_t *out_serr_bits, uint32_t *out_derr_bits);

/* Function: ecc_api_clear_counters
 *
 * Clear the software single-bit and double-bit counts.
 *
 * ECC_API_BLOCK_NONE clears every block. ECC_API_BLOCK_OCRAM or ECC_API_BLOCK_DDR clears that block. This call does not clear a hardware counter register.
 *
 * Parameters:
 *
 *    block - ECC_API_BLOCK_NONE or one ECC_API_BLOCK_* ID.
 *
 * Returns:
 *
 *    ECC_API_OK on success. ECC_API_EINVAL for any other block value.
 */
int32_t ecc_api_clear_counters(uint32_t block);

/* Function: ecc_api_set_callback
 *
 * Register a user callback for ECC events.
 *
 * Pass NULL to clear a previously installed callback.
 *
 * Parameters:
 *
 *    callback - User callback or NULL.
 *
 * Returns:
 *
 *    ECC_API_OK.
 */
int32_t ecc_api_set_callback(ecc_api_callback_t callback);

/* Function: ecc_api_get_serr_status
 *
 * Read the System Manager raw SERR status word.
 *
 * Bit i is set when the corresponding ECC block has a pending SBE.
 *
 * Returns:
 *
 *    Raw 32-bit status.
 */
uint32_t ecc_api_get_serr_status(void);

/* Function: ecc_api_get_derr_status
 *
 * Read the System Manager raw DERR status word.
 *
 * Returns:
 *
 *    Raw 32-bit status.
 */
uint32_t ecc_api_get_derr_status(void);

/* Function: ecc_api_block_name
 *
 * Translate a block ID to a short human-readable name.
 *
 * Useful for example/test logging.
 *
 * Parameters:
 *
 *    block - Block ID.
 *
 * Returns:
 *
 *    Pointer to a static string. Never NULL.
 */
const char *ecc_api_block_name(uint32_t block);

#endif /* __ECC_API_H__ */
