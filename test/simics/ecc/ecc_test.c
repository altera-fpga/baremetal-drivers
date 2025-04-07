#include "ecc.h"
#include "ecc_internal.h"
#include "ecc_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char ecc_initiator[] = "/dev/ecc0";
    int32_t return_value = 0;
    uint32_t param = 0;

    printf("Started Logging\n");

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)0x0000FF00);
    regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("ECC Test Starts\n");

    int32_t ecc_handle = ecc_open(ecc_initiator, 0);
    if (ecc_handle < 0) {
        printf("ERROR: ECC failed to open\n");
        return_value = -1;
        return return_value;
    } else {
        printf("ECC successfully open\n");

        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_IP_REV_ID, (uintptr_t)&param, sizeof(uint32_t));
        printf("REV_ID =%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_IP_REV_ID2, (uintptr_t)&param, sizeof(uint32_t));
        printf("REV_ID_2=%x\n", param);
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_INITSTAT, (uintptr_t)&param, sizeof(uint32_t));
        printf("INSTAT=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ERRINTEN, (uintptr_t)&param, sizeof(uint32_t));
        printf("ERRINTEN=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ERRINTENS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ERRINTENS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ERRINTENR, (uintptr_t)&param, sizeof(uint32_t));
        printf("ERRINTENR=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_INTMODE, (uintptr_t)&param, sizeof(uint32_t));
        printf("INTMODE=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_INTSTAT, (uintptr_t)&param, sizeof(uint32_t));
        printf("INSTAT=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_INTTEST, (uintptr_t)&param, sizeof(uint32_t));
        printf("INTEST=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_MODSTAT, (uintptr_t)&param, sizeof(uint32_t));
        printf("MODSTAT=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_DERRADDRA, (uintptr_t)&param, sizeof(uint32_t));
        printf("DERRADDRA=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_SERRADDRA, (uintptr_t)&param, sizeof(uint32_t));
        printf("SERRADDRA=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_DERRADDRB, (uintptr_t)&param, sizeof(uint32_t));
        printf("DERRADDRB=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_SERRADDRB, (uintptr_t)&param, sizeof(uint32_t));
        printf("SERRADDRB=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_SERRCNTREG, (uintptr_t)&param, sizeof(uint32_t));
        printf("SERRCNTREG=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_ADDRBUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_ADDRBUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATA0BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATA0BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATA1BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATA1BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATA2BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATA2BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATA3BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATA3BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATAECC0BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATAECC0BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_RDATAECC1BUS, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_RDATAECC1BUS=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_DBYTECTRL, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_DBYTECTRL=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_ACCCTRL, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_ACCCTRL=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_STARTACC, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_STARTACC=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_WDCTRL, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_WDCTRL=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_ECC_DECODERSTAT, (uintptr_t)&param, sizeof(uint32_t));
        printf("ECC_DECODERSTAT=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_SERRLKUPA0, (uintptr_t)&param, sizeof(uint32_t));
        printf("SERRLKUPA0=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
        ecc_ioctl(ecc_handle, (int32_t)IOCTL_ECC_GET_SERRLKUPB0, (uintptr_t)&param, sizeof(uint32_t));
        printf("SERRLKUPB0=%x\n", param);
        if (param != 0) {
            return_value = -1;
            return return_value;
        }
    }

    // close ECC handle
    return_value = ecc_close(ecc_handle);
    if (return_value == 0) {
        printf("ECC close: OK\n");
    } else {
        printf("ECC close: FAILED\n");
    }

    if (return_value == 0) {
        printf("ECC Tests successful!!!\n");
    }

    return return_value;
}