#ifndef NOC_PROBE_INTERNAL_H
#define NOC_PROBE_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Read from all NoC probe registers.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_read_internal(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Write to all NoC probe registers.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_write_internal(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the atbendpoint_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_atbendpoint_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the atbendpoint_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_atbendpoint_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the atbendpoint_atbid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_atbendpoint_atbid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the atbendpoint_atbid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_atbendpoint_atbid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the atbendpoint_atben register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_atbendpoint_atben_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the atbendpoint_atben register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_atbendpoint_atben_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_faulten register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_faulten_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the errorlogger_0_faulten register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_errorlogger_0_faulten_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errvld register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errvld_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the errorlogger_0_errclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_errorlogger_0_errclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog0 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog0_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog1 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog1_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog3 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog3_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog4 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog4_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog5 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog5_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog6 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog6_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_errlog7 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_errlog7_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the errorlogger_0_stallen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_errorlogger_0_stallen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the errorlogger_0_stallen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_errorlogger_0_stallen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the stpv2converter_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_stpv2converter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the stpv2converter_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_stpv2converter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the stpv2converter_asyncperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_stpv2converter_asyncperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the stpv2converter_asyncperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_stpv2converter_asyncperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the stpv2converter_stpv2en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_stpv2converter_stpv2en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the stpv2converter_stpv2en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_stpv2converter_stpv2en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_tracealarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_tracealarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statgo register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_statalarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statalarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_0_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_1_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_2_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_probe_counters_3_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_tracealarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_tracealarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statgo register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_statalarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statalarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_0_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_1_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_2_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_probe_counters_3_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_tracealarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_tracealarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statgo register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_statalarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statalarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_0_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_1_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_2_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the soc2fpga_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_soc2fpga_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the soc2fpga_probe_counters_3_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_soc2fpga_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_thresholds_0_0 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_thresholds_0_0 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_thresholds_0_1 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_thresholds_0_1 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_thresholds_0_2 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_thresholds_0_2 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_overflowstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_overflowstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_overflowreset register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_overflowreset_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_pendingeventmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_pendingeventmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatprofiler_prescaler register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatprofiler_prescaler register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_mainctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_mainctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_cfgctl register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_cfgctl_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filterlut register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filterlut_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_tracealarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_tracealarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_tracealarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_tracealarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_tracealarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_tracealarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statperiod register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statperiod_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statgo register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statgo_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statalarmmin register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statalarmmin_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statalarmmax register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statalarmmax_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_statalarmstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_statalarmstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statalarmclr register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statalarmclr_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_statalarmen register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_statalarmen_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_0_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_0_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_routeidbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_routeidbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_routeidmask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_routeidmask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_windowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_windowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_status register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_status_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_length register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_length_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_filters_1_urgency register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_filters_1_urgency_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_0_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_0_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_0_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_0_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_0_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_0_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_1_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_1_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_1_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_1_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_1_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_1_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_2_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_2_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_2_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_2_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_2_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_2_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_3_src register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_3_src_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_probe_counters_3_alarmmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_probe_counters_3_alarmmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_probe_counters_3_val register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_probe_counters_3_val_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_en register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_en_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_thresholds_0_0 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_thresholds_0_0 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_0_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_thresholds_0_1 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_thresholds_0_1 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_1_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_thresholds_0_2 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_thresholds_0_2 register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_thresholds_0_2_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_overflowstatus register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_overflowstatus_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_overflowreset register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_overflowreset_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_pendingeventmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_pendingeventmode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_pendingeventmode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatprofiler_prescaler register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatprofiler_prescaler register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatprofiler_prescaler_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the ccu_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_ccu_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the ccu_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_ccu_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the dma_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_dma_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the dma_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_dma_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the dma_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_dma_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the dma_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_dma_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the dma_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_dma_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the dma_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_dma_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the sdm_qosgenerator_priority register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_sdm_qosgenerator_priority_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the sdm_qosgenerator_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_sdm_qosgenerator_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the sdm_qosgenerator_bandwidth register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_sdm_qosgenerator_bandwidth_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the sdm_qosgenerator_saturation register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_sdm_qosgenerator_saturation_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the sdm_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_sdm_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the sdm_qosgenerator_extcontrol register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_sdm_qosgenerator_extcontrol_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_addrwindowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_addrwindowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_userbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_userbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_usermask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_usermask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_userbasehigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_userbasehigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the emac_transactionstatfilter_usermaskhigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_emac_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the emac_transactionstatfilter_usermaskhigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_emac_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_id_coreid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_id_coreid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_id_revisionid register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_id_revisionid_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_mode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_mode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_addrbase_low register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_addrbase_low_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_addrbase_high register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_addrbase_high_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_addrwindowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_addrwindowsize register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_addrwindowsize_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_opcode register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_opcode_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_userbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_userbase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_userbase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_usermask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_usermask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_usermask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_securitybase register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_securitybase_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_securitymask register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_securitymask_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_userbasehigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_userbasehigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_userbasehigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Get the io_transactionstatfilter_usermaskhigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Buffer to be filled by register data.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_get_io_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length);

/**
 * @brief Set the io_transactionstatfilter_usermaskhigh register.
 *
 * @param fd The file descriptor returned by a previous noc_probe_open() call.
 * @param buffer Data to send to the register.
 * @param length Length of buffer.
 * @return 0 on success or -1 on failure.
 */
int32_t noc_probe_set_io_transactionstatfilter_usermaskhigh_reg(int32_t fd, uintptr_t buffer, size_t length);

#endif // NOC_PROBE_INTERNAL_H
