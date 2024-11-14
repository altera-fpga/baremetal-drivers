#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "uart.h"

extern int32_t stdout_uart_fd;

int main(void) {
    const char test_uart[] = "/dev/uart0";
    const char test_message[] = "Hello, World!";

    const char reset_manager[] = "/dev/rstmgr";

    // /dev/uart0 is opened during CPU init, so close it here first
    if (uart_close(stdout_uart_fd) != 0) {
        return -3;
    }

    // If main is in the OCRAM, then this is an OCRAM test and requires reset manager
    // Else, this has been loaded by ATF and does not need reset manager
    if ((uintptr_t)(reset_manager) < 0x3FFFF) {
        int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
        if (rstmgr_handle < 0) {
            return rstmgr_handle;
        }
        hps_rstmgr_regs_t regs_buffer;

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        rstmgr_close(rstmgr_handle);
    }
    int32_t handle = uart_open(test_uart, 0);
    int32_t return_value = 1;

    if (handle < 0) {
        return_value = handle;
    } else {
        if (uart_send(handle, (const uintptr_t)test_message, 13, 0) != 13UL) {
            return_value = -2;
        }
        if (uart_close(handle) != 0) {
            return_value = -1;
        }
        if (return_value == 1) {
            return_value = 0;
        }
    }
    return return_value;
}
