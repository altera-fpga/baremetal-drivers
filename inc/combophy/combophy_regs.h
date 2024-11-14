#ifndef COMBOPHY_REGS_H__
#define COMBOPHY_REGS_H__

/*
 * COMBOPHY Documentation Overview
 *  -- Register Map
 *     -- "i_combo_phy__combophy_reg_apb__10b92000"
 *  -- High-Level Architecture Specification
 *     --  "SM HPS COMBOPHY Controller HAS 1.1.pdf"
 */

// Base memory address for combo phy access
#define COMBOPHY_BASE 0x10B92000
#define COMBOPHY_DATASLICE_OFST 0x0
#define COMBOPHY_CTB_OFST 0x80

/* The struct declaration for the raw register contents of register group ALT_COMBO_PHY_DATASLICE. */

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t phy_dq_timing_reg;           /* Offset 0x00 */
    volatile uint32_t phy_dqs_timing_reg;          /* Offset 0x04 */
    volatile uint32_t phy_gate_lpbk_ctrl_reg;      /* Offset 0x08 */
    volatile uint32_t phy_dll_master_ctrl_reg;     /* Offset 0x0C */
    volatile uint32_t phy_dll_slave_ctrl_reg;      /* Offset 0x10 */
    volatile uint32_t phy_ie_timing_reg;           /* Offset 0x14 */
    volatile uint32_t phy_obs_reg_0;               /* Offset 0x18 */
    volatile uint32_t phy_dll_obs_reg_0;           /* Offset 0x1C */
    volatile uint32_t phy_dll_obs_reg_1;           /* Offset 0x20 */
    volatile uint32_t phy_dll_obs_reg_2;           /* Offset 0x24 */
    volatile uint32_t phy_static_togg_reg;         /* Offset 0x28 */
    volatile uint32_t phy_wr_deskew_reg;           /* Offset 0x2C */
    volatile uint32_t phy_wr_rd_deskew_cmd_reg;    /* Offset 0x30 */
    volatile uint32_t phy_wr_deskew_pd_ctrl_0_reg; /* Offset 0x34 */
    volatile uint32_t phy_wr_deskew_pd_ctrl_1_reg; /* Offset 0x38 */
    volatile uint32_t phy_rd_deskew_reg;           /* Offset 0x3C */
    volatile uint32_t _pad_0x40_0x6f[12];          /* *UNDEFINED* */
    volatile uint32_t phy_version_reg;             /* Offset 0x70 */
    volatile uint32_t phy_features_reg;            /* Offset 0x74 */
} combophy_dataslice_regs_words_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t phy_ctrl_reg; /* Offset 0x00 */
    volatile uint32_t phy_tsel_reg; /* Offset 0x04 */
} combophy_ctb_reg_words_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    combophy_dataslice_regs_words_t combo_phy_dataslice_regs_words_s;
    combophy_ctb_reg_words_t combo_phy_ctb_reg_words_s;
} combophy_regs_t;

#endif // COMBOPHY_REGS_H__
