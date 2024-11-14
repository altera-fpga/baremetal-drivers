#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "timer.h"
#include <stdio.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    if ((uintptr_t)(reset_manager) < 0x3FFFF) {
        int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
        if (rstmgr_handle < 0) {
            return rstmgr_handle;
        }

        hps_rstmgr_regs_t regs_buffer;

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        regs_buffer.per1modrst &= ~((uint32_t)0x00030040);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        rstmgr_close(rstmgr_handle);
    }
    int32_t return_value = 1;

    int32_t timer_handle = timer_open("/dev/timer0", 0);

    if (timer_handle < 0) {
        return_value = timer_handle;
    } else {
        // Set timer count to 0x1000
        uint32_t param = 0x1000;
        if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_COUNT_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
            printf("Error setting timer count\n");
            return -1;
        }
        printf("Timer count set\n");
        // Set timer not free running
        param = 0x2;
        if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CONTROL_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
            printf("Error setting timer control\n");
            return -1;
        }
        printf("Timer mode set\n");
        // Start timer
        param = 0x3;
        if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CONTROL_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
            printf("Error starting timer\n");
            return -1;
        }
        // Verify timer is not 0
        param = 0;
        if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CURRENT_VAL_GET, (uintptr_t)(&param), sizeof(uint32_t))) {
            printf("Error getting timer current value\n");
            return -1;
        }
        if (param == 0) {
            printf("Timer current value is 0 at start\n");
            return -1;
        }
        printf("Timer started\n");
        // Wait for timer to expire
        while (1) {
            param = 0;
            if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CURRENT_VAL_GET, (uintptr_t)(&param),
                            sizeof(uint32_t))) {
                printf("Error getting timer current value\n");
                return -1;
            }
            if (param == 0) {
                printf("Timer expired -- test pass\n");
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}
