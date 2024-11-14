#ifndef GPIO_INTERNAL_H
#define GPIO_INTERNAL_H

#include <stdint.h>

int32_t gpio_set_direction(uintptr_t base, uintptr_t arg);
int32_t gpio_get_direction(uintptr_t base, uintptr_t arg);
int32_t gpio_set_value(uintptr_t base, uintptr_t arg);
int32_t gpio_get_value(uintptr_t base, uintptr_t arg);
int32_t gpio_set_interrupt_enable(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_enable(uintptr_t base, uintptr_t arg);
int32_t gpio_set_interrupt_mask(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_mask(uintptr_t base, uintptr_t arg);
int32_t gpio_set_interrupt_type(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_type(uintptr_t base, uintptr_t arg);
int32_t gpio_set_interrupt_polarity(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_polarity(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_status(uintptr_t base, uintptr_t arg);
int32_t gpio_get_interrupt_status_raw(uintptr_t base, uintptr_t arg);
int32_t gpio_set_debounce(uintptr_t base, uintptr_t arg);
int32_t gpio_get_debounce(uintptr_t base, uintptr_t arg);
int32_t gpio_get_sync(uintptr_t base, uintptr_t arg);
int32_t gpio_set_sync(uintptr_t base, uintptr_t arg);
int32_t gpio_get_id(uintptr_t base, uintptr_t arg);
int32_t gpio_get_version(uintptr_t base, uintptr_t arg);
int32_t gpio_get_config(uintptr_t base, uintptr_t arg);

#endif // GPIO_INTERNAL_H
