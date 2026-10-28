/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: example_register.h
 *
 * Example Register example registration interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef EXAMPLE_REGISTER_H
#define EXAMPLE_REGISTER_H

/* Callback: register_func_t
 *
 * Callback signature used by the Example Register module.
 *
 * Parameters:
 *
 *    See the typedef prototype for callback argument order and meaning.
 */
typedef void (*register_func_t)(void);

#define APP_REGISTER(func) \
    static const register_func_t __reg_##func \
    __attribute__((used, aligned(8), section(".example_register"))) = (func);

/* Function: app_register
 *
 * Queries the current Example Register state and reports the result to the caller.
 *
 * Returns:
 *
 *    None.
 */
void app_register(void);

#endif