/*
This source file defines a POSIX compliant API for controlling a synopsis
designware SPI master controller. It uses the register definitions in
spi_regs.h.

These functions call the internal definitions in spi_internal.h and
spi_internal.c

It also implements the driver discovery mechanism for the SPI master controller.
*/

#include "spi.h"
#include "device.h"
#include "spi_internal.h"
#include "spi_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

device_descriptor_t spi_devices[] = {
    {.name = "/dev/spim0", .fd = SPIM0_BASE, .acquired = 0},
    {.name = "/dev/spim1", .fd = SPIM1_BASE, .acquired = 0},
    {.name = "/dev/spis0", .fd = SPIS0_BASE, .acquired = 0},
    {.name = "/dev/spis1", .fd = SPIS1_BASE, .acquired = 0},
};

int32_t spi_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(spi_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(spi_devices[i].name, name) == 0) {
                if (claim_device(&spi_devices[i])) {
                    fd = spi_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t spi_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(spi_devices) / sizeof(device_descriptor_t)); i++) {
            if (spi_devices[i].fd == fd) {
                spi_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t spi_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        uintptr_t base = (uintptr_t)fd;
        return_value = spi_receive(base, buf, size);
    }
    return return_value;
}

size_t spi_read(int32_t fd, uintptr_t buf, size_t size) { return spi_recv(fd, buf, size, 0); }

size_t spi_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        uintptr_t base = (uintptr_t)fd;
        return_value = spi_transmit(base, buf, size);
    }
    return return_value;
}

size_t spi_write(int32_t fd, const uintptr_t buf, size_t size) { return spi_send(fd, buf, size, 0); }

int32_t spi_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((spi_ioctl_op_t)request) {
        case (IOCTL_SPI_REGS_READ):
            return_value = spi_regs_read(fd, arg, length);
            break;
        case (IOCTL_SPI_REGS_WRITE):
            return_value = spi_regs_write(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_FRAME_FORMAT):
            return_value = spi_set_frame_format(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_FRAME_FORMAT):
            return_value = spi_get_frame_format(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_FRAME_SIZE):
            return_value = spi_set_frame_size(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_FRAME_SIZE):
            return_value = spi_get_frame_size(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_CONTROL_FRAME_SIZE):
            return_value = spi_set_control_frame_size(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_CONTROL_FRAME_SIZE):
            return_value = spi_get_control_frame_size(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_TRANSFER_MODE):
            return_value = spi_set_transfer_mode(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_TRANSFER_MODE):
            return_value = spi_get_transfer_mode(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_CLOCK_POLARITY):
            return_value = spi_set_clock_polarity(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_CLOCK_POLARITY):
            return_value = spi_get_clock_polarity(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_CLOCK_PHASE):
            return_value = spi_set_clock_phase(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_CLOCK_PHASE):
            return_value = spi_get_clock_phase(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_NUM_DATA_FRAMES):
            return_value = spi_set_num_data_frames(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_NUM_DATA_FRAMES):
            return_value = spi_get_num_data_frames(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_SSI_ENABLE):
            return_value = spi_set_ssi_enable(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_SSI_ENABLE):
            return_value = spi_get_ssi_enable(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_MW_TRANSFER_MODE):
            return_value = spi_set_mw_transfer_mode(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_MW_TRANSFER_MODE):
            return_value = spi_get_mw_transfer_mode(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_MW_CONTROL):
            return_value = spi_set_mw_control(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_MW_CONTROL):
            return_value = spi_get_mw_control(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_MW_HANDSHAKE):
            return_value = spi_set_mw_handshake(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_MW_HANDSHAKE):
            return_value = spi_get_mw_handshake(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_CS):
            return_value = spi_set_cs(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_CS):
            return_value = spi_get_cs(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_BAUD_RATE):
            return_value = spi_set_baud_rate(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_BAUD_RATE):
            return_value = spi_get_baud_rate(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_TX_FIFO_THRESHOLD):
            return_value = spi_set_tx_fifo_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_TX_FIFO_THRESHOLD):
            return_value = spi_get_tx_fifo_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_RX_FIFO_THRESHOLD):
            return_value = spi_set_rx_fifo_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_RX_FIFO_THRESHOLD):
            return_value = spi_get_rx_fifo_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_TX_FIFO_LEVEL):
            return_value = spi_get_tx_fifo_level(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_RX_FIFO_LEVEL):
            return_value = spi_get_rx_fifo_level(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_STATUS):
            return_value = spi_get_status(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_INTERRUPT_MASK):
            return_value = spi_get_interrupt_mask(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_INTERRUPT_MASK):
            return_value = spi_set_interrupt_mask(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_INTERRUPT_STATUS):
            return_value = spi_get_interrupt_status(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_RAW_INTERRUPT_STATUS):
            return_value = spi_get_raw_interrupt_status(fd, arg, length);
            break;
        case (IOCTL_SPI_CLEAR_TX_OVERFLOW_INTERRUPT):
            return_value = spi_clear_tx_overflow_interrupt(fd, arg, length);
            break;
        case (IOCTL_SPI_CLEAR_RX_OVERFLOW_INTERRUPT):
            return_value = spi_clear_rx_overflow_interrupt(fd, arg, length);
            break;
        case (IOCTL_SPI_CLEAR_RX_UNDERFLOW_INTERRUPT):
            return_value = spi_clear_rx_underflow_interrupt(fd, arg, length);
            break;
        case (IOCTL_SPI_CLEAR_MULTI_MASTER_INTERRUPT):
            return_value = spi_clear_multi_master_interrupt(fd, arg, length);
            break;
        case (IOCTL_SPI_CLEAR_INTERRUPT):
            return_value = spi_clear_interrupt(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_DMA_CONTROL):
            return_value = spi_get_dma_control(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_DMA_CONTROL):
            return_value = spi_set_dma_control(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_DMA_TX_THRESHOLD):
            return_value = spi_get_dma_tx_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_DMA_TX_THRESHOLD):
            return_value = spi_set_dma_tx_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_DMA_RX_THRESHOLD):
            return_value = spi_get_dma_rx_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_DMA_RX_THRESHOLD):
            return_value = spi_set_dma_rx_threshold(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_ID):
            return_value = spi_get_id(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_VERSION):
            return_value = spi_get_version(fd, arg, length);
            break;
        case (IOCTL_SPI_GET_RX_SAMPLE_DLY):
            return_value = spi_get_rx_sample_dly(fd, arg, length);
            break;
        case (IOCTL_SPI_SET_RX_SAMPLE_DLY):
            return_value = spi_set_rx_sample_dly(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t spi_error(int32_t fd) {
    int32_t return_value = -1;
    if (fd == -1) {
        return_value = -1;
    } else {
        uintptr_t base = (uintptr_t)fd;
        return_value = spi_get_error_state(base);
    }
    return return_value;
}