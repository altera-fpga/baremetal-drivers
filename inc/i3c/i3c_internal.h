#ifndef DRIVERS_INC_I3C_H__
#define DRIVERS_INC_I3C_H__

#ifdef __cplusplus
extern "C" {
#endif

// Includes
#include <stddef.h>
#include <stdint.h>
// Macros

// Possible values for DEV_OPERATION_MODE field
// In Secondary Master mode, this can configure an I3C bus to be in Initiator or
// Target mode.
#define I3C_DEV_OPERATION_MODE_I 0
#define I3C_DEV_OPERATION_MODE_T 1

// Public APIs
int32_t i3c_internal_init(int32_t fd);

int32_t i3c_internal_send(int32_t fd, uint32_t *data, uint32_t data_length, uint32_t cmd_info);
int32_t i3c_internal_recv(int32_t fd, uint32_t *data, uint32_t data_length, uint32_t cmd_info);

// IOCTLs
int32_t i3c_read_regs(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_write_regs(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_iba_inc_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_iba_inc_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_i2c_present_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_i2c_present_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_hot_join_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_hot_join_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_dma_enable_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_dma_enable_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_abort_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_abort_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_resume_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_resume_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_enable_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_cfg_enable_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_addr_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_addr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_hw_capability_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_command_queue_port_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_response_queue_port_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_tx_data_port_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_ibi_queue_status_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_queue_thld_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_queue_thld_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_data_buffer_thld_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_data_buffer_thld_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_ibi_queue_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_ibi_queue_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_reset_control_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_reset_control_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_slv_event_status_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_slv_event_status_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_status_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_status_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_status_en_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_status_en_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_signal_en_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_signal_en_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_intr_force_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_queue_status_level_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_data_buffer_status_level_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_present_state_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_addr_table_ptr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_dev_char_table_ptr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_dev_char_table_ptr_set_idx(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_vendor_specific_reg_ptr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_control_ext_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_control_ext_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i3c_od_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i3c_od_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i3c_pp_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i3c_pp_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i2c_fm_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i2c_fm_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i2c_fmp_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_i2c_fmp_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_scl_ext_lcnt_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_scl_ext_lcnt_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_scl_ext_termn_lcnt_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_scl_ext_termn_lcnt_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_sda_delay_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_sda_delay_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_bus_free_avail_timing_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_bus_free_avail_timing_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_version_id_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_version_type_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_queue_size_capability_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_address_table_set(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_address_table_get(int32_t fd, uintptr_t arg, size_t length);
int32_t i3c_device_characteristic_table_get(int32_t fd, uintptr_t arg, size_t length);

#ifdef __cplusplus
}
#endif

#endif // DRIVERS_INC_I3C_H__
