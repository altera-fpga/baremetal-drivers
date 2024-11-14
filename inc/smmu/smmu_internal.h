#ifndef SMMU_INTERNAL_H__
#define SMMU_INTERNAL_H__

#include <stddef.h>
#include <stdint.h>

int32_t smmu_idr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_idr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_idr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_idr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_idr5_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_iidr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_aidr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr0_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr0ack_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cr2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gbpa_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gbpa_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerrorn_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerrorn_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_gerror_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_cfg_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_strtab_base_cfg_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_prod_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_prod_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_cons_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cmdq_cons_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr4_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr5_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr6_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pidr7_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cidr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cidr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cidr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_cidr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper0_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evtyper3_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_smr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_smr0_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cnten_setbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cnten_clrbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_inten_setbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_inten_clrbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_scr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_scr_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cfgr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cfgr_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cr_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ceid0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ceid0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ceid1_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ceid1_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_aidr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pmauthstatus_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pmdevarch_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pmdevtype_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr4_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr5_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr6_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_pidr7_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cidr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cidr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cidr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_cidr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_idr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_idr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_idr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr0_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr0ack_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr0ack_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cr2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_init_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_init_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gbpa_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gbpa_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_irq_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_irq_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_irq_ctrlack_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerrorn_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerrorn_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_gerror_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_cfg_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_strtab_base_cfg_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_prod_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_prod_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_cons_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_cmdq_cons_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_base_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_base_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_base_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_base_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_prod_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_prod_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_cons_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_cons_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg0_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg0_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg0_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg0_hi_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_s_eventq_irq_cfg2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_qos_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_qos_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_cfg_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_cfg_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_status_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_scr_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_scr_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errfr_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errfr_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errctlr_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errctlr_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errctlr_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errstatus_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errstatus_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errstatus_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errgen_lo_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errgen_lo_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_errgen_hi_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_node_ctrl_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_node_ctrl_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_tcu_node_status_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_prod_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_prod_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_cons_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_eventq_cons_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_prod_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_prod_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_cons_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_priq_cons_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr0_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr1_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr2_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_evcntr3_set(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_svr0_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_svr1_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_svr2_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_svr3_get(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ovs_clrbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_ovs_setbits(int32_t fd, uintptr_t arg, size_t length);
int32_t smmu_pmcg_capr_set(int32_t fd, uintptr_t arg, size_t length);

#endif