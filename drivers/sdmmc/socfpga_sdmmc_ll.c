/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sdmmc_ll.c
 *
 * SDMMC source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "errno.h"
#include "cache.h"
#include "mmio.h"
#include "socfpga_combo_phy.h"
#include "socfpga_sdmmc_ll.h"
#include "socfpga_sdmmc_reg.h"
#include "socfpga_clk_mngr_reg_plat.h"
#include "../api/uart/uart_api.h"


#define SINGLE_BLOCK              (0U)
#define DATA_WRITE                (0U)
#define HIGH_SPEED_MODE           (1U)
#define DEF_SPEED_MODE            (0U)
#define CARD_DETECTED             (1U)
#define VAL_DESCRIPTOR            (1U)
#define EN_BUS_PWR                (1U)
#define DATA_READ                 (1U)
#define MULTI_BLOCK               (1U)
#define CMD_ID_CHECK_EN           (1U)
#define CMD_SEND_EXT_CSD          (8U)
#define CMD_READ_SINGLE_BLOCK     (17U)
#define CMD_READ_MULT_BLOCK       (18U)
#define CMD_WRITE_SINGLE_BLOCK    (24U)
#define CMD_WRITE_MULT_BLOCK      (25U)
#define DATA_XFER_BITS_512        (0x200U)
#define SHORT_RESP_BUSY           (3U)
#define DATA_PRESENT              (1U)

#define CLEAR_INT      (0x0U)
#define EN_CMD_INT     (0x10001U)
#define EN_XFER_INT    (0x100002U)

#define SDCLK_FREQ            (2U)
#define EN_INTERN_CLK         (1U)
#define EN_SD_CLK             (1U)
#define SEL_ADMA2             (3U)
#define EN_DMA                (1U)
#define EN_BCT                (1U)
#define SET_VOLT_3_3          (7U)
#define PHY_SW_RST            (1U)
#define EN_EXT_WR_MODE        (1U)
#define EN_EXT_RDCMD_MODE     (1U)
#define EN_EXT_RDDATA_MODE    (1U)
#define EN_BUS_WIDTH_4        (1U)

#define CMD_INHIBIT_SET    (1U)
#define FREQ_SEL_25MHz     (4U)
#define FREQ_SEL_50MHz     (2U)
#define AUTO_CMD_23_EN     (2U)

#define SDSC_DETECTED     (0x0U)
#define SDHC_DETECTED     (0x1U)
#define DAT_TIMOUT_CTR    (0xeU)

#define SDMMC_DMA_MAX_BUFFER_SIZE    (64U * 1024U)
#define RESET_SOFTPHY                (1U << 6U)
#define RESET_SDMMC                  (1U << 7U)
#define RESET_SDMMC_ECC              ((uint32_t)1 << 15U)
#define IS_CARD_READY                ((uint32_t)1 << 31U)
#define END_DESCRIPTOR               (1U << 1U)
#define EN_DMA_INT                   (1U << 2U)
#define XFER_DATA                    (1U << 5U)
#define BIT_MASK_32                  (0xFFFFFFFFUL)

/*delays approx 12.5 micro-seconds*/
#define SECTOR_SIZE           512UL
#define RESET_TIMEOUT         10000
#define EMMC_8_BIT_MODE_EN    1

#define SOFTPHY_CLK_200_MHZ    1

static int32_t reset_dll(void);
static void prgm_host_config(void);
static void program_reg(uint32_t val, uint32_t reg_add);
static void config_phy_xfer_params(void);
static void sdmmc_enable_cmd_int(void);
static void sdmmc_enable_xfer_int(void);

/*
 * Set up the command parameters and send the command to the card.
 */
int32_t sdmmc_send_command(const cmd_parameters_t *params)
{
    uint32_t count = 0;
    uint32_t srs03_reg_value = 0;
    uint32_t srs02_reg_value;
    uint32_t srs11_reg_value = 0;
    /*should retain the loaded configs*/
    srs03_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS03);
    srs11_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS11);

    srs03_reg_value &= ~(SDMMC_SRS03_CIDX_MASK | SDMMC_SRS03_DPS_MASK |
            SDMMC_SRS03_CRCCE_MASK | SDMMC_SRS03_CICE_MASK |
            SDMMC_SRS03_RTS_MASK);
    /*reset cmd line*/
    srs11_reg_value |= SDMMC_SRS11_SRCMD_MASK;
    /*reset data line */
    srs11_reg_value |= SDMMC_SRS11_SRDAT_MASK;
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS11, srs11_reg_value);
    /*host requires some delay to reset cmd line*/
    count = RESET_TIMEOUT;
    while ((RD_REG32(SRS_BASE_ADDR + SDMMC_SRS11) & SDMMC_SRS11_SRCMD_MASK) ==
            SDMMC_SRS11_SRCMD_MASK)
    {
        if (count == 0U)
        {
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }
    /*Host requires some delay to reset data line*/
    count = RESET_TIMEOUT;
    while ((RD_REG32(SRS_BASE_ADDR + SDMMC_SRS11) & SDMMC_SRS11_SRDAT_MASK) ==
            SDMMC_SRS11_SRDAT_MASK)
    {
        if (count == 0U)
        {
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }
    /*argument and dependent param configuration*/
    srs03_reg_value |= (uint32_t)params->command_index << SDMMC_SRS03_CIDX_POS;
    srs03_reg_value |= (uint32_t)params->data_xfer_present <<
            SDMMC_SRS03_DPS_POS;
    srs03_reg_value |= (uint32_t)params->id_check_enable <<
            SDMMC_SRS03_CICE_POS;
    srs03_reg_value |= (uint32_t)params->crc_check_enable <<
            SDMMC_SRS03_CRCCE_POS;
    srs03_reg_value |= (uint32_t)params->response_type << SDMMC_SRS03_RTS_POS;

    srs02_reg_value = (uint32_t)params->argument;
    /*send stop request once block count decrements to 0 in case of multi block read/write*/
    if ((params->command_index == CMD_WRITE_MULT_BLOCK) ||
            (params->command_index == CMD_READ_MULT_BLOCK))
    {
        srs03_reg_value |= (AUTO_CMD_23_EN << SDMMC_SRS03_ACE_POS);
    }
    /*check if the cmd line is inhibited to send command*/
    if ((RD_REG32(SRS_BASE_ADDR + SDMMC_SRS09) & CMD_INHIBIT_SET) == 0U)
    {
        if ((params->data_xfer_present == DATA_PRESENT) ||
                (params->response_type == SHORT_RESP_BUSY))
        {
            sdmmc_enable_xfer_int();
        }
        else
        {
            sdmmc_enable_cmd_int();
        }

        WR_REG32(SRS_BASE_ADDR + SDMMC_SRS02, srs02_reg_value);
        WR_REG32(SRS_BASE_ADDR + SDMMC_SRS03, srs03_reg_value);
    }
    else
    {
        return CMD_ERR;
    }

    return CMD_SND_OK;
}

/*
 * Configure the host for data transmission and reception.
 */
void sdmmc_set_xfer_config(cmd_parameters_t const *params)
{
    uint32_t srs11_reg_value = 0;
    uint32_t srs03_reg_value = 0;
    /*should retain the loaded configs*/
    srs11_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS11);
    srs03_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS03);

    srs11_reg_value |= SDMMC_SRS11_SRDAT_MASK;
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS11, srs11_reg_value);

    srs03_reg_value &= ~(SDMMC_SRS03_DTDS_MASK | SDMMC_SRS03_MSBS_MASK);
    /*configure no of blocks for the transaction*/
    switch (params->command_index)
    {
        case CMD_READ_MULT_BLOCK:
        case CMD_READ_SINGLE_BLOCK:
        case CMD_SEND_EXT_CSD:
            srs03_reg_value |= DATA_READ << SDMMC_SRS03_DTDS_POS;
            break;

        case CMD_WRITE_MULT_BLOCK:
        case CMD_WRITE_SINGLE_BLOCK:
            srs03_reg_value |= DATA_WRITE << SDMMC_SRS03_DTDS_POS;
            break;
        default:
            /*Do Nothing*/
            break;
    }
    /*configure for write and read*/
    switch (params->command_index)
    {
        case CMD_READ_MULT_BLOCK:
        case CMD_WRITE_MULT_BLOCK:
            srs03_reg_value |= (uint32_t)MULTI_BLOCK << SDMMC_SRS03_MSBS_POS;
            break;

        case CMD_READ_SINGLE_BLOCK:
        case CMD_WRITE_SINGLE_BLOCK:
        case CMD_SEND_EXT_CSD:
            srs03_reg_value |= (uint32_t)SINGLE_BLOCK << SDMMC_SRS03_MSBS_POS;
            break;
        default:
            /*Do Nothing*/
            break;
    }

    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS03, srs03_reg_value);
    /*wait for the configurations to reflect*/
    for (int i = 0; i < 10000; i++)
    {
		__asm__ volatile("nop");
    }
}

/*
 * Set up DMA attributes.
 */
void sdmmc_set_up_xfer(dma_descriptor_t *pdesc, uint64_t *buff,
        uint32_t block_size, uint32_t block_ct)
{
    uint64_t desc = 0;
    uint32_t volatile val = 0;
    uint32_t volatile i = 0;
    uint32_t size = block_size * block_ct;
    uint32_t descriptor_count = 0;

    descriptor_count = (size + (DESC_MAX_XFER_SIZE)-1U) / DESC_MAX_XFER_SIZE;
    cache_force_invalidate((uint64_t *)buff, size);
    desc = (uint64_t)pdesc;
    /*count number of descriptors required*/
    while ((i + 1U) < descriptor_count)
    {
        pdesc->attribute = XFER_DATA | VAL_DESCRIPTOR | EN_DMA_INT;
        pdesc->reserved = 0U;
        pdesc->len = 0U;
        pdesc->addr_lo = (uint32_t)((uint64_t)buff & BIT_MASK_32) +
                (DESC_MAX_XFER_SIZE * i);
        pdesc->addr_hi = (uint32_t)(((uint64_t)buff >> 32U) & BIT_MASK_32);
        size -= SDMMC_DMA_MAX_BUFFER_SIZE;
        pdesc++;
        i++;
    }
    pdesc->attribute = XFER_DATA | VAL_DESCRIPTOR | EN_DMA_INT | END_DESCRIPTOR;
    pdesc->reserved = 0U;
    pdesc->len = (uint16_t)size;
    pdesc->addr_lo = (uint32_t)(((uint64_t)(uintptr_t)buff & BIT_MASK_32) +
            ((uint64_t)DESC_MAX_XFER_SIZE * i));
    pdesc->addr_hi = (uint32_t)((((uint64_t)buff >> 32U) & BIT_MASK_32));

    cache_force_write_back((uint64_t *)desc, descriptor_count *
            sizeof(dma_descriptor_t));

    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS22, (uint32_t)desc);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS23, (uint32_t)((uint64_t)desc >> 32U));
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS00, (uint32_t)block_ct);

    val = (uint32_t)(block_ct << SDMMC_SRS01_BCCT_POS);
    val |= (uint32_t)block_size << SDMMC_SRS01_TBS_POS;

    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS01, val);
}

/*
 * Initialize sdmmc host configuration
 */
void sdmmc_init_configs(uint32_t emmc_bus_width, uint32_t def_speed)
{
    uint32_t srs10_reg_value = 0;
    uint32_t srs11_reg_value = 0;
    uint32_t srs03_reg_value = 0;

    srs03_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS03);
    srs10_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS10);
    srs10_reg_value &= ~((SDMMC_SRS10_DMASEL_MASK) | (SDMMC_SRS10_DTW_MASK) |
            (SDMMC_SRS10_EDTW_MASK) | (SDMMC_SRS10_SBGR_MASK) |
            (SDMMC_SRS10_BVS_MASK) | (SDMMC_SRS10_BVS_MASK));

    if (def_speed == 1U)
    {
        srs11_reg_value = (uint32_t)FREQ_SEL_25MHz << SDMMC_SRS11_SDCFSL_POS;
        srs10_reg_value |= DEF_SPEED_MODE << SDMMC_SRS10_HSE_POS;
    }
    else
    {
        srs11_reg_value = (uint32_t)FREQ_SEL_50MHz << SDMMC_SRS11_SDCFSL_POS;
        srs10_reg_value |= HIGH_SPEED_MODE << SDMMC_SRS10_HSE_POS;
    }
    srs11_reg_value |= ((uint32_t)DAT_TIMOUT_CTR << SDMMC_SRS11_DTCV_POS);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS11, srs11_reg_value);

    srs11_reg_value |= (EN_SD_CLK << SDMMC_SRS11_SDCE_POS);
    srs11_reg_value |= (EN_INTERN_CLK << SDMMC_SRS11_ICE_POS);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS11, srs11_reg_value);

    srs10_reg_value |= ((uint32_t)SET_VOLT_3_3 << SDMMC_SRS10_BVS_POS);
    srs10_reg_value |= (SEL_ADMA2 << SDMMC_SRS10_DMASEL_POS);
    srs10_reg_value |= (uint32_t)EN_BUS_PWR << SDMMC_SRS10_BP_POS;
    srs10_reg_value |= emmc_bus_width << SDMMC_SRS10_EDTW_POS;
    srs10_reg_value |= EN_BUS_WIDTH_4 << SDMMC_SRS10_DTW_POS;

    srs03_reg_value |= (EN_BCT << SDMMC_SRS03_BCE_POS);
    srs03_reg_value |= (EN_DMA << SDMMC_SRS03_DMAE_POS);

    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS03, srs03_reg_value);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS10, srs10_reg_value);

    config_phy_xfer_params();
}

/*
 * Parse and read relative card address from the response.
 */
void sd_read_response_rel_addr(card_data_t *pxcard)
{
    uint32_t srs04_reg_value = 0;
    srs04_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS04);
    pxcard->relative_address = ((uint64_t)srs04_reg_value >> 16U) & 0xFFFFUL;
}

/*
 * Reset all sdmmc host configurations.
 */
int32_t sdmmc_reset_configs(void)
{
    uint32_t count = 0;
    uint32_t hrs00_reg_value = 0;
    uint32_t ulhrs09_reg_value = 0;

    hrs00_reg_value = RD_REG32(HRS_BASE_ADDR + SDMMC_HRS00);
    ulhrs09_reg_value = RD_REG32(HRS_BASE_ADDR + SDMMC_HRS09);

    hrs00_reg_value |= 1U << SDMMC_HRS00_SWR_POS;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS00, hrs00_reg_value);
    /*Host requires some delay to reset*/
    count = RESET_TIMEOUT;
    while ((RD_REG32(HRS_BASE_ADDR + SDMMC_HRS00) & 1U) == 1U)
    {
        if (count == 0U)
        {
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }
    ulhrs09_reg_value = 0U;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, ulhrs09_reg_value);
    return CTRL_CONFIG_PASS;
}

/*
 * Configure the sdmmc combo-phy
 */
int32_t sdmmc_init_phy(void)
{
    uint32_t reg_value;
    uint16_t val;
    int32_t ret = CTRL_CONFIG_PASS;

    reg_value = USE_EXT_LPBK_DQS | USE_LPBK_DQS | USE_PHONY_DQS |
            USE_PHONY_DQS_CMD | DQS_SEL_OE_END;
    program_reg(reg_value, PHY_DQS_TIM_REG_ADD);

    reg_value = SYNC_METHOD_EN | RD_DEL_SEL | SW_HALF_CYCLE_SHIFT |
            SET_UNDERRUN_SUPPRESS | GATE_CFG_ALWAYS_ON;
    program_reg(reg_value, PHY_GATE_LPBK_CTL_ADD);

    reg_value = SEL_DLL_BYPASS_MODE | PARAM_DLL_START_POINT;
    program_reg(reg_value, PHY_DLL_MASTER_CTL_ADD);

    reg_value = READ_DQS_CMD_DELAY | CLK_WRDQS_DELAY | CLK_WR_DELAY |
            READ_DQS_DELAY;

    program_reg(reg_value, PHY_DLL_SLAVE_CTL_ADD);

    val = PHY_CTL_REG_ADD & 0xFFFFU;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS04, (uint32_t)val);
    reg_value = RD_REG32(HRS_BASE_ADDR + SDMMC_HRS05);
    reg_value &= ~PHONY_DQS_DELAY;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS05, reg_value);

    ret = reset_dll();

    reg_value = IO_MASK_DISABLE | IO_MASK_END | IO_MASK_START | DATA_SEL_OE_END;
    program_reg(reg_value, (uint32_t)PHY_DQ_TIM_REG_ADD);

    prgm_host_config();
    return ret;

}

/*
 * Program phy registers.
 */
static void program_reg(uint32_t val, uint32_t reg_add)
{
    reg_add &= REG_ADD_LSB_MASK;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS04, reg_add);
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS05, val);
}

/*
 * Reset all dll registers.
 */
static int32_t reset_dll(void)
{
    uint32_t reg_val;
    uint32_t count = RESET_TIMEOUT;

    do
    {
        reg_val = RD_REG32(HRS_BASE_ADDR + SDMMC_HRS09);
        reg_val |= 1U;
        WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, reg_val);
        if (count == 0U)
        {
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    } while ((RD_REG32(HRS_BASE_ADDR + SDMMC_HRS09) &
    (1U << SDMMC_HRS09_PHY_INIT_COMPLETE_POS)) ==
    (0U << SDMMC_HRS09_PHY_INIT_COMPLETE_POS));
    return CTRL_CONFIG_PASS;
}

/*
 * Program host configuration for cmd/xfer.
 */
static void prgm_host_config(void)
{
    uint32_t reg_val;

    reg_val = ((uint32_t)1 << SDMMC_HRS09_RDDATA_EN_POS) |
            ((uint32_t)1 << SDMMC_HRS09_RDCMD_EN_POS) |
            (1U << SDMMC_HRS09_EXTENDED_RD_MODE_POS) |
            (1U << SDMMC_HRS09_EXTENDED_WR_MODE_POS);
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, reg_val);

    reg_val = (uint32_t)6 << SDMMC_HRS10_HCSDCLKADJ_POS;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS10, reg_val);

    reg_val = (WRCMD0_SDCLK_DLY) |
            ((uint32_t)1 << SDMMC_HRS16_WRDATA0_DLY_POS) |
            ((uint32_t)1 << SDMMC_HRS16_WRCMD0_DLY_POS);
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS16, reg_val);

    reg_val = (uint32_t)0xA << SDMMC_HRS07_RW_COMPENSATE_POS;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS07, reg_val);

    reg_val = (uint32_t)0x3 << 20U;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS10, reg_val);
}

/*
 * Calculate the sector count of the sd card.
 */
uint64_t sdmmc_read_sector_count(void)
{
    /*C_SIZE is parsed from bit 40 to 61*/
    uint32_t reg[4];
    uint64_t card_size;
    uint64_t sector_count;
    uint64_t temp_ops;

    reg[0] = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS04);
    reg[1] = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS05);

    /*extract C_SIZE*/
    temp_ops = (((uint64_t)reg[1] >> 8) & (0x3FFFFFUL));
    /*card size in bytes*/
    card_size = (temp_ops + 1UL) * SECTOR_SIZE * 1024UL;
    sector_count = card_size / SECTOR_SIZE;

    return sector_count;
}

/*
 * Reset the sdmmc peripherel.
 */
int32_t sdmmc_reset_per0(void)
{
    uint32_t reg_add_val;
    uint32_t count = 0;

#if SOFTPHY_CLK_200_MHZ
    /*The clock gated to combo-phy is 200MHz instead of 800MHz.
     * Dividing the combo-phy clock by 1 instead of 4
     * to make the combo-phy to its optimal
     * clock frequency.
     */
    reg_add_val = RD_REG32(PER0MODRST_ADDR);
    /*Assert the sdmmc module reset signal*/
    reg_add_val |= RESET_SOFTPHY;
    reg_add_val |= RESET_SDMMC;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);
    uint32_t read_val = RD_REG32(CLK_MNGR_BASE_ADDR + MAINPLL_CLK_MNGR_NOCDIV);

    /*divide the clock by 1*/
    read_val &= ~(0x30000U);
    WR_REG32((CLK_MNGR_BASE_ADDR + MAINPLL_CLK_MNGR_NOCDIV), read_val);
#endif

    reg_add_val = RD_REG32(PER0MODRST_ADDR);
    reg_add_val |= RESET_SOFTPHY;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);

    reg_add_val &= ~RESET_SOFTPHY;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);
    /*Host requires some delay to reset*/
    count = RESET_TIMEOUT;

    while ((RD_REG32(PER0MODRST_ADDR) & RESET_SOFTPHY) == (1U << 6U))
    {
        if (count == 0U)
        {
            printf("RESET FAILED");
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }

    reg_add_val |= RESET_SDMMC;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);

    reg_add_val &= ~RESET_SDMMC;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);
    /*Host requires some delay to reset*/
    count = RESET_TIMEOUT;

    while ((RD_REG32(PER0MODRST_ADDR) & RESET_SDMMC) == (1U << 7U))
    {
        if (count == 0U)
        {
            printf("RESET FAILED");
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }

    reg_add_val |= RESET_SDMMC_ECC;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);

    reg_add_val &= ~RESET_SDMMC_ECC;
    WR_REG32(PER0MODRST_ADDR, reg_add_val);
    while ((RD_REG32(PER0MODRST_ADDR) & RESET_SDMMC_ECC) ==
            ((uint32_t)1U << 15U))
    {
        if (count == 0U)
        {
            printf("RESET FAILED");
            return CTRL_CONFIG_FAIL;
        }
        else
        {
            count--;
        }
    }
    return CTRL_CONFIG_PASS;
}

/*
 * Enable the extended read,write and command mode.
 */
static void config_phy_xfer_params(void)
{
    uint32_t hrs09_reg_val;

    hrs09_reg_val = RD_REG32(HRS_BASE_ADDR + SDMMC_HRS09);
    hrs09_reg_val &= ~(PHY_SW_RST);
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, hrs09_reg_val);

    hrs09_reg_val |= ((EN_EXT_WR_MODE << SDMMC_HRS09_EXTENDED_WR_MODE_POS) |
            ((uint32_t)EN_EXT_RDCMD_MODE << SDMMC_HRS09_RDCMD_EN_POS) |
            ((uint32_t)EN_EXT_RDDATA_MODE << SDMMC_HRS09_RDDATA_EN_POS));

    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, hrs09_reg_val);
    hrs09_reg_val |= PHY_SW_RST;
    WR_REG32(HRS_BASE_ADDR + SDMMC_HRS09, hrs09_reg_val);
}

/*
 * Parse the response and check if the card is ready.
 */
uint32_t sdmmc_is_card_ready(void)
{
    uint32_t card_read_status = (RD_REG32(SRS_BASE_ADDR + SDMMC_SRS04) &
            IS_CARD_READY);
    card_read_status = card_read_status >> 31;
    return card_read_status;
}

/*
 * Parse the response and check the card type.
 */
void sd_get_card_type(card_data_t *pxcard)
{
    pxcard->card_type = ((RD_REG32(SRS_BASE_ADDR + SDMMC_SRS04) &
            ((uint32_t)1 << 31U)) == ((uint32_t)1 << 31U))
            ? SDHC_DETECTED : SDSC_DETECTED;
}

/*
 * Enable command interrupts.
 */
static void sdmmc_enable_cmd_int(void)
{
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS14, EN_CMD_INT);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS13, EN_CMD_INT);
}

/*
 * Enable transaction interrupts.
 */
static void sdmmc_enable_xfer_int(void)
{
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS14, EN_XFER_INT);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS13, EN_XFER_INT);
}

/*
 * Clear sdmmc interrupt flags.
 */
void sdmmc_clear_int(void)
{
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS14, CLEAR_INT);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS13, CLEAR_INT);
}

/*
 * Read interrupt status register.
 */
uint32_t sdmmc_get_int_status(void)
{
    return RD_REG32(SRS_BASE_ADDR + SDMMC_SRS12);
}

/*
 * Disable interrupts for data and response triggers.
 */
void sdmmc_disable_int(void)
{
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS12, CLEAR_INT);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS13, CLEAR_INT);
    WR_REG32(SRS_BASE_ADDR + SDMMC_SRS14, CLEAR_INT);
}


/*
 * Check if the SD/eMMC card detected.
 */
uint32_t sdmmc_is_card_detected(void)
{
    /*INFO:sdmmc_is_card_detected is used to check if the card is detected or not.
       The detection bitfield is always set regardless of the presence or absence of the card.*/
    uint32_t srs09_reg_value;
    uint32_t card_check;

    srs09_reg_value = RD_REG32(SRS_BASE_ADDR + SDMMC_SRS09);
    card_check = (srs09_reg_value >> SDMMC_SRS09_CI_POS) & CARD_DETECTED;
    return card_check;
}

