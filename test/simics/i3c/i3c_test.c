#include "i3c.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BLOCK_COUNT 20
#define BLOCK_SIZE (BLOCK_COUNT * sizeof(uint32_t))

void delay_ms(uint32_t ms) {
    clock_t start_time = clock();
    // Convert milliseconds to clock ticks (based on CLOCKS_PER_SEC)
    clock_t delay_ticks = (ms * CLOCKS_PER_SEC) / 1000;

    // Busy-wait loop until the desired delay has passed
    while ((clock() - start_time) < delay_ticks) {
        // Do nothing, just keep looping
    }
}

static inline uint8_t fifo_level(int32_t i3c_handle, bool is_read) {
    uint32_t levels;
    i3c_ioctl(i3c_handle, I3C_IOCTL_DATA_BUFFER_STATUS_LEVEL_GET, (uintptr_t)(&levels), sizeof(uint32_t));
    if (is_read)
        levels >>= 16;
    return levels;
}

static uint8_t wait_fifo_level(int32_t i3c_handle, bool is_read) {
    uint8_t level;
    const int max_retry = 10000;
    for (int i = 0; i < max_retry; i++) {
        level = fifo_level(i3c_handle, is_read);
        if (level)
            return level;
        delay_ms(100);
    }

    puts("timeout waiting for FIFO!\r\n");
    return 0;
}

int check_response(int32_t i3c_handle, uint32_t expected) {
    // Wait for a transfer to complete
    uint32_t param;
    i3c_ioctl(i3c_handle, I3C_IOCTL_QUEUE_STATUS_LEVEL_GET, (uintptr_t)(&param), sizeof(uint32_t));
    while (((param >> 8) & 255) == 0) {
        i3c_ioctl(i3c_handle, I3C_IOCTL_QUEUE_STATUS_LEVEL_GET, (uintptr_t)(&param), sizeof(uint32_t));
        delay_ms(10000);
    }
    i3c_ioctl(i3c_handle, I3C_IOCTL_RESPONSE_QUEUE_PORT_GET, (uintptr_t)(&param), sizeof(uint32_t));

    return param != expected;
}

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";
    const char i3c_initiator[] = "/dev/i3c0";

    uint32_t src_buf[BLOCK_COUNT];
    uint32_t dst_buf[BLOCK_COUNT];
    src_buf[0] = 0x11223344;
    for (int i = 1; i < BLOCK_COUNT; i++) {
        src_buf[i] = src_buf[i - 1] + 0x01010101;
    }

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00036000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 0;
    printf("I3C0 Test Start\n");
    int32_t i3c_handle = i3c_open(i3c_initiator, 0);
    if (i3c_handle < 0) {
        return_value = i3c_handle;
        printf("I3C0 failed open\n");
    } else {
        uint32_t param = 0x01;

        printf("I3C0 Handle Open\n");

        // Set the initiator device address
        param = (1 << 31) | (1 << 16);
        i3c_ioctl(i3c_handle, I3C_IOCTL_DEVICE_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Enabling I3C
        param = (1 << 31);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_CFG_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("I3C0 Enabled\n");

        // Setting up Command 7
        param = ((1 << 21) | (7 << 7) | 3);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_COMMAND_QUEUE_PORT_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("I3C0 Command 7 set up\n");

        printf("I3C0 Init Completed\n");

        // Writing
        param = ((BLOCK_SIZE << 16) | 1);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_COMMAND_QUEUE_PORT_SET, (uintptr_t)(&param), sizeof(uint32_t));

        param = (0 << 28) | (1 << 26) | (1 << 30) | (0 << 16);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_COMMAND_QUEUE_PORT_SET, (uintptr_t)(&param), sizeof(uint32_t));

        uint8_t level = 0;
        for (int i = 0; i < BLOCK_COUNT; i++) {
            if (!level) {
                level = wait_fifo_level(i3c_handle, false);
                assert(level);
            }
            i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_TX_DATA_PORT_SET, (uintptr_t)(&src_buf[i]), sizeof(uint32_t));
            level--;
        }
        check_response(i3c_handle, 0);

        printf("I3C0 Writing Completed\n");

        // Reading
        param = ((BLOCK_SIZE << 16) | 1);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_COMMAND_QUEUE_PORT_SET, (uintptr_t)(&param), sizeof(uint32_t));

        param = (1 << 28) | (1 << 26) | (1 << 30) | (0 << 16);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_COMMAND_QUEUE_PORT_SET, (uintptr_t)(&param), sizeof(uint32_t));

        level = 0;
        for (int i = 0; i < BLOCK_COUNT; i++) {
            if (!level) {
                level = wait_fifo_level(i3c_handle, true);
                assert(level);
            }
            i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_TX_DATA_PORT_GET, (uintptr_t)(&dst_buf[i]), sizeof(uint32_t));
            level--;
        }
        check_response(i3c_handle, BLOCK_SIZE);

        printf("I3C0 Reading Completed\n");

        for (int i = 0; i < BLOCK_COUNT; i++) {
            if (src_buf[i] != ~dst_buf[i]) {
                return_value = -1;
                printf("Srce buff: %x\n", src_buf[i]);
                printf("Dest buff: %x\n", ~dst_buf[i]);
                return return_value;
            }
        }

        // close I3C handle
        return_value = i3c_close(i3c_handle);
        if (return_value == 0) {
            printf("I3C0 Close: OK\n");
        } else {
            return_value = -1;
            printf("I3C0 Close: FAILED\n");
        }

        if (return_value == 0) {
            printf("I3C0 Tests Successful!!!\n");
        }
    }

    return return_value;
}
