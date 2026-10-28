/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "errno.h"
#include "crc_api.h"
#include "socfpga_crc.h"

int crc_api_calculate(const uint8_t *image,
                      size_t image_size,
                      uint64_t channel,
                      uint32_t *crc_out)
{
    socfpga_crc_ctx_t ctx;

    if ((crc_out == NULL) || ((image == NULL) && (image_size != 0U)))
    {
        return -EINVAL;
    }

    socfpga_crc_init(&ctx, channel);
    socfpga_crc_update_buffer(&ctx, image, image_size);
    *crc_out = socfpga_crc_get(&ctx);

    return 0;
}

int crc_api_validate(const crc_image_desc_t *desc,
                     crc_image_result_t *result)
{
    int rc;
    uint32_t calculated_crc = 0U;

    if ((desc == NULL) || (result == NULL))
    {
        return -EINVAL;
    }

    (void)memset(result, 0, sizeof(*result));
    result->actual_size = desc->actual_size;
    result->expected_size = desc->expected_size;

    if ((desc->image == NULL) && (desc->actual_size != 0U))
    {
        return -EINVAL;
    }

    if ((desc->max_size != 0U) && (desc->actual_size > desc->max_size))
    {
        return -EFBIG;
    }

    if (desc->actual_size != desc->expected_size)
    {
        return -EMSGSIZE;
    }

    result->size_valid = 1;

    rc = crc_api_calculate(desc->image,
                           desc->actual_size,
                           desc->channel,
                           &calculated_crc);
    if (rc != 0)
    {
        return rc;
    }

    result->calculated_crc = calculated_crc;

    if (calculated_crc != desc->expected_crc)
    {
        return -EIO;
    }

    result->crc_valid = 1;
    return 0;
}

