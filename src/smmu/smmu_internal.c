#include "smmu_internal.h"
#include "smmu_regs.h"

int32_t smmu_idr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_idr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_idr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IDR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_idr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_idr5_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IDR5;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_iidr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IIDR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_aidr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_AIDR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr0_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr0ack_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CR0ACK;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CR1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cr2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CR2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gbpa_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GBPA;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gbpa_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GBPA = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IRQ_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_IRQ_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_IRQ_CTRLACK;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERROR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerrorn_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERRORN;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerrorn_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GERRORN = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERROR_IRQ_CFG0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GERROR_IRQ_CFG0_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERROR_IRQ_CFG0_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GERROR_IRQ_CFG0_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERROR_IRQ_CFG1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GERROR_IRQ_CFG1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_GERROR_IRQ_CFG2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_gerror_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_GERROR_IRQ_CFG2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_STRTAB_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_STRTAB_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_STRTAB_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_STRTAB_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_cfg_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_STRTAB_BASE_CFG;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_strtab_base_cfg_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_STRTAB_BASE_CFG = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CMDQ_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CMDQ_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CMDQ_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CMDQ_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_prod_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CMDQ_PROD;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_prod_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CMDQ_PROD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_cons_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);

    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CMDQ_CONS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cmdq_cons_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_CMDQ_CONS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_IRQ_CFG0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_IRQ_CFG0_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_IRQ_CFG0_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_IRQ_CFG0_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_IRQ_CFG1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_IRQ_CFG1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_IRQ_CFG2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_IRQ_CFG2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_IRQ_CFG0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_IRQ_CFG0_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_IRQ_CFG0_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_IRQ_CFG0_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_IRQ_CFG1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_IRQ_CFG1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_IRQ_CFG2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_IRQ_CFG2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr4_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR4;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr5_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR5;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr6_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR6;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pidr7_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PIDR7;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cidr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CIDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cidr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CIDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cidr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CIDR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_cidr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_CIDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVTYPER0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper0_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVTYPER0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVTYPER1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVTYPER1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVTYPER2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVTYPER2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVTYPER3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evtyper3_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVTYPER3 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_smr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SMR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_smr0_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_SMR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cnten_setbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_CNTENSET0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cnten_clrbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_CNTENCLR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_inten_setbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_INTENSET0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_inten_clrbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_INTENCLR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_scr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SCR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_scr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_SCR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cfgr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CFGR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cfgr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_CFGR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_CR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_ceid0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CEID0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_ceid0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CEID0_HI;
        return_value = 0;
    }
    return return_value;
}

int32_t smmu_pmcg_ceid1_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CEID1_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_ceid1_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CEID1_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_IRQ_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_IRQ_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_IRQ_CTRLACK;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_aidr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_AIDR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pmauthstatus_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PMAUTHSTATUS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pmdevarch_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PMDEVARCH;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pmdevtype_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PMDEVTYPE;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr4_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR4;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr5_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR5;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr6_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR6;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_pidr7_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_PIDR7;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cidr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CIDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cidr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CIDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cidr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CIDR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_cidr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_CIDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_idr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_IDR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_idr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_IDR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_idr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_IDR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr0_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr0ack_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CR0ACK;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr0ack_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CR0ACK = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CR1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cr2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CR2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_init_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_INIT;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_init_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_INIT = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gbpa_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GBPA;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gbpa_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GBPA = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_IRQ_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_IRQ_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_IRQ_CTRLACK;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERROR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerrorn_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERRORN;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerrorn_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GERRORN = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERROR_IRQ_CFG0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GERROR_IRQ_CFG0_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERROR_IRQ_CFG0_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GERROR_IRQ_CFG0_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERROR_IRQ_CFG1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GERROR_IRQ_CFG1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_GERROR_IRQ_CFG2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_gerror_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_GERROR_IRQ_CFG2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_STRTAB_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_STRTAB_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_STRTAB_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_STRTAB_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_cfg_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_STRTAB_BASE_CFG;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_strtab_base_cfg_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_STRTAB_BASE_CFG = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CMDQ_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CMDQ_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CMDQ_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CMDQ_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_prod_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CMDQ_PROD;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_prod_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CMDQ_PROD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_cons_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_CMDQ_CONS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_cmdq_cons_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_CMDQ_CONS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_base_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_BASE_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_base_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_BASE_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_base_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_BASE_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_base_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_BASE_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_prod_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_PROD;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_prod_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_PROD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_cons_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_CONS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_cons_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_CONS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_IRQ_CFG0_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_IRQ_CFG0_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_IRQ_CFG0_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_IRQ_CFG0_HI = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_IRQ_CFG1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_IRQ_CFG1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_S_EVENTQ_IRQ_CFG2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_s_eventq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_S_EVENTQ_IRQ_CFG2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;

    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_CTRL;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_CTRL = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_qos_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_QOS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_qos_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_QOS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_cfg_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_CFG;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_cfg_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_CFG = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_status_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_STATUS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_scr_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_SCR;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_scr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_SCR = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errfr_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRFR_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errfr_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRFR_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errctlr_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRCTLR_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errctlr_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_ERRCTLR_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errctlr_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRCTLR_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errstatus_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRSTATUS_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errstatus_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_ERRSTATUS_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errstatus_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRSTATUS_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errgen_lo_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRGEN_LO;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errgen_lo_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->TCU_ERRGEN_LO = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_errgen_hi_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->TCU_ERRGEN_HI;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_node_ctrl_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint64_t)) {
        return_value = -1;
    } else {
        buf[1] = *((uint32_t *)((uint32_t)(fd) + TCU_NODE_CTRL_OFFSET + ((uint32_t)(4) * buf[0])));
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_node_ctrl_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint64_t)) {
        return_value = -1;
    } else {
        *((uint32_t *)((uint32_t)(fd) + TCU_NODE_CTRL_OFFSET + ((uint32_t)(4) * buf[0]))) = buf[1];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_tcu_node_status_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint64_t)) {
        return_value = -1;
    } else {
        buf[1] = *((uint32_t *)((uint32_t)(fd) + TCU_NODE_STATUS_OFFSET + ((uint32_t)(4) * buf[0])));
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_prod_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_PROD;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_prod_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_PROD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_cons_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_EVENTQ_CONS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_eventq_cons_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_EVENTQ_CONS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_prod_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_PROD;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_prod_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_PROD = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_cons_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PRIQ_CONS;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_priq_cons_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PRIQ_CONS = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVCNTR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr0_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVCNTR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVCNTR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr1_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVCNTR1 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVCNTR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr2_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVCNTR2 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_EVCNTR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_evcntr3_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_EVCNTR3 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_svr0_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SVR0;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_svr1_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SVR1;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_svr2_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SVR2;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_svr3_get(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        buf[0] = smmu_regs->SMMU_PMCG_SVR3;
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_ovs_clrbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_OVSCLR0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_ovs_setbits(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_OVSSET0 = buf[0];
        return_value = 0;
    }
    return return_value;
}
int32_t smmu_pmcg_capr_set(int32_t fd, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    smmu_regs_t *smmu_regs = (smmu_regs_t *)fd;
    uint32_t *buf = (uint32_t *)(arg);
    if (length < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        smmu_regs->SMMU_PMCG_CAPR = buf[0];
        return_value = 0;
    }
    return return_value;
}
