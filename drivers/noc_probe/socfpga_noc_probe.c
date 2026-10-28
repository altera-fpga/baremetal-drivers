/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_noc_probe.c
 *
 * NoC Probe source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_noc_probe.h"
#include "socfpga_noc_probe_ll.h"
#include "socfpga_noc_probe_reg.h"

static uint32_t noc_probe_block_base(socfpga_noc_probe_block_t block)
{
    switch (block) {
    case SOCFPGA_NOC_PROBE_CCU:
        return NOC_PROBE_CCU_PROBE_BASE;
    case SOCFPGA_NOC_PROBE_SOC2FPGA:
        return NOC_PROBE_SOC2FPGA_PROBE_BASE;
    case SOCFPGA_NOC_PROBE_IO:
        return NOC_PROBE_IO_PROBE_BASE;
    default:
        return 0U;
    }
}

int32_t socfpga_noc_probe_read_id(uint32_t base_address, uint32_t *core_id)
{
    if ((base_address == 0U) || (core_id == NULL)) {
        return -EINVAL;
    }

    *core_id = socfpga_noc_probe_ll_read(base_address,
                                         NOC_PROBE_ATBENDPOINT_ID_COREID);
    return 0;
}

int32_t socfpga_noc_probe_error_logger_enable(uint32_t base_address,
                                              bool enable)
{
    if (base_address == 0U) {
        return -EINVAL;
    }
    socfpga_noc_probe_ll_write(base_address,
                               NOC_PROBE_ERRORLOGGER0_BASE +
                               NOC_PROBE_ERRORLOGGER_FAULTEN,
                               enable ? 1U : 0U);
    return 0;
}

int32_t socfpga_noc_probe_error_is_valid(uint32_t base_address, bool *valid)
{
    uint32_t reg;

    if ((base_address == 0U) || (valid == NULL)) {
        return -EINVAL;
    }
    reg = socfpga_noc_probe_ll_read(base_address,
                                    NOC_PROBE_ERRORLOGGER0_BASE +
                                    NOC_PROBE_ERRORLOGGER_ERRVLD);
    *valid = ((reg & NOC_PROBE_ERRORLOGGER_ERRVLD_MASK) != 0U);
    return 0;
}

int32_t socfpga_noc_probe_error_read(uint32_t base_address,
                                     socfpga_noc_probe_error_log_t *log)
{
    if ((base_address == 0U) || (log == NULL)) {
        return -EINVAL;
    }
    log->errlog0 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG0);
    log->errlog1 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG1);
    log->errlog3 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG3);
    log->errlog4 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG4);
    log->errlog5 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG5);
    log->errlog6 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG6);
    log->errlog7 = socfpga_noc_probe_ll_read(base_address, NOC_PROBE_ERRORLOGGER0_BASE + NOC_PROBE_ERRORLOGGER_ERRLOG7);
    return 0;
}

int32_t socfpga_noc_probe_error_clear(uint32_t base_address)
{
    if (base_address == 0U) {
        return -EINVAL;
    }
    socfpga_noc_probe_ll_write(base_address,
                               NOC_PROBE_ERRORLOGGER0_BASE +
                               NOC_PROBE_ERRORLOGGER_ERRCLR,
                               NOC_PROBE_ERRORLOGGER_ERRCLR_MASK);
    return 0;
}

int32_t socfpga_noc_probe_counter_set_source(uint32_t base_address,
                                             socfpga_noc_probe_block_t block,
                                             uint32_t counter,
                                             uint32_t source)
{
    uint32_t block_ofst = noc_probe_block_base(block);
    uint32_t offset;

    if ((base_address == 0U) || (block_ofst == 0U) || (counter >= 4U)) {
        return -EINVAL;
    }
    offset = block_ofst + NOC_PROBE_PROBE_COUNTER_BASE +
             (counter * NOC_PROBE_PROBE_COUNTER_STRIDE) +
             NOC_PROBE_PROBE_COUNTER_SRC;
    socfpga_noc_probe_ll_write(base_address, offset, source);
    return 0;
}

int32_t socfpga_noc_probe_counter_get_value(uint32_t base_address,
                                            socfpga_noc_probe_block_t block,
                                            uint32_t counter,
                                            uint32_t *value)
{
    uint32_t block_ofst = noc_probe_block_base(block);
    uint32_t offset;

    if ((base_address == 0U) || (block_ofst == 0U) ||
        (counter >= 4U) || (value == NULL)) {
        return -EINVAL;
    }
    offset = block_ofst + NOC_PROBE_PROBE_COUNTER_BASE +
             (counter * NOC_PROBE_PROBE_COUNTER_STRIDE) +
             NOC_PROBE_PROBE_COUNTER_VAL;
    *value = socfpga_noc_probe_ll_read(base_address, offset);
    return 0;
}
