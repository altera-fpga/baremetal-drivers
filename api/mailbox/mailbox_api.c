/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>
#include "mailbox_api.h"
#include "socfpga_mbox_client.h"

/* Single global client  sufficient for single-threaded baremetal use */
static sdm_client_handle g_handle;

/* -----------------------------------------------------------------------
 * Lifecycle
 * ----------------------------------------------------------------------- */

int32_t mailbox_init(void)
{
	g_handle = mbox_client_acquire();
	if (g_handle == NULL) {
		return MAILBOX_ERROR;
	}

	return MAILBOX_OK;
}

void mailbox_deinit(void)
{
	/* Keep the shared MBOX client for reuse by other examples/drivers. */
	mbox_client_release();
	g_handle = NULL;
}

/* -----------------------------------------------------------------------
 * mailbox_exec
 *
 * Uses V1 INTEL_SIP_SMC_MBOX_SEND_CMD via mbox_send_command(): ATF runs a
 * synchronous mailbox_send_cmd() and returns when the SDM response is ready.
 * No V3 async poll is required. This path is not subject to the V3 GEN_MBOX
 * default-deny allowlist (CONFIG_STATUS-only).
 * ----------------------------------------------------------------------- */
int32_t mailbox_exec(uint32_t  cmd,
                     uint32_t *args,     uint32_t arg_words,
                     uint32_t *resp_ddr, uint32_t resp_words)
{
	int32_t ret;

	if (g_handle == NULL) {
		return MAILBOX_ERROR;
	}

	ret = mbox_send_command(g_handle,
	                        cmd,
	                        args,     arg_words  * sizeof(uint32_t),
	                        resp_ddr, resp_words * sizeof(uint32_t),
	                        NULL, 0U);
	if (ret != 0) {
		return MAILBOX_ERROR;
	}

	return MAILBOX_OK;
}
