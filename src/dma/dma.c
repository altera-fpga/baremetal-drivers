#include "dma.h"
#include "device.h"
#include "dma_internal.h"
#include "dma_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

device_descriptor_t dma_devices[] = {{.name = "/dev/dma0", .fd = DMA0_BASE, .acquired = 0},
                                     {.name = "/dev/dma1", .fd = DMA1_BASE, .acquired = 0}};

// channel number of the DMA controller
int32_t dma_chan_num = 4;

/**
 * @brief This function gets an available channel
 *
 * @param fd base address of DMA controller (handler)
 * @return the index of the available channel
 */
int32_t dma_get_chan(int32_t fd) {
    uint64_t channel_en_bitmap = 0;
    uintptr_t p_temp;
    int32_t ret = -1;

    if (fd != -1) {
        dma_get_chen_enable_reg(fd, (uintptr_t)&p_temp);

        channel_en_bitmap = p_temp;

        for (int32_t i = 0; i < dma_chan_num; i++) {
            if ((channel_en_bitmap & ((uint64_t)1 << (uint64_t)i)) == 0u) {
                ret = i;
                break;
            } else {
                continue;
            }
        }
    }

    return ret;
}

/**
 * @brief This function disable the DMA controller
 *
 * @param fd base address of DMA controller (handler)
 * @return 0 if successful, otherwise return non-zero values
 */

int32_t dma_disable(int32_t fd) {

    uint64_t args;
    int32_t ret = -1;
    uintptr_t disable_bitmap = 0;

    if (fd != -1) {
        args = ~(DMA_CFG_INT_ENABLE_MASK | DMA_CFG_ENABLE_MASK);
        dma_set_cfg_reg(fd, (uintptr_t)&args);

        dma_get_chen_enable_reg(fd, (uintptr_t)&args);

        if (args == disable_bitmap) {
            ret = 0;
        }
    }

    return ret;
}

/**
 * @brief This function opens the DMA controller
 *
 * @param name the path to the device
 * @param flags currently unused
 * @return the base address of the controller. -1 means there is no available controller
 */

int32_t dma_open(const char *name, int32_t flags) {
    int32_t return_value = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(dma_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(dma_devices[i].name, name) == 0) {
                if (claim_device(&dma_devices[i])) {
                    return_value = dma_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

/**
 * @brief This function closes the DMA controller
 *
 * @param fd base address of DMA controller (handler)
 * @return 0 if successful, otherwise return non-zero values
 */

int32_t dma_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        dma_disable(fd);

        for (uint32_t i = 0; i < (sizeof(dma_devices) / sizeof(device_descriptor_t)); i++) {
            if (dma_devices[i].fd == fd) {
                dma_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/**
 * @brief This function enables the DMA transmission
 *
 * @param channel the channel used to be transferring data
 * @return 0 if successful
 */

int32_t dma_trans_enable(int32_t fd, int32_t channel) {
    int32_t return_value = -1;
    if (fd != -1) {
        uint64_t val_chen_en = ((uint64_t)(1u) << (uint32_t)channel) & DMA_CHEN_ENABLE_MASK;
        uint64_t val_chen_wr_en =
            (((uint64_t)(1u) << (uint32_t)channel) << DMA_CHEN_WRITE_EN_ENABLE_OFST) & DMA_CHEN_WRITE_EN_ENABLE_MASK;

        uintptr_t args = (DMA_CFG_ENABLE_MASK | DMA_CFG_INT_ENABLE_MASK);
        dma_set_cfg_reg(fd, (uintptr_t)&args);

        args = (val_chen_wr_en | val_chen_en);
        dma_set_chen_enable_reg(fd, (uintptr_t)&args);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

/**
 * @brief This function provides a generic interface for DMA operations
 *
 * @param fd base address of DMA controller (handler)
 * @param operation the operation to retrieve the DMA register
 * @param args the read/write data of the register
 * @param length the size of the read/write data
 * @param channel the channel index to be configured
 * @return 0 if successful
 */

int32_t dma_ioctl(int32_t fd, int32_t operation, uintptr_t args, size_t length, int32_t channel) {
    int32_t return_value = -1;
    if ((length < sizeof(uint64_t)) || (((void *)(args)) == nullptr) || (fd == -1)) {
        return_value = -1;
    } else {
        switch ((dma_ioctl_t)operation) {
        case IOCTL_DMA_REGS_READ:
            return_value = dma_read_regs(fd, args, length);
            break;
        case IOCTL_DMA_REGS_WRITE:
            return_value = dma_write_regs(fd, args, length);
            break;
        case IOCTL_DMA_IDREG_GET:
            return_value = dma_get_id_reg(fd, args);
            break;
        case IOCTL_DMA_COMPVERREG_GET:
            return_value = dma_get_comp_ver_no_reg(fd, args);
            break;
        case IOCTL_DMA_CFG_SET:
            return_value = dma_set_cfg_reg(fd, args);
            break;
        case IOCTL_DMA_CFG_GET:
            return_value = dma_get_cfg_reg(fd, args);
            break;
        case IOCTL_DMA_CHENREG_EN_SET:
            return_value = dma_set_chen_enable_reg(fd, args);
            break;
        case IOCTL_DMA_CHENREG_GET:
            return_value = dma_get_chen_enable_reg(fd, args);
            break;
        case IOCTL_DMA_INTSTATUSREG_GET:
            return_value = dma_get_int_status_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTCLEARREG_SET:
            return_value = dma_set_common_int_clear_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTSTATUS_ENABLEREG_GET:
            return_value = dma_get_common_int_sts_en_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTSTATUS_ENABLEREG_SET:
            return_value = dma_set_common_int_sts_en_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTSIGNAL_ENABLEREG_GET:
            return_value = dma_get_common_int_sig_en_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTSIGNAL_ENABLEREG_SET:
            return_value = dma_set_common_int_sig_en_reg(fd, args);
            break;
        case IOCTL_DMA_COMMONREG_INTSTATUSREG_GET:
            return_value = dma_get_common_int_status_reg(fd, args);
            break;
        case IOCTL_DMA_RESETREG_SET:
            return_value = dma_set_reset_reg(fd, args);
            break;
        case IOCTL_DMA_RESETREG_GET:
            return_value = dma_get_reset_reg(fd, args);
            break;
        case IOCTL_DMA_LOWPOWER_CFGREG_SET:
            return_value = dma_set_low_power_cfg_reg(fd, args);
            break;
        case IOCTL_DMA_LOWPOWER_CFGREG_GET:
            return_value = dma_get_low_power_cfg_reg(fd, args);
            break;
        case IOCTL_DMA_CH_SAR_SET:
            return_value = dma_ch_set_src_addr_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_SAR_GET:
            return_value = dma_ch_get_src_addr_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_DAR_SET:
            return_value = dma_ch_set_dst_addr_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_DAR_GET:
            return_value = dma_ch_get_dst_addr_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_BLOCK_TS_GET:
            return_value = dma_ch_get_blk_tran_size_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_BLOCK_TS_SET:
            return_value = dma_ch_set_blk_tran_size_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_CTL_GET:
            return_value = dma_ch_get_trans_ctl_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_CTL_SET:
            return_value = dma_ch_set_trans_ctl_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_CFG2_GET:
            return_value = dma_ch_get_trans_cfg2_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_CFG2_SET:
            return_value = dma_ch_set_trans_cfg2_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_LLP_GET:
            return_value = dma_ch_get_linked_list_point_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_LLP_SET:
            return_value = dma_ch_set_linked_list_point_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_STATUSREG_GET:
            return_value = dma_ch_get_status_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_SWHSSRCREG_GET:
            return_value = dma_ch_get_sw_hsk_src_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_SWHSSRCREG_SET:
            return_value = dma_ch_set_sw_hsk_src_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_SWHSDSTREG_GET:
            return_value = dma_ch_get_sw_hsk_dst_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_SWHSDSTREG_SET:
            return_value = dma_ch_set_sw_hsk_dst_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_BLK_TFR_RESUMEREQREG_SET:
            return_value = dma_ch_set_blk_tfr_resume_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_AXI_IDREG_GET:
            return_value = dma_ch_get_axi_id_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_AXI_IDREG_SET:
            return_value = dma_ch_set_axi_id_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_AXI_QOSREG_GET:
            return_value = dma_ch_get_axi_qos_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_AXI_QOSREG_SET:
            return_value = dma_ch_set_axi_qos_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTSTATUS_ENABLEREG_GET:
            return_value = dma_ch_get_int_status_en_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTSTATUS_ENABLEREG_SET:
            return_value = dma_ch_set_int_status_en_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTSTATUS_GET:
            return_value = dma_ch_get_int_status_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTSIGNAL_ENABLEREG_GET:
            return_value = dma_ch_get_int_signal_en_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTSIGNAL_ENABLEREG_SET:
            return_value = dma_ch_set_int_signal_en_reg(fd, args, channel);
            break;
        case IOCTL_DMA_CH_INTCLEARREG_SET:
            return_value = dma_ch_set_int_clear_reg(fd, args, channel);
            break;
        default:
            return_value = -1;
            break;
        }
    }

    return return_value;
}
