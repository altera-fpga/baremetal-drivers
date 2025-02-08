#ifndef WATCHDOG_REGS_H__
#define WATCHDOG_REGS_H__

/*
 * Watchdog Timer Documentation Overview
 *  -- Register Map
 *     -- "i_watchdog_#_0x10D0_0#00.html"
 *  -- High-Level Architecture Specification
 *     --  "SM HPS Watchdog Timers HAS .8.pdf"
 */

// Endianness verification "Little Endian only supported"
#ifdef __BYTE_ORDER__
#if (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
#error "The processor setting's are invalid for the watchdog"
#endif
#else
#pragma message "Assuming the native endianness is little endian"
#endif

#include "hps_address_map.h"

/*
 * structure yielding access to both watchdog timer parameters worda
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t wdt_cr;               // Offset 0x00
    volatile uint32_t wdt_torr;             // Offset 0x04
    volatile uint32_t wdt_ccvr;             // Offset 0x08
    volatile uint32_t wdt_crr;              // Offset 0x0C
    volatile uint32_t wdt_stat;             // Offset 0x10
    volatile uint32_t wdt_eoi;              // Offset 0x14
    volatile uint32_t __pad__0x18_0xf0[55]; // Offset 0x18-0xf0
    volatile uint32_t wdt_comp_param_1;     // Offset 0xf4
    volatile uint32_t wdt_comp_version;     // Offset 0xf8
    volatile uint32_t wdt_comp_type;        // Offset 0xfc
} watchdog_regs_words_t;

/*
 * structure yielding access to both watchdog timer parameters bits
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t wdt_cr_en : 1;                      // Offset 0x00 Watchdog timer enable
    volatile uint32_t wdt_cr_rmod : 1;                    // Offset 0x00 Watchdog timer Response mode setting
                                                          // "interrupt or immediate reset"
    volatile uint32_t wdt_cr_rpl : 3;                     // Offset 0x00 Watchdog timer Reset Pulse length "
    volatile uint32_t wdt_cr_reserved : 27;               // Offset 0x00 Watchdog reserved bits of wdt_cr
    volatile uint32_t wdt_torr_top : 4;                   // Offset 0x04 Watchdog timer Time out period
    volatile uint32_t wdt_torr_top_init : 4;              // Offset 0x04 Watchdog iniial timer Time out period
    volatile uint32_t wdt_torr_reserved : 24;             // Offset 0x04 reserved bits of wdt torr
    volatile uint32_t wdt_ccvr_bits : 32;                 // Offset 0x08 Watchdog timer internal counter value
    volatile uint32_t wdt_crr_cnt : 8;                    // Offset 0x0C Watchdog timer counter register bits
    volatile uint32_t wdt_crr_reserved : 24;              // Offset 0x0C reserved bits of wdt_crr
    volatile uint32_t wdt_stat_status : 1;                // Offset 0x10 Watchdog timer interrupt status
    volatile uint32_t wdt_stat_reserved : 31;             // Offset 0x10 reserved bits of wdt_stat
    volatile uint32_t wdt_eoi_clear_int : 1;              // Offset 0x14 Watchdog timer interrupt clear register
    volatile uint32_t wdt_eoi_reserved : 31;              // Offset 0x14 reserved bits of wdt_eoi
    volatile uint32_t wdt_comp_param_1_alw_en : 1;        // Offset 0xf4 Watchdog timer Always enable
    volatile uint32_t wdt_comp_param_1_dflt_rmod : 1;     // Offset 0xf4 Watchdog timer default rmod
    volatile uint32_t wdt_comp_param_1_dual_top : 1;      // Offset 0xf4 Watchdog timer dual top
    volatile uint32_t wdt_comp_param_1_hc_rmod : 1;       // Offset 0xf4 Watchdog timer hc rmod
    volatile uint32_t wdt_comp_param_1_hc_rpl : 1;        // Offset 0xf4 Watchdog timer hc rpl
    volatile uint32_t wdt_comp_param_1_hc_top : 1;        // Offset 0xf4 Watchdog timer hc top
    volatile uint32_t wdt_comp_param_1_fixed_top : 1;     // Offset 0xf4 Watchdog timer fixed top
    volatile uint32_t wdt_comp_param_1_pause : 1;         // Offset 0xf4 Watchdog timer pause
    volatile uint32_t wdt_comp_param_1_apb_data_wdt : 2;  // Offset 0xf4 Watchdog timer apb data width
    volatile uint32_t wdt_comp_param_1_dflt_rpl : 3;      // Offset 0xf4 Watchdog timer default rpl
    volatile uint32_t wdt_comp_param_1_reserved : 3;      // Offset 0xf4 reserved set 1
    volatile uint32_t wdt_comp_param_1_dflt_top : 4;      // Offset 0xf4 Watchdog timer default top
    volatile uint32_t wdt_comp_param_1_dflt_top_init : 4; // Offset 0xf4 Watchdog timer default top init
    volatile uint32_t wdt_comp_param_1_cnt_width : 5;     // Offset 0xf4 Watchdog timer default top init
    volatile uint32_t wdt_comp_param_1_reserved_2 : 3;    // Offset 0xf4 reserved set 2
    volatile uint32_t wdt_comp_version_bits : 32;         // Offset 0xf8 Watchdog timer ASCII value for version
    volatile uint32_t wdt_comp_type_bits : 32;            // Offset 0xfc Watchdog timer component type
} watchdog_regs_bitfields_t;

#ifdef WDT_UNION_DEF
/*
 * union yielding access to both watchdog timer parameters as words and bitfields
 */
union watchdog_regs_un {
    watchdog_regs_words_t wdt_reg_word;
    watchdog_regs_bitfields_t wdt_reg_bit;
};

typedef union watchdog_regs_un watchdog_regs_u;
#endif //

#endif // WATCHDOG_REGS_H__
