/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: i2c_selftest.c
 *
 * I2C validation example for the SoCFPGA bare-metal shell.
 *
 * Command:
 *   i2c_selftest [instance] [7bit_addr] [reg8] [len] [bus_hz]
 *
 * Controller identity, SCL timing, bus scan and recovery are checked on every
 * board because they need no external device. The transfer phases need a target
 * on the bus, so they are skipped rather than failed when the scan finds none;
 * a board without an I2C device fitted is not a firmware defect.
 *
 * Layer: examples
 * Component: I2C Demo
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "errno.h"
#include "console_api.h"
#include "example_register.h"
#include "i2c_api.h"

#define I2C_DEMO_DEFAULT_INSTANCE 0U
#define I2C_DEMO_DEFAULT_REG      0x00U
#define I2C_DEMO_DEFAULT_LEN      4U
#define I2C_DEMO_MAX_READ_LEN     32U
#define I2C_DEMO_PROBE_ADDR       0x50U
#define I2C_DEMO_BUS_HZ           100000U
#define I2C_DEMO_FAST_BUS_HZ      400000U

/* Reserved addresses at both ends are skipped, matching what i2cdetect scans. */
#define I2C_SCAN_FIRST_ADDR       0x08U
#define I2C_SCAN_LAST_ADDR        0x77U
#define I2C_SCAN_MAX_INSTANCE     4U

/* A NACK proves the bus is alive; a timeout means nothing is driving it. Bail out
 * early on consecutive timeouts so scanning an unrouted instance stays quick.
 */
#define I2C_SCAN_DEAD_BUS_PROBES  4U

#define I2C_P3T_ADDR_PRIMARY      0x4CU
#define I2C_P3T_ADDR_SECONDARY    0x48U
#define I2C_P3T_TEMP_REG          0x00U
#define I2C_P3T_CONFIG_REG        0x01U
#define I2C_P3T_TLOW_REG          0x02U
#define I2C_P3T_THIGH_REG         0x03U
#define I2C_P3T_TEMP_MIN_MC       15000
#define I2C_P3T_TEMP_MAX_MC       40000

/* Specification minimum SCL high times, and the fall time the controller adds. */
#define I2C_SS_MIN_HIGH_NS        4000U
#define I2C_FS_MIN_HIGH_NS        600U
#define I2C_SCL_FALL_NS           300U

/* Checked against the requested period, not the driver's arithmetic, so the band
 * is deliberately generous.
 */
#define I2C_TIMING_TOLERANCE_PCT  30U

/* Fixed cycles the controller adds around the programmed counts. */
#define I2C_TIMING_FIXED_CYCLES   4U

#define I2C_SELFTEST_SKIP         1

struct i2c_selftest_state {
    uint32_t instance;
    uint32_t target;
    uint32_t reg;
    uint32_t len;
    uint32_t bus_hz;
    bool target_supplied;
    uint32_t found_count;
    uint32_t first_found;
    uint32_t first_absent;
    bool bus_responsive;
    bool p3t_found;
    uint32_t p3t_instance;
    uint32_t p3t_addr;
};

static struct i2c_selftest_state i2c_state;

static const char *skip_spaces(const char *p)
{
    while ((p != NULL) && (*p == ' ')) {
        p++;
    }
    return p;
}

static int parse_u32_arg(const char **pp, uint32_t *value, uint32_t default_value)
{
    const char *p = skip_spaces(*pp);

    if ((p == NULL) || (*p == '\0')) {
        *value = default_value;
        *pp = p;
        return 0;
    }

    if ((p[0] == '0') && ((p[1] == 'x') || (p[1] == 'X'))) {
        *value = (uint32_t)parse_hex(p);
    } else {
        *value = parse_dec(p);
    }

    while ((*p != '\0') && (*p != ' ')) {
        p++;
    }
    *pp = p;
    return 1;
}

static void print_bytes(const uint8_t *buf, uint32_t len)
{
    uint32_t i;

    for (i = 0U; i < len; i++) {
        printf(" %02X", buf[i]);
    }
    printf("\n");
}

static int32_t i2c_open(uint32_t instance, uint32_t target, uint32_t bus_hz)
{
    int32_t ret = i2c_api_init(instance, (uint16_t)target, bus_hz);

    if (ret == -ENOSYS) {
        printf("[I2C] instance %u has no platform base address\n", instance);
    } else if (ret == -ENODEV) {
        printf("[I2C] no controller responding on instance %u\n", instance);
    } else if (ret != 0) {
        printf("[I2C] instance %u init rc=%d\n", instance, ret);
    }
    return ret;
}

/* Distinguishes "nothing at this address" from "the controller cannot drive". */
static void print_transfer_error(int32_t ret)
{
    uint32_t source = 0U;

    if (ret == -ETIMEDOUT) {
        printf("[I2C] no bus activity, SCL or SDA is not being driven\n");
        return;
    }

    if (i2c_api_get_abort_source(&source) == 0) {
        printf("[I2C] rc=%d abort=%s (0x%08X, %u byte(s) flushed)\n", ret,
               socfpga_i2c_abort_source_str(source), source,
               socfpga_i2c_abort_flush_count(source));
    } else {
        printf("[I2C] rc=%d\n", ret);
    }
}

static uint32_t i2c_scl_period_cycles(const socfpga_i2c_info_t *info)
{
    return info->scl_high_count + info->scl_low_count + I2C_TIMING_FIXED_CYCLES;
}

static uint32_t i2c_percent_error(uint32_t actual, uint32_t expected)
{
    uint32_t diff = (actual > expected) ? (actual - expected) : (expected - actual);

    if (expected == 0U) {
        return 100U;
    }
    return (diff * 100U) / expected;
}

/* Establishes that a controller exists, is clocked and out of reset, and reports
 * what the driver programmed into it.
 */
static int32_t phase_controller(void)
{
    socfpga_i2c_info_t info;
    uint32_t status = 0U;
    int32_t ret;

    ret = i2c_open(i2c_state.instance, i2c_state.target, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_CTRL][FAIL] open rc=%d\n", ret);
        return ret;
    }

    ret = i2c_api_get_info(&info);
    if (ret != 0) {
        printf("[I2C_CTRL][FAIL] info rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    ret = i2c_api_get_status(&status);
    if (ret != 0) {
        printf("[I2C_CTRL][FAIL] status rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    printf("[I2C_CTRL] instance=%u component_version=0x%08X status=0x%08X\n",
           i2c_state.instance, info.component_version, status);
    printf("[I2C_CTRL] input_clock=%u Hz requested=%u Hz speed_mode=%u\n",
           info.input_clock_hz, info.bus_hz, info.speed_mode);
    printf("[I2C_CTRL] scl_hcnt=%u scl_lcnt=%u tx_fifo=%u rx_fifo=%u\n",
           info.scl_high_count, info.scl_low_count,
           info.tx_fifo_depth, info.rx_fifo_depth);

    if ((info.input_clock_hz == 0U) || (info.scl_high_count == 0U) ||
        (info.scl_low_count == 0U) || (info.tx_fifo_depth == 0U)) {
        printf("[I2C_CTRL][FAIL] controller reported an unusable configuration\n");
        (void)i2c_api_close();
        return -EIO;
    }

    printf("[I2C_CTRL][PASS] controller present and configured\n");
    (void)i2c_api_close();
    return 0;
}

/* The SCL counts must track the requested frequency and still honour the
 * specification minimum high time, at both standard and fast speed.
 */
static int32_t phase_timing(void)
{
    static const uint32_t rates[2] = { I2C_DEMO_BUS_HZ, I2C_DEMO_FAST_BUS_HZ };
    static const uint32_t min_high_ns[2] = { I2C_SS_MIN_HIGH_NS,
                                             I2C_FS_MIN_HIGH_NS };
    uint32_t period[2] = { 0U, 0U };
    uint32_t i;

    for (i = 0U; i < 2U; i++) {
        socfpga_i2c_info_t info;
        uint32_t expected;
        uint32_t error_pct;
        uint32_t high_ns;
        int32_t ret;

        ret = i2c_open(i2c_state.instance, i2c_state.target, rates[i]);
        if (ret != 0) {
            printf("[I2C_TIMING][FAIL] open at %u Hz rc=%d\n", rates[i], ret);
            return ret;
        }

        ret = i2c_api_get_info(&info);
        (void)i2c_api_close();
        if (ret != 0) {
            printf("[I2C_TIMING][FAIL] info at %u Hz rc=%d\n", rates[i], ret);
            return ret;
        }

        if (info.input_clock_hz == 0U) {
            printf("[I2C_TIMING][FAIL] input clock is unknown at %u Hz\n",
                   rates[i]);
            return -EIO;
        }

        period[i] = i2c_scl_period_cycles(&info);
        expected = info.input_clock_hz / rates[i];
        error_pct = i2c_percent_error(period[i], expected);
        /* SCL high = (HCNT + 3) ic_clk periods plus the bus fall time. */
        high_ns = (uint32_t)(((uint64_t)info.scl_high_count + 3ULL) *
                             1000000000ULL / (uint64_t)info.input_clock_hz) +
                  I2C_SCL_FALL_NS;

        printf("[I2C_TIMING] %u Hz: hcnt=%u lcnt=%u period=%u cycles "
               "(want %u, %u%% off) high=%u ns\n",
               rates[i], info.scl_high_count, info.scl_low_count, period[i],
               expected, error_pct, high_ns);

        if (error_pct > I2C_TIMING_TOLERANCE_PCT) {
            printf("[I2C_TIMING][FAIL] SCL period does not match %u Hz\n",
                   rates[i]);
            return -ERANGE;
        }
        if (high_ns < min_high_ns[i]) {
            printf("[I2C_TIMING][FAIL] SCL high time %u ns is below the %u ns "
                   "minimum\n", high_ns, min_high_ns[i]);
            return -ERANGE;
        }
    }

    if (period[1] >= period[0]) {
        printf("[I2C_TIMING][FAIL] fast mode is not faster than standard mode\n");
        return -ERANGE;
    }

    printf("[I2C_TIMING][PASS] SCL counts track the requested bus frequency\n");
    return 0;
}

/* The bare-metal equivalent of i2cdetect. A NACK is a healthy answer; only a bus
 * that never responds at all is a failure.
 */
static int32_t phase_scan(void)
{
    uint32_t addr;
    uint32_t consecutive_timeouts = 0U;
    int32_t ret;

    i2c_state.found_count = 0U;
    i2c_state.first_found = 0U;
    i2c_state.first_absent = 0U;
    i2c_state.bus_responsive = false;

    ret = i2c_open(i2c_state.instance, I2C_DEMO_PROBE_ADDR, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_SCAN][FAIL] open rc=%d\n", ret);
        return ret;
    }

    printf("[I2C_SCAN] probing 0x%02X..0x%02X on instance %u\n",
           I2C_SCAN_FIRST_ADDR, I2C_SCAN_LAST_ADDR, i2c_state.instance);

    for (addr = I2C_SCAN_FIRST_ADDR; addr <= I2C_SCAN_LAST_ADDR; addr++) {
        ret = i2c_api_probe((uint16_t)addr);

        if (ret == 0) {
            printf("[I2C_SCAN] target at 0x%02X\n", addr);
            if (i2c_state.found_count == 0U) {
                i2c_state.first_found = addr;
            }
            i2c_state.found_count++;
            i2c_state.bus_responsive = true;
            consecutive_timeouts = 0U;
        } else if (ret == -ETIMEDOUT) {
            consecutive_timeouts++;
            if (consecutive_timeouts >= I2C_SCAN_DEAD_BUS_PROBES) {
                break;
            }
        } else {
            /* NACK and other bus-level answers mean the controller drove the
             * bus and something terminated the cycle.
             */
            if ((ret == -ENXIO) && (i2c_state.first_absent == 0U)) {
                i2c_state.first_absent = addr;
            }
            i2c_state.bus_responsive = true;
            consecutive_timeouts = 0U;
        }
    }

    (void)i2c_api_close();

    if (!i2c_state.bus_responsive) {
        printf("[I2C_SCAN][FAIL] instance %u never reached the bus; SCL or SDA "
               "is not routed or has no pull-up\n", i2c_state.instance);
        return -ETIMEDOUT;
    }

    printf("[I2C_SCAN][PASS] bus reachable, %u target(s) responding\n",
           i2c_state.found_count);
    return 0;
}

/* Register read from the address the caller gave, or the first one the scan found. */
static int32_t phase_register_read(void)
{
    uint8_t tx[1];
    uint8_t rx[I2C_DEMO_MAX_READ_LEN];
    uint32_t target;
    int32_t ret;

    target = i2c_state.target_supplied ? i2c_state.target
                                       : i2c_state.first_found;
    if (target == 0U) {
        printf("[I2C_XFER][SKIP] no target on instance %u; pass an address to "
               "test one explicitly\n", i2c_state.instance);
        return I2C_SELFTEST_SKIP;
    }

    printf("[I2C_XFER] instance=%u addr=0x%02X reg=0x%02X len=%u\n",
           i2c_state.instance, target, i2c_state.reg, i2c_state.len);

    ret = i2c_open(i2c_state.instance, target, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_XFER][FAIL] open rc=%d\n", ret);
        return ret;
    }

    tx[0] = (uint8_t)i2c_state.reg;
    ret = i2c_api_write_then_read(tx, 1U, rx, i2c_state.len);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_XFER][FAIL] write_then_read rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    printf("[I2C_XFER] data:");
    print_bytes(rx, i2c_state.len);
    printf("[I2C_XFER][PASS] combined write-then-read completed\n");

    (void)i2c_api_close();
    return 0;
}

/* The equivalent of i2cset followed by i2cget. Only runs against an address the
 * caller named, because writing to a scanned device could reconfigure the board.
 */
static int32_t phase_write_readback(void)
{
    static const uint8_t pattern[2] = { 0xDEU, 0xADU };
    uint8_t tx[3];
    uint8_t saved[2] = { 0U, 0U };
    uint8_t rx[2] = { 0U, 0U };
    int32_t ret;

    if (!i2c_state.target_supplied) {
        printf("[I2C_RW][SKIP] no address given; a write is only issued to a "
               "target the caller names\n");
        return I2C_SELFTEST_SKIP;
    }

    ret = i2c_open(i2c_state.instance, i2c_state.target, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_RW][FAIL] open rc=%d\n", ret);
        return ret;
    }

    tx[0] = (uint8_t)i2c_state.reg;
    ret = i2c_api_write_then_read(tx, 1U, saved, 2U);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_RW][FAIL] read of original content rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    tx[1] = pattern[0];
    tx[2] = pattern[1];
    ret = i2c_api_write(tx, 3U);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_RW][FAIL] write rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    tx[0] = (uint8_t)i2c_state.reg;
    ret = i2c_api_write_then_read(tx, 1U, rx, 2U);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_RW][FAIL] readback rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    printf("[I2C_RW] wrote %02X %02X read %02X %02X\n",
           pattern[0], pattern[1], rx[0], rx[1]);

    if ((rx[0] != pattern[0]) || (rx[1] != pattern[1])) {
        printf("[I2C_RW][FAIL] readback does not match the written pattern\n");
        (void)i2c_api_close();
        return -EIO;
    }

    /* Put back what was there so the test leaves no persistent change. */
    tx[1] = saved[0];
    tx[2] = saved[1];
    (void)i2c_api_write(tx, 3U);

    printf("[I2C_RW][PASS] write and readback verified at 0x%02X\n",
           i2c_state.target);
    (void)i2c_api_close();
    return 0;
}

/* A terminated transfer must leave the controller recoverable to idle. */
static int32_t phase_recovery(void)
{
    uint32_t status = 0U;
    int32_t ret;

    ret = i2c_open(i2c_state.instance, I2C_DEMO_PROBE_ADDR, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_RECOVER][FAIL] open rc=%d\n", ret);
        return ret;
    }

    /* The result of this probe does not matter; it exists to leave the
     * controller having just terminated a transfer.
     */
    (void)i2c_api_probe(I2C_SCAN_LAST_ADDR);

    /* Recovery only reports success once the master is inactive and the TX FIFO
     * has drained, so its return code is the oracle here.
     */
    ret = i2c_api_recover();
    if (ret != 0) {
        printf("[I2C_RECOVER][FAIL] recover rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    ret = i2c_api_get_status(&status);
    if (ret != 0) {
        printf("[I2C_RECOVER][FAIL] status rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    printf("[I2C_RECOVER] status after recovery: 0x%08X\n", status);
    printf("[I2C_RECOVER][PASS] controller returned to idle\n");
    (void)i2c_api_close();
    return 0;
}

static int32_t p3t_temp_milli_c(uint8_t msb, uint8_t lsb)
{
    int32_t raw12 = (int32_t)(((uint32_t)msb << 4) |
                              (((uint32_t)lsb >> 4) & 0x0FU));

    /* The 12-bit reading is two's complement, so sub-zero values sign-extend. */
    if (raw12 >= 2048) {
        raw12 -= 4096;
    }

    /* P3T 12-bit temperature LSB = 0.0625 degree C = 62.5 milli-C. */
    return (raw12 * 625) / 10;
}

static void p3t_encode_temp_c(uint32_t temp_c, uint8_t out[2])
{
    uint32_t raw12 = temp_c * 16U;

    out[0] = (uint8_t)((raw12 >> 4) & 0xFFU);
    out[1] = (uint8_t)((raw12 & 0x0FU) << 4);
}

static void print_temp_mc(const char *name, int32_t temp_mc)
{
    int32_t whole = temp_mc / 1000;
    int32_t frac = temp_mc % 1000;

    if (frac < 0) {
        frac = -frac;
    }
    printf("%s: %d.%03d C\n", name, whole, frac);
}

static int32_t i2c_reg_read8(uint8_t reg, uint8_t *rx, uint32_t len)
{
    uint8_t tx[1];

    if ((rx == NULL) || (len == 0U)) {
        return -EINVAL;
    }
    tx[0] = reg;
    return i2c_api_write_then_read(tx, 1U, rx, len);
}

static int32_t i2c_reg_write_bytes(uint8_t reg, const uint8_t *data, uint32_t len)
{
    uint8_t tx[4];
    uint32_t i;

    if ((data == NULL) || (len == 0U) || (len > 3U)) {
        return -EINVAL;
    }

    tx[0] = reg;
    for (i = 0U; i < len; i++) {
        tx[i + 1U] = data[i];
    }

    return i2c_api_write(tx, len + 1U);
}

/* The sensor sits on a detachable NXP evaluation board, so absence is recorded
 * rather than reported as an error.
 */
static void p3t_locate(void)
{
    static const uint8_t addrs[2] = { I2C_P3T_ADDR_PRIMARY,
                                      I2C_P3T_ADDR_SECONDARY };
    uint32_t instance;
    uint32_t i;

    i2c_state.p3t_found = false;

    for (instance = 0U; instance <= I2C_SCAN_MAX_INSTANCE; instance++) {
        if (i2c_api_init(instance, (uint16_t)addrs[0], I2C_DEMO_BUS_HZ) != 0) {
            continue;
        }

        for (i = 0U; i < 2U; i++) {
            if (i2c_api_probe((uint16_t)addrs[i]) == 0) {
                i2c_state.p3t_found = true;
                i2c_state.p3t_instance = instance;
                i2c_state.p3t_addr = addrs[i];
                break;
            }
        }

        (void)i2c_api_close();

        if (i2c_state.p3t_found) {
            return;
        }
    }
}

/* Read and write exercise against the P3T temperature sensor when one is fitted. */
static int32_t phase_p3t(void)
{
    uint8_t temp_raw[2] = { 0U, 0U };
    uint8_t cfg_raw[2] = { 0U, 0U };
    uint8_t cfg_new[1] = { 0U };
    uint8_t cfg_verify[2] = { 0U, 0U };
    uint8_t t_low[2];
    uint8_t t_high[2];
    uint8_t verify[2] = { 0U, 0U };
    int32_t temp_mc;
    int32_t ret;

    p3t_locate();

    if (!i2c_state.p3t_found) {
        printf("[I2C_P3T][SKIP] no P3T-compatible sensor at 0x%02X or 0x%02X on "
               "instances 0..%u; this board has no NXP I2C daughter-board\n",
               I2C_P3T_ADDR_PRIMARY, I2C_P3T_ADDR_SECONDARY,
               I2C_SCAN_MAX_INSTANCE);
        return I2C_SELFTEST_SKIP;
    }

    printf("[I2C_P3T] sensor at instance %u addr 0x%02X\n",
           i2c_state.p3t_instance, i2c_state.p3t_addr);

    ret = i2c_open(i2c_state.p3t_instance, i2c_state.p3t_addr, I2C_DEMO_BUS_HZ);
    if (ret != 0) {
        printf("[I2C_P3T][FAIL] open rc=%d\n", ret);
        return ret;
    }

    ret = i2c_reg_read8((uint8_t)I2C_P3T_TEMP_REG, temp_raw, 2U);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_P3T][FAIL] temperature read rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    temp_mc = p3t_temp_milli_c(temp_raw[0], temp_raw[1]);
    printf("[I2C_P3T] temp raw: %02X %02X\n", temp_raw[0], temp_raw[1]);
    print_temp_mc("[I2C_P3T] temperature", temp_mc);

    if ((temp_mc < I2C_P3T_TEMP_MIN_MC) || (temp_mc > I2C_P3T_TEMP_MAX_MC)) {
        printf("[I2C_P3T][FAIL] temperature outside the 15-40 C lab range\n");
        (void)i2c_api_close();
        return -ERANGE;
    }

    ret = i2c_reg_read8((uint8_t)I2C_P3T_CONFIG_REG, cfg_raw, 2U);
    if (ret != 0) {
        printf("[I2C_P3T][FAIL] config read rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    cfg_new[0] = (cfg_raw[0] == 0x00U) ? 0x28U : 0x00U;
    ret = i2c_reg_write_bytes((uint8_t)I2C_P3T_CONFIG_REG, cfg_new, 1U);
    if (ret != 0) {
        printf("[I2C_P3T][FAIL] config write rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    ret = i2c_reg_read8((uint8_t)I2C_P3T_CONFIG_REG, cfg_verify, 2U);
    if ((ret != 0) || (cfg_verify[0] != cfg_new[0])) {
        printf("[I2C_P3T][FAIL] config verify rc=%d wrote=%02X read=%02X\n",
               ret, cfg_new[0], cfg_verify[0]);
        (void)i2c_api_close();
        return (ret != 0) ? ret : -EIO;
    }

    /* Restore the original config byte to avoid a persistent side effect. */
    (void)i2c_reg_write_bytes((uint8_t)I2C_P3T_CONFIG_REG, cfg_raw, 1U);

    p3t_encode_temp_c(15U, t_low);
    p3t_encode_temp_c(30U, t_high);

    ret = i2c_reg_write_bytes((uint8_t)I2C_P3T_TLOW_REG, t_low, 2U);
    if (ret != 0) {
        printf("[I2C_P3T][FAIL] T-low write rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }
    ret = i2c_reg_read8((uint8_t)I2C_P3T_TLOW_REG, verify, 2U);
    if ((ret != 0) || (verify[0] != t_low[0]) || (verify[1] != t_low[1])) {
        printf("[I2C_P3T][FAIL] T-low verify rc=%d wrote=%02X %02X read=%02X %02X\n",
               ret, t_low[0], t_low[1], verify[0], verify[1]);
        (void)i2c_api_close();
        return (ret != 0) ? ret : -EIO;
    }

    ret = i2c_reg_write_bytes((uint8_t)I2C_P3T_THIGH_REG, t_high, 2U);
    if (ret != 0) {
        printf("[I2C_P3T][FAIL] T-high write rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }
    ret = i2c_reg_read8((uint8_t)I2C_P3T_THIGH_REG, verify, 2U);
    if ((ret != 0) || (verify[0] != t_high[0]) || (verify[1] != t_high[1])) {
        printf("[I2C_P3T][FAIL] T-high verify rc=%d wrote=%02X %02X read=%02X %02X\n",
               ret, t_high[0], t_high[1], verify[0], verify[1]);
        (void)i2c_api_close();
        return (ret != 0) ? ret : -EIO;
    }

    printf("[I2C_P3T][PASS] temperature, config and threshold registers verified\n");
    (void)i2c_api_close();
    return 0;
}

static volatile int32_t i2c_async_status;
static volatile bool i2c_async_done;

static void i2c_async_callback(socfpga_i2c_handle_t handle, int32_t status,
                               void *context)
{
    (void)handle;
    (void)context;
    i2c_async_status = status;
    i2c_async_done = true;
}

/* Exercises the standalone write path against an address the scan proved is empty.
 * No device is written, yet the write must still drive the address and report the
 * missing acknowledge as -ENXIO. This is the only write coverage that needs no
 * scratch device on the bus.
 */
static int32_t phase_write_nack(void)
{
    uint8_t tx[2] = { 0x00U, 0x00U };
    uint32_t source = 0U;
    int32_t ret;

    if (i2c_state.first_absent == 0U) {
        printf("[I2C_WNACK][SKIP] scan found no unoccupied address to write to\n");
        return I2C_SELFTEST_SKIP;
    }

    ret = i2c_open(i2c_state.instance, i2c_state.first_absent, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_WNACK][FAIL] open rc=%d\n", ret);
        return ret;
    }

    ret = i2c_api_write(tx, sizeof(tx));
    (void)i2c_api_get_abort_source(&source);

    printf("[I2C_WNACK] write to unused 0x%02X rc=%d abort=%s (0x%08X, %u of %u "
           "byte(s) flushed)\n", i2c_state.first_absent, ret,
           socfpga_i2c_abort_source_str(source), source,
           socfpga_i2c_abort_flush_count(source), (uint32_t)sizeof(tx));

    if (ret != -ENXIO) {
        printf("[I2C_WNACK][FAIL] expected -ENXIO from an unused address\n");
        (void)i2c_api_close();
        return (ret == 0) ? -EIO : ret;
    }
    if ((source & SOCFPGA_I2C_ABORT_ADDR_NACK) == 0U) {
        printf("[I2C_WNACK][FAIL] address-NACK bit not set in abort source\n");
        (void)i2c_api_close();
        return -EIO;
    }

    printf("[I2C_WNACK][PASS] write aborted on address NACK and reported it\n");
    (void)i2c_api_close();
    return 0;
}

/* Runs the same combined transfer through the interrupt-driven engine and requires
 * it to match the synchronous path. The engine is serviced from this context
 * because the I2C interrupt is not routed to the GIC, so this proves the state
 * machine rather than interrupt delivery.
 */
static int32_t phase_async(void)
{
    uint8_t tx[1];
    uint8_t sync_rx[I2C_DEMO_MAX_READ_LEN];
    uint8_t async_rx[I2C_DEMO_MAX_READ_LEN];
    uint32_t target;
    uint32_t i;
    int32_t ret;

    target = i2c_state.target_supplied ? i2c_state.target
                                       : i2c_state.first_found;
    if (target == 0U) {
        printf("[I2C_ASYNC][SKIP] no target on instance %u to transfer against\n",
               i2c_state.instance);
        return I2C_SELFTEST_SKIP;
    }

    ret = i2c_open(i2c_state.instance, target, i2c_state.bus_hz);
    if (ret != 0) {
        printf("[I2C_ASYNC][FAIL] open rc=%d\n", ret);
        return ret;
    }

    tx[0] = (uint8_t)i2c_state.reg;
    ret = i2c_api_write_then_read(tx, 1U, sync_rx, i2c_state.len);
    if (ret != 0) {
        print_transfer_error(ret);
        printf("[I2C_ASYNC][FAIL] reference synchronous read rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    i2c_async_status = 0;
    i2c_async_done = false;

    tx[0] = (uint8_t)i2c_state.reg;
    ret = i2c_api_write_then_read_async(tx, 1U, async_rx, i2c_state.len,
                                       i2c_async_callback, NULL);
    if (ret != 0) {
        printf("[I2C_ASYNC][FAIL] queue rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }

    ret = i2c_api_wait_async(0U);
    if (ret != 0) {
        printf("[I2C_ASYNC][FAIL] transfer did not complete rc=%d\n", ret);
        (void)i2c_api_close();
        return ret;
    }
    if (!i2c_async_done) {
        printf("[I2C_ASYNC][FAIL] completion callback never fired\n");
        (void)i2c_api_close();
        return -EIO;
    }
    if (i2c_async_status != 0) {
        printf("[I2C_ASYNC][FAIL] callback reported rc=%d\n", i2c_async_status);
        (void)i2c_api_close();
        return i2c_async_status;
    }

    printf("[I2C_ASYNC] sync:");
    print_bytes(sync_rx, i2c_state.len);
    printf("[I2C_ASYNC] async:");
    print_bytes(async_rx, i2c_state.len);

    for (i = 0U; i < i2c_state.len; i++) {
        if (async_rx[i] != sync_rx[i]) {
            printf("[I2C_ASYNC][FAIL] byte %u differs: sync %02X async %02X\n",
                   i, sync_rx[i], async_rx[i]);
            (void)i2c_api_close();
            return -EIO;
        }
    }

    printf("[I2C_ASYNC][PASS] combined transfer matches the synchronous path\n");
    (void)i2c_api_close();
    return 0;
}

struct i2c_selftest_phase {
    const char *title;
    int32_t (*run)(void);
};

static const struct i2c_selftest_phase i2c_phases[] = {
    { "I2C CONTROLLER",     phase_controller },
    { "I2C SCL TIMING",     phase_timing },
    { "I2C BUS SCAN",       phase_scan },
    { "I2C REGISTER READ",  phase_register_read },
    { "I2C WRITE NACK",     phase_write_nack },
    { "I2C WRITE READBACK", phase_write_readback },
    { "I2C ASYNC TRANSFER", phase_async },
    { "I2C BUS RECOVERY",   phase_recovery },
    { "I2C P3T SENSOR",     phase_p3t },
};

#define I2C_PHASE_COUNT (sizeof(i2c_phases) / sizeof(i2c_phases[0]))

static void cmd_i2c_selftest(const char *args)
{
    const char *p = args;
    uint32_t total = (uint32_t)I2C_PHASE_COUNT;
    uint32_t passed = 0U;
    uint32_t skipped = 0U;
    uint32_t failures = 0U;
    uint32_t i;

    /* Discard results from any earlier invocation in this session. */
    i2c_state.found_count = 0U;
    i2c_state.first_found = 0U;
    i2c_state.first_absent = 0U;
    i2c_state.bus_responsive = false;
    i2c_state.p3t_found = false;
    i2c_state.p3t_instance = 0U;
    i2c_state.p3t_addr = 0U;

    (void)parse_u32_arg(&p, &i2c_state.instance, I2C_DEMO_DEFAULT_INSTANCE);
    i2c_state.target_supplied = (parse_u32_arg(&p, &i2c_state.target, 0U) != 0) &&
                               (i2c_state.target != 0U);
    (void)parse_u32_arg(&p, &i2c_state.reg, I2C_DEMO_DEFAULT_REG);
    (void)parse_u32_arg(&p, &i2c_state.len, I2C_DEMO_DEFAULT_LEN);
    (void)parse_u32_arg(&p, &i2c_state.bus_hz, I2C_DEMO_BUS_HZ);

    if ((i2c_state.bus_hz < 1000U) || (i2c_state.bus_hz > 1000000U)) {
        printf("[I2C] ignoring %u Hz, using %u Hz\n", i2c_state.bus_hz,
               I2C_DEMO_BUS_HZ);
        i2c_state.bus_hz = I2C_DEMO_BUS_HZ;
    }
    if (i2c_state.bus_hz > I2C_DEMO_FAST_BUS_HZ) {
        printf("[I2C] %u Hz selects fast-plus, beyond the fast-mode maximum this "
               "controller reports in IC_COMP_PARAM_1\n", i2c_state.bus_hz);
    }

    if (i2c_state.target > 0x7FU) {
        printf("[I2C] ignoring 0x%02X, only 7-bit addresses are supported\n",
               i2c_state.target);
        i2c_state.target = 0U;
        i2c_state.target_supplied = false;
    }
    if ((i2c_state.len == 0U) || (i2c_state.len > I2C_DEMO_MAX_READ_LEN)) {
        i2c_state.len = I2C_DEMO_DEFAULT_LEN;
    }
    if (!i2c_state.target_supplied) {
        i2c_state.target = I2C_DEMO_PROBE_ADDR;
    }

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  I2C SELF-TEST                             |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    for (i = 0U; i < total; i++) {
        int32_t ret;

        printf("Test %u of %u : %s\n", i + 1U, total, i2c_phases[i].title);
        printf("------------------------------------------------------------\n");

        ret = i2c_phases[i].run();
        if (ret == 0) {
            printf("PASS\n\n");
            passed++;
        } else if (ret == I2C_SELFTEST_SKIP) {
            printf("SKIP\n\n");
            skipped++;
        } else {
            printf("FAIL (%d)\n\n", ret);
            failures++;
        }
    }

    printf("RESULT : %u of %u tests passed, %u skipped  -  SELF-TEST %s\n",
           passed, total, skipped, (failures == 0U) ? "PASSED" : "FAILED");
    printf("\n");
}

static void register_i2c_commands(void)
{
    cli_register_command("i2c_selftest", cmd_i2c_selftest);
}

APP_REGISTER(register_i2c_commands)
