/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errno.h"

#include "sdmmc_api.h"
#include "socfpga_interrupt.h"

#include "../../../drivers/sdmmc/socfpga_sdmmc.h"

static bool sdmmc_api_initialized = false;

int32_t sdmmc_api_init(uint64_t *sector_count)
{
	if (sector_count == NULL) {
		return -EINVAL;
	}

	int32_t ret;

	// interrupt_init_gic();
	ret = sdmmc_init_card(sector_count);
	if (ret == 0) {
		sdmmc_api_initialized = true;
	}
	return ret;
}

int32_t sdmmc_api_deinit(void)
{
	if (!sdmmc_api_initialized) {
		return -EINVAL;
	}

	/*
	 * The lower SD/eMMC HAL does not currently expose a hardware deinit path.
	 * Keep this API-level deinit conservative: mark the API closed so a future
	 * init can be performed without pretending to reset controller/card state.
	 */
	sdmmc_api_initialized = false;
	return 0;
}

int32_t sdmmc_api_read(uint64_t block_addr, uint32_t block_count, uint8_t *buffer)
{
	uint64_t byte_addr;
	uint32_t byte_len;

	if (buffer == NULL || block_count == 0U) {
		return -EINVAL;
	}

	byte_addr = block_addr * (uint64_t)SDMMC_API_BLOCK_SIZE;
	byte_len  = block_count * SDMMC_API_BLOCK_SIZE;

	printf("[SDMMC API] read:  ctrl=0x%lx  card 0x%lx - 0x%lx\n",
	       (unsigned long)SDMMC_HW_BASE,
	       (unsigned long)byte_addr,
	       (unsigned long)(byte_addr + byte_len - 1U));
	/* Cast through void* to avoid -Wcast-align; caller guarantees alignment */
	return sdmmc_read_block_sync((uint64_t *)(void *)buffer, byte_addr,
				     SDMMC_API_BLOCK_SIZE, block_count);
}

int32_t sdmmc_api_write(uint64_t block_addr, uint32_t block_count, const uint8_t *buffer)
{
	uint64_t byte_addr;
	uint32_t byte_len;

	if (buffer == NULL || block_count == 0U) {
		return -EINVAL;
	}

	byte_addr = block_addr * (uint64_t)SDMMC_API_BLOCK_SIZE;
	byte_len  = block_count * SDMMC_API_BLOCK_SIZE;

	printf("[SDMMC API] write: ctrl=0x%lx  card 0x%lx - 0x%lx\n",
	       (unsigned long)SDMMC_HW_BASE,
	       (unsigned long)byte_addr,
	       (unsigned long)(byte_addr + byte_len - 1U));
	/*
	 * Driver API takes uint64_t* (no const). Cast through uintptr_t to drop
	 * const without -Wdiscarded-qualifiers; driver never modifies the buffer.
	 */
	return sdmmc_write_block_sync((uint64_t *)(uintptr_t)buffer, byte_addr,
				      SDMMC_API_BLOCK_SIZE, block_count);
}

int32_t sdmmc_api_is_ready(void)
{
	return (int32_t)sdmmc_is_card_present();
}
