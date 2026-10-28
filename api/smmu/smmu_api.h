/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: smmu_api.h
 *
 * Configure and query the System Memory Management Unit (SMMU) through the
 * platform SMMU driver.
 */

#ifndef SMMU_API_H
#define SMMU_API_H

#include <stdint.h>
#include <stdbool.h>
#include "errno.h"

/* Function: smmu_api_enable
 *
 * Prepares the SMMUv3 tables and queues, then enables the SMMU.
 *
 * Returns:
 *
 *    0 on success; -EIO when required queues or the final enable acknowledgement cannot be established.
 */
int32_t smmu_api_enable(void);
/* Function: smmu_api_disable
 *
 * Disables SMMU translation and driver-owned queues, then waits for CR0ACK to clear.
 *
 * Returns:
 *
 *    0 on success; -ETIMEDOUT if the hardware does not acknowledge the disabled state.
 */
int32_t smmu_api_disable(void);
/* Function: smmu_api_deinit
 *
 * Deinitializes the SMMU by calling the same hardware-disable path used by smmu_api_disable().
 *
 * Returns:
 *
 *    0 on success; -ETIMEDOUT if the hardware does not acknowledge the disabled state.
 */
int32_t smmu_api_deinit(void);
/* Function: smmu_api_is_enabled
 *
 * Reads SMMU_CR0 and reports whether the SMMUEN bit is set.
 *
 * Parameters:
 *
 *    enabled - Receives the current SMMU enable state.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when enabled is NULL.
 */
int32_t smmu_api_is_enabled(bool *enabled);
/* Function: smmu_api_read_reg
 *
 * Reads a 32-bit SMMU register at the supplied offset from SMMU_BASE_ADDR.
 *
 * Parameters:
 *
 *    offset - Byte offset from SMMU_BASE_ADDR.
 *    value - Receives the 32-bit register value.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when value is NULL.
 */
int32_t smmu_api_read_reg(uint32_t offset, uint32_t *value);
/* Function: smmu_api_write_reg
 *
 * Writes a 32-bit value to an SMMU register at the supplied offset from SMMU_BASE_ADDR.
 *
 * Parameters:
 *
 *    offset - Byte offset from SMMU_BASE_ADDR.
 *    value - 32-bit value to write.
 *
 * Returns:
 *
 *    0.
 */
int32_t smmu_api_write_reg(uint32_t offset, uint32_t value);

#endif /* SMMU_API_H */

