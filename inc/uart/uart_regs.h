#ifndef UART_REGS_H
#define UART_REGS_H

#include "device.h"
#include <stdint.h>

#include "hps_address_map.h"

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t RBR;                // 0x00
    volatile uint32_t IER;                // 0x04
    volatile uint32_t IIR;                // 0x08
    volatile uint32_t LCR;                // 0x0C
    volatile uint32_t MCR;                // 0x10
    volatile uint32_t LSR;                // 0x14
    volatile uint32_t MSR;                // 0x18
    volatile uint32_t SCR;                // 0x1C
    volatile uint32_t _pad_0x20_0x2f[4];  // 0x20 - 0x2F
    volatile uint32_t SRBR0;              // 0x30
    volatile uint32_t SRBR1;              // 0x34
    volatile uint32_t SRBR2;              // 0x38
    volatile uint32_t SRBR3;              // 0x3C
    volatile uint32_t SRBR4;              // 0x40
    volatile uint32_t SRBR5;              // 0x44
    volatile uint32_t SRBR6;              // 0x48
    volatile uint32_t SRBR7;              // 0x4C
    volatile uint32_t SRBR8;              // 0x50
    volatile uint32_t SRBR9;              // 0x54
    volatile uint32_t SRBR10;             // 0x58
    volatile uint32_t SRBR11;             // 0x5C
    volatile uint32_t SRBR12;             // 0x60
    volatile uint32_t SRBR13;             // 0x64
    volatile uint32_t SRBR14;             // 0x68
    volatile uint32_t SRBR15;             // 0x6C
    volatile uint32_t FAR;                // 0x70
    volatile uint32_t TFR;                // 0x74
    volatile uint32_t RFW;                // 0x78
    volatile uint32_t USR;                // 0x7C
    volatile uint32_t TFL;                // 0x80
    volatile uint32_t RFL;                // 0x84
    volatile uint32_t SRR;                // 0x88
    volatile uint32_t SRTS;               // 0x8C
    volatile uint32_t SBCR;               // 0x90
    volatile uint32_t SDMAM;              // 0x94
    volatile uint32_t SFE;                // 0x98
    volatile uint32_t SRT;                // 0x9C
    volatile uint32_t STET;               // 0xA0
    volatile uint32_t HTX;                // 0xA4
    volatile uint32_t DMASA;              // 0xA8
    volatile uint32_t _pad_0xac_0xf3[18]; // 0xAC - 0xF3
    volatile uint32_t CPR;                // 0xF4
    volatile uint32_t UCV;                // 0xF8
    volatile uint32_t CTR;                // 0xFC
} uart_regs_t;

#endif // UART_REGS_H
