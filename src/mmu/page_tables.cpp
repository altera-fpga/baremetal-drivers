#include <stdint.h>

#include "debug.h"
#include "page_tables.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// This approach to page table generation assumes the procesor is in EL2 or EL3 always
// This does not implement secure/non-secure distinctions in the page table
// This approach constructs a default 3-level page table that describes the lower 4GB
// Level 1 is a block table with 4 entries of 1GB each:
//          0 points to a Level 2 page table
//          1-3 point to 1GB blocks with no translation
// Level 2 is a block table with 512 entries of 2MB each:
//          0 points to a Level 3 page table
//          1-511 point to 2MB blocks with no translation
// Level 3 is a page table with 512 entries of 4KB each:
//          Each entry points to a 4KB block with no translation
// The level 3 page allows for access beyond OCRAM which is rejected by the HW

// Pages are statically allocated

// Define the size of a page
#define PAGE_SIZE 4096

// Define the attributes for a page table entry
#define PAGE_TABLE_DESCRIPTOR_VALID (uint64_t)(1UL << 0UL)
#define PAGE_TABLE_ENTRY_IS_NEXT_TABLE_OR_PAGE (uint64_t)(1UL << 1UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_0 (uint64_t)((0UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_1 (uint64_t)((1UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_2 (uint64_t)((2UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_3 (uint64_t)((3UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_4 (uint64_t)((4UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_5 (uint64_t)((5UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_6 (uint64_t)((6UL) << 2UL)
#define PAGE_TABLE_ENTRY_ATTR_IDX_7 (uint64_t)((7UL) << 2UL)
#define PAGE_TABLE_ENTRY_NON_SECURE (uint64_t)(1UL << 5UL)
#define PAGE_TABLE_ENTRY_ACCESS_FLAG (uint64_t)(1UL << 10UL)
#define PAGE_TABLE_ENTRY_NOT_GLOBAL (uint64_t)(1UL << 11UL)
#define PAGE_TABLE_ENTRY_CONTIGUOUS_HINT (uint64_t)(1UL << 52UL)
#define PAGE_TABLE_ENTRY_PXN (uint64_t)(1UL << 53UL)
#define PAGE_TABLE_ENTRY_XN (uint64_t)(1UL << 54UL)

#define MEMORY_PROPERTY_NORMAL_NON_CACHEABLE (0x44UL)
#define MEMORY_PROPERTY_DEVICE_nGnRE (0x04UL)
#define MEMORY_SHIFT_2MB (21ULL)

// Define the type for a page table entry
typedef uint64_t page_table_entry_t;

// Define identity page table entries. Below we define MAIR to be 0xFF for entry 0 and 0x04 for entry 1
// Herein, we use two levels of page tables so we can flag the OCRAM as normal memory.
page_table_entry_t level2_page0[512] __attribute__((aligned(4096))) = {0};

page_table_entry_t level1_pages[] __attribute__((aligned(4096))) = {
    (0x00000000ULL | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID | PAGE_TABLE_ENTRY_ATTR_IDX_0),
    (0x40000000ULL | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID | PAGE_TABLE_ENTRY_ATTR_IDX_0),
    (0x80000000ULL | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID | PAGE_TABLE_ENTRY_ATTR_IDX_1),
    (0xC0000000ULL | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID | PAGE_TABLE_ENTRY_ATTR_IDX_1),
};

void setup_level2_page0(void) {
    // Setup the pages so entry 0 is normal memory and all others are device memory
    level1_pages[0] |= (uint64_t)(level2_page0) | PAGE_TABLE_ENTRY_IS_NEXT_TABLE_OR_PAGE;
    for (uint64_t i = 0; i < 512ULL; i++) {
        if (i == 0UL) {
            level2_page0[i] = (0x00000000ULL | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID |
                               PAGE_TABLE_ENTRY_ATTR_IDX_1);
        } else {
            level2_page0[i] = ((i << MEMORY_SHIFT_2MB) | PAGE_TABLE_ENTRY_ACCESS_FLAG | PAGE_TABLE_DESCRIPTOR_VALID |
                               PAGE_TABLE_ENTRY_ATTR_IDX_0);
        }
    }
}

void apply_page_tables_el3(void) {
    debug(__FUNCTION__);

    setup_level2_page0();

    // Set MAIR_EL3 for the memory attribute indices
    // Index 0 is device memory and is the default in the page table
    // Index 1 is normal memory, non-cacheable (0x44) and is applied to DDR and OCRAM
    // ranges
    uint64_t mair_value = (uint64_t)((MEMORY_PROPERTY_NORMAL_NON_CACHEABLE << 8UL) | MEMORY_PROPERTY_DEVICE_nGnRE);

    asm volatile("msr mair_el3, %0" ::"r"(mair_value));

    // Set TCR_EL3 to set address span (T0SZ)
    // value was changed to -> 0x20UL recently whcih breaks our current tests
    uint64_t tcr_value = 0x1FUL;
    asm volatile("msr tcr_el3, %0" ::"r"(tcr_value));

    // Set TTBR0_EL3 to the base of level 0
    uint64_t ttbr0_value = (uint64_t)level1_pages;
    asm volatile("msr ttbr0_el3, %0" ::"r"((uint64_t)ttbr0_value));

    // Flush pipeline before enabling page tables
    asm volatile("dsb ish");
    asm volatile("isb");

    // Set SCTLR_EL3 C bit
    uint64_t sctlr_value;
    asm volatile("mrs %0, sctlr_el3" : "=r"(sctlr_value));
    sctlr_value |= (uint64_t)(1UL << 2UL); // Set C bit
    asm volatile("msr sctlr_el3, %0" ::"r"(sctlr_value));

    // Set SCTLR_EL3 M bit
    asm volatile("mrs %0, sctlr_el3" : "=r"(sctlr_value));
    sctlr_value |= (uint64_t)(1UL << 0UL); // Set M bit
    asm volatile("msr sctlr_el3, %0" ::"r"(sctlr_value));

    // Flush pipeline before continuing to user code
    asm volatile("isb");
}

void apply_page_tables_el2(void) {
    debug(__FUNCTION__);

    setup_level2_page0();

    // Set MAIR_EL2 for the memory attribute indices
    // Index 0 is device memory and is the default in the page table
    // Index 1 is normal memory, non-cacheable (0x44) and is applied to DDR and OCRAM
    // ranges
    uint64_t mair_value = (uint64_t)((MEMORY_PROPERTY_NORMAL_NON_CACHEABLE << 8UL) | MEMORY_PROPERTY_DEVICE_nGnRE);

    asm volatile("msr mair_el2, %0" ::"r"(mair_value));

    // Set TCR_EL2 to set address span (T0SZ)
    // Value was recently changed to 0x20YL which breaks our current tests
    uint64_t tcr_value = 0x1FUL;
    asm volatile("msr tcr_el2, %0" ::"r"(tcr_value));

    // Set TTBR0_EL2 to the base of level 0
    uint64_t ttbr0_value = (uint64_t)level1_pages;
    asm volatile("msr ttbr0_el2, %0" ::"r"((uint64_t)ttbr0_value));

    // Flush pipeline before enabling page tables
    asm volatile("dsb ish");
    asm volatile("isb");

    uint64_t sctlr_value;

    // TODO: Set SCTLR_EL2 C bit
    // retrieve the code that was here from commit history

    // Set SCTLR_EL2 M bit
    asm volatile("mrs %0, sctlr_el2" : "=r"(sctlr_value));
    sctlr_value |= (uint64_t)(1UL << 0UL); // Set M bit
    asm volatile("msr sctlr_el2, %0" ::"r"(sctlr_value));

    // Flush pipeline before continuing to user code
    asm volatile("isb");
}

void apply_page_tables_el1(void) {
    debug(__FUNCTION__);

    setup_level2_page0();

    // Set MAIR_EL2 for the memory attribute indices
    // Index 0 is device memory and is the default in the page table
    // Index 1 is normal memory, non-cacheable (0x44) and is applied to DDR and OCRAM
    // ranges
    uint64_t mair_value = (uint64_t)((MEMORY_PROPERTY_NORMAL_NON_CACHEABLE << 8UL) | MEMORY_PROPERTY_DEVICE_nGnRE);

    asm volatile("msr mair_el1, %0" ::"r"(mair_value));

    // Set TCR_EL1 to set address span (T0SZ)
    // Value was recently changed to 0x20YL which breaks our current tests
    uint64_t tcr_value = 0x1FUL;
    asm volatile("msr tcr_el1, %0" ::"r"(tcr_value));

    // Set TTBR0_EL1 to the base of level 0
    uint64_t ttbr0_value = (uint64_t)level1_pages;
    asm volatile("msr ttbr0_el1, %0" ::"r"((uint64_t)ttbr0_value));

    // Flush pipeline before enabling page tables
    asm volatile("dsb ish");
    asm volatile("isb");

    uint64_t sctlr_value;

    // TODO: Set SCTLR_EL1 C bit
    // retrieve the code that was here from commit history

    // Set SCTLR_EL1 M bit
    asm volatile("mrs %0, sctlr_el1" : "=r"(sctlr_value));
    sctlr_value |= (uint64_t)(1UL << 0UL); // Set M bit
    asm volatile("msr sctlr_el1, %0" ::"r"(sctlr_value));

    uint64_t cpacr_el1_value;
    asm volatile("mrs %0, cpacr_el1" : "=r"(cpacr_el1_value));
    cpacr_el1_value |= (uint64_t)(3UL << 20UL); // Set FPEN bits
    cpacr_el1_value |= (uint64_t)(3UL << 26UL); // set SMEN bits
    asm volatile("msr cpacr_el1, %0" ::"r"(cpacr_el1_value));

    // Flush pipeline before continuing to user code
    asm volatile("isb");
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
