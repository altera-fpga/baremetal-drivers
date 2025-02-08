#ifndef FSBL_BOOT_HELP_H__
#define FSBL_BOOT_HELP_H__

#include "debug.h"
#include "uart.h"
#include "uart_regs.h"
#include <stdbool.h>
#include <stdint.h>

/*
 * This enum is used to update the contents of an array
 */
typedef enum { UPDATE_SEL_ARRAY, UPDATE_CTRL_ARRAY, UPDATE_FPGA_ARRAY, UPDATE_IO_DELAY } pinmux_update_group_t;

/*
 * This structure gives an understanding of the default configuration
 * structures sysmgr_pinmux_array_sel, sysmgr_pinmux_array_ctrl
 * sysmgr_pinmux_array_fpga & sysmgr_pinmux_array_iodelay
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    uint32_t pinmux_reg_ofst;
    const uint32_t pinmux_value;
} pinmux_default_cfg_t;

/*
 * Default fsbl configuration method
 */
int32_t fsbl_configuration(void);

// The below consts will be used in future pinmux configuration components

int32_t config_pinmux_update(pinmux_update_group_t array_to_update, uint32_t *updt_arry);
#endif // FSBL_BOOT_HELP_H__
