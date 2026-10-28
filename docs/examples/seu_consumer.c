/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include "errno.h"
#include "seu_api.h"

/* Requires TF-A and a configured FPGA. init writes the scratch ranges listed
 * in the module guide. An error-queue read consumes one entry. No injection. */
int example_seu_snapshot(seu_api_stat_t *statistics, seu_api_err_data_t *event)
{
    uint8_t sector;
    int close_rc;
    int rc;
    if ((statistics == NULL) || (event == NULL)) {
        return -EINVAL;
    }
    rc = seu_api_init();
    if (rc != 0) {
        return rc;
    }
    rc = seu_api_get_first_valid_sector(8U, &sector);
    if (rc == 0) {
        rc = seu_api_read_stat(sector, statistics);
    }
    if (rc == 0) {
        rc = seu_api_read_err(event);
    }
    close_rc = seu_api_deinit();
    return rc != 0 ? rc : close_rc;
}
