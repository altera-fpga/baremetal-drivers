#ifndef TIMER_H
#define TIMER_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    IOCTL_TIMER_REGS_READ,
    IOCTL_TIMER_REGS_WRITE,
    IOCTL_TIMER_COUNT_SET,
    IOCTL_TIMER_COUNT_GET,
    IOCTL_TIMER_CURRENT_VAL_GET,
    IOCTL_TIMER_CONTROL_SET,
    IOCTL_TIMER_CONTROL_GET,
    IOCTL_TIMER_INT_STAT_GET,
    IOCTL_TIMERS_INT_STAT_GET,
    IOCTL_TIMERS_RAW_INT_STAT_GET,
    IOCTL_TIMERS_EOI_APPLY,
    IOCTL_TIMER_EOI_APPLY,
    IOCTL_TIMER_COMP_VERSION_GET,

    // adding new elements before this line
    IOCTL_TIMER_END
} timer_ioctl_op_t;

int32_t timer_open(const char *name, int32_t flags);
int32_t timer_close(int32_t fd);
size_t timer_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags);
size_t timer_read(int32_t fd, uintptr_t buf, size_t size);
size_t timer_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags);
size_t timer_write(int32_t fd, const uintptr_t buf, size_t size);
int32_t timer_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t size);
int32_t timer_error(int32_t fd);

#endif // TIMER_H