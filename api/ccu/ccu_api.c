/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>

#include "errno.h"
#include "ccu_api.h"
#include "socfpga_peripheral_reg_plat.h"

static uint32_t ccu_api_base(void)
{
#ifdef SOCFPGA_CCU_BASE
    return SOCFPGA_CCU_BASE;
#else
    return 0U;
#endif
}

int32_t ccu_api_get_id(uint32_t *id)
{
    uint32_t base = ccu_api_base();

    if (base == 0U) {
        return -ENOSYS;
    }

    return socfpga_ccu_get_id(base, id);
}

int32_t ccu_api_get_error_status(uint32_t *status)
{
    uint32_t base = ccu_api_base();

    if (base == 0U) {
        return -ENOSYS;
    }

    return socfpga_ccu_get_error_status(base, status);
}

int32_t ccu_api_flush_l3_cache(void)
{
    uint32_t base = ccu_api_base();

    if (base == 0U) {
        return -ENOSYS;
    }

    return socfpga_ccu_flush_l3_cache(base, CCU_API_DEFAULT_TIMEOUT_POLLS);
}

int32_t ccu_api_get_id_with_base(uint32_t base_address, uint32_t *id)
{
    return socfpga_ccu_get_id(base_address, id);
}

int32_t ccu_api_flush_l3_cache_with_base(uint32_t base_address,
                                         uint32_t timeout_polls)
{
    return socfpga_ccu_flush_l3_cache(base_address, timeout_polls);
}

