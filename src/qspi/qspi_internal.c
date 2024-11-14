#include "qspi_internal.h"
#include "qspi_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence QSPI controller for an Altera Agilex5e HPS
*/
size_t qspi_recv_internal(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    qspi_regs_t *base = (qspi_regs_t *)fd;
    uint32_t *qspi_fifo_addr = (uint32_t *)((uint32_t)fd + QSPI_SRAM_BASE_OFFSET);
    uint32_t *buffer = (uint32_t *)buf;
    uint32_t timeout = (uint32_t)0x100000;
    size_t read_length = (size_t)0;
    base->INDRDCNT = (uint32_t)size; // set indirect read size in bytes
    base->INDRD |= (uint32_t)1;      // start indirect read
    while ((base->INDRD & (uint32_t)(0x4)) != (uint32_t)0) {
        timeout--;
        if (timeout == (uint32_t)0) {
            // Cancel the operation and break
            base->INDRD |= ((uint32_t)(1) << (uint32_t)(1));
            break;
        }
    }
    // Determine the fill level and read into the buffer
    // SRAMFILL indicates number of 32-bit words in the buffer
    read_length = (uint32_t)(base->SRAMFILL & (uint32_t)0xFFFF);
    for (uint32_t i = 0; i < read_length; i++) {
        buffer[i] = *qspi_fifo_addr;
    }
    // Clear the completed bit
    base->INDRD |= ((uint32_t)(1) << (uint32_t)(5));
    return sizeof(uint32_t) * read_length;
}
size_t qspi_send_internal(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    qspi_regs_t *base = (qspi_regs_t *)fd;
    uint32_t *qspi_fifo_addr = (uint32_t *)((uint32_t)fd + QSPI_SRAM_BASE_OFFSET);
    uint32_t *buffer = (uint32_t *)buf;
    uint32_t timeout = (uint32_t)0x100000;
    size_t written_length = (size_t)0;
    base->INDWRCNT = (uint32_t)size; // set indirect write size in bytes
    // Copy data into the buffer
    for (uint32_t i = 0; i < (size / sizeof(uint32_t)); i++) {
        *qspi_fifo_addr = buffer[i];
    }
    base->INDWR |= (uint32_t)1; // start indirect write
    while ((base->INDWR & (uint32_t)0x4) != (uint32_t)0) {
        timeout--;
        if (timeout == (uint32_t)0) {
            // Cancel the operation and break
            base->INDWR |= ((uint32_t)(1) << (uint32_t)(1));
            break;
        }
    }
    // Determine the fill level and adjust return value based on remaining length
    // SRAMFILL indicates number of 32-bit words in the buffer
    written_length = (uint32_t)((base->SRAMFILL & (uint32_t)0xFFFF0000u) >> 16);
    // Clear the completed bit
    base->INDWR |= ((uint32_t)(1) << (uint32_t)(5));
    return size - (sizeof(uint32_t) * written_length);
}

// Whole register bank access
int32_t qspi_read_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(qspi_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(qspi_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_write_regs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    uint32_t *base = (uint32_t *)fd;
    if (length < sizeof(qspi_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(qspi_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

// CFG whole reg access
int32_t qspi_set_cfg_reg(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_cfg_reg(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->CFG;
        return_value = 0;
    }
    return return_value;
}

// CFG field access
int32_t qspi_set_baud_rate_div(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_BAUD_RATE_DIV_OFST) & QSPI_CFG_BAUD_RATE_DIV_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_baud_rate_div(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_BAUD_RATE_DIV_MASK) >> QSPI_CFG_BAUD_RATE_DIV_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_enable(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_ENABLE_OFST) & QSPI_CFG_ENABLE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_enable(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_ENABLE_MASK) >> QSPI_CFG_ENABLE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_clkpol(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_CLKPOL_OFST) & QSPI_CFG_CLKPOL_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_cklpol(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_CLKPOL_MASK) >> QSPI_CFG_CLKPOL_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_clkphase(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_CLKPHASE_OFST) & QSPI_CFG_CLKPHASE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_clkphase(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_CLKPHASE_MASK) >> QSPI_CFG_CLKPHASE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_cs_decode(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_CS_DECODE_OFST) & QSPI_CFG_CS_DECODE_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_cs_decode(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_CS_DECODE_MASK) >> QSPI_CFG_CS_DECODE_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_cs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_CS_SELECT_OFST) & QSPI_CFG_CS_SELECT_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_cs(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_CS_SELECT_MASK) >> QSPI_CFG_CS_SELECT_OFST;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_write_protect_pin(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->CFG = (buf[0] << QSPI_CFG_WRITE_PROTECT_PIN_OFST) & QSPI_CFG_WRITE_PROTECT_PIN_MASK;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_write_protect_pin(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = (base->CFG & QSPI_CFG_WRITE_PROTECT_PIN_MASK) >> QSPI_CFG_WRITE_PROTECT_PIN_OFST;
        return_value = 0;
    }
    return return_value;
}

// External timing settings
int32_t qspi_set_read_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->DEVRD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_read_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->DEVRD;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_write_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->DEVWR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_write_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->DEVWR;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_cs_delays(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->DELAY = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_cs_delays(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->DELAY;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_read_data_capture_dly(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->RDDATACAP = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_read_data_capture_dly(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->RDDATACAP;
        return_value = 0;
    }
    return return_value;
}

// Attached flash device size info
int32_t qspi_set_device_size_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->DEVSZ = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_device_size_params(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->DEVSZ;
        return_value = 0;
    }
    return return_value;
}

// Indirect mode subset
int32_t qspi_set_indirect_addr_span(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->SRAMPART = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_addr_span(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->SRAMPART;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_base_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDADDRTRIG = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_base_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDADDRTRIG;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_dma_cfg(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->DMAPER = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_dma_cfg(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->DMAPER;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_remap_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->REMAPADDR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_remap_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->REMAPADDR;
        return_value = 0;
    }
    return return_value;
}

// Mode bits
int32_t qspi_set_mode_bits(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->MODEBIT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_mode_bits(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->MODEBIT;
        return_value = 0;
    }
    return return_value;
}

// Current SRAM fill level inspection
int32_t qspi_get_sram_fill_lvl(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->SRAMFILL;
        return_value = 0;
    }
    return return_value;
}

// interrupt control and status
int32_t qspi_set_irq_txthresh(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->TXTHRESH = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_irq_txthresh(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->TXTHRESH;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_irq_rxthresh(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->RXTHRESH = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_irq_rxthresh(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->RXTHRESH;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_irqstat(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->IRQSTAT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_irqstat(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->IRQSTAT;
        return_value = 0;
    }
    return return_value;
}

int32_t qspi_set_irqmask(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->IRQMASK = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t qspi_get_irqmask(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->IRQMASK;
        return_value = 0;
    }
    return return_value;
}

// Write protect subset
int32_t qspi_set_wrprot(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->WRPROT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_wrprot(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->WRPROT;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_wrprot_low(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->LOWWRPROT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_wrprot_low(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->LOWWRPROT;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_wrprot_high(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->UPPWRPROT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_wrprot_high(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->UPPWRPROT;
        return_value = 0;
    }
    return return_value;
}

// Indirect read subset
int32_t qspi_set_indirect_read(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDRD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_read(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDRD;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_rd_watermark(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDRDWATER = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_rd_watermark(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDRDWATER;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_rd_start_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDRDSTADDR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_rd_start_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDRDSTADDR;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_rd_count(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDRDCNT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_rd_count(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDRDCNT;
        return_value = 0;
    }
    return return_value;
}

// Indirect write subset
int32_t qspi_set_indirect_write(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDWR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_write(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDWR;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_wr_watermark(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDWRWATER = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_wr_watermark(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDWRWATER;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_wr_start_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDWRSTADDR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_wr_start_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDWRSTADDR;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_indirect_wr_count(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->INDWRCNT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_indirect_wr_count(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->INDWRCNT;
        return_value = 0;
    }
    return return_value;
}

// Flash Command Subset
int32_t qspi_set_flash_cmd(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->FLASHCMD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_flash_cmd(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->FLASHCMD;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_flash_cmd_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        base->FLASHCMDADDR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_flash_cmd_addr(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->FLASHCMDADDR;
        return_value = 0;
    }
    return return_value;
}

int32_t qspi_get_flash_cmd_rd_data(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint64_t)) {
        return_value = -1;
    } else {
        buf[0] = base->FLASHCMDRDDATALO;
        buf[1] = base->FLASHCMDRDDATAUP;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_set_flash_cmd_wr_data(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < ((size_t)2 * (sizeof(uint64_t)))) {
        return_value = -1;
    } else {
        base->FLASHCMDWRDATALO = buf[0];
        base->FLASHCMDWRDATAUP = buf[1];
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_flash_cmd_wr_data(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < ((size_t)2 * (sizeof(uint32_t)))) {
        return_value = -1;
    } else {
        buf[0] = base->FLASHCMDWRDATALO;
        buf[1] = base->FLASHCMDWRDATAUP;
        return_value = 0;
    }
    return return_value;
}
int32_t qspi_get_module_id(int32_t fd, uintptr_t args, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)args;
    qspi_regs_t *base = (qspi_regs_t *)fd;

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = base->MODULEID;
        return_value = 0;
    }
    return return_value;
}