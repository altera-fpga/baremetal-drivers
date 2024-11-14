# I3C Driver

## Overview
This driver provides an interface to the designware i3c interface in the Agilex5e HPS.

## Notes
This driver does not implement the read and write functions. Parameters needed to construct the I3C transaction are passed in as flags to i3c_recv and i3c_send.

## I3C_READ_REGS & I3C_WRITE_REGS
Reads and Writes the whole register bank.

## I3C_CFG_SET & I3C_CFG_GET
Get and Set DWC_mipi_i3c control Register
This Register controls the transfer properties and disposition of controller's capabilities.
Size: 32
Offset: 0
Access: RW

## I3C_CFG_IBA_INC_SET & I3C_CFG_IBA_INC_GET
Get and Set I3C Broadcast Address include
This bit is used in Master mode of operation.
This bit is used to include DWC_mipi_i3c broadcast address (0x7E) for private transfer.
Note: If DWC_mipi_i3c broadcast address is not included for the private transfers, In-band Interrupts (IBI) driven from Slaves might not win address arbitration. Hence, the IBIs get delayed.
Value	Description
0x0	    I3C Broadcast Address is not included for Private Transfers
0x1	    I3C Broadcast Address is included for Private Transfers

## I3C_CFG_I2C_PRESENT_SET & I3C_CFG_I2C_PRESENT_GET
Get and Set I2C Slave Present
This bit is used in master mode of operation. 
This bit indicates whether any Legacy I2C devices are present in the system.
In HDR mode, this field is used to select TSL over TSP in a mixed bus configuration.
Value	Description
0x0	    I2C Slave not present
0x1	    I2C Slave present

## I3C_CFG_HOT_JOIN_SET & I3C_CFG_HOT_JOIN_GET
Get and Set Hot-Join ACK/NACK Control
This bit is used in master mode of operation. 
This bit acts as a global control to ACK/NACK the Hot-Join request from the devices. The DWC_mipi_i3c Master ACK/NACKs the Hot-Join request from other devices connected on the DWC_mipi_i3c bus, based on programming of this bit.
Value	Description
0x0	    Ack Hot-Join requests
0x1	    Nack and send broadcast CCC to disable Hot-Join 
        OR
        auto-disable Hot-Join request

## I3C_CFG_DMA_ENABLE_SET & I3C_CFG_DMA_ENABLE_GET
Get and Set DMA Handshake Interface Enable
This bit is used to enable or disable the DMA Handshaking interface, and is applicable to both Master and Slave modes of operation. 
 - 1: Enables the DMA handshake control to interact with external DMA.
 - 0: The DMA handshake control has no significance.

## I3C_CFG_ABORT_SET & I3C_CFG_ABORT_GET
Get and Set DWC_mipi_i3c Abort
This bit is used in Master mode of operation. 
This bit allows the controller to relinquish the DWC_mipi_i3c bus before completing the issued transfer.
In response to an ABORT request, the controller issues the STOP condition after the complete data byte is transferred or received.
This bit is auto-cleared once the transfer is aborted and the controller issues a 'Transfer Abort' interrupt.

## I3C_CFG_RESUME_SET & I3C_CFG_RESUME_GET
Get and Set DWC_mipi_i3c Resume
This bit is used to resume the controller after it goes to the halt state.
In the Master mode of operation, the controller goes to the halt state (as indicated in PRESENT_STATE Register) due to any type of error in the transfer (the type of error is indicated by ERR_STATUS field in the RESPONSE_QUEUE_PORT register).
After the controller gones to the halt state, the application has to write 1'b1 to this bit to resume the controller.
This bit is auto-cleared once the controller resumes the transfers by initiating the next command.

## I3C_CFG_ENABLE_SET & I3C_CFG_ENABLE_GET
Get and Set Enable
Controls whether or not DWC_mipi_i3c is enabled.
 - 1: Enables the DWC_mipi_i3c controller.
 - 0: Disables the DWC_mipi_i3c controller.

In Master mode of operation, software can disable DWC_mipi_i3c while it is active.
However, the controller may not get disabled immediately and is 'Disabled' after commands in the Command queue (if any) are executed leading to a STOP condition on the bus and Master FSM is in IDLE state (as indicated by PRESENT_STATE Register).

## I3C_DEVICE_ADDR_SET & I3C_DEVICE_ADDR_GET
Get and Set Device Address Register
In the master mode of operation this Register is used to program the Device Dynamic Addresses and its respective valid bit.
Size: 32
Offset: 0x4
Access: RW

## I3C_IOCTL_HW_CAPABILITY_GET
Get and Set Hardware Capability register 
This register reflects the configured capabilities of DWC_mipi_i3c.
Size: 32
Offset: 0x8
Access: RO

## I3C_IOCTL_COMMAND_QUEUE_PORT_SET
Set COMMAND_QUEUE_PORT Register
In Master mode of operation:
Command Descriptor structure is used to schedule the transfers to devices on I3C bus.
There are four types of commands defined
 - Transfer Command
 - Transfer Argument
 - Short Data Argument
 - Address Assignment Command
Size: 32
Offset: 0xC
Access: WO

## I3C_IOCTL_RESPONSE_QUEUE_PORT_GET
Get RESPONSE_QUEUE_PORT Register
In Master mode of operation:
The response status for each Command is written into the Response Queue by the controller if ROC (Response On Completion) bit is set or
if transfer error occurs. The Response Queue can be read through this register. 
It is expected that this register
is be read whenever RESP_READY_STAT_INTR bit is set in INTR_STATUS register. Not doing so might result in execution of new commands getting stalled. A new command is executed only if there is space available in Response Queue to push the corresponding response.
Size: 32
Offset: 0x10
Access: RO

## I3C_IOCTL_TX_DATA_PORT_SET
Set Transmit Data Port Register
This register when written into, writes data to the TX Buffer. This has the same offset as RX_DATA_PORT to provide a single bi-directional data port for transmitting or receiving the data from the DWC_mipi_i3c.
Size: 32
Offset: 0x14
Access: WO
The Transmit Data port is mapped to the Tx-Data Buffer.
The transmit data should always be packed as 4-byte aligned data words and written to the Transmit Data Port register.
If the Command length is not aligned to 4-bytes, then the additional bytes are ignored.

## I3C_IOCTL_IBI_QUEUE_STATUS_GET
Get In-Band Interrupt Queue Status Register
This register is used in master mode of operation. It is expected that this register is read whenever INTR_STATUS.IBI_THLD_STS is set.
This register when read from, returns the data from the IBI Queue and indicates how the controller responded to incoming IBI (SIR,MR and HJ).
Size: 32
Offset: 0x18
Access: RO

## I3C_QUEUE_THLD_CTRL_SET & I3C_QUEUE_THLD_CTRL_GET
Get and Set Queue Threshold Control Register 
This register is used to program the threshold settings for the Queues in DWC_mipi_i3c.
Size: 32
Offset: 0x1C
Access: RW

## I3C_DATA_BUFFER_THLD_CTRL_SET & I3C_DATA_BUFFER_THLD_CTRL_GET
Get and Set Data Buffer Threshold Control Register 
This register is used to program the threshold settings for the Data Buffers in DWC_mipi_i3c.
Size: 32
Offset: 0x20
Access: RW

## I3C_IBI_QUEUE_CTRL_SET & I3C_IBI_QUEUE_CTRL_GET
Get and Set IBI Queue Control Register
This Register is used to control whether or not to intimate the application if an IBI request is rejected (Nacked).
This register is only used in master mode of operation
Size: 32
Offset: 0x24
Access: RW

## I3C_RESET_CONTROL_SET & I3C_RESET_CONTROL_GET
Get and Set Reset Control Register
This Register is used for general software reset and for individual buffer reset.
Size: 32
Offset: 0x34
Access: RW

## I3C_SLV_EVENT_STATUS_GET & I3C_SLV_EVENT_STATUS_SET
Get and Set Slave Event Status Register
This register indicates the status/values of some events/controls that are relavant to slave mode of operation. These values are set by Master initiated CCCs.
Size: 32
Offset: 0x38
Access: RW

## I3C_INTR_STATUS_GET & I3C_INTR_STATUS_SET
Get and Set Interrupt Status Register
Size: 32
Offset: 0x3C
Access: RW

## I3C_INTR_STATUS_EN_GET & I3C_INTR_STATUS_EN_SET
Get and Set Interrupt Status Enable Register.
The interrupt status is updated in INTR_STATUS register only if corresponding Status Enable bit is set.
Size: 32
Offset: 0x40
Access: RW

## I3C_INTR_SIGNAL_EN_GET & I3C_INTR_SIGNAL_EN_SET
Get and Set Interrupt Signal Enable Register
The interrupt pin is triggered based on INTR_STATUS only if corresponding Signal Enable bit is set.
Size: 32
Offset: 0x44
Access: RW

## I3C_IOCTL_INTR_FORCE_SET
Set Interrupt Force Enable Register
Individual interrupts can be forcefully triggered if corresponding Force Enable bit is set, provided
the corresponding bit in the INTR_STATUS_EN register is set.
Size: 32
Offset: 0x48
Access: WO

## I3C_IOCTL_QUEUE_STATUS_LEVEL_GET
Get Queue Status Level Register. 
This register reflects the status level of the Queues in DWC_mipi_i3c.
Size: 32
Offset: 0x4C
Access: RO

## I3C_IOCTL_DATA_BUFFER_STATUS_LEVEL_GET
Get Data Buffer Status Level Register. 
This register reflects the status level of the Buffers in DWC_mipi_i3c.
Size: 32
Offset: 0x50
Access: RO

## I3C_IOCTL_PRESENT_STATE_GET
Get Present State Register
The user can get status of the DWC_mipi_i3c Controller from this 32-bit read only register. This register is relevant in both master and slave mode of operation and is meant to be used to get debug information related to the controllers internal states.
Size: 32
Offset: 0x54
Access: RO

## I3C_IOCTL_DEVICE_ADDR_TABLE_PTR_GET
Get Pointer for Device Address Table
This register is used in master mode of operation.
Size: 32
Offset: 0x5C
Access: RO

## I3C_IOCTL_DEV_CHAR_TABLE_PTR_GET
Get Pointer for Device Characteristics Table
This register is used in master mode of operation.
Size: 32
Offset: 0x60
Access: RW

## I3C_IOCTL_DEV_CHAR_TABLE_PTR_SET_IDX
Set Current index of Device Characteristics Table.
This field returns the current location of Device Characteristics Table index. Initially, this index points to 0.
Once the complete characteristics information of a Slave device is written into Device Characteristics Table during ENTDAA,
this index increments by 1. The first winning device information is stored in Device Characteristics Table index 0,
the second winning device information in index 1, and so on. 
If required, this index can be used to override the location, where  characteristic information of Slave devices on the I3C bus are written during ENTDAA. Hence, this field is useful only if the device is Current Master. During DEFSLV CCC, the index always starts from 0. 
In Non-current Master, this field is always read-only.

## I3C_IOCTL_VENDOR_SPECIFIC_REG_PTR_GET
Get Pointer for Vendor Specific Registers.
This register is used in master mode of operation.
Size: 32
Offset: 0x6C
Access: RO

## I3C_DEVICE_CONTROL_EXT_SET & I3C_DEVICE_CONTROL_EXT_GET
Get and Set Device Control Extended register.
This register is relevant to both Master and Slave modes of operation and hosts functions related to Slaves disposition to incoming GETACCMST CCC from current master. It also allows for the Device Role to be fixed through Software programming in some configurations. 
Size: 32
Offset: 0xB0
Access: RW

## I3C_I3C_OD_TIMING_SET & I3C_I3C_OD_TIMING_GET
Get and Set SCL I3C Open Drain Timing Register
This register sets the SCL clock high period and low period count for I3C Open Drain transfers. The count value takes the number of core_clks to maintain the I/O SCL High/Low Period timing.
Size: 32
Offset: 0xB4
Access: RW

## I3C_I3C_PP_TIMING_SET & I3C_I3C_PP_TIMING_GET
Get and Set SCL I3C Push Pull Timing Register
This register sets the SCL clock high period and low period count for I3C Push Pull transfers. The count value
takes the number of core_clks to maintain the I/O SCL High/Low Period timing.
Size: 32
Offset: 0xB8
Access: RW

## I3C_I2C_FM_TIMING_SET & I3C_I2C_FM_TIMING_GET
Get and Set SCL I2C Fast Mode Timing Register
This register sets the SCL clock high period and low period count for I2C Fast Mode transfers. The count value
takes the number of core_clks to maintain the I/O SCL Low/High period timing.
Size: 32
Offset: 0xBC
Access: RW

## I3C_I2C_FMP_TIMING_SET & I3C_I2C_FMP_TIMING_GET
Get and Set SCL I2C Fast Mode Plus Timing Register
This register sets the SCL clock high period and low period count for I2C Fast Mode Plus transfers. The count value
takes the number of core_clks to maintain the I/O SCL Low/High period timing.
Size: 32
Offset: 0xC0
Access: RW

## I3C_SCL_EXT_LCNT_TIMING_SET & I3C_SCL_EXT_LCNT_TIMING_GET
Get and Set SCL Extended Low Count Timing Register.
This register sets the extended low periods for the I3C transfers to allow the low data rates of the Slave devices
as specified in GETMXDS CCC.The Speed field of Transfer command (COMMAND_QUEUE_PORT_TRANSFER_COMMAND) decides the selection
of extended low period to achieve the lower data rate for the transfers to Slave devices.
 - SDR1: Uses I3C_EXT_LCNT_1 field for the data transfer.
 - SDR2: Uses I3C_EXT_LCNT_2 field for the data transfer.
 - SDR3: Uses I3C_EXT_LCNT_3 field for the data transfer.
 - SDR4: Uses I3C_EXT_LCNT_4 field for the data transfer.
Size: 32
Offset: 0xC8
Access: RW

## I3C_SCL_EXT_TERMN_LCNT_TIMING_SET & I3C_SCL_EXT_TERMN_LCNT_TIMING_GET
Get and Set SCL Termination Bit Low Count Timing Register
This register is used to extend the SCL Low period for Read Termination Bit.
Size: 32
Offset: 0xCC
Access: RW

## I3C_SDA_HOLD_SWITCH_DLY_TIMING_SET & I3C_SDA_HOLD_SWITCH_DLY_TIMING_GET
Get and Set SDA Hold and Mode Switch Delay Timing Register
The Bits [2:0] of this register are used to shift the sda_out with respect to sda_oe while switching transfer from Open Drain timing to Push Pull timing.
The bits [10:8] of this register are used to shift the sda_oe with respect to sda_out while switching transfer from Pus pull timing to Open Drain timing.
The bits [18:16] of this register are used to control the hold time of SDA during transmit mode in SDR & DDR transfers.
Size: 32
Offset: 0xD0
Access: RW

## I3C_BUS_FREE_AVAIL_TIMING_SET & I3C_BUS_FREE_AVAIL_TIMING_GET
Get and Set Bus Free and Available Timing Register 
This register sets the Bus free time for initiating the transfer in master mode or generating IBI in non-current master mode.
Size: 32
Offset: 0xD4
Access: RW

## I3C_IOCTL_VERSION_ID_GET
This register reflects the current release number of DWC_mipi_i3c
Size: 32
Offset: 0xE0
Access: RO
Current release number - 0x3130302A
This field indicates the Synopsys DesignWare Cores DWC_mipi_i3c current release number that is read by an application.
For example, release number "1.00a" is represented in ASCII as 0x313030. Lower 8 bits read from this register can be ignored by the application. An application  reading this register along with the I3C_VER_TYPE register, gathers details of the current release.
Reset Value: 0x3130302A

## I3C_IOCTL_VERSION_TYPE_GET
This register reflects the current release type of DWC_mipi_i3c.
Size: 32
Offset: 0xE4
Access: RO
Current release type 
This field indicates the Synopsys DesignWare Cores DWC_mipi_i3c current release type that is read by an application.
For example, release type "ga" is represented in ASCII as 0x6761 and "ea" is represented as 0x6561. Lower 16 bits read from this register can be ignored by the application if release type is "ga". If release type is "ea" the lower 16 bits represents the "ea" release version.
An application reading this register along with the I3C_VER_ID register, gathers details of the current release.
Reset Value: 0x6C633033

## I3C_IOCTL_QUEUE_SIZE_CAPABILITY_GET
This register reflects the configured size of the Data Buffer and Queues in DWC_mipi_i3c.
Size: 32
Offset: 0xE8
Access: RO

## I3C_DEVICE_ADDRESS_TABLE_SET & I3C_DEVICE_ADDRESS_TABLE_GET
Get and Set the Device Address Table.
Size: 32
Offset: 0x280
Access: RW
There are in all 11 [1-11] address tables. 
When getting the device address table, pass in the index-1 at arg[0].
When setting the device address table, pass in the index-1 at arg[0] and value at arg[1] This requires two 32-bit values to be passed in.

## I3C_IOCTL_DEVICE_CHARACTERISTIC_TABLE_GET
Get the Device Characteristic Table.
This register is used in master mode of operation.
Size: 32
Offset: 0x200
Access: RO
There are in all 8 [1-8] characteristic tables with each one having 4 [1-4] locations.
When inspecting the device characteristic table, pass in the index-1 at arg[0].

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_i3c_main_master_summary.html