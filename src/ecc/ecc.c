#include "ecc.h"
#include "ecc_internal.h"
#include "ecc_regs.h"

#include <stdint.h>
#include <string.h>

device_descriptor_t ecc_devices[] = {{.name = "/dev/ecc0", .fd = ECC0_BASE, .acquired = 0}};

/* name: ecc_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t ecc_open(const char *path, int32_t flags) {
    int32_t fd = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(ecc_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(ecc_devices[i].name, path) == 0) {
                if (claim_device(&ecc_devices[i])) {
                    fd = ecc_devices[i].fd;
                }
            }
        }
    }
    return fd;
}

/* name: ecc_close
 * description: close the base_add via the base address of the device
 * parameters(s): base_add "address of the sdmmc device open"
 */
int32_t ecc_close(int32_t base_add) {
    int32_t return_value = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(ecc_devices) / sizeof(device_descriptor_t)); i++) {
            if (ecc_devices[i].fd == base_add) {
                ecc_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* name: ecc_recv
 * description: reading registers (future development, not functional as of now)
 * parameters(s): base_add "address of the eccc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t ecc_recv(int32_t base_add, uintptr_t user_data, size_t length, int32_t flags) { return 0; }

/* name: ecc_read
 * description: reading registers (future development, not functional as of now)
 * parameters(s): base_add "address of the ecc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t ecc_read(int32_t base_add, uintptr_t user_data, size_t length) {
    return ecc_recv(base_add, user_data, length, 0);
}

/* name: ecc_send
 * description: writing registers (future development, not functional as of now)
 * parameters(s): base_add "address of the ecc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t ecc_send(int32_t base_add, uintptr_t user_data, size_t size, int32_t flags) { return 0; }

/* name: ecc_write
 * description: writing registers (future development, not functional as of now)
 * parameters(s): base_add "address of the ecc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t ecc_write(int32_t base_add, uintptr_t user_data, size_t length) {
    return ecc_send(base_add, user_data, length, 0);
}

/* name: ecc_ioctl
 * description: process the input output control command
 * parameters(s): base_add, user_data, length "address of the ecc device open"
 *                operation "specific ioctl command for ecc"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
int32_t ecc_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    int32_t return_value = -1;
    if ((base_add == -1) || (((void *)(user_data)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((ecc_ioctl_t)operation) {
        case IOCTL_ECC_READ_REGS:
            return_value = ecc_regs_read(base_add, user_data, length);
            break;
        case IOCTL_ECC_WRITE_REGS:
            return_value = ecc_regs_write(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_IP_REV_ID:
            return_value = ecc_get_ip_rev_id(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_IP_REV_ID2:
            return_value = ecc_get_ip_rev_id2(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_CTRL:
            return_value = ecc_get_ctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_CTRL:
            return_value = ecc_set_ctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_INITSTAT:
            return_value = ecc_get_initstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_INITSTAT:
            return_value = ecc_set_initstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ERRINTEN:
            return_value = ecc_get_errinten(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ERRINTEN:
            return_value = ecc_set_errinten(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ERRINTENS:
            return_value = ecc_get_errintens(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ERRINTENS:
            return_value = ecc_set_errintens(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ERRINTENR:
            return_value = ecc_get_errintenr(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ERRINTENR:
            return_value = ecc_set_errintenr(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_INTMODE:
            return_value = ecc_get_intmode(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_INTMODE:
            return_value = ecc_set_intmode(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_INTSTAT:
            return_value = ecc_get_intstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_INTSTAT:
            return_value = ecc_set_intstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_INTTEST:
            return_value = ecc_get_inttest(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_INTTEST:
            return_value = ecc_set_inttest(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_MODSTAT:
            return_value = ecc_get_modstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_MODSTAT:
            return_value = ecc_set_modstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_DERRADDRA:
            return_value = ecc_get_derraddra(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_SERRADDRA:
            return_value = ecc_get_serraddra(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_DERRADDRB:
            return_value = ecc_get_derraddrb(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_SERRADDRB:
            return_value = ecc_get_serraddrb(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_SERRCNTREG:
            return_value = ecc_get_serrcntreg(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_SERRCNTREG:
            return_value = ecc_set_serrcntreg(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_ADDRBUS:
            return_value = ecc_get_ecc_addrbus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_ADDRBUS:
            return_value = ecc_set_ecc_addrbus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATA0BUS:
            return_value = ecc_get_ecc_rdata0bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATA1BUS:
            return_value = ecc_get_ecc_rdata1bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATA2BUS:
            return_value = ecc_get_ecc_rdata2bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATA3BUS:
            return_value = ecc_get_ecc_rdata3bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATA0BUS:
            return_value = ecc_set_ecc_wdata0bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATA1BUS:
            return_value = ecc_set_ecc_wdata1bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATA2BUS:
            return_value = ecc_set_ecc_wdata2bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATA3BUS:
            return_value = ecc_set_ecc_wdata3bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATAECC0BUS:
            return_value = ecc_get_ecc_rdataecc0bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_RDATAECC1BUS:
            return_value = ecc_get_ecc_rdataecc1bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATAECC0BUS:
            return_value = ecc_set_ecc_wdataecc0bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDATAECC1BUS:
            return_value = ecc_set_ecc_wdataecc1bus(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_DBYTECTRL:
            return_value = ecc_get_ecc_dbytectrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_DBYTECTRL:
            return_value = ecc_set_ecc_dbytectrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_ACCCTRL:
            return_value = ecc_get_ecc_accctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_ACCCTRL:
            return_value = ecc_set_ecc_accctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_STARTACC:
            return_value = ecc_get_ecc_startacc(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_STARTACC:
            return_value = ecc_set_ecc_startacc(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_WDCTRL:
            return_value = ecc_get_ecc_wdctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_WDCTRL:
            return_value = ecc_set_ecc_wdctrl(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_ECC_DECODERSTAT:
            return_value = ecc_get_ecc_decoderstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_ECC_DECODERSTAT:
            return_value = ecc_set_ecc_decoderstat(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_SERRLKUPA0:
            return_value = ecc_get_serrlkupa0(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_SERRLKUPA0:
            return_value = ecc_set_serrlkupa0(base_add, user_data, length);
            break;
        case IOCTL_ECC_GET_SERRLKUPB0:
            return_value = ecc_get_serrlkupb0(base_add, user_data, length);
            break;
        case IOCTL_ECC_SET_SERRLKUPB0:
            return_value = ecc_set_serrlkupb0(base_add, user_data, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}