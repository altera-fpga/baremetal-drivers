#include "watchdog_internal.h"
#include "watchdog.h"
#include "watchdog_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence WATCHDOG controller for an Altera Agilex5e HPS
*/

/*
 * Read watchdog enable state
 */
uint32_t wdt_get_enable_state(int32_t base_address) {

    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    // Get enable status
    return (uint32_t)wdt_reg->wdt_cr_en;
}

/*
 * Enable Watchdog
 */
void wdt_set_enable(int32_t base_address, uint32_t wparam) {

    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    wdt_reg->wdt_cr_en = (uint8_t)(wparam);
}

/*
 * Read watchdog response mode
 */
uint32_t wdt_get_rmod(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_cr_rmod;
}

/*
 * Set watchdog response mode
 */
void wdt_set_rmod(int32_t base_address, uint32_t wparam) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    wdt_reg->wdt_cr_rmod = (uint8_t)wparam;
}

/*
 * Read watchdog reset pulse
 */
uint32_t wdt_get_reset_pulse(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_cr_rpl;
}

/*
 * Set watchdog reset pulse
 */
void wdt_set_reset_pulse(int32_t base_address, uint32_t wparam) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    wdt_reg->wdt_cr_rpl = (uint8_t)wparam;
}

/*
 * Read watchdog time out period
 */
uint32_t wdt_get_top(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_torr_top;
}

/*
 * Set watchdog time out period
 */
void wdt_set_top(int32_t base_address, uint32_t wparam) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    wdt_reg->wdt_torr_top = (uint8_t)wparam;
}

/*
 * Read watchdog initial time out period
 */
uint32_t wdt_get_init_top(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_torr_top_init;
}

/*
 * Set watchdog initial timeout period
 */
void wdt_set_init_top(int32_t base_address, uint32_t wparam) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    wdt_reg->wdt_torr_top_init = (uint8_t)wparam;
}

/*
 * Read watchdog current internal counter
 */
uint32_t wdt_get_ccvr(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_ccvr_bits;
}

/*
 * Read watchdog interrupt status
 */
uint32_t wdt_get_int_status(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_stat_status;
}

/*
 * Read/clear watchdog interrupt
 */
uint32_t wdt_clear_interrupt(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_eoi_clear_int;
}

/*
 * Read watchdog counter width
 */
uint32_t wdt_get_counter_width(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_cnt_width;
}

/*
 * Read watchdog default initial time out period
 */
uint32_t wdt_get_dflt_itop(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_dflt_top_init;
}

/*
 * Read watchdog default time out period
 */
uint32_t wdt_get_dflt_top(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_dflt_top;
}

/*
 * Read watchdog default reset pulse width
 */
uint32_t wdt_get_dflt_rst_pulse(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_dflt_rpl;
}

/*
 * Read watchdog default apb data width
 */
uint32_t wdt_get_apb_dwidth(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_apb_data_wdt;
}

/*
 * Read watchdog pause state
 */
uint32_t wdt_get_pause_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_pause;
}

/*
 * Read watchdog fixed timeout period state
 */
uint32_t wdt_get_fixed_top_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_fixed_top;
}

/*
 * Read watchdog get hardcoded timeout period state
 */
uint32_t wdt_get_hdcoded_top_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_hc_top;
}

/*
 * Read watchdog get hardcoded reset pulse state
 */
uint32_t wdt_get_hdcoded_rstp_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_hc_rmod;
}

/*
 * Read watchdog get default response mode state
 */
uint32_t wdt_get_dflt_rmode_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_dflt_rmod;
}

/*
 * Read watchdog get dual timeout period state
 */
uint32_t wdt_get_dual_top_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_dual_top;
}

/*
 * Read watchdog get always enabled state
 */
uint32_t wdt_get_alwen_state(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_param_1_alw_en;
}

/*
 * Read watchdog comp version
 */
uint32_t wdt_get_comp_version(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_version_bits;
}

/*
 * Read watchdog comp type
 */
uint32_t wdt_get_comp_type(int32_t base_address) {
    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    return (uint32_t)wdt_reg->wdt_comp_type_bits;
}

/*
 * Restart watchdog counter
 */
int32_t wdt_reset_wdt_cnt(int32_t base_address, uint32_t wparam) {
    // default return value to error
    int32_t return_value = -1;

    // Get pointer to address space
    watchdog_regs_bitfields_t *wdt_reg = (watchdog_regs_bitfields_t *)base_address;

    // Restart watchdog if value valid
    if (wparam == (uint32_t)WDT_RESET_VALUE) {
        wdt_reg->wdt_crr_cnt = (uint8_t)wparam;
        return_value = 0;
    }

    return return_value;
}
