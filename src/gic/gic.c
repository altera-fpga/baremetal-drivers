#include "gic.h"
#include "gic_internal.h"
#include "gic_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t gic_devices[] = {{.name = "/dev/gic", .fd = HPS_GICD_BASE, .acquired = 0}};

int32_t gic_open(const char *path, int32_t flags) {
    int32_t fd = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(gic_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(gic_devices[i].name, path) == 0) {
                if (claim_device(&gic_devices[i])) {
                    fd = gic_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t gic_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(gic_devices) / sizeof(device_descriptor_t)); i++) {
            if (gic_devices[i].fd == fd) {
                gic_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t gic_read(int32_t fd, uintptr_t buf, size_t count) { return gic_recv(fd, buf, count, 0); }

size_t gic_recv(int32_t fd, uintptr_t buf, size_t count, int32_t flags) { return 0; }

size_t gic_write(int32_t fd, const uintptr_t buf, size_t count) { return gic_send(fd, buf, count, 0); }

size_t gic_send(int32_t fd, const uintptr_t buf, size_t count, int32_t flags) { return 0; }

int32_t gic_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    // GIC is a bit of a special case in our implementation pattern
    // There is only one GIC but it has several pages
    // So a user needs to acquire the GIC device defined by HPS_GICD_BASE
    // We check the fd matches and that the device has been acquired before allowing access
    // But, the underlying internal functions use the base addresses of the GIC pages directly
    if ((fd == gic_devices[0].fd) && (gic_devices[0].acquired == true) && (((void *)(arg)) != nullptr)) {
        switch ((ioctl_gic_op_t)request) {
        case IOCTL_GICD_REGS_READ:
            return_value = gicd_regs_read(arg, length);
            break;
        case IOCTL_GICD_REGS_WRITE:
            return_value = gicd_regs_write(arg, length);
            break;
        case IOCTL_GICA_REGS_READ:
            return_value = gica_regs_read(arg, length);
            break;
        case IOCTL_GICA_REGS_WRITE:
            return_value = gica_regs_write(arg, length);
            break;
        case IOCTL_GICT_REGS_READ:
            return_value = gict_regs_read(arg, length);
            break;
        case IOCTL_GICT_REGS_WRITE:
            return_value = gict_regs_write(arg, length);
            break;
        case IOCTL_GICP_REGS_READ:
            return_value = gicp_regs_read(arg, length);
            break;
        case IOCTL_GICP_REGS_WRITE:
            return_value = gicp_regs_write(arg, length);
            break;
        case IOCTL_GITS0_REGS_READ:
            return_value = gits0_regs_read(arg, length);
            break;
        case IOCTL_GITS0_REGS_WRITE:
            return_value = gits0_regs_write(arg, length);
            break;
        case IOCTL_GITS0_TRANSLATER_REGS_READ:
            return_value = gits0_translater_regs_read(arg, length);
            break;
        case IOCTL_GITS0_TRANSLATER_REGS_WRITE:
            return_value = gits0_translater_regs_write(arg, length);
            break;
        case IOCTL_GICR_LPI0_REGS_READ:
            return_value = gicr_lpi0_regs_read(arg, length);
            break;
        case IOCTL_GICR_LPI0_REGS_WRITE:
            return_value = gicr_lpi0_regs_write(arg, length);
            break;
        case IOCTL_GICR_LPI1_REGS_READ:
            return_value = gicr_lpi1_regs_read(arg, length);
            break;
        case IOCTL_GICR_LPI1_REGS_WRITE:
            return_value = gicr_lpi1_regs_write(arg, length);
            break;
        case IOCTL_GICR_LPI2_REGS_READ:
            return_value = gicr_lpi2_regs_read(arg, length);
            break;
        case IOCTL_GICR_LPI2_REGS_WRITE:
            return_value = gicr_lpi2_regs_write(arg, length);
            break;
        case IOCTL_GICR_LPI3_REGS_READ:
            return_value = gicr_lpi3_regs_read(arg, length);
            break;
        case IOCTL_GICR_LPI3_REGS_WRITE:
            return_value = gicr_lpi3_regs_write(arg, length);
            break;
        case IOCTL_GICR_SGI0_REGS_READ:
            return_value = gicr_sgi0_regs_read(arg, length);
            break;
        case IOCTL_GICR_SGI0_REGS_WRITE:
            return_value = gicr_sgi0_regs_write(arg, length);
            break;
        case IOCTL_GICR_SGI1_REGS_READ:
            return_value = gicr_sgi1_regs_read(arg, length);
            break;
        case IOCTL_GICR_SGI1_REGS_WRITE:
            return_value = gicr_sgi1_regs_write(arg, length);
            break;
        case IOCTL_GICR_SGI2_REGS_READ:
            return_value = gicr_sgi2_regs_read(arg, length);
            break;
        case IOCTL_GICR_SGI2_REGS_WRITE:
            return_value = gicr_sgi2_regs_write(arg, length);
            break;
        case IOCTL_GICR_SGI3_REGS_READ:
            return_value = gicr_sgi3_regs_read(arg, length);
            break;
        case IOCTL_GICR_SGI3_REGS_WRITE:
            return_value = gicr_sgi3_regs_write(arg, length);
            break;
        case IOCTL_GICDA_REGS_READ:
            return_value = gicda_regs_read(arg, length);
            break;
        case IOCTL_GICDA_REGS_WRITE:
            return_value = gicda_regs_write(arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t gic_error(int32_t fd) { return 0; }