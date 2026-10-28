/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_ecc.c
 *
 * ECC source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errno.h"
#include "mmio.h"
#include "socfpga_ecc.h"
#include "socfpga_interrupt.h"
#include "socfpga_sip_handler.h"
#include "socfpga_sys_mngr_reg_plat.h"

/* -----------------------------------------------------------------------
 * Hardware addresses
 * ----------------------------------------------------------------------- */
#define ECC_OCRAM_BASE_ADDR       0x108CC000U
#define ECC_EMAC0_RX_BASE_ADDR    0x108C0000U
#define ECC_EMAC0_TX_BASE_ADDR    0x108C0400U
#define ECC_EMAC1_RX_BASE_ADDR    0x108C0800U
#define ECC_EMAC1_TX_BASE_ADDR    0x108C0C00U
#define ECC_EMAC2_RX_BASE_ADDR    0x108C1000U
#define ECC_EMAC2_TX_BASE_ADDR    0x108C1400U
#define ECC_USB0_RAM0_BASE_ADDR   0x108C4000U
#define ECC_USB1_RAM0_BASE_ADDR   0x108C4400U
#define ECC_USB1_RAM1_BASE_ADDR   0x108C4800U
#define ECC_USB1_RAM2_BASE_ADDR   0x108C4C00U
#define ECC_QSPI_BASE_ADDR        0x10A22000U

/* -----------------------------------------------------------------------
 * Per-block ECC controller registers
 * ----------------------------------------------------------------------- */
#define ECC_CTRL                  0x008U
#define ECC_INIT_STAT             0x00CU
#define ECC_ERR_INT_EN            0x010U
#define ECC_ERR_INT_SET           0x014U
#define ECC_ERR_INT_RESET         0x018U
#define ECC_INT_MODE              0x01CU
#define ECC_INT_STAT              0x020U
#define ECC_INT_TEST              0x024U
#define ECC_D_ERR_ADDR_A          0x02CU
#define ECC_S_ERR_ADDR_A          0x030U
#define ECC_S_ERR_CNT             0x03CU

/* CTRL bits */
#define ECC_CTRL_ECC_EN_BIT       (1U << 0)
#define ECC_CTRL_INIT_PORTA_BIT   (1U << 16)

/* INIT_STAT bits (port-A complete) */
#define ECC_INIT_STAT_PORTA_DONE  (1U << 0)

/* INT_STAT bits */
#define ECC_INT_STAT_SB_PORTA     (1U << 0)
#define ECC_INT_STAT_DB_PORTA     (1U << 8)

/* INT_TEST bits (force SBE/DBE on next access) */
#define ECC_INT_TEST_SB_PORTA     (1U << 0)
#define ECC_INT_TEST_DB_PORTA     (1U << 8)

/* -----------------------------------------------------------------------
 * SiP function IDs (mirror plat/altera/soc/common/include/socfpga_sip_svc.h)
 * ----------------------------------------------------------------------- */
#define SIP_SMC_REG_READ          0xC2000007U
#define SIP_SMC_REG_WRITE         0xC2000008U
#define SIP_SMC_INJECT_IO96B_ECC  0xC200009CU

#define SIP_SMC_STATUS_OK         0x0U

/* Sentinel for "this driver block is not aggregated in System Manager
 * intstatus_serr/derr" (e.g. QSPI which gets its own SDM_HPS_SPARE line). */
#define ECC_NO_SYSMGR_BIT         0xFFFFFFFFU

/* Memory init poll budget. Long enough for OCRAM (largest) at 200 MHz. */
#define ECC_MEM_INIT_TIMEOUT      200000U

/* -----------------------------------------------------------------------
 * Driver state
 * ----------------------------------------------------------------------- */
typedef struct {
    uint32_t base_addr;        /* hardware base or 0 if unused          */
    uint32_t sysmgr_bit;       /* sysmgr SERR/DERR bit, or NO_SYSMGR_BIT */
    volatile uint32_t sbe_cnt;          /* cumulative SBE seen in ISR/poll       */
    volatile uint32_t dbe_cnt;          /* cumulative DBE seen in ISR/poll       */
    bool     enabled;          /* ECC checking enabled by enable_blocks */
} socfpga_ecc_block_state_t;

typedef struct {
    socfpga_ecc_block_state_t blocks[SOCFPGA_ECC_BLOCK_MAX];
    socfpga_ecc_callback_t    user_cb;
    bool                      initialised;
} socfpga_ecc_state_t;

static socfpga_ecc_state_t s_ecc;

/* -----------------------------------------------------------------------
 * SiP helpers
 * ----------------------------------------------------------------------- */

static inline void smc_secure_reg_write32(uint64_t addr, uint32_t val)
{
    uint64_t args[SMC_CALL_REG_COUNT] = {0};
    args[0] = addr;
    args[1] = val;
    (void)smc_call(SIP_SMC_REG_WRITE, args);
}

static inline uint32_t smc_secure_reg_read32(uint64_t addr)
{
    uint64_t args[SMC_CALL_REG_COUNT] = {0};
    args[0] = addr;
    (void)smc_call(SIP_SMC_REG_READ, args);
    return (uint32_t)args[1];
}

static inline int32_t smc_inject_io96b_ecc(uint32_t syndrome, uint32_t command)
{
    uint64_t args[SMC_CALL_REG_COUNT] = {0};
    int      smc_ret;

    args[0] = syndrome;
    args[1] = command;
    smc_ret = smc_call(SIP_SMC_INJECT_IO96B_ECC, args);
    if (smc_ret != (int)SIP_SMC_STATUS_OK) {
        return -EIO;
    }
    return 0;
}

/* -----------------------------------------------------------------------
 * Per-block register helpers (transparent QSPI redirection to SMC)
 * ----------------------------------------------------------------------- */

static inline bool ecc_block_is_secure(uint32_t block)
{
    return (block == SOCFPGA_ECC_BLOCK_QSPI);
}

static inline uint32_t ecc_blk_read32(uint32_t block, uint32_t base, uint32_t off)
{
    if (ecc_block_is_secure(block)) {
        return smc_secure_reg_read32((uint64_t)base + off);
    }
    return RD_REG32(base + off);
}

static inline void ecc_blk_write32(uint32_t block, uint32_t base,
                                   uint32_t off, uint32_t val)
{
    if (ecc_block_is_secure(block)) {
        smc_secure_reg_write32((uint64_t)base + off, val);
    } else {
        WR_REG32(base + off, val);
    }
}

/* -----------------------------------------------------------------------
 * Block <-> System Manager bit translation
 *
 * The driver's SOCFPGA_ECC_BLOCK_* enum is opportunistically aligned with
 * the System Manager intstatus_serr / intstatus_derr bit positions for
 * OCRAM / USB0 / EMAC0..2 / USB1_RAM1 / USB1_RAM2 / DDR. A few enum
 * values are sentinels (USB1_RAM0 alias, QSPI) or have intentionally
 * different numeric values for backwards compatibility, so a per-block
 * lookup table maps the driver block to the sysmgr bit position.
 * ----------------------------------------------------------------------- */

static uint32_t ecc_block_sysmgr_bit(uint32_t block)
{
    switch (block) {
    case SOCFPGA_ECC_BLOCK_OCRAM:      return 1U;
    case SOCFPGA_ECC_BLOCK_USB0_RAM0:  return 2U;
    case SOCFPGA_ECC_BLOCK_USB1_RAM0:  return 3U;
    case SOCFPGA_ECC_BLOCK_EMAC0_RX:   return 4U;
    case SOCFPGA_ECC_BLOCK_EMAC0_TX:   return 5U;
    case SOCFPGA_ECC_BLOCK_EMAC1_RX:   return 6U;
    case SOCFPGA_ECC_BLOCK_EMAC1_TX:   return 7U;
    case SOCFPGA_ECC_BLOCK_EMAC2_RX:   return 8U;
    case SOCFPGA_ECC_BLOCK_EMAC2_TX:   return 9U;
    case SOCFPGA_ECC_BLOCK_USB1_RAM1:  return 11U;
    case SOCFPGA_ECC_BLOCK_USB1_RAM2:  return 12U;
    case SOCFPGA_ECC_BLOCK_DDR:
        /*
         * DDR0 is sysmgr SERR/DERR bit 16, but DDR ECC is enabled and
         * owned by ATF / IOSSM, not by this driver. We deliberately do
         * NOT track it through the sysmgr aggregation - on some
         * platforms (e.g. simulation models) the bit is asserted spuriously
         * since boot and would inflate the DDR software counters.
         * Use socfpga_ecc_get_sysmgr_*_status() if a caller needs the
         * raw DDR0 bit.
         */
        return ECC_NO_SYSMGR_BIT;
    case SOCFPGA_ECC_BLOCK_QSPI:       /* fallthrough */
    default:                           return ECC_NO_SYSMGR_BIT;
    }
}

static uint32_t ecc_sysmgr_bit_to_block(uint32_t bit)
{
    switch (bit) {
    case 1U:  return SOCFPGA_ECC_BLOCK_OCRAM;
    case 2U:  return SOCFPGA_ECC_BLOCK_USB0_RAM0;
    case 3U:  return SOCFPGA_ECC_BLOCK_USB1_RAM0;
    case 4U:  return SOCFPGA_ECC_BLOCK_EMAC0_RX;
    case 5U:  return SOCFPGA_ECC_BLOCK_EMAC0_TX;
    case 6U:  return SOCFPGA_ECC_BLOCK_EMAC1_RX;
    case 7U:  return SOCFPGA_ECC_BLOCK_EMAC1_TX;
    case 8U:  return SOCFPGA_ECC_BLOCK_EMAC2_RX;
    case 9U:  return SOCFPGA_ECC_BLOCK_EMAC2_TX;
    case 11U: return SOCFPGA_ECC_BLOCK_USB1_RAM1;
    case 12U: return SOCFPGA_ECC_BLOCK_USB1_RAM2;
    /* bit 16 (DDR0) is intentionally NOT mapped - see comment above. */
    default:  return SOCFPGA_ECC_BLOCK_NONE;
    }
}

/* OR of all sysmgr bits the driver software-counts. DDR0 (bit 16) is
 * deliberately excluded because DDR ECC is owned by ATF/IOSSM. */
#define ECC_SYSMGR_TRACKED_BITS \
    ((1U <<  1) | (1U <<  2) | (1U <<  3) | \
     (1U <<  4) | (1U <<  5) | (1U <<  6) | (1U <<  7) | \
     (1U <<  8) | (1U <<  9) | (1U << 11) | (1U << 12))

/* -----------------------------------------------------------------------
 * Internal helpers
 * ----------------------------------------------------------------------- */

static bool ecc_block_id_is_hps(uint32_t block)
{
    switch (block) {
    case SOCFPGA_ECC_BLOCK_OCRAM:
    case SOCFPGA_ECC_BLOCK_USB0_RAM0:
    case SOCFPGA_ECC_BLOCK_USB1_RAM0:
    case SOCFPGA_ECC_BLOCK_USB1_RAM1:
    case SOCFPGA_ECC_BLOCK_USB1_RAM2:
    case SOCFPGA_ECC_BLOCK_EMAC0_RX:
    case SOCFPGA_ECC_BLOCK_EMAC0_TX:
    case SOCFPGA_ECC_BLOCK_EMAC1_RX:
    case SOCFPGA_ECC_BLOCK_EMAC1_TX:
    case SOCFPGA_ECC_BLOCK_EMAC2_RX:
    case SOCFPGA_ECC_BLOCK_EMAC2_TX:
    case SOCFPGA_ECC_BLOCK_QSPI:
        return true;
    default:
        return false;
    }
}

static bool ecc_block_id_is_valid(uint32_t block)
{
    return (block > (uint32_t)SOCFPGA_ECC_BLOCK_NONE) &&
           (block <  (uint32_t)SOCFPGA_ECC_BLOCK_MAX);
}

static int32_t ecc_block_init_hw(uint32_t block)
{
    socfpga_ecc_block_state_t *blk;
    uint32_t base;
    uint32_t reg_val;
    uint32_t retries;
    uint32_t sysmgr_bit;

    blk = &s_ecc.blocks[block];
    if (blk->base_addr == 0U) {
        printf("ECC: block %u has no base address\n", (unsigned)block);
        return -EINVAL;
    }
    base = blk->base_addr;

    /* Disable existing SBE interrupt and ECC checking before init. */
    ecc_blk_write32(block, base, ECC_ERR_INT_RESET, 1U);

    reg_val = ecc_blk_read32(block, base, ECC_CTRL);
    reg_val &= ~ECC_CTRL_ECC_EN_BIT;
    ecc_blk_write32(block, base, ECC_CTRL, reg_val);

    /* Trigger hardware memory init on PORTA. */
    reg_val |= ECC_CTRL_INIT_PORTA_BIT;
    ecc_blk_write32(block, base, ECC_CTRL, reg_val);

    /* Wait for PORTA init done. */
    for (retries = 0U; retries < ECC_MEM_INIT_TIMEOUT; retries++) {
        if ((ecc_blk_read32(block, base, ECC_INIT_STAT) &
             ECC_INIT_STAT_PORTA_DONE) != 0U) {
            break;
        }
    }
    if (retries >= ECC_MEM_INIT_TIMEOUT) {
        /* Most likely the parent IP (EMAC / USB / QSPI) is held in reset
         * or unclocked on the current platform. Leave the block disabled
         * and let the caller decide whether that is fatal. */
        printf("ECC: block %u memory init timeout (parent IP not ready?)\n",
               (unsigned)block);
        blk->enabled = false;
        return -EIO;
    }

    /* Set SBE counter saturation to 1 so every SBE raises an interrupt. */
    ecc_blk_write32(block, base, ECC_S_ERR_CNT, 1U);

    /* Configure interrupt-on-distinct-error mode. */
    reg_val = ecc_blk_read32(block, base, ECC_INT_MODE);
    reg_val |= 1U;
    ecc_blk_write32(block, base, ECC_INT_MODE, reg_val);

    /* Re-enable ECC detection and correction. */
    reg_val = ecc_blk_read32(block, base, ECC_CTRL);
    reg_val |= ECC_CTRL_ECC_EN_BIT;
    ecc_blk_write32(block, base, ECC_CTRL, reg_val);

    /* Enable SBE interrupt at the block. */
    ecc_blk_write32(block, base, ECC_ERR_INT_SET, 1U);

    /* Unmask the corresponding line in the System Manager (if any). */
    sysmgr_bit = blk->sysmgr_bit;
    if (sysmgr_bit != ECC_NO_SYSMGR_BIT) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTMASK_CLR,
                 (1U << sysmgr_bit));
    }

    blk->enabled = true;
    return 0;
}

static int32_t ecc_block_disable_hw(uint32_t block)
{
    socfpga_ecc_block_state_t *blk;
    uint32_t base;
    uint32_t reg_val;
    uint32_t sysmgr_bit;

    blk = &s_ecc.blocks[block];
    if (blk->base_addr == 0U) {
        return -EINVAL;
    }
    base = blk->base_addr;

    /* Disable SBE interrupt. */
    ecc_blk_write32(block, base, ECC_ERR_INT_RESET, 1U);

    /* Disable ECC detection / correction. */
    reg_val = ecc_blk_read32(block, base, ECC_CTRL);
    reg_val &= ~ECC_CTRL_ECC_EN_BIT;
    ecc_blk_write32(block, base, ECC_CTRL, reg_val);

    /* Mask the System Manager line. */
    sysmgr_bit = blk->sysmgr_bit;
    if (sysmgr_bit != ECC_NO_SYSMGR_BIT) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTMASK_SET,
                 (1U << sysmgr_bit));
    }

    blk->enabled = false;
    return 0;
}

static void ecc_handle_serr_block(uint32_t block)
{
    socfpga_ecc_block_state_t *blk = &s_ecc.blocks[block];
    uint32_t base = blk->base_addr;
    uint32_t int_stat;

    if (base == 0U) {
        return;
    }
    int_stat = ecc_blk_read32(block, base, ECC_INT_STAT);
    if ((int_stat & ECC_INT_STAT_SB_PORTA) != 0U) {
        uint32_t addr = ecc_blk_read32(block, base, ECC_S_ERR_ADDR_A);
        printf("ECC: SBE block=%u err_addr=0x%08x\n",
               (unsigned)block, (unsigned)addr);
        ecc_blk_write32(block, base, ECC_INT_STAT, ECC_INT_STAT_SB_PORTA);
        blk->sbe_cnt++;
    }
}

static void ecc_handle_derr_block(uint32_t block)
{
    socfpga_ecc_block_state_t *blk = &s_ecc.blocks[block];
    uint32_t base = blk->base_addr;
    uint32_t int_stat;

    if (base == 0U) {
        return;
    }
    int_stat = ecc_blk_read32(block, base, ECC_INT_STAT);
    if ((int_stat & ECC_INT_STAT_DB_PORTA) != 0U) {
        uint32_t addr = ecc_blk_read32(block, base, ECC_D_ERR_ADDR_A);
        printf("ECC: DBE block=%u err_addr=0x%08x\n",
               (unsigned)block, (unsigned)addr);
        ecc_blk_write32(block, base, ECC_INT_STAT, ECC_INT_STAT_DB_PORTA);
        blk->dbe_cnt++;
    }
}

/*
 * Walk every set bit in a sysmgr SERR/DERR snapshot, dispatch a per-block
 * handler, optionally invoke the user callback, and W1C the original
 * sysmgr bit so a follow-up event can be observed. Returns the bitmap of
 * bits actually processed (which may be a subset of @snapshot if some
 * bits do not map back to a known block).
 */
static uint32_t ecc_dispatch_sysmgr_status(uint32_t snapshot,
                                           bool is_double,
                                           bool fire_callback)
{
    uint32_t handled = 0U;
    uint32_t bit;

    snapshot &= ECC_SYSMGR_TRACKED_BITS;
    for (bit = 0U; bit < 32U; bit++) {
        uint32_t mask = (1U << bit);
        uint32_t block;

        if ((snapshot & mask) == 0U) {
            continue;
        }
        block = ecc_sysmgr_bit_to_block(bit);
        if (block == (uint32_t)SOCFPGA_ECC_BLOCK_NONE) {
            continue;
        }

        if (is_double) {
            if (s_ecc.blocks[block].base_addr != 0U) {
                ecc_handle_derr_block(block);
            } else {
                /* DDR0 has no MMIO base in this driver. Just count. */
                s_ecc.blocks[block].dbe_cnt++;
            }
        } else {
            if (s_ecc.blocks[block].base_addr != 0U) {
                ecc_handle_serr_block(block);
            } else {
                s_ecc.blocks[block].sbe_cnt++;
            }
        }

        if (fire_callback && (s_ecc.user_cb != NULL)) {
            s_ecc.user_cb(block,
                          is_double ? (uint32_t)SOCFPGA_ECC_ERR_DBE
                                    : (uint32_t)SOCFPGA_ECC_ERR_SBE);
        }
        handled |= mask;
    }
    return handled;
}

/* -----------------------------------------------------------------------
 * ISRs
 * ----------------------------------------------------------------------- */

static void ecc_serr_global_isr(void *param)
{
    uint32_t status;
    uint32_t handled;

    (void)param;

    status = RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR);
    handled = ecc_dispatch_sysmgr_status(status, false, true);
    if (handled != 0U) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR, handled);
    }
}

static void ecc_derr_global_isr(void *param)
{
    uint32_t status;
    uint32_t handled;

    (void)param;

    status = RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR);
    handled = ecc_dispatch_sysmgr_status(status, true, true);
    if (handled != 0U) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR, handled);
    }
}

static void ecc_qspi_isr(void *param)
{
    uint32_t base = s_ecc.blocks[SOCFPGA_ECC_BLOCK_QSPI].base_addr;
    uint32_t status;

    (void)param;

    if (base == 0U) {
        return;
    }
    status = smc_secure_reg_read32((uint64_t)base + ECC_INT_STAT);
    if ((status & ECC_INT_STAT_SB_PORTA) != 0U) {
        smc_secure_reg_write32((uint64_t)base + ECC_INT_STAT,
                               ECC_INT_STAT_SB_PORTA);
        s_ecc.blocks[SOCFPGA_ECC_BLOCK_QSPI].sbe_cnt++;
        if (s_ecc.user_cb != NULL) {
            s_ecc.user_cb(SOCFPGA_ECC_BLOCK_QSPI,
                          (uint32_t)SOCFPGA_ECC_ERR_SBE);
        }
    }
    if ((status & ECC_INT_STAT_DB_PORTA) != 0U) {
        smc_secure_reg_write32((uint64_t)base + ECC_INT_STAT,
                               ECC_INT_STAT_DB_PORTA);
        s_ecc.blocks[SOCFPGA_ECC_BLOCK_QSPI].dbe_cnt++;
        if (s_ecc.user_cb != NULL) {
            s_ecc.user_cb(SOCFPGA_ECC_BLOCK_QSPI,
                          (uint32_t)SOCFPGA_ECC_ERR_DBE);
        }
    }
}

/* -----------------------------------------------------------------------
 * Public driver API
 * ----------------------------------------------------------------------- */

int32_t socfpga_ecc_init(void)
{
    socfpga_interrupt_err_t int_ret;
    uint32_t                i;

    if (s_ecc.initialised) {
        printf("ECC: already initialised\n");
        return -EINVAL;
    }

    (void)memset(&s_ecc, 0, sizeof(s_ecc));

    s_ecc.blocks[SOCFPGA_ECC_BLOCK_OCRAM].base_addr      = ECC_OCRAM_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC0_RX].base_addr   = ECC_EMAC0_RX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC0_TX].base_addr   = ECC_EMAC0_TX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC1_RX].base_addr   = ECC_EMAC1_RX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC1_TX].base_addr   = ECC_EMAC1_TX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC2_RX].base_addr   = ECC_EMAC2_RX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_EMAC2_TX].base_addr   = ECC_EMAC2_TX_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_USB0_RAM0].base_addr  = ECC_USB0_RAM0_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_USB1_RAM0].base_addr  = ECC_USB1_RAM0_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_USB1_RAM1].base_addr  = ECC_USB1_RAM1_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_USB1_RAM2].base_addr  = ECC_USB1_RAM2_BASE_ADDR;
    s_ecc.blocks[SOCFPGA_ECC_BLOCK_QSPI].base_addr       = ECC_QSPI_BASE_ADDR;
    /* DDR has no MMIO base in this driver - it is reached via SiP. */

    /* Cache sysmgr bit for every block so we don't recompute later. */
    for (i = 0U; i < (uint32_t)SOCFPGA_ECC_BLOCK_MAX; i++) {
        s_ecc.blocks[i].sysmgr_bit = ecc_block_sysmgr_bit(i);
    }

    /* Mask all sysmgr ECC interrupts before wiring up the GIC. */
    WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTMASK_SET,
             ECC_SYSMGR_TRACKED_BITS);

    /* Clear any leftover sysmgr SERR/DERR pending bits from boot. */
    WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR,
             ECC_SYSMGR_TRACKED_BITS);
    WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR,
             ECC_SYSMGR_TRACKED_BITS);

    /* Wire up the global SERR / DERR handlers. */
    int_ret = interrupt_register_isr(SERR_GLOBAL, ecc_serr_global_isr, NULL);
    if (int_ret == ERR_OK) {
        (void)interrupt_enable(SERR_GLOBAL, GIC_INTERRUPT_PRIORITY_EDAC);
    } else {
        printf("ECC: SERR_GLOBAL ISR register failed (%d), continuing\n",
               (int)int_ret);
    }

    int_ret = interrupt_register_isr(ECC_DERR_INTR_N, ecc_derr_global_isr,
                                     NULL);
    if (int_ret == ERR_OK) {
        (void)interrupt_enable(ECC_DERR_INTR_N, GIC_INTERRUPT_PRIORITY_EDAC);
    } else {
        printf("ECC: ECC_DERR_INTR_N ISR register failed (%d), continuing\n",
               (int)int_ret);
    }

    /* QSPI ECC SBE / DBE come in via SDM_HPS_SPARE_INTR1 / 2. These lines
     * may not be hooked up on every platform (e.g. simulation models) so we
     * tolerate registration failures and continue with polling.            */
    int_ret = interrupt_register_isr(SDM_HPS_SPARE_INTR1, ecc_qspi_isr, NULL);
    if (int_ret == ERR_OK) {
        (void)interrupt_enable(SDM_HPS_SPARE_INTR1,
                               GIC_INTERRUPT_PRIORITY_EDAC);
    }
    int_ret = interrupt_register_isr(SDM_HPS_SPARE_INTR2, ecc_qspi_isr, NULL);
    if (int_ret == ERR_OK) {
        (void)interrupt_enable(SDM_HPS_SPARE_INTR2,
                               GIC_INTERRUPT_PRIORITY_EDAC);
    }

    s_ecc.initialised = true;
    return 0;
}

int32_t socfpga_ecc_deinit(void)
{
    if (!s_ecc.initialised) {
        return -EINVAL;
    }

    WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTMASK_SET,
             ECC_SYSMGR_TRACKED_BITS);

    s_ecc.user_cb = NULL;
    s_ecc.initialised = false;
    return 0;
}

int32_t socfpga_ecc_enable_blocks(uint32_t block_mask)
{
    uint32_t i;
    int32_t  rc;
    uint32_t enabled = 0U;
    uint32_t failed  = 0U;

    if (!s_ecc.initialised) {
        return -EINVAL;
    }
    if ((block_mask & SOCFPGA_ECC_BLOCK_MASK_ALL_HPS) == 0U) {
        printf("ECC: no valid blocks in mask 0x%x\n", (unsigned)block_mask);
        return -EINVAL;
    }

    /*
     * Try each requested block independently. A timeout on one block
     * (e.g. EMAC ECC when the EMAC controller is held in reset) must
     * not prevent other blocks from being enabled. The return code
     * reports failure only if EVERY requested block failed.
     */
    for (i = (uint32_t)SOCFPGA_ECC_BLOCK_NONE + 1U;
         i < (uint32_t)SOCFPGA_ECC_BLOCK_MAX; i++) {
        if ((block_mask & (1U << i)) == 0U) {
            continue;
        }
        if (!ecc_block_id_is_hps(i)) {
            continue;
        }
        if (s_ecc.blocks[i].enabled) {
            enabled++;
            continue;
        }
        rc = ecc_block_init_hw(i);
        if (rc == 0) {
            enabled++;
        } else {
            failed++;
        }
    }

    if (enabled == 0U) {
        return (failed != 0U) ? -EIO : -EINVAL;
    }
    return 0;
}

int32_t socfpga_ecc_disable_blocks(uint32_t block_mask)
{
    uint32_t i;
    int32_t  rc;

    if (!s_ecc.initialised) {
        return -EINVAL;
    }
    for (i = (uint32_t)SOCFPGA_ECC_BLOCK_NONE + 1U;
         i < (uint32_t)SOCFPGA_ECC_BLOCK_MAX; i++) {
        if ((block_mask & (1U << i)) == 0U) {
            continue;
        }
        if (!ecc_block_id_is_hps(i)) {
            continue;
        }
        if (!s_ecc.blocks[i].enabled) {
            continue;
        }
        rc = ecc_block_disable_hw(i);
        if (rc != 0) {
            return rc;
        }
    }
    return 0;
}

int32_t socfpga_ecc_inject_block_err(uint32_t block, uint32_t err_type)
{
    uint32_t base;
    uint32_t test;

    if (!s_ecc.initialised) {
        return -EINVAL;
    }
    if (!ecc_block_id_is_hps(block)) {
        printf("ECC: inject_block_err: block %u not a HPS block\n",
               (unsigned)block);
        return -EINVAL;
    }
    base = s_ecc.blocks[block].base_addr;
    if (base == 0U) {
        return -EINVAL;
    }
    if (!s_ecc.blocks[block].enabled) {
        printf("ECC: inject_block_err: block %u not enabled; "
               "call socfpga_ecc_enable_blocks() first\n",
               (unsigned)block);
        return -EINVAL;
    }

    switch (err_type) {
    case (uint32_t)SOCFPGA_ECC_ERR_SBE:
        test = ECC_INT_TEST_SB_PORTA;
        break;
    case (uint32_t)SOCFPGA_ECC_ERR_DBE:
        test = ECC_INT_TEST_DB_PORTA;
        break;
    default:
        return -EINVAL;
    }

    ecc_blk_write32(block, base, ECC_INT_TEST, test);
    return 0;
}

int32_t socfpga_ecc_inject_ddr_err(uint32_t syndrome, uint32_t command)
{
    if (!s_ecc.initialised) {
        return -EINVAL;
    }
    return smc_inject_io96b_ecc(syndrome, command);
}

int32_t socfpga_ecc_poll_status(uint32_t *out_serr_bits,
                                uint32_t *out_derr_bits)
{
    uint32_t serr;
    uint32_t derr;
    uint32_t s_handled;
    uint32_t d_handled;
    int32_t  events = 0;
    uint32_t bit;

    if (out_serr_bits != NULL) {
        *out_serr_bits = 0U;
    }
    if (out_derr_bits != NULL) {
        *out_derr_bits = 0U;
    }
    if (!s_ecc.initialised) {
        return 0;
    }

    serr = RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR);
    s_handled = ecc_dispatch_sysmgr_status(serr, false, false);
    if (s_handled != 0U) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR,
                 s_handled);
    }

    derr = RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR);
    d_handled = ecc_dispatch_sysmgr_status(derr, true, false);
    if (d_handled != 0U) {
        WR_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR,
                 d_handled);
    }

    /* Count bits we actually translated into per-block updates. */
    for (bit = 0U; bit < 32U; bit++) {
        if ((s_handled & (1U << bit)) != 0U) {
            events++;
        }
        if ((d_handled & (1U << bit)) != 0U) {
            events++;
        }
    }

    if (out_serr_bits != NULL) {
        *out_serr_bits = s_handled;
    }
    if (out_derr_bits != NULL) {
        *out_derr_bits = d_handled;
    }
    return events;
}

int32_t socfpga_ecc_get_sbe_count(uint32_t block)
{
    if (!ecc_block_id_is_valid(block)) {
        return -EINVAL;
    }
    return (int32_t)s_ecc.blocks[block].sbe_cnt;
}

int32_t socfpga_ecc_get_dbe_count(uint32_t block)
{
    if (!ecc_block_id_is_valid(block)) {
        return -EINVAL;
    }
    return (int32_t)s_ecc.blocks[block].dbe_cnt;
}

int32_t socfpga_ecc_get_hw_sbe_count(uint32_t block)
{
    socfpga_ecc_block_state_t *blk;

    if (!s_ecc.initialised) {
        return -EINVAL;
    }
    if (!ecc_block_id_is_hps(block)) {
        return -EINVAL;
    }
    blk = &s_ecc.blocks[block];
    if ((blk->base_addr == 0U) || !blk->enabled) {
        return -EINVAL;
    }
    return (int32_t)ecc_blk_read32(block, blk->base_addr, ECC_S_ERR_CNT);
}

int32_t socfpga_ecc_clear_counters(uint32_t block)
{
    uint32_t i;

    if (block == (uint32_t)SOCFPGA_ECC_BLOCK_NONE) {
        for (i = 0U; i < (uint32_t)SOCFPGA_ECC_BLOCK_MAX; i++) {
            s_ecc.blocks[i].sbe_cnt = 0U;
            s_ecc.blocks[i].dbe_cnt = 0U;
        }
        return 0;
    }
    if (!ecc_block_id_is_valid(block)) {
        return -EINVAL;
    }
    s_ecc.blocks[block].sbe_cnt = 0U;
    s_ecc.blocks[block].dbe_cnt = 0U;
    return 0;
}

int32_t socfpga_ecc_set_callback(socfpga_ecc_callback_t callback)
{
    s_ecc.user_cb = callback;
    return 0;
}

uint32_t socfpga_ecc_get_sysmgr_serr_status(void)
{
    return RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_SERR);
}

uint32_t socfpga_ecc_get_sysmgr_derr_status(void)
{
    return RD_REG32(SYS_MNGR_BASE_ADDR + SYS_MNGR_ECC_INTSTATUS_DERR);
}

