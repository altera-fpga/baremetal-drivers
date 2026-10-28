/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ecc_selftest.c
 *
 * Ecc Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Ecc Example
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "../api/console/console_api.h"
#include "ecc_api.h"
#include "example_register.h"

/*
 * OCRAM probe address: well inside the 256 KB OCRAM aperture but
 * outside .text / .rodata / vector table at the start of OCRAM_CODE.
 */
#define ECC_DEMO_OCRAM_PROBE_ADDR  0x00010000UL

#define PF(rc)  (((rc) == ECC_API_OK) ? "PASS" : "FAIL")

/*
 * Demo callback - prints a one-line trace and is purposely minimal so
 * it stays safe inside an ISR.
 */
static volatile uint32_t s_cb_events;

static void ecc_demo_cb(uint32_t block, uint32_t err_type)
{
    s_cb_events++;
    printf("ECC[cb]: %s %s (events=%u)\n",
           ecc_api_block_name(block),
           (err_type == ECC_API_ERR_SBE) ? "SBE" : "DBE",
           (unsigned)s_cb_events);
}

/* ----------------------------------------------------------------------- */
/* Helpers                                                                 */
/* ----------------------------------------------------------------------- */

static void ecc_demo_print_status(void)
{
    uint32_t serr = ecc_api_get_serr_status();
    uint32_t derr = ecc_api_get_derr_status();

    printf("ECC: sysmgr SERR=0x%08X DERR=0x%08X\n",
           (unsigned)serr, (unsigned)derr);
}

static void ecc_demo_print_counters(uint32_t block)
{
    int32_t sbe    = ecc_api_get_sbe_count(block);
    int32_t dbe    = ecc_api_get_dbe_count(block);
    int32_t hw_sbe = ecc_api_get_hw_sbe_count(block);

    if (hw_sbe >= 0) {
        printf("ECC: %s sbe=%d dbe=%d (hw_s_err_cnt=%d)\n",
               ecc_api_block_name(block),
               (int)sbe, (int)dbe, (int)hw_sbe);
    } else {
        printf("ECC: %s sbe=%d dbe=%d\n",
               ecc_api_block_name(block),
               (int)sbe, (int)dbe);
    }
}

/*
 * Touch a memory location read-only so the ECC engine performs its
 * compare. The address is routed through a volatile uintptr_t to hide
 * it from the optimiser - otherwise low OCRAM addresses look like
 * NULL-derefs and trip -Warray-bounds at -O2.
 */
static uint32_t ecc_demo_probe_read32(uintptr_t addr)
{
    volatile uintptr_t guarded = addr;
    volatile uint32_t *p = (volatile uint32_t *)guarded;
    return *p;
}

static int ecc_demo_streq(const char *a, const char *b)
{
    if ((a == NULL) || (b == NULL)) {
        return 0;
    }
    while ((*a != '\0') && (*b != '\0')) {
        if (*a != *b) {
            return 0;
        }
        ++a;
        ++b;
    }
    return ((*a == '\0') && (*b == '\0')) ? 1 : 0;
}

static const char *ecc_demo_skip_ws(const char *s)
{
    if (s == NULL) {
        return "";
    }
    while (*s == ' ') {
        ++s;
    }
    return s;
}

/* ----------------------------------------------------------------------- */
/* Per-case helpers                                                        */
/* ----------------------------------------------------------------------- */

static int ecc_demo_inject_block_and_probe(uint32_t block, uint32_t err_type,
                                           uintptr_t probe_addr)
{
    int32_t  rc;
    uint32_t sample;

    rc = ecc_api_inject_block(block, err_type);
    printf("[ECC][%s] inject %s on %s rc=%d\n",
           PF(rc),
           (err_type == ECC_API_ERR_SBE) ? "SBE" : "DBE",
           ecc_api_block_name(block),
           (int)rc);
    if (rc != ECC_API_OK) {
        return rc;
    }

    /* Trigger a read to provoke the ECC compare. */
    sample = ecc_demo_probe_read32(probe_addr);
    printf("ECC: probe 0x%08lX -> 0x%08X\n",
           (unsigned long)probe_addr, (unsigned)sample);

    /* On platforms where the SERR_GLOBAL / ECC_DERR_INTR_N GIC SPIs are
     * not delivered (e.g. simulation models), pull the System Manager status
     * register manually so the per-block counters still reflect the
     * injected event. */
    {
        uint32_t s_bits = 0U;
        uint32_t d_bits = 0U;
        int32_t  events = ecc_api_poll_status(&s_bits, &d_bits);
        if (events != 0) {
            printf("ECC: poll handled %d event(s) "
                   "(SERR=0x%08X DERR=0x%08X)\n",
                   (int)events, (unsigned)s_bits, (unsigned)d_bits);
        }
    }

    ecc_demo_print_counters(block);
    ecc_demo_print_status();
    return ECC_API_OK;
}

static int ecc_demo_counter_for_type(uint32_t block, uint32_t err_type)
{
    if (err_type == ECC_API_ERR_SBE) {
        return ecc_api_get_sbe_count(block);
    }

    return ecc_api_get_dbe_count(block);
}

static int32_t ecc_bist_run_case(uint32_t err_type)
{
    const uint32_t block = ECC_API_BLOCK_OCRAM;
    const char *label = (err_type == ECC_API_ERR_SBE) ? "SBE" : "DBE";
    int32_t rc;
    int before_count;
    int after_count;
    uint32_t before_events;
    uint32_t after_events;
    int32_t result = ECC_API_ERROR;

    s_cb_events = 0U;

    rc = ecc_api_init();
    if (rc != ECC_API_OK) {
        printf("[ECC_BIST][FAIL] OCRAM %s init rc=%d\n", label, (int)rc);
        return rc;
    }

    (void)ecc_api_set_callback(ecc_demo_cb);
    (void)ecc_api_clear_counters(block);

    rc = ecc_api_enable(1U << block);
    if (rc != ECC_API_OK) {
        printf("[ECC_BIST][FAIL] OCRAM %s enable rc=%d\n", label, (int)rc);
        goto out;
    }

    before_count = ecc_demo_counter_for_type(block, err_type);
    before_events = s_cb_events;

    rc = ecc_demo_inject_block_and_probe(block, err_type,
                                         ECC_DEMO_OCRAM_PROBE_ADDR);
    if (rc != ECC_API_OK) {
        printf("[ECC_BIST][FAIL] OCRAM %s inject/probe rc=%d\n",
               label, (int)rc);
        goto out;
    }

    after_count = ecc_demo_counter_for_type(block, err_type);
    after_events = s_cb_events;

    /*
     * Pass on software counter bump. inject path calls ecc_api_poll_status(),
     * which updates counters but does NOT invoke the user callback
     * (socfpga_ecc_poll_status). Requiring cb growth false-fails when the
     * OCRAM ECC hardware path is actually working.
     */
    if ((before_count >= 0) && (after_count > before_count)) {
        printf("[ECC_BIST][PASS] OCRAM %s observed "
               "(count %d -> %d, cb %u -> %u)\n",
               label,
               before_count,
               after_count,
               (unsigned)before_events,
               (unsigned)after_events);
        result = ECC_API_OK;
    } else {
        printf("[ECC_BIST][FAIL] OCRAM %s not observed "
               "(count %d -> %d, cb %u -> %u)\n",
               label,
               before_count,
               after_count,
               (unsigned)before_events,
               (unsigned)after_events);
    }

out:
    (void)ecc_api_disable(1U << block);
    (void)ecc_api_deinit();
    return result;
}

static void ecc_bist_run(void)
{
    int32_t sbe_rc;
    int32_t dbe_rc;

    printf("\n=== ECC BIST ===\n\n");
    printf("Target: OCRAM ECC hardware path\n");
    printf("Method: inject SBE/DBE, force readback, verify counters "
           "(callback optional; poll path does not fire it)\n\n");

    sbe_rc = ecc_bist_run_case(ECC_API_ERR_SBE);
    dbe_rc = ecc_bist_run_case(ECC_API_ERR_DBE);

    if ((sbe_rc == ECC_API_OK) && (dbe_rc == ECC_API_OK)) {
        printf("\n[ECC_BIST][PASS] OCRAM ECC BIST complete\n");
    } else {
        printf("\n[ECC_BIST][FAIL] OCRAM ECC BIST incomplete\n");
    }
}

/* ----------------------------------------------------------------------- */
/* Full demo                                                               */
/* ----------------------------------------------------------------------- */

static void ecc_demo_run(void)
{
    int32_t rc;

    printf("\n=== ECC Demo ===\n\n");

    printf("[Step 1] init + register callback\n");
    rc = ecc_api_init();
    printf("[ECC][%s] ecc_api_init rc=%d\n", PF(rc), (int)rc);
    if (rc != ECC_API_OK) {
        return;
    }
    (void)ecc_api_set_callback(ecc_demo_cb);

    printf("\n[Step 2] enable OCRAM ECC\n");
    rc = ecc_api_enable(ECC_API_BLOCK_MASK_ALL_HPS_MMIO);
    printf("[ECC][%s] ecc_api_enable rc=%d\n", PF(rc), (int)rc);
    if (rc != ECC_API_OK) {
        printf("ECC: no HPS block came up; aborting demo\n");
        (void)ecc_api_deinit();
        return;
    }

    printf("\n[Step 3] OCRAM SBE\n");
    (void)ecc_demo_inject_block_and_probe(ECC_API_BLOCK_OCRAM,
                                          ECC_API_ERR_SBE,
                                          ECC_DEMO_OCRAM_PROBE_ADDR);

    printf("\n[Step 4] OCRAM DBE\n");
    (void)ecc_demo_inject_block_and_probe(ECC_API_BLOCK_OCRAM,
                                          ECC_API_ERR_DBE,
                                          ECC_DEMO_OCRAM_PROBE_ADDR);

    printf("\n[Step 5] disable blocks + deinit\n");
    rc = ecc_api_disable(ECC_API_BLOCK_MASK_ALL_HPS_MMIO);
    printf("[ECC][%s] ecc_api_disable rc=%d\n", PF(rc), (int)rc);

    rc = ecc_api_deinit();
    printf("[ECC][%s] ecc_api_deinit rc=%d\n", PF(rc), (int)rc);

    printf("\n=== ECC Demo complete (cb_events=%u) ===\n",
           (unsigned)s_cb_events);
}

/* ----------------------------------------------------------------------- */
/* CLI dispatch                                                            */
/* ----------------------------------------------------------------------- */

static void ecc_demo_run_single(uint32_t block, uint32_t err_type,
                                uintptr_t probe_addr)
{
    int32_t rc;

    rc = ecc_api_init();
    if (rc != ECC_API_OK) {
        printf("[ECC][FAIL] init rc=%d\n", (int)rc);
        return;
    }
    (void)ecc_api_set_callback(ecc_demo_cb);
    (void)ecc_api_enable(1U << block);

    (void)ecc_demo_inject_block_and_probe(block, err_type, probe_addr);

    (void)ecc_api_disable(1U << block);
    (void)ecc_api_deinit();
}

static void ecc_demo_status(void)
{
    int32_t rc;

    rc = ecc_api_init();
    if (rc != ECC_API_OK) {
        printf("[ECC][FAIL] init rc=%d\n", (int)rc);
        return;
    }

    (void)ecc_api_poll_status(NULL, NULL);

    ecc_demo_print_status();
    ecc_demo_print_counters(ECC_API_BLOCK_OCRAM);
    ecc_demo_print_counters(ECC_API_BLOCK_DDR);

    (void)ecc_api_deinit();
}

void cmd_ecc_demo(const char *args)
{
    const char *mode = ecc_demo_skip_ws(args);

    if ((*mode == '\0') || ecc_demo_streq(mode, "all")) {
        ecc_demo_run();
        return;
    }
    if (ecc_demo_streq(mode, "ocram_sbe")) {
        ecc_demo_run_single(ECC_API_BLOCK_OCRAM, ECC_API_ERR_SBE,
                            ECC_DEMO_OCRAM_PROBE_ADDR);
        return;
    }
    if (ecc_demo_streq(mode, "ocram_dbe")) {
        ecc_demo_run_single(ECC_API_BLOCK_OCRAM, ECC_API_ERR_DBE,
                            ECC_DEMO_OCRAM_PROBE_ADDR);
        return;
    }
    if (ecc_demo_streq(mode, "status")) {
        ecc_demo_status();
        return;
    }

    printf("Usage: ecc_selftest [all|ocram_sbe|ocram_dbe|status]\n");
    printf("  (default)  - OCRAM SBE/DBE demo\n");
    printf("  all        - same as default\n");
    printf("  ocram_sbe  - inject one OCRAM SBE and report\n");
    printf("  ocram_dbe  - inject one OCRAM DBE and report\n");
    printf("  status     - dump raw SERR/DERR and per-block counters\n");
    printf("\nNote: DDR injection via IO96B SiP SMC is not supported;\n");
    printf("      the MPFE firewall blocks EL3 access after DDR handoff.\n");
}

static void cmd_ecc_bist(const char *args)
{
    const char *mode = ecc_demo_skip_ws(args);

    if ((*mode == '\0') || ecc_demo_streq(mode, "all")) {
        ecc_bist_run();
        return;
    }
    if (ecc_demo_streq(mode, "ocram_sbe")) {
        (void)ecc_bist_run_case(ECC_API_ERR_SBE);
        return;
    }
    if (ecc_demo_streq(mode, "ocram_dbe")) {
        (void)ecc_bist_run_case(ECC_API_ERR_DBE);
        return;
    }

    printf("Usage: ecc_bist [all|ocram_sbe|ocram_dbe]\n");
    printf("  (default)  - run OCRAM SBE + DBE ECC BIST\n");
    printf("  all        - same as default\n");
    printf("  ocram_sbe  - run OCRAM single-bit ECC BIST only\n");
    printf("  ocram_dbe  - run OCRAM double-bit ECC BIST only\n");
}

/* CLI registration */
static void register_ecc_example(void)
{
    cli_register_command("ecc_selftest", cmd_ecc_demo);
    cli_register_command("ecc_bist", cmd_ecc_bist);
}

APP_REGISTER(register_ecc_example)

