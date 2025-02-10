#ifndef XGMAC_H__
#define XGMAC_H__

#include <stddef.h>
#include <stdint.h>

// DEFINES FOR QUEUE'S
#define TCQ_QUEUE0 0
#define TCQ_QUEUE1 1
#define TCQ_QUEUE2 2
#define TCQ_QUEUE3 3
#define TCQ_QUEUE4 4
#define TCQ_QUEUE5 5
#define TCQ_QUEUE6 6
#define TCQ_QUEUE7 7

// IOCTL commands for getting and setting XGMAC registers
typedef enum {
    /* READ ACCES RELATED CALLS START */
    // IOCTL DWCXG_CORE ELEMENTS
    IOCTL_XGMAC_GET_MAC_TX_CONFIG,       // Retrieve MAC Transmit Configuration
    IOCTL_XGMAC_GET_MAC_RX_CONFIG,       // Retrieve MAC Receive Configuration
    IOCTL_XGMAC_GET_MAC_PKT_FLTR,        // Retrieve MAC Packet Filter Configuration
    IOCTL_XGMAC_GET_MAC_WD_JD_TOUT,      // Retrieve MAC Watchdog and Jabber Timeout
    IOCTL_XGMAC_GET_MAC_HSH_TREGO,       // Retrieve MAC HASH Table REG0
    IOCTL_XGMAC_GET_MAC_HSH_TREG1,       // Retrieve MAC HASH TAble REG1
    IOCTL_XGMAC_GET_MAC_VLAN_TCTRL,      // Retrieve MAC MAC_VLAN_TAG_CTRL
    IOCTL_XGMAC_GET_MAC_VLAN_HTBL,       // Retrieve MAC VLAN HASH Table
    IOCTL_XGMAC_GET_MAC_VLAN_TDATA,      // Retrieve MAC VLAN TAG Data
    IOCTL_XGMAC_GET_MAC_VLAN_INCL,       // Retrieve MAC VLAN Inclusion/Replacement register
    IOCTL_XGMAC_GET_MAC_INN_VLAN_INCL,   // Retrieve MAC Inner VLAN Inclusion register
    IOCTL_XGMAC_GET_MAC_RX_ETH_TYPE,     // Retrieve MAC receive Ethernet type match register
    IOCTL_XGMAC_GET_MAC_Q0_TXFLW_CTRL,   // Retrieve MAC Q0 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q1_TXFLW_CTRL,   // Retrieve MAC Q1 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q2_TXFLW_CTRL,   // Retrieve MAC Q2 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q3_TXFLW_CTRL,   // Retrieve MAC Q3 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q4_TXFLW_CTRL,   // Retrieve MAC Q4 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q5_TXFLW_CTRL,   // Retrieve MAC Q5 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q6_TXFLW_CTRL,   // Retrieve MAC Q6 transmit flow control register
    IOCTL_XGMAC_GET_MAC_Q7_TXFLW_CTRL,   // Retrieve MAC Q7 transmit flow control register
    IOCTL_XGMAC_GET_MAC_MAX_RXFLW_CTRL,  // Retrieve MAC Max receive flow control register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL4,       // Retrieve MAC receive queue control 4 register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL5,       // Retrieve MAC receive queue control 5 register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL0,       // Retrieve MAC receive queue control 0 register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL1,       // Retrieve MAC receive queue control 1 register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL2,       // Retrieve MAC receive queue control 2 register
    IOCTL_XGMAC_GET_MAC_RXQ_CTRL3,       // Retrieve MAC receive queue control 3 register
    IOCTL_XGMAC_GET_MAC_INT_STATUS,      // Retrieve MAC interrupt status register  "read only"
    IOCTL_XGMAC_GET_MAC_INT_ENABLE,      // Retrieve MAC interrupt enable register
    IOCTL_XGMAC_GET_MAC_RX_TX_STATUS,    // Retrieve MAC receive/transmit status register "read only"
    IOCTL_XGMAC_GET_MAC_LPI_CTRL_STS,    // Retrieve MAC LPI control status register
    IOCTL_XGMAC_GET_MAC_LPI_TM_CTRL,     // Retrieve MAC LPI timers control register
    IOCTL_XGMAC_GET_MAC_AUTO_ENTRY_TM,   // Retrieve MAC LPI auto entry timer value "microseconds" register
    IOCTL_XGMAC_GET_MAC_US_TIC_CNTR,     // Retrieve MAC register to control the generation of reference time in
                                         // "microseconds"
    IOCTL_XGMAC_GET_MAC_VERSION,         // Retrieve MAC version register "read only"
    IOCTL_XGMAC_GET_MAC_DEBUG,           // Retrieve MAC debug register "read only"
    IOCTL_XGMAC_GET_MAC_HW_FEAT0,        // Retrieve MAC feature 0 presence indicator register "read only"
    IOCTL_XGMAC_GET_MAC_HW_FEAT1,        // Retrieve MAC feature 1 presence indicator register "read only"
    IOCTL_XGMAC_GET_MAC_HW_FEAT2,        // Retrieve MAC feature 2 presence indicator register "read only"
    IOCTL_XGMAC_GET_MAC_HW_FEAT3,        // Retrieve MAC feature 3 presence indicator register "read only"
    IOCTL_XGMAC_GET_MAC_HW_FEAT4,        // Retrieve MAC feature 2 presence indicator register "read only"
    IOCTL_XGMAC_GET_MAC_EXT_CONFIG,      // Retrieve MAC extended configuration register est operation mode of MAC
                                         // transmitter
    IOCTL_XGMAC_GET_MAC_EXT_CONFIG1,     // Retrieve MAC register split mode control field
    IOCTL_XGMAC_GET_MAC_FPE_CTRL_STS,    // Retrieve MAC operation of frame preemption
    IOCTL_XGMAC_GET_MAC_CSR_SW_CTRL,     // Retrieve MAC programmable controls for CSR
    IOCTL_XGMAC_GET_MAC_ADDR0_HIGH,      // Retrieve MAC address 0 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR0_LOW,       // Retrieve MAC address 0 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR1_HIGH,      // Retrieve MAC address 1 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR1_LOW,       // Retrieve MAC address 1 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR2_HIGH,      // Retrieve MAC address 2 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR2_LOW,       // Retrieve MAC address 2 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR3_HIGH,      // Retrieve MAC address 3 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR3_LOW,       // Retrieve MAC address 3 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR4_HIGH,      // Retrieve MAC address 4 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR4_LOW,       // Retrieve MAC address 4 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR5_HIGH,      // Retrieve MAC address 5 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR5_LOW,       // Retrieve MAC address 5 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR6_HIGH,      // Retrieve MAC address 6 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR6_LOW,       // Retrieve MAC address 6 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR7_HIGH,      // Retrieve MAC address 7 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR7_LOW,       // Retrieve MAC address 7 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR8_HIGH,      // Retrieve MAC address 8 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR8_LOW,       // Retrieve MAC address 8 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR9_HIGH,      // Retrieve MAC address 9 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR9_LOW,       // Retrieve MAC address 9 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR10_HIGH,     // Retrieve MAC address 10 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR10_LOW,      // Retrieve MAC address 10 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR11_HIGH,     // Retrieve MAC address 11 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR11_LOW,      // Retrieve MAC address 11 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR12_HIGH,     // Retrieve MAC address 12 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR12_LOW,      // Retrieve MAC address 12 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR13_HIGH,     // Retrieve MAC address 13 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR13_LOW,      // Retrieve MAC address 13 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR14_HIGH,     // Retrieve MAC address 14 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR14_LOW,      // Retrieve MAC address 14 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR15_HIGH,     // Retrieve MAC address 15 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR15_LOW,      // Retrieve MAC address 15 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR16_HIGH,     // Retrieve MAC address 16 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR16_LOW,      // Retrieve MAC address 16 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR17_HIGH,     // Retrieve MAC address 17 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR17_LOW,      // Retrieve MAC address 17 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR18_HIGH,     // Retrieve MAC address 18 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR18_LOW,      // Retrieve MAC address 18 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR19_HIGH,     // Retrieve MAC address 19 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR19_LOW,      // Retrieve MAC address 19 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR20_HIGH,     // Retrieve MAC address 20 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR20_LOW,      // Retrieve MAC address 20 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR21_HIGH,     // Retrieve MAC address 21 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR21_LOW,      // Retrieve MAC address 21 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR22_HIGH,     // Retrieve MAC address 22 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR22_LOW,      // Retrieve MAC address 22 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR23_HIGH,     // Retrieve MAC address 23 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR23_LOW,      // Retrieve MAC address 23 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR24_HIGH,     // Retrieve MAC address 24 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR24_LOW,      // Retrieve MAC address 24 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR25_HIGH,     // Retrieve MAC address 25 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR25_LOW,      // Retrieve MAC address 25 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR26_HIGH,     // Retrieve MAC address 26 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR26_LOW,      // Retrieve MAC address 26 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR27_HIGH,     // Retrieve MAC address 27 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR27_LOW,      // Retrieve MAC address 27 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR28_HIGH,     // Retrieve MAC address 28 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR28_LOW,      // Retrieve MAC address 28 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR29_HIGH,     // Retrieve MAC address 29 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR29_LOW,      // Retrieve MAC address 29 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR30_HIGH,     // Retrieve MAC address 30 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR30_LOW,      // Retrieve MAC address 30 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_ADDR31_HIGH,     // Retrieve MAC address 31 high "upper 16 bits"
    IOCTL_XGMAC_GET_MAC_ADDR31_LOW,      // Retrieve MAC address 31 low "lower 32 bits"
    IOCTL_XGMAC_GET_MAC_IND_ACTRL,       // Retrieve MAC indirect access control of MAC
    IOCTL_XGMAC_GET_MAC_IND_ADATA,       // Retrieve MAC indirect access data of MAC
    IOCTL_XGMAC_GET_MAC_L3_L4_ADDR_CTRL, // Retrieve indirect address and control for layer 3/4 filter
    IOCTL_XGMAC_GET_MAC_L3_L4_ADDR_DATA, // Retrieve indirect data and control for layer 3/4 filter
    IOCTL_XGMAC_GET_MAC_ARP_ADDR,        // Retrieve arp address register IPV4 destination address
    IOCTL_XGMAC_GET_MAC_TMTMP_CTRL,      // Retrieve system time generator register
    IOCTL_XGMAC_GET_MAC_SSEC_INCR,   // Retrieve IEEE 1588 timestamp governed feature for sub second increment register
    IOCTL_XGMAC_GET_MAC_SYS_TM_SEC,  // Retrieve system time in seconds "read only"
    IOCTL_XGMAC_GET_MAC_SYS_TM_NSEC, // Retrieve system time in nano seconds "read only"
    IOCTL_XGMAC_GET_MAC_SYS_TM_SEC_UPDT,    // Retrieve system time seconds
    IOCTL_XGMAC_GET_MAC_SYS_TM_NSEC_UPDT,   // Retrieve system time nano seconds
    IOCTL_XGMAC_GET_MAC_SYS_TMTMP_ADDEND,   // Retrieve timestamp addend register "present only when 1588 timestamp
                                            // feature is selected"
    IOCTL_XGMAC_GET_MAC_SYS_TM_HWORD_SEC,   // Retrieve timestamp higher word seconds register "present only when 1588
                                            // timestamp feature is selected"
    IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS,      // Retrieve timestamp status register
    IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_NSEC, // Retrieve nanoseconds portion of 64 bit timestamp captured for the PTP
                                            // packet successfully transmitted "read only"
    IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_SEC,  // Retrieve seconds portion of 64 bit timestamp captured for the PTP packet
                                            // successfully transmitted "read only"
    IOCTL_XGMAC_GET_MAC_TX_TMSTMP_STS_PID,  // Retrieve ptp packet ID relative to TX timestamp status (sec & nanosec)
                                            // "read only"
    IOCTL_XGMAC_GET_MAC_AUX_TMPSTMP_CTRL,   // Retrieve auxillary timestamp control register "snapshot"
    IOCTL_XGMAC_GET_MAC_AUX_TMSTMP_NSEC,    // Retrieve auxillary nanoseconds portion of 64 bit auxillary snapshot "read
                                            // only"
    IOCTL_XGMAC_GET_MAC_AUX_TMSTMP_SEC, // Retrieve auxillary seconds portion of 64 bit auxillary snapshot "read only"
    IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_ASYM_CORR,  // Retrieve mac timestamp ingress asymmetry correction register
    IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_ASYM_CORR,  // Retrieve mac timestamp egress asymmetry correction register
    IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_CORR_NSEC,  // Retrieve mac timestamp ingress correction nanosecond register
    IOCTL_XGMAC_GET_MAC_TMSTMP_IGRS_CORR_SNSEC, // Retrieve mac timestamp ingress correction sub-nanosecond register
    IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_CORR_NSEC,  // Retrieve mac timestamp egress correction nanosecond register
    IOCTL_XGMAC_GET_MAC_TMSTMP_EGRS_CORR_SNSEC, // Retrieve mac timestamp egress correction sub-nanosecond register
    IOCTL_XGMAC_GET_MAC_PPS_CTRL,      // Retrieve mac pps control register "only when timestamp feature is selected no
                                       // external timestamp"
    IOCTL_XGMAC_GET_MAC_PPS0_TRG_SEC,  // Retrieve mac PPS0 target time seconds register
    IOCTL_XGMAC_GET_MAC_PPS0_TRG_NSEC, // Retrieve mac PPS0 target time nano seconds register
    IOCTL_XGMAC_GET_MAC_PPS0_INTV,  // Retrieve mac PPS0 interval register "number of sub-second increment value between
                                    // rising edges"
    IOCTL_XGMAC_GET_MAC_PPS0_WIDTH, // Retrieve mac PPS0 width register "number of sub-second increment value between
                                    // rising & falaling edges"
    IOCTL_XGMAC_GET_MAC_PPS1_TRG_SEC,  // Retrieve mac PPS1 target time seconds register
    IOCTL_XGMAC_GET_MAC_PPS1_TRG_NSEC, // Retrieve mac PPS1 target time nano seconds register
    IOCTL_XGMAC_GET_MAC_PPS1_INTV,  // Retrieve mac PPS1 interval register "number of sub-second icrement value between
                                    // rising edges"
    IOCTL_XGMAC_GET_MAC_PPS1_WIDTH, // Retrieve mac PPS1 with register "number of sub-second icrement value between
                                    // rising & falaling edges"
    IOCTL_XGMAC_GET_MAC_PTO_CTRL, // Retrieve mac PTP offload engine operation "ptp timestamp offload feature selected"
    IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN0, // Retrieve mac part 1 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN1, // Retrieve mac part 2 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_GET_MAC_SRC_PORT_IDN2, // Retrieve mac part 3 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_GET_MAC_LOG_MSG_INTV,  // Retrieve mac register contains periodic intervals for automatic PTP packet
                                       // generation
    // MAC RELATED REGISTER READ ACCESS END

    // MDIO RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_GET_MDIO_SGL_CMD_ADDR,      // Retrieve MDIO address of ports, devices and registers by the SMA
    IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA,      // Retrieve MDIO DATA of ports, devices and registers
    IOCTL_XGMAC_GET_MDIO_CONT_WR_ADDR,      // Retrieve MDIO program to start continuous write operation
    IOCTL_XGMAC_GET_MDIO_CONT_WR_DATA,      // Retrieve MDIO data to be written during continuous write operation
    IOCTL_XGMAC_GET_MDIO_CONT_SCAN_PEN,     // Retrieve MDIO control for PHY ports and corresponding devices
    IOCTL_XGMAC_GET_MDIO_INT_STATUS,        // Retrieve MDIO source of SMA interrupt "read only"
    IOCTL_XGMAC_GET_MDIO_INT_ENABLE,        // Retrieve MDIO Interrupt Enable
    IOCTL_XGMAC_GET_MDIO_PORT_CON_DISC_STS, // Retrieve MDIO hot plug in status for port 0-31 "read only"
    IOCTL_XGMAC_GET_MDIO_CLS22_PORT,        // Retrieve MDIO configuration of SMA to access PHY ports
    IOCTL_XGMAC_GET_MDIO_PORT_NX4_IND_CTRL, // Retrieve MDIO fields for controling port range select
    IOCTL_XGMAC_GET_MDIO_PORTNX4P0_INUSE,   // Retrieve MDIO status of each device on port nx4 plus 0
    IOCTL_XGMAC_GET_MDIO_PORTNX4P0_LSTS,    // Retrieve MDIO link status of each device on port nx4 plus 0 "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P0_ASTS,    // Retrieve MDIO alive status of each device on port nx4 plus 0 "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P1_INUSE,   // Retrieve MDIO status of each device on port nx4 plus 1
    IOCTL_XGMAC_GET_MDIO_PORTNX4P1_LSTS,    // Retrieve MDIO link status of each device on port nx4 plus 1  "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P1_ASTS,    // Retrieve MDIO alive status of each device on port nx4 plus 1  "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P2_INUSE,   // Retrieve MDIO status of each device on port nx4 plus 2
    IOCTL_XGMAC_GET_MDIO_PORTNX4P2_LSTS,    // Retrieve MDIO link status of each device on port nx4 plus 2 "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P2_ASTS,    // Retrieve MDIO alive status of each device on port nx4 plus 2 "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P3_INUSE,   // Retrieve MDIO status of each device on port nx4 plus 3
    IOCTL_XGMAC_GET_MDIO_PORTNX4P3_LSTS,    // Retrieve MDIO link status of each device on port nx4 plus 3 "read only"
    IOCTL_XGMAC_GET_MDIO_PORTNX4P3_ASTS,    // Retrieve MDIO alive status of each device on port nx4 plus 3 "read only"
    // MDIO RELATED REGISTER READ ACCESS END

    // MMC RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_GET_MMC_CTRL,           // Retrieve MMC control register
    IOCTL_XGMAC_GET_MMC_RX_INT,         // Retrieve MMC receive interrupt status "read only"
    IOCTL_XGMAC_GET_MMC_TX_INT,         // Retrieve MMC transmit interrupt status "read only"
    IOCTL_XGMAC_GET_MMC_RX_INT_EN,      // Retrieve MMC receive interrupt enable register
    IOCTL_XGMAC_GET_MMC_TX_INT_EN,      // Retrieve MMC transmit interrupt enable
    IOCTL_XGMAC_GET_MMC_FPE_TX_INT,     // Retrieve interrupts generated from all FPE related TX statistics "read only"
    IOCTL_XGMAC_GET_MMC_FPE_TX_INT_MSK, // Retrieve interrupt masks generated from all FPE related TX statistics "read
                                        // only"
    IOCTL_XGMAC_GET_MMC_TX_FPE_FRAG_CNTR, // Retrieve number of mpackets transmitted due to preemption "read only"
    IOCTL_XGMAC_GET_MMC_TX_HOLD_RQ_CNTR,  // Retrieve count of times for hold request "read only"
    IOCTL_XGMAC_GET_MMC_FPE_RX_INT,       // Retrieve interrupts generated from FPE related stat counters "read only"
    IOCTL_XGMAC_GET_MMC_FPE_RX_INT_MSK, // Retrieve interrupt masks generated from FPE related stat counters "read only"
    IOCTL_XGMAC_GET_MMC_RX_PKT_ASM_ERR_CNTR, // Retrieve number of mac frames with reassembly erros on RX'er "read only"
    IOCTL_XGMAC_GET_MMC_RX_PKT_SMD_ERR_CNTR, // Retrieve number of mac frames with unknown SMD value "read only"
    IOCTL_XGMAC_GET_MMC_RX_PKT_ASM_OK_CNTR,  // Retrieve number of mac frames successfully reassemebled "read only"
    IOCTL_XGMAC_GET_MMC_RX_FPE_FRAG_CNTR,    // Retrieve number of additional mpacket for preemption "read only"
    IOCTL_XGMAC_GET_MMC_IPC_RX_INT_MASK, // Retrieve mask for interrupt generated from receive IPC statistics counters
    IOCTL_XGMAC_GET_MMC_IPC_RX_INT, // Retrieve interrupts generated from receive IPC statistics counters "read only"
    // MMC RELATED REGISTER READ ACCESS END

    // TX RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_GET_TX_OCT_CNT_GBL, // Retrieve lower 32 bits of transmitted octet count in good and bad packets "read
                                    // only"
    IOCTL_XGMAC_GET_TX_OCT_CNT_GBH, // Retrieve upper 32 bits of transmitted octet count in good and bad packets "read
                                    // only"
    IOCTL_XGMAC_GET_TX_PKT_CNT_GBL, // Retrieve lower 32 bits of transmitted good and bad packets "read only"
    IOCTL_XGMAC_GET_TX_BCAST_PKT_CNT_GL, // Retrieve lower 32 bits of transmitted broadcast good and low packets "read
                                         // only"
    IOCTL_XGMAC_GET_TX_MCAST_PKT_CNT_GL, // Retrieve lower 32 bits of transmitted multicast good and low packets "read
                                         // only"
    IOCTL_XGMAC_GET_TX_64OCT_PKT_GBL, // Retrieve lower 32 bits of transmitted 64 octet size good and bad packets "read
                                      // only"
    IOCTL_XGMAC_GET_TX_65_127_OCT_PKT_GBL,   // Retrieve lower 32 bits of transmitted 65-127 octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_TX_128_255_OCT_PKT_GBL,  // Retrieve lower 32 bits of transmitted 128-255 octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_TX_256_511_OCT_PKT_GBL,  // Retrieve lower 32 bits of transmitted 256-511 octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_TX_512_1023_OCT_PKT_GBL, // Retrieve lower 32 bits of transmitted 512-1023 octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_TX_1024_MAX_OCT_PKT_GBL, // Retrieve lower 32 bits of transmitted 1023 - max octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_TX_UCAST_PKT_GBL,  // Retrieve lower 32 bits of transmitted unicast good and bad packets "read only"
    IOCTL_XGMAC_GET_TX_MCAST_PKT_GBL,  // Retrieve lower 32 bits of transmitted multicast good and bad packets "read
                                       // only"
    IOCTL_XGMAC_GET_TX_BCAST_PKT_GBL,  // Retrieve lower 32 bits of transmitted broadcast good and bad packets "read
                                       // only"
    IOCTL_XGMAC_GET_TX_UNDFLW_ERR_PKT, // Retrieve lower 32 bits of transmitted packets aborted for underlfow "read
                                       // only"
    IOCTL_XGMAC_GET_TX_OCT_COUNT_GL,   // Retrieve lower 32 bits of transmitted good octets "read only"
    IOCTL_XGMAC_GET_TX_OCT_COUNT_GH,   // Retrieve upper 32 bits of transmitted good octets "read only"
    IOCTL_XGMAC_GET_TX_PKT_COUNT_GL,   // Retrieve lower 32 bits of transmitted good packets "read only"
    IOCTL_XGMAC_GET_TX_PSE_PKT_COUNT,  // Retrieve lower 32 bits of transmitted pause packets "read only"
    IOCTL_XGMAC_GET_TX_VLAN_PKT_COUNT_GL, // Retrieve lower 32 bits of transmitted good VLAN packets "read only"
    IOCTL_XGMAC_GET_TX_LPI_USEC_CTR,      // Retrieve duration in "microseconds" MAC was in TX LPI "read only"
    IOCTL_XGMAC_GET_TX_LPI_TRAN_CTR,      // Retrieve number of times MAC transitioned to LPI TX "read only"
    IOCTL_XGMAC_GET_TX_SGL_COL_PKT_G,  // Retrieve number of successfully transmitted packets by DWC_xgmac after single
                                       // collision "read only"
    IOCTL_XGMAC_GET_TX_MULT_COL_PKT_G, // Retrieve number of successfully transmitted packets by DWC_xgmac after
                                       // multiple collisions "read only"
    IOCTL_XGMAC_GET_TX_DFRD_EPKT, // Retrieve number of successfully transmitted packets by DWC_xgmac after half duplex
                                  // deferral "read only"
    IOCTL_XGMAC_GET_TX_LATE_COL_EPKT, // Retrieve number of packets aborted by DWC_xgmac for late collision error "read
                                      // only"
    IOCTL_XGMAC_GET_TX_EXC_COL_EPKT,  // Retrieve number of packets aborted by DWC_xgmac for excessive (16) collision
                                      // error "read only"
    IOCTL_XGMAC_GET_TX_CAR_ERR_EPKT,  // Retrieve number of aborted packets for carrier sense error "read only"
    IOCTL_XGMAC_GET_TX_EXC_DFRD_ERR,  // Retrieve number of packets aborted by DWC_xgmac for excessive deferral error
                                      // "read only"
    // TX RELATED REGISTER READ ACCESS END

    // RX RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_GET_RX_PKT_COUNT_GBL, // Retrieve lower 32 bits of received good and bad packets count "read only"
    IOCTL_XGMAC_GET_RX_OCT_COUNT_GBL, // Retrieve lower 32 bits of received good and bad octet count "read only"
    IOCTL_XGMAC_GET_RX_OCT_COUNT_GBH, // Retrieve upper 32 bits of received good and bad octet count "read only"
    IOCTL_XGMAC_GET_RX_OCT_COUNT_GL,  // Retrieve lower 32 bits of received good octet count "read only"
    IOCTL_XGMAC_GET_RX_OCT_COUNT_GH,  // Retrieve upper 32 bits of received good octet count "read only"
    IOCTL_XGMAC_GET_RX_BCAST_PKT_GL,  // Retrieve lower 32 bits of received good broadcast packets count "read only"
    IOCTL_XGMAC_GET_RX_MCAST_PKT_GL,  // Retrieve lower 32 bits of received good multicast packets count "read only"
    IOCTL_XGMAC_GET_RX_CRC_PKT_ERR_L, // Retrieve lower 32 bits of received packets with CRC errors "read only"
    IOCTL_XGMAC_GET_RX_RUNT_PKT_ERR,  // Retrieve received packets with runt error "read only"
    IOCTL_XGMAC_GET_RX_JBR_PKT_ERR,   // Retrieve received packets with jabber error "read only"
    IOCTL_XGMAC_GET_RX_USZE_PKT_G,    // Retrieve received good undersize packets "read only"
    IOCTL_XGMAC_GET_RX_OSZE_PKT_G,    // Retrieve received good oversize packets "read only"
    IOCTL_XGMAC_GET_RX_64OCT_PKT_GBL, // Retrieve lower 32 bits of received 64 octet size good and bad packets "read
                                      // only"
    IOCTL_XGMAC_GET_RX_65_127_OCT_PKT_GBL,  // Retrieve lower 32 bits of received 65-127 octet size good and bad packets
                                            // "read only"
    IOCTL_XGMAC_GET_RX_128_255_OCT_PKT_GBL, // Retrieve lower 32 bits of received 128-255 octet size good and bad
                                            // packets "read only"
    IOCTL_XGMAC_GET_RX_256_511_OCT_PKT_GBL, // Retrieve lower 32 bits of received 256-511 octet size good and bad
                                            // packets "read only"
    IOCTL_XGMAC_GET_RX_512_1023_OCT_PKT_GBL, // Retrieve lower 32 bits of received 512-1023 octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_RX_1024_MAX_OCT_PKT_GBL, // Retrieve lower 32 bits of received 1023 - max octet size good and bad
                                             // packets "read only"
    IOCTL_XGMAC_GET_RX_UCAST_PKT_GL,         // Retrieve lower 32 bits of received good unicast packets "read only"
    IOCTL_XGMAC_GET_RX_LGTH_ERR_PKT_L, // Retrieve lower 32 bits of received packets with length errors "read only"
    IOCTL_XGMAC_GET_RX_OUT_RNG_PKT_L, // Retrieve lower 32 bits of received packets with out of range length field count
                                      // "read only"
    IOCTL_XGMAC_GET_RX_PSE_PKT_L,     // Retrieve lower 32 bits of received pause packet count "read only"
    IOCTL_XGMAC_GET_RX_FIFO_OFLW_PKT_L, // Retrieve lower 32 bits of received packets count that had RX queue overflow
                                        // "read only"
    IOCTL_XGMAC_GET_RX_VLAN_PKT_GBL,    // Retrieve lower 32 bits of received good bad VLAN packets count "read only"
    IOCTL_XGMAC_GET_RX_WDT_ERR_PKT,  // Retrieve lower 32 bits of received packets with watchdog error count "read only"
    IOCTL_XGMAC_GET_RX_LPI_USEC_CTR, // Retrieve duration in "microseconds" MAC was in RX LPI "read only"
    IOCTL_XGMAC_GET_RX_LPI_TRAN_CTR, // Retrieve number of times MAC transitioned to RX "read only"
    IOCTL_XGMAC_GET_RX_DCRD_PKT_GBL, // Retrieve lower 32 bits of received good bad discarded packets count "read only"
    IOCTL_XGMAC_GET_RX_DCRD_OCT_GBL, // Retrieve lower 32 bits of received good bad discarded octets count "read only"
    IOCTL_XGMAC_GET_RX_DCRD_OCT_GBH, // Retrieve upper 32 bits of received good bad discarded packets count "read only"
    IOCTL_XGMAC_GET_RX_ALGN_ERR_PKT, // Retrieve number of packets received by DWC_xgmac with alignment error "read
                                     // only"
    IOCTL_XGMAC_GET_RX_IPV4_GD_PKT_L, // Retrieve lower 32 bits of good ipv4 datagrams received TCP,UDP, or ICMP "read
                                      // only"
    IOCTL_XGMAC_GET_RX_IPV4_HDR_ERR_PKT_L, // Retrieve header error packets "read only"
    IOCTL_XGMAC_GET_RX_IPV4_NOPAYL_PKT_L, // Retrieve lower 32 bits of good IPv4 datagrams received NOT TCP,UDP, or ICMP
                                          // "read only"
    IOCTL_XGMAC_GET_RX_IPV4_FRAG_PKT_L,   // Retrieve lower 32 bits of good IPv4 datagrams with framentation "read only"
    IOCTL_XGMAC_GET_RX_IPV4_UDP_CHKSM_DPKT_L, // Retrieve lower 32 bits of good IPv4 datagrams received with UDP
                                              // checksum disabled "read only"
    IOCTL_XGMAC_GET_RX_IPV6_GD_PKT_L,         // Retrieve lower 32 bits of good IPv6 datagrams received "read only"
    IOCTL_XGMAC_GET_RX_IPV6_HDR_ERR_PKT_L,    // Retrieve lower 32 bits of datagram IPv6 with header error "read only"
    IOCTL_XGMAC_GET_RX_IPV6_NOPAYL_PKT_L, // Retrieve lower 32 bits of good IPv6 datagrans received NOT TCP,UDP, or ICMP
                                          // "read only"
    IOCTL_XGMAC_GET_RX_UDP_GD_PKT_L,      // Retrieve lower 32 bits of good UDP datagrams received "read only"
    IOCTL_XGMAC_GET_RX_UDP_ERR_PKT_L, // Retrieve lower 32 bits of good UDP datagrams received with checksum error "read
                                      // only"
    IOCTL_XGMAC_GET_RX_TCP_GD_PKT_L,  // Retrieve lower 32 bits of good TCP datagrams received "read only"
    IOCTL_XGMAC_GET_RX_TCP_ERR_PKT_L, // Retrieve lower 32 bits of good TCP datagrams received with checksum error "read
                                      // only"
    IOCTL_XGMAC_GET_RX_ICMP_GD_PKT_L, // Retrieve lower 32 bits of good ICMP datagrams received "read only"
    IOCTL_XGMAC_GET_RX_ICMP_ERR_PKT_L, // Retrieve lower 32 bits of good ICMP datagrams received with checksum error
                                       // "read only"
    IOCTL_XGMAC_GET_RX_IPV4_GD_OCT_L,  // Retrieve lower 32 bits of good IPv4 octet datagrams received TCP,UDP, or ICMP
                                       // "read only"
    IOCTL_XGMAC_GET_RX_IPV4_HDR_ERR_OCT_L, // Retrieve header error packets "read only"
    IOCTL_XGMAC_GET_RX_IPV4_NOPAYL_OCT_L,  // Retrieve lower 32 bits of good IPv4 octet datagrams received NOT TCP,UDP,
                                           // or ICMP "read only"
    IOCTL_XGMAC_GET_RX_IPV4_FRAG_OCT_L, // Retrieve lower 32 bits of good IPv4 octet datagrams with framentation "read
                                        // only"
    IOCTL_XGMAC_GET_RX_IPV4_UDP_CHKSM_DOCT_L, // Retrieve lower 32 bits of good IPv4 octet datagrams received with UDP
                                              // checksum disabled "read only"
    IOCTL_XGMAC_GET_RX_IPV6_GD_OCT_L,         // Retrieve lower 32 bits of good IPv6 datagrams received "read only"
    IOCTL_XGMAC_GET_RX_IPV6_HDR_ERR_OCT_L,    // Retrieve lower 32 bits of octet datagram IPv6 with header error "read
                                              // only"
    IOCTL_XGMAC_GET_RX_IPV6_NOPAYL_OCT_L, // Retrieve lower 32 bits of good IPv6 octet datagrans received NOT TCP,UDP,
                                          // or ICMP "read only"
    IOCTL_XGMAC_GET_RX_UDP_GD_OCT_L,      // Retrieve lower 32 bits of good UDP octet datagrams received "read only"
    IOCTL_XGMAC_GET_RX_UDP_ERR_OCT_L, // Retrieve lower 32 bits of good UDP octet datagrams received with checksum error
                                      // "read only"
    IOCTL_XGMAC_GET_RX_TCP_GD_OCT_L,  // Retrieve lower 32 bits of good TCP octet datagrams received "read only"
    IOCTL_XGMAC_GET_RX_TCP_ERR_OCT_L, // Retrieve lower 32 bits of good TCP octet datagrams received with checksum error
                                      // "read only"
    IOCTL_XGMAC_GET_RX_ICMP_GD_OCT_L, // Retrieve lower 32 bits of good ICMP octet datagrams received "read only"
    IOCTL_XGMAC_GET_RX_ICMP_ERR_OCT_L, // Retrieve lower 32 bits of good ICMP octet datagrams received with checksum
                                       // error "read only"
    // RX RELATED REGISTER READ ACCESS END
    /* READ ACCESS CALLS END */

    /* WRITE ACCES RELATED CALLS START */
    // MAC RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_SET_MAC_TX_CONFIG,      // set MAC Transmit Configuration
    IOCTL_XGMAC_SET_MAC_RX_CONFIG,      // set MAC Receive Configuration
    IOCTL_XGMAC_SET_MAC_PKT_FLTR,       // set MAC Packet Filter Configuration
    IOCTL_XGMAC_SET_MAC_WD_JD_TOUT,     // set MAC Watchdog and Jabber Timeout
    IOCTL_XGMAC_SET_MAC_HSH_TREGO,      // set MAC HASH Table REG0
    IOCTL_XGMAC_SET_MAC_HSH_TREG1,      // set MAC HASH TAble REG1
    IOCTL_XGMAC_SET_MAC_VLAN_TCTRL,     // set MAC MAC_VLAN_TAG_CTRL
    IOCTL_XGMAC_SET_MAC_VLAN_HTBL,      // set MAC VLAN HASH Table
    IOCTL_XGMAC_SET_MAC_VLAN_TDATA,     // set MAC VLAN TAG Data
    IOCTL_XGMAC_SET_MAC_VLAN_INCL,      // set MAC VLAN Inclusion/Replacement register
    IOCTL_XGMAC_SET_MAC_INN_VLAN_INCL,  // set MAC Inner VLAN Inclusion register
    IOCTL_XGMAC_SET_MAC_RX_ETH_TYPE,    // set MAC receive Ethernet type match register
    IOCTL_XGMAC_SET_MAC_Q0_TXFLW_CTRL,  // set MAC Q0 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q1_TXFLW_CTRL,  // set MAC Q1 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q2_TXFLW_CTRL,  // set MAC Q2 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q3_TXFLW_CTRL,  // set MAC Q3 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q4_TXFLW_CTRL,  // set MAC Q4 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q5_TXFLW_CTRL,  // set MAC Q5 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q6_TXFLW_CTRL,  // set MAC Q6 transmit flow control register
    IOCTL_XGMAC_SET_MAC_Q7_TXFLW_CTRL,  // set MAC Q7 transmit flow control register
    IOCTL_XGMAC_SET_MAC_MAX_RXFLW_CTRL, // set MAC Max receive flow control register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL4,      // set MAC receive queue control 4 register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL5,      // set MAC receive queue control 5 register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL0,      // set MAC receive queue control 0 register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL1,      // set MAC receive queue control 1 register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL2,      // set MAC receive queue control 2 register
    IOCTL_XGMAC_SET_MAC_RXQ_CTRL3,      // set MAC receive queue control 3 register
    IOCTL_XGMAC_SET_MAC_INT_ENABLE,     // set MAC interrupt enable register
    IOCTL_XGMAC_SET_MAC_LPI_CTRL_STS,   // set MAC LPI control status register
    IOCTL_XGMAC_SET_MAC_LPI_TM_CTRL,    // set MAC LPI timers control register
    IOCTL_XGMAC_SET_MAC_AUTO_ENTRY_TM,  // set MAC LPI auto entry timer value "microseconds" register
    IOCTL_XGMAC_SET_MAC_US_TIC_CNTR,  // set MAC register to control the generation of reference time in "microseconds"
    IOCTL_XGMAC_SET_MAC_EXT_CONFIG,   // set MAC extended configuration register est operation mode of MAC transmitter
    IOCTL_XGMAC_SET_MAC_EXT_CONFIG1,  // set MAC register split mode control field
    IOCTL_XGMAC_SET_MAC_FPE_CTRL_STS, // set MAC operation of frame preemption
    IOCTL_XGMAC_SET_MAC_CSR_SW_CTRL,  // set MAC programmable controls for CSR
    IOCTL_XGMAC_SET_MAC_FADDR0_HIGH,  // set MAC address 0 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR0_LOW,   // set MAC address 0 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR1_HIGH,  // set MAC address 1 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR1_LOW,   // set MAC address 1 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR2_HIGH,  // set MAC address 2 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR2_LOW,   // set MAC address 2 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR3_HIGH,  // set MAC address 3 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR3_LOW,   // set MAC address 3 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR4_HIGH,  // set MAC address 4 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR4_LOW,   // set MAC address 4 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR5_HIGH,  // set MAC address 5 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR5_LOW,   // set MAC address 5 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR6_HIGH,  // set MAC address 6 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR6_LOW,   // set MAC address 6 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR7_HIGH,  // set MAC address 7 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR7_LOW,   // set MAC address 7 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR8_HIGH,  // set MAC address 8 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR8_LOW,   // set MAC address 8 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR9_HIGH,  // set MAC address 9 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR9_LOW,   // set MAC address 9 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR10_HIGH, // set MAC address 10 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR10_LOW,  // set MAC address 10 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR11_HIGH, // set MAC address 11 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR11_LOW,  // set MAC address 11 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR12_HIGH, // set MAC address 12 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR12_LOW,  // set MAC address 12 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR13_HIGH, // set MAC address 13 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR13_LOW,  // set MAC address 13 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR14_HIGH, // set MAC address 14 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR14_LOW,  // set MAC address 14 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR15_HIGH, // set MAC address 15 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR15_LOW,  // set MAC address 15 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR16_HIGH, // set MAC address 16 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR16_LOW,  // set MAC address 16 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR17_HIGH, // set MAC address 17 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR17_LOW,  // set MAC address 17 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR18_HIGH, // set MAC address 18 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR18_LOW,  // set MAC address 18 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR19_HIGH, // set MAC address 19 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR19_LOW,  // set MAC address 19 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR20_HIGH, // set MAC address 20 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR20_LOW,  // set MAC address 20 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR21_HIGH, // set MAC address 21 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR21_LOW,  // set MAC address 21 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR22_HIGH, // set MAC address 22 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR22_LOW,  // set MAC address 22 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR23_HIGH, // set MAC address 23 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR23_LOW,  // set MAC address 23 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR24_HIGH, // set MAC address 24 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR24_LOW,  // set MAC address 24 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR25_HIGH, // set MAC address 25 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR25_LOW,  // set MAC address 25 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR26_HIGH, // set MAC address 26 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR26_LOW,  // set MAC address 26 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR27_HIGH, // set MAC address 27 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR27_LOW,  // set MAC address 27 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR28_HIGH, // set MAC address 28 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR28_LOW,  // set MAC address 28 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR29_HIGH, // set MAC address 29 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR29_LOW,  // set MAC address 29 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR30_HIGH, // set MAC address 30 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR30_LOW,  // set MAC address 30 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_FADDR31_HIGH, // set MAC address 31 high "upper 16 bits"
    IOCTL_XGMAC_SET_MAC_FADDR31_LOW,  // set MAC address 31 low "lower 32 bits"
    IOCTL_XGMAC_SET_MAC_IND_ACTRL,    // set MAC indirect access control of MAC
    IOCTL_XGMAC_SET_MAC_IND_ADATA,    // set MAC indirect access data of MAC
    IOCTL_XGMAC_SET_MAC_L3_L4_ADDR_CTRL,  // set indirect address and control for layer 3/4 filter
    IOCTL_XGMAC_SET_MAC_L3_L4_ADDR_DATA,  // set indirect data and control for layer 3/4 filter
    IOCTL_XGMAC_SET_MAC_ARP_ADDR,         // set arp address register IPV4 destination address
    IOCTL_XGMAC_SET_MAC_TSTMP_CTRL,       // set system time generator register
    IOCTL_XGMAC_SET_MAC_SSEC_INCR,        // set IEEE 1588 timestamp governed feature for sub second increment register
    IOCTL_XGMAC_SET_MAC_SYS_TM_SEC_UPDT,  // set system time seconds
    IOCTL_XGMAC_SET_MAC_SYS_TM_NSEC_UPDT, // set system time nano seconds
    IOCTL_XGMAC_SET_MAC_SYS_TMTMP_ADDEND, // set timestamp addend register "present only when 1588 timestamp feature is
                                          // selected"
    IOCTL_XGMAC_SET_MAC_SYS_TM_HWORD_SEC, // set timestamp higher word seconds register "present only when 1588
                                          // timestamp feature is selected"
    IOCTL_XGMAC_SET_MAC_AUX_CTRL,         // set auxillary timestamp control register "snapshot"
    IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_ASYM_CORR,  // set mac timestamp ingress asymmetry correction register
    IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_ASYM_CORR,  // set mac timestamp egress asymmetry correction register
    IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_CORR_NSEC,  // set mac timestamp ingress correction nanosecond register
    IOCTL_XGMAC_SET_MAC_TMSTMP_IGRS_CORR_SNSEC, // set mac timestamp ingress correction sub-nanosecond register
    IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_CORR_NSEC,  // set mac timestamp egress correction nanosecond register
    IOCTL_XGMAC_SET_MAC_TMSTMP_EGRS_CORR_SNSEC, // set mac timestamp egress correction sub-nanosecond register
    IOCTL_XGMAC_SET_MAC_PPS_CTRL, // set mac pps control register "only when timestamp feature is selected no external
                                  // timestamp"
    IOCTL_XGMAC_SET_MAC_PPS0_TRG_SEC,  // set mac PPS0 target time seconds register
    IOCTL_XGMAC_SET_MAC_PPS0_TRG_NSEC, // set mac PPS0 target time nano seconds register
    IOCTL_XGMAC_SET_MAC_PPS0_INTV, // set mac PPS0 interval register "number of sub-second icrement value between rising
                                   // edges"
    IOCTL_XGMAC_SET_MAC_PPS0_WIDTH, // set mac PPS0 with register "number of sub-second icrement value between rising &
                                    // falaling edges"
    IOCTL_XGMAC_SET_MAC_PPS1_TRG_SEC,  // set mac PPS1 target time seconds register
    IOCTL_XGMAC_SET_MAC_PPS1_TRG_NSEC, // set mac PPS1 target time nano seconds register
    IOCTL_XGMAC_SET_MAC_PPS1_INTV, // set mac PPS1 interval register "number of sub-second icrement value between rising
                                   // edges"
    IOCTL_XGMAC_SET_MAC_PPS1_WIDTH, // set mac PPS1 with register "number of sub-second icrement value between rising &
                                    // falaling edges"
    IOCTL_XGMAC_SET_MAC_PTO_CTRL,   // set mac PTP offload engine operation "ptp timestamp offload feature selected"
    IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN0, // set mac part 1 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN1, // set mac part 2 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_SET_MAC_SRC_PORT_IDN2, // set mac part 3 of 80 bit port identity of the PTP node
    IOCTL_XGMAC_SET_MAC_LOG_MSG_INTV, // set mac register contains periodic intervalsfor automatic PTP packet generation
    // MAC RELATED REGISTER READ ACCESS END

    // MDIO RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_SET_MDIO_SGL_CMD_ADDR,      // set MDIO address of ports, devices and registers by the SMA
    IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA,      // set MDIO DATA of ports, devices and registers
    IOCTL_XGMAC_SET_MDIO_CONT_WR_ADDR,      // set MDIO program to start continuous write operation
    IOCTL_XGMAC_SET_MDIO_CONT_WR_DATA,      // set MDIO data to be written during continuous write operation
    IOCTL_XGMAC_SET_MDIO_CONT_SCAN_PEN,     // set MDIO control for PHY ports and corresponding devicesss
    IOCTL_XGMAC_SET_MDIO_INT_STATUS,        // set MDIO source of SMA interrupt "read only"
    IOCTL_XGMAC_SET_MDIO_INT_ENABLE,        // set MDIO Interrupt Enable
    IOCTL_XGMAC_SET_MDIO_PORT_CON_DISC_STS, // set MDIO hot plug in status for port 0-31 "read only"
    IOCTL_XGMAC_SET_MDIO_CLS22_PORT,        // set MDIO configuration of SMA to access PHY ports
    IOCTL_XGMAC_SET_MDIO_PORT_NX4_IND_CTRL, // set MDIO fields for controling port range select
    IOCTL_XGMAC_SET_MDIO_PORTNX4P0_INUSE,   // set MDIO status of each device on port nx4 plus 0
    IOCTL_XGMAC_SET_MDIO_PORTNX4P1_INUSE,   // set MDIO status of each device on port nx4 plus 1
    IOCTL_XGMAC_SET_MDIO_PORTNX4P2_INUSE,   // set MDIO status of each device on port nx4 plus 2
    IOCTL_XGMAC_SET_MDIO_PORTNX4P3_INUSE,   // set MDIO status of each device on port nx4 plus 3
    // MDIO RELATED REGISTER READ ACCESS END

    // MMC RELATED REGISTER READ ACCESS START
    IOCTL_XGMAC_SET_MMC_CTRL,            // set MMC control register
    IOCTL_XGMAC_SET_MMC_RX_INT_EN,       // set MMC receive interrupt enable register
    IOCTL_XGMAC_SET_MMC_TX_INT_EN,       // set MMC transmit interrupt enable
    IOCTL_XGMAC_SET_MMC_IPC_RX_INT_MASK, // set mask for interrupt generated from receive IPC statistics counters
    // MMC RELATED REGISTER READ ACCESS END

    // MTL IOCTL CALL START
    IOCTL_XGMAC_MTL_GET_MTL_OP_MODE,
    IOCTL_XGMAC_MTL_GET_INT_STS,
    IOCTL_XGMAC_MTL_GET_RXQ_DMAP0,
    IOCTL_XGMAC_MTL_GET_RXQ_DMAP1,
    IOCTL_XGMAC_MTL_GET_TC_PRTY_MAP0,
    IOCTL_XGMAC_MTL_GET_TC_PRTY_MAP1,
    IOCTL_XGMAC_MTL_GET_TBS_CTRL,
    IOCTL_XGMAC_MTL_GET_TBS_STS,
    IOCTL_XGMAC_MTL_GET_EST_CTRL,
    IOCTL_XGMAC_MTL_GET_EST_OHD,
    IOCTL_XGMAC_MTL_GET_EST_STS,
    IOCTL_XGMAC_MTL_GET_EST_SCH_ERROR,
    IOCTL_XGMAC_MTL_GET_EST_FSZ_ERROR,
    IOCTL_XGMAC_MTL_GET_EST_FSZ_CPTR,
    IOCTL_XGMAC_MTL_GET_EST_INT_EN,
    IOCTL_XGMAC_MTL_GET_GCL_CTRL,
    IOCTL_XGMAC_MTL_GET_GCL_DATA,
    IOCTL_XGMAC_MTL_GET_FPE_CSTS,
    IOCTL_XGMAC_MTL_GET_FPE_ADV,

    // TCQ0 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ0_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ0_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ0_DBG,
    IOCTL_XGMAC_MTL_GET_TC0_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC0_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC0_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ0_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ0_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ0_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ0_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ0_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q0_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q0_INT_STS,
    // TCQ0 IOCTL's End

    // TCQ1 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ1_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ1_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ1_DBG,
    IOCTL_XGMAC_MTL_GET_TC1_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC1_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC1_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ1_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ1_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ1_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ1_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ1_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q1_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q1_INT_STS,
    // TCQ1 IOCTL's End

    // TCQ2 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ2_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ2_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ2_DBG,
    IOCTL_XGMAC_MTL_GET_TC2_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC2_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC2_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ2_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ2_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ2_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ2_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ2_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q2_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q2_INT_STS,
    // TCQ2 IOCTL's End

    // TCQ3 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ3_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ3_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ3_DBG,
    IOCTL_XGMAC_MTL_GET_TC3_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC3_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC3_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ3_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ3_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ3_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ3_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ3_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q3_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q3_INT_STS,
    // TCQ3 IOCTL's End

    // TCQ4 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ4_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ4_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ4_DBG,
    IOCTL_XGMAC_MTL_GET_TC4_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC4_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC4_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ4_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ4_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ4_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ4_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ4_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q4_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q4_INT_STS,
    // TCQ4 IOCTL's End

    // TCQ5 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ5_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ5_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ5_DBG,
    IOCTL_XGMAC_MTL_GET_TC5_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC5_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC5_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ5_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ5_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ5_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ5_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ5_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q5_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q5_INT_STS,
    // TCQ5 IOCTL's End

    // TCQ6 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ6_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ6_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ6_DBG,
    IOCTL_XGMAC_MTL_GET_TC6_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC6_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC6_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_RXQ6_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ6_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ6_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ6_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ6_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q6_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q6_INT_STS,
    // TCQ6 IOCTL's End

    // TCQ7 IOCTL's Start
    IOCTL_XGMAC_MTL_GET_TXQ7_OP_MODE,
    IOCTL_XGMAC_MTL_GET_TXQ7_UFLW,
    IOCTL_XGMAC_MTL_GET_TXQ7_DBG,
    IOCTL_XGMAC_MTL_GET_TC7_ETS_CTRL,
    IOCTL_XGMAC_MTL_GET_TC7_ETS_STS,
    IOCTL_XGMAC_MTL_GET_TC7_QWEIGHT,
    IOCTL_XGMAC_MTL_GET_TC7_SSCREDIT,
    IOCTL_XGMAC_MTL_GET_TC7_HCREDIT,
    IOCTL_XGMAC_MTL_GET_TC7_LCREDIT,
    IOCTL_XGMAC_MTL_GET_RXQ7_OP_MODE,
    IOCTL_XGMAC_MTL_GET_RXQ7_MPKT_OCNT,
    IOCTL_XGMAC_MTL_GET_RXQ7_DBG,
    IOCTL_XGMAC_MTL_GET_RXQ7_CTRL,
    IOCTL_XGMAC_MTL_GET_RXQ7_FCTRL,
    IOCTL_XGMAC_MTL_GET_Q7_INT_EN,
    IOCTL_XGMAC_MTL_GET_Q7_INT_STS,
    // TCQ0 IOCTL's End

    // MTL SET IOCTL's
    // BASE Element IOCTL's
    IOCTL_XGMAC_MTL_SET_MTL_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ_DMAP0,
    IOCTL_XGMAC_MTL_SET_RXQ_DMAP1,
    IOCTL_XGMAC_MTL_SET_TC_PRTY_MAP0,
    IOCTL_XGMAC_MTL_SET_TC_PRTY_MAP1,
    IOCTL_XGMAC_MTL_SET_TBS_CTRL,
    IOCTL_XGMAC_MTL_SET_TBS_STS,
    IOCTL_XGMAC_MTL_SET_EST_CTRL,
    IOCTL_XGMAC_MTL_SET_EST_OHD,
    IOCTL_XGMAC_MTL_SET_EST_STS,
    IOCTL_XGMAC_MTL_SET_EST_SCH_ERROR,
    IOCTL_XGMAC_MTL_SET_EST_FSZ_ERROR,
    IOCTL_XGMAC_MTL_SET_EST_INT_EN,
    IOCTL_XGMAC_MTL_SET_GCL_CTRL,
    IOCTL_XGMAC_MTL_SET_GCL_DATA,
    IOCTL_XGMAC_MTL_SET_FPE_CSTS,
    IOCTL_XGMAC_MTL_SET_FPE_ADV,

    // TCQ0 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ0_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC0_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC0_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ0_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ0_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ0_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q0_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q0_INT_STS,
    // TCQ0 IOCTL's End

    // TCQ1 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ1_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC1_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC1_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ1_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ1_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ1_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q1_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q1_INT_STS,
    // TCQ1 IOCTL's End

    // TCQ2 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ2_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC2_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC2_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ2_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ2_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ2_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q2_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q2_INT_STS,
    // TCQ2 IOCTL's End

    // TCQ3 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ3_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC3_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC3_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ3_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ3_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ3_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q3_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q3_INT_STS,
    // TCQ3 IOCTL's End

    // TCQ4 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ4_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC4_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC4_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ4_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ4_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ4_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q4_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q4_INT_STS,
    // TCQ4 IOCTL's End

    // TCQ5 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ5_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC5_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC5_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ5_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ5_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ5_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q5_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q5_INT_STS,
    // TCQ5 IOCTL's End

    // TCQ6 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ6_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC6_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC6_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_RXQ6_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ6_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ6_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q6_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q6_INT_STS,
    // TCQ6 IOCTL's End

    // TCQ7 IOCTL's Start
    IOCTL_XGMAC_MTL_SET_TXQ7_OP_MODE,
    IOCTL_XGMAC_MTL_SET_TC7_ETS_CTRL,
    IOCTL_XGMAC_MTL_SET_TC7_QWEIGHT,
    IOCTL_XGMAC_MTL_SET_TC7_SSCREDIT,
    IOCTL_XGMAC_MTL_SET_TC7_HCREDIT,
    IOCTL_XGMAC_MTL_SET_TC7_LCREDIT,
    IOCTL_XGMAC_MTL_SET_RXQ7_OP_MODE,
    IOCTL_XGMAC_MTL_SET_RXQ7_CTRL,
    IOCTL_XGMAC_MTL_SET_RXQ7_FCTRL,
    IOCTL_XGMAC_MTL_SET_Q7_INT_EN,
    IOCTL_XGMAC_MTL_SET_Q7_INT_STS,
    // TCQ7 IOCTL's End

    // DWCXG IOCTL DMA START
    IOCTL_XGMAC_DMA_MODE,
    IOCTL_XGMAC_GET_DMA_MODE,
    IOCTL_XGMAC_SET_DMA_MODE,
    IOCTL_XGMAC_GET_DMA_SYSBUS_MODE,
    IOCTL_XGMAC_SET_DMA_SYSBUS_MODE,
    IOCTL_XGMAC_GET_DMA_INTERRUPT_STATUS,
    IOCTL_XGMAC_SET_DMA_INTERRUPT_STATUS,
    IOCTL_XGMAC_GET_DMA_AXI_TX_AR_ACE_CONTROL,
    IOCTL_XGMAC_SET_DMA_AXI_TX_AR_ACE_CONTROL,
    IOCTL_XGMAC_GET_DMA_AXI_RX_AW_ACE_CONTROL,
    IOCTL_XGMAC_SET_DMA_AXI_RX_AW_ACE_CONTROL,
    IOCTL_XGMAC_GET_DMA_AXI_TXRX_AWAR_ACE_CONTROL,
    IOCTL_XGMAC_SET_DMA_AXI_TXRX_AWAR_ACE_CONTROL,
    IOCTL_XGMAC_GET_DMA_DEBUG_STATUS0,
    IOCTL_XGMAC_SET_DMA_DEBUG_STATUS0,
    IOCTL_XGMAC_GET_DMA_DEBUG_STATUS1,
    IOCTL_XGMAC_SET_DMA_DEBUG_STATUS1,
    IOCTL_XGMAC_GET_DMA_DEBUG_STATUS3,
    IOCTL_XGMAC_SET_DMA_DEBUG_STATUS3,
    IOCTL_XGMAC_GET_DMA_TX_EDMA_CONTROL,
    IOCTL_XGMAC_SET_DMA_TX_EDMA_CONTROL,
    IOCTL_XGMAC_GET_DMA_RX_EDMA_CONTROL,
    IOCTL_XGMAC_SET_DMA_RX_EDMA_CONTROL,
    IOCTL_XGMAC_GET_DMA_AXI_LPI_ENTRY_INTERVAL,
    IOCTL_XGMAC_SET_DMA_AXI_LPI_ENTRY_INTERVAL,
    IOCTL_XGMAC_GET_DMA_TBS_CONTROL0,
    IOCTL_XGMAC_SET_DMA_TBS_CONTROL0,
    IOCTL_XGMAC_GET_DMA_TBS_CONTROL1,
    IOCTL_XGMAC_SET_DMA_TBS_CONTROL1,
    IOCTL_XGMAC_GET_DMA_TBS_CONTROL2,
    IOCTL_XGMAC_SET_DMA_TBS_CONTROL2,
    IOCTL_XGMAC_GET_DMA_TBS_CONTROL3,
    IOCTL_XGMAC_SET_DMA_TBS_CONTROL3,
    IOCTL_XGMAC_GET_DMA_CH_IND_CTRL,
    IOCTL_XGMAC_SET_DMA_CH_IND_CTRL,
    IOCTL_XGMAC_GET_DMA_CH_IND_DATA,
    IOCTL_XGMAC_SET_DMA_CH_IND_DATA,

    // DMA Channel 0
    IOCTL_XGMAC_GET_DMA_CH0_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH0_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH0_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH0_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH0_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH0_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH0_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH0_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH0_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH0_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH0_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH0_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH0_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH0_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH0_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH0_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH0_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH0_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH0_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH0_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH0_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH0_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH0_STATUS,
    IOCTL_XGMAC_SET_DMA_CH0_STATUS,
    IOCTL_XGMAC_GET_DMA_CH0_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH0_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH0_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH0_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH0_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH0_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH0_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH0_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH0_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH0_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH0_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH0_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH0_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH0_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 1
    IOCTL_XGMAC_GET_DMA_CH1_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH1_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH1_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH1_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH1_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH1_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH1_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH1_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH1_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH1_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH1_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH1_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH1_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH1_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH1_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH1_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH1_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH1_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH1_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH1_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH1_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH1_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH1_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH1_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH1_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH1_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH1_STATUS,
    IOCTL_XGMAC_SET_DMA_CH1_STATUS,
    IOCTL_XGMAC_GET_DMA_CH1_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH1_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH1_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH1_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH1_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH1_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH1_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH1_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH1_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH1_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH1_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH1_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH1_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH1_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 2
    IOCTL_XGMAC_GET_DMA_CH2_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH2_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH2_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH2_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH2_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH2_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH2_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH2_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH2_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH2_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH2_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH2_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH2_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH2_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH2_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH2_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH2_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH2_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH2_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH2_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH2_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH2_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH2_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH2_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH2_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH2_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH2_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH2_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH2_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH2_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH2_STATUS,
    IOCTL_XGMAC_SET_DMA_CH2_STATUS,
    IOCTL_XGMAC_GET_DMA_CH2_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH2_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH2_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH2_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH2_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH2_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH2_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH2_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH2_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH2_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH2_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH2_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH2_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH2_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 3
    IOCTL_XGMAC_GET_DMA_CH3_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH3_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH3_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH3_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH3_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH3_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH3_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH3_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH3_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH3_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH3_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH3_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH3_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH3_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH3_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH3_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH3_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH3_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH3_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH3_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH3_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH3_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH3_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH3_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH3_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH3_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH3_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH3_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH3_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH3_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH3_STATUS,
    IOCTL_XGMAC_SET_DMA_CH3_STATUS,
    IOCTL_XGMAC_GET_DMA_CH3_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH3_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH3_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH3_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH3_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH3_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH3_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH3_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH3_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH3_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH3_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH3_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH3_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH3_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 4
    IOCTL_XGMAC_GET_DMA_CH4_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH4_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH4_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH4_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH4_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH4_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH4_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH4_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH4_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH4_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH4_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH4_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH4_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH4_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH4_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH4_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH4_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH4_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH4_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH4_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH4_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH4_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH4_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH4_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH4_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH4_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH4_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH4_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH4_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH4_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH4_STATUS,
    IOCTL_XGMAC_SET_DMA_CH4_STATUS,
    IOCTL_XGMAC_GET_DMA_CH4_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH4_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH4_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH4_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH4_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH4_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH4_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH4_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH4_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH4_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH4_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH4_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH4_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH4_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 5
    IOCTL_XGMAC_GET_DMA_CH5_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH5_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH5_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH5_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH5_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH5_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH5_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH5_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH5_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH5_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH5_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH5_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH5_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH5_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH5_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH5_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH5_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH5_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH5_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH5_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH5_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH5_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH5_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH5_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH5_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH5_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH5_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH5_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH5_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH5_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH5_STATUS,
    IOCTL_XGMAC_SET_DMA_CH5_STATUS,
    IOCTL_XGMAC_GET_DMA_CH5_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH5_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH5_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH5_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH5_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH5_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH5_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH5_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH5_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH5_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH5_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH5_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH5_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH5_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 6
    IOCTL_XGMAC_GET_DMA_CH6_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH6_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH6_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH6_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH6_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH6_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH6_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH6_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH6_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH6_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH6_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH6_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH6_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH6_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH6_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH6_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH6_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH6_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH6_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH6_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH6_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH6_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH6_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH6_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH6_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH6_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH6_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH6_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH6_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH6_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH6_STATUS,
    IOCTL_XGMAC_SET_DMA_CH6_STATUS,
    IOCTL_XGMAC_GET_DMA_CH6_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH6_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH6_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH6_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH6_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH6_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH6_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH6_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH6_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH6_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH6_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH6_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH6_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH6_RX_DESC_XFER_RING_OFFSET,

    // DMA Channel 7
    IOCTL_XGMAC_GET_DMA_CH7_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH7_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH7_TX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH7_TX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH7_RX_CONTROL,
    IOCTL_XGMAC_SET_DMA_CH7_RX_CONTROL,
    IOCTL_XGMAC_GET_DMA_CH7_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_SET_DMA_CH7_SLOT_FUNCTION_CONTROL_STATUS,
    IOCTL_XGMAC_GET_DMA_CH7_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH7_TXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH7_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH7_TXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH7_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_SET_DMA_CH7_RXDESC_LIST_HADDRESS,
    IOCTL_XGMAC_GET_DMA_CH7_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_SET_DMA_CH7_RXDESC_LIST_LADDRESS,
    IOCTL_XGMAC_GET_DMA_CH7_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH7_TXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH7_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_SET_DMA_CH7_RXDESC_TAIL_LPOINTER,
    IOCTL_XGMAC_GET_DMA_CH7_TX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH7_TX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH7_RX_CONTROL2,
    IOCTL_XGMAC_SET_DMA_CH7_RX_CONTROL2,
    IOCTL_XGMAC_GET_DMA_CH7_INTERRUPT_ENABLE,
    IOCTL_XGMAC_SET_DMA_CH7_INTERRUPT_ENABLE,
    IOCTL_XGMAC_GET_DMA_CH7_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_SET_DMA_CH7_RX_INTERRUPT_WATCHDOG_TIMER,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXDESC_L,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_TXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXBUFFER_H,
    IOCTL_XGMAC_GET_DMA_CH7_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_SET_DMA_CH7_CURRENT_APP_RXBUFFER_L,
    IOCTL_XGMAC_GET_DMA_CH7_STATUS,
    IOCTL_XGMAC_SET_DMA_CH7_STATUS,
    IOCTL_XGMAC_GET_DMA_CH7_DEBUG_STATUS,
    IOCTL_XGMAC_SET_DMA_CH7_DEBUG_STATUS,
    IOCTL_XGMAC_GET_DMA_CH7_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_SET_DMA_CH7_DESC_MEM_CACHE_FILL_LEVEL,
    IOCTL_XGMAC_GET_DMA_CH7_MISS_PACKET_CNT,
    IOCTL_XGMAC_SET_DMA_CH7_MISS_PACKET_CNT,
    IOCTL_XGMAC_GET_DMA_CH7_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH7_TX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH7_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH7_RX_DATA_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH7_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH7_TX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_GET_DMA_CH7_RX_DESC_XFER_RING_OFFSET,
    IOCTL_XGMAC_SET_DMA_CH7_RX_DESC_XFER_RING_OFFSET,
    // DWCXG_DMA IOCTL END
    // XGMAC IOCTL END
    IOCTL_XGMAC_END
} xgmac_ioctl_t;

// Descriptor structures & Defines
// For understanding of the descriptor settings read:
// DWC_xgmac_databook.pdf
#define DESC_TXSTS_OWNBYDMA (1 << 31)
#define DESC_TXSTS_TXFIRST (1 << 29)
#define DESC_TXSTS_TXLAST (1 << 28)
#define DESC_TXCTRL_IOC (1 << 31)
#define DESC_TX_PKT_LENMSK (0X7FFF << 0)
#define DESC_TX_PKT_LENSHIFT (0)
#define DESC_TXCTRL_SIZE1MASK (0x3FFF << 0)
#define DESC_HDR_TXCTRL_SIZE1MASK (0x3FFF << 0)
#define DESC_TXCTRL_SIZE1SHFT (0)
#define DESC_RXSTS_OWNBYDMA (1 << 31)
#define DESC_RXSTS_IOC (1 << 30)

// Defines noting interrupts from IOCTL_XGMAC_SET_DMA_CH#_STATUS
#define ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_TI_SET_MSK 0x00000001
#define ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_RI_SET_MSK 0x00000040
#define ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_RBU_SET_MSK 0x00000080
#define ALT_EMACX_DWCXG_DMA_CH0_DMA_CH0_STATUS_TBU_SET_MSK 0x00000004

// transmit descriptor
typedef struct {
    uint32_t header_or_buffer1_addr;  // Physical address of the data buffer1 - TDES0
    uint32_t buffer2_or_buffer1_addr; // Physical address of the data buffer2 - TDES1
    uint32_t control0;                // Control and status information (HL/BL1,B2L,TTSE,IOC) - TDES2
    uint32_t control1;                // Control and status information (OWN,CTXT,FD,LD,TSE,TPL,FL/TPL) - TDES3
} txDescr_t;

// receiver descriptor
typedef struct {
    volatile uint32_t bufferAddress;  // Physical address of the data buffer
    volatile uint32_t bufferAddress1; // Various control flags
    volatile uint32_t bufferAddress2; // Various control flags
    volatile uint32_t controlFlags;   // Reserved or additional control data
    // Other fields as defined by the NIC's datasheet
} rxDescr_t;

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      xgmac_recv
 * description:
 *      return 0
 */
size_t xgmac_recv(int32_t fd, uintptr_t user_data, size_t size, int32_t flags);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      xgmac_read
 * description:
 *      return 0
 */
size_t xgmac_read(int32_t fd, uintptr_t user_data, size_t size);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      xgmac_send
 * description:
 *      return 0
 */
size_t xgmac_send(int32_t fd, const uintptr_t user_data, size_t size, int32_t flags);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      xgmac_write
 * description:
 *      return 0
 */
size_t xgmac_write(int32_t fd, const uintptr_t user_data, size_t size);

/* name: xgmac_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t xgmac_open(const char *path, int32_t flags);

/* name: xgmac_close
 * description: close the fd via the base address of the device
 * parameters(s): base_add "address of the xgma device open"
 */
int32_t xgmac_close(int32_t base_add);

/* name: xgmac_ioctl
 * description: process the input output control command
 * parameters(s): base_add "address of the xgmac timer device open"
 *                operation "specific ioctl command for xgmac"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to
 */
int32_t xgmac_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length);

#endif // XGMAC_H__
