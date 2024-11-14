#include "dma.h"
#include "dma_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <stdio.h>
#include <string.h>

#define RST_MGR_PER0MODRST_DMA_MASK 0xFF210000
#define RST_MGR_PER1MODRST_UART_MASK 0x00030000
#define DMA_ID 0x000746A1
#define DMA_LOWPOWER_CFG_DEFAULT_VALUE 0x404040000000F
#define DMA_BLOCK_NUMBER 7
#define DMA_MEM_SRC_ADDR 0x80000000
#define DMA_MEM_DST_ADDR 0x80001000
#define DMA_CFG2_TT_FC_MEM_TO_MEM_MASK ~(DMA_CHx_CFG2_TT_FC_MASK)

#ifdef __cplusplus
extern "C" {
#endif

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";
    const char dma_initiator[] = "/dev/dma0";
    int32_t return_value = 0;
    int32_t chan_idx = 0;

    uint32_t src_addr = DMA_MEM_SRC_ADDR;
    uint32_t dst_addr = DMA_MEM_DST_ADDR;
    uint32_t *p_src = (uint32_t *)src_addr;
    uint32_t *p_dst = (uint32_t *)dst_addr;
    dma_lli_t lli;

    printf("Dummy log to avoid missing logs\n");

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }

    hps_rstmgr_regs_t regs_buffer;
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
    regs_buffer.per0modrst &= ~((uint32_t)RST_MGR_PER0MODRST_DMA_MASK);
    regs_buffer.per1modrst &= ~((uint32_t)RST_MGR_PER1MODRST_UART_MASK);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

    printf("DMA Test Start\n");

    int32_t dma_handle = dma_open(dma_initiator, 0);
    if (dma_handle < 0) {
        return_value = dma_handle;
        printf("ERROR: DMA failed open\n");
    } else {
        printf("DMA open\n");
        uint64_t param = 0;
        param = 0;

        if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_IDREG_GET, (uintptr_t)&param, sizeof(uint64_t), 0) == 0) {
            if (param == DMA_ID) {
                printf("DMA enabled with correct ID\n");
            } else {
                printf("ERROR: DMA enabled with wrong ID\n");
                return_value = -1;
            }
        } else {
            printf("ERROR: DMA ioctl failed\n");
            return_value = -1;
        }

        if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_LOWPOWER_CFGREG_GET, (uintptr_t)&param, sizeof(uint64_t), 0) ==
            0) {
            if ((param == DMA_LOWPOWER_CFG_DEFAULT_VALUE)) {
                printf("DMA got correct LOWPOWER CFG default value\n");

                // DMA read test
                chan_idx = dma_get_chan(dma_handle);
                printf("DMA get channel: %d\n", chan_idx);
            } else {
                printf("ERROR: DMA got wrong LOWPOWER CFG default value\n");
                return_value = -1;
            }
        } else {
            printf("ERROR: DMA ioctl failed\n");
            return_value = -1;
        }

        for (int i = 0; i < 32; i++) {
            p_src[i] = 0x5A5A5A00 + i;
        }

        // set the transfer type to memory to memory
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CFG2_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        param &= DMA_CFG2_TT_FC_MEM_TO_MEM_MASK;
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CFG2_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("DMA write to CFG2 is done\n");

        param = (uintptr_t)(&(lli));
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_LLP_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("DMA write to LLP is done\n");

        lli.sar = src_addr;
        lli.dar = dst_addr;
        lli.block_ts = DMA_BLOCK_NUMBER; // the actual block number is (DMA_BLOCK_NUMBER+1)
        lli.llp = param;                 // Not necessary required as we have only one linked list item in the test

        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CTL_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        lli.ctl = param | DMA_CTL_SHADOWREG_OR_LLI_VALID_MASK | DMA_CTL_SHADOWREG_OR_LLI_LAST_MASK;

        dma_trans_enable(dma_handle, chan_idx);
        printf("DMA starts transmission...\n");

        // Check INT STATUS & CLEAR
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTSTATUS_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);

        // The status bit needs to be cleared
        if (param == (DMA_CHx_INTSTS_BLOCK_TFR_DONE | DMA_CHx_INTSTS_DMA_TFR_DONE | DMA_CHx_INTSTS_SRC_TRANSCOMP |
                      DMA_CHx_INTSTS_DST_TRANSCOMP)) {

            printf("---DMA transmission completed---\n");
            printf("DMA INT STATUS is EXPECTED.\n");
            param = (DMA_CHx_INTSTS_BLOCK_TFR_DONE | DMA_CHx_INTSTS_DMA_TFR_DONE | DMA_CHx_INTSTS_SRC_TRANSCOMP |
                     DMA_CHx_INTSTS_DST_TRANSCOMP);

            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTCLEARREG_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("DMA set INT CLEAR\n");

            if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTSTATUS_GET, (uintptr_t)&param, sizeof(uint64_t),
                          chan_idx) == 0) {
                if (param == 0) {
                    printf("DMA INT CLEAR: OK\n");
                } else {
                    printf("ERROR: DMA INT CLEAR: failed\n");
                    return_value = -1;
                }
            } else {
                printf("ERROR: DMA ioctl failed\n");
                return_value = -1;
            }

            if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CHENREG_GET, (uintptr_t)&param, sizeof(uint64_t), 0) == 0) {
                // The enable bit will be cleared if the transmission is completed
                if (param & (1 << chan_idx)) {
                    printf("ERROR: DMA check CHEN REG to be cleared: FAILED\n");
                    return_value = -1;
                } else {
                    printf("DMA check CHEN REG to be cleared: OK\n");
                }
            } else {
                printf("ERROR: DMA ioctl failed\n");
                return_value = -1;
            }

            for (int j = 0; j < (DMA_BLOCK_NUMBER + 1); j++) {
                if (p_src[j] != p_dst[j]) {
                    printf("ERROR: DMA data comparison failed at position %d\n", j);
                    return_value = -1;
                    break;
                }
            }
            printf("DMA transmission: Done\n");

            // close DMA
            int32_t ret = dma_close(dma_handle);
            if (ret == 0) {
                printf("DMA close: OK\n");
            } else {
                printf("DMA close: FAILED\n");
            }

        } else {
            printf("ERROR: INT STATUS is NOT expected: 0x%lx\n", param);
            return_value = -1;
        }
    }

    return return_value;
}

#ifdef __cplusplus
}
#endif
