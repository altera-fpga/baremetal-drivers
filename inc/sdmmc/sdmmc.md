# SDMMC Driver

This describes the registers and their operational details for integration of the SD/eMMC Host Controller IP into a target design.
All the control over the registers are via IOCTL functions.

## SDMMC_READ_REGS & SDMMC_WRITE_REGS
Reads and Writes the whole register bank

## SDMMC_GET_HRS00 & SDMMC_SET_HRS00
Get and Set for the General Information Register

### SDMMC_SET_HRS00_SWR
Sets the Software Reset bit. When set to 1, the entore core is reset.

## SDMMC_GET_HRS01 & SDMMC_SET_HRS01 
Get and Set the Debounce setting register

## SDMMC_GET_HRS02 & SDMMC_SET_HRS02
Get and Set the bus setting register

## SDMMC_GET_HRS03 & SDMMC_SET_HRS03
Get and Set the AXI ERROR responses register
These registers extend the standard set of SD-HOST interrupt statuses by information about AXI interface exceptions.
            The registers are divided into three groups:
            - Signal Enable registers allow to enable/mask signaling the Interrupt Status registers (HRS03[3:0]) on interrupt port
            - Status Enable registers allow to enable/disable interrupt source for each Interrupt Status separately
            - Interrupt Status are triggered whenever the interrupt source is detected and the Status Enable register is enabled

## SDMMC_GET_HRS04 & SDMMC_SET_HRS04
Get and Set the register which contains a field that defines the PHY Register Address for read / write accesses to PHY Register done through the HRS05.

## SDMMC_GET_HRS05 & SDMMC_SET_HRS05
Get and Set the register which has PHY Register Data Port
Access to this register generates read or write transaction to Combo PHY Register.
            - When this field is read, a read transaction is sent to PHY through APB interface. Value received in the transaction is passed back as the access result.
            - When this field is write, a write transaction is sent to PHY through APB interface along with the written data.
            - Host Controller -- Combo PHY APB interface does not support unaligned transfers, and so access to this field is limited to 32-bit transactions only. Unaligned (16-bit or 8-bit) access to this field may lead to unexpected result.

## SDMMC_GET_HRS06 & SDMMC_SET_HRS06
Get and Set the emmc control registers

## SDMMC_GET_HRS07 & SDMMC_SET_HRS07
Get and Set IO Delay Information register

## SDMMC_GET_HRS08 & SDMMC_SET_HRS08
Get and Set PHY DLL Update control status register

### SDMMC_SET_HRS08_PHY_DLL_UPDREQ
Setting this controls sdphy_dfi_ctrl_upd_req port

## SDMMC_GET_HRS09 & SDMMC_SET_HRS09
Get and Set PHY Control and Status register

### SDMMC_SET_HRS09_PHY_SW_RESET
Setting this controls sdphy_dll_rst_n

### SDMMC_SET_HRS09_EXTENDED_RD_MODE
Setting this controls sdphy_param_extended_rd_mode port. None of software resets clear this register.

### SDMMC_SET_HRS09_EXTENDED_WR_MODE
Setting this controls sdphy_param_extended_wr_mode port. None of software resets clear this register.

### SDMMC_SET_HRS09_RDCMD_EN
Setting this, dfi_rdcmd_en is forced to 1, else host logic controls the signal.

### SDMMC_SET_HRS09_RDDATA_EN
Setting this, dfi_rddata_en is forced to 1, else host logic controls the signal.

### SDMMC_SET_HRS09_LVSI_TCKSEL
Setting this field defines unit for LVSI_CNT.
    0 - 2*t_CLK (two CLK clock cycles) 
    1 - 4*t_CLK (four CLK clock cycles)
    2 - 8*t_CLK (eight CLK clock cycles)
    3 - 16*t_CLK (sixteen clock cycles) 
    N - (2^(N+1))*t_CLK, where N must equal 0 to 47
    Values above 47 are reserved.

### SDMMC_SET_HRS09_LVSI_CNT 
Setting this field defines period of SDCLK pulse during LVS Identification.
The period varies in range from LVSI_CNT * 2^(LVSI_TCKSEL+1) * t_CLK to (LVSI_CNT + 1) * 2^(LVSI_TCKSEL+1) * t_CLK.
It is recommended to use lower LVSI_TCKSEL value and higher LVSI_CNT value to reduce SDCLK pulse period variation. 
The variation is +1/-1 LVSI_TCLKSEL unit.

## SDMMC_GET_HRS10 & SDMMC_SET_HRS10
Get and Set Host Controller SDCLK start point adjustment.

## SDMMC_GET_HRS12 & SDMMC_SET_HRS12
Get and Set Host Interrupt Status.

## SDMMC_GET_HRS13 & SDMMC_SET_HRS13
Get and Set Host Status Enable.

## SDMMC_GET_HRS14 & SDMMC_SET_HRS14
Get and Set Host Signal Enable.

## SDMMC_GET_HRS16 & SDMMC_SET_HRS16
Get and Set CMD/DAT output delay.

## SDMMC_GET_HRS29
Get SD Magic Number. 
"Product Number" - identification number aligned to the right (LSB).

## SDMMC_GET_HRS30
Get Host Capability Register.
This register states whether configurable options are available or are not available in the SD/eMMC Host Controller configuration. This register gives such information about features not been covered by the standard capability registers (SRS16-SRS18).

## SDMMC_GET_HRS31
Get Host Controller Version.
This register contains the host controller version number.

## SDMMC_GET_HRS32 & SDMMC_SET_HRS32
Get and Set FSM Monitor Register.

### SDMMC_SET_HRS32_ADDR
Setting this field selects which FSM status will be read.

### SDMMC_SET_HRS32_LOAD
Setting this bit to 1 starts internal FSM monitor to load value from selected FSM.
After finishing this bit will be automatically cleared by hardware and FSM status can be read.

## SDMMC_GET_HRS33
Get Tune Status 0 Register.

## SDMMC_GET_HRS34
Get Tune Status 1 Register.



## SDMMC_GET_SRS00 & SDMMC_SET_SRS00
Get and Set SDMA System Address / Argument 2 / 32-bit block count.
This field is used as:
    - 32-bit Block Count register
    - SDMA system memory address
    - Auto CMD23 Argument

## SDMMC_GET_SRS01 & SDMMC_SET_SRS01
Get and Set Block Size / Block Count

## SDMMC_GET_SRS02 & SDMMC_SET_SRS02
Get and Set Argument 1

## SDMMC_GET_SRS03 & SDMMC_SET_SRS03
Get and Set Command / Transfer Mode

## SDMMC_GET_SRS04 & SDMMC_GET_SRS05 & SDMMC_GET_SRS06 & SDMMC_GET_SRS07
These registers store the response returned by the card.
The mapping of the actual device response and the SRS04 - SRS07 contents depends on the type of response.
The type of response is determined by the RTS field (Response Type) for all user-defined commands.
The separate cases are the Auto-CMD12 response (called R1b in the SD Memory Specification) and Auto-CMD23 response (called R1 in the SD Memory Specification).
Auto-CMD12 and Auto-CMD23 responses are handled by the core automatically and goes to the SRS07 register regardless of the RTS value.
SRS04-SRS07 relation to received response field:
    - Auto-CMD12 resp: Response field R[39:8] - RESP3[31:0]
    - Auto-CMD23 resp: Response field R[39:8] - RESP3[31:0]
    - No response: RTS=00b
    - 136-bit: RTS=01b, Response field R[127:8] - {RESP3[23:0], RESP2[31:0], RESP1[31:0], RESP0[31:0]}
    - 48-bit: RTS=10b, Response field R[39:8] - RESP0[31:0]
    - 48-bit with BUSY: RTS=11b, Response field R[39:8] - RESP0[31:0]

Implementation note: Registers value are undefined after reset, and will be valid after response is received.

## SDMMC_GET_SRS08 & SDMMC_SET_SRS08
Get and Set the Buffer Data Port.

## SDMMC_GET_SRS09 & SDMMC_SET_SRS09
Get and Set Present State Register.

## SDMMC_GET_SRS10 & SDMMC_SET_SRS10
Get and Set Host Control 1 (General / Power / Block-Gap / Wake-Up).

## SDMMC_GET_SRS11 & SDMMC_SET_SRS11
Get and Set Host Control 2 (Clock, Timeout, Reset).

### SDMMC_SET_SRS11_ICE
Set Internal Clock Enable bit.
This field is designated to controls (enable/disable) external clock generator (e.g. PLL).
The ICE bits of every slot are logically OR-ed together and then drive the ice pin.
It means, the ice pin is 0 only when ICE in 0 for every slot implemented inside the host.
The ice pin is 1 if at least one of the ICE bits is set to 1.
When set to 0, the clock on sdmclk pin can be stopped externally.
If the sdmclk is stopped, then host goes to a very low power state.
The hosts registers are still operable (read and written operation are valid) even if the clock on sdmclk is stopped.
Setting of the ICE bit does not affect card detection. It means, the card detection works even if the clock on sdmclk is stopped.

### SDMMC_SET_SRS11_SDCE
Sets SD Clock Enable bit.
When set to 1, SDCLK clock is enabled.
When cleared to 0, SDCLK clock is stopped.
The host clears SDCE automatically when card is removed from the slot (i.e. after the high to low transition on pad_mem_ctrl_0 pad).
The SDCLK clock should be stopped by the software when changing the clock divider (i.e. SDCE bit will be cleared before writing SRS11.SDCFSL, SRS11.SDCFSH).
            
### SDMMC_SET_SRS11_SDCFSH
Sets SDCLK Frequency Select (higher part).
This register is an extension to SDCFSL.

### SDMMC_SET_SRS11_SDCFSL
Sets SDCLK Frequency Select (lower part).
This register and SRS11.SDCFSH are used to calculate frequency of SDCLK clock.
The SDCLK frequency is calculated with following expressions:
- sdclk = sdmclk; when (N=0)
- sdclk = sdmclk/2N; when (N>0)
Variable N is concatenation of SRS11.SDCFSH and SRS11.SDCFSL.
The value of SDCFSL, SDCFSH registers can be changed only when SRS11.SDCE (SD Clock Enable)=0.

### SDMMC_SET_SRS11_DTCV
Sets Data Timeout Counter Value.
This value determines the interval by which DAT line timeouts are detected.
The interval can be computed as below:
- 1111b - Reserved
- 1110b - t_sdmclk*2^(27+2)
- 1101b - t_sdmclk*2^(26+2)
- ...
- 0001b - t_sdmclk*2^(14+2)
- 0000b - t_sdmclk*2^(13+2)
Where t_sdmclk is the sdmclk clock periodRefer to the Data Timeout Error (SRS12.EDT) register for information on factors which generate data timeouts.

### SDMMC_SET_SRS11_SRFA
Sets Software Reset For All.
When set to 1, the entire slot is reset.After completing the reset operation, SRFA bit is automatically cleared. It takes some time to complete the reset operation, so the software will wait until SRFA=0, and continue the other operations only when SRFA=0.
Additionally, after SRFA, software should reset and reinitialize card inserted to the slot.
SD Card Power may be enabled 1 ms after this bit is cleared to ensure SD Card has been reset properly.

### SDMMC_SET_SRS11_SRCMD
Sets Software Reset For CMD Line.
When set to 1, resets the logic related to the command generation and response checking.
The following registers and bits are cleared:
- SRS09 register: Command Inhibit CMD
- SRS12 register: Command Complete

After completing the reset operation, SRS11.SRCMD bit is automatically cleared.
It takes some time to complete the reset operation, so the software will wait until SRCMD=0, and continue the other operations only when SRS11.SRCMD=0.

### SDMMC_SET_SRS11_SRDAT
Sets Software Reset For DAT Line.
When set to 1, resets the logic related to the data path, including data buffers and the DMA logic.
The following registers and bits are cleared:
- SRS08 register:
    - Buffer

- SRS09 register:
    - Buffer Read Enable
    - Buffer Write Enable
    - Read Transfer Active
    - Write Transfer Active
    - DAT Line Active
    - Command Inhibit

- DATSRS10 register:
    - Continue Request
    - Stop At Block Gap Request

- SRS12 register:
    - Buffer Read Ready
    - Buffer Write Ready
    - DMA Interrupt
    - Block Gap Event
    - Transfer Complete

After completing the reset operation, SRS11.SRDAT bit is automatically cleared.
It takes some time to complete the reset operation, so the software will wait until SRS11.SRDAT=0, and continue the other operations only when SRS11.SRDAT=0.

## SDMMC_GET_SRS12 & SDMMC_SET_SRS12
Get and Set Error/Normal Interrupt Status.

## SDMMC_GET_SRS13 & SDMMC_SET_SRS13
Get and Set Error/Normal Status Enable.

## SDMMC_GET_SRS14 & SDMMC_SET_SRS14
Get and Set Error/Normal Signal Enable.

## SDMMC_GET_SRS15 & SDMMC_SET_SRS15
Get and Set Host Control #2 / Auto CMD Error Status.

### SDMMC_SET_SRS15_UMS
Sets UHS Mode Select.
Used to select one of UHS-I modes:
- 000b - SDR12
- 001b - SDR25
- 010b - SDR50
- 011b - SDR104
- 100b - DDR50
- 101b - Reserved
- 110b - Reserved
- 111b - Reserved

The selected UHS-I mode (when value is in range 000b-100b) will be ignored when V18SE is 0.

### SDMMC_SET_SRS15_V18SE
Sets 1.8V Signaling Enable.
This bit controls I/O signaling voltage level.
If the bit is 0 or 1, the I/O uses the 3.3V or 1.8V signaling, respectively.
The SW driver will set this bit 1 when UHS-I mode.
Depend on the selected SD interface mode, the software will set this field as follows:
- 0 - for Default Speed, High Speed mode
- 1 - for UHS-I mode

### SDMMC_SET_SRS15_DSS
Sets Driver Strength Select.
This bit controls the electric parameters of I/O driver via sdphy_dfi_drvss output of the SD/eMMC Host Controller core. Up to 4 configurations of I/O driver settings can be implemented:
- 00 - Driver Type B (default)
- 01 - Driver Type A
- 10 - Driver Type C
- 11 - Driver Type D
The bit is ignored when the V18SE is cleared.

### SDMMC_SET_SRS15_EXTNG
Sets Execute Tuning.
This register controls tuning procedure.
The procedure starts when the bit is set 1.
The procedure can be aborted when the bit is cleared.

The bit is read 1 while the procedure is in progress, and 0 when the procedure is finished.
SCS = 0, EXTNG = 0 - Reset and disable clock tuning logic
SCS = 0, EXTNG = 1 - Reset and restart tuning process
SCS = 1, EXTNG = 0 - Stop tuning procedure
SCS = 1, EXTNG = 1 - Start retuning (without clock tuning logic reset)

### SDMMC_SET_SRS15_SCS
Sets Sampling Clock Select.
The host updates this bit when the tuning procedure is finished. If this bit is set to 1, this means that the tuning procedure is successfully completed.
Otherwise it means that procedure failed and clock tuning logic is disabled.
This bit is valid only after the procedure is finished.Writing 1 will be ignored.
Writing 0 will reset and disable tuning block.

### SDMMC_SET_SRS15_LVSIEXEC
Sets LVS Identification Execution.
Setting this field to 1, generates one pulse on SDCLK output.
This bit does not change while DAT[2] stays LOW. After detecting DAT[2] is HIGH, this field automatically changes its value to 0 confirming end of the Low Voltage Sequence.

### SDMMC_SET_SRS15_ADMA2LM
Sets ADMA2 Length Mode.
This bit selects one of ADMA2 Length Modes either 16-bit or 26-bit.
0 - 16-bit Data Length Mode
1 - 26-bit Data Length Mode

### SDMMC_SET_SRS15_CMD23E
Sets CMD23 Enable.
In result of Card Identification process, Host Driver set this bit to 1 if Card supports CMD23 (SCR[33]==1).

### SDMMC_SET_SRS15_HV4E
Sets Host Version 4.00 Enable.
Selects backward (SD Host 3.00 Version) compatibility mode or SD Host 4.00 Version mode.
0 - Version 3.00
1 - Version 4.00
The software can select system address register SRS00 (when this bit is 0) or SRS23 / SRS22 (when this bit is 1) for the SDMA engine.

### SDMMC_SET_SRS15_A64B
Sets 64-bit Addressing.
Specifies the addressing mode for DMA ending. This field is ignored when SRS15.HV4E=0.
0 - 32-bit addressing
1 - 64-bit addressing

### SDMMC_SET_SRS15_PVE
Sets Preset Value Enable
Setting this bit to 1 triggers an automatically update of SRS11.SDCFSL, SRS11.SDCFSH, SRS11.CGS, SRS15.DSS registers by the host.
Values for an update are taken from SRS24 - SRS27 and depends on SRS15.UMS.

## SDMMC_GET_SRS16
Get Capabilities #1.

## SDMMC_GET_SRS17
Get Capabilities #2.

## SDMMC_GET_SRS18
Get Capabilities #3.

## SDMMC_GET_SRS19
Get Capabilities #4.

## SDMMC_GET_SRS20 & SDMMC_SET_SRS20
Get and Set Force Event.
Each field of this register is related to the specific error status. Writing 1 to field will set the status error. This function is provided for SW debug purpose.

## SDMMC_GET_SRS21 & SDMMC_SET_SRS21
Get and Set ADMA Error Status.

## SDMMC_GET_SRS22 & SDMMC_SET_SRS22
Get and Set ADMA/SDMA System Address 1.

## SDMMC_GET_SRS23 & SDMMC_SET_SRS23
Get and Set ADMA/SDMA System Address 2.

## SDMMC_GET_SRS24 & SDMMC_SET_SRS24
Get and Set Preset Value (Default Speed)
SRS24[31:16] - Default Speed if:
SRS15.V18SE = 0
SRS10.HSE   = 0

HWINIT Register - Note this register is hardware initialized after reset and the value read back will match the IP configuration.

## SDMMC_GET_SRS25 & SDMMC_SET_SRS25
Get and Set Preset Value (High Speed and SDR12)
SRS25[15:0] - High Speed if:
SRS15.V18SE=0
SRS.HSE=1

SRS25[31:16] - SDR12 if:
SRS15.V18SE=1
SRS15.UMS=000b

HWINIT Register - Note this register is hardware initialized after reset and the value read back will match the IP configuration.

## SDMMC_GET_SRS26 & SDMMC_SET_SRS26
Get and Set Preset Value (SDR25 and SDR50)
SRS26[15:0] - SDR25 if:
SRS15.V18SE=1
SRS15.UMS=001b

SRS26[31:16] - SDR50 if:
SRS15.V18SE=1
SRS15.UMS=010b

HWINIT Register - Note this register is hardware initialized after reset and the value read back will match the IP configuration.

## SDMMC_GET_SRS27 & SDMMC_SET_SRS27
Get and Set Preset Value (SDR104 and DDR50)
SRS27[15:0] - SDR104 if:
SRS15.V18SE=1
SRS15.UMS=011b

SRS27[31:16] - DDR50 if:
SRS15.V18SE=1
SRS15.UMS=100b

HWINIT Register - Note this register is hardware initialized after reset and the value read back will match the IP configuration.

## SDMMC_GET_SRS30 & SDMMC_SET_SRS30
Get and Set ADMA3 ID Address 1.

## SDMMC_GET_SRS31 & SDMMC_SET_SRS31
Get and Set ADMA3 ID Address 2.



## SDMMC_GET_CRS63
Gets Host Controller Version/Slot Interrupt Status.



## SDMMC_GET_CQRS00
Gets the Command Queuing Version.

## SDMMC_GET_CQRS01
Gets the Command Queuing Capabilities.

## SDMMC_GET_CQRS02 & SDMMC_SET_CQRS02
Get and Set the Command Queuing Configuration.

## SDMMC_GET_CQRS03 & SDMMC_SET_CQRS03
Get and Set the Command Queuing Control.

## SDMMC_GET_CQRS04 & SDMMC_SET_CQRS04
Get and Set the Command Queuing Interrupt Status.
This register has several status bit related to specific interrupt event.
When even happened and related Command Queuing Interrupt Status Enable is set, the status bit is set to 1.
The bits can be cleared by S/W.
Write 0 clears bit.
Write 1 is ignored.

## SDMMC_GET_CQRS05 & SDMMC_SET_CQRS05
Get and Set the Command Queuing Interrupt Status Enable.
Statuses Enable bits enables interrupt sources. The status is enabled when bit is set 1 (S/W wrote 1 to the field).

## SDMMC_GET_CQRS06 & SDMMC_SET_CQRS06
Get and Set Command Queuing Interrupt Signal Enable.
This register allows to turn on or turn off interrupt notification separately for each bit of the Command Queuing Interrupt Status.  When Interrupt status bit is set 1 and related field in this register is set (S/W wrote 1 to the filed),
The Interrupt Status is reported on interrupt port.

## SDMMC_GET_CQRS07 & SDMMC_SET_CQRS07
Get and Set Interrupt Coalescing.
This register allows to group a CQ transfer and report single interrupt for entire group of requested tasks.

### SDMMC_SET_CQRS07_CQICTOVAL
Set Interrupt Coalescing Timeout Value (ICTOVAL)
CQE generates interrupt when internal counter reaches period defined in this field. The counter starts when first transfer with INT=0 is completed.
The counter increments each time when Internal Clock * 1024 period elapsed. S/W can disable this timer by setting this filed to 0.

### SDMMC_SET_CQRS07_CQICTOVALEN
Set Interrupt Coalescing Timeout Value Write Enable (ICTOVALWEN).
This is write enable for CQICTOVAL. When this bit is set 1, the field will be updated.

### SDMMC_SET_CQRS07_CQICCTH
Set Interrupt Coalescing Counter Threshold (ICCTH).
CQE increments internal counter when task with INT=0 is completed. When internal counter reaches this value the coalescing generates interrupt.
S/W can select treshold value in range 1 to 31.
S/W can disable internal counter and interrupt generation by setting this field to 0.

### SDMMC_SET_CQRS07_CQICCTHWEN
Set Interrupt Coalescing Counter Threshold Write Enable (ICCTHWEN).
This is write enable for CQICCTH. When this bit is set 1, the field will be updated.

### SDMMC_SET_CQRS07_CQICCTR
Set Counter and Timer Reset(ICCTR).
S/W resets interrupt coalescing timer and counter.

### SDMMC_SET_CQRS07_CQICED
Set Interrupt Coalescing Enable/Disable.
Enables coalescing mechanism allowing to generate coalescing interrupts.

## SDMMC_GET_CQRS08 & SDMMC_SET_CQRS08
Get and Set Command Queuing Task Descriptor List Base Address.

## SDMMC_GET_CQRS09 & SDMMC_SET_CQRS09
Get and Set Command Queuing Task Descriptor List Base Address Upper 32 Bits.

## SDMMC_GET_CQRS10 & SDMMC_SET_CQRS10
Get and Set Command Queuing Task Doorbell
CQ has 32 tasks have individual bits to start operation on desired task.
The S/W writes 1 on any position from 0 to 31 to start task 0 to 31.
The S/W can request more than one task in single write.
The CQ Engine process tasks in order they were requested:
- when more than one task is requested in single register write, the task with lower number has higher priority over task with higher number.
- task(s) requested in earlier register write has higher priority over task(s) in later register write. The order of the tasks are maintained during all phases of transaction. If given task is not ready for execution, the CQ Engine takes next task with highest number.
CQ Engine needs several clock cycles to push requested in the single register write Task Doorbell to queue.  The slave interface ends write transfer as soon all tasks are in the queue.
When S/W writes 0 to bit in this register, the related task won't start - this value is ignored.
Task Doorbell bit remain 1 until task execution is completed, task is cleared by
Clear All Task or Clear Task with this number or CQ Engine is disabled (CQE=0).

## SDMMC_GET_CQRS11 & SDMMC_SET_CQRS11
Get and Set Task Complete Notification
32 bits related to 32 tasks. If task N is completed N bit is set 1.
Bit that is set 1 can be cleared by writing 1 to this bit.

## SDMMC_GET_CQRS12
Get the Device Queue Status.

## SDMMC_GET_CQRS13
Get the Device Pending Tasks.
This register information which task is submitted to eMMC (CMD44 and CMD45 was sent) and is not executed. Task N is submitted and not executed when N bit is set 1. 
Bit N is cleared when task N is completed.

## SDMMC_GET_CQRS14 & SDMMC_SET_CQRS14
Get and Set Task Clear.
S/W writes 1 to N bit of this register to clear task N.
Bit remains 1 until clear operation is completed. Once operations ends, the CQE clears this bit to 0.
The S/W has to ensure the CQ Engine is halted before clearing tasks.
The S/W can clear only single task.  When any bit of this register is set, the
S/W has no to request new task clear. This operation clears only task in the Host Controller.
The S/W should take care about clearing task in the device.
Writing 0 to register is ignored.

## SDMMC_GET_CQRS16 & SDMMC_SET_CQRS16
Get and Set Send Status Configuration 1.

## SDMMC_GET_CQRS17 & SDMMC_SET_CQRS17
Get and Set Send Status Configuration 2.

## SDMMC_GET_CQRS18
Get the Command Response for Direct-Command Task.

## SDMMC_GET_CQRS20 & SDMMC_SET_CQRS20
Get and Set Response Mode Error Mask.

## SDMMC_GET_CQRS21
Get Task Error Information.

## SDMMC_GET_CQRS22
Get Command Response Index.

## SDMMC_GET_CQRS23
Get Command Response Argument.

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_SDMMC_summary.html