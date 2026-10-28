/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "i2c_api.h"
#include "socfpga_peripheral_reg_plat.h"

static socfpga_i2c_handle_t i2c_api_handle;

static uint32_t i2c_api_instance_to_base(uint32_t instance)
{
    uint32_t base = 0U;

    switch (instance) {
#ifdef SOCFPGA_I2C0_BASE
    case 0U:
        base = SOCFPGA_I2C0_BASE;
        break;
#endif
#ifdef SOCFPGA_I2C1_BASE
    case 1U:
        base = SOCFPGA_I2C1_BASE;
        break;
#endif
#ifdef SOCFPGA_I2C2_BASE
    case 2U:
        base = SOCFPGA_I2C2_BASE;
        break;
#endif
#ifdef SOCFPGA_I2C3_BASE
    case 3U:
        base = SOCFPGA_I2C3_BASE;
        break;
#endif
#ifdef SOCFPGA_I2C4_BASE
    case 4U:
        base = SOCFPGA_I2C4_BASE;
        break;
#endif
    default:
        base = 0U;
        break;
    }

    return base;
}


static uint32_t i2c_api_instance_to_reset(uint32_t instance)
{
    uint32_t reset_id = SOCFPGA_I2C_RESET_NONE;

    switch (instance) {
    case 0U:
        reset_id = (uint32_t)RST_I2C0;
        break;
    case 1U:
        reset_id = (uint32_t)RST_I2C1;
        break;
    case 2U:
        reset_id = (uint32_t)RST_I2C2;
        break;
    case 3U:
        reset_id = (uint32_t)RST_I2C3;
        break;
    case 4U:
        reset_id = (uint32_t)RST_I2C4;
        break;
    default:
        break;
    }

    return reset_id;
}

static uint32_t i2c_api_bus_to_speed_mode(uint32_t bus_hz)
{
    if (bus_hz <= 100000U) {
        return SOCFPGA_I2C_SPEED_STANDARD;
    }
    if (bus_hz <= 400000U) {
        return SOCFPGA_I2C_SPEED_FAST;
    }
    return SOCFPGA_I2C_SPEED_FASTPLUS;
}

/* bus_hz is passed through so the driver derives the SCL counts from the live
 * input clock rather than leaving the reset values in place.
 */
static void i2c_api_fill_config(socfpga_i2c_config_t *config,
                                uint32_t base_address, uint32_t reset_id,
                                uint16_t target_address, uint32_t bus_hz)
{
    config->base_address = base_address;
    config->target_address = target_address;
    config->speed_mode = i2c_api_bus_to_speed_mode(bus_hz);
    config->bus_hz = bus_hz;
    config->input_clock_hz = 0U;
    config->timeout = SOCFPGA_I2C_DEFAULT_TIMEOUT;
    config->reset_id = reset_id;
    config->scl_high_count = 0U;
    config->scl_low_count = 0U;
    config->ten_bit_address = (target_address > 0x007FU);
    config->restart_enable = true;
}

int32_t i2c_api_init(uint32_t instance, uint16_t target_address,
                     uint32_t bus_hz)
{
    uint32_t base = i2c_api_instance_to_base(instance);
    uint32_t reset_id = i2c_api_instance_to_reset(instance);
    socfpga_i2c_config_t config;

    if (base == 0U) {
        return -ENOSYS;
    }

    if (i2c_api_handle != NULL) {
        return -EBUSY;
    }

    i2c_api_fill_config(&config, base, reset_id, target_address, bus_hz);

    return socfpga_i2c_init(&config, &i2c_api_handle);
}

int32_t i2c_api_init_with_base(uint32_t base_address, uint16_t target_address,
                               uint32_t bus_hz)
{
    socfpga_i2c_config_t config;

    if (i2c_api_handle != NULL) {
        return -EBUSY;
    }

    i2c_api_fill_config(&config, base_address, SOCFPGA_I2C_RESET_NONE,
                        target_address, bus_hz);

    return socfpga_i2c_init(&config, &i2c_api_handle);
}

int32_t i2c_api_close(void)
{
    int32_t ret;

    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }

    ret = socfpga_i2c_deinit(i2c_api_handle);
    if (ret == -EBUSY) {
        /* Keep the handle so a later close can release it. */
        return ret;
    }
    if (ret != 0) {
        /* Release it anyway, or this singleton stays permanently unavailable. */
        (void)socfpga_i2c_close(i2c_api_handle);
    }

    i2c_api_handle = NULL;
    return ret;
}

int32_t i2c_api_deinit(void)
{
    return i2c_api_close();
}

int32_t i2c_api_write(const uint8_t *buffer, size_t length)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_write_sync(i2c_api_handle, buffer, length);
}

int32_t i2c_api_read(uint8_t *buffer, size_t length)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_read_sync(i2c_api_handle, buffer, length);
}


int32_t i2c_api_write_then_read(const uint8_t *tx_buffer, size_t tx_length,
                                uint8_t *rx_buffer, size_t rx_length)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_write_then_read_sync(i2c_api_handle,
                                            tx_buffer,
                                            tx_length,
                                            rx_buffer,
                                            rx_length);
}

int32_t i2c_api_get_status(uint32_t *status)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_get_status(i2c_api_handle, status);
}

int32_t i2c_api_get_info(socfpga_i2c_info_t *info)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_get_info(i2c_api_handle, info);
}

int32_t i2c_api_set_target(uint16_t target_address)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_set_target_address(i2c_api_handle, target_address);
}

int32_t i2c_api_probe(uint16_t target_address)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_probe(i2c_api_handle, target_address);
}

int32_t i2c_api_recover(void)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_recover_bus(i2c_api_handle);
}

int32_t i2c_api_write_async(const uint8_t *buffer, size_t length,
                            socfpga_i2c_callback_t callback, void *context)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_write_async(i2c_api_handle, buffer, length, callback,
                                   context);
}

int32_t i2c_api_read_async(uint8_t *buffer, size_t length,
                           socfpga_i2c_callback_t callback, void *context)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_read_async(i2c_api_handle, buffer, length, callback,
                                  context);
}

int32_t i2c_api_write_then_read_async(const uint8_t *tx_buffer,
                                      size_t tx_length, uint8_t *rx_buffer,
                                      size_t rx_length,
                                      socfpga_i2c_callback_t callback,
                                      void *context)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_write_then_read_async(i2c_api_handle, tx_buffer,
                                             tx_length, rx_buffer, rx_length,
                                             callback, context);
}

int32_t i2c_api_wait_async(uint32_t timeout_us)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_wait_async_complete(i2c_api_handle, timeout_us);
}

int32_t i2c_api_get_abort_source(uint32_t *source)
{
    if (i2c_api_handle == NULL) {
        return -EINVAL;
    }
    return socfpga_i2c_get_abort_source(i2c_api_handle, source);
}
