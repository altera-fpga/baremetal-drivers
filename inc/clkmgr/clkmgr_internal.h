#ifndef CLKMGR_INTERNAL_H
#define CLKMGR_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t clkmgr_regs_read(uintptr_t arg);
int32_t clkmgr_regs_write(uintptr_t arg);
int32_t clkmgr_mainpll_regs_read(uintptr_t arg);
int32_t clkmgr_mainpll_regs_write(uintptr_t arg);
int32_t clkmgr_perpll_regs_read(uintptr_t arg);
int32_t clkmgr_perpll_regs_write(uintptr_t arg);
int32_t clkmgr_ctlgrp_regs_read(uintptr_t arg);
int32_t clkmgr_ctlgrp_regs_write(uintptr_t arg);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CLKMGR_INTERNAL_H
