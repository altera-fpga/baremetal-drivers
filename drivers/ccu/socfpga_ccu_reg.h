/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ccu_reg.h
 *
 * CCU register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_CCU_REG_H
#define SOCFPGA_CCU_REG_H

#define CCU_CAIU_IDR                    0x0000U
#define CCU_CAIU_FUIDR                  0x0004U
#define CCU_CAIU_TCR                    0x0040U
#define CCU_CAIU_TAR                    0x0044U
#define CCU_CAIU_UESR                   0x0108U
#define CCU_CAIU_UELR0                  0x010CU
#define CCU_CAIU_UELR1                  0x0110U
#define CCU_CAIU_CRTR                   0x0180U
#define CCU_CAIU_QOSCR                  0x0200U
#define CCU_CAIU_QOSSR                  0x0204U

/* Distributed memory interface cache-maintenance registers. */
#define CCU_DMI_STRIDE                  0x1000U
#define CCU_DMI_MAX_COUNT               2U
#define CCU_DMI0_USMCTCR                0x7300U
#define CCU_DMI0_USMCMCR                0x7340U
#define CCU_DMI0_USMCMAR                0x7344U

#define CCU_DMI_MNTOP_MASK              0x0000000FU
#define CCU_DMI_MNTOP_POS               0U
#define CCU_DMI_MNTOP_FLUSH_ALL         0x4U
#define CCU_DMI_ARRAY_ID_MASK           0x003F0000U
#define CCU_DMI_ARRAY_ID_POS            16U
#define CCU_DMI_ARRAY_ID_TAG            0x0U
#define CCU_DMI_ARRAY_ID_DATA           0x1U
#define CCU_DMI_CACHE_OP_DONE_MASK      0x00000001U

#define CCU_REGISTER_VALUE_MASK         0xFFFFFFFFU
#define CCU_REGISTER_VALUE_POS          0U

#endif /* SOCFPGA_CCU_REG_H */
