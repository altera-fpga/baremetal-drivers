/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_dma.h
 *
 * DMA middleware service interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_DMA_H__
#define __SOCFPGA_DMA_H__

/*
 * DMA Supported Instances
 */
#define DMA_INSTANCE0    0U /*DMA Instance 0*/
#define DMA_INSTANCE1    1U /*DMA Instance 1*/

#define DMA_POLL_NO_EVENT        0
#define DMA_POLL_EVENT_HANDLED   1

/*
 * DMA Channel IDs
 */
#define DMA_CH1    0U       /*DMA Channel 1*/
#define DMA_CH2    1U       /*DMA Channel 2*/
#define DMA_CH3    2U       /*DMA Channel 3*/
#define DMA_CH4    3U       /*DMA Channel 4*/

struct dma_ch_cntxt;

/*
 * The handle type returned by calling dma_open().
 * This represents a DMA channel.
 * This is initialized in open() and returned to caller.
 * The caller must pass this pointer to the rest of APIs.
 */
/* Type: dma_handle_t
 *
 * Opaque DMA handle type used to preserve module state between calls.
 */
typedef struct dma_ch_cntxt *dma_handle_t;

/*
 * Function pointer for user callback. Accepts DMA handle as argument.
 */
/* Callback: dma_callback_t
 *
 * Callback signature used by the DMA module.
 *
 * Parameters:
 *
 *    See the typedef prototype for callback argument order and meaning.
 */
typedef void (*dma_callback_t)(dma_handle_t pdma_handle);

/*
 * DMA Supported Burst Transfer length for Source and destination
 */
/* Enum: dma_burst_len_t
 *
 * Enumerates DMA options, states, commands, or status values.
 *
 * Values:
 *
 *    DMA_BURST_LEN_1 - dma burst len 1 value.
 *    DMA_BURST_LEN_4 - dma burst len 4 value.
 *    DMA_BURST_LEN_8 - dma burst len 8 value.
 *    DMA_BURST_LEN_16 - dma burst len 16 value.
 *    DMA_BURST_LEN_32 - dma burst len 32 value.
 *    DMA_BURST_LEN_64 - dma burst len 64 value.
 *    DMA_BURST_LEN_128 - dma burst len 128 value.
 *    DMA_BURST_LEN_256 - dma burst len 256 value.
 *    DMA_BURST_LEN_512 - dma burst len 512 value.
 *    DMA_BURST_LEN_1024 - dma burst len 1024 value.
 *    DMA_BURST_LEN_MAX - dma burst len max value.
 */
typedef enum
{
    DMA_BURST_LEN_1 = 0, /*1 byte burst transfer*/
    DMA_BURST_LEN_4, /*4 byte burst transfer*/
    DMA_BURST_LEN_8, /*8 byte burst transfer*/
    DMA_BURST_LEN_16, /*16 byte burst transfer*/
    DMA_BURST_LEN_32, /*32 byte burst transfer*/
    DMA_BURST_LEN_64, /*64 byte burst transfer*/
    DMA_BURST_LEN_128, /*128 byte burst transfer*/
    DMA_BURST_LEN_256, /*256 byte burst transfer*/
    DMA_BURST_LEN_512, /*512 byte burst transfer*/
    DMA_BURST_LEN_1024 = 9, /*1024 byte burst transfer*/
    DMA_BURST_LEN_MAX = 9 /*Maximum burst transfer length*/
} dma_burst_len_t;

/*
 * DMA Supported Transfer width for Source and destination
 */
/* Enum: dma_xfer_width_t
 *
 * Enumerates DMA options, states, commands, or status values.
 *
 * Values:
 *
 *    DMA_TRANSFER_WIDTH1 - dma transfer width1 value.
 *    DMA_TRANSFER_WIDTH2 - dma transfer width2 value.
 *    DMA_TRANSFER_WIDTH4 - dma transfer width4 value.
 *    DMA_ID_XFER_WIDTH8 - dma id xfer width8 value.
 *    DMA_ID_XFER_WIDTH16 - dma id xfer width16 value.
 *    DMA_ID_XFER_WIDTH32 - dma id xfer width32 value.
 *    DMA_ID_XFER_WIDTH64 - dma id xfer width64 value.
 *    DMA_ID_XFER_WIDTH_MAX - dma id xfer width max value.
 */
typedef enum
{
    DMA_TRANSFER_WIDTH1 = 0, /*Transfer width of 1 byte*/
    DMA_TRANSFER_WIDTH2, /*Transfer width of 2 bytes*/
    DMA_TRANSFER_WIDTH4, /*Transfer width of 4 bytes*/
    DMA_ID_XFER_WIDTH8, /*Transfer width of 8 bytes*/
    DMA_ID_XFER_WIDTH16, /*Transfer width of 16 bytes*/
    DMA_ID_XFER_WIDTH32, /*Transfer width of 32 bytes*/
    DMA_ID_XFER_WIDTH64 = 6, /*Transfer width of 64 bytes*/
    DMA_ID_XFER_WIDTH_MAX = 6 /*Maximum transfer width*/
} dma_xfer_width_t;

/*
 * DMA Multi-block transfer type
 */
/* Enum: dma_multi_blk_xfer_type_t
 *
 * Enumerates DMA options, states, commands, or status values.
 *
 * Values:
 *
 *    DMA_MULTI_BLK_CONTIGUOUS - dma multi blk contiguous value.
 *    DMA_MULTI_BLK_RELOAD - dma multi blk reload value.
 *    DMA_MULTI_BLK_SHADOW_REG - dma multi blk shadow reg value.
 *    DMA_MULTI_BLK_LL - dma multi blk ll value.
 *    DMA_MULTI_BLK_INVALID_TYPE - dma multi blk invalid type value.
 */
typedef enum
{
    DMA_MULTI_BLK_CONTIGUOUS, /*Multi-block contiguous transfer*/
    DMA_MULTI_BLK_RELOAD, /*Multi-block reload transfer*/
    DMA_MULTI_BLK_SHADOW_REG, /*Multi-block Shadow Register transfer*/
    DMA_MULTI_BLK_LL = 3, /*Multi-block linked list transfer*/
    DMA_MULTI_BLK_INVALID_TYPE = 3 /*Invalid multi-block transfer type*/
} dma_multi_blk_xfer_type_t;

/*
 * DMA supported transfer direction and flow controller options
 */
/* Enum: dma_xfer_type_t
 *
 * Enumerates DMA options, states, commands, or status values.
 *
 * Values:
 *
 *    DMA_MEM_TO_MEM_DMAC - dma mem to mem dmac value.
 *    DMA_MEM_TO_PERI_DMAC - dma mem to peri dmac value.
 *    DMA_PERI_TO_MEM_DMAC - dma peri to mem dmac value.
 *    DMA_PERI_TO_PERI_DMAC - dma peri to peri dmac value.
 *    DMA_PERI_TO_MEM_SRC - dma peri to mem src value.
 *    DMA_PERI_TO_PERI_SRC - dma peri to peri src value.
 *    DMA_MEM_TO_PERI_DST - dma mem to peri dst value.
 *    DMA_PERI_TO_PERI_DST - dma peri to peri dst value.
 *    DMA_INVALID_XFER_TYPE - dma invalid xfer type value.
 */
typedef enum
{
    DMA_MEM_TO_MEM_DMAC = 0, /*Memory to memory transfer, DMAC as flow controller*/
    DMA_MEM_TO_PERI_DMAC, /*Memory to peripheral transfer, DMAC as flow controller*/
    DMA_PERI_TO_MEM_DMAC, /*Peripheral to memory transfer, DMAC as flow controller*/
    DMA_PERI_TO_PERI_DMAC, /*Peripheral to peripheral transfer, DMAC as flow controller*/
    DMA_PERI_TO_MEM_SRC, /*Peripheral to memory transfer, source peripheral as flow controller*/
    DMA_PERI_TO_PERI_SRC, /*Peripheral to peripheral transfer, source peripheral as flow controller*/
    DMA_MEM_TO_PERI_DST, /*Memory to peripheral transfer, destination peripheral as flow controller*/
    DMA_PERI_TO_PERI_DST = 7, /*Peripheral to peripheral transfer, destination peripheral as flow controller*/
    DMA_INVALID_XFER_TYPE = 7 /*Invalid transfer type*/
} dma_xfer_type_t;

/*
 * DMA Channel state
 */
/* Enum: dma_ch_state_t
 *
 * Enumerates DMA options, states, commands, or status values.
 *
 * Values:
 *
 *    DMA_CH_IDLE - dma ch idle value.
 *    DMA_CH_SUSPENDED - dma ch suspended value.
 *    DMA_CH_ABORT - dma ch abort value.
 *    DMA_CH_ACTIVE - dma ch active value.
 *    DMA_CH_ERROR - dma ch error value.
 */
typedef enum
{
    DMA_CH_IDLE, /*Channel is idle*/
    DMA_CH_SUSPENDED, /*Channel is suspended*/
    DMA_CH_ABORT, /*Channel is aborted*/
    DMA_CH_ACTIVE, /*Channel is active*/
    DMA_CH_ERROR, /*Channel encountered a transfer error*/
} dma_ch_state_t;

/*
 * DMA peripheral ID list
 */
/* Enum: dma_peri_id_t
 *
 * Enumerates DMA options, states, commands, or status values.
 */
typedef enum
{
    DMA_FPGA_PERI0, /*DMA peripheral ID for FPGA Peripheral 0*/
    DMA_FPGA_PERI1, /*DMA peripheral ID for FPGA Peripheral 1*/
    DMA_FPGA_PERI2, /*DMA peripheral ID for FPGA Peripheral 2*/
    DMA_FPGA_PERI3, /*DMA peripheral ID for FPGA Peripheral 3*/
    DMA_FPGA_PERI4, /*DMA peripheral ID for FPGA Peripheral 4*/
    DMA_FPGA_PERI5, /*DMA peripheral ID for FPGA Peripheral 5*/
    DMA_FPGA_PERI6, /*DMA peripheral ID for FPGA Peripheral 6*/
    DMA_FPGA_PERI7, /*DMA peripheral ID for FPGA Peripheral 7*/
    DMA_I2C0_TX, /*DMA peripheral ID for I2C instance 0 Tx*/
    DMA_I2C0_RX, /*DMA peripheral ID for I2C instance 0 Rx*/
    DMA_I2C1_TX, /*DMA peripheral ID for I2C instance 1 Tx*/
    DMA_I2C1_RX, /*DMA peripheral ID for I2C instance 1 Rx*/
    DMA_I2C_EMAC0_TX, /*DMA peripheral ID for EMAC instance 0 Tx*/
    DMA_I2C_EMAC0_RX, /*DMA peripheral ID for EMAC instance 0 Rx*/
    DMA_I2C_EMAC1_TX, /*DMA peripheral ID for EMAC instance 1 Tx*/
    DMA_I2C_EMAC1_RX, /*DMA peripheral ID for EMAC instance 1 Rx*/
    DMA_ID_SPI0_MASTER_TX, /*DMA peripheral ID for SPI instance 0 Master Tx*/
    DMA_ID_SPI0_MASTER_RX, /*DMA peripheral ID for SPI instance 0 Master Rx*/
    DMA_ID_SPI0_SLAVE_TX, /*DMA peripheral ID for SPI instance 0 Slave Tx*/
    DMA_ID_SPI0_SLAVE_RX, /*DMA peripheral ID for SPI instance 0 Slave Rx*/
    DMA_ID_SPI1_MASTER_TX, /*DMA peripheral ID for SPI instance 1 Master Tx*/
    DMA_ID_SPI1_MASTER_RX, /*DMA peripheral ID for SPI instance 1 Master Rx*/
    DMA_ID_SPI1_SLAVE_TX, /*DMA peripheral ID for SPI instance 1 Slave Tx*/
    DMA_ID_SPI1_SLAVE_RX, /*DMA peripheral ID for SPI instance 1 Slave Rx*/
    DMA_ID_STM = 26, /*DMA peripheral ID for System Trace Macrocell*/
    DMA_ID_UART0_TX = 28, /*DMA peripheral ID for UART instance 0 Tx*/
    DMA_ID_UART0_RX, /*DMA peripheral ID for UART instance 0 Rx*/
    DMA_ID_UART1_TX, /*DMA peripheral ID for UART instance 1 Tx*/
    DMA_ID_UART1_RX, /*DMA peripheral ID for UART instance 1 Rx*/
    DMA_I2C_EMAC2_TX, /*DMA peripheral ID for EMAC instance 2 Tx*/
    DMA_I2C_EMAC2_RX, /*DMA peripheral ID for EMAC instance 2 Rx*/
    DMA_I3C0_TX = 35, /*DMA peripheral ID for I3C instance 0 Tx*/
    DMA_I3C0_RX, /*DMA peripheral ID for I3C instance 0 Rx*/
    DMA_I3C1_TX, /*DMA peripheral ID for I3C instance 1 Tx*/
    DMA_I3C1_RX, /*DMA peripheral ID for I3C instance 1 Rx*/
    DMA_INVALID_CH = 48 /*Invalid peripheral ID*/
} dma_peri_id_t;

/*
 * Configuration parameters for the DMA.
 *
 * The application will send the user configuration in the form of the
 * following structure in dma_config.
 */
/* Struct: dma_config_t
 *
 * Describes DMA configuration, state, or transfer information.
 */
typedef struct dma_cfg
{
    uint8_t instance; /* DMA controller instance number */
    dma_xfer_type_t ch_dir; /* DMA channel transfer direction */
    uint8_t ch_prio; /* DMA channel priority */
    dma_peri_id_t peri_id; /* Peripheral ID for the DMA channel */
    dma_callback_t callback; /* Callback function for DMA interrupts */

} dma_config_t;

/*
 * Block transfer configuration parameters for the DMA.
 *
 * The application will send the block transfer configuration in the form of the
 * following structure in dma_setup_transfer.
 */
/* Struct: dma_xfer_cfg_t
 *
 * Describes DMA configuration, state, or transfer information.
 */
typedef struct dma_xfer_cfg
{
    uint64_t src; /* Source address for the DMA transfer */
    uint64_t dst; /* Destination address for the DMA transfer */
    uint32_t blk_size; /* Size of the block to be transferred in bytes */
    struct dma_xfer_cfg *next_trnsfr_cfg; /* Pointer to the next block transfer configuration*/

} dma_xfer_cfg_t;

/*
 * Initialize a DMA channel and return the handle to it
 *
 * The application should call this function to initialize the desired DMA channel.
 * The handle shall be passed while calling all other APIs
 *
 * instance - The desired DMA controller instance.
 *                     Select from the DmaInstance_t enum
 * ch - The desired DMA channel instance.
 *                     Select from the DmaChannels_t enum
 *
 * Returns: * - 'the handle to the DMA channel (not NULL)', on success.
 * - 'NULL', if
 *      - invalid instance number
 *      - open same instance more than once before closing it
 *      - failed to enable the interrupt
 */
/* Function: dma_mw_open
 *
 * Opens a DMA instance and prepares it for subsequent operations.
 *
 * Parameters:
 *
 *    instance - Hardware instance index.
 *    ch - Input value used by the operation.
 *
 * Returns:
 *
 *    A valid handle or pointer on success; NULL when the operation cannot be completed.
 */
dma_handle_t dma_mw_open(uint32_t instance, uint32_t ch);

/*
 * Configure the DMA channel parameters
 *
 * This function configures channel properties that does not change every
 * transfer. That is properties like channel direction, peripheral id etc
 *
 * hdma - Handle to the channel returned by the Open()
 * pcfg - The channel configuration structure
 *
 * Returns: * - 0, on success
 * - -EINVAL: if hdma is NULL
 * - -EIO:    if the channel is not opened before invoking dma_config.
 * - -EBUSY:  if another transfer is in progress.
 *
 */
/* Function: dma_mw_config
 *
 * Performs a DMA operation exposed by this layer.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *    pcfg - Configuration structure or configuration selector.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_config(dma_handle_t const hdma, dma_config_t *pcfg);

/*
 * Setup a DMA data transfer
 *
 * This will setup a data transfer with given transfer parameters. It does
 * not start the data transfer.
 *
 * hdma - Handle to the channel returned by the Open()
 * xfer_list - A linked list with transfer parameters of each
 *                      block in a multi-block tranasfer. For each block
 *                      the soource address, destination aaddress and
 *                      transfer size can be specified
 * numxfers - The number of blocks in the linked list
 *
 * Returns: * - 0, on success
 * - -EINVAL: if hdma is NULL
 * - -EFAULT: if xfer_list is NULL or channel is not opened.
 * - -EBUSY:  if another transfer is in progress.
 *
 */
/* Function: dma_mw_setup_transfer
 *
 * Writes or configures DMA state, data, or register content.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *    xfer_list - Output storage or caller-provided buffer used by the operation.
 *    numxfers - Number of items, blocks, or transfers to process.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_setup_transfer(dma_handle_t const hdma, dma_xfer_cfg_t *xfer_list, uint32_t numxfers);

/*
 * Start the data transfer
 *
 * This will start the data transfer which is already set up by dma_setup_transfer.
 *
 * hdma - Handle to the channel returned by the Open()
 *
 * Returns: * - 0, on success
 * - -EINVAL: if hdma is NULL
 * - -EIO:    if channel is not open
 * - -EBUSY:  if another transfer is in progress.
 *
 */
/* Function: dma_mw_start_transfer
 *
 * Starts the requested DMA operation.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_start_transfer(dma_handle_t const hdma);

/*
 * Stop a data transfer in progress
 *
 * This will stop a data transfer which is in progress
 *
 * hdma - Handle to the channel returned by the Open()
 *
 * Returns: * - 0, on success
 * - -EINVAL: if hdma is NULL
 * - -EIO:    if no data trasnfer is in progress
 * - -EIO:    if it fails to stop the transfer
 */
/* Function: dma_mw_stop_transfer
 *
 * Stops the requested DMA operation.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_stop_transfer(dma_handle_t const hdma);

/*
 * Abort a data transfer immediately via hardware ABORT mechanism
 *
 * Issues an immediate hardware abort (CHENREG ABORT bits). Unlike
 * dma_stop_transfer() which suspends then disables gracefully, this
 * forces the channel to stop regardless of in-progress AXI bursts.
 *
 * hdma - Handle to the channel returned by the Open()
 *
 * Returns: * - 0, on success
 * - -EINVAL:    if hdma is NULL
 * - -ETIMEDOUT: if the channel does not deactivate within the timeout
 */
/* Function: dma_mw_abort_transfer
 *
 * Transfers data through the DMA path.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_abort_transfer(dma_handle_t const hdma);

/*
 * Get the current state of a DMA channel
 *
 * hdma - Handle to the channel returned by the Open()
 *
 * Returns: Current dma_ch_state_t value
 */
/* Function: dma_mw_get_channel_status
 *
 * Reads DMA state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    A module-specific value or status code.
 */
dma_ch_state_t dma_mw_get_channel_status(dma_handle_t hdma);

/*
 * Poll for transfer completion without relying on a GIC interrupt.
 *
 * Reads CH_INTSTATUS directly.  If TFR_DONE is set the function performs
 * the same completion work as the ISR (clear interrupt, set channel IDLE,
 * invoke callback) and returns DMA_POLL_EVENT_HANDLED. Returns DMA_POLL_NO_EVENT if the transfer is still
 * in progress.  Used by dma_wait() as a fallback when the GIC interrupt
 * is not delivered (e.g. routing not configured, or simulation delivery constraint).
 *
 * hdma - Handle to the channel returned by dma_open()
 * Returns: DMA_POLL_EVENT_HANDLED if completion was processed, DMA_POLL_NO_EVENT otherwise
 */
/* Function: dma_mw_check_transfer
 *
 * Validates the requested DMA data, status, or configuration.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_check_transfer(dma_handle_t const hdma);

/*
 * Close the dma channel
 *
 * This will close the dma channel
 *
 * hdma - Handle to the channel returned by the Open()
 *
 * Returns: * - 0: on success
 * - -EINVAL: if hdma is NULL
 */
/* Function: dma_mw_close
 *
 * Closes the DMA handle or instance and returns it to the inactive state.
 *
 * Parameters:
 *
 *    hdma - Input value used by the operation.
 *
 * Returns:
 *
 *    0 or a positive result on success; a negative error/status code on failure unless documented otherwise by the implementation.
 */
int32_t dma_mw_close(dma_handle_t const hdma);

/* Backward-compatible aliases for legacy callers. */
#define dma_open               dma_mw_open
#define dma_config             dma_mw_config
#define dma_setup_transfer     dma_mw_setup_transfer
#define dma_start_transfer     dma_mw_start_transfer
#define dma_stop_transfer      dma_mw_stop_transfer
#define dma_abort_transfer     dma_mw_abort_transfer
#define dma_get_channel_status dma_mw_get_channel_status
#define dma_check_transfer     dma_mw_check_transfer
#define dma_close              dma_mw_close

#endif /* __SOCFPGA_DMA_H__ */
