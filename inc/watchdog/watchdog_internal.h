#ifndef WATCHDOG_INTERNAL_H
#define WATCHDOG_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence WATCHDOG controller for an Altera Agilex5e HPS
*/

/*
 * Read watchdog get always enabled state
 */
uint32_t wdt_get_alwen_state(int32_t base_address);

/*
 * Read watchdog default apb data width
 */
uint32_t wdt_get_apb_dwidth(int32_t base_address);

/*
 * Read watchdog current internal counter
 */
uint32_t wdt_get_ccvr(int32_t base_address);

/*
 * Read watchdog comp type
 */
uint32_t wdt_get_comp_type(int32_t base_address);

/*
 * Read watchdog comp version
 */
uint32_t wdt_get_comp_version(int32_t base_address);

/*
 * Read watchdog counter width
 */
uint32_t wdt_get_counter_width(int32_t base_address);

/*
 * Read watchdog default initial time out period
 */
uint32_t wdt_get_dflt_itop(int32_t base_address);

/*
 * Read watchdog get default response mode state
 */
uint32_t wdt_get_dflt_rmode_state(int32_t base_address);

/*
 * Read watchdog default reset pulse width
 */
uint32_t wdt_get_dflt_rst_pulse(int32_t base_address);

/*
 * Read watchdog default time out period
 */
uint32_t wdt_get_dflt_top(int32_t base_address);

/*
 * Read watchdog get dual timeout period state
 */
uint32_t wdt_get_dual_top_state(int32_t base_address);

/*
 * Read watchdog enable state
 */
uint32_t wdt_get_enable_state(int32_t base_address);

/*
 * Read watchdog fixed timeout period state
 */
uint32_t wdt_get_fixed_top_state(int32_t base_address);

/*
 * Read watchdog get hardcoded reset pulse state
 */
uint32_t wdt_get_hdcoded_rstp_state(int32_t base_address);

/*
 * Read watchdog get hardcoded timeout period state
 */
uint32_t wdt_get_hdcoded_top_state(int32_t base_address);

/*
 * Read watchdog time out period
 */
uint32_t wdt_get_init_top(int32_t base_address);

/*
 * Read watchdog interrupt status
 */
uint32_t wdt_get_int_status(int32_t base_address);

/*
 * Read watchdog pause state
 */
uint32_t wdt_get_pause_state(int32_t base_address);

/*
 * Read watchdog reset pulse
 */
uint32_t wdt_get_reset_pulse(int32_t base_address);

/*
 * Read watchdog response mode
 */
uint32_t wdt_get_rmod(int32_t base_address);

/*
 * Read watchdog time out period
 */
uint32_t wdt_get_top(int32_t base_address);

/*
 * Set watchdog time out period
 */
void wdt_set_ccvr(int32_t base_address, uint32_t wparam);

/*
 * Read/clear watchdog interrupt
 */
uint32_t wdt_clear_interrupt(int32_t base_address);

/*
 * Restart watchdog counter
 */
int32_t wdt_reset_wdt_cnt(int32_t base_address, uint32_t wparam);

/*
 * Enable Watchdog
 */
void wdt_set_enable(int32_t base_address, uint32_t wparam);

/*
 * Set watchdog initial timeout period
 */
void wdt_set_init_top(int32_t base_address, uint32_t wparam);

/*
 * Set watchdog reset pulse
 */
void wdt_set_reset_pulse(int32_t base_address, uint32_t wparam);

/*
 * Set watchdog response mode
 */
void wdt_set_rmod(int32_t base_address, uint32_t wparam);

/*
 * Set watchdog time out period
 */
void wdt_set_top(int32_t base_address, uint32_t wparam);

#endif // WATCHDOG_INTERNAL_H
