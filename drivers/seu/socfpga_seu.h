/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_seu.h
 *
 * SEU hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SEU_H__
#define __SOCFPGA_SEU_H__

/*
 * File: socfpga_seu.h
 * Header file for SEU HAL driver
 */

/*
 * seu SEU
 * APIs for SoC FPGA SEU driver.
 * Details: * The SEU driver provides APIs to inject and read SEU-safe errors, read SEU statistics,
 * and inject errors into FPGA-fabric LSM NIOS RAMs.  The driver communicates with the
 * SIP SVC subsystem via V1 INTEL_SIP_SMC_MBOX_SEND_CMD to perform these operations.
 * To see example usage, see seu_sample "SEU sample application".
 * 
 */

/*
 * seu_fns Functions
 * SEU HAL APIs
 */

/*
 * seu_structs Structures
 * SEU Specific Structures
 */

#include <stdint.h>
#include <stdbool.h>

/*
 * seu_structs
 * 
 *
 */

/*
 * Seu error data parameters
 */
/* Struct: read_err_data_t
 *
 * Describes SEU configuration, state, or transfer information.
 */
typedef struct
{
    uint8_t op_state;               /*!<seu output success/fail status*/
    uint8_t sector_addr;            /*!<Sector address at which the error was intentionally injected */
    uint8_t err_type;               /*!<type of the error injected*/
    uint16_t node_specific_status;  /*!<seu node specific status of the error injection*/
    uint32_t err_cnt;               /*!< no of errors injected*/
    bool correction_status;         /*!< Flag indicating if the injected error was corrected */

} read_err_data_t;

/*
 * Seu parameters used to configure the error injection
 */
/* Struct: seu_err_params_t
 *
 * Describes SEU configuration, state, or transfer information.
 */
typedef struct
{
    uint8_t sector_addr;      /*!< Logical sector address for error injection */
    uint8_t cram_sel0;        /*!< CRAM select 0 for injection*/
    uint8_t cram_sel1;        /*!< CRAM select 1 for injection */
    uint8_t injection_cycle;  /*!< Cycle at which the error should be injected */
    uint8_t no_of_injection;  /*!< Number of errors to be injected */
} seu_err_params_t;

/*
 * Seu safe error statistics
 */
/* Struct: seu_stat_t
 *
 * Describes SEU configuration, state, or transfer information.
 */
typedef struct
{
    uint8_t op_state;                /*!< seu output success/fail status */
    uint32_t t_seu_cycle;            /*!< The time between the start of the most recent SEU detection cycle to the previous cycle*/
    uint32_t t_seu_detect;           /*!< The most recent time spent in performing the SEU detection within a SEU cycle*/
    uint32_t t_seu_correct;          /*!< The most recent time spent in performing the SEU correction*/
    uint32_t t_seu_inject_detect;    /*!< The most recent duration from the SEU error being injected to the time the SEU is detected.*/
    uint32_t t_sdm_seu_poll_interval;/*!< The time for SDM to toggle the SEU_ERROR pin after SDM detects error when polling the SEU error*/
} seu_stat_t;
/*
 * 
 */

/*
 * seu_fns
 * 
 */

/*
 * SEU callback function type
 *
 */
/* Type: seu_call_back_t
 *
 * Callback signature used by the SEU module.
 *
 * Parameters:
 *
 *    See the typedef prototype for callback argument order and meaning.
 */
typedef void (*seu_call_back_t)(void);

/*
 * Inject an SEU-safe error.
 *
 * err_params - Parameters used to configure the SEU error injection.
 *
 * Returns: * - 0:       on success
 * - -EINVAL: if parameters are invalid
 * - -EIO:    if the driver is not initialized or SDM rejects the command
 */
/* Function: seu_insert_safe_err
 *
 * Performs a SEU operation exposed by this layer.
 *
 * Parameters:
 *
 *    err_params - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t seu_insert_safe_err(seu_err_params_t err_params);

/*
 * Set the SEU callback function.
 *
 * call_back - Callback function to be registered.
 */
/* Function: seu_set_call_back
 *
 * Writes or configures SEU state, data, or register content.
 *
 * Parameters:
 *
 *    call_back - Input value used by the operation.
 *
 * Returns:
 *
 *    None.
 */
void seu_set_call_back(seu_call_back_t call_back);

/*
 * Initialize the SEU module.
 *
 * Returns: * -  0: on success
 * - -EIO:  if the driver is not initialized
 */
/* Function: seu_init
 *
 * Initializes the SEU block or software context for use.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t seu_init(void);

/*
 * Read SEU safe error data.
 *
 * Returns: * - A read_err_data handle with op_state set to 0 on success
 * - -EIO:    if the driver is not initialized or SDM rejects the command
 */
/* Function: seu_read_err
 *
 * Reads SEU state, data, or register content for the caller.
 *
 * Returns:
 *
 *    A module-specific value or status code.
 */
read_err_data_t seu_read_err(void);

/*
 * Read SEU safe error statistics.
 *
 * Returns: * - A seu_stat handle with op_state set to 0 on success
 * - -EIO:    if the driver is not initialized or SDM rejects the command
 */
/* Function: seu_read_stat
 *
 * Reads SEU state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    sec_addr - Target address used by the operation.
 *
 * Returns:
 *
 *    A module-specific value or status code.
 */
seu_stat_t seu_read_stat(uint8_t sec_addr);

/*
 * Inject an FPGA-fabric LSM NIOS RAM error via the SDM.
 *
 * Wraps SDM mailbox cmd 0x42.  Detection and reporting of the injected
 * bit-flip is performed by the FPGA fabric LSM, not the HPS.
 *
 * err_mode - 1 = single-bit, 2 = double-bit (debug silicon only).
 * ram_id - Target NIOS RAM channel (0..31).
 * sector_addr - LSM sector index.
 *
 * Returns: * - 0:       on success
 * - -EINVAL: if parameters are invalid
 * - -EIO:    if the driver is not initialized or SDM rejects the command
 */
/* Function: seu_insert_fpga_ram_err
 *
 * Performs a SEU operation exposed by this layer.
 *
 * Parameters:
 *
 *    err_mode - Input value used by the operation.
 *    ram_id - Input value used by the operation.
 *    sector_addr - Block or sector address/count value.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t seu_insert_fpga_ram_err(uint8_t err_mode, uint8_t ram_id, uint8_t
        sector_addr);

/*
 * Probe the SDM for the first valid LSM sector index.
 *
 * The SDM does not expose a public command to enumerate the device's
 * cnoc_topography table.  This helper discovers a valid LSM sector by
 * issuing seu_read_stat() with successive sector indices 0..max_idx-1
 * and returning the first one for which the SDM firmware reports
 * STATOK.  Indices that are out-of-range or that map to non-sector
 * nodes will be rejected with ALT_SDM_MBOX_RESP_INVALID_ADDR; if the
 * FPGA is not in user mode every probe will be rejected with
 * ALT_SDM_MBOX_RESP_NOT_CONFIGURED and the function returns -ENODEV.
 *
 * Each probe issues one synchronous V1 mailbox command per sector index,
 * so callers should keep max_idx modest (8 is typical).
 *
 * max_idx - Maximum number of sector indices to probe.
 * out_sector - On success, set to the discovered LSM sector
 *                         index.  Untouched on failure.
 *
 * Returns: * -  0:       on success
 * - -EINVAL:  if out_sector is NULL or max_idx is 0
 * - -ENODEV:  if no valid sector was found in [0, max_idx)
 */
/* Function: seu_get_first_lsm_sector
 *
 * Reads SEU state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    max_idx - Input value used by the operation.
 *    out_sector - Block or sector address/count value.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t seu_get_first_lsm_sector(uint8_t max_idx, uint8_t *out_sector);

/*
 * De-initialize the SEU module.
 *
 * Returns: 0 on success.
 */
/* Function: seu_deinit
 *
 * Deinitializes the SEU context and releases resources owned by the caller.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t seu_deinit(void);
/*
 * 
 */
/* end of group seu_fns */

/*
 * 
 */
/* end of group seu */

#endif
