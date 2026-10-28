/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_crc.h
 *
 * CRC driver interface. Each calculation keeps its own checksum in a
 * <socfpga_crc_ctx_t>.
 */

#ifndef SOCFPGA_CRC_H
#define SOCFPGA_CRC_H

#include <stddef.h>
#include <stdint.h>

/* Constant: SOCFPGA_CRC_INIT_VALUE
 * The default starting value used to initialize the CRC register.
 */
#define SOCFPGA_CRC_INIT_VALUE       0xFFFFFFFFU

/* Constant: SOCFPGA_CRC_POLYNOMIAL
 * The CRC generator polynomial (0x10000081) utilized by the hardware 
 * for computation.
 */
#define SOCFPGA_CRC_POLYNOMIAL       0x10000081U

/* Type: socfpga_crc_ctx_t
 *
 * A state-tracking structure that maintains the current CRC result and the 
 * associated hardware channel identifier. This must be passed to all CRC 
 * calculation functions to ensure correct continuation of the checksum stream.
 *
 * Fields:
 *
 * crc     - The rolling CRC sum (updated after each word or buffer processing).
 * channel - The specific hardware channel index assigned for the operation.
 */
typedef struct {
    uint32_t crc;
    uint64_t channel;
} socfpga_crc_ctx_t;


/* Function: socfpga_crc_init
 *
 * Initializes a CRC context structure and binds it to a specific hardware channel.
 *
 * Parameters:
 *
 * ctx     - Pointer to the CRC context structure to initialize.
 * channel - The hardware channel index to assign to this context.
 */
void socfpga_crc_init(socfpga_crc_ctx_t *ctx, uint64_t channel);

/* Function: socfpga_crc_reset
 *
 * Resets the CRC checksum within the context back to the initial value 
 * (<SOCFPGA_CRC_INIT_VALUE>).
 *
 * Parameters:
 *
 * ctx - Pointer to the CRC context to reset.
 */
void socfpga_crc_reset(socfpga_crc_ctx_t *ctx);

/* Function: socfpga_crc_set_channel
 *
 * Updates the hardware channel identifier within an existing CRC context.
 *
 * Parameters:
 *
 * ctx     - Pointer to the CRC context.
 * channel - The new hardware channel index.
 */
void socfpga_crc_set_channel(socfpga_crc_ctx_t *ctx, uint64_t channel);

/* Function: socfpga_crc_update_word
 *
 * Performs a single 64-bit word update to the rolling CRC checksum.
 *
 * Parameters:
 *
 * ctx       - Pointer to the CRC context.
 * data_word - The 64-bit data value to include in the calculation.
 */
void socfpga_crc_update_word(socfpga_crc_ctx_t *ctx, uint64_t data_word);

/* Function: socfpga_crc_update_buffer
 *
 * Streams a byte buffer into the CRC calculation engine, updating the context 
 * checksum incrementally.
 *
 * Parameters:
 *
 * ctx  - Pointer to the CRC context.
 * data - Pointer to the start of the source data buffer.
 * len  - The number of bytes to process.
 */
void socfpga_crc_update_buffer(socfpga_crc_ctx_t *ctx,
                               const uint8_t *data,
                               size_t len);

/* Function: socfpga_crc_get
 *
 * Returns the final calculated CRC value from the provided context.
 *
 * Parameters:
 *
 * ctx - Pointer to the CRC context.
 *
 * Returns:
 *
 * The current 32-bit CRC checksum value.
 */
uint32_t socfpga_crc_get(const socfpga_crc_ctx_t *ctx);

#endif /* SOCFPGA_CRC_H */