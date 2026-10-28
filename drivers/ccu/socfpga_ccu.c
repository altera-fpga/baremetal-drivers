/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ccu.c
 *
 * CCU source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdint.h>

#include "errno.h"
#include "socfpga_ccu.h"
#include "socfpga_ccu_ll.h"
#include "socfpga_ccu_reg.h"

#define CCU_FIELD_PREP(mask, pos, value) \
    ((((uint32_t)(value)) << (pos)) & (mask))

static int32_t socfpga_ccu_wait_maintenance_done(uint32_t base_address,
                                                 uint32_t status_offset,
                                                 uint32_t timeout_polls)
{
    uint32_t status;

    while (timeout_polls > 0U) {
        status = socfpga_ccu_ll_read(base_address, status_offset);
        if ((status & CCU_DMI_CACHE_OP_DONE_MASK) == 0U) {
            return 0;
        }
        timeout_polls--;
    }

    return -ETIMEDOUT;
}

static int32_t socfpga_ccu_flush_array(uint32_t base_address,
                                       uint32_t dmi_index,
                                       uint32_t array_id,
                                       uint32_t timeout_polls)
{
    uint32_t cmd;
    uint32_t cmd_offset = CCU_DMI0_USMCMCR + (dmi_index * CCU_DMI_STRIDE);
    uint32_t status_offset = CCU_DMI0_USMCMAR + (dmi_index * CCU_DMI_STRIDE);

    cmd = CCU_FIELD_PREP(CCU_DMI_MNTOP_MASK,
                         CCU_DMI_MNTOP_POS,
                         CCU_DMI_MNTOP_FLUSH_ALL) |
          CCU_FIELD_PREP(CCU_DMI_ARRAY_ID_MASK,
                         CCU_DMI_ARRAY_ID_POS,
                         array_id);

    socfpga_ccu_ll_write(base_address, cmd_offset, cmd);
    return socfpga_ccu_wait_maintenance_done(base_address,
                                             status_offset,
                                             timeout_polls);
}

int32_t socfpga_ccu_get_id(uint32_t base_address, uint32_t *id)
{
    return socfpga_ccu_read_reg(base_address, CCU_CAIU_IDR, id);
}

int32_t socfpga_ccu_get_error_status(uint32_t base_address, uint32_t *status)
{
    return socfpga_ccu_read_reg(base_address, CCU_CAIU_UESR, status);
}

int32_t socfpga_ccu_flush_l3_cache(uint32_t base_address, uint32_t timeout_polls)
{
    uint32_t i;
    int32_t ret;

    if ((base_address == 0U) || (timeout_polls == 0U)) {
        return -EINVAL;
    }

    for (i = 0U; i < CCU_DMI_MAX_COUNT; i++) {
        uint32_t control = socfpga_ccu_ll_read(base_address,
                                               CCU_DMI0_USMCTCR +
                                               (i * CCU_DMI_STRIDE));

        /* Skip disabled distributed-memory interfaces. */
        if (control == 0U) {
            continue;
        }

        ret = socfpga_ccu_flush_array(base_address,
                                      i,
                                      CCU_DMI_ARRAY_ID_TAG,
                                      timeout_polls);
        if (ret != 0) {
            return ret;
        }

        ret = socfpga_ccu_flush_array(base_address,
                                      i,
                                      CCU_DMI_ARRAY_ID_DATA,
                                      timeout_polls);
        if (ret != 0) {
            return ret;
        }
    }

    return 0;
}

int32_t socfpga_ccu_read_reg(uint32_t base_address, uint32_t offset, uint32_t *value)
{
    if ((base_address == 0U) || (value == NULL)) {
        return -EINVAL;
    }

    *value = socfpga_ccu_ll_read(base_address, offset);
    return 0;
}

int32_t socfpga_ccu_write_reg(uint32_t base_address, uint32_t offset, uint32_t value)
{
    if (base_address == 0U) {
        return -EINVAL;
    }

    socfpga_ccu_ll_write(base_address, offset, value);
    return 0;
}

