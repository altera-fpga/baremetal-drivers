/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_sdmmc_ll.h
 *
 * SDMMC low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SDMMC_LL_H__
#define __SOCFPGA_SDMMC_LL_H__

#define PER0MODRST_ADDR    (0x10D11024U)

#define DESC_MAX_XFER_SIZE    (64U * 1024U)

/* Struct: cmd_parameters_t
 *
 * Describes SDMMC configuration, state, or transfer information.
 */
typedef struct
{
    uint64_t argument;
    uint8_t command_index;
    uint8_t data_xfer_present;
    uint8_t response_type;
    uint8_t id_check_enable;
    uint8_t crc_check_enable;

} cmd_parameters_t;

/* Struct: card_data_t
 *
 * Describes SDMMC configuration, state, or transfer information.
 */
typedef struct
{
    uint64_t relative_address;
    uint8_t card_type;
} card_data_t;

/* Struct: dma_descriptor_t
 *
 * Describes SDMMC configuration, state, or transfer information.
 */
typedef struct __attribute__((packed))
{
    uint8_t attribute;
    uint8_t reserved;
    uint16_t len;
    uint32_t addr_lo;
    uint32_t addr_hi;
} dma_descriptor_t;

#define CMD_SND_OK          0
#define CMD_ERR             1
#define XFER_CPT_OK         2
#define XFER_TIMOUT_ERR     3
#define CTRL_CONFIG_FAIL    4
#define CTRL_CONFIG_PASS    5


/*
 * Disables interrupts.
 *
 * Disables interrupts related to data and response triggers.
 */
/* Function: sdmmc_disable_int
 *
 * Disables the requested SDMMC feature, path, interrupt, or hardware block.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sdmmc_disable_int(void);

/*
 * Configures the host for data transmission and reception.
 *
 * Configures the host based on read/write operation and the number of blocks.
 *
 * params - The command parameter instance.
 */
/* Function: sdmmc_set_xfer_config
 *
 * Writes or configures SDMMC state, data, or register content.
 *
 * Parameters:
 *
 *    params - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sdmmc_set_xfer_config(cmd_parameters_t const *params);

/*
 * Reads the Relative Card Address (RCA).
 *
 * pxcard - Instance containing card-specific data.
 */
/* Function: sd_read_response_rel_addr
 *
 * Reads SDMMC state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    pxcard - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sd_read_response_rel_addr(card_data_t *pxcard);

/*
 * Sets the DMA attributes.
 *
 * Prepares the DMA for data transmission/reception with appropriate attributes.
 *
 * pdesc - Pointer to dynamically allocated memory for descriptor preparation.
 * buff - Memory buffer used for data transmission/reception.
 * block_size - Size of each block in bytes.
 * block_ct - Number of blocks to be transferred/received.
 */
/* Function: sdmmc_set_up_xfer
 *
 * Writes or configures SDMMC state, data, or register content.
 *
 * Parameters:
 *
 *    pdesc - Descriptor describing the transfer, image, or hardware operation.
 *    buff - Caller-provided data buffer.
 *    block_size - Size in bytes of the supplied buffer or transfer.
 *    block_ct - Block or sector address/count value.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sdmmc_set_up_xfer(dma_descriptor_t *pdesc, uint64_t *buff, uint32_t
        block_size, uint32_t block_ct);

/*
 * Checks the card type based on its capacity.
 *
 * pxcard - Reference to card-specific data.
 */
/* Function: sd_get_card_type
 *
 * Reads SDMMC state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    pxcard - Output storage or caller-provided buffer used by the operation.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sd_get_card_type(card_data_t *pxcard);

/*
 * Configures send parameters and sends a command to the card.
 *
 * params - Reference to the parameters loaded for sending the command.
 *
 * Returns: * - CMD_SND_OK, on successfully sending the command.
 * - CTRL_CONFIG_FAIL, on configuration failure.
 */
/* Function: sdmmc_send_command
 *
 * Transfers data through the SDMMC path.
 *
 * Parameters:
 *
 *    params - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
int32_t sdmmc_send_command(const cmd_parameters_t *params);

/*
 * Check if card is present.
 *
 * Returns: * - 1 , if card is detected
 * - 0, if card is not detected
 */
/* Function: sdmmc_is_card_detected
 *
 * Queries the current SDMMC state and reports the result to the caller.
 *
 * Returns:
 *
 *    The requested value, count, address, or status flag.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
uint32_t sdmmc_is_card_detected(void);

/*
 * Check if card enable bit is set.
 *
 * Returns: * - 1 , if enable bit not set.
 * - 0 , if enable bit is set.
 */
/* Function: sdmmc_is_card_ready
 *
 * Queries the current SDMMC state and reports the result to the caller.
 *
 * Returns:
 *
 *    The requested value, count, address, or status flag.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
uint32_t sdmmc_is_card_ready(void);

/*
 * Read interrupt status register.
 *
 * Returns: *  Interrupt status.
 */
/* Function: sdmmc_get_int_status
 *
 * Reads SDMMC state, data, or register content for the caller.
 *
 * Returns:
 *
 *    The requested value, count, address, or status flag.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
uint32_t sdmmc_get_int_status(void);

/*
 * Calculates the sector count of the sd card.
 *
 * Returns: *  Sector count of the sd card.
 */
/* Function: sdmmc_read_sector_count
 *
 * Reads SDMMC state, data, or register content for the caller.
 *
 * Returns:
 *
 *    The requested value, count, address, or status flag.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
uint64_t sdmmc_read_sector_count(void);

/*
 * Resets all sdmmc host configurations.
 *
 * Returns: *  - CTRL_CONFIG_PASS , on reset success.
 *  - CTRL_CONFIG_FAIL , on reset fail.
 */
/* Function: sdmmc_reset_configs
 *
 * Writes or configures SDMMC state, data, or register content.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
int32_t sdmmc_reset_configs(void);

/*
 * Initializes sdmmc host configuration.
 * emmc_bus_width - - setting the bus width to 8.
 * def_speed - - is default speed supported.
 */
/* Function: sdmmc_init_configs
 *
 * Initializes the SDMMC block or software context for use.
 *
 * Parameters:
 *
 *    emmc_bus_width - Input value used by the operation.
 *    def_speed - Input value used by the operation.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sdmmc_init_configs(uint32_t emmc_bus_width, uint32_t def_speed);

/*
 * Resets the sdmmc peripherel.
 *
 * Returns: *  - CTRL_CONFIG_PASS , on reset success.
 *  - CTRL_CONFIG_FAIL , on reset fail.
 */
/* Function: sdmmc_reset_per0
 *
 * Writes or configures SDMMC state, data, or register content.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
int32_t sdmmc_reset_per0(void);

/*
 * Configures the sdmmc combo-phy.
 *
 * Returns: *  - CTRL_CONFIG_PASS , on reset success
 *  - CTRL_CONFIG_FAIL , on reset fail
 */
/* Function: sdmmc_init_phy
 *
 * Initializes the SDMMC block or software context for use.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
int32_t sdmmc_init_phy(void);

/*
 * Clears sdmmc interrupt flags.
 */
/* Function: sdmmc_clear_int
 *
 * Clears the requested SDMMC status, event, or pending condition.
 *
 * Returns:
 *
 *    None.
 *
 * Notes:
 *
 *    Low-level helpers are intentionally thin and expect validated parameters from the caller or higher layer.
 */
void sdmmc_clear_int(void);

#endif /*__SOCFPGA_SDMMC_LL_H__*/
