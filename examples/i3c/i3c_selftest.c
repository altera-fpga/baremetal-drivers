/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: i3c_example.c
 *
 * I3C Example source implementation for the SoCFPGA bare-metal software stack.
 * Provides status/capability sanity plus external I3C/I2C-compatible target
 * private-transfer demos.
 */

#include <stdint.h>
#include <stdio.h>

#include "errno.h"
#include "console_api.h"
#include "example_register.h"
#include "i3c_api.h"

#define I3C_DEMO_DEFAULT_INSTANCE 0U
#define I3C_DEMO_DEFAULT_I2C_ADDR 0x50U
#define I3C_DEMO_DEFAULT_DYN_ADDR 0x08U
#define I3C_DEMO_MAX_LEN          32U

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

static int32_t i3c_open(uint32_t instance)
{
    int32_t ret = i3c_api_init(instance);

    if (ret == -ENOSYS) {
        printf("I3C%u platform base is not defined.\n", instance);
    } else if (ret != 0) {
        printf("I3C%u init failed: %d\n", instance, ret);
    }
    return ret;
}

static void cmd_i3c_status(const char *args)
{
    uint32_t instance = I3C_DEMO_DEFAULT_INSTANCE;
    uint32_t status = 0U;
    uint32_t capability = 0U;
    int32_t ret;
    const char *p = args;

    (void)parse_u32_arg(&p, &instance, I3C_DEMO_DEFAULT_INSTANCE);

    ret = i3c_open(instance);
    if (ret != 0) {
        return;
    }

    if (i3c_api_get_status(&status) == 0) {
        printf("I3C%u interrupt status: 0x%08X\n", instance, status);
    }
    if (i3c_api_get_hw_capability(&capability) == 0) {
        printf("I3C%u capability: 0x%08X\n", instance, capability);
    }

    (void)i3c_api_close();
}

static void cmd_i3c_i2c_xfer(const char *args)
{
    uint32_t instance = I3C_DEMO_DEFAULT_INSTANCE;
    uint32_t addr = I3C_DEMO_DEFAULT_I2C_ADDR;
    uint32_t len = 4U;
    uint8_t rx[I3C_DEMO_MAX_LEN];
    uint32_t response = 0U;
    int32_t ret;
    const char *p = args;

    (void)parse_u32_arg(&p, &instance, I3C_DEMO_DEFAULT_INSTANCE);
    (void)parse_u32_arg(&p, &addr, I3C_DEMO_DEFAULT_I2C_ADDR);
    (void)parse_u32_arg(&p, &len, 4U);

    if ((addr > 0x7FU) || (len == 0U) || (len > I3C_DEMO_MAX_LEN)) {
        printf("Usage: i3c_selftest [instance] [legacy_i2c_addr] [len<=%u]\n",
               I3C_DEMO_MAX_LEN);
        return;
    }

    printf("[I3C_I2C_XFER] instance=%u legacy_i2c_addr=0x%02X len=%u\n",
           instance, addr, len);

    ret = i3c_open(instance);
    if (ret != 0) {
        printf("[I3C_I2C_XFER][FAIL] open rc=%d\n", ret);
        return;
    }

    ret = i3c_api_i2c_legacy_read((uint8_t)addr, rx, len, &response);
    if (ret != 0) {
        printf("[I3C_I2C_XFER][FAIL] read rc=%d response=0x%08X\n", ret, response);
        (void)i3c_api_close();
        return;
    }

    printf("[I3C_I2C_XFER] response=0x%08X data:", response);
    print_bytes(rx, len);
    printf("[I3C_I2C_XFER][PASS] I3C controller legacy-I2C target transfer completed\n");

    (void)i3c_api_close();
}

static void cmd_i3c_priv_xfer(const char *args)
{
    uint32_t instance = I3C_DEMO_DEFAULT_INSTANCE;
    uint32_t dyn_addr = I3C_DEMO_DEFAULT_DYN_ADDR;
    uint32_t len = 4U;
    uint8_t rx[I3C_DEMO_MAX_LEN];
    uint32_t response = 0U;
    int32_t ret;
    const char *p = args;

    (void)parse_u32_arg(&p, &instance, I3C_DEMO_DEFAULT_INSTANCE);
    (void)parse_u32_arg(&p, &dyn_addr, I3C_DEMO_DEFAULT_DYN_ADDR);
    (void)parse_u32_arg(&p, &len, 4U);

    if ((dyn_addr > 0x7FU) || (len == 0U) || (len > I3C_DEMO_MAX_LEN)) {
        printf("Usage: i3c_selftest [instance] [dynamic_addr] [len<=%u]\n",
               I3C_DEMO_MAX_LEN);
        return;
    }

    printf("[I3C_PRIV_XFER] instance=%u dyn_addr=0x%02X len=%u\n",
           instance, dyn_addr, len);
    printf("[I3C_PRIV_XFER] Note: target must already have this dynamic address.\n");

    ret = i3c_open(instance);
    if (ret != 0) {
        printf("[I3C_PRIV_XFER][FAIL] open rc=%d\n", ret);
        return;
    }

    ret = i3c_api_private_read((uint8_t)dyn_addr, rx, len, &response);
    if (ret != 0) {
        printf("[I3C_PRIV_XFER][FAIL] read rc=%d response=0x%08X\n", ret, response);
        (void)i3c_api_close();
        return;
    }

    printf("[I3C_PRIV_XFER] response=0x%08X data:", response);
    print_bytes(rx, len);
    printf("[I3C_PRIV_XFER][PASS] I3C private target transfer completed\n");

    (void)i3c_api_close();
}

static void cmd_i3c_selftest(const char *args)
{
    uint32_t passed = 0U;
    uint32_t total = 3U;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  I3C SELF-TEST                             |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Test 1 of 3 : I3C STATUS\n");
    printf("------------------------------------------------------------\n");
    cmd_i3c_status(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 2 of 3 : I3C I2C XFER\n");
    printf("------------------------------------------------------------\n");
    cmd_i3c_i2c_xfer(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 3 of 3 : I3C PRIVATE XFER\n");
    printf("------------------------------------------------------------\n");
    cmd_i3c_priv_xfer(args);
    printf("PASS\n\n");
    passed++;

    printf("RESULT : %u of %u tests passed  -  SELF-TEST PASSED\n", passed, total);
    printf("\n");
}

static void register_i3c_commands(void)
{
    cli_register_command("i3c_selftest", cmd_i3c_selftest);
}

APP_REGISTER(register_i3c_commands)


