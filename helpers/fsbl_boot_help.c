#include <fsbl_boot_help.h>
#include <hps_address_map.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

// UART related settings
#define PLAT_BAUDRATE (115200)
#define PLAT_UART_CLOCK (100000000)
#define UART_DLL_VAL (PLAT_UART_CLOCK / (PLAT_BAUDRATE * 16)) & 0xff
#define UART_DLLM_VAL (UART_DLL_VAL << 8) & 0xff
#define UARTLCR_DLAB BIT(0)
#define UARTFCR_FIFOEN (1 << 0) /* Enable the Tx/Rx FIFO */
#define UARTFCR_DMAEN (1 << 3)  /* Enable DMA mode */

// OCRAM essential settings
#define OCRAM_REG0_ACCESS_OFST (0x18)
#define OCRAM_REG0_ACCESS_ADDR (OCRAM_FIREWALL_BASE + OCRAM_REG0_ACCESS_OFST)
#define NON_SECURE_ENABLE (0)

// L4 essential settings
#define SOCFPGA_SDMMC_SECU_BIT_OFST (0x40)
#define SOCFPGA_SDMMC_SECU_BIT_ENABLE (0x1010001)
#define SOCFPGA_SDMMC_SECU_L4PER_ADDR (SOCFPGA_L4_PER_SCR_REG_BASE + SOCFPGA_SDMMC_SECU_BIT_OFST)
#define SOCFPGA_SDMMC_SECU_L4SYS_ADDR (SOCFPGA_L4_SYS_SCR_REG_BASE + SOCFPGA_SDMMC_SECU_BIT_OFST)
#define SOCFPGA_LWSOC2FPGA_ENABLE (0xffe0301)

// This typically is already opened as it's needed for printf
extern int32_t stdout_uart_fd;

/* The const arrays below come from:
 * repo:
 *	applications.fpga.soc.arm-trusted-firmware-dev
 * file:
 * ./plat/intel/soc/agilex5/soc/agilex5_pinmux.c
 * Note:
 *   These const setup all elments of our pinmux array. for details of how what value
 *   means search here
 *"https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/memorymap_ExportedMemMap.html"
 */

// The offsets below will be used in the future in other pinmux related setup components
// clang-format off
/*
 *
 * pinmux Offset values for pinmux selection
 */
static const uint32_t pinmux_sel_offset[] = {
    0x00000000,
    0x00000004, 
    0x00000008, 
    0x0000000c, 
    0x00000010,
    0x00000014, 
    0x00000018, 
    0x0000001c, 
    0x00000020, 
    0x00000024, 
    0x00000028, 
    0x0000002c, 
    0x00000030,
    0x00000034, 
    0x00000038, 
    0x0000003c, 
    0x00000040, 
    0x00000044, 
    0x00000048, 
    0x0000004c, 
    0x00000050, 
    0x00000054, 
    0x00000058, 
    0x0000005c, 
    0x00000060,
    0x00000064, 
    0x00000068,
    0x0000006c,
    0x00000070,
    0x00000074, 
    0x00000078,
    0x0000007c, 
    0x00000080,
    0x00000084, 
    0x00000088, 
    0x0000008c, 
    0x00000090,
    0x00000094, 
    0x00000098, 
    0x0000009c, 
    0x00000100, 
    0x00000104,
    0x00000108,
    0x0000010c,
    0x00000110, 
    0x00000114,
    0x00000118, 
    0x0000011c
};

/*
 *
 * pinmux Offset values for pinmux io control
 */
static const uint32_t pinmux_ioctrl_offset[] = {
    0x00000000,
    0x00000004,
    0x00000008,
    0x0000000c,
    0x00000010,
    0x00000014,
    0x00000018,
    0x0000001c,
    0x00000020,
    0x00000024,
    0x00000028,
    0x0000002c,
    0x00000030,
    0x00000034,
    0x00000038,
    0x0000003c,
    0x00000040,
    0x00000044,
    0x00000048,
    0x0000004c,
    0x00000050,
    0x00000054,
    0x00000058,
    0x0000005c,
    0x00000060,
    0x00000064,
    0x00000068,
    0x0000006c,
    0x000000d0,
    0x000000d4,
    0x000000d8,
    0x000000dc,
    0x000000e0,
    0x000000e4,
    0x000000e8,
    0x000000ec,
    0x000000f0,
    0x000000f4,
    0x000000f8,
    0x000000fc,
    0x00000100,
    0x00000104,
    0x00000108,
    0x0000010c,
    0x00000110,
    0x00000114,
    0x00000118,
    0x0000011c
};

/*
 *
 * pinmux Offset values for pinmux fpga setting parameter
 */
static const uint32_t pinmux_fpga_offset[] = {
    0x00000000,
    0x00000004,
    0x00000008,
    0x0000000c,
    0x00000010,
    0x00000014,
    0x00000018,
    0x0000001c,
    0x00000020,
    0x00000028,
    0x0000002c,
    0x00000030,
    0x00000034,
    0x00000038,
    0x0000003c,
    0x00000040,
    0x00000044,
    0x00000048,
    0x00000050,
    0x00000054
};

/*
 *
 * pinmux Offset values for pinmux io delay 
 */
static const uint32_t pinmux_iodelay_offset[] = {
    0x00000000,
    0x00000004,
    0x00000008,
    0x0000000c,
    0x00000010,
    0x00000014,
    0x00000018,
    0x0000001c,
    0x00000020,
    0x00000024,
    0x00000028,
    0x0000002c,
    0x00000030,
    0x00000034,
    0x00000038,
    0x0000003c,
    0x00000040,
    0x00000044,
    0x00000048,
    0x0000004c,
    0x00000050,
    0x00000054,
    0x00000058,
    0x0000005c,
    0x00000060,
    0x00000064,
    0x00000068,
    0x0000006c,
    0x00000070,
    0x00000074,
    0x00000078,
    0x0000007c,
    0x00000080,
    0x00000084,
    0x00000088,
    0x0000008c,
    0x00000090,
    0x00000094,
    0x00000098,
    0x0000009c,
    0x00000100,
    0x00000104,
    0x00000108,
    0x0000010c,
    0x00000110,
    0x00000114,
    0x00000118,
    0x0000011c
};

// Default pinmux select array "Currently 48 (pinmux_default_cfg_t) elements here"
// Each elemt of this array is structured as such relative to pinmux registers:
//  offset, value
static const pinmux_default_cfg_t sysmgr_pinmux_array_sel[] = {
	{pinmux_sel_offset[0], 0x00000005},
	{pinmux_sel_offset[1], 0x00000005},
	{pinmux_sel_offset[2], 0x00000005},
	{pinmux_sel_offset[3], 0x00000005},
	{pinmux_sel_offset[4], 0x00000000},
	{pinmux_sel_offset[5], 0x00000000},
	{pinmux_sel_offset[6], 0x00000006},
	{pinmux_sel_offset[7], 0x00000005},
	{pinmux_sel_offset[8], 0x00000000},
	{pinmux_sel_offset[9], 0x00000000},
	{pinmux_sel_offset[10], 0x00000009},
	{pinmux_sel_offset[11], 0x00000008},
	{pinmux_sel_offset[12], 0x00000001},
	{pinmux_sel_offset[13], 0x00000001},
	{pinmux_sel_offset[14], 0x00000001},
	{pinmux_sel_offset[15], 0x00000001},
	{pinmux_sel_offset[16], 0x00000001},
	{pinmux_sel_offset[17], 0x00000001},
	{pinmux_sel_offset[18], 0x00000001},
	{pinmux_sel_offset[19], 0x00000001},
	{pinmux_sel_offset[20], 0x00000001},
	{pinmux_sel_offset[21], 0x00000001},
	{pinmux_sel_offset[22], 0x00000001},
	{pinmux_sel_offset[23], 0x00000001},
	{pinmux_sel_offset[24], 0x00000003},
	{pinmux_sel_offset[25], 0x00000003},
	{pinmux_sel_offset[26], 0x00000008},
	{pinmux_sel_offset[27], 0x00000003},
	{pinmux_sel_offset[28], 0x00000003},
	{pinmux_sel_offset[29], 0x00000003},
	{pinmux_sel_offset[30], 0x00000003},
	{pinmux_sel_offset[31], 0x00000007},
	{pinmux_sel_offset[32], 0x00000007},
	{pinmux_sel_offset[33], 0x00000007},
	{pinmux_sel_offset[34], 0x00000007},
	{pinmux_sel_offset[35], 0x00000000},
	{pinmux_sel_offset[36], 0x00000000},
	{pinmux_sel_offset[37], 0x00000000},
	{pinmux_sel_offset[38], 0x00000000},
	{pinmux_sel_offset[39], 0x00000000},
	{pinmux_sel_offset[40], 0x00000000},
	{pinmux_sel_offset[41], 0x00000000},
	{pinmux_sel_offset[42], 0x00000000},
	{pinmux_sel_offset[43], 0x00000000},
	{pinmux_sel_offset[44], 0x00000000},
	{pinmux_sel_offset[45], 0x00000000},
	{pinmux_sel_offset[46], 0x00000000},
	{pinmux_sel_offset[47], 0x00000000}};

   /* default pinmux control array "Currently 48 (pinmux_default_cfg_t) elements here"
  	* Each element of this array is structured as such relative to pinmux registers:
	* offset, value
	*/
static const pinmux_default_cfg_t sysmgr_pinmux_array_ctrl[] = {
	{pinmux_ioctrl_offset[0],	 0x00000023},
	{pinmux_ioctrl_offset[1],	 0x00000023},
	{pinmux_ioctrl_offset[2],	 0x00000024},
	{pinmux_ioctrl_offset[3],	 0x00000022},
	{pinmux_ioctrl_offset[4],	 0x00000022},
	{pinmux_ioctrl_offset[5],	 0x00000022},
	{pinmux_ioctrl_offset[6],	 0x00000022},
	{pinmux_ioctrl_offset[7],	 0x00000024},
	{pinmux_ioctrl_offset[8],	 0x00000024},
	{pinmux_ioctrl_offset[9],	 0x00000022},
	{pinmux_ioctrl_offset[10],	 0x00000022},
	{pinmux_ioctrl_offset[11],	 0x00000023},
	{pinmux_ioctrl_offset[12],	 0x00000022},
	{pinmux_ioctrl_offset[13],	 0x00000022},
	{pinmux_ioctrl_offset[14],	 0x00000022},
	{pinmux_ioctrl_offset[15],	 0x00000022},
	{pinmux_ioctrl_offset[16],	 0x00000022},
	{pinmux_ioctrl_offset[17],	 0x00000022},
	{pinmux_ioctrl_offset[18],	 0x00000022},
	{pinmux_ioctrl_offset[19],	 0x00000022},
	{pinmux_ioctrl_offset[20],	 0x00000022},
	{pinmux_ioctrl_offset[21],	 0x00000022},
	{pinmux_ioctrl_offset[22],	 0x00000022},
	{pinmux_ioctrl_offset[23],	 0x00000022},
	{pinmux_ioctrl_offset[24],	 0x00000022},
	{pinmux_ioctrl_offset[25],	 0x00000022},
	{pinmux_ioctrl_offset[26],	 0x00000022},
	{pinmux_ioctrl_offset[27],	 0x00000022},
	{pinmux_ioctrl_offset[28],	 0x00000022},
	{pinmux_ioctrl_offset[29],	 0x00000022},
	{pinmux_ioctrl_offset[30],	 0x00000022},
	{pinmux_ioctrl_offset[31],	 0x00000022},
	{pinmux_ioctrl_offset[32],	 0x00000022},
	{pinmux_ioctrl_offset[33],	 0x00000022},
	{pinmux_ioctrl_offset[34],	 0x00000023},
	{pinmux_ioctrl_offset[35],	 0x00000022},
	{pinmux_ioctrl_offset[36],	 0x00000022},
	{pinmux_ioctrl_offset[37],	 0x00000022},
	{pinmux_ioctrl_offset[38],	 0x00000022},
	{pinmux_ioctrl_offset[39],	 0x00000022},
	{pinmux_ioctrl_offset[40],	 0x00000022},
	{pinmux_ioctrl_offset[41],	 0x00000022},
	{pinmux_ioctrl_offset[42],	 0x00000022},
	{pinmux_ioctrl_offset[43],	 0x00000022},
	{pinmux_ioctrl_offset[44],	 0x00000022},
	{pinmux_ioctrl_offset[45],	 0x00000022},
	{pinmux_ioctrl_offset[46],	 0x00000022},
	{pinmux_ioctrl_offset[47],	 0x00000022}};

  /* Default pinmux fpag array "Currently 20 (pinmux_default_cfg_t) elements"
   * Each element of this array is structured as such relative to pinmux registers:
   * offset, value
   */
static const pinmux_default_cfg_t sysmgr_pinmux_array_fpga[] = {
	{pinmux_fpga_offset[0],	 	0x00000000},
	{pinmux_fpga_offset[1],	 	0x00000000},
	{pinmux_fpga_offset[2],	 	0x00000000},
	{pinmux_fpga_offset[3],	 	0x00000000},
	{pinmux_fpga_offset[4],	 	0x00000000},
	{pinmux_fpga_offset[5],	 	0x00000000},
	{pinmux_fpga_offset[6],	 	0x00000000},
	{pinmux_fpga_offset[7],	 	0x00000000},
	{pinmux_fpga_offset[8],	 	0x00000000},
	{pinmux_fpga_offset[9],	 	0x00000000},
	{pinmux_fpga_offset[10],	0x00000000},
	{pinmux_fpga_offset[11],	0x00000000},
	{pinmux_fpga_offset[12],	0x00000000},
	{pinmux_fpga_offset[13],	0x00000000},
	{pinmux_fpga_offset[14],	0x00000000},
	{pinmux_fpga_offset[15],	0x00000000},
	{pinmux_fpga_offset[16],	0x00000000},
	{pinmux_fpga_offset[17],	0x00000000},
	{pinmux_fpga_offset[18],	0x00000000},
	{pinmux_fpga_offset[19],	0x00000000}};

// Default io delay array "Currently 48 (pinmux_default_cfg_t) elements"
// Each elemt of this array is structured as such relative to pinmux registers:
//  offset, value
static const pinmux_default_cfg_t sysmgr_pinmux_array_iodelay[] = {
	{pinmux_iodelay_offset[0],	 0x00000000},
	{pinmux_iodelay_offset[1],	 0x00000000},
	{pinmux_iodelay_offset[2],	 0x00000000},
	{pinmux_iodelay_offset[3],	 0x00000000},
	{pinmux_iodelay_offset[4],	 0x00000000},
	{pinmux_iodelay_offset[5],	 0x00000000},
	{pinmux_iodelay_offset[6],	 0x00000000},
	{pinmux_iodelay_offset[7],	 0x00000000},
	{pinmux_iodelay_offset[8],	 0x00000000},
	{pinmux_iodelay_offset[9],	 0x00000000},
	{pinmux_iodelay_offset[10],	 0x00000000},
	{pinmux_iodelay_offset[11],	 0x00000000},
	{pinmux_iodelay_offset[12],	 0x00000000},
	{pinmux_iodelay_offset[13],	 0x00000000},
	{pinmux_iodelay_offset[14],	 0x00000000},
	{pinmux_iodelay_offset[15],	 0x00000000},
	{pinmux_iodelay_offset[16],	 0x00000000},
	{pinmux_iodelay_offset[17],	 0x00000000},
	{pinmux_iodelay_offset[18],	 0x00000000},
	{pinmux_iodelay_offset[19],	 0x00000000},
	{pinmux_iodelay_offset[20],	 0x00000000},
	{pinmux_iodelay_offset[21],	 0x00000000},
	{pinmux_iodelay_offset[22],	 0x00000000},
	{pinmux_iodelay_offset[23],	 0x00000000},
	{pinmux_iodelay_offset[24],	 0x00000000},
	{pinmux_iodelay_offset[25],	 0x00000000},
	{pinmux_iodelay_offset[26],	 0x00000000},
	{pinmux_iodelay_offset[27],	 0x00000000},
	{pinmux_iodelay_offset[28],	 0x00000000},
	{pinmux_iodelay_offset[29],	 0x00000000},
	{pinmux_iodelay_offset[30],	 0x00000000},
	{pinmux_iodelay_offset[31],	 0x00000000},
	{pinmux_iodelay_offset[32],	 0x00000000},
	{pinmux_iodelay_offset[33],	 0x00000000},
	{pinmux_iodelay_offset[34],	 0x00000000},
	{pinmux_iodelay_offset[35],	 0x00000000},
	{pinmux_iodelay_offset[36],	 0x00001D4C},
	{pinmux_iodelay_offset[37],	 0x00000000},
	{pinmux_iodelay_offset[38],	 0x0000004B},
	{pinmux_iodelay_offset[39],	 0x00000000},
	{pinmux_iodelay_offset[40],	 0x00000000},
	{pinmux_iodelay_offset[41],	 0x00000000},
	{pinmux_iodelay_offset[42],	 0x00000000},
	{pinmux_iodelay_offset[43],	 0x00000000},
	{pinmux_iodelay_offset[44],	 0x00000000},
	{pinmux_iodelay_offset[45],	 0x00000000},
	{pinmux_iodelay_offset[46],	 0x00000000},
	{pinmux_iodelay_offset[47],	 0x00000000}};
// clang-format on

// Quick helper method to return value of address
static inline uint32_t mem_quick_read_32(uintptr_t addr) { return *(volatile uint32_t *)addr; }

// Quick helper method to write value to address
static inline void mem_quick_write_32(uintptr_t addr, uint32_t value) { *(volatile uint32_t *)addr = value; }

// Quick helper method to clear specific bits @ address
static inline void mem_quick_clear_32(uintptr_t addr, uint32_t clear) {
    mem_quick_write_32(addr, mem_quick_read_32(addr) & ~clear);
}

/* This quick helper method setsup the UART mimicking the bl2 image
 * deriving repo:
 *    applications.fpga.soc.arm-trusted-firmware-dev
 * file:
 *   16550_conosle.S
 * Note:
 *  This quick helper method setsup the UART mimicking the bl2 image
 */
static int32_t uart_fsbl_init(uint32_t base) {

    // Used to set values for UART components
    uint32_t uart_value = 0;

    // Set data length to 8 bits per char
    uart_value = 3;
    uart_ioctl(base, IOCTL_UART_LINE_CONTROL_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Ensure there are no interrupts allowed
    uart_value = 0;
    uart_ioctl(base, IOCTL_UART_INTERRUPT_ENABLE_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Enable programming of DLL & DLLM
    uart_ioctl(base, IOCTL_UART_LINE_CONTROL_GET, (uintptr_t)&uart_value, sizeof(uint32_t));
    uart_value |= (1UL << 7UL);
    uart_ioctl(base, IOCTL_UART_LINE_CONTROL_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Set the DLL
    uart_value = UART_DLL_VAL;
    uart_ioctl(base, IOCTL_UART_WRITE_REGS, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Set the DLLM
    uart_value = UART_DLLM_VAL;
    uart_ioctl(base, IOCTL_UART_INTERRUPT_ENABLE_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Disble programming of DLL and DLLM
    uart_ioctl(base, IOCTL_UART_LINE_CONTROL_GET, (uintptr_t)&uart_value, sizeof(uint32_t));
    uart_value &= ~(1UL << 7UL);
    uart_ioctl(base, IOCTL_UART_LINE_CONTROL_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Set DTR and RTS
    uart_value = 3;
    uart_ioctl(base, IOCTL_UART_MODEM_CONTROL_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Enable FIFO and DMA
    uart_value = 0;
    uart_ioctl(base, IOCTL_UART_FIFO_ACCESS_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    // Enable RX interrupts
    uart_ioctl(base, IOCTL_UART_INTERRUPT_ENABLE_GET, (uintptr_t)&uart_value, sizeof(uint32_t));
    uart_value |= 1;
    uart_ioctl(base, IOCTL_UART_INTERRUPT_ENABLE_SET, (uintptr_t)&uart_value, sizeof(uint32_t));

    return 0;
}

/*
 * config_pinmux configures pinmux value to default known values
 * Notes:
 * 	This only works at el3.
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 */
static void config_pinmux(void) {

    // Iterator
    uint32_t i;

    /* Configure the pin selection */
    for (i = 0; i < sizeof(sysmgr_pinmux_array_sel) / sizeof(sysmgr_pinmux_array_sel[0]); i++) {
        mem_quick_write_32(AGX5_PINMUX_PIN0SEL + sysmgr_pinmux_array_sel[i].pinmux_reg_ofst,
                           sysmgr_pinmux_array_sel[i].pinmux_value);
    }

    /* Configure the pin control */
    for (i = 0; i < sizeof(sysmgr_pinmux_array_ctrl) / sizeof(sysmgr_pinmux_array_ctrl[0]); i++) {
        mem_quick_write_32(AGX5_PINMUX_IO0CTRL + sysmgr_pinmux_array_ctrl[i].pinmux_reg_ofst,
                           sysmgr_pinmux_array_ctrl[i].pinmux_value);
    }

    /*
     * Configure the FPGA use.
     * The actual generic handoff contains extra 4 elements, and these 4 elements
     * are not applicable to the Agilex5 platform. Writing these extra 4 elements
     * will cause the system to crash, so let's avoid writing them here.
     */
    for (i = 0; i < sizeof(sysmgr_pinmux_array_fpga) / sizeof(sysmgr_pinmux_array_fpga[0]); i++) {
        mem_quick_write_32(AGX5_PINMUX_EMAC0_USEFPGA + sysmgr_pinmux_array_fpga[i].pinmux_reg_ofst,
                           sysmgr_pinmux_array_fpga[i].pinmux_value);
    }

    /* Configure the IO delay */
    for (i = 0; i < sizeof(sysmgr_pinmux_array_iodelay) / sizeof(sysmgr_pinmux_array_iodelay[0]); i++) {
        mem_quick_write_32(AGX5_PINMUX_IO0_DELAY + sysmgr_pinmux_array_iodelay[i].pinmux_reg_ofst,
                           sysmgr_pinmux_array_iodelay[i].pinmux_value);
    }
}

/*
 * config_pinmux configures pinmux value to default known values
 * Notes:
 * 	This only works at el3.
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 */
int32_t config_pinmux_update(pinmux_update_group_t array_to_update, uint32_t *updt_arry) {
    int32_t ret_val = -1;
    uint32_t i = 0;
    uint32_t set_val = 0;
    switch (array_to_update) {
    case UPDATE_SEL_ARRAY:
        /* Configure the pin selection */
        for (i = 0; i < sizeof(sysmgr_pinmux_array_sel) / sizeof(sysmgr_pinmux_array_sel[0]); i++) {
            set_val = mem_quick_read_32(AGX5_PINMUX_PIN0SEL + sysmgr_pinmux_array_sel[i].pinmux_reg_ofst);

            set_val &= 0xFFFFFFF0;
            set_val |= updt_arry[i];
            mem_quick_write_32(AGX5_PINMUX_PIN0SEL + sysmgr_pinmux_array_sel[i].pinmux_reg_ofst, set_val);
        }
        ret_val = 0;
        break;
    case UPDATE_CTRL_ARRAY:
        /* Configure the pin control */
        for (i = 0; i < sizeof(sysmgr_pinmux_array_ctrl) / sizeof(sysmgr_pinmux_array_ctrl[0]); i++) {
            mem_quick_write_32(AGX5_PINMUX_IO0CTRL + sysmgr_pinmux_array_ctrl[i].pinmux_reg_ofst, updt_arry[i]);
        }
        ret_val = 0;
        break;
    case UPDATE_FPGA_ARRAY:
        /*
         * Configure the FPGA use.
         * The actual generic handoff contains extra 4 elements, and these 4 elements
         * are not applicable to the Agilex5 platform. Writing these extra 4 elements
         * will cause the system to crash, so let's avoid writing them here.
         */
        for (i = 0; i < sizeof(sysmgr_pinmux_array_fpga) / sizeof(sysmgr_pinmux_array_fpga[0]); i++) {
            mem_quick_write_32(AGX5_PINMUX_EMAC0_USEFPGA + sysmgr_pinmux_array_fpga[i].pinmux_reg_ofst, updt_arry[i]);
        }
        ret_val = 0;
        break;
    case UPDATE_IO_DELAY:
        /* Configure the IO delay */
        for (i = 0; i < sizeof(sysmgr_pinmux_array_iodelay) / sizeof(sysmgr_pinmux_array_iodelay[0]); i++) {
            mem_quick_write_32(AGX5_PINMUX_IO0_DELAY + sysmgr_pinmux_array_iodelay[i].pinmux_reg_ofst, updt_arry[i]);
        }
        ret_val = 0;
        break;

    default:
        printf("invalid pinmux update\n");
        break;
    }

    return ret_val;
}

/*
 * Default configuration for executing task under FSBL "bl2"
 */
int32_t fsbl_configuration(void) {
    int32_t ret_val = -1;

    // Default pinmux
    config_pinmux();

    // stdout_uart_fd should be equal to our uart0 base address if not something is wrong
    if (stdout_uart_fd == UART0_BASE) {

        // Setup UART elements to print
        uart_fsbl_init((uint32_t)(stdout_uart_fd));

        // successful return
        ret_val = 0;
    } else {

        // Set to open UART0
        const char test_uart[] = "/dev/uart0";
        uint32_t prev_uart_fd_value = stdout_uart_fd;

        // Lets open UART and send a message that things are not as expected
        stdout_uart_fd = uart_open(test_uart, 0);
        if (stdout_uart_fd == UART0_BASE) {
            printf("previous stdout_uart_fd value was %x\n", prev_uart_fd_value);
            ret_val = 0;
        }
    }

    // Set OCRAM to allow secure and non-secure access to its memory
    mem_quick_write_32(OCRAM_REG0_ACCESS_ADDR, NON_SECURE_ENABLE);

    // Allow "PER-master" secure and non secure transactions from (axi_ap, fpga2soc & mpu) to sdmcc
    mem_quick_write_32(SOCFPGA_SDMMC_SECU_L4PER_ADDR, SOCFPGA_SDMMC_SECU_BIT_ENABLE);

    // Allow "PER-master" secure and non secure transactions from (axi_ap, fpga2sco & mpu) to sdmcc_ecc
    mem_quick_write_32(SOCFPGA_SDMMC_SECU_L4SYS_ADDR, SOCFPGA_SDMMC_SECU_BIT_ENABLE);

    /* Allow secure and non secure transactions of:
        sdm_sdmmc to LWSOC2FPGA
        etr to LWSOC2FPGA
        axi_ap to LWSOC2FPGA
        nand to LWSOC2FPGA
        sdmmc to LWSOC2FPGA
        usb1 to LWSOC2FPGA
        usb0 to LWSOC2FPGA
        emac2 to LWSOC2FPGA
        emac1 to LWSOC2FPGA
        emac0 to LWSOC2FPGA
        dmam1 to LWSOC2FPGA
        dmam0 to LWSOC2FPGA
        mpu to LWSOC2FPGA
    */
    mem_quick_write_32(SOCFPGA_L4_LWHPS2FPA_SCR_BASE, SOCFPGA_LWSOC2FPGA_ENABLE);

    return ret_val;
}

#ifdef __cplusplus
}
#endif
