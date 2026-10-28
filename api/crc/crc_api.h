/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: crc_api.h
 *
 * Software CRC calculation over a memory buffer and size-and-checksum
 * validation for an image descriptor. The channel value is used as an input
 * to the CRC calculation; callers must use the same value when validating.
 */

#ifndef CRC_API_H
#define CRC_API_H

#include <stddef.h>
#include <stdint.h>

/* Struct: crc_image_desc_t
 *
 * Image description and expected values used by crc_api_validate().
 *
 * Fields:
 *
 *    image - Image bytes to validate. May be NULL only when actual_size is zero.
 *    actual_size - Number of bytes present in image.
 *    expected_size - Required image size used for the size check.
 *    max_size - Optional upper size limit; zero disables this limit.
 *    channel - Value passed to the CRC calculation context; its meaning is defined by the CRC driver.
 *    expected_crc - CRC value that the calculated checksum must match.
 */
typedef struct {
    const uint8_t *image;
    size_t actual_size;
    size_t expected_size;
    size_t max_size;
    uint64_t channel;
    uint32_t expected_crc;
} crc_image_desc_t;

/* Struct: crc_image_result_t
 *
 * Validation result filled by crc_api_validate(). The structure is cleared on entry, and fields written before a failed check remain available to the caller.
 *
 * Fields:
 *
 *    calculated_crc - CRC calculated from the image when CRC calculation is reached.
 *    actual_size - Copy of crc_image_desc_t.actual_size.
 *    expected_size - Copy of crc_image_desc_t.expected_size.
 *    size_valid - Nonzero only when the actual and expected sizes match and the optional maximum-size check passes.
 *    crc_valid - Nonzero only when calculated_crc equals the expected CRC.
 */
typedef struct {
    uint32_t calculated_crc;
    size_t actual_size;
    size_t expected_size;
    int size_valid;
    int crc_valid;
} crc_image_result_t;

/* Function: crc_api_calculate
 *
 * Compute the software CRC over image[0 .. image_size).
 *
 * A NULL image is accepted only when image_size is 0. The stored value is then the CRC of an empty buffer.
 *
 * Parameters:
 *
 *    image - Bytes to checksum. NULL only when image_size is 0.
 *    image_size - Number of bytes.
 *    channel - Value passed to the CRC context. Meaning is defined by the CRC driver.
 *    crc_out - Receives the CRC. Must be non-NULL.
 *
 * Returns:
 *
 *    0 on success. -EINVAL when crc_out is NULL, or when image is NULL and image_size is not 0.
 */
int crc_api_calculate(const uint8_t *image,
                      size_t image_size,
                      uint64_t channel,
                      uint32_t *crc_out);

/* Function: crc_api_validate
 *
 * Check actual_size against expected_size and max_size, then compare the CRC with expected_crc.
 *
 * On entry, result is cleared. actual_size and expected_size are copied before the checks. size_valid is set only when the sizes match. If the CRC is computed, calculated_crc is stored even when it does not match. crc_valid is set only when the CRC matches.
 *
 * Parameters:
 *
 *    desc - Image descriptor. Must be non-NULL.
 *    result - Receives the check outcome. Must be non-NULL.
 *
 * Returns:
 *
 *    0 when the size and CRC both match. -EINVAL for a NULL pointer, or a NULL image with a non-zero actual_size. -EFBIG when max_size is non-zero and actual_size exceeds it. -EMSGSIZE when actual_size does not equal expected_size. -EIO when the CRC does not match.
 */
int crc_api_validate(const crc_image_desc_t *desc,
                     crc_image_result_t *result);

#endif /* CRC_API_H */
