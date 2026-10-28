/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */


/* File: socfpga_i2c_reg.h
 *
 * I2C register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef SOCFPGA_I2C_REG_H
#define SOCFPGA_I2C_REG_H

/* Synopsys DesignWare APB I2C register offsets. */
#define I2C_CON                         0x0000U
#define I2C_TAR                         0x0004U
#define I2C_SAR                         0x0008U
#define I2C_HS_MADDR                    0x000CU
#define I2C_DATA_CMD                    0x0010U
#define I2C_SS_SCL_HCNT                 0x0014U
#define I2C_SS_SCL_LCNT                 0x0018U
#define I2C_FS_SCL_HCNT                 0x001CU
#define I2C_FS_SCL_LCNT                 0x0020U
#define I2C_HS_SCL_HCNT                 0x0024U
#define I2C_HS_SCL_LCNT                 0x0028U
#define I2C_INTR_STAT                   0x002CU
#define I2C_INTR_MASK                   0x0030U
#define I2C_RAW_INTR_STAT               0x0034U
#define I2C_RX_TL                       0x0038U
#define I2C_TX_TL                       0x003CU
#define I2C_CLR_INTR                    0x0040U
#define I2C_CLR_RX_UNDER                0x0044U
#define I2C_CLR_RX_OVER                 0x0048U
#define I2C_CLR_TX_OVER                 0x004CU
#define I2C_CLR_RD_REQ                  0x0050U
#define I2C_CLR_TX_ABRT                 0x0054U
#define I2C_CLR_RX_DONE                 0x0058U
#define I2C_CLR_ACTIVITY                0x005CU
#define I2C_CLR_STOP_DET                0x0060U
#define I2C_CLR_START_DET               0x0064U
#define I2C_CLR_GEN_CALL                0x0068U
#define I2C_ENABLE                      0x006CU
#define I2C_STATUS                      0x0070U
#define I2C_TXFLR                       0x0074U
#define I2C_RXFLR                       0x0078U
#define I2C_SDA_HOLD                    0x007CU
#define I2C_TX_ABRT_SOURCE              0x0080U
#define I2C_DMA_CR                      0x0088U
#define I2C_DMA_TDLR                    0x008CU
#define I2C_DMA_RDLR                    0x0090U
#define I2C_SDA_SETUP                   0x0094U
#define I2C_ACK_GENERAL_CALL            0x0098U
#define I2C_ENABLE_STATUS               0x009CU
#define I2C_FS_SPKLEN                   0x00A0U
#define I2C_HS_SPKLEN                   0x00A4U
#define I2C_CLR_RESTART_DET             0x00A8U
#define I2C_COMP_PARAM_1                0x00F4U
#define I2C_COMP_VERSION                0x00F8U
#define I2C_COMP_TYPE                   0x00FCU

#define I2C_CON_MASTER_MODE_MASK        0x00000001U
#define I2C_CON_MASTER_MODE_POS         0U
#define I2C_CON_SPEED_MASK              0x00000006U
#define I2C_CON_SPEED_POS               1U
/* IC_CON.SPEED encoding; fast-plus shares the fast-mode value. */
#define I2C_CON_SPEED_SS                1U
#define I2C_CON_SPEED_FS                2U
#define I2C_CON_SPEED_HS                3U
#define I2C_CON_10BITADDR_MASTER_MASK   0x00000010U
#define I2C_CON_10BITADDR_MASTER_POS    4U
#define I2C_CON_RESTART_EN_MASK         0x00000020U
#define I2C_CON_RESTART_EN_POS          5U
#define I2C_CON_SLAVE_DISABLE_MASK      0x00000040U
#define I2C_CON_SLAVE_DISABLE_POS       6U

#define I2C_TAR_ADDR_MASK               0x000003FFU
#define I2C_TAR_ADDR_POS                0U

#define I2C_DATA_CMD_DAT_MASK           0x000000FFU
#define I2C_DATA_CMD_DAT_POS            0U
#define I2C_DATA_CMD_CMD_MASK           0x00000100U
#define I2C_DATA_CMD_CMD_POS            8U
#define I2C_DATA_CMD_STOP_MASK          0x00000200U
#define I2C_DATA_CMD_STOP_POS           9U
#define I2C_DATA_CMD_RESTART_MASK       0x00000400U
#define I2C_DATA_CMD_RESTART_POS        10U

#define I2C_INTR_RX_UNDER_MASK          0x00000001U
#define I2C_INTR_RX_UNDER_POS           0U
#define I2C_INTR_RX_OVER_MASK           0x00000002U
#define I2C_INTR_RX_OVER_POS            1U
#define I2C_INTR_RX_FULL_MASK           0x00000004U
#define I2C_INTR_RX_FULL_POS            2U
#define I2C_INTR_TX_OVER_MASK           0x00000008U
#define I2C_INTR_TX_OVER_POS            3U
#define I2C_INTR_TX_EMPTY_MASK          0x00000010U
#define I2C_INTR_TX_EMPTY_POS           4U
#define I2C_INTR_TX_ABRT_MASK           0x00000040U
#define I2C_INTR_TX_ABRT_POS            6U
#define I2C_INTR_STOP_DET_MASK          0x00000200U
#define I2C_INTR_STOP_DET_POS           9U

#define I2C_ENABLE_ENABLE_MASK          0x00000001U
#define I2C_ENABLE_ENABLE_POS           0U
#define I2C_ENABLE_ABORT_MASK           0x00000002U
#define I2C_ENABLE_ABORT_POS            1U

#define I2C_STATUS_ACTIVITY_MASK        0x00000001U
#define I2C_STATUS_ACTIVITY_POS         0U
#define I2C_STATUS_TFNF_MASK            0x00000002U
#define I2C_STATUS_TFNF_POS             1U
#define I2C_STATUS_TFE_MASK             0x00000004U
#define I2C_STATUS_TFE_POS              2U
#define I2C_STATUS_RFNE_MASK            0x00000008U
#define I2C_STATUS_RFNE_POS             3U
#define I2C_STATUS_RFF_MASK             0x00000010U
#define I2C_STATUS_RFF_POS              4U
#define I2C_STATUS_MST_ACTIVITY_MASK    0x00000020U
#define I2C_STATUS_MST_ACTIVITY_POS     5U

#define I2C_ENABLE_STATUS_IC_EN_MASK    0x00000001U
#define I2C_ENABLE_STATUS_IC_EN_POS     0U

#define I2C_TX_ABRT_7B_ADDR_NOACK_MASK  0x00000001U
#define I2C_TX_ABRT_10ADDR1_NOACK_MASK  0x00000002U
#define I2C_TX_ABRT_10ADDR2_NOACK_MASK  0x00000004U
#define I2C_TX_ABRT_TXDATA_NOACK_MASK   0x00000008U
#define I2C_TX_ABRT_GCALL_NOACK_MASK    0x00000010U
#define I2C_TX_ABRT_GCALL_READ_MASK     0x00000020U
#define I2C_TX_ABRT_HS_ACKDET_MASK      0x00000040U
#define I2C_TX_ABRT_SBYTE_ACKDET_MASK   0x00000080U
#define I2C_TX_ABRT_HS_NORSTRT_MASK     0x00000100U
#define I2C_TX_ABRT_SBYTE_NORSTRT_MASK  0x00000200U
#define I2C_TX_ABRT_10B_RD_NORSTRT_MASK 0x00000400U
#define I2C_TX_ABRT_MASTER_DIS_MASK     0x00000800U
#define I2C_TX_ABRT_ARB_LOST_MASK       0x00001000U
#define I2C_TX_ABRT_SLVFLUSH_TXFIFO_MASK 0x00002000U
#define I2C_TX_ABRT_SLV_ARBLOST_MASK    0x00004000U
#define I2C_TX_ABRT_SLVRD_INTX_MASK     0x00008000U

#define I2C_TX_ABRT_USER_ABRT_MASK      0x00010000U

#define I2C_TX_ABRT_ADDR_NOACK_MASK     (I2C_TX_ABRT_7B_ADDR_NOACK_MASK | \
                                         I2C_TX_ABRT_10ADDR1_NOACK_MASK | \
                                         I2C_TX_ABRT_10ADDR2_NOACK_MASK)

/* The upper bits count flushed TX bytes and must be masked off before the word
 * is read as a cause.
 */
#define I2C_TX_ABRT_CAUSE_MASK          0x007FFFFFU
#define I2C_TX_ABRT_FLUSH_CNT_MASK      0xFF800000U
#define I2C_TX_ABRT_FLUSH_CNT_POS       23U

#define I2C_COMP_PARAM_1_SPEED_MODE_MASK 0x0000000CU
#define I2C_COMP_PARAM_1_SPEED_MODE_POS  2U
#define I2C_COMP_PARAM_1_SPEED_MODE_HIGH 0x0000000CU
#define I2C_COMP_PARAM_1_RX_DEPTH_MASK   0x0000FF00U
#define I2C_COMP_PARAM_1_RX_DEPTH_POS    8U
#define I2C_COMP_PARAM_1_TX_DEPTH_MASK   0x00FF0000U
#define I2C_COMP_PARAM_1_TX_DEPTH_POS    16U

/* Reads back only on a controller that is clocked and out of reset. */
#define I2C_COMP_TYPE_VALUE             0x44570140U

#endif /* SOCFPGA_I2C_REG_H */
