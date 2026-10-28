/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "perf_api.h"
#include "lib_time.h"

static perf_log_entry_t perf_log_entries[PERF_LOG_MAX_ENTRIES];
static uint32_t perf_log_head;
static uint32_t perf_log_used;
static uint32_t perf_log_seq;

static void perf_copy_tag(char *dst, const char *src)
{
    uint32_t i;

    if (src == NULL) {
        src = "unknown";
    }

    for (i = 0U; i < (PERF_LOG_TAG_LEN - 1U); i++) {
        dst[i] = src[i];
        if (src[i] == '\0') {
            return;
        }
    }

    dst[PERF_LOG_TAG_LEN - 1U] = '\0';
}

static perf_log_entry_t *perf_log_alloc_entry(void)
{
    uint32_t idx;

    if (perf_log_used < PERF_LOG_MAX_ENTRIES) {
        idx = (perf_log_head + perf_log_used) % PERF_LOG_MAX_ENTRIES;
        perf_log_used++;
    } else {
        idx = perf_log_head;
        perf_log_head = (perf_log_head + 1U) % PERF_LOG_MAX_ENTRIES;
    }

    memset(&perf_log_entries[idx], 0, sizeof(perf_log_entries[idx]));
    perf_log_entries[idx].seq = ++perf_log_seq;
    return &perf_log_entries[idx];
}

uint64_t perf_counter_hz(void)
{
    return clock_hz();
}

uint64_t perf_counter_ticks(void)
{
    return clock_ticks();
}

uint64_t perf_ticks_to_us(uint64_t ticks)
{
    return ticks_to_us(ticks);
}

uint64_t perf_ticks_to_ns(uint64_t ticks)
{
    return ticks_to_ns(ticks);
}

uint64_t perf_elapsed_us(uint64_t start_ticks)
{
    uint64_t now = perf_counter_ticks();

    if (now < start_ticks) {
        return 0ULL;
    }

    return perf_ticks_to_us(now - start_ticks);
}

uint64_t perf_elapsed_ns(uint64_t start_ticks)
{
    uint64_t now = perf_counter_ticks();

    if (now < start_ticks) {
        return 0ULL;
    }

    return perf_ticks_to_ns(now - start_ticks);
}

uint64_t perf_kib_per_sec(uint64_t bytes, uint64_t elapsed_us)
{
    if (elapsed_us == 0ULL) {
        return 0ULL;
    }

    return (bytes * 1000000ULL) / (elapsed_us * 1024ULL);
}

uint64_t perf_mbps_x1000(uint64_t bytes, uint64_t elapsed_us)
{
    if (elapsed_us == 0ULL) {
        return 0ULL;
    }

    /* Mbps = bytes * 8 / elapsed_us.  Return Mbps x 1000. */
    return (bytes * 8000ULL) / elapsed_us;
}

void perf_log_add_result(const char *tag, uint64_t bytes, uint64_t elapsed_us, int status)
{
    perf_log_entry_t *entry = perf_log_alloc_entry();

    entry->type = PERF_LOG_TYPE_THROUGHPUT;
    perf_copy_tag(entry->tag, tag);
    entry->status = status;
    entry->bytes = bytes;
    entry->elapsed_us = elapsed_us;
    entry->kib_per_sec = perf_kib_per_sec(bytes, elapsed_us);
    entry->mbps_x1000 = perf_mbps_x1000(bytes, elapsed_us);
}

void perf_log_add_latency(const char *tag,
                          uint32_t samples,
                          uint64_t min_ns,
                          uint64_t avg_ns,
                          uint64_t max_ns,
                          int status)
{
    perf_log_entry_t *entry = perf_log_alloc_entry();

    entry->type = PERF_LOG_TYPE_LATENCY;
    perf_copy_tag(entry->tag, tag);
    entry->status = status;
    entry->samples = samples;
    entry->min_ns = min_ns;
    entry->avg_ns = avg_ns;
    entry->max_ns = max_ns;
}

void perf_log_clear(void)
{
    memset(perf_log_entries, 0, sizeof(perf_log_entries));
    perf_log_head = 0U;
    perf_log_used = 0U;
    perf_log_seq = 0U;
    printf("[PERF][LOG] cleared\n");
}

uint32_t perf_log_count(void)
{
    return perf_log_used;
}

void perf_log_dump(void)
{
    printf("\n[PERF][LOG] entries=%u max=%u\n", perf_log_used, PERF_LOG_MAX_ENTRIES);

    if (perf_log_used == 0U) {
        printf("[PERF][LOG] empty\n");
        return;
    }

    for (uint32_t i = 0U; i < perf_log_used; i++) {
        uint32_t idx = (perf_log_head + i) % PERF_LOG_MAX_ENTRIES;
        const perf_log_entry_t *e = &perf_log_entries[idx];

        if (e->type == PERF_LOG_TYPE_THROUGHPUT) {
            printf("[PERF][LOG][%02u] seq=%u type=THR tag=%s bytes=%llu time=%llu us rate=%llu KiB/s %llu.%03llu Mbps status=%d\n",
                   i,
                   e->seq,
                   e->tag,
                   (unsigned long long)e->bytes,
                   (unsigned long long)e->elapsed_us,
                   (unsigned long long)e->kib_per_sec,
                   (unsigned long long)(e->mbps_x1000 / 1000ULL),
                   (unsigned long long)(e->mbps_x1000 % 1000ULL),
                   e->status);
        } else if (e->type == PERF_LOG_TYPE_LATENCY) {
            printf("[PERF][LOG][%02u] seq=%u type=LAT tag=%s samples=%u min=%llu ns avg=%llu ns max=%llu ns status=%d\n",
                   i,
                   e->seq,
                   e->tag,
                   e->samples,
                   (unsigned long long)e->min_ns,
                   (unsigned long long)e->avg_ns,
                   (unsigned long long)e->max_ns,
                   e->status);
        }
    }
}

void perf_print_result_status(const char *tag, uint64_t bytes, uint64_t elapsed_us, int status)
{
    uint64_t kib_s = perf_kib_per_sec(bytes, elapsed_us);
    uint64_t mbps_x1000 = perf_mbps_x1000(bytes, elapsed_us);

    printf("[PERF] %s: bytes=%llu time=%llu us rate=%llu KiB/s %llu.%03llu Mbps status=%d\n",
           tag,
           (unsigned long long)bytes,
           (unsigned long long)elapsed_us,
           (unsigned long long)kib_s,
           (unsigned long long)(mbps_x1000 / 1000ULL),
           (unsigned long long)(mbps_x1000 % 1000ULL),
           status);

    perf_log_add_result(tag, bytes, elapsed_us, status);
}

void perf_print_result(const char *tag, uint64_t bytes, uint64_t elapsed_us)
{
    uint64_t kib_s = perf_kib_per_sec(bytes, elapsed_us);
    uint64_t mbps_x1000 = perf_mbps_x1000(bytes, elapsed_us);

    printf("[PERF] %s: bytes=%llu time=%llu us rate=%llu KiB/s %llu.%03llu Mbps\n",
           tag,
           (unsigned long long)bytes,
           (unsigned long long)elapsed_us,
           (unsigned long long)kib_s,
           (unsigned long long)(mbps_x1000 / 1000ULL),
           (unsigned long long)(mbps_x1000 % 1000ULL));

    perf_log_add_result(tag, bytes, elapsed_us, 0);
}

void perf_print_latency_result(const char *tag,
                               uint32_t samples,
                               uint64_t min_ticks,
                               uint64_t sum_ticks,
                               uint64_t max_ticks,
                               int status)
{
    uint64_t avg_ticks;
    uint64_t min_ns;
    uint64_t avg_ns;
    uint64_t max_ns;

    if (samples == 0U) {
        printf("[PERF][LAT] %s: no samples status=%d\n", tag, status);
        perf_log_add_latency(tag, 0U, 0ULL, 0ULL, 0ULL, status);
        return;
    }

    avg_ticks = sum_ticks / samples;
    min_ns = perf_ticks_to_ns(min_ticks);
    avg_ns = perf_ticks_to_ns(avg_ticks);
    max_ns = perf_ticks_to_ns(max_ticks);

    printf("[PERF][LAT] %s: samples=%u min=%llu ns avg=%llu ns max=%llu ns status=%d\n",
           tag,
           samples,
           (unsigned long long)min_ns,
           (unsigned long long)avg_ns,
           (unsigned long long)max_ns,
           status);

    perf_log_add_latency(tag, samples, min_ns, avg_ns, max_ns, status);
}

void perf_dmb(void)
{
    __asm__ __volatile__("dmb sy" ::: "memory");
}

void perf_dsb(void)
{
    __asm__ __volatile__("dsb sy" ::: "memory");
}

void perf_isb(void)
{
    __asm__ __volatile__("isb" ::: "memory");
}
