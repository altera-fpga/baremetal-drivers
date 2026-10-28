/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_spi.c
 *
 * SPI source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "mmio.h"
#include "errno.h"
#include "socfpga_spi.h"
#include "socfpga_spi_ll.h"
#include "socfpga_spi_reg.h"

#define MAX_INSTANCES    2U

struct spi_handle
{
    bool is_open;
    bool is_rx_busy;
    bool is_tx_busy;
    bool is_rx_async;
    bool is_tx_async;
    bool is_rx_on;
    bool is_tx_on;
    uint32_t instance;
    uint32_t base_address;
    uint32_t slave_id;
    uint16_t tx_size;
    uint16_t rx_size;
    uint16_t tx_bytes_left;
    uint16_t rx_bytes_left;
    uint8_t *tx_buf;
    uint8_t *rx_buf;
    spi_callback_t callback_fn;
    void *cb_user_context;
};

static struct spi_handle spi_descriptor[MAX_INSTANCES];

void spi_isr(void *param);

static bool spi_is_handle_valid(spi_handle_t handle)
{
    uint32_t i;

    if (handle == NULL) {
        return false;
    }

    for (i = 0U; i < MAX_INSTANCES; i++) {
        if (handle == &spi_descriptor[i]) {
            return true;
        }
    }

    return false;
}

spi_handle_t spi_open(uint32_t instance)
{
    spi_handle_t handle;

    if (instance >= MAX_INSTANCES) {
        return NULL;
    }

    handle = &spi_descriptor[instance];
    if (handle->is_open) {
        return NULL;
    }

    (void)memset(handle, 0, sizeof(*handle));
    handle->is_open = true;
    handle->instance = instance;
    handle->base_address = GET_BASE_ADDRESS(instance);
    handle->slave_id = 1U;

    spi_init(instance);
    spi_disable_interrupt(handle->base_address, SPI_ALL_INTERRUPTS);

    return handle;
}

int32_t spi_set_callback(spi_handle_t const hspi,
                         spi_callback_t callback,
                         void *pcntxt)
{
    if (!spi_is_handle_valid(hspi) || !hspi->is_open) {
        return -EINVAL;
    }

    if (hspi->is_rx_busy || hspi->is_tx_busy) {
        return -EBUSY;
    }

    hspi->callback_fn = callback;
    hspi->cb_user_context = pcntxt;

    return 0;
}

int32_t spi_ioctl(spi_handle_t const hspi, spi_ioctl_t cmd, void *const buf)
{
    spi_cfg_t config = {0U, SPI_MODE0};

    if (!spi_is_handle_valid(hspi) || !hspi->is_open) {
        return -EINVAL;
    }

    switch (cmd) {
    case SPI_SET_CONFIG:
        if (hspi->is_tx_busy || hspi->is_rx_busy) {
            return -EBUSY;
        }
        if (buf == NULL) {
            return -EINVAL;
        }
        config = *(spi_cfg_t *)buf;

        int32_t cfg_rc = spi_set_config(hspi->base_address,
                                        config.clk,
                                        config.mode);
        if (cfg_rc != 0) {
            return cfg_rc;
        }

        spi_set_transfermode(hspi->base_address, SPI_TX_RX_MOD);
        break;

    case SPI_GET_CONFIG:
        if (buf == NULL) {
            return -EINVAL;
        }
        spi_get_config(hspi->base_address, &config.clk, &config.mode);
        *(spi_cfg_t *)buf = config;
        break;

    case SPI_GET_TX_NBYTES:
        if (buf == NULL) {
            return -EINVAL;
        }
        *(uint16_t *)buf = (uint16_t)(hspi->tx_size - hspi->tx_bytes_left);
        break;

    case SPI_GET_RX_NBYTES:
        if (buf == NULL) {
            return -EINVAL;
        }
        *(uint16_t *)buf = (uint16_t)(hspi->rx_size - hspi->rx_bytes_left);
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

static void spi_mark_transfer_start(spi_handle_t hspi,
                                    uint8_t *txbuf,
                                    uint8_t *rxbuf,
                                    uint16_t nbytes,
                                    bool async)
{
    hspi->tx_buf = txbuf;
    hspi->rx_buf = rxbuf;
    hspi->tx_size = nbytes;
    hspi->rx_size = (rxbuf != NULL) ? nbytes : 0U;
    hspi->tx_bytes_left = nbytes;
    hspi->rx_bytes_left = (rxbuf != NULL) ? nbytes : 0U;
    hspi->is_tx_busy = true;
    hspi->is_rx_busy = (rxbuf != NULL);
    hspi->is_tx_async = async;
    hspi->is_rx_async = async;
    hspi->is_tx_on = true;
    hspi->is_rx_on = (rxbuf != NULL);
}

static void spi_mark_transfer_done(spi_handle_t hspi, uint16_t nbytes)
{
    hspi->tx_bytes_left = 0U;
    hspi->rx_bytes_left = 0U;
    hspi->is_tx_busy = false;
    hspi->is_rx_busy = false;
    hspi->is_tx_async = false;
    hspi->is_rx_async = false;
    hspi->is_tx_on = false;
    hspi->is_rx_on = false;
    (void)nbytes;
}

int32_t spi_transfer_sync(spi_handle_t const hspi,
                          uint8_t *const txbuf,
                          uint8_t *const rxbuf,
                          uint16_t nbytes)
{
    int32_t ret;

    if (!spi_is_handle_valid(hspi) || (txbuf == NULL) || (nbytes == 0U)) {
        return -EINVAL;
    }

    if (!hspi->is_open) {
        return -EINVAL;
    }

    if (hspi->is_tx_busy || hspi->is_rx_busy) {
        return -EBUSY;
    }

    spi_mark_transfer_start(hspi, txbuf, rxbuf, nbytes, false);

    spi_set_transfermode(hspi->base_address, SPI_TX_RX_MOD);
    spi_select_chip(hspi->instance, hspi->slave_id);
    ret = spi_transfer_poll(hspi->base_address,
                            txbuf,
                            rxbuf,
                            nbytes,
                            SPI_POLL_TIMEOUT);
    spi_select_chip(hspi->instance, 0U);

    spi_mark_transfer_done(hspi, nbytes);
    return ret;
}

int32_t spi_transfer_async(spi_handle_t const hspi,
                           uint8_t *const txbuf,
                           uint8_t *const rxbuf,
                           uint16_t nbytes)
{
    int32_t ret;
    spi_xfer_status_t status;

    if (!spi_is_handle_valid(hspi) || (txbuf == NULL) || (nbytes == 0U)) {
        return -EINVAL;
    }

    if (!hspi->is_open) {
        return -EINVAL;
    }

    if (hspi->is_tx_busy || hspi->is_rx_busy) {
        return -EBUSY;
    }

    /* This bare-metal implementation completes the requested transfer with
     * bounded polling and then invokes the callback before returning.  It keeps
     * the public asynchronous entry point available without depending on an
     * operating-system semaphore or scheduler.
     */
    spi_mark_transfer_start(hspi, txbuf, rxbuf, nbytes, true);
    spi_set_transfermode(hspi->base_address, SPI_TX_RX_MOD);
    spi_select_chip(hspi->instance, hspi->slave_id);
    ret = spi_transfer_poll(hspi->base_address,
                            txbuf,
                            rxbuf,
                            nbytes,
                            SPI_POLL_TIMEOUT);
    spi_select_chip(hspi->instance, 0U);
    spi_mark_transfer_done(hspi, nbytes);

    if (hspi->callback_fn != NULL) {
        status = (ret == 0) ? SPI_SUCCESS : SPI_XFER_ERROR;
        hspi->callback_fn(status, hspi->cb_user_context);
    }

    return ret;
}

int32_t spi_select_slave(spi_handle_t const hspi, uint32_t ss)
{
    if (!spi_is_handle_valid(hspi) || !hspi->is_open) {
        return -EINVAL;
    }

    if ((ss < 1U) || (ss > 4U)) {
        return -EINVAL;
    }

    if (hspi->is_tx_busy || hspi->is_rx_busy) {
        return -EBUSY;
    }

    hspi->slave_id = ss;
    return 0;
}

int32_t spi_cancel(spi_handle_t const hspi)
{
    if (!spi_is_handle_valid(hspi) || !hspi->is_open) {
        return -EINVAL;
    }

    spi_disable_interrupt(hspi->base_address, SPI_ALL_INTERRUPTS);
    spi_select_chip(hspi->instance, 0U);
    spi_flush_rx_fifo(hspi->base_address);
    hspi->is_tx_busy = false;
    hspi->is_rx_busy = false;
    hspi->tx_bytes_left = 0U;
    hspi->rx_bytes_left = 0U;

    return 0;
}

int32_t spi_close(spi_handle_t const hspi)
{
    if (!spi_is_handle_valid(hspi)) {
        return -EINVAL;
    }
    if (!hspi->is_open) {
        return -EINVAL;
    }
    if (hspi->is_tx_busy || hspi->is_rx_busy) {
        return -EBUSY;
    }

    spi_deinit(hspi->instance);
    (void)memset(hspi, 0, sizeof(*hspi));

    return 0;
}

void spi_isr(void *param)
{
    spi_handle_t hspi = (spi_handle_t)param;

    if ((hspi == NULL) || !spi_is_handle_valid(hspi) || !hspi->is_open) {
        return;
    }

    /* Interrupt-driven SPI is intentionally not used by the default bare-metal
     * API path.  Keep the handler as a safe drain path for applications that
     * register the interrupt manually.
     */
    spi_disable_interrupt(hspi->base_address, SPI_ALL_INTERRUPTS);
    spi_flush_rx_fifo(hspi->base_address);
    hspi->is_tx_busy = false;
    hspi->is_rx_busy = false;

    if (hspi->callback_fn != NULL) {
        hspi->callback_fn(SPI_XFER_ERROR, hspi->cb_user_context);
    }
}
