/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: crt0.c
 *
 * Crt0 source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: src
 * Component: Crt0
 */

#include <stdint.h>
#include <stddef.h>

extern uint8_t __ldata;   /* LOADADDR(.data) */
extern uint8_t __sdata;   /* VMA start .data */
extern uint8_t __edata;   /* VMA end .data */
extern uint8_t __sbss;    /* VMA start .bss */
extern uint8_t __ebss;    /* VMA end .bss */

void crt0_init(void)
{
	uint8_t *src = &__ldata;
	uint8_t *dst = &__sdata;
	uint8_t *ed  = &__edata;

	/* If data is already in place (LOADADDR == VMA) skip copy */
	if (src != dst) {
		while (dst < ed) {
			*dst++ = *src++;
		}
	}

	/* Zero initialize .bss */
	dst = &__sbss;
	ed  = &__ebss;
	while (dst < ed) {
		*dst++ = 0;
	}
}