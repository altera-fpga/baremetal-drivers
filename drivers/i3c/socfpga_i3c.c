/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_i3c.c
 *
 * I3C source implementation for the SoCFPGA bare-metal software stack.
 */

#include <string.h>

#include "socfpga_i3c.h"
#include "socfpga_i3c_ll.h"
#include "socfpga_i3c_reg.h"

#define SOCFPGA_I3C_MAX_HANDLES 2U

struct socfpga_i3c_descriptor {
    bool is_open;
    bool tx_is_busy;
    bool rx_is_busy;
    socfpga_i3c_config_t config;
    socfpga_i3c_callback_t callback;
    void *callback_context;
};

static struct socfpga_i3c_descriptor i3c_handles[SOCFPGA_I3C_MAX_HANDLES];

static bool i3c_valid_handle(socfpga_i3c_handle_t handle)
{
    return ((handle != NULL) && (handle->is_open));
}

static struct socfpga_i3c_descriptor *i3c_alloc_handle(uint32_t base_address)
{
    uint32_t index;
    struct socfpga_i3c_descriptor *free_handle = NULL;

    for (index = 0U; index < SOCFPGA_I3C_MAX_HANDLES; index++) {
        if ((i3c_handles[index].is_open) &&
            (i3c_handles[index].config.base_address == base_address)) {
            return NULL;
        }
        if ((!i3c_handles[index].is_open) && (free_handle == NULL)) {
            free_handle = &i3c_handles[index];
        }
    }
    return free_handle;
}

uint32_t socfpga_i3c_build_command(uint32_t msg_type, uint32_t transaction_id,
                                   uint32_t command_code, uint32_t device_index,
                                   bool write, bool response_on_completion)
{
    uint32_t command = 0U;

    command |= ((msg_type << I3C_CMD_XFER_ATTR_POS) & I3C_CMD_XFER_ATTR_MASK);
    command |= ((transaction_id << I3C_CMD_TRANSACTION_ID_POS) & I3C_CMD_TRANSACTION_ID_MASK);
    command |= ((command_code << I3C_CMD_COMMAND_CODE_POS) & I3C_CMD_COMMAND_CODE_MASK);
    command |= ((device_index << I3C_CMD_DEVICE_INDEX_POS) & I3C_CMD_DEVICE_INDEX_MASK);

    if (command_code != 0U) {
        command |= I3C_CMD_COMMAND_PRESENT_MASK;
    }
    if (write) {
        command |= I3C_CMD_DIR_WRITE_MASK;
    }
    if (response_on_completion) {
        command |= I3C_CMD_RESP_ON_COMPLETION_MASK;
    }

    return command;
}

int32_t socfpga_i3c_init(const socfpga_i3c_config_t *config,
                         socfpga_i3c_handle_t *handle)
{
    struct socfpga_i3c_descriptor *desc;
    uint32_t timeout;
    uint32_t ctrl;
    int32_t ret;

    if ((config == NULL) || (handle == NULL) || (config->base_address == 0U)) {
        return -EINVAL;
    }

    desc = i3c_alloc_handle(config->base_address);
    if (desc == NULL) {
        return -EBUSY;
    }

    timeout = (config->timeout == 0U) ? SOCFPGA_I3C_DEFAULT_TIMEOUT : config->timeout;

    if (config->reset_id != SOCFPGA_I3C_RESET_NONE) {
        ret = rstmgr_deassert_reset((reset_periphrl_t)config->reset_id);
        if (ret != 0) {
            return ret;
        }
    }

    ret = socfpga_i3c_ll_enable(config->base_address, false);
    if (ret != 0) {
        return ret;
    }

    ret = socfpga_i3c_ll_soft_reset(config->base_address, I3C_RESET_CTRL_SOFT_RST_MASK);
    if (ret != 0) {
        return ret;
    }

    ctrl = 0U;
    if (config->enable_i2c_compatibility) {
        ctrl |= I3C_DEVICE_CTRL_I2C_PRESENT_MASK;
    }
    if (config->enable_hot_join) {
        ctrl |= I3C_DEVICE_CTRL_HOT_JOIN_MASK;
    }
    socfpga_i3c_ll_write_reg(config->base_address, I3C_DEVICE_CTRL, ctrl);

    ret = socfpga_i3c_ll_enable_interrupts(config->base_address,
                                           I3C_INTR_STATUS_CMD_READY_MASK |
                                           I3C_INTR_STATUS_RESP_READY_MASK |
                                           I3C_INTR_STATUS_TX_THLD_MASK |
                                           I3C_INTR_STATUS_RX_THLD_MASK |
                                           I3C_INTR_STATUS_TRANSFER_ABORT_MASK |
                                           I3C_INTR_STATUS_TRANSFER_ERR_MASK,
                                           false);
    if (ret != 0) {
        return ret;
    }

    ret = socfpga_i3c_ll_enable(config->base_address, true);
    if (ret != 0) {
        return ret;
    }

    (void)timeout;
    (void)memset(desc, 0, sizeof(*desc));
    desc->is_open = true;
    desc->config = *config;
    desc->config.timeout = timeout;
    *handle = desc;
    return 0;
}

int32_t socfpga_i3c_deinit(socfpga_i3c_handle_t handle)
{
    int32_t ret;

    if (!i3c_valid_handle(handle)) {
        return -EINVAL;
    }
    ret = socfpga_i3c_ll_enable(handle->config.base_address, false);
    if (ret != 0) {
        return ret;
    }
    return socfpga_i3c_close(handle);
}

int32_t socfpga_i3c_close(socfpga_i3c_handle_t handle)
{
    if (!i3c_valid_handle(handle)) {
        return -EINVAL;
    }
    (void)memset(handle, 0, sizeof(*handle));
    return 0;
}

int32_t socfpga_i3c_transfer_sync(socfpga_i3c_handle_t handle,
                                  socfpga_i3c_transfer_t *transfer)
{
    int32_t ret;

    if ((!i3c_valid_handle(handle)) || (transfer == NULL)) {
        return -EINVAL;
    }
    if (handle->tx_is_busy || handle->rx_is_busy) {
        return -EBUSY;
    }
    if ((transfer->tx_word_count > SOCFPGA_I3C_MAX_DATA_WORDS) ||
        (transfer->rx_word_count > SOCFPGA_I3C_MAX_DATA_WORDS)) {
        return -EINVAL;
    }

    handle->tx_is_busy = true;
    ret = socfpga_i3c_ll_send_command(handle->config.base_address,
                                      transfer->command,
                                      transfer->tx_words,
                                      transfer->tx_word_count,
                                      handle->config.timeout);
    handle->tx_is_busy = false;
    if (ret != 0) {
        return ret;
    }

    ret = socfpga_i3c_ll_read_response(handle->config.base_address,
                                       &transfer->response,
                                       handle->config.timeout);
    if (ret != 0) {
        return ret;
    }

    if (transfer->rx_word_count != 0U) {
        handle->rx_is_busy = true;
        ret = socfpga_i3c_ll_read_data(handle->config.base_address,
                                       transfer->rx_words,
                                       transfer->rx_word_count,
                                       handle->config.timeout);
        handle->rx_is_busy = false;
    }

    if (((transfer->response & I3C_RESP_ERR_STATUS_MASK) >>
         I3C_RESP_ERR_STATUS_POS) != 0U) {
        return -EIO;
    }

    return ret;
}

int32_t socfpga_i3c_write_sync(socfpga_i3c_handle_t handle,
                               const uint32_t *data_words,
                               uint32_t word_count,
                               uint32_t command)
{
    socfpga_i3c_transfer_t transfer;

    transfer.command = command;
    transfer.tx_words = data_words;
    transfer.tx_word_count = word_count;
    transfer.rx_words = NULL;
    transfer.rx_word_count = 0U;
    transfer.response = 0U;
    return socfpga_i3c_transfer_sync(handle, &transfer);
}

int32_t socfpga_i3c_read_sync(socfpga_i3c_handle_t handle,
                              uint32_t *data_words,
                              uint32_t word_count,
                              uint32_t command)
{
    socfpga_i3c_transfer_t transfer;

    transfer.command = command;
    transfer.tx_words = NULL;
    transfer.tx_word_count = 0U;
    transfer.rx_words = data_words;
    transfer.rx_word_count = word_count;
    transfer.response = 0U;
    return socfpga_i3c_transfer_sync(handle, &transfer);
}


static int32_t i3c_simple_private_transfer(socfpga_i3c_handle_t handle,
                                           uint8_t address,
                                           bool legacy_i2c,
                                           bool read,
                                           const uint8_t *tx_buffer,
                                           uint32_t tx_length,
                                           uint8_t *rx_buffer,
                                           uint32_t rx_length,
                                           uint32_t *response)
{
    int32_t ret;
    uint32_t length = read ? rx_length : tx_length;
    const uint32_t device_index = 0U;

    if ((!i3c_valid_handle(handle)) || (address > 0x7FU) || (length == 0U) ||
        (length > (SOCFPGA_I3C_MAX_DATA_WORDS * 4U))) {
        return -EINVAL;
    }

    ret = socfpga_i3c_ll_program_dat_entry(handle->config.base_address,
                                           device_index,
                                           address,
                                           legacy_i2c);
    if (ret != 0) {
        return ret;
    }

    return socfpga_i3c_ll_private_transfer(handle->config.base_address,
                                           device_index,
                                           read,
                                           tx_buffer,
                                           tx_length,
                                           rx_buffer,
                                           rx_length,
                                           handle->config.timeout,
                                           response);
}

int32_t socfpga_i3c_i2c_legacy_read(socfpga_i3c_handle_t handle,
                                    uint8_t i2c_address,
                                    uint8_t *buffer,
                                    uint32_t length,
                                    uint32_t *response)
{
    return i3c_simple_private_transfer(handle, i2c_address, true, true,
                                       NULL, 0U, buffer, length, response);
}

int32_t socfpga_i3c_i2c_legacy_write(socfpga_i3c_handle_t handle,
                                     uint8_t i2c_address,
                                     const uint8_t *buffer,
                                     uint32_t length,
                                     uint32_t *response)
{
    return i3c_simple_private_transfer(handle, i2c_address, true, false,
                                       buffer, length, NULL, 0U, response);
}

int32_t socfpga_i3c_private_read(socfpga_i3c_handle_t handle,
                                 uint8_t dynamic_address,
                                 uint8_t *buffer,
                                 uint32_t length,
                                 uint32_t *response)
{
    return i3c_simple_private_transfer(handle, dynamic_address, false, true,
                                       NULL, 0U, buffer, length, response);
}

int32_t socfpga_i3c_private_write(socfpga_i3c_handle_t handle,
                                  uint8_t dynamic_address,
                                  const uint8_t *buffer,
                                  uint32_t length,
                                  uint32_t *response)
{
    return i3c_simple_private_transfer(handle, dynamic_address, false, false,
                                       buffer, length, NULL, 0U, response);
}

int32_t socfpga_i3c_transfer_async(socfpga_i3c_handle_t handle,
                                   socfpga_i3c_transfer_t *transfer,
                                   socfpga_i3c_callback_t callback,
                                   void *context)
{
    int32_t ret;

    if ((!i3c_valid_handle(handle)) || (transfer == NULL)) {
        return -EINVAL;
    }

    handle->callback = callback;
    handle->callback_context = context;
    ret = socfpga_i3c_transfer_sync(handle, transfer);
    if (callback != NULL) {
        callback(handle, ret, context);
    }
    return ret;
}

void socfpga_i3c_isr(void *param)
{
    socfpga_i3c_handle_t handle = (socfpga_i3c_handle_t)param;

    if (!i3c_valid_handle(handle)) {
        return;
    }
    if (handle->callback != NULL) {
        handle->callback(handle, 0, handle->callback_context);
    }
}

int32_t socfpga_i3c_get_status(socfpga_i3c_handle_t handle, uint32_t *status)
{
    if ((!i3c_valid_handle(handle)) || (status == NULL)) {
        return -EINVAL;
    }
    *status = socfpga_i3c_ll_get_status(handle->config.base_address);
    return 0;
}

int32_t socfpga_i3c_get_hw_capability(socfpga_i3c_handle_t handle,
                                      uint32_t *capability)
{
    if ((!i3c_valid_handle(handle)) || (capability == NULL)) {
        return -EINVAL;
    }
    *capability = socfpga_i3c_ll_get_hw_capability(handle->config.base_address);
    return 0;
}

int32_t socfpga_i3c_read_reg(socfpga_i3c_handle_t handle, uint32_t offset,
                             uint32_t *value)
{
    if ((!i3c_valid_handle(handle)) || (value == NULL)) {
        return -EINVAL;
    }
    *value = socfpga_i3c_ll_read_reg(handle->config.base_address, offset);
    return 0;
}

int32_t socfpga_i3c_write_reg(socfpga_i3c_handle_t handle, uint32_t offset,
                              uint32_t value)
{
    if (!i3c_valid_handle(handle)) {
        return -EINVAL;
    }
    socfpga_i3c_ll_write_reg(handle->config.base_address, offset, value);
    return 0;
}
