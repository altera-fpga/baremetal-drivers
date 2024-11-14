#include "i3c.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";

    const char i3c_initiator[] = "/dev/i3c0";

    const uint8_t i3c_mem_addr = 0x57;
    const char i3c_test_stream[] = {'1', '2', '3', '4', '5', '\0'};
    char i3c_receive_buffer[sizeof(i3c_test_stream)];

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00036000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 1;
    printf("I3C0 Test Start\n");
    int32_t i3c_handle = i3c_open(i3c_initiator, 0);
    if (i3c_handle < 0) {
        return_value = i3c_handle;
        printf("I3C0 failed open\n");
    } else {
        uint64_t param = 0x01;

        printf("I3C0 opened\n");

        // Set the initiator device address
        param = (1 << 31) | (1 << 16);
        i3c_ioctl(i3c_handle, I3C_IOCTL_DEVICE_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));
        // Set the device address table
        param = (uint64_t)(1) | ((uint64_t)((uint64_t)(0x5A << 16)) << 32);
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_DEVICE_ADDRESS_TABLE_SET, (uintptr_t)(&param), sizeof(uint64_t));
        printf("I3C0 address set\n");

        param = 0x01;
        i3c_ioctl(i3c_handle, (int32_t)I3C_IOCTL_CFG_ENABLE_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("I3C0 enabled\n");

        if (i3c_send(i3c_handle, 0, 0,
                     I3C_FLAGS_XFER_ATTR(I3C_MSG_TYPE_ADDR_ASSIGN) | I3C_FLAGS_COMMAND_CODE(0x07) |
                         I3C_FLAGS_ADDR_ASSIGN_IDX(0) | I3C_FLAGS_ADDR_ASSIGN_DEV_COUNT(1)) == 0) {
            printf("I3C0 failed at i3c_send: cmd 0x7\n");
        }

        // Write test stream

        for (uint32_t i = 0; i < sizeof(i3c_test_stream); i++) {
            uint32_t temp_buffer = (((uint32_t)i3c_test_stream[i]) << (uint32_t)8) | (i3c_mem_addr + i);
            i3c_send(i3c_handle, (const uintptr_t)(&temp_buffer), 2,
                     I3C_FLAGS_XFER_ATTR(I3C_MSG_TYPE_IMMEDIATE) | I3C_FLAGS_DEVICE_INDEX(0) |
                         I3C_FLAGS_XFER_SPEED(SDR0) | I3C_FLAGS_TERMINATE_ON_COMPLETION);
        }

        printf("I3C0 wrote test stream\n");

        for (uint32_t i = 0; i < sizeof(i3c_test_stream); i++) {
            uint32_t temp_buffer = (i3c_mem_addr + i);
            i3c_recv(i3c_handle, (const uintptr_t)(&temp_buffer), 2,
                     I3C_FLAGS_XFER_ATTR(I3C_MSG_TYPE_IMMEDIATE) | I3C_FLAGS_DEVICE_INDEX(0) |
                         I3C_FLAGS_XFER_SPEED(SDR0) | I3C_FLAGS_TERMINATE_ON_COMPLETION);
            i3c_receive_buffer[i] = (char)(temp_buffer & (uint32_t)0xFF);
        }
        printf("I3C0 read test stream\n");

        if (strcmp(i3c_test_stream, i3c_receive_buffer) == 0) {
            return_value = 0;
            printf("I3C test passed\n");
        } else {
            return_value = -1;
            printf("I3C test miscompare\n");

            // commented out for now due to printf issue and i3c is not testable yet.
            // printf("Expected: ");
            // for (uint32_t i = 0; i < sizeof(i3c_test_stream); i++) {
            //    uart_send(log_handle, (const uintptr_t)(&(i3c_test_stream[i])), 1, 0);
            //}

            // printf("Observed: ");
            // for (uint32_t i = 0; i < sizeof(i3c_receive_buffer); i++) {
            //     uart_send(log_handle, (const uintptr_t)(&(i3c_receive_buffer[i])), 1, 0);
            // }
        }
    }
    return return_value;
}
