#include "noc_probe.h"
#include "noc_probe_internal.h"
#include "noc_probe_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int set_check(int32_t fd, noc_probe_ioctl_t set_op, noc_probe_ioctl_t get_op, uint32_t param, char *name) {
    uint32_t value = param;
    if (noc_probe_ioctl(fd, (int32_t)set_op, (uintptr_t)&param, sizeof(param)) < 0) {
        printf("ERROR: Failed to set %s\n", name);
        return -1;
    }
    if (noc_probe_ioctl(fd, (int32_t)get_op, (uintptr_t)&param, sizeof(param)) < 0) {
        printf("ERROR: Failed to get %s to verify write\n", name);
        return -1;
    }
    if (param != value) {
        printf("ERROR: %s was not set successfully (wrote %#x, read %#x)\n", name, value, param);
        return -1;
    }
    printf("Successfully wrote %#x to %s\n", param, name);
    return 0;
}

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char noc_probe_initiator[] = "/dev/noc_probe0";

    int32_t return_value = 0;
    uint32_t param = 0;

    printf("Started Logging\n");

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("NOC Probe Test Starts\n");

    int32_t noc_probe_handle = noc_probe_open(noc_probe_initiator, 0);
    if (noc_probe_handle < 0) {
        printf("ERROR: NOC Probe failed to open\n");
        return_value = -1;
        return return_value;
    } else {
        printf("NOC Probe successfully open\n");

        /**
         * TODO - Not tested:
         * - Quality of Service (QoS) generators
         * - Effects of "STPv2Converter"
         * - TransactionStat{Profiler,Filter}
         * - Filter registers within the probes
         */

        // sanity check: ensure read-only, nonzero-on-reset register has correct value
        if (noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_IO_PROBE_ID_COREID, (uintptr_t)&param,
                            sizeof(param)) < 0) {
            printf("ERROR: Failed to read reset value of Core ID register\n");
            return -1;
        };
        if (param != 0x81109E06) {
            printf("ERROR: Wrong reset value of Core ID register: %#x\n", param);
            return -1;
        }
        printf("Got correct reset value of Core ID register: %#x\n", param);

        // enable ATB unit
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_ATBENDPOINT_ATBEN, IOCTL_NOC_PROBE_GET_ATBENDPOINT_ATBEN, 1,
                      "ATB Unit Enable") < 0) {
            return -1;
        }

        // enable the probe
        param = 1;
        if (noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_SET_CCU_PROBE_CFGCTL, (uintptr_t)&param,
                            sizeof(param)) < 0) {
            printf("ERROR: Failed to set %s\n", "CCU probe configuration control");
            return -1;
        }
        if (noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_CFGCTL, (uintptr_t)&param,
                            sizeof(param)) < 0) {
            printf("ERROR: Failed to get %s to verify write\n", "CCU probe configuration control");
            return -1;
        }
        if (!(param & 0b01)) {
            printf("ERROR: %s was not set successfully (wrote %#x, read %#x)\n", "CCU probe configuration control", 1,
                   param);
            return -1;
        }
        if (param & 0b10) {
            printf("CCU packet probe is ACTIVE!\n");
        }
        printf("Successfully wrote %#x to %s\n", 1, "CCU probe configuration control");

        // enable statistics profiling and alarms
        if (set_check(
                noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_MAINCTL, IOCTL_NOC_PROBE_GET_CCU_PROBE_MAINCTL,
                // ALARMEN  (bit 4): When set, register field AlarmEn enables the probe to collect alarm-related
                // information. When the register field bit is null, both TraceAlarm and StatAlarm outputs are driven to
                // 0. STATEN   (bit 3): When set to 1, register field StatEn enables statistics profiling. The probe
                // sendS statistics results to the output for signal ObsTx. All statistics counters are cleared when the
                // StatEn bit goes from 0 to 1. When set to 0, counters are disabled.
                0b11000, "CCU probe main control") < 0) {
            return -1;
        }

        // counter 0 tracks idle cycles
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_0_SRC,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_SRC,
                      1, // counts Idle cycles (Vld=0 out of a packet)
                      "CCU probe counter 0 Src") < 0) {
            return -1;
        }

        // counter 1 tracks effective transfer cycles
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_1_SRC,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_SRC,
                      2, // counts effective transfer cycles (Vld=1 and Rdy=1)
                      "CCU probe counter 1 Src") < 0) {
            return -1;
        }

        // counter 2 tracks busy cycles
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_2_SRC,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_SRC,
                      3, // counts busy cycles (Vld=1 and Rdy=0)
                      "CCU probe counter 2 Src") < 0) {
            return -1;
        }

        // counter 3 tracks wait cycles
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_3_SRC,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_SRC,
                      4, // counts wait cycles (Vld=0 inside a packet)
                      "CCU probe counter 3 Src") < 0) {
            return -1;
        }

        // enable a statistics alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMEN,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMEN, 1, "CCU statistics alarm enable") < 0) {
            return -1;
        }

        // enable counter 0 to trigger the alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_0_ALARMMODE,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_ALARMMODE,
                      2, // if the value of the counter is greater than the StatAlarmMax register at the dump period,
                         // the StatAlarmStatus bit is set
                      "CCU probe counter 0 AlarmMode") < 0) {
            return -1;
        }

        // enable counter 1 to trigger the alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_1_ALARMMODE,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_ALARMMODE,
                      2, // if the value of the counter is greater than the StatAlarmMax register at the dump period,
                         // the StatAlarmStatus bit is set
                      "CCU probe counter 1 AlarmMode") < 0) {
            return -1;
        }

        // enable counter 2 to trigger the alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_2_ALARMMODE,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_ALARMMODE,
                      2, // if the value of the counter is greater than the StatAlarmMax register at the dump period,
                         // the StatAlarmStatus bit is set
                      "CCU probe counter 2 AlarmMode") < 0) {
            return -1;
        }

        // enable counter 3 to trigger the alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_COUNTERS_3_ALARMMODE,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_ALARMMODE,
                      2, // if the value of the counter is greater than the StatAlarmMax register at the dump period,
                         // the StatAlarmStatus bit is set
                      "CCU probe counter 3 AlarmMode") < 0) {
            return -1;
        }

        // set the maximum count that does not trigger the alarm
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_CCU_PROBE_STATALARMMAX,
                      IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMMAX, 5, "CCU statistics alarm max count") < 0) {
            return -1;
        }

        // exercise an STPv2Converter register
        if (set_check(noc_probe_handle, IOCTL_NOC_PROBE_SET_STPV2CONVERTER_ASYNCPERIOD,
                      IOCTL_NOC_PROBE_GET_STPV2CONVERTER_ASYNCPERIOD, 0b11111, "STPv2Converter AsyncPeriod") < 0) {
            return -1;
        }
        // check error logs
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRVLD, (uintptr_t)&param,
                        sizeof(param));
        if (param) {
            struct {
                uint32_t FORMAT : 1; // bit 31
                uint32_t __pad_30_28 : 3;
                uint32_t LEN1 : 12; // bits 27:16
                uint32_t __pad_15_11 : 5;
                uint32_t ERRCODE : 3; // bits 10:8
                uint32_t __pad_7_5;
                uint32_t OPC : 4; // bits 4:1
                uint32_t LOCK : 1;
            } errlog;
            noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRLOG0, (uintptr_t)&errlog,
                            sizeof(errlog));
            printf("Got error log 0: format %u, length %u, code %#x, OPC %#x, lock %u\n", errlog.FORMAT, errlog.LEN1,
                   errlog.ERRCODE, errlog.OPC, errlog.LOCK);
            // write param back to errclr to clear errvld
            noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_SET_ERRORLOGGER_0_ERRCLR, (uintptr_t)&param,
                            sizeof(param));
            noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_ERRORLOGGER_0_ERRVLD, (uintptr_t)&param,
                            sizeof(param));
            if (param) {
                printf("ERROR: Failed to clear ERRVLD signal\n");
                return_value = -1;
                return return_value;
            }
        } else {
            printf("No error logged in error logger\n");
        }

        // trigger statistics dump
        param = 1;
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_SET_CCU_PROBE_STATGO, (uintptr_t)&param,
                        sizeof(param));
        uint32_t counts[4];
        // read counter 0 value
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_0_VAL, (uintptr_t)&param,
                        sizeof(param));
        counts[0] = param;
        // read counter 1 value
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_1_VAL, (uintptr_t)&param,
                        sizeof(param));
        counts[1] = param;
        // read counter 2 value
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_2_VAL, (uintptr_t)&param,
                        sizeof(param));
        counts[2] = param;
        // read counter 3 value
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_COUNTERS_3_VAL, (uintptr_t)&param,
                        sizeof(param));
        counts[3] = param;
        // check if there was an alarm
        noc_probe_ioctl(noc_probe_handle, (int32_t)IOCTL_NOC_PROBE_GET_CCU_PROBE_STATALARMSTATUS, (uintptr_t)&param,
                        sizeof(param));
        // print counter values
        int should_trigger = 0;
        for (int i = 0; i < 4; ++i) {
            if (counts[i] > 5) {
                should_trigger = 1;
            }
            printf("Counter %d value %u < 5\n", i, counts[i]);
        }
        // check if triggered when should have
        if (should_trigger) {
            if (!param) {
                printf("ERROR: Statistics alarm failed to trigger despite a counter having value > 5\n");
                return -1;
            }
            printf("Statistics alarm successfully triggered\n");
        } else {
            if (param) {
                printf("ERROR: Statistics alarm triggered despite no counter having value > 5\n");
                return -1;
            }
            printf("Statistics alarm successfully did not trigger\n");
        }
    }

    // close NOC Probe handle
    int32_t ret = noc_probe_close(noc_probe_handle);
    if (ret == 0) {
        printf("NOC Probe close: OK\n");
    } else {
        printf("NOC Probe close: FAILED\n");
        return_value = ret;
    }

    return return_value;
}
