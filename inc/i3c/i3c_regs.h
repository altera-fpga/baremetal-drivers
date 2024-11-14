#ifndef I3C_REGS_H__
#define I3C_REGS_H__

#include <stdint.h>

#include "system.h"

// I3C Command & Reesponse Data structure
#define I3C_RESP_DATA_LENGTH_MASK (uint32_t)(0x0000FFFFU)
#define I3C_RESP_DATA_ID_MASK (uint32_t)(0x0F000000U)
#define I3C_RESP_ERR_STATUS_MASK (uint32_t)(0xF0000000U)

// IBI
// bitmask for IBI_STS in IBI_QUEUE_STATUS register
#define I3C_IBI_QUEUE_STATUS_IBI_STS_NACK_MASK (uint32_t)(0x8)
// IBI_STS in SLV_IBI_RESP
// 2'b00: Reserved
// 2'b01: IBI accepted by the Master (ACK response received)
// 2'b10: Master Early Terminate (only for SIR with Data).
// 2'b11: IBI Not Attempted
#define I3C_SLV_IBI_RESP_IBI_STS_ACK (uint32_t)(0x1)
#define I3C_SLV_IBI_RESP_IBI_STS_EARLY_TERM (uint32_t)(0x2)
#define I3C_SLV_IBI_RESP_IBI_STS_NOT_ATTEMPTED (uint32_t)(0x3)

#define I3C_DEVICE_CTRL_IBA_INCLUDE_OFST (uint32_t)(0)
#define I3C_DEVICE_CTRL_IBA_INCLUDE_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_IBA_INCLUDE_OFST)

#define I3C_DEVICE_CTRL_I2C_PRESENT_OFST (uint32_t)(7)
#define I3C_DEVICE_CTRL_I2C_PRESENT_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_I2C_PRESENT_OFST)

#define I3C_DEVICE_CTRL_HOT_JOIN_OFST (uint32_t)(8)
#define I3C_DEVICE_CTRL_HOT_JOIN_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_HOT_JOIN_OFST)

#define I3C_DEVICE_CTRL_DMA_ENABLE_OFST (uint32_t)(28)
#define I3C_DEVICE_CTRL_DMA_ENABLE_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_DMA_ENABLE_OFST)

#define I3C_DEVICE_CTRL_ABORT_OFST (uint32_t)(29)
#define I3C_DEVICE_CTRL_ABORT_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_ABORT_OFST)

#define I3C_DEVICE_CTRL_RESUME_OFST (uint32_t)(30)
#define I3C_DEVICE_CTRL_RESUME_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_RESUME_OFST)

#define I3C_DEVICE_CTRL_ENABLE_OFST (uint32_t)(31)
#define I3C_DEVICE_CTRL_ENABLE_MASK ((uint32_t)(0x1) << I3C_DEVICE_CTRL_ENABLE_OFST)

#define I3C_DEV_CHAR_TABLE_PTR_IDX_OFST (uint32_t)(19)
#define I3C_DEV_CHAR_TABLE_PTR_IDX_MASK ((uint32_t)(0x7) << I3C_DEV_CHAR_TABLE_PTR_IDX_OFST)

#define I3C_DEV_CHAR_TABLE_BASE_BYTE_OFST (uint32_t)(0x200)

#define I3C_DEV_ADDR_TABLE_BASE_BYTE_OFST (uint32_t)(0x280)

#define I3C_INTR_STATUS_TX_THLD_STS_OFST (uint32_t)(0)
#define I3C_INTR_STATUS_TX_THLD_STS_MASK ((uint32_t)(0x1) << I3C_INTR_STATUS_TX_THLD_STS_OFST)

#define I3C_INTR_STATUS_RX_THLD_STS_OFST (uint32_t)(1)
#define I3C_INTR_STATUS_RX_THLD_STS_MASK ((uint32_t)(0x1) << I3C_INTR_STATUS_RX_THLD_STS_OFST)

#define I3C_INTR_STATUS_IBI_THLD_STS_OFST (uint32_t)(2)
#define I3C_INTR_STATUS_IBI_THLD_STS_MASK ((uint32_t)(0x1) << I3C_INTR_STATUS_IBI_THLD_STS_OFST)

#define I3C_INTR_STATUS_CMD_QUEUE_READY_STS_OFST (uint32_t)(3)
#define I3C_INTR_STATUS_CMD_QUEUE_READY_STS_MASK ((uint32_t)(0x1) << I3C_INTR_STATUS_CMD_QUEUE_READY_STS_OFST)

#define I3C_INTR_STATUS_RESP_READY_STS_OFST (uint32_t)(4)
#define I3C_INTR_STATUS_RESP_READY_STS_MASK ((uint32_t)(0x1) << I3C_INTR_STATUS_RESP_READY_STS_OFST)

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t DEVICE_CTRL;                 /* ALT_I3C_DEVICE_CTRL */
    volatile uint32_t DEVICE_ADDR;                 /* ALT_I3C_DEVICE_ADDR */
    volatile uint32_t HW_CAPABILITY;               /* ALT_I3C_HW_CAPABILITY */
    volatile uint32_t COMMAND_QUEUE_PORT;          /* ALT_I3C_COMMAND_QUEUE_PORT */
    volatile uint32_t RESPONSE_QUEUE_PORT;         /* ALT_I3C_RESPONSE_QUEUE_PORT */
    volatile uint32_t TX_DATA_PORT;                /* ALT_I3C_TX_DATA_PORT */
    volatile uint32_t IBI_QUEUE_STATUS;            /* ALT_I3C_IBI_QUEUE_STATUS */
    volatile uint32_t QUEUE_THLD_CTRL;             /* ALT_I3C_QUEUE_THLD_CTRL */
    volatile uint32_t DATA_BUFFER_THLD_CTRL;       /* ALT_I3C_DATA_BUFFER_THLD_CTRL */
    volatile uint32_t IBI_QUEUE_CTRL;              /* ALT_I3C_IBI_QUEUE_CTRL */
    volatile uint32_t _pad_0x28_0x2b;              /* *UNDEFINED* */
    volatile uint32_t IBI_MR_REQ_REJECT;           /* ALT_I3C_IBI_MR_REQ_REJECT */
    volatile uint32_t IBI_SIR_REQ_REJECT;          /* ALT_I3C_IBI_SIR_REQ_REJECT */
    volatile uint32_t RESET_CTRL;                  /* ALT_I3C_RESET_CTRL */
    volatile uint32_t SLV_EVENT_STATUS;            /* ALT_I3C_SLV_EVENT_STATUS */
    volatile uint32_t INTR_STATUS;                 /* ALT_I3C_INTR_STATUS */
    volatile uint32_t INTR_STATUS_EN;              /* ALT_I3C_INTR_STATUS_EN */
    volatile uint32_t INTR_SIGNAL_EN;              /* ALT_I3C_INTR_SIGNAL_EN */
    volatile uint32_t INTR_FORCE;                  /* ALT_I3C_INTR_FORCE */
    volatile uint32_t QUEUE_STATUS_LEVEL;          /* ALT_I3C_QUEUE_STATUS_LEVEL */
    volatile uint32_t DATA_BUFFER_STATUS_LEVEL;    /* ALT_I3C_DATA_BUFFER_STATUS_LEVEL */
    volatile uint32_t PRESENT_STATE;               /* ALT_I3C_PRESENT_STATE */
    volatile uint32_t CCC_DEVICE_STATUS;           /* ALT_I3C_CCC_DEVICE_STATUS */
    volatile uint32_t DEVICE_ADDR_TABLE_POINTER;   /* ALT_I3C_DEVICE_ADDR_TABLE_POINTER */
    volatile uint32_t DEV_CHAR_TABLE_POINTER;      /* ALT_I3C_DEV_CHAR_TABLE_POINTER */
    volatile uint32_t _pad_0x64_0x6b[2];           /* *UNDEFINED* */
    volatile uint32_t VENDOR_SPECIFIC_REG_POINTER; /* ALT_I3C_VENDOR_SPECIFIC_REG_POINTER */
    volatile uint32_t SLV_MIPI_ID_VALUE;           /* ALT_I3C_SLV_MIPI_ID_VALUE */
    volatile uint32_t SLV_PID_VALUE;               /* ALT_I3C_SLV_PID_VALUE */
    volatile uint32_t SLV_CHAR_CTRL;               /* ALT_I3C_SLV_CHAR_CTRL */
    volatile uint32_t SLV_MAX_LEN;                 /* ALT_I3C_SLV_MAX_LEN */
    volatile uint32_t MAX_READ_TURNAROUND;         /* ALT_I3C_MAX_READ_TURNAROUND */
    volatile uint32_t MAX_DATA_SPEED;              /* ALT_I3C_MAX_DATA_SPEED */
    volatile uint32_t _pad_0x88_0x8b;              /* *UNDEFINED* */
    volatile uint32_t SLV_INTR_REQ;                /* ALT_I3C_SLV_INTR_REQ */
    volatile uint32_t _pad_0x90_0xaf[8];           /* *UNDEFINED* */
    volatile uint32_t DEVICE_CTRL_EXTENDED;        /* ALT_I3C_DEVICE_CTRL_EXTENDED */
    volatile uint32_t SCL_I3C_OD_TIMING;           /* ALT_I3C_SCL_I3C_OD_TIMING */
    volatile uint32_t SCL_I3C_PP_TIMING;           /* ALT_I3C_SCL_I3C_PP_TIMING */
    volatile uint32_t SCL_I2C_FM_TIMING;           /* ALT_I3C_SCL_I2C_FM_TIMING */
    volatile uint32_t SCL_I2C_FMP_TIMING;          /* ALT_I3C_SCL_I2C_FMP_TIMING */
    volatile uint32_t _pad_0xc4_0xc7;              /* *UNDEFINED* */
    volatile uint32_t SCL_EXT_LCNT_TIMING;         /* ALT_I3C_SCL_EXT_LCNT_TIMING */
    volatile uint32_t SCL_EXT_TERMN_LCNT_TIMING;   /* ALT_I3C_SCL_EXT_TERMN_LCNT_TIMING */
    volatile uint32_t SDA_HOLD_SWITCH_DLY_TIMING;  /* ALT_I3C_SDA_HOLD_SWITCH_DLY_TIMING */
    volatile uint32_t BUS_FREE_AVAIL_TIMING;       /* ALT_I3C_BUS_FREE_AVAIL_TIMING */
    volatile uint32_t BUS_IDLE_TIMING;             /* ALT_I3C_BUS_IDLE_TIMING */
    volatile uint32_t _pad_0xdc_0xdf;              /* *UNDEFINED* */
    volatile uint32_t I3C_VER_ID;                  /* ALT_I3C_I3C_VER_ID */
    volatile uint32_t I3C_VER_TYPE;                /* ALT_I3C_I3C_VER_TYPE */
    volatile uint32_t QUEUE_SIZE_CAPABILITY;       /* ALT_I3C_QUEUE_SIZE_CAPABILITY */
    volatile uint32_t _pad_0xec_0x1ff[69];         /* *UNDEFINED* */
    volatile uint32_t DEV_CHAR_TABLE1_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE1_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE1_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE1_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE1_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE1_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE1_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE1_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE2_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE2_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE2_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE2_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE2_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE2_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE2_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE2_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE3_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE3_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE3_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE3_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE3_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE3_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE3_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE3_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE4_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE4_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE4_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE4_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE4_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE4_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE4_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE4_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE5_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE5_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE5_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE5_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE5_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE5_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE5_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE5_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE6_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE6_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE6_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE6_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE6_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE6_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE6_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE6_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE7_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE7_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE7_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE7_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE7_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE7_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE7_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE7_LOC4 */
    volatile uint32_t DEV_CHAR_TABLE8_LOC1;        /* ALT_I3C_DEV_CHAR_TABLE8_LOC1 */
    volatile uint32_t DEV_CHAR_TABLE8_LOC2;        /* ALT_I3C_DEV_CHAR_TABLE8_LOC2 */
    volatile uint32_t DEV_CHAR_TABLE8_LOC3;        /* ALT_I3C_DEV_CHAR_TABLE8_LOC3 */
    volatile uint32_t DEV_CHAR_TABLE8_LOC4;        /* ALT_I3C_DEV_CHAR_TABLE8_LOC4 */
    volatile uint32_t DEV_ADDR_TABLE_LOC1;         /* ALT_I3C_DEV_ADDR_TABLE_LOC1 */
    volatile uint32_t DEV_ADDR_TABLE_LOC2;         /* ALT_I3C_DEV_ADDR_TABLE_LOC2 */
    volatile uint32_t DEV_ADDR_TABLE_LOC3;         /* ALT_I3C_DEV_ADDR_TABLE_LOC3 */
    volatile uint32_t DEV_ADDR_TABLE_LOC4;         /* ALT_I3C_DEV_ADDR_TABLE_LOC4 */
    volatile uint32_t DEV_ADDR_TABLE_LOC5;         /* ALT_I3C_DEV_ADDR_TABLE_LOC5 */
    volatile uint32_t DEV_ADDR_TABLE_LOC6;         /* ALT_I3C_DEV_ADDR_TABLE_LOC6 */
    volatile uint32_t DEV_ADDR_TABLE_LOC7;         /* ALT_I3C_DEV_ADDR_TABLE_LOC7 */
    volatile uint32_t DEV_ADDR_TABLE_LOC8;         /* ALT_I3C_DEV_ADDR_TABLE_LOC8 */
    volatile uint32_t DEV_ADDR_TABLE_LOC9;         /* ALT_I3C_DEV_ADDR_TABLE_LOC9 */
    volatile uint32_t DEV_ADDR_TABLE_LOC10;        /* ALT_I3C_DEV_ADDR_TABLE_LOC10 */
    volatile uint32_t DEV_ADDR_TABLE_LOC11;        /* ALT_I3C_DEV_ADDR_TABLE_LOC11 */
    volatile uint32_t _pad_0x2ac_0x300[21];        /* *UNDEFINED* */
} i3c_regs_t;

#endif // I3C_REGS_H__