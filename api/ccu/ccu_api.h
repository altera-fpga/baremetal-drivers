/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ccu_api.h
 *
 * Read Coherency Control Unit (CCU) identification and error status, and flush
 * enabled L3 cache arrays. Calls without an explicit base address use the
 * platform CCU base.
 */

#ifndef CCU_API_H
#define CCU_API_H

#include <stdint.h>
#include "socfpga_ccu.h"
/* Constant: CCU_API_DEFAULT_TIMEOUT_POLLS
 * Default poll-count limit used by CCU cache-maintenance operations that do not take an explicit timeout.
 */

#define CCU_API_DEFAULT_TIMEOUT_POLLS    200000U

/* Function: ccu_api_get_id
 *
 * Reads the CCU identification register using the platform default base address.
 *
 * Parameters:
 *
 *    id - Output storage for the ID value.
 *
 * Returns:
 *
 *    0 on success; -ENOSYS when the platform does not provide a fixed CCU base;
 *    -EINVAL if id is NULL.
 */
int32_t ccu_api_get_id(uint32_t *id);

/* Function: ccu_api_get_error_status
 *
 * Reads the CCU uncorrected error status register using the platform default base address.
 *
 * Parameters:
 *
 *    status - Output storage for the status value.
 *
 * Returns:
 *
 *    0 on success; -ENOSYS when the platform does not provide a fixed CCU base;
 *    -EINVAL if status is NULL.
 */
int32_t ccu_api_get_error_status(uint32_t *status);

/* Function: ccu_api_flush_l3_cache
 *
 * Flushes all enabled CCU system-memory cache entries using the platform default base address.
 *
 * Returns:
 *
 *    0 on success; -ENOSYS when the platform does not provide a fixed CCU base;
 *    -ETIMEDOUT if an enabled cache array does not complete maintenance within
 *    CCU_API_DEFAULT_TIMEOUT_POLLS.
 */
int32_t ccu_api_flush_l3_cache(void);

/* Function: ccu_api_get_id_with_base
 *
 * Reads the CCU identification register using a caller-provided base address.
 *
 * Parameters:
 *
 *    base_address - MMIO base address of the CCU block.
 *    id - Output storage for the ID value.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if base_address is zero or id is NULL.
 */
int32_t ccu_api_get_id_with_base(uint32_t base_address, uint32_t *id);

/* Function: ccu_api_flush_l3_cache_with_base
 *
 * Flushes all enabled CCU system-memory cache entries using a caller-provided base address.
 *
 * Parameters:
 *
 *    base_address - MMIO base address of the CCU block.
 *    timeout_polls - Maximum polls for each cache-maintenance operation.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if base_address or timeout_polls is zero; -ETIMEDOUT
 *    if an enabled cache array does not complete maintenance within the limit.
 */
int32_t ccu_api_flush_l3_cache_with_base(uint32_t base_address,
                                         uint32_t timeout_polls);

#endif /* CCU_API_H */
