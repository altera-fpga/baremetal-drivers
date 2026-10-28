/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include "mailbox_api.h"

/* response must be a reserved, firmware-accessible DDR buffer of at least
 * one uint32_t. See the module guide for the TF-A address restrictions. */
int32_t example_mailbox_id(uint32_t *response)
{
    int32_t rc;
    if (response == NULL) {
        return MAILBOX_ERROR;
    }
    rc = mailbox_init();
    if (rc != MAILBOX_OK) {
        return rc;
    }
    rc = mailbox_exec(MAILBOX_CMD_GET_IDCODE, NULL, 0U, response, 1U);
    mailbox_deinit();
    return rc; /* response is usable only when rc == MAILBOX_OK */
}
