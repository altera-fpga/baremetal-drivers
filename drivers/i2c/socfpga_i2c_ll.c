/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_i2c_ll.c
 *
 * I2C source implementation for the SoCFPGA bare-metal software stack.
 */

#include "lib_time.h"
#include "socfpga_i2c_ll.h"
#include "socfpga_i2c_reg.h"

/* Timing minimums in nanoseconds from the I2C-bus specification, plus the bus
 * rise and fall times assumed for a board without measured values.
 */
#define I2C_SS_MIN_HIGH_NS  4000U
#define I2C_SS_MIN_LOW_NS   4700U
#define I2C_FS_MIN_HIGH_NS  600U
#define I2C_FS_MIN_LOW_NS   1300U
#define I2C_FP_MIN_HIGH_NS  260U
#define I2C_FP_MIN_LOW_NS   500U
#define I2C_SS_RISE_NS      1000U
#define I2C_SS_FALL_NS      300U
#define I2C_FS_RISE_NS      300U
#define I2C_FS_FALL_NS      300U
#define I2C_FP_RISE_NS      260U
#define I2C_FP_FALL_NS      500U
#define I2C_SDA_HOLD_NS     300U

/* The controller adds three ic_clk cycles to the programmed high count, the same
 * offset the U-Boot and Linux DesignWare drivers assume.
 */
#define I2C_HCNT_OVERHEAD   3U

/* The spin fallback only guards host unit builds and pre-PLL bring-up, where
 * CNTFRQ_EL0 reads zero and clock_us() would never advance.
 */
struct i2c_deadline {
    uint64_t hz;
    uint64_t start_us;
    uint32_t timeout_us;
    uint32_t spins;
};

static void i2c_deadline_start(struct i2c_deadline *deadline, uint32_t timeout)
{
    deadline->hz = clock_hz();
    deadline->timeout_us = timeout;
    deadline->start_us = (deadline->hz != 0ULL) ? clock_us() : 0ULL;
    deadline->spins = (deadline->hz != 0ULL)
                      ? 0U : (timeout * SOCFPGA_I2C_FALLBACK_SPINS_PER_US);
}

static bool i2c_deadline_expired(struct i2c_deadline *deadline)
{
    if (deadline->hz != 0ULL) {
        return ((clock_us() - deadline->start_us) >=
                (uint64_t)deadline->timeout_us);
    }

    if (deadline->spins == 0U) {
        return true;
    }

    deadline->spins--;
    __asm__ volatile("nop");
    return false;
}

static int32_t i2c_wait_mask(uint32_t base_address, uint32_t offset,
                             uint32_t mask, bool set, uint32_t timeout)
{
    struct i2c_deadline deadline;

    i2c_deadline_start(&deadline, timeout);

    for (;;) {
        uint32_t value = RD_REG32(base_address + offset);
        bool is_set = ((value & mask) != 0U);

        if (is_set == set) {
            return 0;
        }
        if (i2c_deadline_expired(&deadline)) {
            return -ETIMEDOUT;
        }
    }
}



/* Maps IC_TX_ABRT_SOURCE onto an errno the caller can act on. */
int32_t socfpga_i2c_ll_abort_to_errno(uint32_t abort_source)
{
    /* Drop the flushed-byte count so it can never be read as a cause. */
    abort_source &= I2C_TX_ABRT_CAUSE_MASK;

    if ((abort_source & I2C_TX_ABRT_ADDR_NOACK_MASK) != 0U) {
        return -ENXIO;
    }
    if ((abort_source & I2C_TX_ABRT_ARB_LOST_MASK) != 0U) {
        return -EAGAIN;
    }
    if ((abort_source & I2C_TX_ABRT_TXDATA_NOACK_MASK) != 0U) {
        return -EIO;
    }
    if ((abort_source & (I2C_TX_ABRT_MASTER_DIS_MASK |
                         I2C_TX_ABRT_SBYTE_NORSTRT_MASK |
                         I2C_TX_ABRT_HS_NORSTRT_MASK |
                         I2C_TX_ABRT_10B_RD_NORSTRT_MASK)) != 0U) {
        return -EPROTO;
    }
    /* -ENXIO is reserved for a genuine address NACK so callers can rely on it
     * to mean "nothing at this address".
     */
    return -EIO;
}

/* The TX FIFO stays flushed and held until IC_CLR_TX_ABRT is read. */
static int32_t i2c_get_abort(uint32_t base_address, uint32_t *abort_source)
{
    uint32_t raw = RD_REG32(base_address + I2C_RAW_INTR_STAT);
    uint32_t source;

    if ((raw & I2C_INTR_TX_ABRT_MASK) == 0U) {
        return 0;
    }

    source = RD_REG32(base_address + I2C_TX_ABRT_SOURCE);
    if (abort_source != NULL) {
        *abort_source = source;
    }
    (void)RD_REG32(base_address + I2C_CLR_TX_ABRT);

    return socfpga_i2c_ll_abort_to_errno(source);
}

static int32_t i2c_wait_mask_or_abort(uint32_t base_address, uint32_t offset,
                                      uint32_t mask, bool set, uint32_t timeout,
                                      uint32_t *abort_source)
{
    struct i2c_deadline deadline;

    i2c_deadline_start(&deadline, timeout);

    for (;;) {
        uint32_t value = RD_REG32(base_address + offset);
        bool is_set = ((value & mask) != 0U);
        int32_t abort_rc = i2c_get_abort(base_address, abort_source);

        if (abort_rc != 0) {
            return abort_rc;
        }
        if (is_set == set) {
            return 0;
        }
        if (i2c_deadline_expired(&deadline)) {
            return -ETIMEDOUT;
        }
    }
}

static int32_t i2c_wait_bus_idle(uint32_t base_address, uint32_t timeout,
                                 uint32_t *abort_source)
{
    struct i2c_deadline deadline;

    i2c_deadline_start(&deadline, timeout);

    for (;;) {
        uint32_t status = RD_REG32(base_address + I2C_STATUS);
        int32_t abort_rc = i2c_get_abort(base_address, abort_source);

        if (abort_rc != 0) {
            return abort_rc;
        }

        if (((status & I2C_STATUS_MST_ACTIVITY_MASK) == 0U) &&
            ((status & I2C_STATUS_TFE_MASK) != 0U)) {
            return 0;
        }

        if (i2c_deadline_expired(&deadline)) {
            return -ETIMEDOUT;
        }
    }
}

static void i2c_flush_rxfifo(uint32_t base_address)
{
    while ((RD_REG32(base_address + I2C_STATUS) & I2C_STATUS_RFNE_MASK) != 0U) {
        (void)RD_REG32(base_address + I2C_DATA_CMD);
    }
}

static int32_t i2c_finish_transfer(uint32_t base_address, uint32_t timeout,
                                   uint32_t *abort_source)
{
    struct i2c_deadline deadline;

    i2c_deadline_start(&deadline, timeout);

    for (;;) {
        uint32_t raw = RD_REG32(base_address + I2C_RAW_INTR_STAT);
        uint32_t status = RD_REG32(base_address + I2C_STATUS);
        int32_t ret = i2c_get_abort(base_address, abort_source);

        if (ret != 0) {
            i2c_flush_rxfifo(base_address);
            return ret;
        }

        if ((raw & I2C_INTR_STOP_DET_MASK) != 0U) {
            (void)RD_REG32(base_address + I2C_CLR_STOP_DET);
            i2c_flush_rxfifo(base_address);
            return i2c_wait_bus_idle(base_address, timeout, abort_source);
        }

        if (((status & I2C_STATUS_MST_ACTIVITY_MASK) == 0U) &&
            ((status & I2C_STATUS_TFE_MASK) != 0U)) {
            i2c_flush_rxfifo(base_address);
            return 0;
        }

        if (i2c_deadline_expired(&deadline)) {
            i2c_flush_rxfifo(base_address);
            return -ETIMEDOUT;
        }
    }
}

static uint32_t i2c_ns_to_counts(uint32_t ic_clk_hz, uint32_t period_ns)
{
    uint64_t cycles = ((uint64_t)ic_clk_hz * (uint64_t)period_ns) + 999999999ULL;

    return (uint32_t)(cycles / 1000000000ULL);
}

int32_t socfpga_i2c_ll_probe_controller(uint32_t base_address,
                                        uint32_t *version)
{
    if (base_address == 0U) {
        return -EINVAL;
    }

    if (RD_REG32(base_address + I2C_COMP_TYPE) != I2C_COMP_TYPE_VALUE) {
        return -ENODEV;
    }

    if (version != NULL) {
        *version = RD_REG32(base_address + I2C_COMP_VERSION);
    }

    return 0;
}

int32_t socfpga_i2c_ll_get_fifo_depth(uint32_t base_address,
                                      uint32_t *tx_depth, uint32_t *rx_depth)
{
    uint32_t param;

    if (base_address == 0U) {
        return -EINVAL;
    }

    param = RD_REG32(base_address + I2C_COMP_PARAM_1);

    /* The synthesis parameter stores depth minus one. */
    if (tx_depth != NULL) {
        *tx_depth = ((param & I2C_COMP_PARAM_1_TX_DEPTH_MASK) >>
                     I2C_COMP_PARAM_1_TX_DEPTH_POS) + 1U;
    }
    if (rx_depth != NULL) {
        *rx_depth = ((param & I2C_COMP_PARAM_1_RX_DEPTH_MASK) >>
                     I2C_COMP_PARAM_1_RX_DEPTH_POS) + 1U;
    }

    return 0;
}

int32_t socfpga_i2c_ll_enable(uint32_t base_address, bool enable,
                              uint32_t timeout)
{
    uint32_t value = enable ? I2C_ENABLE_ENABLE_MASK : 0U;

    if (base_address == 0U) {
        return -EINVAL;
    }

    WR_REG32(base_address + I2C_ENABLE, value);
    return i2c_wait_mask(base_address, I2C_ENABLE_STATUS,
                         I2C_ENABLE_STATUS_IC_EN_MASK, enable, timeout);
}

/* Fast-plus shares the fast-mode encoding; encoding 3 is high speed and must not
 * be reached from a fast-plus request.
 */
static uint32_t i2c_con_speed_field(uint32_t speed_mode)
{
    return (speed_mode == SOCFPGA_I2C_SPEED_STANDARD) ? I2C_CON_SPEED_SS
                                                      : I2C_CON_SPEED_FS;
}

static uint32_t i2c_hcnt_offset(uint32_t speed_mode)
{
    return (speed_mode == SOCFPGA_I2C_SPEED_STANDARD) ? I2C_SS_SCL_HCNT
                                                      : I2C_FS_SCL_HCNT;
}

static uint32_t i2c_lcnt_offset(uint32_t speed_mode)
{
    return (speed_mode == SOCFPGA_I2C_SPEED_STANDARD) ? I2C_SS_SCL_LCNT
                                                      : I2C_FS_SCL_LCNT;
}

int32_t socfpga_i2c_ll_configure_master(uint32_t base_address,
                                        uint16_t target_address,
                                        uint32_t speed_mode,
                                        bool ten_bit_address,
                                        bool restart_enable)
{
    uint32_t con;
    uint32_t tar;

    if ((base_address == 0U) ||
        (speed_mode < SOCFPGA_I2C_SPEED_STANDARD) ||
        (speed_mode > SOCFPGA_I2C_SPEED_FASTPLUS) ||
        (target_address > 0x03FFU)) {
        return -EINVAL;
    }
    if ((!ten_bit_address) && (target_address > 0x007FU)) {
        return -EINVAL;
    }

    con = I2C_CON_MASTER_MODE_MASK | I2C_CON_SLAVE_DISABLE_MASK;
    con |= ((i2c_con_speed_field(speed_mode) << I2C_CON_SPEED_POS) &
            I2C_CON_SPEED_MASK);
    if (ten_bit_address) {
        con |= I2C_CON_10BITADDR_MASTER_MASK;
    }
    if (restart_enable) {
        con |= I2C_CON_RESTART_EN_MASK;
    }

    tar = ((uint32_t)target_address << I2C_TAR_ADDR_POS) & I2C_TAR_ADDR_MASK;

    WR_REG32(base_address + I2C_CON, con);
    WR_REG32(base_address + I2C_TAR, tar);
    return 0;
}

int32_t socfpga_i2c_ll_set_scl_count(uint32_t base_address,
                                     uint32_t speed_mode,
                                     uint16_t high_count,
                                     uint16_t low_count)
{
    if ((base_address == 0U) || (high_count == 0U) || (low_count == 0U)) {
        return -EINVAL;
    }

    WR_REG32(base_address + i2c_hcnt_offset(speed_mode), (uint32_t)high_count);
    WR_REG32(base_address + i2c_lcnt_offset(speed_mode), (uint32_t)low_count);

    return 0;
}

int32_t socfpga_i2c_ll_set_timing(uint32_t base_address, uint32_t ic_clk_hz,
                                  uint32_t bus_hz, uint32_t *speed_mode)
{
    uint32_t mode;
    uint32_t min_high_ns;
    uint32_t min_low_ns;
    uint32_t rise_ns;
    uint32_t fall_ns;
    uint32_t period_cnt;
    uint32_t rise_cnt;
    uint32_t fall_cnt;
    uint32_t hcnt;
    uint32_t lcnt;
    uint32_t total;
    uint32_t sda_hold;

    if ((base_address == 0U) || (ic_clk_hz == 0U) || (bus_hz == 0U)) {
        return -EINVAL;
    }

    if (bus_hz <= 100000U) {
        mode = SOCFPGA_I2C_SPEED_STANDARD;
        min_high_ns = I2C_SS_MIN_HIGH_NS;
        min_low_ns = I2C_SS_MIN_LOW_NS;
        rise_ns = I2C_SS_RISE_NS;
        fall_ns = I2C_SS_FALL_NS;
    } else if (bus_hz <= 400000U) {
        mode = SOCFPGA_I2C_SPEED_FAST;
        min_high_ns = I2C_FS_MIN_HIGH_NS;
        min_low_ns = I2C_FS_MIN_LOW_NS;
        rise_ns = I2C_FS_RISE_NS;
        fall_ns = I2C_FS_FALL_NS;
    } else {
        mode = SOCFPGA_I2C_SPEED_FASTPLUS;
        min_high_ns = I2C_FP_MIN_HIGH_NS;
        min_low_ns = I2C_FP_MIN_LOW_NS;
        rise_ns = I2C_FP_RISE_NS;
        fall_ns = I2C_FP_FALL_NS;
    }

    period_cnt = ic_clk_hz / bus_hz;
    rise_cnt = i2c_ns_to_counts(ic_clk_hz, rise_ns);
    fall_cnt = i2c_ns_to_counts(ic_clk_hz, fall_ns);
    hcnt = i2c_ns_to_counts(ic_clk_hz, min_high_ns);
    lcnt = i2c_ns_to_counts(ic_clk_hz, min_low_ns);

    if ((hcnt <= (fall_cnt + I2C_HCNT_OVERHEAD)) ||
        ((lcnt + fall_cnt) <= (rise_cnt + 1U))) {
        return -ERANGE;
    }

    hcnt -= (fall_cnt + I2C_HCNT_OVERHEAD);
    lcnt += fall_cnt;
    lcnt -= (rise_cnt + 1U);

    /* Stretch both halves to the requested period, biasing the remainder low. */
    total = hcnt + lcnt + I2C_HCNT_OVERHEAD + rise_cnt + 1U;
    if (total < period_cnt) {
        uint32_t slack = (period_cnt - total) / 2U;

        hcnt += slack;
        lcnt += slack;
        total = hcnt + lcnt + I2C_HCNT_OVERHEAD + rise_cnt + 1U;
        lcnt += (period_cnt - total);
    }

    if ((hcnt > 0xFFFFU) || (lcnt > 0xFFFFU)) {
        return -ERANGE;
    }

    WR_REG32(base_address + i2c_hcnt_offset(mode), hcnt);
    WR_REG32(base_address + i2c_lcnt_offset(mode), lcnt);

    sda_hold = i2c_ns_to_counts(ic_clk_hz, I2C_SDA_HOLD_NS);
    if (sda_hold != 0U) {
        WR_REG32(base_address + I2C_SDA_HOLD, sda_hold);
    }

    if (speed_mode != NULL) {
        *speed_mode = mode;
    }

    return 0;
}

int32_t socfpga_i2c_ll_set_target_address(uint32_t base_address,
                                         uint16_t target_address,
                                         bool ten_bit_address,
                                         uint32_t timeout)
{
    uint32_t con;
    int32_t ret;

    if ((base_address == 0U) || (target_address > 0x03FFU)) {
        return -EINVAL;
    }
    if ((!ten_bit_address) && (target_address > 0x007FU)) {
        return -EINVAL;
    }

    ret = socfpga_i2c_ll_enable(base_address, false, timeout);
    if (ret != 0) {
        return ret;
    }

    con = RD_REG32(base_address + I2C_CON);
    if (ten_bit_address) {
        con |= I2C_CON_10BITADDR_MASTER_MASK;
    } else {
        con &= ~I2C_CON_10BITADDR_MASTER_MASK;
    }
    WR_REG32(base_address + I2C_CON, con);
    WR_REG32(base_address + I2C_TAR,
             ((uint32_t)target_address << I2C_TAR_ADDR_POS) & I2C_TAR_ADDR_MASK);

    return socfpga_i2c_ll_enable(base_address, true, timeout);
}

int32_t socfpga_i2c_ll_probe_address(uint32_t base_address, uint32_t timeout,
                                     uint32_t *abort_source)
{
    uint8_t discard = 0U;

    if (base_address == 0U) {
        return -EINVAL;
    }

    return socfpga_i2c_ll_read_sync(base_address, &discard, 1U, timeout,
                                    abort_source);
}

int32_t socfpga_i2c_ll_recover_bus(uint32_t base_address, uint32_t timeout)
{
    uint32_t enable;
    int32_t ret;

    if (base_address == 0U) {
        return -EINVAL;
    }

    enable = RD_REG32(base_address + I2C_ENABLE);
    if ((enable & I2C_ENABLE_ENABLE_MASK) != 0U) {
        WR_REG32(base_address + I2C_ENABLE,
                 enable | I2C_ENABLE_ABORT_MASK);
        (void)i2c_wait_mask(base_address, I2C_ENABLE, I2C_ENABLE_ABORT_MASK,
                            false, timeout);
    }

    ret = socfpga_i2c_ll_enable(base_address, false, timeout);
    if (ret != 0) {
        return ret;
    }

    i2c_flush_rxfifo(base_address);
    (void)RD_REG32(base_address + I2C_CLR_INTR);

    ret = socfpga_i2c_ll_enable(base_address, true, timeout);
    if (ret != 0) {
        return ret;
    }

    return i2c_wait_bus_idle(base_address, timeout, NULL);
}

int32_t socfpga_i2c_ll_write_sync(uint32_t base_address, const uint8_t *buffer,
                                  size_t length, uint32_t timeout,
                                  uint32_t *abort_source)
{
    size_t index;
    int32_t ret;

    if ((base_address == 0U) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }

    ret = i2c_wait_bus_idle(base_address, timeout, abort_source);
    if (ret != 0) {
        return ret;
    }

    for (index = 0U; index < length; index++) {
        uint32_t cmd = (uint32_t)buffer[index] & I2C_DATA_CMD_DAT_MASK;

        if (index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }
        if ((index + 1U) == length) {
            cmd |= I2C_DATA_CMD_STOP_MASK;
        }

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_TFNF_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }

        WR_REG32(base_address + I2C_DATA_CMD, cmd);
    }

    ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                 I2C_STATUS_TFE_MASK, true, timeout,
                                 abort_source);
    if (ret != 0) {
        return ret;
    }

    return i2c_finish_transfer(base_address, timeout, abort_source);
}

int32_t socfpga_i2c_ll_read_sync(uint32_t base_address, uint8_t *buffer,
                                 size_t length, uint32_t timeout,
                                 uint32_t *abort_source)
{
    size_t index;
    int32_t ret;

    if ((base_address == 0U) || (buffer == NULL) || (length == 0U)) {
        return -EINVAL;
    }

    ret = i2c_wait_bus_idle(base_address, timeout, abort_source);
    if (ret != 0) {
        return ret;
    }

    for (index = 0U; index < length; index++) {
        uint32_t cmd = I2C_DATA_CMD_CMD_MASK;

        if (index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }
        if ((index + 1U) == length) {
            cmd |= I2C_DATA_CMD_STOP_MASK;
        }

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_TFNF_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }
        WR_REG32(base_address + I2C_DATA_CMD, cmd);

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_RFNE_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }
        buffer[index] = (uint8_t)(RD_REG32(base_address + I2C_DATA_CMD) &
                                  I2C_DATA_CMD_DAT_MASK);
    }

    return i2c_finish_transfer(base_address, timeout, abort_source);
}


int32_t socfpga_i2c_ll_write_then_read_sync(uint32_t base_address,
                                            const uint8_t *tx_buffer,
                                            size_t tx_length,
                                            uint8_t *rx_buffer,
                                            size_t rx_length,
                                            uint32_t timeout,
                                            uint32_t *abort_source)
{
    size_t index;
    int32_t ret;

    if ((base_address == 0U) || (tx_buffer == NULL) || (tx_length == 0U) ||
        (rx_buffer == NULL) || (rx_length == 0U)) {
        return -EINVAL;
    }

    /* The direction change mid-transaction is only legal with RESTART enabled. */
    if ((RD_REG32(base_address + I2C_CON) & I2C_CON_RESTART_EN_MASK) == 0U) {
        return -EPROTO;
    }

    ret = i2c_wait_bus_idle(base_address, timeout, abort_source);
    if (ret != 0) {
        return ret;
    }

    /* Write phase: no STOP on final byte so the read phase uses repeated START. */
    for (index = 0U; index < tx_length; index++) {
        uint32_t cmd = ((uint32_t)tx_buffer[index] & I2C_DATA_CMD_DAT_MASK);

        if (index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_TFNF_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }
        WR_REG32(base_address + I2C_DATA_CMD, cmd);
    }

    /* Read phase: first read command asserts RESTART, final read command asserts STOP. */
    for (index = 0U; index < rx_length; index++) {
        uint32_t cmd = I2C_DATA_CMD_CMD_MASK;

        if (index == 0U) {
            cmd |= I2C_DATA_CMD_RESTART_MASK;
        }
        if ((index + 1U) == rx_length) {
            cmd |= I2C_DATA_CMD_STOP_MASK;
        }

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_TFNF_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }
        WR_REG32(base_address + I2C_DATA_CMD, cmd);

        ret = i2c_wait_mask_or_abort(base_address, I2C_STATUS,
                                     I2C_STATUS_RFNE_MASK, true, timeout,
                                     abort_source);
        if (ret != 0) {
            return ret;
        }
        rx_buffer[index] = (uint8_t)(RD_REG32(base_address + I2C_DATA_CMD) &
                                    I2C_DATA_CMD_DAT_MASK);
    }

    return i2c_finish_transfer(base_address, timeout, abort_source);
}

uint32_t socfpga_i2c_ll_get_status(uint32_t base_address)
{
    return RD_REG32(base_address + I2C_STATUS);
}

uint32_t socfpga_i2c_ll_get_intr_status(uint32_t base_address)
{
    return RD_REG32(base_address + I2C_INTR_STAT);
}

uint32_t socfpga_i2c_ll_get_tx_abort_source(uint32_t base_address)
{
    return RD_REG32(base_address + I2C_TX_ABRT_SOURCE);
}

void socfpga_i2c_ll_mask_all_interrupts(uint32_t base_address)
{
    WR_REG32(base_address + I2C_INTR_MASK, 0U);
}

void socfpga_i2c_ll_clear_interrupts(uint32_t base_address)
{
    (void)RD_REG32(base_address + I2C_CLR_INTR);
}

uint32_t socfpga_i2c_ll_read_reg(uint32_t base_address, uint32_t offset)
{
    return RD_REG32(base_address + offset);
}

void socfpga_i2c_ll_write_reg(uint32_t base_address, uint32_t offset,
                              uint32_t value)
{
    WR_REG32(base_address + offset, value);
}
