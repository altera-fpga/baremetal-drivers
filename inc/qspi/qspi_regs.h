#ifndef QSPI_REGS_H__
#define QSPI_REGS_H__

#include "hps_address_map.h"

#define QSPI_CFG_BAUD_RATE_DIV_OFST (uint32_t)(19)
#define QSPI_CFG_BAUD_RATE_DIV_MASK (uint32_t)((uint32_t)(0xF) << QSPI_CFG_BAUD_RATE_DIV_OFST)

#define QSPI_CFG_ENABLE_OFST (uint32_t)(0)
#define QSPI_CFG_ENABLE_MASK (uint32_t)((uint32_t)(0x1) << QSPI_CFG_ENABLE_OFST)

#define QSPI_CFG_CLKPOL_OFST (uint32_t)(1)
#define QSPI_CFG_CLKPOL_MASK (uint32_t)((uint32_t)(0x1) << QSPI_CFG_CLKPOL_OFST)

#define QSPI_CFG_CLKPHASE_OFST (uint32_t)(2)
#define QSPI_CFG_CLKPHASE_MASK (uint32_t)((uint32_t)(0x1) << QSPI_CFG_CLKPHASE_OFST)

#define QSPI_CFG_CS_DECODE_OFST (uint32_t)(9)
#define QSPI_CFG_CS_DECODE_MASK (uint32_t)((uint32_t)(0x1) << QSPI_CFG_CS_DECODE_OFST)

#define QSPI_CFG_CS_SELECT_OFST (uint32_t)(10)
#define QSPI_CFG_CS_SELECT_MASK (uint32_t)((uint32_t)(0xF) << QSPI_CFG_CS_SELECT_OFST)

#define QSPI_CFG_WRITE_PROTECT_PIN_OFST (uint32_t)(14)
#define QSPI_CFG_WRITE_PROTECT_PIN_MASK (uint32_t)((uint32_t)(0x1) << QSPI_CFG_WRITE_PROTECT_PIN_OFST)

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t CFG;         // Offset 0x00
    volatile uint32_t DEVRD;       // Offset 0x04
    volatile uint32_t DEVWR;       // Offset 0x08
    volatile uint32_t DELAY;       // Offset 0x0C
    volatile uint32_t RDDATACAP;   // Offset 0x10
    volatile uint32_t DEVSZ;       // Offset 0x14
    volatile uint32_t SRAMPART;    // Offset 0x18
    volatile uint32_t INDADDRTRIG; // Offset 0x1C
    volatile uint32_t DMAPER;      // Offset 0x20
    volatile uint32_t REMAPADDR;   // Offset 0x24
    volatile uint32_t MODEBIT;     // Offset 0x28
    volatile uint32_t SRAMFILL;    // Offset 0x2C
    volatile uint32_t TXTHRESH;    // Offset 0x30
    volatile uint32_t RXTHRESH;    // Offset 0x34
    volatile uint32_t _pad_0x38_0x3C[2];
    volatile uint32_t IRQSTAT; // Offset 0x40
    volatile uint32_t IRQMASK; // Offset 0x44
    volatile uint32_t _pad_0x48_0x4C[2];
    volatile uint32_t LOWWRPROT;   // Offset 0x50
    volatile uint32_t UPPWRPROT;   // Offset 0x54
    volatile uint32_t WRPROT;      // Offset 0x58
    volatile uint32_t _pad_0x5C;   // Offset 0x5C
    volatile uint32_t INDRD;       // Offset 0x60
    volatile uint32_t INDRDWATER;  // Offset 0x64
    volatile uint32_t INDRDSTADDR; // Offset 0x68
    volatile uint32_t INDRDCNT;    // Offset 0x6C
    volatile uint32_t INDWR;       // Offset 0x70
    volatile uint32_t INDWRWATER;  // Offset 0x74
    volatile uint32_t INDWRSTADDR; // Offset 0x78
    volatile uint32_t INDWRCNT;    // Offset 0x7C
    volatile uint32_t _pad_0x80_0x8C[4];
    volatile uint32_t FLASHCMD;     // Offset 0x90
    volatile uint32_t FLASHCMDADDR; // Offset 0x94
    volatile uint32_t _pad_0x98_0x9C[2];
    volatile uint32_t FLASHCMDRDDATALO; // Offset 0xA0
    volatile uint32_t FLASHCMDRDDATAUP; // Offset 0xA4
    volatile uint32_t FLASHCMDWRDATALO; // Offset 0xA8
    volatile uint32_t FLASHCMDWRDATAUP; // Offset 0xAC
    volatile uint32_t _pad_0xB0_0xF8[18];
    volatile uint32_t MODULEID; // Offset 0xFC
} qspi_regs_t;

#endif // QSPI_REGS_H__