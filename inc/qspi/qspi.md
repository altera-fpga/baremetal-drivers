# QSPI Driver

Quad Serial Peripheral Interface (QSPI) is an extension of the standard Serial Peripheral Interface (SPI) that uses four data lines instead of one, allowing for higher data transfer rates. The QSPI access for HPS is through the PSI link to SDM. Therefore, the request permission from the SDM is required to get exclusive access to the QSPI before using it. This is already implemented in the U-Boot and UEFI bootloaders supported by Altera. *(Need to confirm)* 

All the control over the registers are via IOCTL functions.

## Driver limitations
While the API exposes functions to manage the direct mode interface, direct mode is unsupported.
XIP is unsupported

## Whole register bank access
### qspi_read_regs & qspi_write_regs
Reads and writes the whole register bank.

## CFG whole reg access
### qspi_set_cfg_reg & qspi_get_cfg_reg
Sets and gets the whole CFG reigster.

## CFG field access
### qspi_set_baud_rate_div & qspi_get_baud_rate_div
Sets and gets the baud rate divisor

### qspi_set_enable & qspi_get_enable
Sets and gets the enable bit in CFG register.

### qspi_set_clkpol & qspi_get_clkpol
Sets and gets the clock polarity (quiescent high or quiescent low) in CFG register. (CPOL)

### qspi_set_clkphase & qspi_get_clkphase
Sets and gets the clock phase (CPHA) in CFG register.

### qspi_set_cs_decode & qspi_get_cs_decode
Sets and gets the decoding of chip select in CFG register.

### qspi_set_cs & qspi_get_cs
Sets and gets the decoding of chip select in CFG register.

### qspi_set_write_protect_pin & qspi_get_write_protect_pin
Sets and gets the chip select in CFG register.

### qspi_set_read_params & qspi_get_read_params 
Sets and gets the device read instruction configuration.

### qspi_set_write_params & qspi_get_write_params 
Sets and gets the device write instruction configuration.

### qspi_set_cs_delays & qspi_get_cs_delays
Sets and gets the device delay register.

### qspi_set_read_data_capture_dly & qspi_get_read_data_capture_dly
Sets and gets the read data capture register.

### qspi_set_device_size_params & qspi_get_device_size_params
Sets and gets the device size configuration register.

## Indirect mode subset
### qspi_set_indirect_addr_span & qspi_get_indirect_addr_span
Sets and gets SRAM Partition Configuration

### qspi_set_indirect_base_addr & qspi_get_indirect_base_addr
Sets and gets Indirect AHB Address Trigger

## Configuration and status subset
### qspi_set_dma_cfg & qspi_get_dma_cfg
Sets and gets DMA Peripheral Configuration

### qspi_set_remap_addr & qspi_get_remap_addr
Sets and gets Remap Address

### qspi_set_mode_bits & qspi_get_mode_bits
Sets and gets Mode Bit Configuration

### qspi_get_sram_fill_lvl
Returns SRAM Fill level for read and write operation

## interrupt control and status
### qspi_set_irq_txthresh & qspi_get_irq_txthresh
Sets and gets TX Threshold

### qspi_set_irq_rxthresh & qspi_get_irq_rxthresh
Sets and gets RX Threshold

### qspi_set_irqstat & qspi_get_irqstat
Sets and gets Interrupt Status

### qspi_set_irqmask & qspi_get_irqmask
Sets and gets Interrupt Mask

## Write protect subset
### qspi_set_wrprot & qspi_get_wrprot
Sets and gets Write Protection Control 

### qspi_set_wrprot_low & qspi_get_wrprot_low
Sets and gets Lower Write Protection

### qspi_set_wrprot_high & qspi_get_wrprot_high
Sets and gets Higher Write Protection

## Indirect read subset
### qspi_set_indirect_read & qspi_get_indirect_read
Sets and gets Indirect Read Transfer Control 

### qspi_set_indirect_rd_watermark & qspi_get_indirect_rd_watermark
Sets and gets Indirect Read Transfer Watermark

### qspi_set_indirect_rd_start_addr & qspi_get_indirect_rd_start_addr
Sets and gets Indirect Read Transfer Start Address

### qspi_set_indirect_rd_count & qspi_get_indirect_rd_count
Sets and gets Indirect Read Transfer Number Byte

## Indirect write subset
### qspi_set_indirect_write & qspi_get_indirect_write
Sets and gets Indirect Write Transfer Control 

### qspi_set_indirect_wr_watermark & qspi_get_indirect_wr_watermark
Sets and gets Indirect Write Transfer Watermark

### qspi_set_indirect_wr_start_addr & qspi_get_indirect_wr_start_addr
Sets and gets Indirect Write Transfer Start Address

### qspi_set_indirect_wr_count & qspi_get_indirect_wr_count
Sets and gets Indirect Write Transfer Number Byte


## Flash Command Subset
### qspi_set_flash_cmd & qspi_get_flash_cmd
Sets and gets Flash Command Control

### qspi_set_flash_cmd_addr & qspi_get_flash_cmd_addr
Sets and gets Flash Command Address

### qspi_get_flash_cmd_rd_data
Returns Flash Command Read Data 

### qspi_set_flash_cmd_wr_data & qspi_get_flash_cmd_wr_data
Sets and gets Flash Command Write Data

### qspi_get_module_id
Returns Module ID

More details can be found in [Register Map](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_QSPI_csr_summary.html)