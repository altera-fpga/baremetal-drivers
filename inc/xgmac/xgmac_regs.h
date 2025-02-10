#ifndef XGMAC_REGS_H__
#define XGMAC_REGS_H__

#include <stddef.h>

/*
 *  XGMAC Documentation Overview

 */

// Endianness verification "Little Endian only supported"
#ifdef __BYTE_ORDER__
#if (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
#error "The processor setting's are invalid for the XGMAC"
#endif
#else
#pragma message "Assuming the native endianness is little endian"
#endif

#include "hps_address_map.h"

/*
 * structure denoting DWCXG_DMA_BASE
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t DMA_Mode;
    volatile uint32_t DMA_SysBus_Mode;
    volatile uint32_t DMA_Interrupt_Status;
    volatile uint32_t gap1; /* *UNDEFINED* */
    volatile uint32_t AXI_Tx_AR_ACE_Control;
    volatile uint32_t gap2; /* *UNDEFINED* */
    volatile uint32_t AXI_Rx_AW_ACE_Control;
    volatile uint32_t AXI_TxRx_AWAR_ACE_Control;
    volatile uint32_t DMA_Debug_Status0;
    volatile uint32_t DMA_Debug_Status1;
    volatile uint32_t gap3; /* *UNDEFINED* */
    volatile uint32_t DMA_Debug_Status3;
    volatile uint32_t gap4[4]; /* *UNDEFINED* */
    volatile uint32_t DMA_Tx_EDMA_Control;
    volatile uint32_t DMA_Rx_EDMA_Control;
    volatile uint32_t gap5[2]; /* *UNDEFINED* */
    volatile uint32_t AXI_LPI_Entry_Interval;
    volatile uint32_t DMA_TBS_CTRL0;
    volatile uint32_t DMA_TBS_CTRL1;
    volatile uint32_t DMA_TBS_CTRL2;
    volatile uint32_t DMA_TBS_CTRL3;
    volatile uint32_t gap6[7]; /* *UNDEFINED* */
    volatile uint32_t DMA_CH_Ind_Ctrl;
    volatile uint32_t DMA_CH_Ind_Data;
    volatile uint32_t gap7[30]; /* *UNDEFINED* */
} xgmac_dma_base_t;

/*
 * structure denoting DWCXG_DMA_CHANNEL
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t DMA_CH_Control;
    volatile uint32_t DMA_CH_Tx_Control;
    volatile uint32_t DMA_CH_Rx_Control;
    volatile uint32_t DMA_CH_Slot_Function_Control_Status;
    volatile uint32_t DMA_CH_TxDesc_List_HAddress;
    volatile uint32_t DMA_CH_TxDesc_List_LAddress;
    volatile uint32_t DMA_CH_RxDesc_List_HAddress;
    volatile uint32_t DMA_CH_RxDesc_List_LAddress;
    volatile uint32_t gap1; /* *UNDEFINED* */
    volatile uint32_t DMA_CH_TxDesc_Tail_LPointer;
    volatile uint32_t gap2; /* *UNDEFINED* */
    volatile uint32_t DMA_CH_RxDesc_Tail_LPointer;
    volatile uint32_t DMA_CH_Tx_Control2;
    volatile uint32_t DMA_CH_Rx_Control2;
    volatile uint32_t DMA_CH_Interrupt_Enable;
    volatile uint32_t DMA_CH_Rx_Interrupt_Watchdog_Timer;
    volatile uint32_t gap3; /* *UNDEFINED* */
    volatile uint32_t DMA_CH_Current_App_TxDesc_L;
    volatile uint32_t gap4; /* *UNDEFINED* */
    volatile uint32_t DMA_CH_Current_App_RxDesc_L;
    volatile uint32_t DMA_CH_Current_App_TxBuffer_H;
    volatile uint32_t DMA_CH_Current_App_TxBuffer_L;
    volatile uint32_t DMA_CH_Current_App_RxBuffer_H;
    volatile uint32_t DMA_CH_Current_App_RxBuffer_L;
    volatile uint32_t DMA_CH_Status;
    volatile uint32_t DMA_CH_Debug_Status;
    volatile uint32_t DMA_CH_Desc_Mem_Cache_Fill_Level;
    volatile uint32_t DMA_CH_Miss_Packet_Cnt;
    volatile uint32_t DMA_CH_Tx_Data_Xfer_Ring_Offset;
    volatile uint32_t DMA_CH_Rx_Data_Xfer_Ring_Offset;
    volatile uint32_t DMA_CH_Tx_Desc_Write_Ring_Offset;
    volatile uint32_t DMA_CH_Rx_Desc_Write_Ring_Offset;
} xgmac_dma_ch_t;

/*
 * structure denoting DWCXG_DMA
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    xgmac_dma_base_t dma_base;
    xgmac_dma_ch_t dma_ch[8];
} xgmac_dma_t;

/*
 * structure denoting DWCXG_CORE/MAC elements
 * This structure covers offset 0x000 - 0xDD0
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t mac_tx_cfg;
    volatile uint32_t mac_rx_cfg;
    volatile uint32_t mac_pkt_fltr;
    volatile uint32_t mac_wdt_jb_tout;
    volatile uint32_t mac_hash_tbl_reg0;
    volatile uint32_t mac_hash_tbl_reg1;
    uint32_t gap1[14];
    volatile uint32_t mac_vlan_tag_ctrl;
    volatile uint32_t mac_vlan_tag_dt;
    volatile uint32_t mac_vlan_hash_tbl;
    uint32_t gap2;
    volatile uint32_t mac_vlan_incl;
    volatile uint32_t mac_in_vlan_incl;
    uint32_t gap3;
    volatile uint32_t mac_rx_eth_tp_mch;
    volatile uint32_t mac_q0_tx_fl_ctrl;
    volatile uint32_t mac_q1_tx_fl_ctrl;
    volatile uint32_t mac_q2_tx_fl_ctrl;
    volatile uint32_t mac_q3_tx_fl_ctrl;
    volatile uint32_t mac_q4_tx_fl_ctrl;
    volatile uint32_t mac_q5_tx_fl_ctrl;
    volatile uint32_t mac_q6_tx_fl_ctrl;
    volatile uint32_t mac_q7_tx_fl_ctrl;
    volatile uint32_t mac_rx_fl_ctrl;
    volatile uint32_t mac_rxq_ctrl4;
    volatile uint32_t mac_rxq_ctrl5;
    uint32_t gap3x;
    volatile uint32_t mac_rxq_ctrl0;
    volatile uint32_t mac_rxq_ctrl1;
    volatile uint32_t mac_rxq_ctrl2;
    volatile uint32_t mac_rxq_ctrl3;
    volatile uint32_t mac_int_sts;
    volatile uint32_t mac_int_en;
    volatile uint32_t mac_rx_tx_sts;
    uint32_t gap4[5];
    volatile uint32_t mac_lpi_ctr_sts;
    volatile uint32_t mac_lpi_tm_ctrl;
    volatile uint32_t mac_lpi_au_en_tm;
    volatile uint32_t mac_us_tk_cntr;
    uint32_t gap5[12];
    volatile uint32_t mac_ver;
    volatile uint32_t mac_dbg;
    uint32_t gap6;
    volatile uint32_t mac_hw_feat0;
    volatile uint32_t mac_hw_feat1;
    volatile uint32_t mac_hw_feat2;
    volatile uint32_t mac_hw_feat3;
    volatile uint32_t mac_hw_feat4;
    uint32_t gap7[4];
    volatile uint32_t mac_ext_cfg;
    volatile uint32_t mac_ext_cfg1;
    uint32_t gap8[46];

    // MDIO "Management Data Input/Output" registers Start
    volatile uint32_t mdio_sgl_cmd_addr;
    volatile uint32_t mdio_sgl_cmd_ctrl_dt;
    volatile uint32_t mdio_cnt_wrt_addr;
    volatile uint32_t mdio_cnt_wrt_dt;
    volatile uint32_t mdio_cnt_scan_pt_en;
    volatile uint32_t mdio_int_sts;
    volatile uint32_t mdio_int_en;
    volatile uint32_t mdio_port_ct_dct_sts;
    volatile uint32_t mdio_cls22_port;
    volatile uint32_t mdio_port_nx4_idrt_ctrl;
    uint32_t gap9[2];
    volatile uint32_t mdio_portnx4p0_dev_in_use;
    volatile uint32_t mdio_portnx4p0_lnk_sts;
    volatile uint32_t mdio_portnx4p0_alv_sts;
    uint32_t gap10;
    volatile uint32_t mdio_portnx4p1_dev_in_use;
    volatile uint32_t mdio_portnx4p1_lnk_sts;
    volatile uint32_t mdio_portnx4p1_alv_sts;
    uint32_t gap11;
    volatile uint32_t mdio_portnx4p2_dev_in_use;
    volatile uint32_t mdio_portnx4p2_lnk_sts;
    volatile uint32_t mdio_portnx4p2_alv_sts;
    uint32_t gap12;
    volatile uint32_t mdio_portnx4p3_dev_in_use;
    volatile uint32_t mdio_portnx4p3_lnk_sts;
    volatile uint32_t mdio_portnx4p3_alv_sts;
    uint32_t gap13[5];
    // MDIO "Management Data Input/Output" registers END

    volatile uint32_t mac_fpe_ctrl_sts;
    uint32_t gap14[3];
    volatile uint32_t mac_csr_sw_ctrl;
    uint32_t gap15[27];
    volatile uint32_t mac_addr0_high;
    volatile uint32_t mac_addr0_low;
    volatile uint32_t mac_addr1_high;
    volatile uint32_t mac_addr1_low;
    volatile uint32_t mac_addr2_high;
    volatile uint32_t mac_addr2_low;
    volatile uint32_t mac_addr3_high;
    volatile uint32_t mac_addr3_low;
    volatile uint32_t mac_addr4_high;
    volatile uint32_t mac_addr4_low;
    volatile uint32_t mac_addr5_high;
    volatile uint32_t mac_addr5_low;
    volatile uint32_t mac_addr6_high;
    volatile uint32_t mac_addr6_low;
    volatile uint32_t mac_addr7_high;
    volatile uint32_t mac_addr7_low;
    volatile uint32_t mac_addr8_high;
    volatile uint32_t mac_addr8_low;
    volatile uint32_t mac_addr9_high;
    volatile uint32_t mac_addr9_low;
    volatile uint32_t mac_addr10_high;
    volatile uint32_t mac_addr10_low;
    volatile uint32_t mac_addr11_high;
    volatile uint32_t mac_addr11_low;
    volatile uint32_t mac_addr12_high;
    volatile uint32_t mac_addr12_low;
    volatile uint32_t mac_addr13_high;
    volatile uint32_t mac_addr13_low;
    volatile uint32_t mac_addr14_high;
    volatile uint32_t mac_addr14_low;
    volatile uint32_t mac_addr15_high;
    volatile uint32_t mac_addr15_low;
    volatile uint32_t mac_addr16_high;
    volatile uint32_t mac_addr16_low;
    volatile uint32_t mac_addr17_high;
    volatile uint32_t mac_addr17_low;
    volatile uint32_t mac_addr18_high;
    volatile uint32_t mac_addr18_low;
    volatile uint32_t mac_addr19_high;
    volatile uint32_t mac_addr19_low;
    volatile uint32_t mac_addr20_high;
    volatile uint32_t mac_addr20_low;
    volatile uint32_t mac_addr21_high;
    volatile uint32_t mac_addr21_low;
    volatile uint32_t mac_addr22_high;
    volatile uint32_t mac_addr22_low;
    volatile uint32_t mac_addr23_high;
    volatile uint32_t mac_addr23_low;
    volatile uint32_t mac_addr24_high;
    volatile uint32_t mac_addr24_low;
    volatile uint32_t mac_addr25_high;
    volatile uint32_t mac_addr25_low;
    volatile uint32_t mac_addr26_high;
    volatile uint32_t mac_addr26_low;
    volatile uint32_t mac_addr27_high;
    volatile uint32_t mac_addr27_low;
    volatile uint32_t mac_addr28_high;
    volatile uint32_t mac_addr28_low;
    volatile uint32_t mac_addr29_high;
    volatile uint32_t mac_addr29_low;
    volatile uint32_t mac_addr30_high;
    volatile uint32_t mac_addr30_low;
    volatile uint32_t mac_addr31_high;
    volatile uint32_t mac_addr31_low;
    uint32_t gap16[192];
    volatile uint32_t mac_ind_acc_ctrl;
    volatile uint32_t mac_ind_acc_data;
    uint32_t gap17[62];

    volatile uint32_t mmc_ctrl;
    volatile uint32_t mmc_rx_int;
    volatile uint32_t mmc_tx_int;
    volatile uint32_t mmc_rx_int_en;
    volatile uint32_t mmc_tx_int_en;

    // Transmit specific registers START
    volatile uint32_t tx_oct_cnt_gbl;
    volatile uint32_t tx_oct_cnt_gbh;
    volatile uint32_t tx_pkt_cnt_gbl;
    uint32_t gap18;
    volatile uint32_t tx_bcst_cnt_gl;
    uint32_t gap19;
    volatile uint32_t tx_mcst_cnt_gl;
    uint32_t gap20;
    volatile uint32_t tx_64oct_pkt_gbl;
    uint32_t gap21;
    volatile uint32_t tx_65_127_oct_pkt_gbl;
    uint32_t gap22;
    volatile uint32_t tx_128_255_oct_pkt_gbl;
    uint32_t gap23;
    volatile uint32_t tx_256_511_oct_pkt_gbl;
    uint32_t gap24;
    volatile uint32_t tx_512_1023_oct_pkt_gbl;
    uint32_t gap25;
    volatile uint32_t tx_1024_max_oct_pkt_gbl;
    uint32_t gap26;
    volatile uint32_t tx_ucst_pkt_gbl;
    uint32_t gap27;
    volatile uint32_t tx_mcst_pkt_gbl;
    uint32_t gap28;
    volatile uint32_t tx_bcst_pkt_gbl;
    uint32_t gap29;
    volatile uint32_t tx_uflw_err_pkt_gbl;
    uint32_t gap30;
    volatile uint32_t tx_oct_cnt_gl;
    volatile uint32_t tx_oct_cnt_gh;
    volatile uint32_t tx_pkt_cnt_gl;
    uint32_t gap31;
    volatile uint32_t tx_pause_pkt_low;
    uint32_t gap32;
    volatile uint32_t tx_vlan_pkt_gl;
    uint32_t gap33;
    volatile uint32_t tx_lpi_usec_cntr;
    volatile uint32_t tx_lpi_tran_cntr;
    uint32_t gap34[21];
    // Transmit specific registers END

    // Receive specific registers Start
    volatile uint32_t rx_pkt_cnt_gbl;
    uint32_t gap35;
    volatile uint32_t rx_oct_cnt_gbl;
    volatile uint32_t rx_oct_cnt_gbh;
    volatile uint32_t rx_oct_gl;
    volatile uint32_t rx_oct_gh;
    volatile uint32_t rx_bcst_pkt_gl;
    uint32_t gap36;
    volatile uint32_t rx_mcst_pkt_gl;
    uint32_t gap37;
    volatile uint32_t rx_crc_err_pkt_low;
    uint32_t gap38;
    volatile uint32_t rx_runt_err_pkt;
    volatile uint32_t rx_jb_err_pkt;
    volatile uint32_t rx_usze_pkt_gd;
    volatile uint32_t rx_osze_pkt_gd;
    volatile uint32_t rx_64_oct_pkt_gbl;
    uint32_t gap39;
    volatile uint32_t rx_65_127_oct_pkt_gbl;
    uint32_t gap40;
    volatile uint32_t rx_128_255_oct_pkt_gbl;
    uint32_t gap41;
    volatile uint32_t rx_256_511_oct_pkt_gbl;
    uint32_t gap42;
    volatile uint32_t rx_512_1023_oct_pkt_gbl;
    uint32_t gap43;
    volatile uint32_t rx_1024_max_oct_pkt_gbl;
    uint32_t gap44;
    volatile uint32_t rx_ucst_pkt_gl;
    uint32_t gap45;
    volatile uint32_t rx_lth_er_pkt_low;
    uint32_t gap46;
    volatile uint32_t rx_outrng_pkt_low;
    uint32_t gap47;
    volatile uint32_t rx_pause_pkt_low;
    uint32_t gap48;
    volatile uint32_t rx_fifo_oflw_pkt_low;
    uint32_t gap49;
    volatile uint32_t rx_vlan_pkt_gbl;
    uint32_t gap50;
    volatile uint32_t rx_wdt_er_pkt;
    volatile uint32_t rx_lpi_usec_cntr;
    volatile uint32_t rx_tran_cntr;
    volatile uint32_t rx_dcrd_pkt_gbl;
    uint32_t gap51;
    volatile uint32_t rx_dcrd_oct_gbl;
    volatile uint32_t rx_dcrd_oct_gbh;
    volatile uint32_t rx_algn_err_pkt;
    uint32_t gap52[16];
    // Receive specific registers END

    // MMC specific registers start
    volatile uint32_t mmc_fpe_tx_int;
    volatile uint32_t mmc_fpe_tx_int_mask;
    volatile uint32_t mmc_tx_fpe_frag_cntr;
    volatile uint32_t mmc_tx_hold_req_cntr;
    uint32_t gap53[4];
    volatile uint32_t mmc_fpe_rx_int;
    volatile uint32_t mmc_fpe_rx_int_mask;
    volatile uint32_t mmc_rx_pkt_assm_er_cntr;
    volatile uint32_t mmc_rx_pkt_smd_er_cntr;
    volatile uint32_t mmc_rx_pkt_assm_ok_cntr;
    volatile uint32_t mmc_rx_fpe_frag_cntr;
    uint32_t gap54[2];
    // MMC specific registers END

    // TX packet stat's
    volatile uint32_t tx_sgl_col_gpkt;
    volatile uint32_t tx_mtl_col_gpkt;
    volatile uint32_t tx_dferd_gpkt;
    volatile uint32_t tx_lt_col_epkt;
    volatile uint32_t tx_exc_col_epkt;
    volatile uint32_t tx_carr_err_epkt;
    volatile uint32_t tx_exc_dferd_epkt;
    // TX packet stat's

    // MMC IPC registers
    volatile uint32_t mmc_ipc_rx_int_mask;
    volatile uint32_t mmc_ipc_rx_int;

    // RX IPV4 registers START
    volatile uint32_t rx_ipv4_gd_pkt_low;
    uint32_t gap55x;
    volatile uint32_t rx_ipv4_hdr_err_pkt_low;
    uint32_t gap55;
    volatile uint32_t rx_ipv4_no_pyld_pkt_low;
    uint32_t gap56;
    volatile uint32_t rx_ipv4_frag_pkt_low;
    uint32_t gap57;
    volatile uint32_t rx_ipv4_udp_cksm_dsbl_pkt_low;
    uint32_t gap58;
    // RX IPV4 registers END

    // RX IPV6 registers Start
    volatile uint32_t rx_ipv6_gd_pkt_low;
    uint32_t gap59;
    volatile uint32_t rx_ipv6_hdr_err_pkt_low;
    uint32_t gap60x;
    volatile uint32_t rx_ipv6_no_pyld_pkt_low;
    uint32_t gap60;
    // RX IPV6 registers END

    // RX UDP registers Start
    volatile uint32_t rx_udp_gd_pkt_low;
    uint32_t gap61;
    volatile uint32_t rx_udp_ecks_pkt_low;
    uint32_t gap62;
    // RX UDP registers End

    // RX TCP registers Start
    volatile uint32_t rx_tcp_gd_pkt_low;
    uint32_t gap63;
    volatile uint32_t rx_tcp_ecks_pkt_low;
    uint32_t gap64;
    // RX TCP registers End

    // RX ICMP registers Start
    volatile uint32_t rx_icmp_gd_pkt_low;
    uint32_t gap65;
    volatile uint32_t rx_icmp_ecks_pkt_low;
    uint32_t gap66;
    // RX IPV4 "continuation"
    volatile uint32_t rx_ipv4_gd_oct_low;
    uint32_t gap67;
    volatile uint32_t rx_ipv4_hecks_oct_low;
    uint32_t gap68;
    volatile uint32_t rx_ipv4_no_pyld_oct_low;
    uint32_t gap69;
    volatile uint32_t rx_ipv4_frag_oct_low;
    uint32_t gap70;
    volatile uint32_t rx_ipv4_udp_ck_dbl_oct_low;
    uint32_t gap71;

    // RX IPV6 "continuation"
    volatile uint32_t rx_ipv6_gd_oct_low;
    uint32_t gap72;
    volatile uint32_t rx_ipv6_hdr_err_oct_low;
    uint32_t gap73;
    volatile uint32_t rx_ipv6_no_pyld_oct_low;
    uint32_t gap74;

    volatile uint32_t rx_udp_gd_oct_low;
    uint32_t gap75;
    volatile uint32_t rx_udp_ecks_oct_low;
    uint32_t gap76;

    volatile uint32_t rx_tcp_gd_oct_low;
    uint32_t gap77;
    volatile uint32_t rx_tcp_ecks_oct_low;
    uint32_t gap78;

    volatile uint32_t rx_icmp_gd_oct_low;
    uint32_t gap79;
    volatile uint32_t rx_icmp_ecks_oct_low;
    uint32_t gap80[48];

    // MAC specific registers "continuation"
    volatile uint32_t mac_l3_l4_addr_ctrl;
    volatile uint32_t mac_l3_l4_data;
    uint32_t gap81[2];
    volatile uint32_t mac_arp_addr;
    uint32_t gap82[59];
    volatile uint32_t mac_tmstamp_ctrl;
    volatile uint32_t mac_sub_sec_incr;
    volatile uint32_t mac_sys_tm_sec;
    volatile uint32_t mac_sys_tm_nsec;
    volatile uint32_t mac_sys_tm_sec_updt;
    volatile uint32_t mac_sys_tm_nsec_updt;
    volatile uint32_t mac_tmstamp_addend;
    volatile uint32_t mac_sys_tm_hgh_wrd_sec;
    volatile uint32_t mac_tmstamp_sts;
    uint32_t gap83[3];
    volatile uint32_t mac_tx_tmstamp_sts_nsec;
    volatile uint32_t mac_tx_tmstamp_sts_sec;
    volatile uint32_t mac_tx_tmstamp_sts_pktid;
    uint32_t gap84;
    volatile uint32_t mac_aux_tmstamp_ctrl;
    uint32_t gap85;
    volatile uint32_t mac_aux_tmstamp_nsec;
    volatile uint32_t mac_aux_tmstamp_sec;
    volatile uint32_t mac_tmstamp_ingr_asym_corr;
    volatile uint32_t mac_tmstamp_egr_asym_corr;
    volatile uint32_t mac_tmstamp_ingr_corr_nsec;
    volatile uint32_t mac_tmpsatmp_ingr_corr_subnsec;
    volatile uint32_t mac_tmpstamp_egr_corr_nsec;
    volatile uint32_t mac_tmpstamp_egr_corr_subnsec;
    uint32_t gap86[2];
    volatile uint32_t mac_pps_ctrl;
    uint32_t gap87[3];
    volatile uint32_t mac_pps0_trg_tm_sec;
    volatile uint32_t mac_pps0_trg_tm_nsec;
    volatile uint32_t mac_pps0_intv;
    volatile uint32_t mac_pps0_wdh;
    volatile uint32_t mac_pps1_trg_tm_sec;
    volatile uint32_t mac_pps1_trg_tm_nsec;
    volatile uint32_t mac_pps1_intv;
    volatile uint32_t mac_pps1_wdh;
    uint32_t gap88[8];
    volatile uint32_t mac_pto_ctrl;
    volatile uint32_t mac_src_pt_iden0;
    volatile uint32_t mac_src_pt_iden1;
    volatile uint32_t mac_src_pt_iden2;
    volatile uint32_t mac_log_msg_intv; // Offset 0DD0 "Final Element of DWCXG_CORE" --
} xgmac_core_t;
/*
 * structure denoting DWCXG_BASE_MTL elements
 * This structure covers offset 0x1000 - 0x1097
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t mtl_op_mode;
    volatile uint32_t gap0[7];
    volatile uint32_t mtl_interrupt_sts;
    volatile uint32_t gap1[3];
    volatile uint32_t mtl_rxq_dma_m0;
    volatile uint32_t mtl_rxq_dma_m1;
    volatile uint32_t gap2[2];
    volatile uint32_t mtl_prty_m0;
    volatile uint32_t mtl_prty_m1;
    volatile uint32_t mtl_tbs_ctrl;
    volatile uint32_t mtl_tbs_sts;
    volatile uint32_t mtl_est_ctrl;
    volatile uint32_t mtl_est_ovrhd;
    volatile uint32_t mtl_est_sts;
    volatile uint32_t gap3;
    volatile uint32_t mtl_est_sch_err;
    volatile uint32_t mtl_est_frm_szerr;
    volatile uint32_t mtl_est_frm_cptr;
    volatile uint32_t gap4;
    volatile uint32_t mtl_est_int_en;
    volatile uint32_t gap5[3];
    volatile uint32_t mtl_gcl_ctrl;
    volatile uint32_t mtl_gcl_data;
    volatile uint32_t gap6[2];
    volatile uint32_t mtl_fpe_ctrl_sts;
    volatile uint32_t mtl_fpe_adv;
} xgmac_mtl_base_t;

/*
 * structure denoting DWCXG_TCQ_MTL elements 0-6
 * This structure covers offsets 0x1100 - 0x1477
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t mtl_txqN_op_mode;
    volatile uint32_t mtl_txqN_unflow;
    volatile uint32_t mtl_txqN_dbg;
    uint32_t gap0;
    volatile uint32_t mtl_tcN_ets_ctrl;
    volatile uint32_t mtl_tcN_ets_sts;
    volatile uint32_t mtl_tcN_qntm_wght;
    uint32_t gap1[9];
    volatile uint32_t mtl_rxqN_op_mode;
    volatile uint32_t mtl_rxqN_msd_pkt_ocnt;
    volatile uint32_t mtl_rxqN_dbg;
    volatile uint32_t mtl_rxqN_ctrl;
    volatile uint32_t mtl_rxqN_fctrl;
    uint32_t gap2[7];
    volatile uint32_t mtl_qN_int_en;
    volatile uint32_t mtl_qN_int_sts;
    uint32_t gap3[2];
} xgmac_mtl_tcq0_6_t;

/*
 * structure denoting DWCXG_TCQ_MTL element 7
 * This structure covers offsets 0x1480 - 0x14F4
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t mtl_txq7_op_mode;
    volatile uint32_t mtl_txq7_unflow;
    volatile uint32_t mtl_txq7_dbg;
    volatile uint32_t gap0;
    volatile uint32_t mtl_tc7_ets_ctrl;
    volatile uint32_t mtl_tc7_ets_sts;
    volatile uint32_t mtl_tc7_qntm_wght;
    volatile uint32_t mtl_tc7_snd_slp_credit;
    volatile uint32_t mtl_tc7_hi_credit;
    volatile uint32_t mtl_tc7_low_credit;
    volatile uint32_t gap1[6];
    volatile uint32_t mtl_rxq7_op_mode;
    volatile uint32_t mtl_rxq7_msd_pkt_ocnt;
    volatile uint32_t mtl_rxq7_dbg;
    volatile uint32_t mtl_rxq7_ctrl;
    volatile uint32_t mtl_rxq7_fctrl;
    uint32_t gap2[7];
    volatile uint32_t mtl_q7_int_en;
    volatile uint32_t mtl_q7_int_sts;
} xgmac_mtl_tcq7_t;

/*
 * structure denoting DWCXG_BASE_MTL elements
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    xgmac_mtl_base_t xgmac_mtl_base;
    uint32_t gap0[26]; // 2 word gap from offset 1098 - 10FF
    xgmac_mtl_tcq0_6_t xgmac_mtl_tcq0_6g[7];
    xgmac_mtl_tcq7_t xgmac_mtl_tcq_7g;
} xgmac_mtl_t;

/*
 * structure denoting DWCXG_(DMA,MTL & CORE) elements
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    xgmac_core_t xgmac_core;
    uint32_t gap0[139]; // 0xDD4 - 0xFFF
    xgmac_mtl_t xgmac_mtl;
    uint32_t gap[1730];
    xgmac_dma_t xgmac_dma;
} xgmac_t;

#endif // XGMAC_REGS_H__
