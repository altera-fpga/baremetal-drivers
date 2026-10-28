/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: noc_firewall_api.h
 *
 * Read and write one Network-on-Chip (NoC) firewall aperture.
 *
 * The calls without a base address use the platform firewall base and return
 * -ENOSYS when that base is missing or zero. target is the aperture offset
 * socfpga_noc_firewall_target_t. A NULL output pointer or an unknown offset
 * returns -EINVAL from the driver. The *_with_base calls return -EINVAL for a
 * zero base_address as well.
 */

#ifndef NOC_FIREWALL_API_H
#define NOC_FIREWALL_API_H

#include <stdint.h>
#include "socfpga_noc_firewall.h"

/* Function: noc_firewall_api_get
 *
 * Read one firewall aperture at the platform base.
 *
 * Parameters:
 *
 *    target - Aperture selector.
 *    value - Receives the register value. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when value is NULL or target is out of range.
 */
int32_t noc_firewall_api_get(socfpga_noc_firewall_target_t target,
                             uint32_t *value);

/* Function: noc_firewall_api_set
 *
 * Write one firewall aperture at the platform base.
 *
 * Parameters:
 *
 *    target - Aperture selector.
 *    value - Value to write.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when target is out of range.
 */
int32_t noc_firewall_api_set(socfpga_noc_firewall_target_t target,
                             uint32_t value);

/* Function: noc_firewall_api_get_with_base
 *
 * Read one firewall aperture at base_address. Does not substitute the platform base.
 *
 * Parameters:
 *
 *    base_address - Firewall MMIO base. Zero is rejected.
 *    target - Aperture selector.
 *    value - Receives the register value. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when value is NULL, base_address is 0, or target is out of range.
 */
int32_t noc_firewall_api_get_with_base(uint32_t base_address,
                                       socfpga_noc_firewall_target_t target,
                                       uint32_t *value);

/* Function: noc_firewall_api_set_with_base
 *
 * Write one firewall aperture at base_address.
 *
 * Parameters:
 *
 *    base_address - Firewall MMIO base. Zero is rejected.
 *    target - Aperture selector.
 *    value - Value to write.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0 or target is out of range.
 */
int32_t noc_firewall_api_set_with_base(uint32_t base_address,
                                       socfpga_noc_firewall_target_t target,
                                       uint32_t value);

/* Function: noc_firewall_api_allow_nonsecure
 *
 * Write the allow-non-secure policy for target at the platform base.
 *
 * Does not read the aperture back. Bridge targets receive the bridge policy value; other targets receive the L4 policy value.
 *
 * Parameters:
 *
 *    target - Aperture selector.
 *
 * Returns:
 *
 *    0 on success. -ENOSYS when the platform base is missing or zero. -EINVAL when target is out of range.
 */
int32_t noc_firewall_api_allow_nonsecure(socfpga_noc_firewall_target_t target);

/* Function: noc_firewall_api_allow_nonsecure_with_base
 *
 * Same write as noc_firewall_api_allow_nonsecure(), at base_address.
 *
 * Parameters:
 *
 *    base_address - Firewall MMIO base. Zero is rejected.
 *    target - Aperture selector.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when base_address is 0 or target is out of range.
 */
int32_t noc_firewall_api_allow_nonsecure_with_base(uint32_t base_address,
                                                  socfpga_noc_firewall_target_t target);

#endif /* NOC_FIREWALL_API_H */
