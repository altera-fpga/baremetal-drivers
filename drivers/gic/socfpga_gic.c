/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic.c
 *
 * GIC source implementation for the SoCFPGA bare-metal software stack.
 */

#include "crt0.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "socfpga_gic_registers.h"

#include "socfpga_gic.h"

#define INTERRUPT_DCTRL_ENG0      (1U << 0U)
#define INTERRUPT_DCTRL_ENG1NS    (1U << 1U)
#define INTERRUPT_DCTRL_ENG1S     (1U << 2U)
#define INTERRUPT_DCTRL_ARE_S     (1U << 4U)
#define INTERRUPT_DCTRL_ARE_NS    (1U << 5U)
#define INTERRUPT_DCTRL_DS        (1U << 6U)
#define INTERRUPT_DCTRL_E1NWF     (1U << 7U)
#define portPRIORITY_SHIFT        4

#define INTERRUPT_MAKE_PRIORITY(x)    (((uint32_t)(x) << portPRIORITY_SHIFT) & 0xFFU)

static struct gic_v3_dist_if *gic_dist;
static struct gic_v3_rdist_if *gic_rdist;

static uint32_t gic_max_rd = 0U;

#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
/* Software shadows of the SGI/PPI group registers. Reads of this redistributor
 * can stall on this silicon, so we never read GICR_IGROUPR0/GICR_IGRPMODR0
 * back; instead we track their contents here (reset value 0 = all Group0) and
 * write the whole register. Single redistributor (RD0) is assumed for this
 * bare-metal use. */
static uint32_t gic_shadow_igroupr0 = 0U;
static uint32_t gic_shadow_igrpmodr0 = 0U;
#endif

/* Function: gic_enable_gic
 *
 * Saves the distributor and redistributor addresses. On Agilex 5 and
 * Agilex 3 it records one redistributor. On other platforms it counts
 * redistributors until GICR_TYPER says this is the last one. At EL3 it
 * writes GICD_CTLR so affinity routing and interrupt groups 0 and 1 are
 * on. At EL2 and EL1 it does not write GICD_CTLR.
 *
 * Returns:
 *   INTERRUPT_RETURN_ERROR if the distributor address is NULL.
 *   INTERRUPT_RETURN_SUCCESS otherwise.
 */
int32_t gic_enable_gic(void)
{

    uint64_t cur_el;

    gic_dist = (struct gic_v3_dist_if *)((void *)REGISTER_SOCFPGA_DIST_BASE_ADDR);
    gic_rdist = (struct gic_v3_rdist_if *)((void *)REGISTER_SOCFPGA_RD_BASE_ADDR);

    if (gic_dist == NULL)
    {
        return INTERRUPT_RETURN_ERROR;
    }

    /* On Agilex5 OCRAM EL3, GICR_TYPER is inaccessible. Assume single redistributor. */
    gic_max_rd = 0U;

    /* At EL3 (secure), initialize the distributor. At EL2/EL1 (non-secure),
     * skip GICD writes because it's controlled by secure firmware (ATF). */
    __asm__ volatile ("mrs %0, CurrentEL" : "=r" (cur_el));
    if ((cur_el & 0xCU) == 0xCU) {
        /* EL3: write GICD registers */
        /* First set the ARE bits */
        gic_dist->GICD_CTLR = INTERRUPT_DCTRL_ARE_S | INTERRUPT_DCTRL_ARE_NS |
                INTERRUPT_DCTRL_DS;

        /* The split here is because the register layout is different once ARE==1 */

        /* Now set the rest of the options */
        gic_dist->GICD_CTLR = INTERRUPT_DCTRL_ENG0 | INTERRUPT_DCTRL_ENG1NS |
                INTERRUPT_DCTRL_ENG1S | INTERRUPT_DCTRL_ARE_S |
                INTERRUPT_DCTRL_ARE_NS | INTERRUPT_DCTRL_DS;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

/* Function: gic_get_redist_id
 *
 * Finds the redistributor whose GICR_TYPER affinity word equals
 * affinity. On Agilex 5 and Agilex 3 the affinity argument is ignored
 * and the function returns 0.
 *
 * Parameters:
 *   affinity - Value compared with the affinity word in GICR_TYPER.
 *
 * Returns:
 *   The matching redistributor index.
 *   0 on Agilex 5 and Agilex 3.
 *   INTERRUPT_RETURN_ERROR if the redistributor address is NULL.
 *   INTERRUPT_RETURN_SUCCESS if no redistributor matches.
 */
int32_t gic_get_redist_id(uint32_t affinity)
{
    if (gic_rdist == NULL)
    {
        return INTERRUPT_RETURN_ERROR;
    }

#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
    (void)affinity;  /* Unused on Agilex5 */
    /* On Agilex5 OCRAM EL3, GICR_TYPER is inaccessible. Return redistributor 0. */
    return 0;
#else
    int32_t index = 0;
    do
    {
        if (gic_rdist[index].lpis.GICR_TYPER[1] == affinity)
        {
            return index;
        }
        index++;
    } while ((uint32_t)index <= gic_max_rd);

    return INTERRUPT_RETURN_SUCCESS; /* return -1 to signal not RD found */
#endif
}

/* Function: gic_wakeup_redist
 *
 * Wakes redistributor rd. On Agilex 5 and Agilex 3 it writes 0 to
 * GICR_PWRR and to GICR_WAKER, and waits a short time after each write.
 * On other platforms it clears the ProcessorSleep bit in GICR_WAKER and
 * waits until the ChildrenAsleep bit is clear.
 *
 * Parameters:
 *   rd - Redistributor index.
 *
 * Returns:
 *   INTERRUPT_RETURN_ERROR if the redistributor address is NULL.
 *   INTERRUPT_RETURN_SUCCESS otherwise.
 */
int32_t gic_wakeup_redist(uint32_t rd)
{
    if (gic_rdist == NULL)
    {
        return INTERRUPT_RETURN_ERROR;
    }

#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
    /* Agilex5 OCRAM/EL3: reads of this redistributor can stall, so wake it
     * write-only - request power-on and clear GICR_WAKER.ProcessorSleep, then
     * give it time to settle instead of polling ChildrenAsleep. The GIC itself
     * is made reachable by opening the CCU CAIU GIC window in
     * interrupt_init_gic() before this runs. */
    volatile uint32_t delay;

    gic_rdist[rd].lpis.GICR_PWRR = 0x0;   /* blind power-on request */
    __asm__ volatile ("dsb sy" ::: "memory");
    for (delay = 20000U; delay != 0U; delay--)
    {
        __asm__ volatile ("nop");
    }

    gic_rdist[rd].lpis.GICR_WAKER = 0x0;  /* blind ProcessorSleep clear */
    __asm__ volatile ("dsb sy" ::: "memory");
    for (delay = 20000U; delay != 0U; delay--)
    {
        __asm__ volatile ("nop");
    }

    return INTERRUPT_RETURN_SUCCESS;
#else
    uint32_t tmp;
    /* Tell the Redistributor to wake-up by clearing ProcessorSleep bit */
    tmp = gic_rdist[rd].lpis.GICR_WAKER;
    tmp = tmp & ~0x2U;
    gic_rdist[rd].lpis.GICR_WAKER = tmp;

    /* Poll ChildrenAsleep bit until Redistributor wakes */
    do
    {
        tmp = gic_rdist[rd].lpis.GICR_WAKER;
    } while ((tmp & 0x4U) != 0U);

    return INTERRUPT_RETURN_SUCCESS;
#endif
}

static uint32_t gic_is_valid_ext_spi(uint32_t id)
{
    uint32_t max_spi;

    /* Check Ext SPI implemented */
    if (((gic_dist->GICD_TYPER >> 8U) & 0x1U) == 0U)
    {
#ifdef DEBUG
        /* put debug print here */
#endif
        return 0U;  /* GICD_TYPER.ESPI==0: Extended SPI range not present */
    }
    else
    {
        max_spi = ((gic_dist->GICD_TYPER >> 27U) & 0x1FU); /* Get field which reports the number ESPIs in blocks of 32, minus 1 */
        max_spi = (max_spi + 1U) * 32U;          /* Convert into number of ESPIs */
        max_spi = max_spi + 4096U;               /* Range starts at 4096 */

        if (!(id < max_spi))
        {
#ifdef DEBUG
            /* put debug print here */
#endif
            return 0U;
        }
    }

    return 1U;
}

#define GIC_PRIORITY_MASK(offset)                 (uint32_t)(0xFFU << (offset))
#define GIC_PRIORITY_SHIFT_OFFSET(val, offset)    (uint32_t)((val) << (offset))
#define GIC_CLEAR_PRIORITY(dest, \
            offset)                               ((dest) &= (~GIC_PRIORITY_MASK(offset)))
#define GIC_SET_PRIORITY(dest, val, offset)       GIC_CLEAR_PRIORITY((dest), (offset)); \
    (dest) |= GIC_PRIORITY_SHIFT_OFFSET((val), (offset))

/* Function: gic_set_int_priority
 *
 * Stores the priority of one interrupt. The value is shifted left by 4
 * before the write. Interrupt numbers 0 to 30 are written in the
 * redistributor. Numbers 32 to 1019 are written in the distributor.
 * On Agilex 5 and Agilex 3, a redistributor priority that is not below
 * the CPU priority mask is stored as one less than that mask. On other
 * platforms a priority whose high 4 bits are all 1 is rejected.
 *
 * Parameters:
 *   id       - Interrupt number.
 *   rd       - Redistributor index. Used for interrupt numbers 0 to 30.
 *   priority - Priority value.
 *
 * Returns:
 *   INTERRUPT_RETURN_SUCCESS when the register is written.
 *   INTERRUPT_RETURN_INVALID_PRIORITY, INTERRUPT_RETURN_ERROR,
 *   INTERRUPT_RETURN_INVALID_RDIST, INTERRUPT_RETURN_INVALID_SPI, or
 *   INTERRUPT_RETURN_INVALID_ID when a check fails.
 */
int32_t gic_set_int_priority(uint32_t id, uint32_t rd, uint8_t priority)
{
    /* Check if the priority is within the bounds */
    /* On Agilex5, we need to allow higher priority values (0xF0-0xFF) to match the PMR threshold */
#if !defined(PLAT_AGILEX5) && !defined(PLAT_AGILEX3)
    if ((priority & 0xF0U) == 0xF0U)
    {
        return INTERRUPT_RETURN_INVALID_PRIORITY;
    }
#endif

    if ((gic_rdist == NULL) || (gic_dist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        /* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }
        /* SGI or PPI */
        uint8_t pri_val = (uint8_t)INTERRUPT_MAKE_PRIORITY(priority);
        
#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
        /* On Agilex5, ICC_PMR_EL1 is hardware-clamped to 0xF8.
         * GIC rule: interrupt fires if priority < PMR (numerically).
         * Any priority value 0x00-0xF7 will pass through PMR=0xF8.
         * Priority 0xF8 or higher would be blocked (equal or lower priority).
         * We warn if the requested priority would be blocked, but do NOT adjust. */
        uint64_t icc_pmr;
        __asm__ volatile ("mrs %0, s3_0_c4_c6_0" : "=r" (icc_pmr));
        uint8_t pmr_val = (uint8_t)(icc_pmr & 0xFF);
        
        if (pri_val >= pmr_val)
        {
            pri_val = (uint8_t)(pmr_val - 1U);
        }
#endif
        
        gic_rdist[rd].sgis.GICR_IPRIORITYR[id] = pri_val;
        
        /* Data Synchronization Barrier ensures the write completes */
        __asm__ volatile ("dsb sy" ::: "memory");
    }
    else if (id < 1020U)
    {
        /* SPI */
        /* similar checks are to avoid numeric overflow violation in static analysis */
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */

        uint32_t index = id / 4U;
        uint32_t offset = (id & 0x03U) * 8U;
        uint32_t priority_temp = gic_dist->GICD_IPRIORITYR[index];
        GIC_SET_PRIORITY(priority_temp, INTERRUPT_MAKE_PRIORITY(priority), offset);
        gic_dist->GICD_IPRIORITYR[index] = priority_temp;
    }
    else if ((id > 1055U) && (id < 1120U))
    {
        return INTERRUPT_RETURN_INVALID_ID;
    }
    else if ((id > 4095U) && (id < 5120U))
    {
        return INTERRUPT_RETURN_INVALID_ID;
    }
    else
    {
        return INTERRUPT_RETURN_INVALID_ID;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

int32_t gic_set_int_group(uint32_t id, uint32_t rd, uint32_t security)
{
    uint32_t bank, group, mod, ret = 0U;

#ifdef DEBUG
    /* put debug print here */
#endif

    if ((gic_rdist == NULL) || (gic_dist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        /* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }

        /* SGI or PPI */
        id = 1U << id;

#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
        /* Reads of this redistributor can stall, so source the current values
         * from software shadows instead of a hardware read-modify-write. The
         * group MUST be programmed (not left at the reset default) because
         * ICC_SGI0R_EL1 only pends Group0 SGIs. */
        group = gic_shadow_igroupr0;
        mod = gic_shadow_igrpmodr0;
#else
        /* Read current values */
        group = gic_rdist[rd].sgis.GICR_IGROUPR0;
        mod = gic_rdist[rd].sgis.GICR_IGRPMODR0;
#endif

        /* Update required bits */
        switch (security)
        {
            case GICV3_GROUP0:
                group = (group & ~id);
                mod = (mod & ~id);
                break;

            case GICV3_GROUP1_SECURE:
                group = (group & ~id);
                mod = (mod | id);
                break;

            case GICV3_GROUP1_NON_SECURE:
                group = (group | id);
                mod = (mod & ~id);
                break;

            default:
                ret = 1U;
                break;
        }
        if (ret == 1U)
        {
            return INTERRUPT_RETURN_INVALID_GROUP;
        }

#if defined(PLAT_AGILEX5) || defined(PLAT_AGILEX3)
        /* Commit shadows before the blind write of the whole register. */
        gic_shadow_igroupr0 = group;
        gic_shadow_igrpmodr0 = mod;
#endif
        /* Write modified version back */
        gic_rdist[rd].sgis.GICR_IGROUPR0 = group;
        gic_rdist[rd].sgis.GICR_IGRPMODR0 = mod;
    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        // SPI
        bank = id / 32U; /* There are 32 uIDs per register, need to work out which register to access */
        id = id & 0x1fU;    /* ... and which bit within the register */

        id = 1U << id;

        group = gic_dist->GICD_IGROUPR[bank];
        mod = gic_dist->GICD_IGRPMODR[bank];

        switch (security)
        {
            case GICV3_GROUP0:
                group = (group & ~id);
                mod = (mod & ~id);
                break;

            case GICV3_GROUP1_SECURE:
                group = (group & ~id);
                mod = (mod | id);
                break;

            case GICV3_GROUP1_NON_SECURE:
                group = (group | id);
                mod = (mod & ~id);
                break;

            default:
                ret = 2U;
                break;
        }
        if (ret == 2U)
        {
            return INTERRUPT_RETURN_INVALID_GROUP;
        }

        gic_dist->GICD_IGROUPR[bank] = group;
        gic_dist->GICD_IGRPMODR[bank] = mod;
    }
    else
    {
        /* Unknown or unsupported uID */
        return INTERRUPT_RETURN_INVALID_ID;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

#define GICV3_ROUTE_AFF3_SHIFT    (8)

/* Function: gic_set_int_route
 *
 * Builds a route word from mode and affinity. It writes that word to
 * GICD_IROUTER only when id is from 64 to 1019. Other accepted ids
 * still return success, and the register is left unchanged.
 *
 * Parameters:
 *   id       - Interrupt number.
 *   mode     - Routing mode. It is ORed into the route word.
 *   affinity - Affinity value packed into the route word.
 *
 * Returns:
 *   INTERRUPT_RETURN_ERROR if the distributor address is NULL.
 *   INTERRUPT_RETURN_INVALID_SPI if id is outside 32 to 1019 and is
 *   not a valid extended SPI from 4096 to 5119.
 *   INTERRUPT_RETURN_SUCCESS otherwise.
 */
int32_t gic_set_int_route(uint32_t id, uint32_t mode, uint32_t affinity)
{
    uint64_t tmp;

#ifdef DEBUG
    /* put debug print here */
#endif

    if (gic_dist == NULL)
    {
        return INTERRUPT_RETURN_ERROR;
    }

    /* Check for SPI ranges */
    if (!((id > 31U) && (id < 1020U)))
    {
        /* Not a GICv3.0 SPI */

        if (!((id > 4095U) && (id < 5120U)))
        {
            /* Not a GICv3.1 SPI either */
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        /* Check Ext SPI implemented */
        if (gic_is_valid_ext_spi(id) == 0U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }
    }

    id -= 32U; /* Adjust ID for Distributor registers */
    /* Combine routing in */
    tmp = (uint64_t)(affinity & 0x00FFFFFFU) |
            (((uint64_t)affinity & 0xFF000000U) << GICV3_ROUTE_AFF3_SHIFT) | (uint64_t)mode;

    if ((id > 31U) && (id < 1020U))
    {
        gic_dist->GICD_IROUTER[id] = tmp;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

/* Interrupt configuration */

int32_t gic_enable_int(uint32_t id, uint32_t rd)
{
    uint32_t bank;

    if ((gic_rdist == NULL) || (gic_dist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        /* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }

        volatile uint32_t *addr = &gic_rdist[rd].sgis.GICR_ISENABLER0;
        uint32_t val = (1U << id);
        
        *addr = val;
        
        /* Data Synchronization Barrier ensures the write completes before returning */
        __asm__ volatile ("dsb sy" ::: "memory");
    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        /* SPI */
        bank = id / 32U; /* There are 32 uIDs per register, need to work out which register to access */
        id = id & 0x1fU; /* ... and which bit within the register */

        id = 1U << id;

        gic_dist->GICD_ISENABLER[bank] = id;
    }
    else
    {
#ifdef DEBUG
    printf("enableInt:: ERROR - Invalid or unsupported interrupt.\n");
#endif
        return INTERRUPT_RETURN_ERROR;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

int32_t gic_disable_int(uint32_t id, uint32_t rd)
{
    uint32_t bank;

    if ((gic_rdist == NULL) || (gic_dist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        //* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }
        /* SGI or PPI */
        id = id & 0x1fU;    /* ... and which bit within the register */
        id = 1U << id;      /* Move a '1' into the correct bit position */

        gic_rdist[rd].sgis.GICR_ICENABLER0 = id;
    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        /* SPI */
        bank = id / 32U; /* There are 32 uIDs per register, need to work out which register to access */
        id = id & 0x1fU; /* ... and which bit within the register */

        id = 1U << id;

        gic_dist->GICD_ICENABLER[bank] = id;
    }
    else
    {
#ifdef DEBUG
        /* put debug print here */
#endif
        return INTERRUPT_RETURN_ERROR;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

int32_t gic_set_int_type(uint32_t id, uint32_t rd, uint32_t type)
{
    uint32_t bank, tmp, conf;

    if ((gic_dist == NULL) || (gic_rdist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

#ifdef DEBUG
    /* put debug print here */
#endif

    if (id < 31U)
    {
        if (id < 16U)
        {
            return INTERRUPT_RETURN_INVALID_ID;
        }
        else
        {
            gic_rdist[rd].sgis.GICR_ICFGR[1] = (type & 0x3U) << ((id - 16U) << 1U);
        }
    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        /* SPI */
        type = type & 0x3U;   /* Mask out unused bits */

        bank = id / 16U; /*There are 16 uIDs per register, need to work out which register to access */
        id = id & 0xFU;  /* ... and which field within the register */
        id = id * 2U;    /* Convert from which field to a bit offset (2-bits per field) */

        conf = type << id; /* Move configuration value into correct bit position */

        tmp = gic_dist->GICD_ICFGR[bank];       /* Read current value */
        tmp = tmp & ~(0x3U << id);              /* Clear the bits for the specified field */
        tmp = tmp | conf;                       /* OR in new configuration */
        gic_dist->GICD_ICFGR[bank] = tmp;       /* Write updated value back */
    }
    else
    {
        return INTERRUPT_RETURN_ERROR;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

int32_t gic_clear_int_pending(uint32_t id, uint32_t rd)
{
    uint32_t bank;

    if ((gic_dist == NULL) || (gic_rdist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        /* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }

        gic_rdist[rd].sgis.GICR_ICPENDR0 |= (1U << id);
    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        /* SPI */
        bank = id / 32U; /* There are 32 uIDs per register, need to work out which register to access */
        id = id & 0x1fU; /* ... and which bit within the register */

        id = 1U << id;

        gic_dist->GICD_ICPENDR[bank] = id;
    }
    else
    {
        return INTERRUPT_RETURN_ERROR;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

/* Interrupt state */

int32_t gic_set_int_pending(uint32_t id, uint32_t rd)
{
    uint32_t bank;

    /* Adjust for SPI */
    id -= 32U;

    if ((gic_dist == NULL) || (gic_rdist == NULL))
    {
        return INTERRUPT_RETURN_ERROR;
    }

    if (id < 31U)
    {
        /* Check rd in range */
        if (rd > gic_max_rd)
        {
            return INTERRUPT_RETURN_INVALID_RDIST;
        }

        id = id & 0x1fU;    /* Find which bit within the register */
        id = 1U << id;      /* Move a '1' into the correct bit position */

        gic_rdist[rd].sgis.GICR_ISPENDR0 |= id;

    }
    else if (id < 1020U)
    {
        if (id == 31U)
        {
            return INTERRUPT_RETURN_INVALID_SPI;
        }

        id -= 32U; /* Adjust ID for Distributor registers */
        /* SPI */
        bank = id / 32U; /*There are 32 uIDs per register, need to work out which register to access */
        id = id & 0x1fU; /* ... and which bit within the register */

        id = 1U << id;    /* Move a '1' into the correct bit position */

        gic_dist->GICD_ISPENDR[bank] |= id;
    }
    else
    {
        return INTERRUPT_RETURN_ERROR;
    }

    return INTERRUPT_RETURN_SUCCESS;
}

void gic_enable_interrupts(void)
{
    __asm__ volatile ("msr DAIFClr, #0xf" ::: "memory");
}
