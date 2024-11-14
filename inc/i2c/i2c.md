# I2C Driver

## Overview
The I2C driver supports both initiator and target mode. Addressing modes are 8-bit and 10-bit.

## Use Cases
The I2C driver and the associated tests enable send and receive of data in both 8-bit and 10-bit addressing mode as an initiator.
As a target, the I2C driver responds to 8-bit and 10-bit addressing requests, but testing coverage is limited.
IOCTL operations expose more operations than the above supported use cases.

## IOCTL_I2C_REGS_READ & IOCTL_I2C_REGS_WRITE
Reads and Writes the whole register bank.

## IOCTL_I2C_SET_MASTER_MODE & IOCTL_I2C_GET_MASTER_MODE
Get and Set the Master Mode.
This bit controls whether the DW_apb_i2c master is enabled.
0: master disabled
1: master enabled
Reset value: IC_MASTER_MODE configuration parameter
NOTE: Software should ensure that if this bit is written with '1' then bit 6(IC_SLAVE_DISABLE) should also be written with a '1'.

## IOCTL_I2C_SET_TARGET_ADDR
This is the target address for any master transaction. When transmitting a General Call, these bits are ignored. To generate a START BYTE, the CPU needs to write only once into these bits.
Reset value: IC_DEFAULT_TAR_SLAVE_ADDR configuration parameter
If the IC_TAR and IC_SAR are the same, loopback exists but the FIFOs are shared between master and slave, so full loopback is not feasible. Only one direction loopback mode is supported (simplex), not duplex. A master cannot transmit to itself; it can transmit only to a slave.

## IOCTL_I2C_GET_INTSTAT
Name: I2C Interrupt Status Register
Size: 15 bits
Address Offset: 0x2C
Read/Write Access: RO
Get High Speed I2C Clock SCL Low Count Register.
Each bit in this register has a corresponding mask bit in the IC_INTR_MASK register. These bits are cleared by reading the matching interrupt clear register. The unmasked raw versions of these bits are available in the IC_RAW_INTR_STAT register.

## IOCTL_I2C_GET_INTSTAT_RAW
Name: I2C Raw Interrupt Status Register
Size: 15 bits
Address Offset: 0x34
Read/Write Access: RO
Get I2C Raw Interrupt Status Register.
Unlike the IC_INTR_STAT register, these bits are not masked so they always show the true status of the DW_apb_i2c.

## IOCTL_I2C_GET_INTMASK & IOCTL_I2C_SET_INTMASK
Name: I2C Interrupt Mask Register
Size: 15 bits
Address Offset: 0x30
Read/Write Access: RW However, 
if configuration parameter IC_SLV_RESTART_DET = 0, bit 13(M_MASTER_ON_HOLD) is read only; 
if configuration parameter I2C_DYNAMIC_TAR_UPDATE = 0 or IC_EMPTYFIFO_HOLD_MASTER_EN = 0, bit 14(RSVD_M_SCL_STUCK_AT_LOW) is read only.
if configuration parameter IC_BUS_CLEAR_FEATURE = 0, bit 15(RSVD_IC_INTR_STAT) is read only.
These bits mask their corresponding interrupt status bits.
They are active high; a value of 0 prevents a bit from generating an interrupt.

## IOCTL_I2C_INTCLR
Name: Clear Combined and Individual Interrupt Register
Size: 1 bit
Address Offset: 0x40
Read/Write Access: RO
Read this register to clear the combined interrupt, all individual interrupts, and the IC_TX_ABRT_SOURCE register. This bit does not clear hardware clearable interrupts but software clearable interrupts. Refer to Bit 9(ABRT_SBYTE_NORSTRT) of the IC_TX_ABRT_SOURCE register for an exception to clearing IC_TX_ABRT_SOURCE.
Reset value: 0x0

## IOCTL_I2C_SET_ENABLE & IOCTL_I2C_GET_ENABLE
Controls whether the DW_apb_i2c is enabled.
0: Disables DW_apb_i2c (TX and RX FIFOs are held in an erased state)
1: Enables DW_apb_i2c
Software can disable DW_apb_i2c while it is active. However, it is important that care be taken to ensure that DW_apb_i2c is disabled properly.
When DW_apb_i2c is disabled, the following occurs:
- The TX FIFO and RX FIFO get flushed.
- Status bits in the IC_INTR_STAT register are still active until DW_apb_i2c goes into IDLE state.
If the module is transmitting, it stops as well as deletes the contents of the transmit buffer after the current transfer is complete. If the module is receiving, the DW_apb_i2c stops the current transfer at the end of the current byte and does not acknowledge the transfer.
In systems with asynchronous pclk and ic_clk when IC_CLK_TYPE parameter set to asynchronous (1), there is a two ic_clk delay when enabling or disabling the DW_apb_i2c.
Reset value: 0x0

## IOCTL_I2C_GET_STATUS
Name: I2C Status Register
Size: 21 bits
Address Offset: 0x70
Read/Write Access: RO
This is a read-only register used to indicate the current transfer status and FIFO status. The status register may be read at any time. None of the bits in this register request an interrupt.
When the I2C is disabled by writing 0 in bit 0(ENABLE) of the IC_ENABLE register:
- Bits 1 and 2 are set to 1
- Bits 3 and 10 are set to 0
When the master or slave state machines goes to idle and ic_en=0:
- Bits 5 and 6 are set to 0

## IOCTL_I2C_SET_TX_FIFO_THRESH & IOCTL_I2C_GET_TX_FIFO_THRESH
Name: I2C Transmit FIFO Threshold Register
Size: 8 bits
Address Offset: 0x3c
Read/Write Access: Read/Write
Get and Set TX FIFO Threshold

## IOCTL_I2C_GET_TX_FIFO_LVL
Name: I2C Transmit FIFO Level Register
Size: TX_ABW + 1
Address Offset: 0x74
Read/Write Access: RO
This register contains the number of valid data entries in the transmit FIFO buffer. It is cleared whenever:
- The I2C is disabled
- There is a transmit abort that is, TX_ABRT bit is set in the IC_RAW_INTR_STAT register
- The slave bulk transmit mode is aborted
The register increments whenever data is placed into the transmit FIFO and decrements when data is taken from the transmit FIFO.

## IOCTL_I2C_SET_RX_FIFO_TRESH & IOCTL_I2C_GET_RX_FIFO_THRESH
Name: I2C Receive FIFO Threshold Register
Size: 8bits
Address Offset: 0x38
Read/Write Access: RW
Get and Set RX FIFO threshold

## IOCTL_I2C_GET_RX_FIFO_LVL
Name: I2C Receive FIFO Level Register
Size: RX_ABW + 1
Address Offset: 0x78
Read/Write Access: RO
This register contains the number of valid data entries in the receive FIFO buffer. It is cleared whenever:
- The I2C is disabled
- Whenever there is a transmit abort caused by any of the events tracked in IC_TX_ABRT_SOURCE
The register increments whenever data is placed into the receive FIFO and decrements when data is taken from the receive FIFO.

## IOCTL_I2C_SET_TENBIT_ADDR_MODE
This bit controls whether the DW_apb_i2c starts its transfers in 7 or 10-bit addressing mode when acting as a master.
0: 7-bit addressing
1: 10-bit addressing
Dependencies: This bit exists in this register only if the I2C_DYNAMIC_TAR_UPDATE configuration parameter is set to 'Yes' (1).
Reset value: IC_10BITADDR_MASTER configuration parameter

## IOCTL_I2C_SET_DMA_MODE
Name: DMA Control Register
Size: 2 bits
Address Offset: 0x88
Read/Write Access: RW
This register is only valid when DW_apb_i2c is configured with a set of DMA Controller interface signals (IC_HAS_DMA = 1).
When DW_apb_i2c is not configured for DMA operation, this register does not exist and writing to the register's address has no effect and reading from this register address will return zero.
The register is used to enable the DMA Controller interface operation.
There is a separate bit for transmit and receive. This can be programmed regardless of the state of IC_ENABLE.

## IOCTL_I2C_SET_DMA_TX_FIFO_TRIGGER_LEVEL & IOCTL_I2C_GET_DMA_TX_FIFO_TRIGGER_LEVEL
Name: DMA Transmit Data Level Register
Size: log2(IC_TX_BUFFER_DEPTH)  bits
Address Offset: 0x8c
Read/Write Access: RW
This register is only valid when the DW_apb_i2c is configured with a set of DMA interface signals (IC_HAS_DMA = 1). When DW_apb_i2c is not configured
for DMA operation, this register does not exist;
writing to its address has no effect; reading from its address returns zero.

Transmit Data Level.
This bit field controls the level at which a DMA request is made by the transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to or below this field value, and TDMAE = 1.
Reset value: 0x0

## IOCTL_I2C_SET_DMA_RX_FIFO_TRIGGER_LEVEL & IOCTL_I2C_GET_DMA_RX_FIFO_TRIGGER_LEVEL
Name: I2C Receive Data Level Register
Size: log2(IC_RX_BUFFER_DEPTH)  bits
Address Offset: 0x90
Read/Write Access: RW
This register is only valid when DW_apb_i2c is configured with a set of DMA interface signals (IC_HAS_DMA = 1). When DW_apb_i2c is not configured for DMA operation, this register does not exist;
writing to its address has no effect; 
reading from its address returns zero.

Receive Data Level.
This bit field controls the level at which a DMA request is made by the receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal to or more than this field value + 1, and RDMAE =1. For instance, when DMARDL is 0, then dma_rx_req is asserted when 1 or more data entries are present in the receive FIFO.
Reset value: 0x0

## IOCTL_I2C_SET_STD_SCL_HIGHTIME
Name: Standard Speed I2C Clock SCL High Count Register
Size: 16 bits
Address Offset: 0x14
Read/Write Access: RW
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1
This register must be set before any I2C bus transaction can take place to
ensure proper I/O timing. This register sets the SCL clock high-period
count for standard speed. 
This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this register is read only.
NOTE: This register must not be programmed to a value higher than 65525, because DW_apb_i2c uses a 16-bit counter to flag an I2C bus idle condition when this counter reaches a value of IC_SS_SCL_HCNT + 10.
Reset value: IC_SS_SCL_HIGH_COUNT configuration parameter

## IOCTL_I2C_SET_STD_SCL_LOWTIME
Name: Standard Speed I2C Clock SCL Low Count Register
Size: 16 bits
Address Offset: 0x18
Read/Write Access: RW
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1
This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for standard speed. 
This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
The minimum valid value is 8; hardware prevents values less than this being written, and if attempted, results in 8 being set. For designs with APB_DATA_WIDTH = 8, the order of programming is important to ensure the correct operation of DW_apb_i2c. The lower byte must be programmed first, and then the upper byte is programmed.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this register is read only.
Reset value: IC_SS_SCL_LOW_COUNT configuration parameter

## IOCTL_I2C_SET_FAST_SCL_HIGHTIME
Name: Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register
Size: 16 bits
Address Offset: 0x1c
Read/Write Access: RW
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1
This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock high-period count for fast mode or fast mode plus. It is used in high-speed mode to send the Master Code and START BYTE or General CALL. 
This register goes away and becomes read-only returning 0s if IC_MAX_SPEED_MODE = standard. This register can be written only when the I2C interface is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
The minimum valid value is 6; hardware prevents values less than this being written, and if attempted results in 6 being set. For designs with APB_DATA_WIDTH == 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this register is read only.
Reset value: IC_FS_SCL_HIGH_COUNT configuration parameter

## IOCTL_I2C_SET_FAST_SCL_LOWTIME
Name: Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register
Size: 16 bits
Address Offset: 0x20
Read/Write Access: RW
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1
This register must be set before any I2C bus transaction can take place to ensure proper I/O timing. This register sets the SCL clock low period count for fast speed. It is used in high-speed mode to send the Master Code and START BYTE or General CALL. 
This register goes away and becomes read-only returning 0s if IC_MAX_SPEED_MODE = standard.
This register can be written only when the I2C interface is disabled, which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
The minimum valid value is 8; hardware prevents values less than this being written, and if attempted results in 8 being set. For designs with APB_DATA_WIDTH = 8 the order of programming is important to ensure the correct operation of the DW_apb_i2c. The lower byte must be programmed first. Then the upper byte is programmed. If the value is less than 8 then the count value gets changed to 8.
When the configuration parameter IC_HC_COUNT_VALUES is set to 1, this register is read only.
Reset value: IC_FS_SCL_LOW_COUNT configuration parameter

## IOCTL_I2C_SET_TX_SDA_HOLD & IOCLT_I2C_GET_TX_SDA_HOLD
Name: I2C SDA Hold Time Length Register
Size: 24 bits
Address Offset: 0x7c
Read/Write Access: RW
The bits [15:0] of this register are used to control the hold time of SDA during transmit in both slave and master mode (after SCL goes from HIGH to LOW).
The values in this register are in units of ic_clk period.
This register controls the amount of time delay.
The relevant I2C requirement is thd:DAT as detailed in the I2C Bus Specification.

Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a transmitter.
Reset value: IC_DEFAULT_SDA_HOLD[15:0].

## IOCTL_I2C_SET_RX_SDA_HOLD & IOCTL_I2C_GET_RX_SDA_HOLD
Name: I2C SDA Hold Time Length Register
Size: 24 bits
Address Offset: 0x7c
Read/Write Access: RW
The bits [23:16] of this register are used to extend the SDA transition (if any) whenever SCL is HIGH in the receiver in either master or slave mode.
The values in this register are in units of ic_clk period.
This register controls the amount of time delay.
The relevant I2C requirement is thd:DAT as detailed in the I2C Bus Specification.

Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c acts as a receiver.
Reset value: IC_DEFAULT_SDA_HOLD[23:16].

## IOCTL_I2C_SET_SDA_SETUP & IOCTL_I2C_GET_SDA_SETUP
Name: I2C SDA Setup Register
Size: 8 bits
Address Offset: 0x94
Read/Write Access: RW
This register controls the amount of time delay (in terms of number of ic_clk clock periods) introduced in the rising edge of SCL, relative to SDA changing, when DW_apb_i2c services a read request in a slave-transmitter operation.
The relevant I2C requirement is tSU:DAT (note 4) as detailed in the I2C Bus Specification.
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1

SDA Setup.
It is recommended that if the required delay is 1000ns, then for an ic_clk frequency of 10 MHz, IC_SDA_SETUP should be programmed to a value of 11.
Default Reset value: 0x64, but can be hardcoded by setting the IC_DEFAULT_SDA_SETUP configuration parameter.

## IOCTL_I2C_SET_GENERAL_CALL_ENABLE
Returns -1 for now.

## IOCTL_I2C_SET_GENERAL_CALL_ACK
Name: I2C ACK General Call Register
Size: 1 bit
Address Offset: 0x98
Read/Write Access: RW
The register controls whether DW_apb_i2c responds with a ACK or NACK when it receives an I2C General Call address.
Note :This register is applicable only when the DW_apb_i2c is in slave mode 
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1

ACK General Call.
When set to 1, DW_apb_i2c responds with a ACK (by asserting ic_data_oe) when it receives a General Call.
Otherwise, DW_apb_i2c responds with a NACK (by negating ic_data_oe).
Default Reset value: 0x1, but can be hardcoded by setting the IC_DEFAULT_ACK_GENERAL_CALL configuration parameter.

## IOCTL_I2C_SET_SLAVE_NACK
Name: Generate Slave Data NACK Register
Size: 1 bit
Address Offset: 0x84
Read/Write Access: RW
The register is used to generate a NACK for the data part of a transfer when DW_apb_i2c is acting as a slave-receiver. This register only exists when the IC_SLV_DATA_NACK_ONLY parameter is set to 1. When this parameter disabled, this register does not exist and writing to the register's address has no effect.
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1

Generate NACK.
This NACK generation only occurs when DW_apb_i2c is a slave-receiver. 
If this register is set to a value of 1, it can only generate a NACK after a data byte is received; hence, the data transfer is aborted and the data received is not pushed to the receive buffer.
When the register is set to a value of 0, it generates NACK/ACK, depending on normal criteria.
1 = generate NACK after data byte received
0 = generate NACK/ACK normally
Reset value: 0x0

## IOCTL_I2C_CLR_ABORT
Name: Clear TX_ABRT Interrupt Register
Size: 1 bit
Address Offset: 0x54
Read/Write Access: RO
Read this register to clear the TX_ABRT interrupt (bit 6) of the IC_RAW_INTR_STAT register, and the IC_TX_ABRT_SOURCE register.
This also releases the TX FIFO from the flushed/reset state, allowing more writes to the TX FIFO.
Refer to Bit 9 of the IC_TX_ABRT_SOURCE register for an exception to clearing IC_TX_ABRT_SOURCE.
Reset value: 0x0

## IOCTL_I2C_GET_ABORTS
Name: I2C Transmit Abort Source Register
Size: 32 bits
Address Offset: 0x80
Read/Write Access: RO
This register has 32 bits that indicate the source of the TX_ABRT bit. Except for Bit 9(ABRT_SBYTE_NORSTRT), this register is cleared whenever the IC_CLR_TX_ABRT register or the IC_CLR_INTR register is read. To clear Bit 9(ABRT_SBYTE_NORSTRT), the source of the ABRT_SBYTE_NORSTRT must be fixed first; RESTART must be enabled (IC_CON[5]=1), the SPECIAL bit must be cleared (IC_TAR[11]), or the GC_OR_START bit must be cleared (IC_TAR[10]).
Once the source of the ABRT_SBYTE_NORSTRT is fixed, then this bit can be cleared in the same manner as other bits in this register. If the source of the ABRT_SBYTE_NORSTRT is not fixed before attempting to clear this bit, Bit 9(ABRT_SBYTE_NORSTRT) clears for one cycle and is then re-asserted.

## IOCTL_I2C_SET_SPIKE_SUPPRESSION & IOCTL_I2C_GET_SPIKE_SUPPRESSION
Name: I2C SS, FS or FM+  spike suppression limit
Size: 8 bits
Address: 0xA0
Read/Write Access: RW
This register is used to store the duration, measured in ic_clk cycles, of the longest spike that is filtered out by the spike suppression logic when the component is operating in SS, FS or FM+ modes. 
The relevant I2C requirement is tSP (table 4) as detailed in the I2C Bus Specification. This register must be programmed with a minimum value of 1.
Dependencies: This register is not applicable  when IC_ULTRA_FAST_MODE=1

This register must be set before any I2C bus transaction can take place to ensure stable operation. This register sets the duration, measured in ic_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic.
This register can be written only when the I2C interface is disabled which corresponds to the IC_ENABLE[0] register being set to 0. Writes at other times have no effect.
The minimum valid value is 1; hardware prevents values less than this being written, and if attempted results in 1 being set. 
Default Reset value: IC_DEFAULT_FS_SPKLEN configuration parameter.

## IOCTL_I2C_CLR_RESTART_DETECT
Name: Clear RESTART_DET Interrupt Register
Size: 1 bit
Address Offset: 0xA8
Read/Write Access: RO
Read this register to clear the RESTART_DET interrupt (bit 12) of IC_RAW_INTR_STAT register.
Reset value: 0x0

## IOCTL_I2C_GET_ENABLE_STATUS
Name: I2C Enable Status Register
Size: 3 bits
Address Offset: 0x9C
Read/Write Access: RO
The register is used to report the DW_apb_i2c hardware status when the IC_ENABLE[0] register is set from 1 to 0; that is, when DW_apb_i2c is disabled.
If IC_ENABLE[0] has been set to 1, bits 2:1(SLV_DISABLED_WHILE_BUSY & SLV_RX_DATA_LOST) are forced to 0, and bit 0(IC_EN) is forced to 1.
If IC_ENABLE[0] has been set to 0, bits 2:1(SLV_DISABLED_WHILE_BUSY & SLV_RX_DATA_LOST) is only be valid as soon as bit 0(IC_EN) is read as '0'.
Note: When IC_ENABLE[0] has been written with '0' a delay occurs for bit 0(IC_EN) to be read as '0' because disabling the DW_apb_i2c depends on I2C bus activities.

ic_en Status.
This bit always reflects the value driven on the output port ic_en.
When read as 1, DW_apb_i2c is deemed to be in an enabled state.
When read as 0, DW_apb_i2c is deemed completely inactive.
NOTE: The CPU can safely read this bit anytime. When this bit is read as 0, the CPU can safely read SLV_RX_DATA_LOST (bit 2) and SLV_DISABLED_WHILE_BUSY (bit 1).
Reset value: 0x0

## IOCTL_I2C_GET_PARAM
Name: Component Parameter Register 1
Size: 32 bits
Address Offset: 0xf4
Read/Write Access: RO
Note: This is a constant read-only register that contains encoded information about the component's parameter settings. 
The reset value depends on coreConsultant parameter(s).

## IOCTL_I2C_GET_VERSION
Name: I2C Component Version Register
Size: 32 bits
Address Offset: 0xf8
Read/Write Access: RO

Specific values for this register are described in the Releases Table in the DW_apb_i2c Release Notes
Reset value: 0x3230302A

## IOCTL_I2C_GET_TYPE
Name: I2C Component Type Register
Size: 32 bits
Address Offset: 0xfc
Read/Write Access: RO

Designware Component Type number= 0x44_57_01_40. This assigned unique hex value is constant and is derived from the two ASCII letters 'DW' followed by a 16-bit unsigned number.
Reset value: 0x44570140


For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_I2C_summary.html