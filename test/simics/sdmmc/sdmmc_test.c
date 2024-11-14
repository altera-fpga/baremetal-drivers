#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "sdmmc.h"
#include "sdmmc_internal.h"
#include "sdmmc_regs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SDMMC_MAGIC_NUM 0x6061
#define SDMMC_CARD_INSERTED_BIT 0x10000
#define SDMMC_DLA_ACTIVE_STATUS_BIT_OFFSET 0x2
#define SDMMC_SDMA_MODE 0

void delay_ms(uint32_t ms) {
    clock_t start_time = clock();
    // Convert milliseconds to clock ticks (based on CLOCKS_PER_SEC)
    clock_t delay_ticks = (ms * CLOCKS_PER_SEC) / 1000;

    // Busy-wait loop until the desired delay has passed
    while ((clock() - start_time) < delay_ticks) {
        // Do nothing, just keep looping
    }
}

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char sdmmc_initiator[] = "/dev/sdmmc0";

    int32_t return_value = 0;
    uint32_t sdmmc_param = 0;
    uint32_t is_hv4e = 1;
    uint32_t block_size = 100;
    uint32_t block_count = 1;
    uint32_t buffer_size = block_count * block_size;

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

    printf("SDMMC Tests Start\n");

    int32_t sdmmc_handle = sdmmc_open(sdmmc_initiator, 0);
    if (sdmmc_handle < 0) {
        printf("ERROR: SDMMC failed to open\n");
        return_value = -1;
        return return_value;
    } else {
        printf("SDMMC successfully open\n");

        // Magic number verification
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_HRS29, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        if (sdmmc_param != SDMMC_MAGIC_NUM) {
            printf("ERROR: Magic number incorrect\n");
            return_value = -1;
            return return_value;
        }
        printf("Magic Number verified\n");

        // SD card detection
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_SRS09, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        if (!(sdmmc_param & SDMMC_CARD_INSERTED_BIT)) {
            printf("ERROR: Card Not Detected\n");
            return_value = -1;
            return return_value;
        }
        printf("SD card detection successful\n");

        /*
         * SD card initilaiziation
         */

        printf("SD initialization starts\n");

        // Setting Internal clock enable
        sdmmc_param = 0x1;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS11_ICE, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Setting SD clock enable
        sdmmc_param = 0x1;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS11_SDCE, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 0 - Reset the card. card will come into idle state
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x00000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        delay_ms(5);

        // Command 55 - To be send before issuing an application specific command
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x37000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 41 - Sends host capacity support and ask the card it's OCR content
        sdmmc_param = 0x01;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x29000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 11 - To switch bus signalling to 1.8v level
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x0B000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        uint32_t is_DAT_line_active;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_SRS09, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        is_DAT_line_active =
            (sdmmc_param & (1 << SDMMC_DLA_ACTIVE_STATUS_BIT_OFFSET)) >> SDMMC_DLA_ACTIVE_STATUS_BIT_OFFSET;
        if (is_DAT_line_active != 1) {
            printf("WARNING: DAT_line bad, should be 1\n");
        }

        delay_ms(5);

        while (is_DAT_line_active != 0) {
            sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_SRS09, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
            is_DAT_line_active =
                (sdmmc_param & (1 << SDMMC_DLA_ACTIVE_STATUS_BIT_OFFSET)) >> SDMMC_DLA_ACTIVE_STATUS_BIT_OFFSET;
            if (is_DAT_line_active != 0) {
                printf("WARNING: DAT_line bad, should be 0\n");
            }
        }

        // Command 2 - To get unique card identification(CID) number, CID number is send in the response
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x02000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 3 - To get new relative card address(RCA)
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x03000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // reading the response register
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_GET_SRS04, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 7 - Selecting the card
        uint32_t cmd_response = sdmmc_param;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&cmd_response, sizeof(uint32_t));
        sdmmc_param = 0x07000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        printf("SD card initialization complete\n");

        /*
        / Read write test
        */

        printf("R/W test starts\n");

        uint8_t write_memory[buffer_size];
        uint8_t read_memory[buffer_size];

        memset(write_memory, 0, sizeof(write_memory));
        for (uint8_t i = 0; i < buffer_size; i++) {
            write_memory[i] = i;
        }
        memset(read_memory, 0, sizeof(read_memory));

        // Command complete interrupt enable
        sdmmc_param = 0x01;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS14, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command complete status enable
        sdmmc_param = 0x01;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS13, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Command 16
        sdmmc_param = block_size;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x10000000;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Setting command complete bit
        sdmmc_param = 0x01;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS12, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS14, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Writing to card memory
        sdmmc_param = (SDMMC_SDMA_MODE << 3);
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS10, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = block_count;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS00, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = block_size;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS01, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = is_hv4e;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS15_HV4E, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        uintptr_t write_addr = (uintptr_t)(&write_memory[0]);
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS22, (uintptr_t)(&write_addr), sizeof(uint32_t));

        // Command 24
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x18200003;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        delay_ms(5);

        // Reading from card memory
        sdmmc_param = block_count;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS00, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = block_size;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS01, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = is_hv4e;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS15_HV4E, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        uintptr_t read_addr = (uintptr_t)(&read_memory[0]);
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS22, (uintptr_t)(&read_addr), sizeof(uint32_t));

        // Command 17
        sdmmc_param = 0x00;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS02, (uintptr_t)&sdmmc_param, sizeof(uint32_t));
        sdmmc_param = 0x11200013;
        sdmmc_ioctl(sdmmc_handle, (int32_t)IOCTL_SDMMC_SET_SRS03, (uintptr_t)&sdmmc_param, sizeof(uint32_t));

        // Reading back system memory
        if (memcmp(write_memory, read_memory, sizeof(write_memory)) != 0) {
            printf("ERROR: Memory Mismatch\n");
            return_value = -1;
        } else {
            printf("R/W test passes\n");
        }
    }
    if (return_value == 0) {
        printf("SDMMC Tests successful!\n");
    }

    return return_value;
}
