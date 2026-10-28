/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: lib_parse.c
 *
 * Minimal parsing and compare helpers for freestanding bare-metal builds.
 */

#include <stdint.h>
#include "lib_parse.h"

int cstrcmp(const char *a, const char *b)
{
    while ((*a != '\0') && (*b != '\0') && (*a == *b)) {
        a++;
        b++;
    }

    return (int)((unsigned char)*a - (unsigned char)*b);
}

uint64_t parse_hex(const char *s)
{
    uint64_t val = 0;

    if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X'))) {
        s += 2;
    }

    while (*s != '\0') {
        char c = *s++;
        uint8_t v;

        if ((c >= '0') && (c <= '9')) {
            v = (uint8_t)(c - '0');
        } else if ((c >= 'a') && (c <= 'f')) {
            v = (uint8_t)(10 + (c - 'a'));
        } else if ((c >= 'A') && (c <= 'F')) {
            v = (uint8_t)(10 + (c - 'A'));
        } else {
            break;
        }

        val = (val << 4U) | v;
    }

    return val;
}

uint32_t parse_dec(const char *s)
{
    uint32_t val = 0;

    while ((*s >= '0') && (*s <= '9')) {
        val = (val * 10U) + (uint32_t)(*s - '0');
        s++;
    }

    return val;
}
