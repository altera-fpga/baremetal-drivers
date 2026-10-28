/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_interrupt.c
 *
 * GIC source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdio.h>

#include "crt0.h"
#include "socfpga_interrupt.h"
#include "socfpga_gic.h"
#include "socfpga_gic_reg.h"
#include "socfpga_gic_reg_plat.h"
#include "../api/uart/uart_api.h"

static uint32_t gic_redis_id;


typedef struct
{
    socfpga_interrupt_callback_t callback;
    void *data;
} interrupt_handler_t;

static interrupt_handler_t interrupt_callbacks[MAX_SPI_HPU_INTERRUPT] =
{
    [0 ... MAX_SPI_HPU_INTERRUPT - 1U] = { gic_default_interrupt_handler, NULL }
};

void gic_default_interrupt_handler(void *data) {
    (void)data;
#ifdef SOCFPGA_DEFAULT_INTERRUPT_SPIN
    while (1 == 1) {
    }
#else
    return;
#endif
}

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
/*
 * Open the CCU coherent-agent-interface (CAIU) address-map window that
 *          routes CPU accesses to the GIC (0x1D000000).
 *
 * On Agilex5 the A55 cluster reaches the GIC through the CCU CAIU. Region 2 of
 * that interface is the GIC window. A normal boot stage (BootROM / ATF BL2
 * init_ncore_ccu) programs it, but a cold OCRAM first-stage image does not, so
 * the window is closed and every GIC access decodes to nothing, taking a
 * synchronous external abort (ESR DFSC=0x10). Program the window here, once,
 * before the first GIC MMIO access. Values are from ATF ncore_ccu.h
 * (DII2_GICREGS). The operation is idempotent.
 */
static void gic_open_ccu_gic_window(void)
{
    volatile uint32_t *amigr = (volatile uint32_t *)(0x1C0003C0UL); /* CAIUAMIGR */
    volatile uint32_t *ar2   = (volatile uint32_t *)(0x1C000420UL); /* region-2 ctrl */
    volatile uint32_t *blr2  = (volatile uint32_t *)(0x1C000424UL); /* region-2 base lo */
    volatile uint32_t *bhr2  = (volatile uint32_t *)(0x1C000428UL); /* region-2 base hi */

    *blr2 = 0x0001D000U;   /* GIC base 0x1D000000 (>> 12) */
    __asm__ volatile ("dsb sy" ::: "memory");
    *bhr2 = 0x00000000U;
    __asm__ volatile ("dsb sy" ::: "memory");
    *ar2  = 0xC0800400U;   /* valid + target DII2 + size */
    __asm__ volatile ("dsb sy" ::: "memory");
    *amigr = (*amigr & ~0x1FU) | 0x3U;   /* enable address-map interface */
    __asm__ volatile ("dsb sy; isb" ::: "memory");
}
#endif

/*
 * Initializes the GIC600 interrupt controller.
 */
void interrupt_init_gic(void)
{
    uint64_t cur_el;
    __asm__ volatile ("mrs %0, CurrentEL" : "=r" (cur_el));

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
    /* Must run before ANY GIC MMIO: open the CCU CAIU->GIC address window,
     * otherwise GIC accesses take a synchronous external abort. */
    gic_open_ccu_gic_window();
#endif

    /* Enable the GICv3 system-register interface (ICC_SRE.SRE) at whatever
     * Exception Level we are running at. */
    if ((cur_el & 0xCU) == 0xCU) {
        /* EL3: ICC_SRE_EL3 */
        __asm__ volatile ("msr S3_6_C12_C12_5, %0" : : "r" (1UL));
    } else if ((cur_el & 0xCU) == 0x8U) {
        /* EL2: ICC_SRE_EL2 */
        __asm__ volatile ("msr S3_4_C12_C9_5, %0" : : "r" (1UL));
    } else {
        /* EL1: ICC_SRE_EL1 */
        __asm__ volatile ("msr S3_0_C12_C12_5, %0" : : "r" (1UL));
    }
    __asm__ volatile ("isb");

    /* Initialize GIC: scan redistributors and (at EL3 only) initialize
     * distributor registers. At EL2/EL1, ATF owns GICD. */
    if (gic_enable_gic() != INTERRUPT_RETURN_SUCCESS) {
        return;
    }

#ifdef BUILD_MODE_OCRAM
    /* SCR_EL3 IRQ/FIQ routing at EL3 only. */
    if ((cur_el & 0xCU) == 0xCU) {
        uint64_t scr;
        __asm__ volatile ("mrs %0, scr_el3" : "=r" (scr));
        scr |= (1UL << 1) | (1UL << 2);
        __asm__ volatile ("msr scr_el3, %0" : : "r" (scr));
        __asm__ volatile ("isb");
    }
#endif

    /* Now configure our local redistributor. */
    gic_redis_id = (uint32_t)gic_get_redist_id((uint32_t)gic_reg_get_cpu_affinity());

    /* Mark this core as being active. */
    if (gic_wakeup_redist(gic_redis_id) != INTERRUPT_RETURN_SUCCESS) {
        return;
    }

    /* Set the priority mask to 0xFF to allow all priorities. */
    gic_reg_set_priority_mask(0xFF);

    /* Enable interrupt groups at the CPU interface. Both groups are enabled so
     * we work at EL3 (Group0/FIQ) and EL2/EL1 (Group1/IRQ). */
    gic_reg_enable_group0_interrupts();
    gic_reg_enable_group1_interrupts();
}

socfpga_interrupt_err_t interrupt_ppi_enable(socfpga_hpu_interrupt_t id,
        socfpga_hpu_interrupt_type_t interrupt_type,
        uint8_t priority, uint32_t gic_redis_id) {
    uint32_t type = GICV3_CONFIG_LEVEL;
    if ((id > PPI_MAX) || (id < PPI_START))
    {
        return ERR_PPI_ID;
    }

    if (interrupt_type == SPI_INTERRUPT_TYPE_EDGE)
    {
        type = GICV3_CONFIG_EDGE;
    }

    if (gic_enable_int((uint32_t)id, gic_redis_id) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_PPI_ID;
    }
    if (gic_set_int_group((uint32_t)id, gic_redis_id,
            GICV3_GROUP1_NON_SECURE) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_PPI_ID;
    }
    if (gic_set_int_type((uint32_t)id, 0U, type) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_PPI_ID;
    }
    if (gic_set_int_priority((uint32_t)id, gic_redis_id, priority) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_PPI_ID;
    }
    return ERR_OK;
}

socfpga_interrupt_err_t interrupt_spi_enable(socfpga_hpu_interrupt_t id,
        socfpga_hpu_interrupt_type_t interrupt_type,
        socfpga_hpu_spi_interrupt_mode_t interrupt_mode,
        uint8_t priority) {
    uint32_t mode = GICV3_ROUTE_MODE_ANY;
    uint32_t type = GICV3_CONFIG_LEVEL;

    if ((id > SOCFPGA_MAX_SPI) || (id < SOCFPGA_SPI_START))
    {
        return ERR_SPI_ID;
    }

    if (interrupt_type == SPI_INTERRUPT_TYPE_EDGE)
    {
        type = GICV3_CONFIG_EDGE;
    }
    if (interrupt_mode == SPI_INTERRUPT_MODE_TARGET)
    {
        mode = GICV3_ROUTE_MODE_COORDINATE;
    }

    if (gic_set_int_priority((uint32_t)id, 0U, priority) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    if (gic_set_int_group((uint32_t)id, 0U, GICV3_GROUP1_NON_SECURE) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    if (gic_set_int_route((uint32_t)id, mode, 0U) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    if (gic_set_int_type((uint32_t)id, 0U, type) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    if (gic_enable_int((uint32_t)id, 0U) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    return ERR_OK;
}

socfpga_interrupt_err_t interrupt_enable(socfpga_hpu_interrupt_t id, uint8_t priority) {

    socfpga_interrupt_err_t error = ERR_OK;
    uint32_t gic_redisributor_id;
    if ((uint32_t)id < 16U)
    {
        gic_redisributor_id = (uint32_t)gic_get_redist_id(
                (uint32_t)gic_reg_get_cpu_affinity());

        if (gic_enable_int((uint32_t)id, gic_redisributor_id) != INTERRUPT_RETURN_SUCCESS)
        {
            return ERR_SGI_ID;
        }
        /* Select the interrupt group based on platform and Exception Level.
         * Agilex5 OCRAM runs at EL3 and uses Group0 (FIQ); under ATF in DDR
         * at EL2/EL1, FIQ is routed to EL3, so use Group1 (IRQ). */
        uint32_t sgi_group;
#if defined(PLAT_AGILEX5)
        uint64_t cur_el;
        __asm__ volatile ("mrs %0, CurrentEL" : "=r" (cur_el));
        sgi_group = ((cur_el & 0xCU) == 0xCU) ? GICV3_GROUP0 : GICV3_GROUP1_NON_SECURE;
#else
        sgi_group = GICV3_GROUP1_NON_SECURE;
#endif
        if (gic_set_int_group((uint32_t)id, gic_redisributor_id, sgi_group)
                != INTERRUPT_RETURN_SUCCESS)
        {
            return ERR_SGI_ID;
        }
        if (gic_set_int_priority((uint32_t)id, gic_redisributor_id, priority) != INTERRUPT_RETURN_SUCCESS)
        {
            return ERR_SGI_ID;
        }
    }
    else if (id < SOCFPGA_SPI_START)
    {
        gic_redisributor_id = (uint32_t)gic_get_redist_id(
                (uint32_t)gic_reg_get_cpu_affinity());
        error = interrupt_ppi_enable(id, SPI_INTERRUPT_TYPE_LEVEL, priority, gic_redisributor_id);
    }
    else
    {
        error = interrupt_spi_enable(id, SPI_INTERRUPT_TYPE_LEVEL, SPI_INTERRUPT_MODE_TARGET,
                priority);
    }

    return error;
}

socfpga_interrupt_err_t interrupt_spi_disable(socfpga_hpu_interrupt_t id) {
    if (gic_disable_int((uint32_t)id, 0) != INTERRUPT_RETURN_SUCCESS)
    {
        return ERR_SPI_ID;
    }
    return ERR_OK;
}

socfpga_interrupt_err_t interrupt_register_isr(socfpga_hpu_interrupt_t id,
        socfpga_interrupt_callback_t callback,
        void *user_data) {
    if (id > MAX_HPU_SPI_INTERRUPT)
    {
        return ERR_SPI_ID;
    }
    if (callback == 0)
    {
        return ERR_INTERRUPT_CALLBACK;
    }
    interrupt_callbacks[id].callback = callback;
    interrupt_callbacks[id].data = user_data;
    return ERR_OK;
}

void interrupt_irq_handler(unsigned int interrupt_id)
{
    /* Clear pending interrupts. */
    gic_redis_id = (uint32_t)gic_get_redist_id(
            (uint32_t)gic_reg_get_cpu_affinity());
    if (gic_clear_int_pending(interrupt_id, gic_redis_id) != INTERRUPT_RETURN_SUCCESS)
    {
        return;
    }

    /*This is the Max ID for PPI and SPI*/
    if (interrupt_id < MAX_SPI_HPU_INTERRUPT)
    {
        interrupt_callbacks[interrupt_id].callback(interrupt_callbacks[
                    interrupt_id].data);
    }
    else if (interrupt_id == 1023U)
    {
        printf("FIQ: Interrupt was spurious\n");
    }
    else
    {
        printf("FIQ: Panic, unexpected INTID\n");
    }

    return;
}

socfpga_interrupt_err_t gic_send_sgi(uint32_t sgi_id, uint8_t target_cpu_mask)
{
    if (sgi_id > 15U)  // SGIs are 0..15
        return ERR_SGI_ID;

    /* Native GICv3 Triggering: detect EL and use correct SGI register */
    uint64_t sgi_val = ((uint64_t)sgi_id << 24) | (target_cpu_mask & 0xFFFFU);
    uint64_t cur_el;
    __asm__ volatile ("mrs %0, CurrentEL" : "=r" (cur_el));
    
    
    if ((cur_el & 0xCU) == 0xCU) {
        /* EL3: use ICC_SGI0R_EL1 (Group0/FIQ) */
        __asm__ volatile ("msr icc_sgi0r_el1, %0" : : "r" (sgi_val));
    } else {
        /* EL2/EL1: use ICC_SGI1R_EL1 (Group1/IRQ) */
        __asm__ volatile ("msr icc_sgi1r_el1, %0" : : "r" (sgi_val));
    }
    __asm__ volatile ("isb" : : : "memory");

    return ERR_OK;
}
