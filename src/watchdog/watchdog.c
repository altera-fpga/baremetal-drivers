#include "watchdog.h"
#include "device.h"
#include "watchdog_internal.h"
#include "watchdog_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// watchdog descriptors
device_descriptor_t watchdog_devices[] = {
    {.name = "/dev/watchdog0", .fd = WATCHDOG_BASE0, .acquired = 0},
    {.name = "/dev/watchdog1", .fd = WATCHDOG_BASE1, .acquired = 0},
    {.name = "/dev/watchdog2", .fd = WATCHDOG_BASE2, .acquired = 0},
    {.name = "/dev/watchdog3", .fd = WATCHDOG_BASE3, .acquired = 0},
    {.name = "/dev/watchdog4", .fd = WATCHDOG_BASE4, .acquired = 0},
};

/* name: watchdog_verify_wdt_access
 * description: search if "base_address" has been properly captured for access
 * parameters(s): "base_address" base address of the watchdog timer
 */
static int32_t watchdog_verify_wdt_access(int32_t base_address) {

    int32_t return_value = -1;
    // Search through devices for matching
    for (uint32_t i = 0; i < (sizeof(watchdog_devices) / sizeof(device_descriptor_t)); i++) {
        // Is the current base address valid and acquired
        if ((watchdog_devices[i].fd == base_address) && (watchdog_devices[i].acquired == true)) {
            return_value = 0;
            break;
        }
    }
    return return_value;
}

/* name: watchdog_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t watchdog_open(const char *path, int32_t flags) {
    int32_t wdt_memory_base = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(watchdog_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(watchdog_devices[i].name, path) == 0) {
                if (claim_device(&watchdog_devices[i])) {
                    wdt_memory_base = watchdog_devices[i].fd;
                }
            }
        }
    }
    return wdt_memory_base;
}

/* name: watchdog_close
 * description: close the fd via the base address of the device
 * parameters(s): base_add "address of the watchdog timer device open"
 */
int32_t watchdog_close(int32_t base_add) {
    int32_t return_value = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(watchdog_devices) / sizeof(device_descriptor_t)); i++) {
            if (watchdog_devices[i].fd == base_add) {
                watchdog_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* name: watchdog_ioctl
 * description: process the input output control command
 * parameters(s): base_add "address of the watchdog timer device open"
 *                operation "specific ioctl command for watchdog"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to
 */
int32_t watchdog_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    // TODO create structure of status return values
    int32_t return_value = -1;

    // pointer to the memory denoted via argument user_buf
    uint32_t *cmd_data = (uint32_t *)user_data;

    // Validate if base address is currently acquired
    if ((watchdog_verify_wdt_access(base_add) == -1) || (length < (sizeof(uint32_t))) ||
        (((void *)(user_data)) == nullptr)) {
        return_value = -2;
    } else {

        // Check if operation is valid
        switch ((uint32_t)operation) {

        // Commands to retrieving register content
        case IOCTL_WDT_GET_ENABLE:
            *cmd_data = wdt_get_enable_state(base_add);
            break;

        case IOCTL_WDT_GET_RMOD:
            *cmd_data = wdt_get_rmod(base_add);
            break;

        case IOCTL_WDT_GET_RESET_PULSE:
            *cmd_data = wdt_get_reset_pulse(base_add);
            break;

        case IOCTL_WDT_GET_TOP:
            *cmd_data = wdt_get_top(base_add);
            break;

        case IOCTL_WDT_GET_TOP_INIT:
            *cmd_data = wdt_get_init_top(base_add);
            break;

        case IOCTL_WDT_GET_INTERRUPT_STATUS:
            *cmd_data = wdt_get_int_status(base_add);
            break;

        case IOCTL_WDT_GET_CLEAR_INTERRUPT:
            *cmd_data = wdt_clear_interrupt(base_add);
            break;

        case IOCTL_WDT_GET_COUNT_WIDTH:
            *cmd_data = wdt_get_counter_width(base_add);
            break;

        case IOCTL_WDT_GET_DFLT_TOP_INIT:
            *cmd_data = wdt_get_dflt_itop(base_add);
            break;

        case IOCTL_WDT_GET_DFLT_TOP:
            *cmd_data = wdt_get_dflt_top(base_add);
            break;

        case IOCTL_WDT_GET_DFLT_RST_PULSE_WIDTH:
            *cmd_data = wdt_get_dflt_rst_pulse(base_add);
            break;

        case IOCTL_WDT_GET_APB_DATA_WIDTH:
            *cmd_data = wdt_get_apb_dwidth(base_add);
            break;

        case IOCTL_WDT_GET_PAUSE_STATE:
            *cmd_data = wdt_get_fixed_top_state(base_add);
            break;

        case IOCTL_WDT_GET_FIX_TOP_STATE:
            *cmd_data = wdt_get_fixed_top_state(base_add);
            break;

        case IOCTL_WDT_GET_HDCODE_TOP_STATE:
            *cmd_data = wdt_get_hdcoded_top_state(base_add);
            break;

        case IOCTL_WDT_GET_HDCODE_RST_PULSE_STATE:
            *cmd_data = wdt_get_hdcoded_rstp_state(base_add);
            break;

        case IOCTL_WDT_GET_HDCODE_RSP_MODE_STATE:
            *cmd_data = wdt_get_dflt_rmode_state(base_add);
            break;

        case IOCTL_WDT_GET_DUAL_TOP:
            *cmd_data = wdt_get_dual_top_state(base_add);
            break;

        case IOCTL_WDT_GET_DFLT_RSP_MODE:
            *cmd_data = wdt_get_dflt_rmode_state(base_add);
            break;

        case IOCTL_WDT_GET_ALWAYS_ENABLE_STATE:
            *cmd_data = wdt_get_alwen_state(base_add);
            break;

        case IOCTL_WDT_GET_GET_COMP_VERSION:
            *cmd_data = wdt_get_comp_version(base_add);
            break;

        case IOCTL_WDT_GET_GET_COMP_TYPE:
            *cmd_data = wdt_get_comp_type(base_add);
            break;

        // Commands to setting register content
        case IOCTL_WDT_SET_ENABLE:
            wdt_set_enable(base_add, *cmd_data);
            break;

        case IOCTL_WDT_SET_RMOD:
            wdt_set_rmod(base_add, *cmd_data);
            break;

        case IOCTL_WDT_SET_RESET_PULSE:
            wdt_set_reset_pulse(base_add, *cmd_data);
            break;

        case IOCTL_WDT_SET_TOP:
            wdt_set_top(base_add, *cmd_data);
            break;

        case IOCTL_WDT_SET_TOP_INIT:
            wdt_set_init_top(base_add, *cmd_data);
            break;

        case IOCTL_WDT_SET_COUNTER_RESTART:
            wdt_reset_wdt_cnt(base_add, *cmd_data);
            break;

        default:
            // INVALID COMMAND
            return_value = -3; // Lets go ahead and future proof this error
            break;
        }
    }
    return return_value;
};

/* name: watchdog_error
 * description: TBD
 * parameters(s):TBD
 */
int32_t watchdog_error(int32_t base_add) { return -1; }
