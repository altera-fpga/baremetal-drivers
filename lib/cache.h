/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: cache.h
 *
 * Cache management abstraction driver interface for the SoCFPGA bare-metal 
 * software stack.
 *
 * These functions provide the low-level wrappers required to manage data 
 * coherency between the processor's L1/L2 caches and the main system memory. 
 * Proper usage is mandatory when performing DMA transfers or communicating with 
 * peripheral hardware that does not snoop the processor cache.
 *
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#include <stddef.h>

/* Section: Functions */

/* Function: cache_force_write_back
 *
 * Performs a Cache Clean (Write-Back) operation on the specified memory region.
 *
 * This function iterates through the cache lines covering [addr, addr + sz] 
 * and forces dirty data to be written out to the Point of Coherency (PoC) in 
 * main memory. This is required before a DMA controller reads from HPS-managed 
 * memory to ensure the DMA reads the most recent data.
 *
 * Parameters:
 *
 * addr - The starting virtual address of the memory region.
 * sz   - The size of the memory region in bytes.
 */
void cache_force_write_back(void *addr, size_t sz);

/* Function: cache_force_invalidate
 *
 * Performs a Cache Invalidate operation on the specified memory region.
 *
 * This function marks the cache lines covering [addr, addr + sz] as invalid. 
 * This forces the processor to discard any cached copies and fetch fresh data 
 * from main memory on the next read access. This is essential after a DMA 
 * device writes data to memory to ensure the processor does not read stale 
 * data from the cache.
 *
 * Parameters:
 *
 * addr - The starting virtual address of the memory region.
 * sz   - The size of the memory region in bytes.
 */
void cache_force_invalidate(void *addr, size_t sz);

/* Function: cache_flush
 *
 * Performs a combined Clean and Invalidate operation on the specified memory region.
 *
 * This function ensures that any dirty data is written back to main memory and 
 * subsequently clears the cache lines. This guarantees total synchronization 
 * between the cache and main memory, ensuring the cache is "clean" and empty 
 * for the specified range.
 *
 * Parameters:
 *
 * addr - The starting virtual address of the memory region.
 * sz   - The size of the memory region in bytes.
 */
void cache_flush(void *addr, size_t sz);

#endif /* __SOCFPGA_CACHE_H__ */