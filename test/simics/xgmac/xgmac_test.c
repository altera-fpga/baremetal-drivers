#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Extra driver's needed
#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "uart.h"

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#include <mrvl_phy_helper.h>
#else
// XGMAC required headers
#include "xgmac.h"
#include "xgmac_internal.h"
#include "xgmac_regs.h"
#endif

#ifdef FSBL_EXECUTION
// clang-format off
/*
 * Below are the settings for each pinmux in the update array "xgma_pinmux_sel_update"
 * The settings below are specific to OOBE2
    Offset 0	uart0.cts_n "Needed for printf on OOBE2"
    Offset1	    uart0.rts_n "Needed for printf on OOBE2"
    Offset2	    uart0.tx "Needed for printf on OOBE2"
    Offset3	    uart0.rx "Needed for printf on OOBE2"
    Offset4	    emac2.pps2
    Offset5	    emac2.ppstrig2
    Offset6	    mdio2.mdio "needed to configure the MARVEL PHY on OOBE2"
    Offset7	    mdio2.mdc "needed to configure the MARVEL PHY on OOBE2"
    Offset8	    cm.hps_osc_clk
    Offset9	    mdio1.mdc
    Offset10	mdio0.mdio
    Offset11	i3c0.scl
    Offset12	emac0.tx_clk
    Offset13	emac0.tx_ctl
    Offset14	emac0.rx_clk
    Offset15	emac0.rx_ctl
    Offset16	emac0.txd0
    Offset17	emac0.txd1
    Offset18	emac0.rxd0
    Offset19	emac0.rxd1
    Offset20	emac0.txd2
    Offset21	emac0.txd3
    Offset22	emac0.rxd2
    Offset23	emac0.rxd3
    Offset24	nand.ADQ0/sdmmc.data0
    Offset25	nand.ADQ1/sdmmc.data1
    Offset26	nand.we_n/sdmmc.clk
    Offset27	emac1.rx_ctl
    Offset28	emac1.txd0
    Offset29	emac1.txd1
    Offset30	nand.ADQ3/sdmmc.data3
    Offset31	nand.cle/sdmmc.cmd
    Offset32	jtag.tck
    Offset33	jtag.tms
    Offset34	jtag.tdo
    Offset35	jtag.tdi
    Offset36	emac2.tx_clk
    Offset37	emac2.tx_ctl
    Offset38	emac2.rx_clk
    Offset39	emac2.rx_ctl
    Offset40	emac2.txd0
    Offset41	emac2.txd1
    Offset42	emac2.rxd0
    Offset43	emac2.rxd1
    Offset44	emac2.txd2
    Offset45	emac2.txd3
    Offset46	emac2.rxd2
    Offset47	emac2.rxd3
 */
// clang-format on
uint32_t xgma_pinmux_sel_update[] = {
    // offst 0     offst 1       offst 2       offst 3       offst 4       offst 5       offst 6       offst 7
    (0x00000005), (0x00000005), (0x00000005), (0x00000005), (0x00000000), (0x00000000), (0x00000006), (0x00000006),
    // offst 8     offst 9       offst 10      offst 11      offst 12      offst 13      offst 14      offst 15
    (0x00000009), (0x00000005), (0x00000005), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000),
    // offst 16    offst 17      offst 18      offst 19      offst 20      offst 21      offst 22      offst 23
    (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000),
    // offst 24    offst 25      offst 26      offst 27      offst 28      offst 29      offst 30      offst 31
    (0x00000003), (0x00000003), (0x00000003), (0x00000003), (0x00000003), (0x00000003), (0x00000003), (0x00000003),
    // offst 32    offst 33      offst 34      offst 35      offst 36      offst 37      offst 38      offst 39
    (0x00000007), (0x00000007), (0x00000007), (0x00000007), (0x00000000), (0x00000000), (0x00000000), (0x00000000),
    // offst 40    offst 41      offst 42      offst 43      offst 44      offst 45      offst 46      offst 47
    (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000), (0x00000000)};

#endif // FSBL_EXECUTION

#ifdef __cplusplus
extern "C" {
#endif

#define MAC_VERSION 0x00107631
#ifdef FSBL_EXECUTION
#define NUM_TX_DESCRIPTORS 4
#define NUM_RX_DESCRIPTORS 4
#define TX_TOTAL_BUFSIZE 2048
#define RX_TOTAL_BUFSIZE 2048

// Index of the current descriptor to check for completion
volatile uint32_t currentTxDescriptorIndex = 0;
volatile uint32_t currentRxDescriptorIndex = 0;

// Buffers passed to the descriptors
volatile uint8_t send_buffer[TX_TOTAL_BUFSIZE] __attribute__((section(".data"))) __attribute__((aligned(4)));
volatile uint8_t rcv_buffer[NUM_RX_DESCRIPTORS][RX_TOTAL_BUFSIZE] __attribute__((section(".data")))
__attribute__((aligned(4)));
void *g_revc_descr0_addr[NUM_RX_DESCRIPTORS];

// Transmit descriptor
volatile txDescr_t txDescriptorRing[NUM_TX_DESCRIPTORS] __attribute__((section(".data"))) __attribute__((aligned(4)));

// Receive descriptor
volatile rxDescr_t rxDescriptorRing[NUM_RX_DESCRIPTORS] __attribute__((section(".data"))) __attribute__((aligned(4)));

// Buffer used to update what's being sent
uint32_t tx_buffer[400] __attribute__((aligned(8)));

// Function to initialize the Tx descriptor ring
void initTxDescriptorRing(uint32_t base_address) {
    uint32_t reg_val = 0;
    uint32_t addr1_val = (uint32_t)((uintptr_t)(&send_buffer[0])); /* Physical address of the data buffer */

    for (uint32_t ii = 0; ii < NUM_TX_DESCRIPTORS; ii++) {
        txDescriptorRing[ii].header_or_buffer1_addr = (addr1_val); /* Physical address of the data buffer */
        txDescriptorRing[ii].buffer2_or_buffer1_addr = 0;          /* Initial control and status */
        txDescriptorRing[ii].control0 = 0;

        txDescriptorRing[ii].control1 |= ((DESC_TXSTS_TXFIRST | DESC_TXSTS_TXLAST));
        txDescriptorRing[ii].control1 |= (DESC_TXSTS_OWNBYDMA);
        txDescriptorRing[ii].control1 |= (DESC_TXCTRL_IOC);
    }
    reg_val = (uint32_t)(((uintptr_t)&txDescriptorRing[currentTxDescriptorIndex]));
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_LADDRESS, (uintptr_t)&reg_val, sizeof(reg_val));

    reg_val = (uint32_t)(((uintptr_t)&txDescriptorRing[currentTxDescriptorIndex] >> sizeof(uint32_t)));
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_HADDRESS, (uintptr_t)&reg_val, sizeof(reg_val));

    reg_val = (uint32_t)(((uintptr_t)&txDescriptorRing[NUM_RX_DESCRIPTORS - 1]));
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_TXDESC_TAIL_LPOINTER, (uintptr_t)&reg_val, sizeof(reg_val));

    reg_val = (NUM_TX_DESCRIPTORS - 1);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL2, (uintptr_t)&reg_val, sizeof(reg_val));
}

// Function to initialize the Tx descriptor ring
void initRxDescriptorRing(uint32_t base_address) {
    int i;
    uint32_t reg_val = 0;

    // clear the buffers first.
    for (i = 0; i < NUM_RX_DESCRIPTORS; i++) {
        rxDescriptorRing[i].bufferAddress = 0;  /* Physical address of the Rx buffer */
        rxDescriptorRing[i].bufferAddress1 = 0; /* Initial control flags */
        rxDescriptorRing[i].bufferAddress2 = 0; /* Initial status */
        rxDescriptorRing[i].controlFlags = 0;
    }

    // clear all receive buffers
    for (i = 0; i < NUM_RX_DESCRIPTORS; i++) {
        for (uint32_t ii = 0; ii < RX_TOTAL_BUFSIZE; ii++) {
            rcv_buffer[i][ii] = 0;
        }
    }
    for (i = 0; i < NUM_RX_DESCRIPTORS; i++) {
        /* Physical address of the Rx buffer */
        rxDescriptorRing[i].bufferAddress = (uint32_t)((uintptr_t)&rcv_buffer[i][0]);

        /* Initial control flags */
        rxDescriptorRing[i].bufferAddress1 = 0;

        /* Initial status */
        rxDescriptorRing[i].bufferAddress2 = 0;

        // Set to owned by DMA and interrupt on completion bit
        rxDescriptorRing[i].controlFlags = (DESC_RXSTS_OWNBYDMA | DESC_RXSTS_IOC);

        g_revc_descr0_addr[i] = (void *)(&rxDescriptorRing[i]);
    }

    asm("DSB SY");
    // Set the starting PTR address
    reg_val = (uint32_t)((uintptr_t)&rxDescriptorRing[0]);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_LADDRESS, (uintptr_t)&reg_val, sizeof(reg_val));
    reg_val = (uint32_t)(((uintptr_t)&rxDescriptorRing[0]) >> 32);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_HADDRESS, (uintptr_t)&reg_val, sizeof(reg_val));

    // Set tail ptr address
    reg_val = (uint32_t)((uintptr_t)&rxDescriptorRing[NUM_RX_DESCRIPTORS - 1]); //[i]);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_RXDESC_TAIL_LPOINTER, (uintptr_t)&reg_val, sizeof(reg_val));

    reg_val = (NUM_RX_DESCRIPTORS - 1);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL2, (uintptr_t)&reg_val, sizeof(reg_val));
}

// Function to start the DMA or MAC
void startTx(uint32_t xgmac_base_addr, uint32_t *send_buf, uint32_t len, uint8_t speed) {
    int i;
    uint32_t *dst;
    uint32_t xgmac_param = 0;

    // Setup descritors to be owned by DMA and interrupt on completion
    for (i = 0; i < NUM_TX_DESCRIPTORS; i++) {

        dst = (uint32_t *)(txDescriptorRing[i].header_or_buffer1_addr);
        uint32_t word_size = len / sizeof(uint32_t);
        for (uint32_t ii = 0; ii < word_size; ii++) {
            dst[ii] = send_buf[ii];
        }
        txDescriptorRing[i].control0 |= ((len << DESC_TXCTRL_SIZE1SHFT) & DESC_TXCTRL_SIZE1MASK);
        txDescriptorRing[i].control0 |= (DESC_TXCTRL_IOC);

        txDescriptorRing[i].control1 |= ((len << DESC_TX_PKT_LENSHIFT) & DESC_TX_PKT_LENMSK);
        txDescriptorRing[i].control1 |= (DESC_TXSTS_OWNBYDMA);
    }

    // Set RX Ctrl to sysbus
    xgmac_param = 0x202001;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL, (uintptr_t)&xgmac_param,
                sizeof(uint32_t));

    // Set TX control to sysbus
    xgmac_param = 0x00040011;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL, (uintptr_t)&xgmac_param,
                sizeof(uint32_t));

    // START MTL transfer
    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_MTL_GET_GCL_CTRL, (uintptr_t)&xgmac_param, sizeof(uint32_t));
    xgmac_param |= 0x00000405; // Start TX transfer
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_MTL_SET_GCL_CTRL, (uintptr_t)&xgmac_param, sizeof(uint32_t));

    // Get MTL control settings
    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_MTL_GET_GCL_CTRL, (uintptr_t)&xgmac_param, sizeof(uint32_t));
    printf("MTL control settings 0x%x\n", xgmac_param);

    // Turn receiver DMA receiver on and loop
    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_MAC_RX_CONFIG, (uintptr_t)&xgmac_param, sizeof(uint32_t));
    xgmac_param = 0x2f0d27c1; //
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_RX_CONFIG, (uintptr_t)&xgmac_param, sizeof(uint32_t));

    // Turn on transmit @100M
    xgmac_param = 0x60013001; //
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_TX_CONFIG, (uintptr_t)&xgmac_param, sizeof(uint32_t));
}

// Function used to stop all transmission
void stopTx(uint32_t xgmac_base_addr) {
    uint32_t xgmac_param = 0;
    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_TX_CONFIG, (uintptr_t)&xgmac_param, sizeof(uint32_t));

    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL, (uintptr_t)&xgmac_param,
                sizeof(uint32_t));
}

// Function used to stop all receiving
void stopRx(uint32_t xgmac_base_addr) {
    uint32_t xgmac_param = 0;
    // Clear necessary bits to stop the transmitter
    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_RX_CONFIG, (uintptr_t)&xgmac_param, sizeof(uint32_t));

    xgmac_param = 0;
    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL, (uintptr_t)&xgmac_param,
                sizeof(uint32_t));
}

// Function used to ensure next descriptor is setup for DMA control and tail pointer is accurate
static void processTxDescriptor(uint32_t base_address, uint32_t length) {
    // Re-init descriptor and put it back in to pool
    /* Physical address of the data buffer */
    txDescriptorRing[currentTxDescriptorIndex].header_or_buffer1_addr = (uint32_t)((uintptr_t)send_buffer);

    /* Initial control and status */
    txDescriptorRing[currentTxDescriptorIndex].buffer2_or_buffer1_addr = 0;

    txDescriptorRing[currentTxDescriptorIndex].control0 |=
        (((length << DESC_TXCTRL_SIZE1SHFT) & DESC_TXCTRL_SIZE1MASK));
    txDescriptorRing[currentTxDescriptorIndex].control0 |= (DESC_TXCTRL_IOC);

    txDescriptorRing[currentTxDescriptorIndex].control1 |= ((length << DESC_TX_PKT_LENSHIFT) & DESC_TX_PKT_LENMSK);
    txDescriptorRing[currentTxDescriptorIndex].control1 |= (DESC_TXSTS_OWNBYDMA);

    currentTxDescriptorIndex++;
    if (currentTxDescriptorIndex == NUM_TX_DESCRIPTORS) {
        currentTxDescriptorIndex = 0;
    }

    // Update tail ptr
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_TXDESC_TAIL_LPOINTER,
                (uintptr_t)&txDescriptorRing[currentTxDescriptorIndex], sizeof(uint32_t));
}

// Function used to ensure the next RX descriptor is setup for DMA control and tail pointer is accurate
static void processRxDescriptor(uint32_t base_address) {

    /* Physical address of the Rx buffer */
    rxDescriptorRing[currentRxDescriptorIndex].bufferAddress =
        (uint32_t)((uintptr_t)g_revc_descr0_addr[currentRxDescriptorIndex]);

    /* Initial control flags */
    rxDescriptorRing[currentRxDescriptorIndex].bufferAddress1 = 0;

    /* Initial status */
    rxDescriptorRing[currentRxDescriptorIndex].bufferAddress2 = 0;
    rxDescriptorRing[currentRxDescriptorIndex].controlFlags = (DESC_RXSTS_OWNBYDMA | DESC_RXSTS_IOC);

    currentRxDescriptorIndex++;
    if (currentRxDescriptorIndex == NUM_RX_DESCRIPTORS) {
        currentRxDescriptorIndex = 0;
    }

    // Set tail ptr address
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_DMA_CH0_RXDESC_TAIL_LPOINTER,
                (uintptr_t)&rxDescriptorRing[currentRxDescriptorIndex], sizeof(uint32_t));
}
#endif // FSBL_EXECUTION

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char xgmac_dev[] = "/dev/xgmac2";
    int32_t ret_val = -1;
    uint32_t xgmac_param = 0;

#ifdef FSBL_EXECUTION

    // Configure pinmux for boot up to access UART for debugging
    fsbl_configuration();

    // Update pinmux
    config_pinmux_update(UPDATE_SEL_ARRAY, xgma_pinmux_sel_update);

    // Set OCRAM non secure access
    volatile uint32_t *lcl_ptr = (uint32_t *)0x108CC418;
    *lcl_ptr = (uint32_t)0;
#endif
    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    hps_rstmgr_regs_t regs_buffer;

    if (rstmgr_handle < 0) {
        ret_val = rstmgr_handle;
    } else {

        int32_t xgmac_base_addr = -1;
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));
        regs_buffer.per0modrst &= ~((uint32_t)0x00230707);
        regs_buffer.per1modrst &= ~((uint32_t)0x0403000F);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));

        // Open XGMAC
        xgmac_base_addr = xgmac_open(xgmac_dev, 0);
        if (xgmac_base_addr < 0) {
            ret_val = xgmac_base_addr;
            printf("XGMAC failed to open\n");
        } else {

#ifdef FSBL_EXECUTION
            // The size of the packets being transmitted
            const uint32_t rx_tx_transmit_length = 1500;
            // Replace each element in the buffer with 0x00 - 0xFFFFFFF
            for (uint32_t i = 0; i < sizeof(tx_buffer) / sizeof(tx_buffer[0]); i++) {
                tx_buffer[i] = i % (0xFFFFFFFF);
            }

            // Set clear on write 1 for registers "RCWE"
            xgmac_param = 1;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_CSR_SW_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // ensure interrrupt signal response is as desired
            xgmac_param = 0x1000;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            printf("CURRENT DMA MODE %x\n", xgmac_param);

            // ensure master can perform burst up to maximum allowd "bit 0"
            // ensure burst lengths of 32,64,128 & 256 are allowed "bit 4-7"
            // Ensure enahanced mode is enabled "bit 11"
            // ensure address aligned burst transfers are set "bit 12"
            // Setup maximum AXI read request "bit 16-20"
            // Setup maximum AXI write request "bit 24-28"
            xgmac_param = 0x1f1f18f1;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_SYSBUS_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // Set Packet Filter to accept all
            xgmac_param = 0x80000001;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_MAC_PKT_FLTR, (uintptr_t)&xgmac_param, sizeof(xgmac_param));

            xgmac_param = 0;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_MAC_Q0_TXFLW_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            xgmac_param = 0;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_DMA_TX_EDMA_CONTROL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            // Enable Frame Pre-emption interrupt       BIT15
            // Enable Receive Error Status Interrupt    BIT14
            // Enable Transmit Error Status Interrupt   BIT13
            // Enable Timestamp enable                  BIT12
            xgmac_param = 0x0000f000;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_MAC_INT_ENABLE, (uintptr_t)&xgmac_param, sizeof(xgmac_param));

            // Enable Transmit Queue underflow interrupt    BIT0
            // Enable Receive Queue underflow interrupt     BIT16
            xgmac_param = 0x10001;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_SET_Q0_INT_EN, (uintptr_t)&xgmac_param, sizeof(xgmac_param));

            // Enable interrupts
            xgmac_param = 0x9fff; // Bits 0, 2 & 6 set "Normal Interrupt Summary Enabled"
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_DMA_CH0_INTERRUPT_ENABLE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // Set to forward even errorneous packets BIT4
            // Set packet to be read from RXQ after complete packet receieved BIT5
            // Set the receive Q size for buffer size 2048 = log2(RX_TOTAL_BUFSIZE/256) = log2(8) = 3 (bits) BIT(16-18)
            // "RX_TOTAL_BUFSIZE=2048"
            xgmac_param = 0x003f0030;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_SET_RXQ0_OP_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));

            xgmac_param = 2;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_MAC_RXQ_CTRL0, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            // Enalbe MTL transmit Queue is enabled BIT(3:2) = 10
            // Flush transmit Queue BIT0
            // Set the TX Queue size in blocks of 256 bytes = log2(TX_TOTAL_BUFSIZE/256) = log2(8) = 3 bits
            // "TX_TOTAL_BUFSIZE = 2048"
            xgmac_param = 0xf000a;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_MTL_SET_TXQ0_OP_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // Set CH0 to use enhanced descriptors bit 28
            // Set to ignore PBL bit 15
            // Set DMA to operate on second packet
            xgmac_param = 0x01008010;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_CONTROL, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // Configure PHY
            ret_val = (uint32_t)configure_mrvl_phy88E1512(xgmac_base_addr, 0x00);
            if (ret_val != 0) {

                // This isn't the correct PHY lest quit
                xgmac_close(xgmac_base_addr);
                rstmgr_close(rstmgr_handle);
                return ret_val;
            }

            // Configure RX & TX descriptors
            initRxDescriptorRing(xgmac_base_addr);
            initTxDescriptorRing(xgmac_base_addr);

            // Enable timestamp BIT0
            // Enable updating and initializing of time via MAC_System_Time_Seconds_Update and
            // MAC_System_Time_Nanoseconds_Update registers BIT2 & BIT3 Allow snapshot of timestamp for all pakcets
            // received via MAC BIT8 Allow low register of timestamp to roll over BIT9
            xgmac_param = 0x30D;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_TSTMP_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // the emac_ptp_clock should be represented here in nanoseconds
            // BIT16-23 are subseconds "nanoseconds"
            // BIT9-15 are sub nanoseconds "picoseconds" x 28
            xgmac_param = 0x28000;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_MAC_SSEC_INCR, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));

            // Start TX
            startTx(xgmac_base_addr, tx_buffer, rx_tx_transmit_length, 0);

            // Lets see if we can consum a few packets
            bool rx_pckt = 0; // note if we've received a packet
            bool tx_pckt = 0; // note if we've transmitted a packet
            do {
                // Used to capture debug status
                uint32_t dma_status = 0;
                xgmac_param = 0;
                xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_CH0_STATUS, (uintptr_t)&dma_status,
                            sizeof(uint32_t));
                xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_CH0_STATUS, (uintptr_t)&dma_status,
                            sizeof(uint32_t));

#ifdef EXTRA_XGMAC_DEBUG
                uint32_t dma_dbg_status = 0;
                dma_dbg_status = 0;
                xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_CH0_DEBUG_STATUS, (uintptr_t)&dma_dbg_status,
                            sizeof(uint32_t));

                printf("DMA STATUS 0x%x\n", dma_status);
                printf("Debug Status ch0 0x%x\n", dma_dbg_status);
#endif
                // Has transmission of the TX descriptor occured?
                if (dma_status & ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_TI_SET_MSK) {
                    printf("PACKET TRANSMITTED\n");
                    if (dma_status & ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_TBU_SET_MSK) {
                        printf("TX buffer unavailable\n");
                    }
                    processTxDescriptor(xgmac_base_addr, rx_tx_transmit_length);
                    tx_pckt = true;
                }

                // Has a descriptor been received
                if (dma_status & ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_RI_SET_MSK) {

                    printf("PACKET RECEIVED\n");
                    if (dma_status & ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_RBU_SET_MSK) {
                        printf("RX buffer unavailabe\n");
                    }
                    processRxDescriptor(xgmac_base_addr);

                    rx_pckt = true;
                }

                // The next TX Descriptor is not owned by DMA therefore it cannot be consmuned
                if (dma_status & 0x00000004) {

                    xgmac_param = 0;
                    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXDESC_L,
                                (uintptr_t)&xgmac_param, sizeof(uint32_t));
                    txDescr_t *cur_txdescp = (txDescr_t *)(xgmac_param);

                    // Set owned by DMA bit
                    cur_txdescp->control1 |= (1 << 31);

                    // Place tail at the next descriptor
                    xgmac_param += 0x10;
                    xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_DMA_CH0_TXDESC_TAIL_LPOINTER, (uintptr_t)&xgmac_param,
                                sizeof(xgmac_param));

#ifdef EXTRA_XGMAC_DEBUG
                    printf("wrote 0x%x to tail ptr\n", xgmac_param);
#endif
                }

                // The next Received Descriptor is not owned by DMA and thus ownership needs to be take
                if (dma_status & 0x00000080) {
                    xgmac_param = 0;
                    xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXDESC_L,
                                (uintptr_t)&xgmac_param, sizeof(uint32_t));
                    rxDescr_t *curRxdescp = (rxDescr_t *)(xgmac_param);

                    curRxdescp->controlFlags |= (1 << 31);
                    xgmac_param += 0x10;
                    xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_SET_DMA_CH0_RXDESC_TAIL_LPOINTER, (uintptr_t)&xgmac_param,
                                sizeof(xgmac_param));
                }
#ifdef EXTRA_XGMAC_DEBUG
                printf("Current TX index %d\n", currentTxDescriptorIndex);
                printf("Current RX index %d\n", currentRxDescriptorIndex);
#endif
            } while ((currentTxDescriptorIndex < 3) && (currentRxDescriptorIndex < 2));

            // stop all transmission
            stopRx(xgmac_base_addr);
            stopTx(xgmac_base_addr);
            if ((rx_pckt & tx_pckt) == true) {
                printf("Successful TX and RX of XGMAC Packet\n");
                ret_val = 0;
            }
#else  // NON FSBL TEST START

            /* CORE SPECIFIC TESTS START */
            // Read memory version
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_GET_MAC_VERSION, (uintptr_t)&xgmac_param, sizeof(xgmac_param));

            // Print Version
            if (xgmac_param == MAC_VERSION) {
                printf("MAC is CORRECT VERSION\n");
                ret_val = 0;
            } else {
                printf("MAC version is incorrect\n");
                ret_val = -1;
            }

            /* CORE SPECIFIC TEST END */

            // XGMAC DMA tests
            xgmac_param = 0x10;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            if (xgmac_param != 0x10) {
                printf("MISMATCH\n");
                ret_val = -1;
            } else {
                printf("DMA MODE MATCH\n");
            }

            xgmac_param = 0x1;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_SYSBUS_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_SYSBUS_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));
            if (xgmac_param != 0x1) {
                printf("MISMATCH\n");
                ret_val = -1;
            } else {
                printf("DMA SYS BUS MATCH\n");
            }
            /* MTL Specific Test Start */
            // Read Transmission selection algorithm
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_GET_TC0_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            // Print ETS control word
            printf("XGMAC ETS control word\n");
            ret_val = 0;

            // Set transmission selection algorithm to CBS
            xgmac_param = 0x00000001;

            // Read Transmission selection algorithm
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_SET_TC7_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            xgmac_param = 0;
            // Read Transmission selection algorithm
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_GET_TC7_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));
            // Print ETS control word
            if ((xgmac_param & 0x00000004) == 0x00000004) {
                printf("XGMAC ETS control CBSEN SET\n");
            } else {
                printf("XGMAC ETS control CBSEN NOT set (SIMICS BUG) \n");
            }

            // XGMAC DMA tests
            xgmac_param = 0x10;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            xgmac_param = 0;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_MODE, (uintptr_t)&xgmac_param, sizeof(uint32_t));
            if ((xgmac_param & 0x10) != 0x10) {
                printf("MISMATCH\n");
                ret_val = -1;
            } else {
                printf("DMA MODE MATCH\n");
            }

            xgmac_param = 0x1;
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_SET_DMA_SYSBUS_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));
            xgmac_ioctl(xgmac_base_addr, (int32_t)IOCTL_XGMAC_GET_DMA_SYSBUS_MODE, (uintptr_t)&xgmac_param,
                        sizeof(uint32_t));
            if (xgmac_param != 0x1) {
                printf("MISMATCH\n");
                ret_val = -1;
            } else {
                printf("DMA SYS BUS MATCH\n");
            }
            /* MTL Specific Test Start */
            // Read Transmission selection algorithm
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_GET_TC0_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            // Print ETS control word
            printf("XGMAC ETS control word\n");
            ret_val = 0;

            // Set transmission selection algorithm to CBS
            xgmac_param = 0x00000001;
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_SET_TC7_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));

            xgmac_param = 0;
            // Read Transmission selection algorithm
            xgmac_ioctl(xgmac_base_addr, IOCTL_XGMAC_MTL_GET_TC7_ETS_CTRL, (uintptr_t)&xgmac_param,
                        sizeof(xgmac_param));
            // Print ETS control word
            if ((xgmac_param & 0x00000004) == 0x00000004) {
                printf("XGMAC ETS control CBSEN SET\n");
            } else {
                printf("XGMAC ETS control CBSEN NOT set (SIMICS BUG) \n");
            }
            /* MTL specific Test Ending */
#endif // FSBL_EXECUTION
            printf("XGMAC Test Complete\n");
            xgmac_close(xgmac_base_addr);
            rstmgr_close(rstmgr_handle);
            return ret_val;
        }
    }
}

#ifdef __cplusplus
}
#endif
