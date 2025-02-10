#include "device.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// XGMAC Specific header
#include "xgmac.h"
#include "xgmac_internal.h"
#include "xgmac_regs.h"

// global file defines
#define INVALID_QOPTION -1

// XGMAC descriptors
device_descriptor_t xgmac_dev[] = {{.name = "/dev/xgmac0", .fd = XGMAC0_BASE, .acquired = 0},
                                   {.name = "/dev/xgmac1", .fd = XGMAC1_BASE, .acquired = 0},
                                   {.name = "/dev/xgmac2", .fd = XGMAC2_BASE, .acquired = 0}};

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      recv, read, send, write
 * description:
 *      return 0
 */
size_t xgmac_recv(int32_t fd, uintptr_t user_data, size_t size, int32_t flags) { return 0; }
size_t xgmac_read(int32_t fd, uintptr_t user_data, size_t size) { return xgmac_recv(fd, user_data, size, 0); }
size_t xgmac_send(int32_t fd, const uintptr_t user_data, size_t size, int32_t flags) { return 0; }
size_t xgmac_write(int32_t fd, const uintptr_t user_data, size_t size) { return xgmac_send(fd, user_data, size, 0); }

/* name: verify_xgmac_access
 * description: search if "base_address" has been properly captured for access
 * parameters(s): "base_address" base address of the xgmac timer
 */
static int32_t verify_xgmac_access(int32_t base_address) {

    int32_t ret_val = -1;
    // Search through devices for matching
    for (uint32_t i = 0; i < (sizeof(xgmac_dev) / sizeof(device_descriptor_t)); i++) {
        // Is the current base address valid and acquired
        if ((xgmac_dev[i].fd == base_address) && (xgmac_dev[i].acquired == true)) {
            ret_val = 0;
            break;
        }
    }
    return ret_val;
}

/* name: xgmac_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t xgmac_open(const char *path, int32_t flags) {
    int32_t xgmac_memory_base = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(xgmac_dev) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(xgmac_dev[i].name, path) == 0) {
                if (claim_device(&xgmac_dev[i])) {
                    xgmac_memory_base = xgmac_dev[i].fd;
                }
            }
        }
    }
    return xgmac_memory_base;
}

/* name: xgmac_close
 * description: close the fd via the base address of the device
 * parameters(s): base_add "address of the xgma device open"
 */
int32_t xgmac_close(int32_t base_add) {
    int32_t ret_val = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(xgmac_dev) / sizeof(device_descriptor_t)); i++) {
            if (xgmac_dev[i].fd == base_add) {
                xgmac_dev[i].acquired = 0;
                ret_val = 0;
                break;
            }
        }
    }
    return ret_val;
}

/* name: xgmac_ioctl
 * description: process the input output control command
 * parameters(s): base_add "address of the xgmac timer device open"
 *                operation "specific ioctl command for xgmac"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to
 */
int32_t xgmac_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    // TODO create structure of status return values
    int32_t ret_val = -1;

    // pointer to the memory denoted via argument user_buf
    uint32_t *cmd_data = (uint32_t *)user_data;

    // Validate if base address is currently acquired
    if ((verify_xgmac_access(base_add) == -1) || (length < (sizeof(uint32_t))) || (((void *)(user_data)) == nullptr)) {
        ret_val = -2;
    } else {

        /* CORE IOCTL CALLS START */
        switch ((xgmac_ioctl_t)operation) {
        case IOCTL_XGMAC_GET_MAC_TX_CONFIG: // Retrieve MAC Transmit Configuration
            *cmd_data = xgmac_get_tx_mac_config(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RX_CONFIG: // Retrieve MAC Receive Configuration
            *cmd_data = xgmac_get_rx_mac_config(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PKT_FLTR: // Retrieve MAC Packet Filter Configuration
            *cmd_data = xgmac_get_mac_pckt_filter(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_WD_JD_TOUT: // Retrieve MAC Watchdog and Jabber Timeout
            *cmd_data = xgmac_get_mac_wdt_jb_tout(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HSH_TREGO: // Retrieve MAC HASH Table REG0
            *cmd_data = xgmac_get_mac_htbl_reg0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HSH_TREG1: // Retrieve MAC HASH TAble REG1
            *cmd_data = xgmac_get_mac_htbl_reg1(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_GET_MAC_VLAN_TCTRL: // Retrieve MAC MAC_VLAN_TAG_CTRL
            *cmd_data = xgmac_get_mac_vlan_tctrl(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_GET_MAC_VLAN_HTBL: // Retrieve MAC VLAN HASH Table
            *cmd_data = xgmac_get_mac_vlan_htbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_VLAN_TDATA: // Retrieve MAC VLAN TAG Data
            *cmd_data = xgmac_get_mac_vlan_tdata(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_VLAN_INCL: // Retrieve MAC VLAN Inclusion/Replacement register
            *cmd_data = xgmac_get_mac_vlan_incl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_INN_VLAN_INCL: // Retrieve MAC Inner VLAN Inclusion register
            *cmd_data = xgmac_get_mac_vlan_nincl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RX_ETH_TYPE: // Retrieve MAC receive Ethernet type match register
            *cmd_data = xgmac_get_mac_rx_etmtch(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q0_TXFLW_CTRL: // Retrieve MAC Q0 transmit flow control register
            *cmd_data = xgmac_get_mac_q0_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q1_TXFLW_CTRL: // Retrieve MAC Q1 transmit flow control register
            *cmd_data = xgmac_get_mac_q1_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q2_TXFLW_CTRL: // Retrieve MAC Q2 transmit flow control register
            *cmd_data = xgmac_get_mac_q2_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q3_TXFLW_CTRL: // Retrieve MAC Q3 transmit flow control register
            *cmd_data = xgmac_get_mac_q3_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q4_TXFLW_CTRL: // Retrieve MAC Q4 transmit flow control register
            *cmd_data = xgmac_get_mac_q4_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q5_TXFLW_CTRL: // Retrieve MAC Q5 transmit flow control register
            *cmd_data = xgmac_get_mac_q5_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q6_TXFLW_CTRL: // Retrieve MAC Q6 transmit flow control register
            *cmd_data = xgmac_get_mac_q6_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_Q7_TXFLW_CTRL: // Retrieve MAC Q7 transmit flow control register
            *cmd_data = xgmac_get_mac_q7_fctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_MAX_RXFLW_CTRL: // Retrieve MAC Max receive flow control register
            *cmd_data = xgmac_get_mac_max_rxfctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL4: // Retrieve MAC receive queue control 4 register
            *cmd_data = xgmac_get_mac_rx_qctrl4(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL5: // Retrieve MAC receive queue control 5 register
            *cmd_data = xgmac_get_mac_rx_qctrl5(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL0: // Retrieve MAC receive queue control 0 register
            *cmd_data = xgmac_get_mac_rx_qctrl0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL1: // Retrieve MAC receive queue control 1 register
            *cmd_data = xgmac_get_mac_rx_qctrl1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL2: // Retrieve MAC receive queue control 2 register
            *cmd_data = xgmac_get_mac_rx_qctrl2(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RXQ_CTRL3: // Retrieve MAC receive queue control 3 register
            *cmd_data = xgmac_get_mac_rx_qctrl3(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_INT_STATUS: // Retrieve MAC interrupt status register  "read only"
            *cmd_data = xgmac_get_mac_int_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_INT_ENABLE: // Retrieve MAC interrupt enable register
            *cmd_data = xgmac_get_mac_int_en(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_RX_TX_STATUS: // Retrieve MAC receive/transmit status register "read only"
            *cmd_data = xgmac_get_mac_rx_tx_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_LPI_CTRL_STS: // Retrieve MAC LPI control status register
            *cmd_data = xgmac_get_mac_lpi_ctrl_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_LPI_TM_CTRL: // Retrieve MAC LPI timers control register
            *cmd_data = xgmac_get_mac_lpi_tm_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_AUTO_ENTRY_TM: // Retrieve MAC LPI auto entry timer value "microseconds" register
            *cmd_data = xgmac_get_mac_lpi_aet_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_US_TIC_CNTR: // Retrieve MAC register to control the generation of reference time in
                                              // "microseconds"
            *cmd_data = xgmac_get_mac_tic_ucntr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_VERSION: // Retrieve MAC version register "read only"
            *cmd_data = xgmac_get_mac_version(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_DEBUG: // Retrieve MAC debug register "read only"
            *cmd_data = xgmac_get_mac_debug(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HW_FEAT0: // Retrieve MAC feature 0 presence indicator register "read only"
            *cmd_data = xgmac_get_mac_feat0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HW_FEAT1: // Retrieve MAC feature 1 presence indicator register "read only"
            *cmd_data = xgmac_get_mac_feat1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HW_FEAT2: // Retrieve MAC feature 2 presence indicator register "read only"
            *cmd_data = xgmac_get_mac_feat2(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HW_FEAT3: // Retrieve MAC feature 3 presence indicator register "read only"
            *cmd_data = xgmac_get_mac_feat3(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_HW_FEAT4: // Retrieve MAC feature 4 presence indicator register "read only"
            *cmd_data = xgmac_get_mac_feat4(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_EXT_CONFIG: // Retrieve MAC extended configuration register est operation mode of MAC
                                             // transmitter
            *cmd_data = xgmac_get_mac_ext_cfg0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_EXT_CONFIG1: // Retrieve MAC register split mode control field
            *cmd_data = xgmac_get_mac_ext_cfg1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_FPE_CTRL_STS: // Retrieve MAC operation of frame preemption
            *cmd_data = xgmac_get_mac_fpe_ctrl_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_CSR_SW_CTRL: // Retrieve MAC programmable controls for CSR
            *cmd_data = xgmac_get_mac_csr_pg_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR0_HIGH: // Retrieve MAC address 0 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR0_LOW: // Retrieve MAC address 0 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR1_HIGH: // Retrieve MAC address 1 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR1_LOW: // Retrieve MAC address 1 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR2_HIGH: // Retrieve MAC address 2 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr2(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR2_LOW: // Retrieve MAC address 2 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr2(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR3_HIGH: // Retrieve MAC address 3 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr3(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR3_LOW: // Retrieve MAC address 3 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr3(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR4_HIGH: // Retrieve MAC address 4 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr4(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR4_LOW: // Retrieve MAC address 4 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr4(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR5_HIGH: // Retrieve MAC address 5 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr5(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR5_LOW: // Retrieve MAC address 5 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr5(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR6_HIGH: // Retrieve MAC address 6 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr6(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR6_LOW: // Retrieve MAC address 6 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr6(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR7_HIGH: // Retrieve MAC address 7 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr7(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR7_LOW: // Retrieve MAC address 7 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr7(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR8_HIGH: // Retrieve MAC address 8 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr8(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR8_LOW: // Retrieve MAC address 8 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr8(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR9_HIGH: // Retrieve MAC address 9 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr9(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR9_LOW: // Retrieve MAC address 9 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr9(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR10_HIGH: // Retrieve MAC address 10 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr10(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR10_LOW: // Retrieve MAC address 10 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr10(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR11_HIGH: // Retrieve MAC address 11 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr11(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR11_LOW: // Retrieve MAC address 11 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr11(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR12_HIGH: // Retrieve MAC address 12 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr12(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR12_LOW: // Retrieve MAC address 12 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr12(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR13_HIGH: // Retrieve MAC address 13 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr13(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR13_LOW: // Retrieve MAC address 13 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr13(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR14_HIGH: // Retrieve MAC address 14 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr14(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR14_LOW: // Retrieve MAC address 14 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr14(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR15_HIGH: // Retrieve MAC address 15 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr15(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR15_LOW: // Retrieve MAC address 15 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr15(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR16_HIGH: // Retrieve MAC address 16 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr16(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR16_LOW: // Retrieve MAC address 16 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr16(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR17_HIGH: // Retrieve MAC address 17 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr17(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR17_LOW: // Retrieve MAC address 17 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr17(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR18_HIGH: // Retrieve MAC address 18 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr18(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR18_LOW: // Retrieve MAC address 18 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr18(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR19_HIGH: // Retrieve MAC address 19 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr19(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR19_LOW: // Retrieve MAC address 19 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr19(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR20_HIGH: // Retrieve MAC address 20 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr20(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR20_LOW: // Retrieve MAC address 20 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr20(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR21_HIGH: // Retrieve MAC address 21 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr21(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR21_LOW: // Retrieve MAC address 21 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr21(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR22_HIGH: // Retrieve MAC address 22 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr22(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR22_LOW: // Retrieve MAC address 22 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr22(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR23_HIGH: // Retrieve MAC address 23 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr23(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR23_LOW: // Retrieve MAC address 23 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr23(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR24_HIGH: // Retrieve MAC address 24 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr24(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR24_LOW: // Retrieve MAC address 24 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr24(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR25_HIGH: // Retrieve MAC address 25 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr25(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR25_LOW: // Retrieve MAC address 25 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr25(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR26_HIGH: // Retrieve MAC address 26 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr26(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR26_LOW: // Retrieve MAC address 26 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr26(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR27_HIGH: // Retrieve MAC address 27 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr27(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR27_LOW: // Retrieve MAC address 27 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr27(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR28_HIGH: // Retrieve MAC address 28 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr28(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR28_LOW: // Retrieve MAC address 28 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr28(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR29_HIGH: // Retrieve MAC address 29 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr29(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR29_LOW: // Retrieve MAC address 29 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr29(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR30_HIGH: // Retrieve MAC address 30 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr30(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR30_LOW: // Retrieve MAC address 30 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr30(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR31_HIGH: // Retrieve MAC address 31 high "upper 16 bits"
            *cmd_data = xgmac_get_mac_haddr31(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ADDR31_LOW: // Retrieve MAC address 31 low "lower 32 bits"
            *cmd_data = xgmac_get_mac_laddr31(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_GET_MAC_IND_ACTRL: // Retrieve MAC indirect access control of MAC
            *cmd_data = xgmac_get_mac_ind_actrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_IND_ADATA: // Retrieve MAC indirect access data of MAC
            *cmd_data = xgmac_get_mac_ind_adata(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_L3_L4_ADDR_CTRL: // Retrieve indirect address and control for layer 3/4 filter
            *cmd_data = xgmac_get_mac_l3_l4_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_L3_L4_ADDR_DATA: // Retrieve indirect data and control for layer 3/4 filter
            *cmd_data = xgmac_get_mac_l3_l4_data(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_ARP_ADDR: // Retrieve arp address register IPV4 destination address
            *cmd_data = xgmac_get_mac_arp_addr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMTMP_CTRL: // Retrieve system time generator register
            *cmd_data = xgmac_get_mac_tmstamp_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SSEC_INCR: // Retrieve IEEE 1588 timestamp governed feature for sub second increment
                                            // register
            *cmd_data = xgmac_get_mac_tmstamp_ssec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TM_SEC: // Retrieve system time in seconds "read only"
            *cmd_data = xgmac_get_mac_syst_sec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TM_NSEC: // Retrieve system time in nano seconds "read only"
            *cmd_data = xgmac_get_mac_syst_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TM_SEC_UPDT: // Retrieve system time seconds
            *cmd_data = xgmac_get_mac_systu_sec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TM_NSEC_UPDT: // Retrieve system time nano seconds
            *cmd_data = xgmac_get_mac_systu_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TMTMP_ADDEND: // Retrieve timestamp addend register "present only when 1588
                                                   // timestamp feature is selected"
            *cmd_data = xgmac_get_mac_tmstamp_addend(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SYS_TM_HWORD_SEC: // Retrieve timestamp higher word seconds register "present only when
                                                   // 1588 timestamp feature is selected"
            *cmd_data = xgmac_get_mac_tmstamp_hsword(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS: // Retrieve timestamp status register
            *cmd_data = xgmac_get_mac_tmstamp_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_NSEC: // Retrieve nanoseconds portion of 64 bit timestamp captured for
                                                     // the PTP packet successfully transmitted "read only"
            *cmd_data = xgmac_get_mac_tmstamp_snsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_SEC: // Retrieve seconds portion of 64 bit timestamp captured for the PTP
                                                    // packet successfully transmitted "read only"
            *cmd_data = xgmac_get_mac_tmstamp_sts_sec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_PID: // Retrieve ptp packet ID relative to TX timestamp status (sec &
                                                    // nanosec) "read only"
            *cmd_data = xgmac_get_mac_tmstamp_pkt_id(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_AUX_TMPSTMP_CTRL: // Retrieve auxillary timestamp control register "snapshot"
            *cmd_data = xgmac_get_mac_aux_tctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_AUX_TMSTMP_NSEC: // Retrieve auxillary nanoseconds portion of 64 bit auxillary snapshot
                                                  // "read only"
            *cmd_data = xgmac_get_mac_aux_nsec_snshot(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_AUX_TMSTMP_SEC: // Retrieve auxillary seconds portion of 64 bit auxillary snapshot
                                                 // "read only"
            *cmd_data = xgmac_get_mac_aux_sec_snshot(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_ASYM_CORR: // Retrieve mac timestamp ingress asymmetry correction register
            *cmd_data = xgmac_get_mac_tmstamp_ingress(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_ASYM_CORR: // Retrieve mac timestamp egress asymmetry correction register
            *cmd_data = xgmac_get_mac_tmstamp_egress(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_CORR_NSEC: // Retrieve mac timestamp ingress correction nanosecond register
            *cmd_data = xgmac_get_mac_ingress_cor_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_CORR_SNSEC: // Retrieve mac timestamp ingress correction sub-nanosecond
                                                         // register
            *cmd_data = xgmac_get_mac_ingress_cor_snsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_CORR_NSEC: // Retrieve mac timestamp egress correction nanosecond register
            *cmd_data = xgmac_get_mac_egress_cor_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_CORR_SNSEC: // Retrieve mac timestamp egress correction sub-nanosecond
                                                         // register
            *cmd_data = xgmac_get_mac_egress_cor_snsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS_CTRL: // Retrieve mac pps control register "only when timestamp feature is selected
                                           // no external timestamp"
            *cmd_data = xgmac_get_mac_pps_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS0_TRG_SEC: // Retrieve mac PPS0 target time seconds register
            *cmd_data = xgmac_get_mac_pps0_tgt_sec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS0_TRG_NSEC: // Retrieve mac PPS0 target time nano seconds register
            *cmd_data = xgmac_get_mac_pps0_tgt_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS0_INTV: // Retrieve mac PPS0 interval register "number of sub-second increment value
                                            // between rising edges"
            *cmd_data = xgmac_get_mac_pps0_intv(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS0_WIDTH: // Retrieve mac PPS0 width register "number of sub-second increment value
                                             // between rising & falaling edges"
            *cmd_data = xgmac_get_mac_pps0_width(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS1_TRG_SEC: // Retrieve mac PPS1 target time seconds register
            *cmd_data = xgmac_get_mac_pps1_tgt_sec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS1_TRG_NSEC: // Retrieve mac PPS1 target time nano seconds register
            *cmd_data = xgmac_get_mac_pps1_tgt_nsec(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS1_INTV: // Retrieve mac PPS1 interval register "number of sub-second icrement value
                                            // between rising edges"
            *cmd_data = xgmac_get_mac_pps1_intv(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PPS1_WIDTH: // Retrieve mac PPS1 with register "number of sub-second icrement value
                                             // between rising & falaling edges"
            *cmd_data = xgmac_get_mac_pps1_width(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_PTO_CTRL: // Retrieve mac PTP offload engine operation "ptp timestamp offload feature
                                           // selected"
            *cmd_data = xgmac_get_mac_pto_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN0: // Retrieve mac part 1 of 80 bit port identity of the PTP node
            *cmd_data = xgmac_get_mac_port_id0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN1: // Retrieve mac part 2 of 80 bit port identity of the PTP node
            *cmd_data = xgmac_get_mac_port_id1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN2: // Retrieve mac part 3 of 80 bit port identity of the PTP node
            *cmd_data = xgmac_get_mac_port_id2(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MAC_LOG_MSG_INTV: // Retrieve mac register contains periodic intervals for automatic PTP
                                               // packet generation
            *cmd_data = xgmac_get_mac_ptp_aintv(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_SGL_CMD_ADDR: // Retrieve MDIO address of ports: devices and registers by the SMA
            *cmd_data = xgmac_get_mdio_sgl_cmd_addr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA: // Retrieve MDIO DATA of ports: devices and registers
            *cmd_data = xgmac_get_mdio_sgl_cmd_data(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_CONT_WR_ADDR: // Retrieve MDIO program to start continuous write operation
            *cmd_data = xgmac_get_mdio_cnt_wr_addr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_CONT_WR_DATA: // Retrieve MDIO data to be written during continuous write operation
            *cmd_data = xgmac_get_mdio_cnt_wr_data(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_CONT_SCAN_PEN: // Retrieve MDIO control for PHY ports and corresponding devices
            *cmd_data = xgmac_get_mdio_sctn_pen(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_INT_STATUS: // Retrieve MDIO source of SMA interrupt "read only"
            *cmd_data = xgmac_get_mdio_sma_int_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_INT_ENABLE: // Retrieve MDIO Interrupt Enable
            *cmd_data = xgmac_get_mdio_sma_int_en(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORT_CON_DISC_STS: // Retrieve MDIO hot plug in status for port 0-31 "read only"
            *cmd_data = xgmac_get_mdio_conn_disc_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_CLS22_PORT: // Retrieve MDIO configuration of SMA to access PHY ports
            *cmd_data = xgmac_get_mdio_cl22_port(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORT_NX4_IND_CTRL: // Retrieve MDIO fields for controling port range select
            *cmd_data = xgmac_get_mdio_port_rng_sel(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P0_INUSE: // Retrieve MDIO status of each device on port nx4 plus 0
            *cmd_data = xgmac_get_mdio_nx4_p0_dsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P0_LSTS: // Retrieve MDIO link status of each device on port nx4 plus 0 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p0_lsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P0_ASTS: // Retrieve MDIO alive status of each device on port nx4 plus 0 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p0_asts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P1_INUSE: // Retrieve MDIO status of each device on port nx4 plus 1
            *cmd_data = xgmac_get_mdio_nx4_p1_dsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P1_LSTS: // Retrieve MDIO link status of each device on port nx4 plus 1  "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p1_lsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P1_ASTS: // Retrieve MDIO alive status of each device on port nx4 plus 1  "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p1_asts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P2_INUSE: // Retrieve MDIO status of each device on port nx4 plus 2
            *cmd_data = xgmac_get_mdio_nx4_p2_dsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P2_LSTS: // Retrieve MDIO link status of each device on port nx4 plus 2 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p2_lsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P2_ASTS: // Retrieve MDIO alive status of each device on port nx4 plus 2 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p2_asts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P3_INUSE: // Retrieve MDIO status of each device on port nx4 plus 3
            *cmd_data = xgmac_get_mdio_nx4_p3_dsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P3_LSTS: // Retrieve MDIO link status of each device on port nx4 plus 3 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p3_lsts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MDIO_PORTNX4P3_ASTS: // Retrieve MDIO alive status of each device on port nx4 plus 3 "read
                                                  // only"
            *cmd_data = xgmac_get_mdio_nx4_p3_asts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_CTRL: // Retrieve MMC control register
            *cmd_data = xgmac_get_mmc_ctrl_reg(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_INT: // Retrieve MMC receive interrupt status "read only"
            *cmd_data = xgmac_get_mmc_rx_int_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_TX_INT: // Retrieve MMC transmit interrupt status "read only"
            *cmd_data = xgmac_get_mmc_tx_int_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_INT_EN: // Retrieve MMC receive interrupt enable register
            *cmd_data = xgmac_get_mmc_rx_int_en(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_TX_INT_EN: // Retrieve MMC transmit interrupt enable
            *cmd_data = xgmac_get_mmc_tx_int_en(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_FPE_TX_INT: // Retrieve interrupts generated from all FPE related TX statistics "read
                                             // only"
            *cmd_data = xgmac_get_fpe_tx_int(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_FPE_TX_INT_MSK: // Retrieve interrupt masks generated from all FPE related TX
                                                 // statistics "read only"
            *cmd_data = xgmac_get_fpe_tx_int_msk(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_TX_FPE_FRAG_CNTR: // Retrieve number of mpackets transmitted due to preemption "read
                                                   // only"
            *cmd_data = xgmac_get_fpe_frag_cnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_TX_HOLD_RQ_CNTR: // Retrieve count of times for hold request "read only"
            *cmd_data = xgmac_get_fpe_hold_req(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_FPE_RX_INT: // Retrieve interrupts generated from FPE related stat counters "read only"
            *cmd_data = xgmac_get_fpe_rx_int(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_FPE_RX_INT_MSK: // Retrieve interrupt masks generated from FPE related stat counters
                                                 // "read only"
            *cmd_data = xgmac_get_fpe_rx_int_mask(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_PKT_ASM_ERR_CNTR: // Retrieve number of mac frames with reassembly erros on RX'er
                                                      // "read only"
            *cmd_data = xgmac_get_fpe_rx_pae_cntr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_PKT_SMD_ERR_CNTR: // Retrieve number of mac frames with unknown SMD value "read
                                                      // only"
            *cmd_data = xgmac_get_fpe_rx_ukn_esmd_cntr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_PKT_ASM_OK_CNTR: // Retrieve number of mac frames successfully reassemebled "read
                                                     // only"
            *cmd_data = xgmac_get_fpe_rx_asok_cntr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_RX_FPE_FRAG_CNTR: // Retrieve number of additional mpacket for preemption "read only"
            *cmd_data = xgmac_get_fpe_rx_frag_cntr(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_IPC_RX_INT_MASK: // Retrieve mask for interrupt generated from receive IPC statistics
                                                  // counters
            *cmd_data = xgmac_get_ipc_rx_int_mask(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_MMC_IPC_RX_INT: // Retrieve interrupts generated from receive IPC statistics counters "read
                                             // only"
            *cmd_data = xgmac_get_ipc_rx_int(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_OCT_CNT_GBL: // Retrieve lower 32 bits of transmitted octet count in good and bad
                                             // packets "read only"
            *cmd_data = xgmac_get_tx_oct_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_OCT_CNT_GBH: // Retrieve upper 32 bits of transmitted octet count in good and bad
                                             // packets "read only"
            *cmd_data = xgmac_get_tx_oct_gbh(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_PKT_CNT_GBL: // Retrieve lower 32 bits of transmitted good and bad packets "read only"
            *cmd_data = xgmac_get_tx_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_BCAST_PKT_CNT_GL: // Retrieve lower 32 bits of transmitted broadcast good and low
                                                  // packets "read only"
            *cmd_data = xgmac_get_tx_bpkg_gl(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_GET_TX_MCAST_PKT_CNT_GL: // Retrieve lower 32 bits of transmitted multicast good and low
                                                  // packets "read only"
            *cmd_data = xgmac_get_tx_mpkg_gl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_64OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 64 octet size good and bad
                                               // packets "read only"
            *cmd_data = xgmac_get_tx_g0_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_65_127_OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 65-127 octet size good and
                                                    // bad packets "read only"
            *cmd_data = xgmac_get_tx_g1_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_128_255_OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 128-255 octet size good
                                                     // and bad packets "read only"
            *cmd_data = xgmac_get_tx_g2_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_256_511_OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 256-511 octet size good
                                                     // and bad packets "read only"
            *cmd_data = xgmac_get_tx_g3_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_512_1023_OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 512-1023 octet size good
                                                      // and bad packets "read only"
            *cmd_data = xgmac_get_tx_g4_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_1024_MAX_OCT_PKT_GBL: // Retrieve lower 32 bits of transmitted 1023 - max octet size
                                                      // good and bad packets "read only"
            *cmd_data = xgmac_get_tx_g5_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_UCAST_PKT_GBL: // Retrieve lower 32 bits of transmitted unicast good and bad packets
                                               // "read only"
            *cmd_data = xgmac_get_tx_ucast_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_MCAST_PKT_GBL: // Retrieve lower 32 bits of transmitted multicast good and bad packets
                                               // "read only"
            *cmd_data = xgmac_get_tx_mcast_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_BCAST_PKT_GBL: // Retrieve lower 32 bits of transmitted broadcast good and bad packets
                                               // "read only"
            *cmd_data = xgmac_get_tx_bcast_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_UNDFLW_ERR_PKT: // Retrieve lower 32 bits of transmitted packets aborted for underlfow
                                                // "read only"
            *cmd_data = xgmac_get_tx_uferr_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_OCT_COUNT_GL: // Retrieve lower 32 bits of transmitted good octets "read only"
            *cmd_data = xgmac_get_tx_oct_cnt_gl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_OCT_COUNT_GH: // Retrieve upper 32 bits of transmitted good octets "read only"
            *cmd_data = xgmac_get_tx_oct_cnt_gh(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_PKT_COUNT_GL: // Retrieve lower 32 bits of transmitted good packets "read only"
            *cmd_data = xgmac_get_tx_pkt_cnt_gl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_PSE_PKT_COUNT: // Retrieve lower 32 bits of transmitted pause packets "read only"
            *cmd_data = xgmac_get_tx_pse_lpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_VLAN_PKT_COUNT_GL: // Retrieve lower 32 bits of transmitted good VLAN packets "read
                                                   // only"
            *cmd_data = xgmac_get_tx_vlan_lpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_LPI_USEC_CTR: // Retrieve duration in "microseconds" MAC was in TX LPI "read only"
            *cmd_data = xgmac_get_tx_lpi_uscnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_LPI_TRAN_CTR: // Retrieve number of times MAC transitioned to LPI TX "read only"
            *cmd_data = xgmac_get_tx_lpi_tr_cnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_SGL_COL_PKT_G: // Retrieve number of successfully transmitted packets by DWC_xgmac after
                                               // single collision "read only"
            *cmd_data = xgmac_get_tx_sgl_col_gpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_MULT_COL_PKT_G: // Retrieve number of successfully transmitted packets by DWC_xgmac
                                                // after multiple collisions "read only"
            *cmd_data = xgmac_get_tx_mtl_col_gpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_DFRD_EPKT: // Retrieve number of successfully transmitted packets by DWC_xgmac after
                                           // half duplex deferral "read only"
            *cmd_data = xgmac_get_tx_dfr_gpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_LATE_COL_EPKT: // Retrieve number of packets aborted by DWC_xgmac for late collision
                                               // error "read only"
            *cmd_data = xgmac_get_tx_lcol_epkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_EXC_COL_EPKT: // Retrieve number of packets aborted by DWC_xgmac for excessive (16)
                                              // collision error "read only"
            *cmd_data = xgmac_get_tx_ecol_epkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_CAR_ERR_EPKT: // Retrieve number of aborted packets for carrier sense error "read only"
            *cmd_data = xgmac_get_tx_ecar_epkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_TX_EXC_DFRD_ERR: // Retrieve number of packets aborted by DWC_xgmac for excessive deferral
                                              // error "read only"
            *cmd_data = xgmac_get_tx_edfr_epkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_PKT_COUNT_GBL: // Retrieve lower 32 bits of received good and bad packets count "read
                                               // only"
            *cmd_data = xgmac_get_rx_pcnt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OCT_COUNT_GBL: // Retrieve lower 32 bits of received good and bad octet count "read
                                               // only"
            *cmd_data = xgmac_get_rx_ocnt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OCT_COUNT_GBH: // Retrieve upper 32 bits of received good and bad octet count "read
                                               // only"
            *cmd_data = xgmac_get_rx_ocnt_gbh(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OCT_COUNT_GL: // Retrieve lower 32 bits of received good octet count "read only"
            *cmd_data = xgmac_get_rx_gd_lcnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OCT_COUNT_GH: // Retrieve upper 32 bits of received good octet count "read only"
            *cmd_data = xgmac_get_rx_gd_hcnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_BCAST_PKT_GL: // Retrieve lower 32 bits of received good broadcast packets count "read
                                              // only"
            *cmd_data = xgmac_get_rx_bcst_glpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_MCAST_PKT_GL: // Retrieve lower 32 bits of received good multicast packets count "read
                                              // only"
            *cmd_data = xgmac_get_rx_mcst_glpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_CRC_PKT_ERR_L: // Retrieve lower 32 bits of received packets with CRC errors "read only"
            *cmd_data = xgmac_get_rx_ecrc_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_RUNT_PKT_ERR: // Retrieve received packets with runt error "read only"
            *cmd_data = xgmac_get_rx_erunt_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_JBR_PKT_ERR: // Retrieve received packets with jabber error "read only"
            *cmd_data = xgmac_get_rx_ejbr_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_USZE_PKT_G: // Retrieve received good undersize packets "read only"
            *cmd_data = xgmac_get_rx_usize_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OSZE_PKT_G: // Retrieve received good oversize packets "read only"
            *cmd_data = xgmac_get_rx_osize_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_64OCT_PKT_GBL: // Retrieve lower 32 bits of received 64 octet size good and bad packets
                                               // "read only"
            *cmd_data = xgmac_get_rx_g0_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_65_127_OCT_PKT_GBL: // Retrieve lower 32 bits of received 65-127 octet size good and bad
                                                    // packets "read only"
            *cmd_data = xgmac_get_rx_g1_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_128_255_OCT_PKT_GBL: // Retrieve lower 32 bits of received 128-255 octet size good and
                                                     // bad packets "read only"
            *cmd_data = xgmac_get_rx_g2_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_256_511_OCT_PKT_GBL: // Retrieve lower 32 bits of received 256-511 octet size good and
                                                     // bad packets "read only"
            *cmd_data = xgmac_get_rx_g3_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_512_1023_OCT_PKT_GBL: // Retrieve lower 32 bits of received 512-1023 octet size good and
                                                      // bad packets "read only"
            *cmd_data = xgmac_get_rx_g4_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_1024_MAX_OCT_PKT_GBL: // Retrieve lower 32 bits of received 1023 - max octet size good
                                                      // and bad packets "read only"
            *cmd_data = xgmac_get_rx_g5_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_UCAST_PKT_GL: // Retrieve lower 32 bits of received good unicast packets "read only"
            *cmd_data = xgmac_get_rx_gupkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_LGTH_ERR_PKT_L: // Retrieve lower 32 bits of received packets with length errors "read
                                                // only"
            *cmd_data = xgmac_get_rx_lerr_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_OUT_RNG_PKT_L: // Retrieve lower 32 bits of received packets with out of range length
                                               // field count "read only"
            *cmd_data = xgmac_get_rx_ornge_lpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_PSE_PKT_L: // Retrieve lower 32 bits of received pause packet count "read only"
            *cmd_data = xgmac_get_rx_pse_lpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_FIFO_OFLW_PKT_L: // Retrieve lower 32 bits of received packets count that had RX queue
                                                 // overflow "read only"
            *cmd_data = xgmac_get_rx_fifo_opkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_VLAN_PKT_GBL: // Retrieve lower 32 bits of received good bad VLAN packets count "read
                                              // only"
            *cmd_data = xgmac_get_rx_vlan_pkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_WDT_ERR_PKT: // Retrieve lower 32 bits of received packets with watchdog error count
                                             // "read only"
            *cmd_data = xgmac_get_rx_ewdt_pkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_LPI_USEC_CTR: // Retrieve duration in "microseconds" MAC was in RX LPI "read only"
            *cmd_data = xgmac_get_rx_lpi_uscnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_LPI_TRAN_CTR: // Retrieve number of times MAC transitioned to RX "read only"
            *cmd_data = xgmac_get_rx_trans_cnt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_DCRD_PKT_GBL: // Retrieve lower 32 bits of received good bad discarded packets count
                                              // "read only"
            *cmd_data = xgmac_get_rx_gdpkt_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_DCRD_OCT_GBL: // Retrieve lower 32 bits of received good bad discarded octets count
                                              // "read only"
            *cmd_data = xgmac_get_rx_gdoct_gbl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_DCRD_OCT_GBH: // Retrieve upper 32 bits of received good bad discarded packets count
                                              // "read only"
            *cmd_data = xgmac_get_rx_gdoct_gbh(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_ALGN_ERR_PKT: // Retrieve number of packets received by DWC_xgmac with alignment error
                                              // "read only"
            *cmd_data = xgmac_get_rx_algn_epkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_GD_PKT_L: // Retrieve lower 32 bits of good ipv4 datagrams received TCP:UDP: or
                                               // ICMP "read only"
            *cmd_data = xgmac_get_rxipv4_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_HDR_ERR_PKT_L: // Retrieve header error packets "read only"
            *cmd_data = xgmac_get_rxipv4_hepkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_NOPAYL_PKT_L: // Retrieve lower 32 bits of good IPv4 datagrams received NOT
                                                   // TCP:UDP: or ICMP "read only"
            *cmd_data = xgmac_get_rxipv4_npyld_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_FRAG_PKT_L: // Retrieve lower 32 bits of good IPv4 datagrams with framentation
                                                 // "read only"
            *cmd_data = xgmac_get_rxipv4_frag_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_UDP_CHKSM_DPKT_L: // Retrieve lower 32 bits of good IPv4 datagrams received with
                                                       // UDP checksum disabled "read only"
            *cmd_data = xgmac_get_rxipv4_upd_dckpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_GD_PKT_L: // Retrieve lower 32 bits of good IPv6 datagrams received "read only"
            *cmd_data = xgmac_get_rxipv6_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_HDR_ERR_PKT_L: // Retrieve lower 32 bits of datagram IPv6 with header error "read
                                                    // only"
            *cmd_data = xgmac_get_rxipv6_hepkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_NOPAYL_PKT_L: // Retrieve lower 32 bits of good IPv6 datagrans received NOT
                                                   // TCP:UDP: or ICMP "read only"
            *cmd_data = xgmac_get_rxipv6_npyld_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_UDP_GD_PKT_L: // Retrieve lower 32 bits of good UDP datagrams received "read only"
            *cmd_data = xgmac_get_rxudp_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_UDP_ERR_PKT_L: // Retrieve lower 32 bits of good UDP datagrams received with checksum
                                               // error "read only"
            *cmd_data = xgmac_get_rxudp_eckpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_TCP_GD_PKT_L: // Retrieve lower 32 bits of good TCP datagrams received "read only"
            *cmd_data = xgmac_get_rxtcp_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_TCP_ERR_PKT_L: // Retrieve lower 32 bits of good TCP datagrams received with checksum
                                               // error "read only"
            *cmd_data = xgmac_get_rxtcp_eckpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_ICMP_GD_PKT_L: // Retrieve lower 32 bits of good ICMP datagrams received "read only"
            *cmd_data = xgmac_get_rxicmp_gdpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_ICMP_ERR_PKT_L: // Retrieve lower 32 bits of good ICMP datagrams received with checksum
                                                // error "read only"
            *cmd_data = xgmac_get_rxicmp_eckpkt(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_GD_OCT_L: // Retrieve lower 32 bits of good IPv4 octet datagrams received TCP:UDP:
                                               // or ICMP "read only"
            *cmd_data = xgmac_get_rxipv4_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_HDR_ERR_OCT_L: // Retrieve header error packets "read only"
            *cmd_data = xgmac_get_rxipv4_heoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_NOPAYL_OCT_L: // Retrieve lower 32 bits of good IPv4 octet datagrams received NOT
                                                   // TCP:UDP: or ICMP "read only"
            *cmd_data = xgmac_get_rxipv4_npyld_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_FRAG_OCT_L: // Retrieve lower 32 bits of good IPv4 octet datagrams with
                                                 // framentation "read only"
            *cmd_data = xgmac_get_rxipv4_frag_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV4_UDP_CHKSM_DOCT_L: // Retrieve lower 32 bits of good IPv4 octet datagrams received
                                                       // with UDP checksum disabled "read only"
            *cmd_data = xgmac_get_rxipv4_upd_dckoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_GD_OCT_L: // Retrieve lower 32 bits of good IPv6 datagrams received "read only"
            *cmd_data = xgmac_get_rxipv6_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_HDR_ERR_OCT_L: // Retrieve lower 32 bits of octet datagram IPv6 with header error
                                                    // "read only"
            *cmd_data = xgmac_get_rxipv6_heoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_IPV6_NOPAYL_OCT_L: // Retrieve lower 32 bits of good IPv6 octet datagrans received NOT
                                                   // TCP:UDP: or ICMP "read only"
            *cmd_data = xgmac_get_rxipv6_npyld_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_UDP_GD_OCT_L: // Retrieve lower 32 bits of good UDP octet datagrams received "read only"
            *cmd_data = xgmac_get_rxudp_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_UDP_ERR_OCT_L: // Retrieve lower 32 bits of good UDP octet datagrams received with
                                               // checksum error "read only"
            *cmd_data = xgmac_get_rxudp_eckoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_TCP_GD_OCT_L: // Retrieve lower 32 bits of good TCP octet datagrams received "read only"
            *cmd_data = xgmac_get_rxtcp_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_TCP_ERR_OCT_L: // Retrieve lower 32 bits of good TCP octet datagrams received with
                                               // checksum error "read only"
            *cmd_data = xgmac_get_rxtcp_eckoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_ICMP_GD_OCT_L: // Retrieve lower 32 bits of good ICMP octet datagrams received "read
                                               // only"
            *cmd_data = xgmac_get_rxicmp_gdoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_GET_RX_ICMP_ERR_OCT_L: // Retrieve lower 32 bits of good ICMP octet datagrams received with
                                                // checksum error "read only"
            *cmd_data = xgmac_get_rxicmp_eckoct(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TX_CONFIG: // set MAC Transmit Configuration
            xgmac_set_tx_mac_config(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RX_CONFIG: // set MAC Receive Configuration
            xgmac_set_rx_mac_config(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PKT_FLTR: // set MAC Packet Filter Configuration
            xgmac_set_mac_pckt_filter(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_WD_JD_TOUT: // set MAC Watchdog and Jabber Timeout
            xgmac_set_mac_wdt_jb_tout(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_HSH_TREGO: // set MAC HASH Table REG0
            xgmac_set_mac_htbl_reg0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_HSH_TREG1: // set MAC HASH TAble REG1
            xgmac_set_mac_htbl_reg1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_VLAN_TCTRL: // set MAC MAC_VLAN_TAG_CTRL
            xgmac_set_mac_vlan_tctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_VLAN_HTBL: // set MAC VLAN HASH Table
            xgmac_set_mac_vlan_htbl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_VLAN_TDATA: // set MAC VLAN TAG Data
            xgmac_set_mac_vlan_tdata(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_VLAN_INCL: // set MAC VLAN Inclusion/Replacement register
            xgmac_set_mac_vlan_incl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_INN_VLAN_INCL: // set MAC Inner VLAN Inclusion register
            xgmac_set_mac_vlan_nincl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RX_ETH_TYPE: // set MAC receive Ethernet type match register
            xgmac_set_mac_rx_etmtch(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q0_TXFLW_CTRL: // set MAC Q0 transmit flow control register
            xgmac_set_mac_q0_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q1_TXFLW_CTRL: // set MAC Q1 transmit flow control register
            xgmac_set_mac_q1_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q2_TXFLW_CTRL: // set MAC Q2 transmit flow control register
            xgmac_set_mac_q2_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q3_TXFLW_CTRL: // set MAC Q3 transmit flow control register
            xgmac_set_mac_q3_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q4_TXFLW_CTRL: // set MAC Q4 transmit flow control register
            xgmac_set_mac_q4_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q5_TXFLW_CTRL: // set MAC Q5 transmit flow control register
            xgmac_set_mac_q5_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q6_TXFLW_CTRL: // set MAC Q6 transmit flow control register
            xgmac_set_mac_q6_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_Q7_TXFLW_CTRL: // set MAC Q7 transmit flow control register
            xgmac_set_mac_q7_fctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_MAX_RXFLW_CTRL: // set MAC Max receive flow control register
            xgmac_set_mac_max_rxfctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL4: // set MAC receive queue control 4 register
            xgmac_set_mac_rx_qctrl4(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL5: // set MAC receive queue control 5 register
            xgmac_set_mac_rx_qctrl5(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL0: // set MAC receive queue control 0 register
            xgmac_set_mac_rx_qctrl0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL1: // set MAC receive queue control 1 register
            xgmac_set_mac_rx_qctrl1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL2: // set MAC receive queue control 2 register
            xgmac_set_mac_rx_qctrl2(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_RXQ_CTRL3: // set MAC receive queue control 3 register
            xgmac_set_mac_rx_qctrl3(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_INT_ENABLE: // set MAC interrupt enable register
            xgmac_set_mac_int_en(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_LPI_CTRL_STS: // set MAC LPI control status register
            xgmac_set_mac_lpi_ctrl_sts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_LPI_TM_CTRL: // set MAC LPI timers control register
            xgmac_set_mac_lpi_tm_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_AUTO_ENTRY_TM: // set MAC LPI auto entry timer value "microseconds" register
            xgmac_set_mac_lpi_aet_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_US_TIC_CNTR: // set MAC register to control the generation of reference time in
                                              // "microseconds"
            xgmac_set_mac_tic_ucntr(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_EXT_CONFIG: // set MAC extended configuration register est operation mode of MAC
                                             // transmitter
            xgmac_set_mac_ext_cfg0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_EXT_CONFIG1: // set MAC register split mode control field
            xgmac_set_mac_ext_cfg1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FPE_CTRL_STS: // set MAC operation of frame preemption
            xgmac_set_mac_fpe_ctrl_sts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_CSR_SW_CTRL: // set MAC programmable controls for CSR
            xgmac_set_mac_csr_pg_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR0_HIGH: // set MAC address 0 high "upper 16 bits"
            xgmac_set_mac_haddr0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR0_LOW: // set MAC address 0 low "lower 32 bits"
            xgmac_set_mac_laddr0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR1_HIGH: // set MAC address 1 high "upper 16 bits"
            xgmac_set_mac_haddr1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR1_LOW: // set MAC address 1 low "lower 32 bits"
            xgmac_set_mac_laddr1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR2_HIGH: // set MAC address 2 high "upper 16 bits"
            xgmac_set_mac_haddr2(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR2_LOW: // set MAC address 2 low "lower 32 bits"
            xgmac_set_mac_laddr2(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR3_HIGH: // set MAC address 3 high "upper 16 bits"
            xgmac_set_mac_haddr3(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR3_LOW: // set MAC address 3 low "lower 32 bits"
            xgmac_set_mac_laddr3(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR4_HIGH: // set MAC address 4 high "upper 16 bits"
            xgmac_set_mac_haddr4(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR4_LOW: // set MAC address 4 low "lower 32 bits"
            xgmac_set_mac_laddr4(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR5_HIGH: // set MAC address 5 high "upper 16 bits"
            xgmac_set_mac_haddr5(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR5_LOW: // set MAC address 5 low "lower 32 bits"
            xgmac_set_mac_laddr5(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR6_HIGH: // set MAC address 6 high "upper 16 bits"
            xgmac_set_mac_haddr5(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR6_LOW: // set MAC address 6 low "lower 32 bits"
            xgmac_set_mac_laddr6(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR7_HIGH: // set MAC address 7 high "upper 16 bits"
            xgmac_set_mac_haddr7(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR7_LOW: // set MAC address 7 low "lower 32 bits"
            xgmac_set_mac_laddr7(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR8_HIGH: // set MAC address 8 high "upper 16 bits"
            xgmac_set_mac_haddr8(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR8_LOW: // set MAC address 8 low "lower 32 bits"
            xgmac_set_mac_laddr8(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR9_HIGH: // set MAC address 9 high "upper 16 bits"
            xgmac_set_mac_haddr9(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR9_LOW: // set MAC address 9 low "lower 32 bits"
            xgmac_set_mac_laddr9(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR10_HIGH: // set MAC address 10 high "upper 16 bits"
            xgmac_set_mac_haddr10(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR10_LOW: // set MAC address 10 low "lower 32 bits"
            xgmac_set_mac_laddr10(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR11_HIGH: // set MAC address 11 high "upper 16 bits"
            xgmac_set_mac_haddr11(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR11_LOW: // set MAC address 11 low "lower 32 bits"
            xgmac_set_mac_laddr11(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR12_HIGH: // set MAC address 12 high "upper 16 bits"
            xgmac_set_mac_haddr12(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR12_LOW: // set MAC address 12 low "lower 32 bits"
            xgmac_set_mac_laddr12(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR13_HIGH: // set MAC address 13 high "upper 16 bits"
            xgmac_set_mac_haddr13(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR13_LOW: // set MAC address 13 low "lower 32 bits"
            xgmac_set_mac_laddr13(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR14_HIGH: // set MAC address 14 high "upper 16 bits"
            xgmac_set_mac_haddr14(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR14_LOW: // set MAC address 14 low "lower 32 bits"
            xgmac_set_mac_laddr14(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR15_HIGH: // set MAC address 15 high "upper 16 bits"
            xgmac_set_mac_haddr15(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR15_LOW: // set MAC address 15 low "lower 32 bits"
            xgmac_set_mac_laddr15(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR16_HIGH: // set MAC address 16 high "upper 16 bits"
            xgmac_set_mac_haddr16(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR16_LOW: // set MAC address 16 low "lower 32 bits"
            xgmac_set_mac_laddr16(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR17_HIGH: // set MAC address 17 high "upper 16 bits"
            xgmac_set_mac_haddr17(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR17_LOW: // set MAC address 17 low "lower 32 bits"
            xgmac_set_mac_laddr17(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR18_HIGH: // set MAC address 18 high "upper 16 bits"
            xgmac_set_mac_haddr18(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR18_LOW: // set MAC address 18 low "lower 32 bits"
            xgmac_set_mac_laddr18(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR19_HIGH: // set MAC address 19 high "upper 16 bits"
            xgmac_set_mac_haddr19(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR19_LOW: // set MAC address 19 low "lower 32 bits"
            xgmac_set_mac_laddr19(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR20_HIGH: // set MAC address 20 high "upper 16 bits"
            xgmac_set_mac_haddr20(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR20_LOW: // set MAC address 20 low "lower 32 bits"
            xgmac_set_mac_laddr20(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR21_HIGH: // set MAC address 21 high "upper 16 bits"
            xgmac_set_mac_haddr21(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR21_LOW: // set MAC address 21 low "lower 32 bits"
            xgmac_set_mac_laddr21(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR22_HIGH: // set MAC address 22 high "upper 16 bits"
            xgmac_set_mac_haddr22(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR22_LOW: // set MAC address 22 low "lower 32 bits"
            xgmac_set_mac_laddr22(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR23_HIGH: // set MAC address 23 high "upper 16 bits"
            xgmac_set_mac_haddr23(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR23_LOW: // set MAC address 23 low "lower 32 bits"
            xgmac_set_mac_laddr23(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR24_HIGH: // set MAC address 24 high "upper 16 bits"
            xgmac_set_mac_haddr24(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR24_LOW: // set MAC address 24 low "lower 32 bits"
            xgmac_set_mac_laddr24(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR25_HIGH: // set MAC address 25 high "upper 16 bits"
            xgmac_set_mac_haddr25(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR25_LOW: // set MAC address 25 low "lower 32 bits"
            xgmac_set_mac_laddr25(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR26_HIGH: // set MAC address 26 high "upper 16 bits"
            xgmac_set_mac_haddr26(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR26_LOW: // set MAC address 26 low "lower 32 bits"
            xgmac_set_mac_laddr26(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR27_HIGH: // set MAC address 27 high "upper 16 bits"
            xgmac_set_mac_haddr27(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR27_LOW: // set MAC address 27 low "lower 32 bits"
            xgmac_set_mac_laddr27(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR28_HIGH: // set MAC address 28 high "upper 16 bits"
            xgmac_set_mac_haddr28(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR28_LOW: // set MAC address 28 low "lower 32 bits"
            xgmac_set_mac_laddr28(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR29_HIGH: // set MAC address 29 high "upper 16 bits"
            xgmac_set_mac_haddr29(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR29_LOW: // set MAC address 29 low "lower 32 bits"
            xgmac_set_mac_laddr29(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR30_HIGH: // set MAC address 30 high "upper 16 bits"
            xgmac_set_mac_haddr30(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR30_LOW: // set MAC address 30 low "lower 32 bits"
            xgmac_set_mac_laddr30(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR31_HIGH: // set MAC address 31 high "upper 16 bits"
            xgmac_set_mac_haddr31(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_FADDR31_LOW: // set MAC address 31 low "lower 32 bits"
            xgmac_set_mac_laddr31(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_IND_ACTRL: // set MAC indirect access control of MAC
            xgmac_set_mac_ind_actrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_IND_ADATA: // set MAC indirect access data of MAC
            xgmac_set_mac_ind_adata(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_L3_L4_ADDR_CTRL: // set indirect address and control for layer 3/4 filter
            xgmac_set_mac_l3_l4_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_L3_L4_ADDR_DATA: // set indirect data and control for layer 3/4 filter
            xgmac_set_mac_l3_l4_data(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_ARP_ADDR: // set arp address register IPV4 destination address
            xgmac_set_mac_arp_addr(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TSTMP_CTRL: // set system time generator register
            xgmac_set_mac_tmstamp_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SSEC_INCR: // set IEEE 1588 timestamp governed feature for sub second increment
                                            // register
            xgmac_set_mac_tmstamp_ssec(base_add, *cmd_data);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_SET_MAC_SYS_TM_SEC_UPDT: // set system time seconds
            xgmac_set_mac_systu_sec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SYS_TM_NSEC_UPDT: // set system time nano seconds
            xgmac_set_mac_systu_nsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SYS_TMTMP_ADDEND: // set timestamp addend register "present only when 1588 timestamp
                                                   // feature is selected"
            xgmac_set_mac_tmstamp_addend(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SYS_TM_HWORD_SEC: // set timestamp higher word seconds register "present only when 1588
                                                   // timestamp feature is selected"
            xgmac_set_mac_tmstamp_hsword(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_AUX_CTRL: // set auxillary timestamp control register "snapshot"
            xgmac_set_mac_aux_tctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_ASYM_CORR: // set mac timestamp ingress asymmetry correction register
            xgmac_set_mac_tmstamp_ingress(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_ASYM_CORR: // set mac timestamp egress asymmetry correction register
            xgmac_set_mac_tmstamp_egress(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_CORR_NSEC: // set mac timestamp ingress correction nanosecond register
            xgmac_set_mac_ingress_cor_nsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_CORR_SNSEC: // set mac timestamp ingress correction sub-nanosecond register
            xgmac_set_mac_ingress_cor_snsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_CORR_NSEC: // set mac timestamp egress correction nanosecond register
            xgmac_set_mac_egress_cor_nsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_CORR_SNSEC: // set mac timestamp egress correction sub-nanosecond register
            xgmac_set_mac_egress_cor_snsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS_CTRL: // set mac pps control register "only when timestamp feature is selected no
                                           // external timestamp"
            xgmac_set_mac_pps_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS0_TRG_SEC: // set mac PPS0 target time seconds register
            xgmac_set_mac_pps0_tgt_sec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS0_TRG_NSEC: // set mac PPS0 target time nano seconds register
            xgmac_set_mac_pps0_tgt_nsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS0_INTV: // set mac PPS0 interval register "number of sub-second icrement value
                                            // between rising edges"
            xgmac_set_mac_pps0_intv(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS0_WIDTH: // set mac PPS0 with register "number of sub-second icrement value between
                                             // rising & falaling edges"
            xgmac_set_mac_pps0_width(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS1_TRG_SEC: // set mac PPS1 target time seconds register
            xgmac_set_mac_pps1_tgt_sec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS1_TRG_NSEC: // set mac PPS1 target time nano seconds register
            xgmac_set_mac_pps1_tgt_nsec(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS1_INTV: // set mac PPS1 interval register "number of sub-second icrement value
                                            // between rising edges"
            xgmac_set_mac_pps1_intv(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PPS1_WIDTH: // set mac PPS1 with register "number of sub-second icrement value between
                                             // rising & falaling edges"
            xgmac_set_mac_pps1_width(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_PTO_CTRL: // set mac PTP offload engine operation "ptp timestamp offload feature
                                           // selected"
            xgmac_set_mac_pto_ctrl(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN0: // set mac part 1 of 80 bit port identity of the PTP node
            xgmac_set_mac_port_id0(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN1: // set mac part 2 of 80 bit port identity of the PTP node
            xgmac_set_mac_port_id1(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN2: // set mac part 3 of 80 bit port identity of the PTP node
            xgmac_set_mac_port_id2(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MAC_LOG_MSG_INTV: // set mac register contains periodic intervalsfor automatic PTP packet
                                               // generation
            xgmac_set_mac_ptp_aintv(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_SGL_CMD_ADDR: // set MDIO address of ports: devices and registers by the SMA
            xgmac_set_mdio_sgl_cmd_addr(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA: // set MDIO DATA of ports: devices and registers
            xgmac_set_mdio_sgl_cmd_data(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_CONT_WR_ADDR: // set MDIO program to start continuous write operation
            xgmac_set_mdio_cnt_wr_addr(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_CONT_WR_DATA: // set MDIO data to be written during continuous write operation
            xgmac_set_mdio_cnt_wr_data(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_CONT_SCAN_PEN: // set MDIO control for PHY ports and corresponding devicesss
            xgmac_set_mdio_sctn_pen(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_INT_STATUS: // set MDIO source of SMA interrupt "read only"
            xgmac_set_mdio_sma_int_sts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_INT_ENABLE: // set MDIO Interrupt Enable
            xgmac_set_mdio_sma_int_en(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORT_CON_DISC_STS: // set MDIO hot plug in status for port 0-31 "read only"
            xgmac_set_mdio_conn_disc_sts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_CLS22_PORT: // set MDIO configuration of SMA to access PHY ports
            xgmac_set_mdio_cl22_port(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORT_NX4_IND_CTRL: // set MDIO fields for controling port range select
            xgmac_set_mdio_port_rng_sel(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORTNX4P0_INUSE: // set MDIO status of each device on port nx4 plus 0
            xgmac_set_mdio_nx4_p0_dsts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORTNX4P1_INUSE: // set MDIO status of each device on port nx4 plus 1
            xgmac_set_mdio_nx4_p1_dsts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORTNX4P2_INUSE: // set MDIO status of each device on port nx4 plus 2
            xgmac_set_mdio_nx4_p2_dsts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MDIO_PORTNX4P3_INUSE: // set MDIO status of each device on port nx4 plus 3
            xgmac_set_mdio_nx4_p3_dsts(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MMC_CTRL: // set MMC control register
            xgmac_set_mmc_ctrl_reg(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MMC_RX_INT_EN: // set MMC receive interrupt enable register
            xgmac_set_mmc_rx_int_en(base_add, *cmd_data);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_SET_MMC_TX_INT_EN: // set MMC transmit interrupt enable
            xgmac_set_mmc_tx_int_en(base_add, *cmd_data);
            ret_val = 0;
            break;
        /* CORE IOCTL CALLS END */

        /* MTL IOCTL CALL START */
        /* MTL READ ELEMENT START */
        case IOCTL_XGMAC_MTL_GET_MTL_OP_MODE:
            *cmd_data = xgmac_mtl_get_opmode(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_INT_STS:
            *cmd_data = xgmac_mtl_get_int_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ_DMAP0:
            *cmd_data = xgmac_mtl_get_rxq_dmap0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ_DMAP1:
            *cmd_data = xgmac_mtl_get_rxq_dmap1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC_PRTY_MAP0:
            *cmd_data = xgmac_mtl_get_tc_pmap0(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC_PRTY_MAP1:
            *cmd_data = xgmac_mtl_get_tc_pmap1(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TBS_CTRL:
            *cmd_data = xgmac_mtl_get_tbs_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TBS_STS:
            *cmd_data = xgmac_mtl_get_tbs_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_CTRL:
            *cmd_data = xgmac_mtl_get_est_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_OHD:
            *cmd_data = xgmac_mtl_get_est_ohead(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_STS:
            *cmd_data = xgmac_mtl_get_est_sts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_SCH_ERROR:
            *cmd_data = xgmac_mtl_get_est_scerror(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_FSZ_ERROR:
            *cmd_data = xgmac_mtl_get_est_fsz_error(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_FSZ_CPTR:
            *cmd_data = xgmac_mtl_get_est_cptr_efsze(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_EST_INT_EN:
            *cmd_data = xgmac_mtl_get_est_intr_en(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_GCL_CTRL:
            *cmd_data = xgmac_mtl_get_gcl_ctrl(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_GCL_DATA:
            *cmd_data = xgmac_mtl_get_gcl_data(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_FPE_CSTS:
            *cmd_data = xgmac_mtl_get_fpe_csts(base_add);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_FPE_ADV:
            *cmd_data = xgmac_mtl_get_fpe_adv(base_add);
            ret_val = 0;
            break;

        /* TC QUEUE 0-7 READ METHODS Start */
        case IOCTL_XGMAC_MTL_GET_TXQ0_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ1_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ2_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ3_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ4_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ5_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ6_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ7_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ0_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ1_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ2_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ3_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ4_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ5_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ6_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TXQ7_UFLW:
            *cmd_data = xgmac_mtl_get_tcq_tx_uflow(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ0_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ1_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ2_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ3_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ4_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ5_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ6_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TXQ7_DBG:
            *cmd_data = xgmac_mtl_get_tcq_tx_dbg(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC0_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC1_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC2_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC3_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC4_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC5_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC6_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC7_ETS_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC0_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC1_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC2_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC3_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC4_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC5_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC6_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC7_ETS_STS:
            *cmd_data = xgmac_mtl_get_tcq_ets_sts(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC0_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC1_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC2_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC3_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC4_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC5_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC6_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_TC7_QWEIGHT:
            *cmd_data = xgmac_mtl_get_tcq_qwght(base_add, TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_RXQ0_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ1_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ2_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ3_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ4_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ5_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ6_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ7_OP_MODE:
            *cmd_data = xgmac_mtl_get_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_RXQ0_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ1_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ2_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ3_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ4_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ5_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ6_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ7_MPKT_OCNT:
            *cmd_data = xgmac_mtl_get_tcq_rx_mpocnt(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_RXQ0_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ1_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ2_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ3_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ4_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ5_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ6_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ7_DBG:
            *cmd_data = xgmac_mtl_get_tcq_rx_dbg(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_RXQ0_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ1_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ2_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ3_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ4_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ5_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ6_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ7_CTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_RXQ0_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ1_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ2_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ3_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ4_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ5_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ6_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_RXQ7_FCTRL:
            *cmd_data = xgmac_mtl_get_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_Q0_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q1_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q2_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q3_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q4_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q5_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q6_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q7_INT_EN:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_Q0_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE0);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q1_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE1);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q2_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE2);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q3_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE3);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q4_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE4);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q5_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE5);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q6_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE6);
            ret_val = 0;
            break;
        case IOCTL_XGMAC_MTL_GET_Q7_INT_STS:
            *cmd_data = xgmac_mtl_get_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE7);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC7_SSCREDIT:
            *cmd_data = xgmac_mtl_get_q7_slope_credit(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC7_HCREDIT:
            *cmd_data = xgmac_mtl_get_q7_high_credit(base_add);
            ret_val = 0;
            break;

        case IOCTL_XGMAC_MTL_GET_TC7_LCREDIT:
            *cmd_data = xgmac_mtl_get_q7_low_credit(base_add);
            ret_val = 0;
            break;
        /* TC QUEUE 0-7 READ METHODS End */
        /* MTL READ METHODS END */

        /* MTL SET METHODS START */
        case IOCTL_XGMAC_MTL_SET_MTL_OP_MODE:
            ret_val = xgmac_mtl_set_opmode(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ_DMAP0:
            ret_val = xgmac_mtl_set_rxq_dmap0(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ_DMAP1:
            ret_val = xgmac_mtl_set_rxq_dmap1(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC_PRTY_MAP0:
            ret_val = xgmac_mtl_set_tc_pmap0(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC_PRTY_MAP1:
            ret_val = xgmac_mtl_set_tc_pmap1(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TBS_CTRL:
            ret_val = xgmac_mtl_set_tbs_ctrl(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TBS_STS:
            ret_val = xgmac_mtl_set_tbs_sts(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_CTRL:
            ret_val = xgmac_mtl_set_est_ctrl(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_OHD:
            ret_val = xgmac_mtl_set_est_ohead(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_STS:
            ret_val = xgmac_mtl_set_est_sts(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_SCH_ERROR:
            ret_val = xgmac_mtl_set_est_scerror(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_FSZ_ERROR:
            ret_val = xgmac_mtl_set_est_fsz_error(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_EST_INT_EN:
            ret_val = xgmac_mtl_set_est_intr_en(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_GCL_CTRL:
            ret_val = xgmac_mtl_set_gcl_ctrl(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_GCL_DATA:
            ret_val = xgmac_mtl_set_gcl_data(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_FPE_CSTS:
            ret_val = xgmac_mtl_set_fpe_csts(base_add, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_FPE_ADV:
            ret_val = xgmac_mtl_set_fpe_adv(base_add, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_TXQ0_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ1_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ2_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ3_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ4_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ5_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ6_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TXQ7_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_tx_opmode(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_TC0_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC1_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC2_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC3_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC4_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC5_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC6_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC7_ETS_CTRL:
            ret_val = xgmac_mtl_set_tcq_ets_ctrl(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_TC0_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC1_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC2_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC3_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC4_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC5_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC6_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_TC7_QWEIGHT:
            ret_val = xgmac_mtl_set_tcq_qwght(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_RXQ0_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ1_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ2_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ3_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ4_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ5_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ6_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ7_OP_MODE:
            ret_val = xgmac_mtl_set_tcq_rx_opmode(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_RXQ0_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ1_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ2_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ3_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ4_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ5_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ6_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ7_CTRL:
            ret_val = xgmac_mtl_set_tcq_rx_ctrl(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_RXQ0_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ1_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ2_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ3_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ4_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ5_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ6_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_RXQ7_FCTRL:
            ret_val = xgmac_mtl_set_tcq_rx_fctrl(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_Q0_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q1_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q2_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q3_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q4_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q5_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q6_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q7_INT_EN:
            ret_val = xgmac_mtl_set_tcq_queue_int_en(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;

        case IOCTL_XGMAC_MTL_SET_Q0_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE0, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q1_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE1, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q2_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE2, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q3_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE3, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q4_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE4, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q5_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE5, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q6_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE6, *cmd_data);
            break;
        case IOCTL_XGMAC_MTL_SET_Q7_INT_STS:
            ret_val = xgmac_mtl_set_tcq_queue_int_sts(base_add, (uint32_t)TCQ_QUEUE7, *cmd_data);
            break;
        /* MTL IOCTL CALLS END */

        /* DMA IOCTL CALLS START */
        case IOCTL_XGMAC_GET_DMA_MODE:
            ret_val = xgmac_get_dma_mode(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_MODE:
            ret_val = xgmac_set_dma_mode(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_SYSBUS_MODE:
            ret_val = xgmac_get_dma_sysbus_mode(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_SYSBUS_MODE:
            ret_val = xgmac_set_dma_sysbus_mode(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_INTERRUPT_STATUS:
            ret_val = xgmac_get_dma_interrupt_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_INTERRUPT_STATUS:
            ret_val = xgmac_set_dma_interrupt_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_AXI_TX_AR_ACE_CONTROL:
            ret_val = xgmac_get_dma_axi_tx_ar_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_AXI_TX_AR_ACE_CONTROL:
            ret_val = xgmac_set_dma_axi_tx_ar_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_AXI_RX_AW_ACE_CONTROL:
            ret_val = xgmac_get_dma_axi_rx_aw_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_AXI_RX_AW_ACE_CONTROL:
            ret_val = xgmac_set_dma_axi_rx_aw_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_AXI_TXRX_AWAR_ACE_CONTROL:
            ret_val = xgmac_get_dma_axi_txrx_awar_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_AXI_TXRX_AWAR_ACE_CONTROL:
            ret_val = xgmac_set_dma_axi_txrx_awar_ace_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_DEBUG_STATUS0:
            ret_val = xgmac_get_dma_debug_status0(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_DEBUG_STATUS0:
            ret_val = xgmac_set_dma_debug_status0(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_DEBUG_STATUS1:
            ret_val = xgmac_get_dma_debug_status1(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_DEBUG_STATUS1:
            ret_val = xgmac_set_dma_debug_status1(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_DEBUG_STATUS3:
            ret_val = xgmac_get_dma_debug_status3(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_DEBUG_STATUS3:
            ret_val = xgmac_set_dma_debug_status3(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_TX_EDMA_CONTROL:
            ret_val = xgmac_get_dma_tx_edma_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_TX_EDMA_CONTROL:
            ret_val = xgmac_set_dma_tx_edma_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_RX_EDMA_CONTROL:
            ret_val = xgmac_get_dma_rx_edma_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_RX_EDMA_CONTROL:
            ret_val = xgmac_set_dma_rx_edma_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_AXI_LPI_ENTRY_INTERVAL:
            ret_val = xgmac_get_dma_axi_lpi_entry_interval(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_AXI_LPI_ENTRY_INTERVAL:
            ret_val = xgmac_set_dma_axi_lpi_entry_interval(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_TBS_CONTROL0:
            ret_val = xgmac_get_dma_tbs_control0(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_TBS_CONTROL0:
            ret_val = xgmac_set_dma_tbs_control0(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_TBS_CONTROL1:
            ret_val = xgmac_get_dma_tbs_control1(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_TBS_CONTROL1:
            ret_val = xgmac_set_dma_tbs_control1(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_TBS_CONTROL2:
            ret_val = xgmac_get_dma_tbs_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_TBS_CONTROL2:
            ret_val = xgmac_set_dma_tbs_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_TBS_CONTROL3:
            ret_val = xgmac_get_dma_tbs_control3(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_TBS_CONTROL3:
            ret_val = xgmac_set_dma_tbs_control3(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH_IND_CTRL:
            ret_val = xgmac_get_dma_ch_ind_ctrl(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH_IND_CTRL:
            ret_val = xgmac_set_dma_ch_ind_ctrl(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH_IND_DATA:
            ret_val = xgmac_get_dma_ch_ind_data(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH_IND_DATA:
            ret_val = xgmac_set_dma_ch_ind_data(base_add, user_data, length);
            break;

        // DMA Channel 0
        case IOCTL_XGMAC_GET_DMA_CH0_CONTROL:
            ret_val = xgmac_get_dma_ch0_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CONTROL:
            ret_val = xgmac_set_dma_ch0_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TX_CONTROL:
            ret_val = xgmac_get_dma_ch0_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL:
            ret_val = xgmac_set_dma_ch0_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RX_CONTROL:
            ret_val = xgmac_get_dma_ch0_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL:
            ret_val = xgmac_set_dma_ch0_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch0_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch0_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch0_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch0_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch0_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch0_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch0_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch0_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch0_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch0_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch0_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch0_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch0_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch0_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch0_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch0_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch0_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch0_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch0_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch0_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch0_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch0_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch0_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch0_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch0_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch0_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch0_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch0_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch0_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch0_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch0_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch0_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch0_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch0_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_STATUS:
            ret_val = xgmac_get_dma_ch0_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_STATUS:
            ret_val = xgmac_set_dma_ch0_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch0_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch0_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch0_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch0_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch0_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch0_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch0_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch0_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch0_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch0_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch0_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch0_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH0_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch0_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH0_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch0_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 1
        case IOCTL_XGMAC_GET_DMA_CH1_CONTROL:
            ret_val = xgmac_get_dma_ch1_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CONTROL:
            ret_val = xgmac_set_dma_ch1_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TX_CONTROL:
            ret_val = xgmac_get_dma_ch1_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TX_CONTROL:
            ret_val = xgmac_set_dma_ch1_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RX_CONTROL:
            ret_val = xgmac_get_dma_ch1_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RX_CONTROL:
            ret_val = xgmac_set_dma_ch1_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch1_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch1_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch1_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch1_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch1_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch1_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch1_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch1_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch1_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch1_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch1_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch1_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch1_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch1_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch1_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch1_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch1_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch1_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch1_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch1_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch1_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch1_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch1_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch1_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch1_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch1_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch1_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch1_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch1_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch1_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch1_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch1_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch1_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch1_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_STATUS:
            ret_val = xgmac_get_dma_ch1_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_STATUS:
            ret_val = xgmac_set_dma_ch1_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch1_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch1_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch1_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch1_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch1_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch1_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch1_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch1_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch1_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch1_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch1_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch1_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH1_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch1_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH1_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch1_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 2
        case IOCTL_XGMAC_GET_DMA_CH2_CONTROL:
            ret_val = xgmac_get_dma_ch2_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CONTROL:
            ret_val = xgmac_set_dma_ch2_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TX_CONTROL:
            ret_val = xgmac_get_dma_ch2_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TX_CONTROL:
            ret_val = xgmac_set_dma_ch2_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RX_CONTROL:
            ret_val = xgmac_get_dma_ch2_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RX_CONTROL:
            ret_val = xgmac_set_dma_ch2_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch2_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch2_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch2_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch2_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch2_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch2_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch2_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch2_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch2_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch2_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch2_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch2_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch2_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch2_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch2_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch2_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch2_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch2_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch2_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch2_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch2_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch2_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch2_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch2_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch2_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch2_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch2_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch2_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch2_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch2_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch2_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch2_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch2_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch2_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_STATUS:
            ret_val = xgmac_get_dma_ch2_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_STATUS:
            ret_val = xgmac_set_dma_ch2_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch2_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch2_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch2_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch2_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch2_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch2_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch2_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch2_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch2_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch2_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch2_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch2_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH2_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch2_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH2_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch2_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 3
        case IOCTL_XGMAC_GET_DMA_CH3_CONTROL:
            ret_val = xgmac_get_dma_ch3_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CONTROL:
            ret_val = xgmac_set_dma_ch3_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TX_CONTROL:
            ret_val = xgmac_get_dma_ch3_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TX_CONTROL:
            ret_val = xgmac_set_dma_ch3_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RX_CONTROL:
            ret_val = xgmac_get_dma_ch3_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RX_CONTROL:
            ret_val = xgmac_set_dma_ch3_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch3_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch3_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch3_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch3_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch3_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch3_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch3_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch3_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch3_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch3_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch3_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch3_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch3_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch3_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch3_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch3_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch3_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch3_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch3_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch3_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch3_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch3_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch3_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch3_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch3_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch3_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch3_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch3_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch3_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch3_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch3_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch3_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch3_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch3_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_STATUS:
            ret_val = xgmac_get_dma_ch3_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_STATUS:
            ret_val = xgmac_set_dma_ch3_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch3_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch3_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch3_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch3_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch3_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch3_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch3_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch3_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch3_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch3_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch3_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch3_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH3_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch3_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH3_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch3_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 4
        case IOCTL_XGMAC_GET_DMA_CH4_CONTROL:
            ret_val = xgmac_get_dma_ch4_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CONTROL:
            ret_val = xgmac_set_dma_ch4_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TX_CONTROL:
            ret_val = xgmac_get_dma_ch4_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TX_CONTROL:
            ret_val = xgmac_set_dma_ch4_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RX_CONTROL:
            ret_val = xgmac_get_dma_ch4_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RX_CONTROL:
            ret_val = xgmac_set_dma_ch4_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch4_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch4_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch4_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch4_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch4_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch4_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch4_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch4_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch4_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch4_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch4_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch4_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch4_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch4_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch4_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch4_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch4_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch4_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch4_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch4_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch4_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch4_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch4_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch4_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch4_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch4_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch4_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch4_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch4_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch4_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch4_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch4_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch4_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch4_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_STATUS:
            ret_val = xgmac_get_dma_ch4_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_STATUS:
            ret_val = xgmac_set_dma_ch4_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch4_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch4_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch4_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch4_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch4_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch4_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch4_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch4_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch4_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch4_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch4_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch4_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH4_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch4_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH4_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch4_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 5
        case IOCTL_XGMAC_GET_DMA_CH5_CONTROL:
            ret_val = xgmac_get_dma_ch5_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CONTROL:
            ret_val = xgmac_set_dma_ch5_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TX_CONTROL:
            ret_val = xgmac_get_dma_ch5_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TX_CONTROL:
            ret_val = xgmac_set_dma_ch5_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RX_CONTROL:
            ret_val = xgmac_get_dma_ch5_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RX_CONTROL:
            ret_val = xgmac_set_dma_ch5_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch5_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch5_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch5_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch5_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch5_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch5_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch5_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch5_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch5_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch5_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch5_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch5_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch5_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch5_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch5_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch5_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch5_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch5_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch5_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch5_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch5_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch5_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch5_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch5_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch5_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch5_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch5_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch5_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch5_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch5_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch5_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch5_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch5_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch5_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_STATUS:
            ret_val = xgmac_get_dma_ch5_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_STATUS:
            ret_val = xgmac_set_dma_ch5_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch5_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch5_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch5_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch5_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch5_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch5_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch5_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch5_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch5_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch5_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch5_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch5_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH5_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch5_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH5_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch5_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 6
        case IOCTL_XGMAC_GET_DMA_CH6_CONTROL:
            ret_val = xgmac_get_dma_ch6_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CONTROL:
            ret_val = xgmac_set_dma_ch6_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TX_CONTROL:
            ret_val = xgmac_get_dma_ch6_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TX_CONTROL:
            ret_val = xgmac_set_dma_ch6_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RX_CONTROL:
            ret_val = xgmac_get_dma_ch6_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RX_CONTROL:
            ret_val = xgmac_set_dma_ch6_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch6_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch6_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch6_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch6_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch6_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch6_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch6_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch6_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch6_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch6_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch6_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch6_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch6_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch6_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch6_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch6_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch6_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch6_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch6_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch6_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch6_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch6_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch6_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch6_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch6_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch6_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch6_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch6_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch6_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch6_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch6_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch6_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch6_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch6_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_STATUS:
            ret_val = xgmac_get_dma_ch6_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_STATUS:
            ret_val = xgmac_set_dma_ch6_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch6_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch6_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch6_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch6_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch6_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch6_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch6_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch6_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch6_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch6_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch6_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch6_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH6_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch6_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH6_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch6_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        // DMA Channel 7
        case IOCTL_XGMAC_GET_DMA_CH7_CONTROL:
            ret_val = xgmac_get_dma_ch7_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CONTROL:
            ret_val = xgmac_set_dma_ch7_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TX_CONTROL:
            ret_val = xgmac_get_dma_ch7_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TX_CONTROL:
            ret_val = xgmac_set_dma_ch7_tx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RX_CONTROL:
            ret_val = xgmac_get_dma_ch7_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RX_CONTROL:
            ret_val = xgmac_set_dma_ch7_rx_control(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_get_dma_ch7_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_SLOT_FUNCTION_CONTROL_STATUS:
            ret_val = xgmac_set_dma_ch7_slot_function_control_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch7_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch7_txdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch7_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch7_txdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_get_dma_ch7_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RXDESC_LIST_HADDRESS:
            ret_val = xgmac_set_dma_ch7_rxdesc_list_haddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_get_dma_ch7_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RXDESC_LIST_LADDRESS:
            ret_val = xgmac_set_dma_ch7_rxdesc_list_laddress(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch7_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch7_txdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_get_dma_ch7_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RXDESC_TAIL_LPOINTER:
            ret_val = xgmac_set_dma_ch7_rxdesc_tail_lpointer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TX_CONTROL2:
            ret_val = xgmac_get_dma_ch7_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TX_CONTROL2:
            ret_val = xgmac_set_dma_ch7_tx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RX_CONTROL2:
            ret_val = xgmac_get_dma_ch7_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RX_CONTROL2:
            ret_val = xgmac_set_dma_ch7_rx_control2(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_INTERRUPT_ENABLE:
            ret_val = xgmac_get_dma_ch7_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_INTERRUPT_ENABLE:
            ret_val = xgmac_set_dma_ch7_interrupt_enable(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_get_dma_ch7_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RX_INTERRUPT_WATCHDOG_TIMER:
            ret_val = xgmac_set_dma_ch7_rx_interrupt_watchdog_timer(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_get_dma_ch7_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXDESC_L:
            ret_val = xgmac_set_dma_ch7_current_app_txdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_get_dma_ch7_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXDESC_L:
            ret_val = xgmac_set_dma_ch7_current_app_rxdesc_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_get_dma_ch7_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXBUFFER_H:
            ret_val = xgmac_set_dma_ch7_current_app_txbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_get_dma_ch7_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXBUFFER_L:
            ret_val = xgmac_set_dma_ch7_current_app_txbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_get_dma_ch7_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXBUFFER_H:
            ret_val = xgmac_set_dma_ch7_current_app_rxbuffer_h(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_get_dma_ch7_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXBUFFER_L:
            ret_val = xgmac_set_dma_ch7_current_app_rxbuffer_l(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_STATUS:
            ret_val = xgmac_get_dma_ch7_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_STATUS:
            ret_val = xgmac_set_dma_ch7_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_DEBUG_STATUS:
            ret_val = xgmac_get_dma_ch7_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_DEBUG_STATUS:
            ret_val = xgmac_set_dma_ch7_debug_status(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_get_dma_ch7_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_DESC_MEM_CACHE_FILL_LEVEL:
            ret_val = xgmac_set_dma_ch7_desc_mem_cache_fill_level(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_MISS_PACKET_CNT:
            ret_val = xgmac_get_dma_ch7_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_MISS_PACKET_CNT:
            ret_val = xgmac_set_dma_ch7_miss_packet_cnt(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch7_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch7_tx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch7_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RX_DATA_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch7_rx_data_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch7_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_TX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch7_tx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_GET_DMA_CH7_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_get_dma_ch7_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;
        case IOCTL_XGMAC_SET_DMA_CH7_RX_DESC_XFER_RING_OFFSET:
            ret_val = xgmac_set_dma_ch7_rx_desc_xfer_ring_offset(base_add, user_data, length);
            break;

        default:
            // Invalid IOCTL COMMAND FOR XGMAC
            ret_val = -3;
            break;
        } // Switch case End
    }     // End if/else
    return ret_val;
}
int32_t s_xgmac_error(int32_t base_add) { return -1; }
