/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: crt0.h
 *
 * Crt0 common public include interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __CRT0_H__
#define __CRT0_H__

/* Function: crt0_init
 *
 * Initializes the Crt0 block or software context for use.
 *
 * Returns:
 *
 *    None.
 */
void crt0_init(void);
// void dsb(void);

static inline void dsb(void)
{
	__asm__ volatile("dsb sy" ::: "memory");
}


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "errno.h"

/* Type definitions. */
#define portCHAR          char
#define portFLOAT         float
#define portDOUBLE        double
#define portLONG          long
#define portSHORT         short
#define portSTACK_TYPE    size_t
#define portBASE_TYPE     long

/* Type: StackType_t
 *
 * Crt0 typedef used by this interface.
 */
typedef portSTACK_TYPE   StackType_t;
/* Type: BaseType_t
 *
 * Crt0 typedef used by this interface.
 */
typedef portBASE_TYPE    BaseType_t;
/* Type: UBaseType_t
 *
 * Crt0 typedef used by this interface.
 */
typedef uint64_t         UBaseType_t;

/* Type: TickType_t
 *
 * Crt0 typedef used by this interface.
 */
typedef uint64_t         TickType_t;
#define portMAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )


#endif /* __CRT0_H__ */
