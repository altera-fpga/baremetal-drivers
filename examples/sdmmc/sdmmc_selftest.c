/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: sdmmc_selftest.c
 *
 * Sdmmc Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Sdmmc Example
 */

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errno.h"
#include "console_api.h"
#include "example_register.h"
#include "sdmmc_api.h"

/* Test parameters */
#define TEST_BLOCK_ADDR   0U    /* Start at block 0 */
#define TEST_BLOCK_COUNT  2U    /* 2 blocks = 1024 bytes */
#define TEST_DATA_SIZE    (TEST_BLOCK_COUNT * SDMMC_API_BLOCK_SIZE)
#define TEST_PATTERN      0xA5A5A5A5U

static uint8_t s_write_buf[TEST_DATA_SIZE] __attribute__((aligned(8)));
static uint8_t s_read_buf[TEST_DATA_SIZE]  __attribute__((aligned(8)));

static void fill_pattern(uint8_t *buf, uint32_t size)
{
    uint32_t *p = (uint32_t *)(void *)buf;
    uint32_t words = size / (uint32_t)sizeof(uint32_t);

    for (uint32_t i = 0U; i < words; i++) {
        p[i] = TEST_PATTERN;
    }
}

static int verify_pattern(const uint8_t *buf, uint32_t size)
{
    const uint32_t *p = (const uint32_t *)(const void *)buf;
    uint32_t words = size / (uint32_t)sizeof(uint32_t);

    for (uint32_t i = 0U; i < words; i++) {
        if (p[i] != TEST_PATTERN) {
            printf("[SDMMC] mismatch @ 0x%" PRIx32 ": got 0x%" PRIx32
                   " expected 0x%" PRIx32 "\n",
                   i * (uint32_t)sizeof(uint32_t), p[i], TEST_PATTERN);
            return -EIO;
        }
    }
    return 0;
}

static void sdmmc_example_main(const char *args)
{
    (void)args;
    int32_t ret;
    uint64_t total_sectors = 0U;

    printf("\n[SDMMC] ---- SDMMC Read/Write Example ----\n");

    /* Init */
    ret = sdmmc_api_init(&total_sectors);
    if (ret != 0) {
        printf("[SDMMC][FAIL] init: %d\n", ret);
        return;
    }
    printf("[SDMMC][PASS] init  sectors=%" PRIu64 "  size=%.1f MB\n",
           total_sectors,
           (double)total_sectors * SDMMC_API_BLOCK_SIZE / (1024.0 * 1024.0));

    /* Write */
    fill_pattern(s_write_buf, TEST_DATA_SIZE);
    ret = sdmmc_api_write(TEST_BLOCK_ADDR, TEST_BLOCK_COUNT, s_write_buf);
    if (ret != 0) {
        printf("[SDMMC][FAIL] write: %d\n", ret);
        return;
    }
    printf("[SDMMC][PASS] wrote %u blocks @ block %" PRIu64
           "  (byte 0x%" PRIx64 " - 0x%" PRIx64 ")\n",
           TEST_BLOCK_COUNT, (uint64_t)TEST_BLOCK_ADDR,
           (uint64_t)TEST_BLOCK_ADDR * SDMMC_API_BLOCK_SIZE,
           ((uint64_t)TEST_BLOCK_ADDR + TEST_BLOCK_COUNT) * SDMMC_API_BLOCK_SIZE - 1U);

    /* Read */
    memset(s_read_buf, 0, TEST_DATA_SIZE);
    ret = sdmmc_api_read(TEST_BLOCK_ADDR, TEST_BLOCK_COUNT, s_read_buf);
    if (ret != 0) {
        printf("[SDMMC][FAIL] read: %d\n", ret);
        return;
    }
    printf("[SDMMC][PASS] read  %u blocks @ block %" PRIu64
           "  (byte 0x%" PRIx64 " - 0x%" PRIx64 ")\n",
           TEST_BLOCK_COUNT, (uint64_t)TEST_BLOCK_ADDR,
           (uint64_t)TEST_BLOCK_ADDR * SDMMC_API_BLOCK_SIZE,
           ((uint64_t)TEST_BLOCK_ADDR + TEST_BLOCK_COUNT) * SDMMC_API_BLOCK_SIZE - 1U);

    /* Verify */
    if (verify_pattern(s_read_buf, TEST_DATA_SIZE) == 0) {
        printf("[SDMMC][PASS] verify  %u bytes match pattern 0x%08" PRIx32 "\n",
               TEST_DATA_SIZE, TEST_PATTERN);
    } else {
        printf("[SDMMC][FAIL] verify\n");
        return;
    }

    printf("[SDMMC] ---- done ----\n\n");
}

void register_sdmmc_example(void)
{
    cli_register_command("sdmmc_selftest", sdmmc_example_main);
}

APP_REGISTER(register_sdmmc_example)


