#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Extra driver's needed
#include "rstmgr.h"
#include "rstmgr_regs.h"
// #include "uart.h"

// smmu required headers
#include "smmu.h"
#include "smmu_internal.h"
#include "smmu_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SMMU_IIDR 0x4832143b

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char smmu_dev[] = "/dev/smmu0";
    int32_t ret_val = 1;
    uint32_t smmu_param = 0;

    // For some unknown reason this test doesn't work without this print statement here SO DON'T MOVE THIS UNTIL WE
    // UNDERSTAND WHY
    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    hps_rstmgr_regs_t regs_buffer;

    if (rstmgr_handle < 0) {
        ret_val = rstmgr_handle;
    } else {

        printf("Starting Basic SMMU Test\n");
        int32_t smmu_base_addr = -1;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));
        regs_buffer.per0modrst &= ~((uint32_t)0x00020000);
        regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));
        // Open SMMU 0
        smmu_base_addr = smmu_open(smmu_dev, 0);
        if (smmu_base_addr < 0) {
            ret_val = smmu_base_addr;
        } else {

            /* CORE SPECIFIC TESTS START */
            // Read memory version
            smmu_ioctl(smmu_base_addr, IOCTL_SMMU_IIDR_GET, (uintptr_t)&smmu_param, sizeof(smmu_param));
            printf("Verify if IIDR value equals 0x4832143b\n");
            if (smmu_param & SMMU_IIDR) {
                printf("SMMU IIDR value is accurate \n");
                ret_val = 0;
            }
        }

        // Close SMMU 0
        smmu_close(smmu_base_addr);
        rstmgr_close(rstmgr_handle);
        return ret_val;
    }
}

#ifdef __cplusplus
}
#endif
