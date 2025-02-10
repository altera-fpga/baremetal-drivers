#ifndef RSTMGR_REGS_H
#define RSTMGR_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device.h"
#include <stdint.h>

#include "hps_address_map.h"

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t stat;                 /* RSTMGR_STAT */
    volatile uint32_t _pad_0x4_0x7;         /* *UNDEFINED* */
    volatile uint32_t miscstat;             /* RSTMGR_MISCSTAT */
    volatile uint32_t _pad_0xc_0xf;         /* *UNDEFINED* */
    volatile uint32_t hdsken;               /* RSTMGR_HDSKEN */
    volatile uint32_t hdskreq;              /* RSTMGR_HDSKREQ */
    volatile uint32_t hdskack;              /* RSTMGR_HDSKACK */
    volatile uint32_t hdskstall;            /* RSTMGR_HDSKSTALL */
    volatile uint32_t _pad_0x20_0x23;       /* *UNDEFINED* */
    volatile uint32_t per0modrst;           /* RSTMGR_PER0MODRST */
    volatile uint32_t per1modrst;           /* RSTMGR_PER1MODRST */
    volatile uint32_t brgmodrst;            /* RSTMGR_BRGMODRST */
    volatile uint32_t _pad_0x30_0x3b[3];    /* *UNDEFINED* */
    volatile uint32_t dbgmodrst;            /* RSTMGR_DBGMODRST */
    volatile uint32_t _pad_0x40_0x4b[3];    /* *UNDEFINED* */
    volatile uint32_t brgwarmmask;          /* RSTMGR_BRGWARMMASK */
    volatile uint32_t _pad_0x50_0x5b[3];    /* *UNDEFINED* */
    volatile uint32_t tststa;               /* RSTMGR_TSTSTA */
    volatile uint32_t _pad_0x60_0x63;       /* *UNDEFINED* */
    volatile uint32_t hdsktimeout;          /* RSTMGR_HDSKTIMEOUT */
    volatile uint32_t _pad_0x68_0x6b;       /* *UNDEFINED* */
    volatile uint32_t dbghdsktimeout;       /* RSTMGR_DBGHDSKTIMEOUT */
    volatile uint32_t dbgrstcmplt;          /* RSTMGR_DBGRSTCMPLT */
    volatile uint32_t _pad_0x74_0x7f[3];    /* *UNDEFINED* */
    volatile uint32_t hpsrstcmplt;          /* RSTMGR_HPSRSTCMPLT */
    volatile uint32_t _pad_0x84_0x8f[3];    /* *UNDEFINED* */
    volatile uint32_t cpuinreset;           /* RSTMGR_CPUINRESET */
    volatile uint32_t cpurstrelease;        /* RSTMGR_CPURSTRELEASE */
    volatile uint32_t cpu0_reset_base_low;  /* RSTMGR_CPU0_RESET_BASE_LOW */
    volatile uint32_t cpu0_reset_base_high; /* RSTMGR_CPU0_RESET_BASE_HIGH */
    volatile uint32_t cpu1_reset_base_low;  /* RSTMGR_CPU1_RESET_BASE_LOW */
    volatile uint32_t cpu1_reset_base_high; /* RSTMGR_CPU1_RESET_BASE_HIGH */
    volatile uint32_t cpu2_reset_base_low;  /* RSTMGR_CPU2_RESET_BASE_LOW */
    volatile uint32_t cpu2_reset_base_high; /* RSTMGR_CPU2_RESET_BASE_HIGH */
    volatile uint32_t cpu3_reset_base_low;  /* RSTMGR_CPU3_RESET_BASE_LOW */
    volatile uint32_t cpu3_reset_base_high; /* RSTMGR_CPU3_RESET_BASE_HIGH */
    volatile uint32_t _pad_0xb8_0x100[18];  /* *UNDEFINED* */
} hps_rstmgr_regs_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* RSTMGR_REGS_H */
