#include "clkmgr.h"
#include "clkmgr_internal.h"
#include "clkmgr_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t clkmgr_devices[] = {{.name = "/dev/clkmgr", .fd = HPS_CLKMGR_REGS_BASE, .acquired = 0}};

int32_t clkmgr_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(clkmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(clkmgr_devices[i].name, name) == 0) {
                if (claim_device(&clkmgr_devices[i])) {
                    fd = clkmgr_devices[i].fd;
                    break;
                }
            }
        }
    }
    return fd;
}

int32_t clkmgr_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(clkmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (clkmgr_devices[i].fd == fd) {
                clkmgr_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t clkmgr_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t clkmgr_read(int32_t fd, uintptr_t buf, size_t size) { return clkmgr_recv(fd, buf, size, 0); }

size_t clkmgr_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t clkmgr_write(int32_t fd, const uintptr_t buf, size_t size) { return clkmgr_send(fd, buf, size, 0); }

int32_t clkmgr_ioctl(int32_t fd, int32_t request, uintptr_t arg) {
    int32_t return_value = -1;
    if ((fd != -1) && (((void *)(arg)) != nullptr)) {
        switch ((clkmgr_ioctl_op_t)request) {
        case (IOCTL_CLKMGR_REGS_READ):
            return_value = clkmgr_regs_read(arg);
            break;
        case (IOCTL_CLKMGR_REGS_WRITE):
            return_value = clkmgr_regs_write(arg);
            break;
        case (IOCTL_CLKMGR_MAINPLL_REGS_READ):
            return_value = clkmgr_mainpll_regs_read(arg);
            break;
        case (IOCTL_CLKMGR_MAINPLL_REGS_WRITE):
            return_value = clkmgr_mainpll_regs_write(arg);
            break;
        case (IOCTL_CLKMGR_PERPLL_REGS_READ):
            return_value = clkmgr_perpll_regs_read(arg);
            break;
        case (IOCTL_CLKMGR_PERPLL_REGS_WRITE):
            return_value = clkmgr_perpll_regs_write(arg);
            break;
        case (IOCTL_CLKMGR_CTLGRP_READ):
            return_value = clkmgr_ctlgrp_regs_read(arg);
            break;
        case (IOCTL_CLKMGR_CTLGRP_WRITE):
            return_value = clkmgr_ctlgrp_regs_write(arg);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t clkmgr_error(int32_t fd) { return 0; }