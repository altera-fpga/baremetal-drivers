/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include "ecc_api.h"

/* Initialize and enable the required blocks before polling. Polling updates
 * counters and clears handled status. It does not invoke a registered
 * callback, and it does not inject an error. */
int32_t example_ecc_poll(uint32_t *single_bits, uint32_t *double_bits)
{
    if ((single_bits == NULL) || (double_bits == NULL)) {
        return ECC_API_EINVAL;
    }
    /* The return is a handled-bit count, which may be positive. */
    int32_t handled = ecc_api_poll_status(single_bits, double_bits);
    return handled;
}
