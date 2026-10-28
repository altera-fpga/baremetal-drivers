/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: mmio.h
 *
 * Common hardware abstraction driver interface for the SoCFPGA bare-metal 
 * software stack.
 *
 * This header defines the fundamental Memory-Mapped I/O (MMIO) primitives 
 * used across all drivers. These accessors utilize the `volatile` keyword 
 * to ensure that the compiler treats every memory reference as a distinct 
 * hardware interaction, preventing unwanted optimizations or reordering of 
 * peripheral access cycles.
 *
 */

#ifndef __MMIO_H__
#define __MMIO_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Section: Macros */

/* Group: Register Access Wrappers
 * Convenience macros for standardized 16/32/64-bit register access.
 */
#define WR_REG16(address, val)    io_write16(address, val)
#define RD_REG16(address)         io_read16(address)

#define WR_REG32(address, val)    io_write32(address, val)
#define RD_REG32(address)         io_read32(address)

#define WR_REG64(address, val)    io_write64(address, val)
#define RD_REG64(address)         io_read64(address)


/* Section: Functions */

/* Function: io_write16
 * Performs a 16-bit volatile store to the specified physical memory address.
 */
static inline void io_write16(uint32_t address, uint32_t value) {
    volatile uint16_t *paddress = (volatile uint16_t *)((uint64_t)address);
    *paddress = (uint16_t)value;
}

/* Function: io_read16
 * Performs a 16-bit volatile load from the specified physical memory address.
 */
static inline uint32_t io_read16(uint32_t address) {
    volatile uint16_t *paddress = (volatile uint16_t *)((uint64_t)address);
    return (uint32_t)(*paddress);
}

/* Function: io_write32
 * Performs a 32-bit volatile store to the specified physical memory address.
 */
static inline void io_write32(uint32_t address, uint32_t value) {
    volatile uint32_t *paddress = (volatile uint32_t *)((uint64_t)address);
    *paddress = value;
}

/* Function: io_read32
 * Performs a 32-bit volatile load from the specified physical memory address.
 */
static inline uint32_t io_read32(uint32_t address) {
    volatile uint32_t *paddress = (volatile uint32_t *)((uint64_t)address);
    return *paddress;
}

/* Function: io_write64
 * Performs a 64-bit volatile store to the specified physical memory address.
 */
static inline void io_write64(uint32_t address, uint64_t value) {
    volatile uint64_t *paddress = (volatile uint64_t *)((uint64_t)address);
    *paddress = value;
}

/* Function: io_read64
 * Performs a 64-bit volatile load from the specified physical memory address.
 */
static inline uint64_t io_read64(uint32_t address) {
    volatile uint64_t *paddress = (volatile uint64_t *)((uint64_t)address);
    return *paddress;
}

#endif /* __SOCFPGA_DEFINES_H__ */