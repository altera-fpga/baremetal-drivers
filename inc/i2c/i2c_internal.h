#ifndef I2C_INTERNAL_H
#define I2C_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

size_t i2c_transmit(uintptr_t base, uintptr_t buffer, size_t length);
size_t i2c_receive(uintptr_t base, uintptr_t buffer, size_t length);
uint32_t i2c_get_error_state(uintptr_t base);
uint32_t i2c_clear_error_state(uintptr_t base);

int32_t i2c_regs_read(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_regs_write(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_con(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_master_mode(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_master_mode(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_target_addr(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_intstat(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_intstat_raw(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_intmask(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_intmask(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_intclr(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_enable(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_enable(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_status(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_tx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_tx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_tx_fifo_lvl(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_rx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_rx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_rx_fifo_lvl(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_tenbit_addr_mode(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_smbus_mode(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_dma_mode(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_dma_tx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_dma_tx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_dma_rx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_dma_rx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_std_scl_hightime(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_std_scl_lowtime(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_fast_scl_hightime(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_fast_scl_lowtime(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_tx_sda_hold(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_tx_sda_hold(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_rx_sda_hold(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_rx_sda_hold(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_sda_setup(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_sda_setup(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_general_call_enable(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_general_call_ack(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_slave_nack(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_clear_abort(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_aborts(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_set_spike_suppression(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_spike_suppression(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_clear_restart_detect(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_enable_status(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_param(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_version(uintptr_t base, uintptr_t arg, size_t length);
int32_t i2c_get_type(uintptr_t base, uintptr_t arg, size_t length);

#endif
