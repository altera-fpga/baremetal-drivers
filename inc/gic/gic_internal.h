#ifndef GIC_INTERNAL_H
#define GIC_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

#include "gic_regs.h"

int32_t gicd_regs_read(uintptr_t arg, size_t length);
int32_t gicd_regs_write(uintptr_t arg, size_t length);
int32_t gica_regs_read(uintptr_t arg, size_t length);
int32_t gica_regs_write(uintptr_t arg, size_t length);
int32_t gict_regs_read(uintptr_t arg, size_t length);
int32_t gict_regs_write(uintptr_t arg, size_t length);
int32_t gicp_regs_read(uintptr_t arg, size_t length);
int32_t gicp_regs_write(uintptr_t arg, size_t length);
int32_t gits0_regs_read(uintptr_t arg, size_t length);
int32_t gits0_regs_write(uintptr_t arg, size_t length);
int32_t gits0_translater_regs_read(uintptr_t arg, size_t length);
int32_t gits0_translater_regs_write(uintptr_t arg, size_t length);
int32_t gicr_lpi0_regs_read(uintptr_t arg, size_t length);
int32_t gicr_lpi0_regs_write(uintptr_t arg, size_t length);
int32_t gicr_lpi1_regs_read(uintptr_t arg, size_t length);
int32_t gicr_lpi1_regs_write(uintptr_t arg, size_t length);
int32_t gicr_lpi2_regs_read(uintptr_t arg, size_t length);
int32_t gicr_lpi2_regs_write(uintptr_t arg, size_t length);
int32_t gicr_lpi3_regs_read(uintptr_t arg, size_t length);
int32_t gicr_lpi3_regs_write(uintptr_t arg, size_t length);
int32_t gicr_sgi0_regs_read(uintptr_t arg, size_t length);
int32_t gicr_sgi0_regs_write(uintptr_t arg, size_t length);
int32_t gicr_sgi1_regs_read(uintptr_t arg, size_t length);
int32_t gicr_sgi1_regs_write(uintptr_t arg, size_t length);
int32_t gicr_sgi2_regs_read(uintptr_t arg, size_t length);
int32_t gicr_sgi2_regs_write(uintptr_t arg, size_t length);
int32_t gicr_sgi3_regs_read(uintptr_t arg, size_t length);
int32_t gicr_sgi3_regs_write(uintptr_t arg, size_t length);
int32_t gicda_regs_read(uintptr_t arg, size_t length);
int32_t gicda_regs_write(uintptr_t arg, size_t length);

#endif // GIC_INTERNAL_H
