#include "i2c_internal.h"
#include "i2c_regs.h"

#include <stdio.h>
#include <string.h>

static uint32_t i2c_error_state = 0;

uint32_t i2c_get_error_state(uintptr_t base) { return i2c_error_state; }

uint32_t i2c_clear_error_state(uintptr_t base) {
    i2c_error_state = 0;
    return 0;
}

size_t i2c_transmit(uintptr_t base, uintptr_t buffer, size_t length) {
    i2c_regs_t *regs = (i2c_regs_t *)base;
    uint8_t *data = (uint8_t *)buffer;
    for (uint8_t i = 0; i < length; i++) {
        // Determine the data to be written
        uint8_t index = i * 2U;
        uint8_t byte_addr = data[index];
        uint8_t test_val = data[index + 1U];

        // Checking TX FIFO!
        while ((regs->I2C_STATUS & I2C_CMD_STATUS_TFE) == 0U) {
        }
        if ((regs->I2C_STATUS & I2C_CMD_STATUS_TFE) == 0U) {
            // TX FIFO Full
        }

        // Write data to IC_DATA_CMD
        regs->I2C_DATA_CMD = (uint32_t)byte_addr | I2C_CMD_DATA_CMD_WRITE;

        regs->I2C_DATA_CMD = (uint32_t)test_val | I2C_CMD_DATA_CMD_WRITE | I2C_CMD_DATA_STOP;
    }
    return length;
}

size_t i2c_receive(uintptr_t base, uintptr_t buffer, size_t length) {
    uint32_t timeout = 0x100000;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    uint8_t byte_addr = *((uint8_t *)buffer);

    for (uint8_t i = 0; i < length; i++) {
        while ((regs->I2C_STATUS & I2C_CMD_STATUS_TFE) == 0U) {
            // TX FIFO Full, waiting...
        }

        regs->I2C_DATA_CMD = (uint32_t)byte_addr | I2C_CMD_DATA_CMD_WRITE;

        regs->I2C_DATA_CMD = I2C_CMD_DATA_CMD_READ | I2C_CMD_DATA_STOP;

        while ((regs->I2C_RXFLR == (uint32_t)0) && (timeout > 0U)) {
            timeout--;
        }
        if (timeout == 0U) {
            i2c_error_state = (uint32_t)(-1);
            // ERROR: RX FIFO timeout occurred
        }

        uint8_t read_byte = (uint8_t)(regs->I2C_DATA_CMD & 0xFFU);
        *((uint8_t *)buffer) = read_byte;
    }
    return length;
}

int32_t i2c_regs_read(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(i2c_regs_t)) {
        return_value = -1;
    } else {
        // This read is implemented with a for loop so as to skip I2C_DATA_CMD
        // (offset 0x10), which is
        //      used for both receive and transmit operations.
        for (uint32_t i = 0; i < length; i++) {
            if ((i >= (uint32_t)0x10) && (i < (uint32_t)0x14)) {
                continue;
            }
            ((uint8_t *)arg)[i] = ((uint8_t *)base)[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_regs_write(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(i2c_regs_t)) {
        return_value = -1;
    } else {
        // This write is implemented with a for loop so as to skip I2C_DATA_CMD
        // (offset 0x10), which is
        //      used for both receive and transmit operations.
        for (uint32_t i = 0; i < length; i++) {
            if ((i >= (uint32_t)0x10) && (i < (uint32_t)0x14)) {
                continue;
            }
            ((uint8_t *)base)[i] = ((uint8_t *)arg)[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_con(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_CON = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_master_mode(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    if (length >= sizeof(uint32_t)) {
        if (((uint32_t)(*((uint32_t *)arg)) & (uint32_t)(1)) != (uint32_t)(0)) {
            regs->I2C_CON |= (uint32_t)(1);
        } else {
            regs->I2C_CON &= (uint32_t)(~(uint32_t)0x1);
        }
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_master_mode(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_CON & (uint32_t)(1);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_target_addr(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    if (length >= sizeof(uint32_t)) {
        regs->I2C_TAR &= (uint32_t)(~(uint32_t)0x1FF);
        regs->I2C_TAR |= (uint32_t)(*((uint32_t *)arg) & (uint32_t)0x1FF);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_intstat(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_INTR_STAT;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_intstat_raw(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_RAW_INTR_STAT;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_intmask(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_INTR_MASK;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_intmask(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_INTR_MASK = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_intclr(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_CLR_INTR = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_enable(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    if (length >= sizeof(uint32_t)) {
        if (((uint32_t)(*((uint32_t *)arg) & (uint32_t)(1)) != (uint32_t)(0))) {
            regs->I2C_ENABLE |= (uint32_t)(1);
        } else {
            regs->I2C_ENABLE &= (uint32_t)(~(uint32_t)0x1);
        }
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_enable(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_ENABLE & (uint32_t)(1);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_status(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_STATUS;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_tx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_TX_TL = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_tx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_TX_TL;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_tx_fifo_lvl(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_TXFLR;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_rx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_RX_TL = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_rx_fifo_thresh(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_RX_TL;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_rx_fifo_lvl(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_RXFLR;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_tenbit_addr_mode(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    if (length >= sizeof(uint32_t)) {
        if (((uint32_t)(*((uint32_t *)arg)) & (uint32_t)1) != (uint32_t)(0)) {
            regs->I2C_TAR |= (uint32_t)((uint32_t)(1) << (uint32_t)(12));
        } else {
            regs->I2C_TAR &= (uint32_t)(~((uint32_t)(1) << (uint32_t)(12)));
        }
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_dma_mode(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    i2c_regs_t *regs = (i2c_regs_t *)base;
    if (length >= sizeof(uint32_t)) {
        if (((uint32_t)(*((uint32_t *)arg)) & (uint32_t)1) != (uint32_t)(0)) {
            regs->I2C_DMA_CR |= (uint32_t)(3UL);
        } else {
            regs->I2C_DMA_CR &= (uint32_t)(~(3UL));
        }
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_dma_tx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_DMA_TDLR = (uint32_t)((*((uint32_t *)arg)) & (uint32_t)0x3F);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_dma_tx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_DMA_TDLR;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_dma_rx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_DMA_RDLR = (uint32_t)((*((uint32_t *)arg)) & (uint32_t)0x3F);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_dma_rx_fifo_trigger_level(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = regs->I2C_DMA_RDLR;
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_std_scl_hightime(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SS_SCL_HCNT = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_std_scl_lowtime(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SS_SCL_LCNT = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_fast_scl_hightime(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_FS_SCL_HCNT = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_fast_scl_lowtime(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_FS_SCL_LCNT = (uint32_t)(*((uint32_t *)arg));
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_tx_sda_hold(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SDA_HOLD &= (uint32_t)(~(uint32_t)0x000000FF);
        regs->I2C_SDA_HOLD |= (uint32_t)((*((uint32_t *)arg) & (uint32_t)0xFF) << 0);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_tx_sda_hold(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (regs->I2C_SDA_HOLD & (uint32_t)0xFF);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_rx_sda_hold(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SDA_HOLD &= (uint32_t)(~(uint32_t)0x00FF0000);
        regs->I2C_SDA_HOLD = (uint32_t)((*((uint32_t *)arg) & (uint32_t)0x0F) << 16);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_rx_sda_hold(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = ((regs->I2C_SDA_HOLD >> (uint32_t)(16)) & (uint32_t)0x0F);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_sda_setup(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SDA_SETUP &= (uint32_t)(~(uint32_t)0x000000FF);
        regs->I2C_SDA_SETUP |= (uint32_t)(*((uint32_t *)arg) & (uint32_t)0xFF);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_sda_setup(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (uint32_t)((regs->I2C_SDA_SETUP) & (uint32_t)0xFF);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_general_call_enable(uintptr_t base, uintptr_t arg, size_t length) { return -1; }

int32_t i2c_set_general_call_ack(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_ACK_GENERAL_CALL = (uint32_t)(*((uint32_t *)arg) & (uint32_t)0x01);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_set_slave_nack(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_SLV_DATA_NACK_ONLY = (uint32_t)(*((uint32_t *)arg) & (uint32_t)0x01);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_clear_abort(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_CLR_TX_ABRT = (uint32_t)(uint32_t)0x1;
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_aborts(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (uint32_t)(regs->I2C_TX_ABRT_SOURCE);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_set_spike_suppression(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_FS_SPKLEN = (uint32_t)(*((uint32_t *)arg) & (uint32_t)0xFF);
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_spike_suppression(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (uint32_t)(regs->I2C_FS_SPKLEN);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_clear_restart_detect(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        regs->I2C_CLR_RESTART_DET = (uint32_t)(uint32_t)0x1;
        return_value = 0;
    } else {
        return_value = -1;
    }
    return return_value;
}

int32_t i2c_get_enable_status(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (regs->I2C_ENABLE_STATUS & (uint32_t)0x1);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_param(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (regs->I2C_COMP_PARAM_1 & (uint32_t)0xFF);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_version(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (regs->I2C_COMP_VERSION & (uint32_t)0xFF);
        return_value = 0;
    }
    return return_value;
}

int32_t i2c_get_type(uintptr_t base, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length >= sizeof(uint32_t)) {
        i2c_regs_t *regs = (i2c_regs_t *)base;
        *((uint32_t *)arg) = (regs->I2C_COMP_TYPE & (uint32_t)0xFF);
        return_value = 0;
    }
    return return_value;
}