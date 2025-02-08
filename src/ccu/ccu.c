#include "ccu.h"
#include "ccu_internal.h"
#include "ccu_regs.h"
#include "device.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

device_descriptor_t ccu_devices[] = {{.name = "/dev/ccu", .fd = CCU_BASE, .acquired = 0}};

/**
 * @brief This function opens the CCU controller
 *
 * @param name the path to the device
 * @param flags currently unused
 * @return the base address of the controller. -1 means there is no available controller
 */

int32_t ccu_open(const char *name, int32_t flags) {
    int32_t return_value = -1;
    if (name != nullptr) {
        for (uint32_t i = 0; i < (sizeof(ccu_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(ccu_devices[i].name, name) == 0) {
                if (claim_device(&ccu_devices[i])) {
                    return_value = ccu_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

/**
 * @brief This function closes the CCU controller
 *
 * @param fd base address of CCU controller (handler)
 * @return 0 if successful, otherwise return non-zero values
 */

int32_t ccu_close(int32_t fd) {
    int32_t return_value = -1;

    for (uint32_t i = 0; i < (sizeof(ccu_devices) / sizeof(device_descriptor_t)); i++) {
        if (ccu_devices[i].fd == fd) {
            ccu_devices[i].acquired = 0;
            return_value = 0;
            break;
        }
    }
    return return_value;
}

/**
 * @brief This function provides a generic interface for CCU operations
 *
 * @param fd base address of CCU controller (handler)
 * @param operation the operation to retrieve the CCU register
 * @param args the read/write data of the register
 * @param length the size of the read/write data
 * @param channel the channel index to be configured
 * @return 0 if successful
 */

int32_t ccu_ioctl(int32_t fd, int32_t operation, uintptr_t args, size_t length, int32_t reg_offset) {
    int32_t return_value = -1;
    if ((length < sizeof(uint32_t)) || (((void *)(args)) == nullptr) || (fd == -1)) {
        return_value = -1;
    } else {
        switch ((ccu_ioctl_t)operation) {
        case IOCTL_CCU_DSU_CAIUIDR_GET:
            return_value = ccu_dsu_get_caiuidr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUFUIDR_GET:
            return_value = ccu_dsu_get_caiufuidr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTCR_GET:
            return_value = ccu_dsu_get_caiutcr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTCR_SET:
            return_value = ccu_dsu_set_caiutcr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTAR_GET:
            return_value = ccu_dsu_get_caiutar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUEDR_GET:
            return_value = ccu_dsu_get_caiuuedr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUEDR_SET:
            return_value = ccu_dsu_set_caiuuedr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUEIR_GET:
            return_value = ccu_dsu_get_caiuueir_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUEIR_SET:
            return_value = ccu_dsu_set_caiuueir_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUESR_GET:
            return_value = ccu_dsu_get_caiuuesr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUESR_SET:
            return_value = ccu_dsu_set_caiuuesr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUELR0_GET:
            return_value = ccu_dsu_get_caiuuelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUELR0_SET:
            return_value = ccu_dsu_set_caiuuelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUELR1_GET:
            return_value = ccu_dsu_get_caiuuelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUELR1_SET:
            return_value = ccu_dsu_set_caiuuelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUESAR_GET:
            return_value = ccu_dsu_get_caiuuesar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUESAR_SET:
            return_value = ccu_dsu_set_caiuuesar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCRTR_GET:
            return_value = ccu_dsu_get_caiucrtr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCRTR_SET:
            return_value = ccu_dsu_set_caiucrtr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOCR_GET:
            return_value = ccu_dsu_get_caiutocr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOCR_SET:
            return_value = ccu_dsu_set_caiutocr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUQOSCR_GET:
            return_value = ccu_dsu_get_caiuqoscr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUQOSCR_SET:
            return_value = ccu_dsu_set_caiuqoscr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUQOSSR_GET:
            return_value = ccu_dsu_get_caiuqossr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUQOSSR_SET:
            return_value = ccu_dsu_set_caiuqossr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBAR_GET:
            return_value = ccu_dsu_get_nrsbar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBAR_SET:
            return_value = ccu_dsu_set_nrsbar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBHR_GET:
            return_value = ccu_dsu_get_nrsbhr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBHR_SET:
            return_value = ccu_dsu_set_nrsbhr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBLR_GET:
            return_value = ccu_dsu_get_nrsblr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_NRSBLR_SET:
            return_value = ccu_dsu_set_nrsblr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRAR_GET:
            return_value = ccu_dsu_get_caiubrar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRAR_SET:
            return_value = ccu_dsu_set_caiubrar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRBLR_GET:
            return_value = ccu_dsu_get_caiubrblr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRBLR_SET:
            return_value = ccu_dsu_set_caiubrblr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRBHR_GET:
            return_value = ccu_dsu_get_caiubrbhr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUBRBHR_SET:
            return_value = ccu_dsu_set_caiubrbhr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUAMIGR_GET:
            return_value = ccu_dsu_get_caiuamigr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUAMIGR_SET:
            return_value = ccu_dsu_set_caiuamigr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUMIFSR_GET:
            return_value = ccu_dsu_get_caiumifsr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUMIFSR_SET:
            return_value = ccu_dsu_set_caiumifsr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR0_GET:
            return_value = ccu_dsu_get_caiugprar0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR0_SET:
            return_value = ccu_dsu_set_caiugprar0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR0_GET:
            return_value = ccu_dsu_get_caiugprblr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR0_SET:
            return_value = ccu_dsu_set_caiugprblr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR0_GET:
            return_value = ccu_dsu_get_caiugprbhr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR0_SET:
            return_value = ccu_dsu_set_caiugprbhr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR1_GET:
            return_value = ccu_dsu_get_caiugprar1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR1_SET:
            return_value = ccu_dsu_set_caiugprar1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR1_GET:
            return_value = ccu_dsu_get_caiugprblr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR1_SET:
            return_value = ccu_dsu_set_caiugprblr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR1_GET:
            return_value = ccu_dsu_get_caiugprbhr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR1_SET:
            return_value = ccu_dsu_set_caiugprbhr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR2_GET:
            return_value = ccu_dsu_get_caiugprar2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR2_SET:
            return_value = ccu_dsu_set_caiugprar2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR2_GET:
            return_value = ccu_dsu_get_caiugprblr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR2_SET:
            return_value = ccu_dsu_set_caiugprblr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR2_GET:
            return_value = ccu_dsu_get_caiugprbhr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR2_SET:
            return_value = ccu_dsu_set_caiugprbhr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR11_GET:
            return_value = ccu_dsu_get_caiugprar11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRAR11_SET:
            return_value = ccu_dsu_set_caiugprar11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR11_GET:
            return_value = ccu_dsu_get_caiugprblr11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBLR11_SET:
            return_value = ccu_dsu_set_caiugprblr11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR11_GET:
            return_value = ccu_dsu_get_caiugprbhr11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUGPRBHR11_SET:
            return_value = ccu_dsu_set_caiugprbhr11_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCCTRLR_GET:
            return_value = ccu_dsu_get_caiucctrlr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCCTRLR_SET:
            return_value = ccu_dsu_set_caiucctrlr_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTCTRLR0_GET:
            return_value = ccu_dsu_get_caiutctrlr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTCTRLR0_SET:
            return_value = ccu_dsu_set_caiutctrlr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTBALR0_GET:
            return_value = ccu_dsu_get_caiutbalr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTBALR0_SET:
            return_value = ccu_dsu_set_caiutbalr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTBAHR0_GET:
            return_value = ccu_dsu_get_caiutbahr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTBAHR0_SET:
            return_value = ccu_dsu_set_caiutbahr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOPCR00_GET:
            return_value = ccu_dsu_get_caiutopcr00_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOPCR00_SET:
            return_value = ccu_dsu_set_caiutopcr00_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOPCR10_GET:
            return_value = ccu_dsu_get_caiutopcr10_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTOPCR10_SET:
            return_value = ccu_dsu_set_caiutopcr10_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTUBR0_GET:
            return_value = ccu_dsu_get_caiutubr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTUBR0_SET:
            return_value = ccu_dsu_set_caiutubr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTUBMR0_GET:
            return_value = ccu_dsu_get_caiutubmr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUTUBMR0_SET:
            return_value = ccu_dsu_set_caiutubmr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR0_GET:
            return_value = ccu_dsu_get_caiucntcr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR0_SET:
            return_value = ccu_dsu_set_caiucntcr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR0_GET:
            return_value = ccu_dsu_get_caiucntvr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR0_SET:
            return_value = ccu_dsu_set_caiucntvr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR0_GET:
            return_value = ccu_dsu_get_caiucntsr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR0_SET:
            return_value = ccu_dsu_set_caiucntsr0_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR1_GET:
            return_value = ccu_dsu_get_caiucntcr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR1_SET:
            return_value = ccu_dsu_set_caiucntcr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR1_GET:
            return_value = ccu_dsu_get_caiucntvr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR1_SET:
            return_value = ccu_dsu_set_caiucntvr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR1_GET:
            return_value = ccu_dsu_get_caiucntsr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR1_SET:
            return_value = ccu_dsu_set_caiucntsr1_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR2_GET:
            return_value = ccu_dsu_get_caiucntcr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR2_SET:
            return_value = ccu_dsu_set_caiucntcr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR2_GET:
            return_value = ccu_dsu_get_caiucntvr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR2_SET:
            return_value = ccu_dsu_set_caiucntvr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR2_GET:
            return_value = ccu_dsu_get_caiucntsr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR2_SET:
            return_value = ccu_dsu_set_caiucntsr2_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR3_GET:
            return_value = ccu_dsu_get_caiucntcr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTCR3_SET:
            return_value = ccu_dsu_set_caiucntcr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR3_GET:
            return_value = ccu_dsu_get_caiucntvr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTVR3_SET:
            return_value = ccu_dsu_set_caiucntvr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR3_GET:
            return_value = ccu_dsu_get_caiucntsr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUCNTSR3_SET:
            return_value = ccu_dsu_set_caiucntsr3_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUNRSAR_GET:
            return_value = ccu_dsu_get_caiunrsar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUNRSAR_SET:
            return_value = ccu_dsu_set_caiunrsar_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUUEVIR_GET:
            return_value = ccu_dsu_get_caiuuevir_reg(fd, args);
            break;
        case IOCTL_CCU_DSU_CAIUINFOR_GET:
            return_value = ccu_dsu_get_caiuinfor_reg(fd, args);
            break;
        case IOCTL_CCU_NCAIU_XAIUIDR_GET:
            return_value = ccu_ncaiu_get_xaiuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUFUIDR_GET:
            return_value = ccu_ncaiu_get_xaiufuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTCR_GET:
            return_value = ccu_ncaiu_get_xaiutcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTCR_SET:
            return_value = ccu_ncaiu_set_xaiutcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTAR_GET:
            return_value = ccu_ncaiu_get_xaiutar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUEDR_GET:
            return_value = ccu_ncaiu_get_xaiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUEDR_SET:
            return_value = ccu_ncaiu_set_xaiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUEIR_GET:
            return_value = ccu_ncaiu_get_xaiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUEIR_SET:
            return_value = ccu_ncaiu_set_xaiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUESR_GET:
            return_value = ccu_ncaiu_get_xaiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUESR_SET:
            return_value = ccu_ncaiu_set_xaiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUELR0_GET:
            return_value = ccu_ncaiu_get_xaiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUELR0_SET:
            return_value = ccu_ncaiu_set_xaiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUELR1_GET:
            return_value = ccu_ncaiu_get_xaiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUELR1_SET:
            return_value = ccu_ncaiu_set_xaiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUESAR_GET:
            return_value = ccu_ncaiu_get_xaiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUUESAR_SET:
            return_value = ccu_ncaiu_set_xaiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCECR_GET:
            return_value = ccu_ncaiu_get_xaiucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCECR_SET:
            return_value = ccu_ncaiu_set_xaiucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCESR_GET:
            return_value = ccu_ncaiu_get_xaiucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCESR_SET:
            return_value = ccu_ncaiu_set_xaiucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCELR0_GET:
            return_value = ccu_ncaiu_get_xaiucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCELR0_SET:
            return_value = ccu_ncaiu_set_xaiucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCELR1_GET:
            return_value = ccu_ncaiu_get_xaiucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCELR1_SET:
            return_value = ccu_ncaiu_set_xaiucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCESAR_GET:
            return_value = ccu_ncaiu_get_xaiucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCESAR_SET:
            return_value = ccu_ncaiu_set_xaiucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCRTR_GET:
            return_value = ccu_ncaiu_get_xaiucrtr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCRTR_SET:
            return_value = ccu_ncaiu_set_xaiucrtr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOCR_GET:
            return_value = ccu_ncaiu_get_xaiutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOCR_SET:
            return_value = ccu_ncaiu_set_xaiutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUQOSCR_GET:
            return_value = ccu_ncaiu_get_xaiuqoscr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUQOSCR_SET:
            return_value = ccu_ncaiu_set_xaiuqoscr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUQOSSR_GET:
            return_value = ccu_ncaiu_get_xaiuqossr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUQOSSR_SET:
            return_value = ccu_ncaiu_set_xaiuqossr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUNRSBAR_GET:
            return_value = ccu_ncaiu_get_xaiunrsbar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUNRSBHR_GET:
            return_value = ccu_ncaiu_get_xaiunrsbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUNRSBHR_SET:
            return_value = ccu_ncaiu_set_xaiunrsbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUNRSBLR_GET:
            return_value = ccu_ncaiu_get_xaiunrsblr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRAR_GET:
            return_value = ccu_ncaiu_get_xaiubrar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRAR_SET:
            return_value = ccu_ncaiu_set_xaiubrar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRBLR_GET:
            return_value = ccu_ncaiu_get_xaiubrblr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRBLR_SET:
            return_value = ccu_ncaiu_set_xaiubrblr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRBHR_GET:
            return_value = ccu_ncaiu_get_xaiubrbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUBRBHR_SET:
            return_value = ccu_ncaiu_set_xaiubrbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUAMIGR_GET:
            return_value = ccu_ncaiu_get_xaiuamigr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUAMIGR_SET:
            return_value = ccu_ncaiu_set_xaiuamigr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUMIFSR_GET:
            return_value = ccu_ncaiu_get_xaiumifsr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUMIFSR_SET:
            return_value = ccu_ncaiu_set_xaiumifsr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR0_GET:
            return_value = ccu_ncaiu_get_xaiugprar0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR0_SET:
            return_value = ccu_ncaiu_set_xaiugprar0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR0_GET:
            return_value = ccu_ncaiu_get_xaiugprblr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR0_SET:
            return_value = ccu_ncaiu_set_xaiugprblr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR0_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR0_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR1_GET:
            return_value = ccu_ncaiu_get_xaiugprar1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR1_SET:
            return_value = ccu_ncaiu_set_xaiugprar1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR1_GET:
            return_value = ccu_ncaiu_get_xaiugprblr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR1_SET:
            return_value = ccu_ncaiu_set_xaiugprblr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR1_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR1_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR2_GET:
            return_value = ccu_ncaiu_get_xaiugprar2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR2_SET:
            return_value = ccu_ncaiu_set_xaiugprar2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR2_GET:
            return_value = ccu_ncaiu_get_xaiugprblr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR2_SET:
            return_value = ccu_ncaiu_set_xaiugprblr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR2_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR2_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR3_GET:
            return_value = ccu_ncaiu_get_xaiugprar3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR3_SET:
            return_value = ccu_ncaiu_set_xaiugprar3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR3_GET:
            return_value = ccu_ncaiu_get_xaiugprblr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR3_SET:
            return_value = ccu_ncaiu_set_xaiugprblr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR3_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR3_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR4_GET:
            return_value = ccu_ncaiu_get_xaiugprar4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR4_SET:
            return_value = ccu_ncaiu_set_xaiugprar4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR4_GET:
            return_value = ccu_ncaiu_get_xaiugprblr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR4_SET:
            return_value = ccu_ncaiu_set_xaiugprblr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR4_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR4_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR5_GET:
            return_value = ccu_ncaiu_get_xaiugprar5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR5_SET:
            return_value = ccu_ncaiu_set_xaiugprar5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR5_GET:
            return_value = ccu_ncaiu_get_xaiugprblr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR5_SET:
            return_value = ccu_ncaiu_set_xaiugprblr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR5_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR5_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR6_GET:
            return_value = ccu_ncaiu_get_xaiugprar6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR6_SET:
            return_value = ccu_ncaiu_set_xaiugprar6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR6_GET:
            return_value = ccu_ncaiu_get_xaiugprblr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR6_SET:
            return_value = ccu_ncaiu_set_xaiugprblr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR6_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR6_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR7_GET:
            return_value = ccu_ncaiu_get_xaiugprar7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR7_SET:
            return_value = ccu_ncaiu_set_xaiugprar7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR7_GET:
            return_value = ccu_ncaiu_get_xaiugprblr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR7_SET:
            return_value = ccu_ncaiu_set_xaiugprblr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR7_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR7_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR8_GET:
            return_value = ccu_ncaiu_get_xaiugprar8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR8_SET:
            return_value = ccu_ncaiu_set_xaiugprar8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR8_GET:
            return_value = ccu_ncaiu_get_xaiugprblr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR8_SET:
            return_value = ccu_ncaiu_set_xaiugprblr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR8_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR8_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR9_GET:
            return_value = ccu_ncaiu_get_xaiugprar9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR9_SET:
            return_value = ccu_ncaiu_set_xaiugprar9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR9_GET:
            return_value = ccu_ncaiu_get_xaiugprblr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR9_SET:
            return_value = ccu_ncaiu_set_xaiugprblr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR9_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR9_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR10_GET:
            return_value = ccu_ncaiu_get_xaiugprar10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR10_SET:
            return_value = ccu_ncaiu_set_xaiugprar10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR10_GET:
            return_value = ccu_ncaiu_get_xaiugprblr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR10_SET:
            return_value = ccu_ncaiu_set_xaiugprblr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR10_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR10_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR11_GET:
            return_value = ccu_ncaiu_get_xaiugprar11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRAR11_SET:
            return_value = ccu_ncaiu_set_xaiugprar11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR11_GET:
            return_value = ccu_ncaiu_get_xaiugprblr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBLR11_SET:
            return_value = ccu_ncaiu_set_xaiugprblr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR11_GET:
            return_value = ccu_ncaiu_get_xaiugprbhr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUGPRBHR11_SET:
            return_value = ccu_ncaiu_set_xaiugprbhr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTBALR0_GET:
            return_value = ccu_ncaiu_get_xaiutbalr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTBALR0_SET:
            return_value = ccu_ncaiu_set_xaiutbalr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTBAHR0_GET:
            return_value = ccu_ncaiu_get_xaiutbahr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTBAHR0_SET:
            return_value = ccu_ncaiu_set_xaiutbahr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOPCR00_GET:
            return_value = ccu_ncaiu_get_xaiutopcr00_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOPCR00_SET:
            return_value = ccu_ncaiu_set_xaiutopcr00_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOPCR10_GET:
            return_value = ccu_ncaiu_get_xaiutopcr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTOPCR10_SET:
            return_value = ccu_ncaiu_set_xaiutopcr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTUBR0_GET:
            return_value = ccu_ncaiu_get_xaiutubr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTUBR0_SET:
            return_value = ccu_ncaiu_set_xaiutubr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTUBMR0_GET:
            return_value = ccu_ncaiu_get_xaiutubmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTUBMR0_SET:
            return_value = ccu_ncaiu_set_xaiutubmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCCTRLR_GET:
            return_value = ccu_ncaiu_get_xaiucctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCCTRLR_SET:
            return_value = ccu_ncaiu_set_xaiucctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTCTRLR0_GET:
            return_value = ccu_ncaiu_get_xaiutctrlr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUTCTRLR0_SET:
            return_value = ccu_ncaiu_set_xaiutctrlr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR0_GET:
            return_value = ccu_ncaiu_get_xaiuedr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR0_SET:
            return_value = ccu_ncaiu_set_xaiuedr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR1_GET:
            return_value = ccu_ncaiu_get_xaiuedr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR1_SET:
            return_value = ccu_ncaiu_set_xaiuedr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR2_GET:
            return_value = ccu_ncaiu_get_xaiuedr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR2_SET:
            return_value = ccu_ncaiu_set_xaiuedr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR3_GET:
            return_value = ccu_ncaiu_get_xaiuedr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR3_SET:
            return_value = ccu_ncaiu_set_xaiuedr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR4_GET:
            return_value = ccu_ncaiu_get_xaiuedr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR4_SET:
            return_value = ccu_ncaiu_set_xaiuedr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR5_GET:
            return_value = ccu_ncaiu_get_xaiuedr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR5_SET:
            return_value = ccu_ncaiu_set_xaiuedr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR6_GET:
            return_value = ccu_ncaiu_get_xaiuedr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR6_SET:
            return_value = ccu_ncaiu_set_xaiuedr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR7_GET:
            return_value = ccu_ncaiu_get_xaiuedr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUEDR7_SET:
            return_value = ccu_ncaiu_set_xaiuedr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR0_GET:
            return_value = ccu_ncaiu_get_xaiucntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR0_SET:
            return_value = ccu_ncaiu_set_xaiucntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR0_GET:
            return_value = ccu_ncaiu_get_xaiucntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR0_SET:
            return_value = ccu_ncaiu_set_xaiucntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR0_GET:
            return_value = ccu_ncaiu_get_xaiucntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR0_SET:
            return_value = ccu_ncaiu_set_xaiucntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR1_GET:
            return_value = ccu_ncaiu_get_xaiucntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR1_SET:
            return_value = ccu_ncaiu_set_xaiucntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR1_GET:
            return_value = ccu_ncaiu_get_xaiucntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR1_SET:
            return_value = ccu_ncaiu_set_xaiucntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR1_GET:
            return_value = ccu_ncaiu_get_xaiucntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR1_SET:
            return_value = ccu_ncaiu_set_xaiucntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR2_GET:
            return_value = ccu_ncaiu_get_xaiucntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR2_SET:
            return_value = ccu_ncaiu_set_xaiucntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR2_GET:
            return_value = ccu_ncaiu_get_xaiucntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR2_SET:
            return_value = ccu_ncaiu_set_xaiucntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR2_GET:
            return_value = ccu_ncaiu_get_xaiucntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR2_SET:
            return_value = ccu_ncaiu_set_xaiucntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR3_GET:
            return_value = ccu_ncaiu_get_xaiucntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTCR3_SET:
            return_value = ccu_ncaiu_set_xaiucntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR3_GET:
            return_value = ccu_ncaiu_get_xaiucntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTVR3_SET:
            return_value = ccu_ncaiu_set_xaiucntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR3_GET:
            return_value = ccu_ncaiu_get_xaiucntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUCNTSR3_SET:
            return_value = ccu_ncaiu_set_xaiucntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUNRSAR_GET:
            return_value = ccu_ncaiu_get_xaiunrsar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUENGIDR_GET:
            return_value = ccu_ncaiu_get_xaiuengidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_NCAIU_XAIUINFOR_GET:
            return_value = ccu_ncaiu_get_xaiuinfor_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUIDR_GET:
            return_value = ccu_dce_get_dceuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUFUIDR_GET:
            return_value = ccu_dce_get_dceufuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUTCR_GET:
            return_value = ccu_dce_get_dceutcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUTCR_SET:
            return_value = ccu_dce_set_dceutcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUTAR_GET:
            return_value = ccu_dce_get_dceutar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSER0_GET:
            return_value = ccu_dce_get_dceuser0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSER0_SET:
            return_value = ccu_dce_set_dceuser0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCECR_GET:
            return_value = ccu_dce_get_dceucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCECR_SET:
            return_value = ccu_dce_set_dceucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCESR_GET:
            return_value = ccu_dce_get_dceucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCESR_SET:
            return_value = ccu_dce_set_dceucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCELR0_GET:
            return_value = ccu_dce_get_dceucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCELR0_SET:
            return_value = ccu_dce_set_dceucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCELR1_GET:
            return_value = ccu_dce_get_dceucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCELR1_SET:
            return_value = ccu_dce_set_dceucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCESAR_GET:
            return_value = ccu_dce_get_dceucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCESAR_SET:
            return_value = ccu_dce_set_dceucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUEDR_GET:
            return_value = ccu_dce_get_dceuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUEDR_SET:
            return_value = ccu_dce_set_dceuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUEIR_GET:
            return_value = ccu_dce_get_dceuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUEIR_SET:
            return_value = ccu_dce_set_dceuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUESR_GET:
            return_value = ccu_dce_get_dceuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUESR_SET:
            return_value = ccu_dce_set_dceuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUELR0_GET:
            return_value = ccu_dce_get_dceuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUELR0_SET:
            return_value = ccu_dce_set_dceuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUELR1_GET:
            return_value = ccu_dce_get_dceuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUELR1_SET:
            return_value = ccu_dce_set_dceuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUESAR_GET:
            return_value = ccu_dce_get_dceuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUUESAR_SET:
            return_value = ccu_dce_set_dceuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUTOCR_GET:
            return_value = ccu_dce_get_dceutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUTOCR_SET:
            return_value = ccu_dce_set_dceutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUQOSCR0_GET:
            return_value = ccu_dce_get_dceuqoscr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUQOSCR0_SET:
            return_value = ccu_dce_set_dceuqoscr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSFMCR_GET:
            return_value = ccu_dce_get_dceusfmcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSFMCR_SET:
            return_value = ccu_dce_set_dceusfmcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSFMAR_GET:
            return_value = ccu_dce_get_dceusfmar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRAR_GET:
            return_value = ccu_dce_get_dceubrar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRAR_SET:
            return_value = ccu_dce_set_dceubrar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRBLR_GET:
            return_value = ccu_dce_get_dceubrblr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRBLR_SET:
            return_value = ccu_dce_set_dceubrblr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRBHR_GET:
            return_value = ccu_dce_get_dceubrbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUBRBHR_SET:
            return_value = ccu_dce_set_dceubrbhr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUAMIGR_GET:
            return_value = ccu_dce_get_dceuamigr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUAMIGR_SET:
            return_value = ccu_dce_set_dceuamigr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUMIFSR_GET:
            return_value = ccu_dce_get_dceumifsr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUMIFSR_SET:
            return_value = ccu_dce_set_dceumifsr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR0_GET:
            return_value = ccu_dce_get_dceugprar0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR0_SET:
            return_value = ccu_dce_set_dceugprar0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR0_GET:
            return_value = ccu_dce_get_dceugprblr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR0_SET:
            return_value = ccu_dce_set_dceugprblr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR0_GET:
            return_value = ccu_dce_get_dceugprbhr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR0_SET:
            return_value = ccu_dce_set_dceugprbhr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR1_GET:
            return_value = ccu_dce_get_dceugprar1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR1_SET:
            return_value = ccu_dce_set_dceugprar1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR1_GET:
            return_value = ccu_dce_get_dceugprblr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR1_SET:
            return_value = ccu_dce_set_dceugprblr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR1_GET:
            return_value = ccu_dce_get_dceugprbhr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR1_SET:
            return_value = ccu_dce_set_dceugprbhr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR2_GET:
            return_value = ccu_dce_get_dceugprar2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR2_SET:
            return_value = ccu_dce_set_dceugprar2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR2_GET:
            return_value = ccu_dce_get_dceugprblr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR2_SET:
            return_value = ccu_dce_set_dceugprblr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR2_GET:
            return_value = ccu_dce_get_dceugprbhr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR2_SET:
            return_value = ccu_dce_set_dceugprbhr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR3_GET:
            return_value = ccu_dce_get_dceugprar3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR3_SET:
            return_value = ccu_dce_set_dceugprar3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR3_GET:
            return_value = ccu_dce_get_dceugprblr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR3_SET:
            return_value = ccu_dce_set_dceugprblr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR3_GET:
            return_value = ccu_dce_get_dceugprbhr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR3_SET:
            return_value = ccu_dce_set_dceugprbhr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR4_GET:
            return_value = ccu_dce_get_dceugprar4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR4_SET:
            return_value = ccu_dce_set_dceugprar4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR4_GET:
            return_value = ccu_dce_get_dceugprblr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR4_SET:
            return_value = ccu_dce_set_dceugprblr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR4_GET:
            return_value = ccu_dce_get_dceugprbhr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR4_SET:
            return_value = ccu_dce_set_dceugprbhr4_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR5_GET:
            return_value = ccu_dce_get_dceugprar5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR5_SET:
            return_value = ccu_dce_set_dceugprar5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR5_GET:
            return_value = ccu_dce_get_dceugprblr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR5_SET:
            return_value = ccu_dce_set_dceugprblr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR5_GET:
            return_value = ccu_dce_get_dceugprbhr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR5_SET:
            return_value = ccu_dce_set_dceugprbhr5_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR6_GET:
            return_value = ccu_dce_get_dceugprar6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR6_SET:
            return_value = ccu_dce_set_dceugprar6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR6_GET:
            return_value = ccu_dce_get_dceugprblr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR6_SET:
            return_value = ccu_dce_set_dceugprblr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR6_GET:
            return_value = ccu_dce_get_dceugprbhr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR6_SET:
            return_value = ccu_dce_set_dceugprbhr6_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR7_GET:
            return_value = ccu_dce_get_dceugprar7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR7_SET:
            return_value = ccu_dce_set_dceugprar7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR7_GET:
            return_value = ccu_dce_get_dceugprblr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR7_SET:
            return_value = ccu_dce_set_dceugprblr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR7_GET:
            return_value = ccu_dce_get_dceugprbhr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR7_SET:
            return_value = ccu_dce_set_dceugprbhr7_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR8_GET:
            return_value = ccu_dce_get_dceugprar8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR8_SET:
            return_value = ccu_dce_set_dceugprar8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR8_GET:
            return_value = ccu_dce_get_dceugprblr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR8_SET:
            return_value = ccu_dce_set_dceugprblr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR8_GET:
            return_value = ccu_dce_get_dceugprbhr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR8_SET:
            return_value = ccu_dce_set_dceugprbhr8_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR9_GET:
            return_value = ccu_dce_get_dceugprar9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR9_SET:
            return_value = ccu_dce_set_dceugprar9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR9_GET:
            return_value = ccu_dce_get_dceugprblr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR9_SET:
            return_value = ccu_dce_set_dceugprblr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR9_GET:
            return_value = ccu_dce_get_dceugprbhr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR9_SET:
            return_value = ccu_dce_set_dceugprbhr9_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR10_GET:
            return_value = ccu_dce_get_dceugprar10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR10_SET:
            return_value = ccu_dce_set_dceugprar10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR10_GET:
            return_value = ccu_dce_get_dceugprblr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR10_SET:
            return_value = ccu_dce_set_dceugprblr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR10_GET:
            return_value = ccu_dce_get_dceugprbhr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR10_SET:
            return_value = ccu_dce_set_dceugprbhr10_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR11_GET:
            return_value = ccu_dce_get_dceugprar11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRAR11_SET:
            return_value = ccu_dce_set_dceugprar11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR11_GET:
            return_value = ccu_dce_get_dceugprblr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBLR11_SET:
            return_value = ccu_dce_set_dceugprblr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR11_GET:
            return_value = ccu_dce_get_dceugprbhr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUGPRBHR11_SET:
            return_value = ccu_dce_set_dceugprbhr11_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUEDR0_GET:
            return_value = ccu_dce_get_dceuedr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUEDR0_SET:
            return_value = ccu_dce_set_dceuedr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR0_GET:
            return_value = ccu_dce_get_dcecntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR0_SET:
            return_value = ccu_dce_set_dcecntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR0_GET:
            return_value = ccu_dce_get_dcecntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR0_SET:
            return_value = ccu_dce_set_dcecntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR0_GET:
            return_value = ccu_dce_get_dcecntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR0_SET:
            return_value = ccu_dce_set_dcecntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR1_GET:
            return_value = ccu_dce_get_dcecntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR1_SET:
            return_value = ccu_dce_set_dcecntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR1_GET:
            return_value = ccu_dce_get_dcecntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR1_SET:
            return_value = ccu_dce_set_dcecntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR1_GET:
            return_value = ccu_dce_get_dcecntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR1_SET:
            return_value = ccu_dce_set_dcecntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR2_GET:
            return_value = ccu_dce_get_dcecntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR2_SET:
            return_value = ccu_dce_set_dcecntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR2_GET:
            return_value = ccu_dce_get_dcecntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR2_SET:
            return_value = ccu_dce_set_dcecntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR2_GET:
            return_value = ccu_dce_get_dcecntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR2_SET:
            return_value = ccu_dce_set_dcecntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR3_GET:
            return_value = ccu_dce_get_dcecntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTCR3_SET:
            return_value = ccu_dce_set_dcecntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR3_GET:
            return_value = ccu_dce_get_dcecntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTVR3_SET:
            return_value = ccu_dce_set_dcecntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR3_GET:
            return_value = ccu_dce_get_dcecntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCECNTSR3_SET:
            return_value = ccu_dce_set_dcecntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCCR0_GET:
            return_value = ccu_dce_get_dceuccr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCCR0_SET:
            return_value = ccu_dce_set_dceuccr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCCR1_GET:
            return_value = ccu_dce_get_dceuccr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUCCR1_SET:
            return_value = ccu_dce_set_dceuccr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEMCNTCR_GET:
            return_value = ccu_dce_get_dcemcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEMCNTCR_SET:
            return_value = ccu_dce_set_dcemcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUSBSIR_GET:
            return_value = ccu_dce_get_dceusbsir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUENGIDR_GET:
            return_value = ccu_dce_get_dceuengidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DCE_DCEUINFOR_GET:
            return_value = ccu_dce_get_dceuinfor_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUIDR_GET:
            return_value = ccu_dmi_get_dmiuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUFUIDR_GET:
            return_value = ccu_dmi_get_dmiufuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUTAR_GET:
            return_value = ccu_dmi_get_dmiutar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUEDR_GET:
            return_value = ccu_dmi_get_dmiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUEDR_SET:
            return_value = ccu_dmi_set_dmiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUEIR_GET:
            return_value = ccu_dmi_get_dmiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUEIR_SET:
            return_value = ccu_dmi_set_dmiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUESR_GET:
            return_value = ccu_dmi_get_dmiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUESR_SET:
            return_value = ccu_dmi_set_dmiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUELR0_GET:
            return_value = ccu_dmi_get_dmiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUELR0_SET:
            return_value = ccu_dmi_set_dmiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUELR1_GET:
            return_value = ccu_dmi_get_dmiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUELR1_SET:
            return_value = ccu_dmi_set_dmiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUESAR_GET:
            return_value = ccu_dmi_get_dmiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUUESAR_SET:
            return_value = ccu_dmi_set_dmiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCECR_GET:
            return_value = ccu_dmi_get_dmiucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCECR_SET:
            return_value = ccu_dmi_set_dmiucecr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCESR_GET:
            return_value = ccu_dmi_get_dmiucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCESR_SET:
            return_value = ccu_dmi_set_dmiucesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCELR0_GET:
            return_value = ccu_dmi_get_dmiucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCELR0_SET:
            return_value = ccu_dmi_set_dmiucelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCELR1_GET:
            return_value = ccu_dmi_get_dmiucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCELR1_SET:
            return_value = ccu_dmi_set_dmiucelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCESAR_GET:
            return_value = ccu_dmi_get_dmiucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUCESAR_SET:
            return_value = ccu_dmi_set_dmiucesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUTOCR_GET:
            return_value = ccu_dmi_get_dmiutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUTOCR_SET:
            return_value = ccu_dmi_set_dmiutocr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUQOSCR0_GET:
            return_value = ccu_dmi_get_dmiuqoscr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUQOSCR0_SET:
            return_value = ccu_dmi_set_dmiuqoscr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCTCR_GET:
            return_value = ccu_dmi_get_dmiusmctcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCTCR_SET:
            return_value = ccu_dmi_set_dmiusmctcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCTAR_GET:
            return_value = ccu_dmi_get_dmiusmctar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCAPR_GET:
            return_value = ccu_dmi_get_dmiusmcapr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCAPR_SET:
            return_value = ccu_dmi_set_dmiusmcapr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCISR_GET:
            return_value = ccu_dmi_get_dmiusmcisr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMCR_GET:
            return_value = ccu_dmi_get_dmiusmcmcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMCR_SET:
            return_value = ccu_dmi_set_dmiusmcmcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMAR_GET:
            return_value = ccu_dmi_get_dmiusmcmar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMLR0_GET:
            return_value = ccu_dmi_get_dmiusmcmlr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMLR0_SET:
            return_value = ccu_dmi_set_dmiusmcmlr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMLR1_GET:
            return_value = ccu_dmi_get_dmiusmcmlr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMLR1_SET:
            return_value = ccu_dmi_set_dmiusmcmlr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMDR_GET:
            return_value = ccu_dmi_get_dmiusmcmdr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCMDR_SET:
            return_value = ccu_dmi_set_dmiusmcmdr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICCTRLR_GET:
            return_value = ccu_dmi_get_dmicctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICCTRLR_SET:
            return_value = ccu_dmi_set_dmicctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR0_GET:
            return_value = ccu_dmi_get_dmicntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR0_SET:
            return_value = ccu_dmi_set_dmicntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR0_GET:
            return_value = ccu_dmi_get_dmicntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR0_SET:
            return_value = ccu_dmi_set_dmicntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR0_GET:
            return_value = ccu_dmi_get_dmicntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR0_SET:
            return_value = ccu_dmi_set_dmicntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR1_GET:
            return_value = ccu_dmi_get_dmicntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR1_SET:
            return_value = ccu_dmi_set_dmicntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR1_GET:
            return_value = ccu_dmi_get_dmicntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR1_SET:
            return_value = ccu_dmi_set_dmicntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR1_GET:
            return_value = ccu_dmi_get_dmicntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR1_SET:
            return_value = ccu_dmi_set_dmicntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR2_GET:
            return_value = ccu_dmi_get_dmicntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR2_SET:
            return_value = ccu_dmi_set_dmicntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR2_GET:
            return_value = ccu_dmi_get_dmicntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR2_SET:
            return_value = ccu_dmi_set_dmicntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR2_GET:
            return_value = ccu_dmi_get_dmicntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR2_SET:
            return_value = ccu_dmi_set_dmicntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR3_GET:
            return_value = ccu_dmi_get_dmicntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTCR3_SET:
            return_value = ccu_dmi_set_dmicntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR3_GET:
            return_value = ccu_dmi_get_dmicntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTVR3_SET:
            return_value = ccu_dmi_set_dmicntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR3_GET:
            return_value = ccu_dmi_get_dmicntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMICNTSR3_SET:
            return_value = ccu_dmi_set_dmicntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR0_GET:
            return_value = ccu_dmi_get_dmibcntfr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR0_SET:
            return_value = ccu_dmi_set_dmibcntfr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR0_GET:
            return_value = ccu_dmi_get_dmibcntmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR0_SET:
            return_value = ccu_dmi_set_dmibcntmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR1_GET:
            return_value = ccu_dmi_get_dmibcntfr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR1_SET:
            return_value = ccu_dmi_set_dmibcntfr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR1_GET:
            return_value = ccu_dmi_get_dmibcntmr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR1_SET:
            return_value = ccu_dmi_set_dmibcntmr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR2_GET:
            return_value = ccu_dmi_get_dmibcntfr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR2_SET:
            return_value = ccu_dmi_set_dmibcntfr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR2_GET:
            return_value = ccu_dmi_get_dmibcntmr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR2_SET:
            return_value = ccu_dmi_set_dmibcntmr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR3_GET:
            return_value = ccu_dmi_get_dmibcntfr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTFR3_SET:
            return_value = ccu_dmi_set_dmibcntfr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR3_GET:
            return_value = ccu_dmi_get_dmibcntmr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIBCNTMR3_SET:
            return_value = ccu_dmi_set_dmibcntmr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMILCNTCR_GET:
            return_value = ccu_dmi_get_dmilcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMILCNTCR_SET:
            return_value = ccu_dmi_set_dmilcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIMCNTCR_GET:
            return_value = ccu_dmi_get_dmimcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIMCNTCR_SET:
            return_value = ccu_dmi_set_dmimcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_MRDSBSIR_GET:
            return_value = ccu_dmi_get_mrdsbsir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_CMDSBSIR_GET:
            return_value = ccu_dmi_get_cmdsbsir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUEVIDR_GET:
            return_value = ccu_dmi_get_dmiuevidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUSMCIFR_GET:
            return_value = ccu_dmi_get_dmiusmcifr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DMI_DMIUINFOR_GET:
            return_value = ccu_dmi_get_dmiuinfor_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUIDR_GET:
            return_value = ccu_dii_get_diiuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUFUIDR_GET:
            return_value = ccu_dii_get_diiufuidr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUTAR_GET:
            return_value = ccu_dii_get_diiutar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUEDR_GET:
            return_value = ccu_dii_get_diiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUEDR_SET:
            return_value = ccu_dii_set_diiuuedr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUEIR_GET:
            return_value = ccu_dii_get_diiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUEIR_SET:
            return_value = ccu_dii_set_diiuueir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUESR_GET:
            return_value = ccu_dii_get_diiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUESR_SET:
            return_value = ccu_dii_set_diiuuesr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUELR0_GET:
            return_value = ccu_dii_get_diiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUELR0_SET:
            return_value = ccu_dii_set_diiuuelr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUELR1_GET:
            return_value = ccu_dii_get_diiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUELR1_SET:
            return_value = ccu_dii_set_diiuuelr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUESAR_GET:
            return_value = ccu_dii_get_diiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUESAR_SET:
            return_value = ccu_dii_set_diiuuesar_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICCTRLR_GET:
            return_value = ccu_dii_get_diicctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICCTRLR_SET:
            return_value = ccu_dii_set_diicctrlr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR0_GET:
            return_value = ccu_dii_get_diicntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR0_SET:
            return_value = ccu_dii_set_diicntcr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR0_GET:
            return_value = ccu_dii_get_diicntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR0_SET:
            return_value = ccu_dii_set_diicntvr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR0_GET:
            return_value = ccu_dii_get_diicntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR0_SET:
            return_value = ccu_dii_set_diicntsr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR1_GET:
            return_value = ccu_dii_get_diicntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR1_SET:
            return_value = ccu_dii_set_diicntcr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR1_GET:
            return_value = ccu_dii_get_diicntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR1_SET:
            return_value = ccu_dii_set_diicntvr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR1_GET:
            return_value = ccu_dii_get_diicntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR1_SET:
            return_value = ccu_dii_set_diicntsr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR2_GET:
            return_value = ccu_dii_get_diicntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR2_SET:
            return_value = ccu_dii_set_diicntcr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR2_GET:
            return_value = ccu_dii_get_diicntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR2_SET:
            return_value = ccu_dii_set_diicntvr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR2_GET:
            return_value = ccu_dii_get_diicntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR2_SET:
            return_value = ccu_dii_set_diicntsr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR3_GET:
            return_value = ccu_dii_get_diicntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTCR3_SET:
            return_value = ccu_dii_set_diicntcr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR3_GET:
            return_value = ccu_dii_get_diicntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTVR3_SET:
            return_value = ccu_dii_set_diicntvr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR3_GET:
            return_value = ccu_dii_get_diicntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIICNTSR3_SET:
            return_value = ccu_dii_set_diicntsr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR0_GET:
            return_value = ccu_dii_get_diibcntfr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR0_SET:
            return_value = ccu_dii_set_diibcntfr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR0_GET:
            return_value = ccu_dii_get_diibcntmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR0_SET:
            return_value = ccu_dii_set_diibcntmr0_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR1_GET:
            return_value = ccu_dii_get_diibcntfr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR1_SET:
            return_value = ccu_dii_set_diibcntfr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR1_GET:
            return_value = ccu_dii_get_diibcntmr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR1_SET:
            return_value = ccu_dii_set_diibcntmr1_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR2_GET:
            return_value = ccu_dii_get_diibcntfr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR2_SET:
            return_value = ccu_dii_set_diibcntfr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR2_GET:
            return_value = ccu_dii_get_diibcntmr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR2_SET:
            return_value = ccu_dii_set_diibcntmr2_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR3_GET:
            return_value = ccu_dii_get_diibcntfr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTFR3_SET:
            return_value = ccu_dii_set_diibcntfr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR3_GET:
            return_value = ccu_dii_get_diibcntmr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIBCNTMR3_SET:
            return_value = ccu_dii_set_diibcntmr3_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIILCNTCR_GET:
            return_value = ccu_dii_get_diilcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIILCNTCR_SET:
            return_value = ccu_dii_set_diilcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIMCNTCR_GET:
            return_value = ccu_dii_get_diimcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIMCNTCR_SET:
            return_value = ccu_dii_set_diimcntcr_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUSBSIR_GET:
            return_value = ccu_dii_get_diiusbsir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUUEVIR_GET:
            return_value = ccu_dii_get_diiuuevir_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DII_DIIUINFOR_GET:
            return_value = ccu_dii_get_diiuinfor_reg(fd, args, reg_offset);
            break;
        case IOCTL_CCU_DVE_DVEUIDR_GET:
            return_value = ccu_dve_get_dveuidr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUFUIDR_GET:
            return_value = ccu_dve_get_dveufuidr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUTAR_GET:
            return_value = ccu_dve_get_dveutar_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECECR_GET:
            return_value = ccu_dve_get_dvececr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECECR_SET:
            return_value = ccu_dve_set_dvececr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECESR_GET:
            return_value = ccu_dve_get_dvecesr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECESR_SET:
            return_value = ccu_dve_set_dvecesr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECELR0_GET:
            return_value = ccu_dve_get_dvecelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECELR0_SET:
            return_value = ccu_dve_set_dvecelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECELR1_GET:
            return_value = ccu_dve_get_dvecelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECELR1_SET:
            return_value = ccu_dve_set_dvecelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECESAR_GET:
            return_value = ccu_dve_get_dvecesar_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECESAR_SET:
            return_value = ccu_dve_set_dvecesar_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUEDR_GET:
            return_value = ccu_dve_get_dveuuedr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUEDR_SET:
            return_value = ccu_dve_set_dveuuedr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUEIR_GET:
            return_value = ccu_dve_get_dveuueir_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUEIR_SET:
            return_value = ccu_dve_set_dveuueir_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUESR_GET:
            return_value = ccu_dve_get_dveuuesr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUESR_SET:
            return_value = ccu_dve_set_dveuuesr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUELR0_GET:
            return_value = ccu_dve_get_dveuuelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUELR0_SET:
            return_value = ccu_dve_set_dveuuelr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUELR1_GET:
            return_value = ccu_dve_get_dveuuelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUUELR1_SET:
            return_value = ccu_dve_set_dveuuelr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUESAR_GET:
            return_value = ccu_dve_get_dveuesar_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUESAR_SET:
            return_value = ccu_dve_set_dveuesar_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUCRTR_GET:
            return_value = ccu_dve_get_dveucrtr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUCRTR_SET:
            return_value = ccu_dve_set_dveucrtr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUSER0_GET:
            return_value = ccu_dve_get_dveuser0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUSER0_SET:
            return_value = ccu_dve_set_dveuser0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETASCR_GET:
            return_value = ccu_dve_get_dvetascr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETASCR_SET:
            return_value = ccu_dve_set_dvetascr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETADHR_GET:
            return_value = ccu_dve_get_dvetadhr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETADTSR_GET:
            return_value = ccu_dve_get_dvetadtsr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD0R_GET:
            return_value = ccu_dve_get_dvetad0r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD1R_GET:
            return_value = ccu_dve_get_dvetad1r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD2R_GET:
            return_value = ccu_dve_get_dvetad2r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD3R_GET:
            return_value = ccu_dve_get_dvetad3r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD4R_GET:
            return_value = ccu_dve_get_dvetad4r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD5R_GET:
            return_value = ccu_dve_get_dvetad5r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD6R_GET:
            return_value = ccu_dve_get_dvetad6r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD7R_GET:
            return_value = ccu_dve_get_dvetad7r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD8R_GET:
            return_value = ccu_dve_get_dvetad8r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD9R_GET:
            return_value = ccu_dve_get_dvetad9r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD10R_GET:
            return_value = ccu_dve_get_dvetad10r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD11R_GET:
            return_value = ccu_dve_get_dvetad11r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD12R_GET:
            return_value = ccu_dve_get_dvetad12r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD13R_GET:
            return_value = ccu_dve_get_dvetad13r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD14R_GET:
            return_value = ccu_dve_get_dvetad14r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVETAD15R_GET:
            return_value = ccu_dve_get_dvetad15r_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR0_GET:
            return_value = ccu_dve_get_dvecntcr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR0_SET:
            return_value = ccu_dve_set_dvecntcr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR0_GET:
            return_value = ccu_dve_get_dvecntvr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR0_SET:
            return_value = ccu_dve_set_dvecntvr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR0_GET:
            return_value = ccu_dve_get_dvecntsr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR0_SET:
            return_value = ccu_dve_set_dvecntsr0_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR1_GET:
            return_value = ccu_dve_get_dvecntcr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR1_SET:
            return_value = ccu_dve_set_dvecntcr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR1_GET:
            return_value = ccu_dve_get_dvecntvr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR1_SET:
            return_value = ccu_dve_set_dvecntvr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR1_GET:
            return_value = ccu_dve_get_dvecntsr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR1_SET:
            return_value = ccu_dve_set_dvecntsr1_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR2_GET:
            return_value = ccu_dve_get_dvecntcr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR2_SET:
            return_value = ccu_dve_set_dvecntcr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR2_GET:
            return_value = ccu_dve_get_dvecntvr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR2_SET:
            return_value = ccu_dve_set_dvecntvr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR2_GET:
            return_value = ccu_dve_get_dvecntsr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR2_SET:
            return_value = ccu_dve_set_dvecntsr2_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR3_GET:
            return_value = ccu_dve_get_dvecntcr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTCR3_SET:
            return_value = ccu_dve_set_dvecntcr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR3_GET:
            return_value = ccu_dve_get_dvecntvr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTVR3_SET:
            return_value = ccu_dve_set_dvecntvr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR3_GET:
            return_value = ccu_dve_get_dvecntsr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVECNTSR3_SET:
            return_value = ccu_dve_set_dvecntsr3_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEMCNTCR_GET:
            return_value = ccu_dve_get_dvemcntcr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEMCNTCR_SET:
            return_value = ccu_dve_set_dvemcntcr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUENGDBR_GET:
            return_value = ccu_dve_get_dveuengdbr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUENGDBR_SET:
            return_value = ccu_dve_set_dveuengdbr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUENGIDR_GET:
            return_value = ccu_dve_get_dveuengidr_reg(fd, args);
            break;
        case IOCTL_CCU_DVE_DVEUINFOR_GET:
            return_value = ccu_dve_get_dveuinfor_reg(fd, args);
            break;
        case IOCTL_CCU_SYS_GLOBAL_GRBUCSSFIDR0_GET:
            return_value = ccu_sys_global_get_grbucssfidr0_reg(fd, args);
            break;
        case IOCTL_CCU_SYS_GLOBAL_GRBUNRRIR_GET:
            return_value = ccu_sys_global_get_grbunrrir_reg(fd, args);
            break;
        case IOCTL_CCU_SYS_GLOBAL_GRBUENGIDR_GET:
            return_value = ccu_sys_global_get_grbuengidr_reg(fd, args);
            break;
        case IOCTL_CCU_SYS_GLOBAL_GRBUNRRUCR_GET:
            return_value = ccu_sys_global_get_grbunrrucr_reg(fd, args);
            break;
        case IOCTL_CCU_SYS_GLOBAL_GRBUNSIDR_GET:
            return_value = ccu_sys_global_get_grbunsidr_reg(fd, args);
            break;
        default:
            return_value = -1;
            break;
        }
    }

    return return_value;
}
