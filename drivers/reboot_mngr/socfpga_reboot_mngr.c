/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_reboot_mngr.c
 *
 * Reboot Manager source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "socfpga_reboot_mngr.h"
#include "socfpga_sip_handler.h"
#include "../api/uart/uart_api.h"

#define COLD_REBOOT_CMD    0x84000009U
#define WARM_REBOOT_CMD    0x84000012U

#define PSCI_E_NOT_SUPPORTED     -1
#define PSCI_E_INVALID_PARAMS    -2

static reboot_callback_t cold_boot_callback = NULL;
static reboot_callback_t warm_boot_callback = NULL;

int32_t reboot_mngr_set_callback(reboot_callback_t callback, uint32_t event)
{
	int32_t ret = 0;

	if (event == REBOOT_COLD)
	{
		cold_boot_callback = callback;
	}
	else if (event == REBOOT_WARM)
	{
		warm_boot_callback = callback;
	}
	else
	{
	ret = -EINVAL;
	}

	return ret;
}

int32_t reboot_mngr_do_reboot(uint32_t event)
{
	uint32_t reset_command = COLD_REBOOT_CMD;
	int32_t ret = 0;
	uint64_t mail_box_args[SMC_CALL_REG_COUNT] = { 0 };

	switch (event)
	{
		case REBOOT_COLD:
			reset_command = COLD_REBOOT_CMD;
			if (cold_boot_callback != NULL)
			{
				cold_boot_callback(NULL);
			}
			break;

		case REBOOT_WARM:
			reset_command = WARM_REBOOT_CMD;
			if (warm_boot_callback != NULL)
			{
				warm_boot_callback(NULL);
			}
			break;

		default:
			printf("Not a valid reboot option");
			ret = -EINVAL;
			break;
	}
	if (ret != 0)
	{
		return ret;
	}

	if (reset_command == WARM_REBOOT_CMD)
	{
		printf("Inititating Warm Reboot");
	}
	else
	{
		printf("Inititating Cold Reboot");
	}

	ret = smc_call(reset_command, mail_box_args);

	switch (ret)
	{
		case PSCI_E_NOT_SUPPORTED:
			printf("Operation not supported");
			ret = -ENOTSUP;
			break;

		case PSCI_E_INVALID_PARAMS:
			printf("Invalid Parameters");
			ret = -EINVAL;
			break;

		default:
		printf("SMC call failed with error code %d", ret);
		ret = -EINVAL;
			break;
	}

	return ret;
}
