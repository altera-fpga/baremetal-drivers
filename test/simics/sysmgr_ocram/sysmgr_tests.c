#include <stdint.h>
#include <stdio.h>
#include <string.h>

// system manager includes
#include "sysmgr.h"
#include "sysmgr_internal.h"
#include "sysmgr_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <fsbl_boot_help.h>

// system manager IOCTL calls
const uint32_t sysmgr_ioctl_defines[] = {IOCTL_SYSMGR_GET_SILICON_ID1,
                                         IOCTL_SYSMGR_GET_SILICON_ID2,
                                         IOCTL_SYSMGR_GET_WDDBG,
                                         IOCTL_SYSMGR_SET_WDDBG,
                                         IOCTL_SYSMGR_GET_MPU_STATUS,
                                         IOCTL_SYSMGR_GET_SDMMC_L3_MASTER,
                                         IOCTL_SYSMGR_SET_SDMMC_L3_MASTER,
                                         IOCTL_SYSMGR_GET_NAND_L3_MASTER,
                                         IOCTL_SYSMGR_SET_NAND_L3_MASTER,
                                         IOCTL_SYSMGR_GET_USB0_L3_MASTER,
                                         IOCTL_SYSMGR_SET_USB0_L3_MASTER,
                                         IOCTL_SYSMGR_GET_USB1_L3_MASTER,
                                         IOCTL_SYSMGR_SET_USB1_L3_MASTER,
                                         IOCTL_SYSMGR_GET_TSN_GLOBAL,
                                         IOCTL_SYSMGR_SET_TSN_GLOBAL,
                                         IOCTL_SYSMGR_GET_TSN0,
                                         IOCTL_SYSMGR_SET_TSN0,
                                         IOCTL_SYSMGR_GET_TSN1,
                                         IOCTL_SYSMGR_SET_TSN1,
                                         IOCTL_SYSMGR_GET_TSN2,
                                         IOCTL_SYSMGR_SET_TSN2,
                                         IOCTL_SYSMGR_GET_TSN0_ACE,
                                         IOCTL_SYSMGR_SET_TSN0_ACE,
                                         IOCTL_SYSMGR_GET_TSN1_ACE,
                                         IOCTL_SYSMGR_SET_TSN1_ACE,
                                         IOCTL_SYSMGR_GET_TSN2_ACE,
                                         IOCTL_SYSMGR_SET_TSN2_ACE,
                                         IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL,
                                         IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL,
                                         IOCTL_SYSMGR_GET_FPGA_INTF_EN1,
                                         IOCTL_SYSMGR_SET_FPGA_INTF_EN1,
                                         IOCTL_SYSMGR_GET_FPGA_INTF_EN2,
                                         IOCTL_SYSMGR_SET_FPGA_INTF_EN2,
                                         IOCTL_SYSMGR_GET_FPGA_INTF_EN3,
                                         IOCTL_SYSMGR_SET_FPGA_INTF_EN3,
                                         IOCTL_SYSMGR_GET_DMAC0_L3_MASTER,
                                         IOCTL_SYSMGR_SET_DMAC0_L3_MASTER,
                                         IOCTL_SYSMGR_GET_ETR_L3_MASTER,
                                         IOCTL_SYSMGR_SET_ETR_L3_MASTER,
                                         IOCTL_SYSMGR_GET_DMAC1_L3_MASTER,
                                         IOCTL_SYSMGR_SET_DMAC1_L3_MASTER,
                                         IOCTL_SYSMGR_GET_SEC_CTRL_SELECT,
                                         IOCTL_SYSMGR_SET_SEC_CTRL_SELECT,
                                         IOCTL_SYSMGR_GET_OSC_TRIM,
                                         IOCTL_SYSMGR_GET_DMAC0_CTRL_STATUS_REG,
                                         IOCTL_SYSMGR_SET_DMAC0_CTRL_STATUS_REG,
                                         IOCTL_SYSMGR_GET_DMAC1_CTRL_STATUS_REG,
                                         IOCTL_SYSMGR_SET_DMAC1_CTRL_STATUS_REG,
                                         IOCTL_SYSMGR_GET_ECC_INTMASK_VALUE,
                                         IOCTL_SYSMGR_SET_ECC_INTMASK_VALUE,
                                         IOCTL_SYSMGR_ECC_INTMASK_SETBITS,
                                         IOCTL_SYSMGR_ECC_INTMASK_CLRBITS,
                                         IOCTL_SYSMGR_GET_ECC_INTSTATUS_SERR,
                                         IOCTL_SYSMGR_GET_ECC_INTSTATUS_DERR,
                                         IOCTL_SYSMGR_GET_NOC_TIMEOUT,
                                         IOCTL_SYSMGR_SET_NOC_TIMEOUT,
                                         IOCTL_SYSMGR_GET_NOC_IDLESTATUS,
                                         IOCTL_SYSMGR_GET_FPGA2SOC_CTRL,
                                         IOCTL_SYSMGR_SET_FPGA2SOC_CTRL,
                                         IOCTL_SYSMGR_GET_FPGA_CONFIG,
                                         IOCTL_SYSMGR_SET_GPO,
                                         IOCTL_SYSMGR_GET_GPI,
                                         IOCTL_SYSMGR_GET_MPU,
                                         IOCTL_SYSMGR_SET_MPU,
                                         IOCTL_SYSMGR_SET_SDM_HPS_SPARE,
                                         IOCTL_SYSMGR_GET_HPS_SDM_SPARE,
                                         IOCTL_SYSMGR_SET_HPS_SDM_SPARE,
                                         IOCTL_SYSMGR_GET_DFI_INTERFACE_CFG,
                                         IOCTL_SYSMGR_SET_DFI_INTERFACE_CFG,
                                         IOCTL_SYSMGR_GET_NAND_DD_CTRL,
                                         IOCTL_SYSMGR_SET_NAND_DD_CTRL,
                                         IOCTL_SYSMGR_GET_NAND_PHY_CTRL_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_CTRL_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_TSEL_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_TSEL_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_DQ_TIMING_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_DQ_TIMING_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_DQS_TIMING_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_DQS_TIMING_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_GATE_LPBK_CTRL_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_GATE_LPBK_CTRL_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_DLL_MASTER_CTRL_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_DLL_MASTER_CTRL_REG,
                                         IOCTL_SYSMGR_GET_NAND_PHY_DLL_SLAVE_CTRL_REG,
                                         IOCTL_SYSMGR_SET_NAND_PHY_DLL_SLAVE_CTRL_REG,
                                         IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG0,
                                         IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG0,
                                         IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG1,
                                         IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG1,
                                         IOCTL_SYSMGR_GET_NAND_DD_STATUS_REG,
                                         IOCTL_SYSMGR_GET_NAND_DD_ID_LOW_REG,
                                         IOCTL_SYSMGR_GET_NAND_DD_ID_HIGH_REG,
                                         IOCTL_SYSMGR_GET_NAND_WRITE_PROT_EN_REG,
                                         IOCTL_SYSMGR_SET_NAND_WRITE_PROT_EN_REG,
                                         IOCTL_SYSMGR_GET_SDMMC_CMD_QUEUE_SETTING_REG,
                                         IOCTL_SYSMGR_SET_SDMMC_CMD_QUEUE_SETTING_REG,
                                         IOCTL_SYSMGR_GET_I3C_SLV_PID_LOW,
                                         IOCTL_SYSMGR_SET_I3C_SLV_PID_LOW,
                                         IOCTL_SYSMGR_GET_I3C_SLV_PID_HIGH,
                                         IOCTL_SYSMGR_SET_I3C_SLV_PID_HIGH,
                                         IOCTL_SYSMGR_GET_I3C_SLV_CTRL0,
                                         IOCTL_SYSMGR_SET_I3C_SLV_CTRL0,
                                         IOCTL_SYSMGR_GET_I3C_SLV_CTRL1,
                                         IOCTL_SYSMGR_SET_I3C_SLV_CTRL1,
                                         IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL,
                                         IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA0,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA0,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA1,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA1,
                                         IOCTL_SYSMGR_GET_SDM_TBU_STASH_CTRL_REG1_SDM,
                                         IOCTL_SYSMGR_SET_SDM_TBU_STASH_CTRL_REG1_SDM,
                                         IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB2,
                                         IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB2,
                                         IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB3,
                                         IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB3,
                                         IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_SDMMC,
                                         IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_SDMMC,
                                         IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_NAND,
                                         IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_NAND,
                                         IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_ETR,
                                         IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_ETR,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN0,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN0,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN1,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN1,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN2,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN2,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA0,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA0,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA1,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA1,
                                         IOCTL_SYSMGR_GET_SDM_TBU_STREAM_CTRL_REG1_SDM,
                                         IOCTL_SYSMGR_SET_SDM_TBU_STREAM_CTRL_REG1_SDM,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB2,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB2,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB3,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB3,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_SDMMC,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_SDMMC,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_NAND,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_NAND,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_ETR,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_ETR,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN0,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN0,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN1,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN1,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN2,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN2,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA0,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA0,
                                         IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA1,
                                         IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA1,
                                         IOCTL_SYSMGR_GET_SDM_TBU_STREAM_ID_AX_REG1_SDM,
                                         IOCTL_SYSMGR_SET_SDM_TBU_STREAM_ID_AX_REG1_SDM,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB2,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB2,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB3,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB3,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_SDMMC,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_SDMMC,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_NAND,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_NAND,
                                         IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_ETR,
                                         IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_ETR,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN0,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN0,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN1,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN1,
                                         IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN2,
                                         IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN2,
                                         IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG0,
                                         IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG0,
                                         IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG1,
                                         IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG1,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD0,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD0,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD1,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD1,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD2,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD2,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD3,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD3,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD4,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD4,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD5,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD5,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD6,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD6,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD7,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD7,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD8,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD8,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD9,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD9,
                                         IOCTL_SYSMGR_GET_MPFE_CONFIG,
                                         IOCTL_SYSMGR_SET_MPFE_CONFIG,
                                         IOCTL_SYSMGR_GET_MPFE_STATUS,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM0,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM0,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM1,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM1,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM2,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM2,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM3,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM3,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM4,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM4,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM5,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM5,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM6,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM6,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM7,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM7,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM8,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM8,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM9,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM9,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR0,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR0,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR1,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR1,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR2,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR2,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR3,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR3,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR4,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR4,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR5,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR5,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR6,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR6,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR7,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR7,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR8,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR8,
                                         IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR9,
                                         IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR9,
                                         IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP,
                                         IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP,
                                         IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP,
                                         IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP};

// The array below denotes the values that will be verified
// All items with "1" will be validated
// All items with "0" will simply be printed
const bool sysmgr_ioctl_toverify[] = {1,  // IOCTL_SYSMGR_GET_SILICON_ID1,,
                                      1,  // IOCTL_SYSMGR_GET_SILICON_ID2,
                                      1,  // IOCTL_SYSMGR_GET_WDDBG,
                                      1,  // IOCTL_SYSMGR_SET_WDDBG,
                                      1,  // IOCTL_SYSMGR_GET_MPU_STATUS,
                                      1,  // IOCTL_SYSMGR_GET_SDMMC_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_SDMMC_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_NAND_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_NAND_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_USB0_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_USB0_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_USB1_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_USB1_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_TSN_GLOBAL,
                                      1,  // IOCTL_SYSMGR_SET_TSN_GLOBAL,
                                      1,  // IOCTL_SYSMGR_GET_TSN0,
                                      1,  // IOCTL_SYSMGR_SET_TSN0,
                                      1,  // IOCTL_SYSMGR_GET_TSN1,
                                      1,  // IOCTL_SYSMGR_SET_TSN1,
                                      1,  // IOCTL_SYSMGR_GET_TSN2,
                                      1,  // IOCTL_SYSMGR_SET_TSN2,
                                      1,  // IOCTL_SYSMGR_GET_TSN0_ACE,
                                      1,  // IOCTL_SYSMGR_SET_TSN0_ACE,
                                      1,  // IOCTL_SYSMGR_GET_TSN1_ACE,
                                      1,  // IOCTL_SYSMGR_SET_TSN1_ACE,
                                      1,  // IOCTL_SYSMGR_GET_TSN2_ACE,
                                      1,  // IOCTL_SYSMGR_SET_TSN2_ACE,
                                      1,  // IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL,
                                      1,  // IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL,
                                      1,  // IOCTL_SYSMGR_GET_FPGA_INTF_EN1,
                                      1,  // IOCTL_SYSMGR_SET_FPGA_INTF_EN1,
                                      1,  // IOCTL_SYSMGR_GET_FPGA_INTF_EN2,
                                      1,  // IOCTL_SYSMGR_SET_FPGA_INTF_EN2,
                                      1,  // IOCTL_SYSMGR_GET_FPGA_INTF_EN3,
                                      1,  // IOCTL_SYSMGR_SET_FPGA_INTF_EN3,
                                      1,  // IOCTL_SYSMGR_GET_DMAC0_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_DMAC0_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_ETR_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_ETR_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_DMAC1_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_SET_DMAC1_L3_MASTER,
                                      1,  // IOCTL_SYSMGR_GET_SEC_CTRL_SELECT,
                                      1,  // IOCTL_SYSMGR_SET_SEC_CTRL_SELECT,
                                      0,  // IOCTL_SYSMGR_GET_OSC_TRIM,
                                      1,  // IOCTL_SYSMGR_GET_DMAC0_CTRL_STATUS_REG,
                                      1,  // IOCTL_SYSMGR_SET_DMAC0_CTRL_STATUS_REG,
                                      1,  // IOCTL_SYSMGR_GET_DMAC1_CTRL_STATUS_REG,
                                      1,  // IOCTL_SYSMGR_SET_DMAC1_CTRL_STATUS_REG,
                                      1,  // IOCTL_SYSMGR_GET_ECC_INTMASK_VALUE,
                                      1,  // IOCTL_SYSMGR_SET_ECC_INTMASK_VALUE,
                                      1,  // IOCTL_SYSMGR_ECC_INTMASK_SETBITS,
                                      1,  // IOCTL_SYSMGR_ECC_INTMASK_CLRBITS,
                                      1,  // IOCTL_SYSMGR_GET_ECC_INTSTATUS_SERR,
                                      1,  // IOCTL_SYSMGR_GET_ECC_INTSTATUS_DERR,
                                      1,  // IOCTL_SYSMGR_GET_NOC_TIMEOUT,
                                      1,  // IOCTL_SYSMGR_SET_NOC_TIMEOUT,
                                      1,  // IOCTL_SYSMGR_GET_NOC_IDLESTATUS,
                                      1,  // IOCTL_SYSMGR_GET_FPGA2SOC_CTRL,
                                      1,  // IOCTL_SYSMGR_SET_FPGA2SOC_CTRL,
                                      1,  // IOCTL_SYSMGR_GET_FPGA_CONFIG,
                                      1,  // IOCTL_SYSMGR_SET_GPO,
                                      1,  // IOCTL_SYSMGR_GET_GPI,
                                      1,  // IOCTL_SYSMGR_GET_MPU,
                                      1,  // IOCTL_SYSMGR_SET_MPU,
                                      1,  // IOCTL_SYSMGR_SET_SDM_HPS_SPARE,
                                      1,  // IOCTL_SYSMGR_GET_HPS_SDM_SPARE,
                                      1,  // IOCTL_SYSMGR_SET_HPS_SDM_SPARE,
                                      1,  // IOCTL_SYSMGR_GET_DFI_INTERFACE_CFG,
                                      1,  // IOCTL_SYSMGR_SET_DFI_INTERFACE_CFG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_CTRL,
                                      1,  // IOCTL_SYSMGR_SET_NAND_DD_CTRL,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_TSEL_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_TSEL_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_DQ_TIMING_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_DQ_TIMING_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_DQS_TIMING_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_DQS_TIMING_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_GATE_LPBK_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_GATE_LPBK_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_DLL_MASTER_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_DLL_MASTER_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_PHY_DLL_SLAVE_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_PHY_DLL_SLAVE_CTRL_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG0,
                                      1,  // IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG0,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG1,
                                      1,  // IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG1,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_STATUS_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_ID_LOW_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_DD_ID_HIGH_REG,
                                      1,  // IOCTL_SYSMGR_GET_NAND_WRITE_PROT_EN_REG,
                                      1,  // IOCTL_SYSMGR_SET_NAND_WRITE_PROT_EN_REG,
                                      1,  // IOCTL_SYSMGR_GET_SDMMC_CMD_QUEUE_SETTING_REG,
                                      1,  // IOCTL_SYSMGR_SET_SDMMC_CMD_QUEUE_SETTING_REG,
                                      1,  // IOCTL_SYSMGR_GET_I3C_SLV_PID_LOW,
                                      1,  // IOCTL_SYSMGR_SET_I3C_SLV_PID_LOW,
                                      1,  // IOCTL_SYSMGR_GET_I3C_SLV_PID_HIGH,
                                      1,  // IOCTL_SYSMGR_SET_I3C_SLV_PID_HIGH,
                                      1,  // IOCTL_SYSMGR_GET_I3C_SLV_CTRL0,
                                      1,  // IOCTL_SYSMGR_SET_I3C_SLV_CTRL0,
                                      1,  // IOCTL_SYSMGR_GET_I3C_SLV_CTRL1,
                                      1,  // IOCTL_SYSMGR_SET_I3C_SLV_CTRL1,
                                      1,  // IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL,
                                      1,  // IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_GET_SDM_TBU_STASH_CTRL_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_SET_SDM_TBU_STASH_CTRL_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_GET_SDM_TBU_STREAM_CTRL_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_SET_SDM_TBU_STREAM_CTRL_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA0,
                                      1,  // IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA1,
                                      1,  // IOCTL_SYSMGR_GET_SDM_TBU_STREAM_ID_AX_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_SET_SDM_TBU_STREAM_ID_AX_REG1_SDM,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB2,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB3,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_SDMMC,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_NAND,
                                      1,  // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_ETR,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN0,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN1,
                                      1,  // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN2,
                                      1,  // IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG0,
                                      1,  // IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG0,
                                      1,  // IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG1,
                                      1,  // IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG1,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD0,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD0,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD1,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD1,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD2,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD2,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD3,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD3,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD4,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD4,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD5,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD5,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD6,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD6,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD7,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD7,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD8,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD8,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD9,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD9,
                                      1,  // IOCTL_SYSMGR_GET_MPFE_CONFIG,
                                      1,  // IOCTL_SYSMGR_SET_MPFE_CONFIG,
                                      1,  // IOCTL_SYSMGR_GET_MPFE_STATUS,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM0,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM0,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM1,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM1,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM2,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM2,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM3,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM3,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM4,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM4,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM5,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM5,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM6,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM6,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM7,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM7,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM8,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM8,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM9,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM9,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR0,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR0,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR1,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR1,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR2,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR2,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR3,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR3,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR4,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR4,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR5,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR5,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR6,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR6,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR7,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR7,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR8,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR8,
                                      1,  // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR9,
                                      1,  // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR9,
                                      1,  // IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP,
                                      1,  // IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP,
                                      1,  // IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP,
                                      1}; // IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP

#define NUM_OF_IOCTLS sizeof(sysmgr_ioctl_defines) / sizeof(sysmgr_ioctl_defines[0])
// clang-format off
// system manager IOCTL call test expectations. 
// All Set operations are noted to have an expected value of "0" to represent "NULL" as there isn't any expected returned value from "_SET_" operations
const uint32_t sysmgr_ioctl_test_exp[] = {
    0x00030000, 	// IOCTL_SYSMGR_GET_SILICON_ID1
    0x00000000, 	// IOCTL_SYSMGR_GET_SILICON_ID2
    0x88080808,	    // IOCTL_SYSMGR_GET_WDDBG
    0,          	// IOCTL_SYSMGR_SET_WDDBG
    0x00000000, 	// IOCTL_SYSMGR_GET_MPU_STATUS
    0x0000F000, 	// IOCTL_SYSMGR_GET_SDMMC_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_SDMMC_L3_MASTER
    0x0C000C00, 	// IOCTL_SYSMGR_GET_NAND_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_NAND_L3_MASTER
    0x00003001,  	// IOCTL_SYSMGR_GET_USB0_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_USB0_L3_MASTER
    0x0000F000,	    // IOCTL_SYSMGR_GET_USB1_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_USB1_L3_MASTER
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_GLOBAL
    0,          	// IOCTL_SYSMGR_SET_TSN_GLOBAL
    0x00000003, 	// IOCTL_SYSMGR_GET_TSN0
    0,          	// IOCTL_SYSMGR_SET_TSN0
    0x00000003, 	// IOCTL_SYSMGR_GET_TSN1
    0,          	// IOCTL_SYSMGR_SET_TSN1
    0x00000003, 	// IOCTL_SYSMGR_GET_TSN2
    0,	            // IOCTL_SYSMGR_SET_TSN2
    0x00000000,  	// IOCTL_SYSMGR_GET_TSN0_ACE
    0,          	// IOCTL_SYSMGR_SET_TSN0_ACE
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN1_ACE
    0,          	// IOCTL_SYSMGR_SET_TSN1_ACE
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN2_ACE
    0,          	// IOCTL_SYSMGR_SET_TSN2_ACE
    0x00000000, 	// IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL
    0,          	// IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL
    0x01010110,	    // IOCTL_SYSMGR_GET_FPGA_INTF_EN1
    0,          	// IOCTL_SYSMGR_SET_FPGA_INTF_EN1
    0x00000000, 	// IOCTL_SYSMGR_GET_FPGA_INTF_EN2
    0,          	// IOCTL_SYSMGR_SET_FPGA_INTF_EN2
    0x00000000, 	// IOCTL_SYSMGR_GET_FPGA_INTF_EN3
    0,          	// IOCTL_SYSMGR_SET_FPGA_INTF_EN3
    0x0000F000, 	// IOCTL_SYSMGR_GET_DMAC0_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_DMAC0_L3_MASTER
    0x0000F000, 	// IOCTL_SYSMGR_GET_ETR_L3_MASTER
    0,	            // IOCTL_SYSMGR_SET_ETR_L3_MASTER
    0x0000F000, 	// IOCTL_SYSMGR_GET_DMAC1_L3_MASTER
    0,          	// IOCTL_SYSMGR_SET_DMAC1_L3_MASTER
    0x00000001, 	// IOCTL_SYSMGR_GET_SEC_CTRL_SELECT
    0,          	// IOCTL_SYSMGR_SET_SEC_CTRL_SELECT
    0x000000a5, 	// IOCTL_SYSMGR_GET_OSC_TRIM
    0x00000000, 	// IOCTL_SYSMGR_GET_DMAC0_CTRL_STATUS_REG
    0,          	// IOCTL_SYSMGR_SET_DMAC0_CTRL_STATUS_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_DMAC1_CTRL_STATUS_REG
    0,	            // IOCTL_SYSMGR_SET_DMAC1_CTRL_STATUS_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_ECC_INTMASK_VALUE
    0,          	// IOCTL_SYSMGR_SET_ECC_INTMASK_VALUE
    0,          	// IOCTL_SYSMGR_ECC_INTMASK_SETBITS
    0,          	// IOCTL_SYSMGR_ECC_INTMASK_CLRBITS
    0x00000000, 	// IOCTL_SYSMGR_GET_ECC_INTSTATUS_SERR
    0x00000000, 	// IOCTL_SYSMGR_GET_ECC_INTSTATUS_DERR
    0x00000000, 	// IOCTL_SYSMGR_GET_NOC_TIMEOUT
    0,          	// IOCTL_SYSMGR_SET_NOC_TIMEOUT
    0x00000011,	    // IOCTL_SYSMGR_GET_NOC_IDLESTATUS
    0x00000001, 	// IOCTL_SYSMGR_GET_FPGA2SOC_CTRL
    0,          	// IOCTL_SYSMGR_SET_FPGA2SOC_CTRL
    0x00000002, 	// IOCTL_SYSMGR_GET_FPGA_CONFIG "Because this test is being executed at EL3 FPGA configuration is at 0x2 or early usermode"
    0,          	// IOCTL_SYSMGR_SET_GPO
    0, 	            // IOCTL_SYSMGR_GET_GPI
    0x00000000, 	// IOCTL_SYSMGR_GET_MPU
    0,          	// IOCTL_SYSMGR_SET_MPU
    0,          	// IOCTL_SYSMGR_SET_SDM_HPS_SPARE
    0x00000000,	    // IOCTL_SYSMGR_GET_HPS_SDM_SPARE
    0,          	// IOCTL_SYSMGR_SET_HPS_SDM_SPARE
    0x00000000, 	// IOCTL_SYSMGR_GET_DFI_INTERFACE_CFG
    0,          	// IOCTL_SYSMGR_SET_DFI_INTERFACE_CFG
    0x00c80010, 	// IOCTL_SYSMGR_GET_NAND_DD_CTRL  Default for EL3 first boot"
    0,          	// IOCTL_SYSMGR_SET_NAND_DD_CTRL
    0x00004310,	    // IOCTL_SYSMGR_GET_NAND_PHY_CTRL_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_CTRL_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_PHY_TSEL_REG
    0,	            // IOCTL_SYSMGR_SET_NAND_PHY_TSEL_REG
    0x00000002, 	// IOCTL_SYSMGR_GET_NAND_PHY_DQ_TIMING_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_DQ_TIMING_REG
    0x00100004, 	// IOCTL_SYSMGR_GET_NAND_PHY_DQS_TIMING_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_DQS_TIMING_REG
    0x01A00000, 	// IOCTL_SYSMGR_GET_NAND_PHY_GATE_LPBK_CTRL_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_GATE_LPBK_CTRL_REG
    0x00800000, 	// IOCTL_SYSMGR_GET_NAND_PHY_DLL_MASTER_CTRL_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_DLL_MASTER_CTRL_REG
    0x00000000,	    // IOCTL_SYSMGR_GET_NAND_PHY_DLL_SLAVE_CTRL_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_PHY_DLL_SLAVE_CTRL_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG0
    0,          	// IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG0
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG1
    0,          	// IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG1
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_DD_STATUS_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_DD_ID_LOW_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_NAND_DD_ID_HIGH_REG
    0x00000000,	    // IOCTL_SYSMGR_GET_NAND_WRITE_PROT_EN_REG
    0,          	// IOCTL_SYSMGR_SET_NAND_WRITE_PROT_EN_REG
    0x00000640, 	// IOCTL_SYSMGR_GET_SDMMC_CMD_QUEUE_SETTING_REG
    0,          	// IOCTL_SYSMGR_SET_SDMMC_CMD_QUEUE_SETTING_REG
    0x00000000, 	// IOCTL_SYSMGR_GET_I3C_SLV_PID_LOW
    0,          	// IOCTL_SYSMGR_SET_I3C_SLV_PID_LOW
    0x00000000, 	// IOCTL_SYSMGR_GET_I3C_SLV_PID_HIGH
    0,          	// IOCTL_SYSMGR_SET_I3C_SLV_PID_HIGH
    0x40000000, 	// IOCTL_SYSMGR_GET_I3C_SLV_CTRL0
    0,	            // IOCTL_SYSMGR_SET_I3C_SLV_CTRL0
    0x00000000, 	// IOCTL_SYSMGR_GET_I3C_SLV_CTRL1
    0,          	// IOCTL_SYSMGR_SET_I3C_SLV_CTRL1
    0x00000002, 	// IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL
    0,          	// IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL
    0x00000000, 	// IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA0
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA0
    0x00000000, 	// IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA1
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA1
    0x00000000,	    // IOCTL_SYSMGR_GET_SDM_TBU_STASH_CTRL_REG1_SDM
    0,          	// IOCTL_SYSMGR_SET_SDM_TBU_STASH_CTRL_REG1_SDM
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB2
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB2
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB3
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB3
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_SDMMC
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_SDMMC
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_NAND
    0,	            // IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_NAND
    0x00000000,	    // IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_ETR
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_ETR
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN0
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN0
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN1
    0,         	    // IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN1
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN2
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN2
    0x00000030,	    // IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA0
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA0
    0x00000030, 	// IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA1
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA1
    0x00000033, 	// IOCTL_SYSMGR_GET_SDM_TBU_STREAM_CTRL_REG1_SDM
    0,         	    // IOCTL_SYSMGR_SET_SDM_TBU_STREAM_CTRL_REG1_SDM
    0x00000030, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB2
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB2
    0x00000030, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB3
    0,	            // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB3
    0x00000030, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_SDMMC
    0,         	    // IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_SDMMC
    0x00000030, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_NAND
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_NAND
    0x00000030, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_ETR
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_ETR
    0x00000030, 	// IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN0
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN0
    0x00000030,	    // IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN1
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN1
    0x00000030, 	// IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN2
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN2
    0x00000000, 	// IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA0
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA0
    0x00000000, 	// IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA1
    0,          	// IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA1
    0x00000000, 	// IOCTL_SYSMGR_GET_SDM_TBU_STREAM_ID_AX_REG1_SDM
    0,	            // IOCTL_SYSMGR_SET_SDM_TBU_STREAM_ID_AX_REG1_SDM
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB2
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB2
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB3
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB3
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_SDMMC
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_SDMMC
    0x00000000, 	// IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_NAND
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_NAND
    0x00000000,	    // IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_ETR
    0,          	// IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_ETR
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN0
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN0
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN1
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN1
    0x00000000, 	// IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN2
    0,          	// IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN2
    0x07c00c11, 	// IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG0
    0,	            // IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG0
    0x00000000, 	// IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG1
    0,          	// IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG1
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD0
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD0
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD1
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD1
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD2
    0,         	    // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD2
    0x00000000,	    // IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD3
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD3
    0x4364c0dd, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD4 this value seems to be used in boot
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD4
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD5
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD5
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD6
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD6
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD7
    0,	            // IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD7
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD8
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD8
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD9
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD9
    0x0000003b, 	// IOCTL_SYSMGR_GET_MPFE_CONFIG
    0,          	// IOCTL_SYSMGR_SET_MPFE_CONFIG
    0x00000000, 	// IOCTL_SYSMGR_GET_MPFE_STATUS
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM0
    0,	            // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM0
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM1
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM1
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM2
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM2
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM3
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM3
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM4
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM4
    0x00000000,	    // IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM5
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM5
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM6
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM6
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM7
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM7
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM8
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM8
    0x00000100, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM9 "This value isn't 0 as expected by default. It seems this scratch value is used."
    0,	            // IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM9
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR0
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR0
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR1
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR1
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR2
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR2
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR3
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR3
    0x00000000,	    // IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR4
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR4
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR5
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR5
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR6
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR6
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR7
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR7
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR8
    0,	            // IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR8
    0x00000000, 	// IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR9
    0,          	// IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR9
    0x00000000, 	// IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP
    0,          	// IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP
    0x00000000, 	// IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP
    0};	            // IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP
// clang-format on
int main(void) {
    int32_t return_value = -1;
    uint32_t sysmgr_param = 0;
    sysmgr_regs_t sysmgr_all_param = {0};

    // These tests can only be executed in secure mode lets verify
    fsbl_configuration();

    int32_t sysmgr_handle = 0;
    // Test opening invalid from an invalid source
    sysmgr_handle = sysmgr_open("/dev/invalid", 0);

    // Verify reception of invalid handle
    if (sysmgr_handle == -1) {
        printf("Invalid handle received as expected\n");
    }

    // Verify invalid close
    if (sysmgr_close(sysmgr_handle) == -1) {
        printf("Invalid close operation as expected\n");
    }

    // Open valid sysmgr device
    sysmgr_handle = sysmgr_open("/dev/sysmgr", 0);

    if (sysmgr_handle == HPS_SYSMGR_BASE) {

        printf("Valid sysmgr handle open\n");

        // The remap registers require that the remappers are present
        printf("remap register verification test start\n");
        sysmgr_param = 0;
        sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP, (uintptr_t)(&sysmgr_param),
                     sizeof(sysmgr_regs_t));
        printf("remap address AWADDR 0x%x\n", sysmgr_param);

        sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP, (uintptr_t)(&sysmgr_param),
                     sizeof(sysmgr_regs_t));

        sysmgr_param = 0;
        sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP, (uintptr_t)(&sysmgr_param),
                     sizeof(sysmgr_regs_t));

        sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP, (uintptr_t)(&sysmgr_param),
                     sizeof(sysmgr_regs_t));
        printf("remap register verification test end\n");

        // Execute all but the last 4 REMAP IOCTL's
        for (uint32_t ii = 0; ii < (uint32_t)(NUM_OF_IOCTLS - 4); ii++) {
            sysmgr_param = 0;
            sysmgr_ioctl(sysmgr_handle, sysmgr_ioctl_defines[ii], (uintptr_t)(&sysmgr_param), sizeof(sysmgr_regs_t));
            if (sysmgr_param != sysmgr_ioctl_test_exp[ii]) {

                // If this IOCTL isn't to be verified simply print the value and the ioctl value
                if (sysmgr_ioctl_toverify[ii] == false) {
                    printf("IOCTL COMMAND = 0x%x actual resp = 0x%x\n", sysmgr_ioctl_defines[ii], sysmgr_param);
                } else {
                    printf("UnExpected response for IOCTL COMMAND = 0x%x actual resp = 0x%x  expected resp = 0x%x\n",
                           sysmgr_ioctl_defines[ii], sysmgr_param, sysmgr_ioctl_test_exp[ii]);
                    return -2;
                }
            } else {
                printf("IOCTL COMMAND = 0x%x success iteration %d\n", sysmgr_ioctl_defines[ii], ii);
            }
        }

        // read all registers
        if (sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_REGS_READ, (uintptr_t)(&sysmgr_all_param),
                         sizeof(sysmgr_regs_t)) == 0) {
            printf("Successfully read all registers\n");
        }

        // write all registers
        if (sysmgr_ioctl(sysmgr_handle, IOCTL_SYSMGR_REGS_WRITE, (uintptr_t)(&sysmgr_all_param),
                         sizeof(sysmgr_regs_t)) == 0) {
            printf("Successfully wrote all registers\n");
        }

        return_value = 0;
        printf("SYSMGR test completed successfully\n");
    } else {

        printf("Invalid open handle\n");
        return_value = -1;
    }
    sysmgr_close(sysmgr_handle);
    return return_value;
}

#ifdef __cplusplus
}
#endif
