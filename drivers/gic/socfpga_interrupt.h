/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_interrupt.h
 *
 * GIC hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_INTERRUPT_H__
#define __SOCFPGA_INTERRUPT_H__

#include <stdint.h>
#include "socfpga_interrupt_priority.h"

/* Constant: interrupt_min_interrupt_priority
 * Defines the minimum allowed software-defined priority level for interrupts 
 * within the SoC FPGA environment.
 */
#define interrupt_min_interrupt_priority    14 

/* Constant: MAX_SPI_HPU_INTERRUPT
 * The upper boundary of the SPI (Shared Peripheral Interrupt) identifier range 
 * supported by the hardware.
 */
#define MAX_SPI_HPU_INTERRUPT    274U 

/* Constant: SOCFPGA_DEFAULT_INTERRUPT_SPIN
 * Selects the driver's default wait behavior for interrupt handling. When 
 * defined, the driver uses a busy-wait (spin) loop while servicing or polling 
 * interrupt state instead of yielding or sleeping.
 */
#define SOCFPGA_DEFAULT_INTERRUPT_SPIN

/* Constant: SOCFPGA_PPI_START
 * The first valid INTID of the Private Peripheral Interrupt (PPI) range. PPIs 
 * are per-core interrupts delivered through the Redistributor.
 */
#define SOCFPGA_PPI_START    22

/* Constant: SOCFPGA_MAX_PPI
 * The last valid INTID of the Private Peripheral Interrupt (PPI) range, marking 
 * the inclusive upper bound used for PPI ID validation.
 */
#define SOCFPGA_MAX_PPI      30

/* Constant: SOCFPGA_SPI_START
 * The first valid INTID of the Shared Peripheral Interrupt (SPI) range. Aliases 
 * <SDM_APS_MAILBOX_INTR>, the lowest SPI routed to the GIC Distributor.
 */
#define SOCFPGA_SPI_START    SDM_APS_MAILBOX_INTR

/* Constant: SOCFPGA_MAX_SPI
 * The last valid INTID of the Shared Peripheral Interrupt (SPI) range. Aliases 
 * <MAX_HPU_SPI_INTERRUPT>, the inclusive upper bound used for SPI ID validation.
 */
#define SOCFPGA_MAX_SPI      MAX_HPU_SPI_INTERRUPT


/* Enum: socfpga_hpu_interrupt_t
 *
 * A comprehensive map of hardware interrupt identifiers (INTIDs) for the 
 * SoCFPGA SoC. These values represent the physical signals from IP blocks 
 * (SDM, EMAC, DMA, etc.) that are routed to the GIC distributor.
 */
typedef enum {
    /* System PPIs */
    PPI_START = 22,         /* Start of Private Peripheral Interface (PPI) range */
    EL1PHY_TMR_INTR = 30,   /* EL1 Physical Timer Interrupt */
    PPI_MAX = 30,           /* End of PPI range */

    /* SDM Block interrupts */
    SDM_APS_MAILBOX_INTR = 32,
    SDM_I2C_INTR0,
    SDM_I2C_INTR1,
    SDM_QSPI_INTR,
    SDM_PWR_ALERT_INTR = 38,
    SDM_HPS_SPARE_INTR0,
    SDM_HPS_SPARE_INTR1,
    SDM_HPS_SPARE_INTR2,

    /* Secure manager block interrupts */
    SECMGR_TRIPLE_REDUN_ERROR = 46,
    SERR_GLOBAL,

    /* CCU block interrupts */
    INTERRUPT_CCU,

    /* FPGA to HPS Interrupts (SPIs 48-111) */
    FPGA2HPS_INTERRUPT0 = 48,
    /* ... (entries 1-62 omitted for brevity) ... */
    FPGA2HPS_INTERRUPT63 = 111,

    /* DMA0 interrupts */
    DMA_IRQ0 = 112,
    DMA_IRQ1,
    DMA_IRQ2,
    DMA_IRQ3,
    DMA0COMMON_IRQ,
    DMA0COMBINED_IRQ,

    /* USB interrupts */
    USB_HOST_SYSTEM_ERR_IRQ = 124,
    USB0IRQ,
    USB1IRQ,

    /* MPFE interrupt */
    IO96B0_DBE_IRQ,

    /* SDMMC/NAND interrupts */
    SDMMC_IRQ,
    NAND_IRQ,
    NAND_SYS_WAKE_IRQ,

    /* SPI interrupts */
    SPI0IRQ,
    SPI1IRQ,
    SPI2IRQ,
    SPI3IRQ,

    /* I2C interrupts */
    I2C0IRQ,
    I2C1IRQ,
    I2C2IRQ,
    I2C3IRQ,
    I2C4IRQ,

    /* UART interrupts */
    UART0IRQ,
    UART1IRQ,

    /* GPIO interrupts */
    GPIO0IRQ,
    GPIO1IRQ,

    /* Timer interrupts */
    TIMER_L4SP0IRQ = 145,
    TIMER_L4SP1IRQ,
    TIMER_OSC10IRQ,
    TIMER_OSC11IRQ,

    /* Watchdog 0/1 interrupts */
    WDOG0IRQ,
    WDOG1IRQ,

    /* Clock manager interrupt */
    CLKMGR_IRQ,

    /* MPFE block interrupt */
    IO96B1DBE_IRQ,

    /* Watchdog 2/3 interrupts */
    WDOG2IRQ = 157,
    WDOG3IRQ,

    /* SMMU/TCU interrupts */
    SYS_TCU_GLOBAL_IRPT_S = 160,
    /* ... (entries omitted for brevity) ... */
    F2SDRAM_TBU_PMU_IRPT = 194,

    /* MPU block interrupt */
    ETR_BUFINTR = 195,

    /* I3C interrupts */
    I3C0IRQ,
    I3C1IRQ,

    /* DMA1 interrupts */
    DMA1IRQ0,
    DMA1IRQ1,
    DMA1IRQ2,
    DMA1IRQ3,
    DMA1COMMON_IRQ,
    DMA1COMBINED_IRQ,

    /* Watchdog 4 interrupt */
    WDOG4IRQ = 207,

    /* MPU block/PMU interrupts */
    NCLUSTERPMUIRQ = 208,
    /* ... (entries omitted for brevity) ... */

    /* EMAC block interrupts */
    EMAC0IRQ = 222,
    /* ... (entries omitted for brevity) ... */
    EMAC2RX_IRQ7 = 273,

    /* ECC block interrupt */
    ECC_DERR_INTR_N,

    MAX_HPU_SPI_INTERRUPT 
} socfpga_hpu_interrupt_t;

/* Type: socfpga_interrupt_callback_t
 *
 * Function signature for user-defined ISR handlers registered through the driver.
 *
 * Parameters:
 *
 * data - An opaque pointer provided by the user during registration, passed 
 * directly to the callback when the interrupt fires.
 */
typedef void (*socfpga_interrupt_callback_t)(void *data);

/* Enum: socfpga_hpu_interrupt_type_t
 *
 * Specifies the hardware trigger sensitivity for a peripheral interrupt.
 */
typedef enum {
    SPI_INTERRUPT_TYPE_LEVEL = 0, /* Level-sensitive trigger */
    SPI_INTERRUPT_TYPE_EDGE = 2   /* Edge-triggered (rising/falling) */
} socfpga_hpu_interrupt_type_t;

/* Enum: socfpga_hpu_spi_interrupt_mode_t
 *
 * Defines the routing behavior for SPIs (Shared Peripheral Interrupts).
 */
typedef enum {
    SPI_INTERRUPT_MODE_ANY = 0,    /* Allow GIC to distribute interrupt to any target CPU */
    SPI_INTERRUPT_MODE_TARGET = 2  /* Target a specific CPU core via affinity routing */
} socfpga_hpu_spi_interrupt_mode_t;

/* Enum: socfpga_interrupt_err_t
 *
 * Standard status codes returned by GIC management functions to indicate 
 * configuration or registration errors.
 */
typedef enum {
    ERR_OK = 0,                /* Operation completed successfully */
    ERR_SPI_ID,                /* Provided SPI ID is out of hardware bounds */
    ERR_SPI_TYPE,              /* Unsupported trigger type requested */
    ERR_SPI_MODE,              /* Unsupported routing mode requested */
    ERR_SPI_TARGET,            /* Invalid CPU affinity target */
    ERR_INTERRUPT_CALLBACK,    /* Provided callback function is NULL */
    ERR_PPI_ID,                /* Provided PPI ID is out of hardware bounds */
    ERR_SGI_ID                 /* Provided SGI ID is invalid */
} socfpga_interrupt_err_t;


/* Function: interrupt_init_gic
 *
 * Performs hardware-level initialization of the GIC Distributor and Redistributor 
 * logic. This includes enabling Group 0 and Group 1 interrupt delivery and 
 * configuring global interrupt security settings.
 */
void interrupt_init_gic(void);

/* Function: gic_default_interrupt_handler
 *
 * The fallback ISR triggered for unexpected or unhandled interrupts. This 
 * usually halts the system or logs a fatal error depending on the debug level.
 *
 * Parameters:
 *
 * data - Pointer to context-specific information or NULL.
 */
void gic_default_interrupt_handler(void *data);

/* Function: interrupt_spi_enable
 *
 * Configures and unmasks a Shared Peripheral Interrupt (SPI).
 *
 * Parameters:
 *
 * id             - Hardware interrupt ID (<socfpga_hpu_interrupt_t>).
 * interrupt_type - Sensitivity trigger (<socfpga_hpu_interrupt_type_t>).
 * interrupt_mode - Routing policy (<socfpga_hpu_spi_interrupt_mode_t>).
 * priority       - 8-bit priority level (0 = highest).
 *
 * Returns:
 *
 * <ERR_OK> on success; <ERR_SPI_ID> if the ID is outside the valid range.
 */
socfpga_interrupt_err_t interrupt_spi_enable(socfpga_hpu_interrupt_t id,
        socfpga_hpu_interrupt_type_t interrupt_type,
        socfpga_hpu_spi_interrupt_mode_t interrupt_mode, uint8_t priority);

/* Function: interrupt_spi_disable
 *
 * Disables a previously enabled SPI, preventing it from being forwarded to the 
 * CPU interface.
 *
 * Parameters:
 *
 * id - Hardware interrupt ID.
 *
 * Returns:
 *
 * <ERR_OK> on success; <ERR_SPI_ID> if the ID is invalid.
 */
socfpga_interrupt_err_t interrupt_spi_disable(socfpga_hpu_interrupt_t id);

/* Function: interrupt_register_isr
 *
 * Binds a specific user-supplied callback function to a hardware interrupt ID.
 *
 * Parameters:
 *
 * id        - Hardware interrupt ID.
 * callback  - The ISR function pointer.
 * user_data - Opaque data passed back to the callback during invocation.
 *
 * Returns:
 *
 * <ERR_OK> on success; <ERR_INTERRUPT_CALLBACK> if the function pointer is NULL.
 */
socfpga_interrupt_err_t interrupt_register_isr(socfpga_hpu_interrupt_t id,
        socfpga_interrupt_callback_t callback, void *user_data);

/* Function: interrupt_ppi_enable
 *
 * Configures and unmasks a Private Peripheral Interrupt (PPI).
 *
 * Parameters:
 *
 * id             - Hardware interrupt ID.
 * interrupt_type - Sensitivity trigger.
 * priority       - 8-bit priority level.
 * gic_redis_id   - The logical Redistributor ID associated with the target core.
 *
 * Returns:
 *
 * <ERR_OK> on success; <ERR_PPI_ID> if the ID is out of range.
 */
socfpga_interrupt_err_t interrupt_ppi_enable(socfpga_hpu_interrupt_t id,
        socfpga_hpu_interrupt_type_t interrupt_type, uint8_t priority,
        uint32_t gic_redis_id);

/* Function: interrupt_enable
 *
 * A generalized helper to enable any GIC interrupt by its ID.
 *
 * Parameters:
 *
 * id       - Hardware interrupt ID.
 * priority - 8-bit priority level.
 *
 * Returns:
 *
 * <ERR_OK> on success; <ERR_SPI_ID> or <ERR_PPI_ID> on failure.
 */
socfpga_interrupt_err_t interrupt_enable(socfpga_hpu_interrupt_t id,
        uint8_t priority);

/* Function: gic_send_sgi
 *
 * Triggers a Software Generated Interrupt (SGI) to inter-processor communication.
 *
 * Parameters:
 *
 * sgi_id          - The SGI identifier (0-15).
 * target_cpu_mask - A bitmask targeting specific CPU cores.
 *
 * Returns:
 *
 * <ERR_OK> on success.
 */
socfpga_interrupt_err_t gic_send_sgi(uint32_t sgi_id, uint8_t target_cpu_mask);

#endif /* __SOCFPGA_INTERRUPT_H__ */