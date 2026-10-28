/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_dma_reg_plat.h
 *
 * Agilex3 platform integration interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_DMA_REG_PLAT_H
#define SOCFPGA_DMA_REG_PLAT_H

/* Base addresses and channel topology */

#define SOCFPGA_DMAC0_BASE_ADDR            0x10DB0000U
#define SOCFPGA_DMAC1_BASE_ADDR            0x10DC0000U

#define SOCFPGA_DMAC_CHNL1_BASE_OFFSET     0x00000100U
#define SOCFPGA_DMAC_CHNL2_BASE_OFFSET     0x00000200U
#define SOCFPGA_DMAC_CHNL3_BASE_OFFSET     0x00000300U
#define SOCFPGA_DMAC_CHNL4_BASE_OFFSET     0x00000400U

#define SOCFPGA_DMA_INSTANCE_BASE_ADDRESSES  { SOCFPGA_DMAC0_BASE_ADDR, SOCFPGA_DMAC1_BASE_ADDR }
#define SOCFPGA_DMA_CHANNEL_OFFSETS          { SOCFPGA_DMAC_CHNL1_BASE_OFFSET, SOCFPGA_DMAC_CHNL2_BASE_OFFSET, \
                                               SOCFPGA_DMAC_CHNL3_BASE_OFFSET, SOCFPGA_DMAC_CHNL4_BASE_OFFSET }

/* Backward-compatible aliases. */
#define DMAC0_BASE_ADDR              SOCFPGA_DMAC0_BASE_ADDR
#define DMAC1_BASE_ADDR              SOCFPGA_DMAC1_BASE_ADDR
#define DMAC_CHNL1_BASE_ADDR         SOCFPGA_DMAC_CHNL1_BASE_OFFSET
#define DMAC_CHNL2_BASE_ADDR         SOCFPGA_DMAC_CHNL2_BASE_OFFSET
#define DMAC_CHNL3_BASE_ADDR         SOCFPGA_DMAC_CHNL3_BASE_OFFSET
#define DMAC_CHNL4_BASE_ADDR         SOCFPGA_DMAC_CHNL4_BASE_OFFSET
#define DMA_INSTANCE_BASE_ADDRESSES  SOCFPGA_DMA_INSTANCE_BASE_ADDRESSES
#define DMA_CHANNEL_OFFSETS          SOCFPGA_DMA_CHANNEL_OFFSETS

/*
 * BLOCK_TS hardware limit: 22-bit field, max 4,194,304 beats (0x400000).
 * DMA_MAX_BLOCK_TS is the fundamental ATF-style beat-count limit.
 * DMA_MAX_CHUNK_BYTES caps transfers at 1 MiB for practical descriptor sizing.
 */
#define SOCFPGA_DMA_MAX_BLOCK_TS     0x400000U  /* 22-bit BLOCK_TS: max 4,194,304 beats */
#define SOCFPGA_DMA_MAX_CHUNK_BYTES  0x100000U  /* 1 MiB practical cap */

/* Backward-compatible aliases. */
#define DMA_MAX_BLOCK_TS             SOCFPGA_DMA_MAX_BLOCK_TS
#define DMA_MAX_CHUNK_BYTES          SOCFPGA_DMA_MAX_CHUNK_BYTES

/* Error mask: data-path + LLI-walk + shadow-register errors */
#define SOCFPGA_DMA_ERROR_INT_MASK  (DMA_DATA_ERROR_INT_MASK                                    \
                                     | DMA_CH_INTSTATUS_LLI_RD_DEC_ERR_INTSTAT_MASK             \
                                     | DMA_CH_INTSTATUS_LLI_WR_DEC_ERR_INTSTAT_MASK             \
                                     | DMA_CH_INTSTATUS_LLI_RD_SLV_ERR_INTSTAT_MASK             \
                                     | DMA_CH_INTSTATUS_LLI_WR_SLV_ERR_INTSTAT_MASK             \
                                     | DMA_CH_INTSTATUS_SHADOWREG_OR_LLI_INVALID_ERR_INTSTAT_MASK)

/* Backward-compatible alias. */
#define DMA_ERROR_INT_MASK SOCFPGA_DMA_ERROR_INT_MASK

#endif /* SOCFPGA_DMA_REG_PLAT_H */
