/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>

#include "ecc_api.h"
#include "socfpga_ecc.h"

/*
 * Default syndrome / command pair for DDR ECC injection helpers.
 * These match the register usage in ATF's intel_inject_io96b_ecc_err():
 *   syndrome -> IOSSM_CMD_PARAM
 *   command  -> IOSSM_CMD_TRIG_OP
 *
 * The single-bit syndrome programs one error bit position; the double-bit
 * syndrome programs two adjacent bits which IO96B reports as DBE.
 */
#define ECC_API_DDR_SBE_SYNDROME    0x00000001U
#define ECC_API_DDR_SBE_COMMAND     0x00000F4U  /* IOSSM_LL_SING_BIT_ERR_PARAM */
#define ECC_API_DDR_DBE_SYNDROME    0x00000003U
#define ECC_API_DDR_DBE_COMMAND     0x0000003U  /* IOSSM_LL_DBL_BIT_ERR_PARAM  */

static int32_t map_driver_rc(int32_t rc)
{
    if (rc == 0) {
        return ECC_API_OK;
    }
    if (rc == -22 /* -EINVAL */) {
        return ECC_API_EINVAL;
    }
    if (rc == -5 /* -EIO */) {
        return ECC_API_ETIMEOUT;
    }
    return ECC_API_ERROR;
}

int32_t ecc_api_init(void)
{
    return map_driver_rc(socfpga_ecc_init());
}

int32_t ecc_api_deinit(void)
{
    return map_driver_rc(socfpga_ecc_deinit());
}

static int ecc_api_block_mask_ok(uint32_t block_mask)
{
    return (block_mask & ~(uint32_t)ECC_API_BLOCK_MASK_ALL_HPS) == 0U;
}

static int ecc_api_counter_block_ok(uint32_t block)
{
    return (block == ECC_API_BLOCK_OCRAM) || (block == ECC_API_BLOCK_DDR);
}

int32_t ecc_api_enable(uint32_t block_mask)
{
    if ((block_mask == 0U) || !ecc_api_block_mask_ok(block_mask)) {
        return ECC_API_EINVAL;
    }
    return map_driver_rc(socfpga_ecc_enable_blocks(block_mask));
}

int32_t ecc_api_disable(uint32_t block_mask)
{
    if (!ecc_api_block_mask_ok(block_mask)) {
        return ECC_API_EINVAL;
    }
    return map_driver_rc(socfpga_ecc_disable_blocks(block_mask));
}

int32_t ecc_api_inject_block(uint32_t block, uint32_t err_type)
{
    if (block != ECC_API_BLOCK_OCRAM) {
        return ECC_API_EINVAL;
    }
    return map_driver_rc(socfpga_ecc_inject_block_err(block, err_type));
}

int32_t ecc_api_inject_ddr(uint32_t syndrome, uint32_t command)
{
    return map_driver_rc(socfpga_ecc_inject_ddr_err(syndrome, command));
}

int32_t ecc_api_inject_ddr_sbe(void)
{
    return ecc_api_inject_ddr(ECC_API_DDR_SBE_SYNDROME,
                              ECC_API_DDR_SBE_COMMAND);
}

int32_t ecc_api_inject_ddr_dbe(void)
{
    return ecc_api_inject_ddr(ECC_API_DDR_DBE_SYNDROME,
                              ECC_API_DDR_DBE_COMMAND);
}

int32_t ecc_api_get_sbe_count(uint32_t block)
{
    int32_t rc;

    if (!ecc_api_counter_block_ok(block)) {
        return ECC_API_EINVAL;
    }
    rc = socfpga_ecc_get_sbe_count(block);
    if (rc < 0) {
        return ECC_API_EINVAL;
    }
    return rc;
}

int32_t ecc_api_get_dbe_count(uint32_t block)
{
    int32_t rc;

    if (!ecc_api_counter_block_ok(block)) {
        return ECC_API_EINVAL;
    }
    rc = socfpga_ecc_get_dbe_count(block);
    if (rc < 0) {
        return ECC_API_EINVAL;
    }
    return rc;
}

int32_t ecc_api_get_hw_sbe_count(uint32_t block)
{
    int32_t rc;

    if (block != ECC_API_BLOCK_OCRAM) {
        return ECC_API_EINVAL;
    }
    rc = socfpga_ecc_get_hw_sbe_count(block);
    if (rc < 0) {
        return ECC_API_EINVAL;
    }
    return rc;
}

int32_t ecc_api_poll_status(uint32_t *out_serr_bits, uint32_t *out_derr_bits)
{
    return socfpga_ecc_poll_status(out_serr_bits, out_derr_bits);
}

int32_t ecc_api_clear_counters(uint32_t block)
{
    if ((block != ECC_API_BLOCK_NONE) && !ecc_api_counter_block_ok(block)) {
        return ECC_API_EINVAL;
    }
    return map_driver_rc(socfpga_ecc_clear_counters(block));
}

int32_t ecc_api_set_callback(ecc_api_callback_t callback)
{
    /*
     * The driver-level and API-level prototypes are identical
     * (uint32_t block, uint32_t err_type). The cast is safe.
     */
    return map_driver_rc(
        socfpga_ecc_set_callback((socfpga_ecc_callback_t)callback));
}

uint32_t ecc_api_get_serr_status(void)
{
    return socfpga_ecc_get_sysmgr_serr_status();
}

uint32_t ecc_api_get_derr_status(void)
{
    return socfpga_ecc_get_sysmgr_derr_status();
}

const char *ecc_api_block_name(uint32_t block)
{
    switch (block) {
    case ECC_API_BLOCK_OCRAM:      return "OCRAM";
    case ECC_API_BLOCK_DDR:        return "DDR";
    default:                       return "UNKNOWN";
    }
}
