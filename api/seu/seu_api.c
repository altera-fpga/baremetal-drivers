/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include <stdint.h>

#include "errno.h"
#include "seu_api.h"
#include "socfpga_seu.h"

int seu_api_init(void)
{
    return (int)seu_init();
}

int seu_api_deinit(void)
{
    return (int)seu_deinit();
}

int seu_api_set_callback(seu_api_callback_t cb)
{
    if (cb == NULL)
    {
        return -EINVAL;
    }
    seu_set_call_back((seu_call_back_t)cb);
    return 0;
}

int seu_api_get_first_valid_sector(uint8_t max_probe, uint8_t *out_sector)
{
    if ((out_sector == NULL) || (max_probe == 0U))
    {
        return -EINVAL;
    }
    return (int)seu_get_first_lsm_sector(max_probe, out_sector);
}

int seu_api_read_stat(uint8_t sector, seu_api_stat_t *out_stat)
{
    if (out_stat == NULL)
    {
        return -EINVAL;
    }

    seu_stat_t s = seu_read_stat(sector);
    if (s.op_state != 0)
    {
        return -EIO;
    }

    out_stat->t_seu_cycle         = s.t_seu_cycle;
    out_stat->t_seu_detect        = s.t_seu_detect;
    out_stat->t_seu_correct       = s.t_seu_correct;
    out_stat->t_seu_inject_detect = s.t_seu_inject_detect;
    out_stat->t_poll_interval     = s.t_sdm_seu_poll_interval;
    return 0;
}

int seu_api_insert_safe_err(uint8_t sector, const seu_api_inj_params_t *params)
{
    if (params == NULL)
    {
        return -EINVAL;
    }
    if ((params->count < 1U) || (params->count > 2U))
    {
        return -EINVAL;
    }

    seu_err_params_t p = {
        .sector_addr     = sector,
        .cram_sel0       = params->cram_sel0,
        .cram_sel1       = params->cram_sel1,
        .injection_cycle = params->injection_cycle,
        /* driver no_of_injection: 0 = inject 1 error, 1 = inject 2 errors */
        .no_of_injection = params->count - 1U,
    };
    return (int)seu_insert_safe_err(p);
}

int seu_api_read_err(seu_api_err_data_t *out_err)
{
    if (out_err == NULL)
    {
        return -EINVAL;
    }

    read_err_data_t d = seu_read_err();
    if (d.op_state != 0)
    {
        return -EIO;
    }

    out_err->sector_addr = d.sector_addr;
    out_err->err_type    = d.err_type;
    out_err->err_cnt     = d.err_cnt;
    out_err->corrected   = d.correction_status;
    return 0;
}

int seu_api_inject_fpga_ram_err(uint8_t sector, uint8_t err_mode, uint8_t ram_id)
{
    return (int)seu_insert_fpga_ram_err(err_mode, ram_id, sector);
}

