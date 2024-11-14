#include <stdint.h>
#include <string.h>

// inc
#include "i3c.h"
#include "i3c_internal.h"
#include "i3c_regs.h"

#include "device.h"

device_descriptor_t i3c_devices[] = {{.name = "/dev/i3c0", .fd = I3C0_BASE, .acquired = 0},
                                     {.name = "/dev/i3c1", .fd = I3C1_BASE, .acquired = 0}};

int32_t i3c_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(i3c_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(i3c_devices[i].name, name) == 0) {
                if (claim_device(&i3c_devices[i])) {
                    fd = i3c_devices[i].fd;
                    i3c_internal_init(fd);
                }
            }
        }
    }
    return fd;
}

int32_t i3c_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(i3c_devices) / sizeof(device_descriptor_t)); i++) {
            if (i3c_devices[i].fd == fd) {
                i3c_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t i3c_send(int32_t fd, const uintptr_t buf, size_t length, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        int32_t send_value = i3c_internal_send(fd, (uint32_t *)buf, (uint32_t)length, (uint32_t)flags);

        if (send_value < 0) {
            return_value = (size_t)0;
        } else {
            return_value = (size_t)send_value;
        }
    }
    return return_value;
}

size_t i3c_write(int32_t fd, uintptr_t buf, size_t count) { return (size_t)(-1); }

size_t i3c_recv(int32_t fd, uintptr_t buf, size_t count, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        int32_t recv_value = i3c_internal_recv(fd, (uint32_t *)buf, (uint32_t)count, (uint32_t)flags);

        if (recv_value < 0) {
            return_value = (size_t)0;
        } else {
            return_value = (size_t)recv_value;
        }
    }
    return return_value;
}

size_t i3c_read(int32_t fd, uintptr_t buf, size_t count) { return (size_t)(-1); }

int32_t i3c_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((i3c_ioctl_op_t)request) {
        case I3C_IOCTL_READ_REGS:
            return_value = i3c_read_regs(fd, arg, length);
            break;
        case I3C_IOCTL_WRITE_REGS:
            return_value = i3c_write_regs(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_SET:
            return_value = i3c_cfg_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_GET:
            return_value = i3c_cfg_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_IBA_INC_SET:
            return_value = i3c_cfg_iba_inc_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_IBA_INC_GET:
            return_value = i3c_cfg_iba_inc_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_I2C_PRESENT_SET:
            return_value = i3c_cfg_i2c_present_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_I2C_PRESENT_GET:
            return_value = i3c_cfg_i2c_present_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_HOT_JOIN_SET:
            return_value = i3c_cfg_hot_join_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_HOT_JOIN_GET:
            return_value = i3c_cfg_hot_join_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_DMA_ENABLE_SET:
            return_value = i3c_cfg_dma_enable_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_DMA_ENABLE_GET:
            return_value = i3c_cfg_dma_enable_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_ABORT_SET:
            return_value = i3c_cfg_abort_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_ABORT_GET:
            return_value = i3c_cfg_abort_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_RESUME_SET:
            return_value = i3c_cfg_resume_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_RESUME_GET:
            return_value = i3c_cfg_resume_get(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_ENABLE_SET:
            return_value = i3c_cfg_enable_set(fd, arg, length);
            break;
        case I3C_IOCTL_CFG_ENABLE_GET:
            return_value = i3c_cfg_enable_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_ADDR_SET:
            return_value = i3c_device_addr_set(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_ADDR_GET:
            return_value = i3c_device_addr_get(fd, arg, length);
            break;
        case I3C_IOCTL_HW_CAPABILITY_GET:
            return_value = i3c_hw_capability_get(fd, arg, length);
            break;
        case I3C_IOCTL_COMMAND_QUEUE_PORT_SET:
            return_value = i3c_command_queue_port_set(fd, arg, length);
            break;
        case I3C_IOCTL_RESPONSE_QUEUE_PORT_GET:
            return_value = i3c_response_queue_port_get(fd, arg, length);
            break;
        case I3C_IOCTL_TX_DATA_PORT_SET:
            return_value = i3c_tx_data_port_set(fd, arg, length);
            break;
        case I3C_IOCTL_IBI_QUEUE_STATUS_GET:
            return_value = i3c_ibi_queue_status_get(fd, arg, length);
            break;
        case I3C_IOCTL_QUEUE_THLD_CTRL_SET:
            return_value = i3c_queue_thld_ctrl_set(fd, arg, length);
            break;
        case I3C_IOCTL_QUEUE_THLD_CTRL_GET:
            return_value = i3c_queue_thld_ctrl_get(fd, arg, length);
            break;
        case I3C_IOCTL_DATA_BUFFER_THLD_CTRL_SET:
            return_value = i3c_data_buffer_thld_ctrl_set(fd, arg, length);
            break;
        case I3C_IOCTL_DATA_BUFFER_THLD_CTRL_GET:
            return_value = i3c_data_buffer_thld_ctrl_get(fd, arg, length);
            break;
        case I3C_IOCTL_IBI_QUEUE_CTRL_SET:
            return_value = i3c_ibi_queue_ctrl_set(fd, arg, length);
            break;
        case I3C_IOCTL_IBI_QUEUE_CTRL_GET:
            return_value = i3c_ibi_queue_ctrl_get(fd, arg, length);
            break;
        case I3C_IOCTL_RESET_CONTROL_SET:
            return_value = i3c_reset_control_set(fd, arg, length);
            break;
        case I3C_IOCTL_RESET_CONTROL_GET:
            return_value = i3c_reset_control_get(fd, arg, length);
            break;
        case I3C_IOCTL_SLV_EVENT_STATUS_GET:
            return_value = i3c_slv_event_status_get(fd, arg, length);
            break;
        case I3C_IOCTL_SLV_EVENT_STATUS_SET:
            return_value = i3c_slv_event_status_set(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_STATUS_GET:
            return_value = i3c_intr_status_get(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_STATUS_SET:
            return_value = i3c_intr_status_set(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_STATUS_EN_GET:
            return_value = i3c_intr_status_en_get(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_STATUS_EN_SET:
            return_value = i3c_intr_status_en_set(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_SIGNAL_EN_GET:
            return_value = i3c_intr_signal_en_get(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_SIGNAL_EN_SET:
            return_value = i3c_intr_signal_en_set(fd, arg, length);
            break;
        case I3C_IOCTL_INTR_FORCE_SET:
            return_value = i3c_intr_force_set(fd, arg, length);
            break;
        case I3C_IOCTL_QUEUE_STATUS_LEVEL_GET:
            return_value = i3c_queue_status_level_get(fd, arg, length);
            break;
        case I3C_IOCTL_DATA_BUFFER_STATUS_LEVEL_GET:
            return_value = i3c_data_buffer_status_level_get(fd, arg, length);
            break;
        case I3C_IOCTL_PRESENT_STATE_GET:
            return_value = i3c_present_state_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_ADDR_TABLE_PTR_GET:
            return_value = i3c_device_addr_table_ptr_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEV_CHAR_TABLE_PTR_GET:
            return_value = i3c_dev_char_table_ptr_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEV_CHAR_TABLE_PTR_SET_IDX:
            return_value = i3c_dev_char_table_ptr_set_idx(fd, arg, length);
            break;
        case I3C_IOCTL_VENDOR_SPECIFIC_REG_PTR_GET:
            return_value = i3c_vendor_specific_reg_ptr_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_CONTROL_EXT_SET:
            return_value = i3c_device_control_ext_set(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_CONTROL_EXT_GET:
            return_value = i3c_device_control_ext_get(fd, arg, length);
            break;
        case I3C_IOCTL_I3C_OD_TIMING_SET:
            return_value = i3c_i3c_od_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_I3C_OD_TIMING_GET:
            return_value = i3c_i3c_od_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_I3C_PP_TIMING_SET:
            return_value = i3c_i3c_pp_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_I3C_PP_TIMING_GET:
            return_value = i3c_i3c_pp_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_I2C_FM_TIMING_SET:
            return_value = i3c_i2c_fm_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_I2C_FM_TIMING_GET:
            return_value = i3c_i2c_fm_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_I2C_FMP_TIMING_SET:
            return_value = i3c_i2c_fmp_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_I2C_FMP_TIMING_GET:
            return_value = i3c_i2c_fmp_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_SCL_EXT_LCNT_TIMING_SET:
            return_value = i3c_scl_ext_lcnt_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_SCL_EXT_LCNT_TIMING_GET:
            return_value = i3c_scl_ext_lcnt_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_SCL_EXT_TERMN_LCNT_TIMING_SET:
            return_value = i3c_scl_ext_termn_lcnt_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_SCL_EXT_TERMN_LCNT_TIMING_GET:
            return_value = i3c_scl_ext_termn_lcnt_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_SDA_HOLD_SWITCH_DLY_TIMING_SET:
            return_value = i3c_sda_delay_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_SDA_HOLD_SWITCH_DLY_TIMING_GET:
            return_value = i3c_sda_delay_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_BUS_FREE_AVAIL_TIMING_SET:
            return_value = i3c_bus_free_avail_timing_set(fd, arg, length);
            break;
        case I3C_IOCTL_BUS_FREE_AVAIL_TIMING_GET:
            return_value = i3c_bus_free_avail_timing_get(fd, arg, length);
            break;
        case I3C_IOCTL_VERSION_ID_GET:
            return_value = i3c_version_id_get(fd, arg, length);
            break;
        case I3C_IOCTL_VERSION_TYPE_GET:
            return_value = i3c_version_type_get(fd, arg, length);
            break;
        case I3C_IOCTL_QUEUE_SIZE_CAPABILITY_GET:
            return_value = i3c_queue_size_capability_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_ADDRESS_TABLE_SET:
            return_value = i3c_device_address_table_set(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_ADDRESS_TABLE_GET:
            return_value = i3c_device_address_table_get(fd, arg, length);
            break;
        case I3C_IOCTL_DEVICE_CHARACTERISTIC_TABLE_GET:
            return_value = i3c_device_characteristic_table_get(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t i3c_error(int32_t fd) { return 0; }
