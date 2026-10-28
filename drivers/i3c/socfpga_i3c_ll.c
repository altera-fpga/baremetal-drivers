/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_i3c_ll.c
 *
 * I3C source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_i3c_ll.h"
#include "socfpga_i3c_reg.h"

static int32_t i3c_wait_status(uint32_t base_address, uint32_t mask,
                               bool set, uint32_t timeout)
{
    while (timeout > 0U) {
        uint32_t status = RD_REG32(base_address + I3C_INTR_STATUS);
        bool is_set = ((status & mask) != 0U);

        if ((status & I3C_INTR_STATUS_TRANSFER_ERR_MASK) != 0U) {
            WR_REG32(base_address + I3C_INTR_STATUS,
                     I3C_INTR_STATUS_TRANSFER_ERR_MASK);
            return -EIO;
        }

        if (is_set == set) {
            return 0;
        }
        timeout--;
    }
    return -ETIMEDOUT;
}

static int32_t i3c_wait_reset_clear(uint32_t base_address, uint32_t mask,
                                    uint32_t timeout)
{
    while (timeout > 0U) {
        if ((RD_REG32(base_address + I3C_RESET_CTRL) & mask) == 0U) {
            return 0;
        }
        timeout--;
    }
    return -ETIMEDOUT;
}

static int32_t i3c_reset_xfer_queues(uint32_t base_address)
{
    WR_REG32(base_address + I3C_RESET_CTRL, I3C_RESET_CTRL_XFER_QUEUES_MASK);
    return i3c_wait_reset_clear(base_address, I3C_RESET_CTRL_XFER_QUEUES_MASK,
                                SOCFPGA_I3C_DEFAULT_TIMEOUT);
}

static void i3c_clear_xfer_status(uint32_t base_address)
{
    WR_REG32(base_address + I3C_INTR_STATUS,
             I3C_INTR_STATUS_RESP_READY_MASK |
             I3C_INTR_STATUS_CMD_READY_MASK |
             I3C_INTR_STATUS_RX_THLD_MASK |
             I3C_INTR_STATUS_TX_THLD_MASK |
             I3C_INTR_STATUS_TRANSFER_ABORT_MASK |
             I3C_INTR_STATUS_TRANSFER_ERR_MASK);
}

int32_t socfpga_i3c_ll_enable(uint32_t base_address, bool enable)
{
    uint32_t reg;

    if (base_address == 0U) {
        return -EINVAL;
    }

    reg = RD_REG32(base_address + I3C_DEVICE_CTRL);
    if (enable) {
        reg |= I3C_DEVICE_CTRL_ENABLE_MASK;
    } else {
        reg &= ~I3C_DEVICE_CTRL_ENABLE_MASK;
    }
    WR_REG32(base_address + I3C_DEVICE_CTRL, reg);
    return 0;
}

int32_t socfpga_i3c_ll_soft_reset(uint32_t base_address, uint32_t reset_mask)
{
    if (base_address == 0U) {
        return -EINVAL;
    }
    WR_REG32(base_address + I3C_RESET_CTRL, reset_mask);
    return i3c_wait_reset_clear(base_address, reset_mask,
                                SOCFPGA_I3C_DEFAULT_TIMEOUT);
}

int32_t socfpga_i3c_ll_enable_interrupts(uint32_t base_address, uint32_t mask,
                                         bool signal)
{
    if (base_address == 0U) {
        return -EINVAL;
    }
    WR_REG32(base_address + I3C_INTR_STATUS_EN, mask);
    WR_REG32(base_address + I3C_INTR_SIGNAL_EN, signal ? mask : 0U);
    return 0;
}

int32_t socfpga_i3c_ll_send_command(uint32_t base_address, uint32_t command,
                                    const uint32_t *data_words,
                                    uint32_t word_count,
                                    uint32_t timeout)
{
    uint32_t index;
    int32_t ret;

    if (base_address == 0U) {
        return -EINVAL;
    }
    if ((word_count != 0U) && (data_words == NULL)) {
        return -EINVAL;
    }

    i3c_clear_xfer_status(base_address);

    for (index = 0U; index < word_count; index++) {
        ret = i3c_wait_status(base_address, I3C_INTR_STATUS_TX_THLD_MASK,
                              true, timeout);
        if (ret != 0) {
            return ret;
        }
        WR_REG32(base_address + I3C_TX_DATA_PORT, data_words[index]);
    }

    ret = i3c_wait_status(base_address, I3C_INTR_STATUS_CMD_READY_MASK,
                          true, timeout);
    if (ret != 0) {
        return ret;
    }

    WR_REG32(base_address + I3C_COMMAND_QUEUE_PORT, command);
    return 0;
}

int32_t socfpga_i3c_ll_read_response(uint32_t base_address, uint32_t *response,
                                     uint32_t timeout)
{
    int32_t ret;

    if ((base_address == 0U) || (response == NULL)) {
        return -EINVAL;
    }

    ret = i3c_wait_status(base_address, I3C_INTR_STATUS_RESP_READY_MASK,
                          true, timeout);
    if (ret != 0) {
        return ret;
    }

    *response = RD_REG32(base_address + I3C_RESPONSE_QUEUE_PORT);
    WR_REG32(base_address + I3C_INTR_STATUS, I3C_INTR_STATUS_RESP_READY_MASK);
    return 0;
}

int32_t socfpga_i3c_ll_read_data(uint32_t base_address, uint32_t *data_words,
                                 uint32_t word_count, uint32_t timeout)
{
    uint32_t index;
    int32_t ret;

    if ((base_address == 0U) || ((word_count != 0U) && (data_words == NULL))) {
        return -EINVAL;
    }

    for (index = 0U; index < word_count; index++) {
        ret = i3c_wait_status(base_address, I3C_INTR_STATUS_RX_THLD_MASK,
                              true, timeout);
        if (ret != 0) {
            return ret;
        }
        data_words[index] = RD_REG32(base_address + I3C_RX_TX_DATA_PORT);
    }
    return 0;
}


static uint32_t i3c_dat_base(uint32_t base_address)
{
    uint32_t ptr = RD_REG32(base_address + I3C_DEVICE_ADDR_TABLE_POINTER);

    if ((ptr & I3C_DEVICE_ADDR_TABLE_POINTER_ADDR_MASK) != 0U) {
        return ptr & I3C_DEVICE_ADDR_TABLE_POINTER_ADDR_MASK;
    }
    return I3C_DEV_ADDR_TABLE_BASE;
}

static uint32_t pack_le_word(const uint8_t *buf, uint32_t len, uint32_t offset)
{
    uint32_t word = 0U;
    uint32_t i;

    for (i = 0U; (i < 4U) && ((offset + i) < len); i++) {
        word |= ((uint32_t)buf[offset + i] << (i * 8U));
    }
    return word;
}

static void unpack_le_word(uint32_t word, uint8_t *buf, uint32_t len, uint32_t offset)
{
    uint32_t i;

    for (i = 0U; (i < 4U) && ((offset + i) < len); i++) {
        buf[offset + i] = (uint8_t)((word >> (i * 8U)) & 0xFFU);
    }
}

int32_t socfpga_i3c_ll_program_dat_entry(uint32_t base_address,
                                         uint32_t device_index,
                                         uint8_t address,
                                         bool legacy_i2c)
{
    uint32_t dat_base;
    uint32_t entry;

    if ((base_address == 0U) || (device_index >= 16U) || (address > 0x7FU)) {
        return -EINVAL;
    }

    dat_base = i3c_dat_base(base_address);
    entry = legacy_i2c ?
            (I3C_DAT_LEGACY_I2C_DEV_MASK | I3C_DAT_STATIC_ADDR(address)) :
            I3C_DAT_DYNAMIC_ADDR(address);

    WR_REG32(base_address + dat_base + (device_index * 4U), entry);
    return 0;
}

int32_t socfpga_i3c_ll_private_transfer(uint32_t base_address,
                                        uint32_t device_index,
                                        bool read,
                                        const uint8_t *tx_buffer,
                                        uint32_t tx_length,
                                        uint8_t *rx_buffer,
                                        uint32_t rx_length,
                                        uint32_t timeout,
                                        uint32_t *response)
{
    uint32_t len = read ? rx_length : tx_length;
    uint32_t cmd_hi;
    uint32_t cmd_lo;
    uint32_t index;
    uint32_t resp = 0U;

    if ((base_address == 0U) || (device_index >= 16U) || (len == 0U)) {
        return -EINVAL;
    }
    if ((!read) && (tx_buffer == NULL)) {
        return -EINVAL;
    }
    if (read && (rx_buffer == NULL)) {
        return -EINVAL;
    }

    if (i3c_reset_xfer_queues(base_address) != 0) {
        return -ETIMEDOUT;
    }
    i3c_clear_xfer_status(base_address);

    if (!read) {
        for (index = 0U; index < tx_length; index += 4U) {
            int32_t ret = i3c_wait_status(base_address,
                                          I3C_INTR_STATUS_TX_THLD_MASK,
                                          true, timeout);
            if (ret != 0) {
                (void)i3c_reset_xfer_queues(base_address);
                return ret;
            }
            WR_REG32(base_address + I3C_RX_TX_DATA_PORT,
                     pack_le_word(tx_buffer, tx_length, index));
        }
    }

    {
        int32_t ret = i3c_wait_status(base_address, I3C_INTR_STATUS_CMD_READY_MASK,
                                      true, timeout);
        if (ret != 0) {
            (void)i3c_reset_xfer_queues(base_address);
            return ret;
        }
    }

    cmd_hi = I3C_COMMAND_PORT_ARG_LEN(len) | I3C_COMMAND_PORT_TRANSFER_ARG;
    cmd_lo = I3C_COMMAND_PORT_TID(0U) |
             I3C_COMMAND_PORT_DEV_INDEX(device_index) |
             I3C_COMMAND_PORT_ROC_MASK |
             I3C_COMMAND_PORT_TOC_MASK;
    if (read) {
        cmd_lo |= I3C_COMMAND_PORT_READ_MASK;
    }

    /* DesignWare I3C command queue takes high word first, then low word. */
    WR_REG32(base_address + I3C_COMMAND_QUEUE_PORT, cmd_hi);
    WR_REG32(base_address + I3C_COMMAND_QUEUE_PORT, cmd_lo);

    {
        int32_t ret = i3c_wait_status(base_address, I3C_INTR_STATUS_RESP_READY_MASK,
                                      true, timeout);
        if (ret != 0) {
            (void)i3c_reset_xfer_queues(base_address);
            return ret;
        }
    }

    resp = RD_REG32(base_address + I3C_RESPONSE_QUEUE_PORT);
    WR_REG32(base_address + I3C_INTR_STATUS, I3C_INTR_STATUS_RESP_READY_MASK);
    if (response != NULL) {
        *response = resp;
    }

    if (((resp & I3C_RESP_ERR_STATUS_MASK) >> I3C_RESP_ERR_STATUS_POS) != 0U) {
        (void)i3c_reset_xfer_queues(base_address);
        return -EIO;
    }

    if (read) {
        for (index = 0U; index < rx_length; index += 4U) {
            uint32_t word;
            int32_t ret = i3c_wait_status(base_address,
                                          I3C_INTR_STATUS_RX_THLD_MASK,
                                          true, timeout);
            if (ret != 0) {
                (void)i3c_reset_xfer_queues(base_address);
                return ret;
            }
            word = RD_REG32(base_address + I3C_RX_TX_DATA_PORT);
            unpack_le_word(word, rx_buffer, rx_length, index);
        }
    }

    i3c_clear_xfer_status(base_address);
    return 0;
}

uint32_t socfpga_i3c_ll_get_status(uint32_t base_address)
{
    return RD_REG32(base_address + I3C_INTR_STATUS);
}

uint32_t socfpga_i3c_ll_get_hw_capability(uint32_t base_address)
{
    return RD_REG32(base_address + I3C_HW_CAPABILITY);
}

uint32_t socfpga_i3c_ll_read_reg(uint32_t base_address, uint32_t offset)
{
    return RD_REG32(base_address + offset);
}

void socfpga_i3c_ll_write_reg(uint32_t base_address, uint32_t offset,
                              uint32_t value)
{
    WR_REG32(base_address + offset, value);
}
