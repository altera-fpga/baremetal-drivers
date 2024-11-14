/*
This source code implements control of a synopsis designware SPI master
controller. It uses the register definitions in spi_regs.h.

Functions here are called by the POSIX API defined in spi.c and spi.h

Implementations must be MISRA C 2012 compliant

*/

#include "spi_internal.h"
#include "spi_regs.h"

#include <stddef.h>
#include <stdint.h>

size_t spi_transmit(uintptr_t base, uintptr_t buffer, size_t length) {
    volatile spi_regs_t *spi = (spi_regs_t *)base;
    uint8_t *buf = (uint8_t *)buffer;
    uint32_t i = 0;
    for (i = 0; i < (length / sizeof(uint8_t)); i++) {
        spi->DR0 = buf[i];
    }
    return (size_t)i;
}

size_t spi_receive(uintptr_t base, uintptr_t buffer, size_t length) {
    volatile spi_regs_t *spi = (spi_regs_t *)base;
    uint8_t *buf = (uint8_t *)buffer;
    uint32_t i = 0;
    for (i = 0; i < (length / sizeof(uint8_t)); i++) {
        if ((spi->SR & spi_SR_RFNE_MASK) != (uint32_t)0) {
            buf[i] = (uint8_t)(spi->DR0);
        } else {
            break;
        }
    }
    return (size_t)i;
}

int32_t spi_get_error_state(uintptr_t base) { return 0; }

// Reads the entire register set of the SPI master controller
int32_t spi_regs_read(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)arg;
    if (length < (sizeof(spi_regs_t) / sizeof(uint32_t))) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(spi_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = ((uint32_t *)fd)[i];
        }
        return_value = 0;
    }
    return return_value;
}

// Writes the entire register set of the SPI master controller
int32_t spi_regs_write(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)arg;
    if (length < (sizeof(spi_regs_t) / sizeof(uint32_t))) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(spi_regs_t) / sizeof(uint32_t)); i++) {
            ((uint32_t *)fd)[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

// Set the frame format of the SPI master controller
int32_t spi_set_frame_format(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_FRF_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_CFS_BIT_OFST) & spi_CTRLR0_FRF_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_frame_format(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_FRF_MASK) >> spi_CTRLR0_FRF_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_frame_size(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_DFS_32_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_CFS_BIT_OFST) & spi_CTRLR0_DFS_32_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_frame_size(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_DFS_32_MASK) >> spi_CTRLR0_DFS_32_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_control_frame_size(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_CFS_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_CFS_BIT_OFST) & spi_CTRLR0_CFS_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_control_frame_size(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_CFS_MASK) >> spi_CTRLR0_CFS_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_transfer_mode(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_TMOD_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_TMOD_BIT_OFST) & spi_CTRLR0_TMOD_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_transfer_mode(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_TMOD_MASK) >> spi_CTRLR0_TMOD_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_clock_polarity(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_SCPOL_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_SCPOL_BIT_OFST) & spi_CTRLR0_SCPOL_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_clock_polarity(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_SCPOL_MASK) >> spi_CTRLR0_SCPOL_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_clock_phase(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->CTRLR0 &= ~spi_CTRLR0_SCPH_MASK;
        spi->CTRLR0 |= ((buf[0] << spi_CTRLR0_SCPH_BIT_OFST) & spi_CTRLR0_SCPH_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_clock_phase(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (spi->CTRLR0 & spi_CTRLR0_SCPH_MASK) >> spi_CTRLR0_SCPH_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_num_data_frames(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        spi->CTRLR1 &= ~spi_CTRLR1_NDF_MASK;
        spi->CTRLR1 |= (buf[0] & spi_CTRLR1_NDF_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_num_data_frames(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        buf[0] = spi->CTRLR1 & spi_CTRLR1_NDF_MASK;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_ssi_enable(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->SSIENR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_ssi_enable(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->SSIENR;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_mw_transfer_mode(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->MWCR |= ((*((uint32_t *)arg) << spi_MWCR_MWMOD_BIT_OFST) & spi_MWCR_MWMOD_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_mw_transfer_mode(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = (spi->MWCR & spi_MWCR_MWMOD_MASK) >> spi_MWCR_MWMOD_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_mw_control(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->MWCR |= ((*((uint32_t *)arg) << spi_MWCR_MDD_BIT_OFST) & spi_MWCR_MDD_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_mw_control(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = (spi->MWCR & spi_MWCR_MDD_MASK) >> spi_MWCR_MDD_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_mw_handshake(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->MWCR |= ((*((uint32_t *)arg) << spi_MWCR_MHS_BIT_OFST) & spi_MWCR_MHS_MASK);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_mw_handshake(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = (spi->MWCR & spi_MWCR_MHS_MASK) >> spi_MWCR_MHS_BIT_OFST;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_cs(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        spi->SER = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_cs(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        *((uint32_t *)arg) = spi->SER;
    }
    return return_value;
}

int32_t spi_set_baud_rate(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        spi->BAUDR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_baud_rate(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        *((uint32_t *)arg) = spi->BAUDR;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_set_tx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->TXFTLR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_tx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->TXFTLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_rx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->RXFTLR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_rx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->RXFTLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_tx_fifo_level(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->TXFLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_rx_fifo_level(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->RXFLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_status(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->SR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_interrupt_mask(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->IMR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_interrupt_mask(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->IMR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_interrupt_status(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->ISR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_raw_interrupt_status(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->RISR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_clear_tx_overflow_interrupt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    spi->TXOICR = 0x1;
    return_value = 0;
    return return_value;
}
int32_t spi_clear_rx_overflow_interrupt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    spi->RXOICR = 0x1;
    return_value = 0;
    return return_value;
}
int32_t spi_clear_rx_underflow_interrupt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    spi->RXUICR = 0x1;
    return_value = 0;
    return return_value;
}
int32_t spi_clear_multi_master_interrupt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    spi->MSTICR = 0x1;
    return_value = 0;
    return return_value;
}
int32_t spi_clear_interrupt(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->ICR = 0x1;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_dma_control(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->DMACR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_dma_control(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->DMACR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_dma_tx_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->DMATDLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_dma_tx_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->DMATDLR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_dma_rx_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->DMARDLR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_dma_rx_threshold(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        spi->DMARDLR = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_id(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->IDR;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_get_version(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)arg) = spi->SSI_VERSION_ID;
        return_value = 0;
    }
    return return_value;
}

int32_t spi_get_rx_sample_dly(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        *((uint32_t *)arg) = spi->RX_SAMPLE_DLY;
        return_value = 0;
    }
    return return_value;
}
int32_t spi_set_rx_sample_dly(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    volatile spi_regs_t *spi = (spi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if (spi->IDR == (uint32_t)0x05510005) {
        return_value = -2; // In slave mode, not supported
    } else {
        spi->RX_SAMPLE_DLY = *((uint32_t *)arg);
        return_value = 0;
    }
    return return_value;
}