/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_crc.c
 *
 * CRC source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "socfpga_crc.h"

static uint32_t socfpga_crc_accumulate(uint32_t crc_in,
                                       uint64_t channel_word,
                                       uint64_t data_word)
{
    uint32_t crc_temp = crc_in;
    uint32_t i;

    for (i = 0U; i < 128U; ++i)
    {
        uint32_t data_bit;

        if (i < 64U)
        {
            data_bit = (uint32_t)((channel_word >> i) & 0x1U);
        }
        else
        {
            data_bit = (uint32_t)((data_word >> (i - 64U)) & 0x1U);
        }

        if ((((crc_temp >> 31U) & 0x1U) ^ data_bit) != 0U)
        {
            crc_temp = (crc_temp << 1U) ^ SOCFPGA_CRC_POLYNOMIAL;
        }
        else
        {
            crc_temp = (crc_temp << 1U) & 0xFFFFFFFFU;
        }

        crc_temp &= 0xFFFFFFFFU;
    }

    return crc_temp;
}

void socfpga_crc_init(socfpga_crc_ctx_t *ctx, uint64_t channel)
{
    if (ctx == NULL)
    {
        return;
    }

    ctx->channel = channel;
    ctx->crc = SOCFPGA_CRC_INIT_VALUE;
}

void socfpga_crc_reset(socfpga_crc_ctx_t *ctx)
{
    if (ctx == NULL)
    {
        return;
    }

    ctx->crc = SOCFPGA_CRC_INIT_VALUE;
}

void socfpga_crc_set_channel(socfpga_crc_ctx_t *ctx, uint64_t channel)
{
    if (ctx == NULL)
    {
        return;
    }

    ctx->channel = channel;
}

void socfpga_crc_update_word(socfpga_crc_ctx_t *ctx, uint64_t data_word)
{
    if (ctx == NULL)
    {
        return;
    }

    ctx->crc = socfpga_crc_accumulate(ctx->crc, ctx->channel, data_word);
}

void socfpga_crc_update_buffer(socfpga_crc_ctx_t *ctx,
                               const uint8_t *data,
                               size_t len)
{
    size_t offset;

    if ((ctx == NULL) || ((data == NULL) && (len != 0U)))
    {
        return;
    }

    for (offset = 0U; offset < len; offset += sizeof(uint64_t))
    {
        uint64_t word = 0U;
        size_t chunk = len - offset;

        if (chunk > sizeof(uint64_t))
        {
            chunk = sizeof(uint64_t);
        }

        /*
         * The Simics reference model treats out-of-range bytes as zero.
         * Zero padding the tail chunk preserves that behaviour for partial
         * 64-bit words.
         */
        (void)memcpy(&word, data + offset, chunk);
        socfpga_crc_update_word(ctx, word);
    }
}

uint32_t socfpga_crc_get(const socfpga_crc_ctx_t *ctx)
{
    if (ctx == NULL)
    {
        return 0U;
    }

    return ctx->crc;
}
