
#ifndef RSTMGR_INTERNAL_H
#define RSTMGR_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rstmgr_regs.h"
#include <stddef.h>
#include <stdint.h>

int32_t rstmgr_regs_read(int32_t fd, uintptr_t arg, size_t size);
int32_t rstmgr_regs_write(int32_t fd, uintptr_t arg, size_t size);

int32_t rstmgr_get_stat(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_stat(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_miscstat(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_miscstat(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hdsk_en(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hdsk_en(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hdsk_req(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hdsk_req(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hdsk_ack(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hdsk_ack(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hdsk_stall(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hdsk_stall(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_per0_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_per0_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_per1_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_per1_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_brg_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_brg_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_dbg_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_dbg_modrst(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_brg_warmmask(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_brg_warmmask(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_tst_sta(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_dbg_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_dbg_hdsk_timeout(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_dbg_rst_cmplt(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_dbg_rst_cmplt(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_hps_rst_cmplt(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_hps_rst_cmplt(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu_in_reset(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu_rst_release(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu_rst_release(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu0_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu0_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu0_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu0_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu1_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu1_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu1_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu1_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu2_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu2_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu2_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu2_reset_base_high(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_get_cpu3_reset_base_low(int32_t fd, uintptr_t arg, size_t length);
int32_t rstmgr_set_cpu3_reset_base_low(int32_t fd, uintptr_t arg, size_t length);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* RSTMGR_INTERNAL_H */
