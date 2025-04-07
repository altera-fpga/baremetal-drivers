#include "bridge_helper.h"

#include <stdio.h>
#include <string.h>

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

#define RST_MGR_PER0MODRST_MASK 0xFF7FBFff
#define RST_MGR_PER1MODRST_MASK 0x07037FFF

#ifdef __cplusplus
extern "C" {
#endif

void close_drivers(int32_t rstmgr, int32_t timer, int32_t sysmgr, int32_t smmu, int32_t mbox) {
    if (smmu >= 0)
        smmu_close(smmu);
    if (sysmgr >= 0)
        sysmgr_close(sysmgr);
    if (timer >= 0)
        timer_close(timer);
    if (rstmgr >= 0)
        rstmgr_close(rstmgr);

#ifdef FSBL_EXECUTION
    if (mbox >= 0)
        hps_mbox_close(mbox);
#endif
}

int main(void) {

    int32_t return_value = 0;
    int32_t mbox_handle = -1;

#ifdef FSBL_EXECUTION
    fsbl_configuration();
#endif

    int32_t rstmgr_handle = rstmgr_open("/dev/rstmgr", 0);
    if (rstmgr_handle < 0)
        return rstmgr_handle;

    int32_t timer_handle = timer_open("/dev/timer0", 0);
    if (timer_handle < 0) {
        close_drivers(rstmgr_handle, -1, -1, -1, -1);
        return timer_handle;
    }

    int32_t sysmgr_handle = sysmgr_open("/dev/sysmgr", 0);
    if (sysmgr_handle < 0) {
        close_drivers(rstmgr_handle, timer_handle, -1, -1, -1);
        return sysmgr_handle;
    }

    int32_t smmu_handle = smmu_open("/dev/smmu0", 0);
    if (smmu_handle < 0) {
        close_drivers(rstmgr_handle, timer_handle, sysmgr_handle, -1, -1);
        return smmu_handle;
    }

    hps_rstmgr_regs_t regs_buffer;

    // deassert_peripheral_reset
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)RST_MGR_PER0MODRST_MASK);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)RST_MGR_PER1MODRST_MASK);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

#ifdef FSBL_EXECUTION

    mbox_handle = hps_mbox_open("/dev/hps_mailbox", 0);

    if (mbox_handle < 0) {
        close_drivers(rstmgr_handle, timer_handle, sysmgr_handle, smmu_handle, -1);
        return mbox_handle;
    }

    // This is for checking CONFIG ready for bridge enable
    uint32_t resp[MBOX_GET_CONFIG_STATUS_RESP_NUM];
    if (0 != bridge_mbox_helper(mbox_handle, MBOX_GET_CONFIG_STATUS, resp, MBOX_GET_CONFIG_STATUS_RESP_NUM)) {
        printf("MBOX_GET_CONFIG_STATUS FAILED!\n");
        return_value = -1;
    }

    if (resp[MBOX_CONFIG_STATUS_RESP_STATE] != 0) {
        printf("[Error] CONFIG STATUS STATE is not IDLE, actual value: 0x%x!\n", resp[MBOX_CONFIG_STATUS_RESP_STATE]);
        return_value = -1;
    }

    if ((resp[MBOX_CONFIG_STATUS_RESP_PIN_STATUS] & MBOX_CONFIG_STATUS_RESP_PIN_STATUS_MASK) !=
        MBOX_CONFIG_STATUS_RESP_PIN_STATUS_MASK) {
        printf("[Error] CONFIG STATUS PIN STATUS is not expected, actual value: 0x%x!\n",
               resp[MBOX_CONFIG_STATUS_RESP_PIN_STATUS]);
        return_value = -1;
    }

    if (resp[MBOX_CONFIG_STATUS_RESP_SOFT_FUNCTION] ^ MBOX_CONFIG_STATUS_RESP_SOFT_FUNCTION_MASK) {
        printf("[Error] CONFIG STATUS SOFT FUNCTION is not expected, actual value: 0x%x!\n",
               resp[MBOX_CONFIG_STATUS_RESP_SOFT_FUNCTION_MASK]);
        return_value = -1;
    }
#endif // FSBL_EXECUTION

    printf("Bridge Test Start\n");

    if (bridge_enable(rstmgr_handle, timer_handle, sysmgr_handle) != 0) {
        printf("Bridge enable FAILED!\n");
        return_value = -1;
    } else if (bridge_disable(rstmgr_handle, timer_handle, sysmgr_handle) != 0) {
        printf("Bridge disable FAILED!\n");
        return_value = -1;
    } else {

#ifdef FSBL_EXECUTION
        // If SMMU is enabled, then MBOX_HPS_FPGA_CONFIG_COMP isolates the connection between HPS and FPGA
        if (bridge_smmu_enabled_check_helper(smmu_handle)) {
            printf("SMMU is enabled, sending MBOX_HPS_FPGA_CONFIG_COMP...\n");
            if (0 != bridge_mbox_helper(mbox_handle, MBOX_HPS_FPGA_CONFIG_COMP, resp, 0)) {
                printf("MBOX_HPS_FPGA_CONFIG_COMP FAILED!\n");
                return_value = -1;
            }
        }
#endif
        printf("Bridge Test is successful!\n");
    }

    close_drivers(rstmgr_handle, timer_handle, sysmgr_handle, smmu_handle, mbox_handle);

    return return_value;
}
#ifdef __cplusplus
}
#endif
