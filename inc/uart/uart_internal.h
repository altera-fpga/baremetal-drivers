#ifndef UART_INTERNAL_H
#define UART_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

int32_t uart_init(uintptr_t base);
size_t uart_send_internal(uintptr_t base, const uintptr_t buf, size_t count, int32_t flags);
size_t uart_recv_internal(uintptr_t base, uintptr_t buf, size_t count, int32_t flags);

// Function to handle IOCTL_UART_READ_REGS
int32_t uart_read_regs(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_WRITE_REGS
int32_t uart_write_regs(int32_t fd, const uintptr_t data, size_t length);

// Function to handle IOCTL_UART_BAUD_RATE_DIVISOR_GET
int32_t uart_baud_rate_divisor_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_BAUD_RATE_DIVISOR_SET
int32_t uart_baud_rate_divisor_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_INTERRUPT_ENABLE_GET
int32_t uart_interrupt_enable_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_INTERRUPT_ENABLE_SET
int32_t uart_interrupt_enable_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_INTERRUPT_STATUS_GET
int32_t uart_interrupt_status_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_LINE_CONTROL_GET
int32_t uart_line_control_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_LINE_CONTROL_SET
int32_t uart_line_control_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_MODEM_CONTROL_GET
int32_t uart_modem_control_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_MODEM_CONTROL_SET
int32_t uart_modem_control_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_LINE_STATUS_GET
int32_t uart_line_status_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_MODEM_STATUS_GET
int32_t uart_modem_status_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SCRATCH_GET
int32_t uart_scratch_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SCRATCH_SET
int32_t uart_scratch_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_RECEIVE_BUFFER_GET
int32_t uart_shadow_receive_buffer_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_FIFO_ACCESS_GET
int32_t uart_fifo_access_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_FIFO_ACCESS_SET
int32_t uart_fifo_access_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_XMIT_FIFO_READ
int32_t uart_xmit_fifo_read(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_RECV_FIFO_WRITE
int32_t uart_recv_fifo_write(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_STATUS_GET
int32_t uart_status_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_XMIT_FIFO_LEVEL_GET
int32_t uart_xmit_fifo_level_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_RECV_FIFO_LEVEL_GET
int32_t uart_recv_fifo_level_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SW_RESET_SET
int32_t uart_sw_reset_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_RTS_GET
int32_t uart_shadow_rts_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_RTS_SET
int32_t uart_shadow_rts_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_BREAK_CTRL_GET
int32_t uart_shadow_break_ctrl_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_BREAK_CTRL_SET
int32_t uart_shadow_break_ctrl_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_DMA_MODE_GET
int32_t uart_shadow_dma_mode_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_DMA_MODE_SET
int32_t uart_shadow_dma_mode_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_FIFO_ENABLE_GET
int32_t uart_shadow_fifo_enable_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_FIFO_ENABLE_SET
int32_t uart_shadow_fifo_enable_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_RECV_TRIGGER_GET
int32_t uart_shadow_recv_trigger_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_RECV_TRIGGER_SET
int32_t uart_shadow_recv_trigger_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_GET
int32_t uart_shadow_tx_empty_trigger_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_SET
int32_t uart_shadow_tx_empty_trigger_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_HALT_TX_GET
int32_t uart_halt_tx_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_HALT_TX_SET
int32_t uart_halt_tx_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_DMA_SW_ACK_SET
int32_t uart_dma_sw_ack_set(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_COMPONENT_PARAMETER_GET
int32_t uart_component_parameter_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_COMPONENT_VERSION_GET
int32_t uart_component_version_get(int32_t fd, uintptr_t data, size_t length);

// Function to handle IOCTL_UART_COMPONENT_TYPE_GET
int32_t uart_component_type_get(int32_t fd, uintptr_t data, size_t length);
#endif // UART_INTERNAL_H
