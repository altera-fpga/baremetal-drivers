/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "reboot_mngr_api.h"
#include "socfpga_reboot_mngr.h"
#include "errno.h"

/* Context storage */
typedef struct
{
	reboot_callback_t cb;
	void *user_data;
} reboot_ctx_t;

static reboot_ctx_t cold_ctx = {0};
static reboot_ctx_t warm_ctx = {0};

/* Bridge callbacks (driver expects this form) */
static void cold_cb_bridge(void *arg)
{
	(void)arg;

	if (cold_ctx.cb)
	{
		cold_ctx.cb(cold_ctx.user_data);
	}
}

static void warm_cb_bridge(void *arg)
{
	(void)arg;

	if (warm_ctx.cb)
	{
		warm_ctx.cb(warm_ctx.user_data);
	}
}

int32_t reboot(reboot_type_t type, reboot_callback_t cb, void *user_data)
{
	int32_t ret;

	if (type == REBOOT_COLD)
	{
		cold_ctx.cb = cb;
		cold_ctx.user_data = user_data;

		ret = reboot_mngr_set_callback(cold_cb_bridge, REBOOT_COLD);
		if (ret != 0)
		{
		return ret;
		}

	return reboot_mngr_do_reboot(REBOOT_COLD);
	}
	else if (type == REBOOT_WARM)
	{
		warm_ctx.cb = cb;
		warm_ctx.user_data = user_data;

		ret = reboot_mngr_set_callback(warm_cb_bridge, REBOOT_WARM);
		if (ret != 0)
		{
			return ret;
		}

		return reboot_mngr_do_reboot(REBOOT_WARM);
	}

	return -EINVAL;
}