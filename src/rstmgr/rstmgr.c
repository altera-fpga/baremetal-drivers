#include "rstmgr.h"
#include "rstmgr_internal.h"
#include "rstmgr_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t rstmgr_devices[] = {{.name = "/dev/rstmgr", .fd = HPS_RSTMGR_BASE, .acquired = 0}};

int32_t rstmgr_open(const char *name, int32_t flags) {
    int32_t fd = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(rstmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(rstmgr_devices[i].name, name) == 0) {
                if (claim_device(&rstmgr_devices[i])) {
                    fd = rstmgr_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

int32_t rstmgr_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(rstmgr_devices) / sizeof(device_descriptor_t)); i++) {
            if (rstmgr_devices[i].fd == fd) {
                rstmgr_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

size_t rstmgr_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t rstmgr_read(int32_t fd, uintptr_t buf, size_t size) { return rstmgr_recv(fd, buf, size, 0); }

size_t rstmgr_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }

size_t rstmgr_write(int32_t fd, const uintptr_t buf, size_t size) { return rstmgr_send(fd, buf, size, 0); }

int32_t rstmgr_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((rstmgr_ioctl_op_t)request) {
        case (IOCTL_RSTMGR_READ):
            return_value = rstmgr_regs_read(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_WRITE):
            return_value = rstmgr_regs_write(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_STAT):
            return_value = rstmgr_get_stat(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_STAT):
            return_value = rstmgr_set_stat(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_MISCSTAT):
            return_value = rstmgr_get_miscstat(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_MISCSTAT):
            return_value = rstmgr_set_miscstat(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HDSKEN):
            return_value = rstmgr_get_hdsk_en(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HDSKEN):
            return_value = rstmgr_set_hdsk_en(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HDSKREQ):
            return_value = rstmgr_get_hdsk_req(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HDSKREQ):
            return_value = rstmgr_set_hdsk_req(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HDSKACK):
            return_value = rstmgr_get_hdsk_ack(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HDSKACK):
            return_value = rstmgr_set_hdsk_ack(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HDSKSTALL):
            return_value = rstmgr_get_hdsk_stall(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HDSKSTALL):
            return_value = rstmgr_set_hdsk_stall(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_PER0MODRST):
            return_value = rstmgr_get_per0_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_PER0MODRST):
            return_value = rstmgr_set_per0_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_PER1MODRST):
            return_value = rstmgr_get_per1_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_PER1MODRST):
            return_value = rstmgr_set_per1_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_BRGMODRST):
            return_value = rstmgr_get_brg_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_BRGMODRST):
            return_value = rstmgr_set_brg_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_DBGMODRST):
            return_value = rstmgr_get_dbg_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_DBGMODRST):
            return_value = rstmgr_set_dbg_modrst(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_BRGWARMMASK):
            return_value = rstmgr_get_brg_warmmask(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_BRGWARMMASK):
            return_value = rstmgr_set_brg_warmmask(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_TSTSTA):
            return_value = rstmgr_get_tst_sta(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HDSKTIMEOUT):
            return_value = rstmgr_get_hdsk_timeout(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HDSKTIMEOUT):
            return_value = rstmgr_set_hdsk_timeout(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_DBGHDSKTIMEOUT):
            return_value = rstmgr_get_dbg_hdsk_timeout(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_DBGHDSKTIMEOUT):
            return_value = rstmgr_set_dbg_hdsk_timeout(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_DBGRSTCMPLT):
            return_value = rstmgr_get_dbg_rst_cmplt(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_DBGRSTCMPLT):
            return_value = rstmgr_set_dbg_rst_cmplt(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_HPSRSTCMPLT):
            return_value = rstmgr_get_hps_rst_cmplt(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_HPSRSTCMPLT):
            return_value = rstmgr_set_hps_rst_cmplt(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPUINRESET):
            return_value = rstmgr_get_cpu_in_reset(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPURSTRELEASE):
            return_value = rstmgr_get_cpu_rst_release(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPURSTRELEASE):
            return_value = rstmgr_set_cpu_rst_release(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU0_RESET_BASE_LOW):
            return_value = rstmgr_get_cpu0_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU0_RESET_BASE_LOW):
            return_value = rstmgr_set_cpu0_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU0_RESET_BASE_HIGH):
            return_value = rstmgr_get_cpu0_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU0_RESET_BASE_HIGH):
            return_value = rstmgr_set_cpu0_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU1_RESET_BASE_LOW):
            return_value = rstmgr_get_cpu1_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU1_RESET_BASE_LOW):
            return_value = rstmgr_set_cpu1_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU1_RESET_BASE_HIGH):
            return_value = rstmgr_get_cpu1_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU1_RESET_BASE_HIGH):
            return_value = rstmgr_set_cpu1_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU2_RESET_BASE_LOW):
            return_value = rstmgr_get_cpu2_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU2_RESET_BASE_LOW):
            return_value = rstmgr_set_cpu2_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU2_RESET_BASE_HIGH):
            return_value = rstmgr_get_cpu2_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU2_RESET_BASE_HIGH):
            return_value = rstmgr_set_cpu2_reset_base_high(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_GET_CPU3_RESET_BASE_LOW):
            return_value = rstmgr_get_cpu3_reset_base_low(fd, arg, length);
            break;
        case (IOCTL_RSTMGR_SET_CPU3_RESET_BASE_LOW):
            return_value = rstmgr_set_cpu3_reset_base_low(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t rstmgr_error(int32_t fd) { return 0; }