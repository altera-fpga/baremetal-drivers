/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "lib_time.h"

static void fallback_delay(uint32_t usec)
{
    volatile uint64_t loops = (uint64_t)usec * 200ULL;

    while (loops-- != 0U) {
        __asm__ volatile("nop");
    }
}

uint64_t clock_hz(void)
{
    uint64_t hz = 0U;

#if defined(__aarch64__)
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(hz));
#endif
    return hz;
}

uint64_t clock_ticks(void)
{
    uint64_t ticks = 0U;

#if defined(__aarch64__)
    __asm__ volatile("isb" ::: "memory");
    __asm__ volatile("mrs %0, cntpct_el0" : "=r"(ticks));
#endif
    return ticks;
}

uint64_t ticks_to_us(uint64_t ticks)
{
    uint64_t hz = clock_hz();

    if (hz == 0ULL) {
        return 0ULL;
    }

    return (ticks * 1000000ULL) / hz;
}

uint64_t ticks_to_ns(uint64_t ticks)
{
    uint64_t hz = clock_hz();

    if (hz == 0ULL) {
        return 0ULL;
    }

    return (ticks * 1000000000ULL) / hz;
}

uint64_t clock_us(void)
{
    return ticks_to_us(clock_ticks());
}

uint64_t clock_ns(void)
{
    return ticks_to_ns(clock_ticks());
}

void udelay(uint32_t usec)
{
    uint64_t hz = clock_hz();

    if (hz != 0U) {
        uint64_t start = clock_us();

        while ((clock_us() - start) < (uint64_t)usec) {
            /* spin */
        }
        return;
    }

    fallback_delay(usec);
}
