#include "noc_probe.h"
#include "device.h"
#include "noc_probe_internal.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t noc_probe_devices[] = {{.name = "/dev/noc_probe0", .fd = NOC_PROBE_BASE, .acquired = 0}};

int32_t noc_probe_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != NULL) {
        for (uint32_t i = 0; i < (sizeof(noc_probe_devices) / sizeof(device_descriptor_t)); ++i) {
            if (strcmp(noc_probe_devices[i].name, path) == 0) {
                if (claim_device(&noc_probe_devices[i])) {
                    return_value = noc_probe_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

int32_t noc_probe_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(noc_probe_devices) / sizeof(device_descriptor_t)); i++) {
            if (noc_probe_devices[i].fd == fd) {
                noc_probe_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t noc_probe_read(int32_t fd, uintptr_t buffer, size_t length) { return noc_probe_recv(fd, buffer, length, 0); }

size_t noc_probe_write(int32_t fd, uintptr_t buffer, size_t length) { return noc_probe_send(fd, buffer, length, 0); }

size_t noc_probe_recv(int32_t fd, uintptr_t buffer, size_t length, int32_t flags) { return 0; }

size_t noc_probe_send(int32_t fd, uintptr_t buffer, size_t length, int32_t flags) { return 0; }

int32_t noc_probe_ioctl(int32_t fd, int32_t operation, uintptr_t buffer, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || ((void *)buffer == NULL)) {
        return_value = -1;
    } else {
        switch ((noc_probe_ioctl_t)operation) {
        case IOCTL_NOC_PROBE_READ_REGS:
            return_value = noc_probe_read_internal(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_WRITE_REGS:
            return_value = noc_probe_write_internal(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ATBENDPOINT_ID_COREID:
            return_value = noc_probe_get_atbendpoint_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ATBENDPOINT_ID_REVISIONID:
            return_value = noc_probe_get_atbendpoint_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ATBENDPOINT_ATBID:
            return_value = noc_probe_get_atbendpoint_atbid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_ATBENDPOINT_ATBID:
            return_value = noc_probe_set_atbendpoint_atbid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ATBENDPOINT_ATBEN:
            return_value = noc_probe_get_atbendpoint_atben_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_ATBENDPOINT_ATBEN:
            return_value = noc_probe_set_atbendpoint_atben_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ID_COREID:
            return_value = noc_probe_get_errorlogger_0_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ID_REVISIONID:
            return_value = noc_probe_get_errorlogger_0_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_FAULTEN:
            return_value = noc_probe_get_errorlogger_0_faulten_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_ERRORLOGGER_0_FAULTEN:
            return_value = noc_probe_set_errorlogger_0_faulten_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRVLD:
            return_value = noc_probe_get_errorlogger_0_errvld_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_ERRORLOGGER_0_ERRCLR:
            return_value = noc_probe_set_errorlogger_0_errclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG0:
            return_value = noc_probe_get_errorlogger_0_errlog0_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG1:
            return_value = noc_probe_get_errorlogger_0_errlog1_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG3:
            return_value = noc_probe_get_errorlogger_0_errlog3_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG4:
            return_value = noc_probe_get_errorlogger_0_errlog4_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG5:
            return_value = noc_probe_get_errorlogger_0_errlog5_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG6:
            return_value = noc_probe_get_errorlogger_0_errlog6_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG7:
            return_value = noc_probe_get_errorlogger_0_errlog7_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_STALLEN:
            return_value = noc_probe_get_errorlogger_0_stallen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_ERRORLOGGER_0_STALLEN:
            return_value = noc_probe_set_errorlogger_0_stallen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_STPV2CONVERTER_ID_COREID:
            return_value = noc_probe_get_stpv2converter_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_STPV2CONVERTER_ID_REVISIONID:
            return_value = noc_probe_get_stpv2converter_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_STPV2CONVERTER_ASYNCPERIOD:
            return_value = noc_probe_get_stpv2converter_asyncperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_STPV2CONVERTER_ASYNCPERIOD:
            return_value = noc_probe_set_stpv2converter_asyncperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_STPV2CONVERTER_STPV2EN:
            return_value = noc_probe_get_stpv2converter_stpv2en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_STPV2CONVERTER_STPV2EN:
            return_value = noc_probe_set_stpv2converter_stpv2en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_ID_COREID:
            return_value = noc_probe_get_ccu_probe_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_ID_REVISIONID:
            return_value = noc_probe_get_ccu_probe_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_MAINCTL:
            return_value = noc_probe_get_ccu_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_MAINCTL:
            return_value = noc_probe_set_ccu_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_CFGCTL:
            return_value = noc_probe_get_ccu_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_CFGCTL:
            return_value = noc_probe_set_ccu_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERLUT:
            return_value = noc_probe_get_ccu_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERLUT:
            return_value = noc_probe_set_ccu_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_TRACEALARMEN:
            return_value = noc_probe_get_ccu_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_TRACEALARMEN:
            return_value = noc_probe_set_ccu_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_TRACEALARMSTATUS:
            return_value = noc_probe_get_ccu_probe_tracealarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_TRACEALARMCLR:
            return_value = noc_probe_set_ccu_probe_tracealarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_STATPERIOD:
            return_value = noc_probe_get_ccu_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATPERIOD:
            return_value = noc_probe_set_ccu_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATGO:
            return_value = noc_probe_set_ccu_probe_statgo_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMMIN:
            return_value = noc_probe_get_ccu_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMMIN:
            return_value = noc_probe_set_ccu_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMMAX:
            return_value = noc_probe_get_ccu_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMMAX:
            return_value = noc_probe_set_ccu_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMSTATUS:
            return_value = noc_probe_get_ccu_probe_statalarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMCLR:
            return_value = noc_probe_set_ccu_probe_statalarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMEN:
            return_value = noc_probe_get_ccu_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMEN:
            return_value = noc_probe_set_ccu_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_get_ccu_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_set_ccu_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_get_ccu_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_set_ccu_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_get_ccu_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_set_ccu_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_get_ccu_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_set_ccu_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_get_ccu_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_set_ccu_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_get_ccu_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_set_ccu_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_get_ccu_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_set_ccu_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_get_ccu_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_set_ccu_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_get_ccu_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_set_ccu_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_get_ccu_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_set_ccu_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_get_ccu_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_set_ccu_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_get_ccu_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_set_ccu_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_get_ccu_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_set_ccu_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_get_ccu_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_set_ccu_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_get_ccu_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_set_ccu_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_get_ccu_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_set_ccu_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_get_ccu_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_set_ccu_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_get_ccu_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_set_ccu_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_get_ccu_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_set_ccu_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_get_ccu_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_set_ccu_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_get_ccu_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_set_ccu_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_get_ccu_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_set_ccu_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_get_ccu_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_set_ccu_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_get_ccu_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_set_ccu_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_VAL:
            return_value = noc_probe_get_ccu_probe_counters_0_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_get_ccu_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_set_ccu_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_get_ccu_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_set_ccu_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_VAL:
            return_value = noc_probe_get_ccu_probe_counters_1_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_get_ccu_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_set_ccu_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_get_ccu_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_set_ccu_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_VAL:
            return_value = noc_probe_get_ccu_probe_counters_2_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_get_ccu_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_set_ccu_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_get_ccu_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_set_ccu_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_VAL:
            return_value = noc_probe_get_ccu_probe_counters_3_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_ID_COREID:
            return_value = noc_probe_get_emac_probe_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_ID_REVISIONID:
            return_value = noc_probe_get_emac_probe_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_MAINCTL:
            return_value = noc_probe_get_emac_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_MAINCTL:
            return_value = noc_probe_set_emac_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_CFGCTL:
            return_value = noc_probe_get_emac_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_CFGCTL:
            return_value = noc_probe_set_emac_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERLUT:
            return_value = noc_probe_get_emac_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERLUT:
            return_value = noc_probe_set_emac_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_TRACEALARMEN:
            return_value = noc_probe_get_emac_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_TRACEALARMEN:
            return_value = noc_probe_set_emac_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_TRACEALARMSTATUS:
            return_value = noc_probe_get_emac_probe_tracealarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_TRACEALARMCLR:
            return_value = noc_probe_set_emac_probe_tracealarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_STATPERIOD:
            return_value = noc_probe_get_emac_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATPERIOD:
            return_value = noc_probe_set_emac_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATGO:
            return_value = noc_probe_set_emac_probe_statgo_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_STATALARMMIN:
            return_value = noc_probe_get_emac_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATALARMMIN:
            return_value = noc_probe_set_emac_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_STATALARMMAX:
            return_value = noc_probe_get_emac_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATALARMMAX:
            return_value = noc_probe_set_emac_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_STATALARMSTATUS:
            return_value = noc_probe_get_emac_probe_statalarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATALARMCLR:
            return_value = noc_probe_set_emac_probe_statalarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_STATALARMEN:
            return_value = noc_probe_get_emac_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_STATALARMEN:
            return_value = noc_probe_set_emac_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_get_emac_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_set_emac_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_get_emac_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_set_emac_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_get_emac_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_set_emac_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_get_emac_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_set_emac_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_get_emac_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_set_emac_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_get_emac_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_set_emac_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_get_emac_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_set_emac_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_get_emac_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_set_emac_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_get_emac_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_set_emac_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_get_emac_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_set_emac_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_get_emac_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_set_emac_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_get_emac_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_set_emac_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_get_emac_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_set_emac_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_get_emac_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_set_emac_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_get_emac_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_set_emac_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_get_emac_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_set_emac_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_get_emac_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_set_emac_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_get_emac_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_set_emac_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_get_emac_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_set_emac_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_get_emac_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_set_emac_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_get_emac_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_set_emac_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_get_emac_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_set_emac_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_get_emac_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_set_emac_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_get_emac_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_set_emac_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_0_VAL:
            return_value = noc_probe_get_emac_probe_counters_0_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_get_emac_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_set_emac_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_get_emac_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_set_emac_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_1_VAL:
            return_value = noc_probe_get_emac_probe_counters_1_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_get_emac_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_set_emac_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_get_emac_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_set_emac_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_2_VAL:
            return_value = noc_probe_get_emac_probe_counters_2_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_get_emac_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_set_emac_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_get_emac_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_set_emac_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_PROBE_COUNTERS_3_VAL:
            return_value = noc_probe_get_emac_probe_counters_3_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_ID_COREID:
            return_value = noc_probe_get_soc2fpga_probe_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_ID_REVISIONID:
            return_value = noc_probe_get_soc2fpga_probe_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_MAINCTL:
            return_value = noc_probe_get_soc2fpga_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_MAINCTL:
            return_value = noc_probe_set_soc2fpga_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_CFGCTL:
            return_value = noc_probe_get_soc2fpga_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_CFGCTL:
            return_value = noc_probe_set_soc2fpga_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERLUT:
            return_value = noc_probe_get_soc2fpga_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERLUT:
            return_value = noc_probe_set_soc2fpga_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_TRACEALARMEN:
            return_value = noc_probe_get_soc2fpga_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_TRACEALARMEN:
            return_value = noc_probe_set_soc2fpga_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_TRACEALARMSTATUS:
            return_value = noc_probe_get_soc2fpga_probe_tracealarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_TRACEALARMCLR:
            return_value = noc_probe_set_soc2fpga_probe_tracealarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_STATPERIOD:
            return_value = noc_probe_get_soc2fpga_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATPERIOD:
            return_value = noc_probe_set_soc2fpga_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATGO:
            return_value = noc_probe_set_soc2fpga_probe_statgo_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_STATALARMMIN:
            return_value = noc_probe_get_soc2fpga_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATALARMMIN:
            return_value = noc_probe_set_soc2fpga_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_STATALARMMAX:
            return_value = noc_probe_get_soc2fpga_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATALARMMAX:
            return_value = noc_probe_set_soc2fpga_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_STATALARMSTATUS:
            return_value = noc_probe_get_soc2fpga_probe_statalarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATALARMCLR:
            return_value = noc_probe_set_soc2fpga_probe_statalarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_STATALARMEN:
            return_value = noc_probe_get_soc2fpga_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_STATALARMEN:
            return_value = noc_probe_set_soc2fpga_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_get_soc2fpga_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_set_soc2fpga_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_get_soc2fpga_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_set_soc2fpga_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_get_soc2fpga_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_set_soc2fpga_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_get_soc2fpga_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_set_soc2fpga_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_0_VAL:
            return_value = noc_probe_get_soc2fpga_probe_counters_0_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_get_soc2fpga_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_set_soc2fpga_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_get_soc2fpga_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_set_soc2fpga_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_1_VAL:
            return_value = noc_probe_get_soc2fpga_probe_counters_1_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_get_soc2fpga_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_set_soc2fpga_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_get_soc2fpga_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_set_soc2fpga_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_2_VAL:
            return_value = noc_probe_get_soc2fpga_probe_counters_2_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_get_soc2fpga_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_set_soc2fpga_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_get_soc2fpga_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SOC2FPGA_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_set_soc2fpga_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SOC2FPGA_PROBE_COUNTERS_3_VAL:
            return_value = noc_probe_get_soc2fpga_probe_counters_3_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_ID_COREID:
            return_value = noc_probe_get_emac_transactionstatprofiler_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_ID_REVISIONID:
            return_value = noc_probe_get_emac_transactionstatprofiler_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_EN:
            return_value = noc_probe_get_emac_transactionstatprofiler_en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_EN:
            return_value = noc_probe_set_emac_transactionstatprofiler_en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_MODE:
            return_value = noc_probe_get_emac_transactionstatprofiler_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_MODE:
            return_value = noc_probe_set_emac_transactionstatprofiler_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_0:
            return_value = noc_probe_get_emac_transactionstatprofiler_thresholds_0_0_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_0:
            return_value = noc_probe_set_emac_transactionstatprofiler_thresholds_0_0_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_1:
            return_value = noc_probe_get_emac_transactionstatprofiler_thresholds_0_1_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_1:
            return_value = noc_probe_set_emac_transactionstatprofiler_thresholds_0_1_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_2:
            return_value = noc_probe_get_emac_transactionstatprofiler_thresholds_0_2_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_THRESHOLDS_0_2:
            return_value = noc_probe_set_emac_transactionstatprofiler_thresholds_0_2_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_OVERFLOWSTATUS:
            return_value = noc_probe_get_emac_transactionstatprofiler_overflowstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_OVERFLOWRESET:
            return_value = noc_probe_set_emac_transactionstatprofiler_overflowreset_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_PENDINGEVENTMODE:
            return_value = noc_probe_get_emac_transactionstatprofiler_pendingeventmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_PENDINGEVENTMODE:
            return_value = noc_probe_set_emac_transactionstatprofiler_pendingeventmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATPROFILER_PRESCALER:
            return_value = noc_probe_get_emac_transactionstatprofiler_prescaler_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATPROFILER_PRESCALER:
            return_value = noc_probe_set_emac_transactionstatprofiler_prescaler_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_ID_COREID:
            return_value = noc_probe_get_io_probe_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_ID_REVISIONID:
            return_value = noc_probe_get_io_probe_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_MAINCTL:
            return_value = noc_probe_get_io_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_MAINCTL:
            return_value = noc_probe_set_io_probe_mainctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_CFGCTL:
            return_value = noc_probe_get_io_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_CFGCTL:
            return_value = noc_probe_set_io_probe_cfgctl_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERLUT:
            return_value = noc_probe_get_io_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERLUT:
            return_value = noc_probe_set_io_probe_filterlut_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_TRACEALARMEN:
            return_value = noc_probe_get_io_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_TRACEALARMEN:
            return_value = noc_probe_set_io_probe_tracealarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_TRACEALARMSTATUS:
            return_value = noc_probe_get_io_probe_tracealarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_TRACEALARMCLR:
            return_value = noc_probe_set_io_probe_tracealarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_STATPERIOD:
            return_value = noc_probe_get_io_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATPERIOD:
            return_value = noc_probe_set_io_probe_statperiod_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATGO:
            return_value = noc_probe_set_io_probe_statgo_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_STATALARMMIN:
            return_value = noc_probe_get_io_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATALARMMIN:
            return_value = noc_probe_set_io_probe_statalarmmin_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_STATALARMMAX:
            return_value = noc_probe_get_io_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATALARMMAX:
            return_value = noc_probe_set_io_probe_statalarmmax_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_STATALARMSTATUS:
            return_value = noc_probe_get_io_probe_statalarmstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATALARMCLR:
            return_value = noc_probe_set_io_probe_statalarmclr_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_STATALARMEN:
            return_value = noc_probe_get_io_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_STATALARMEN:
            return_value = noc_probe_set_io_probe_statalarmen_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_get_io_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_ROUTEIDBASE:
            return_value = noc_probe_set_io_probe_filters_0_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_get_io_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_ROUTEIDMASK:
            return_value = noc_probe_set_io_probe_filters_0_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_get_io_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_ADDRBASE_LOW:
            return_value = noc_probe_set_io_probe_filters_0_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_get_io_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_ADDRBASE_HIGH:
            return_value = noc_probe_set_io_probe_filters_0_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_get_io_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_WINDOWSIZE:
            return_value = noc_probe_set_io_probe_filters_0_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_get_io_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_SECURITYBASE:
            return_value = noc_probe_set_io_probe_filters_0_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_get_io_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_SECURITYMASK:
            return_value = noc_probe_set_io_probe_filters_0_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_get_io_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_OPCODE:
            return_value = noc_probe_set_io_probe_filters_0_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_get_io_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_STATUS:
            return_value = noc_probe_set_io_probe_filters_0_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_get_io_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_LENGTH:
            return_value = noc_probe_set_io_probe_filters_0_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_get_io_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_0_URGENCY:
            return_value = noc_probe_set_io_probe_filters_0_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_get_io_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_ROUTEIDBASE:
            return_value = noc_probe_set_io_probe_filters_1_routeidbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_get_io_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_ROUTEIDMASK:
            return_value = noc_probe_set_io_probe_filters_1_routeidmask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_get_io_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_ADDRBASE_LOW:
            return_value = noc_probe_set_io_probe_filters_1_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_get_io_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_ADDRBASE_HIGH:
            return_value = noc_probe_set_io_probe_filters_1_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_get_io_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_WINDOWSIZE:
            return_value = noc_probe_set_io_probe_filters_1_windowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_get_io_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_SECURITYBASE:
            return_value = noc_probe_set_io_probe_filters_1_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_get_io_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_SECURITYMASK:
            return_value = noc_probe_set_io_probe_filters_1_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_get_io_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_OPCODE:
            return_value = noc_probe_set_io_probe_filters_1_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_get_io_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_STATUS:
            return_value = noc_probe_set_io_probe_filters_1_status_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_get_io_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_LENGTH:
            return_value = noc_probe_set_io_probe_filters_1_length_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_get_io_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_FILTERS_1_URGENCY:
            return_value = noc_probe_set_io_probe_filters_1_urgency_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_get_io_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_0_SRC:
            return_value = noc_probe_set_io_probe_counters_0_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_get_io_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_0_ALARMMODE:
            return_value = noc_probe_set_io_probe_counters_0_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_0_VAL:
            return_value = noc_probe_get_io_probe_counters_0_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_get_io_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_1_SRC:
            return_value = noc_probe_set_io_probe_counters_1_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_get_io_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_1_ALARMMODE:
            return_value = noc_probe_set_io_probe_counters_1_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_1_VAL:
            return_value = noc_probe_get_io_probe_counters_1_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_get_io_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_2_SRC:
            return_value = noc_probe_set_io_probe_counters_2_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_get_io_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_2_ALARMMODE:
            return_value = noc_probe_set_io_probe_counters_2_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_2_VAL:
            return_value = noc_probe_get_io_probe_counters_2_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_get_io_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_3_SRC:
            return_value = noc_probe_set_io_probe_counters_3_src_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_get_io_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_PROBE_COUNTERS_3_ALARMMODE:
            return_value = noc_probe_set_io_probe_counters_3_alarmmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_PROBE_COUNTERS_3_VAL:
            return_value = noc_probe_get_io_probe_counters_3_val_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_ID_COREID:
            return_value = noc_probe_get_io_transactionstatprofiler_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_ID_REVISIONID:
            return_value = noc_probe_get_io_transactionstatprofiler_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_EN:
            return_value = noc_probe_get_io_transactionstatprofiler_en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_EN:
            return_value = noc_probe_set_io_transactionstatprofiler_en_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_MODE:
            return_value = noc_probe_get_io_transactionstatprofiler_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_MODE:
            return_value = noc_probe_set_io_transactionstatprofiler_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_0:
            return_value = noc_probe_get_io_transactionstatprofiler_thresholds_0_0_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_0:
            return_value = noc_probe_set_io_transactionstatprofiler_thresholds_0_0_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_1:
            return_value = noc_probe_get_io_transactionstatprofiler_thresholds_0_1_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_1:
            return_value = noc_probe_set_io_transactionstatprofiler_thresholds_0_1_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_2:
            return_value = noc_probe_get_io_transactionstatprofiler_thresholds_0_2_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_THRESHOLDS_0_2:
            return_value = noc_probe_set_io_transactionstatprofiler_thresholds_0_2_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_OVERFLOWSTATUS:
            return_value = noc_probe_get_io_transactionstatprofiler_overflowstatus_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_OVERFLOWRESET:
            return_value = noc_probe_set_io_transactionstatprofiler_overflowreset_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_PENDINGEVENTMODE:
            return_value = noc_probe_get_io_transactionstatprofiler_pendingeventmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_PENDINGEVENTMODE:
            return_value = noc_probe_set_io_transactionstatprofiler_pendingeventmode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATPROFILER_PRESCALER:
            return_value = noc_probe_get_io_transactionstatprofiler_prescaler_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATPROFILER_PRESCALER:
            return_value = noc_probe_set_io_transactionstatprofiler_prescaler_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_ID_COREID:
            return_value = noc_probe_get_ccu_qosgenerator_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_ID_REVISIONID:
            return_value = noc_probe_get_ccu_qosgenerator_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_get_ccu_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_set_ccu_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_MODE:
            return_value = noc_probe_get_ccu_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_QOSGENERATOR_MODE:
            return_value = noc_probe_set_ccu_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_get_ccu_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_set_ccu_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_SATURATION:
            return_value = noc_probe_get_ccu_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_QOSGENERATOR_SATURATION:
            return_value = noc_probe_set_ccu_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_CCU_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_get_ccu_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_CCU_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_set_ccu_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_ID_COREID:
            return_value = noc_probe_get_dma_qosgenerator_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_ID_REVISIONID:
            return_value = noc_probe_get_dma_qosgenerator_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_get_dma_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_DMA_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_set_dma_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_MODE:
            return_value = noc_probe_get_dma_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_DMA_QOSGENERATOR_MODE:
            return_value = noc_probe_set_dma_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_get_dma_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_DMA_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_set_dma_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_SATURATION:
            return_value = noc_probe_get_dma_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_DMA_QOSGENERATOR_SATURATION:
            return_value = noc_probe_set_dma_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_DMA_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_get_dma_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_DMA_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_set_dma_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_ID_COREID:
            return_value = noc_probe_get_emac_qosgenerator_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_ID_REVISIONID:
            return_value = noc_probe_get_emac_qosgenerator_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_get_emac_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_set_emac_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_MODE:
            return_value = noc_probe_get_emac_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_QOSGENERATOR_MODE:
            return_value = noc_probe_set_emac_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_get_emac_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_set_emac_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_SATURATION:
            return_value = noc_probe_get_emac_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_QOSGENERATOR_SATURATION:
            return_value = noc_probe_set_emac_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_get_emac_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_set_emac_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_ID_COREID:
            return_value = noc_probe_get_io_qosgenerator_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_ID_REVISIONID:
            return_value = noc_probe_get_io_qosgenerator_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_get_io_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_set_io_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_MODE:
            return_value = noc_probe_get_io_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_QOSGENERATOR_MODE:
            return_value = noc_probe_set_io_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_get_io_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_set_io_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_SATURATION:
            return_value = noc_probe_get_io_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_QOSGENERATOR_SATURATION:
            return_value = noc_probe_set_io_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_get_io_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_set_io_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_ID_COREID:
            return_value = noc_probe_get_sdm_qosgenerator_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_ID_REVISIONID:
            return_value = noc_probe_get_sdm_qosgenerator_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_get_sdm_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SDM_QOSGENERATOR_PRIORITY:
            return_value = noc_probe_set_sdm_qosgenerator_priority_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_MODE:
            return_value = noc_probe_get_sdm_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SDM_QOSGENERATOR_MODE:
            return_value = noc_probe_set_sdm_qosgenerator_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_get_sdm_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SDM_QOSGENERATOR_BANDWIDTH:
            return_value = noc_probe_set_sdm_qosgenerator_bandwidth_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_SATURATION:
            return_value = noc_probe_get_sdm_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SDM_QOSGENERATOR_SATURATION:
            return_value = noc_probe_set_sdm_qosgenerator_saturation_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_SDM_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_get_sdm_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_SDM_QOSGENERATOR_EXTCONTROL:
            return_value = noc_probe_set_sdm_qosgenerator_extcontrol_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_ID_COREID:
            return_value = noc_probe_get_emac_transactionstatfilter_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_ID_REVISIONID:
            return_value = noc_probe_get_emac_transactionstatfilter_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_MODE:
            return_value = noc_probe_get_emac_transactionstatfilter_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_MODE:
            return_value = noc_probe_set_emac_transactionstatfilter_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_ADDRBASE_LOW:
            return_value = noc_probe_get_emac_transactionstatfilter_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_ADDRBASE_LOW:
            return_value = noc_probe_set_emac_transactionstatfilter_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_ADDRBASE_HIGH:
            return_value = noc_probe_get_emac_transactionstatfilter_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_ADDRBASE_HIGH:
            return_value = noc_probe_set_emac_transactionstatfilter_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_ADDRWINDOWSIZE:
            return_value = noc_probe_get_emac_transactionstatfilter_addrwindowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_ADDRWINDOWSIZE:
            return_value = noc_probe_set_emac_transactionstatfilter_addrwindowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_OPCODE:
            return_value = noc_probe_get_emac_transactionstatfilter_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_OPCODE:
            return_value = noc_probe_set_emac_transactionstatfilter_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_USERBASE:
            return_value = noc_probe_get_emac_transactionstatfilter_userbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_USERBASE:
            return_value = noc_probe_set_emac_transactionstatfilter_userbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_USERMASK:
            return_value = noc_probe_get_emac_transactionstatfilter_usermask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_USERMASK:
            return_value = noc_probe_set_emac_transactionstatfilter_usermask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_SECURITYBASE:
            return_value = noc_probe_get_emac_transactionstatfilter_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_SECURITYBASE:
            return_value = noc_probe_set_emac_transactionstatfilter_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_SECURITYMASK:
            return_value = noc_probe_get_emac_transactionstatfilter_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_SECURITYMASK:
            return_value = noc_probe_set_emac_transactionstatfilter_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_USERBASEHIGH:
            return_value = noc_probe_get_emac_transactionstatfilter_userbasehigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_USERBASEHIGH:
            return_value = noc_probe_set_emac_transactionstatfilter_userbasehigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_EMAC_TRANSACTIONSTATFILTER_USERMASKHIGH:
            return_value = noc_probe_get_emac_transactionstatfilter_usermaskhigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_EMAC_TRANSACTIONSTATFILTER_USERMASKHIGH:
            return_value = noc_probe_set_emac_transactionstatfilter_usermaskhigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_ID_COREID:
            return_value = noc_probe_get_io_transactionstatfilter_id_coreid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_ID_REVISIONID:
            return_value = noc_probe_get_io_transactionstatfilter_id_revisionid_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_MODE:
            return_value = noc_probe_get_io_transactionstatfilter_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_MODE:
            return_value = noc_probe_set_io_transactionstatfilter_mode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_ADDRBASE_LOW:
            return_value = noc_probe_get_io_transactionstatfilter_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_ADDRBASE_LOW:
            return_value = noc_probe_set_io_transactionstatfilter_addrbase_low_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_ADDRBASE_HIGH:
            return_value = noc_probe_get_io_transactionstatfilter_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_ADDRBASE_HIGH:
            return_value = noc_probe_set_io_transactionstatfilter_addrbase_high_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_ADDRWINDOWSIZE:
            return_value = noc_probe_get_io_transactionstatfilter_addrwindowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_ADDRWINDOWSIZE:
            return_value = noc_probe_set_io_transactionstatfilter_addrwindowsize_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_OPCODE:
            return_value = noc_probe_get_io_transactionstatfilter_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_OPCODE:
            return_value = noc_probe_set_io_transactionstatfilter_opcode_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_USERBASE:
            return_value = noc_probe_get_io_transactionstatfilter_userbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_USERBASE:
            return_value = noc_probe_set_io_transactionstatfilter_userbase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_USERMASK:
            return_value = noc_probe_get_io_transactionstatfilter_usermask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_USERMASK:
            return_value = noc_probe_set_io_transactionstatfilter_usermask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_SECURITYBASE:
            return_value = noc_probe_get_io_transactionstatfilter_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_SECURITYBASE:
            return_value = noc_probe_set_io_transactionstatfilter_securitybase_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_SECURITYMASK:
            return_value = noc_probe_get_io_transactionstatfilter_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_SECURITYMASK:
            return_value = noc_probe_set_io_transactionstatfilter_securitymask_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_USERBASEHIGH:
            return_value = noc_probe_get_io_transactionstatfilter_userbasehigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_USERBASEHIGH:
            return_value = noc_probe_set_io_transactionstatfilter_userbasehigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_GET_IO_TRANSACTIONSTATFILTER_USERMASKHIGH:
            return_value = noc_probe_get_io_transactionstatfilter_usermaskhigh_reg(fd, buffer, length);
            break;
        case IOCTL_NOC_PROBE_SET_IO_TRANSACTIONSTATFILTER_USERMASKHIGH:
            return_value = noc_probe_set_io_transactionstatfilter_usermaskhigh_reg(fd, buffer, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}
