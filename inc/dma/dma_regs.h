#ifndef DMA_REGS_H__
#define DMA_REGS_H__

#include "system.h"

#define DMA_CFG_ENABLE_OFST (uint64_t)(0)
#define DMA_CFG_ENABLE_MASK (uint64_t)((uint64_t)(0x1) << DMA_CFG_ENABLE_OFST)
#define DMA_CFG_INT_ENABLE_OFST (uint64_t)(1)
#define DMA_CFG_INT_ENABLE_MASK (uint64_t)((uint64_t)(0x1) << DMA_CFG_INT_ENABLE_OFST)
#define DMA_CHEN_WRITE_EN_ENABLE_OFST (uint64_t)(8)
#define DMA_CHEN_WRITE_EN_ENABLE_MASK (uint64_t)((uint64_t)(0xF) << DMA_CHEN_WRITE_EN_ENABLE_OFST)
#define DMA_CHEN_WRITE_EN_SUSPEND_OFST (uint64_t)(24)
#define DMA_CHEN_WRITE_EN_SUSPEND_MASK (uint64_t)((uint64_t)(0xFF) << DMA_CHEN_WRITE_EN_SUSPEND_OFST)
#define DMA_CHEN_WRITE_EN_ABORT_OFST (uint64_t)(40)
#define DMA_CHEN_WRITE_EN_ABORT_MASK (uint64_t)((uint64_t)(0xFF) << DMA_CHEN_WRITE_EN_ABORT_OFST)
#define DMA_CHEN_ENABLE_OFST (uint64_t)(0)
#define DMA_CHEN_ENABLE_MASK (uint64_t)((uint64_t)(0xF) << DMA_CHEN_ENABLE_OFST)
#define DMA_CHEN_SUSPEND_OFST (uint64_t)(16)
#define DMA_CHEN_SUSPEND_MASK (uint64_t)((uint64_t)(0xFF) << DMA_CHEN_SUSPEND_OFST)
#define DMA_CHEN_ABORT_OFST (uint64_t)(32)
#define DMA_CHEN_ABORT_MASK (uint64_t)((uint64_t)(0xFF) << DMA_CHEN_ABORT_OFST)

#define DMA_CTL_SRC_TR_WIDTH_OFST (uint64_t)(8)
#define DMA_CTL_SRC_TR_WIDTH_MASK (uint64_t)((uint64_t)(0x7) << DMA_CTL_SRC_TR_WIDTH_OFST)
#define DMA_CTL_DST_TR_WIDTH_OFST (uint64_t)(11)
#define DMA_CTL_DST_TR_WIDTH_MASK (uint64_t)((uint64_t)(0x7) << DMA_CTL_SRC_TR_WIDTH_OFST)
#define DMA_CTL_SHADOWREG_OR_LLI_VALID_OFST (uint64_t)(63)
#define DMA_CTL_SHADOWREG_OR_LLI_VALID_MASK (uint64_t)((uint64_t)(0x1) << DMA_CTL_SHADOWREG_OR_LLI_VALID_OFST)
#define DMA_CTL_SHADOWREG_OR_LLI_LAST_OFST (uint64_t)(62)
#define DMA_CTL_SHADOWREG_OR_LLI_LAST_MASK (uint64_t)((uint64_t)(0x1) << DMA_CTL_SHADOWREG_OR_LLI_LAST_OFST)
#define DMA_CHx_BLOCK_TS_OFST (uint64_t)(0)
#define DMA_CHx_BLOCK_TS_MASK (uint64_t)((uint64_t)(0x3FFFFF) << DMA_CHx_BLOCK_TS_OFST)
#define DMA_CHx_LLP_LOC_MASK (uint64_t)(0xFFFFFFFFFFFFFFC0u)

#define DMA_CHx_CFG2_TT_FC_OFST (uint64_t)(32)
#define DMA_CHx_CFG2_TT_FC_MASK (uint64_t)((uint64_t)(0x7) << DMA_CHx_CFG2_TT_FC_OFST)

#define DMA_CHx_INTSTS_BLOCK_TFR_DONE 0x1
#define DMA_CHx_INTSTS_DMA_TFR_DONE 0x2
#define DMA_CHx_INTSTS_SRC_TRANSCOMP 0x8
#define DMA_CHx_INTSTS_DST_TRANSCOMP 0x10

typedef struct __attribute__((packed)) __attribute__((aligned(8))) {
    volatile uint64_t SAR;                  // Offset 0x00
    volatile uint64_t DAR;                  // Offset 0x08
    volatile uint64_t BLOCK_TS;             // Offset 0x10
    volatile uint64_t CTL;                  // Offset 0x18
    volatile uint64_t CFG2;                 // Offset 0x20
    volatile uint64_t LLP;                  // Offset 0x28
    volatile uint64_t STATUSREG;            // Offset 0x30
    volatile uint64_t SWHSSRCREG;           // Offset 0x38
    volatile uint64_t SWHSDSTREG;           // Offset 0x40
    volatile uint64_t BLK_TFR_RESUMEREQREG; // Offset 0x48
    volatile uint64_t AXI_IDREG;            // Offset 0x50
    volatile uint64_t AXI_QOSREG;           // Offset 0x58
    volatile uint64_t _pad_0x60_0x78[4];
    volatile uint64_t INTSTATUS_ENABLEREG; // Offset 0x80
    volatile uint64_t INTSTATUS;           // Offset 0x88
    volatile uint64_t INTSIGNAL_ENABLEREG; // Offset 0x90
    volatile uint64_t INTCLEARREG;         // Offset 0x98
    volatile uint64_t _pad_0xA0_0xF8[12];
} dma_chan_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(8))) {
    volatile uint64_t IDREG;      // Offset 0x00
    volatile uint64_t COMPVERREG; // Offset 0x08
    volatile uint64_t CFGREG;     // Offset 0x10
    volatile uint64_t CHENREG;    // Offset 0x18
    volatile uint64_t _pad_0x20_0x28[2];
    volatile uint64_t INTSTATUSREG;                  // Offset 0x30
    volatile uint64_t COMMONREG_INTCLEARREG;         // Offset 0x38
    volatile uint64_t COMMONREG_INTSTATUS_ENABLEREG; // Offset 0x40
    volatile uint64_t COMMONREG_INTSIGNAL_ENABLEREG; // Offset 0x48
    volatile uint64_t COMMONREG_INTSTATUSREG;        // Offset 0x50
    volatile uint64_t RESETREG;                      // Offset 0x58
    volatile uint64_t LOWPOWER_CFGREG;               // Offset 0x60
    volatile uint64_t _pad_0x68_0xF8[19];
    volatile dma_chan_regs_t dma_ch[4]; // Offset 0x100/0x200/0x300/0x400
} dma_regs_t;

#endif // DMA_REGS_H__