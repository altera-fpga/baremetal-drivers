# DMA Driver

The Direct Memory Access (DMA) driver is responsible for controlling two DMA controllers. It provides a pair of access functions that facilitate reading from and writing to the entire register bank. The system includes one common register block and four individual register blocks for each channel. Control over these register blocks is managed through IOCTL (Input/Output Control) functions.

## Access to the whole register bank

### dma_read_regs & dma_write_regs
Reads and Writes the whole register bank.

## Common register 

### dma_get_id_reg
Returns the 32-bit hardwired value from the ID register.

### dma_get_comp_ver_no_reg
Returns the 32-bit hardwired Component Version Register.

### dma_set_cfg_reg & dma_get_cfg_reg 
Sets and gets the enable and interrupt enable for the DMA, globally.

### dma_set_chen_enable_reg & dma_get_chen_enable_reg 
Sets and gets the channel enable and its corresponding write enable (write only).

### dma_get_int_status_reg
Returns the interrupt status for channels and common register.

### dma_set_common_int_clear_reg 
Clears specific DMA common register interrupt status.

### dma_set_common_int_sts_en_reg  & dma_get_common_int_sts_en_reg
Sets and/or gets to enable the interrupt status for specific DMA common register.

### dma_set_common_int_sig_en_reg & dma_get_common_int_sig_en_reg 
Sets and/or gets to enable the interrupt signal as a port level interrupt for specific DMA common register.

### dma_get_common_int_status_reg
Returns slave interface access errors.

### dma_set_reset_reg & dma_get_reset_reg 
Sets and gets to initiate the software reset to DMA.

### dma_set_low_power_cfg_reg & dma_get_low_power_cfg_reg
Sets and gets to configure the Context Sensitive Low Power feature. This register should be programmed prior to enabling the channel.

## Channel register
When invoking the IOCTL function, you must specify the channel. Each DMA controller has four available channels. The specific controller (either DMAC0 or DMAC1) is determined when calling `DMA_open()` and must also be provided as an argument to the IOCTL function.

### dma_ch_set_src_addr_reg & dma_ch_get_src_addr_reg
Sets and gets the source address. It shall be programmed by software before the DMA channel is enabled, or by an LLI update before the start of DMA transfer.  While the DMA transfer is in progress, this register is updated to reflect the source address of the current AXI transfer.

### dma_ch_set_dst_addr_reg & dma_ch_get_dst_addr_reg
Sets and gets the destination address. It shall be programmed by software before the DMA channel is enabled, or by an LLI update before the start of DMA transfer.  While the DMA transfer is in progress, this register is updated to reflect the destination address of the current AXI transfer.

### dma_ch_set_blk_tran_size_reg & dma_ch_get_blk_tran_size_reg
Sets and gets the block transfer size (`BLOCK_TS`) when DMA is the flow controller. The size of a block is set in `CHx_CTL.SRC_TR_WIDTH`, then the actual block transfer size would be `(BLOCK_TS + 1)`.

### dma_ch_set_trans_ctl_reg & dma_ch_get_trans_ctl_reg
Sets and gets the control of the DMA transfer. It shall be programmed prior to enabling the channel, except for LLI-based multi-block transfer.
When LLI-based multi-block transfer is enabled, the CHx_CTL register is loaded from the corresponding location of the LLI and it can be varied on a block-by-block basis within a DMA transfer.

### dma_ch_set_trans_cfg2_reg & dma_ch_get_trans_cfg2_reg
Sets and gets the configuration of the DMA transfer. Certain fields are fixed for multi-block transfers, while other settings have varying scopes.

### dma_ch_set_linked_list_point_reg & dma_ch_get_linked_list_point_reg 
Sets and gets the Linked List Poitner (LLP) register. It shall be programmed to point to the first Linked List Item (LLI) in memory prior to enabling the channel if linked-list-based block chaining is enabled. 

### dma_ch_get_status_reg 
Returns the status of DMA transfers for Channelx.

### dma_ch_get_sw_hsk_src_reg & dma_ch_set_sw_hsk_src_reg 
Sets and gets software handshake source register.

### dma_ch_get_sw_hsk_dst_reg & dma_ch_set_sw_hsk_dst_reg
Sets and gets software handshake destination register.

### dma_ch_set_blk_tfr_resume_reg
Sets the block transfer resume request. This register is used during Linked List or Shadow Register based multi-block transfer.

### dma_ch_set_axi_id_reg & dma_ch_get_axi_id_reg
Sets and gets AXI ID register for Channelx.

### dma_ch_set_axi_qos_reg & dma_ch_get_axi_qos_reg 
Sets and gets AXI QOS register for Channelx.

### dma_ch_set_int_status_en_reg & dma_ch_get_int_status_en_reg
Sets and gets to enable the interrupt status for Channelx.

### dma_ch_get_int_status_reg
Returns the interrupt status for Channelx.

### dma_ch_set_int_signal_en_reg & dma_ch_get_int_signal_en_reg
Sets and gets to enable the generation of port level interrupt at the channel level.

### dma_ch_set_int_clear_reg
Clears the interrupt status register for Channelx.

- More details can be found in Register Map: [DMA0](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_DMAC0_summary.html) [DMA1](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_DMAC1_summary.html)