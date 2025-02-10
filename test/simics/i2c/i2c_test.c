#include "i2c.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    const char i2c_initiator[] = "/dev/i2c0";

    const uint8_t i2c_mem_addr = 0x57;
    const uint8_t buffer_size = 5;
    const uint8_t i2c_test_stream[] = {'1', '2', '3', '4', '5'};
    uint8_t i2c_receive_buffer[buffer_size];

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
        uint32_t param = 0x0;
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_ENABLE, (uintptr_t)&param, sizeof(uint32_t));
        param = 0x43;
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_CON, (uintptr_t)&param, sizeof(uint32_t));
        printf("I2C0 set to master mode\n");
        param = 0x54;
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_TARGET_ADDR, (uintptr_t)&param, sizeof(uint32_t));
        printf("I2C0 set target address\n");
        param = 0x1;
        i2c_ioctl(i2c_handle, (int32_t)IOCTL_I2C_SET_ENABLE, (uintptr_t)&param, sizeof(uint32_t));
        printf("I2C0 enabled\n");

        for (uint32_t i = 0; i < buffer_size; i++) {
            uint8_t temp_buffer[2] = {i2c_mem_addr + i, i2c_test_stream[i]};
            i2c_write(i2c_handle, (uintptr_t)(&temp_buffer), 1);
        }

        printf("I2C0 wrote test stream\n");

        for (uint32_t i = 0; i < buffer_size; i++) {
            uint8_t temp_buffer = (i2c_mem_addr + i);
            i2c_read(i2c_handle, (uintptr_t)(&temp_buffer), 1);
            i2c_receive_buffer[i] = temp_buffer;
        }
        printf("I2C0 read test stream\n");

        if (memcmp(i2c_test_stream, i2c_receive_buffer, buffer_size) == 0) {
            return_value = 0;
            printf("I2C test passed\n");
        } else {
            return_value = -1;
            printf("I2C test miscompare\n");
            printf("Expected: ");
            for (uint32_t i = 0; i < buffer_size; i++) {
                putchar((int)(i2c_test_stream[i]));
            }
            printf("\n");
            printf("Observed: ");
            for (uint32_t i = 0; i < buffer_size; i++) {
                putchar((int)(i2c_receive_buffer[i]));
            }
            printf("\n");
        }
    }
    return return_value;
}