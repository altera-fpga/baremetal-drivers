/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: ddr_platform_compat.h
 *
 * Maps the TF-A helpers used by the ported Agilex 5 DDR driver onto this bare-metal stack.
 * The helpers are register access, logging, delays, bit masks, and the system-manager window.
 */
#ifndef __DDR_PLATFORM_COMPAT_H__
#define __DDR_PLATFORM_COMPAT_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "mmio.h"   /* RD_REG32 / WR_REG32 */

/* Constants: Bit and size helpers
 *
 * Small TF-A macros. Each one is compiled only when the name is not
 * already defined.
 *
 * BIT     - Bit n set, as (1UL << n).
 * GENMASK - Mask with bits l through h set.
 * SZ_1M   - 0x00100000 bytes (1 MB).
 * SZ_1G   - 0x40000000 bytes (1 GB).
 * LO      - Low 32 bits of a 64-bit value.
 * HI      - High 32 bits of a 64-bit value.
 */
#ifndef BIT
#define BIT(n)              (1UL << (n))
#endif

#ifndef GENMASK
#define GENMASK(h, l) \
	(((~0UL) - (1UL << (l)) + 1) & (~0UL >> (64 - 1 - (h))))
#endif

#ifndef SZ_1M
#define SZ_1M               0x00100000U
#endif
#ifndef SZ_1G
#define SZ_1G               0x40000000U
#endif

#ifndef LO
#define LO(x)               ((uint32_t)((x) & 0xffffffffULL))
#endif
#ifndef HI
#define HI(x)               ((uint32_t)(((x) >> 32) & 0xffffffffULL))
#endif

/* Function: mmio_read_32
 *
 * Reads one 32-bit register.
 * The address is cut down to 32 bits. DDR and IOSSM registers sit below 4 GB.
 *
 * Parameters:
 *   addr - Register address.
 *
 * Returns:
 *   The value returned by RD_REG32().
 */
static inline uint32_t mmio_read_32(uintptr_t addr)
{
	return RD_REG32((uint32_t)addr);
}

/* Function: mmio_write_32
 *
 * Writes one 32-bit register. The address is cut down to 32 bits.
 *
 * Parameters:
 *   addr  - Register address.
 *   value - Value to write.
 *
 * Returns:
 *   Nothing.
 */
static inline void mmio_write_32(uintptr_t addr, uint32_t value)
{
	WR_REG32((uint32_t)addr, value);
}

/* Function: mmio_setbits_32
 *
 * Sets the bits selected by mask. Other bits in the register stay as they are.
 *
 * Parameters:
 *   addr - Register address.
 *   mask - Bits to set.
 *
 * Returns:
 *   Nothing.
 */
static inline void mmio_setbits_32(uintptr_t addr, uint32_t mask)
{
	WR_REG32((uint32_t)addr, RD_REG32((uint32_t)addr) | mask);
}

/* Function: mmio_clrbits_32
 *
 * Clears the bits selected by mask. Other bits in the register stay as they are.
 *
 * Parameters:
 *   addr - Register address.
 *   mask - Bits to clear.
 *
 * Returns:
 *   Nothing.
 */
static inline void mmio_clrbits_32(uintptr_t addr, uint32_t mask)
{
	WR_REG32((uint32_t)addr, RD_REG32((uint32_t)addr) & ~mask);
}

/* Constants: Logging macros
 *
 * Stand-ins for the TF-A log calls.
 * NOTICE, WARN, and ERROR print with printf. INFO and VERBOSE do nothing,
 * so the polling traces stay off the console.
 *
 * NOTICE  - Prints with printf.
 * WARN    - Prints with printf.
 * ERROR   - Prints with printf.
 * INFO    - Does nothing.
 * VERBOSE - Does nothing.
 */
#define NOTICE(...)         printf(__VA_ARGS__)
#define WARN(...)           printf(__VA_ARGS__)
#define ERROR(...)          printf(__VA_ARGS__)
#define INFO(...)           ((void)0)
#define VERBOSE(...)        ((void)0)

/* Function: udelay
 *
 * Spins for us * 300 NOP instructions.
 * There is no hardware timer behind this delay. Callers use it as a
 * timeout backoff, so a longer wait is acceptable.
 *
 * Parameters:
 *   us - Delay count. Multiplied by 300 to get the spin count.
 *
 * Returns:
 *   Nothing.
 */
static inline void udelay(uint32_t us)
{
	volatile uint64_t loops = (uint64_t)us * 300ULL;

	while (loops-- != 0U) {
		__asm__ volatile("nop" ::: "memory");
	}
}

/* Function: mdelay
 *
 * Calls udelay(1000) once for each count in ms.
 *
 * Parameters:
 *   ms - How many times to call udelay(1000).
 *
 * Returns:
 *   Nothing.
 */
static inline void mdelay(uint32_t ms)
{
	while (ms-- != 0U) {
		udelay(1000U);
	}
}

/* Constants: System manager registers
 *
 * Agilex 5 system manager addresses the DDR driver reads.
 * SOCFPGA_SYSMGR(name) adds the matching offset to the base.
 *
 * SOCFPGA_SYSMGR_REG_BASE            - Base address 0x10D12000.
 * SOCFPGA_SYSMGR_BOOT_SCRATCH_COLD_3 - Offset 0x20C. Holds the reset type and the double-bit error flags.
 * SOCFPGA_SYSMGR_MPFE_CONFIG         - Offset 0x228. Dual-EMIF init sets bit 8 and bit 2.
 * SOCFPGA_SYSMGR_BOOT_SCRATCH_POR_0  - Offset 0x258. Bit 0 is the DDR init-in-progress flag.
 * SOCFPGA_SYSMGR                     - Base plus SOCFPGA_SYSMGR_##_reg. The driver calls SOCFPGA_SYSMGR(BOOT_SCRATCH_COLD_3) and the same form for the other offsets.
 */
#define SOCFPGA_SYSMGR_REG_BASE                0x10D12000U
#define SOCFPGA_SYSMGR_BOOT_SCRATCH_COLD_3     0x20CU
#define SOCFPGA_SYSMGR_MPFE_CONFIG             0x228U
#define SOCFPGA_SYSMGR_BOOT_SCRATCH_POR_0      0x258U
#define SOCFPGA_SYSMGR(_reg)                   (SOCFPGA_SYSMGR_REG_BASE + SOCFPGA_SYSMGR_##_reg)

/* Constants: DDR window base
 *
 * Start of the DDR window on Agilex 5.
 *
 * DRAM_BASE - Default 0x80000000. Used when the build does not already define DRAM_BASE.
 */
#ifndef DRAM_BASE
#define DRAM_BASE           0x80000000ULL
#endif

/* Struct: handoff
 *
 * The only handoff data this DDR driver reads.
 * Bit 0 of ddr_config is dual-port. Bit 1 is dual-EMIF.
 *
 * ddr_config - Bit 0 selects dual-port. Bit 1 selects dual-EMIF.
 */
typedef struct {
	uint32_t ddr_config;
} handoff;

/* Function: mailbox_reset_cold
 *
 * Prints that a cold reset is required, then waits in a WFI loop.
 * Bring-up calls this on an ECC double-bit error. This function does not return.
 *
 * Returns:
 *   Does not return.
 */
static inline void mailbox_reset_cold(void)
{
	printf("DDR: ECC double-bit error at init - cold reset required, halting\n");
	while (1) {
		__asm__ volatile("wfi");
	}
}

/* Function: ddr_strcmp
 *
 * Compares two C strings.
 * This stack is built without the C library, so the compare lives here.
 *
 * Parameters:
 *   a - First string.
 *   b - Second string.
 *
 * Returns:
 *   0 when the strings match.
 *   The difference of the first unequal bytes when they do not.
 */
static inline int ddr_strcmp(const char *a, const char *b)
{
	while ((*a != '\0') && (*a == *b)) {
		a++;
		b++;
	}
	return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

#endif /* __DDR_PLATFORM_COMPAT_H__ */
