/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: gic_selftest.c
 * Layer: examples
 * Component: Gic Control
 */

#include <stdio.h>
#include <stdint.h>
#include "../api/console/console_api.h"
#include "gic_api.h"
#include "example_register.h"

/* ISR state, updated from interrupt context. */
static volatile uint32_t sgi_hit_count = 0U;
static volatile uint32_t sgi_last_irq = 0U;
static uint32_t sgi_irq_positive = 1U;
static uint32_t sgi_irq_negative = 2U;

static void test_isr(void *data)
{
    uint32_t irq = (data != NULL) ? *(uint32_t *)data : 0U;
    sgi_last_irq = irq;
    sgi_hit_count++;
}

static void gic_prepare_environment(void)
{
    uint64_t currentel;
    uint64_t scr;
    uint64_t hcr;

    /* Ensure GIC and redistributor are initialized before using the SGI path. */
    gic_api_init();

    /* Configure physical interrupt routing for the current exception level. */
    __asm__ volatile ("mrs %0, CurrentEL" : "=r" (currentel));
    if ((currentel & 0xCU) == 0xCU) {
        /* EL3: route physical IRQ/FIQ to EL3 (SCR_EL3.IRQ | SCR_EL3.FIQ). */
        __asm__ volatile ("mrs %0, scr_el3" : "=r" (scr));
        scr |= (1ULL << 1) | (1ULL << 2);
        __asm__ volatile ("msr scr_el3, %0" : : "r" (scr));
        __asm__ volatile ("isb" : : : "memory");
    } else if ((currentel & 0xCU) == 0x8U) {
        /* EL2: set HCR_EL2.IMO (bit 4) so physical interrupts are taken to EL2. */
        __asm__ volatile ("mrs %0, hcr_el2" : "=r" (hcr));
        hcr |= (1ULL << 4);
        __asm__ volatile ("msr hcr_el2, %0" : : "r" (hcr));
        __asm__ volatile ("isb" : : : "memory");
    }

    /* Clear the PSTATE exception masks (D, A, I, F) to enable interrupt delivery. */
    __asm__ volatile(
        "msr daifclr, #0xF \n\t"
        "dsb sy \n\t"
        "isb \n\t"
        : : : "memory"
    );
}

static uint32_t gic_wait_for_irq(uint32_t timeout)
{
    while ((sgi_hit_count == 0U) && timeout--) {
        __asm__ volatile("nop" : : : "memory");
    }

    return sgi_hit_count;
}

static void gic_sgi_selftest_main(const char *args)
{
    (void)args;
    socfpga_interrupt_err_t err;
    uint32_t tests_passed = 0U;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|              GIC SGI INTERRUPT SELF-TEST                   |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Initializing GIC environment ................ ");
    gic_prepare_environment();
    printf("done\n\n");

    /* ---------------------------------------------------------------- */
    printf("Test 1 of 2 : Masked SGI must NOT be delivered\n");
    printf("------------------------------------------------------------\n");

    sgi_hit_count = 0U;
    sgi_last_irq = 0U;

    printf("  Register ISR for SGI %u .................... ", sgi_irq_negative);
    err = gic_api_register_isr(sgi_irq_negative, test_isr, &sgi_irq_negative);
    if (err != ERR_OK) {
        printf("FAIL (err=%d)\n", err);
        goto summary;
    }
    printf("OK\n");

    printf("  Trigger SGI %u while disabled .............. ", sgi_irq_negative);
    err = gic_api_trigger_sgi(sgi_irq_negative, 0x1U);
    if (err != ERR_OK) {
        printf("FAIL (err=%d)\n", err);
        goto summary;
    }
    printf("OK\n");

    printf("  Verify no ISR was invoked ................. ");
    if (gic_wait_for_irq(2000000U) == 0U) {
        printf("PASS\n");
        tests_passed++;
    } else {
        printf("FAIL (unexpected IRQ=%u, count=%u)\n",
                (uint32_t)sgi_last_irq, (uint32_t)sgi_hit_count);
        goto summary;
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("Test 2 of 2 : Enabled SGI must be delivered\n");
    printf("------------------------------------------------------------\n");

    sgi_hit_count = 0U;
    sgi_last_irq = 0U;

    printf("  Register ISR for SGI %u .................... ", sgi_irq_positive);
    err = gic_api_register_isr(sgi_irq_positive, test_isr, &sgi_irq_positive);
    if (err != ERR_OK) {
        printf("FAIL (err=%d)\n", err);
        goto summary;
    }
    printf("OK\n");

    printf("  Enable SGI %u .............................. ", sgi_irq_positive);
    err = gic_api_enable(sgi_irq_positive, 0x80U);
    if (err != ERR_OK) {
        printf("FAIL (err=%d)\n", err);
        goto summary;
    }
    printf("OK\n");

    printf("  Trigger SGI %u ............................. ", sgi_irq_positive);
    err = gic_api_trigger_sgi(sgi_irq_positive, 0x1U);
    if (err != ERR_OK) {
        printf("FAIL (err=%d)\n", err);
        goto summary;
    }
    printf("OK\n");

    printf("  Verify ISR was invoked .................... ");
    if (gic_wait_for_irq(5000000U) > 0U) {
        printf("PASS (IRQ=%u, count=%u)\n",
                (uint32_t)sgi_last_irq, (uint32_t)sgi_hit_count);
        tests_passed++;
    } else {
        printf("FAIL (timeout)\n");
    }
    printf("------------------------------------------------------------\n");

summary:
    printf("\n");
    printf("RESULT : %u of 2 tests passed  -  SELF-TEST %s\n",
            tests_passed, (tests_passed == 2U) ? "PASSED" : "FAILED");
    printf("\n");
}

/* CLI registration wrapper */
void register_gic_control(void)
{
    cli_register_command("gic_selftest", gic_sgi_selftest_main);
}

APP_REGISTER(register_gic_control)
