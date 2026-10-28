/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include "errno.h"
#include "noc_probe_api.h"
#include "socfpga_peripheral_reg_plat.h"

static uint32_t noc_probe_api_base(void)
{
#ifdef SOCFPGA_NOC_PROBE_BASE
    return SOCFPGA_NOC_PROBE_BASE;
#else
    return 0U;
#endif
}

int32_t noc_probe_api_error_is_valid(bool *valid)
{
    uint32_t base = noc_probe_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_probe_error_is_valid(base, valid);
}

int32_t noc_probe_api_error_read(socfpga_noc_probe_error_log_t *log)
{
    uint32_t base = noc_probe_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_probe_error_read(base, log);
}

int32_t noc_probe_api_error_is_valid_with_base(uint32_t base_address,
                                               bool *valid)
{
    return socfpga_noc_probe_error_is_valid(base_address, valid);
}

int32_t noc_probe_api_error_read_with_base(uint32_t base_address,
                                           socfpga_noc_probe_error_log_t *log)
{
    return socfpga_noc_probe_error_read(base_address, log);
}

int32_t noc_probe_api_read_id(uint32_t *core_id)
{
    uint32_t base = noc_probe_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_probe_read_id(base, core_id);
}

int32_t noc_probe_api_error_logger_enable(bool enable)
{
    uint32_t base = noc_probe_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_probe_error_logger_enable(base, enable);
}

int32_t noc_probe_api_error_clear(void)
{
    uint32_t base = noc_probe_api_base();
    if (base == 0U) {
        return -ENOSYS;
    }
    return socfpga_noc_probe_error_clear(base);
}

int32_t noc_probe_api_read_id_with_base(uint32_t base_address,
                                        uint32_t *core_id)
{
    return socfpga_noc_probe_read_id(base_address, core_id);
}

int32_t noc_probe_api_error_logger_enable_with_base(uint32_t base_address,
                                                    bool enable)
{
    return socfpga_noc_probe_error_logger_enable(base_address, enable);
}

int32_t noc_probe_api_error_clear_with_base(uint32_t base_address)
{
    return socfpga_noc_probe_error_clear(base_address);
}

