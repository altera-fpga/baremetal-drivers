/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/*
 * FCS sample application.
 *
 * Registers a single CLI command, "fcs_demo", that exercises every
 * fcs_api_* wrapper end-to-end. The SDM responds normally, so the
 * printed values reflect the actual silicon (chip ID, JTAG IDCODE,
 * RNG bytes ...). The demo surfaces every result and reports a
 * PASS/FAIL count at the end.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../api/console/console_api.h"
#include "example_register.h"

#include "fcs_api.h"
#include "socfpga_fcs.h"

#define FCS_DEMO_RNG_BYTES        16U
#define FCS_DEMO_CONTEXT_ID       0xC0FFEE01U

/*
 * GET_PROVISION payload must sit above BL31_LIMIT so ATF's
 * is_address_in_ddr_range() accepts it (same constraint as FCS ops buffers).
 */
#define FCS_DEMO_PROV_DDR         0x83800000UL
#define FCS_DEMO_PROV_MIN_WORDS   3U

#define PF(rc)  (((rc) == FCS_API_OK) ? "PASS" : "FAIL")

typedef struct {
    unsigned int total;
    unsigned int passed;
    unsigned int expected_skips;
} fcs_demo_stats_t;

static void stat_record(fcs_demo_stats_t *s, const char *step, int rc)
{
    s->total++;
    if (rc == FCS_API_OK) {
        s->passed++;
    }
    printf("[FCS][%s] %s: rc=%d\n", PF(rc), step, rc);
}

/* Expected platform/security outcome — not counted against PASS rate. */
static void stat_record_expected(fcs_demo_stats_t *s, const char *step,
                                 const char *detail)
{
    s->expected_skips++;
    printf("[FCS][INFO] %s: %s\n", step, detail);
}

static void print_hex(const char *label, const void *data, size_t n)
{
    const uint8_t *p = (const uint8_t *)data;
    size_t i;

    printf("%s [%u bytes]:", label, (unsigned int)n);
    for (i = 0U; i < n; i++) {
        if ((i % 16U) == 0U) {
            printf("\n  ");
        }
        printf("%02x ", p[i]);
    }
    printf("\n");
}

/*
 * Query MBOX_FCS_GET_PROVISION (0x7B) and summarise ownership / secure state.
 * Do not treat open_session 0x85 alone as proof of device state.
 */
static void fcs_demo_query_provision_status(void)
{
    char *prov = (char *)(uintptr_t)FCS_DEMO_PROV_DDR;
    uint32_t prov_size = FCS_PROV_DATA_MAX_SIZE;
    const uint32_t *words;
    uint32_t field;
    uint8_t secure_state;
    uint8_t hash_count;
    int rc;

    (void)memset(prov, 0, FCS_PROV_DATA_MAX_SIZE);

    printf("[FCS] Querying provisioning via MBOX_FCS_GET_PROVISION (0x7B)...\n");

    rc = fcs_api_get_provision_data(prov, &prov_size);
    if (rc == FCS_API_SECURITY_DENIED) {
        printf("[FCS][INFO] GET_PROVISION also returned SDM 0x85 "
               "(commonly seen when unowned).\n");
        return;
    }
    if (rc != FCS_API_OK) {
        printf("[FCS][INFO] GET_PROVISION failed (rc=%d). "
               "Cannot confirm OWNED/secure state from 0x85 alone.\n", rc);
        return;
    }

    if (prov_size < (FCS_DEMO_PROV_MIN_WORDS * sizeof(uint32_t))) {
        printf("[FCS][INFO] GET_PROVISION returned %u bytes "
               "(need >= 12); payload too short to interpret.\n",
               (unsigned int)prov_size);
        return;
    }

    words = (const uint32_t *)(const void *)prov;
    field = words[2];
    secure_state = (uint8_t)(field & 0xFFU);
    hash_count = (uint8_t)((field >> 8) & 0xFFU);

    printf("[FCS][INFO] provision dword[2]=0x%08x "
           "(secure_state=%u hash_count=%u)\n",
           (unsigned int)field,
           (unsigned int)secure_state,
           (unsigned int)hash_count);

    if ((secure_state == 0U) || (hash_count == 0xFFU)) {
        printf("[FCS][INFO] Device appears UNOWNED / not provisioned "
               "(user public key not present).\n"
               "             Provision the owner key before open_session "
               "can succeed.\n");
    } else if ((secure_state == 1U) || (secure_state == 2U)) {
        printf("[FCS][INFO] Device reports provisioned secure_state=%u "
               "(OWNED-like). Investigate other security settings if\n"
               "             open_session still returns 0x85.\n",
               (unsigned int)secure_state);
    } else {
        printf("[FCS][INFO] Unrecognised secure_state=%u; treat 0x85 as "
               "security denial and check provisioning docs.\n",
               (unsigned int)secure_state);
    }
}

static void cmd_fcs_demo(const char *args)
{
    fcs_demo_stats_t stats = { 0U, 0U, 0U };
    char     uuid[FCS_UUID_SIZE];
    uint8_t  rng[FCS_DEMO_RNG_BYTES];
    uint32_t chip_low  = 0U;
    uint32_t chip_high = 0U;
    uint32_t idcode    = 0U;
    int rc;
    int open_rc;

    (void)args;
    (void)memset(uuid, 0, sizeof(uuid));
    (void)memset(rng,  0, sizeof(rng));

    printf("\n=== FCS demo: end-to-end ===\n");

    /* 1. init */
    rc = fcs_api_init();
    stat_record(&stats, "fcs_api_init", rc);
    if (rc != FCS_API_OK) {
        printf("=== FCS demo: aborted (init failed) ===\n\n");
        return;
    }

    /* 2. chip id (no session required) */
    rc = fcs_api_get_chip_id(&chip_low, &chip_high);
    stat_record(&stats, "fcs_api_get_chip_id", rc);
    printf("       chip_id: hi=0x%08x lo=0x%08x\n",
           (unsigned int)chip_high, (unsigned int)chip_low);

    /* 3. jtag idcode (no session required) */
    rc = fcs_api_get_jtag_idcode(&idcode);
    stat_record(&stats, "fcs_api_get_jtag_idcode", rc);
    printf("       jtag_idcode: 0x%08x\n", (unsigned int)idcode);

    /* 4. open session (UUID round-trip) */
    open_rc = fcs_api_open_session(uuid);
    if (open_rc == FCS_API_OK) {
        stat_record(&stats, "fcs_api_open_session", FCS_API_OK);
        print_hex("       uuid", uuid, FCS_UUID_SIZE);
    } else if (open_rc == FCS_API_SECURITY_DENIED) {
        /*
         * SDM 0x85 is expected on unprovisioned / non-OWNED devices and on
         * Simics without owner-key setup. Do not mark the selftest FAIL.
         */
        stat_record_expected(&stats, "fcs_api_open_session",
                             "SDM 0x85 security denial (expected when device "
                             "is not OWNED / user pubkey not provisioned)");
        printf("[FCS][INFO] Crypto session steps will be skipped; "
               "chip-id / idcode checks above remain valid.\n");
        fcs_demo_query_provision_status();
    } else {
        stat_record(&stats, "fcs_api_open_session", FCS_API_ERROR);
        printf("[FCS][INFO] Unexpected open_session rc=%d "
               "(not the common 0x85 security denial).\n", open_rc);
    }

    /* 5. random number generator */
    if (open_rc == FCS_API_OK) {
        int rng_rc = fcs_api_get_random_number(uuid,
                                               FCS_DEMO_CONTEXT_ID,
                                               (char *)rng,
                                               FCS_DEMO_RNG_BYTES);
        stat_record(&stats, "fcs_api_get_random_number", rng_rc);
        if (rng_rc == FCS_API_OK) {
            print_hex("       rng", rng, FCS_DEMO_RNG_BYTES);
        }
    } else {
        printf("[FCS][INFO] fcs_api_get_random_number skipped "
               "(no crypto session).\n");
    }

    /* 6. close session */
    if (open_rc == FCS_API_OK) {
        int close_rc = fcs_api_close_session(uuid);
        stat_record(&stats, "fcs_api_close_session", close_rc);
    } else {
        printf("[FCS][INFO] fcs_api_close_session skipped "
               "(no crypto session).\n");
    }

    /* 7. deinit */
    rc = fcs_api_deinit();
    stat_record(&stats, "fcs_api_deinit", rc);

    if (stats.expected_skips != 0U) {
        printf("=== FCS demo: %u/%u step(s) PASS "
               "(%u expected security skip(s)) ===\n\n",
               stats.passed, stats.total, stats.expected_skips);
    } else {
        printf("=== FCS demo: %u/%u step(s) PASS ===\n\n",
               stats.passed, stats.total);
    }
}

static void register_fcs_example(void)
{
    cli_register_command("fcs_selftest", cmd_fcs_demo);
}

APP_REGISTER(register_fcs_example)
