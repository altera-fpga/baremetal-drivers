#include "i2c.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    const char i2c_initiator[] = "/dev/i2c0";

    const uint8_t i2c_mem_addr = 0x57;
    const char i2c_test_stream[] = {'1', '2', '3', '4', '5', '\0'};
    char i2c_receive_buffer[sizeof(i2c_test_stream)];

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00030100);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 1;
    printf("I2C0 Test Start\n");
    int32_t i2c_handle = i2c_open(i2c_initiator, 0);
    if (i2c_handle < 0) {
        return_value = i2c_handle;
        printf("I2C0 failed open\n");
    } else {
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_MASTER_MODE, 1, 0);
        printf("I2C0 set to master mode\n");
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_TARGET_ADDR, 0x54, 0);
        printf("I2C0 set target address\n");
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_ENABLE, 1, 0);
        printf("I2C0 enabled\n");

        for (uint32_t i = 0; i < sizeof(i2c_test_stream); i++) {
            uint32_t temp_buffer = (((uint32_t)i2c_test_stream[i]) << (uint32_t)8) | (i2c_mem_addr + i);
            i2c_write(i2c_handle, (const uintptr_t)(&temp_buffer), 2);
        }

        printf("I2C0 wrote test stream\n");

        for (uint32_t i = 0; i < sizeof(i2c_test_stream); i++) {
            uint32_t temp_buffer = (i2c_mem_addr + i);
            i2c_read(i2c_handle, (const uintptr_t)(&temp_buffer), 2);
            i2c_receive_buffer[i] = (uint8_t)(temp_buffer & (uint32_t)0xFF);
        }
        printf("I2C0 read test stream\n");

        if (strcmp(i2c_test_stream, i2c_receive_buffer) == 0) {
            return_value = 0;
            printf("I2C test passed\n");
        } else {
            return_value = -1;
            printf("I2C test miscompare\n");
            printf("Expected: ");
            for (uint32_t i = 0; i < sizeof(i2c_test_stream); i++) {
                putchar((int)(i2c_test_stream[i]));
            }
            printf("\n");
            printf("Observed: ");
            for (uint32_t i = 0; i < sizeof(i2c_receive_buffer); i++) {
                putchar((int)(i2c_receive_buffer[i]));
            }
            printf("\n");
        }
    }
    return return_value;
}
