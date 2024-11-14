#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "i3c.h"
#include "i3c_internal.h"
#include "i3c_regs.h"

int32_t i3c_internal_init(int32_t fd) {
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    regs->INTR_STATUS_EN |= I3C_INTR_STATUS_CMD_QUEUE_READY_STS_MASK;
    regs->INTR_STATUS_EN |= I3C_INTR_STATUS_RESP_READY_STS_MASK;
    regs->INTR_STATUS_EN |= I3C_INTR_STATUS_TX_THLD_STS_MASK;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// I3C Read & Write Data
//
///////////////////////////////////////////////////////////////////////////////
int32_t i3c_internal_send(int32_t fd, uint32_t *data, uint32_t data_length, uint32_t cmd_info) {
    int32_t ret = 0;
    uint32_t timeout = 0x100000;
    uint32_t cmd = cmd_info;
    volatile i3c_regs_t *regs = (i3c_regs_t *)(fd);

    if (data_length == (uint32_t)0) {
        if ((cmd & (uint32_t)(I3C_FLAGS_XFER_ATTR_MASK)) == (uint32_t)I3C_MSG_TYPE_ADDR_ASSIGN) {
            regs->COMMAND_QUEUE_PORT = cmd;
            ret = 0;
        } else {
            ret = -1;
        }
    } else if (data_length <= (uint32_t)3) {
        // This is an immediate data transfer
        // Set bits for immediate then push short data to command queue
        cmd &= ~((uint32_t)I3C_FLAGS_XFER_ATTR_MASK);
        cmd |= (uint32_t)(I3C_MSG_TYPE_IMMEDIATE)&I3C_FLAGS_XFER_ATTR_MASK;
        regs->COMMAND_QUEUE_PORT = *data;
        regs->COMMAND_QUEUE_PORT = cmd;
        ret = 0;
    } else {
        // Regular transfer
        // Set bits for regular transfer then push data to data port
        cmd &= ~I3C_FLAGS_XFER_ATTR_MASK;
        cmd |= (uint32_t)(I3C_MSG_TYPE_REGULAR)&I3C_FLAGS_XFER_ATTR_MASK;
        // Push data to TX fifo
        for (uint32_t i = 0; i < (data_length / sizeof(uint32_t)); i++) {
            while ((regs->INTR_STATUS & I3C_INTR_STATUS_TX_THLD_STS_MASK) != (uint32_t)0) {
                timeout--;
                if (timeout == (uint32_t)0) {
                    ret = -1;
                    break;
                }
            }
            regs->TX_DATA_PORT = data[i];
        }

        if (ret == 0) {
            regs->COMMAND_QUEUE_PORT = cmd;
        }
    }
    // Wait for response
    timeout = 0x100000;
    while ((regs->INTR_STATUS & I3C_INTR_STATUS_CMD_QUEUE_READY_STS_MASK) == (uint32_t)0) {
        timeout--;
        if (timeout == (uint32_t)0) {
            ret = -1;
            break;
        }
    }
    return ret;
}

int32_t i3c_internal_recv(int32_t fd, uint32_t *data, uint32_t data_length, uint32_t cmd_info) {
    int32_t ret = 0;
    uint32_t timeout = 0x100000;
    volatile i3c_regs_t *regs = (i3c_regs_t *)(fd);

    timeout = 0x100000;
    while ((regs->INTR_STATUS & I3C_INTR_STATUS_CMD_QUEUE_READY_STS_MASK) == (uint32_t)0) {
        timeout--;
        if (timeout == (uint32_t)0) {
            ret = -1;
            break;
        }
    }

    // Wait for response
    timeout = 0x100000;
    while ((regs->INTR_STATUS & I3C_INTR_STATUS_RESP_READY_STS_MASK) == (uint32_t)0) {
        timeout--;
        if (timeout == (uint32_t)0) {
            ret = -1;
            break;
        }
    }
    if (ret == 0) {
        // Read response
        uint32_t resp = regs->RESPONSE_QUEUE_PORT;

        // Read data port if the command is a read transfer
        uint32_t resp_dl = resp & I3C_RESP_DATA_LENGTH_MASK;

        for (uint32_t i = 0; i < (resp_dl / sizeof(uint32_t)); i++) {
            data[i] = regs->TX_DATA_PORT;
        }
        ret = (int32_t)resp_dl;
    }

    return ret;
}

// IOCTLS
int32_t i3c_read_regs(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *regs = (uint32_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(i3c_regs_t)) {
        return_value = -1;
    } else {
        for (size_t i = 0; i < (sizeof(i3c_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = regs[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_write_regs(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *regs = (uint32_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(i3c_regs_t)) {
        return_value = -1;
    } else {
        for (size_t i = 0; i < (sizeof(i3c_regs_t) / sizeof(uint32_t)); i++) {
            regs[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DEVICE_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_iba_inc_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_IBA_INCLUDE_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_IBA_INCLUDE_OFST) & I3C_DEVICE_CTRL_IBA_INCLUDE_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_iba_inc_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_IBA_INCLUDE_MASK) >> I3C_DEVICE_CTRL_IBA_INCLUDE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_i2c_present_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_I2C_PRESENT_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_I2C_PRESENT_OFST) & I3C_DEVICE_CTRL_I2C_PRESENT_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_i2c_present_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_I2C_PRESENT_MASK) >> I3C_DEVICE_CTRL_I2C_PRESENT_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_hot_join_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_HOT_JOIN_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_HOT_JOIN_OFST) & I3C_DEVICE_CTRL_HOT_JOIN_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_hot_join_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_HOT_JOIN_MASK) >> I3C_DEVICE_CTRL_HOT_JOIN_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_dma_enable_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_DMA_ENABLE_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_DMA_ENABLE_OFST) & I3C_DEVICE_CTRL_DMA_ENABLE_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_dma_enable_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_DMA_ENABLE_MASK) >> I3C_DEVICE_CTRL_DMA_ENABLE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_abort_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_ABORT_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_ABORT_OFST) & I3C_DEVICE_CTRL_ABORT_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_abort_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_ABORT_MASK) >> I3C_DEVICE_CTRL_ABORT_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_resume_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_RESUME_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_RESUME_OFST) & I3C_DEVICE_CTRL_RESUME_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_resume_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_RESUME_MASK) >> I3C_DEVICE_CTRL_RESUME_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_enable_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL &= ~(I3C_DEVICE_CTRL_ENABLE_MASK);
        regs->DEVICE_CTRL |= ((buf[0] << I3C_DEVICE_CTRL_ENABLE_OFST) & I3C_DEVICE_CTRL_ENABLE_MASK);
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_cfg_enable_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (regs->DEVICE_CTRL & I3C_DEVICE_CTRL_ENABLE_MASK) >> I3C_DEVICE_CTRL_ENABLE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_device_addr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_ADDR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_device_addr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DEVICE_ADDR;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_hw_capability_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->HW_CAPABILITY;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_command_queue_port_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->COMMAND_QUEUE_PORT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_response_queue_port_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->RESPONSE_QUEUE_PORT;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_tx_data_port_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->TX_DATA_PORT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_ibi_queue_status_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->IBI_QUEUE_STATUS;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_queue_thld_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->QUEUE_THLD_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_queue_thld_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->QUEUE_THLD_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_data_buffer_thld_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DATA_BUFFER_THLD_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_data_buffer_thld_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DATA_BUFFER_THLD_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_ibi_queue_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->IBI_QUEUE_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_ibi_queue_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->IBI_QUEUE_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_reset_control_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->RESET_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_reset_control_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->RESET_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_slv_event_status_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SLV_EVENT_STATUS;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_slv_event_status_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SLV_EVENT_STATUS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_status_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->INTR_STATUS;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_status_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->INTR_STATUS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_status_en_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->INTR_STATUS_EN;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_status_en_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->INTR_STATUS_EN = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_signal_en_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->INTR_SIGNAL_EN;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_signal_en_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->INTR_SIGNAL_EN = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_intr_force_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->INTR_FORCE = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_queue_status_level_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);
    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->QUEUE_STATUS_LEVEL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_data_buffer_status_level_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DATA_BUFFER_STATUS_LEVEL;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_present_state_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->PRESENT_STATE;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_device_addr_table_ptr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DEVICE_ADDR_TABLE_POINTER;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_dev_char_table_ptr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DEV_CHAR_TABLE_POINTER;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_dev_char_table_ptr_set_idx(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEV_CHAR_TABLE_POINTER = (buf[0] << I3C_DEV_CHAR_TABLE_PTR_IDX_OFST) & I3C_DEV_CHAR_TABLE_PTR_IDX_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_vendor_specific_reg_ptr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->VENDOR_SPECIFIC_REG_POINTER;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_device_control_ext_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->DEVICE_CTRL_EXTENDED = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_device_control_ext_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->DEVICE_CTRL_EXTENDED;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i3c_od_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_I3C_OD_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i3c_od_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_I3C_OD_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i3c_pp_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_I3C_PP_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i3c_pp_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_I3C_PP_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i2c_fm_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_I2C_FM_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i2c_fm_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_I2C_FM_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i2c_fmp_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_I2C_FMP_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_i2c_fmp_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_I2C_FMP_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_scl_ext_lcnt_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_EXT_LCNT_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_scl_ext_lcnt_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_EXT_LCNT_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_scl_ext_termn_lcnt_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SCL_EXT_TERMN_LCNT_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_scl_ext_termn_lcnt_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SCL_EXT_TERMN_LCNT_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_sda_delay_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->SDA_HOLD_SWITCH_DLY_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_sda_delay_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->SDA_HOLD_SWITCH_DLY_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_bus_free_avail_timing_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        regs->BUS_FREE_AVAIL_TIMING = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_bus_free_avail_timing_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->BUS_FREE_AVAIL_TIMING;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_version_id_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->I3C_VER_ID;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_version_type_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->I3C_VER_TYPE;
        return_value = 0;
    }
    return return_value;
}
int32_t i3c_queue_size_capability_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i3c_regs_t *regs = (i3c_regs_t *)(fd);

    uint32_t *buf = (uint32_t *)arg;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = regs->QUEUE_SIZE_CAPABILITY;
        return_value = 0;
    }
    return return_value;
}

/*
When getting the device address table, pass in the index-1 at arg[0]
*/
int32_t i3c_device_address_table_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;

    uint32_t *buf = (uint32_t *)arg;
    uint32_t entry = buf[0];
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else if ((entry < (uint32_t)1) || (entry > (uint32_t)11)) {
        return_value = -2;
    } else {
        uint32_t *dev_addr_table = (uint32_t *)((uint32_t)(fd) + I3C_DEV_ADDR_TABLE_BASE_BYTE_OFST);
        buf[0] = dev_addr_table[entry - (uint32_t)(1)];
        return_value = 0;
    }
    return return_value;
}

/*
When setting the device address table, pass in the index-1 at arg[0] and value
at arg[1] This requires two 32-bit values to be passed in
*/
int32_t i3c_device_address_table_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;

    uint32_t *buf = (uint32_t *)arg;
    uint32_t entry = buf[0];
    if (length < ((size_t)2 * sizeof(uint32_t))) {
        return_value = -1;
    } else if ((entry < (uint32_t)1) || (entry > (uint32_t)11)) {
        return_value = -2;
    } else {
        uint32_t *dev_addr_table = (uint32_t *)((uint32_t)(fd) + I3C_DEV_ADDR_TABLE_BASE_BYTE_OFST);
        dev_addr_table[entry - (uint32_t)(1)] = buf[1];
        return_value = 0;
    }
    return return_value;
}

/*
When inspecting the device characteristic table, pass in the index-1 at arg[0]
*/
int32_t i3c_device_characteristic_table_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;

    uint32_t *buf = (uint32_t *)arg;
    uint32_t entry = buf[0];
    if (length < ((size_t)(4) * sizeof(uint32_t))) {
        return_value = -1;
    } else if ((entry < (uint32_t)1) || (entry > (uint32_t)11)) {
        return_value = -2;
    } else {
        uint32_t *dev_char_table = (uint32_t *)((uint32_t)(fd) + ((uint32_t)(16) * (entry - (uint32_t)(1))));
        for (uint32_t i = 0; i < (uint32_t)(4); i++) {
            buf[i] = dev_char_table[i];
        }
        return_value = 0;
    }
    return return_value;
}
