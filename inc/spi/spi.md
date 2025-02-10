# Serial Peripheral Interface

This driver provides means to control the SPI peripheral.

## IOCTL_SPI_REGS_READ & IOCTL_SPI_REGS_WRITE
Reads and Writes the whole register bank.

## SPI_SET_FRAME_FORMAT & SPI_GET_FRAME_FORMAT
Set and Get Frame Format.
Selects which serial protocol transfers the data.
- **00** – Motorola SPI  
- **01** – Texas Instruments SSP  
- **10** – National Semiconductors Microwire  
- **11** – Reserved  

## SPI_SET_FRAME_SIZE & SPI_GET_FRAME_SIZE
Set and Get Data Frame Size in 32-bit transfer size mode.
Selects the data frame length. When the data frame size is programmed to be less than 32 bits, the receive data are automatically right-justified by the receive logic, with the upper bits of the receive FIFO zero-padded. You must right-justify transmit data before writing into the transmit FIFO. The transmit logic ignores the upper unused bits when transmitting the data.
Note: When SSI_SPI_MODE is either set to “Dual” or “Dual/Quad Both” mode and  SPI_FRF  is not set to 2’b00. 
DFS value should be multiple of 2 if SPI_FRF = 01, and 
DFS value should be multiple of 4 if SPI_FRF = 10.

| Value | Description                        |
|-------|------------------------------------|
| 0x3   | 04-bit serial data transfer        |
| 0x4   | 05-bit serial data transfer        |
| 0x5   | 06-bit serial data transfer        |
| 0x6   | 07-bit serial data transfer        |
| 0x7   | 08-bit serial data transfer        |
| 0x8   | 09-bit serial data transfer        |
| 0x9   | 10-bit serial data transfer        |
| 0xa   | 11-bit serial data transfer        |
| 0xb   | 12-bit serial data transfer        |
| 0xc   | 13-bit serial data transfer        |
| 0xd   | 14-bit serial data transfer        |
| 0xe   | 15-bit serial data transfer        |
| 0xf   | 16-bit serial data transfer        |
| 0x10  | 17-bit serial data transfer        |
| 0x11  | 18-bit serial data transfer        |
| 0x12  | 19-bit serial data transfer        |
| 0x13  | 20-bit serial data transfer        |
| 0x14  | 21-bit serial data transfer        |
| 0x15  | 22-bit serial data transfer        |
| 0x16  | 23-bit serial data transfer        |
| 0x17  | 24-bit serial data transfer        |
| 0x18  | 25-bit serial data transfer        |
| 0x19  | 26-bit serial data transfer        |
| 0x1a  | 27-bit serial data transfer        |
| 0x1b  | 28-bit serial data transfer        |
| 0x1c  | 29-bit serial data transfer        |
| 0x1d  | 30-bit serial data transfer        |
| 0x1e  | 31-bit serial data transfer        |
| 0x1f  | 32-bit serial data transfer        |


## SPI_SET_CONTROL_FRAME_SIZE & SPI_GET_CONTROL_FRAME_SIZE
Set and Get Control Frame Size. 
Selects the length of the control word for the Microwire frame format.
When SSI_SPI_MODE is either set to “Dual” or “Dual/Quad Both” mode and  SPI_FRF  is not set to 2’b00.
This bit defines Length of Address to be transmitted.
Only after this much bits are programmed in to the FIFO the transfer can begin.

| Value | Description            |
|-------|------------------------|
| 0x0   | 01-bit Control Word    |
| 0x1   | 02-bit Control Word    |
| 0x2   | 03-bit Control Word    |
| 0x3   | 04-bit Control Word    |
| 0x4   | 05-bit Control Word    |
| 0x5   | 06-bit Control Word    |
| 0x6   | 07-bit Control Word    |
| 0x7   | 08-bit Control Word    |
| 0x8   | 09-bit Control Word    |
| 0x9   | 10-bit Control Word    |
| 0xa   | 11-bit Control Word    |
| 0xb   | 12-bit Control Word    |
| 0xc   | 13-bit Control Word    |
| 0xd   | 14-bit Control Word    |
| 0xe   | 15-bit Control Word    |
| 0xf   | 16-bit Control Word    |


## SPI_SET_TRANSFER_MODE & SPI_GET_TRANSFER_MODE
Set and Get Transfer Mode.
Selects the mode of transfer for serial communication. This field does not affect the transfer duplicity. Only indicates whether the receive or transmit data are valid. 
In transmit-only mode, data received from the external device is not valid and is not stored in the receive FIFO memory, it is overwritten on the next transfer. 
In receive-only mode, transmitted data are not valid. After the first write to the transmit FIFO, the same word is retransmitted for the duration of the transfer. 
In transmit-and-receive mode, both transmit and receive data are valid. The transfer continues until the transmit FIFO is empty. Data received from the external device are stored into the receive FIFO memory, where it can be accessed by the host processor. 

| Value | Description             |
|-------|-------------------------|
| 00    | Transmit & Receive      |
| 01    | Transmit Only           |
| 10    | Receive Only            |
| 11    | EEPROM Read             |


When SSI_SPI_MODE is either set to “Dual” or “Dual/Quad Both” mode and  SPI_FRF is not set to 2’b00. 
There are only two valid combinations: 

| Value | Description  |
|-------|--------------|
| 01    | Read         |
| 10    | Write        |

## SPI_SET_CLOCK_POLARITY & SPI_GET_CLOCK_POLARITY
Set and Get Serial Clock Polarity.
Valid when the frame format (FRF) is set to Motorola SPI. Used to select the polarity of the inactive serial clock, which is held inactive when the DW_apb_ssi master is not actively transferring data on the serial bus. 

| Value | Description                                     |
|-------|-------------------------------------------------|
| 0x0   | Inactive state of serial clock is low           |
| 0x1   | Inactive state of serial clock is high          |


## SPI_SET_CLOCK_PHASE & SPI_GET_CLOCK_PHASE
Set and Get Serial Clock Phase.
Valid when the frame format (FRF) is set to Motorola SPI. The serial clock phase selects the relationship of the serial clock with the slave select signal.
When SCPH = 0, data are captured on the first edge of the serial clock. 
When SCPH = 1, the serial clock starts toggling one cycle after the slave select line is activated, and data are captured on the second edge of the serial clock. 

| Value | Description                                         |
|-------|-----------------------------------------------------|
| 0x0   | Serial clock toggles in middle of first data bit   |
| 0x1   | Serial clock toggles at start of first data bit    |


## SPI_SET_NUM_DATA_FRAMES & SPI_GET_NUM_DATA_FRAMES
Set and Get Number of Data Frames.
When TMOD = 10 or TMOD = 11 , this register field sets the number of data frames to be continuously received by the DW_apb_ssi. 
The DW_apb_ssi continues to receive serial data until the number of data frames received is equal to this register value plus 1, which enables you to receive up to 64 KB of data in a continuous transfer. 
When the DW_apb_ssi is configured as a serial slave, the transfer continues for as long as the slave is selected. Therefore, this register serves no purpose and is not present when the DW_apb_ssi is configured as a serial slave.

## SPI_SET_SSI_ENABLE & SPI_GET_SSI_ENABLE
Set and Get SSI Enable. 
Enables and disables all DW_apb_ssi operations. 
When disabled, all serial transfers are halted immediately. Transmit and receive FIFO buffers are cleared when the device is disabled. It is impossible to program some of the DW_apb_ssi control registers when enabled. When disabled, the ssi_sleep output is set (after delay) to inform the system that it is safe to remove the ssi_clk, thus saving power consumption in the system.

| Value | Description                    |
|-------|--------------------------------|
| 0x0   | Disables Serial Transfer      |
| 0x1   | Enables Serial Transfer       |



## SPI_SET_MW_TRANSFER_MODE & SPI_GET_MW_TRANSFER_MODE
Set and Get Microwire Transfer Mode.
Defines whether the Microwire transfer is sequential or non-sequential.
When sequential mode is used, only one control word is needed to transmit or receive a block of data words. 
When non-sequential mode is used, there must be a control word for each data word that is transmitted or received.

| Value | Description                        |
|-------|------------------------------------|
| 0x0   | Non-Sequential Microwire Transfer  |
| 0x1   | Sequential Microwire Transfer      |


## SPI_SET_MW_CONTROL & SPI_GET_MW_CONTROL
Set and Get Microwire Control.
Defines the direction of the data word when the Microwire serial protocol is used. 
When this bit is set to 0, the data word is received by the DW_apb_ssi MacroCell from the external serial device. 
When this bit is set to 1, the data word is transmitted from the DW_apb_ssi MacroCell to the external serial device.

| Value | Description               |
|-------|---------------------------|
| 0x0   | SSI receives data         |
| 0x1   | SSI transmits data        |


## SPI_SET_MW_HANDSHAKE & SPI_GET_MW_HANDSHAKE
Set and Get Microwire Handshaking.
Relevant only when the DW_apb_ssi is configured as a serial-master device.
When configured as a serial slave, this bit field has no functionality.
Used to enable and disable the busy/ready handshaking interface for the Microwire protocol. When enabled, the DW_apb_ssi checks for a ready status from the target slave, after the transfer of the last data/control bit, before clearing the BUSY status in the SR register.

| Value | Description                |
|-------|----------------------------|
| 0x0   | Disables Handshaking IF    |
| 0x1   | Enables Handshaking IF     |


## SPI_SET_CS & SPI_GET_CS
Set and Get Slave Enable Register.
This register is valid only when the DW_apb_ssi is configured as a master device. 
When the DW_apb_ssi is configured as a serial slave, writing to this location has no effect; reading from this location returns 0. The register enables the individual slave select output lines from the DW_apb_ssi master. Up to 16 slave-select output pins are available on the DW_apb_ssi master. You cannot write to this register when DW_apb_ssi is busy and when SSI_EN = 1.

This register contains Slave Select Enable Flag.
Each bit in this register corresponds to a slave select line (ss_x_n) from the DW_apb_ssi master. 
When a bit in this register is set (1), the corresponding slave select line from the master is activated when a serial transfer begins. It should be noted that setting or clearing bits in this register have no effect on the corresponding slave select outputs until a transfer is started. Before beginning a transfer, you should enable the bit in this register that corresponds to the slave device with which the master wants to communicate. When not operating in broadcast mode, only one bit in this field should be set.

| Value | Description            |
|-------|------------------------|
| 0x0   | No slave selected      |
| 0x1   | Slave is selected      |


## SPI_SET_BAUD_RATE & SPI_GET_BAUD_RATE
Set and Get Baud Rate Select.
This register is valid only when the DW_apb_ssi is configured as a master device. 
When the DW_apb_ssi is configured as a serial slave, writing to this location has no effect; reading from this location returns 0. The register derives the frequency of the serial clock that regulates the data transfer. The 16-bit field in this register defines the ssi_clk divider value. It is impossible to write to this register when the DW_apb_ssi is enabled. The DW_apb_ssi is enabled and disabled by writing to the SSIENR register.

This register contains SSI Clock Divider.
The LSB for this field is always set to 0 and is unaffected by a write operation, which ensures an even value is held in this register. If the value is 0, the serial output clock (sclk_out) is disabled. The frequency of the sclk_out is derived from the following equation: 
Fsclk_out = Fssi_clk/SCKDV
where SCKDV is any even value between 2 and 65534. 
For example:
for Fssi_clk = 3.6864MHz and SCKDV =2
Fsclk_out = 3.6864/2 = 1.8432MHz

## SPI_SET_TX_FIFO_THRESHOLD & SPI_GET_TX_FIFO_THRESHOLD
Set and Get Transmit FIFO Threshold.
Controls the level of entries (or below) at which the transmit FIFO controller triggers an interrupt. 
The FIFO depth is configurable in the range 2-256, this register is sized to the number of address bits needed to access the FIFO. 
If you attempt to set this value greater than or equal to the depth of the FIFO, this field is not written and retains its current value. 
When the number of transmit FIFO entries is less than or equal to this value, the transmit FIFO empty interrupt is triggered.

## SPI_SET_RX_FIFO_THRESHOLD & SPI_GET_RX_FIFO_THRESHOLD
Set and Get Receive FIFO Threshold.
Controls the level of entries (or above) at which the receive FIFO controller triggers an interrupt. 
The FIFO depth is configurable in the range 2-256. This register is sized to the number of address bits needed to access the FIFO. 
If you attempt to set this value greater than the depth of the FIFO, this field is not written and retains its current value. 
When the number of receive FIFO entries is greater than or equal to this value + 1, the receive FIFO full interrupt is triggered.

## SPI_GET_TX_FIFO_LEVEL
Get Transmit FIFO Level.
Contains the number of valid data entries in the transmit FIFO.

## SPI_GET_RX_FIFO_LEVEL
Get Receive FIFO Level.
Contains the number of valid data entries in the receive FIFO.

## SPI_GET_STATUS
Get Status Register.
This is a read-only register used to indicate the current transfer status, FIFO status, and any transmission/reception errors that may have occurred.
The status register may be read at any time. None of the bits in this register request an interrupt.

## SPI_GET_INTERRUPT_MASK & SPI_SET_INTERRUPT_MASK
Set and Get Interrupt Mask Register
This register can define or read if the interrupts (Transmit FIFO Empty, Transmit FIFO Overflow, Receive FIFO Underflow, Receive FIFO Overflow & Receive FIFO Full) is masked or not.

## SPI_GET_INTERRUPT_STATUS
Get Interrupt Status Register
This register only reads the interrupt status for Transmit FIFO Empty, Transmit FIFO Overflow, Receive FIFO Underflow, Receive FIFO Overflow & Receive FIFO Full.

## SPI_GET_RAW_INTERRUPT_STATUS
Get Raw Interrupt Status Register
This register only reads the raw interrupt status for Transmit FIFO Empty, Transmit FIFO Overflow, Receive FIFO Underflow, Receive FIFO Overflow & Receive FIFO Full.

## SPI_CLEAR_TX_OVERFLOW_INTERRUPT
Clear Transmit FIFO Overflow Interrupt.
This register reflects the status of the interrupt. A read from this register clears the ssi_txo_intr interrupt; writing has no effect.

## SPI_CLEAR_RX_OVERFLOW_INTERRUPT
Clear Receive FIFO Overflow Interrupt.
This register reflects the status of the interrupt. A read from this register clears the ssi_rxo_intr interrupt; writing has no effect.

## SPI_CLEAR_RX_UNDERFLOW_INTERRUPT
Clear Receive FIFO Underflow Interrupt.
This register reflects the status of the interrupt. A read from this register clears the ssi_rxu_intr interrupt; writing has no effect.

## SPI_CLEAR_MULTI_MASTER_INTERRUPT
Clear Multi-Master Contention Interrupt.
This register reflects the status of the interrupt. A read from this register clears the ssi_mst_intr interrupt; writing has no effect.

## SPI_CLEAR_INTERRUPT
Clear Interrupts.
This register is set if any of the interrupts below are active. A read clears the ssi_txo_intr, ssi_rxu_intr, ssi_rxo_intr, and the ssi_mst_intr interrupts. 
Writing to this register has no effect.

## SPI_GET_DMA_CONTROL & SPI_SET_DMA_CONTROL
Set and Get DMA Control Register.
This register is only valid when DW_apb_ssi is configured with a set of DMA Controller interface signals (SSI_HAS_DMA = 1). 
When DW_apb_ssi is not configured for DMA operation, this register will not exist and writing to the register's address will have no effect, reading from this register address will return zero. 
The register is used to enable the DMA Controller interface operation.

## SPI_GET_DMA_TX_THRESHOLD & SPI_SET_DMA_TX_THRESHOLD
Set and Get DMA Transmit Data Level.
This register is only valid when the DW_apb_ssi is configured with a set of DMA interface signals (SSI_HAS_DMA = 1). 
When DW_apb_ssi is not configured for DMA operation, this register will not exist and writing to its address will have no effect, reading from its address will
return zero.

## SPI_GET_DMA_RX_THRESHOLD & SPI_SET_DMA_RX_THRESHOLD
Set and Get DMA Receive Data Level.
This register is only valid when DW_apb_ssi is configured with a set of DMA interface signals (SSI_HAS_DMA = 1). 
When DW_apb_ssi is not configured for DMA operation, this register will not exist and writing to its address will have no effect, reading from its address will return zero.

## SPI_GET_ID
Get Identification Register.
This register contains the peripherals identification code, which is written into the register at configuration time using coreConsultant.

## SPI_GET_VERSION
Get coreKit Version ID Register
Contains the hex representation of the Synopsys component version. Consists of ASCII value for each number in the version, followed by *. For example 32_30_31_2A represents the version 2.01*.

## SPI_GET_RX_SAMPLE_DLY & SPI_SET_RX_SAMPLE_DLY
Set and Get RX Sample Delay.
This register is only valid when the DW_apb_ssi is configured with rxd sample delay logic (SSI_HAS_RX_SAMPLE_DELAY==1). 
When the DW_apb_ssi is not configured with rxd sample delay logic, this register will not exist and writing to its address location will have no effect; reading from its address will return zero. This register control the number of ssi_clk cycles that are delayed (from the default sample time) before the actual sample of the rxd input occurs. It is impossible to write to this register when the DW_apb_ssi is enabled. The DW_apb_ssi is enabled and disabled by writing to the SSIENR register.

This register contains Rxd Sample Delay.
This register is used to delay the sample of the rxd input port. Each value represents a single ssi_clk delay on the sample of rxd. 
Note; If this register is programmed with a value that exceeds the depth of the internal shift registers (SSI_RX_DLY_SR_DEPTH) zero delay will be applied to the rxd sample.


For a detailed register map, please refer to: https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/