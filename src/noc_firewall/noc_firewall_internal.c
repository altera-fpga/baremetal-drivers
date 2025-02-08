#include "noc_firewall_internal.h"
#include "noc_firewall_regs.h"

#include <stddef.h>
#include <stdint.h>

/*
This code controls the NOC Firewall for an Altera Agilex5e HPS
*/
int32_t noc_firewall_read_internal(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(noc_firewall_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(noc_firewall_regs_t) / sizeof(uint32_t)); i++) {
            buf[i] = base[i];
        }
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_write_internal(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    uint32_t *base = (uint32_t *)base_address;
    if (length < sizeof(noc_firewall_regs_t)) {
        return_value = -1;
    } else {
        for (uint32_t i = 0; i < (sizeof(noc_firewall_regs_t) / sizeof(uint32_t)); i++) {
            base[i] = buf[i];
        }
        return_value = 0;
    }
    return return_value;
}

// L4_per register bank access
int32_t noc_firewall_get_l4_per_nand_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->nand_register;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_nand_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->nand_register = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_usb0_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb0_register;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_usb0_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb0_register = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_usb1_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb1_register;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_usb1_register(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb1_register = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_spi_master0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->spi_master0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_spi_master0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->spi_master0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_spi_master1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->spi_master1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_spi_master1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->spi_master1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_spi_slave0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->spi_slave0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_spi_salve0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->spi_slave0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_spi_slave1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->spi_slave1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_spi_slave1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->spi_slave1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_emac0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_emac0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_emac1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_emac1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_emac2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac2;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_emac2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac2 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_sdmmc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->sdmmc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_sdmmc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->sdmmc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_gpio0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->gpio0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_gpio0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->gpio0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_gpio1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->gpio1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_gpio1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->gpio1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i2c0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i2c0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i2c0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i2c0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i2c1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i2c1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i2c1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i2c1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i2c2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i2c2;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i2c2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i2c2 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i2c3(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i2c3;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i2c3(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i2c3 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i2c4(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i2c4;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i2c4(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i2c4 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_sp_timer0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->sp_timer0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_sp_timer0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->sp_timer0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_sp_timer1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->sp_timer1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_sp_timer1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->sp_timer1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_uart0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->uart0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_uart0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->uart0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_uart1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->uart1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_uart1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->uart1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i3c0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i3c0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i3c0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i3c0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_i3c1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->i3c1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_i3c1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->i3c1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_dma0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->dma0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_dma0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->dma0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_dma1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->dma1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_dma1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->dma1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_combo_phy(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->combo_phy;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_combo_phy(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->combo_phy = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_per_nand_sdma(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->nand_sdma;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_per_nand_sdma(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_per_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_per_regs_words_t *)(base_address + NOC_FIREWALL_L4_PER_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->nand_sdma = buf[0];
        return_value = 0;
    }
    return return_value;
}

// L4 sys register bank access
int32_t noc_firewall_get_l4_sys_dma_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->dma_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_dma_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->dma_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac0rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac0rx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac0rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac0rx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac0tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac0tx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac0tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac0tx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac1rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac1rx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac1rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac1rx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac1tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac1tx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac1tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac1tx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac2rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac2rx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac2rx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac2rx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_emac2tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->emac2tx_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_emac2tx_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->emac2tx_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_nand_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->nand_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_nand_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->nand_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_nand_read_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->nand_read_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_nand_read_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->nand_read_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_nand_write_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->nand_write_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_nand_write_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->nand_write_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_ocram_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->ocram_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_ocram_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->ocram_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_sdmmc_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->sdmmc_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_sdmmc_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->sdmmc_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_usb0_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb0_ecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_usb0_ecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb0_ecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_usb1_cacheecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb1_cacheecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_usb1_cacheecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb1_cacheecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_clock_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->clock_manager;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_clock_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->clock_manager = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_io_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->io_manager;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_io_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->io_manager = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_reset_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->reset_manager;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_reset_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->reset_manager = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_system_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->system_manager;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_system_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->system_manager = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_osc0_timer(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->osc0_timer;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_osc0_timer(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->osc0_timer = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_osc1_timer(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->osc1_timer;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_osc1_timer(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->osc1_timer = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_watchdog0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->watchdog0;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_watchdog0(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->watchdog0 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_watchdog1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->watchdog1;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_watchdog1(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->watchdog1 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_watchdog2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->watchdog2;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_watchdog2(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->watchdog2 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_watchdog3(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->watchdog3;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_watchdog3(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->watchdog3 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_dap(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->dap;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_dap(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->dap = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_watchdog4(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->watchdog4;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_watchdog4(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->watchdog4 = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_power_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->power_manager;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_power_manager(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->power_manager = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_usb1_rxecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb1_rxecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_usb1_rxecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb1_rxecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_usb1_txecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->usb1_txecc;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_usb1_txecc(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->usb1_txecc = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_l4_noc_probes(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->l4_noc_probes;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_l4_noc_probes(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->l4_noc_probes = buf[0];
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_get_l4_sys_l4_noc_qos(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->l4_noc_qos;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_l4_sys_l4_noc_qos(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_l4_sys_regs_words_t *noc_firewall_reg =
        (noc_firewall_l4_sys_regs_words_t *)(base_address + NOC_FIREWALL_L4_SYS_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->l4_noc_qos = buf[0];
        return_value = 0;
    }
    return return_value;
}

// HPS2FPGA register bank access
int32_t noc_firewall_get_hps2fpga_soc2fpga(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_hps2fpga_regs_words_t *noc_firewall_reg =
        (noc_firewall_hps2fpga_regs_words_t *)(base_address + NOC_FIREWALL_HPS2FPGA_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->soc2fpga;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_hps2fpga_soc2fpga(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_hps2fpga_regs_words_t *noc_firewall_reg =
        (noc_firewall_hps2fpga_regs_words_t *)(base_address + NOC_FIREWALL_HPS2FPGA_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->soc2fpga = buf[0];
        return_value = 0;
    }
    return return_value;
}

// LWHPS2FPGA register bank access
int32_t noc_firewall_get_lwhps2fpga_lwsoc2fpga(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_lwhps2fpga_regs_words_t *noc_firewall_reg =
        (noc_firewall_lwhps2fpga_regs_words_t *)(base_address + NOC_FIREWALL_LWHPS2FPGA_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->lwsoc2fpga;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_lwhps2fpga_lwsoc2fpga(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_lwhps2fpga_regs_words_t *noc_firewall_reg =
        (noc_firewall_lwhps2fpga_regs_words_t *)(base_address + NOC_FIREWALL_LWHPS2FPGA_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->lwsoc2fpga = buf[0];
        return_value = 0;
    }
    return return_value;
}

// TCU register bank access
int32_t noc_firewall_get_tcu_tcu(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_tcu_regs_words_t *noc_firewall_reg =
        (noc_firewall_tcu_regs_words_t *)(base_address + NOC_FIREWALL_TCU_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = noc_firewall_reg->tcu;
        return_value = 0;
    }
    return return_value;
}

int32_t noc_firewall_set_tcu_tcu(int32_t base_address, uintptr_t param, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)param;
    noc_firewall_tcu_regs_words_t *noc_firewall_reg =
        (noc_firewall_tcu_regs_words_t *)(base_address + NOC_FIREWALL_TCU_OFST);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        noc_firewall_reg->tcu = buf[0];
        return_value = 0;
    }
    return return_value;
}
