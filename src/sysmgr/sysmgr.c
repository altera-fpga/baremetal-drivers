#ifdef __cplusplus
extern "C" {
#endif

#include "sysmgr.h"
#include "device.h"
#include "sysmgr_internal.h"
#include "sysmgr_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t sysmgr_devices[] = {{.name = "/dev/sysmgr", .fd = HPS_SYSMGR_BASE, .acquired = 0}};

int32_t sysmgr_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(sysmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(sysmgr_devices[i].name, name) == 0) {
                if (claim_device(&sysmgr_devices[i])) {
                    fd = sysmgr_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t sysmgr_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(sysmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (sysmgr_devices[i].fd == fd) {
                sysmgr_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}
size_t sysmgr_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t sysmgr_read(int32_t fd, uintptr_t buf, size_t size) { return sysmgr_recv(fd, buf, size, 0); }

size_t sysmgr_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t sysmgr_write(int32_t fd, const uintptr_t buf, size_t size) { return sysmgr_send(fd, buf, size, 0); }

int32_t sysmgr_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((sysmgr_ioctl_op_t)request) {
        case (IOCTL_SYSMGR_REGS_READ):
            return_value = sysmgr_regs_read(fd, arg, length);
            break;
        case (IOCTL_SYSMGR_REGS_WRITE):
            return_value = sysmgr_regs_write(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SILICON_ID1:
            return_value = sysmgr_get_silicon_id1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SILICON_ID2:
            return_value = sysmgr_get_silicon_id2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_WDDBG:
            return_value = sysmgr_get_wddbg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_WDDBG:
            return_value = sysmgr_set_wddbg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_MPU_STATUS:
            return_value = sysmgr_get_mpu_status(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDMMC_L3_MASTER:
            return_value = sysmgr_get_sdmmc_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDMMC_L3_MASTER:
            return_value = sysmgr_set_sdmmc_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_L3_MASTER:
            return_value = sysmgr_get_nand_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_L3_MASTER:
            return_value = sysmgr_set_nand_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_USB0_L3_MASTER:
            return_value = sysmgr_get_usb0_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_USB0_L3_MASTER:
            return_value = sysmgr_set_usb0_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_USB1_L3_MASTER:
            return_value = sysmgr_get_usb1_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_USB1_L3_MASTER:
            return_value = sysmgr_set_usb1_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_GLOBAL:
            return_value = sysmgr_get_tsn_global(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_GLOBAL:
            return_value = sysmgr_set_tsn_global(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN0:
            return_value = sysmgr_get_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN0:
            return_value = sysmgr_set_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN1:
            return_value = sysmgr_get_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN1:
            return_value = sysmgr_set_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN2:
            return_value = sysmgr_get_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN2:
            return_value = sysmgr_set_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN0_ACE:
            return_value = sysmgr_get_tsn0_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN0_ACE:
            return_value = sysmgr_set_tsn0_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN1_ACE:
            return_value = sysmgr_get_tsn1_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN1_ACE:
            return_value = sysmgr_set_tsn1_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN2_ACE:
            return_value = sysmgr_get_tsn2_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN2_ACE:
            return_value = sysmgr_set_tsn2_ace(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL:
            return_value = sysmgr_get_fpga_bridge_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL:
            return_value = sysmgr_set_fpga_bridge_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA_INTF_EN1:
            return_value = sysmgr_get_fpga_intf_en1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_FPGA_INTF_EN1:
            return_value = sysmgr_set_fpga_intf_en1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA_INTF_EN2:
            return_value = sysmgr_get_fpga_intf_en2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_FPGA_INTF_EN2:
            return_value = sysmgr_set_fpga_intf_en2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA_INTF_EN3:
            return_value = sysmgr_get_fpga_intf_en3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_FPGA_INTF_EN3:
            return_value = sysmgr_set_fpga_intf_en3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMAC0_L3_MASTER:
            return_value = sysmgr_get_dmac0_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMAC0_L3_MASTER:
            return_value = sysmgr_set_dmac0_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_ETR_L3_MASTER:
            return_value = sysmgr_get_etr_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_ETR_L3_MASTER:
            return_value = sysmgr_set_etr_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMAC1_L3_MASTER:
            return_value = sysmgr_get_dmac1_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMAC1_L3_MASTER:
            return_value = sysmgr_set_dmac1_l3_master(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SEC_CTRL_SELECT:
            return_value = sysmgr_get_sec_ctrl_select(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SEC_CTRL_SELECT:
            return_value = sysmgr_set_sec_ctrl_select(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_OSC_TRIM:
            return_value = sysmgr_get_osc_trim(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMAC0_CTRL_STATUS_REG:
            return_value = sysmgr_get_dmac0_ctrl_status_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMAC0_CTRL_STATUS_REG:
            return_value = sysmgr_set_dmac0_ctrl_status_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMAC1_CTRL_STATUS_REG:
            return_value = sysmgr_get_dmac1_ctrl_status_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMAC1_CTRL_STATUS_REG:
            return_value = sysmgr_set_dmac1_ctrl_status_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_ECC_INTMASK_VALUE:
            return_value = sysmgr_get_ecc_intmask_value(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_ECC_INTMASK_VALUE:
            return_value = sysmgr_set_ecc_intmask_value(fd, arg, length);
            break;
        case IOCTL_SYSMGR_ECC_INTMASK_SETBITS:
            return_value = sysmgr_ecc_intmask_setbits(fd, arg, length);
            break;
        case IOCTL_SYSMGR_ECC_INTMASK_CLRBITS:
            return_value = sysmgr_ecc_intmask_clrbits(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_ECC_INTSTATUS_SERR:
            return_value = sysmgr_get_ecc_intstatus_serr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_ECC_INTSTATUS_DERR:
            return_value = sysmgr_get_ecc_intstatus_derr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NOC_TIMEOUT:
            return_value = sysmgr_get_noc_timeout(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NOC_TIMEOUT:
            return_value = sysmgr_set_noc_timeout(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NOC_IDLESTATUS:
            return_value = sysmgr_get_noc_idlestatus(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA2SOC_CTRL:
            return_value = sysmgr_get_fpga2soc_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_FPGA2SOC_CTRL:
            return_value = sysmgr_set_fpga2soc_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_FPGA_CONFIG:
            return_value = sysmgr_get_fpga_config(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_GPO:
            return_value = sysmgr_set_gpo(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_GPI:
            return_value = sysmgr_get_gpi(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_MPU:
            return_value = sysmgr_get_mpu(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_MPU:
            return_value = sysmgr_set_mpu(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_HPS_SPARE:
            return_value = sysmgr_set_sdm_hps_spare(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_HPS_SDM_SPARE:
            return_value = sysmgr_get_hps_sdm_spare(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_HPS_SDM_SPARE:
            return_value = sysmgr_set_hps_sdm_spare(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DFI_INTERFACE_CFG:
            return_value = sysmgr_get_dfi_interface_cfg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DFI_INTERFACE_CFG:
            return_value = sysmgr_set_dfi_interface_cfg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_CTRL:
            return_value = sysmgr_get_nand_dd_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_DD_CTRL:
            return_value = sysmgr_set_nand_dd_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_CTRL_REG:
            return_value = sysmgr_get_nand_phy_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_CTRL_REG:
            return_value = sysmgr_set_nand_phy_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_TSEL_REG:
            return_value = sysmgr_get_nand_phy_tsel_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_TSEL_REG:
            return_value = sysmgr_set_nand_phy_tsel_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_DQ_TIMING_REG:
            return_value = sysmgr_get_nand_phy_dq_timing_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_DQ_TIMING_REG:
            return_value = sysmgr_set_nand_phy_dq_timing_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_DQS_TIMING_REG:
            return_value = sysmgr_get_nand_phy_dqs_timing_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_DQS_TIMING_REG:
            return_value = sysmgr_set_nand_phy_dqs_timing_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_GATE_LPBK_CTRL_REG:
            return_value = sysmgr_get_nand_phy_gate_lpbk_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_GATE_LPBK_CTRL_REG:
            return_value = sysmgr_set_nand_phy_gate_lpbk_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_DLL_MASTER_CTRL_REG:
            return_value = sysmgr_get_nand_phy_dll_master_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_DLL_MASTER_CTRL_REG:
            return_value = sysmgr_set_nand_phy_dll_master_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_PHY_DLL_SLAVE_CTRL_REG:
            return_value = sysmgr_get_nand_phy_dll_slave_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_PHY_DLL_SLAVE_CTRL_REG:
            return_value = sysmgr_set_nand_phy_dll_slave_ctrl_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG0:
            return_value = sysmgr_get_nand_dd_default_setting_reg0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG0:
            return_value = sysmgr_set_nand_dd_default_setting_reg0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_DEFAULT_SETTING_REG1:
            return_value = sysmgr_get_nand_dd_default_setting_reg1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_DD_DEFAULT_SETTING_REG1:
            return_value = sysmgr_set_nand_dd_default_setting_reg1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_STATUS_REG:
            return_value = sysmgr_get_nand_dd_status_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_ID_LOW_REG:
            return_value = sysmgr_get_nand_dd_id_low_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_DD_ID_HIGH_REG:
            return_value = sysmgr_get_nand_dd_id_high_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_NAND_WRITE_PROT_EN_REG:
            return_value = sysmgr_get_nand_write_prot_en_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_NAND_WRITE_PROT_EN_REG:
            return_value = sysmgr_set_nand_write_prot_en_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDMMC_CMD_QUEUE_SETTING_REG:
            return_value = sysmgr_get_sdmmc_cmd_queue_setting_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDMMC_CMD_QUEUE_SETTING_REG:
            return_value = sysmgr_set_sdmmc_cmd_queue_setting_reg(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_I3C_SLV_PID_LOW:
            return_value = sysmgr_get_i3c_slv_pid_low(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_I3C_SLV_PID_LOW:
            return_value = sysmgr_set_i3c_slv_pid_low(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_I3C_SLV_PID_HIGH:
            return_value = sysmgr_get_i3c_slv_pid_high(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_I3C_SLV_PID_HIGH:
            return_value = sysmgr_set_i3c_slv_pid_high(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_I3C_SLV_CTRL0:
            return_value = sysmgr_get_i3c_slv_ctrl0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_I3C_SLV_CTRL0:
            return_value = sysmgr_set_i3c_slv_ctrl0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_I3C_SLV_CTRL1:
            return_value = sysmgr_get_i3c_slv_ctrl1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_I3C_SLV_CTRL1:
            return_value = sysmgr_set_i3c_slv_ctrl1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL:
            return_value = sysmgr_get_f2s_bridge_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL:
            return_value = sysmgr_set_f2s_bridge_ctrl(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA0:
            return_value = sysmgr_get_dma_tbu_stash_ctrl_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA0:
            return_value = sysmgr_set_dma_tbu_stash_ctrl_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STASH_CTRL_REG0_DMA1:
            return_value = sysmgr_get_dma_tbu_stash_ctrl_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STASH_CTRL_REG0_DMA1:
            return_value = sysmgr_set_dma_tbu_stash_ctrl_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDM_TBU_STASH_CTRL_REG1_SDM:
            return_value = sysmgr_get_sdm_tbu_stash_ctrl_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_TBU_STASH_CTRL_REG1_SDM:
            return_value = sysmgr_set_sdm_tbu_stash_ctrl_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB2:
            return_value = sysmgr_get_io_tbu_stash_ctrl_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB2:
            return_value = sysmgr_set_io_tbu_stash_ctrl_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_USB3:
            return_value = sysmgr_get_io_tbu_stash_ctrl_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_USB3:
            return_value = sysmgr_set_io_tbu_stash_ctrl_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_SDMMC:
            return_value = sysmgr_get_io_tbu_stash_ctrl_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_SDMMC:
            return_value = sysmgr_set_io_tbu_stash_ctrl_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_NAND:
            return_value = sysmgr_get_io_tbu_stash_ctrl_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_NAND:
            return_value = sysmgr_set_io_tbu_stash_ctrl_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STASH_CTRL_REG2_ETR:
            return_value = sysmgr_get_io_tbu_stash_ctrl_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STASH_CTRL_REG2_ETR:
            return_value = sysmgr_set_io_tbu_stash_ctrl_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN0:
            return_value = sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN0:
            return_value = sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN1:
            return_value = sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN1:
            return_value = sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STASH_CTRL_REG3_TSN2:
            return_value = sysmgr_get_tsn_tbu_stash_ctrl_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STASH_CTRL_REG3_TSN2:
            return_value = sysmgr_set_tsn_tbu_stash_ctrl_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA0:
            return_value = sysmgr_get_dma_tbu_stream_ctrl_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA0:
            return_value = sysmgr_set_dma_tbu_stream_ctrl_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STREAM_CTRL_REG0_DMA1:
            return_value = sysmgr_get_dma_tbu_stream_ctrl_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STREAM_CTRL_REG0_DMA1:
            return_value = sysmgr_set_dma_tbu_stream_ctrl_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDM_TBU_STREAM_CTRL_REG1_SDM:
            return_value = sysmgr_get_sdm_tbu_stream_ctrl_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_TBU_STREAM_CTRL_REG1_SDM:
            return_value = sysmgr_set_sdm_tbu_stream_ctrl_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB2:
            return_value = sysmgr_get_io_tbu_stream_ctrl_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB2:
            return_value = sysmgr_set_io_tbu_stream_ctrl_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_USB3:
            return_value = sysmgr_get_io_tbu_stream_ctrl_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_USB3:
            return_value = sysmgr_set_io_tbu_stream_ctrl_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_SDMMC:
            return_value = sysmgr_get_io_tbu_stream_ctrl_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_SDMMC:
            return_value = sysmgr_set_io_tbu_stream_ctrl_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_NAND:
            return_value = sysmgr_get_io_tbu_stream_ctrl_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_NAND:
            return_value = sysmgr_set_io_tbu_stream_ctrl_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_CTRL_REG2_ETR:
            return_value = sysmgr_get_io_tbu_stream_ctrl_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_CTRL_REG2_ETR:
            return_value = sysmgr_set_io_tbu_stream_ctrl_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN0:
            return_value = sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN0:
            return_value = sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN1:
            return_value = sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN1:
            return_value = sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_CTRL_REG3_TSN2:
            return_value = sysmgr_get_tsn_tbu_stream_ctrl_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_CTRL_REG3_TSN2:
            return_value = sysmgr_set_tsn_tbu_stream_ctrl_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA0:
            return_value = sysmgr_get_dma_tbu_stream_id_ax_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA0:
            return_value = sysmgr_set_dma_tbu_stream_id_ax_reg0_dma0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_DMA_TBU_STREAM_ID_AX_REG0_DMA1:
            return_value = sysmgr_get_dma_tbu_stream_id_ax_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_DMA_TBU_STREAM_ID_AX_REG0_DMA1:
            return_value = sysmgr_set_dma_tbu_stream_id_ax_reg0_dma1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDM_TBU_STREAM_ID_AX_REG1_SDM:
            return_value = sysmgr_get_sdm_tbu_stream_id_ax_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_TBU_STREAM_ID_AX_REG1_SDM:
            return_value = sysmgr_set_sdm_tbu_stream_id_ax_reg1_sdm(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB2:
            return_value = sysmgr_get_io_tbu_stream_id_ax_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB2:
            return_value = sysmgr_set_io_tbu_stream_id_ax_reg2_usb2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_USB3:
            return_value = sysmgr_get_io_tbu_stream_id_ax_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_USB3:
            return_value = sysmgr_set_io_tbu_stream_id_ax_reg2_usb3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_SDMMC:
            return_value = sysmgr_get_io_tbu_stream_id_ax_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_SDMMC:
            return_value = sysmgr_set_io_tbu_stream_id_ax_reg2_sdmmc(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_NAND:
            return_value = sysmgr_get_io_tbu_stream_id_ax_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_NAND:
            return_value = sysmgr_set_io_tbu_stream_id_ax_reg2_nand(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_IO_TBU_STREAM_ID_AX_REG2_ETR:
            return_value = sysmgr_get_io_tbu_stream_id_ax_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_IO_TBU_STREAM_ID_AX_REG2_ETR:
            return_value = sysmgr_set_io_tbu_stream_id_ax_reg2_etr(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN0:
            return_value = sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN0:
            return_value = sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN1:
            return_value = sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN1:
            return_value = sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_TSN_TBU_STREAM_ID_AX_REG3_TSN2:
            return_value = sysmgr_get_tsn_tbu_stream_id_ax_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_TSN_TBU_STREAM_ID_AX_REG3_TSN2:
            return_value = sysmgr_set_tsn_tbu_stream_id_ax_reg3_tsn2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG0:
            return_value = sysmgr_get_usb3_misc_ctrl_reg0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG0:
            return_value = sysmgr_set_usb3_misc_ctrl_reg0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_USB3_MISC_CTRL_REG1:
            return_value = sysmgr_get_usb3_misc_ctrl_reg1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_USB3_MISC_CTRL_REG1:
            return_value = sysmgr_set_usb3_misc_ctrl_reg1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD0:
            return_value = sysmgr_get_boot_scratch_cold0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD0:
            return_value = sysmgr_set_boot_scratch_cold0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD1:
            return_value = sysmgr_get_boot_scratch_cold1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD1:
            return_value = sysmgr_set_boot_scratch_cold1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD2:
            return_value = sysmgr_get_boot_scratch_cold2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD2:
            return_value = sysmgr_set_boot_scratch_cold2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD3:
            return_value = sysmgr_get_boot_scratch_cold3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD3:
            return_value = sysmgr_set_boot_scratch_cold3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD4:
            return_value = sysmgr_get_boot_scratch_cold4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD4:
            return_value = sysmgr_set_boot_scratch_cold4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD5:
            return_value = sysmgr_get_boot_scratch_cold5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD5:
            return_value = sysmgr_set_boot_scratch_cold5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD6:
            return_value = sysmgr_get_boot_scratch_cold6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD6:
            return_value = sysmgr_set_boot_scratch_cold6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD7:
            return_value = sysmgr_get_boot_scratch_cold7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD7:
            return_value = sysmgr_set_boot_scratch_cold7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD8:
            return_value = sysmgr_get_boot_scratch_cold8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD8:
            return_value = sysmgr_set_boot_scratch_cold8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_COLD9:
            return_value = sysmgr_get_boot_scratch_cold9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_COLD9:
            return_value = sysmgr_set_boot_scratch_cold9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_MPFE_CONFIG:
            return_value = sysmgr_get_mpfe_config(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_MPFE_CONFIG:
            return_value = sysmgr_set_mpfe_config(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_MPFE_STATUS:
            return_value = sysmgr_get_mpfe_status(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM0:
            return_value = sysmgr_get_boot_scratch_warm0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM0:
            return_value = sysmgr_set_boot_scratch_warm0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM1:
            return_value = sysmgr_get_boot_scratch_warm1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM1:
            return_value = sysmgr_set_boot_scratch_warm1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM2:
            return_value = sysmgr_get_boot_scratch_warm2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM2:
            return_value = sysmgr_set_boot_scratch_warm2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM3:
            return_value = sysmgr_get_boot_scratch_warm3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM3:
            return_value = sysmgr_set_boot_scratch_warm3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM4:
            return_value = sysmgr_get_boot_scratch_warm4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM4:
            return_value = sysmgr_set_boot_scratch_warm4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM5:
            return_value = sysmgr_get_boot_scratch_warm5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM5:
            return_value = sysmgr_set_boot_scratch_warm5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM6:
            return_value = sysmgr_get_boot_scratch_warm6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM6:
            return_value = sysmgr_set_boot_scratch_warm6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM7:
            return_value = sysmgr_get_boot_scratch_warm7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM7:
            return_value = sysmgr_set_boot_scratch_warm7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM8:
            return_value = sysmgr_get_boot_scratch_warm8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM8:
            return_value = sysmgr_set_boot_scratch_warm8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_WARM9:
            return_value = sysmgr_get_boot_scratch_warm9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_WARM9:
            return_value = sysmgr_set_boot_scratch_warm9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR0:
            return_value = sysmgr_get_boot_scratch_por0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR0:
            return_value = sysmgr_set_boot_scratch_por0(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR1:
            return_value = sysmgr_get_boot_scratch_por1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR1:
            return_value = sysmgr_set_boot_scratch_por1(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR2:
            return_value = sysmgr_get_boot_scratch_por2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR2:
            return_value = sysmgr_set_boot_scratch_por2(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR3:
            return_value = sysmgr_get_boot_scratch_por3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR3:
            return_value = sysmgr_set_boot_scratch_por3(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR4:
            return_value = sysmgr_get_boot_scratch_por4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR4:
            return_value = sysmgr_set_boot_scratch_por4(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR5:
            return_value = sysmgr_get_boot_scratch_por5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR5:
            return_value = sysmgr_set_boot_scratch_por5(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR6:
            return_value = sysmgr_get_boot_scratch_por6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR6:
            return_value = sysmgr_set_boot_scratch_por6(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR7:
            return_value = sysmgr_get_boot_scratch_por7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR7:
            return_value = sysmgr_set_boot_scratch_por7(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR8:
            return_value = sysmgr_get_boot_scratch_por8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR8:
            return_value = sysmgr_set_boot_scratch_por8(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_BOOT_SCRATCH_POR9:
            return_value = sysmgr_get_boot_scratch_por9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_BOOT_SCRATCH_POR9:
            return_value = sysmgr_set_boot_scratch_por9(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDM_BE_AWADDR_REMAP:
            return_value = sysmgr_get_sdm_be_awaddr_remap(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_BE_AWADDR_REMAP:
            return_value = sysmgr_set_sdm_be_awaddr_remap(fd, arg, length);
            break;
        case IOCTL_SYSMGR_GET_SDM_BE_ARADDR_REMAP:
            return_value = sysmgr_get_sdm_be_araddr_remap(fd, arg, length);
            break;
        case IOCTL_SYSMGR_SET_SDM_BE_ARADDR_REMAP:
            return_value = sysmgr_set_sdm_be_araddr_remap(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t sysmgr_error(int32_t fd) { return -1; }

#ifdef __cplusplus
}
#endif // __cplusplus