#ifndef HPS_MAILBOX_REGS_H__
#define HPS_MAILBOX_REGS_H__

/*
 * HPS MAILBOX Documentation Overview

 */

// Endianness verification "Little Endian only supported"
#ifdef __BYTE_ORDER__
#if (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
#error "The processor setting's are invalid for the hps mailbox"
#endif
#else
#pragma message "Assuming the native endianness is little endian"
#endif

// Noted as external_master_mailbox within "i_mailbox_0x10A3_0000" documentation
#define HPS_MAILBOX_BASE 0x10A30000
#define HPS_MBOX_CMD_BUF_BASE 0x10A30040
#define HPS_MBOX_CMD_BUF_END 0x10A300BF
#define HPS_MBOX_RSP_BUF_BASE 0x10A300C0
#define HPS_MBOX_RSP_BUF_END 0x10A300FF
#define HPS_MBOX_DBELL_TOSDM 0x10A30400
#define HPS_MBOX_DBELL_TOHPS 0x10A30480

// All sizes are in "words" with a word defined as 4 bytes
#define HPS_COMMAND_BUF_SIZE (uint32_t)(32)
#define HPS_RESPONSE_BUF_SIZE (uint32_t)(16)
#define HPS_UNUSED_SPACE_SIZE (uint32_t)(192)
#define HPS_DOORBELL_SIZE_GAP (uint32_t)(31)
#define HPS_REG_MSG_BODY_SIZE (uint32_t)(31)
#define HPS_INDCT_MSG_BODY_SIZE (uint32_t)(29)
#define HPS_STREAM_SIZE (uint32_t)(0x3C00)

/*
 * structure denoting the base header elements for message
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t hps_mbox_cer_cd : 11; // Offset 0x00 "command/err code"
    volatile uint32_t hps_mbox_ind : 1;     // Offset 0x00 "Indirect versus direct indicator"
    volatile uint32_t hps_mbox_size : 11;   // Offset 0x00 "total count/length"
    volatile uint32_t hps_mbox_cksm : 1;    // Offset 0x00 "Checksum present bit"
    volatile uint32_t hps_mbox_cmd_id : 4;  // Offset 0x00 "command ID"
    volatile uint32_t hps_mbox_ch_cl : 4;   // Offset 0x00 "client/Channel ID"
} hps_mailbox_base_header_bits_t;

/*
 * structure denoting the header elements for indirect message
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    hps_mailbox_base_header_bits_t hps_mbox_bhdr; // "see relevant structure"
    volatile uint32_t hps_mbox_dct_count : 8;     // Offset 0x01 "direct count, argument count, response count"
    volatile uint32_t hps_mbox_arg_count : 8;     // Offset 0x01 "direct count, argument count, response count"
    volatile uint32_t hps_mbox_resp_count : 8;    // Offset 0x01 "direct count, argument count, response count"
    volatile uint32_t hps_mbox_unused : 8;        // Offset 0x01 "unused words"
    volatile uint32_t hps_mbox_direct_words : 8;  // Offset 0x01 "direct count words only"
} hps_mailbox_indirect_header_bits_t;

/*
 * structure denoting the elements for normal message
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    hps_mailbox_base_header_bits_t hps_mbox_nrm_bhdr;            // "see relevant structure"
    volatile uint32_t hps_mbox_norm_body[HPS_REG_MSG_BODY_SIZE]; // Remaining components for normal message "
} hps_mailbox_reg_msg_t;

/*
 * structure denoting the elements for indirect message
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    hps_mailbox_indirect_header_bits_t hps_mbox_Ndirect_bhdr;      // "see relevant structure"
    volatile uint32_t hps_mbox_ndrt_body[HPS_INDCT_MSG_BODY_SIZE]; // Remaining components for indirect message "
} hps_mailbox_indirect_msg_t;

/*
 * structure denoting the elements for within the flags register
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t hps_mbox_flag_coe : 1;    // Offset 0x0C "flags COUT update interrupt enable
    volatile uint32_t hps_mbox_flag_rie : 1;    // Offset 0x0C "flags RIN update interrupt enable
    volatile uint32_t hps_mbox_flag_rsvd : 6;   // Offset 0x0C "flags reserved 1
    volatile uint32_t hps_mbox_flag_uae : 1;    // Offset 0x0C "flags Urgent ACK Interrupt enable
    volatile uint32_t hps_mbox_flag_rsvd1 : 23; // Offset 0x0C "flags reserved 2
} hps_mailbox_flags_t;

/*
 * structure denoting the elements for within the Status register
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t hps_mbox_status_rsvd : 8; // Offset 0x2C "status reserved 1"
    volatile uint32_t hps_mbox_status_ua : 1;   // Offset 0x2C "status" urgent ack
    volatile uint32_t hps_mbox_status_thr : 1;  // Offset 0x2C "status source is being throttled"
    volatile uint32_t hps_mbox_status_adw : 1;  // Offset 0x2C "status Anti DoS warning"
    volatile uint32_t hps_mbox_status_ads : 1;  // Offset 0x2C "status Anti-DoS stopped"
    volatile uint32_t hps_mbox_flag_rsvd1 : 20; // Offset 0x2C "status reserved 2
} hps_mailbox_status_t;

/*
 * structure denoting the elements for within doorbells
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t hps_mbox_dbell_active : 1; // doorbell active bit
    volatile uint32_t hps_mbox_dbell_rsvd : 31;  // reserved bits
} hps_mailbox_dbell_t;

/*
 * structure yielding access to mailbox base structure
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t hps_mbox_cin;                                // Offset 0x00 "command Valid Offset"
    volatile uint32_t hps_mbox_rout;                               // Offset 0x04 "response output offset"
    volatile uint32_t hps_mbox_urg;                                // Offset 0x08 "urgent Command"
    volatile uint32_t hps_mbox_flags;                              // Offset 0x0C "flags
    volatile uint32_t hps_mbox_rsvd[4];                            // Offset 0x10 "reserved set 1"
    volatile uint32_t hps_mbox_cout;                               // Offset 0x20 "command free offset"
    volatile uint32_t hps_mbox_rin;                                // Offset 0x24 "response valid offset"
    volatile uint32_t hps_mbox_rsvd1;                              // Offset 0x28 "reserved set 2"
    volatile uint32_t hps_mbox_status;                             // Offset 0x2C "status"
    volatile uint32_t hps_mbox_rsvd3[4];                           // Offset 0x30 "reserved set 3"
    volatile uint32_t hps_mbox_cmd_buf[HPS_COMMAND_BUF_SIZE];      // Offset 0x40 "command buffer"
    volatile uint32_t hps_mbox_rsp_buf[HPS_RESPONSE_BUF_SIZE];     // Offset 0xC0 "response buffer"
    volatile uint32_t hps_mbox_taken_space[HPS_UNUSED_SPACE_SIZE]; // Offset 0x100 "space unused by HPS mailbox"
    volatile hps_mailbox_dbell_t hps_mbox_dbell_tosdm;             // Offset 0x400 "doorbell to sdm"
    volatile uint32_t hps_mbox_dbell_gap[HPS_DOORBELL_SIZE_GAP];   // Offset 0x404 gap between doorbells
    volatile hps_mailbox_dbell_t hps_mbox_dbell_tohps;             // Offset 0x480 "doorbell to hps"
    volatile uint32_t hps_mbox_stream; // Offset 0x500 "stream" This area is ~60k "HPS_STREAM_SIZE <-- words"
} hps_mailbox_regs_words_t;

#endif // HPS_MAILBOX_REGS_H__
