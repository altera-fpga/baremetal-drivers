/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: sdmmc_api.h
 *
 * Initialize an SD/eMMC device, perform blocking 512-byte block reads and writes,
 * query card readiness, and release API-side state.
 */

#ifndef __SDMMC_API_H__
#define __SDMMC_API_H__

#include <stdint.h>
/* Constant: SDMMC_API_BLOCK_SIZE
 * Logical block size, in bytes, used by the SD/MMC block read and write APIs.
 */

#define SDMMC_API_BLOCK_SIZE    (512U) /**< Size of one SD/eMMC block in bytes. */
/* Constant: SDMMC_API_NOT_READY
 * Status value returned by readiness helpers when the card is not ready.
 */
#define SDMMC_API_NOT_READY     0
/* Constant: SDMMC_API_READY
 * Status value returned by readiness helpers when the card is ready.
 */
#define SDMMC_API_READY         1

#include "../../drivers/sdmmc/socfpga_sdmmc_reg.h"
#define SDMMC_HW_BASE           SRS_BASE_ADDR

/* Function: sdmmc_api_init
 *
 * Initializes the SD/MMC path and returns the detected card capacity in
 * 512-byte sectors. Call this before read or write operations.
 *
 * Parameters:
 *
 *    sector_count - Output location for the number of addressable sectors.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if sector_count is NULL; on hardware builds,
 *    otherwise returns the status from sdmmc_init_card().
 */
int32_t sdmmc_api_init(uint64_t *sector_count);

/* Function: sdmmc_api_deinit
 *
 * Clears the API-level initialized state. The current lower driver does not
 * perform a controller/card power-down or hardware reset from this call.
 *
 * Returns:
 *
 *    0 on success; -EINVAL if the API was not initialized.
 */
int32_t sdmmc_api_deinit(void);

/* Function: sdmmc_api_read
 *
 * Reads one or more 512-byte blocks synchronously.
 *
 * Parameters:
 *
 *    block_addr - Starting block number.
 *    block_count - Number of blocks to read. Must be non-zero.
 *    buffer - Destination buffer large enough for block_count * 512 bytes.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for a NULL buffer or zero block_count; otherwise
 *    returns the status from sdmmc_read_block_sync().
 */
int32_t sdmmc_api_read(uint64_t block_addr, uint32_t block_count, uint8_t *buffer);

/* Function: sdmmc_api_write
 *
 * Writes one or more 512-byte blocks synchronously.
 *
 * Parameters:
 *
 *    block_addr - Starting block number.
 *    block_count - Number of blocks to write. Must be non-zero.
 *    buffer - Source buffer containing block_count * 512 bytes.
 *
 * Returns:
 *
 *    0 on success; -EINVAL for a NULL buffer or zero block_count; otherwise
 *    returns the status from sdmmc_write_block_sync().
 */
int32_t sdmmc_api_write(uint64_t block_addr, uint32_t block_count, const uint8_t *buffer);

/* Function: sdmmc_api_is_ready
 *
 * Report the card-inserted bit. This does not report whether sdmmc_api_init() succeeded.
 *
 * Returns:
 *
 *    SDMMC_API_READY (1) or SDMMC_API_NOT_READY (0) from the controller present-state card-inserted bit. The SD/MMC driver records that this bit can stay set whether or not a card is inserted, so a ready result is not proof that a card is present.
 */
int32_t sdmmc_api_is_ready(void);

#endif /* __SDMMC_API_H__ */
