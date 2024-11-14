#ifndef SDMMC_INTERNAL_H
#define SDMMC_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence SDMMC controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t sdmmc_read_internal(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_write_internal(int32_t base_address, uintptr_t param, size_t length);

// HRS register bank access
int32_t sdmmc_get_hrs00(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs00(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs00_swr(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs01(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs01(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs04(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs04(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs05(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs05(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs06(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs06(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs07(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs07(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs08_phy_dll_updreq(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs09(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_phy_sw_reset(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_extended_rd_mode(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_extended_wr_mode(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_rdcmd_en(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_rddata_en(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_lvsi_tcksel(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs09_lvsi_cnt(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs12(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs12(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs13(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs13(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs16(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs16(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs29(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs30(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs31(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs32(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs32(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs32_addr(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_hrs32_load(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs33(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_hrs34(int32_t base_address, uintptr_t param, size_t length);

// SRS register bank access
int32_t sdmmc_get_srs00(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs00(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs01(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs01(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs04(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs05(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs06(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs07(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs09(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs11(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_ice(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_sdce(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_sdcfsh(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_sdcfsl(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_dtcv(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_srfa(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_srcmd(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs11_srdat(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs12(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs12(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs13(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs13(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs15(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_ums(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_v18se(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_dss(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_extng(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_scs(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_lvsiexec(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_adma2lm(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_cmd23e(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_hv4e(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_a64b(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs15_pve(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs16(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs17(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs18(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs19(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs20(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs20(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs21(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs22(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs22(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs23(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs23(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs24(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs25(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs26(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs27(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs30(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs30(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_srs31(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_srs31(int32_t base_address, uintptr_t param, size_t length);

// CRS register bank access
int32_t sdmmc_get_crs63(int32_t base_address, uintptr_t param, size_t length);

// CQRS register bank access
int32_t sdmmc_get_cqrs00(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs01(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs02(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs03(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs04(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs04(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs05(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs05(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs06(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs06(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs07(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqictoval(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqictovalen(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqiccth(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqiccthwen(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqicctr(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs07_cqiced(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs08(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs09(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs09(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs10(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs11(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs11(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs12(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs13(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs14(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs16(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs16(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs17(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs17(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs18(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs20(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_set_cqrs20(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs21(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs22(int32_t base_address, uintptr_t param, size_t length);
int32_t sdmmc_get_cqrs23(int32_t base_address, uintptr_t param, size_t length);

#endif // SDMMC_INTERNAL_H