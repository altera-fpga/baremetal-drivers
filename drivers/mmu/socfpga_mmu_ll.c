/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_mmu_ll.c
 *
 * MMU source implementation for the SoCFPGA bare-metal software stack.
 */

#include "socfpga_mmu_ll.h"
#include "socfpga_mmu_reg.h"

uint64_t socfpga_mmu_ll_make_block_descriptor(uint64_t physical_address,
                                              uint32_t attr_index,
                                              uint32_t shareability,
                                              uint32_t access_permission,
                                              bool execute_never)
{
    uint64_t desc;

    desc = MMU_DESC_VALID_MASK;
    desc |= ((uint64_t)attr_index << MMU_DESC_ATTR_INDEX_POS) & MMU_DESC_ATTR_INDEX_MASK;
    desc |= ((uint64_t)shareability << MMU_DESC_SH_POS) & MMU_DESC_SH_MASK;
    desc |= ((uint64_t)access_permission << MMU_DESC_AP_POS) & MMU_DESC_AP_MASK;
    desc |= MMU_DESC_AF_MASK;
    desc |= physical_address & MMU_DESC_OUTPUT_ADDR_MASK;
    if (execute_never) {
        desc |= MMU_DESC_PXN_MASK | MMU_DESC_UXN_MASK;
    }
    return desc;
}

void socfpga_mmu_ll_invalidate_tlb(void)
{
#if defined(__aarch64__)
    __asm__ volatile("dsb sy\n"
                     "tlbi alle3\n"
                     "tlbi alle2\n"
                     "tlbi vmalle1\n"
                     "dsb sy\n"
                     "isb\n" ::: "memory");
#endif
}

int32_t socfpga_mmu_ll_enable_el(uint32_t exception_level, uint64_t ttbr0,
                                 uint64_t tcr, uint64_t mair)
{
#if defined(__aarch64__)
    if (exception_level == 3U) {
        __asm__ volatile("msr ttbr0_el3, %0\nmsr tcr_el3, %1\nmsr mair_el3, %2\nisb\n" :: "r"(ttbr0), "r"(tcr), "r"(mair) : "memory");
        __asm__ volatile("mrs x0, sctlr_el3\norr x0, x0, %0\nmsr sctlr_el3, x0\nisb\n" :: "r"((uint64_t)(MMU_SCTLR_M_MASK | MMU_SCTLR_C_MASK | MMU_SCTLR_I_MASK)) : "x0", "memory");
        return 0;
    }
    if (exception_level == 2U) {
        __asm__ volatile("msr ttbr0_el2, %0\nmsr tcr_el2, %1\nmsr mair_el2, %2\nisb\n" :: "r"(ttbr0), "r"(tcr), "r"(mair) : "memory");
        __asm__ volatile("mrs x0, sctlr_el2\norr x0, x0, %0\nmsr sctlr_el2, x0\nisb\n" :: "r"((uint64_t)(MMU_SCTLR_M_MASK | MMU_SCTLR_C_MASK | MMU_SCTLR_I_MASK)) : "x0", "memory");
        return 0;
    }
    if (exception_level == 1U) {
        __asm__ volatile("msr ttbr0_el1, %0\nmsr tcr_el1, %1\nmsr mair_el1, %2\nisb\n" :: "r"(ttbr0), "r"(tcr), "r"(mair) : "memory");
        __asm__ volatile("mrs x0, sctlr_el1\norr x0, x0, %0\nmsr sctlr_el1, x0\nisb\n" :: "r"((uint64_t)(MMU_SCTLR_M_MASK | MMU_SCTLR_C_MASK | MMU_SCTLR_I_MASK)) : "x0", "memory");
        return 0;
    }
    return -EINVAL;
#else
    (void)exception_level;
    (void)ttbr0;
    (void)tcr;
    (void)mair;
    return -ENOSYS;
#endif
}

int32_t socfpga_mmu_ll_disable_el(uint32_t exception_level)
{
#if defined(__aarch64__)
    uint64_t clear = (uint64_t)(MMU_SCTLR_M_MASK | MMU_SCTLR_C_MASK | MMU_SCTLR_I_MASK);
    if (exception_level == 3U) {
        __asm__ volatile("mrs x0, sctlr_el3\nbic x0, x0, %0\nmsr sctlr_el3, x0\nisb\n" :: "r"(clear) : "x0", "memory");
        return 0;
    }
    if (exception_level == 2U) {
        __asm__ volatile("mrs x0, sctlr_el2\nbic x0, x0, %0\nmsr sctlr_el2, x0\nisb\n" :: "r"(clear) : "x0", "memory");
        return 0;
    }
    if (exception_level == 1U) {
        __asm__ volatile("mrs x0, sctlr_el1\nbic x0, x0, %0\nmsr sctlr_el1, x0\nisb\n" :: "r"(clear) : "x0", "memory");
        return 0;
    }
    return -EINVAL;
#else
    (void)exception_level;
    return -ENOSYS;
#endif
}

int32_t socfpga_mmu_ll_is_enabled(uint32_t exception_level, bool *enabled)
{
#if defined(__aarch64__)
    uint64_t sctlr = 0U;
    if (enabled == NULL) {
        return -EINVAL;
    }
    if (exception_level == 3U) {
        __asm__ volatile("mrs %0, sctlr_el3" : "=r"(sctlr));
    } else if (exception_level == 2U) {
        __asm__ volatile("mrs %0, sctlr_el2" : "=r"(sctlr));
    } else if (exception_level == 1U) {
        __asm__ volatile("mrs %0, sctlr_el1" : "=r"(sctlr));
    } else {
        return -EINVAL;
    }
    *enabled = ((sctlr & MMU_SCTLR_M_MASK) != 0U);
    return 0;
#else
    (void)exception_level;
    if (enabled == NULL) {
        return -EINVAL;
    }
    *enabled = false;
    return -ENOSYS;
#endif
}
