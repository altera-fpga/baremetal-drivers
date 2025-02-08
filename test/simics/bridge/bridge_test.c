#include "bridge_helper.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "sysmgr.h"
#include "timer.h"

#include <stdio.h>
#include <string.h>

#define RST_MGR_PER1MODRST_UART_MASK 0x00030040

#ifdef __cplusplus
extern "C" {
#endif

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";

    int32_t return_value = 0;

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    int32_t timer_handle = timer_open("/dev/timer0", 0);
    if (timer_handle < 0) {
        return timer_handle;
    }

    int32_t sysmgr_handle = sysmgr_open("/dev/sysmgr", 0);
    if (sysmgr_handle < 0) {
        return sysmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per1modrst &= ~((uint32_t)RST_MGR_PER1MODRST_UART_MASK);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("Bridge Test Start\n");

    if (bridge_disable(rstmgr_handle, timer_handle, sysmgr_handle) != 0) {
        printf("Bridge disable FAILED!\n");
        return -1;
    } else if (bridge_enable(rstmgr_handle, timer_handle, sysmgr_handle) != 0) {
        printf("Bridge enable FAILED!\n");
        return -1;
    } else {
        printf("Bridge Test is successful!\n");
    }

    printf("Bridge Test Done\n");

    return return_value;
}

#ifdef __cplusplus
}
#endif
