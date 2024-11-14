#include "gpio_internal.h"
#include "gpio_regs.h"

int32_t gpio_set_direction(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_swporta_ddr) = *data;
    return 0;
}

int32_t gpio_get_direction(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_swporta_ddr);
    return 0;
}

int32_t gpio_set_value(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_swporta_dr) = *data;
    return 0;
}

int32_t gpio_get_value(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_swporta_dr);
    return 0;
}

int32_t gpio_set_interrupt_enable(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_inten) = *data;
    return 0;
}

int32_t gpio_get_interrupt_enable(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_inten);
    return 0;
}

int32_t gpio_set_interrupt_mask(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_intmask) = *data;
    return 0;
}

int32_t gpio_get_interrupt_mask(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_intmask);
    return 0;
}

int32_t gpio_set_interrupt_type(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_inttype_level) = *data;
    return 0;
}

int32_t gpio_get_interrupt_type(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_inttype_level);
    return 0;
}

int32_t gpio_set_interrupt_polarity(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_int_polarity) = *data;
    return 0;
}

int32_t gpio_get_interrupt_polarity(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_int_polarity);
    return 0;
}

int32_t gpio_get_interrupt_status(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_intstatus);
    return 0;
}

int32_t gpio_get_interrupt_status_raw(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_raw_intstatus);
    return 0;
}

int32_t gpio_set_debounce(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_debounce) = *data;
    return 0;
}

int32_t gpio_get_debounce(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_debounce);
    return 0;
}

int32_t gpio_get_sync(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_ls_sync);
    return 0;
}

int32_t gpio_set_sync(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    (gpio_regs->gpio_ls_sync) = *data;
    return 0;
}
int32_t gpio_get_id(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_id_code);
    return 0;
}

int32_t gpio_get_version(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint32_t *data = (uint32_t *)arg;
    *data = (gpio_regs->gpio_ver_id_code);
    return 0;
}

int32_t gpio_get_config(uintptr_t base, uintptr_t arg) {
    hps_gpio_regs_t *gpio_regs = (hps_gpio_regs_t *)base;
    uint64_t *data = (uint64_t *)arg;
    *data = ((uint64_t)(gpio_regs->gpio_config_reg2) << 32) | (uint64_t)(gpio_regs->gpio_config_reg1);
    return 0;
}