#ifndef spi_REGS_H
#define spi_REGS_H

#include <stdint.h>

#include "hps_address_map.h"

#define spi_CTRLR0_FRF_BIT_OFST ((uint32_t)(21))
#define spi_CTRLR0_FRF_MASK ((uint32_t)(((uint32_t)0x3) << spi_CTRLR0_FRF_BIT_OFST))

#define spi_CTRLR0_DFS_32_BIT_OFST ((uint32_t)(16))
#define spi_CTRLR0_DFS_32_MASK ((uint32_t)(((uint32_t)0x1f) << spi_CTRLR0_DFS_32_BIT_OFST))

#define spi_CTRLR0_CFS_BIT_OFST ((uint32_t)(12))
#define spi_CTRLR0_CFS_MASK ((uint32_t)(((uint32_t)0xf) << spi_CTRLR0_CFS_BIT_OFST))

#define spi_CTRLR0_TMOD_BIT_OFST ((uint32_t)(8))
#define spi_CTRLR0_TMOD_MASK ((uint32_t)(((uint32_t)0x3) << spi_CTRLR0_TMOD_BIT_OFST))

#define spi_CTRLR0_SCPH_BIT_OFST ((uint32_t)(6))
#define spi_CTRLR0_SCPH_MASK ((uint32_t)(((uint32_t)1) << spi_CTRLR0_SCPH_BIT_OFST))

#define spi_CTRLR0_SCPOL_BIT_OFST ((uint32_t)(7))
#define spi_CTRLR0_SCPOL_MASK ((uint32_t)(((uint32_t)1) << spi_CTRLR0_SCPOL_BIT_OFST))

#define spi_CTRLR1_NDF_MASK ((uint32_t)0x0000ffff)

#define spi_SR_TFE_BIT_OFST ((uint32_t)(2))
#define spi_SR_TFE_MASK ((uint32_t)(((uint32_t)1) << spi_SR_TFE_BIT_OFST))

#define spi_SR_RFNE_BIT_OFST ((uint32_t)(3))
#define spi_SR_RFNE_MASK ((uint32_t)(((uint32_t)1) << spi_SR_RFNE_BIT_OFST))

#define spi_MWCR_MHS_BIT_OFST ((uint32_t)(2))
#define spi_MWCR_MHS_MASK ((uint32_t)(((uint32_t)1) << spi_MWCR_MHS_BIT_OFST))

#define spi_MWCR_MDD_BIT_OFST ((uint32_t)(1))
#define spi_MWCR_MDD_MASK ((uint32_t)(((uint32_t)1) << spi_MWCR_MDD_BIT_OFST))

#define spi_MWCR_MWMOD_BIT_OFST ((uint32_t)(0))
#define spi_MWCR_MWMOD_MASK ((uint32_t)(((uint32_t)1) << spi_MWCR_MWMOD_BIT_OFST))

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t CTRLR0;         /* ALT_spi_CTRLR0 */
    volatile uint32_t CTRLR1;         /* ALT_spi_CTRLR1 */
    volatile uint32_t SSIENR;         /* ALT_spi_SSIENR */
    volatile uint32_t MWCR;           /* ALT_spi_MWCR */
    volatile uint32_t SER;            /* ALT_spi_SER */
    volatile uint32_t BAUDR;          /* ALT_spi_BAUDR */
    volatile uint32_t TXFTLR;         /* ALT_spi_TXFTLR */
    volatile uint32_t RXFTLR;         /* ALT_spi_RXFTLR */
    volatile uint32_t TXFLR;          /* ALT_spi_TXFLR */
    volatile uint32_t RXFLR;          /* ALT_spi_RXFLR */
    volatile uint32_t SR;             /* ALT_spi_SR */
    volatile uint32_t IMR;            /* ALT_spi_IMR */
    volatile uint32_t ISR;            /* ALT_spi_ISR */
    volatile uint32_t RISR;           /* ALT_spi_RISR */
    volatile uint32_t TXOICR;         /* ALT_spi_TXOICR */
    volatile uint32_t RXOICR;         /* ALT_spi_RXOICR */
    volatile uint32_t RXUICR;         /* ALT_spi_RXUICR */
    volatile uint32_t MSTICR;         /* ALT_spi_MSTICR */
    volatile uint32_t ICR;            /* ALT_spi_ICR */
    volatile uint32_t DMACR;          /* ALT_spi_DMACR */
    volatile uint32_t DMATDLR;        /* ALT_spi_DMATDLR */
    volatile uint32_t DMARDLR;        /* ALT_spi_DMARDLR */
    volatile uint32_t IDR;            /* ALT_spi_IDR */
    volatile uint32_t SSI_VERSION_ID; /* ALT_spi_SSI_VERSION_ID */
    volatile uint32_t DR0;            /* ALT_spi_DR0 */
    volatile uint32_t DR1;            /* ALT_spi_DR1 */
    volatile uint32_t DR2;            /* ALT_spi_DR2 */
    volatile uint32_t DR3;            /* ALT_spi_DR3 */
    volatile uint32_t DR4;            /* ALT_spi_DR4 */
    volatile uint32_t DR5;            /* ALT_spi_DR5 */
    volatile uint32_t DR6;            /* ALT_spi_DR6 */
    volatile uint32_t DR7;            /* ALT_spi_DR7 */
    volatile uint32_t DR8;            /* ALT_spi_DR8 */
    volatile uint32_t DR9;            /* ALT_spi_DR9 */
    volatile uint32_t DR10;           /* ALT_spi_DR10 */
    volatile uint32_t DR11;           /* ALT_spi_DR11 */
    volatile uint32_t DR12;           /* ALT_spi_DR12 */
    volatile uint32_t DR13;           /* ALT_spi_DR13 */
    volatile uint32_t DR14;           /* ALT_spi_DR14 */
    volatile uint32_t DR15;           /* ALT_spi_DR15 */
    volatile uint32_t DR16;           /* ALT_spi_DR16 */
    volatile uint32_t DR17;           /* ALT_spi_DR17 */
    volatile uint32_t DR18;           /* ALT_spi_DR18 */
    volatile uint32_t DR19;           /* ALT_spi_DR19 */
    volatile uint32_t DR20;           /* ALT_spi_DR20 */
    volatile uint32_t DR21;           /* ALT_spi_DR21 */
    volatile uint32_t DR22;           /* ALT_spi_DR22 */
    volatile uint32_t DR23;           /* ALT_spi_DR23 */
    volatile uint32_t DR24;           /* ALT_spi_DR24 */
    volatile uint32_t DR25;           /* ALT_spi_DR25 */
    volatile uint32_t DR26;           /* ALT_spi_DR26 */
    volatile uint32_t DR27;           /* ALT_spi_DR27 */
    volatile uint32_t DR28;           /* ALT_spi_DR28 */
    volatile uint32_t DR29;           /* ALT_spi_DR29 */
    volatile uint32_t DR30;           /* ALT_spi_DR30 */
    volatile uint32_t DR31;           /* ALT_spi_DR31 */
    volatile uint32_t DR32;           /* ALT_spi_DR32 */
    volatile uint32_t DR33;           /* ALT_spi_DR33 */
    volatile uint32_t DR34;           /* ALT_spi_DR34 */
    volatile uint32_t DR35;           /* ALT_spi_DR35 */
    volatile uint32_t RX_SAMPLE_DLY;  /* ALT_spi_RX_SAMPLE_DLY */
    volatile uint32_t _pad_0xf4_0xf7; /* *UNDEFINED* */
    volatile uint32_t RSVD_1;         /* ALT_spi_RSVD_1 */
    volatile uint32_t RSVD_2;         /* ALT_spi_RSVD_2 */
} spi_regs_t;

#endif // spi_REGS_H
