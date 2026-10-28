/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: crc_selftest.c
 *
 * CRC example commands for the SoCFPGA bare-metal software stack.
 *
 * Layer: examples
 * Component: CRC Example
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errno.h"
#include "console_api.h"
#include "crc_api.h"
#include "example_register.h"

#define CRC_DEMO_CHANNEL       0x0000000000001123ULL
#define CRC_DEMO_IMAGE_SIZE    32U
#define CRC_DEMO_MAX_SIZE      64U

static const uint8_t crc_demo_image[CRC_DEMO_IMAGE_SIZE] = {
    0x10U, 0x32U, 0x54U, 0x76U, 0x98U, 0xBAU, 0xDCU, 0xFEU,
    0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
    0x55U, 0xAAU, 0x5AU, 0xA5U, 0x11U, 0x22U, 0x33U, 0x44U,
    0x77U, 0x88U, 0x99U, 0x00U, 0xDEU, 0xADU, 0xBEU, 0xEFU
};

static const char *crc_demo_status_name(int rc)
{
    switch (rc) {
    case 0:
        return "PASS";
    case -EIO:
        return "CRC_MISMATCH";
    case -EMSGSIZE:
        return "SIZE_MISMATCH";
    case -EFBIG:
        return "IMAGE_TOO_LARGE";
    default:
        return "ERROR";
    }
}

static void crc_demo_print_result(const char *name,
                                  int rc,
                                  int expected_rc,
                                  const crc_image_result_t *result,
                                  uint32_t *total,
                                  uint32_t *passed)
{
    const char *verdict = (rc == expected_rc) ? "OK" : "UNEXPECTED";

    (*total)++;
    if (rc == expected_rc) {
        (*passed)++;
    }

    printf("[%s] %s | verdict=%s\n", name, crc_demo_status_name(rc), verdict);
    if (result != NULL) {
        printf("  actual=%u expected=%u calc_crc=0x%08X size_valid=%s crc_valid=%s\n",
               (unsigned)result->actual_size,
               (unsigned)result->expected_size,
               result->calculated_crc,
               result->size_valid ? "yes" : "no",
               result->crc_valid ? "yes" : "no");
    }
}

static int crc_demo_validate_case(const uint8_t *image,
                                  size_t actual_size,
                                  size_t expected_size,
                                  size_t max_size,
                                  uint32_t expected_crc,
                                  crc_image_result_t *result)
{
    crc_image_desc_t desc;

    desc.image = image;
    desc.actual_size = actual_size;
    desc.expected_size = expected_size;
    desc.max_size = max_size;
    desc.channel = CRC_DEMO_CHANNEL;
    desc.expected_crc = expected_crc;

    return crc_api_validate(&desc, result);
}

static void cmd_crc_demo(const char *args)
{
    uint32_t golden_crc = 0U;
    uint32_t total = 0U;
    uint32_t passed = 0U;
    int rc;
    crc_image_result_t result;
    uint8_t corrupt_image[CRC_DEMO_IMAGE_SIZE];
    (void)args;

    rc = crc_api_calculate(crc_demo_image,
                           sizeof(crc_demo_image),
                           CRC_DEMO_CHANNEL,
                           &golden_crc);
    if (rc != 0) {
        printf("CRC calculate failed: %d\n", rc);
        return;
    }

    printf("\n==== CRC API DEMO ====\n");
    printf("  channel    : 0x%016llX\n", (unsigned long long)CRC_DEMO_CHANNEL);
    printf("  image size : %u bytes\n", (unsigned)sizeof(crc_demo_image));
    printf("  golden CRC : 0x%08X\n", golden_crc);
    printf("======================\n");

    rc = crc_demo_validate_case(crc_demo_image,
                                sizeof(crc_demo_image),
                                sizeof(crc_demo_image),
                                CRC_DEMO_MAX_SIZE,
                                golden_crc,
                                &result);
    crc_demo_print_result("success", rc, 0, &result, &total, &passed);

    (void)memcpy(corrupt_image, crc_demo_image, sizeof(corrupt_image));
    corrupt_image[7] ^= 0x5AU;
    rc = crc_demo_validate_case(corrupt_image,
                                sizeof(corrupt_image),
                                sizeof(corrupt_image),
                                CRC_DEMO_MAX_SIZE,
                                golden_crc,
                                &result);
    crc_demo_print_result("corrupt", rc, -EIO, &result, &total, &passed);

    rc = crc_demo_validate_case(crc_demo_image,
                                sizeof(crc_demo_image) - 5U,
                                sizeof(crc_demo_image),
                                CRC_DEMO_MAX_SIZE,
                                golden_crc,
                                &result);
    crc_demo_print_result("partial", rc, -EMSGSIZE, &result, &total, &passed);

    rc = crc_demo_validate_case(crc_demo_image,
                                CRC_DEMO_MAX_SIZE + 1U,
                                CRC_DEMO_MAX_SIZE + 1U,
                                CRC_DEMO_MAX_SIZE,
                                golden_crc,
                                &result);
    crc_demo_print_result("large", rc, -EFBIG, &result, &total, &passed);

    printf("\n==== CRC DEMO SUMMARY ====\n");
    printf("  executed : %u case(s)\n", total);
    printf("  passed   : %u case(s)\n", passed);
    printf("  failed   : %u case(s)\n", total - passed);
    printf("==========================\n");
}

static void register_crc_commands(void)
{
    cli_register_command("crc_selftest", cmd_crc_demo);
}

APP_REGISTER(register_crc_commands)


