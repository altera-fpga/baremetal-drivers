#ifndef CLKMGR_H
#define CLKMGR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum {
    IOCTL_CLKMGR_REGS_READ,
    IOCTL_CLKMGR_REGS_WRITE,
    IOCTL_CLKMGR_MAINPLL_REGS_READ,
    IOCTL_CLKMGR_MAINPLL_REGS_WRITE,
    IOCTL_CLKMGR_PERPLL_REGS_READ,
    IOCTL_CLKMGR_PERPLL_REGS_WRITE,
    IOCTL_CLKMGR_CTLGRP_READ,
    IOCTL_CLKMGR_CTLGRP_WRITE,

    // adding new elements before this line
    IOCTL_CLKMGR_END
} clkmgr_ioctl_op_t;

int32_t clkmgr_open(const char *name, int32_t flags);
int32_t clkmgr_close(int32_t fd);
size_t clkmgr_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags);
size_t clkmgr_read(int32_t fd, uintptr_t buf, size_t size);
size_t clkmgr_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags);
size_t clkmgr_write(int32_t fd, const uintptr_t buf, size_t size);
int32_t clkmgr_ioctl(int32_t fd, int32_t request, uintptr_t arg);
int32_t clkmgr_error(int32_t fd);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CLKMGR_H
