/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_iossm.h
 *
 * IOSSM middleware service interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_IOSSM_H__
#define __SOCFPGA_IOSSM_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * Status / event flag macros
 * Re-exported from LL for convenience of upper layers.
 */
#define IOSSM_MW_ECC_CRCT_EVENT_DET          (1U << 0U)   /* Single correctable ECC event detected      */
#define IOSSM_MW_MUL_ECC_CRCT_EVENT_DET      (1U << 1U)   /* Multiple correctable ECC events detected   */
#define IOSSM_MW_ECC_UNCRCT_EVENT_DET        (1U << 2U)   /* Single uncorrectable ECC event detected    */
#define IOSSM_MW_MUL_ECC_UNCRCT_EVENT_DET    (1U << 3U)   /* Multiple uncorrectable ECC events detected */
#define IOSSM_MW_ECC_WRT_BACK_ERROR          (1U << 6U)   /* ECC write-back error                       */
#define IOSSM_MW_SCRUB_OP_OK                 (1U << 7U)   /* Scrub operation completed                  */
#define IOSSM_MW_ECC_CRCT_SCRB_EVENT_DET     (1U << 8U)   /* Correctable error during scrub             */
#define IOSSM_MW_WR_ECC_SIN_BIT              (1U << 9U)   /* Single-bit error during write              */
#define IOSSM_MW_WR_ECC_DBL_BIT              (1U << 10U)  /* Double-bit error during write              */
#define IOSSM_MW_RD_ECC_SIN_BIT              (1U << 11U)  /* Single-bit error during read               */
#define IOSSM_MW_RD_ECC_DBL_BIT              (1U << 12U)  /* Double-bit error during read               */
#define IOSSM_MW_RMW_ECC_DBL_BIT             (1U << 13U)  /* Double-bit error during read-modify-write  */

#define IOSSM_MW_INSTANCE_0      0U   /* Instance 0 identifier */
#define IOSSM_MW_INSTANCE_1      1U   /* Instance 1 identifier */
#define IOSSM_MW_MAX_INSTANCE    2U   /* Maximum supported instances */

#define IOSSM_MW_OP_SUCCESS    0     /* Operation completed successfully */
#define IOSSM_MW_OP_FAILED    -1     /* Operation failed                 */

/*
 * ECC operating mode.
 */
/* Enum: iossm_mw_ecc_mode_t
 *
 * Enumerates IOSSM options, states, commands, or status values.
 *
 * Values:
 *
 *    IOSSM_MW_ECC_DI - iossm mw ecc di value.
 *    IOSSM_MW_ECC_NO_TRIG - iossm mw ecc no trig value.
 *    IOSSM_MW_ECC_DETECT - iossm mw ecc detect value.
 *    IOSSM_MW_ECC_DETECT_CORRECT - iossm mw ecc detect correct value.
 */
typedef enum
{
    IOSSM_MW_ECC_DI,              /* ECC disabled                             */
    IOSSM_MW_ECC_NO_TRIG,         /* ECC enabled, no error trigger            */
    IOSSM_MW_ECC_DETECT,          /* ECC enabled, detection only              */
    IOSSM_MW_ECC_DETECT_CORRECT   /* ECC enabled, detection and correction    */
} iossm_mw_ecc_mode_t;

/*
 * ECC storage type.
 */
/* Enum: iossm_mw_ecc_type_t
 *
 * Enumerates IOSSM options, states, commands, or status values.
 *
 * Values:
 *
 *    IOSSM_MW_OUT_OF_BAND - iossm mw out of band value.
 *    IOSSM_MW_IN_LINE - iossm mw in line value.
 */
typedef enum
{
    IOSSM_MW_OUT_OF_BAND,  /* ECC stored separately from main data */
    IOSSM_MW_IN_LINE       /* ECC stored inline with main data     */
} iossm_mw_ecc_type_t;

/*
 * ECC error detail record populated by the middleware IRQ handler.
 */
/* Struct: iossm_mw_err_info_t
 *
 * Describes IOSSM configuration, state, or transfer information.
 */
typedef struct
{
    uintptr_t info_ptr;     /* Platform-dependent additional error info pointer */
    uint64_t  err_addr;     /* Address at which the ECC error occurred          */
    uint64_t  err_data;     /* Data word that caused the ECC error              */
    uint32_t  err_dat_size; /* Size of the erroneous data in bytes              */
    uint32_t  err_id;       /* Source / origin identifier                       */
    uint32_t  err_syndrome; /* ECC syndrome value                               */
    uint8_t   err_type;     /* Error type (correctable / uncorrectable)         */
} iossm_mw_err_info_t;

/*
 * IOSSM middleware instance context.
 *
 * Returned by iossm_mw_open() and passed back to all other middleware calls.
 * The caller must treat this as an opaque handle.
 */
/* Callback: cb_handler
 *
 * Callback signature used by the IOSSM module.
 *
 * Parameters:
 *
 *    See the typedef prototype for callback argument order and meaning.
 */
typedef struct
{
    uint32_t           base_addr;         /* Hardware base address              */
    uint8_t            ip_type;           /* IP type from GET_SYS_INFO response */
    uint8_t            instance_id;       /* Instance ID from GET_SYS_INFO      */
    void             (*cb_handler)(void); /* User-registered ECC event callback */
    bool               is_open;           /* True when instance is initialised  */
    bool               irq_enabled;       /* True when GIC IRQ wiring succeeded;
                                               false means polling mode only      */
} iossm_mw_ctx_t;

/*
 * Open and initialise an IOSSM instance.
 *
 * Resolves the hardware base address and queries the instance identity via
 * GET_SYS_INFO.  GIC IRQ wiring is attempted but is non-fatal: if the GIC
 * is not yet initialised the instance opens in polling mode (ctx->irq_enabled
 * is false) and all mailbox / ECC / safe-memory operations still work.
 *
 * instance - Instance index (IOSSM_MW_INSTANCE_0 or _1).
 * Returns: Pointer to the instance context on success, NULL on failure.
 */
/* Function: iossm_mw_open
 *
 * Opens a IOSSM instance and prepares it for subsequent operations.
 *
 * Parameters:
 *
 *    instance - Hardware instance index.
 *
 * Returns:
 *
 *    A valid handle or pointer on success; NULL when the operation cannot be completed.
 */
iossm_mw_ctx_t *iossm_mw_open(uint32_t instance);

/*
 * Release an IOSSM instance.
 *
 * instance - Instance index to close.
 * Returns: 0 on success, -EINVAL for invalid index, -EIO if not opened.
 */
/* Function: iossm_mw_close
 *
 * Closes the IOSSM handle or instance and returns it to the inactive state.
 *
 * Parameters:
 *
 *    instance - Hardware instance index.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_close(uint32_t instance);

/* Function: iossm_mw_close_ctx
 *
 * Closes an IOSSM instance using a middleware context pointer.
 *
 * Parameters:
 *
 *    ctx - Context returned by iossm_mw_open().
 *
 * Returns:
 *
 *    0 on success; negative errno on failure.
 */
int32_t iossm_mw_close_ctx(const iossm_mw_ctx_t *ctx);

/*
 * Enable or disable ECC on thr IOSSM instance.
 *
 * ctx - Handle returned by iossm_mw_open().
 * enable - Non-zero to enable, zero to disable.
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_enable_ecc
 *
 * Enables the requested IOSSM feature, path, interrupt, or hardware block.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    enable - Boolean enable state supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_enable_ecc(const iossm_mw_ctx_t *ctx, uint32_t enable);

/*
 * Read the current ECC error count.
 *
 * ctx - Handle returned by iossm_mw_open().
 * Returns: Number of errors (>= 0), or negative error code.
 */
/* Function: iossm_mw_read_ecc_status
 *
 * Reads IOSSM state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_read_ecc_status(const iossm_mw_ctx_t *ctx);

/*
 * Clear the ECC error buffer on the IOSSM instance.
 *
 * ctx - Handle returned by iossm_mw_open().
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_clear_ecc_buffer
 *
 * Clears the requested IOSSM status, event, or pending condition.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_clear_ecc_buffer(const iossm_mw_ctx_t *ctx);

/*
 * Mask (inhibit) a set of ECC interrupt sources.
 *
 * ctx - Handle returned by iossm_mw_open().
 * interrupts - Bitmask of IOSSM_MW_* event flags to mask.
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_mask_interrupt
 *
 * Updates the requested IOSSM mask configuration.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    interrupts - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_mask_interrupt(const iossm_mw_ctx_t *ctx, uint32_t interrupts);

/*
 * Acknowledge (clear) a set of ECC interrupt sources.
 *
 * ctx - Handle returned by iossm_mw_open().
 * interrupts - Bitmask of IOSSM_MW_* event flags to acknowledge.
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_ack_interrupt
 *
 * Performs a IOSSM operation exposed by this layer.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    interrupts - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_ack_interrupt(const iossm_mw_ctx_t *ctx, uint32_t interrupts);

/*
 * Get the error type field for an ECC error entry.
 *
 * ctx - Handle returned by iossm_mw_open().
 * index - Entry index in the error data array.
 * Returns: Error type nibble (>= 0), or negative error code.
 */
/* Function: iossm_mw_get_err_type
 *
 * Reads IOSSM state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    index - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_get_err_type(const iossm_mw_ctx_t *ctx, uint32_t index);

/*
 * Get the address offset for an ECC error entry.
 *
 * ctx - Handle returned by iossm_mw_open().
 * index - Entry index in the error data array.
 * Returns: Address offset (>= 0), or negative error code.
 */
/* Function: iossm_mw_get_err_addr_offset
 *
 * Reads IOSSM state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    index - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_get_err_addr_offset(const iossm_mw_ctx_t *ctx, uint32_t index);

/*
 * Inject a single-bit ECC error at the provided DDR address.
 *
 * The address is bounds- and alignment-checked by the LL layer before any
 * memory write is performed.
 *
 * ctx - Handle returned by iossm_mw_open().
 * ddr_addr - 8-byte-aligned physical DDR address for error injection.
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_inject_sbit_err
 *
 * Performs a IOSSM operation exposed by this layer.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    ddr_addr - Target address used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_inject_sbit_err(const iossm_mw_ctx_t *ctx, uint64_t ddr_addr);

/*
 * Inject a double-bit ECC error at the provided DDR address.
 *
 * ctx - Handle returned by iossm_mw_open().
 * ddr_addr - 8-byte-aligned physical DDR address for error injection.
 * Returns: 0 on success, negative on error.
 */
/* Function: iossm_mw_inject_dbit_err
 *
 * Performs a IOSSM operation exposed by this layer.
 *
 * Parameters:
 *
 *    ctx - Input pointer supplied by the caller.
 *    ddr_addr - Target address used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t iossm_mw_inject_dbit_err(const iossm_mw_ctx_t *ctx, uint64_t ddr_addr);

/*
 * Register a callback invoked from the IOSSM IRQ handler.
 *
 * ctx - Handle returned by iossm_mw_open().
 * handler - Function pointer; NULL clears a previously set callback.
 */
/* Function: iossm_mw_set_callback
 *
 * Writes or configures IOSSM state, data, or register content.
 *
 * Parameters:
 *
 *    ctx - Output storage or caller-provided buffer used by the operation.
 *    handler - Handle returned by the corresponding open or initialization routine.
 *
 * Returns:
 *
 *    None.
 */
void iossm_mw_set_callback(iossm_mw_ctx_t *ctx, void (*handler)(void));

/*
 * IOSSM interrupt service routine.
 *
 * Registered with the interrupt controller by iossm_mw_open().  Not
 * intended to be called directly from application code.
 *
 * pparam - Pointer to the iossm_mw_ctx_t for the firing instance.
 */
/* Function: iossm_mw_irq_handler
 *
 * Performs a IOSSM operation exposed by this layer.
 *
 * Parameters:
 *
 *    pparam - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    None.
 */
void iossm_mw_irq_handler(void *pparam);

/*  */

#endif /* __SOCFPGA_IOSSM_H__ */
