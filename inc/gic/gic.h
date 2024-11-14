#ifndef GIC_H
#define GIC_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    IOCTL_GICD_REGS_READ,
    IOCTL_GICD_REGS_WRITE,
    IOCTL_GICA_REGS_READ,
    IOCTL_GICA_REGS_WRITE,
    IOCTL_GICT_REGS_READ,
    IOCTL_GICT_REGS_WRITE,
    IOCTL_GICP_REGS_READ,
    IOCTL_GICP_REGS_WRITE,
    IOCTL_GITS0_REGS_READ,
    IOCTL_GITS0_REGS_WRITE,
    IOCTL_GITS0_TRANSLATER_REGS_READ,
    IOCTL_GITS0_TRANSLATER_REGS_WRITE,
    IOCTL_GICR_LPI0_REGS_READ,
    IOCTL_GICR_LPI0_REGS_WRITE,
    IOCTL_GICR_LPI1_REGS_READ,
    IOCTL_GICR_LPI1_REGS_WRITE,
    IOCTL_GICR_LPI2_REGS_READ,
    IOCTL_GICR_LPI2_REGS_WRITE,
    IOCTL_GICR_LPI3_REGS_READ,
    IOCTL_GICR_LPI3_REGS_WRITE,
    IOCTL_GICR_SGI0_REGS_READ,
    IOCTL_GICR_SGI0_REGS_WRITE,
    IOCTL_GICR_SGI1_REGS_READ,
    IOCTL_GICR_SGI1_REGS_WRITE,
    IOCTL_GICR_SGI2_REGS_READ,
    IOCTL_GICR_SGI2_REGS_WRITE,
    IOCTL_GICR_SGI3_REGS_READ,
    IOCTL_GICR_SGI3_REGS_WRITE,
    IOCTL_GICDA_REGS_READ,
    IOCTL_GICDA_REGS_WRITE,

    // adding new elements before this line
    IOCTL_GIC_END
} ioctl_gic_op_t;

int32_t gic_open(const char *path, int32_t flags);
int32_t gic_close(int32_t fd);
size_t gic_read(int32_t fd, uintptr_t buf, size_t count);
size_t gic_recv(int32_t fd, uintptr_t buf, size_t count, int32_t flags);
size_t gic_write(int32_t fd, const uintptr_t buf, size_t count);
size_t gic_send(int32_t fd, const uintptr_t buf, size_t count, int32_t flags);
int32_t gic_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length);
int32_t gic_error(int32_t fd);

#endif // GIC_H
