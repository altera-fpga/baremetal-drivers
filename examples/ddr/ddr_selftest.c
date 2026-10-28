/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ddr_selftest.c
 * Layer: examples
 * Component: Mem Validation
 */

#include <stdint.h>
#include <stdio.h>
#include "errno.h"
#include "../api/console/console_api.h"
#include "example_register.h"

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
#include "../../drivers/ddr/socfpga_ddr.h"
#endif

/*
 * Destructive DDR scratch window.
 *
 * Must stay above linker_ddr.ld _stack_top (0x81300000) so BIST does not
 * clobber .bss/stack and hang before CLI returns.
 * Also stay above reserved scratch used elsewhere in this tree:
 *   BL31_LIMIT 0x82000000, mailbox 0x82100000, mailbox DMA 0x822/0x82300000.
 */
#define DDR_BIST_BASE   0x83000000UL
#define DDR_BIST_SIZE   (16UL * 1024UL * 1024UL)

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
static volatile uint32_t ocram_fallback_memval[4096]; /* 16 KB safe window */
#define OCRAM_FALLBACK_BASE ((unsigned long)(uintptr_t)ocram_fallback_memval)
#define OCRAM_FALLBACK_SIZE ((unsigned long)sizeof(ocram_fallback_memval))
#endif

/* Optional barrier helper for Cortex-A */
static inline void dmb(void)
{
    __asm__ __volatile__("dmb sy" ::: "memory");
}

/* --------------------------------------------------------- */

static uint32_t pattern_test(volatile uint32_t *mem, uint32_t words, uint32_t pattern)
{
    uint32_t errs = 0U;

    for (uint32_t i = 0; i < words; i++)
        mem[i] = pattern;

    dmb();

    for (uint32_t i = 0; i < words; i++)
        if (mem[i] != pattern)
            errs++;

    return errs;
}

/* --------------------------------------------------------- */

static uint32_t walking_bit_test(volatile uint32_t *mem, uint32_t words)
{
    uint32_t errs = 0U;

    for (uint32_t bit = 0; bit < 32; bit++) {
        uint32_t pattern = (1u << bit);

        for (uint32_t i = 0; i < words; i++)
            mem[i] = pattern;

        dmb();

        for (uint32_t i = 0; i < words; i++)
            if (mem[i] != pattern)
                errs++;
    }

    return errs;
}

/* --------------------------------------------------------- */

static uint32_t address_test(volatile uint32_t *mem, uint32_t words)
{
    uint32_t errs = 0U;

    for (uint32_t i = 0; i < words; i++)
        mem[i] = i;

    dmb();

    for (uint32_t i = 0; i < words; i++)
        if (mem[i] != i)
            errs++;

    return errs;
}

/* --------------------------------------------------------- */

static uint32_t march_test(volatile uint32_t *mem, uint32_t words)
{
    uint32_t errs = 0U;

    /* Up write 0 */
    for (uint32_t i = 0; i < words; i++)
        mem[i] = 0;

    dmb();

    /* Up read 0, write 1 */
    for (uint32_t i = 0; i < words; i++) {
        if (mem[i] != 0)
            errs++;
        mem[i] = 1;
    }

    dmb();

    /* Down read 1, write 0 */
    for (int64_t i = (int64_t)words - 1; i >= 0; i--) {
        if (mem[i] != 1)
            errs++;
        mem[i] = 0;
    }

    dmb();

    /* Down read 0 */
    for (int64_t i = (int64_t)words - 1; i >= 0; i--) {
        if (mem[i] != 0)
            errs++;
    }

    return errs;
}

/* --------------------------------------------------------- */

static void run_mem_validation_suite(unsigned long base, unsigned long size)
{
    volatile uint32_t *mem = (volatile uint32_t *)(uintptr_t)base;
    uint32_t words = (uint32_t)(size / sizeof(uint32_t));
    uint32_t tests_passed = 0U;
    uint32_t errs;

    printf("Region: 0x%08lx - 0x%08lx (%lu MB)\n\n",
           base,
           (unsigned long)(base + size - 1),
           size / (1024UL * 1024UL));

    /* ---------------------------------------------------------------- */
    printf("Test 1 of 4 : Fixed data-pattern test\n");
    printf("------------------------------------------------------------\n");
    {
        static const uint32_t patterns[] = {
            0x00000000U, 0xFFFFFFFFU, 0xAAAAAAAAU, 0x55555555U,
        };
        uint32_t pat_errs = 0U;

        for (unsigned p = 0; p < (sizeof(patterns) / sizeof(patterns[0])); p++) {
            printf("  Pattern 0x%08x ....................... ", patterns[p]);
            errs = pattern_test(mem, words, patterns[p]);
            pat_errs += errs;
            if (errs == 0U) {
                printf("PASS\n");
            } else {
                printf("FAIL (%u errors)\n", errs);
            }
        }

        if (pat_errs == 0U) {
            tests_passed++;
        }
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("Test 2 of 4 : Walking-bit test\n");
    printf("------------------------------------------------------------\n");
    printf("  Walk 32 single-bit patterns ............... ");
    errs = walking_bit_test(mem, words);
    if (errs == 0U) {
        printf("PASS\n");
        tests_passed++;
    } else {
        printf("FAIL (%u errors)\n", errs);
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("Test 3 of 4 : Address-uniqueness test\n");
    printf("------------------------------------------------------------\n");
    printf("  Write/verify unique address values ........ ");
    errs = address_test(mem, words);
    if (errs == 0U) {
        printf("PASS\n");
        tests_passed++;
    } else {
        printf("FAIL (%u errors)\n", errs);
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("Test 4 of 4 : March C- test\n");
    printf("------------------------------------------------------------\n");
    printf("  March C- up/down sweeps ................... ");
    errs = march_test(mem, words);
    if (errs == 0U) {
        printf("PASS\n");
        tests_passed++;
    } else {
        printf("FAIL (%u errors)\n", errs);
    }
    printf("------------------------------------------------------------\n");

    printf("\n");
    printf("RESULT : %u of 4 tests passed  -  SELF-TEST %s\n",
            tests_passed, (tests_passed == 4U) ? "PASSED" : "FAILED");
    printf("\n");
}

void ddr_bist_main(const char *args)
{
    (void)args;

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
    int ret;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  DDR BIST / INIT COMMAND                   |\n");
    printf("+------------------------------------------------------------+\n");
    printf("Mode  : Agilex5 OCRAM on-demand DDR bring-up\n");
    printf("Step 1: Run IOSSM/DDR init flow (ATF-compatible) ... ");

    ret = ddr_init();
    if (ret != 0) {
        if (ret == -EOPNOTSUPP) {
            printf("SKIPPED (ret=%d)\n", ret);
            printf("Reason: DDR init is unsupported in JTAG Config flow.\n");
            printf("\n");
            printf("Step 2: Run fallback memory validation (OCRAM safe mode)\n");
            printf("------------------------------------------------------------\n");
            run_mem_validation_suite(OCRAM_FALLBACK_BASE, OCRAM_FALLBACK_SIZE);
            printf("Result: DDR stage skipped; fallback memory validation completed.\n\n");
            return;
        }

        printf("FAIL (ret=%d)\n", ret);
        printf("Result: DDR init/BIST flow did not complete.\n\n");
        return;
    }

    printf("PASS\n");
    printf("\n");
    printf("Step 2: Run DDR memory validation suite\n");
    printf("------------------------------------------------------------\n");
    run_mem_validation_suite(DDR_BIST_BASE, DDR_BIST_SIZE);
#else
    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  DDR BIST / INIT COMMAND                   |\n");
    printf("+------------------------------------------------------------+\n");
    printf("Mode  : Direct DDR validation (no OCRAM DDR-init stage)\n\n");
    run_mem_validation_suite(DDR_BIST_BASE, DDR_BIST_SIZE);
#endif
}

void register_mem_val(void) {
    cli_register_command("ddr_selftest", ddr_bist_main);
}

// Auto-register into special section
APP_REGISTER(register_mem_val)
