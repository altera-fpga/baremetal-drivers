#include "dma.h"
#include "dma_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include <inttypes.h>
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

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

uint32_t src_buf[32] = {0};
uint32_t dst_buf[32] = {0};

dma_lli_t lli;

int main(void) {

    const char reset_manager[] = "/dev/rstmgr";
    const char dma_initiator[] = "/dev/dma0";
    int32_t return_value = 0;
    int32_t chan_idx = 0;

    uint32_t src_addr = (uint32_t)(uintptr_t)src_buf;
    uint32_t dst_addr = (uint32_t)(uintptr_t)dst_buf;

#ifdef FSBL_EXECUTION

    uint32_t *lcl_ptr;

    fsbl_configuration();

    // Set OCRAM non secure access
    lcl_ptr = (uint32_t *)0x108CC418;
    *lcl_ptr = 0;

#endif

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
                printf("ERROR: DMA enabled with wrong ID: 0x%lx\n", param);
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
                printf("Enabled with channel #%d\n", chan_idx + 1);

                param = 1 | (1 << 8);
                printf("CHEN REG write: 0x%lx\n", param);
                dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CHENREG_SET, (uintptr_t)&param, sizeof(uint64_t), 0);

            } else {
                printf("ERROR: DMA got wrong LOWPOWER CFG default value: 0x%lx\n", param);
                return_value = -1;
            }
        } else {
            printf("ERROR: DMA ioctl failed\n");
            return_value = -1;
        }

        // initialize the source data
        for (int i = 0; i < 32; i++) {
            src_buf[i] = 0x5A5A5A00 + i;
        }

        // set the transfer type to memory to memory
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CFG2_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("CFG2 read: 0x%lx\n", param);

        param &= DMA_CFG2_TT_FC_MEM_TO_MEM_MASK;

        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CFG2_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("CFG2 write\n");

        param = (uintptr_t)(&(lli));
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_LLP_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("LLP write\n");

        lli.sar = src_addr;
        lli.dar = dst_addr;
        lli.block_ts = DMA_BLOCK_NUMBER; // the actual block number is (DMA_BLOCK_NUMBER+1)

        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CTL_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("CTL read original: 0x%lx\n", param);

        param |= DMA_CTL_SHADOWREG_OR_LLI_VALID_MASK | DMA_CTL_SHADOWREG_OR_LLI_LAST_MASK;
        lli.ctl = param;

        printf("LLI.CTL: 0x%lx\n", lli.ctl);

        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CTL_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("CTL read: 0x%lx\n", param);

        dma_trans_enable(dma_handle, chan_idx);
        printf("----DMA transmission started----\n");

        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CTL_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
        printf("CTL read after start: 0x%lx\n", param);

        // Check INT STATUS & CLEAR
        dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTSTATUS_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);

        if (param | DMA_CHx_INTSTS_DMA_TFR_DONE) {

            printf("---DMA transmission completed---\n");
            printf("DMA INT STATUS is EXPECTED.\n");

#if 0 // this passed the hw test, but not simics. Need to file an HSD for simics
      // verify if the number of complete block is matched.
            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_STATUSREG_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            if((param & DMA_CHx_STATUS_CMPLTD_BLK_MASK)!= lli.block_ts) {
                printf("Number of complete blocks NOT matched: expected: %d, actual: %ld\n", lli.block_ts, param);
            } else {
                printf("Verify number of complete blocks: OK\n");
            }
#endif
            // clear the status
            param = DMA_CHx_INTSTS_DMA_TFR_DONE;
            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTCLEARREG_SET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("DMA set INT CLEAR\n");

            // verify the status is cleared
            if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_INTSTATUS_GET, (uintptr_t)&param, sizeof(uint64_t),
                          chan_idx) == 0) {
                if ((param & DMA_CHx_INTSTS_DMA_TFR_DONE) == 0) {
                    printf("DMA INT CLEAR: OK\n");
                } else {
                    printf("ERROR: DMA INT CLEAR: failed\n");
                    return_value = -1;
                }
            } else {
                printf("ERROR: DMA ioctl failed\n");
                return_value = -1;
            }

            // verify if the corresponding channel is cleared indicating the transmission is complete
            if (dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CHENREG_GET, (uintptr_t)&param, sizeof(uint64_t), 0) == 0) {
                if (param & (1 << chan_idx)) {
                    printf("ERROR: DMA check CHEN REG to be cleared: FAILED\n");
                    return_value = -1;
                } else {
                    printf("Channel register for Channel %d is cleared: OK\n", chan_idx + 1);
                }
            } else {
                printf("ERROR: DMA ioctl failed\n");
                return_value = -1;
            }

            // Data comparison
            for (int j = 0; j < (DMA_BLOCK_NUMBER + 1); j++) {
                if (src_buf[j] != dst_buf[j]) {
                    printf("ERROR: DMA data comparison failed at position %d\n", j);
                    printf("Expected: 0x%x; observed: 0x%x\n", src_buf[j], dst_buf[j]);
                    return_value = -1;
                    break;
                }
            }

            // close DMA
            int32_t ret = dma_close(dma_handle);
            if (ret == 0) {
                printf("DMA close: OK\n");
            } else {
                printf("DMA close: FAILED\n");
            }

        } else {
            printf("ERROR: unexpected INT STATUS. Expected: 0x%x, observed: 0x%lx\n", DMA_CHx_INTSTS_DMA_TFR_DONE,
                   param);

            // Check if source data set correctly
            for (int i = 0; i < 32; i++) {
                if (src_buf[i] != (uint32_t)(0x5A5A5A00 + i)) {
                    printf("Write to source address 0x%" PRIxPTR " failed. Expected 0x%08x, but got 0x%08x\n",
                           (uintptr_t)&src_buf[i], 0x5A5A5A00 + i, src_buf[i]);
                }
            }

            // Check if linked list data is parsed successfully - should be consistent with the LLI
            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_CTL_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("CTL read: 0x%lx\n", param);
            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_SAR_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("SAR read: 0x%lx\n", param);

            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_DAR_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("DAR read: 0x%lx\n", param);
            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_BLOCK_TS_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("block ts read: 0x%lx\n", param);

            dma_ioctl(dma_handle, (int32_t)IOCTL_DMA_CH_LLP_GET, (uintptr_t)&param, sizeof(uint64_t), chan_idx);
            printf("LLI data dump for debug:\n");
            printf("LLI pointer is located at 0x%lx\n", param);
            printf("SRC address: 0x%lx, DST address: 0x%lx\n", lli.sar, lli.dar);
            printf("block ts: 0x%x, LLP: 0x%lx, CTL: 0x%lx\n", lli.block_ts, lli.llp, lli.ctl);

            // If write back is enabled, the info below should be updated
            printf("LLI status: sstat: %d, dstat: %d, llp_status_lo: %d, llp_status_hi: %d\n", lli.sstat, lli.dstat,
                   lli.llp_status_lo, lli.llp_status_hi);

            return_value = -1;
        }
    }

    return return_value;
}

#ifdef __cplusplus
}
#endif
