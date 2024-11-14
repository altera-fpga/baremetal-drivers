#include "combophy.h"
#include "combophy_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "sdmmc.h"
#include "sdmmc_internal.h"
#include "sdmmc_regs.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMBOPHY_RELEASE_IDENTIFICATION_NO 0x61820107
#define COMBOPHY_FEATURES_REG 0x00001FFF

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char sdmmc_initiator[] = "/dev/sdmmc0";
    const char combophy_initiator[] = "/dev/combophy0";

    int32_t return_value = 0;
    uint32_t param = 0;

    printf("Started Logging\n");

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)0x000080C0);
    regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("Combophy Test Start\n");

    int32_t sdmmc_handle = sdmmc_open(sdmmc_initiator, 0);
    int32_t combophy_handle = combophy_open(combophy_initiator, 0);
    if ((sdmmc_handle < 0) || (combophy_handle < 0)) {
        printf("ERROR: Failed to open handle\n");
        return_value = -1;
        return return_value;
    } else {
        printf("Combophy successfully open\n");

        /*
         * Release Identification number verification
         */
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_GET_VERSION, (uintptr_t)&param, sizeof(uint32_t));
        if (param != COMBOPHY_RELEASE_IDENTIFICATION_NO) {
            printf("ERROR: Incorrect Identification no.\n");
            return_value = -1;
            return return_value;
        }

        printf("Identification no. verified\n");

        /*
         * Combophy Features reg verification
         */
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_GET_FEATURES, (uintptr_t)&param, sizeof(uint32_t));
        if (param != COMBOPHY_FEATURES_REG) {
            printf("ERROR: Incorrect features in reg. \n");
            return_value = -1;
            return return_value;
        }

        printf("Features reg. verified\n");

        /*
         * Combo Phy read write test
         */

        // Writing default values to the SDeMMC registers
        param = 0xff;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_HRS01, (uintptr_t)&param, sizeof(uint32_t));
        param = 0x02;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_HRS02, (uintptr_t)&param, sizeof(uint32_t));

        // Reading back the SDeMMC register values
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_HRS01, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0xFF) {
            printf("ERROR: Mismatch\n");
            return_value = -1;
            return return_value;
        }
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_HRS02, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0x02) {
            printf("ERROR: Mismatch\n");
            return_value = -1;
            return return_value;
        }

        // Writing default values to the ComboPHY registers
        param = 0x03;
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_SET_DQ_TIMING, (uintptr_t)&param, sizeof(uint32_t));
        param = 0x04;
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_SET_DQS_TIMING, (uintptr_t)&param, sizeof(uint32_t));

        // Reading back the ComboPHY register values
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_GET_DQ_TIMING, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0x03) {
            printf("ERROR: Mismatch\n");
            return_value = -1;
            return return_value;
        }
        combophy_ioctl(combophy_handle, (int32_t)IOCTL_COMBOPHY_GET_DQS_TIMING, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0x04) {
            printf("ERROR: Mismatch\n");
            return_value = -1;
            return return_value;
        }

        // Writing and reading default values to the ComboPHY registers via SDeMMC register
        param = 0x400;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_HRS04, (uintptr_t)&param, sizeof(uint32_t));
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_HRS04, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0x400) {
            printf("ERROR: Mismatch\n");
            return_value = -1;
            return return_value;
        }

        param = 0x404;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_HRS04, (uintptr_t)&param, sizeof(uint32_t));
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_HRS04, (uintptr_t)&param, sizeof(uint32_t));
        if (param != 0x0404) {
            printf("Error: Mismatch\n");
            return_value = -1;
            return return_value;
        }
    }

    sdmmc_close(sdmmc_handle);
    combophy_close(combophy_handle);
    if (return_value == 0) {
        printf("Combophy successfully closed\n");
    }
    return return_value;
}
