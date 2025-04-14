#ifndef ecc_INTERNAL_H
#define ecc_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls the ECC controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t ecc_regs_read(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_regs_write(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ip_rev_id(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ip_rev_id2(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_initstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_initstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_errinten(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_errinten(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_errintens(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_errintens(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_errintenr(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_errintenr(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_intmode(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_intmode(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_intstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_intstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_inttest(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_inttest(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_modstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_modstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_derraddra(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_serraddra(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_derraddrb(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_serraddrb(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_serrcntreg(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_serrcntreg(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_addrbus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_addrbus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdata0bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdata1bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdata2bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdata3bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdata0bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdata1bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdata2bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdata3bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdataecc0bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_rdataecc1bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdataecc0bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdataecc1bus(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_dbytectrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_dbytectrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_accctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_accctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_startacc(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_startacc(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_wdctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_wdctrl(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_ecc_decoderstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_ecc_decoderstat(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_serrlkupa0(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_serrlkupa0(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_get_serrlkupb0(int32_t base_address, uintptr_t param, size_t length);
int32_t ecc_set_serrlkupb0(int32_t base_address, uintptr_t param, size_t length);

#endif