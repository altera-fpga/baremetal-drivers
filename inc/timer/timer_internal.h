#ifndef TIMER_INTERNAL_H
#define TIMER_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

int32_t timer_regs_read(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_regs_write(uintptr_t base, uintptr_t arg, size_t length);

int32_t timer_count_set(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_count_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_current_val_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_control_set(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_control_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_int_stat_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_timers_int_stat_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_timers_raw_int_stat_get(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_timers_eoi_apply(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_timer_eoi_apply(uintptr_t base, uintptr_t arg, size_t length);
int32_t timer_comp_version_get(uintptr_t base, uintptr_t arg, size_t length);

#endif // TIMER_INTERNAL_H