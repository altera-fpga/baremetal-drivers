#ifndef COMBOPHY_INTERNAL_H
#define COMBOPHY_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence COMBOPHY controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t combophy_read_regs(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_write_regs(int32_t base_address, uintptr_t param, size_t length);

// Dataslice register bank access
int32_t combophy_get_dq_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_dq_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dqs_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_dqs_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_gate_lpbk_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_gate_lpbk_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dll_master_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_dll_master_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dll_slave_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_dll_slave_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_ie_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_ie_timing(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_obs_reg_0(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dll_obs_reg0(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dll_obs_reg1(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_dll_obs_reg2(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_static_togg(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_static_togg(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_wr_deskew(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_wr_deskew(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_wr_rd_deskew_cmd(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_wr_rd_deskew_cmd(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_wr_deskew_pd_ctrl0(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_wr_deskew_pd_ctrl0(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_wr_deskew_pd_ctrl1(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_wr_deskew_pd_ctrl1(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_rd_deskew(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_rd_deskew(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_version(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_features(int32_t base_address, uintptr_t param, size_t length);

// CTB register bank access
int32_t combophy_get_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_get_tsel(int32_t base_address, uintptr_t param, size_t length);
int32_t combophy_set_tsel(int32_t base_address, uintptr_t param, size_t length);

#endif // COMBOPHY_INTERNAL_H