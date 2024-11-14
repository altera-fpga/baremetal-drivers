#include "gic_internal.h"
#include "gic_regs.h"

#include <string.h>

int32_t gicd_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicd_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICD_BASE, sizeof(arm_gicd_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicd_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicd_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICD_BASE, (void *)arg, sizeof(arm_gicd_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gica_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gica_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICA_BASE, sizeof(arm_gica_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gica_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gica_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICA_BASE, (void *)arg, sizeof(arm_gica_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gict_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gict_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICT_BASE, sizeof(arm_gict_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gict_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gict_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICT_BASE, (void *)arg, sizeof(arm_gict_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicp_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicp_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICP_BASE, sizeof(arm_gicp_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicp_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicp_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICP_BASE, (void *)arg, sizeof(arm_gicp_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gits0_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gits0_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GITS0_BASE, sizeof(arm_gits0_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gits0_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gits0_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GITS0_BASE, (void *)arg, sizeof(arm_gits0_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gits0_translater_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gits0_translater_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GITS0_TRANSLATER_BASE, sizeof(arm_gits0_translater_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gits0_translater_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gits0_translater_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GITS0_TRANSLATER_BASE, (void *)arg, sizeof(arm_gits0_translater_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi0_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_LPI0_BASE, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi0_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_LPI0_BASE, (void *)arg, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi1_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_LPI1_BASE, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi1_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_LPI1_BASE, (void *)arg, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi2_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_LPI2_BASE, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi2_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_LPI2_BASE, (void *)arg, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi3_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_LPI3_BASE, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_lpi3_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_lpi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_LPI3_BASE, (void *)arg, sizeof(arm_gicr_lpi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi0_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_SGI0_BASE, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi0_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_SGI0_BASE, (void *)arg, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi1_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_SGI1_BASE, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi1_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_SGI1_BASE, (void *)arg, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi2_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_SGI2_BASE, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi2_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_SGI2_BASE, (void *)arg, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi3_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICR_SGI3_BASE, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicr_sgi3_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicr_sgi_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICR_SGI3_BASE, (void *)arg, sizeof(arm_gicr_sgi_regs_t));
        return_value = 0;
    }
    return return_value;
}
int32_t gicda_regs_read(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicd_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)arg, (void *)HPS_GICD_BASE, sizeof(arm_gicd_regs_t));
        return_value = 0;
    }
    return return_value;
}

int32_t gicda_regs_write(uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if (length < sizeof(arm_gicd_regs_t)) {
        return_value = -1;
    } else {
        memcpy((void *)HPS_GICD_BASE, (void *)arg, sizeof(arm_gicd_regs_t));
        return_value = 0;
    }
    return return_value;
}
