/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: noc_probe_api.h
 *
 * Read the Network-on-Chip (NoC) probe identity and its error logger.
 *
 * The calls without a base address use the platform probe base and return
 * -ENOSYS when that base is missing or zero. A zero base_address on a
 * *_with_base call returns -EINVAL.
 */

#ifndef NOC_PROBE_API_H
#define NOC_PROBE_API_H

#include <stdbool.h>
#include <stdint.h>
#include "socfpga_noc_probe.h"

/* Function: noc_probe_api_error_is_valid
 *
 * Report whether the error logger has a latched error.
 *
 * Parameters:
 *
 *    valid - Set true when the valid bit is set. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when valid is NULL.
 */
int32_t noc_probe_api_error_is_valid(bool *valid);

/* Function: noc_probe_api_error_read
 *
 * Copy the latched error-log words into log. Does not clear the latch.
 *
 * Parameters:
 *
 *    log - Receives errlog0, errlog1, and errlog3 through errlog7. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when log is NULL.
 */
int32_t noc_probe_api_error_read(socfpga_noc_probe_error_log_t *log);

/* Function: noc_probe_api_error_is_valid_with_base
 *
 * Same check as noc_probe_api_error_is_valid(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Probe MMIO base. Zero is rejected.
 *    valid - Set true when the valid bit is set. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0 or valid is NULL.
 */
int32_t noc_probe_api_error_is_valid_with_base(uint32_t base_address,
                                               bool *valid);

/* Function: noc_probe_api_error_read_with_base
 *
 * Same copy as noc_probe_api_error_read(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Probe MMIO base. Zero is rejected.
 *    log - Receives the latched error words. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0 or log is NULL.
 */
int32_t noc_probe_api_error_read_with_base(uint32_t base_address,
                                           socfpga_noc_probe_error_log_t *log);

/* Function: noc_probe_api_read_id
 *
 * Read the probe core identification register.
 *
 * Parameters:
 *
 *    core_id - Receives the ID. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when core_id is NULL.
 */
int32_t noc_probe_api_read_id(uint32_t *core_id);

/* Function: noc_probe_api_error_logger_enable
 *
 * Enable or disable the error logger.
 *
 * Parameters:
 *
 *    enable - true writes 1 to the fault-enable bit. false writes 0.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero.
 */
int32_t noc_probe_api_error_logger_enable(bool enable);

/* Function: noc_probe_api_error_clear
 *
 * Clear the latched error-valid bit.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero.
 */
int32_t noc_probe_api_error_clear(void);

/* Function: noc_probe_api_read_id_with_base
 *
 * Same read as noc_probe_api_read_id(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Probe MMIO base. Zero is rejected.
 *    core_id - Receives the ID. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0 or core_id is NULL.
 */
int32_t noc_probe_api_read_id_with_base(uint32_t base_address,
                                        uint32_t *core_id);

/* Function: noc_probe_api_error_logger_enable_with_base
 *
 * Same control as noc_probe_api_error_logger_enable(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Probe MMIO base. Zero is rejected.
 *    enable - true enables the logger. false disables it.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0.
 */
int32_t noc_probe_api_error_logger_enable_with_base(uint32_t base_address,
                                                    bool enable);

/* Function: noc_probe_api_error_clear_with_base
 *
 * Same clear as noc_probe_api_error_clear(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Probe MMIO base. Zero is rejected.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0.
 */
int32_t noc_probe_api_error_clear_with_base(uint32_t base_address);

#endif /* NOC_PROBE_API_H */
