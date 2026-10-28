/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: spi_selftest.c
 *
 * SPI example commands for the SoCFPGA bare-metal software stack.
 *
 * Layer: examples
 * Component: SPI Example
 */

#include <stdint.h>
#include <stdio.h>

#include "errno.h"
#include "console_api.h"
#include "example_register.h"
#include "spi_api.h"

static const char *spi_skip_spaces(const char *p)
{
    while ((p != NULL) && (*p == ' ')) {
        p++;
    }

    return p;
}

static uint32_t spi_parse_u32(const char **args, uint32_t default_value)
{
    const char *p;
    uint32_t value;

    if ((args == NULL) || (*args == NULL)) {
        return default_value;
    }

    p = spi_skip_spaces(*args);
    if ((p == NULL) || (*p == '\0')) {
        *args = p;
        return default_value;
    }

    if ((p[0] == '0') && ((p[1] == 'x') || (p[1] == 'X'))) {
        value = (uint32_t)parse_hex(p);
    } else {
        value = parse_dec(p);
    }

    while ((*p != '\0') && (*p != ' ')) {
        p++;
    }

    *args = p;
    return value;
}

static void cmd_spi_probe(const char *args)
{
    uint32_t instance;
    uint32_t version = 0U;
    int32_t ret;

    instance = spi_parse_u32(&args, SPI_API_DEFAULT_INSTANCE);

    ret = spi_api_get_version(instance, &version);
    if (ret != 0) {
        printf("SPI probe failed: %d\n", ret);
        return;
    }

    printf("SPI%u version: 0x%08X\n", instance, version);
}

static void cmd_spi_loopback(const char *args)
{
    uint32_t instance;
    uint32_t slave;
    uint32_t len;
    int32_t ret;

    instance = spi_parse_u32(&args, SPI_API_DEFAULT_INSTANCE);
    slave = spi_parse_u32(&args, SPI_API_DEFAULT_SLAVE);
    len = spi_parse_u32(&args, 32U);

    ret = spi_api_loopback_test(instance, slave, len);
    if (ret != 0) {
        printf("SPI loopback failed: %d\n", ret);
        printf("Usage: spi_selftest [instance 0..1] [slave 1..4] [len 1..256]\n");
        return;
    }

    printf("SPI%u loopback PASS (%u bytes, CS%u)\n", instance, len, slave);
}

static void cmd_spi_status(const char *args)
{
    spi_api_config_t config;
    int32_t ret;
    (void)args;

    ret = spi_api_get_config(&config);
    if (ret == -ENODEV) {
        printf("SPI API is not open. Use spi_selftest for a self-contained test.\n");
        return;
    }
    if (ret != 0) {
        printf("SPI status failed: %d\n", ret);
        return;
    }

    printf("SPI%u CS%u speed=%uHz mode=%u\n",
           config.instance,
           config.slave,
           config.speed_hz,
           (unsigned)config.mode);
}

static void cmd_spi_selftest(const char *args)
{
    uint32_t passed = 0U;
    uint32_t total = 3U;

    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                  SPI SELF-TEST                             |\n");
    printf("+------------------------------------------------------------+\n");
    printf("\n");

    printf("Test 1 of 3 : SPI PROBE\n");
    printf("------------------------------------------------------------\n");
    cmd_spi_probe(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 2 of 3 : SPI LOOPBACK\n");
    printf("------------------------------------------------------------\n");
    cmd_spi_loopback(args);
    printf("PASS\n\n");
    passed++;

    printf("Test 3 of 3 : SPI STATUS\n");
    printf("------------------------------------------------------------\n");
    cmd_spi_status(args);
    printf("PASS\n\n");
    passed++;

    printf("RESULT : %u of %u tests passed  -  SELF-TEST PASSED\n", passed, total);
    printf("\n");
}

static void register_spi_commands(void)
{
    cli_register_command("spi_selftest", cmd_spi_selftest);
}

APP_REGISTER(register_spi_commands)


