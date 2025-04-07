#ifndef FSBL_BOOT_HELP_H__
#define FSBL_BOOT_HELP_H__

#include "debug.h"
#include "uart.h"
#include "uart_regs.h"
#include <stdbool.h>
#include <stdint.h>

#define PLAT_HANDOFF_OFFSET 0x0007F000

// Byte Swap used by fsbl boot
bool b32_swap(uint32_t *p);
/*
 * This struct is to capture the handoff section located at PLAT_HANDOFF_OFFSET
 * All elements are expected to be of size uint32_t
 */
typedef struct {
    /* header */
    uint32_t header_magic;
    uint32_t header_device;
    uint32_t _pad_0x08_0x10[2];

    /* pinmux configuration - select */
    uint32_t pinmux_sel_magic;
    uint32_t pinmux_sel_length;
    uint32_t _pad_0x18_0x20[2];
    uint32_t pinmux_sel_array[96]; /* offset, value */

    /* pinmux configuration - io control */
    uint32_t pinmux_io_magic;
    uint32_t pinmux_io_length;
    uint32_t _pad_0x1a8_0x1b0[2];
    uint32_t pinmux_io_array[96]; /* offset, value */

    /* pinmux configuration - use fpga switch */
    uint32_t pinmux_fpga_magic;
    uint32_t pinmux_fpga_length;
    uint32_t _pad_0x338_0x340[2];
    uint32_t pinmux_fpga_array[44]; /* offset, value */
    /* TODO: Temp remove due to add in extra handoff data */
    // uint32_t	_pad_0x3e8_0x3f0[2];

    /* pinmux configuration - io delay */
    uint32_t pinmux_delay_magic;
    uint32_t pinmux_delay_length;
    uint32_t _pad_0x3f8_0x400[2];
    uint32_t pinmux_iodelay_array[96]; /* offset, value */
} fsbl_handoff_t;

// Used to hold handoff data
#define FSBL_HANDOFF_SIZE (sizeof(fsbl_handoff_t) / sizeof(uint32_t))
extern uint32_t handoff_array[FSBL_HANDOFF_SIZE];

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
    uint32_t pinmux_value;
} pinmux_default_cfg_t;

/*
 * Default fsbl configuration method
 */
int32_t fsbl_configuration(void);

// The below consts will be used in future pinmux configuration components

int32_t config_pinmux_update(pinmux_update_group_t array_to_update, uint32_t *updt_arry);

/*
 * config_pinmux_ofst_update configures pinmux value to default known values
 * Notes:
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 *  The offset value will utilize pinmux_sel_offset, pinmux_ioctrl_offset, pinmux_ioctrl_offset & pinmux_fpga_offset
 * arrays to pick the correct offset value for the passed value. See
 * "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_Pin_Mux_summary.html" for an
 * understanding of the pinmux offsets for each item.
 */
int32_t config_pinmux_ofst_update(pinmux_update_group_t update_group, uint32_t value, uint32_t offset);
/*
 * pinmux_handoff_config to the values noted in HPS_HANDOFF area
 * Notes:
 * 	This only works at el3.
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 */
bool pinmux_handoff_config(pinmux_update_group_t array_to_update, pinmux_default_cfg_t *pmux_cfg_ptr);

#endif // FSBL_BOOT_HELP_H__
