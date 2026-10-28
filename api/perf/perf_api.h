/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: perf_api.h
 *
 * Time a section of code and keep a small in-memory result log.
 */

#ifndef PERF_API_H
#define PERF_API_H

#include <stdint.h>
/* Constant: PERF_LOG_MAX_ENTRIES
 * Maximum number of entries retained in the in-memory performance log ring.
 */

#define PERF_LOG_MAX_ENTRIES 64U
/* Constant: PERF_LOG_TAG_LEN
 * Storage size in bytes of perf_log_entry_t.tag, including space for string termination.
 */
#define PERF_LOG_TAG_LEN     32U

/* Enum: perf_log_type_t
 *
 * Kind of record stored in the performance log.
 *
 * Values:
 *
 *    PERF_LOG_TYPE_NONE - Empty entry.
 *    PERF_LOG_TYPE_THROUGHPUT - bytes, elapsed_us, and rate fields are valid.
 *    PERF_LOG_TYPE_LATENCY - sample count and min/avg/max fields are valid.
 */
typedef enum perf_log_type {
    PERF_LOG_TYPE_NONE = 0,
    PERF_LOG_TYPE_THROUGHPUT = 1,
    PERF_LOG_TYPE_LATENCY = 2,
} perf_log_type_t;

/* Struct: perf_log_entry_t
 *
 * One record in the in-memory performance log. Throughput fields are populated for PERF_LOG_TYPE_THROUGHPUT; latency fields are populated for PERF_LOG_TYPE_LATENCY.
 *
 * Fields:
 *
 *    seq - Monotonic sequence number assigned when the entry is stored.
 *    type - PERF_LOG_TYPE_THROUGHPUT or PERF_LOG_TYPE_LATENCY.
 *    tag - NUL-terminated label stored with the measurement.
 *    status - Caller-supplied status associated with the result.
 *    bytes - Byte count for a throughput result.
 *    elapsed_us - Elapsed time in microseconds for a throughput result.
 *    kib_per_sec - Throughput in KiB per second.
 *    mbps_x1000 - Throughput in megabits per second multiplied by 1000.
 *    samples - Sample count for a latency result.
 *    min_ns - Minimum latency in nanoseconds.
 *    avg_ns - Average latency in nanoseconds.
 *    max_ns - Maximum latency in nanoseconds.
 */
typedef struct perf_log_entry {
    uint32_t seq;
    perf_log_type_t type;
    char tag[PERF_LOG_TAG_LEN];
    int status;

    /* Throughput result fields. */
    uint64_t bytes;
    uint64_t elapsed_us;
    uint64_t kib_per_sec;
    uint64_t mbps_x1000;

    /* Latency result fields. */
    uint32_t samples;
    uint64_t min_ns;
    uint64_t avg_ns;
    uint64_t max_ns;
} perf_log_entry_t;

/* Function: perf_counter_hz
 *
 * Returns the ARM architectural counter frequency in hertz.
 *
 * Returns:
 *
 *    The counter frequency in hertz.
 */
uint64_t perf_counter_hz(void);

/* Function: perf_counter_ticks
 *
 * Reads the current ARM architectural physical counter.
 *
 * Returns:
 *
 *    The current counter value in ticks.
 */
uint64_t perf_counter_ticks(void);

/* Function: perf_ticks_to_us
 *
 * Converts architectural counter ticks to microseconds.
 *
 * Parameters:
 *
 *    ticks - Counter ticks to convert.
 *
 * Returns:
 *
 *    The equivalent duration in microseconds.
 */
uint64_t perf_ticks_to_us(uint64_t ticks);

/* Function: perf_ticks_to_ns
 *
 * Converts architectural counter ticks to nanoseconds.
 *
 * Parameters:
 *
 *    ticks - Counter ticks to convert.
 *
 * Returns:
 *
 *    The equivalent duration in nanoseconds.
 */
uint64_t perf_ticks_to_ns(uint64_t ticks);

/* Function: perf_elapsed_us
 *
 * Returns the elapsed time in microseconds since a previously sampled counter value.
 *
 * Parameters:
 *
 *    start_ticks - Counter value captured at the start of the measurement.
 *
 * Returns:
 *
 *    Elapsed microseconds, or 0 if the current counter value is earlier than start_ticks.
 */
uint64_t perf_elapsed_us(uint64_t start_ticks);

/* Function: perf_elapsed_ns
 *
 * Returns the elapsed time in nanoseconds since a previously sampled counter value.
 *
 * Parameters:
 *
 *    start_ticks - Counter value captured at the start of the measurement.
 *
 * Returns:
 *
 *    Elapsed nanoseconds, or 0 if the current counter value is earlier than start_ticks.
 */
uint64_t perf_elapsed_ns(uint64_t start_ticks);

/* Function: perf_kib_per_sec
 *
 * Calculates throughput in KiB/s from a byte count and elapsed time.
 *
 * Parameters:
 *
 *    bytes - Number of bytes transferred.
 *    elapsed_us - Transfer time in microseconds.
 *
 * Returns:
 *
 *    Throughput in KiB/s, or 0 when elapsed_us is 0.
 */
uint64_t perf_kib_per_sec(uint64_t bytes, uint64_t elapsed_us);

/* Function: perf_mbps_x1000
 *
 * Calculates throughput in megabits per second using a fixed x1000 scale.
 *
 * Parameters:
 *
 *    bytes - Number of bytes transferred.
 *    elapsed_us - Transfer time in microseconds.
 *
 * Returns:
 *
 *    Mbps multiplied by 1000, or 0 when elapsed_us is 0. A value of 12345 represents 12.345 Mbps.
 */
uint64_t perf_mbps_x1000(uint64_t bytes, uint64_t elapsed_us);

/* Function: perf_log_add_result
 *
 * Add one throughput result into the in-memory performance log ring.
 *
 * Parameters:
 *
 *    tag - Short label stored with the entry. May be NULL.
 *    bytes - Byte count recorded for the transfer.
 *    elapsed_us - Elapsed time in microseconds.
 *    status - Caller status stored with the entry.
 */
void perf_log_add_result(const char *tag, uint64_t bytes, uint64_t elapsed_us, int status);

/* Function: perf_log_add_latency
 *
 * Add one latency result into the in-memory performance log ring.
 *
 * Parameters:
 *
 *    tag - Short label stored with the entry. May be NULL.
 *    samples - Number of latency samples.
 *    min_ns - Minimum sample, in nanoseconds.
 *    avg_ns - Average sample, in nanoseconds.
 *    max_ns - Maximum sample, in nanoseconds.
 *    status - Caller status stored with the entry.
 */
void perf_log_add_latency(const char *tag,
                          uint32_t samples,
                          uint64_t min_ns,
                          uint64_t avg_ns,
                          uint64_t max_ns,
                          int status);

/* Function: perf_log_clear
 *
 * Discard every entry in the in-memory performance log.
 */
void perf_log_clear(void);

/* Function: perf_log_count
 *
 * Returns the number of performance entries currently stored in the in-memory log.
 *
 * Returns:
 *
 *    The number of stored log entries.
 */
uint32_t perf_log_count(void);

/* Function: perf_log_dump
 *
 * Print the in-memory performance log.
 */
void perf_log_dump(void);

/* Function: perf_print_result
 *
 * Print one normalized throughput line and store it in the performance log.
 *
 * Parameters:
 *
 *    tag - Short label printed with the result. May be NULL.
 *    bytes - Byte count of the transfer.
 *    elapsed_us - Elapsed time in microseconds.
 */
void perf_print_result(const char *tag, uint64_t bytes, uint64_t elapsed_us);

/* Function: perf_print_result_status
 *
 * Print one normalized throughput line with explicit status and store it.
 *
 * Parameters:
 *
 *    tag - Short label printed with the result. May be NULL.
 *    bytes - Byte count of the transfer.
 *    elapsed_us - Elapsed time in microseconds.
 *    status - Caller status stored with the entry.
 */
void perf_print_result_status(const char *tag, uint64_t bytes, uint64_t elapsed_us, int status);

/* Function: perf_print_latency_result
 *
 * Print one normalized latency line and store it in the performance log.
 *
 * Parameters:
 *
 *    tag - Short label printed with the result. May be NULL.
 *    samples - Number of latency samples.
 *    min_ticks - Smallest sample, in counter ticks.
 *    sum_ticks - Sum of samples, in counter ticks.
 *    max_ticks - Largest sample, in counter ticks.
 *    status - Caller status stored with the entry.
 */
void perf_print_latency_result(const char *tag,
                               uint32_t samples,
                               uint64_t min_ticks,
                               uint64_t sum_ticks,
                               uint64_t max_ticks,
                               int status);

/* Barrier helpers used around benchmark windows. */
/* Function: perf_dmb
 *
 * Execute a data memory barrier around a benchmark window.
 */
void perf_dmb(void);
/* Function: perf_dsb
 *
 * Executes a full-system Data Synchronization Barrier (DSB SY).
 *
 * Returns:
 *
 *    None.
 */
void perf_dsb(void);
/* Function: perf_isb
 *
 * Executes an Instruction Synchronization Barrier (ISB).
 *
 * Returns:
 *
 *    None.
 */
void perf_isb(void);

#endif /* PERF_API_H */