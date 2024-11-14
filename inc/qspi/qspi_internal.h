#ifndef QSPI_INTERNAL_H
#define QSPI_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence QSPI controller for an Altera Agilex5e HPS
*/
// Send and receive
size_t qspi_recv_internal(int32_t fd, uintptr_t buf, size_t size, int32_t flags);
size_t qspi_send_internal(int32_t fd, uintptr_t buf, size_t size, int32_t flags);

// Whole register bank access
int32_t qspi_read_regs(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_write_regs(int32_t fd, uintptr_t args, size_t length);

// CFG whole reg access
int32_t qspi_set_cfg_reg(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_cfg_reg(int32_t fd, uintptr_t args, size_t length);

// CFG field access
int32_t qspi_set_baud_rate_div(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_baud_rate_div(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_enable(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_enable(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_clkpol(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_cklpol(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_clkphase(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_clkphase(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_cs_decode(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_cs_decode(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_cs(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_cs(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_write_protect_pin(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_write_protect_pin(int32_t fd, uintptr_t args, size_t length);

// External timing settings
int32_t qspi_set_read_params(int32_t fd, uintptr_t args,
                             size_t length); // devrd
int32_t qspi_get_read_params(int32_t fd, uintptr_t args,
                             size_t length); // devrd
int32_t qspi_set_write_params(int32_t fd, uintptr_t args,
                              size_t length); // devwr
int32_t qspi_get_write_params(int32_t fd, uintptr_t args,
                              size_t length); // devwr
int32_t qspi_set_cs_delays(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_cs_delays(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_read_data_capture_dly(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_read_data_capture_dly(int32_t fd, uintptr_t args, size_t length);

// Attached flash device size info
int32_t qspi_set_device_size_params(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_device_size_params(int32_t fd, uintptr_t args, size_t length);

// Direct mode subset
int32_t qspi_set_indirect_addr_span(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_addr_span(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_base_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_base_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_dma_cfg(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_dma_cfg(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_remap_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_remap_addr(int32_t fd, uintptr_t args, size_t length);

// Mode bits
int32_t qspi_set_mode_bits(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_mode_bits(int32_t fd, uintptr_t args, size_t length);

// Current SRAM fill level inspection
int32_t qspi_get_sram_fill_lvl(int32_t fd, uintptr_t args, size_t length);

// interrupt control and status
int32_t qspi_set_irq_txthresh(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_irq_txthresh(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_irq_rxthresh(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_irq_rxthresh(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_irqstat(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_irqstat(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_irqmask(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_irqmask(int32_t fd, uintptr_t args, size_t length);

// Write protect subset
int32_t qspi_set_wrprot(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_wrprot(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_wrprot_low(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_wrprot_low(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_wrprot_high(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_wrprot_high(int32_t fd, uintptr_t args, size_t length);

// Indirect read subset
int32_t qspi_set_indirect_read(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_read(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_rd_watermark(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_rd_watermark(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_rd_start_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_rd_start_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_rd_count(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_rd_count(int32_t fd, uintptr_t args, size_t length);

// Indirect write subset
int32_t qspi_set_indirect_write(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_write(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_wr_watermark(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_wr_watermark(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_wr_start_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_wr_start_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_indirect_wr_count(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_indirect_wr_count(int32_t fd, uintptr_t args, size_t length);

// Flash Command Subset
int32_t qspi_set_flash_cmd(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_flash_cmd(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_flash_cmd_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_flash_cmd_addr(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_flash_cmd_rd_data(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_set_flash_cmd_wr_data(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_flash_cmd_wr_data(int32_t fd, uintptr_t args, size_t length);
int32_t qspi_get_module_id(int32_t fd, uintptr_t args, size_t length);

#endif // QSPI_INTERNAL_H