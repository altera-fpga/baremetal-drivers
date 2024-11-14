#include "uart.h"
#include "uart_internal.h"
#include "uart_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t uart_devices[] = {{.name = "/dev/uart0", .fd = UART0_BASE, .acquired = 0},
                                      {.name = "/dev/uart1", .fd = UART1_BASE, .acquired = 0}};

int32_t uart_open(const char *path, int32_t flags) {
    int32_t fd = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(uart_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(uart_devices[i].name, path) == 0) {
                if (claim_device(&uart_devices[i])) {
                    fd = uart_devices[i].fd;
                }
            }
        }
        int32_t init_result = uart_init((uintptr_t)fd);
        if (init_result == -1) {
            uart_close(fd);
            fd = -1;
        }
    }
    return fd;
}

int32_t uart_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(uart_devices) / sizeof(device_descriptor_t)); i++) {
            if (uart_devices[i].fd == fd) {
                uart_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t uart_read(int32_t fd, uintptr_t buf, size_t count) { return uart_recv(fd, buf, count, 0); }

size_t uart_recv(int32_t fd, uintptr_t buf, size_t count, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        return_value = uart_recv_internal((uintptr_t)fd, buf, count, flags);
    }
    return return_value;
}

size_t uart_write(int32_t fd, const uintptr_t buf, size_t count) { return uart_send(fd, buf, count, 0); }

size_t uart_send(int32_t fd, const uintptr_t buf, size_t count, int32_t flags) {
    size_t return_value = 0;
    if ((fd == -1) || (((void *)(buf)) == nullptr)) {
        return_value = 0;
    } else {
        return_value = uart_send_internal((uintptr_t)fd, buf, count, flags);
    }
    return return_value;
}

int32_t uart_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((uart_ioctl_op_t)request) {
        case IOCTL_UART_READ_REGS:
            return_value = uart_read_regs(fd, arg, length);
            break;
        case IOCTL_UART_WRITE_REGS:
            return_value = uart_write_regs(fd, arg, length);
            break;
        case IOCTL_UART_BAUD_RATE_DIVISOR_GET:
            return_value = uart_baud_rate_divisor_get(fd, arg, length);
            break;
        case IOCTL_UART_BAUD_RATE_DIVISOR_SET:
            return_value = uart_baud_rate_divisor_set(fd, arg, length);
            break;
        case IOCTL_UART_INTERRUPT_ENABLE_GET:
            return_value = uart_interrupt_enable_get(fd, arg, length);
            break;
        case IOCTL_UART_INTERRUPT_ENABLE_SET:
            return_value = uart_interrupt_enable_set(fd, arg, length);
            break;
        case IOCTL_UART_INTERRUPT_STATUS_GET:
            return_value = uart_interrupt_status_get(fd, arg, length);
            break;
        case IOCTL_UART_LINE_CONTROL_GET:
            return_value = uart_line_control_get(fd, arg, length);
            break;
        case IOCTL_UART_LINE_CONTROL_SET:
            return_value = uart_line_control_set(fd, arg, length);
            break;
        case IOCTL_UART_MODEM_CONTROL_GET:
            return_value = uart_modem_control_get(fd, arg, length);
            break;
        case IOCTL_UART_MODEM_CONTROL_SET:
            return_value = uart_modem_control_set(fd, arg, length);
            break;
        case IOCTL_UART_LINE_STATUS_GET:
            return_value = uart_line_status_get(fd, arg, length);
            break;
        case IOCTL_UART_MODEM_STATUS_GET:
            return_value = uart_modem_status_get(fd, arg, length);
            break;
        case IOCTL_UART_SCRATCH_GET:
            return_value = uart_scratch_get(fd, arg, length);
            break;
        case IOCTL_UART_SCRATCH_SET:
            return_value = uart_scratch_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_RECEIVE_BUFFER_GET:
            return_value = uart_shadow_receive_buffer_get(fd, arg, length);
            break;
        case IOCTL_UART_FIFO_ACCESS_GET:
            return_value = uart_fifo_access_get(fd, arg, length);
            break;
        case IOCTL_UART_FIFO_ACCESS_SET:
            return_value = uart_fifo_access_set(fd, arg, length);
            break;
        case IOCTL_UART_XMIT_FIFO_READ:
            return_value = uart_xmit_fifo_read(fd, arg, length);
            break;
        case IOCTL_UART_RECV_FIFO_WRITE:
            return_value = uart_recv_fifo_write(fd, arg, length);
            break;
        case IOCTL_UART_STATUS_GET:
            return_value = uart_status_get(fd, arg, length);
            break;
        case IOCTL_UART_XMIT_FIFO_LEVEL_GET:
            return_value = uart_xmit_fifo_level_get(fd, arg, length);
            break;
        case IOCTL_UART_RECV_FIFO_LEVEL_GET:
            return_value = uart_recv_fifo_level_get(fd, arg, length);
            break;
        case IOCTL_UART_SW_RESET_SET:
            return_value = uart_sw_reset_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_RTS_GET:
            return_value = uart_shadow_rts_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_RTS_SET:
            return_value = uart_shadow_rts_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_BREAK_CTRL_GET:
            return_value = uart_shadow_break_ctrl_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_BREAK_CTRL_SET:
            return_value = uart_shadow_break_ctrl_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_DMA_MODE_GET:
            return_value = uart_shadow_dma_mode_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_DMA_MODE_SET:
            return_value = uart_shadow_dma_mode_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_FIFO_ENABLE_GET:
            return_value = uart_shadow_fifo_enable_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_FIFO_ENABLE_SET:
            return_value = uart_shadow_fifo_enable_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_RECV_TRIGGER_GET:
            return_value = uart_shadow_recv_trigger_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_RECV_TRIGGER_SET:
            return_value = uart_shadow_recv_trigger_set(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_GET:
            return_value = uart_shadow_tx_empty_trigger_get(fd, arg, length);
            break;
        case IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_SET:
            return_value = uart_shadow_tx_empty_trigger_set(fd, arg, length);
            break;
        case IOCTL_UART_HALT_TX_GET:
            return_value = uart_halt_tx_get(fd, arg, length);
            break;
        case IOCTL_UART_HALT_TX_SET:
            return_value = uart_halt_tx_set(fd, arg, length);
            break;
        case IOCTL_UART_DMA_SW_ACK_SET:
            return_value = uart_dma_sw_ack_set(fd, arg, length);
            break;
        case IOCTL_UART_COMPONENT_PARAMETER_GET:
            return_value = uart_component_parameter_get(fd, arg, length);
            break;
        case IOCTL_UART_COMPONENT_VERSION_GET:
            return_value = uart_component_version_get(fd, arg, length);
            break;
        case IOCTL_UART_COMPONENT_TYPE_GET:
            return_value = uart_component_type_get(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t uart_error(int32_t fd) {
    // Unimplemented -- Errors queried through status registers
    return 0;
}