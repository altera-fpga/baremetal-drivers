#ifndef DMA_H__
#define DMA_H__

#include <stddef.h>
#include <stdint.h>

/* LLI: Linked List Item */
typedef struct __attribute__((aligned(64))) {
    uint64_t sar;
    uint64_t dar;
    uint32_t block_ts;
    uint32_t reserved_0;
    uint64_t llp;
    uint64_t ctl;
    uint32_t sstat;
    uint32_t dstat;
    uint32_t llp_status_lo;
    uint32_t llp_status_hi;
    uint32_t reserved_lo;
    uint32_t reserved_hi;
} dma_lli_t;

typedef enum {
    IOCTL_DMA_REGS_READ = 1,
    IOCTL_DMA_REGS_WRITE,
    IOCTL_DMA_IDREG_GET,
    IOCTL_DMA_COMPVERREG_GET,
    IOCTL_DMA_CFG_SET,
    IOCTL_DMA_CFG_GET,
    IOCTL_DMA_CHENREG_WE_SET,
    IOCTL_DMA_CHENREG_EN_SET,
    IOCTL_DMA_CHENREG_SUSP_SET,
    IOCTL_DMA_CHENREG_ABORT_SET,
    IOCTL_DMA_CHENREG_GET,
    IOCTL_DMA_INTSTATUSREG_GET,
    IOCTL_DMA_COMMONREG_INTCLEARREG_SET,
    IOCTL_DMA_COMMONREG_INTSTATUS_ENABLEREG_GET,
    IOCTL_DMA_COMMONREG_INTSTATUS_ENABLEREG_SET,
    IOCTL_DMA_COMMONREG_INTSIGNAL_ENABLEREG_GET,
    IOCTL_DMA_COMMONREG_INTSIGNAL_ENABLEREG_SET,
    IOCTL_DMA_COMMONREG_INTSTATUSREG_GET,
    IOCTL_DMA_RESETREG_SET,
    IOCTL_DMA_RESETREG_GET,
    IOCTL_DMA_LOWPOWER_CFGREG_SET,
    IOCTL_DMA_LOWPOWER_CFGREG_GET,
    IOCTL_DMA_CH_SAR_SET,
    IOCTL_DMA_CH_SAR_GET,
    IOCTL_DMA_CH_DAR_SET,
    IOCTL_DMA_CH_DAR_GET,
    IOCTL_DMA_CH_BLOCK_TS_GET,
    IOCTL_DMA_CH_BLOCK_TS_SET,
    IOCTL_DMA_CH_CTL_GET,
    IOCTL_DMA_CH_CTL_SET,
    IOCTL_DMA_CH_CFG2_GET,
    IOCTL_DMA_CH_CFG2_SET,
    IOCTL_DMA_CH_LLP_GET,
    IOCTL_DMA_CH_LLP_SET,
    IOCTL_DMA_CH_STATUSREG_GET,
    IOCTL_DMA_CH_SWHSSRCREG_GET,
    IOCTL_DMA_CH_SWHSSRCREG_SET,
    IOCTL_DMA_CH_SWHSDSTREG_GET,
    IOCTL_DMA_CH_SWHSDSTREG_SET,
    IOCTL_DMA_CH_BLK_TFR_RESUMEREQREG_SET,
    IOCTL_DMA_CH_AXI_IDREG_GET,
    IOCTL_DMA_CH_AXI_IDREG_SET,
    IOCTL_DMA_CH_AXI_QOSREG_GET,
    IOCTL_DMA_CH_AXI_QOSREG_SET,
    IOCTL_DMA_CH_INTSTATUS_ENABLEREG_GET,
    IOCTL_DMA_CH_INTSTATUS_ENABLEREG_SET,
    IOCTL_DMA_CH_INTSTATUS_GET,
    IOCTL_DMA_CH_INTSIGNAL_ENABLEREG_GET,
    IOCTL_DMA_CH_INTSIGNAL_ENABLEREG_SET,
    IOCTL_DMA_CH_INTCLEARREG_SET,

    // adding new elements before this line
    IOCTL_DMA_END
} dma_ioctl_t;

int32_t dma_open(const char *name, int32_t flags);
int32_t dma_close(int32_t fd);
int32_t dma_trans_enable(int32_t fd, int32_t channel);
int32_t dma_ioctl(int32_t fd, int32_t operation, uintptr_t args, size_t length, int32_t channel);
int32_t dma_get_chan(int32_t fd);

#endif // DMA_H
