/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: perf_selftest.c
 *
 * Perf Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Perf Example
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "errno.h"

#include "console_api.h"
#include "example_register.h"
#include "perf_api.h"
#include "sdmmc_api.h"

#define PERF_MEM_DEFAULT_BASE      0x80500000ULL
#define PERF_MEM_DEFAULT_SIZE      (256U * 1024U)
#define PERF_MEM_DEFAULT_LOOPS     1U

#define PERF_SDMMC_MAX_BLOCKS      128U
#define PERF_SDMMC_PATTERN         0xA5U

#define PERF_LAT_DEFAULT_LOOPS     100U
#define PERF_LAT_TIMER_LOOPS       1000U
#define PERF_LAT_MAX_LOOPS         10000U

static uint8_t sd_wr_buf[PERF_SDMMC_MAX_BLOCKS * SDMMC_API_BLOCK_SIZE] __attribute__((aligned(64)));
static uint8_t sd_rd_buf[PERF_SDMMC_MAX_BLOCKS * SDMMC_API_BLOCK_SIZE] __attribute__((aligned(64)));

typedef struct perf_latency_accum {
    uint32_t samples;
    uint64_t min_ticks;
    uint64_t sum_ticks;
    uint64_t max_ticks;
} perf_latency_accum_t;

static const char *skip_spaces(const char *p)
{
    while ((p != NULL) && (*p == ' ')) {
        p++;
    }
    return p;
}

static const char *skip_token(const char *p)
{
    p = skip_spaces(p);
    while ((p != NULL) && (*p != '\0') && (*p != ' ')) {
        p++;
    }
    return skip_spaces(p);
}

static int token_eq(const char *p, const char *word)
{
    p = skip_spaces(p);

    while ((*word != '\0') && (p != NULL) && (*p == *word)) {
        p++;
        word++;
    }

    return ((*word == '\0') && ((p == NULL) || (*p == '\0') || (*p == ' ')));
}

static uint64_t parse_num64(const char *p)
{
    p = skip_spaces(p);

    if ((p != NULL) && (p[0] == '0') && ((p[1] == 'x') || (p[1] == 'X'))) {
        return parse_hex(p);
    }

    return (uint64_t)parse_dec(p);
}


static uint32_t parse_loops_or_default(const char *p, uint32_t default_loops)
{
    uint32_t loops = default_loops;

    if ((p != NULL) && (*p != '\0')) {
        loops = (uint32_t)parse_num64(p);
    }

    if (loops == 0U) {
        loops = 1U;
    }

    if (loops > PERF_LAT_MAX_LOOPS) {
        printf("[PERF][LAT] loops capped from %u to %u\n", loops, PERF_LAT_MAX_LOOPS);
        loops = PERF_LAT_MAX_LOOPS;
    }

    return loops;
}

static void latency_accum_init(perf_latency_accum_t *acc)
{
    acc->samples = 0U;
    acc->min_ticks = 0xFFFFFFFFFFFFFFFFULL;
    acc->sum_ticks = 0ULL;
    acc->max_ticks = 0ULL;
}

static void latency_accum_add(perf_latency_accum_t *acc, uint64_t start_ticks, uint64_t end_ticks)
{
    uint64_t delta_ticks;

    if (end_ticks >= start_ticks) {
        delta_ticks = end_ticks - start_ticks;
    } else {
        delta_ticks = 0ULL;
    }

    if (delta_ticks < acc->min_ticks) {
        acc->min_ticks = delta_ticks;
    }

    if (delta_ticks > acc->max_ticks) {
        acc->max_ticks = delta_ticks;
    }

    acc->sum_ticks += delta_ticks;
    acc->samples++;
}

static void fill_pattern(uint8_t *buf, uint32_t len, uint8_t seed)
{
    for (uint32_t i = 0U; i < len; i++) {
        buf[i] = (uint8_t)(seed + (uint8_t)i + (uint8_t)(i >> 8));
    }
}

static int verify_buffer(const uint8_t *exp, const uint8_t *got, uint32_t len, const char *tag)
{
    for (uint32_t i = 0U; i < len; i++) {
        if (exp[i] != got[i]) {
            printf("[PERF][%s][FAIL] mismatch offset=0x%X exp=0x%02X got=0x%02X\n",
                   tag, i, exp[i], got[i]);
            return -EIO;
        }
    }

    printf("[PERF][%s][PASS] verify %u bytes\n", tag, len);
    return 0;
}

static void cmd_perf_help(void)
{
    printf("\nPerformance CLI commands:\n");
    printf("  perf help\n");
    printf("  perf timer\n");
    printf("  perf mem [base] [size_bytes] [loops]\n");
    printf("  perf latency timer [loops]\n");
    printf("  perf latency mem32 [addr] [loops]       destructive 32-bit DDR latency test\n");
    printf("  perf sdmmc read <block> <blocks<=128>\n");
    printf("  perf sdmmc rw   <block> <blocks<=128> destructive write/read test\n");
    printf("  perf latency sdmmc-read <block> <blocks<=128> [loops]\n");
    printf("  perf log dump                           dump in-memory perf results\n");
    printf("  perf log clear                          clear in-memory perf results\n");
    printf("\nExamples:\n");
    printf("  perf timer\n");
    printf("  perf mem 0x80500000 262144 4\n");
    printf("  perf latency timer 1000\n");
    printf("  perf latency mem32 0x80500000 1000\n");
    printf("  perf sdmmc read 2048 128\n");
    printf("  perf sdmmc rw 4096 16\n");
    printf("  perf latency sdmmc-read 2048 1 100\n");
    printf("  perf log dump\n\n");
}

static void cmd_perf_timer(void)
{
    uint64_t hz = perf_counter_hz();
    uint64_t t0;
    uint64_t min_us = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t max_us = 0ULL;
    uint64_t sum_us = 0ULL;

    printf("\n[PERF][TIMER] ARM generic counter frequency: %llu Hz\n",
           (unsigned long long)hz);

    for (uint32_t i = 0U; i < 32U; i++) {
        t0 = perf_counter_ticks();
        uint64_t dt = perf_elapsed_us(t0);
        if (dt < min_us) {
            min_us = dt;
        }
        if (dt > max_us) {
            max_us = dt;
        }
        sum_us += dt;
    }

    printf("[PERF][TIMER] timestamp overhead: min=%llu us avg=%llu us max=%llu us\n",
           (unsigned long long)min_us,
           (unsigned long long)(sum_us / 32ULL),
           (unsigned long long)max_us);
}

static void cmd_perf_latency_timer(const char *args)
{
    const char *p = skip_token(args); /* skip "timer" */
    uint32_t loops = parse_loops_or_default(p, PERF_LAT_TIMER_LOOPS);
    perf_latency_accum_t acc;

    latency_accum_init(&acc);

    printf("\n[PERF][LAT][TIMER] measuring perf_counter_ticks() overhead loops=%u\n", loops);

    for (uint32_t i = 0U; i < loops; i++) {
        uint64_t start = perf_counter_ticks();
        uint64_t end = perf_counter_ticks();
        latency_accum_add(&acc, start, end);
    }

    perf_print_latency_result("timer-overhead", acc.samples, acc.min_ticks, acc.sum_ticks, acc.max_ticks, 0);
}

static void cmd_perf_latency_mem32(const char *args)
{
    const char *p = skip_token(args); /* skip "mem32" */
    uint64_t base = PERF_MEM_DEFAULT_BASE;
    uint32_t loops;
    volatile uint32_t *ptr;
    uint32_t sink = 0U;
    perf_latency_accum_t acc;

    if ((p != NULL) && (*p != '\0')) {
        base = parse_num64(p);
        p = skip_token(p);
    }

    loops = parse_loops_or_default(p, PERF_LAT_DEFAULT_LOOPS);
    ptr = (volatile uint32_t *)(uintptr_t)base;

    latency_accum_init(&acc);

    printf("\n[PERF][LAT][MEM32] destructive 32-bit write+read addr=0x%016llX loops=%u\n",
           (unsigned long long)base,
           loops);

    for (uint32_t i = 0U; i < loops; i++) {
        uint64_t start;
        uint64_t end;

        start = perf_counter_ticks();
        *ptr = 0x5A000000U ^ i;
        perf_dsb();
        sink ^= *ptr;
        perf_dsb();
        end = perf_counter_ticks();

        latency_accum_add(&acc, start, end);
    }

    printf("[PERF][LAT][MEM32] sink=0x%08X\n", sink);
    perf_print_latency_result("mem32-write-read", acc.samples, acc.min_ticks, acc.sum_ticks, acc.max_ticks, 0);
}

static void cmd_perf_mem(const char *args)
{
    uint64_t base = PERF_MEM_DEFAULT_BASE;
    uint32_t size = PERF_MEM_DEFAULT_SIZE;
    uint32_t loops = PERF_MEM_DEFAULT_LOOPS;
    volatile uint32_t *src;
    volatile uint32_t *dst;
    uint32_t words;
    uint64_t start;
    uint64_t elapsed;

    const char *p = skip_token(args); /* skip "mem" */

    if ((p != NULL) && (*p != '\0')) {
        base = parse_num64(p);
        p = skip_token(p);
    }
    if ((p != NULL) && (*p != '\0')) {
        size = (uint32_t)parse_num64(p);
        p = skip_token(p);
    }
    if ((p != NULL) && (*p != '\0')) {
        loops = (uint32_t)parse_num64(p);
    }

    if (size < 64U) {
        size = 64U;
    }
    if (loops == 0U) {
        loops = 1U;
    }

    words = size / 4U;
    size = words * 4U;
    src = (volatile uint32_t *)(uintptr_t)base;
    dst = (volatile uint32_t *)(uintptr_t)(base + (uint64_t)size);

    printf("\n[PERF][MEM] destructive DDR test\n");
    printf("[PERF][MEM] src=0x%016llX dst=0x%016llX size=%u loops=%u\n",
           (unsigned long long)base,
           (unsigned long long)(base + (uint64_t)size),
           size, loops);

    start = perf_counter_ticks();
    for (uint32_t l = 0U; l < loops; l++) {
        for (uint32_t i = 0U; i < words; i++) {
            src[i] = 0xA5000000U ^ i ^ l;
        }
    }
    perf_dsb();
    elapsed = perf_elapsed_us(start);
    perf_print_result("mem-write", (uint64_t)size * loops, elapsed);

    start = perf_counter_ticks();
    uint32_t sink = 0U;
    for (uint32_t l = 0U; l < loops; l++) {
        for (uint32_t i = 0U; i < words; i++) {
            sink ^= src[i];
        }
    }
    perf_dsb();
    elapsed = perf_elapsed_us(start);
    perf_print_result("mem-read", (uint64_t)size * loops, elapsed);
    printf("[PERF][MEM] read sink=0x%08X\n", sink);

    start = perf_counter_ticks();
    for (uint32_t l = 0U; l < loops; l++) {
        for (uint32_t i = 0U; i < words; i++) {
            dst[i] = src[i];
        }
    }
    perf_dsb();
    elapsed = perf_elapsed_us(start);
    perf_print_result("mem-copy", (uint64_t)size * loops, elapsed);
}

static void cmd_perf_sdmmc(const char *args)
{
    const char *p = skip_token(args); /* skip "sdmmc" */
    int do_rw;
    uint64_t block;
    uint32_t blocks;
    uint32_t bytes;
    uint64_t sectors = 0ULL;
    uint64_t start;
    uint64_t elapsed;
    int32_t rc;

    if (token_eq(p, "read")) {
        do_rw = 0;
    } else if (token_eq(p, "rw")) {
        do_rw = 1;
    } else {
        printf("Usage: perf sdmmc read <block> <blocks<=128>\n");
        printf("       perf sdmmc rw   <block> <blocks<=128>\n");
        return;
    }

    p = skip_token(p);
    if ((p == NULL) || (*p == '\0')) {
        printf("[PERF][SDMMC][FAIL] missing block\n");
        return;
    }
    block = parse_num64(p);
    p = skip_token(p);
    if ((p == NULL) || (*p == '\0')) {
        printf("[PERF][SDMMC][FAIL] missing block count\n");
        return;
    }
    blocks = (uint32_t)parse_num64(p);

    if ((blocks == 0U) || (blocks > PERF_SDMMC_MAX_BLOCKS)) {
        printf("[PERF][SDMMC][FAIL] blocks must be 1..128\n");
        return;
    }

    bytes = blocks * SDMMC_API_BLOCK_SIZE;

    rc = sdmmc_api_init(&sectors);
    if (rc != 0) {
        printf("[PERF][SDMMC][FAIL] init rc=%d\n", rc);
        return;
    }

    if ((block + (uint64_t)blocks) > sectors) {
        printf("[PERF][SDMMC][FAIL] range exceeds card sectors=%llu\n",
               (unsigned long long)sectors);
        return;
    }

    printf("\n[PERF][SDMMC] mode=%s block=%llu blocks=%u bytes=%u sectors=%llu\n",
           do_rw ? "rw" : "read",
           (unsigned long long)block,
           blocks,
           bytes,
           (unsigned long long)sectors);

    if (do_rw != 0) {
        for (uint32_t i = 0U; i < bytes; i++) {
            sd_wr_buf[i] = (uint8_t)(PERF_SDMMC_PATTERN ^ (uint8_t)i ^ (uint8_t)(i >> 8));
        }

        start = perf_counter_ticks();
        rc = sdmmc_api_write(block, blocks, sd_wr_buf);
        elapsed = perf_elapsed_us(start);
        if (rc != 0) {
            printf("[PERF][SDMMC][FAIL] write rc=%d\n", rc);
            return;
        }
        perf_print_result("sdmmc-write", bytes, elapsed);
    }

    memset(sd_rd_buf, 0, bytes);
    start = perf_counter_ticks();
    rc = sdmmc_api_read(block, blocks, sd_rd_buf);
    elapsed = perf_elapsed_us(start);
    if (rc != 0) {
        printf("[PERF][SDMMC][FAIL] read rc=%d\n", rc);
        return;
    }
    perf_print_result("sdmmc-read", bytes, elapsed);

    if (do_rw != 0) {
        (void)verify_buffer(sd_wr_buf, sd_rd_buf, bytes, "SDMMC");
    }
}

static void cmd_perf_latency_sdmmc_read(const char *args)
{
    const char *p = skip_token(args); /* skip "sdmmc-read" or "sdmmc" */
    uint64_t block;
    uint32_t blocks;
    uint32_t loops;
    uint32_t bytes;
    uint64_t sectors = 0ULL;
    perf_latency_accum_t acc;
    int32_t rc;

    if ((p == NULL) || (*p == '\0')) {
        printf("Usage: perf latency sdmmc-read <block> <blocks<=128> [loops]\n");
        return;
    }
    block = parse_num64(p);
    p = skip_token(p);

    if ((p == NULL) || (*p == '\0')) {
        printf("Usage: perf latency sdmmc-read <block> <blocks<=128> [loops]\n");
        return;
    }
    blocks = (uint32_t)parse_num64(p);
    p = skip_token(p);

    loops = parse_loops_or_default(p, PERF_LAT_DEFAULT_LOOPS);

    if ((blocks == 0U) || (blocks > PERF_SDMMC_MAX_BLOCKS)) {
        printf("[PERF][LAT][SDMMC][FAIL] blocks must be 1..128\n");
        return;
    }

    bytes = blocks * SDMMC_API_BLOCK_SIZE;

    rc = sdmmc_api_init(&sectors);
    if (rc != 0) {
        printf("[PERF][LAT][SDMMC][FAIL] init rc=%d\n", rc);
        perf_print_latency_result("sdmmc-read-lat", 0U, 0ULL, 0ULL, 0ULL, rc);
        return;
    }

    if ((block + (uint64_t)blocks) > sectors) {
        printf("[PERF][LAT][SDMMC][FAIL] range exceeds card sectors=%llu\n",
               (unsigned long long)sectors);
        return;
    }

    printf("\n[PERF][LAT][SDMMC] read-only block=%llu blocks=%u bytes=%u loops=%u sectors=%llu\n",
           (unsigned long long)block,
           blocks,
           bytes,
           loops,
           (unsigned long long)sectors);

    latency_accum_init(&acc);

    for (uint32_t i = 0U; i < loops; i++) {
        uint64_t start;
        uint64_t end;

        memset(sd_rd_buf, 0, bytes);
        start = perf_counter_ticks();
        rc = sdmmc_api_read(block, blocks, sd_rd_buf);
        end = perf_counter_ticks();

        if (rc != 0) {
            printf("[PERF][LAT][SDMMC][FAIL] read iter=%u rc=%d\n", i, rc);
            perf_print_latency_result("sdmmc-read-lat", acc.samples, acc.min_ticks, acc.sum_ticks, acc.max_ticks, rc);
            return;
        }

        latency_accum_add(&acc, start, end);
    }

    perf_print_latency_result("sdmmc-read-lat", acc.samples, acc.min_ticks, acc.sum_ticks, acc.max_ticks, 0);
}

static void cmd_perf_latency(const char *args)
{
    const char *p = skip_token(args); /* skip "latency" */

    if ((p == NULL) || (*p == '\0') || token_eq(p, "help")) {
        printf("\nLatency benchmark commands:\n");
        printf("  perf latency timer [loops]\n");
        printf("  perf latency mem32 [addr] [loops]\n");
        printf("  perf latency sdmmc-read <block> <blocks<=128> [loops]\n\n");
        return;
    }

    if (token_eq(p, "timer")) {
        cmd_perf_latency_timer(p);
        return;
    }

    if (token_eq(p, "mem32")) {
        cmd_perf_latency_mem32(p);
        return;
    }

    if (token_eq(p, "sdmmc-read") || token_eq(p, "sdmmc")) {
        cmd_perf_latency_sdmmc_read(p);
        return;
    }

    printf("Unknown perf latency subcommand. Use: perf latency help\n");
}

static void cmd_perf_log(const char *args)
{
    const char *p = skip_token(args); /* skip "log" */

    if ((p == NULL) || (*p == '\0') || token_eq(p, "dump")) {
        perf_log_dump();
        return;
    }

    if (token_eq(p, "clear")) {
        perf_log_clear();
        return;
    }

    printf("Usage: perf log dump | clear\n");
}

static void cmd_perf_main(const char *args)
{
    args = skip_spaces(args);

    if ((args == NULL) || (*args == '\0') || token_eq(args, "help")) {
        cmd_perf_help();
        return;
    }

    if (token_eq(args, "timer")) {
        cmd_perf_timer();
        return;
    }

    if (token_eq(args, "latency")) {
        cmd_perf_latency(args);
        return;
    }

    if (token_eq(args, "log")) {
        cmd_perf_log(args);
        return;
    }

    if (token_eq(args, "mem")) {
        cmd_perf_mem(args);
        return;
    }

    if (token_eq(args, "sdmmc")) {
        cmd_perf_sdmmc(args);
        return;
    }

    printf("Unknown perf subcommand. Use: perf help\n");
}

void register_perf_example(void)
{
    cli_register_command("perf_selftest", cmd_perf_main);
}

APP_REGISTER(register_perf_example)
