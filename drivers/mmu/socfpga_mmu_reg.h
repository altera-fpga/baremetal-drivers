/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_mmu_reg.h
 *
 * MMU register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_MMU_REG_H
#define SOCFPGA_MMU_REG_H

#define MMU_DESC_VALID_MASK              0x0000000000000001ULL
#define MMU_DESC_VALID_POS               0U
#define MMU_DESC_TABLE_MASK              0x0000000000000002ULL
#define MMU_DESC_TABLE_POS               1U
#define MMU_DESC_ATTR_INDEX_MASK         0x000000000000001CULL
#define MMU_DESC_ATTR_INDEX_POS          2U
#define MMU_DESC_NS_MASK                 0x0000000000000020ULL
#define MMU_DESC_NS_POS                  5U
#define MMU_DESC_AP_MASK                 0x00000000000000C0ULL
#define MMU_DESC_AP_POS                  6U
#define MMU_DESC_SH_MASK                 0x0000000000000300ULL
#define MMU_DESC_SH_POS                  8U
#define MMU_DESC_AF_MASK                 0x0000000000000400ULL
#define MMU_DESC_AF_POS                  10U
#define MMU_DESC_NG_MASK                 0x0000000000000800ULL
#define MMU_DESC_NG_POS                  11U
#define MMU_DESC_OUTPUT_ADDR_MASK        0x0000FFFFFFFFF000ULL
#define MMU_DESC_OUTPUT_ADDR_POS         12U
#define MMU_DESC_PXN_MASK                0x0020000000000000ULL
#define MMU_DESC_PXN_POS                 53U
#define MMU_DESC_UXN_MASK                0x0040000000000000ULL
#define MMU_DESC_UXN_POS                 54U

#define MMU_SCTLR_M_MASK                 0x00000001U
#define MMU_SCTLR_M_POS                  0U
#define MMU_SCTLR_C_MASK                 0x00000004U
#define MMU_SCTLR_C_POS                  2U
#define MMU_SCTLR_I_MASK                 0x00001000U
#define MMU_SCTLR_I_POS                  12U

#endif /* SOCFPGA_MMU_REG_H */
