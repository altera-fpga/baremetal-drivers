/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gpio.c
 *
 * GPIO source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "socfpga_gpio.h"
#include "socfpga_interrupt.h"
#include "socfpga_gpio_reg.h"
#include "mmio.h"






void gpio_irq_handler(void *data);

/*
 * Check if the pin is configured as gpio in pinmux
 */
bool is_pin_gpio(uint32_t pin)
{
    uint32_t val;
    val = RD_REG32(PINMUX_REG(pin));
    val &= PINMUX_MASK;
    return (val == PINMUX_GPIO);
}

/*
 * Set the bit value in the given gpio block register
 */
void set_gpio_reg_bit(uint32_t reg, uint32_t pin, uint8_t val)
{
    uint32_t reg_val;
    uint32_t base_add = GET_GPIO_BASE_ADDR(pin);
    if (pin >= GPIO_PINS_PER_REG)
    {
        pin -= GPIO_PINS_PER_REG;
    }
    reg_val = RD_REG32(base_add + reg);
    reg_val &= ~(1U << pin);
    reg_val |= ((uint32_t)val << pin);
    WR_REG32(base_add + reg, reg_val);
}

/*
 * Get the bit value in the given gpio block register
 */
uint8_t get_gpio_reg_bit(uint32_t reg, uint8_t pin)
{
    uint32_t val;
    val = RD_REG32(GET_GPIO_BASE_ADDR(pin) + reg);
    if (pin >= GPIO_PINS_PER_REG)
    {
        pin -= GPIO_PINS_PER_REG;
    }
    val = (val >> pin) & 0x01U;
    return ((uint8_t)val);
}

/*
 * set the direction of gpio pin
 */
void gpio_set_direction(gpio_pin_t pin, gpio_dir_t dir)
{
    if (dir == GPIO_DIR_IN)
    {
        set_gpio_reg_bit(GPIO_SWPORTA_DDR, (uint32_t)pin, 0U);
    }
    else
    {
        set_gpio_reg_bit(GPIO_SWPORTA_DDR, (uint32_t)pin, 1U);
    }
}

/*
 * handle the interrupt
 */
void gpio_irq_handler(void *data)
{
    uint8_t gpio_inst = *(uint8_t *)data;
    uint8_t pin_state;
    uint8_t pin_offset;
    uint32_t int_stat;
    uint32_t gpio_base;
    uint8_t pin;
    uint8_t i;

    gpio_base = (gpio_inst == GPIO_INSTANCE1)
            ? GPIO0_BASE_ADDR
            : GPIO1_BASE_ADDR;

    /* get the active interrupts */
    int_stat = RD_REG32(gpio_base + GPIO_INTSTATUS);

    /* clear all the edge interrupts */
    WR_REG32(gpio_base + GPIO_PORTA_EOI, int_stat);

    pin_offset = ((gpio_inst == GPIO_INSTANCE1) ? 0U : GPIO_PINS_PER_REG);

    /* Invoke callback for all active interrupts if it is registered */
    for (i = 0; i < GPIO_PINS_PER_REG; i++)
    {
        if ((int_stat & ((uint32_t)1 << i)) == ((uint32_t)1U << i))
        {
            pin = i + pin_offset;
            if (gpio_descriptors[pin].callback_fn != NULL)
            {
                pin_state = get_gpio_reg_bit(GPIO_SWPORTA_DR, pin);
                gpio_descriptors[pin].callback_fn(pin_state, gpio_descriptors[pin].cb_usercontext);
            }
        }
    }
}

/*
 * set the interrupt configuration
 */
bool gpio_set_interrupt(gpio_pin_t pin, gpio_int_t type)
{
    socfpga_hpu_interrupt_t id;
    uint8_t gpio_inst;
    socfpga_interrupt_err_t int_ret;
    if (pin < GPIO_NPIN_PER_REG)
    {
        id = GPIO0IRQ;
        gpio_inst = 0;
    }
    else
    {
        id = GPIO1IRQ;
        gpio_inst = 1;
    }
    int_ret = interrupt_register_isr(id, gpio_irq_handler, &gpio_inst);
    if (int_ret != ERR_OK)
    {
        return false;
    }

    /* clear the edge interrupt if set already */
    set_gpio_reg_bit(GPIO_PORTA_EOI, (uint32_t)pin, 1U);

    /* Configure the level and polarity and enable the interrupt */
    switch (type)
    {
        case GPIO_INT_NONE:
            set_gpio_reg_bit(GPIO_INTEN, (uint32_t)pin, 0U);
            break;
        case GPIO_INT_RISING:
            set_gpio_reg_bit(GPIO_INTTYPE_LEVEL, (uint32_t)pin, 1U);
            set_gpio_reg_bit(GPIO_INT_POLARITY, (uint32_t)pin, 1U);
            set_gpio_reg_bit(GPIO_INTEN, (uint32_t)pin, 1U);
            break;
        case GPIO_INT_FALLING:
            set_gpio_reg_bit(GPIO_INTTYPE_LEVEL, (uint32_t)pin, 1U);
            set_gpio_reg_bit(GPIO_INT_POLARITY, (uint32_t)pin, 0U);
            set_gpio_reg_bit(GPIO_INTEN, (uint32_t)pin, 1U);
            break;
        case GPIO_INT_LOW:
            set_gpio_reg_bit(GPIO_INTTYPE_LEVEL, (uint32_t)pin, 0U);
            set_gpio_reg_bit(GPIO_INT_POLARITY, (uint32_t)pin, 0U);
            set_gpio_reg_bit(GPIO_INTEN, (uint32_t)pin, 1U);
            break;
        case GPIO_INT_HIGH:
            set_gpio_reg_bit(GPIO_INTTYPE_LEVEL, (uint32_t)pin, 0U);
            set_gpio_reg_bit(GPIO_INT_POLARITY, (uint32_t)pin, 1U);
            set_gpio_reg_bit(GPIO_INTEN, (uint32_t)pin, 1U);
            break;

        default:
            /* do nothing */
            break;
    }
    if (type != GPIO_INT_NONE)
    {
        int_ret = interrupt_enable(id, GIC_INTERRUPT_PRIORITY_GPIO);
        if (int_ret != ERR_OK)
        {
            return false;
        }
    }
    return true;
}

/*
 * get the direction of the gpio pin
 */
uint8_t gpio_get_direction(gpio_pin_t pin)
{
    uint8_t ret_val;
    ret_val = get_gpio_reg_bit(GPIO_SWPORTA_DDR, pin);
    return ret_val;
}

/*
 * get the interrupt configuration of the gpio pin
 */

gpio_int_t gpio_get_interrupt(gpio_pin_t pin)
{
    gpio_int_t ret_val = GPIO_INT_NONE;
    uint8_t res1;
    uint8_t res2;

    /* get the level/edge and polarity */
    res1 = get_gpio_reg_bit(GPIO_INTTYPE_LEVEL, pin);
    res2 = get_gpio_reg_bit(GPIO_INT_POLARITY, pin);
    res1 = (res1 << 1U) | res2;

    switch (res1)
    {
        case 0:
            ret_val = GPIO_INT_LOW;
            break;
        case 1:
            ret_val = GPIO_INT_HIGH;
            break;
        case 2:
            ret_val = GPIO_INT_FALLING;
            break;
        case 3:
            ret_val = GPIO_INT_RISING;
            break;
        default:
            ret_val = GPIO_INT_NONE;
            break;
    }
    res1 = get_gpio_reg_bit(GPIO_INTEN, pin);
    if (res1 == 0U)
    {
        ret_val = GPIO_INT_NONE;
    }
    return ret_val;
}

/*
 * Get the reset instance for the GPIO peripheral
 */
reset_periphrl_t gpio_get_rst_instance(gpio_pin_t pin)
{
    reset_periphrl_t rst_instance = RST_PERIPHERAL_END;
    if (pin <= GPIO0_PIN23)
    {
        rst_instance = RST_GPIO0;
    }
    else if (pin <= GPIO1_PIN23)
    {
        rst_instance = RST_GPIO1;
    }
    else
    {
        rst_instance = RST_GPIO1;
    }
    return rst_instance;
}

/*
 * read the current state of the gpio pin
 */
uint8_t gpio_read_state(gpio_pin_t pin)
{
    uint8_t ret_val;
    ret_val = get_gpio_reg_bit(GPIO_EXT_PORTA, pin);
    return ret_val;
}

/*
 * write the sate of the gpio pin
 */
void gpio_write_state(gpio_pin_t pin, uint8_t state)
{
    set_gpio_reg_bit(GPIO_SWPORTA_DR, (uint32_t)pin, state);
}
