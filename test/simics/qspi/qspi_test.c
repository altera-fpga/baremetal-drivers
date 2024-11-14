#include "qspi.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    const char qspi_initiator[] = "/dev/qspi0";

    uint64_t qspi_receive_buffer;

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00010000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t return_value = 1;
    printf("qspi Test Start\n");
    int32_t qspi_handle = qspi_open(qspi_initiator, 0);
    if (qspi_handle < 0) {
        return_value = qspi_handle;
        printf("qspi failed open\n");
    } else {
        uint32_t param = 0;
        param = 0x80783800;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_SET, (uintptr_t)(&param), sizeof(uint32_t));
        param = 0x40;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_INDIRECT_ADDR_SPAN_SET, (uintptr_t)(&param), sizeof(uint32_t));
        param = 0x05;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_BAUD_RATE_DIV_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("qspi set baud rate\n");
        param = 1;

        param = 0x32320404;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CS_DELAYS_SET, (uintptr_t)(&param), sizeof(uint32_t));

        param = 0x00101003;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_DEVICE_SIZE_PARAMS_SET, (uintptr_t)(&param), sizeof(uint32_t));

        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_ENABLE_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("qspi enabled\n");
        param = 0x00;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_CS_SET, (uintptr_t)(&param), sizeof(uint32_t));
        printf("qspi set chip select\n");

        // SPI Flash set write enable latch (WEL)
        param = 0x06000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Enable 4-byte addressing
        param = 0xB7000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        uint64_t temp_buffer = 0x06;

        // Read 4 bytes from 0xA50000 -- Should be all 0 in the Simics model
        param = 0xA50000;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_IND_RD_START_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));

        param = 0x20003;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_READ_PARAMS_SET, (uintptr_t)(&param), sizeof(uint32_t));

        qspi_read(qspi_handle, (const uintptr_t)(&qspi_receive_buffer), sizeof(uint64_t));

        if ((uint32_t)(qspi_receive_buffer >> 32) == (uint32_t)0x00000000) {
            return_value = 0;
            printf("qspi Verified initial read all 0\n");
        } else {
            printf("qspi Failed initial read\n");
        }

        // Erase the A5 sector

        // Set WEL
        param = 0x06000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        temp_buffer = (0xA5 << 16) | (0x00 << 8) | (0x00 << 0);
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_ADDR_SET, (uintptr_t)(&temp_buffer), sizeof(uint64_t));
        temp_buffer = 0x200B0001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&temp_buffer), sizeof(uint64_t));

        printf("qspi erase 0xA50000\n");

        // SPI Read 4 bytes
        temp_buffer = (0xA5 << 16) | (0x00 << 8) | (0x00 << 0);

        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_IND_RD_START_ADDR_SET, (uintptr_t)(&temp_buffer), sizeof(uint32_t));

        qspi_read(qspi_handle, (const uintptr_t)(&qspi_receive_buffer), sizeof(uint64_t));

        printf("qspi read test stream\n");

        if ((uint32_t)(qspi_receive_buffer >> 32) == (uint32_t)0xFFFFFFFF) {
            return_value = 0;
            printf("qspi Passed erase test\n");
        } else {
            return_value = -1;
            printf("qspi test miscompare\n");
            printf("Expected: 0xFFFFFFFF\n");
            char s[1024];
            sprintf(s, "Observed: %#lX", qspi_receive_buffer);
            puts(s);
        }
    }
    return return_value;
}
