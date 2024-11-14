#ifndef DMA_INTERNAL_H
#define DMA_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence DMA controller for an Altera Agilex5e HPS
*/

// Whole register bank access
int32_t dma_read_regs(int32_t fd, uintptr_t args, size_t length);
int32_t dma_write_regs(int32_t fd, uintptr_t args, size_t length);

// Common register access
int32_t dma_get_id_reg(int32_t fd, uintptr_t args);
int32_t dma_get_comp_ver_no_reg(int32_t fd, uintptr_t args);

int32_t dma_set_cfg_reg(int32_t fd, uintptr_t args);
int32_t dma_get_cfg_reg(int32_t fd, uintptr_t args);
int32_t dma_set_chen_enable_reg(int32_t fd, uintptr_t args);
int32_t dma_get_chen_enable_reg(int32_t fd, uintptr_t args);
int32_t dma_get_int_status_reg(int32_t fd, uintptr_t args);

int32_t dma_set_common_int_clear_reg(int32_t fd, uintptr_t args);
int32_t dma_set_common_int_sts_en_reg(int32_t fd, uintptr_t args);
int32_t dma_get_common_int_sts_en_reg(int32_t fd, uintptr_t args);
int32_t dma_set_common_int_sig_en_reg(int32_t fd, uintptr_t args);
int32_t dma_get_common_int_sig_en_reg(int32_t fd, uintptr_t args);
int32_t dma_get_common_int_status_reg(int32_t fd, uintptr_t args);

int32_t dma_set_reset_reg(int32_t fd, uintptr_t args);
int32_t dma_get_reset_reg(int32_t fd, uintptr_t args);
int32_t dma_set_low_power_cfg_reg(int32_t fd, uintptr_t args);
int32_t dma_get_low_power_cfg_reg(int32_t fd, uintptr_t args);

// Channel register access
int32_t dma_ch_set_src_addr_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_src_addr_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_dst_addr_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_dst_addr_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_blk_tran_size_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_blk_tran_size_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_trans_ctl_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_trans_ctl_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_trans_cfg2_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_trans_cfg2_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_linked_list_point_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_linked_list_point_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_status_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_sw_hsk_src_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_sw_hsk_src_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_sw_hsk_dst_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_sw_hsk_dst_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_blk_tfr_resume_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_axi_id_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_axi_id_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_axi_qos_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_axi_qos_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_int_status_en_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_int_status_en_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_int_status_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_int_signal_en_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_get_int_signal_en_reg(int32_t fd, uintptr_t args, int32_t channel);
int32_t dma_ch_set_int_clear_reg(int32_t fd, uintptr_t args, int32_t channel);

#endif // DMA_INTERNAL_H