#ifndef spi_INTERNAL_H
#define spi_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

size_t spi_transmit(uintptr_t base, uintptr_t buffer, size_t length);
size_t spi_receive(uintptr_t base, uintptr_t buffer, size_t length);
int32_t spi_get_error_state(uintptr_t base);

int32_t spi_regs_read(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_regs_write(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_frame_format(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_frame_format(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_frame_size(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_frame_size(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_control_frame_size(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_control_frame_size(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_transfer_mode(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_transfer_mode(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_clock_polarity(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_clock_polarity(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_clock_phase(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_clock_phase(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_num_data_frames(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_num_data_frames(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_ssi_enable(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_ssi_enable(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_mw_transfer_mode(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_mw_transfer_mode(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_mw_control(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_mw_control(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_mw_handshake(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_mw_handshake(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_cs(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_cs(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_baud_rate(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_baud_rate(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_tx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_tx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_rx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_rx_fifo_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_tx_fifo_level(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_rx_fifo_level(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_status(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_interrupt_mask(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_interrupt_mask(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_interrupt_status(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_raw_interrupt_status(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_clear_tx_overflow_interrupt(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_clear_rx_overflow_interrupt(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_clear_rx_underflow_interrupt(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_clear_multi_master_interrupt(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_clear_interrupt(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_dma_control(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_dma_control(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_dma_tx_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_dma_tx_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_dma_rx_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_dma_rx_threshold(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_id(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_version(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_get_rx_sample_dly(int32_t fd, uintptr_t arg, size_t length);
int32_t spi_set_rx_sample_dly(int32_t fd, uintptr_t arg, size_t length);

#endif // spi_INTERNAL_H
