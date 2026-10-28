/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: bridge_selftest.c
 *
 * Bridge Loopback Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Bridge Loopback Example
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

#include "../api/console/console_api.h"
#include "../api/bridge/bridge_api.h"
#include "cache.h"
#include "example_register.h"
#include "socfpga_bridge_reg_plat.h"

/*
 * Local aliases for the platform bridge defaults in socfpga_bridge_reg_plat.h.
 * Demo window bases, F2H verify address/pattern/words, and SiP support are
 * selected per PLAT at build time.
 */
#define BRIDGE_DEMO_HPS2FPGA_BASE   SOCFPGA_BRIDGE_HPS2FPGA_BASE
#define BRIDGE_DEMO_FPGA2HPS_BASE   SOCFPGA_BRIDGE_FPGA2HPS_BASE
#define BRIDGE_DEMO_WINDOW_SIZE     SOCFPGA_BRIDGE_WINDOW_SIZE
#define BRIDGE_F2H_VERIFY_ADDR      SOCFPGA_BRIDGE_F2H_VERIFY_ADDR
#define BRIDGE_F2H_VERIFY_PATTERN   SOCFPGA_BRIDGE_F2H_VERIFY_PATTERN
#define BRIDGE_F2H_VERIFY_WORDS     SOCFPGA_BRIDGE_F2H_VERIFY_WORDS
#define BRIDGE_F2H_VERIFY_MAX_WORDS SOCFPGA_BRIDGE_F2H_VERIFY_MAX_WORDS
#define BRIDGE_DEMO_SIP_SUPPORTED   SOCFPGA_BRIDGE_SIP_SUPPORTED

/*
 * Loopback word-count bounds.
 *
 * DEFAULT: used when the caller passes "bridge_selftest loopback" with no count.
 *          1024 words = 8 KiB - large enough to stress a few AXI bursts and
 *          spot stuck-bit / address-aliasing bugs, small enough to print
 *          fast and to fit in any reasonable FPGA-side BRAM backing.
 *
 * MAX:     hard cap so the test never writes outside the routing window we
 *          declared in Step 2. Equals window_size / sizeof(uint64_t).
 *          Anything larger is rejected with a clear error.
 */
#define BRIDGE_DEMO_LOOPBACK_DEFAULT_WORDS  1024U
#define BRIDGE_DEMO_LOOPBACK_MAX_WORDS                                   \
    ((uint32_t)(BRIDGE_DEMO_WINDOW_SIZE / sizeof(uint64_t)))

/* Full-system data + instruction barrier; ensures HPS2FPGA writes are
 * globally observed before subsequent reads cross the bridge.            */
#define BRIDGE_DEMO_BARRIER()                                             \
    __asm__ volatile ("dmb sy\n" "isb\n" : : : "memory")

/*
 * FPGA2HPS handle owned by the f2h_* sub-commands. Unlike the control-plane
 * flow, this one is deliberately not released when the sub-command returns:
 * the bridge has to stay enabled while the FPGA-side master writes.
 */
static bridge_handle_t s_f2h_session;

/*
 * CLI arg helpers (file-local; mirror the perf_example pattern).
 */
static const char *demo_skip_spaces(const char *p)
{
    while ((p != NULL) && (*p == ' '))
    {
        p++;
    }
    return p;
}

static int demo_token_eq(const char *p, const char *word)
{
    p = demo_skip_spaces(p);
    while ((*word != '\0') && (p != NULL) && (*p == *word))
    {
        p++;
        word++;
    }
    return ((*word == '\0') && ((p == NULL) || (*p == '\0') || (*p == ' ')));
}

/*
 * Skip the first whitespace-delimited token in p (typically the
 * sub-command name) and return the rest of the string.  Used to find
 * an optional argument that follows "loopback".
 */
static const char *demo_after_token(const char *p)
{
    p = demo_skip_spaces(p);
    while ((p != NULL) && (*p != '\0') && (*p != ' '))
    {
        p++;
    }
    return demo_skip_spaces(p);
}

/*
 * Parse a uint32_t count expressed either as decimal (e.g. "1024") or as
 * hexadecimal with a 0x / 0X prefix (e.g. "0x10000"). Returns 0 when s
 * is empty or NULL.
 */
static uint32_t demo_parse_count(const char *s)
{
    if ((s == NULL) || (*s == '\0'))
    {
        return 0U;
    }
    if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X')))
    {
        return (uint32_t)parse_hex(s);
    }
    return parse_dec(s);
}

/*
 * Per-word test pattern. Generated on the fly so we do not pay any
 * .rodata cost. Each i produces a distinct value, which catches:
 *   - stuck bits         (the same bit always 0 or 1 across all words);
 *   - address aliasing   (word N reads back as word M);
 *   - byte-lane swaps    (low / high halves disagree).
 */
static inline uint64_t demo_pattern(uint32_t i)
{
    return 0xCAFEBABE00000000ULL ^ ((uint64_t)i * 0x0123456789ABCDEFULL);
}

static void print_result(const char *label, int rc)
{
    if (rc == 0)
    {
        printf("  [PASS] %s\n", label);
    }
    else
    {
        printf("  [FAIL] %s (rc=%d)\n", label, rc);
    }
}

/*
 * Same as print_result() but reports a failure as [WARN].
 *
 * Reserved for disabling the FPGA-facing bridges: ATF's reset manager waits
 * for RSTMGR_HDSKACK FPGAHSACK / FPGA2SOCACK and returns
 * SIP_SMC_STATUS_ERROR (4) when no FPGA design completes the handshake. That
 * is platform behaviour rather than a HAL defect, and the bridge simply stays
 * enabled in silicon, so it must not be reported as a hard failure.
 */
static void print_result_soft(const char *label, int rc)
{
    if (rc == 0)
    {
        printf("  [PASS] %s\n", label);
    }
    else
    {
        printf("  [WARN] %s (rc=%d) - FPGA handshake did not complete; "
               "bridge stays enabled\n", label, rc);
    }
}

static void print_usage(void)
{
    printf("\n  Usage: bridge_selftest [loopback [count] | f2h_enable |\n"
           "                          f2h_verify [addr [pattern [words]]] |\n"
           "                          f2h_disable | help]\n"
           "  (no arg)         Control-plane flow: open / route / flow-ctrl /\n"
           "                   enable / pause / resume / disable / close.\n"
           "  loopback         Same plus a write/read through the HPS2FPGA\n"
           "                   window to verify real data movement. Requires\n"
           "                   an FPGA design that provides addressable\n"
           "                   storage at 0x%016llx.\n"
           "                   Default count = %u 64-bit words (%u KiB).\n"
           "  loopback <n>     Override the word count. <n> may be decimal\n"
           "                   or 0x-prefixed hex. Range: 1 .. %u words\n"
           "                   (= window size %u MiB / 8B).\n"
           "  f2h_enable       Enable FPGA2HPS and leave it enabled so an\n"
           "                   external FPGA master can write to HPS memory.\n"
           "  f2h_verify       Re-read what the FPGA wrote. Defaults to %u\n"
           "                   32-bit words of 0x%08x at 0x%016llx.\n"
           "                   Optional args override addr / pattern / words\n"
           "                   (addr and pattern are hex, words 1 .. %u).\n"
           "  f2h_disable      Disable and release the FPGA2HPS session.\n"
           "  help             Show this help.\n\n",
           (unsigned long long)BRIDGE_DEMO_HPS2FPGA_BASE,
           BRIDGE_DEMO_LOOPBACK_DEFAULT_WORDS,
           (unsigned)((BRIDGE_DEMO_LOOPBACK_DEFAULT_WORDS * sizeof(uint64_t)) / 1024U),
           BRIDGE_DEMO_LOOPBACK_MAX_WORDS,
           (unsigned)(BRIDGE_DEMO_WINDOW_SIZE / (1024U * 1024U)),
           BRIDGE_F2H_VERIFY_WORDS,
           BRIDGE_F2H_VERIFY_PATTERN,
           (unsigned long long)BRIDGE_F2H_VERIFY_ADDR,
           BRIDGE_F2H_VERIFY_MAX_WORDS);
#if !BRIDGE_DEMO_SIP_SUPPORTED
    printf("This platform does not support SiP bridge control.\n"
           "  Steps 4/4.5/5 and the Step 7 disable are SKIPPED automatically.\n\n");
#endif
}

static int demo_configure_route(bridge_handle_t handle,
                                bridge_api_dir_t direction,
                                uint64_t base,
                                uint64_t size)
{
    bridge_api_route_t route;

    route.direction   = direction;
    route.base_addr   = base;
    route.window_size = size;

    return bridge_api_set_route(handle, &route);
}

static void demo_dump_route(bridge_handle_t handle, const char *label)
{
    bridge_api_route_t route;
    int32_t rc = bridge_api_get_route(handle, &route);

    if (rc != 0)
    {
        printf("  [FAIL] get_route(%s) rc=%d\n", label, rc);
        return;
    }
    printf("  %s route: dir=%d base=0x%016llx window=0x%016llx\n",
           label,
           (int)route.direction,
           (unsigned long long)route.base_addr,
           (unsigned long long)route.window_size);
}

/*
 * Optional Step 4.5 - drive a write/read pattern through the HPS2FPGA
 * window. The FPGA design must back the address with real storage (RAM,
 * register file, or loopback fabric) for this to pass.
 *
 * words - Number of 64-bit words to exercise. Must be in
 *               [1, BRIDGE_DEMO_LOOPBACK_MAX_WORDS]; a value outside
 *               that range is rejected with -EINVAL.
 *
 * Returns: 0 on success, -EINVAL for a bad count, -1 on data mismatch.
 *
 * Per-word mismatches print a [MISMATCH] line and the first 8 are shown
 * in detail; subsequent mismatches are counted but not printed to keep
 * the log readable for very large transfers.
 */
static int demo_data_loopback(uint32_t words)
{
    volatile uint64_t *win = (volatile uint64_t *)(uintptr_t)BRIDGE_DEMO_HPS2FPGA_BASE;
    uint32_t mismatches = 0U;
    uint32_t printed    = 0U;

    if ((words == 0U) || (words > BRIDGE_DEMO_LOOPBACK_MAX_WORDS))
    {
        printf("  [FAIL] word count %u outside [1, %u]\n",
               words, BRIDGE_DEMO_LOOPBACK_MAX_WORDS);
        return -EINVAL;
    }

    printf("  Writing %u 64-bit words (%u KiB) to 0x%016llx via HPS2FPGA ...\n",
           words,
           (unsigned)(((uint64_t)words * sizeof(uint64_t)) / 1024U),
           (unsigned long long)BRIDGE_DEMO_HPS2FPGA_BASE);

    for (uint32_t i = 0U; i < words; i++)
    {
        win[i] = demo_pattern(i);
    }

    BRIDGE_DEMO_BARRIER();

    printf("  Reading back and verifying ...\n");

    for (uint32_t i = 0U; i < words; i++)
    {
        uint64_t expected = demo_pattern(i);
        uint64_t got      = win[i];
        if (got != expected)
        {
            mismatches++;
            if (printed < 8U)
            {
                printf("    [MISMATCH] word %u: expected 0x%016llx got 0x%016llx\n",
                       i,
                       (unsigned long long)expected,
                       (unsigned long long)got);
                printed++;
            }
        }
    }

    if (mismatches == 0U)
    {
        printf("  All %u words verified.\n", words);
        return 0;
    }
    if (mismatches > printed)
    {
        printf("    ... %u additional mismatches not printed\n",
               mismatches - printed);
    }
    printf("  %u of %u words mismatched.\n", mismatches, words);
    return -EIO;
}

/*
 * Obtain the FPGA2HPS handle for the f2h_* sub-commands.
 *
 * bridge_mw_open() refuses a second open on a bridge whose context is still
 * live, so the handle is cached in s_f2h_session for the following
 * sub-command. A context left behind by an earlier, interrupted run is
 * reclaimed once: close is a software-state release and never touches the
 * silicon, so the enable bit of an already-enabled bridge is preserved.
 *
 * Returns: handle on success, NULL when the bridge cannot be opened.
 */
static bridge_handle_t f2h_acquire(void)
{
    if (s_f2h_session != NULL)
    {
        return s_f2h_session;
    }

    s_f2h_session = bridge_api_open(BRIDGE_API_FPGA2HPS);
    if (s_f2h_session == NULL)
    {
        printf("  Reclaiming FPGA2HPS context left open by an earlier run\n");
        (void)bridge_api_close(BRIDGE_API_FPGA2HPS);
        s_f2h_session = bridge_api_open(BRIDGE_API_FPGA2HPS);
    }

    return s_f2h_session;
}

/*
 * f2h_enable - open and enable FPGA2HPS, then return with it still enabled.
 *
 * The route and flow-control settings are applied for parity with the
 * control-plane flow; both are middleware state today and neither is required
 * for the data-plane check.
 */
static void demo_f2h_enable(void)
{
    bridge_handle_t handle;
    int32_t         rc;

    printf("\n=== FPGA2HPS Enable ===\n\n");

    if (!BRIDGE_DEMO_SIP_SUPPORTED)
    {
        printf("  [FAIL] SiP enable path is not supported on this platform,\n"
               "         so FPGA2HPS cannot be enabled here.\n");
        printf("\n=== F2H enable complete ===\n\n");
        return;
    }

    handle = f2h_acquire();
    if (handle == NULL)
    {
        printf("  [FAIL] open FPGA2HPS returned NULL\n");
        printf("\n=== F2H enable complete ===\n\n");
        return;
    }
    printf("  [PASS] FPGA2HPS opened\n");

    rc = demo_configure_route(handle,
                              BRIDGE_API_DIR_FPGA_TO_HPS,
                              BRIDGE_DEMO_FPGA2HPS_BASE,
                              BRIDGE_DEMO_WINDOW_SIZE);
    print_result("FPGA2HPS route", rc);

    rc = bridge_api_set_flow_ctrl(handle, BRIDGE_API_FLOW_BACKPRESSURE);
    print_result("FPGA2HPS flow ctrl", rc);

    rc = bridge_api_enable(handle);
    print_result("F2H enable", rc);
    if (rc != 0)
    {
        printf("\n=== F2H enable complete ===\n\n");
        return;
    }

    printf("  FPGA2HPS status = %d\n", bridge_api_get_status(handle));
    printf("  Bridge stays enabled; drive the FPGA-side write now, then run\n"
           "  `bridge_selftest f2h_verify`.\n");

    printf("\n=== F2H enable complete ===\n\n");
}

/*
 * f2h_verify - re-read the words an FPGA master pushed across FPGA2HPS.
 *
 * args - Optional "addr [pattern [words]]"; addr and pattern are hex, words
 *        is decimal or 0x-prefixed hex. Omitted fields keep their defaults.
 *
 * The region is invalidated before the loads because an FPGA master writing
 * into HPS memory does not snoop the CPU caches, so a cached copy of the same
 * lines would otherwise satisfy the reads. This is the bare-metal counterpart
 * of the `dcache flush` the U-Boot version issues before `md`.
 */
static void demo_f2h_verify(const char *args)
{
    uint64_t addr        = BRIDGE_F2H_VERIFY_ADDR;
    uint32_t pattern     = BRIDGE_F2H_VERIFY_PATTERN;
    uint32_t words       = BRIDGE_F2H_VERIFY_WORDS;
    uint32_t mismatches  = 0U;
    uint32_t printed     = 0U;
    volatile const uint32_t *win;

    printf("\n=== FPGA2HPS Verify ===\n\n");

    args = demo_skip_spaces(args);
    if ((args != NULL) && (*args != '\0'))
    {
        addr = parse_hex(args);

        args = demo_after_token(args);
        if ((args != NULL) && (*args != '\0'))
        {
            pattern = (uint32_t)parse_hex(args);

            args = demo_after_token(args);
            if ((args != NULL) && (*args != '\0'))
            {
                words = demo_parse_count(args);
            }
        }
    }

    if ((words == 0U) || (words > BRIDGE_F2H_VERIFY_MAX_WORDS))
    {
        printf("  [FAIL] word count %u outside [1, %u]\n",
               words, BRIDGE_F2H_VERIFY_MAX_WORDS);
        printf("\n=== F2H verify complete ===\n\n");
        return;
    }

    if (s_f2h_session == NULL)
    {
        printf("  Note: no FPGA2HPS session from this command; assuming the\n"
               "        bridge was enabled elsewhere (U-Boot, ATF or a prior\n"
               "        `bridge_selftest f2h_enable`).\n");
    }

    printf("  Reading %u 32-bit word(s) at 0x%016llx, expecting 0x%08x\n",
           words, (unsigned long long)addr, pattern);

    win = (volatile const uint32_t *)(uintptr_t)addr;

    cache_force_invalidate((void *)(uintptr_t)addr,
                           (size_t)words * sizeof(uint32_t));
    BRIDGE_DEMO_BARRIER();

    for (uint32_t i = 0U; i < words; i++)
    {
        uint32_t got = win[i];

        if (got != pattern)
        {
            mismatches++;
            if (printed < 8U)
            {
                printf("    [MISMATCH] word %u at 0x%016llx: expected 0x%08x "
                       "got 0x%08x\n",
                       i,
                       (unsigned long long)(addr + ((uint64_t)i * sizeof(uint32_t))),
                       pattern,
                       got);
                printed++;
            }
        }
    }

    if (mismatches > printed)
    {
        printf("    ... %u additional mismatches not printed\n",
               mismatches - printed);
    }

    if (mismatches == 0U)
    {
        printf("  All %u word(s) verified.\n", words);
        print_result("F2H verify", 0);
    }
    else
    {
        printf("  %u of %u word(s) mismatched.\n", mismatches, words);
        print_result("F2H verify", -EIO);
    }

    printf("\n=== F2H verify complete ===\n\n");
}

/*
 * f2h_disable - tear down the session started by f2h_enable.
 *
 * Disable failures are reported through print_result_soft() because ATF can
 * legitimately refuse to disable an FPGA-facing bridge; the context is
 * released either way so a later f2h_enable starts from a known state.
 */
static void demo_f2h_disable(void)
{
    int32_t rc;

    printf("\n=== FPGA2HPS Disable ===\n\n");

    if (s_f2h_session == NULL)
    {
        printf("  No FPGA2HPS session to release.\n");
        printf("\n=== F2H disable complete ===\n\n");
        return;
    }

    if (BRIDGE_DEMO_SIP_SUPPORTED)
    {
        rc = bridge_api_disable(s_f2h_session);
        print_result_soft("Disable FPGA2HPS", rc);
    }
    else
    {
        printf("  [SKIP] Disable FPGA2HPS (SiP bridge control not supported)\n");
    }

    rc = bridge_api_close_handle(s_f2h_session);
    print_result("Close FPGA2HPS", rc);
    s_f2h_session = NULL;

    printf("\n=== F2H disable complete ===\n\n");
}

void cmd_bridge_demo(const char *args)
{
    bridge_handle_t hps2fpga = NULL;
    bridge_handle_t fpga2hps = NULL;
    int32_t         rc;
    int             do_loopback     = 0;
    const int       do_enable       = BRIDGE_DEMO_SIP_SUPPORTED;
    uint32_t        loopback_words  = BRIDGE_DEMO_LOOPBACK_DEFAULT_WORDS;

    args = demo_skip_spaces(args);

    if ((args != NULL) && (*args != '\0'))
    {
        if (demo_token_eq(args, "help"))
        {
            print_usage();
            return;
        }
        if (demo_token_eq(args, "f2h_enable"))
        {
            demo_f2h_enable();
            return;
        }
        if (demo_token_eq(args, "f2h_verify"))
        {
            demo_f2h_verify(demo_after_token(args));
            return;
        }
        if (demo_token_eq(args, "f2h_disable"))
        {
            demo_f2h_disable();
            return;
        }
        if (demo_token_eq(args, "loopback") || demo_token_eq(args, "lb"))
        {
            const char  *rest  = demo_after_token(args);
            uint32_t     count = demo_parse_count(rest);

            if (!do_enable)
            {
                printf("`loopback` requires the SiP enable path, which is\n"
                       "not supported on this platform. Skipping\n"
                       "the data-plane test; the rest of the demo will run.\n");
            }
            else
            {
                do_loopback = 1;
                if (count != 0U)
                {
                    if (count > BRIDGE_DEMO_LOOPBACK_MAX_WORDS)
                    {
                        printf("Requested count %u exceeds max %u, clamping.\n",
                               count, BRIDGE_DEMO_LOOPBACK_MAX_WORDS);
                        count = BRIDGE_DEMO_LOOPBACK_MAX_WORDS;
                    }
                    loopback_words = count;
                }
            }
        }
        else
        {
            printf("Unknown sub-command. Try `bridge_selftest help`.\n");
            return;
        }
    }

    printf("\n=== Bridge Loopback Transfer Demo ===\n");
    if (do_loopback)
    {
        printf("Mode: control-plane + data-plane\n");
    }
    else
    {
        printf("Mode: control-plane only\n");
    }
    if (!do_enable)
    {
        printf("Platform: SiP bridge control not supported -- enable/disable steps are omitted\n");
    }
    printf("\n");

    printf("[Step 1] Open HPS2FPGA and FPGA2HPS bridges\n");

    hps2fpga = bridge_api_open(BRIDGE_API_HPS2FPGA);
    if (hps2fpga == NULL)
    {
        printf("  [FAIL] open HPS2FPGA returned NULL\n");
        return;
    }
    printf("  [PASS] HPS2FPGA opened\n");

    /* Shared with the f2h_* sub-commands so the two entry points cannot fight
     * over the single FPGA2HPS context, whichever ran first. */
    fpga2hps = f2h_acquire();
    if (fpga2hps == NULL)
    {
        printf("  [FAIL] open FPGA2HPS returned NULL\n");
        goto demo_cleanup;
    }
    printf("  [PASS] FPGA2HPS opened\n");

    printf("\n[Step 2] Configure routes\n");
    rc = demo_configure_route(hps2fpga,
                              BRIDGE_API_DIR_HPS_TO_FPGA,
                              BRIDGE_DEMO_HPS2FPGA_BASE,
                              BRIDGE_DEMO_WINDOW_SIZE);
    print_result("HPS2FPGA route", rc);
    if (rc != 0) goto demo_cleanup;

    rc = demo_configure_route(fpga2hps,
                              BRIDGE_API_DIR_FPGA_TO_HPS,
                              BRIDGE_DEMO_FPGA2HPS_BASE,
                              BRIDGE_DEMO_WINDOW_SIZE);
    print_result("FPGA2HPS route", rc);
    if (rc != 0) goto demo_cleanup;

    printf("\n[Step 3] Set flow control = BACKPRESSURE\n");
    rc = bridge_api_set_flow_ctrl(hps2fpga, BRIDGE_API_FLOW_BACKPRESSURE);
    print_result("HPS2FPGA flow ctrl", rc);
    rc = bridge_api_set_flow_ctrl(fpga2hps, BRIDGE_API_FLOW_BACKPRESSURE);
    print_result("FPGA2HPS flow ctrl", rc);

    if (do_enable)
    {
        printf("\n[Step 4] Enable bridges\n");
        rc = bridge_api_enable(hps2fpga);
        print_result("Enable HPS2FPGA", rc);
        rc = bridge_api_enable(fpga2hps);
        print_result("Enable FPGA2HPS", rc);

        printf("  HPS2FPGA status = %d, FPGA2HPS status = %d\n",
               bridge_api_get_status(hps2fpga),
               bridge_api_get_status(fpga2hps));
    }
    else
    {
        printf("\n[Step 4] Enable bridges -- SKIPPED (SiP bridge control not supported)\n");
    }

    if (do_loopback)
    {
        printf("\n[Step 4.5] Data-plane write/read via HPS2FPGA window (%u words)\n",
               loopback_words);
        rc = demo_data_loopback(loopback_words);
        print_result("Data loopback", rc);
    }
    else if (!do_enable)
    {
        printf("\n[Step 4.5] SKIPPED (bridges not enabled)\n");
    }
    else
    {
        printf("\n[Step 4.5] Skipped (re-run with `bridge_selftest loopback` to enable)\n");
    }

    if (do_enable)
    {
        printf("\n[Step 5] Pause / resume cycle\n");
        rc = bridge_api_pause(hps2fpga);
        print_result("Pause HPS2FPGA", rc);
        printf("  Backpressure after pause: %d\n",
               bridge_api_get_backpressure(hps2fpga));

        rc = bridge_api_resume(hps2fpga);
        print_result("Resume HPS2FPGA", rc);
        printf("  Backpressure after resume: %d\n",
               bridge_api_get_backpressure(hps2fpga));
    }
    else
    {
        printf("\n[Step 5] Pause / resume -- SKIPPED (SiP bridge control not supported)\n");
    }

    printf("\n[Step 6] Read back routes\n");
    demo_dump_route(hps2fpga, "HPS2FPGA");
    demo_dump_route(fpga2hps, "FPGA2HPS");

demo_cleanup:
    printf("\n[Step 7] Disable + close bridges\n");
    /*
     * Disable and close are reported separately so failures are honest.
     * Note: the ATF SiP service can reject disabling FPGA-facing bridges
     * (FPGA2HPS / FPGA2SDRAM) when no FPGA design is loaded. The reset
     * manager waits for an FPGA-side handshake ack (RSTMGR_HDSKACK
     * FPGAHSACK / FPGA2SOCACK) and times out, returning
     * SIP_SMC_STATUS_ERROR (4). For the FPGA-facing bridge that outcome is
     * reported as [WARN] rather than [FAIL]: it is expected platform
     * behaviour, and close() is a software-state release that does not retry
     * the SiP call, so the bridge simply remains enabled in silicon.
     *
     * On platforms without SiP bridge control we never enabled the bridges,
     * so we skip the disable SiP calls. close() is still safe; it only
     * releases the middleware context.
     */
    if (hps2fpga != NULL)
    {
        if (do_enable)
        {
            rc = bridge_api_disable(hps2fpga);
            print_result("Disable HPS2FPGA", rc);
        }
        else
        {
            printf("  [SKIP] Disable HPS2FPGA (SiP bridge control not supported)\n");
        }
        rc = bridge_api_close(BRIDGE_API_HPS2FPGA);
        print_result("Close HPS2FPGA", rc);
    }
    if (fpga2hps != NULL)
    {
        if (do_enable)
        {
            rc = bridge_api_disable(fpga2hps);
            print_result_soft("Disable FPGA2HPS", rc);
        }
        else
        {
            printf("  [SKIP] Disable FPGA2HPS (SiP bridge control not supported)\n");
        }
        rc = bridge_api_close(BRIDGE_API_FPGA2HPS);
        print_result("Close FPGA2HPS", rc);
        s_f2h_session = NULL;
    }

    printf("\n=== Bridge demo complete ===\n\n");
}

void register_bridge_example(void)
{
    cli_register_command("bridge_selftest", cmd_bridge_demo);
}

APP_REGISTER(register_bridge_example)

