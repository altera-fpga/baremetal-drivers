#include "noc_firewall.h"
#include "noc_firewall_internal.h"
#include "noc_firewall_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char noc_firewall_initiator[] = "/dev/noc_firewall0";
#ifdef FSBL_EXECUTION
    fsbl_configuration();
#endif
    int32_t return_value = 0;
    uint32_t param = 0;

    printf("Started Logging\n");

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)0xFF7FB8F8);
    regs_buffer.per1modrst &= ~((uint32_t)0x07037FFF);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("NOC Firewall Test Starts\n");

    int32_t noc_firewall_handle = noc_firewall_open(noc_firewall_initiator, 0);
    if (noc_firewall_handle < 0) {
        printf("ERROR: NOC Firewall failed to open\n");
        return_value = -1;
        return return_value;
    } else {
        printf("NOC Firewall successfully open\n");

        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_NAND_REGISTER, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_NAND_REGISTER, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch1\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_USB0_REGISTER, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_USB0_REGISTER, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch2\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_I2C0, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_I2C0, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch3\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_NAND_SDMA, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_NAND_SDMA, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch4\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_WATCHDOG0, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_WATCHDOG0, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch5\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_L4_NOC_QOS, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_L4_NOC_QOS, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch6\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_SOC2FPGA, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_SOC2FPGA, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch7\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_LWSOC2FPGA, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_LWSOC2FPGA, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch8\n");
            return_value = -1;
            return return_value;
        }
        param = 0x1;
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_SET_TCU, (uintptr_t)&param,
                           sizeof(uint32_t));
        noc_firewall_ioctl(noc_firewall_handle, (int32_t)IOCTL_NOC_FIREWALL_GET_TCU, (uintptr_t)&param,
                           sizeof(uint32_t));
        if (param != 0x1) {
            printf("ERROR: Mismatch9\n");
            return_value = -1;
            return return_value;
        }
    }

    // close NOC FW handle
    int32_t ret = noc_firewall_close(noc_firewall_handle);
    if (ret == 0) {
        printf("NOC FW close: OK\n");
    } else {
        printf("NOC FW close: FAILED\n");
    }

    if (return_value == 0) {
        printf("NOC Firewall Tests successful!!!\n");
    }

    return return_value;
}
