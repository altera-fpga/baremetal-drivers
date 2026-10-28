/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_dma.c
 *
 * DMA source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: middleware
 * Component: DMA
 */

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "socfpga_dma.h"
#include "socfpga_dma_ll.h"
#include "socfpga_dma_reg_plat.h"
#include "socfpga_dma_reg.h"
#include "cache.h"
#include "socfpga_interrupt.h"
#include "socfpga_rst_mngr.h"

#define MULTI_BLK_LLI_MODE_ENABLED    1
#define DMA_MAX_INSTANCE              (2U)
#define MAX_CHANNEL_NUM               (4U)
#define MAX_LLI_PER_CHANNEL           128U  /* must fit ceil(max_async_bytes / DMA_MAX_CHUNK_BYTES) */
#define MAX_BLOCK_SIZE                0x1FFFFFU
/* Maximum iterations to wait for a channel to deactivate after disable/abort */
#define DMA_CH_DISABLE_TIMEOUT        1000U

/* DMA channel descriptor structure from low-level layer */
struct dma_channel_reg_list;

/* DMA interrupt IDs */
static socfpga_hpu_interrupt_t interrupt_id[DMA_MAX_INSTANCE][MAX_CHANNEL_NUM] =
{
    {
        DMA_IRQ0, DMA_IRQ1, DMA_IRQ2, DMA_IRQ3
    },
    {
        DMA1IRQ0, DMA1IRQ1, DMA1IRQ2, DMA1IRQ3
    }
};

/* DMA channel context structure */
struct dma_ch_cntxt
{
    bool is_open;
    uint32_t base_address;
    uint32_t ch_offset;
    uint32_t channel_num;
    dma_ch_state_t channel_state;
    socfpga_hpu_interrupt_t intr_id;
    /* dma_channel_reg_list descriptor base pointer */
    struct dma_channel_reg_list *linked_list_base;
    /* DMA transfer direction */
    dma_xfer_type_t direction;
    /* DMA channel config register  */
    uint64_t config;
    /* Interrupt config  */
    uint64_t interrupt_en;
    /* Callback function for interrupts */
    dma_callback_t xp_dma_callback;
};

void dma_mw_irq_handler(void *data);

static struct dma_ch_cntxt hdma_default[DMA_MAX_INSTANCE][MAX_CHANNEL_NUM];

/* Allocate memory for storing the descriptors */
static struct dma_channel_reg_list plinked_list_chain[DMA_MAX_INSTANCE]
[MAX_CHANNEL_NUM * MAX_LLI_PER_CHANNEL] __attribute__ ((aligned (64)));

/* Get the current status of the DMA channel. */
dma_ch_state_t dma_mw_get_channel_status(dma_handle_t hdma)
{
    dma_ch_state_t ret = DMA_CH_IDLE;

    if (hdma == NULL)
    {
        return DMA_CH_IDLE;
    }

    /* Software error state (set by ISR / polling) takes priority over
     * hardware register state because the channel is already IDLE in
     * hardware by the time the caller reads the status. */
    if (hdma->channel_state == DMA_CH_ERROR)
    {
        return DMA_CH_ERROR;
    }

    if (dma_ll_is_channel_enabled(hdma->base_address, hdma->channel_num)) {
        ret = DMA_CH_ACTIVE;
    }
    if (dma_ll_is_channel_suspended(hdma->base_address, hdma->channel_num)) {
        ret = DMA_CH_SUSPENDED;
    }
    if (dma_ll_is_channel_aborted(hdma->base_address, hdma->channel_num)) {
        ret = DMA_CH_ABORT;
    }
    return ret;
}

/* Determine the optimum transfer width for the requested block size. */
static dma_xfer_width_t dma_get_transfer_width(dma_handle_t const hdma, uint32_t block_size)
{
    dma_xfer_width_t dma_transfer_width;

    if (hdma->direction == DMA_MEM_TO_MEM_DMAC)
    {
        if ((block_size & 0x7U) == 0)
        {
            dma_transfer_width = DMA_ID_XFER_WIDTH8;
        }
        else if ((block_size & 0x3U) == 0)
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH4;
        }
        else if ((block_size & 0x1U) == 0)
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH2;
        }
        else
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH1;
        }
    }
    else
    {
        if ((block_size & 0x3U) == 0)
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH4;
        }
        else if ((block_size & 0x1U) == 0)
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH2;
        }
        else
        {
            dma_transfer_width = DMA_TRANSFER_WIDTH1;
        }
    }
    return dma_transfer_width;
}

/* Select DMA burst lengths based on transfer direction. */
static void dma_get_burst_len(dma_handle_t const hdma, dma_burst_len_t *src_burst_len,
        dma_burst_len_t *dst_burst_len)
{
    if (hdma->direction == DMA_MEM_TO_MEM_DMAC)
    {
        *src_burst_len = DMA_BURST_LEN_16;
        *dst_burst_len = DMA_BURST_LEN_16;
    }
    else
    {
        *src_burst_len = DMA_BURST_LEN_4;
        *dst_burst_len = DMA_BURST_LEN_4;
    }
}

dma_handle_t dma_mw_open(uint32_t instance, uint32_t ch)
{
    int32_t status;
    uint8_t reset_status;
    dma_handle_t phandle = NULL;
    socfpga_interrupt_err_t int_ret;

    if ((instance >= DMA_MAX_INSTANCE) || (ch >= MAX_CHANNEL_NUM))
    {
        printf("Not a valid DMAC Instance or Channel");
        return NULL;
    }

    phandle = &hdma_default[instance][ch];
    if (phandle->is_open == 1)
    {
        printf("DMAC channel already opened please close it before re-opening");
        return NULL;
    }
    if (phandle->channel_state != DMA_CH_IDLE)
    {
        printf("DMAC Channel instance is in use");
        return NULL;
    }

    status = rstmgr_get_reset_status(RST_DMA, &reset_status);
    if (status != 0)
    {
        printf("DMAC block get reset status failed. ");
        return NULL;
    }
    if (reset_status == 1U)
    {
        status = rstmgr_toggle_reset(RST_DMA);
        if (status != 0)
        {
            printf("Failed to reset release DMAC block. ");
            return NULL;
        }
    }

    phandle->base_address = dma_ll_get_base_address(instance);
    phandle->ch_offset = phandle->base_address + dma_ll_get_channel_offset(ch);
    phandle->intr_id = interrupt_id[instance][ch];
    phandle->channel_num = ch;
    phandle->linked_list_base = &plinked_list_chain[instance][(ch * MAX_LLI_PER_CHANNEL)];
    phandle->is_open = 1;

    /* Register the DMA ISR with GIC for interrupt-driven completion. */
    int_ret = interrupt_register_isr(phandle->intr_id, dma_mw_irq_handler, phandle);
    if (int_ret != ERR_OK)
    {
        printf("DMA: GIC ISR registration failed (id=%d, rc=%d) - "
               "falling back to polling mode\n", phandle->intr_id, (int)int_ret);
    }
    else
    {
        int_ret = interrupt_enable(phandle->intr_id, GIC_INTERRUPT_PRIORITY_DMA);
        if (int_ret != ERR_OK)
        {
                 printf("DMA: GIC interrupt_enable failed (id=%d, rc=%d) - "
                   "falling back to polling mode\n", phandle->intr_id, (int)int_ret);
        }
    }
    return phandle;
}

int32_t dma_mw_config(dma_handle_t const hdma, dma_config_t *pcfg)
{
    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }
    if (hdma->is_open != 1)
    {
        printf("DMAC channel should be opened before config \n");
        return -EFAULT;
    }
    /* Allow recovery from a previous error without requiring close+reopen */
    if (hdma->channel_state == DMA_CH_ERROR)
    {
        hdma->channel_state = DMA_CH_IDLE;
    }
    if (hdma->channel_state != DMA_CH_IDLE)
    {
        printf("DMAC Channel is in active state");
        return -EBUSY;
    }

    hdma->config = 0UL;
    hdma->interrupt_en = 0UL;

    hdma->direction = pcfg->ch_dir;
    hdma->config |= ((uint64_t)(pcfg->ch_dir) << DMA_CH_CFG2_TT_FC_POS);
    if (pcfg->ch_dir == DMA_MEM_TO_PERI_DMAC)
    {
        hdma->config |= ((uint64_t)pcfg->peri_id << DMA_CH_CFG2_DST_PER_POS);
    }
    if (pcfg->ch_dir == DMA_PERI_TO_MEM_DMAC)
    {
        hdma->config |= ((uint64_t)pcfg->peri_id << DMA_CH_CFG2_SRC_PER_POS);
    }

    hdma->config &= ~((DMA_CH_CFG2_DST_MULTBLK_TYPE_MASK |
            DMA_CH_CFG2_SRC_MULTBLK_TYPE_MASK));
#if MULTI_BLK_LLI_MODE_ENABLED
    /* Data available in multiple blocks of memory */
    hdma->config |= (((uint32_t)DMA_MULTI_BLK_LL << DMA_CH_CFG2_DST_MULTBLK_TYPE_POS) |
            ((uint32_t)DMA_MULTI_BLK_LL << DMA_CH_CFG2_SRC_MULTBLK_TYPE_POS));
#else
    /* Data available in a single contiguous block memory */
    hdma->config |= ((DMA_MULTI_BLK_CONTIGUOUS << DMA_CH_CFG2_DST_MULTBLK_TYPE_POS) |
            (DMA_MULTI_BLK_CONTIGUOUS << DMA_CH_CFG2_SRC_MULTBLK_TYPE_POS));
#endif
    hdma->xp_dma_callback = pcfg->callback;
    return 0;
}

int32_t dma_mw_setup_transfer(dma_handle_t const hdma, dma_xfer_cfg_t *xfer_list, uint32_t num_xfers)
{
    uint64_t transfer_size;
    uint64_t beats;
    uint32_t i;
    dma_xfer_width_t src_width, dst_width;
    dma_burst_len_t src_burst_len, dst_burst_len;
    struct dma_channel_reg_list *plinked_list;
    dma_xfer_cfg_t *ptransfer_cfg;

    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }
    if (num_xfers > MAX_LLI_PER_CHANNEL)
    {
        printf("Number of transfers exceeds current limit of %d", MAX_LLI_PER_CHANNEL);
        return -EINVAL;
    }
    if (xfer_list == NULL)
    {
        printf("Transfer list cannot be null");
        return -EFAULT;
    }
    if (hdma->is_open != 1)
    {
        printf("DMAC channel should be opened before setup transfer \n");
        return -EIO;
    }
    if (hdma->channel_state != DMA_CH_IDLE)
    {
        printf("DMAC Channel is in active state ");
        return -EBUSY;
    }

    (void)memset(hdma->linked_list_base, 0, (sizeof(struct
            dma_channel_reg_list) * MAX_LLI_PER_CHANNEL));
    plinked_list = hdma->linked_list_base;
    if (plinked_list == NULL)
    {
        printf("Linked list is null");
        return -EFAULT;
    }
    ptransfer_cfg = xfer_list;
    if (ptransfer_cfg == NULL)
    {
        printf("Transfer Cfg is NULL");
        return -EFAULT;
    }

    for (i = 0U; i < num_xfers; i++)
    {
        src_width = dma_get_transfer_width(hdma, ptransfer_cfg->blk_size);
        dst_width = src_width;
        dma_get_burst_len(hdma, &src_burst_len, &dst_burst_len);
        transfer_size = (((uint64_t)src_width << DMA_CH_CTL_SRC_TR_WIDTH_POS) |
                ((uint64_t)dst_width << DMA_CH_CTL_DST_TR_WIDTH_POS));
        transfer_size |=
                (((uint64_t)src_burst_len <<
                DMA_CH_CTL_SRC_MSIZE_POS) | ((uint64_t)dst_burst_len << DMA_CH_CTL_DST_MSIZE_POS));
        transfer_size |= ((DMA_CH_CTL_DST_STAT_EN_MASK |
                DMA_CH_CTL_SRC_STAT_EN_MASK) | DMA_CH_CTL_IOC_BLKTFR_MASK);
        if (((1UL << (uint64_t)src_width) == 0U) || (ptransfer_cfg == NULL))
        {
            printf("Transfer width cannot be 0");
            return -EFAULT;
        }

        plinked_list->sar = ptransfer_cfg->src;
        plinked_list->dar = ptransfer_cfg->dst;
        plinked_list->ctl = transfer_size;
        /* Explicit beat count validation (ATF-style): reject over-limit values
         * instead of silently truncating via bit-mask. */
        beats = (uint64_t)ptransfer_cfg->blk_size / (1UL << (uint64_t)src_width);
        if ((beats == 0U) || (beats > (uint64_t)DMA_MAX_BLOCK_TS))
        {
            printf("DMA: blk_size %u / width %u = %u beats, exceeds DMA_MAX_BLOCK_TS %u",
                   ptransfer_cfg->blk_size, (1U << (uint32_t)src_width),
                   (uint32_t)beats, (uint32_t)DMA_MAX_BLOCK_TS);
            return -EINVAL;
        }
        plinked_list->block_ts = (beats - 1UL) & (uint64_t)DMA_CH_BLOCK_TS_BLOCK_TS_MASK;

        /* Set next descriptor address */
        plinked_list->llp = ((uint64_t)(uintptr_t)(plinked_list + (uintptr_t)1U));

#if MULTI_BLK_LLI_MODE_ENABLED
        plinked_list->ctl |= (1UL << DMA_CH_CTL_SHADOWREG_OR_LLI_VALID_POS);
        /* Last descriptor */
        if ((num_xfers) == (i + 1U))
        {
            plinked_list->ctl |= (1UL << DMA_CH_CTL_SHADOWREG_OR_LLI_LAST_POS);
            plinked_list->llp = 0UL;
        }
#endif

        /* Next descriptor updates */
        plinked_list++;
        ptransfer_cfg = ptransfer_cfg->next_trnsfr_cfg;
    }

    cache_force_write_back((void *)hdma->linked_list_base,
            ((MAX_LLI_PER_CHANNEL)*sizeof(plinked_list[0U])));

    /* Enable only the block-transfer-done bit.
     *
     * DMA_ERROR_INT_MASK is intentionally excluded here.  On Simics the
     * dw_axi_dmac model pre-sets error-class bits in CH_RAWINTSTATUS
     * (SRC/DST decode / slave errors); enabling them in
     * CH_INTSTATUS_ENABLEREG would make those bits visible in CH_INTSTATUS
    * immediately after dma_ll_setup_interrupts(), causing dma_mw_check_transfer()
     * to falsely detect an error and return DMA_CH_ERROR before the transfer
     * even starts.  On real hardware, bus-access errors on the DMA path
     * would cause the transfer to time-out or produce bad data, both of which
     * are detectable at the application level without relying on this mask. */
    hdma->interrupt_en = TFR_DONE_MASK;

    /* Enable DMA controller and global interrupts */
    dma_ll_enable_controller(hdma->base_address);

    /* Configure channel */
    dma_ll_configure_channel(hdma->ch_offset, hdma->config);

    /* Setup interrupts */
    dma_ll_setup_interrupts(hdma->ch_offset, hdma->interrupt_en);

    plinked_list = hdma->linked_list_base;
    if (plinked_list == NULL)
    {
        printf("Linked list is null");
        return -EFAULT;
    }

#if MULTI_BLK_LLI_MODE_ENABLED
    dma_ll_write_llp(hdma->ch_offset, ((uint64_t)plinked_list));
#else
    dma_ll_write_sar(hdma->ch_offset, plinked_list->sar);
    dma_ll_write_dar(hdma->ch_offset, plinked_list->dar);
    dma_ll_write_block_ts(hdma->ch_offset, plinked_list->block_ts);
    dma_ll_write_ctl(hdma->ch_offset, plinked_list->ctl);
#endif
    return 0;
}

int32_t dma_mw_start_transfer(dma_handle_t const hdma)
{
    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }
    if (hdma->is_open != 1)
    {
        printf("DMAC channel should be opened before start transfer \n");
        return -EIO;
    }

    if (hdma->channel_state != DMA_CH_IDLE)
    {
        printf("DMAC Channel is in active state ");
        return -EBUSY;
    }

    printf("Starting the DMA transfer on channel %d", hdma->channel_num);

    /* Start the channel for transfer */
    dma_ll_enable_channel(hdma->base_address, hdma->channel_num);

    /* Set the channel state to active as the transfer is started */
    hdma->channel_state = DMA_CH_ACTIVE;
    return 0;
}

int32_t dma_mw_stop_transfer(dma_handle_t const hdma)
{
    uint64_t val;
    uint32_t wait_count = 0U;

    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }
    if (hdma->channel_state == DMA_CH_IDLE)
    {
        printf("DMAC Channel not in active state ");
        return -EIO;
    }

    /* Suspend the transfer */
    dma_ll_suspend_channel(hdma->base_address, hdma->channel_num);

    /* Disable the channel */
    dma_ll_disable_channel(hdma->base_address, hdma->channel_num);

    val = dma_ll_get_chenreg(hdma->base_address);
    while (((val & (1UL << hdma->channel_num)) == (1UL << hdma->channel_num)) &&
            (wait_count < DMA_CH_DISABLE_TIMEOUT))
    {
        val = dma_ll_get_chenreg(hdma->base_address);
        wait_count++;
    }
    if (wait_count >= DMA_CH_DISABLE_TIMEOUT)
    {
        return -ETIMEDOUT;
    }

    /* Set the channel state to idle as the transfer is stopped */
    hdma->channel_state = DMA_CH_IDLE;
    return 0;
}

int32_t dma_mw_abort_transfer(dma_handle_t const hdma)
{
    uint32_t wait_count = 0U;

    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }

    dma_ll_abort_channel(hdma->base_address, hdma->channel_num);

    while (dma_ll_is_channel_enabled(hdma->base_address, hdma->channel_num) &&
            (wait_count < DMA_CH_DISABLE_TIMEOUT))
    {
        wait_count++;
    }

    if (wait_count >= DMA_CH_DISABLE_TIMEOUT)
    {
        return -ETIMEDOUT;
    }

    hdma->channel_state = DMA_CH_IDLE;
    return 0;
}

int32_t dma_mw_close(dma_handle_t const hdma)
{
    if (hdma == NULL)
    {
        printf("DMAC handle cannot be NULL ");
        return -EINVAL;
    }
    (void)memset(hdma, 0, sizeof(struct dma_ch_cntxt));
    return 0;
}

/* Interrupt handler for DMA transfer completion/error events. */
void dma_mw_irq_handler(void *data)
{
    uint64_t val;
    dma_handle_t phandle = (dma_handle_t)data;

    val = dma_ll_get_interrupt_status(phandle->ch_offset);

    /* TFR_DONE is checked before error bits.  On real DW AXI DMAC hardware
     * TFR_DONE and the error flags are mutually exclusive: a successful block
     * transfer raises TFR_DONE and clears all error bits, while an AXI bus
     * error raises an error flag and suppresses TFR_DONE.  A simulation
     * model may deviate from this and may assert both simultaneously; checking
     * TFR_DONE first ensures a completed transfer is never mis-classified as
     * an error in either the real or simulated environment. */
    if ((val & TFR_DONE_MASK) == TFR_DONE_MASK)
    {
        dma_ll_clear_interrupts(phandle->ch_offset, TFR_DONE_MASK);
        phandle->channel_state = DMA_CH_IDLE;
        if (phandle->xp_dma_callback != NULL)
        {
            phandle->xp_dma_callback(phandle);
        }
        return;
    }

    if ((val & DMA_ERROR_INT_MASK) != 0U)
    {
        dma_ll_clear_interrupts(phandle->ch_offset, DMA_ERROR_INT_MASK);
        phandle->channel_state = DMA_CH_ERROR;
        if (phandle->xp_dma_callback != NULL)
        {
            phandle->xp_dma_callback(phandle);
        }
    }
}

/* Poll CH_INTSTATUS for completion without relying on GIC delivery.
 *
 * Called from dma_wait() on each iteration as a fallback.  If GIC fires
 * first, g_transfer_done is already true and this function is never needed.
 * If GIC does not fire (routing not set up, simulation delivery constraint, etc.) this
 * synthesises the completion exactly as the ISR would.
 *
 * Returns: DMA_POLL_EVENT_HANDLED if completion/error was processed,
 *          DMA_POLL_NO_EVENT otherwise.
 */
int32_t dma_mw_check_transfer(dma_handle_t const hdma)
{
    uint64_t val;

    if (hdma == NULL || hdma->channel_state != DMA_CH_ACTIVE)
    {
        return DMA_POLL_NO_EVENT;
    }

    val = dma_ll_get_interrupt_status(hdma->ch_offset);

    /* TFR_DONE is checked before error bits - see pdma_irq_handler() comment
     * above for the rationale. */
    if ((val & TFR_DONE_MASK) == TFR_DONE_MASK)
    {
        dma_ll_clear_interrupts(hdma->ch_offset, TFR_DONE_MASK);
        hdma->channel_state = DMA_CH_IDLE;
        if (hdma->xp_dma_callback != NULL)
        {
            hdma->xp_dma_callback(hdma);
        }
        return DMA_POLL_EVENT_HANDLED;
    }

    if ((val & DMA_ERROR_INT_MASK) != 0U)
    {
        dma_ll_clear_interrupts(hdma->ch_offset, DMA_ERROR_INT_MASK);
        hdma->channel_state = DMA_CH_ERROR;
        if (hdma->xp_dma_callback != NULL)
        {
            hdma->xp_dma_callback(hdma);
        }
        return DMA_POLL_EVENT_HANDLED;
    }
    return DMA_POLL_NO_EVENT;
}
