/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_spi_ll.c
 *
 * SPI source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>

#include "errno.h"
#include "mmio.h"
#include "socfpga_spi_ll.h"
#include "socfpga_clk_mngr_ll.h"
#include "socfpga_rst_mngr.h"
#include "socfpga_spi_reg.h"

static uint32_t spi_clock_mask(uint32_t instance)
{
    return (instance == 1U) ? (1U << CLK_SPIM1_SHIFT) :
                              (1U << CLK_SPIM0_SHIFT);
}

static void spi_enable_clock(uint32_t instance)
{
    uint32_t val = RD_REG32(CLK_PERPLL_EN);

    val |= spi_clock_mask(instance);
    WR_REG32(CLK_PERPLL_EN, val);
}

static void spi_disable_clock(uint32_t instance)
{
    uint32_t val = RD_REG32(CLK_PERPLL_EN);

    val &= ~spi_clock_mask(instance);
    WR_REG32(CLK_PERPLL_EN, val);
}

void spi_enable(uint32_t base_address)
{
    WR_REG32(base_address + SPI_SSIENR, SPI_SSIENR_SSI_EN_MASK);
}

void spi_disable(uint32_t base_address)
{
    WR_REG32(base_address + SPI_SSIENR, 0U);
}

static void spi_clear_interrupts(uint32_t base_address)
{
    (void)RD_REG32(base_address + SPI_ICR);
}

void spi_flush_rx_fifo(uint32_t base_address)
{
    while ((RD_REG32(base_address + SPI_SR) & SPI_SR_RFNE_MASK) != 0U) {
        (void)RD_REG32(base_address + SPI_DR0);
    }
}

static void spi_set_fifo_threshold(uint32_t base_address)
{
    uint32_t val;

    val = RD_REG32(base_address + SPI_TXFTLR);
    val &= ~SPI_TXFTLR_TFT_MASK;
    val |= ((SPI_TX_FIFO_THRESHOLD << SPI_TXFTLR_TFT_POS) &
            SPI_TXFTLR_TFT_MASK);
    WR_REG32(base_address + SPI_TXFTLR, val);

    val = RD_REG32(base_address + SPI_RXFTLR);
    val &= ~SPI_RXFTLR_RFT_MASK;
    val |= ((SPI_RX_FIFO_THRESHOLD << SPI_RXFTLR_RFT_POS) &
            SPI_RXFTLR_RFT_MASK);
    WR_REG32(base_address + SPI_RXFTLR, val);
}

void spi_init(uint32_t instance)
{
    uint32_t base_address = GET_BASE_ADDRESS(instance);
    volatile uint32_t delay;

    spi_enable_clock(instance);

    if (instance == 1U) {
        if (rstmgr_assert_reset(RST_SPIM1) != 0) {
            return;
        }
    } else {
        if (rstmgr_assert_reset(RST_SPIM0) != 0) {
            return;
        }
    }

    for (delay = 0U; delay < 100U; delay++) {
        ;
    }

    if (instance == 1U) {
        if (rstmgr_deassert_reset(RST_SPIM1) != 0) {
            return;
        }
    } else {
        if (rstmgr_deassert_reset(RST_SPIM0) != 0) {
            return;
        }
    }

    spi_disable(base_address);
    spi_disable_interrupt(base_address, SPI_ALL_INTERRUPTS);
    spi_clear_interrupts(base_address);
    spi_flush_rx_fifo(base_address);
    spi_set_fifo_threshold(base_address);
    spi_set_transfermode(base_address, SPI_TX_RX_MOD);
    (void)spi_set_config(base_address, SPI_DEFAULT_SPEED_HZ, SPI_MODE0);
    spi_enable(base_address);
}

void spi_deinit(uint32_t instance)
{
    uint32_t base_address = GET_BASE_ADDRESS(instance);

    spi_disable_interrupt(base_address, SPI_ALL_INTERRUPTS);
    spi_select_chip(instance, 0U);
    spi_disable(base_address);
    spi_clear_interrupts(base_address);
    spi_flush_rx_fifo(base_address);
    spi_disable_clock(instance);
}

int32_t spi_set_config(uint32_t base_address, uint32_t freq, spi_mode_t mode)
{
    uint32_t sclk_dvsr;
    uint32_t spi_clk = 0U;
    uint32_t val;
    int32_t clk_rc;

    if (freq == 0U) {
        return -EINVAL;
    }

    /* CLOCK_SSPI must resolve to the SPIM parent (L4 main). A failed/zero
     * lookup leaves BAUDR untouched and breaks spi_api_open baud setup. */
    clk_rc = clk_mngr_ll_get_clk(CLOCK_SSPI, &spi_clk);
    if ((clk_rc != 0) || (spi_clk == 0U)) {
        return -EIO;
    }

    sclk_dvsr = spi_clk / freq;
    if ((spi_clk % freq) != 0U) {
        sclk_dvsr++;
    }
    if (sclk_dvsr < 2U) {
        sclk_dvsr = 2U;
    }
    if ((sclk_dvsr & 1U) != 0U) {
        sclk_dvsr++;
    }
    if (sclk_dvsr > SPI_BAUDR_SCKDV_MASK) {
        sclk_dvsr = SPI_BAUDR_SCKDV_MASK & ~1U;
    }

    spi_disable(base_address);

    val = RD_REG32(base_address + SPI_CTRLR0);
    val &= ~(SPI_CTRLR0_SPI_FRF_MASK |
             SPI_CTRLR0_FRF_MASK |
             SPI_CTRLR0_DFS_32_MASK |
             SPI_CTRLR0_DFS_MASK |
             SPI_CTRLR0_SCPOL_MASK |
             SPI_CTRLR0_SCPH_MASK);

    /* Configure 8-bit data frames. Set both DFS locations for compatibility
     * with DesignWare APB SSI variants that expose either field.
     */
    val |= ((7U << SPI_CTRLR0_DFS_32_POS) & SPI_CTRLR0_DFS_32_MASK);
    val |= ((7U << SPI_CTRLR0_DFS_POS) & SPI_CTRLR0_DFS_MASK);

    switch (mode) {
    case SPI_MODE1:
        val |= SPI_CTRLR0_SCPH_MASK;
        break;
    case SPI_MODE2:
        val |= SPI_CTRLR0_SCPOL_MASK;
        break;
    case SPI_MODE3:
        val |= SPI_CTRLR0_SCPH_MASK | SPI_CTRLR0_SCPOL_MASK;
        break;
    case SPI_MODE0:
    default:
        break;
    }

    WR_REG32(base_address + SPI_CTRLR0, val);
    WR_REG32(base_address + SPI_BAUDR,
             (sclk_dvsr << SPI_BAUDR_SCKDV_POS) & SPI_BAUDR_SCKDV_MASK);

    spi_enable(base_address);
    return 0;
}

void spi_get_config(uint32_t base_address, uint32_t *freq, spi_mode_t *mode)
{
    uint32_t val;
    uint32_t mode_bits;

    if (freq != NULL) {
        *freq = spi_get_freq(base_address);
    }

    if (mode == NULL) {
        return;
    }

    val = RD_REG32(base_address + SPI_CTRLR0);
    mode_bits = ((val & SPI_CTRLR0_SCPH_MASK) ? 1U : 0U) |
                ((val & SPI_CTRLR0_SCPOL_MASK) ? 2U : 0U);

    switch (mode_bits) {
    case 1U:
        *mode = SPI_MODE1;
        break;
    case 2U:
        *mode = SPI_MODE2;
        break;
    case 3U:
        *mode = SPI_MODE3;
        break;
    case 0U:
    default:
        *mode = SPI_MODE0;
        break;
    }
}

void spi_set_transfermode(uint32_t base_address, uint32_t mode)
{
    uint32_t val;

    spi_disable(base_address);
    val = RD_REG32(base_address + SPI_CTRLR0);
    val &= ~SPI_CTRLR0_TMOD_MASK;
    val |= ((mode << SPI_CTRLR0_TMOD_POS) & SPI_CTRLR0_TMOD_MASK);
    WR_REG32(base_address + SPI_CTRLR0, val);
    spi_enable(base_address);
}

void spi_set_loopback(uint32_t base_address, bool enable)
{
    uint32_t val;

    spi_disable(base_address);
    val = RD_REG32(base_address + SPI_CTRLR0);
    if (enable) {
        val |= SPI_CTRLR0_SRL_MASK;
    } else {
        val &= ~SPI_CTRLR0_SRL_MASK;
    }
    WR_REG32(base_address + SPI_CTRLR0, val);
    spi_enable(base_address);
}

uint32_t spi_get_freq(uint32_t base_address)
{
    uint32_t sclk_dvsr;
    uint32_t spi_clk = 0U;

    if ((clk_mngr_ll_get_clk(CLOCK_SSPI, &spi_clk) != 0) || (spi_clk == 0U)) {
        return 0U;
    }

    sclk_dvsr = RD_REG32(base_address + SPI_BAUDR) & SPI_BAUDR_SCKDV_MASK;
    if (sclk_dvsr == 0U) {
        return 0U;
    }

    return spi_clk / sclk_dvsr;
}

uint32_t spi_get_version(uint32_t base_address)
{
    return RD_REG32(base_address + SPI_SSI_VERSION_ID);
}

void spi_select_chip(uint32_t instance, uint32_t slave)
{
    uint32_t base_address = GET_BASE_ADDRESS(instance);
    uint32_t val = 0U;

    switch (slave) {
    case 1U:
        val = 1U;
        break;
    case 2U:
        val = 2U;
        break;
    case 3U:
        val = 4U;
        break;
    case 4U:
        val = 8U;
        break;
    case 0U:
    default:
        val = 0U;
        break;
    }

    WR_REG32(base_address + SPI_SER, val);
}

uint16_t spi_write_fifo(uint32_t base_address, const uint8_t *buffer, uint16_t bytes)
{
    uint16_t bytes_done = 0U;

    while (bytes > 0U) {
        if ((RD_REG32(base_address + SPI_SR) & SPI_SR_TFNF_MASK) == 0U) {
            break;
        }

        WR_REG32(base_address + SPI_DR0,
                 (buffer != NULL) ? buffer[bytes_done] : 0xFFU);
        bytes_done++;
        bytes--;
    }

    return bytes_done;
}

uint16_t spi_read_fifo(uint32_t base_address, uint8_t *buffer, uint16_t bytes)
{
    uint16_t bytes_done = 0U;

    while (bytes > 0U) {
        uint32_t value;

        if ((RD_REG32(base_address + SPI_SR) & SPI_SR_RFNE_MASK) == 0U) {
            break;
        }

        value = RD_REG32(base_address + SPI_DR0);
        if (buffer != NULL) {
            buffer[bytes_done] = (uint8_t)value;
        }
        bytes_done++;
        bytes--;
    }

    return bytes_done;
}

int32_t spi_wait_idle(uint32_t base_address, uint32_t timeout_polls)
{
    while (timeout_polls > 0U) {
        uint32_t status = RD_REG32(base_address + SPI_SR);

        if (((status & SPI_SR_BUSY_MASK) == 0U) &&
            ((status & SPI_SR_TFE_MASK) != 0U)) {
            return 0;
        }
        timeout_polls--;
    }

    return -ETIMEDOUT;
}

static int32_t spi_check_error(uint32_t base_address)
{
    uint32_t risr = RD_REG32(base_address + SPI_RISR);

    if ((risr & (SPI_ISR_RXOIS_MASK | SPI_ISR_RXUIS_MASK |
                 SPI_ISR_TXOIS_MASK | SPI_ISR_MSTIS_MASK)) != 0U) {
        spi_clear_interrupts(base_address);
        return -EIO;
    }

    return 0;
}

int32_t spi_transfer_poll(uint32_t base_address,
                          const uint8_t *txbuf,
                          uint8_t *rxbuf,
                          uint16_t nbytes,
                          uint32_t timeout_polls)
{
    uint32_t tx_done = 0U;
    uint32_t rx_done = 0U;
    uint32_t idle_polls = timeout_polls;

    if ((base_address == 0U) || (txbuf == NULL) || (nbytes == 0U) ||
        (timeout_polls == 0U)) {
        return -EINVAL;
    }

    spi_disable_interrupt(base_address, SPI_ALL_INTERRUPTS);
    spi_clear_interrupts(base_address);
    spi_flush_rx_fifo(base_address);

    while (rx_done < nbytes) {
        bool progressed = false;
        int32_t ret;

        while ((tx_done < nbytes) &&
               ((tx_done - rx_done) < SPI_FIFO_SAFE_TX_GAP) &&
               ((RD_REG32(base_address + SPI_SR) & SPI_SR_TFNF_MASK) != 0U)) {
            WR_REG32(base_address + SPI_DR0, txbuf[tx_done]);
            tx_done++;
            progressed = true;
        }

        while ((rx_done < nbytes) &&
               ((RD_REG32(base_address + SPI_SR) & SPI_SR_RFNE_MASK) != 0U)) {
            uint32_t value = RD_REG32(base_address + SPI_DR0);

            if (rxbuf != NULL) {
                rxbuf[rx_done] = (uint8_t)value;
            }
            rx_done++;
            progressed = true;
        }

        ret = spi_check_error(base_address);
        if (ret != 0) {
            return ret;
        }

        if (progressed) {
            idle_polls = timeout_polls;
        } else {
            if (idle_polls == 0U) {
                return -ETIMEDOUT;
            }
            idle_polls--;
        }
    }

    return spi_wait_idle(base_address, timeout_polls);
}

uint8_t spi_get_interrupt_status(uint32_t base_address)
{
    uint32_t val = RD_REG32(base_address + SPI_ISR);

    if ((val & SPI_ISR_TXEIS_MASK) != 0U) {
        return SPI_TX_EMPTY_INT;
    }
    if ((val & SPI_ISR_RXFIS_MASK) != 0U) {
        return SPI_RX_FULL_INT;
    }

    return SPI_NO_INTERRUPT;
}

void spi_enable_interrupt(uint32_t base_address, uint32_t ir_id)
{
    uint32_t val = RD_REG32(base_address + SPI_IMR);

    switch (ir_id) {
    case SPI_TX_EMPTY_INT:
        val |= SPI_IMR_TXEIM_MASK;
        break;
    case SPI_RX_FULL_INT:
        val |= SPI_IMR_RXFIM_MASK;
        break;
    case SPI_ALL_INTERRUPTS:
        val |= SPI_IMR_TXEIM_MASK | SPI_IMR_TXOIM_MASK |
               SPI_IMR_RXUIM_MASK | SPI_IMR_RXOIM_MASK |
               SPI_IMR_RXFIM_MASK | SPI_IMR_MSTIM_MASK;
        break;
    default:
        break;
    }

    WR_REG32(base_address + SPI_IMR, val);
}

void spi_disable_interrupt(uint32_t base_address, uint32_t ir_id)
{
    uint32_t val = RD_REG32(base_address + SPI_IMR);

    switch (ir_id) {
    case SPI_TX_EMPTY_INT:
        val &= ~SPI_IMR_TXEIM_MASK;
        break;
    case SPI_RX_FULL_INT:
        val &= ~SPI_IMR_RXFIM_MASK;
        break;
    case SPI_ALL_INTERRUPTS:
        val &= ~(SPI_IMR_TXEIM_MASK | SPI_IMR_TXOIM_MASK |
                 SPI_IMR_RXUIM_MASK | SPI_IMR_RXOIM_MASK |
                 SPI_IMR_RXFIM_MASK | SPI_IMR_MSTIM_MASK);
        break;
    default:
        break;
    }

    WR_REG32(base_address + SPI_IMR, val);
}

