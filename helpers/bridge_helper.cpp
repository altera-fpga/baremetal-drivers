#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "page_tables.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "sysmgr.h"
#include "timer.h"
#include "uart.h"

#include <stdio.h>
#include <string.h>

#define RST_MGR_HDSKEN_FPGAHSEN 0x00000004
#define RST_MGR_HDSKREQ_FPGAHSREQ 0x00000004
#define RST_MGR_HDSKACK_FPGAHSACK 0x00000004

#define RST_MGR_HDSKEN_LWSOC2FPGAFLUSHEN 0x00000200
#define RST_MGR_HDSKREQ_LWSOC2FPGAFLUSHREQ 0x00000200
#define RST_MGR_HDSKACK_LWSOC2FPGAFLUSHACK 0x00000200

#define RST_MGR_HDSKEN_SOC2FPGAFLUSHEN 0x00000400
#define RST_MGR_HDSKREQ_SOC2FPGAFLUSHREQ 0x00000400
#define RST_MGR_HDSKACK_SOC2FPGAFLUSHACK 0x00000400

#define RST_MGR_HDSKEN_F2SDRAMFLUSHEN 0x00000800
#define RST_MGR_HDSKREQ_F2SDRAMFLUSHREQ 0x00000800
#define RST_MGR_HDSKACK_F2SDRAMFLUSHACK 0x00000800

#define RST_MGR_HDSKEN_F2SFLUSHEN 0x00001000
#define RST_MGR_HDSKREQ_F2SFLUSHREQ 0x00001000
#define RST_MGR_HDSKACK_F2SFLUSHACK 0x00001000

#define RST_MGR_BRGMODRST_SOC2FPGA 0x00000001
#define RST_MGR_BRGMODRST_LWSOC2FPGA 0x00000002
#define RST_MGR_BRGMODRST_FPGA2SOC 0x00000004
#define RST_MGR_BRGMODRST_FPGA2SDRAM 0x00000008

// The ref clock l4_sp_clk is 100MHz by default.
// check if clkmgr.nocdiv->l4spclk is 0x2 (default).
// If not, then this definition needs to be updated accordingly.
#define TICKS_PER_MILLI_SEC 0x186A0

#define TMR_SP0_CTRL_TIMER_ENABLE 0x1
#define TMR_SP0_CTRL_TIMER_MODE_USR 0x2
#define ACK_POLLING_MILLI_SEC 1

#define SYS_MGR_FPGA_BRIDGE_CTRL_SOC2FPGA_EN 0x00000001
#define SYS_MGR_FPGA_BRIDGE_CTRL_LWSOC2FPGA_EN 0x00000002

#define SYS_MGR_F2S_BRIDGE_CTRL_F2SOC_EN 0x00000001

int32_t delay_timer(int32_t timer_handle, int32_t count) {
    uint32_t param = count;
    if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_COUNT_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
        printf("[Timer Error] count set.\n");
        return -1;
    }

    // Set timer not free running
    param = TMR_SP0_CTRL_TIMER_MODE_USR;
    if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CONTROL_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
        printf("[Timer Error] control set for free running.\n");
        return -1;
    }

    // Start timer
    param |= TMR_SP0_CTRL_TIMER_ENABLE;
    if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CONTROL_SET, (uintptr_t)(&param), sizeof(uint32_t))) {
        printf("[Timer Error] control set for starting timer.\n");
        return -1;
    }

    // Verify timer is not 0
    param = 0;
    if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CURRENT_VAL_GET, (uintptr_t)(&param), sizeof(uint32_t))) {
        printf("[Timer Error] Unable to get current value.\n");
        return -1;
    }
    if (param == 0) {
        printf("[Timer Error] current value is 0.\n");
        return -1;
    }

    printf("[Timer] START\n");

    // Wait for timer to expire
    while (1) {
        param = 0;
        if (timer_ioctl(timer_handle, (int32_t)IOCTL_TIMER_CURRENT_VAL_GET, (uintptr_t)(&param), sizeof(uint32_t))) {
            printf("[Timer Error] Unable to get current value.\n");
            return -1;
        }
        if (param == 0) {
            printf("[Timer] Expired... Leaving the loop... \n");
            break;
        }
    }
    return 0;
}

int32_t polling_register(int32_t handle, int32_t cmd, int32_t mask, int32_t ms, int32_t timer_handle, bool assert) {

    int32_t param = 0, count = ms;

    while (count-- > 0) {

        printf("POLLING #%d ...\n", (count + 1));

        rstmgr_ioctl(handle, (int32_t)cmd, (uintptr_t)&param, sizeof(uint32_t));
        if (assert) {
            if (param & mask) {
                return 0;
            }
        } else {
            if (!(param & mask)) {
                return 0;
            }
        }

        // delay timer for 1 ms
        if (delay_timer(timer_handle, TICKS_PER_MILLI_SEC) == -1) {
            printf("[polling_register Error]: Timer setup error!\n");
        }
    }

    return -1;
}

int32_t bridge_enable(int32_t rstmgr_handle, int32_t timer_handle, int32_t sysmgr_handle) {
    uint32_t param_req = 0, param_ack = 0, param = 0;
    int32_t return_value = 0;
    int32_t sysmgr_ret = 0;

    printf("============= Bridge Enable =============\n");

    /* Enable SOC2FPGA */

    // Read brgmodrst to make sure it is asserted
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    if (param & RST_MGR_BRGMODRST_SOC2FPGA) {
        printf("[Enable] brgmodrst is 1 for SOC2FPGA\n");

        // De-assert the bridge module reset
        printf("[Enable] De-assert the bridge module reset.\n");
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
        param &= ~RST_MGR_BRGMODRST_SOC2FPGA;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

        // Clear the ACK
        param_ack = RST_MGR_HDSKACK_SOC2FPGAFLUSHACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear SOC2FPGAFLUSHACK.\n");

        // Clear idle status (SOC2FPGA)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & RST_MGR_HDSKREQ_SOC2FPGAFLUSHREQ) {
            param_req &= ~(RST_MGR_HDSKREQ_SOC2FPGAFLUSHREQ);
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear SOC2FPGAFLUSHREQ.\n");
        }

        // Polling ack to be 0 (active) (SOC2FPGA)
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_SOC2FPGAFLUSHACK,
                             ACK_POLLING_MILLI_SEC, timer_handle, false) == -1) {
            printf("[Error] Polling SOC2FPGAFLUSHACK = 0 timeout\n");
            return -1;
        }
        printf("[Enable] Polling SOC2FPGAFLUSHACK = 0 OK\n");

        printf("[Enable] Set soc2fpga_ready_latency_enable.\n");
        sysmgr_ret = sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL, (uintptr_t)&param,
                                  sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_GET_FPGA_BRIDGE_CTRL.\n");
            return -1;
        }
        param |= SYS_MGR_FPGA_BRIDGE_CTRL_SOC2FPGA_EN;

        sysmgr_ret = sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL, (uintptr_t)&param,
                                  sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_SET_FPGA_BRIDGE_CTRL.\n");
            return -1;
        }

        printf("----- SOC2FPGA reset flow is SUCCESSFUL. -----\n");

    } else {
        printf("[Warning]: brgmodrst is 0 for SOC2FPGA\n");
    }

    /* Enable LWSOC2FPGA */

    // Read brgmodrst to make sure it is asserted
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    if (param & RST_MGR_BRGMODRST_LWSOC2FPGA) {
        printf("[Enable] brgmodrst is 1 for LWSOC2FPGA\n");

        // 1. De-assert the bridge module reset
        printf("[Enable] De-assert the bridge module reset.\n");
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
        param &= ~RST_MGR_BRGMODRST_LWSOC2FPGA;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

        // 1.1 Clear the ACK
        param_ack = RST_MGR_HDSKACK_LWSOC2FPGAFLUSHACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear LWSOC2FPGAFLUSHACK.\n");

        // 2. Clear idle status (LWSOC2FPGA)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & RST_MGR_HDSKREQ_LWSOC2FPGAFLUSHREQ) {
            param_req &= ~(RST_MGR_HDSKREQ_LWSOC2FPGAFLUSHREQ);
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear LWSOC2FPGAFLUSHREQ.\n");
        }

        // 4. Polling ack to be 0 (active) (LWSOC2FPGA)
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_LWSOC2FPGAFLUSHACK,
                             ACK_POLLING_MILLI_SEC, timer_handle, false) == -1) {
            printf("[Error] Polling LWSOC2FPGAFLUSHACK = 0 timeout\n");
            return -1;
        }
        printf("[Enable] Polling LWSOC2FPGAFLUSHACK = 0 OK!\n");

        printf("[Enable] Set lwsoc2fpga_ready_latency_enable.\n");
        sysmgr_ret = sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL, (uintptr_t)&param,
                                  sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_GET_FPGA_BRIDGE_CTRL.\n");
            return -1;
        }
        param |= SYS_MGR_FPGA_BRIDGE_CTRL_LWSOC2FPGA_EN;

        sysmgr_ret = sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL, (uintptr_t)&param,
                                  sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_SET_FPGA_BRIDGE_CTRL.\n");
            return -1;
        }

        printf("----- LWSOC2FPGA reset flow is SUCCESSFUL. -----\n");
    } else {
        printf("[Warning]: brgmodrst is 0 for LWSOC2FPGA\n");
    }

    /* Enable FPGA2SOC */
    // Read brgmodrst to make sure it is asserted
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    if (param & RST_MGR_BRGMODRST_FPGA2SOC) {
        printf("[Enable] brgmodrst is 1 for FPGA2SOC\n");

        // De-assert the bridge module reset
        printf("[Enable] De-assert the bridge module reset.\n");
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
        param &= ~RST_MGR_BRGMODRST_FPGA2SOC;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

        // Clear the ACK (FPGA)
        param_ack = RST_MGR_HDSKACK_FPGAHSACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear FPGAHSACK\n");

        // Clear idle status (FPGA)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & (RST_MGR_HDSKREQ_FPGAHSREQ)) {
            param_req &= ~RST_MGR_HDSKREQ_FPGAHSREQ;
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear FPGAHSREQ\n");
        }

        // Polling FPGAHSACK to 0
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_FPGAHSACK, ACK_POLLING_MILLI_SEC,
                             timer_handle, false) == -1) {
            printf("[Enable Error] Polling FPGAHSACK = 0 timeout ...\n");
            return -1;
        }
        printf("[Enable] Polling FPGAHSACK = 0 OK!\n");

        // Clear the ACK (F2SOC)
        param_ack = RST_MGR_HDSKACK_F2SFLUSHACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear  F2SFLUSHACK.\n");

        // Clear idle status (F2SOC)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & RST_MGR_HDSKREQ_F2SFLUSHREQ) {
            param_req &= ~RST_MGR_HDSKREQ_F2SFLUSHREQ;
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear F2SFLUSHREQ.\n");
        }

        // Polling F2SFLUSHACK to 0
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_F2SFLUSHACK,
                             ACK_POLLING_MILLI_SEC, timer_handle, false) == -1) {
            printf("[Error] Polling F2SFLUSHACK = 0 timeout\n");
            return -1;
        }
        printf("[Enable] Polling F2SFLUSHACK = 0 OK!\n");

        printf("[Enable] Set f2soc_enable.\n");
        sysmgr_ret =
            sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_GET_F2S_BRIDGE_CTRL.\n");
            return -1;
        }
        param |= SYS_MGR_F2S_BRIDGE_CTRL_F2SOC_EN;

        sysmgr_ret =
            sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
        if (sysmgr_ret != 0) {
            printf("[SYSMGR Error]: SYSMGR_SET_F2S_BRIDGE_CTRL.\n");
            return -1;
        }

        printf("----- F2SOC reset flow is SUCCESSFUL. -----\n");
    } else {
        printf("[Warning]: brgmodrst is 0 for F2SOC\n");
    }

    /* Enable FPGA2SDRAM */

    // Read brgmodrst to make sure it is asserted
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    if (param & RST_MGR_BRGMODRST_FPGA2SDRAM) {
        printf("[Enable] brgmodrst is 1 for FPGA2SDRAM\n");

        // De-assert the bridge module reset
        printf("[Enable] De-assert the bridge module reset.\n");
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
        param &= ~RST_MGR_BRGMODRST_FPGA2SDRAM;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

        // Clear the ACK (FPGA)
        param_ack = RST_MGR_HDSKACK_FPGAHSACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear FPGAHSACK\n");

        // Clear idle status (FPGA)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & (RST_MGR_HDSKREQ_FPGAHSREQ)) {
            param_req &= ~RST_MGR_HDSKREQ_FPGAHSREQ;
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear FPGAHSREQ\n");
        }

        // Polling FPGAHSACK to 0
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_FPGAHSACK, ACK_POLLING_MILLI_SEC,
                             timer_handle, false) == -1) {
            printf("[Enable Error] Polling FPGAHSACK = 0 timeout ...\n");
            return -1;
        }
        printf("[Enable] Polling FPGAHSACK = 0 OK!\n");

        // Clear the ACK (F2SDRAM)
        param_ack = RST_MGR_HDSKACK_F2SDRAMFLUSHACK;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
        printf("[Enable] Clear F2SDRAMFLUSHACK.\n");

        // Clear idle status (F2SDRAM)
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
        if (param_req & RST_MGR_HDSKREQ_F2SDRAMFLUSHREQ) {
            param_req &= ~RST_MGR_HDSKREQ_F2SDRAMFLUSHREQ;
            rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
            printf("[Enable] Clear F2SDRAMFLUSHREQ.\n");
        }

        // Polling F2SDRAMFLUSHACK to 0
        if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_F2SDRAMFLUSHACK,
                             ACK_POLLING_MILLI_SEC, timer_handle, false) == -1) {
            printf("[Error] Polling F2SDRAMFLUSHACK = 0 timeout\n");
            return -1;
        }
        printf("[Enable] Polling F2SDRAMFLUSHACK = 0 OK!\n");

        printf("----- F2SDRAM reset flow is SUCCESSFUL. -----\n");
    } else {
        printf("[Warning]: brgmodrst is 0 for F2SOC\n");
    }
    return return_value;
}

int32_t bridge_disable(int32_t rstmgr_handle, int32_t timer_handle, int32_t sysmgr_handle) {
    uint32_t param_en = 0, param_req = 0, param_ack = 0, param = 0;
    int32_t return_value = 0;
    int32_t sysmgr_ret = 0;

    printf("========== Bridge Disable ==========\n");

    /* Disable SOC2FPGA */
    printf("----- Disable SOC2FPGA -----\n");

    // clear soc2fpga_ready_latency_enable in sysmgr
    printf("[Disable] Clear soc2fpga_ready_latency_enable.\n");
    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_GET_FPGA_BRIDGE_CTRL.\n");
        return -1;
    }
    param &= ~SYS_MGR_FPGA_BRIDGE_CTRL_SOC2FPGA_EN;

    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_SET_FPGA_BRIDGE_CTRL.\n");
        return -1;
    }

    // clear ack
    param_ack = RST_MGR_HDSKACK_SOC2FPGAFLUSHACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Enable] Clear SOC2FPGAFLUSHACK.\n");

    // idle request
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_SOC2FPGAFLUSHREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    printf("[Disable] SOC2FPGA idle request.\n");

    // get ack
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_SOC2FPGAFLUSHACK,
                         ACK_POLLING_MILLI_SEC, timer_handle, true) == -1) {
        printf("[Error] Polling SOC2FPGAFLUSHACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling SOC2FPGAFLUSHACK = 1 OK!\n");

    // Assert the bridge module reset
    printf("[Disable] Assert the bridge module reset.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    param |= RST_MGR_BRGMODRST_SOC2FPGA;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

    /* Disable LWSOC2FPGA */
    printf("----- Disable LWSOC2FPGA -----\n");

    // clear lwsoc2fpga_ready_latency_enable in sysmgr
    printf("[Disable] Clear lwsoc2fpga_ready_latency_enable.\n");
    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_FPGA_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_GET_FPGA_BRIDGE_CTRL.\n");
        return -1;
    }
    param &= ~SYS_MGR_FPGA_BRIDGE_CTRL_LWSOC2FPGA_EN;

    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_FPGA_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_SET_FPGA_BRIDGE_CTRL.\n");
        return -1;
    }

    // clear ack
    param_ack = RST_MGR_HDSKACK_LWSOC2FPGAFLUSHACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Disable] Clear LWSOC2FPGAFLUSHACK.\n");

    // idle request
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_LWSOC2FPGAFLUSHREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    printf("[Disable] LWSOC2FPGA idle request.\n");

    // get ack
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_LWSOC2FPGAFLUSHACK,
                         ACK_POLLING_MILLI_SEC, timer_handle, true) == -1) {
        printf("[Error] Polling LWSOC2FPGAFLUSHACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling LWSOC2FPGAFLUSHACK = 1 OK!\n");

    // Assert the bridge module reset
    printf("[Disable] Assert the bridge module reset.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    param |= RST_MGR_BRGMODRST_LWSOC2FPGA;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

    /* Disable FPGA2SOC */
    printf("----- Disable FPGA2SOC -----\n");

    // clear f2soc_enable in sysmgr
    printf("[Disable] Clear f2soc_enable.\n");
    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_GET_F2S_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_GET_F2S_BRIDGE_CTRL.\n");
        return -1;
    }
    param &= ~SYS_MGR_F2S_BRIDGE_CTRL_F2SOC_EN;

    sysmgr_ret =
        sysmgr_ioctl(sysmgr_handle, (int32_t)IOCTL_SYSMGR_SET_F2S_BRIDGE_CTRL, (uintptr_t)&param, sizeof(uint32_t));
    if (sysmgr_ret != 0) {
        printf("[Error]: SYSMGR_SET_F2S_BRIDGE_CTRLL.\n");
        return -1;
    }

    // enable idle request for F2SOC
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    param_en |= RST_MGR_HDSKEN_F2SFLUSHEN;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    printf("[Disable] F2S idle request: enabled.\n");

    // enable idle request for FPGA
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    param_en |= RST_MGR_HDSKEN_FPGAHSEN;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    printf("[Disable] FPGA idle request: enabled.\n");

    // clear idle ack (FPGA)
    param_ack = RST_MGR_HDSKACK_FPGAHSACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Disable] Clear FPGAHSACK.\n");

    // idle request (FPGA)
    printf("[Disable] FPGA idle request: request.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_FPGAHSREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));

    // get ack (FPGA)
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_FPGAHSACK, ACK_POLLING_MILLI_SEC,
                         timer_handle, true) == -1) {
        printf("[Error] Polling FPGAHSACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling FPGAHSACK = 1 SUCCESSFUL!\n");

    // Fence and Drain

    // clear idle ack (F2SOC)
    param_ack = RST_MGR_HDSKACK_F2SFLUSHACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Disable] Fence and Drain: Clear F2SFLUSHACK.\n");

    // idle request (F2SOC)
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_F2SFLUSHREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    printf("[Disable] Fence and Drain: requested.\n");

    // get ack (F2SOC)
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_F2SFLUSHACK, ACK_POLLING_MILLI_SEC,
                         timer_handle, true) == -1) {
        printf("[Error] Polling F2SFLUSHACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling F2SFLUSHACK = 1 OK!\n");

    // Assert the bridge module reset
    printf("[Disable] Assert the bridge module reset.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    param |= RST_MGR_BRGMODRST_FPGA2SOC;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

    /* Disable F2SDRAM */
    printf("----- Disable F2SDRAM -----\n");

    // enable idle request for F2SDRAM
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    param_en |= RST_MGR_HDSKEN_F2SDRAMFLUSHEN;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    printf("[Disable] F2SDRAM idle request: enabled.\n");

    // enable idle request for FPGA
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    param_en |= RST_MGR_HDSKEN_FPGAHSEN;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKEN, (uintptr_t)&param_en, sizeof(uint32_t));
    printf("[Disable] FPGA idle request: enabled.\n");

    // clear idle ack (FPGA)
    param_ack = RST_MGR_HDSKACK_FPGAHSACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Disable] Clear FPGAHSACK.\n");

    // idle request (FPGA)
    printf("[Disable] FPGA idle request: request.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_FPGAHSREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));

    // get ack (FPGA)
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_FPGAHSACK, ACK_POLLING_MILLI_SEC,
                         timer_handle, true) == -1) {
        printf("[Error] Polling FPGAHSACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling FPGAHSACK = 1 OK!\n");

    // Fence and Drain

    // clear idle ack (F2SDRAM)
    param_ack = RST_MGR_HDSKACK_F2SDRAMFLUSHACK;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKACK, (uintptr_t)&param_ack, sizeof(uint32_t));
    printf("[Disable] Fence and Drain: Clear F2SDRAMFLUSHACK\n");

    // idle request (F2SDRAM)
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    param_req |= RST_MGR_HDSKREQ_F2SDRAMFLUSHREQ;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_HDSKREQ, (uintptr_t)&param_req, sizeof(uint32_t));
    printf("[Disable] Fence and Drain: requested.\n");

    // get ack (F2SDRAM)
    if (polling_register(rstmgr_handle, IOCTL_RSTMGR_GET_HDSKACK, RST_MGR_HDSKACK_F2SDRAMFLUSHACK,
                         ACK_POLLING_MILLI_SEC, timer_handle, true) == -1) {
        printf("[Error] Polling F2SDRAMFLUSHACK = 1 timeout\n");
        return -1;
    }
    printf("[Disable] Polling F2SDRAMFLUSHACK = 1 OK!\n");

    // Assert the bridge module reset
    printf("[Disable] Assert the bridge module reset.\n");
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));
    param |= RST_MGR_BRGMODRST_FPGA2SDRAM;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_BRGMODRST, (uintptr_t)&param, sizeof(uint32_t));

    return return_value;
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus