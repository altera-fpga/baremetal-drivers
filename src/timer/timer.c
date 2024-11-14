#include "timer.h"
#include "timer_internal.h"
#include "timer_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t timer_devices[] = {{.name = "/dev/timer0", .fd = HPS_TMR_SP0, .acquired = 0},
                                       {.name = "/dev/timer1", .fd = HPS_TMR_SP1, .acquired = 0},
                                       {.name = "/dev/systimer0", .fd = HPS_TMR_SYS0, .acquired = 0},
                                       {.name = "/dev/systimer1", .fd = HPS_TMR_SYS1, .acquired = 0}};

int32_t timer_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(timer_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(timer_devices[i].name, name) == 0) {
                if (claim_device(&timer_devices[i])) {
                    fd = timer_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t timer_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(timer_devices) / sizeof(device_descriptor_t)); i++) {
            if (timer_devices[i].fd == fd) {
                timer_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* recv uimplemented */
size_t timer_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t timer_read(int32_t fd, uintptr_t buf, size_t size) { return timer_recv(fd, buf, size, 0); }

/* send unimplemented */
size_t timer_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t timer_write(int32_t fd, const uintptr_t buf, size_t size) { return timer_send(fd, buf, size, 0); }

int32_t timer_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t size) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((timer_ioctl_op_t)request) {
        case (IOCTL_TIMER_REGS_READ):
            return_value = timer_regs_read((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_REGS_WRITE):
            return_value = timer_regs_write((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_COUNT_SET):
            return_value = timer_count_set((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_COUNT_GET):
            return_value = timer_count_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_CURRENT_VAL_GET):
            return_value = timer_current_val_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_CONTROL_SET):
            return_value = timer_control_set((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_CONTROL_GET):
            return_value = timer_control_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_INT_STAT_GET):
            return_value = timer_int_stat_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMERS_INT_STAT_GET):
            return_value = timer_timers_int_stat_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMERS_RAW_INT_STAT_GET):
            return_value = timer_timers_raw_int_stat_get((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMERS_EOI_APPLY):
            return_value = timer_timers_eoi_apply((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_EOI_APPLY):
            return_value = timer_timer_eoi_apply((uintptr_t)fd, arg, size);
            break;
        case (IOCTL_TIMER_COMP_VERSION_GET):
            return_value = timer_comp_version_get((uintptr_t)fd, arg, size);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

/* Error unimplemented */
int32_t timer_error(int32_t fd) { return 0; }
