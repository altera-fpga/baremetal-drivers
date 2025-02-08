#include "ccu.h"
#include "ccu_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

#define CCU_DSU_CAIUIDR_DEFAULT 0x80000000
#define CCU_DSU_CAIUINFOR_DEFAULT 0x80020348
#define CCU_NCAIU_XAIUINFOR_DEFAULT 0x80011348
#define CCU_DCE_DCEUINFOR_DEFAULT 0x80008348
#define CCU_DMI_DMIUINFOR_DEFAULT 0x80309348
#define CCU_DII_DIIUINFOR_DEFAULT 0x8000A348
#define CCU_DVE_DVEUINFOR_DEFAULT 0x8000B348
#define CCU_SYS_GLOBAL_GRBUNSIDR_DEFAULT 0x00001348

#define NCAIUx_NUM 4
#define DCE_NUM 2
#define DMI_NUM 2
#define DII_NUM 5

#define RST_MGR_PER0MODRST_DMA_MASK 0xFF210000
#define RST_MGR_PER1MODRST_UART_MASK 0x00030000
// #define RST_MGR_PER0MODRST_DMA_MASK 0xFF7FB8F8
// #define RST_MGR_PER1MODRST_UART_MASK 0x07037FFF

#ifdef __cplusplus
extern "C" {
#endif

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";
    const char ccu_initiator[] = "/dev/ccu";
    int32_t return_value = 0;

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    // regs_buffer.per0modrst &= ~((uint32_t)RST_MGR_PER0MODRST_DMA_MASK);
    regs_buffer.per1modrst &= ~((uint32_t)RST_MGR_PER1MODRST_UART_MASK);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    int32_t ccu_handle = ccu_open(ccu_initiator, 0);
    if (ccu_handle < 0) {
        return_value = ccu_handle;
        printf("ERROR: CCU failed open\n");
    } else {
        printf("CCU open\n");
        uint32_t param = 0;
        param = 0;

        if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DSU_CAIUIDR_GET, (uintptr_t)&param, sizeof(uint32_t), 0) == 0) {
            if (param == CCU_DSU_CAIUIDR_DEFAULT) {
                printf("Read DSU CAIUIDR default value SUCCESSFUL!\n");
            } else {
                printf("Read DSU CAIUIDR default value Failed: 0x%x, should be 0x%x!\n", param,
                       CCU_DSU_CAIUIDR_DEFAULT);
                return_value = -1;
            }
        } else {
            printf("ERROR: CCU ioctl failed\n");
            return_value = -1;
        }

        if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DSU_CAIUTCR_GET, (uintptr_t)&param, sizeof(uint32_t), 0) == 0) {
            if (param == 0) {
                printf("Read DSU CAIUTCR SUCCESSFUL!\n");
            } else {
                printf("Read DSU CAIUTCR Failed: 0x%x, should be 0x0!\n", param);
                return_value = -1;
            }
        } else {
            printf("ERROR: CCU ioctl failed\n");
            return_value = -1;
        }

        if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DSU_CAIUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t), 0) == 0) {
            if (param == CCU_DSU_CAIUINFOR_DEFAULT) {
                printf("Read DSU CAIUUEVIR SUCCESSFUL!\n");
            } else {
                printf("Warning: DSU CAIUUEVIR expected: 0x%x, observerd: 0x%x!\n", CCU_DSU_CAIUINFOR_DEFAULT, param);
            }
        } else {
            printf("ERROR: CCU ioctl failed\n");
            return_value = -1;
        }

        for (int32_t reg_off = 0; reg_off < NCAIUx_NUM; reg_off++) {
            if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_NCAIU_XAIUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t),
                          reg_off) == 0) {
                if (param == CCU_NCAIU_XAIUINFOR_DEFAULT) {
                    printf("Read NCAIU XAIUINFOR offset %d SUCCESSFUL!\n", reg_off);
                } else {
                    printf("Warning: NCAIU XAIUINFOR expected: 0x%x, observerd: 0x%x!\n", CCU_NCAIU_XAIUINFOR_DEFAULT,
                           param);
                }
            } else {
                printf("ERROR: CCU ioctl failed\n");
                return_value = -1;
            }
        }

        for (int32_t reg_off = 0; reg_off < DCE_NUM; reg_off++) {
            if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DCE_DCEUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t),
                          reg_off) == 0) {
                if (param == CCU_DCE_DCEUINFOR_DEFAULT) {
                    printf("Read DCE DCEUINFOR offset %d SUCCESSFUL!\n", reg_off);
                } else {
                    printf("Warning: DCE DCEUINFOR expected: 0x%x, observerd: 0x%x!\n", CCU_DCE_DCEUINFOR_DEFAULT,
                           param);
                }
            } else {
                printf("ERROR: CCU ioctl failed\n");
                return_value = -1;
            }
        }

        for (int32_t reg_off = 0; reg_off < DMI_NUM; reg_off++) {
            if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DMI_DMIUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t),
                          reg_off) == 0) {
                if (param == CCU_DMI_DMIUINFOR_DEFAULT) {
                    printf("Read DMI DMIUINFOR offset %d SUCCESSFUL!\n", reg_off);
                } else {
                    printf("Warning: DMI DMIUINFOR expected: 0x%x, observerd: 0x%x!\n", CCU_DMI_DMIUINFOR_DEFAULT,
                           param);
                }
            } else {
                printf("ERROR: CCU ioctl failed\n");
                return_value = -1;
            }
        }

        for (int32_t reg_off = 0; reg_off < DII_NUM; reg_off++) {
            if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DII_DIIUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t),
                          reg_off) == 0) {
                if (param == CCU_DII_DIIUINFOR_DEFAULT) {
                    printf("Read DII DIIUINFOR offset %d SUCCESSFUL!\n", reg_off);
                } else {
                    printf("Warning: DII DIIUINFOR expected: 0x%x, observerd: 0x%x!\n", CCU_DII_DIIUINFOR_DEFAULT,
                           param);
                }
            } else {
                printf("ERROR: CCU ioctl failed\n");
                return_value = -1;
            }
        }

        if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_DVE_DVEUINFOR_GET, (uintptr_t)&param, sizeof(uint32_t), 0) == 0) {
            if (param == CCU_DVE_DVEUINFOR_DEFAULT) {
                printf("Read DVE DVEUINFOR SUCCESSFUL!\n");
            } else {
                printf("Warning: DVE DVEUINFOR expected: 0x%x, observerd: 0x%x!\n", CCU_DVE_DVEUINFOR_DEFAULT, param);
            }
        } else {
            printf("ERROR: CCU ioctl failed\n");
            return_value = -1;
        }

        if (ccu_ioctl(ccu_handle, (int32_t)IOCTL_CCU_SYS_GLOBAL_GRBUNSIDR_GET, (uintptr_t)&param, sizeof(uint32_t),
                      0) == 0) {
            if (param == CCU_SYS_GLOBAL_GRBUNSIDR_DEFAULT) {
                printf("Read SYS GLOBAL GRBUNSIDR SUCCESSFUL!\n");
            } else {
                printf("Warning: SYS GBL GRBUNSIDR expected: 0x%x, observerd: 0x%x!\n",
                       CCU_SYS_GLOBAL_GRBUNSIDR_DEFAULT, param);
            }
        } else {
            printf("ERROR: CCU ioctl failed\n");
            return_value = -1;
        }

        if (ccu_close(ccu_handle) == 0) {
            printf("CCU close\n");
        }
    }

    return return_value;
}

#ifdef __cplusplus
}
#endif
