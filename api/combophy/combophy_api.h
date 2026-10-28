/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: combophy_api.h
 *
 * Read the Combo PHY version and feature registers.
 * Both calls return -ENOSYS when the platform has no Combo PHY base address.
 */

#ifndef COMBOPHY_API_H
#define COMBOPHY_API_H
#include <stdint.h>
#include "socfpga_combophy.h"

/* Function: combophy_api_get_version
 *
 * Read the Combo PHY version register.
 *
 * Parameters:
 *
 *    version - Receives the register value. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when this platform has no Combo PHY base. -EINVAL when version is NULL.
 */
int32_t combophy_api_get_version(uint32_t *version);

/* Function: combophy_api_get_features
 *
 * Read the Combo PHY feature register.
 *
 * Parameters:
 *
 *    features - Receives the register value. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when this platform has no Combo PHY base. -EINVAL when features is NULL.
 */
int32_t combophy_api_get_features(uint32_t *features);
#endif /* COMBOPHY_API_H */
