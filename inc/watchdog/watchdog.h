#ifndef WATCHDOG_H__
#define WATCHDOG_H__

#include <stddef.h>
#include <stdint.h>

// watchod accomompanying defines
#define WDT_RESET_VALUE 0x76
#define WDT_DFLT_TIME_OUT 0x0F   // default time out period
#define WDT_DFTL_PLS_LENGTH 0x04 // default reset pulse length "4 represents 32 clock cycles"

// IOCTL commands for getting and setting watchdog registers
enum {
    // Watchdog Timer getter commands
    IOCTL_WDT_GET_ENABLE = 1,
    IOCTL_WDT_GET_RMOD,
    IOCTL_WDT_GET_RESET_PULSE,
    IOCTL_WDT_GET_TOP,
    IOCTL_WDT_GET_TOP_INIT,
    IOCTL_WDT_GET_CCRV_STATUS,
    IOCTL_WDT_GET_INTERRUPT_STATUS,
    IOCTL_WDT_GET_CLEAR_INTERRUPT, // Reading the wdt_eoi clears the register on read?
    IOCTL_WDT_GET_COUNT_WIDTH,
    IOCTL_WDT_GET_DFLT_TOP_INIT,
    IOCTL_WDT_GET_DFLT_TOP,
    IOCTL_WDT_GET_DFLT_RST_PULSE_WIDTH,
    IOCTL_WDT_GET_APB_DATA_WIDTH,
    IOCTL_WDT_GET_PAUSE_STATE,
    IOCTL_WDT_GET_FIX_TOP_STATE,
    IOCTL_WDT_GET_HDCODE_TOP_STATE,
    IOCTL_WDT_GET_HDCODE_RST_PULSE_STATE,
    IOCTL_WDT_GET_HDCODE_RSP_MODE_STATE,
    IOCTL_WDT_GET_DUAL_TOP,
    IOCTL_WDT_GET_DFLT_RSP_MODE,
    IOCTL_WDT_GET_ALWAYS_ENABLE_STATE,
    IOCTL_WDT_GET_GET_COMP_VERSION,
    IOCTL_WDT_GET_GET_COMP_TYPE,

    // Watchdog timer Setter commands
    IOCTL_WDT_SET_ENABLE,
    IOCTL_WDT_SET_RMOD,
    IOCTL_WDT_SET_RESET_PULSE,
    IOCTL_WDT_SET_TOP,
    IOCTL_WDT_SET_TOP_INIT,
    IOCTL_WDT_SET_COUNTER_RESTART,

    // adding new elements before this line
    IOCTL_WDT_END
};

int32_t watchdog_open(const char *path, int32_t flags);
int32_t watchdog_close(int32_t base_add);
int32_t watchdog_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length);
int32_t watchdog_error(int32_t base_add);

#endif // WATCHDOG_H
