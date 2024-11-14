#include "combophy.h"
#include "combophy_internal.h"
#include "combophy_regs.h"
#include "device.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// combophy descriptor
device_descriptor_t combophy_devices[] = {{.name = "/dev/combophy0", .fd = COMBOPHY_BASE, .acquired = 0}};

/* name: combophy_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t combophy_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != NULL) {
        for (uint32_t i = 0; i < (sizeof(combophy_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(combophy_devices[i].name, path) == 0) {
                if (claim_device(&combophy_devices[i])) {
                    return_value = combophy_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

/* name: combophy_close
 * description: close the base_add via the base address of the device
 * parameters(s): base_add "address of the combophy device open"
 */
int32_t combophy_close(int32_t base_add) {
    int32_t return_value = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(combophy_devices) / sizeof(device_descriptor_t)); i++) {
            if (combophy_devices[i].fd == base_add) {
                combophy_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* name: combophy_read
 * description: reading registers
 * parameters(s): base_add "address of the combophy device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t combophy_read(int32_t base_add, uintptr_t user_data, size_t length) {
    return combophy_recv(base_add, user_data, length, 0);
}

/* name: combophy_write
 * description: writing registers
 * parameters(s): base_add "address of the combophy device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t combophy_write(int32_t base_add, uintptr_t user_data, size_t length) {
    return combophy_send(base_add, user_data, length, 0);
}

/* name: combophy_recv - unimplemented
 * description: reading registers
 * parameters(s): base_add "address of the combophy device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t combophy_recv(int32_t base_add, uintptr_t user_data, size_t length, int32_t flags) { return 0; }

/* name: combophy_send - unimplemented
 * description: writing registers
 * parameters(s): base_add "address of the combophy device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t combophy_send(int32_t base_add, uintptr_t user_data, size_t size, int32_t flags) { return 0; }

/* name: combophy_ioctl
 * description: process the input output control command
 * parameters(s): base_add, user_data, length "address of the combophy device open"
 *                operation "specific ioctl command for combophy"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
int32_t combophy_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    int32_t return_value = -1;
    if ((base_add == -1) || (((void *)(user_data)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((combophy_ioctl_t)operation) {
        case IOCTL_COMBOPHY_READ_REGS:
            return_value = combophy_read_regs(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_WRITE_REGS:
            return_value = combophy_write_regs(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DQ_TIMING:
            return_value = combophy_get_dq_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_DQ_TIMING:
            return_value = combophy_set_dq_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DQS_TIMING:
            return_value = combophy_get_dqs_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_DQS_TIMING:
            return_value = combophy_set_dqs_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_GATE_LPBK_CTRL:
            return_value = combophy_get_gate_lpbk_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_GATE_LPBK_CTRL:
            return_value = combophy_set_gate_lpbk_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DLL_MASTER_CTRL:
            return_value = combophy_get_dll_master_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_DLL_MASTER_CTRL:
            return_value = combophy_set_dll_master_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DLL_SLAVE_CTRL:
            return_value = combophy_get_dll_slave_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_DLL_SLAVE_CTRL:
            return_value = combophy_set_dll_slave_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_IE_TIMING:
            return_value = combophy_get_ie_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_IE_TIMING:
            return_value = combophy_set_ie_timing(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_OBS_REG_0:
            return_value = combophy_get_obs_reg_0(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DLL_OBS_REG0:
            return_value = combophy_get_dll_obs_reg0(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DLL_OBS_REG1:
            return_value = combophy_get_dll_obs_reg1(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_DLL_OBS_REG2:
            return_value = combophy_get_dll_obs_reg2(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_STATIC_TOGG:
            return_value = combophy_get_static_togg(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_STATIC_TOGG:
            return_value = combophy_set_static_togg(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_WR_DESKEW:
            return_value = combophy_get_wr_deskew(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_WR_DESKEW:
            return_value = combophy_set_wr_deskew(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_WR_RD_DESKEW_CMD:
            return_value = combophy_get_wr_rd_deskew_cmd(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_WR_RD_DESKEW_CMD:
            return_value = combophy_set_wr_rd_deskew_cmd(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_WR_DESKEW_PD_CTRL0:
            return_value = combophy_get_wr_deskew_pd_ctrl0(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_WR_DESKEW_PD_CTRL0:
            return_value = combophy_set_wr_deskew_pd_ctrl0(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_WR_DESKEW_PD_CTRL1:
            return_value = combophy_get_wr_deskew_pd_ctrl1(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_WR_DESKEW_PD_CTRL1:
            return_value = combophy_set_wr_deskew_pd_ctrl1(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_RD_DESKEW:
            return_value = combophy_get_rd_deskew(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_RD_DESKEW:
            return_value = combophy_set_rd_deskew(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_VERSION:
            return_value = combophy_get_version(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_FEATURES:
            return_value = combophy_get_features(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_CTRL:
            return_value = combophy_get_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_CTRL:
            return_value = combophy_set_ctrl(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_GET_TSEL:
            return_value = combophy_get_tsel(base_add, user_data, length);
            break;
        case IOCTL_COMBOPHY_SET_TSEL:
            return_value = combophy_set_tsel(base_add, user_data, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}
