#ifndef I2C_REGS_H
#define I2C_REGS_H

#include "device.h"
#include <stdint.h>

#include "system.h"

#define I2C_CMD_DATA_RESTART ((uint32_t)(1) << (uint32_t)(10))
#define I2C_CMD_DATA_STOP ((uint32_t)(1) << (uint32_t)(9))
#define I2C_CMD_DATA_CMD_READ ((uint32_t)(1) << (uint32_t)(8))
#define I2C_CMD_DATA_CMD_WRITE ((uint32_t)(0) << (uint32_t)(8))

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t I2C_CON;                /* 0x00: I2C_CON */
    volatile uint32_t I2C_TAR;                /* 0x04: I2C_TAR */
    volatile uint32_t I2C_SAR;                /* 0x08: I2C_SAR */
    volatile uint32_t _pad_0xc_0xf;           /* *UNDEFINED* */
    volatile uint32_t I2C_DATA_CMD;           /* 0x10: I2C_DATA_CMD */
    volatile uint32_t I2C_SS_SCL_HCNT;        /* 0x14: I2C_SS_SCL_HCNT */
    volatile uint32_t I2C_SS_SCL_LCNT;        /* 0x18: I2C_SS_SCL_LCNT */
    volatile uint32_t I2C_FS_SCL_HCNT;        /* 0x1C: I2C_FS_SCL_HCNT */
    volatile uint32_t I2C_FS_SCL_LCNT;        /* 0x20: I2C_FS_SCL_LCNT */
    volatile uint32_t _pad_0x24_0x2b[2];      /* *UNDEFINED* */
    volatile uint32_t I2C_INTR_STAT;          /* 0x30: I2C_INTR_STAT */
    volatile uint32_t I2C_INTR_MASK;          /* 0x34: I2C_INTR_MASK */
    volatile uint32_t I2C_RAW_INTR_STAT;      /* 0x38: I2C_RAW_INTR_STAT */
    volatile uint32_t I2C_RX_TL;              /* 0x3C: I2C_RX_TL */
    volatile uint32_t I2C_TX_TL;              /* 0x40: I2C_TX_TL */
    volatile uint32_t I2C_CLR_INTR;           /* 0x44: I2C_CLR_INTR */
    volatile uint32_t I2C_CLR_RX_UNDER;       /* 0x48: I2C_CLR_RX_UNDER */
    volatile uint32_t I2C_CLR_RX_OVER;        /* 0x4C: I2C_CLR_RX_OVER */
    volatile uint32_t I2C_CLR_TX_OVER;        /* 0x50: I2C_CLR_TX_OVER */
    volatile uint32_t I2C_CLR_RD_REQ;         /* 0x54: I2C_CLR_RD_REQ */
    volatile uint32_t I2C_CLR_TX_ABRT;        /* 0x58: I2C_CLR_TX_ABRT */
    volatile uint32_t I2C_CLR_RX_DONE;        /* 0x5C: I2C_CLR_RX_DONE */
    volatile uint32_t I2C_CLR_ACTIVITY;       /* 0x60: I2C_CLR_ACTIVITY */
    volatile uint32_t I2C_CLR_STOP_DET;       /* 0x64: I2C_CLR_STOP_DET */
    volatile uint32_t I2C_CLR_START_DET;      /* 0x68: I2C_CLR_START_DET */
    volatile uint32_t I2C_CLR_GEN_CALL;       /* 0x6C: I2C_CLR_GEN_CALL */
    volatile uint32_t I2C_ENABLE;             /* 0x70: I2C_ENABLE */
    volatile uint32_t I2C_STATUS;             /* 0x74: I2C_STATUS */
    volatile uint32_t I2C_TXFLR;              /* 0x78: I2C_TXFLR */
    volatile uint32_t I2C_RXFLR;              /* 0x7C: I2C_RXFLR */
    volatile uint32_t I2C_SDA_HOLD;           /* 0x80: I2C_SDA_HOLD */
    volatile uint32_t I2C_TX_ABRT_SOURCE;     /* 0x84: I2C_TX_ABRT_SOURCE */
    volatile uint32_t I2C_SLV_DATA_NACK_ONLY; /* 0x88: I2C_SLV_DATA_NACK_ONLY */
    volatile uint32_t I2C_DMA_CR;             /* 0x8C: I2C_DMA_CR */
    volatile uint32_t I2C_DMA_TDLR;           /* 0x90: I2C_DMA_TDLR */
    volatile uint32_t I2C_DMA_RDLR;           /* 0x94: I2C_DMA_RDLR */
    volatile uint32_t I2C_SDA_SETUP;          /* 0x98: I2C_SDA_SETUP */
    volatile uint32_t I2C_ACK_GENERAL_CALL;   /* 0x9C: I2C_ACK_GENERAL_CALL */
    volatile uint32_t I2C_ENABLE_STATUS;      /* 0xA0: I2C_ENABLE_STATUS */
    volatile uint32_t I2C_FS_SPKLEN;          /* 0xA4: I2C_FS_SPKLEN */
    volatile uint32_t _pad_0xa4_0xa7;         /* *UNDEFINED* */
    volatile uint32_t I2C_CLR_RESTART_DET;    /* 0xAC: I2C_CLR_RESTART_DET */
    volatile uint32_t _pad_0xac_0xf3[18];     /* *UNDEFINED* */
    volatile uint32_t I2C_COMP_PARAM_1;       /* 0xF4: I2C_COMP_PARAM_1 */
    volatile uint32_t I2C_COMP_VERSION;       /* 0xF8: I2C_COMP_VERSION */
    volatile uint32_t I2C_COMP_TYPE;          /* 0xFC: I2C_COMP_TYPE */
} i2c_regs_t;

#endif
