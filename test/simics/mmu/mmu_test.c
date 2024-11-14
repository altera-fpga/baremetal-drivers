#include "page_tables.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00010000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 1;
    printf("mmu Test Start\n");

    // Set SCR_EL3 NS bit to go to non-secure EL3
    asm volatile("mrs x0, scr_el3");
    asm volatile("orr x0, x0, #(1 << 0)");
    asm volatile("msr scr_el3, x0");

    apply_page_tables_el2();

    uint64_t address = 0x80000000;
    uint64_t translation_result = 0xFFFFFFFF;
    // Test EL2 Level 1 translation using ARM AT instruction
    asm volatile("at s1e2r, %[_addr_]" : : [_addr_] "r"(address));
    // str X0 to translation_result
    asm volatile("str x0, %[_result_]" : [_result_] "=m"(translation_result));

    if (translation_result == address) {
        return_value = 0;
        printf("Translation Successful\n");
    } else {
        return_value = 1;
        printf("Translation Failed\n");
    }

    return return_value;
}
