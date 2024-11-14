#include "gpio.h"
#include "gpio_internal.h"
#include "gpio_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t gpio_devices[] = {{.name = "/dev/gpio0", .fd = HPS_GPIO0_BASE, .acquired = 0},
                                      {.name = "/dev/gpio1", .fd = HPS_GPIO1_BASE, .acquired = 0}};

int32_t gpio_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(gpio_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(gpio_devices[i].name, name) == 0) {
                if (claim_device(&gpio_devices[i])) {
                    fd = gpio_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t gpio_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(gpio_devices) / sizeof(device_descriptor_t)); i++) {
            if (gpio_devices[i].fd == fd) {
                gpio_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t gpio_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t gpio_read(int32_t fd, uintptr_t buf, size_t size) { return gpio_recv(fd, buf, size, 0); }

size_t gpio_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t gpio_write(int32_t fd, const uintptr_t buf, size_t size) { return gpio_send(fd, buf, size, 0); }

int32_t gpio_ioctl(int32_t fd, int32_t request, uintptr_t arg) {
    int32_t return_value = 0;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((ioctl_gpio_op_t)request) {
        case IOCTL_GPIO_SET_DIRECTION:
            return_value = gpio_set_direction((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_DIRECTION:
            return_value = gpio_get_direction((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_VALUE:
            return_value = gpio_set_value((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_VALUE:
            return_value = gpio_get_value((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_INTERRUPT_TYPE:
            return_value = gpio_set_interrupt_type((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_TYPE:
            return_value = gpio_get_interrupt_type((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_INTERRUPT_MASK:
            return_value = gpio_set_interrupt_mask((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_MASK:
            return_value = gpio_get_interrupt_mask((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_INTERRUPT_ENABLE:
            return_value = gpio_set_interrupt_enable((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_ENABLE:
            return_value = gpio_get_interrupt_enable((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_INTERRUPT_POLARITY:
            return_value = gpio_set_interrupt_polarity((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_POLARITY:
            return_value = gpio_get_interrupt_polarity((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_STATUS:
            return_value = gpio_get_interrupt_status((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_INTERRUPT_STATUS_RAW:
            return_value = gpio_get_interrupt_status_raw((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_DEBOUNCE:
            return_value = gpio_set_debounce((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_DEBOUNCE:
            return_value = gpio_get_debounce((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_SYNC:
            return_value = gpio_get_sync((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_SET_SYNC:
            return_value = gpio_set_sync((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_ID:
            return_value = gpio_get_id((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_VERSION:
            return_value = gpio_get_version((uintptr_t)fd, arg);
            break;
        case IOCTL_GPIO_GET_CONFIG:
            return_value = gpio_get_config((uintptr_t)fd, arg);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t gpio_error(int32_t fd) { return 0; }