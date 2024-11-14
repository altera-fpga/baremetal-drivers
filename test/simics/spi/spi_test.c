#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "spi.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    const char spi_initiator[] = "/dev/spim0";

    uint64_t spi_receive_buffer;

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)0x00020000);
    regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 1;
    printf("spi0 Test Start\n");
    int32_t spi_handle = spi_open(spi_initiator, 0);
    if (spi_handle < 0) {
        return_value = spi_handle;
        printf("spi0 failed open\n");
    } else {
        uint32_t param = 0;
        param = 0x05;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_BAUD_RATE, (uintptr_t)(&param), sizeof(uint32_t));
        printf("spi0 set baud rate\n");
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_SSI_ENABLE, (uintptr_t)(&param), sizeof(uint32_t));
        printf("spi0 enabled\n");
        param = 0x01;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_CS, (uintptr_t)(&param), sizeof(uint32_t));
        printf("spi0 set chip select\n");

        uint64_t temp_buffer = 0x06;

        // SPI Read 4 bytes -- Should be all 0 in the Simics model
        temp_buffer = 0x03 | (0xA5 << 8) | (0x00 << 16) | (0x00 << 24) | ((uint64_t)0x00000000 << 32);
        spi_write(spi_handle, (const uintptr_t)(&temp_buffer), sizeof(uint64_t));

        spi_read(spi_handle, (const uintptr_t)(&spi_receive_buffer), sizeof(uint64_t));

        if ((uint32_t)(spi_receive_buffer >> 32) == (uint32_t)0x00000000) {
            return_value = 0;
            printf("spi Verified initial read all 0\n");
        } else {
            printf("spi Failed initial read\n");
        }

        // SPI Flash write enable
        temp_buffer = 0x06;
        spi_write(spi_handle, (const uintptr_t)(&temp_buffer), 1);

        printf("spi0 wrote write enable\n");

        temp_buffer = 1;
        while ((temp_buffer & 0x01) > 0) {
            spi_ioctl(spi_handle, IOCTL_SPI_GET_STATUS, (const uintptr_t)(&temp_buffer), sizeof(uint64_t));
        }

        spi_read(spi_handle, (const uintptr_t)(&temp_buffer), 1);

        // Erase the A5 sector
        temp_buffer = 0x20 | (0xA5 << 8) | (0x00 << 16) | (0x00 << 24);
        spi_write(spi_handle, (const uintptr_t)(&temp_buffer), sizeof(uint32_t));

        printf("spi0 erase 0xA5\n");

        temp_buffer = 1;
        // Wait for SPI operation to complete
        while ((temp_buffer & 0x01) > 0) {
            spi_ioctl(spi_handle, IOCTL_SPI_GET_STATUS, (const uintptr_t)(&temp_buffer), sizeof(uint64_t));
        }

        spi_read(spi_handle, (const uintptr_t)(&temp_buffer), sizeof(uint64_t));

        // SPI Read 4 bytes
        temp_buffer = 0x03 | (0xA5 << 8) | (0x00 << 16) | (0x00 << 24) | ((uint64_t)0x00000000 << (uint64_t)32);
        spi_write(spi_handle, (const uintptr_t)(&temp_buffer), sizeof(uint64_t));

        spi_read(spi_handle, (const uintptr_t)(&spi_receive_buffer), sizeof(uint64_t));

        printf("spi0 read test stream\n");

        if ((uint32_t)(spi_receive_buffer >> 32) == (uint32_t)0xFFFFFFFF) {
            return_value = 0;
            printf("spi Passed erase test\n");
        } else {
            return_value = -1;
            printf("spi test miscompare\n");
            printf("Expected: 0xFFFFFFFF\n");
            char s[1024];
            sprintf(s, "Observed: %#lX", spi_receive_buffer);
            puts(s);
        }
    }
    return return_value;
}
