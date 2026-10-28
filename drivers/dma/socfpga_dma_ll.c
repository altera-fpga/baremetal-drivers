/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_dma_ll.c
 *
 * DMA source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>

#include "socfpga_dma_ll.h"
#include "socfpga_dma_reg_plat.h"
#include "socfpga_dma_reg.h"
#include "mmio.h"

/* DMA instance base addresses */
static const uint32_t dma_base_addresses[] = DMA_INSTANCE_BASE_ADDRESSES;

/* DMA channel offset addresses  */
static const uint32_t dma_channel_offsets[] = DMA_CHANNEL_OFFSETS;

/*
 * Get DMA instance base address
 */
uint32_t dma_ll_get_base_address(uint32_t instance)
{
    if (instance < (sizeof(dma_base_addresses) / sizeof(dma_base_addresses[0]))) {
        return dma_base_addresses[instance];
    }
    return 0U;
}

/*
 * Get DMA channel offset address
 */
uint32_t dma_ll_get_channel_offset(uint32_t channel)
{
    if (channel < (sizeof(dma_channel_offsets) / sizeof(dma_channel_offsets[0]))) {
        return dma_channel_offsets[channel];
    }
    return 0U;
}

/*
 * Enable DMA controller
 */
void dma_ll_enable_controller(uint32_t base_address)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CFGREG);
    val |= (DMA_DMAC_CFGREG_INT_EN_MASK | DMA_DMAC_CFGREG_DMAC_EN_MASK);
    WR_REG64(base_address + DMA_DMAC_CFGREG, val);
}

/*
 * Disable DMA controller
 */
void dma_ll_disable_controller(uint32_t base_address)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CFGREG);
    val &= ~DMA_DMAC_CFGREG_DMAC_EN_MASK;
    WR_REG64(base_address + DMA_DMAC_CFGREG, val);
}

/*
 * Enable DMA channel
 */
void dma_ll_enable_channel(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    val |= (1UL << (channel + CHENREG_CH_EN_POS));
    val |= (1UL << (channel + CHENREG_CH_EN_WE_POS));
    WR_REG64(base_address + DMA_DMAC_CHENREG, val);
}

/*
 * Disable DMA channel
 */
void dma_ll_disable_channel(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    val &= (~(1UL << channel));
    val |= (1UL << (channel + CHENREG_CH_EN_WE_POS));
    WR_REG64(base_address + DMA_DMAC_CHENREG, val);
}

/*
 * Suspend DMA channel
 */
void dma_ll_suspend_channel(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    val |= (1UL << (channel + CHENREG_CH_SUSP_WE_POS));
    val |= (1UL << (channel + CHENREG_CH_SUSP_POS));
    WR_REG64(base_address + DMA_DMAC_CHENREG, val);
}

/*
 * Abort DMA channel (immediate hardware abort via CHENREG abort bits)
 */
void dma_ll_abort_channel(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    val |= (1ULL << (channel + CHENREG_CH_ABORT_WE_POS));
    val |= (1ULL << (channel + CHENREG_CH_ABORT_POS));
    WR_REG64(base_address + DMA_DMAC_CHENREG, val);
}

/*
 * Check if channel is enabled
 */
bool dma_ll_is_channel_enabled(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    return ((val >> (CHENREG_CH_EN_POS + channel)) & 1U) == 1U;
}

/*
 * Check if channel is suspended
 */
bool dma_ll_is_channel_suspended(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    return ((val >> (CHENREG_CH_SUSP_POS + channel)) & 1U) == 1U;
}

/*
 * Check if channel is aborted
 */
bool dma_ll_is_channel_aborted(uint32_t base_address, uint32_t channel)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CHENREG);
    return ((val >> (CHENREG_CH_ABORT_POS + channel)) & 1U) == 1U;
}

/*
 * Configure DMA channel
 */
void dma_ll_configure_channel(uint32_t ch_offset, uint64_t config)
{
    (void)RD_REG64(ch_offset + DMA_CH_CFG2);
    WR_REG64(ch_offset + DMA_CH_CFG2, config);
}

/*
 * Enable channel interrupt status bits (for polling) and disable GIC signal
 */
void dma_ll_setup_interrupts(uint32_t ch_offset, uint64_t interrupt_mask)
{
    WR_REG64(ch_offset + DMA_CH_INTSTATUS_ENABLEREG, interrupt_mask);
    WR_REG64(ch_offset + DMA_CH_INTSIGNAL_ENABLEREG, interrupt_mask);
}

/*
 * Get channel interrupt status
 */
uint64_t dma_ll_get_interrupt_status(uint32_t ch_offset)
{
    return RD_REG64(ch_offset + DMA_CH_INTSTATUS);
}

/*
 * Clear channel interrupts
 */
void dma_ll_clear_interrupts(uint32_t ch_offset, uint64_t interrupt_mask)
{
    WR_REG64(ch_offset + DMA_CH_INTCLEARREG, interrupt_mask);
}

/*
 * Write channel source address
 */
void dma_ll_write_sar(uint32_t ch_offset, uint64_t address)
{
    WR_REG64(ch_offset + DMA_CH_SAR, address);
}

/*
 * Write channel destination address
 */
void dma_ll_write_dar(uint32_t ch_offset, uint64_t address)
{
    WR_REG64(ch_offset + DMA_CH_DAR, address);
}

/*
 * Write channel block transfer size
 */
void dma_ll_write_block_ts(uint32_t ch_offset, uint64_t size)
{
    WR_REG64(ch_offset + DMA_CH_BLOCK_TS, size & DMA_CH_BLOCK_TS_BLOCK_TS_MASK);
}

/*
 * Write channel control register
 */
void dma_ll_write_ctl(uint32_t ch_offset, uint64_t control)
{
    WR_REG64(ch_offset + DMA_CH_CTL, control);
}

/*
 * Write channel linked list pointer
 */
void dma_ll_write_llp(uint32_t ch_offset, uint64_t llp_address)
{
    (void)RD_REG64(ch_offset + DMA_CH_LLP);
    WR_REG64(ch_offset + DMA_CH_LLP, llp_address);
    (void)RD_REG64(ch_offset + DMA_CH_LLP);
}

/*
 * Read channel linked list pointer
 */
uint64_t dma_ll_read_llp(uint32_t ch_offset)
{
    return RD_REG64(ch_offset + DMA_CH_LLP);
}

/*
 * Enable controller global interrupts
 */
void dma_ll_enable_global_interrupts(uint32_t base_address)
{
    uint64_t val = RD_REG64(base_address + DMA_DMAC_CFGREG);
    val |= DMA_DMAC_CFGREG_INT_EN_MASK;
    WR_REG64(base_address + DMA_DMAC_CFGREG, val);
}

/*
 * Get channel enable register value
 */
uint64_t dma_ll_get_chenreg(uint32_t base_address)
{
    return RD_REG64(base_address + DMA_DMAC_CHENREG);
}
