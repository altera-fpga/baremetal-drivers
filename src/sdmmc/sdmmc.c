#include "sdmmc.h"
#include "device.h"
#include "sdmmc_internal.h"
#include "sdmmc_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// sdmmc descriptor
device_descriptor_t sdmmc_devices[] = {{.name = "/dev/sdmmc0", .fd = SDMMC_BASE, .acquired = 0}};

/* name: sdmmc_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t sdmmc_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != NULL) {
        for (uint32_t i = 0; i < (sizeof(sdmmc_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(sdmmc_devices[i].name, path) == 0) {
                if (claim_device(&sdmmc_devices[i])) {
                    return_value = sdmmc_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

/* name: sdmmc_close
 * description: close the base_add via the base address of the device
 * parameters(s): base_add "address of the sdmmc device open"
 */
int32_t sdmmc_close(int32_t base_add) {
    int32_t return_value = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(sdmmc_devices) / sizeof(device_descriptor_t)); i++) {
            if (sdmmc_devices[i].fd == base_add) {
                sdmmc_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* name: sdmmc_read
 * description: reading registers
 * parameters(s): base_add "address of the sdmmc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t sdmmc_read(int32_t base_add, uintptr_t user_data, size_t length) {
    return sdmmc_recv(base_add, user_data, length, 0);
}

/* name: sdmmc_write
 * description: writing registers
 * parameters(s): base_add "address of the sdmmc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t sdmmc_write(int32_t base_add, uintptr_t user_data, size_t length) {
    return sdmmc_send(base_add, user_data, length, 0);
}

/* name: sdmmc_recv
 * description: reading registers
 * parameters(s): base_add "address of the sdmmc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t sdmmc_recv(int32_t base_add, uintptr_t user_data, size_t length, int32_t flags) { return 0; }

/* name: sdmmc_send
 * description: writing registers
 * parameters(s): base_add "address of the sdmmc device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t sdmmc_send(int32_t base_add, uintptr_t user_data, size_t size, int32_t flags) { return 0; }

/* name: sdmmc_ioctl
 * description: process the input output control command
 * parameters(s): base_add, user_data, length "address of the sdmmc device open"
 *                operation "specific ioctl command for sdmmc"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
int32_t sdmmc_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    int32_t return_value = -1;
    if ((base_add == -1) || (((void *)(user_data)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((sdmmc_ioctl_t)operation) {
        case IOCTL_SDMMC_READ_REGS:
            return_value = sdmmc_read_internal(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_WRITE_REGS:
            return_value = sdmmc_write_internal(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS00:
            return_value = sdmmc_get_hrs00(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS00:
            return_value = sdmmc_set_hrs00(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS00_SWR:
            return_value = sdmmc_set_hrs00_swr(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS01:
            return_value = sdmmc_get_hrs01(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS01:
            return_value = sdmmc_set_hrs01(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS02:
            return_value = sdmmc_get_hrs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS02:
            return_value = sdmmc_set_hrs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS03:
            return_value = sdmmc_get_hrs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS03:
            return_value = sdmmc_set_hrs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS04:
            return_value = sdmmc_get_hrs04(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS04:
            return_value = sdmmc_set_hrs04(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS05:
            return_value = sdmmc_get_hrs05(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS05:
            return_value = sdmmc_set_hrs05(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS06:
            return_value = sdmmc_get_hrs06(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS06:
            return_value = sdmmc_set_hrs06(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS07:
            return_value = sdmmc_get_hrs07(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS07:
            return_value = sdmmc_set_hrs07(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS08:
            return_value = sdmmc_get_hrs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS08:
            return_value = sdmmc_set_hrs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS08_PHY_DLL_UPDREQ:
            return_value = sdmmc_set_hrs08_phy_dll_updreq(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS09:
            return_value = sdmmc_get_hrs09(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09:
            return_value = sdmmc_set_hrs09(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_PHY_SW_RESET:
            return_value = sdmmc_set_hrs09_phy_sw_reset(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_EXTENDED_RD_MODE:
            return_value = sdmmc_set_hrs09_extended_rd_mode(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_EXTENDED_WR_MODE:
            return_value = sdmmc_set_hrs09_extended_wr_mode(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_RDCMD_EN:
            return_value = sdmmc_set_hrs09_rdcmd_en(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_RDDATA_EN:
            return_value = sdmmc_set_hrs09_rddata_en(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_LVSI_TCKSEL:
            return_value = sdmmc_set_hrs09_lvsi_tcksel(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS09_LVSI_CNT:
            return_value = sdmmc_set_hrs09_lvsi_cnt(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS10:
            return_value = sdmmc_get_hrs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS10:
            return_value = sdmmc_set_hrs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS12:
            return_value = sdmmc_get_hrs12(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS12:
            return_value = sdmmc_set_hrs12(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS13:
            return_value = sdmmc_get_hrs13(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS13:
            return_value = sdmmc_set_hrs13(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS14:
            return_value = sdmmc_get_hrs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS14:
            return_value = sdmmc_set_hrs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS16:
            return_value = sdmmc_get_hrs16(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS16:
            return_value = sdmmc_set_hrs16(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS29:
            return_value = sdmmc_get_hrs29(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS30:
            return_value = sdmmc_get_hrs30(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS31:
            return_value = sdmmc_get_hrs31(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS32:
            return_value = sdmmc_get_hrs32(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS32:
            return_value = sdmmc_set_hrs32(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS32_ADDR:
            return_value = sdmmc_set_hrs32_addr(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_HRS32_LOAD:
            return_value = sdmmc_set_hrs32_load(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS33:
            return_value = sdmmc_get_hrs33(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_HRS34:
            return_value = sdmmc_get_hrs34(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS00:
            return_value = sdmmc_get_srs00(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS00:
            return_value = sdmmc_set_srs00(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS01:
            return_value = sdmmc_get_srs01(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS01:
            return_value = sdmmc_set_srs01(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS02:
            return_value = sdmmc_get_srs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS02:
            return_value = sdmmc_set_srs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS03:
            return_value = sdmmc_get_srs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS03:
            return_value = sdmmc_set_srs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS04:
            return_value = sdmmc_get_srs04(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS05:
            return_value = sdmmc_get_srs05(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS06:
            return_value = sdmmc_get_srs06(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS07:
            return_value = sdmmc_get_srs07(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS08:
            return_value = sdmmc_get_srs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS08:
            return_value = sdmmc_set_srs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS09:
            return_value = sdmmc_get_srs09(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS10:
            return_value = sdmmc_get_srs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS10:
            return_value = sdmmc_set_srs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS11:
            return_value = sdmmc_get_srs11(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11:
            return_value = sdmmc_set_srs11(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_ICE:
            return_value = sdmmc_set_srs11_ice(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SDCE:
            return_value = sdmmc_set_srs11_sdce(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SDCFSH:
            return_value = sdmmc_set_srs11_sdcfsh(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SDCFSL:
            return_value = sdmmc_set_srs11_sdcfsl(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_DTCV:
            return_value = sdmmc_set_srs11_dtcv(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SRFA:
            return_value = sdmmc_set_srs11_srfa(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SRCMD:
            return_value = sdmmc_set_srs11_srcmd(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS11_SRDAT:
            return_value = sdmmc_set_srs11_srdat(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS12:
            return_value = sdmmc_get_srs12(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS12:
            return_value = sdmmc_set_srs12(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS13:
            return_value = sdmmc_get_srs13(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS13:
            return_value = sdmmc_set_srs13(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS14:
            return_value = sdmmc_get_srs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS14:
            return_value = sdmmc_set_srs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS15:
            return_value = sdmmc_get_srs15(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15:
            return_value = sdmmc_set_srs15(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_UMS:
            return_value = sdmmc_set_srs15_ums(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_V18SE:
            return_value = sdmmc_set_srs15_v18se(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_DSS:
            return_value = sdmmc_set_srs15_dss(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_EXTNG:
            return_value = sdmmc_set_srs15_extng(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_SCS:
            return_value = sdmmc_set_srs15_scs(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_LVSIEXEC:
            return_value = sdmmc_set_srs15_lvsiexec(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_ADMA2LM:
            return_value = sdmmc_set_srs15_adma2lm(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_CMD23E:
            return_value = sdmmc_set_srs15_cmd23e(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_HV4E:
            return_value = sdmmc_set_srs15_hv4e(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_A64B:
            return_value = sdmmc_set_srs15_a64b(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS15_PVE:
            return_value = sdmmc_set_srs15_pve(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS16:
            return_value = sdmmc_get_srs16(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS17:
            return_value = sdmmc_get_srs17(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS18:
            return_value = sdmmc_get_srs18(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS19:
            return_value = sdmmc_get_srs19(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS20:
            return_value = sdmmc_get_srs20(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS20:
            return_value = sdmmc_set_srs20(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS21:
            return_value = sdmmc_get_srs21(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS22:
            return_value = sdmmc_get_srs22(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS22:
            return_value = sdmmc_set_srs22(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS23:
            return_value = sdmmc_get_srs23(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS23:
            return_value = sdmmc_set_srs23(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS24:
            return_value = sdmmc_get_srs24(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS25:
            return_value = sdmmc_get_srs25(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS26:
            return_value = sdmmc_get_srs26(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS27:
            return_value = sdmmc_get_srs27(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS30:
            return_value = sdmmc_get_srs30(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS30:
            return_value = sdmmc_set_srs30(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_SRS31:
            return_value = sdmmc_get_srs31(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_SRS31:
            return_value = sdmmc_set_srs31(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CRS63:
            return_value = sdmmc_get_crs63(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS00:
            return_value = sdmmc_get_cqrs00(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS01:
            return_value = sdmmc_get_cqrs01(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS02:
            return_value = sdmmc_get_cqrs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS02:
            return_value = sdmmc_set_cqrs02(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS03:
            return_value = sdmmc_get_cqrs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS03:
            return_value = sdmmc_set_cqrs03(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS04:
            return_value = sdmmc_get_cqrs04(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS04:
            return_value = sdmmc_set_cqrs04(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS05:
            return_value = sdmmc_get_cqrs05(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS05:
            return_value = sdmmc_set_cqrs05(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS06:
            return_value = sdmmc_get_cqrs06(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS07:
            return_value = sdmmc_get_cqrs07(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07:
            return_value = sdmmc_set_cqrs07(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICTOVAL:
            return_value = sdmmc_set_cqrs07_cqictoval(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICTOVALEN:
            return_value = sdmmc_set_cqrs07_cqictovalen(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICCTH:
            return_value = sdmmc_set_cqrs07_cqiccth(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICCTHWEN:
            return_value = sdmmc_set_cqrs07_cqiccthwen(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICCTR:
            return_value = sdmmc_set_cqrs07_cqicctr(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS07_CQICED:
            return_value = sdmmc_set_cqrs07_cqiced(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS08:
            return_value = sdmmc_get_cqrs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS08:
            return_value = sdmmc_set_cqrs08(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS09:
            return_value = sdmmc_get_cqrs09(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS09:
            return_value = sdmmc_set_cqrs09(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS10:
            return_value = sdmmc_get_cqrs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS10:
            return_value = sdmmc_set_cqrs10(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS11:
            return_value = sdmmc_get_cqrs11(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS12:
            return_value = sdmmc_get_cqrs12(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS13:
            return_value = sdmmc_get_cqrs13(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS14:
            return_value = sdmmc_get_cqrs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS14:
            return_value = sdmmc_set_cqrs14(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS16:
            return_value = sdmmc_get_cqrs16(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS17:
            return_value = sdmmc_get_cqrs17(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_SET_CQRS17:
            return_value = sdmmc_set_cqrs17(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS18:
            return_value = sdmmc_get_cqrs18(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS20:
            return_value = sdmmc_get_cqrs20(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS21:
            return_value = sdmmc_get_cqrs21(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS22:
            return_value = sdmmc_get_cqrs22(base_add, user_data, length);
            break;
        case IOCTL_SDMMC_GET_CQRS23:
            return_value = sdmmc_get_cqrs23(base_add, user_data, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}