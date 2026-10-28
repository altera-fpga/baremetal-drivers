/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: example_register.c
 *
 * Example Register source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Example Register
 */

#include <stdint.h>
#include <stdio.h>
#include "example_register.h"

extern register_func_t __start_example_register[];
extern register_func_t __stop_example_register[];

/* Fallback registration hooks for OCRAM minimal examples. */
void register_hello_world(void) __attribute__((weak));
void register_gic_control(void) __attribute__((weak));
void register_timer_polling(void) __attribute__((weak));
void register_mem_val(void) __attribute__((weak));

static void app_register_fallback(void)
{
    if (register_hello_world != NULL) {
        register_hello_world();
    }
    if (register_gic_control != NULL) {
        register_gic_control();
    }
    if (register_timer_polling != NULL) {
        register_timer_polling();
    }
    if (register_mem_val != NULL) {
        register_mem_val();
    }
}

void app_register(void)
{
    const register_func_t *p = __start_example_register;
    uint32_t count = (uint32_t)(__stop_example_register - __start_example_register);

    if (&__stop_example_register[0] < &__start_example_register[0]) {
        app_register_fallback();
        return;
    }

    /* Keep the registration walk bounded if the linker symbols are corrupted. */
    if (count > 96U) {
        app_register_fallback();
        return;
    }

    /* Some build profiles may not populate the linker section reliably. */
    if (count == 0U) {
        app_register_fallback();
        return;
    }

    for (uint32_t i = 0; i < count; i++, p++) {
        uintptr_t fn = (uintptr_t)(*p);

        if (fn == 0U) {
            continue;
        }

        /* alignment sanity only */
        if ((fn & 0x3U) != 0U) {
            continue;
        }

        (*p)();
    }
}
