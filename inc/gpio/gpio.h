
#ifndef GPIO_H
#define GPIO_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    IOCTL_GPIO_SET_DIRECTION,
    IOCTL_GPIO_GET_DIRECTION,
    IOCTL_GPIO_SET_VALUE,
    IOCTL_GPIO_GET_VALUE,
    IOCTL_GPIO_SET_INTERRUPT_TYPE,
    IOCTL_GPIO_GET_INTERRUPT_TYPE,
    IOCTL_GPIO_SET_INTERRUPT_MASK,
    IOCTL_GPIO_GET_INTERRUPT_MASK,
    IOCTL_GPIO_SET_INTERRUPT_ENABLE,
    IOCTL_GPIO_GET_INTERRUPT_ENABLE,
    IOCTL_GPIO_SET_INTERRUPT_POLARITY,
    IOCTL_GPIO_GET_INTERRUPT_POLARITY,
    IOCTL_GPIO_GET_INTERRUPT_STATUS,
    IOCTL_GPIO_GET_INTERRUPT_STATUS_RAW,
    IOCTL_GPIO_SET_DEBOUNCE,
    IOCTL_GPIO_GET_DEBOUNCE,
    IOCTL_GPIO_GET_SYNC,
    IOCTL_GPIO_SET_SYNC,
    IOCTL_GPIO_GET_ID,
    IOCTL_GPIO_GET_VERSION,
    IOCTL_GPIO_GET_CONFIG,

    // adding new elements before this line
    IOCTL_GPIO_END
} ioctl_gpio_op_t;

int32_t gpio_open(const char *name, int32_t flags);
int32_t gpio_close(int32_t fd);
size_t gpio_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags);
size_t gpio_read(int32_t fd, uintptr_t buf, size_t size);
size_t gpio_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags);
size_t gpio_write(int32_t fd, const uintptr_t buf, size_t size);
int32_t gpio_ioctl(int32_t fd, int32_t request, uintptr_t arg);
int32_t gpio_error(int32_t fd);

#endif // GPIO_H
