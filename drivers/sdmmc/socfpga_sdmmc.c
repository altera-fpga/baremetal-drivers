/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sdmmc.c
 *
 * SDMMC source implementation for the SoCFPGA bare-metal software stack.
 */

/*
 * This is the implementation of the SDMMC/eMMC driver. It supports both the
 * SD card and eMMC device. The driver can be used directly or via the FAT
 * file system. The typical usage is via FAT file system.
 *
 * The below diagram shows how this driver interacts with the file system
 * and the hardware.
 * +==========================================================================+
 * |                         Application Layer                                |
 * |                  (FF_Write, FF_Read, FF_Open, etc.)                      |
 * +==========================================================================+
 *                                 |
 *                                 v
 * +==========================================================================+
 * |                          FATFS Stack                                     |
 * +==========================================================================+
 *                                 |
 *                                 v
 * +==========================================================================+
 * |                   Portable Layer (ff_sddisk.c)                           |
 * +==========================================================================+
 *                                 |
 *                                 v
 * +==========================================================================+
 * |                                                                          |
 * |  +====================================================================+  |
 * |  |                                                                    |  |
 * |  |                       +----------------------+                     |  |
 * |  |                       |      SDMMC HAL       |                     |  |
 * |  |                       +----------------------+                     |  |
 * |  |  +----------------+   +---------------------+   +----------------+ |  |
 * |  |  | DMA and Buffer |   |  SDMMC Low Level    |   |   SDMMC PHY    | |  |
 * |  |  |  Management    |   |      Layer          |   |                | |  |
 * |  |  +----------------+   +---------------------+   +----------------+ |  |
 * |  +====================================================================+  |
 * +==========================================================================+
 *
 * The file ff_sddisk.c serves as the portable layer and translates the FAT
 * file system requests to driver calls. The HAL layer in the driver implements
 * the driver APIs, which can be used by the porting layer or can be invoked
 * directly if used with no file system.
 *
 * The low level driver implements the low level register sequences for the
 * SDMMC controller. And the combo phy module implements the low level register
 * configurations for the combo phy
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>

#include "errno.h"
#include "cache.h"
#include "socfpga_interrupt.h"
#include "socfpga_sdmmc_ll.h"
#include "socfpga_sdmmc.h"
#include "../api/uart/uart_api.h"

/*
 * Maximum time to wait for an sdmmc command response before timeout.
 * 10ms provides a safe margin for back to back command responses.
 */
#define SDMMC_CMD_TIMEOUT_MS   10UL
#define DEF_SPEED_EN    1
#define DEF_SPEED_DI    0

#define DEV_TYPE_SD      0
#define DEV_TYPE_EMMC    1

/*specify max descriptor count here
 * 1 descriptor can handle up to 64KB of data
 */
#define SDMMC_MAX_DESCRIPTOR    160U
/* specify your device here */
#define DEV_TYPE    DEV_TYPE_SD

/*INFO:
 * Driver supports High speed[speed upto 25 MBps at 50 MHz] and
 * Default speed[speed upto 12.5 MBps at 25 MHz] mode.
 **/

#define SUPPORT_DEF_SPEED    DEF_SPEED_DI

#if SDMMC_MAX_DESCRIPTOR < 1
#error Invalid descriptor count
#endif

/*
 * Simple busy-wait delay function (milliseconds)
 * Assumes ARM CPU core clock is steady and available.
 * This is approximate and depends on CPU frequency.
 */
static inline void sdmmc_delay_ms(uint32_t ms)
{
    /* Rough estimate: ~1000 iterations per millisecond at typical ARM frequencies
     * Adjust the multiplier if timing is off. This is conservative for safety. */
    volatile uint32_t delay_count = ms * 1000;
    while (delay_count > 0)
    {
        delay_count--;
    }
}

#if (DEV_TYPE ==  DEV_TYPE_SD)
#define BUS_PARAM    0
static int32_t sd_mmc_init(uint64_t *sec_num);
static int32_t sd_go_idle(cmd_parameters_t *pcmd);
static int32_t sd_snd_if_cond(cmd_parameters_t *pcmd);
static int32_t sd_snd_app_cmd(cmd_parameters_t *pcmd);
static int32_t sd_check_ocr(cmd_parameters_t *pcmd);
static int32_t sd_snd_all_cid(cmd_parameters_t *pcmd);
static int32_t sd_snd_rel_add(cmd_parameters_t *pcmd);
static int32_t sd_sel_card(cmd_parameters_t *pcmd);
static int32_t sd_snd_csd(cmd_parameters_t *pcmd);
static int32_t sd_en_card_ready(cmd_parameters_t *pcmd_handle);
static int32_t sd_snd_app_bus_cmd(cmd_parameters_t *pcmd);
static int32_t sd_set_bus_width(cmd_parameters_t *pcmd_handle);
static int32_t sd_bus_width_4(cmd_parameters_t *pcmd);

#elif (DEV_TYPE ==  DEV_TYPE_EMMC)
#define BUS_PARAM    1
static int32_t sd_mmc_init(uint64_t *sec_num);
static int32_t mmc_go_idle(cmd_parameters_t *pcmd);
static int32_t mmc_snd_all_cid(cmd_parameters_t *pcmd);
static int32_t mmc_set_rel_add(cmd_parameters_t *pcmd);
static int32_t mmc_check_ocr(cmd_parameters_t *pcmd);
static int32_t mmc_sel_card(cmd_parameters_t *pcmd);
static int32_t mmc_snd_csd(cmd_parameters_t *pcmd);
static int32_t mmc_send_ext_csd(cmd_parameters_t *pcmd,
        uint64_t *sector_count_ref);
static int32_t mmc_switch_bus_width(cmd_parameters_t *pcmd);

static uint8_t ext_csd_buff[512];

#else
#error "Device not supported"
#endif

static int32_t sdmmc_setup_host(void);

static void sdmmc_wait_xfer_done(void);
void sdmmc_irq_handler(void *data);
static void sdmmc_wait_cmd_done(void);

static card_data_t *pcard_specific_data;
static card_data_t card_data;


struct sdmmc_context
{
    bool is_api_sync;
    int32_t status_code;
    volatile bool operation_complete;  /* Flag set by IRQ handler when operation finishes */
    sdmmc_cb_fun xfer_call_back;
    dma_descriptor_t dma_descriptor[SDMMC_MAX_DESCRIPTOR];
    uint32_t is_def_speed_supported;
    uint32_t dev_type;
};

static struct sdmmc_context sdmmc_descriptor;

int32_t sdmmc_read_block_async(uint64_t *pread_buffer, uint64_t read_addr,
        uint32_t block_size, uint32_t number_of_blocks,
        sdmmc_cb_fun xfer_done_call_back)
{
    cmd_parameters_t *pcmd;
    cmd_parameters_t command_config;
    pcmd = &command_config;
    uint32_t req_desc_count;
    int32_t state;
    sdmmc_descriptor.status_code = 0;
    sdmmc_descriptor.operation_complete = false;

    sdmmc_descriptor.is_api_sync = false;
    sdmmc_descriptor.xfer_call_back = xfer_done_call_back;

    if (block_size == 0U)
    {
        return -EINVAL;
    }

    /*convert address into block number*/
    read_addr /= block_size;

    if ((pread_buffer == NULL) || (number_of_blocks == 0U))
    {
        return -EINVAL;
    }
    /*send cmd to set block size*/
    pcmd->argument = block_size;
    pcmd->command_index = SDMMC_CMD_SET_BLOCK_LEN;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);

    if (state != 0)
    {
        return -EIO;
    }

    sdmmc_wait_cmd_done();

    if (sdmmc_descriptor.status_code != 0)
    {
        return -EIO;
    }
    /*argument preparation for data read*/
    if (number_of_blocks > 1U)
    {
        pcmd->argument = read_addr;
        pcmd->command_index = SDMMC_CMD_READ_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    else
    {
        pcmd->argument = read_addr;
        pcmd->command_index = SDMMC_CMD_READ_SINGLE_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    /*calculate no of descriptors required*/
    req_desc_count = ((block_size * number_of_blocks) + (DESC_MAX_XFER_SIZE)
            -1U) / DESC_MAX_XFER_SIZE;

    if (req_desc_count > SDMMC_MAX_DESCRIPTOR)
    {
        return -EIO;
    }

    /*send cmd to request data from the card*/
    else
    {
        sdmmc_set_up_xfer(sdmmc_descriptor.dma_descriptor, pread_buffer,
                block_size, number_of_blocks);
        sdmmc_set_xfer_config(pcmd);
        state = sdmmc_send_command(pcmd);
        if (state != 0)
        {
            return -EIO;
        }

        return 0;
    }
}

int32_t sdmmc_read_block_sync(uint64_t *pread_buffer, uint64_t read_addr,
        uint32_t block_size, uint32_t number_of_blocks)
{
    sdmmc_descriptor.is_api_sync = false;
    cmd_parameters_t *pcmd;
    cmd_parameters_t command_config;
    pcmd = &command_config;
    uint32_t req_desc_count;
    int32_t state;

    sdmmc_descriptor.is_api_sync = true;
    sdmmc_descriptor.status_code = 0;
    sdmmc_descriptor.operation_complete = false;
    if (block_size == 0U)
    {
        return -EINVAL;
    }

    /*convert address into block number*/
    read_addr /= block_size;

    if ((pread_buffer == NULL) || (number_of_blocks == 0U))
    {
        return -EINVAL;
    }
    /*send cmd to set block size*/
    pcmd->argument = block_size;
    pcmd->command_index = SDMMC_CMD_SET_BLOCK_LEN;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);

    if (state != 0)
    {
        return -EIO;
    }

    sdmmc_wait_cmd_done();

    if (sdmmc_descriptor.status_code != 0)
    {
        return -EIO;
    }

    if (number_of_blocks > 1U)
    {
        pcmd->argument = read_addr;
        pcmd->command_index = SDMMC_CMD_READ_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    else
    {
        pcmd->argument = read_addr;
        pcmd->command_index = SDMMC_CMD_READ_SINGLE_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }

    /*calculate no of descriptors required*/
    req_desc_count = ((block_size * number_of_blocks) + (DESC_MAX_XFER_SIZE)
            -1U) / DESC_MAX_XFER_SIZE;

    if (req_desc_count > SDMMC_MAX_DESCRIPTOR)
    {
        return -EIO;
    }

    sdmmc_set_up_xfer(sdmmc_descriptor.dma_descriptor, pread_buffer,
            block_size, number_of_blocks);
    sdmmc_set_xfer_config(pcmd);
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return -EIO;
    }

    sdmmc_wait_xfer_done();

    if (sdmmc_descriptor.status_code == 0)
    {
        cache_force_invalidate((uint64_t *)pread_buffer, block_size *
                number_of_blocks);
        return 0;
    }
    else
    {
        return -EIO;
    }
}

int32_t sdmmc_write_block_async(uint64_t *pwrite_buffer, uint64_t write_addr,
        uint32_t block_size, uint32_t number_of_blocks,
        sdmmc_cb_fun xfer_done_call_back)
{
    cmd_parameters_t *pcmd;
    cmd_parameters_t command_config;
    pcmd = &command_config;
    uint32_t req_desc_count;
    int32_t state;

    sdmmc_descriptor.status_code = 0;
    sdmmc_descriptor.operation_complete = false;
    sdmmc_descriptor.is_api_sync = false;
    sdmmc_descriptor.xfer_call_back = xfer_done_call_back;

    if (block_size == 0U)
    {
        return -EINVAL;
    }

    /*converts address into block number*/
    write_addr /= block_size;

    if ((pwrite_buffer == NULL) || (number_of_blocks == 0U))
    {
        return -EINVAL;
    }
    /*set cmd to set block size*/
    pcmd->argument = block_size;
    pcmd->command_index = SDMMC_CMD_SET_BLOCK_LEN;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);

    if (state != 0)
    {
        return -EIO;
    }

    sdmmc_wait_cmd_done();

    if (sdmmc_descriptor.status_code != 0)
    {
        return -EIO;
    }
    /*argument preparation for data transfer*/
    if (number_of_blocks > 1U)
    {
        pcmd->argument = write_addr;
        pcmd->command_index = SDMMC_CMD_WRITE_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    else
    {
        pcmd->argument = write_addr;
        pcmd->command_index = SDMMC_CMD_WRITE_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    /*calculate no of descriptors required*/
    req_desc_count = ((block_size * number_of_blocks) + (DESC_MAX_XFER_SIZE)
            -1U) / DESC_MAX_XFER_SIZE;
    if (req_desc_count > SDMMC_MAX_DESCRIPTOR)
    {
        return -EIO;
    }

    /*send cmd to transfer data to the card*/
    else
    {
        cache_force_write_back((uint64_t *)pwrite_buffer, block_size *
                number_of_blocks);
        sdmmc_set_up_xfer(sdmmc_descriptor.dma_descriptor, pwrite_buffer,
                block_size, number_of_blocks);
        sdmmc_set_xfer_config(pcmd);

        state = sdmmc_send_command(pcmd);
        if (state != 0)
        {
            return -EIO;
        }
    }
    return 0;
}

int32_t sdmmc_write_block_sync(uint64_t *pwrite_buffer, uint64_t write_addr,
        uint32_t block_size, uint32_t number_of_blocks)
{
    cmd_parameters_t *pcmd;
    cmd_parameters_t command_config;
    pcmd = &command_config;
    uint32_t req_desc_count;
    int32_t state;

    sdmmc_descriptor.is_api_sync = true;
    sdmmc_descriptor.status_code = 0;
    sdmmc_descriptor.operation_complete = false;
    if (block_size == 0U)
    {
        return -EINVAL;
    }

    /*converts address into block number*/
    write_addr /= block_size;

    if ((pwrite_buffer == NULL) || (number_of_blocks == 0U))
    {
        return -EINVAL;
    }
    /*set cmd to set block size*/
    pcmd->argument = block_size;
    pcmd->command_index = SDMMC_CMD_SET_BLOCK_LEN;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);

    if (state != 0)
    {
        return -EIO;
    }

    sdmmc_wait_cmd_done();

    if (sdmmc_descriptor.status_code != 0)
    {
        return -EIO;
    }
    /*argument preparation for data transfer*/
    if (number_of_blocks > 1U)
    {
        pcmd->argument = write_addr;
        pcmd->command_index = SDMMC_CMD_WRITE_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    else
    {
        pcmd->argument = write_addr;
        pcmd->command_index = SDMMC_CMD_WRITE_MULT_BLOCK;
        pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
        pcmd->response_type = SDMMC_SHORT_RESPONSE;
        pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
        pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    }
    /*calculate no of descriptors required*/
    req_desc_count = ((block_size * number_of_blocks) + (DESC_MAX_XFER_SIZE)
            -1U) / DESC_MAX_XFER_SIZE;

    if (req_desc_count > SDMMC_MAX_DESCRIPTOR)
    {
        return -EIO;
    }
    /*send cmd to transfer data to the card*/
    else
    {
        cache_force_write_back((uint64_t *)pwrite_buffer, block_size *
                number_of_blocks);
        sdmmc_set_up_xfer(sdmmc_descriptor.dma_descriptor, pwrite_buffer,
                block_size, number_of_blocks);
        sdmmc_set_xfer_config(pcmd);

        state = sdmmc_send_command(pcmd);
        if (state != 0)
        {
            return -EIO;
        }

        sdmmc_wait_xfer_done();

        if (sdmmc_descriptor.status_code == 0)
        {
            return 0;
        }
        else
        {
            return -EIO;
        }
    }
}


int32_t sdmmc_init_card(uint64_t *ptr_sec_num)
{
    int32_t ret;
    int32_t cmd_status;
    socfpga_interrupt_err_t intr_ret;

    pcard_specific_data = &card_data;
    if (pcard_specific_data == NULL)
    {
        return -EIO;
    }

    if (ptr_sec_num == NULL)
    {
        return -EINVAL;
    }

    if (sdmmc_is_card_present() != SDMMC_IS_CARD_DET)
    {
        printf("ERROR: Device detection failed\n");
        return -EIO;
    }

    sdmmc_descriptor.is_def_speed_supported = SUPPORT_DEF_SPEED;
    sdmmc_descriptor.dev_type = DEV_TYPE;

    intr_ret = interrupt_register_isr(SDMMC_IRQ, sdmmc_irq_handler, NULL);
    if (intr_ret != ERR_OK)
    {
        printf("ERROR: ISR registration failed, code=%d\n", intr_ret);
        return -EIO;
    }

    ret = sdmmc_setup_host();

    if (ret != CTRL_CONFIG_PASS)
    {
        printf("ERROR: Host setup failed, ret=%d (expected %d)\n", ret, CTRL_CONFIG_PASS);
        return -EIO;
    }

    cmd_status = sd_mmc_init(ptr_sec_num);

    if (cmd_status == 0)
    {
        return 0;
    }
    else
    {
        printf("ERROR: Card init failed, status=%d\n", cmd_status);
        return -EIO;
    }
}
#if (DEV_TYPE ==  DEV_TYPE_SD)
/*follows SD association standard*/
static int32_t sd_mmc_init(uint64_t *sec_num)
{
    cmd_parameters_t *pcmd_handle;
    cmd_parameters_t command_config;
    int32_t state;

    pcmd_handle = &command_config;
    /*send cmd to set the card idle*/
    state = sd_go_idle(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD GO_IDLE failed, state=%d\n", state);
        return -EIO;
    }

    /*send cmd to echo back the argument*/
    state = sd_snd_if_cond(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD SEND_IF_COND failed, state=%d\n", state);
        return -EIO;
    }

    /*delay required when the combo phy clock -> 200 MHz*/
    sdmmc_delay_ms(10);

    /*send cmd to put card into ready state*/
    state = sd_en_card_ready(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD card ready check failed, state=%d\n", state);
        return -EIO;
    }

    sd_get_card_type(pcard_specific_data);

    /*send cmd to request cid of the card*/
    state = sd_snd_all_cid(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD ALL_SEND_CID failed, state=%d\n", state);
        return -EIO;
    }

    /*send cmd to req the rel card addr of the card*/
    state = sd_snd_rel_add(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD SEND_REL_ADDR failed, state=%d\n", state);
        return -EIO;
    }

    sd_read_response_rel_addr(pcard_specific_data);

    /*send cmd to request csd of the card*/
    state = sd_snd_csd(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD SEND_CSD failed, state=%d\n", state);
        return -EIO;
    }

    *sec_num = sdmmc_read_sector_count();

    /*send cmd to select the card*/
    state = sd_sel_card(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD SELECT_CARD failed, state=%d\n", state);
        return -EIO;
    }

    state = sd_set_bus_width(pcmd_handle);
    if (state != 0)
    {
        printf("ERROR: SD bus width setting failed, state=%d\n", state);
        return -EIO;
    }

    return state;
}
static int32_t sd_go_idle(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_GO_IDLE_STATE;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_NO_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_snd_if_cond(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_ARG_CHECK_PATTERN;
    pcmd->command_index = SDMMC_CMD_SEND_IF_COND;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_snd_app_cmd(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_SEND_APP;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_check_ocr(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_ARG_SDHC_OCR;
    pcmd->command_index = SDMMC_CMD_READ_OCR;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_snd_all_cid(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_ALL_SEND_CID;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_LONG_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_snd_rel_add(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_SND_REL_ADDR;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;

}
static int32_t sd_en_card_ready(cmd_parameters_t *pcmd_handle)
{
    int32_t state;
    int retry = 100;

    /*
     * Poll for sd card ready by reapetedly issuing APP_CMD and followed
     * by OCR check. A retry count of 100 is provided because some time
     * may be needed to complete interanl power-up and voltage negotiation.
     * If the sdmmc card is not ready within 100 iteration, a timeout is
     * returned.
     */
    while ((sdmmc_is_card_ready()) == 0U && (retry > 0))
    {
        state = sd_snd_app_cmd(pcmd_handle);
        if (state != 0)
        {
            return -EIO;
        }
        state = sd_check_ocr(pcmd_handle);
        if (state != 0)
        {
            return -EIO;
        }
        retry--;
        sdmmc_delay_ms(10);
    }
    if (retry <= 0)
    {
        printf("ERROR: SD card never became ready (timeout)\n");
        return -ETIMEDOUT;
    }
    return 0;
}

static int32_t sd_sel_card(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (pcard_specific_data->relative_address) <<
            SDMMC_ARG_MASK_REL_ADD;
    pcmd->command_index = SDMMC_CMD_SELECT_CARD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE_BUSY;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    sdmmc_descriptor.is_api_sync = true;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_xfer_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_snd_csd(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (pcard_specific_data->relative_address) <<
            SDMMC_ARG_MASK_REL_ADD;
    pcmd->command_index = SDMMC_CMD_SEND_CSD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_LONG_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t sd_set_bus_width(cmd_parameters_t *pcmd_handle)
{
    int32_t state;
    state = sd_snd_app_bus_cmd(pcmd_handle);

    if (state != 0)
    {
        return -EIO;
    }

    state = sd_bus_width_4(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }

    return 0;
}

static int32_t sd_bus_width_4(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_ARG_BUS_WIDTH;
    pcmd->command_index = SDMMC_CMD_SWITCH;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}
static int32_t sd_snd_app_bus_cmd(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (pcard_specific_data->relative_address) <<
            SDMMC_ARG_MASK_REL_ADD;
    pcmd->command_index = SDMMC_CMD_SEND_APP;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}
#endif

#if (DEV_TYPE ==  DEV_TYPE_EMMC)
/*follows e.MMC standard: JESD84-B51A: Embedded MultiMediaCard (e.MMC),
 * Electrical Standard (5.1A)
 */
static int32_t sd_mmc_init(uint64_t *sec_num)
{
    cmd_parameters_t *pcmd_handle;
    cmd_parameters_t command_config;
    int32_t state;

    pcmd_handle = &command_config;
    /*required delay for re-init*/
    osal_task_delay(10);
    /*send cmd to set the card idle*/
    state = mmc_go_idle(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send command to set the card into ready state*/
    state = mmc_check_ocr(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send cmd to request cid of the card*/
    state = mmc_snd_all_cid(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send cmd to set the rel addr of the card*/
    state = mmc_set_rel_add(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    sd_read_response_rel_addr(pcard_specific_data);
    /*send command to req csd of the card*/
    state = mmc_snd_csd(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send cmd to select the card*/
    state = mmc_sel_card(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send cmd to set ext_csd */
    state = mmc_switch_bus_width(pcmd_handle);
    if (state != 0)
    {
        return -EIO;
    }
    /*send cmd to request extended csd of the card*/
    state = mmc_send_ext_csd(pcmd_handle, sec_num);
    return state;
}


static int32_t mmc_go_idle(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_GO_IDLE_STATE;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_NO_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}
static int32_t mmc_sel_card(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (SDMMC_SET_ADDR << SDMMC_ARG_MASK_REL_ADD);
    pcmd->command_index = SDMMC_CMD_SELECT_CARD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE_BUSY;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_xfer_done();
    return sdmmc_descriptor.status_code;
}

static int32_t mmc_snd_csd(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (SDMMC_REL_CARD_ADDRESS << SDMMC_ARG_MASK_REL_ADD);
    pcmd->command_index = SDMMC_CMD_SEND_CSD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_LONG_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t mmc_set_rel_add(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = (SDMMC_REL_CARD_ADDRESS << SDMMC_ARG_MASK_REL_ADD);
    pcmd->command_index = SDMMC_CMD_SET_REL_ADD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    sdmmc_descriptor.is_api_sync = true;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t mmc_snd_all_cid(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_ALL_SEND_CID;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_LONG_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_cmd_done();
    return sdmmc_descriptor.status_code;
}

static int32_t mmc_check_ocr(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_ARG_SDHC_OCR;
    pcmd->command_index = SDMMC_CMD_CHECK_OCR;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;

    while (sdmmc_is_card_ready() == 0U)
    {
        state = sdmmc_send_command(pcmd);
        if (state != 0)
        {
            return state;
        }
        sdmmc_wait_cmd_done();
    }
    return sdmmc_descriptor.status_code;
}

static int32_t mmc_send_ext_csd(cmd_parameters_t *pcmd,
        uint64_t *sector_count_ref)
{
    int32_t state;
    pcmd->argument = SDMMC_NO_CMD_ARG;
    pcmd->command_index = SDMMC_CMD_SEND_EXT_CSD;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_EN;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_EN;

    sdmmc_descriptor.is_api_sync = true;

    sdmmc_set_up_xfer(sdmmc_descriptor.dma_descriptor, (uint64_t *)ext_csd_buff,
            SDMMC_BLOCK_SIZE, SDMMC_SINGLE_BLOCK);
    sdmmc_set_xfer_config(pcmd);

    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return -EIO;
    }
    sdmmc_wait_xfer_done();

    if (sdmmc_descriptor.status_code == 0)
    {
        cache_force_invalidate(ext_csd_buff, SDMMC_BLOCK_SIZE);
        *sector_count_ref = *(uint32_t *)(ext_csd_buff + SDMMC_EXT_CSD_SEC_NUM);
    }
    return sdmmc_descriptor.status_code;
}
static int32_t mmc_switch_bus_width(cmd_parameters_t *pcmd)
{
    int32_t state;
    pcmd->argument = SDMMC_SET_EXT_BUS_WIDTH;
    pcmd->command_index = SDMMC_CMD_SWITCH;
    pcmd->data_xfer_present = SDMMC_DATA_XFER_NOT_PST;
    pcmd->response_type = SDMMC_SHORT_RESPONSE_BUSY;
    pcmd->id_check_enable = SDMMC_CMD_ID_CHECK_DI;
    pcmd->crc_check_enable = SDMMC_CMD_CRC_CHECK_DI;
    sdmmc_descriptor.is_api_sync = true;

    state = sdmmc_send_command(pcmd);
    if (state != 0)
    {
        return state;
    }
    sdmmc_wait_xfer_done();
    return sdmmc_descriptor.status_code;
}
#endif

static int32_t sdmmc_setup_host(void)
{
    /*
       the default mux for shared combo phy is configured
       for the nand ,if combophy is not enabled for
       sdmmc at ATF configure dfi_interface_cfg to 1 through smc
     */
    int32_t ret = CTRL_CONFIG_PASS;
    ret = sdmmc_reset_per0();
    if (ret != CTRL_CONFIG_PASS)
    {
        return ret;
    }
    ret = sdmmc_reset_configs();
    if (ret != CTRL_CONFIG_PASS)
    {
        return ret;
    }
    ret = sdmmc_init_phy();

    if (ret != CTRL_CONFIG_PASS)
    {
        return ret;
    }
    sdmmc_init_configs(sdmmc_descriptor.dev_type,
            sdmmc_descriptor.is_def_speed_supported);
    return ret;
}

uint32_t sdmmc_is_card_present(void)
{
    return sdmmc_is_card_detected();
}

static void sdmmc_wait_xfer_done(void)
{
    /* Poll the interrupt status register directly */
    uint32_t timeout_ms = 1000; /* 1 second timeout */
    uint32_t wait_ms = 0;
    uint32_t int_status;

    while (wait_ms < timeout_ms)
    {
        int_status = sdmmc_get_int_status();

        /* Check for transfer completion or timeout in the status register */
        if ((int_status & SDMMC_XFER_CPT_INT_LOG) || (int_status & SDMMC_XFER_TIMOUT_INT_LOG))
        {
            /* Mimics what the interrupt handler would do */
            if (int_status & SDMMC_XFER_CPT_INT_LOG)
            {
                sdmmc_descriptor.status_code = 0;
            }
            else
            {
                sdmmc_descriptor.status_code = XFER_TIMOUT_ERR;
            }
            sdmmc_descriptor.operation_complete = true;
            break;
        }
        sdmmc_delay_ms(1);
        wait_ms++;
    }

    if (wait_ms >= timeout_ms)
    {
        printf("ERROR: SDMMC transfer timeout\n");
        sdmmc_descriptor.status_code = -ETIMEDOUT;
        sdmmc_descriptor.operation_complete = true;
    }
}

static void sdmmc_wait_cmd_done(void)
{
    /* Poll the interrupt status register directly */
    uint32_t timeout_ms = SDMMC_CMD_TIMEOUT_MS;
    uint32_t wait_ms = 0;
    uint32_t int_status;

    while (wait_ms < timeout_ms)
    {
        int_status = sdmmc_get_int_status();

        /* Check for command completion or timeout in the status register */
        if ((int_status & SDMMC_CMD_CPT_INT_LOG) || (int_status & SDMMC_CMD_TIMOUT_INT_LOG))
        {
            /* Mimics what the interrupt handler would do */
            if (int_status & SDMMC_CMD_CPT_INT_LOG)
            {
                sdmmc_descriptor.status_code = 0;
            }
            else
            {
                sdmmc_descriptor.status_code = -EIO;
            }
            sdmmc_descriptor.operation_complete = true;
            break;
        }
        sdmmc_delay_ms(1);
        wait_ms++;
    }

    if (wait_ms >= timeout_ms)
    {
        printf("ERROR: SDMMC command timeout\n");
        sdmmc_descriptor.status_code = -ETIMEDOUT;
        sdmmc_descriptor.operation_complete = true;
    }
}

void sdmmc_irq_handler(void *data)
{
    (void)data;
    uint32_t volatile int_status = sdmmc_get_int_status();

    /* NOTE: Do NOT clear interrupts here since we're using polling!
     * The polling wait functions read the register directly.
     * If we clear here, the polling will never see the completion bits.
     * Clearing would only be appropriate in a true interrupt-driven model.
     */

    switch (int_status)
    {
        case SDMMC_CMD_CPT_INT_LOG:
            sdmmc_descriptor.status_code = 0;
            sdmmc_descriptor.operation_complete = true;
            break;
        case SDMMC_XFER_CPT_INT_LOG:
            if (sdmmc_descriptor.is_api_sync == true)
            {
                sdmmc_descriptor.status_code = 0;
                sdmmc_descriptor.operation_complete = true;
            }
            else
            {
                sdmmc_descriptor.status_code = 0;
                sdmmc_descriptor.operation_complete = true;
                if (sdmmc_descriptor.xfer_call_back != NULL)
                {
                    sdmmc_descriptor.xfer_call_back(0);
                }
            }
            break;

        case SDMMC_CMD_TIMOUT_INT_LOG:
            sdmmc_descriptor.status_code = -EIO;
            sdmmc_descriptor.operation_complete = true;
            break;

        case SDMMC_XFER_TIMOUT_INT_LOG:
            if (sdmmc_descriptor.is_api_sync == true)
            {
                sdmmc_descriptor.status_code = XFER_TIMOUT_ERR;
                sdmmc_descriptor.operation_complete = true;
            }
            else
            {
                sdmmc_descriptor.status_code = XFER_TIMOUT_ERR;
                sdmmc_descriptor.operation_complete = true;
                if (sdmmc_descriptor.xfer_call_back != NULL)
                {
                    sdmmc_descriptor.xfer_call_back(-EIO);
                }
            }
            break;
        default:
            /*Do Nothing*/
            break;
    }
}

