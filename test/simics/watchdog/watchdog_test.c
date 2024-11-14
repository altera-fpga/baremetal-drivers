#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "watchdog.h"
#include "watchdog_internal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Notes: HW_RESET_VERIFICATION
 *  enabling HW_RESET_VERIFICATION will is for implementing watchdog test on actual hardware.
 *  Thsi flag will allow the watchdog to trigger a reset and it should be captured at the beginning of the test
 *  since the test should restart.
 *  Verification is needed thus we have a flag protecting this until we have everything in place <-- TODO REMOVE COMMENT
 * LINE ONCE VERIFIEDS
 */
#define SENSITIVE_AREA_ITERATIONS 100
#define RESTART_WDT 0x76
// BITS 16 - 20 are bits indicating a watchdog caused a reset for reset manager "hps_rstmgr_regs_t"
#define WDT_CAUSE_RESET 0x001F0000
#ifdef __cplusplus
extern "C" {
#endif

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    clock_t start_time, end_time;
    const char wdt_initiator[] = "/dev/watchdog0";
    int32_t return_value = 1;
    uint32_t wdt_param = 0;

    // For some unknown reason this test doesn't work without this print statement here SO DON'T MOVE THIS UNTIL WE
    // UNDERSTAND WHY
    printf("Starting\n");
    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    hps_rstmgr_regs_t regs_buffer;
    if (rstmgr_handle < 0) {
        return_value = rstmgr_handle;
    } else {

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        regs_buffer.per0modrst &= ~((uint32_t)0x00020000);
        regs_buffer.per1modrst &= ~((uint32_t)0x0403000F);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

        printf("Reset Manager CPU states = %08x\n", regs_buffer.cpuinreset);

#ifdef HW_RESET_VERIFICATION
        // If watchdog caused reset, the hw UNIT test is complete and successful
        if (regs_buffer.stat & WDT_CAUSE_RESET) {
            printf("Previous reset was caused by watchdog\n");
            return_value = 0;
            printf("wdt successful\n");
        } else {
#else
        {
#endif
            printf("watchdog test started\n");
            int32_t wdt_handle = watchdog_open(wdt_initiator, 0);
            if (wdt_handle < 0) {
                return_value = wdt_handle;
                printf("wdt failed to open\n");
            } else {
                printf("wdt handle successfully open\n");
                // Interrupt set test
                // Lets set watchdog to generate an interrupt on timeout
                wdt_param = 1;
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_RMOD, (uintptr_t)&wdt_param, sizeof(wdt_param));

                // Set timeout periods for 32 clocks
                wdt_param = 10;

                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_TOP, (uintptr_t)&wdt_param, sizeof(wdt_param));
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_TOP_INIT, (uintptr_t)&wdt_param, sizeof(wdt_param));

                // Set reset pulse length to 256 clocks
                wdt_param = 0x000007;
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_RESET_PULSE, (uintptr_t)&wdt_param,
                               sizeof(wdt_param));

                // Get Reset pulse width
                wdt_param = 0;
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_GET_RESET_PULSE, (uintptr_t)&wdt_param,
                               sizeof(wdt_param));

                // Check value
                if (wdt_param != 7) {
                    printf("reset pulse width not Set to 256 PCLCKS\n");
                } else {
                    printf("reset pulse width Set to 256 PCLCK\n");
                }

                // Enable wdt
                wdt_param = 1;
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_ENABLE, (uintptr_t)&wdt_param, sizeof(wdt_param));

                // Check registers values
                // Sensitive area START
                // -- If anything is added to the area below it will affect the block_tick_iterations value WILL BE
                // AFFECTED
                //    IF MORE THINGS ARE ADDED THE NUMBER OF ITERATIONS MAY HAVE TO DECREASE TO ENSURE THAT WDT
                //    INTERRUPT OCCURS BEFORE BREAKING OUT
                wdt_param = 0;
                watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_GET_ENABLE, (uintptr_t)&wdt_param, sizeof(wdt_param));
                if (wdt_param == 0) {
                    printf("wdt is NOT enabled\n");
                } else {
                    printf("wdt is enabled\n");
                    wdt_param = 0;

                    // Get starting clock
                    start_time = clock();
                    do {
                        watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_GET_INTERRUPT_STATUS, (uintptr_t)&wdt_param,
                                       sizeof(wdt_param));
                        if (wdt_param == 1) {
                            printf("WDT interrupt triggered\n");
#ifndef HW_RESET_VERIFICATION
                            // Restart WDT Counter
                            wdt_param = RESTART_WDT;
                            watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_COUNTER_RESTART, (uintptr_t)&wdt_param,
                                           sizeof(wdt_param));

                            // disable watchdog
                            wdt_param = 0;
                            watchdog_ioctl(wdt_handle, (int32_t)IOCTL_WDT_SET_ENABLE, (uintptr_t)&wdt_param,
                                           sizeof(wdt_param));

                            // Close watchdog
                            return_value = watchdog_close(wdt_handle);
                            printf("wdt successful\n");
#endif
                            break;
                        }
                        // Get new clock ticks
                        end_time = clock();
                    } while ((end_time - start_time) < 256);

#ifdef HW_RESET_VERIFICATION
                    do {
                        printf(" Waiting for reset to occur\n");
                    } while (1);
#endif
                } // if/esle
            }
        }
    }
    return return_value;
}

#ifdef __cplusplus
}
#endif
