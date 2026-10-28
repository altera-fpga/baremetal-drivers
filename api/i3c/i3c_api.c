/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include <stdbool.h>
#include <stdint.h>

#include "i3c_api.h"
#include "socfpga_peripheral_reg_plat.h"

static socfpga_i3c_handle_t i3c_api_handle;


static uint32_t i3c_api_instance_to_reset(uint32_t instance)
{
    switch (instance) {
#ifdef RST_I3C0
    case 0U: return (uint32_t)RST_I3C0;
#endif
#ifdef RST_I3C1
    case 1U: return (uint32_t)RST_I3C1;
#endif
    default: return SOCFPGA_I3C_RESET_NONE;
    }
}


static uint32_t i3c_api_instance_to_base(uint32_t instance)
{
    uint32_t base = 0U;

    switch (instance) {
#ifdef SOCFPGA_I3C0_BASE
    case 0U:
        base = SOCFPGA_I3C0_BASE;
        break;
#endif
#ifdef SOCFPGA_I3C1_BASE
    case 1U:
        base = SOCFPGA_I3C1_BASE;
        break;
#endif
    default:
        base = 0U;
        break;
    }
    return base;
}

int32_t i3c_api_init(uint32_t instance)
{
    uint32_t base = i3c_api_instance_to_base(instance);

    if (base == 0U) {
        return -ENOSYS;
    }
    {
        socfpga_i3c_config_t config;

        if (i3c_api_handle != NULL) {
            return -EBUSY;
        }

        config.base_address = base;
        config.reset_id = i3c_api_instance_to_reset(instance);
        config.timeout = SOCFPGA_I3C_DEFAULT_TIMEOUT;
        config.enable_i2c_compatibility = true;
        config.enable_hot_join = false;

        return socfpga_i3c_init(&config, &i3c_api_handle);
    }
}

int32_t i3c_api_init_with_base(uint32_t base_address)
{
    socfpga_i3c_config_t config;

    if (i3c_api_handle != NULL) {
        return -EBUSY;
    }

    config.base_address = base_address;
    config.reset_id = SOCFPGA_I3C_RESET_NONE;
    config.timeout = SOCFPGA_I3C_DEFAULT_TIMEOUT;
    config.enable_i2c_compatibility = true;
    config.enable_hot_join = false;

    return socfpga_i3c_init(&config, &i3c_api_handle);
}

int32_t i3c_api_close(void)
{
    int32_t ret;

    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    ret = socfpga_i3c_deinit(i3c_api_handle);
    if (ret == 0) {
        i3c_api_handle = NULL;
    }
    return ret;
}

int32_t i3c_api_deinit(void)
{
    return i3c_api_close();
}

int32_t i3c_api_get_status(uint32_t *status)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_get_status(i3c_api_handle, status);
}

int32_t i3c_api_get_hw_capability(uint32_t *capability)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_get_hw_capability(i3c_api_handle, capability);
}


int32_t i3c_api_i2c_legacy_read(uint8_t i2c_address,
                                uint8_t *buffer,
                                uint32_t length,
                                uint32_t *response)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_i2c_legacy_read(i3c_api_handle,
                                       i2c_address,
                                       buffer,
                                       length,
                                       response);
}

int32_t i3c_api_i2c_legacy_write(uint8_t i2c_address,
                                 const uint8_t *buffer,
                                 uint32_t length,
                                 uint32_t *response)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_i2c_legacy_write(i3c_api_handle,
                                        i2c_address,
                                        buffer,
                                        length,
                                        response);
}

int32_t i3c_api_private_read(uint8_t dynamic_address,
                             uint8_t *buffer,
                             uint32_t length,
                             uint32_t *response)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_private_read(i3c_api_handle,
                                    dynamic_address,
                                    buffer,
                                    length,
                                    response);
}

int32_t i3c_api_private_write(uint8_t dynamic_address,
                              const uint8_t *buffer,
                              uint32_t length,
                              uint32_t *response)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_private_write(i3c_api_handle,
                                     dynamic_address,
                                     buffer,
                                     length,
                                     response);
}

int32_t i3c_api_raw_transfer(socfpga_i3c_transfer_t *transfer)
{
    if (i3c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i3c_transfer_sync(i3c_api_handle, transfer);
}
