#include "timer_internal.h"
#include "timer_regs.h"
#include <string.h>

int32_t timer_regs_read(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(hps_timer_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (const void *)base, sizeof(hps_timer_regs_t));
        return_value = 0;
    }
    return return_value;
}

int32_t timer_regs_write(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(hps_timer_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)base, (const void *)arg, sizeof(hps_timer_regs_t));
        return_value = 0;
    }
    return return_value;
}

int32_t timer_count_set(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        timer->TIMER1LOADCOUNT = buffer[0];
        return_value = 0;
    }
    return return_value;
}
int32_t timer_count_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMER1LOADCOUNT;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_current_val_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMER1CURRENTVAL;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_control_set(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        timer->TIMER1CONTROLREG = buffer[0];
        return_value = 0;
    }
    return return_value;
}
int32_t timer_control_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMER1CONTROLREG;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_int_stat_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMER1INTSTAT;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_timers_int_stat_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMERSINTSTAT;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_timers_raw_int_stat_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMERSRAWINTSTAT;
        return_value = 0;
    }
    return return_value;
}
int32_t timer_timers_eoi_apply(uintptr_t base, uintptr_t arg, size_t length) {
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t temp = 0;
    /*
    End of Interrupt is applied by reading the EOI register.
    The read operation clears the interrupt.
    */
    temp = timer->TIMERSEOI;
    // The register value has no meaning, but we return temp
    // This avoids the compiler warning about an unused variable
    return (int32_t)temp;
}
int32_t timer_timer_eoi_apply(uintptr_t base, uintptr_t arg, size_t length) {
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t temp = 0;
    /*
    End of Interrupt is applied by reading the EOI register.
    The read operation clears the interrupt.
    */
    temp = timer->TIMER1EOI;
    // The register value has no meaning, but we return temp
    // This avoids the compiler warning about an unused variable
    return (int32_t)temp;
}
int32_t timer_comp_version_get(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    hps_timer_regs_t *timer = (hps_timer_regs_t *)base;
    uint32_t *buffer = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buffer[0] = timer->TIMERSCOMPVERSION;
        return_value = 0;
    }
    return return_value;
}
