/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIB_TIME_H
#define LIB_TIME_H

#include <stdint.h>

uint64_t clock_hz(void);
uint64_t clock_ticks(void);
uint64_t clock_us(void);
uint64_t clock_ns(void);
uint64_t ticks_to_us(uint64_t ticks);
uint64_t ticks_to_ns(uint64_t ticks);
void udelay(uint32_t usec);

#endif /* LIB_TIME_H */
