/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_i2c.c
 *
 * I2C source implementation for the SoCFPGA bare-metal software stack.
 */

#include <string.h>

#include "lib_time.h"
#include "socfpga_clk_mngr_ll.h"
#include "socfpga_i2c.h"
#include "socfpga_i2c_ll.h"
#include "socfpga_i2c_reg.h"

#define SOCFPGA_I2C_MAX_HANDLES 5U
#define SOCFPGA_I2C_ASYNC_ERROR_MASK (I2C_INTR_RX_UNDER_MASK | \
                                      I2C_INTR_RX_OVER_MASK | \
                                      I2C_INTR_TX_OVER_MASK | \
                                      I2C_INTR_TX_ABRT_MASK)

struct socfpga_i2c_descriptor {
    bool is_open;
    bool tx_is_busy;
    bool rx_is_busy;
    bool tx_holds_bus;
    uint32_t last_abort_source;
    socfpga_i2c_config_t config;
    socfpga_i2c_info_t info;
    const uint8_t *tx_buffer;
    uint8_t *rx_buffer;
    size_t tx_length;
    size_t rx_length;
    size_t tx_index;
    size_t rx_index;
    size_t rx_cmd_index;
    socfpga_i2c_callback_t callback;
    void *callback_context;
};

static struct socfpga_i2c_descriptor i2c_handles[SOCFPGA_I2C_MAX_HANDLES];

static struct socfpga_i2c_descriptor *i2c_alloc_handle(uint32_t base_address)
{
    uint32_t index;
    struct socfpga_i2c_descriptor *free_handle = NULL;

    for (index = 0U; index < SOCFPGA_I2C_MAX_HANDLES; index++) {
        if ((i2c_handles[index].is_open) &&
            (i2c_handles[index].config.base_address == base_address)) {
            return NULL;
        }
        if ((!i2c_handles[index].is_open) && (free_handle == NULL)) {
            free_handle = &i2c_handles[index];
        }
    }

    return free_handle;
}

/* Only descriptors this driver owns are accepted, so a stale or foreign pointer
 * is never dereferenced.
 */
static bool i2c_valid_handle(socfpga_i2c_handle_t handle)
{
    uint32_t index;

    for (index = 0U; index < SOCFPGA_I2C_MAX_HANDLES; index++) {
        if (handle == &i2c_handles[index]) {
            return handle->is_open;
        }
    }

    return false;
}

static void i2c_set_interrupt_mask(socfpga_i2c_handle_t handle, uint32_t mask)
{
    socfpga_i2c_ll_write_reg(handle->config.base_address, I2C_INTR_MASK, mask);
}

static void i2c_drain_rx_fifo(uint32_t base_address)
{
    while ((socfpga_i2c_ll_get_status(base_address) &
            I2C_STATUS_RFNE_MASK) != 0U) {
        (void)socfpga_i2c_ll_read_reg(base_address, I2C_DATA_CMD);
    }
}

static bool i2c_bus_available(uint32_t base_address)
{
    uint32_t status = socfpga_i2c_ll_get_status(base_address);

    return (((status & I2C_STATUS_MST_ACTIVITY_MASK) == 0U) &&
            ((status & I2C_STATUS_TFE_MASK) != 0U));
}

static void i2c_async_update_interrupts(socfpga_i2c_handle_t handle)
{
    uint32_t mask = SOCFPGA_I2C_ASYNC_ERROR_MASK | I2C_INTR_STOP_DET_MASK;

    if (handle->tx_is_busy && (handle->tx_index < handle->tx_length)) {
        mask |= I2C_INTR_TX_EMPTY_MASK;
    }

    if (handle->rx_is_busy) {
        if (handle->rx_index < handle->rx_length) {
            mask |= I2C_INTR_RX_FULL_MASK;
        }
        if ((handle->rx_cmd_index < handle->rx_length) &&
            (handle->rx_cmd_index == handle->rx_index)) {
            mask |= I2C_INTR_TX_EMPTY_MASK;
        }
    }

    i2c_set_interrupt_mask(handle, mask);
}

static void i2c_async_prime_write(socfpga_i2c_handle_t handle)
{
    uint32_t base_address = handle->config.base_address;

    while (handle->tx_index < handle->tx_length) {
        uint32_t status = socfpga_i2c_ll_get_status(base_address);
        uint32_t cmd;

        if ((status & I2C_STATUS_TFNF_MASK) == 0U) {
            break;
        }

        cmd = (uint32_t)handle->tx_buffer[handle->tx_index] &
              I2C_DATA_CMD_DAT_MASK;
        if (handle->tx_index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }
        /* A combined transfer keeps the bus, so STOP only goes on the last write
         * byte when no read phase follows.
         */
        if (((handle->tx_index + 1U) == handle->tx_length) &&
            (!handle->tx_holds_bus)) {
            cmd |= I2C_DATA_CMD_STOP_MASK;
        }

        socfpga_i2c_ll_write_reg(base_address, I2C_DATA_CMD, cmd);
        handle->tx_index++;
    }
}

static void i2c_async_prime_read(socfpga_i2c_handle_t handle)
{
    uint32_t base_address = handle->config.base_address;

    /* The command FIFO is ordered, so read commands must not jump the queue
     * ahead of pending write bytes.
     */
    if (handle->tx_is_busy && (handle->tx_index < handle->tx_length)) {
        return;
    }

    while (handle->rx_index < handle->rx_length) {
        uint32_t status = socfpga_i2c_ll_get_status(base_address);

        if ((status & I2C_STATUS_RFNE_MASK) == 0U) {
            break;
        }
        handle->rx_buffer[handle->rx_index] =
            (uint8_t)(socfpga_i2c_ll_read_reg(base_address, I2C_DATA_CMD) &
                      I2C_DATA_CMD_DAT_MASK);
        handle->rx_index++;
    }

    if ((handle->rx_cmd_index < handle->rx_length) &&
        (handle->rx_cmd_index == handle->rx_index) &&
                ((socfpga_i2c_ll_get_status(base_address) &
                    I2C_STATUS_TFNF_MASK) != 0U)) {
        uint32_t cmd = I2C_DATA_CMD_CMD_MASK;

        if (handle->rx_cmd_index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }
        if ((handle->rx_cmd_index + 1U) == handle->rx_length) {
            cmd |= I2C_DATA_CMD_STOP_MASK;
        }

        socfpga_i2c_ll_write_reg(base_address, I2C_DATA_CMD, cmd);
        handle->rx_cmd_index++;
    }
}

static void i2c_async_complete(socfpga_i2c_handle_t handle, int32_t status)
{
    socfpga_i2c_callback_t callback = handle->callback;
    void *context = handle->callback_context;

    socfpga_i2c_ll_mask_all_interrupts(handle->config.base_address);

    handle->tx_is_busy = false;
    handle->rx_is_busy = false;
    handle->tx_holds_bus = false;
    handle->tx_buffer = NULL;
    handle->rx_buffer = NULL;
    handle->tx_length = 0U;
    handle->rx_length = 0U;
    handle->tx_index = 0U;
    handle->rx_index = 0U;
    handle->rx_cmd_index = 0U;
    handle->callback = NULL;
    handle->callback_context = NULL;

    if (callback != NULL) {
        callback(handle, status, context);
    }
}

/* bus_hz wins; otherwise the legacy speed_mode is expanded to its nominal rate. */
static uint32_t i2c_target_bus_hz(const socfpga_i2c_config_t *config)
{
    if (config->bus_hz != 0U) {
        return config->bus_hz;
    }

    switch (config->speed_mode) {
    case SOCFPGA_I2C_SPEED_FAST:
        return 400000U;
    case SOCFPGA_I2C_SPEED_FASTPLUS:
        return 1000000U;
    default:
        return 100000U;
    }
}

static int32_t i2c_apply_timing(const socfpga_i2c_config_t *config,
                                socfpga_i2c_info_t *info)
{
    uint32_t base_address = config->base_address;
    uint32_t speed_mode = config->speed_mode;
    uint32_t ic_clk_hz = config->input_clock_hz;
    int32_t ret;

    info->bus_hz = i2c_target_bus_hz(config);

    /* An explicit count pair overrides the calculation, which bring-up needs when
     * a board's rise time makes the derived counts unusable.
     */
    if ((config->scl_high_count != 0U) && (config->scl_low_count != 0U)) {
        if ((speed_mode < SOCFPGA_I2C_SPEED_STANDARD) ||
            (speed_mode > SOCFPGA_I2C_SPEED_FASTPLUS)) {
            speed_mode = SOCFPGA_I2C_SPEED_STANDARD;
        }
        ret = socfpga_i2c_ll_set_scl_count(base_address, speed_mode,
                                           config->scl_high_count,
                                           config->scl_low_count);
    } else {
        if (ic_clk_hz == 0U) {
            ret = clk_mngr_ll_get_clk(CLOCK_I2C, &ic_clk_hz);
            if (ret != 0) {
                return ret;
            }
        }

        ret = socfpga_i2c_ll_set_timing(base_address, ic_clk_hz, info->bus_hz,
                                        &speed_mode);
    }

    if (ret != 0) {
        return ret;
    }

    info->input_clock_hz = ic_clk_hz;
    info->speed_mode = speed_mode;

    return 0;
}

int32_t socfpga_i2c_init(const socfpga_i2c_config_t *config,
                         socfpga_i2c_handle_t *handle)
{
    struct socfpga_i2c_descriptor *desc;
    socfpga_i2c_info_t info;
    uint32_t hcnt_offset;
    uint32_t lcnt_offset;
    uint32_t timeout;
    int32_t ret;

    if ((config == NULL) || (handle == NULL) ||
        (config->base_address == 0U) || (config->target_address > 0x03FFU)) {
        return -EINVAL;
    }

    desc = i2c_alloc_handle(config->base_address);
    if (desc == NULL) {
        return -EBUSY;
    }

    timeout = (config->timeout == 0U) ? SOCFPGA_I2C_DEFAULT_TIMEOUT : config->timeout;
    (void)memset(&info, 0, sizeof(info));

    if (config->reset_id != SOCFPGA_I2C_RESET_NONE) {
        ret = rstmgr_deassert_reset((reset_periphrl_t)config->reset_id);
        if (ret != 0) {
            return ret;
        }
    }

    /* Probe before configuring, so an absent or unclocked instance reports -ENODEV
     * instead of surfacing later as an unexplained transfer timeout.
     */
    ret = socfpga_i2c_ll_probe_controller(config->base_address,
                                          &info.component_version);
    if (ret != 0) {
        return ret;
    }

    ret = socfpga_i2c_ll_enable(config->base_address, false, timeout);
    if (ret != 0) {
        return ret;
    }

    /* Timing decides the speed mode, so it is resolved before IC_CON is written. */
    ret = i2c_apply_timing(config, &info);
    if (ret != 0) {
        return ret;
    }

    ret = socfpga_i2c_ll_configure_master(config->base_address,
                                          config->target_address,
                                          info.speed_mode,
                                          config->ten_bit_address,
                                          config->restart_enable);
    if (ret != 0) {
        return ret;
    }

    socfpga_i2c_ll_mask_all_interrupts(config->base_address);
    socfpga_i2c_ll_clear_interrupts(config->base_address);
    socfpga_i2c_ll_write_reg(config->base_address, I2C_RX_TL, 0U);
    socfpga_i2c_ll_write_reg(config->base_address, I2C_TX_TL, 0U);

    ret = socfpga_i2c_ll_enable(config->base_address, true, timeout);
    if (ret != 0) {
        return ret;
    }

    hcnt_offset = (info.speed_mode == SOCFPGA_I2C_SPEED_STANDARD)
                  ? I2C_SS_SCL_HCNT : I2C_FS_SCL_HCNT;
    lcnt_offset = (info.speed_mode == SOCFPGA_I2C_SPEED_STANDARD)
                  ? I2C_SS_SCL_LCNT : I2C_FS_SCL_LCNT;

    info.scl_high_count = socfpga_i2c_ll_read_reg(config->base_address,
                                                  hcnt_offset);
    info.scl_low_count = socfpga_i2c_ll_read_reg(config->base_address,
                                                 lcnt_offset);
    (void)socfpga_i2c_ll_get_fifo_depth(config->base_address,
                                        &info.tx_fifo_depth,
                                        &info.rx_fifo_depth);

    (void)memset(desc, 0, sizeof(*desc));
    desc->is_open = true;
    desc->config = *config;
    desc->config.timeout = timeout;
    desc->config.speed_mode = info.speed_mode;
    desc->info = info;
    *handle = desc;

    return 0;
}

int32_t socfpga_i2c_get_info(socfpga_i2c_handle_t handle,
                             socfpga_i2c_info_t *info)
{
    if ((!i2c_valid_handle(handle)) || (info == NULL)) {
        return -EINVAL;
    }

    *info = handle->info;
    return 0;
}

int32_t socfpga_i2c_set_target_address(socfpga_i2c_handle_t handle,
                                      uint16_t target_address)
{
    bool ten_bit = (target_address > 0x007FU);
    int32_t ret;

    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    ret = socfpga_i2c_ll_set_target_address(handle->config.base_address,
                                            target_address, ten_bit,
                                            handle->config.timeout);
    if (ret != 0) {
        return ret;
    }

    handle->config.target_address = target_address;
    handle->config.ten_bit_address = ten_bit;
    return 0;
}

int32_t socfpga_i2c_probe(socfpga_i2c_handle_t handle, uint16_t target_address)
{
    int32_t ret;

    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    ret = socfpga_i2c_set_target_address(handle, target_address);
    if (ret != 0) {
        return ret;
    }

    handle->last_abort_source = 0U;
    handle->rx_is_busy = true;
    ret = socfpga_i2c_ll_probe_address(handle->config.base_address,
                                        handle->config.timeout,
                                        &handle->last_abort_source);
    handle->rx_is_busy = false;
    return ret;
}

int32_t socfpga_i2c_recover_bus(socfpga_i2c_handle_t handle)
{
    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    return socfpga_i2c_ll_recover_bus(handle->config.base_address,
                                       handle->config.timeout);
}

const char *socfpga_i2c_abort_source_str(uint32_t source)
{
    source &= I2C_TX_ABRT_CAUSE_MASK;

    if ((source & I2C_TX_ABRT_7B_ADDR_NOACK_MASK) != 0U) {
        return "address NACK";
    }
    if ((source & (I2C_TX_ABRT_10ADDR1_NOACK_MASK |
                   I2C_TX_ABRT_10ADDR2_NOACK_MASK)) != 0U) {
        return "10-bit address NACK";
    }
    if ((source & I2C_TX_ABRT_TXDATA_NOACK_MASK) != 0U) {
        return "data NACK";
    }
    if ((source & I2C_TX_ABRT_ARB_LOST_MASK) != 0U) {
        return "arbitration lost";
    }
    if ((source & I2C_TX_ABRT_MASTER_DIS_MASK) != 0U) {
        return "master disabled";
    }
    if ((source & (I2C_TX_ABRT_SBYTE_NORSTRT_MASK |
                   I2C_TX_ABRT_HS_NORSTRT_MASK |
                   I2C_TX_ABRT_10B_RD_NORSTRT_MASK)) != 0U) {
        return "restart required but disabled";
    }
    if ((source & I2C_TX_ABRT_USER_ABRT_MASK) != 0U) {
        return "aborted by software";
    }
    if (source == 0U) {
        return "none";
    }

    return "other";
}

uint32_t socfpga_i2c_abort_flush_count(uint32_t source)
{
    return (source & I2C_TX_ABRT_FLUSH_CNT_MASK) >> I2C_TX_ABRT_FLUSH_CNT_POS;
}

int32_t socfpga_i2c_get_abort_source(socfpga_i2c_handle_t handle,
                                    uint32_t *source)
{
    if ((!i2c_valid_handle(handle)) || (source == NULL)) {
        return -EINVAL;
    }

    *source = handle->last_abort_source;
    return 0;
}

int32_t socfpga_i2c_deinit(socfpga_i2c_handle_t handle)
{
    int32_t ret;

    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    ret = socfpga_i2c_ll_enable(handle->config.base_address, false,
                                handle->config.timeout);
    if (ret != 0) {
        /* A transfer in flight blocks the disable, so cancel it and retry once. */
        (void)socfpga_i2c_ll_recover_bus(handle->config.base_address,
                                         handle->config.timeout);
        ret = socfpga_i2c_ll_enable(handle->config.base_address, false,
                                    handle->config.timeout);
        if (ret != 0) {
            return ret;
        }
    }

    return socfpga_i2c_close(handle);
}

int32_t socfpga_i2c_close(socfpga_i2c_handle_t handle)
{
    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    (void)memset(handle, 0, sizeof(*handle));
    return 0;
}

int32_t socfpga_i2c_write_sync(socfpga_i2c_handle_t handle,
                               const uint8_t *buffer, size_t length)
{
    int32_t ret;

    if ((!i2c_valid_handle(handle)) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    handle->last_abort_source = 0U;
    handle->tx_is_busy = true;
    ret = socfpga_i2c_ll_write_sync(handle->config.base_address, buffer,
                                    length, handle->config.timeout,
                                    &handle->last_abort_source);
    handle->tx_is_busy = false;
    return ret;
}

int32_t socfpga_i2c_read_sync(socfpga_i2c_handle_t handle,
                              uint8_t *buffer, size_t length)
{
    int32_t ret;

    if ((!i2c_valid_handle(handle)) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    handle->last_abort_source = 0U;
    handle->rx_is_busy = true;
    ret = socfpga_i2c_ll_read_sync(handle->config.base_address, buffer,
                                   length, handle->config.timeout,
                                   &handle->last_abort_source);
    handle->rx_is_busy = false;
    return ret;
}


int32_t socfpga_i2c_write_then_read_sync(socfpga_i2c_handle_t handle,
                                         const uint8_t *tx_buffer,
                                         size_t tx_length,
                                         uint8_t *rx_buffer,
                                         size_t rx_length)
{
    int32_t ret;

    if ((!i2c_valid_handle(handle)) || (tx_buffer == NULL) ||
        (tx_length == 0U) || (rx_buffer == NULL) || (rx_length == 0U)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }

    handle->last_abort_source = 0U;
    handle->tx_is_busy = true;
    handle->rx_is_busy = true;
    ret = socfpga_i2c_ll_write_then_read_sync(handle->config.base_address,
                                              tx_buffer,
                                              tx_length,
                                              rx_buffer,
                                              rx_length,
                                              handle->config.timeout,
                                              &handle->last_abort_source);
    handle->rx_is_busy = false;
    handle->tx_is_busy = false;
    return ret;
}

int32_t socfpga_i2c_write_async(socfpga_i2c_handle_t handle,
                                const uint8_t *buffer, size_t length,
                                socfpga_i2c_callback_t callback,
                                void *context)
{
    if ((!i2c_valid_handle(handle)) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }
    if (!i2c_bus_available(handle->config.base_address)) {
        return -EBUSY;
    }

    i2c_drain_rx_fifo(handle->config.base_address);
    socfpga_i2c_ll_mask_all_interrupts(handle->config.base_address);
    socfpga_i2c_ll_clear_interrupts(handle->config.base_address);

    handle->callback = callback;
    handle->callback_context = context;
    handle->tx_buffer = buffer;
    handle->tx_length = length;
    handle->tx_index = 0U;
    handle->rx_buffer = NULL;
    handle->rx_length = 0U;
    handle->rx_index = 0U;
    handle->rx_cmd_index = 0U;
    handle->tx_is_busy = true;
    handle->tx_holds_bus = false;

    i2c_async_prime_write(handle);
    i2c_async_update_interrupts(handle);
    return 0;
}

int32_t socfpga_i2c_read_async(socfpga_i2c_handle_t handle,
                               uint8_t *buffer, size_t length,
                               socfpga_i2c_callback_t callback,
                               void *context)
{
    if ((!i2c_valid_handle(handle)) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }
    if (!i2c_bus_available(handle->config.base_address)) {
        return -EBUSY;
    }

    i2c_drain_rx_fifo(handle->config.base_address);
    socfpga_i2c_ll_mask_all_interrupts(handle->config.base_address);
    socfpga_i2c_ll_clear_interrupts(handle->config.base_address);

    handle->callback = callback;
    handle->callback_context = context;
    handle->tx_buffer = NULL;
    handle->tx_length = 0U;
    handle->tx_index = 0U;
    handle->rx_buffer = buffer;
    handle->rx_length = length;
    handle->rx_index = 0U;
    handle->rx_cmd_index = 0U;
    handle->rx_is_busy = true;

    i2c_async_prime_read(handle);
    i2c_async_update_interrupts(handle);
    return 0;
}

int32_t socfpga_i2c_write_then_read_async(socfpga_i2c_handle_t handle,
                                          const uint8_t *tx_buffer,
                                          size_t tx_length,
                                          uint8_t *rx_buffer,
                                          size_t rx_length,
                                          socfpga_i2c_callback_t callback,
                                          void *context)
{
    if ((!i2c_valid_handle(handle)) || (tx_buffer == NULL) ||
        (tx_length == 0U) || (rx_buffer == NULL) || (rx_length == 0U)) {
        return -EINVAL;
    }
    /* Same repeated-START precondition the synchronous path enforces. */
    if (!handle->config.restart_enable) {
        return -EPROTO;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }
    if (!i2c_bus_available(handle->config.base_address)) {
        return -EBUSY;
    }

    i2c_drain_rx_fifo(handle->config.base_address);
    socfpga_i2c_ll_mask_all_interrupts(handle->config.base_address);
    socfpga_i2c_ll_clear_interrupts(handle->config.base_address);

    handle->callback = callback;
    handle->callback_context = context;
    handle->tx_buffer = tx_buffer;
    handle->tx_length = tx_length;
    handle->tx_index = 0U;
    handle->rx_buffer = rx_buffer;
    handle->rx_length = rx_length;
    handle->rx_index = 0U;
    handle->rx_cmd_index = 0U;
    handle->tx_is_busy = true;
    handle->rx_is_busy = true;
    handle->tx_holds_bus = true;

    i2c_async_prime_write(handle);
    i2c_async_prime_read(handle);
    i2c_async_update_interrupts(handle);
    return 0;
}

void socfpga_i2c_isr(void *param)
{
    socfpga_i2c_handle_t handle = (socfpga_i2c_handle_t)param;
    uint32_t base_address;
    uint32_t intr_status;

    if (!i2c_valid_handle(handle)) {
        return;
    }

    base_address = handle->config.base_address;
    intr_status = socfpga_i2c_ll_get_intr_status(base_address);

    if ((intr_status & SOCFPGA_I2C_ASYNC_ERROR_MASK) != 0U) {
        int32_t status = -EIO;

        if ((intr_status & I2C_INTR_TX_ABRT_MASK) != 0U) {
            handle->last_abort_source =
                socfpga_i2c_ll_get_tx_abort_source(base_address);
            status = socfpga_i2c_ll_abort_to_errno(handle->last_abort_source);
        }

        socfpga_i2c_ll_clear_interrupts(base_address);
        i2c_async_complete(handle, status);
        return;
    }

    if (handle->tx_is_busy) {
        i2c_async_prime_write(handle);
    }
    if (handle->rx_is_busy) {
        i2c_async_prime_read(handle);
    }

    /* STOP_DET is latched, so it is re-sampled after the FIFOs are serviced and
     * cleared on its own register. A blanket IC_CLR_INTR would discard a STOP that
     * arrived during priming and the transfer would never complete.
     */
    intr_status = socfpga_i2c_ll_get_intr_status(base_address);
    if ((intr_status & I2C_INTR_STOP_DET_MASK) != 0U) {
        bool tx_done = (!handle->tx_is_busy) ||
                       (handle->tx_index == handle->tx_length);
        bool rx_done = (!handle->rx_is_busy) ||
                       (handle->rx_index == handle->rx_length);

        (void)socfpga_i2c_ll_read_reg(base_address, I2C_CLR_STOP_DET);

        i2c_async_complete(handle, (tx_done && rx_done) ? 0 : -EIO);
        return;
    }

    if (handle->tx_is_busy || handle->rx_is_busy) {
        i2c_async_update_interrupts(handle);
    }
}

int32_t socfpga_i2c_wait_async_complete(socfpga_i2c_handle_t handle,
                                       uint32_t timeout)
{
    uint64_t hz;
    uint64_t start_us = 0U;
    uint32_t spins = 0U;

    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }

    if (timeout == 0U) {
        timeout = handle->config.timeout;
    }

    hz = clock_hz();
    if (hz != 0ULL) {
        start_us = clock_us();
    } else {
        spins = timeout * SOCFPGA_I2C_FALLBACK_SPINS_PER_US;
    }

    while (handle->tx_is_busy || handle->rx_is_busy) {
        socfpga_i2c_isr(handle);

        if (hz != 0ULL) {
            if ((clock_us() - start_us) >= (uint64_t)timeout) {
                return -ETIMEDOUT;
            }
        } else {
            if (spins == 0U) {
                return -ETIMEDOUT;
            }
            spins--;
        }
    }

    return 0;
}

int32_t socfpga_i2c_get_status(socfpga_i2c_handle_t handle, uint32_t *status)
{
    if ((!i2c_valid_handle(handle)) || (status == NULL)) {
        return -EINVAL;
    }

    *status = socfpga_i2c_ll_get_status(handle->config.base_address);
    return 0;
}

int32_t socfpga_i2c_read_reg(socfpga_i2c_handle_t handle, uint32_t offset,
                             uint32_t *value)
{
    if ((!i2c_valid_handle(handle)) || (value == NULL)) {
        return -EINVAL;
    }

    *value = socfpga_i2c_ll_read_reg(handle->config.base_address, offset);
    return 0;
}

int32_t socfpga_i2c_write_reg(socfpga_i2c_handle_t handle, uint32_t offset,
                              uint32_t value)
{
    if (!i2c_valid_handle(handle)) {
        return -EINVAL;
    }

    socfpga_i2c_ll_write_reg(handle->config.base_address, offset, value);
    return 0;
}
