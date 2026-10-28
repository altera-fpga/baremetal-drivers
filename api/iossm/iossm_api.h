/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: iossm_api.h
 *
 * Control memory-controller error-correcting code (ECC) functions through the I/O subsystem manager (IOSSM), including ECC status, interrupt control, error injection, and guarded DDR access.
 */

#ifndef __IOSSM_API_H__
#define __IOSSM_API_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * Preferred user call flow (handle-based):
 * 1) iossm_api_open(instance)
 * 2) iossm_api_enable_ecc(handle) and operation APIs
 * 3) iossm_api_disable_ecc(handle) when applicable
 * 4) iossm_api_close_handle(handle)
 *
 * Legacy close-by-instance is kept for compatibility during migration.
 */

/* Type: iossm_handle_t
 *
 * Opaque IOSSM handle type used to preserve module state between calls.
 */
typedef void *iossm_handle_t;

/*
 * ECC interrupt / status flag constants
 * (Passed to iossm_api_mask_interrupt / iossm_api_ack_interrupt)
 */
/* Constant: IOSSM_API_INT_CRCT_EVENT
 * Interrupt flag for a correctable ECC event.
 */
#define IOSSM_API_INT_CRCT_EVENT          (1U << 0U)   /* Single correctable event detected      */
/* Constant: IOSSM_API_INT_MUL_CRCT_EVENT
 * Interrupt flag for multiple correctable ECC events.
 */
#define IOSSM_API_INT_MUL_CRCT_EVENT      (1U << 1U)   /* Multiple correctable events detected   */
/* Constant: IOSSM_API_INT_UNCRCT_EVENT
 * Interrupt flag for an uncorrectable ECC event.
 */
#define IOSSM_API_INT_UNCRCT_EVENT        (1U << 2U)   /* Single uncorrectable event detected    */
/* Constant: IOSSM_API_INT_MUL_UNCRCT_EVENT
 * Interrupt flag for multiple uncorrectable ECC events.
 */
#define IOSSM_API_INT_MUL_UNCRCT_EVENT    (1U << 3U)   /* Multiple uncorrectable events detected */
/* Constant: IOSSM_API_INT_WRT_BACK_ERROR
 * Interrupt flag for an ECC write-back error.
 */
#define IOSSM_API_INT_WRT_BACK_ERROR      (1U << 6U)   /* ECC write-back error                   */
/* Constant: IOSSM_API_INT_SCRUB_OP_OK
 * Interrupt flag indicating scrub-operation completion.
 */
#define IOSSM_API_INT_SCRUB_OP_OK         (1U << 7U)   /* Scrub operation completed              */
/* Constant: IOSSM_API_INT_WR_SIN_BIT
 * Interrupt flag for a single-bit ECC error on write.
 */
#define IOSSM_API_INT_WR_SIN_BIT          (1U << 9U)   /* Single-bit error on write              */
/* Constant: IOSSM_API_INT_WR_DBL_BIT
 * Interrupt flag for a double-bit ECC error on write.
 */
#define IOSSM_API_INT_WR_DBL_BIT          (1U << 10U)  /* Double-bit error on write              */
/* Constant: IOSSM_API_INT_RD_SIN_BIT
 * Interrupt flag for a single-bit ECC error on read.
 */
#define IOSSM_API_INT_RD_SIN_BIT          (1U << 11U)  /* Single-bit error on read               */
/* Constant: IOSSM_API_INT_RD_DBL_BIT
 * Interrupt flag for a double-bit ECC error on read.
 */
#define IOSSM_API_INT_RD_DBL_BIT          (1U << 12U)  /* Double-bit error on read               */
/* Constant: IOSSM_API_INT_RMW_DBL_BIT
 * Interrupt flag for a double-bit ECC error during read-modify-write.
 */
#define IOSSM_API_INT_RMW_DBL_BIT         (1U << 13U)  /* Double-bit error during RMW            */
/* Constant: IOSSM_API_INSTANCE_0
 * IOSSM controller instance 0.
 */

#define IOSSM_API_INSTANCE_0    0U  /* IOSSM instance 0 */
/* Constant: IOSSM_API_INSTANCE_1
 * IOSSM controller instance 1.
 */
#define IOSSM_API_INSTANCE_1    1U  /* IOSSM instance 1 */

/* Function: iossm_api_open
 *
 * Open one IOSSM instance and initialize its middleware context. Interrupt registration is attempted during open; failure leaves the instance usable in polling mode.
 *
 * Parameters:
 *
 *    instance - IOSSM instance index accepted by the middleware.
 *
 * Returns:
 *
 *    A handle on success. NULL when instance is out of range, already open, or its base address cannot be resolved.
 */
iossm_handle_t iossm_api_open(uint32_t instance);

/* Function: iossm_api_close_handle
 *
 * Release an IOSSM instance by handle.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL or is not a middleware context. -EIO when the referenced instance is not open.
 */
int32_t iossm_api_close_handle(iossm_handle_t handle);

/* Function: iossm_api_close
 *
 * Release an IOSSM instance by index.
 *
 * Parameters:
 *
 *    instance - IOSSM instance index.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when instance is out of range. -EIO when that instance is not open.
 */
int32_t iossm_api_close(uint32_t instance);

/* Function: iossm_api_enable_ecc
 *
 * Enable ECC for an opened IOSSM instance.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open or the IOSSM command reports failure.
 */
int32_t iossm_api_enable_ecc(iossm_handle_t handle);

/* Function: iossm_api_disable_ecc
 *
 * Disable ECC for an opened IOSSM instance.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open or the IOSSM command reports failure.
 */
int32_t iossm_api_disable_ecc(iossm_handle_t handle);

/* Function: iossm_api_get_ecc_status
 *
 * Read the ECC error-count field for an opened IOSSM instance.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *
 * Returns:
 *
 *    The error count, zero or greater, on success. -EINVAL when handle is NULL. -EIO when the instance is not open.
 */
int32_t iossm_api_get_ecc_status(iossm_handle_t handle);

/* Function: iossm_api_clear_ecc_errors
 *
 * Clear the IOSSM ECC error buffer.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *
 * Returns:
 *
 *    The 3-bit response result from the successful clear command, in the range 0 through 7. -EINVAL when handle is NULL. -EIO when the instance is not open or the IOSSM command reports failure.
 */
int32_t iossm_api_clear_ecc_errors(iossm_handle_t handle);

/* Function: iossm_api_mask_interrupt
 *
 * Mask the selected IOSSM ECC interrupt sources.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    int_flags - Bitwise OR of IOSSM_API_INT_* flags passed to the IOSSM command.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open or the IOSSM command reports failure.
 */
int32_t iossm_api_mask_interrupt(iossm_handle_t handle, uint32_t int_flags);

/* Function: iossm_api_ack_interrupt
 *
 * Acknowledge the selected IOSSM ECC interrupt sources.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    int_flags - Bitwise OR of IOSSM_API_INT_* flags passed to the IOSSM command.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open or the IOSSM command reports failure.
 */
int32_t iossm_api_ack_interrupt(iossm_handle_t handle, uint32_t int_flags);

/* Function: iossm_api_inject_sbe
 *
 * Request a single-bit ECC error injection at a DDR address.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    ddr_addr - Physical DDR address used by the low-level injection command. It must be within the configured DDR window and 8-byte aligned.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open, the DDR address fails the low-level guarded access, or the IOSSM injection command reports failure.
 */
int32_t iossm_api_inject_sbe(iossm_handle_t handle, uint64_t ddr_addr);

/* Function: iossm_api_inject_dbe
 *
 * Request a double-bit ECC error injection at a DDR address.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    ddr_addr - Physical DDR address used by the low-level injection command. It must be within the configured DDR window and 8-byte aligned.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when handle is NULL. -EIO when the instance is not open, the DDR address fails the low-level guarded access, or the IOSSM injection command reports failure.
 */
int32_t iossm_api_inject_dbe(iossm_handle_t handle, uint64_t ddr_addr);

/* Function: iossm_api_get_err_type
 *
 * Read the error-type field for one IOSSM ECC error entry.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    index - Error-entry index used to select the status register.
 *
 * Returns:
 *
 *    The extracted error-type field on success. -EINVAL when handle is NULL. -EIO when the instance is not open.
 */
int32_t iossm_api_get_err_type(iossm_handle_t handle, uint32_t index);

/* Function: iossm_api_get_err_addr
 *
 * Read the address-offset register for one IOSSM ECC error entry.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open().
 *    index - Error-entry index used to select the address register.
 *
 * Returns:
 *
 *    The address-offset register value cast to int32_t on success. -EINVAL when handle is NULL. -EIO when the instance is not open.
 */
int32_t iossm_api_get_err_addr(iossm_handle_t handle, uint32_t index);

/* Function: iossm_api_set_callback
 *
 * Store the callback invoked by the IOSSM middleware interrupt handler.
 *
 * Parameters:
 *
 *    handle - Handle returned by iossm_api_open(). If NULL, this call has no effect.
 *    handler - Callback to invoke when the IOSSM interrupt handler runs. NULL clears the stored callback.
 */
void iossm_api_set_callback(iossm_handle_t handle, void (*handler)(void));

/*
 * Safe DDR memory access
 */

/* iossm_api_mem_write64 / iossm_api_mem_read64 result codes */
/* Constant: IOSSM_API_MEM_OK
 * Successful guarded DDR access status.
 */
#define IOSSM_API_MEM_OK      0   /* Access succeeded                          */
/* Constant: IOSSM_API_MEM_ERANGE
 * Guarded DDR access status indicating an address outside the configured DDR window.
 */
#define IOSSM_API_MEM_ERANGE -1   /* Address is outside the DDR window         */
/* Constant: IOSSM_API_MEM_EALIGN
 * Guarded DDR access status indicating an address that is not 8-byte aligned.
 */
#define IOSSM_API_MEM_EALIGN -2   /* Address is not 8-byte aligned             */
/* Constant: IOSSM_API_DDR_BASE_ADDR
 * First physical DDR address accepted by the guarded 64-bit memory-access helpers in this build.
 */

#define IOSSM_API_DDR_BASE_ADDR    0x0000000080000000ULL  /* DDR start address */
/* Constant: IOSSM_API_DDR_SIZE
 * Size in bytes of the DDR window accepted by the guarded 64-bit memory-access helpers in this build.
 */
#define IOSSM_API_DDR_SIZE         0x0000000100000000ULL  /* DDR size: 4 GB    */
/* Constant: IOSSM_API_DDR_END_ADDR
 * Last physical DDR address represented by IOSSM_API_DDR_BASE_ADDR and IOSSM_API_DDR_SIZE.
 */
#define IOSSM_API_DDR_END_ADDR     (IOSSM_API_DDR_BASE_ADDR + IOSSM_API_DDR_SIZE - 1ULL)

/* Function: iossm_api_mem_write64
 *
 * Write one 64-bit word to DDR after checking the configured DDR range and 8-byte alignment.
 *
 * Parameters:
 *
 *    ddr_addr - Physical DDR address to write.
 *    value - 64-bit value to store.
 *
 * Returns:
 *
 *    IOSSM_API_MEM_OK on success. IOSSM_API_MEM_ERANGE when the address lies outside the configured DDR window. IOSSM_API_MEM_EALIGN when the address is not 8-byte aligned.
 */
int32_t iossm_api_mem_write64(uint64_t ddr_addr, uint64_t value);

/* Function: iossm_api_mem_read64
 *
 * Read one 64-bit word from DDR after checking the output pointer, configured DDR range, and 8-byte alignment.
 *
 * Parameters:
 *
 *    ddr_addr - Physical DDR address to read.
 *    out_value - Receives the 64-bit value. Must not be NULL.
 *
 * Returns:
 *
 *    IOSSM_API_MEM_OK on success. -EINVAL when out_value is NULL. IOSSM_API_MEM_ERANGE when the address lies outside the configured DDR window. IOSSM_API_MEM_EALIGN when the address is not 8-byte aligned.
 */
int32_t iossm_api_mem_read64(uint64_t ddr_addr, uint64_t *out_value);

/*  */

#endif /* __IOSSM_API_H__ */
