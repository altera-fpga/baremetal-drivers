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

// Copy of the handoff data
uint32_t handoff_array[FSBL_HANDOFF_SIZE] = {0xFFFFFFFF};

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
 *  "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/memorymap_ExportedMemMap.html"
 */

// clang-format off
#define PINMUX_SELECTION_ARRAY_SIZE (48)
#define PINMUX_SELECTION_STRUCT_SIZE (PINMUX_SELECTION_ARRAY_SIZE *2) // The selection array structure contains the offset and pinmux value 

#define PINMUX_IODELAY_ARRAY_SIZE   (48)
#define PINMUX_IODELAY_STRUCT_SIZE  (PINMUX_IODELAY_ARRAY_SIZE * 2) // The io delay array structure contains pinmux offset and pinmux value

#define PINMUX_CTRL_ARRAY_SIZE      (48)
#define PINMUX_CTRL_STRUCT_SIZE     (PINMUX_CTRL_ARRAY_SIZE * 2) // The CTRL array structure contains pinmux offset and pinmux value

#define PINMUX_FPGA_ARRAY_SIZE      (22)
#define PINMUX_FPGA_STRUCT_SIZE     (PINMUX_FPGA_ARRAY_SIZE * 2) // The FPGA strcut contains pinmux offset and pinmux value

#define UART_TX_OFFSET              (2)
#define UART_RX_OFFSET              (3)
#define UART_PINMUX_SEL_VAL         (0x00000005)
#define UART_TX_PINMUX_CTRL_VAL     (0x00000024) // pull up 8mA drive strength, fast slew rate, TTL no hysteresis, Weak Pull up 20kohm
#define UART_RX_PINMUX_CTRL_VAL     (0x00000022) // pull up 4mA drive strength, slow slew rate, TTL no hysteresis, Weak Pull up 20kohm

// PINMUX MASKS
#define PINMUX_SELECT_RSV_MASK      (0xFFFFFFF0)
#define PINMUX_SELECT_SET_MASK      (0x0000000F)

#define PINMUX_DELAY_RSV_MASK       (0xFFFF8080)
#define PINMUX_DELAY_SET_MASK       (0x00007F7F)

#define PINMUX_IOCTRL_RSV_MASK      (0xFFFFFC00)
#define PINMUX_IOCTRL_SET_MASK      (0x000003FF)

#define PINMUX_FPGA_USE_RSV_MASK    (0xFFFFFFFE)
#define PINMUX_FPGA_USE_SET_MASK    (0x00000001)

/*
 * The relationship between each offset and the HPS 1048 PINOUT is as such
 *      IOA01 = pinmux_sel_offset[0] or pin0sel, pinmux_ioctrl_offset[0] or io0ctrl & pinmux_iodelay_offset[0] or io0_delay
 *      IOA02 = pinmux_sel_offset[1] or pin1sel, pinmux_ioctrl_offset[1] or io1ctrl & pinmux_iodelay_offset[1] or io1_delay
 *      ................................................................................
 *      IOB01 = pinmux_sel_offset[24] or pin24sel, pinmux_ioctrl_offset[24] or io24ctrl & pinmux_iodelay_offset[24] or io24_delay
 *      IOB02 = pinmux_sel_offset[25] or pin25sel, pinmux_ioctrl_offset[25] or io25ctrl & pinmux_iodelay_offset[25] or io25_delay
 *
 * All the items for pinmux_fpga_offset should be 0 as this denotes that the pin will be used by HPS
 *
 * For an understanding of pinmux values see "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_Pin_Mux_summary.html"
 * For an understanding of how the pinmux values link to the HPS 1048 PINOUT see the "SM72 Premium DevKit HAS"
 */

// The offsets below will be used in the future in other pinmux related setup components 
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
    0x00000054,
    0x000001c0,
    0x000001c4
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
    0x000000a0,
    0x000000a4,
    0x000000a8,
    0x000000ac,
    0x000000b0,
    0x000000b4,
    0x000000b8,
    0x000000bc
};

#ifdef USE_HARDCODED_DEFAULT
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

/*
 * config_pinmux configures pinmux value to default known values
 * Notes:
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
#endif // USE_HARDCODED_DEFAULT
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
 * pinmux_handoff_config to the values noted in HPS_HANDOFF area
 * Notes:
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 */
bool pinmux_handoff_config(pinmux_update_group_t array_to_update, pinmux_default_cfg_t *pmux_cfg_ptr) {

    // Iterator
    uint32_t i;
    bool ret_val = false;
    if (pmux_cfg_ptr != NULL) {
        switch (array_to_update) {
        case UPDATE_SEL_ARRAY:
            /* Configure the pin selection */
            for (i = 0; i < PINMUX_SELECTION_ARRAY_SIZE; i++) {
                if ((i == UART_TX_OFFSET) || (i == UART_RX_OFFSET)) {
                    // update selection for UART0
                    pmux_cfg_ptr[i].pinmux_value = UART_PINMUX_SEL_VAL;
                }
                mem_quick_write_32(AGX5_PINMUX_PIN0SEL + pinmux_sel_offset[i], pmux_cfg_ptr[i].pinmux_value);
            }
            ret_val = true;
            break;
        case UPDATE_CTRL_ARRAY:
            /* Configure the pin control */
            for (i = 0; i < PINMUX_CTRL_ARRAY_SIZE; i++) {
                if (i == UART_TX_OFFSET) {
                    pmux_cfg_ptr[i].pinmux_value = UART_TX_PINMUX_CTRL_VAL;
                }
                if (i == UART_RX_OFFSET) {
                    pmux_cfg_ptr[i].pinmux_value = UART_RX_PINMUX_CTRL_VAL;
                }
                mem_quick_write_32(AGX5_PINMUX_IO0CTRL + pinmux_ioctrl_offset[i], pmux_cfg_ptr[i].pinmux_value);
            }
            ret_val = true;
            break;
        case UPDATE_FPGA_ARRAY:
            /*
             * Configure the FPGA use.
             * The actual generic handoff contains extra 4 elements, and these 4 elements
             * are not applicable to the Agilex5 platform. Writing these extra 4 elements
             * will cause the system to crash, so let's avoid writing them here.
             */
            for (i = 0; i < PINMUX_FPGA_ARRAY_SIZE; i++) {
                if ((i == UART_TX_OFFSET) || (i == UART_RX_OFFSET)) {
                    // update selection for UART0
                    // Value always 0 for HPS
                    pmux_cfg_ptr[i].pinmux_value = 0;
                }
                mem_quick_write_32(AGX5_PINMUX_EMAC0_USEFPGA + pinmux_fpga_offset[i], pmux_cfg_ptr[i].pinmux_value);
            }
            ret_val = true;
            break;
        case UPDATE_IO_DELAY:
            /* Configure the IO delay */
            for (i = 0; i < PINMUX_IODELAY_ARRAY_SIZE; i++) {
                if ((i == UART_TX_OFFSET) || (i == UART_RX_OFFSET)) {
                    // update selection for UART0
                    // Value 0 for no delay
                    pmux_cfg_ptr[i].pinmux_value = 0;
                }
                mem_quick_write_32(AGX5_PINMUX_IO0_DELAY + pinmux_iodelay_offset[i], pmux_cfg_ptr[i].pinmux_value);
            }
            ret_val = true;
            break;
        default:
            printf("Invalid configuration selection\n");
        }
    }
    return ret_val;
}

/*
 * config_pinmux configures pinmux value to default known values
 * Notes:
 *  The main concern is ensuring that uart0 is selected as output pin for the select array
 */
int32_t config_pinmux_update(pinmux_update_group_t array_to_update, uint32_t *updt_arry) {
    int32_t ret_val = -1;
    uint32_t i = 0;
    uint32_t set_val = 0;
    switch (array_to_update) {
    case UPDATE_SEL_ARRAY:
        /* Configure the pin selection */
        for (i = 0; i < PINMUX_SELECTION_ARRAY_SIZE; i++) {
            set_val = (PINMUX_SELECT_SET_MASK & updt_arry[i]);
            mem_quick_write_32(AGX5_PINMUX_PIN0SEL + pinmux_sel_offset[i], set_val);
        }
        ret_val = 0;
        break;
    case UPDATE_CTRL_ARRAY:
        /* Configure the pin control */
        for (i = 0; i < PINMUX_CTRL_ARRAY_SIZE; i++) {
            set_val = (PINMUX_IOCTRL_SET_MASK & updt_arry[i]);
            mem_quick_write_32(AGX5_PINMUX_IO0CTRL + pinmux_ioctrl_offset[i], set_val);
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
        for (i = 0; i < PINMUX_FPGA_ARRAY_SIZE; i++) {
            set_val = (PINMUX_FPGA_USE_SET_MASK & updt_arry[i]);
            mem_quick_write_32(AGX5_PINMUX_EMAC0_USEFPGA + pinmux_fpga_offset[i], set_val);
        }
        ret_val = 0;
        break;
    case UPDATE_IO_DELAY:
        /* Configure the IO delay */
        for (i = 0; i < PINMUX_IODELAY_ARRAY_SIZE; i++) {
            set_val = (PINMUX_DELAY_SET_MASK & updt_arry[i]);
            mem_quick_write_32(AGX5_PINMUX_IO0_DELAY + pinmux_iodelay_offset[i], set_val);
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
 * config_pinmux_ofst_update configures pinmux value to default known values
 * Notes:
 *  -- The main concern is ensuring that uart0 is selected as output pin for the select array
 *  -- The offset value will utilize pinmux_sel_offset, pinmux_ioctrl_offset, pinmux_ioctrl_offset & pinmux_fpga_offset
 * arrays to pick the correct offset value for the passed value. See
 * "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_Pin_Mux_summary.html" for an
 * understanding of the pinmux offsets for each item.
 *  -- The offset value depends on the item being updated
 *     pinmux selection values update pin0sel - pin47sel
 *     pinmux control array updates io0ctrl - io47ctrl
 *     pinmux fpga array updates pinmux_...._usefpga values
 *     pinmux IO dealy array updates io0_delay - io47_delay values
 *     Again see
 * "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_Pin_Mux_summary.html"  for
 * details of values being set
 */
int32_t config_pinmux_ofst_update(pinmux_update_group_t update_group, uint32_t value, uint32_t offset) {
    int32_t ret_val = -1;
    uint32_t set_val = 0;

    // Update selected pinmux parameter
    switch (update_group) {
    case UPDATE_SEL_ARRAY:
        /* Configure the pin selection */
        if (offset < PINMUX_SELECTION_ARRAY_SIZE) {
            set_val = (PINMUX_SELECT_SET_MASK & value);
            mem_quick_write_32(AGX5_PINMUX_PIN0SEL + pinmux_sel_offset[offset], set_val);
            ret_val = 0;
        } else {
            // Invalid selection array size
            ret_val = -2;
        }
        break;
    case UPDATE_CTRL_ARRAY:
        /* Configure the pin control */
        if (offset < PINMUX_CTRL_ARRAY_SIZE) {
            set_val = (PINMUX_IOCTRL_SET_MASK & value);
            mem_quick_write_32(AGX5_PINMUX_IO0CTRL + pinmux_ioctrl_offset[offset], set_val);
            ret_val = 0;
        } else {
            // Invalid control array offset
            ret_val = -2;
        }
        break;
    case UPDATE_FPGA_ARRAY:
        /*
         * Configure the FPGA use.
         */
        if (offset < PINMUX_FPGA_ARRAY_SIZE) {
            set_val = (PINMUX_FPGA_USE_SET_MASK & value);
            mem_quick_write_32(AGX5_PINMUX_EMAC0_USEFPGA + pinmux_fpga_offset[offset], set_val);
            ret_val = 0;
        } else {

            // Invalid FPGA array offset
            ret_val = -2;
        }
        break;
    case UPDATE_IO_DELAY:
        /* Configure the IO delay */
        if (offset < PINMUX_IODELAY_ARRAY_SIZE) {
            set_val = (PINMUX_DELAY_SET_MASK & value);
            mem_quick_write_32(AGX5_PINMUX_IO0_DELAY + pinmux_iodelay_offset[offset], set_val);
            ret_val = 0;
        } else {
            // Invalid IO delay offset
            ret_val = -2;
        }
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

    // Copy handoff data to temporary array
    uint32_t *temp_hndof_ptr = (uint32_t *)PLAT_HANDOFF_OFFSET;
    for (uint32_t ii = 0; ii < FSBL_HANDOFF_SIZE; ii++) {

        handoff_array[ii] = temp_hndof_ptr[ii];
    }

    // Used to view handoff area elements for pinmux
    fsbl_handoff_t *reverse_handoff_ptr = (fsbl_handoff_t *)handoff_array;

    b32_swap((uint32_t *)&(reverse_handoff_ptr->header_magic));
    for (uint32_t ii = 0; ii < 96; ii++) {
        // SWAP handoff area memory
        b32_swap((uint32_t *)&(reverse_handoff_ptr->pinmux_sel_array[ii]));
        b32_swap((uint32_t *)&(reverse_handoff_ptr->pinmux_io_array[ii]));
        b32_swap((uint32_t *)&(reverse_handoff_ptr->pinmux_iodelay_array[ii]));

        if (ii < 44) {
            b32_swap((uint32_t *)&(reverse_handoff_ptr->pinmux_fpga_array[ii]));
        }
    }

#ifdef USE_HARDCODED_DEFAULT
    // Default pinmux
    config_pinmux();
#else
    // Configure pinmux according to handoff area
    pinmux_handoff_config(UPDATE_SEL_ARRAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_sel_array[0]);
    pinmux_handoff_config(UPDATE_CTRL_ARRAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_io_array[0]);
    pinmux_handoff_config(UPDATE_FPGA_ARRAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_fpga_array[0]);
    pinmux_handoff_config(UPDATE_IO_DELAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_iodelay_array[0]);
#endif
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

#ifdef DEBUG_PINMUX_SETTINGS
    pinmux_default_cfg_t *sel_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_sel_array[0];
    pinmux_default_cfg_t *io_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_io_array[0];
    pinmux_default_cfg_t *io_delay_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_iodelay_array[0];
    pinmux_default_cfg_t *fpga_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_fpga_array[0];
    printf("io selection array values\n\n");
    for (uint32_t ii = 0; ii < PINMUX_SELECTION_ARRAY_SIZE; ii++) {
        // SWAP handoff area memory
        printf("0x%x\n", sel_array[ii].pinmux_value);
    }

    printf("\n\n IO ctrl array values\n\n");
    for (uint32_t ii = 0; ii < PINMUX_CTRL_ARRAY_SIZE; ii++) {
        // SWAP handoff area memory
        printf("0x%x\n", io_array[ii].pinmux_value);
    }

    printf("\n\n IO delay array values\n\n");
    for (uint32_t ii = 0; ii < PINMUX_IODELAY_ARRAY_SIZE; ii++) {
        // SWAP handoff area memory
        printf("0x%x\n", io_delay_array[ii].pinmux_value);
    }

    printf("\n\n IO FPGA use array values\n\n");
    for (uint32_t ii = 0; ii < PINMUX_FPGA_ARRAY_SIZE; ii++) {
        // SWAP handoff area memory
        printf("0x%x\n", fpga_array[ii].pinmux_value);
    }
#endif // DEBUG_PINMUX_SETTINGS

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
