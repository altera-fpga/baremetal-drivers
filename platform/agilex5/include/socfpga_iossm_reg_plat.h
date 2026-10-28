/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_iossm_reg_plat.h
 *
 * Agilex5 platform IOSSM register definitions for the SoCFPGA
 * bare-metal software stack.
 *
 */

#ifndef SOCFPGA_IOSSM_REG_PLAT_H
#define SOCFPGA_IOSSM_REG_PLAT_H


/*
 * Agilex5 IOSSM hardware instance base addresses
 */
#define IOSSM0_BASE_ADDR    0x18400000U   /* Base address of IOSSM instance 0 */
#define IOSSM1_BASE_ADDR    0x18800000U   /* Base address of IOSSM instance 1 */

/*
 * Agilex5 DDR memory region
 * Agilex5 supports up to 4 GB of DDR starting at the same physical base.
 */
#define IOSSM_DDR_BASE_ADDR    0x0000000080000000ULL  /* Agilex5 DDR start address */
#define IOSSM_DDR_SIZE         0x0000000100000000ULL  /* Agilex5 DDR size: 4 GB    */
#define IOSSM_DDR_END_ADDR     (IOSSM_DDR_BASE_ADDR + IOSSM_DDR_SIZE - 1ULL)

/*
 * ECC error status and data registers (offsets from instance base)
 */
#define IOSSM_ECC_ERROR_STATUS       0x300U
#define IOSSM_ECC_COUNT_MASK         0xFFU

#define IOSSM_ECC_ERR_DATA_START     0x310U
#define IOSSM_ECC_GET_ERR_TYPE(idx)      (IOSSM_ECC_ERR_DATA_START + ((idx) * 8U))
#define IOSSM_ECC_ERR_TYP_FIELD(data)   (((data) >> 6U) & 0xFU)
#define IOSSM_ECC_GET_ERR_OFFSET(idx)   (IOSSM_ECC_ERR_DATA_START + ((idx) * 8U) + 4U)

/*
 * Calibration status register
 */
#define CALIBRATION_STAT_REG_OFFSET    0x400U

/*
 * Command parameter registers (param6  param0, descending offsets)
 */
#define CMD_PARAM0_REG_OFFSET    0x438U
#define CMD_PARAM1_REG_OFFSET    0x434U
#define CMD_PARAM2_REG_OFFSET    0x430U
#define CMD_PARAM3_REG_OFFSET    0x42CU
#define CMD_PARAM4_REG_OFFSET    0x428U
#define CMD_PARAM5_REG_OFFSET    0x424U
#define CMD_PARAM6_REG_OFFSET    0x420U

/*
 * Command request and response registers
 */
#define CMD_REQ_REG_OFFSET    0x43CU
#define CMD_RESP0_REG_OFF     0x458U
#define CMD_RESP1_REG_OFF     0x454U
#define CMD_RESP2_REG_OFF     0x450U
#define RESP_STAT_REG_OFF     0x45CU

#endif /* SOCFPGA_IOSSM_REG_PLAT_H */
