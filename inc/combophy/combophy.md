# COMBOPHY Driver

This describes the registers and their operational details for integration of the ComboPHY IP into a target design.
All the control over the registers are via IOCTL functions.

## COMBOPHY_READ_REGS & COMBOPHY_WRITE_REGS
Reads and Writes the whole register bank

## COMBOPHY_GET_DQ_TIMING & COMBOPHY_SET_DQ_TIMING
Get and Set the DQ related timing.
Size: 32
Offset: 0
Access: RW

## COMBOPHY_GET_DQS_TIMING & COMBOPHY_SET_DQS_TIMING
Get and Set the DQS related timing.
Size: 32
Offset: 0x4
Access: RW

## COMBOPHY_GET_GATE_LPBK_CTRL & COMBOPHY_SET_GATE_LPBK_CTRL
Get and Set the gate and loopback control related timing.
Size: 32
Offset: 0x8
Access: RW

## COMBOPHY_GET_DLL_MASTER_CTRL & COMBOPHY_SET_DLL_MASTER_CTRL
Get and Set the control for the Master DLL logic.
Size: 32
Offset: 0xC
Access: RW

## COMBOPHY_GET_DLL_SLAVE_CTRL & COMBOPHY_SET_DLL_SLAVE_CTRL
Get and Set the control for the slave DLL logic.
Size: 32
Offset: 0x10
Access: RW

## COMBOPHY_GET_IE_TIMING & COMBOPHY_SET_IE_TIMING
Get and Set the DQS related timing.
Size: 32
Offset: 0x14
Access: RW

## COMBOPHY_GET_OBS_REG_0
Get the loopback status, loopback DQ data, DQS underrun, DQS overflow, DQS CMD underrun & DQS CMD overflow.
Size: 32
Offset: 0x18
Access: RO

## COMBOPHY_GET_DLL_OBS_REG0
Get the DLL lock status, DLL locked mode, DLL unlock count, DLL lock value, DLL lock inc & DLL lock dec.
Size: 32
Offset: 0x1C
Access: RO

## COMBOPHY_GET_DLL_OBS_REG1
Get the encoded value of the read delay line, CMD read delay line, CLK_WR delay line.
Size: 32
Offset: 0x20
Access: RO

## COMBOPHY_GET_DLL_OBS_REG2
Get the encoded value oof the CLK_WRDQS line.
Size: 32
Offset: 0x24
Access: RO

## COMBOPHY_GET_STATIC_TOGG & COMBOPHY_SET_STATIC_TOGG
Get and Set the static aging feature of the PHY.
Size: 32
Offset: 0x28
Access: RW

## COMBOPHY_GET_WR_DESKEW & COMBOPHY_SET_WR_DESKEW
Get and Set the values of delay of each DQ bit on the write path.
Size: 32
Offset: 0x2C
Access: RW

## COMBOPHY_GET_WR_RD_DESKEW_CMD & COMBOPHY_SET_WR_RD_DESKEW_CMD
Get and Set the values of delay of CMD bit on the write and read path as well as the values of phase detect block for CMD bit on the write path.
Size: 32
Offset: 0x30
Access: RW

## COMBOPHY_GET_WR_DESKEW_PD_CTRL0 & COMBOPHY_SET_WR_DESKEW_PD_CTRL0
Get and Set the values of phase detect block for DQ bits [0-3] on the write path.
Size: 32
Offset: 0x34
Access: RW

## COMBOPHY_GET_WR_DESKEW_PD_CTRL1 & COMBOPHY_SET_WR_DESKEW_PD_CTRL1
Get and Set the values of phase detect block for DQ bits [4-7] on the write path.
Size: 32
Offset: 0x38
Access: RW

## COMBOPHY_GET_RD_DESKEW & COMBOPHY_SET_RD_DESKEW
Get and Set the values of delay of each DQ bit on the read path.
Size: 32
Offset: 0x3C
Access: RW

## COMBOPHY_GET_VERSION 
Get the release identification number
Size: 32
Offset: 0x70
Access: RO

## COMBOPHY_GET_FEATURES
Get the available hardware features like support for SD/eMMC, aging, PLL, JTAG muxes, etc.
Size: 32
Offset: 0x74
Access: RO

## COMBOPHY_GET_CTRL & COMBOPHY_SET_CTRL
Get and Set the global control settings for the PHY.
Size: 32
Offset: 0
Access: RW

## COMBOPHY_GET_TSEL & COMBOPHY_SET_TSEL
Get and Set the global control settings for the termination selects for reads. For SD controllers this should be disabled.
Size: 32
Offset: 0x4
Access: RW

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_COMBOPHY_summary.html