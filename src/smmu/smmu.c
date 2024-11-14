#include "smmu.h"
#include "device.h"
#include "smmu_internal.h"
#include "smmu_regs.h"

#include <string.h>

device_descriptor_t smmu_devices[] = {{.name = "/dev/smmu0", .fd = SMMU_BASE, .acquired = 0}};

int32_t smmu_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(smmu_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(smmu_devices[i].name, path) == 0) {
                if (claim_device(&smmu_devices[i])) {
                    return_value = smmu_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

int32_t smmu_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(smmu_devices) / sizeof(device_descriptor_t)); i++) {
            if (smmu_devices[i].fd == fd) {
                smmu_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}
int32_t smmu_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    /* unimplemented */
    return -1;
}
int32_t smmu_read(int32_t fd, uintptr_t buf, size_t size) { return smmu_recv(fd, buf, size, 0); }
int32_t smmu_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) {
    /* unimplemented */
    return -1;
}
int32_t smmu_write(int32_t fd, const uintptr_t buf, size_t size) { return smmu_send(fd, buf, size, 0); }
int32_t smmu_ioctl(int32_t fd, uint32_t operation, uintptr_t arg, size_t size) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((smmu_op_t)operation) {
        case IOCTL_SMMU_IDR0_GET:
            return_value = smmu_idr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IDR1_GET:
            return_value = smmu_idr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IDR2_GET:
            return_value = smmu_idr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IDR3_GET:
            return_value = smmu_idr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IDR5_GET:
            return_value = smmu_idr5_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IIDR_GET:
            return_value = smmu_iidr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_AIDR_GET:
            return_value = smmu_aidr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CR0_GET:
            return_value = smmu_cr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CR0_SET:
            return_value = smmu_cr0_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CR0ACK_GET:
            return_value = smmu_cr0ack_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CR1_GET:
            return_value = smmu_cr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CR1_SET:
            return_value = smmu_cr1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CR2_GET:
            return_value = smmu_cr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CR2_SET:
            return_value = smmu_cr2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_GBPA_GET:
            return_value = smmu_gbpa_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GBPA_SET:
            return_value = smmu_gbpa_set(fd, arg, size);
            break;
        case IOCTL_SMMU_IRQ_CTRL_GET:
            return_value = smmu_irq_ctrl_get(fd, arg, size);
            break;
        case IOCTL_SMMU_IRQ_CTRL_SET:
            return_value = smmu_irq_ctrl_set(fd, arg, size);
            break;
        case IOCTL_SMMU_IRQ_CTRLACK_GET:
            return_value = smmu_irq_ctrlack_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_GET:
            return_value = smmu_gerror_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERRORN_GET:
            return_value = smmu_gerrorn_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERRORN_SET:
            return_value = smmu_gerrorn_set(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG0_LO_GET:
            return_value = smmu_gerror_irq_cfg0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG0_LO_SET:
            return_value = smmu_gerror_irq_cfg0_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG0_HI_GET:
            return_value = smmu_gerror_irq_cfg0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG0_HI_SET:
            return_value = smmu_gerror_irq_cfg0_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG1_GET:
            return_value = smmu_gerror_irq_cfg1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG1_SET:
            return_value = smmu_gerror_irq_cfg1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG2_GET:
            return_value = smmu_gerror_irq_cfg2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_GERROR_IRQ_CFG2_SET:
            return_value = smmu_gerror_irq_cfg2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_LO_GET:
            return_value = smmu_strtab_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_LO_SET:
            return_value = smmu_strtab_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_HI_GET:
            return_value = smmu_strtab_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_HI_SET:
            return_value = smmu_strtab_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_CFG_GET:
            return_value = smmu_strtab_base_cfg_get(fd, arg, size);
            break;
        case IOCTL_SMMU_STRTAB_BASE_CFG_SET:
            return_value = smmu_strtab_base_cfg_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_BASE_LO_GET:
            return_value = smmu_cmdq_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_BASE_LO_SET:
            return_value = smmu_cmdq_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_BASE_HI_GET:
            return_value = smmu_cmdq_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_BASE_HI_SET:
            return_value = smmu_cmdq_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_PROD_GET:
            return_value = smmu_cmdq_prod_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_PROD_SET:
            return_value = smmu_cmdq_prod_set(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_CONS_GET:
            return_value = smmu_cmdq_cons_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CMDQ_CONS_SET:
            return_value = smmu_cmdq_cons_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_BASE_LO_GET:
            return_value = smmu_eventq_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_BASE_LO_SET:
            return_value = smmu_eventq_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_BASE_HI_GET:
            return_value = smmu_eventq_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_BASE_HI_SET:
            return_value = smmu_eventq_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG0_LO_GET:
            return_value = smmu_eventq_irq_cfg0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG0_LO_SET:
            return_value = smmu_eventq_irq_cfg0_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG0_HI_GET:
            return_value = smmu_eventq_irq_cfg0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG0_HI_SET:
            return_value = smmu_eventq_irq_cfg0_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG1_GET:
            return_value = smmu_eventq_irq_cfg1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG1_SET:
            return_value = smmu_eventq_irq_cfg1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG2_GET:
            return_value = smmu_eventq_irq_cfg2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_IRQ_CFG2_SET:
            return_value = smmu_eventq_irq_cfg2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_BASE_LO_GET:
            return_value = smmu_priq_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_BASE_LO_SET:
            return_value = smmu_priq_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_BASE_HI_GET:
            return_value = smmu_priq_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_BASE_HI_SET:
            return_value = smmu_priq_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG0_LO_GET:
            return_value = smmu_priq_irq_cfg0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG0_LO_SET:
            return_value = smmu_priq_irq_cfg0_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG0_HI_GET:
            return_value = smmu_priq_irq_cfg0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG0_HI_SET:
            return_value = smmu_priq_irq_cfg0_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG1_GET:
            return_value = smmu_priq_irq_cfg1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG1_SET:
            return_value = smmu_priq_irq_cfg1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG2_GET:
            return_value = smmu_priq_irq_cfg2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_IRQ_CFG2_SET:
            return_value = smmu_priq_irq_cfg2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR0_GET:
            return_value = smmu_pidr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR1_GET:
            return_value = smmu_pidr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR2_GET:
            return_value = smmu_pidr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR3_GET:
            return_value = smmu_pidr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR4_GET:
            return_value = smmu_pidr4_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR5_GET:
            return_value = smmu_pidr5_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR6_GET:
            return_value = smmu_pidr6_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PIDR7_GET:
            return_value = smmu_pidr7_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CIDR0_GET:
            return_value = smmu_cidr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CIDR1_GET:
            return_value = smmu_cidr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CIDR2_GET:
            return_value = smmu_cidr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_CIDR3_GET:
            return_value = smmu_cidr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER0_GET:
            return_value = smmu_pmcg_evtyper0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER0_SET:
            return_value = smmu_pmcg_evtyper0_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER1_GET:
            return_value = smmu_pmcg_evtyper1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER1_SET:
            return_value = smmu_pmcg_evtyper1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER2_GET:
            return_value = smmu_pmcg_evtyper2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER2_SET:
            return_value = smmu_pmcg_evtyper2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER3_GET:
            return_value = smmu_pmcg_evtyper3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVTYPER3_SET:
            return_value = smmu_pmcg_evtyper3_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SMR0_GET:
            return_value = smmu_pmcg_smr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SMR0_SET:
            return_value = smmu_pmcg_smr0_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CNTEN_SETBITS:
            return_value = smmu_pmcg_cnten_setbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CNTEN_CLRBITS:
            return_value = smmu_pmcg_cnten_clrbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_INTEN_SETBITS:
            return_value = smmu_pmcg_inten_setbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_INTEN_CLRBITS:
            return_value = smmu_pmcg_inten_clrbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SCR_GET:
            return_value = smmu_pmcg_scr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SCR_SET:
            return_value = smmu_pmcg_scr_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CFGR_GET:
            return_value = smmu_pmcg_cfgr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CFGR_SET:
            return_value = smmu_pmcg_cfgr_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CR_GET:
            return_value = smmu_pmcg_cr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CR_SET:
            return_value = smmu_pmcg_cr_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CEID0_LO_GET:
            return_value = smmu_pmcg_ceid0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CEID0_HI_GET:
            return_value = smmu_pmcg_ceid0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CEID1_LO_GET:
            return_value = smmu_pmcg_ceid1_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CEID1_HI_GET:
            return_value = smmu_pmcg_ceid1_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_IRQ_CTRL_GET:
            return_value = smmu_pmcg_irq_ctrl_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_IRQ_CTRL_SET:
            return_value = smmu_pmcg_irq_ctrl_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_IRQ_CTRLACK_GET:
            return_value = smmu_pmcg_irq_ctrlack_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_AIDR_GET:
            return_value = smmu_pmcg_aidr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PMAUTHSTATUS_GET:
            return_value = smmu_pmcg_pmauthstatus_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PMDEVARCH_GET:
            return_value = smmu_pmcg_pmdevarch_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PMDEVTYPE_GET:
            return_value = smmu_pmcg_pmdevtype_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR0_GET:
            return_value = smmu_pmcg_pidr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR1_GET:
            return_value = smmu_pmcg_pidr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR2_GET:
            return_value = smmu_pmcg_pidr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR3_GET:
            return_value = smmu_pmcg_pidr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR4_GET:
            return_value = smmu_pmcg_pidr4_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR5_GET:
            return_value = smmu_pmcg_pidr5_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR6_GET:
            return_value = smmu_pmcg_pidr6_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_PIDR7_GET:
            return_value = smmu_pmcg_pidr7_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CIDR0_GET:
            return_value = smmu_pmcg_cidr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CIDR1_GET:
            return_value = smmu_pmcg_cidr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CIDR2_GET:
            return_value = smmu_pmcg_cidr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CIDR3_GET:
            return_value = smmu_pmcg_cidr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IDR0_GET:
            return_value = smmu_s_idr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IDR1_GET:
            return_value = smmu_s_idr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IDR3_GET:
            return_value = smmu_s_idr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR0_GET:
            return_value = smmu_s_cr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR0_SET:
            return_value = smmu_s_cr0_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR0ACK_GET:
            return_value = smmu_s_cr0ack_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR0ACK_SET:
            return_value = smmu_s_cr0ack_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR1_GET:
            return_value = smmu_s_cr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR1_SET:
            return_value = smmu_s_cr1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR2_GET:
            return_value = smmu_s_cr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CR2_SET:
            return_value = smmu_s_cr2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_INIT_GET:
            return_value = smmu_s_init_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_INIT_SET:
            return_value = smmu_s_init_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GBPA_GET:
            return_value = smmu_s_gbpa_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GBPA_SET:
            return_value = smmu_s_gbpa_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IRQ_CTRL_GET:
            return_value = smmu_s_irq_ctrl_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IRQ_CTRL_SET:
            return_value = smmu_s_irq_ctrl_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_IRQ_CTRLACK_GET:
            return_value = smmu_s_irq_ctrlack_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_GET:
            return_value = smmu_s_gerror_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERRORN_GET:
            return_value = smmu_s_gerrorn_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERRORN_SET:
            return_value = smmu_s_gerrorn_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG0_LO_GET:
            return_value = smmu_s_gerror_irq_cfg0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG0_LO_SET:
            return_value = smmu_s_gerror_irq_cfg0_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG0_HI_GET:
            return_value = smmu_s_gerror_irq_cfg0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG0_HI_SET:
            return_value = smmu_s_gerror_irq_cfg0_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG1_GET:
            return_value = smmu_s_gerror_irq_cfg1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG1_SET:
            return_value = smmu_s_gerror_irq_cfg1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG2_GET:
            return_value = smmu_s_gerror_irq_cfg2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_GERROR_IRQ_CFG2_SET:
            return_value = smmu_s_gerror_irq_cfg2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_LO_GET:
            return_value = smmu_s_strtab_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_LO_SET:
            return_value = smmu_s_strtab_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_HI_GET:
            return_value = smmu_s_strtab_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_HI_SET:
            return_value = smmu_s_strtab_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_CFG_GET:
            return_value = smmu_s_strtab_base_cfg_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_STRTAB_BASE_CFG_SET:
            return_value = smmu_s_strtab_base_cfg_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_BASE_LO_GET:
            return_value = smmu_s_cmdq_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_BASE_LO_SET:
            return_value = smmu_s_cmdq_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_BASE_HI_GET:
            return_value = smmu_s_cmdq_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_BASE_HI_SET:
            return_value = smmu_s_cmdq_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_PROD_GET:
            return_value = smmu_s_cmdq_prod_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_PROD_SET:
            return_value = smmu_s_cmdq_prod_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_CONS_GET:
            return_value = smmu_s_cmdq_cons_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_CMDQ_CONS_SET:
            return_value = smmu_s_cmdq_cons_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_BASE_LO_GET:
            return_value = smmu_s_eventq_base_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_BASE_LO_SET:
            return_value = smmu_s_eventq_base_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_BASE_HI_GET:
            return_value = smmu_s_eventq_base_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_BASE_HI_SET:
            return_value = smmu_s_eventq_base_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_PROD_GET:
            return_value = smmu_s_eventq_prod_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_PROD_SET:
            return_value = smmu_s_eventq_prod_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_CONS_GET:
            return_value = smmu_s_eventq_cons_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_CONS_SET:
            return_value = smmu_s_eventq_cons_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_LO_GET:
            return_value = smmu_s_eventq_irq_cfg0_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_LO_SET:
            return_value = smmu_s_eventq_irq_cfg0_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_HI_GET:
            return_value = smmu_s_eventq_irq_cfg0_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_HI_SET:
            return_value = smmu_s_eventq_irq_cfg0_hi_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG1_GET:
            return_value = smmu_s_eventq_irq_cfg1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG1_SET:
            return_value = smmu_s_eventq_irq_cfg1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG2_GET:
            return_value = smmu_s_eventq_irq_cfg2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_S_EVENTQ_IRQ_CFG2_SET:
            return_value = smmu_s_eventq_irq_cfg2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_CTRL_GET:
            return_value = smmu_tcu_ctrl_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_CTRL_SET:
            return_value = smmu_tcu_ctrl_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_QOS_GET:
            return_value = smmu_tcu_qos_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_QOS_SET:
            return_value = smmu_tcu_qos_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_CFG_GET:
            return_value = smmu_tcu_cfg_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_CFG_SET:
            return_value = smmu_tcu_cfg_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_STATUS_GET:
            return_value = smmu_tcu_status_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_SCR_GET:
            return_value = smmu_tcu_scr_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_SCR_SET:
            return_value = smmu_tcu_scr_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRFR_LO_GET:
            return_value = smmu_tcu_errfr_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRFR_HI_GET:
            return_value = smmu_tcu_errfr_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRCTLR_LO_GET:
            return_value = smmu_tcu_errctlr_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRCTLR_LO_SET:
            return_value = smmu_tcu_errctlr_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRCTLR_HI_GET:
            return_value = smmu_tcu_errctlr_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRSTATUS_LO_GET:
            return_value = smmu_tcu_errstatus_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRSTATUS_LO_SET:
            return_value = smmu_tcu_errstatus_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRSTATUS_HI_GET:
            return_value = smmu_tcu_errstatus_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRGEN_LO_GET:
            return_value = smmu_tcu_errgen_lo_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRGEN_LO_SET:
            return_value = smmu_tcu_errgen_lo_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_ERRGEN_HI_GET:
            return_value = smmu_tcu_errgen_hi_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_NODE_CTRL_GET:
            return_value = smmu_tcu_node_ctrl_get(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_NODE_CTRL_SET:
            return_value = smmu_tcu_node_ctrl_set(fd, arg, size);
            break;
        case IOCTL_SMMU_TCU_NODE_STATUS_GET:
            return_value = smmu_tcu_node_status_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_PROD_GET:
            return_value = smmu_eventq_prod_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_PROD_SET:
            return_value = smmu_eventq_prod_set(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_CONS_GET:
            return_value = smmu_eventq_cons_get(fd, arg, size);
            break;
        case IOCTL_SMMU_EVENTQ_CONS_SET:
            return_value = smmu_eventq_cons_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_PROD_GET:
            return_value = smmu_priq_prod_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_PROD_SET:
            return_value = smmu_priq_prod_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_CONS_GET:
            return_value = smmu_priq_cons_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PRIQ_CONS_SET:
            return_value = smmu_priq_cons_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR0_GET:
            return_value = smmu_pmcg_evcntr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR0_SET:
            return_value = smmu_pmcg_evcntr0_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR1_GET:
            return_value = smmu_pmcg_evcntr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR1_SET:
            return_value = smmu_pmcg_evcntr1_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR2_GET:
            return_value = smmu_pmcg_evcntr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR2_SET:
            return_value = smmu_pmcg_evcntr2_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR3_GET:
            return_value = smmu_pmcg_evcntr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_EVCNTR3_SET:
            return_value = smmu_pmcg_evcntr3_set(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SVR0_GET:
            return_value = smmu_pmcg_svr0_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SVR1_GET:
            return_value = smmu_pmcg_svr1_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SVR2_GET:
            return_value = smmu_pmcg_svr2_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_SVR3_GET:
            return_value = smmu_pmcg_svr3_get(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_OVS_CLRBITS:
            return_value = smmu_pmcg_ovs_clrbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_OVS_SETBITS:
            return_value = smmu_pmcg_ovs_setbits(fd, arg, size);
            break;
        case IOCTL_SMMU_PMCG_CAPR_SET:
            return_value = smmu_pmcg_capr_set(fd, arg, size);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}

int32_t smmu_error(int32_t fd) {
    /* unimplemented */
    return -1;
}