#include "page_tables.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

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

    uint64_t address = 0x80000000;
    union {
        // See:
        // https://developer.arm.com/documentation/ddi0595/2020-12/AArch64-Registers/PAR-EL1--Physical-Address-Register?lang=en
        struct {
            uint64_t ATTR : 8;
            uint64_t __reserved_55_48 : 8;
            uint64_t PA : 36;
            uint64_t __reserved_11 : 1;
            uint64_t __impldef_10 : 1;
            uint64_t NS : 1;
            uint64_t SH : 2;
            uint64_t FST : 6;
            uint64_t F : 1;
        } fields;
        uint64_t value;
    } par_el1;
    // Test EL2 Stage 1 translation using ARM AT instruction
    asm volatile("at s1e2r, %[_addr_]" : : [_addr_] "r"(address));
    // Get translation result
    asm volatile("mrs %0, par_el1" : "=r"(par_el1.value));

    uint64_t physical = par_el1.fields.PA << 16;
    if (par_el1.fields.F) {
        return_value = 1;
        printf("Translation Failed: FST = %#lx\n", (uint64_t)par_el1.fields.FST);
    } else if (physical != address) {
        return_value = 1;
        printf("Translation Incorrect: Physical address = %#lx != %#lx\n", physical, address);
    } else {
        return_value = 0;
        printf("Translation Successful\n");
    }

    return return_value;
}

#ifdef __cplusplus
}
#endif
