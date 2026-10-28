/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: lib_printf.h
 *
 * Minimal formatted print helpers for freestanding bare-metal builds.
 */

#ifndef __LIB_PRINTF_H__
#define __LIB_PRINTF_H__

#include <stdarg.h>

typedef void (*lib_putc_fn_t)(char c, void *ctx);

int lib_vprintf(lib_putc_fn_t putc_fn, void *ctx, const char *fmt, va_list args);

#endif /* __LIB_PRINTF_H__ */
