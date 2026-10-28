/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: seu_api.h
 *
 * Single-event upset (SEU) statistics, error queue, and test injection through the Secure Device Manager.
 */

#ifndef SEU_API_H
#define SEU_API_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Reads single-event upset statistics and the Secure Device Manager error
 * queue, and injects test upsets so application error handling can be
 * exercised. Callers do not send mailbox commands themselves.
 */

/* ---------------------------------------------------------------------- */
/* Constants                                                               */
/* ---------------------------------------------------------------------- */

/*
 * Values returned in seu_api_err_data_t::err_type.
 *
 * Mirrors the SDM firmware enum SEU_ERROR_t in
 * common/inc/lsm_ipc_packet.h.  This is the bit-error severity reported
 * by ALT_SDM_MBOX_CMD_READ_SEU_ERROR; it does NOT identify the source
 * (CRAM, NIOS RAM, etc.).  Source classification is encoded in the
 * node_specific_status bits exposed elsewhere by the driver.
 */
/* Constant: SEU_API_ERR_TYPE_NONE
 * SEU error-queue severity value indicating no error.
 */
#define SEU_API_ERR_TYPE_NONE             0U  /*!< SEU_ERR_NONE              */
/* Constant: SEU_API_ERR_TYPE_SINGLE_BIT
 * SEU error-queue severity value for a single-bit error.
 */
#define SEU_API_ERR_TYPE_SINGLE_BIT       1U  /*!< SEU_ERR_SINGLE_BIT        */
/* Constant: SEU_API_ERR_TYPE_DOUBLE_BIT
 * SEU error-queue severity value for a double-bit error.
 */
#define SEU_API_ERR_TYPE_DOUBLE_BIT       2U  /*!< SEU_ERR_DOUBLE_BIT        */
/* Constant: SEU_API_ERR_TYPE_MULTI_BIT
 * SEU error-queue severity value for a multi-bit error.
 */
#define SEU_API_ERR_TYPE_MULTI_BIT        3U  /*!< SEU_ERR_MULTI_BIT         */
/* Constant: SEU_API_ERR_TYPE_CRAM_INTEGRITY
 * SEU error-queue severity value for a configuration-RAM integrity error.
 */
#define SEU_API_ERR_TYPE_CRAM_INTEGRITY   4U  /*!< SEU_ERR_CRAM_INTEGRITY    */

/*
 * err_mode parameter for seu_api_inject_fpga_ram_err().
 *
 * Mirrors the err_mode bitfield in the SDM mailbox cmd 0x42 request
 * payload.  Only 1 and 2 are valid; 0 and >2 are rejected by the SDM.
 */
/* Constant: SEU_API_FPGA_RAM_ERR_MODE_SBE
 * FPGA RAM injection mode selecting a single-bit correctable error.
 */
#define SEU_API_FPGA_RAM_ERR_MODE_SBE   1U  /*!< Single-bit correctable error.        */
/* Constant: SEU_API_FPGA_RAM_ERR_MODE_DBE
 * FPGA RAM injection mode selecting a double-bit error. Availability can depend on target-device support.
 */
#define SEU_API_FPGA_RAM_ERR_MODE_DBE   2U  /*!< Double-bit uncorrectable. Debug use; */
                                          /*!< production devices may reject it. */

/* ---------------------------------------------------------------------- */
/* Types                                                                   */
/* ---------------------------------------------------------------------- */

/* Callback: seu_api_callback_t
 *
 * Notification callback stored by seu_api_set_callback() for the SEU interrupt path. The callback has no arguments and is not invoked by polling-only flows.
 */
typedef void (*seu_api_callback_t)(void);

/* Struct: seu_api_inj_params_t
 *
 * Parameters for a safe configuration-RAM error injection.
 *
 * Fields:
 *
 *    cram_sel0 - First injection location, 0 through 15.
 *    cram_sel1 - Second injection location, 0 through 15; when count is 2 it must differ from cram_sel0.
 *    injection_cycle - Injection timing selector: 0, 1, or 2.
 *    count - Number of errors to inject: 1 or 2.
 */
typedef struct
{
    uint8_t cram_sel0;        /*!< CRAM injection location 0 (0..15).                  */
    uint8_t cram_sel1;        /*!< CRAM injection location 1 (0..15).                  */
    uint8_t injection_cycle;  /*!< 0=immediate, 1=before detect, 2=after detect.       */
    uint8_t count;            /*!< Number of errors to inject: 1 or 2.                 */
} seu_api_inj_params_t;

/* Struct: seu_api_stat_t
 *
 * SEU timing statistics returned by seu_api_read_stat(). Values are Secure Device Manager clock ticks; 0xFFFFFFFF means the corresponding event has not occurred.
 *
 * Fields:
 *
 *    t_seu_cycle - Time between consecutive detection cycles.
 *    t_seu_detect - Time spent detecting an SEU within one cycle.
 *    t_seu_correct - Time spent correcting the most recent SEU.
 *    t_seu_inject_detect - Latency from injection trigger to detection.
 *    t_poll_interval - Internal SEU polling interval.
 */
typedef struct
{
    uint32_t t_seu_cycle;         /*!< Time between consecutive detection cycles.       */
    uint32_t t_seu_detect;        /*!< Time spent detecting SEU within one cycle.       */
    uint32_t t_seu_correct;       /*!< Time spent correcting the most recent SEU.       */
    uint32_t t_seu_inject_detect; /*!< Latency from inject trigger to detection.        */
    uint32_t t_poll_interval;     /*!< SDM internal SEU polling interval.               */
} seu_api_stat_t;

/* Struct: seu_api_err_data_t
 *
 * One SEU error-queue entry returned by seu_api_read_err(). The fields are meaningful when that call succeeds and err_cnt is greater than zero.
 *
 * Fields:
 *
 *    sector_addr - LSM sector index associated with the event.
 *    err_type - Bit-error severity represented by a SEU_API_ERR_TYPE_* value.
 *    err_cnt - Number of errors represented by the queue entry.
 *    corrected - true when the scrubber reports the error corrected.
 */
typedef struct
{
    uint8_t  sector_addr; /*!< LSM sector index where the error was observed.           */
    uint8_t  err_type;    /*!< Bit-error severity; one of SEU_API_ERR_TYPE_*            */
                          /*!< (mirrors SDM SEU_ERROR_t).                                */
    uint32_t err_cnt;     /*!< Number of errors in the SDM error queue entry.           */
    bool     corrected;   /*!< True if the SDM scrubber has corrected the error.        */
} seu_api_err_data_t;

/* ---------------------------------------------------------------------- */
/* Functions                                                               */
/* ---------------------------------------------------------------------- */

/* Function: seu_api_init
 *
 * Initialize the SEU driver and verify access to its command and response scratch buffers.
 *
 * Returns:
 *
 *    0 on success. -EIO when the scratch-buffer probe fails.
 */
int seu_api_init(void);

/* Function: seu_api_deinit
 *
 * Release SEU subsystem resources.
 *
 * Returns:
 *
 *    0 on success.
 */
int seu_api_deinit(void);

/* Function: seu_api_set_callback
 *
 * Register a notification callback for SEU interrupt events.
 *
 * The callback is stored but only invoked when the interrupt path is
 * active.  In polling-only builds it serves as a hook for future use.
 *
 * Parameters:
 *
 *    cb - Callback function pointer; must not be NULL.
 *
 * Returns:
 *
 *    0 on success, -EINVAL if cb is NULL.
 */
int seu_api_set_callback(seu_api_callback_t cb);

/* Function: seu_api_get_first_valid_sector
 *
 * Probe the SDM to find the first valid LSM sector index.
 *
 * The SDM does not expose a topology-enumeration command, so this
 * function issues successive seu_api_read_stat() probes starting at
 * index 0 and returns the first index for which the SDM reports success.
 * Each probe consumes one mailbox job slot; keep max_probe modest
 * (8 is a typical probe limit).
 *
 * Parameters:
 *
 *    max_probe - Maximum number of indices to probe (1..255).
 *    out_sector - Receives the discovered sector index on success.
 *
 * Returns:
 *
 *    0 on success, -EINVAL on bad arguments, -ENODEV if no valid sector was found (FPGA not in user mode or index range too small).
 */
int seu_api_get_first_valid_sector(uint8_t max_probe, uint8_t *out_sector);

/* Function: seu_api_read_stat
 *
 * Read SEU timing statistics for the given sector.
 *
 * Parameters:
 *
 *    sector - LSM sector index obtained from seu_api_get_first_valid_sector().
 *    out_stat - Receives the timing counters on success; must not be NULL.
 *
 * Returns:
 *
 *    0 on success, -EINVAL if out_stat is NULL, -EIO on SDM error.
 */
int seu_api_read_stat(uint8_t sector, seu_api_stat_t *out_stat);

/* Function: seu_api_insert_safe_err
 *
 * Inject a safe (non-destructive) CRAM SEU error.
 *
 * Sends the injection request to the SDM.  The injected error is
 * automatically corrected by the SDM scrubber on its next cycle and
 * appears in the error queue read by seu_api_read_err().
 *
 * Parameters:
 *
 *    sector - LSM sector index to target.
 *    params - Injection parameters; must not be NULL.
 *
 * Returns:
 *
 *    0 on success, -EINVAL on bad parameters, -EIO on SDM rejection.
 */
int seu_api_insert_safe_err(uint8_t sector, const seu_api_inj_params_t *params);

/* Function: seu_api_read_err
 *
 * Read one entry from the SDM SEU error queue.
 *
 * On success, out_err is populated.  When the queue is empty
 * (no error event pending) the call succeeds with out_err->err_cnt == 0.
 *
 * Parameters:
 *
 *    out_err - Receives the error data; must not be NULL.
 *
 * Returns:
 *
 *    0 on success, -EINVAL if out_err is NULL, -EIO on SDM error.
 */
int seu_api_read_err(seu_api_err_data_t *out_err);

/* Function: seu_api_inject_fpga_ram_err
 *
 * Inject an FPGA-fabric LSM NIOS RAM error via the SDM.
 *
 * Wraps SDM mailbox cmd 0x42.  The SDM sends a CNOC IPC to the target
 * sector, which physically flips a bit in the tile's NIOS RAM.  On the
 * next scrub read the LSM detects (and corrects, for single-bit) the
 * flip and notifies the SDM, which enqueues a single-bit (or multi-bit)
 * event retrievable via seu_api_read_err().
 *
 * Parameters:
 *
 *    sector - LSM sector index (from seu_api_get_first_valid_sector()).
 *    err_mode - SEU_API_FPGA_RAM_ERR_MODE_SBE (single-bit) or SEU_API_FPGA_RAM_ERR_MODE_DBE (double-bit, debug-only).
 *    ram_id - Target RAM channel within the sector (0..31).
 *
 * Returns:
 *
 *    0 on success, -EINVAL on bad parameters, -EIO on SDM rejection.
 */
int seu_api_inject_fpga_ram_err(uint8_t sector, uint8_t err_mode, uint8_t ram_id);

/*  */

#endif /* SEU_API_H */
