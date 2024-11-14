#include "i2c.h"
#include "i2c_internal.h"
#include "i2c_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t i2c_devices[] = {{.name = "/dev/i2c0", .fd = I2C0_BASE, .acquired = 0},
                                     {.name = "/dev/i2c1", .fd = I2C1_BASE, .acquired = 0}};

int32_t i2c_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(i2c_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(i2c_devices[i].name, name) == 0) {
                if (claim_device(&i2c_devices[i])) {
                    fd = i2c_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t i2c_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(i2c_devices) / sizeof(device_descriptor_t)); i++) {
            if (i2c_devices[i].fd == fd) {
                i2c_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t i2c_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        uintptr_t base = (uintptr_t)fd;
        return_value = i2c_receive(base, buf, size);
    }
    return return_value;
}

size_t i2c_read(int32_t fd, uintptr_t buf, size_t size) { return i2c_recv(fd, buf, size, 0); }

size_t i2c_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        uintptr_t base = (uintptr_t)fd;
        return_value = i2c_transmit(base, buf, size);
    }
    return return_value;
}

size_t i2c_write(int32_t fd, const uintptr_t buf, size_t size) { return i2c_send(fd, buf, size, 0); }

int32_t i2c_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uintptr_t base = (uintptr_t)fd;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((i2c_ioctl_op_t)request) {
        case (IOCTL_I2C_REGS_READ):
            return_value = i2c_regs_read(base, arg, length);
            break;
        case (IOCTL_I2C_REGS_WRITE):
            return_value = i2c_regs_write(base, arg, length);
            break;
        case (IOCTL_I2C_SET_MASTER_MODE):
            return_value = i2c_set_master_mode(base, arg, length);
            break;
        case (IOCTL_I2C_GET_MASTER_MODE):
            return_value = i2c_get_master_mode(base, arg, length);
            break;
        case (IOCTL_I2C_SET_TARGET_ADDR):
            return_value = i2c_set_target_addr(base, arg, length);
            break;
        case (IOCTL_I2C_GET_INTSTAT):
            return_value = i2c_get_intstat(base, arg, length);
            break;
        case (IOCTL_I2C_GET_INTSTAT_RAW):
            return_value = i2c_get_intstat_raw(base, arg, length);
            break;
        case (IOCTL_I2C_GET_INTMASK):
            return_value = i2c_get_intmask(base, arg, length);
            break;
        case (IOCTL_I2C_SET_INTMASK):
            return_value = i2c_set_intmask(base, arg, length);
            break;
        case (IOCTL_I2C_INTCLR):
            return_value = i2c_intclr(base, arg, length);
            break;
        case (IOCTL_I2C_SET_ENABLE):
            return_value = i2c_set_enable(base, arg, length);
            break;
        case (IOCTL_I2C_GET_ENABLE):
            return_value = i2c_get_enable(base, arg, length);
            break;
        case (IOCTL_I2C_GET_STATUS):
            return_value = i2c_get_status(base, arg, length);
            break;
        case (IOCTL_I2C_SET_TX_FIFO_THRESH):
            return_value = i2c_set_tx_fifo_thresh(base, arg, length);
            break;
        case (IOCTL_I2C_GET_TX_FIFO_THRESH):
            return_value = i2c_get_tx_fifo_thresh(base, arg, length);
            break;
        case (IOCTL_I2C_GET_TX_FIFO_LVL):
            return_value = i2c_get_tx_fifo_lvl(base, arg, length);
            break;
        case (IOCTL_I2C_SET_RX_FIFO_TRESH):
            return_value = i2c_set_rx_fifo_thresh(base, arg, length);
            break;
        case (IOCTL_I2C_GET_RX_FIFO_THRESH):
            return_value = i2c_get_rx_fifo_thresh(base, arg, length);
            break;
        case (IOCTL_I2C_GET_RX_FIFO_LVL):
            return_value = i2c_get_rx_fifo_lvl(base, arg, length);
            break;
        case (IOCTL_I2C_SET_TENBIT_ADDR_MODE):
            return_value = i2c_set_tenbit_addr_mode(base, arg, length);
            break;
        case (IOCTL_I2C_SET_DMA_MODE):
            return_value = i2c_set_dma_mode(base, arg, length);
            break;
        case (IOCTL_I2C_SET_DMA_TX_FIFO_TRIGGER_LEVEL):
            return_value = i2c_set_dma_tx_fifo_trigger_level(base, arg, length);
            break;
        case (IOCTL_I2C_GET_DMA_TX_FIFO_TRIGGER_LEVEL):
            return_value = i2c_get_dma_tx_fifo_trigger_level(base, arg, length);
            break;
        case (IOCTL_I2C_SET_DMA_RX_FIFO_TRIGGER_LEVEL):
            return_value = i2c_set_dma_rx_fifo_trigger_level(base, arg, length);
            break;
        case (IOCTL_I2C_GET_DMA_RX_FIFO_TRIGGER_LEVEL):
            return_value = i2c_get_dma_rx_fifo_trigger_level(base, arg, length);
            break;
        case (IOCTL_I2C_SET_STD_SCL_HIGHTIME):
            return_value = i2c_set_std_scl_hightime(base, arg, length);
            break;
        case (IOCTL_I2C_SET_STD_SCL_LOWTIME):
            return_value = i2c_set_std_scl_lowtime(base, arg, length);
            break;
        case (IOCTL_I2C_SET_FAST_SCL_HIGHTIME):
            return_value = i2c_set_fast_scl_hightime(base, arg, length);
            break;
        case (IOCTL_I2C_SET_FAST_SCL_LOWTIME):
            return_value = i2c_set_fast_scl_lowtime(base, arg, length);
            break;
        case (IOCTL_I2C_SET_TX_SDA_HOLD):
            return_value = i2c_set_tx_sda_hold(base, arg, length);
            break;
        case (IOCLT_I2C_GET_TX_SDA_HOLD):
            return_value = i2c_get_tx_sda_hold(base, arg, length);
            break;
        case (IOCTL_I2C_SET_RX_SDA_HOLD):
            return_value = i2c_set_rx_sda_hold(base, arg, length);
            break;
        case (IOCTL_I2C_GET_RX_SDA_HOLD):
            return_value = i2c_get_rx_sda_hold(base, arg, length);
            break;
        case (IOCTL_I2C_SET_SDA_SETUP):
            return_value = i2c_set_sda_setup(base, arg, length);
            break;
        case (IOCTL_I2C_GET_SDA_SETUP):
            return_value = i2c_get_sda_setup(base, arg, length);
            break;
        case (IOCTL_I2C_SET_GENERAL_CALL_ENABLE):
            return_value = i2c_set_general_call_enable(base, arg, length);
            break;
        case (IOCTL_I2C_SET_GENERAL_CALL_ACK):
            return_value = i2c_set_general_call_ack(base, arg, length);
            break;
        case (IOCTL_I2C_SET_SLAVE_NACK):
            return_value = i2c_set_slave_nack(base, arg, length);
            break;
        case (IOCTL_I2C_CLR_ABORT):
            return_value = i2c_clear_abort(base, arg, length);
            break;
        case (IOCTL_I2C_GET_ABORTS):
            return_value = i2c_get_aborts(base, arg, length);
            break;
        case (IOCTL_I2C_SET_SPIKE_SUPPRESSION):
            return_value = i2c_set_spike_suppression(base, arg, length);
            break;
        case (IOCTL_I2C_GET_SPIKE_SUPPRESSION):
            return_value = i2c_get_spike_suppression(base, arg, length);
            break;
        case (IOCTL_I2C_CLR_RESTART_DETECT):
            return_value = i2c_clear_restart_detect(base, arg, length);
            break;
        case (IOCTL_I2C_GET_ENABLE_STATUS):
            return_value = i2c_get_enable_status(base, arg, length);
            break;
        case (IOCTL_I2C_GET_PARAM):
            return_value = i2c_get_param(base, arg, length);
            break;
        case (IOCTL_I2C_GET_VERSION):
            return_value = i2c_get_version(base, arg, length);
            break;
        case (IOCTL_I2C_GET_TYPE):
            return_value = i2c_get_type(base, arg, length);
            break;
        default:
            return_value = -3;
            break;
        }
    }
    return return_value;
}

int32_t i2c_error(int32_t fd) {
    uint32_t error_value = (uint32_t)(0);
    error_value = i2c_get_error_state((uintptr_t)fd);
    if (error_value != (uint32_t)0) {
        i2c_clear_error_state((uintptr_t)fd);
    } else {
        i2c_ioctl(fd, (int32_t)IOCTL_I2C_GET_ENABLE_STATUS, (uintptr_t)(&error_value), sizeof(uint32_t));
    }
    return (int32_t)error_value;
}