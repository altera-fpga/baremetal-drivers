/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_dma_ll.h
 *
 * DMA low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 * This header defines the low-level register map and hardware accessors for 
 * the DMA Controller (DMAC). These helpers facilitate raw MMIO access for 
 * channel configuration, descriptor chaining, and interrupt management.
 *
 */

#ifndef __SOCFPGA_DMA_LL_H__
#define __SOCFPGA_DMA_LL_H__

#include <stdint.h>
#include <stdbool.h>

/* Struct: dma_channel_reg_list
 *
 * Represents the memory-mapped register layout for a single DMA channel. 
 * This structure is packed and 64-byte aligned to ensure strict compatibility 
 * with the hardware register block alignment requirements.
 *
 * Fields:
 *
 * sar          - Source Address Register: The 64-bit physical address from which data is read.
 * dar          - Destination Address Register: The 64-bit physical address to which data is written.
 * block_ts     - Block Transfer Size: Configures the total number of data items for the transfer (bits [21:0] active).
 * llp          - Linked List Pointer: Pointer to the next descriptor in a scatter-gather chain (bits [63:6] active).
 * ctl          - Control Register: Contains burst size, addressing increments, and interrupt trigger enable bits.
 * chn_src_stat - Channel Source Status: Reports current hardware status of the source interface.
 * chn_dst_stat - Channel Destination Status: Reports current hardware status of the destination interface.
 * chn_llp_status - Channel LLP Status: The current state of the linked list processing.
 * reserved     - Reserved padding for register block alignment.
 */
struct dma_channel_reg_list
{
    uint64_t sar;
    uint64_t dar;
    uint64_t block_ts; 
    uint64_t llp;
    uint64_t ctl;
    uint32_t chn_src_stat;
    uint32_t chn_dst_stat;
    uint64_t chn_llp_status;
    uint64_t reserved;
} __attribute__((packed, aligned(64)));


/* Function: dma_ll_get_base_address
 *
 * Calculates the physical MMIO base address for a specific DMA hardware instance.
 *
 * Parameters:
 *
 * instance - The zero-indexed identifier of the DMA controller hardware.
 *
 * Returns:
 *
 * The 32-bit physical base address of the requested controller instance.
 */
uint32_t dma_ll_get_base_address(uint32_t instance);

/* Function: dma_ll_get_channel_offset
 *
 * Calculates the memory offset for a specific DMA channel relative to the 
 * controller base address.
 *
 * Parameters:
 *
 * channel - The zero-indexed identifier of the DMA channel.
 *
 * Returns:
 *
 * The byte offset representing the start of the channel's register block.
 */
uint32_t dma_ll_get_channel_offset(uint32_t channel);

/* Function: dma_ll_enable_controller
 *
 * Sets the enable bit in the global DMA Controller Configuration register.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 */
void dma_ll_enable_controller(uint32_t base_address);

/* Function: dma_ll_disable_controller
 *
 * Clears the enable bit in the global DMA Controller Configuration register.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 */
void dma_ll_disable_controller(uint32_t base_address);

/* Function: dma_ll_enable_channel
 *
 * Enables a specific DMA channel for transfer operations.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier to enable.
 */
void dma_ll_enable_channel(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_disable_channel
 *
 * Disables a specific DMA channel, immediately halting any ongoing transfers 
 * for that channel.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier to disable.
 */
void dma_ll_disable_channel(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_suspend_channel
 *
 * Sends a suspend request to a DMA channel, allowing it to complete the current 
 * burst before pausing.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier to suspend.
 */
void dma_ll_suspend_channel(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_abort_channel
 *
 * Forces an immediate abort of the DMA channel transfer, flushing the 
 * internal FIFOs.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier to abort.
 */
void dma_ll_abort_channel(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_is_channel_enabled
 *
 * Queries the Channel Enable Register to determine if the specified channel is active.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier.
 *
 * Returns:
 *
 * true if enabled; false otherwise.
 */
bool dma_ll_is_channel_enabled(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_is_channel_suspended
 *
 * Queries the Channel Suspension Register to determine if the specified channel is paused.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier.
 *
 * Returns:
 *
 * true if suspended; false otherwise.
 */
bool dma_ll_is_channel_suspended(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_is_channel_aborted
 *
 * Queries the Channel Abort Register to determine if the specified channel 
 * has triggered an abort.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 * channel      - The zero-indexed channel identifier.
 *
 * Returns:
 *
 * true if aborted; false otherwise.
 */
bool dma_ll_is_channel_aborted(uint32_t base_address, uint32_t channel);

/* Function: dma_ll_configure_channel
 *
 * Writes the configuration register for a DMA channel.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 * config    - The 64-bit control bitmask defining transfer width, priority, and handshaking.
 */
void dma_ll_configure_channel(uint32_t ch_offset, uint64_t config);

/* Function: dma_ll_setup_interrupts
 *
 * Configures the channel's interrupt enable mask. This enables the bits 
 * required for driver-side polling while ensuring the signal is not routed 
 * to the GIC (Global Interrupt Controller) if unnecessary.
 *
 * Parameters:
 *
 * ch_offset   - The byte offset of the specific DMA channel's register block.
 * status_mask - The bitmask of status flags (e.g., Block Transfer Complete, Error) to monitor.
 */
void dma_ll_setup_interrupts(uint32_t ch_offset, uint64_t status_mask);

/* Function: dma_ll_get_interrupt_status
 *
 * Reads the Interrupt Status Register for a specific DMA channel.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 *
 * Returns:
 *
 * The raw 64-bit status register value.
 */
uint64_t dma_ll_get_interrupt_status(uint32_t ch_offset);

/* Function: dma_ll_clear_interrupts
 *
 * Clears the specified interrupt flags by writing to the channel's 
 * interrupt clear register.
 *
 * Parameters:
 *
 * ch_offset      - The byte offset of the specific DMA channel's register block.
 * interrupt_mask - The bitmask of flags to clear.
 */
void dma_ll_clear_interrupts(uint32_t ch_offset, uint64_t interrupt_mask);

/* Function: dma_ll_write_sar
 *
 * Sets the Source Address Register (SAR) for a channel.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 * address   - The 64-bit physical source address.
 */
void dma_ll_write_sar(uint32_t ch_offset, uint64_t address);

/* Function: dma_ll_write_dar
 *
 * Sets the Destination Address Register (DAR) for a channel.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 * address   - The 64-bit physical destination address.
 */
void dma_ll_write_dar(uint32_t ch_offset, uint64_t address);

/* Function: dma_ll_write_block_ts
 *
 * Writes the Block Transfer Size register. Defines the total amount of data 
 * to be transferred in the current block.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 * size      - The number of data items to transfer.
 */
void dma_ll_write_block_ts(uint32_t ch_offset, uint64_t size);

/* Function: dma_ll_write_ctl
 *
 * Writes the Control (CTL) register for a channel, which defines transfer 
 * characteristics like burst length and address increment settings.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 * control   - The 64-bit configuration word.
 */
void dma_ll_write_ctl(uint32_t ch_offset, uint64_t control);

/* Function: dma_ll_write_llp
 *
 * Configures the Linked List Pointer (LLP) for scatter-gather operations.
 *
 * Parameters:
 *
 * ch_offset   - The byte offset of the specific DMA channel's register block.
 * llp_address - The 64-bit physical address of the next transfer descriptor.
 */
void dma_ll_write_llp(uint32_t ch_offset, uint64_t llp_address);

/* Function: dma_ll_read_llp
 *
 * Reads the current Linked List Pointer (LLP) value.
 *
 * Parameters:
 *
 * ch_offset - The byte offset of the specific DMA channel's register block.
 *
 * Returns:
 *
 * The current 64-bit physical address of the next descriptor.
 */
uint64_t dma_ll_read_llp(uint32_t ch_offset);

/* Function: dma_ll_enable_global_interrupts
 *
 * Enables global interrupt generation for the DMA controller.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 */
void dma_ll_enable_global_interrupts(uint32_t base_address);

/* Function: dma_ll_get_chenreg
 *
 * Retrieves the raw value of the Channel Enable Register (CHENREG), which 
 * indicates the enabled/disabled state of all channels for the controller.
 *
 * Parameters:
 *
 * base_address - The physical MMIO base address of the target DMA instance.
 *
 * Returns:
 *
 * The raw 64-bit enable register value.
 */
uint64_t dma_ll_get_chenreg(uint32_t base_address);

#endif /* __SOCFPGA_DMA_LL_H__ */