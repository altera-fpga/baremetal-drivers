#ifndef GPIO_REGS_H
#define GPIO_REGS_H

#include "device.h"
#include <stdint.h>

#include "system.h"

typedef struct {
    volatile uint32_t gpio_swporta_dr;    /* GPIO_GPIO_SWPORTA_DR */
    volatile uint32_t gpio_swporta_ddr;   /* GPIO_GPIO_SWPORTA_DDR */
    volatile uint32_t _pad_0x8_0x2f[10];  /* *UNDEFINED* */
    volatile uint32_t gpio_inten;         /* GPIO_GPIO_INTEN */
    volatile uint32_t gpio_intmask;       /* GPIO_GPIO_INTMASK */
    volatile uint32_t gpio_inttype_level; /* GPIO_GPIO_INTTYPE_LEVEL */
    volatile uint32_t gpio_int_polarity;  /* GPIO_GPIO_INT_POLARITY */
    volatile uint32_t gpio_intstatus;     /* GPIO_GPIO_INTSTATUS */
    volatile uint32_t gpio_raw_intstatus; /* GPIO_GPIO_RAW_INTSTATUS */
    volatile uint32_t gpio_debounce;      /* GPIO_GPIO_DEBOUNCE */
    volatile uint32_t gpio_porta_eoi;     /* GPIO_GPIO_PORTA_EOI */
    volatile uint32_t gpio_ext_porta;     /* GPIO_GPIO_EXT_PORTA */
    volatile uint32_t _pad_0x54_0x5f[3];  /* *UNDEFINED* */
    volatile uint32_t gpio_ls_sync;       /* GPIO_GPIO_LS_SYNC */
    volatile uint32_t gpio_id_code;       /* GPIO_GPIO_ID_CODE */
    volatile uint32_t _pad_0x68_0x6b;     /* *UNDEFINED* */
    volatile uint32_t gpio_ver_id_code;   /* GPIO_GPIO_VER_ID_CODE */
    volatile uint32_t gpio_config_reg2;   /* GPIO_GPIO_CONFIG_REG2 */
    volatile uint32_t gpio_config_reg1;   /* GPIO_GPIO_CONFIG_REG1 */
    volatile uint32_t _pad_0x78_0x80[2];  /* *UNDEFINED* */
} hps_gpio_regs_t;

#endif // GPIO_REGS_H
