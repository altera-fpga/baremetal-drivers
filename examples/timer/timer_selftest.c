/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: timer_selftest.c
 * Layer: examples
 * Component: Timer Polling
 */

#include <stdio.h>
#include <stdint.h>
#include "../api/console/console_api.h"
#include "timer_api.h"
#include "example_register.h"

#define TIMER_INSTANCE    TIMER_SYS0    /* Choose the timer instance */
#define TIMER_PERIOD_US   1000000U      /* 1 second period */
#define TIMER_POLL_DELAY  1000000U      /* Busy-wait loop count between polls */

static void timer_busy_wait(void)
{
    volatile uint32_t wait = 0U;
    for (uint32_t j = 0U; j < TIMER_POLL_DELAY; j++) {
        wait++;
    }
}

static void timer_polling_main(const char *args)
{
    (void)args;
    timer_handle_t timer;
    uint32_t tests_passed = 0U;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                TIMER POLLING SELF-TEST                     |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Using timer instance %d with period %u us\n\n",
           TIMER_INSTANCE, TIMER_PERIOD_US);

    /* ---------------------------------------------------------------- */
    printf("Test 1 of 2 : Timer must start and advance\n");
    printf("------------------------------------------------------------\n");

    printf("  Open timer instance ....................... ");
    timer = timer_open(TIMER_INSTANCE);
    if (timer == NULL) {
        printf("FAIL (open returned NULL)\n");
        goto summary;
    }
    printf("OK\n");

    printf("  Set timer period to %u us ............. ", TIMER_PERIOD_US);
    if (timer_set_period_us(timer, TIMER_PERIOD_US) != 0) {
        printf("FAIL\n");
        goto summary;
    }
    printf("OK\n");

    printf("  Start timer ............................... ");
    if (timer_start(timer) != 0) {
        printf("FAIL\n");
        goto summary;
    }
    printf("OK\n");

    {
        uint32_t first_us = 0U;
        uint32_t second_us = 0U;

        printf("  Read timer value .......................... ");
        timer_get_time_us(timer, &first_us);
        timer_busy_wait();
        timer_get_time_us(timer, &second_us);
        printf("OK (%u us -> %u us)\n", first_us, second_us);

        printf("  Verify timer advanced ..................... ");
        if (second_us != first_us) {
            printf("PASS\n");
            tests_passed++;
        } else {
            printf("FAIL (value did not change)\n");
            goto summary;
        }
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("Test 2 of 2 : Timer polling over multiple samples\n");
    printf("------------------------------------------------------------\n");

    {
        uint32_t samples_ok = 1U;

        for (int i = 0; i < 5; i++) {
            uint32_t time_us = 0U;
            printf("  Sample %d of 5 ............................. ", i + 1);
            timer_get_time_us(timer, &time_us);
            printf("%u us\n", time_us);
            timer_busy_wait();
        }

        printf("  Stop timer ................................ ");
        if (timer_stop(timer) != 0) {
            printf("FAIL\n");
            samples_ok = 0U;
        } else {
            printf("OK\n");
        }

        printf("  Verify polling completed .................. ");
        if (samples_ok != 0U) {
            printf("PASS\n");
            tests_passed++;
        } else {
            printf("FAIL\n");
        }
    }
    printf("------------------------------------------------------------\n");

summary:
    printf("\n");
    printf("RESULT : %u of 2 tests passed  -  SELF-TEST %s\n",
            tests_passed, (tests_passed == 2U) ? "PASSED" : "FAILED");
    printf("\n");
}

/* CLI registration wrapper */
void register_timer_polling(void)
{
    cli_register_command("timer_selftest", timer_polling_main);
}

/* Auto-register into special section for boot-time registration */
APP_REGISTER(register_timer_polling)

