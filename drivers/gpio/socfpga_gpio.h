/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gpio.h
 *
 * GPIO hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_GPIO_H__
#define __SOCFPGA_GPIO_H__

#include "mmio.h"
#include "socfpga_rst_mngr.h"
#include "errno.h"

/* Constants: Instance configuration
 *
 * Pin counts, bank selectors, and base addresses for the two GPIO banks.
 *
 * GPIO_MAX_INSTANCE - Number of pins in the driver pin table.
 * GPIO_PINS_PER_REG - Number of pins in one GPIO bank.
 * GPIO_INSTANCE1    - Bank selector for GPIO bank 0. Its value is 0.
 * GPIO_INSTANCE0    - Bank selector for GPIO bank 1. Its value is 1.
 * GPIO0_BASE_ADDR   - MMIO base address of GPIO bank 0.
 * GPIO1_BASE_ADDR   - MMIO base address of GPIO bank 1.
 */
#define GPIO_MAX_INSTANCE    (48U)      /* Maximum number of GPIO pins supported across all banks. */
#define GPIO_PINS_PER_REG    (24U)      /* Number of individual GPIO pins managed by a single instance block. */
#define GPIO_INSTANCE1       (0U)       /* Identifier for the first GPIO bank. */
#define GPIO_INSTANCE0       (1U)       /* Identifier for the second GPIO bank. */

#define GPIO0_BASE_ADDR      (0x10C03200U) /* Physical MMIO base address for GPIO Bank 0. */
#define GPIO1_BASE_ADDR      (0x10C03300U) /* Physical MMIO base address for GPIO Bank 1. */

/* Macro: GET_GPIO_BASE_ADDR
 * Resolves the physical base address for a specific pin index.
 */
#define GET_GPIO_BASE_ADDR(instance)    (((instance) < 24U) ? GPIO0_BASE_ADDR : GPIO1_BASE_ADDR)

/* Constants: Pin multiplexer
 *
 * Pinmux register address, the GPIO select value, and the field mask.
 *
 * PINMUX_REG  - Address of the pinmux register for pin p. Pins 0 to 39
 *               start at 0x10D13000. Pins 40 and above start at
 *               0x10D13100. Each pin is 4 bytes apart.
 * PINMUX_GPIO - Field value that selects GPIO.
 * PINMUX_MASK - Mask for the pin-function bits. The driver keeps these
 *               bits and compares them with the GPIO value.
 */
#define PINMUX_REG(p) \
    (((p) < 40U) ? \
     (0x10D13000U + (4U * (p))) : \
     (0x10D13100U + (4U * ((p) - 40U)))) 
#define PINMUX_GPIO          (0x08U)       /* Value to assert GPIO ownership in the pinmux register. */
#define PINMUX_MASK          (0x0FU)       /* Bitmask to isolate the pin functionality selection bits. */


/* Type: gpio_callback_t
 *
 * Function signature invoked by the GPIO Interrupt Service Routine (ISR) when 
 * a configured hardware interrupt condition (e.g., rising edge, level high) 
 * is detected on a pin.
 *
 * Parameters:
 *
 * state - The logical state of the pin at the time of the interrupt.
 * param - An opaque user pointer registered alongside the callback.
 */
typedef void (*gpio_callback_t)(uint8_t state, void *param);

/* Enum: gpio_pin_t
 *
 * Maps logical pin identifiers to their specific hardware positions within the 
 * underlying GPIO controllers. Pins 0-23 belong to GPIO0, and pins 24-47 
 * belong to GPIO1.
 */
typedef enum
{
    GPIO0_PIN0 = 0,
    GPIO0_PIN1,
    GPIO0_PIN2,
    GPIO0_PIN3,
    GPIO0_PIN4,
    GPIO0_PIN5,
    GPIO0_PIN6,
    GPIO0_PIN7,
    GPIO0_PIN8,
    GPIO0_PIN9,
    GPIO0_PIN10,
    GPIO0_PIN11,
    GPIO0_PIN12,
    GPIO0_PIN13,
    GPIO0_PIN14,
    GPIO0_PIN15,
    GPIO0_PIN16,
    GPIO0_PIN17,
    GPIO0_PIN18,
    GPIO0_PIN19,
    GPIO0_PIN20,
    GPIO0_PIN21,
    GPIO0_PIN22,
    GPIO0_PIN23,
    
    GPIO1_PIN0 = 24,
    GPIO1_PIN1,
    GPIO1_PIN2,
    GPIO1_PIN3,
    GPIO1_PIN4,
    GPIO1_PIN5,
    GPIO1_PIN6,
    GPIO1_PIN7,
    GPIO1_PIN8,
    GPIO1IN9,
    GPIO1_PIN10,
    GPIO1_PIN11,
    GPIO1_PIN12,
    GPIO1_PIN13,
    GPIO1_PIN14,
    GPIO1_PIN15,
    GPIO1_PIN16,
    GPIO1_PIN17,
    GPIO1_PIN18,
    GPIO1_PIN19,
    GPIO1_PIN20,
    GPIO1_PIN21,
    GPIO1_PIN22,
    GPIO1_PIN23,
    
    GPIO_NUM_PINS,         /* Total number of available GPIO pins. */
    GPIO_NPIN_PER_REG = 24 /* Maximum pins managed per hardware register block. */
} gpio_pin_t;

/* Enum: gpio_dir_t
 *
 * Specifies the electrical data direction of a GPIO pin. This maps directly 
 * to the `gpio_swportA_ddr` hardware register.
 */
typedef enum
{
    GPIO_DIR_IN,  /* Pin is configured as a high-impedance input. */
    GPIO_DIR_OUT  /* Pin is actively driven as an output. */
} gpio_dir_t;

/* Enum: gpio_int_t
 *
 * Defines the trigger condition for hardware-generated interrupts. This maps 
 * to the `inttype_level` and `int_polarity` registers.
 */
typedef enum
{
    GPIO_INT_NONE,    /* Interrupt generation disabled. */
    GPIO_INT_RISING,  /* Triggered by a low-to-high transition (edge-sensitive). */
    GPIO_INT_FALLING, /* Triggered by a high-to-low transition (edge-sensitive). */
    GPIO_INT_LOW,     /* Triggered while the pin is held low (level-sensitive). */
    GPIO_INT_HIGH,    /* Triggered while the pin is held high (level-sensitive). */
} gpio_int_t;

/* Enum: gpio_ioctl_t
 *
 * Control codes used to read or modify the active hardware configuration of 
 * an opened GPIO pin dynamically.
 */
typedef enum
{
    SET_GPIO_DIR,       /* Update the `gpio_swportA_ddr` register (requires <gpio_dir_t>). */
    SET_GPIO_INT,       /* Update the interrupt trigger logic (requires <gpio_int_t>). */
    GET_GPIO_DIRECTION, /* Query the active data direction. */
    GET_GPIO_INT,       /* Query the active interrupt configuration. */
} gpio_ioctl_t;

/* Struct: gpio_descriptor
 *
 * An internal state-tracking structure maintaining the software context, ownership, 
 * and callback bindings for an individual GPIO pin.
 */
struct gpio_descriptor
{
    bool is_open;                /* Tracks if the pin is currently claimed by a driver. */
    gpio_pin_t instance;         /* The logical pin identifier. */
    gpio_callback_t callback_fn; /* The registered ISR handler. */
    void *cb_usercontext;        /* Opaque pointer passed to the ISR handler. */
};

static struct gpio_descriptor gpio_descriptors[GPIO_MAX_INSTANCE];

/* Type: gpio_handle_t
 *
 * An opaque software handle representing an active claim over a GPIO pin. 
 * Required for subsequent dynamic configuration or teardown.
 */
typedef struct gpio_descriptor *gpio_handle_t;


/* Function: is_pin_gpio
 *
 * Interrogates the System Manager's Pin Multiplexer registers to determine 
 * if a specific external pad is currently routed to the GPIO hardware controller.
 *
 * Parameters:
 *
 * pin - The logical pin identifier to check.
 *
 * Returns:
 *
 * true if the pinmux routing connects the pad to the GPIO core; false otherwise.
 */
bool is_pin_gpio(uint32_t pin);

/* Function: gpio_get_rst_instance
 *
 * Maps a logical GPIO pin to its controlling Reset Manager block identifier. 
 * This allows higher-level subsystems to safely assert or release the hardware 
 * reset line for the specific GPIO bank housing the pin.
 *
 * Parameters:
 *
 * pin - The logical pin identifier.
 *
 * Returns:
 *
 * The corresponding peripheral ID mapped by the Reset Manager driver.
 */
reset_periphrl_t gpio_get_rst_instance(gpio_pin_t pin);

/* Function: gpio_get_direction
 *
 * Samples the `gpio_swportA_ddr` register to determine whether a pin is actively 
 * driving the bus or acting as a high-impedance input.
 *
 * Parameters:
 *
 * pin - The logical pin identifier.
 *
 * Returns:
 *
 * The resolved <gpio_dir_t> value (represented as an 8-bit integer).
 */
uint8_t gpio_get_direction(gpio_pin_t pin);

/* Function: gpio_set_direction
 *
 * Configures the `gpio_swportA_ddr` register to set the electrical direction 
 * of the specified pin.
 *
 * Parameters:
 *
 * pin - The logical pin identifier.
 * dir - The desired direction from <gpio_dir_t>.
 */
void gpio_set_direction(gpio_pin_t pin, gpio_dir_t dir);

/* Function: gpio_set_interrupt
 *
 * Configures the hardware interrupt logic for a specific pin. This safely 
 * performs the read-modify-write sequences across the `inttype_level`, 
 * `int_polarity`, and `inten` registers to program the hardware trigger.
 *
 * Parameters:
 *
 * pin  - The logical pin identifier.
 * type - The hardware trigger condition from <gpio_int_t>.
 *
 * Returns:
 *
 * true on success; false if the pin does not support interrupts or the type is invalid.
 */
bool gpio_set_interrupt(gpio_pin_t pin, gpio_int_t type);

/* Function: gpio_get_interrupt
 *
 * Resolves the active hardware interrupt configuration by reverse-engineering 
 * the values currently residing in the `inttype_level` and `int_polarity` registers.
 *
 * Parameters:
 *
 * pin - The logical pin identifier.
 *
 * Returns:
 *
 * The corresponding <gpio_int_t> enumeration.
 */
gpio_int_t gpio_get_interrupt(gpio_pin_t pin);

/* Function: gpio_read_state
 *
 * Performs a direct read of the `ext_porta` register. This bypasses the data 
 * direction register to sample the true electrical state currently present on 
 * the physical pad, regardless of whether it is configured as an input or output.
 *
 * Parameters:
 *
 * pin - The logical pin identifier.
 *
 * Returns:
 *
 * 1 if the pad is driven high; 0 if the pad is driven low.
 */
uint8_t gpio_read_state(gpio_pin_t pin);

/* Function: gpio_write_state
 *
 * Sets or clears the corresponding bit in the `gpio_swportA_dr` register. If 
 * the pin is configured as an output, this immediately drives the physical pad 
 * to the requested electrical state.
 *
 * Parameters:
 *
 * pin   - The logical pin identifier.
 * state - 1 to drive the pad high; 0 to drive the pad low.
 */
void gpio_write_state(gpio_pin_t pin, uint8_t state);

#endif /* __SOCFPGA_GPIO_H__ */
