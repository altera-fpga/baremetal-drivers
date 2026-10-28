/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "errno.h"
#include "spi_api.h"
#include "socfpga_spi_ll.h"
#include "socfpga_spi_reg.h"

static spi_handle_t g_spi_handle;
static spi_api_config_t g_spi_config = {
    SPI_API_DEFAULT_INSTANCE,
    SPI_API_DEFAULT_SLAVE,
    SPI_API_DEFAULT_SPEED_HZ,
    SPI_MODE0
};

static int32_t spi_api_validate_config(const spi_api_config_t *config)
{
    if (config == NULL) {
        return -EINVAL;
    }
    if (config->instance > 1U) {
        return -EINVAL;
    }
    if ((config->slave < 1U) || (config->slave > 4U)) {
        return -EINVAL;
    }
    if (config->speed_hz == 0U) {
        return -EINVAL;
    }
    if (config->mode > SPI_MODE3) {
        return -EINVAL;
    }

    return 0;
}

int32_t spi_api_open(const spi_api_config_t *config)
{
    spi_cfg_t low_cfg;
    spi_api_config_t requested;
    int32_t ret;

    if (config == NULL) {
        requested.instance = SPI_API_DEFAULT_INSTANCE;
        requested.slave = SPI_API_DEFAULT_SLAVE;
        requested.speed_hz = SPI_API_DEFAULT_SPEED_HZ;
        requested.mode = SPI_MODE0;
    } else {
        requested = *config;
    }

    ret = spi_api_validate_config(&requested);
    if (ret != 0) {
        return ret;
    }

    if (g_spi_handle != NULL) {
        return -EBUSY;
    }

    g_spi_handle = spi_open(requested.instance);
    if (g_spi_handle == NULL) {
        return -EIO;
    }

    ret = spi_select_slave(g_spi_handle, requested.slave);
    if (ret != 0) {
        (void)spi_close(g_spi_handle);
        g_spi_handle = NULL;
        return ret;
    }

    low_cfg.clk = requested.speed_hz;
    low_cfg.mode = requested.mode;
    ret = spi_ioctl(g_spi_handle, SPI_SET_CONFIG, &low_cfg);
    if (ret != 0) {
        (void)spi_close(g_spi_handle);
        g_spi_handle = NULL;
        return ret;
    }

    g_spi_config = requested;
    return 0;
}

int32_t spi_api_close(void)
{
    int32_t ret;

    if (g_spi_handle == NULL) {
        return 0;
    }

    ret = spi_close(g_spi_handle);
    g_spi_handle = NULL;
    return ret;
}

int32_t spi_api_transfer(const uint8_t *txbuf, uint8_t *rxbuf, size_t nbytes)
{
    uint8_t *tx_mutable = (uint8_t *)(uintptr_t)txbuf;

    if (g_spi_handle == NULL) {
        return -ENODEV;
    }
    if ((txbuf == NULL) || (nbytes == 0U) || (nbytes > UINT16_MAX)) {
        return -EINVAL;
    }

    return spi_transfer_sync(g_spi_handle,
                             tx_mutable,
                             rxbuf,
                             (uint16_t)nbytes);
}

int32_t spi_api_get_config(spi_api_config_t *config)
{
    spi_cfg_t low_cfg;
    int32_t ret;

    if (config == NULL) {
        return -EINVAL;
    }
    if (g_spi_handle == NULL) {
        return -ENODEV;
    }

    ret = spi_ioctl(g_spi_handle, SPI_GET_CONFIG, &low_cfg);
    if (ret != 0) {
        return ret;
    }

    *config = g_spi_config;
    config->speed_hz = low_cfg.clk;
    config->mode = low_cfg.mode;

    return 0;
}

int32_t spi_api_get_version(uint32_t instance, uint32_t *version)
{
    spi_api_config_t config;
    int32_t ret;

    if ((instance > 1U) || (version == NULL)) {
        return -EINVAL;
    }

    if (g_spi_handle != NULL) {
        if (g_spi_config.instance != instance) {
            return -EBUSY;
        }
        *version = spi_get_version(GET_BASE_ADDRESS(instance));
        return 0;
    }

    config.instance = instance;
    config.slave = SPI_API_DEFAULT_SLAVE;
    config.speed_hz = SPI_API_DEFAULT_SPEED_HZ;
    config.mode = SPI_MODE0;

    ret = spi_api_open(&config);
    if (ret != 0) {
        return ret;
    }

    *version = spi_get_version(GET_BASE_ADDRESS(instance));
    return spi_api_close();
}

int32_t spi_api_loopback_test(uint32_t instance, uint32_t slave, size_t nbytes)
{
    static uint8_t tx_buf[SPI_API_LOOPBACK_MAX_LEN];
    static uint8_t rx_buf[SPI_API_LOOPBACK_MAX_LEN];
    spi_api_config_t config;
    uint32_t i;
    int32_t ret;

    if ((nbytes == 0U) || (nbytes > SPI_API_LOOPBACK_MAX_LEN)) {
        return -EINVAL;
    }

    config.instance = instance;
    config.slave = slave;
    config.speed_hz = SPI_API_DEFAULT_SPEED_HZ;
    config.mode = SPI_MODE0;

    ret = spi_api_open(&config);
    if (ret != 0) {
        return ret;
    }

    for (i = 0U; i < nbytes; i++) {
        tx_buf[i] = (uint8_t)(0xA5U ^ (uint8_t)i);
        rx_buf[i] = 0U;
    }

    spi_set_loopback(GET_BASE_ADDRESS(instance), true);
    ret = spi_api_transfer(tx_buf, rx_buf, nbytes);
    spi_set_loopback(GET_BASE_ADDRESS(instance), false);

    if (ret == 0) {
        if (memcmp(tx_buf, rx_buf, nbytes) != 0) {
            ret = -EIO;
        }
    }

    (void)spi_api_close();
    return ret;
}

