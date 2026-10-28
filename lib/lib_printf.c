/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: lib_printf.c
 *
 * Minimal formatted print helpers for freestanding bare-metal builds.
 */

#include <stdint.h>
#include <stddef.h>
#include "lib_printf.h"

static void lib_puts(lib_putc_fn_t putc_fn, void *ctx, const char *s)
{
    if (s == NULL) {
        s = "(null)";
    }

    while (*s != '\0') {
        putc_fn(*s++, ctx);
    }
}

static void lib_print_uint(lib_putc_fn_t putc_fn, void *ctx,
                           uint32_t value, int base, int width, char pad)
{
    char buf[32];
    int i = 0;
    const char *alnum = "0123456789ABCDEF";

    if (value == 0U) {
        buf[i++] = '0';
    } else {
        while (value > 0U) {
            buf[i++] = alnum[value % (uint32_t)base];
            value /= (uint32_t)base;
        }
    }

    while (i < width) {
        buf[i++] = pad;
    }

    while (i > 0) {
        putc_fn(buf[--i], ctx);
    }
}

static void lib_print_uint64(lib_putc_fn_t putc_fn, void *ctx,
                             uint64_t value, int base, int width, char pad)
{
    char buf[64];
    int i = 0;
    const char *alnum = "0123456789ABCDEF";

    if (value == 0U) {
        buf[i++] = '0';
    } else {
        while (value > 0U) {
            buf[i++] = alnum[value % (uint64_t)base];
            value /= (uint64_t)base;
        }
    }

    while (i < width) {
        buf[i++] = pad;
    }

    while (i > 0) {
        putc_fn(buf[--i], ctx);
    }
}

static void lib_print_int(lib_putc_fn_t putc_fn, void *ctx,
                          int32_t value, int width, char pad)
{
    if (value < 0) {
        putc_fn('-', ctx);
        value = -value;
        if (width > 0) {
            width--;
        }
    }

    lib_print_uint(putc_fn, ctx, (uint32_t)value, 10, width, pad);
}

int lib_vprintf(lib_putc_fn_t putc_fn, void *ctx, const char *fmt, va_list args)
{
    int count = 0;

    if ((putc_fn == NULL) || (fmt == NULL)) {
        return 0;
    }

    while (*fmt != '\0') {
        if (*fmt == '%') {
            int width = 0;
            char pad = ' ';
            int is_longlong = 0;

            fmt++;

            if (*fmt == '0') {
                pad = '0';
                fmt++;
            }

            while ((*fmt >= '0') && (*fmt <= '9')) {
                width = (width * 10) + (*fmt - '0');
                fmt++;
            }

            if (*fmt == 'l') {
                fmt++;
                if (*fmt == 'l') {
                    is_longlong = 1;
                    fmt++;
                }
            }

            switch (*fmt) {
            case 'c':
                putc_fn((char)va_arg(args, int), ctx);
                count++;
                break;

            case 's':
                lib_puts(putc_fn, ctx, va_arg(args, const char *));
                count++;
                break;

            case 'd':
            case 'i':
                if (is_longlong != 0) {
                    int64_t num = va_arg(args, int64_t);
                    if (num < 0) {
                        putc_fn('-', ctx);
                        num = -num;
                    }
                    lib_print_uint64(putc_fn, ctx, (uint64_t)num, 10, width, pad);
                } else {
                    lib_print_int(putc_fn, ctx, va_arg(args, int32_t), width, pad);
                }
                count++;
                break;

            case 'u':
                if (is_longlong != 0) {
                    lib_print_uint64(putc_fn, ctx, va_arg(args, uint64_t), 10, width, pad);
                } else {
                    lib_print_uint(putc_fn, ctx, va_arg(args, uint32_t), 10, width, pad);
                }
                count++;
                break;

            case 'x':
            case 'X':
                if (is_longlong != 0) {
                    lib_print_uint64(putc_fn, ctx, va_arg(args, uint64_t), 16, width, pad);
                } else {
                    lib_print_uint(putc_fn, ctx, va_arg(args, uint32_t), 16, width, pad);
                }
                count++;
                break;

            case 'p':
                lib_puts(putc_fn, ctx, "0x");
                lib_print_uint64(putc_fn, ctx,
                                 (uint64_t)(uintptr_t)va_arg(args, void *),
                                 16, 16, '0');
                count++;
                break;

            case '%':
                putc_fn('%', ctx);
                count++;
                break;

            default:
                putc_fn('%', ctx);
                putc_fn(*fmt, ctx);
                count += 2;
                break;
            }

            if (*fmt != '\0') {
                fmt++;
            }
        } else {
            putc_fn(*fmt++, ctx);
            count++;
        }
    }

    return count;
}
