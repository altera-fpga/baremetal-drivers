#ifndef ECC_REGS_H
#define ECC_REGS_H

#include "device.h"
#include <stdint.h>

#include "hps_address_map.h"

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t IP_REV_ID;             /* 0x00: IP_REV_ID */
    volatile uint32_t IP_REV_ID2;            /* 0x04: IP_REV_ID2 */
    volatile uint32_t CTRL;                  /* 0x08: CTRL */
    volatile uint32_t INITSTAT;              /* 0x0c: INITSTAT */
    volatile uint32_t ERRINTEN;              /* 0x10: ERRINTEN */
    volatile uint32_t ERRINTENS;             /* 0x14: ERRINTENS */
    volatile uint32_t ERRINTENR;             /* 0x18: ERRINTENR */
    volatile uint32_t INTMODE;               /* 0x1c: INTMODE */
    volatile uint32_t INTSTAT;               /* 0x20: INTSTAT */
    volatile uint32_t INTTEST;               /* 0x24: INTTEST */
    volatile uint32_t MODSTAT;               /* 0x28: MODSTAT */
    volatile uint32_t DERRADDRA;             /* 0x2c DERRADDRA */
    volatile uint32_t SERRADDRA;             /* 0x30: SERRADDRA */
    volatile uint32_t DERRADDRB;             /* 0x34: DERRADDRB */
    volatile uint32_t SERRADDRB;             /* 0x38: SERRADDRB */
    volatile uint32_t SERRCNTREG;            /* 0x3c: SERRCNTREG */
    volatile uint32_t ECC_Addrbus;           /* 0x40: ECC_Addrbus */
    volatile uint32_t ECC_RData0bus;         /* 0x44: ECC_RData0bus */
    volatile uint32_t ECC_RData1bus;         /* 0x48: ECC_RData1bus */
    volatile uint32_t ECC_RData2bus;         /* 0x4c: ECC_RData2bus */
    volatile uint32_t ECC_RData3bus;         /* 0x50: ECC_RData3bus */
    volatile uint32_t ECC_WData0bus;         /* 0x54: ECC_WData0bus */
    volatile uint32_t ECC_WData1bus;         /* 0x58: ECC_WData1bus */
    volatile uint32_t ECC_WData2bus;         /* 0x5c: ECC_WData2bus */
    volatile uint32_t ECC_WData3bus;         /* 0x60: ECC_WData3bus */
    volatile uint32_t ECC_RDataecc0bus;      /* 0x64: ECC_RDataecc0bus */
    volatile uint32_t ECC_RDataecc1bus;      /* 0x68: ECC_RDataecc1bus */
    volatile uint32_t ECC_WDataecc0bus;      /* 0x6c: ECC_WDataecc0bus */
    volatile uint32_t ECC_WDataecc1bus;      /* 0x70: ECC_WDataecc1bus */
    volatile uint32_t ECC_dbytectrl;         /* 0x74: ECC_dbytectrl */
    volatile uint32_t ECC_accctrl;           /* 0x78: ECC_accctrl */
    volatile uint32_t ECC_startacc;          /* 0x7c: ECC_startacc */
    volatile uint32_t ECC_wdctrl;            /* 0x80: ECC_wdctrl */
    volatile uint32_t ECC_DECODERSTAT;       /* 0x84: ECC_DECODERSTAT */
    volatile uint32_t _pad_0x88_0x8f[2];     /* *UNDEFINED* */
    volatile uint32_t SERRLKUPA0[20];        /* 0x90: SERRLKUPA0 */
    volatile uint32_t SERRLKUPB0[20];        /* 0xE0: SERRLKUPB0 */
    volatile uint32_t _pad_0x130_0x400[180]; /* *UNDEFINED* */
} ecc_regs_t;

#endif