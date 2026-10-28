/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: lib_parse.h
 *
 * Minimal parsing and compare helpers for freestanding bare-metal builds.
 */

#ifndef __LIB_PARSE_H__
#define __LIB_PARSE_H__

#include <stdint.h>

int cstrcmp(const char *a, const char *b);
uint64_t parse_hex(const char *s);
uint32_t parse_dec(const char *s);

#endif /* __LIB_PARSE_H__ */
