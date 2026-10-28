/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "fcs_api.h"
#include "socfpga_fcs.h"
#include "socfpga_mbox_client.h"

/*
 * Number of mbox_poll_once() iterations issued by fcs_api_poll_drain().
 * The FCS HAL driver itself reads its response buffer the moment
 * sip_svc_send() returns; this drain is therefore a best-effort hook
 * for callers (and for the example) to give the ATF / SDM ring a chance
 * to deliver any payload that is queued asynchronously.
 */
#define FCS_API_POLL_ITERS    (256U)

static int g_fcs_inited;

int fcs_api_init(void)
{
    int rc;

    if (g_fcs_inited) {
        return FCS_API_OK;
    }

    rc = fcs_init();
    if (rc != 0) {
        return FCS_API_ERROR;
    }

    g_fcs_inited = 1;
    return FCS_API_OK;
}

int fcs_api_deinit(void)
{
    int rc;

    if (!g_fcs_inited) {
        return FCS_API_OK;
    }

    rc = fcs_deinit();
    g_fcs_inited = 0;

    return (rc == 0) ? FCS_API_OK : FCS_API_ERROR;
}

int fcs_api_poll_drain(void)
{
    unsigned int i;
    int processed = 0;

    for (i = 0U; i < FCS_API_POLL_ITERS; i++) {
        int n = mbox_poll_once();
        if (n <= 0) {
            break;
        }
        processed += n;
    }

    return processed;
}

int fcs_api_open_session(char *uuid_out)
{
    int rc;

    if (uuid_out == NULL) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    (void)memset(uuid_out, 0, FCS_UUID_SIZE);

    rc = run_fcs_open_service_session(uuid_out);
    (void)fcs_api_poll_drain();

    if (rc == 0) {
        return FCS_API_OK;
    }
    /* SDM 0x85: often unowned / user pubkey not provisioned — not definitive. */
    if (rc == 0x85) {
        return FCS_API_SECURITY_DENIED;
    }

    return FCS_API_ERROR;
}

int fcs_api_close_session(char *uuid)
{
    int rc;

    if (uuid == NULL) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    rc = run_fcs_close_service_session(uuid);
    (void)fcs_api_poll_drain();

    return (rc == 0) ? FCS_API_OK : FCS_API_ERROR;
}

int fcs_api_get_chip_id(uint32_t *chip_low, uint32_t *chip_high)
{
    int rc;

    if ((chip_low == NULL) || (chip_high == NULL)) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    *chip_low = 0U;
    *chip_high = 0U;

    rc = run_fcs_get_chip_id(chip_low, chip_high);
    (void)fcs_api_poll_drain();

    return (rc == 0) ? FCS_API_OK : FCS_API_ERROR;
}

int fcs_api_get_jtag_idcode(uint32_t *jtag_idcode)
{
    int rc;

    if (jtag_idcode == NULL) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    *jtag_idcode = 0U;

    rc = run_fcs_get_jtag_idcode(jtag_idcode);
    (void)fcs_api_poll_drain();

    return (rc == 0) ? FCS_API_OK : FCS_API_ERROR;
}

int fcs_api_get_random_number(char    *uuid,
                              uint32_t context_id,
                              char    *rand_buf,
                              uint32_t rand_size)
{
    int rc;

    if ((uuid == NULL) || (rand_buf == NULL)) {
        return FCS_API_INVALID_PARAM;
    }
    if ((rand_size == 0U) || (rand_size > FCS_RNG_MAX_SIZE)) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    rc = run_fcs_random_number_ext(rand_buf, uuid, context_id, rand_size);
    (void)fcs_api_poll_drain();

    return (rc == 0) ? FCS_API_OK : FCS_API_ERROR;
}

int fcs_api_get_provision_data(char     *prov_data,
                               uint32_t *prov_data_size)
{
    int rc;

    if ((prov_data == NULL) || (prov_data_size == NULL)) {
        return FCS_API_INVALID_PARAM;
    }
    if (!g_fcs_inited) {
        return FCS_API_NOT_INITED;
    }

    rc = run_fcs_service_get_provision_data(prov_data, prov_data_size);
    (void)fcs_api_poll_drain();

    if (rc == 0) {
        return FCS_API_OK;
    }
    if (rc == 0x85) {
        return FCS_API_SECURITY_DENIED;
    }

    return FCS_API_ERROR;
}
