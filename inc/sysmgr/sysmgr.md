# System Manager

This driver allows access to the system manager registers. Refer to the appropriate product TRM for more details.


## SYSMGR_REGS_READ & SYSMGR_REGS_WRITE
Reads and Writes the whole register bank

## SYSMGR_GET_SILICON_ID1
Specifies Silicon ID and revision number.
This is a read only register and a write should return error.

## SYSMGR_GET_SILICON_ID2
Reserved for future use.
This is a read only register and a write should return error.

## SYSMGR_GET_WDDBG & SYSMGR_SET_WDDBG
Get and Set Controls the behavior of the L4 watchdogs when the CPUs are in debug mode. These control registers are used to drive the pause input signal of the L4 watchdogs. Note that the watchdogs built into the MPU automatically are paused when their associated CPU enters debug mode. Only reset by a cold reset.

## SYSMGR_GET_MPU_STATUS
Get MPU control register.

## SYSMGR_GET_SDMMC_L3_MASTER & SYSMGR_SET_SDMMC_L3_MASTER
Get and Set Register for ACE-lite control

## SYSMGR_GET_NAND_L3_MASTER & SYSMGR_SET_NAND_L3_MASTER
Controls the L3 master ARCACHE and AWCACHE AXI signals.
These register bits should be updated only during system initialization prior to removing the peripheral from reset. They may not be changed dynamically during peripheral operation
All fields are reset by a cold or warm reset.

## SYSMGR_GET_USB0_L3_MASTER & SYSMGR_SET_USB0_L3_MASTER
Controls the L3 master HPROT AHB-Lite signal.
These register bits should be updated only during system initialization prior to removing the peripheral from reset. They may not be changed dynamically during peripheral operation
All fields are reset by a cold or warm reset.

## SYSMGR_GET_USB1_L3_MASTER & SYSMGR_SET_USB1_L3_MASTER
Get and Set Register for ACE-lite control - usb31_l3master.

## SYSMGR_GET_TSN_GLOBAL & SYSMGR_SET_TSN_GLOBAL
Controls the L3 master ARCACHE and AWCACHE AXI signals.
These register bits should be updated only during system initialization prior to removing the peripheral from reset. They may not be changed dynamically during peripheral operation
All fields are reset by a cold or warm reset.

## SYSMGR_GET_TSN0 & SYSMGR_SET_TSN0
Get and Set Registers used by the TSN. All fields are reset by a cold or warm reset.

## SYSMGR_GET_TSN1 & SYSMGR_SET_TSN1
Get and Set Registers used by the TSN. All fields are reset by a cold or warm reset.

## SYSMGR_GET_TSN2 & SYSMGR_SET_TSN2
Get and Set Registers used by the TSN. All fields are reset by a cold or warm reset.

## SYSMGR_GET_TSN0_ACE & SYSMGR_SET_TSN0_ACE
Get and Set The TSN0 ACE-lite control register.

## SYSMGR_GET_TSN1_ACE & SYSMGR_SET_TSN1_ACE
Get and Set The TSN1 ACE-lite control register.

## SYSMGR_GET_TSN2_ACE & SYSMGR_SET_TSN2_ACE
Get and Set The TSN2 ACE-lite control register.

## SYSMGR_GET_FPGA_BRIDGE_CTRL & SYSMGR_SET_FPGA_BRIDGE_CTRL
Get and Set fpga_bridge_ctrl register.

## SYSMGR_GET_FPGA_INTF_EN1 & SYSMGR_SET_FPGA_INTF_EN1
Used to disable individual interfaces between the FPGA and HPS.
This register is reset only on a cold reset (ignores warm reset).

## SYSMGR_GET_FPGA_INTF_EN2 & SYSMGR_SET_FPGA_INTF_EN2
Used to disable individual interfaces between the FPGA and HPS.
This register is reset only on a cold reset (ignores warm reset).

## SYSMGR_GET_FPGA_INTF_EN3 & SYSMGR_SET_FPGA_INTF_EN3
Used to disable individual interfaces between the FPGA and HPS.
This register is reset only on a cold reset (ignores warm reset).

## SYSMGR_GET_DMAC0_L3_MASTER & SYSMGR_SET_DMAC0_L3_MASTER
Get and Set Register for ACE-lite control - dma_l3master.

## SYSMGR_GET_ETR_L3_MASTER & SYSMGR_SET_ETR_L3_MASTER
Get and Set Register for ACE-lite control - etr_l3master.

## SYSMGR_GET_DMAC1_L3_MASTER & SYSMGR_SET_DMAC1_L3_MASTER
Get and Set Register for ACE-lite control - dma_l3master.

## SYSMGR_GET_SEC_CTRL_SELECT & SYSMGR_SET_SEC_CTRL_SELECT
This is the clock selection register. The APS oscillator selection is read only register. This value is driven from secure manager FS.

## SYSMGR_GET_OSC_TRIM
This is the osc_trim register to show internal oscillator.

## SYSMGR_GET_DMAC0_CTRL_STATUS_REG & SYSMGR_SET_DMAC0_CTRL_STATUS_REG
Get and Set DMAC0 control status register.

## SYSMGR_GET_DMAC1_CTRL_STATUS_REG & SYSMGR_SET_DMAC1_CTRL_STATUS_REG
Get and Set DMAC1 control status register.

## SYSMGR_GET_ECC_INTMASK_VALUE & SYSMGR_SET_ECC_INTMASK_VALUE
Get and Set ECC interrupt mask register.
This is a read/write register.

## SYSMGR_ECC_INTMASK_SETBITS
Write 1 to set a specific modules interrupt mask.
Reads should not return an error, but the actual read value is "Undefined" 

## SYSMGR_ECC_INTMASK_CLRBITS
Write 1 to Clear a specific modules interrupt mask.
Reads should not return an error, but the actual read value is "Undefined" .

## SYSMGR_GET_ECC_INTSTATUS_SERR
Get ECC single bit error status of individual modules.
A write to this register should return an error.
 
## SYSMGR_GET_ECC_INTSTATUS_DERR
Get ECC double bit error status of individual modules.
A write to this register should return an error.

## SYSMGR_GET_NOC_TIMEOUT & SYSMGR_SET_NOC_TIMEOUT
Get and Set NOC Timeout Enable. Write 1 to enable noc timeout.

## SYSMGR_GET_NOC_IDLESTATUS
Get Status of IDLE from the NOC masters. A 1 in the field means the specific master is idle.

## SYSMGR_GET_FPGA2SOC_CTRL & SYSMGR_SET_FPGA2SOC_CTRL
Converts transactions from fpga2soc to non secure or allows both secure or non-secure transactions by fpga2soc
- **0** - All Transactions from FPGA2SOC is converted to be Non-Secure
- **1** - Both Secure and Non-Secure Transactions is allowed by FPGA2SOC.

## SYSMGR_GET_FPGA_CONFIG
Get FPGA configuration read only register.

## SYSMGR_SET_GPO
Provides a low-latency, low-performance, and simple way to drive general-purpose signals to the FPGA fabric.
Drives s2f_gp[31:0] with specified value. When read, returns the current value being driven to the FPGA fabric.

## SYSMGR_GET_GPI
Provides a low-latency, low-performance, and simple way to read general-purpose signals driven from the FPGA fabric.
The value being driven from the FPGA fabric on f2s_gp[31:0]. If the FPGA is not in User Mode, the value of this field is undefined.

## SYSMGR_GET_MPU & SYSMGR_SET_MPU
Provides a low-latency, low-performance, and simple way to read general-purpose signals driven from the FPGA fabric.
CFGSDISABLE is typically de-asserted (0) from reset until Secure software has configured the GIC-400 and then subsequently asserted permanently to provide extra security.

## SYSMGR_SET_SDM_HPS_SPARE
SDM to HPS spare signals are mapped to a system manager register. PSI side band signals will set these bits and HPS SW will clear this register.

## SYSMGR_GET_HPS_SDM_SPARE & SYSMGR_SET_HPS_SDM_SPARE
HPS to SDM spare signals are mapped to a system manager register.

## SYSMGR_GET_DFI_INTERFACE_CFG & SYSMGR_SET_DFI_INTERFACE_CFG
Get and Set control bit used to set active DFI interface. 
- **0** - DFI interface for HPNFC is active. 
- **1** - DFI interface for SD is active. 
- **2** - DFI interface fo XSPI is active.

## SYSMGR_GET_NAND_DD_CTRL & SYSMGR_SET_NAND_DD_CTRL
Get and Set NAND device discover control.

## SYSMGR_GET_NAND_PHY_CTRL_REG & SYSMGR_SET_NAND_PHY_CTRL_REG
Get and Set NAND PHY control register.

## SYSMGR_GET_NAND_PHY_TSEL_REG & SYSMGR_SET_NAND_PHY_TSEL_REG
Get and Set NAND PHY Termination Select register.

## SYSMGR_GET_NAND_PHY_DQ_TIMING_REG & SYSMGR_SET_NAND_PHY_DQ_TIMING_REG
Get and Set NAND PHY DQ TIming register.

## SYSMGR_GET_NAND_PHY_DQS_TIMING_REG & SYSMGR_SET_NAND_PHY_DQS_TIMING_REG
Get and Set NAND PHY DQS timing register.

## SYSMGR_GET_NAND_PHY_GATE_LPBK_CTRL_REG & SYSMGR_SET_NAND_PHY_GATE_LPBK_CTRL_REG
Get and Set NAND PHY gate loopback control register.

## SYSMGR_GET_NAND_PHY_DLL_MASTER_CTRL_REG & SYSMGR_SET_NAND_PHY_DLL_MASTER_CTRL_REG
Get and Set NAND PHY DLL master control register.

## SYSMGR_GET_NAND_PHY_DLL_SLAVE_CTRL_REG & SYSMGR_SET_NAND_PHY_DLL_SLAVE_CTRL_REG
Get and Set NAND PHY DLL slave control register.

## SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG0 & SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG0
Get and Set NAND Device Discovery Default Settings Register 1.

## SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG1 & SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG1
Get and Set NAND Device Discovery Default Settings Register 2.

## SYSMGR_GET_NAND_DD_STATUS_REG
Get Nand Device Discovery Status Register.

## SYSMGR_GET_NAND_DD_ID_LOW_REG
Get Device ID low Rgister.

## SYSMGR_GET_NAND_DD_ID_HIGH_REG
Get Device ID High Register.

## SYSMGR_GET_NAND_WRITE_PROT_EN_REG & SYSMGR_SET_NAND_WRITE_PROT_EN_REG
Get and Set NAND write protection enable register.

## IOCTL_SYSMGR_GET_SDMMC_CMD_QUEUE_SETTING_REG & IOCTL_SYSMGR_SET_SDMMC_CMD_QUEUE_SETTING_REG
Get and Set SDMMC Command queue setting register. 

## IOCTL_SYSMGR_GET_I3C_SLV_PID_LOW & IOCTL_SYSMGR_SET_I3C_SLV_PID_LOW
Get and Set I3C slave process ID low register.

## IOCTL_SYSMGR_GET_I3C_SLV_PID_HIGH & IOCTL_SYSMGR_SET_I3C_SLV_PID_HIGH
Get and Set I3C slave process ID high register.

## IOCTL_SYSMGR_GET_I3C_SLV_CTRL0 & IOCTL_SYSMGR_SET_I3C_SLV_CTRL0
Get and Set I3C slave control 0 register.

## IOCTL_SYSMGR_GET_I3C_SLV_CTRL1 & IOCTL_SYSMGR_SET_I3C_SLV_CTRL1
Get and Set I3C slave control 1 register.

## IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL & IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL
Get and Set f2s bridge control register.

## IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA0 & IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA0
Get and Set DMA_TBU_STASH control reg0 dma0 register

## IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA1 & IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA1
Get and Set DMA_TBU_STASH control reg0 dma1 register

## IOCTL_SYSMGR_GET_SDM_TBU_STASH_CTRL_REG1_SDM & IOCTL_SYSMGR_SET_SDM_TBU_STASH_CTRL_REG1_SDM
Get and Set DMA_TBU_STASH control reg1 SDM register

## IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB2 & IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB2
Get and Set IO_TBU_STASH control reg2 USB2 register

## IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB3 & IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB3
Get and Set IO_TBU_STASH control reg2 USB3 register

## IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_SDMMC & IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_SDMMC
Get and Set IO_TBU_STASH control reg0 dma0 register

## IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_NAND & IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_NAND
Get and Set IO_TBU_STASH control reg2 NAND register

## IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_ETR & IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_ETR
Get and Set IO_TBU_STASH control reg2 ETR register

## IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN0 & IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN0
Get and Set TSN_TBU_STASH control reg3 TSN0 register

## IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN1 & IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN1
Get and Set TSN_TBU_STASH control reg3 TSN1 register

## IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN2 & IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN2
Get and Set TSN_TBU_STASH control reg3 TSN2 register

## IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA0 & IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA0
Get and Set DMA_TBU_STREAM control reg0 DMA0 register

## IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA1 & IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA1
Get and Set DMA_TBU_STREAM control reg0 DMA1 register

## IOCTL_SYSMGR_GET_SDM_TBU_STREAM_CTRL_REG1_SDM & IOCTL_SYSMGR_SET_SDM_TBU_STREAM_CTRL_REG1_SDM
Get and Set SDM_TBU_STREAM control reg1 SDM register

## IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB2 & IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB2
Get and Set IO_TBU_STREAM control reg2 USB2 register

## IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB3 & IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB3
Get and Set IO_TBU_STREAM control reg2 USB3 register

## IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_SDMMC & IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_SDMMC
Get and Set IO_TBU_STREAM control reg2 SDMMC register

## IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_NAND & IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_NAND
Get and Set IO_TBU_STREAM control reg2 NAND register

## IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_ETR & IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_ETR
Get and Set IO_TBU_STREAM control reg2 ETR register

## IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN0 & IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN0
Get and Set TSN_TBU_STREAM control reg3 TSN0 register

## IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN1 & IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN1
Get and Set TSN_TBU_STREAM control reg3 TSN1 register

## IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN2 & IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN2
Get and Set TSN_TBU_STREAM control reg3 TSN2 register

## IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG0 & IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG0
Get and Set USB3_MISC control reg0 register

## IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG1 & IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG1
Get and Set USB3_MISC control reg1 register

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD0 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD0
Get and Set Boot scratch register 0

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD1 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD1
Get and Set Boot scratch register 1

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD2 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD2
Get and Set Boot scratch register 2

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD3 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD3
Get and Set Boot scratch register 3

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD4 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD4
Get and Set Boot scratch register 4

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD5 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD5
Get and Set Boot scratch register 5

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD6 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD6
Get and Set Boot scratch register 6

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD7 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD7
Get and Set Boot scratch register 7

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD8 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD8
Get and Set Boot scratch register 8

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD9 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD9
Get and Set Boot scratch register 9

## IOCTL_SYSMGR_GET_MPFE_CONFIG & IOCTL_SYSMGR_SET_MPFE_CONFIG
Get and Set MPFE Interface Select

## IOCTL_SYSMGR_GET_MPFE_STATUS
Get MPFE Interface status

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM0 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM0
Get and Set Boot scratch register 0

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM1 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM1
Get and Set Boot scratch register 1

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM2 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM2
Get and Set Boot scratch register 2

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM3 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM3
Get and Set Boot scratch register 3

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM4 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM4
Get and Set Boot scratch register 4

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM5 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM5
Get and Set Boot scratch register 5

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM6 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM6
Get and Set Boot scratch register 6

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM7 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM7
Get and Set Boot scratch register 7

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM8 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM8
Get and Set Boot scratch register 8

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM9 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM9
Get and Set Boot scratch register 9

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR0 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR0
Get and Set Boot scratch register 0

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR1 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR1
Get and Set Boot scratch register 1

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR2 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR2
Get and Set Boot scratch register 2

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR3 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR3
Get and Set Boot scratch register 3

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR4 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR4
Get and Set Boot scratch register 4

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR5 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR5
Get and Set Boot scratch register 5

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR6 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR6
Get and Set Boot scratch register 6

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR7 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR7
Get and Set Boot scratch register 7

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR8 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR8
Get and Set Boot scratch register 8

## IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR9 & IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR9
Get and Set Boot scratch register 9

## IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP & IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP
Get and Set based address for SDM to access to OCRAM

## IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP & IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP
Get and Set based address for SDM to access to OCRAM

For a detailed register map, please refer to: 
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/index.html#addressblock_sysmgr_summary.html