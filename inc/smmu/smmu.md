# SMMU Driver

This describes the registers and their operational details for integration of the SMMU Host Controller IP into a target design.
All the control over the registers are via IOCTL functions.

## IOCTL_SMMU_IDR0_GET
Get SMMU_IDR0

## IOCTL_SMMU_IDR1_GET
Get SMMU_IDR1

## IOCTL_SMMU_IDR2_GET
Get SMMU_IDR2

## IOCTL_SMMU_IDR3_GET
Get SMMU_IDR3

## IOCTL_SMMU_IDR5_GET
Get SMMU_IDR5

## IOCTL_SMMU_IIDR_GET
Get SMMU_IIDR

## IOCTL_SMMU_AIDR_GET
Get SMMU_AIDR

## IOCTL_SMMU_CR0_GET & IOCTL_SMMU_CR0_SET
Get and Set SMMU_CR0

## IOCTL_SMMU_CR0ACK_GET
Get SMMU_CR0ACK

## IOCTL_SMMU_CR1_GET & IOCTL_SMMU_CR1_SET
Get and Set SMMU_CR1

## IOCTL_SMMU_CR2_GET & IOCTL_SMMU_CR2_SET
Get and Set SMMU_CR2

## IOCTL_SMMU_GBPA_GET & IOCTL_SMMU_GBPA_SET
Get and Set SMMU_GBPA

## IOCTL_SMMU_IRQ_CTRL_GET & IOCTL_SMMU_IRQ_CTRL_SET
Get and Set SMMU_IRQ_CTRL

## IOCTL_SMMU_IRQ_CTRLACK_GET
Get SMMU_IRQ_CTRLACK

## IOCTL_SMMU_GERROR_GET
Get SMMU_GERROR

## IOCTL_SMMU_GERRORN_GET & IOCTL_SMMU_GERRORN_SET
Get and Set SMMU_GERRORN

## IOCTL_SMMU_GERROR_IRQ_CFG0_LO_GET & IOCTL_SMMU_GERROR_IRQ_CFG0_LO_SET
Get and Set SMMU_GERROR_IRQ_CFG0_LO

## IOCTL_SMMU_GERROR_IRQ_CFG0_HI_GET & IOCTL_SMMU_GERROR_IRQ_CFG0_HI_SET
Get and Set SMMU_GERROR_IRQ_CFG0_HI

## IOCTL_SMMU_GERROR_IRQ_CFG1_GET & IOCTL_SMMU_GERROR_IRQ_CFG1_SET
Get and Set SMMU_GERROR_IRQ_CFG1

## IOCTL_SMMU_GERROR_IRQ_CFG2_GET & IOCTL_SMMU_GERROR_IRQ_CFG2_SET
Get and Set SMMU_GERROR_IRQ_CFG2

## IOCTL_SMMU_STRTAB_BASE_LO_GET & IOCTL_SMMU_STRTAB_BASE_LO_SET
Get and Set SMMU_STRTAB_BASE_LO

## IOCTL_SMMU_STRTAB_BASE_HI_GET & IOCTL_SMMU_STRTAB_BASE_HI_SET
Get and Set SMMU_STRTAB_BASE_HI

## IOCTL_SMMU_STRTAB_BASE_CFG_GET & IOCTL_SMMU_STRTAB_BASE_CFG_SET
Get and Set SMMU_STRTAB_BASE_CFG

## IOCTL_SMMU_CMDQ_BASE_LO_GET & IOCTL_SMMU_CMDQ_BASE_LO_SET
Get and Set SMMU_CMDQ_BASE_LO

## IOCTL_SMMU_CMDQ_BASE_HI_GET & IOCTL_SMMU_CMDQ_BASE_HI_SET
Get and Set SMMU_CMDQ_BASE_HI

## IOCTL_SMMU_CMDQ_PROD_GET & IOCTL_SMMU_CMDQ_PROD_SET
Get and Set SMMU_CMDQ_PROD

## IOCTL_SMMU_CMDQ_CONS_GET & IOCTL_SMMU_CMDQ_CONS_SET
Get and Set SMMU_CMDQ_CONS

## IOCTL_SMMU_EVENTQ_BASE_LO_GET & IOCTL_SMMU_EVENTQ_BASE_LO_SET
Get and Set SMMU_EVENTQ_BASE_LO

## IOCTL_SMMU_EVENTQ_BASE_HI_GET & IOCTL_SMMU_EVENTQ_BASE_HI_SET
Get and Set SMMU_EVENTQ_BASE_HI

## IOCTL_SMMU_EVENTQ_IRQ_CFG0_LO_GET & IOCTL_SMMU_EVENTQ_IRQ_CFG0_LO_SET
Get and Set SMMU_EVENTQ_IRQ_CFG0_LO

## IOCTL_SMMU_EVENTQ_IRQ_CFG0_HI_GET & IOCTL_SMMU_EVENTQ_IRQ_CFG0_HI_SET
Get and Set SMMU_EVENTQ_IRQ_CFG0_HI

## IOCTL_SMMU_EVENTQ_IRQ_CFG1_GET & IOCTL_SMMU_EVENTQ_IRQ_CFG1_SET
Get and Set SMMU_EVENTQ_IRQ_CFG1

## IOCTL_SMMU_EVENTQ_IRQ_CFG2_GET & IOCTL_SMMU_EVENTQ_IRQ_CFG2_SET
Get and Set SMMU_EVENTQ_IRQ_CFG2

## IOCTL_SMMU_PRIQ_BASE_LO_GET & IOCTL_SMMU_PRIQ_BASE_LO_SET
Get and Set SMMU_PRIQ_BASE_LO

## IOCTL_SMMU_PRIQ_BASE_HI_GET & IOCTL_SMMU_PRIQ_BASE_HI_SET
Get and Set SMMU_PRIQ_BASE_HI

## IOCTL_SMMU_PRIQ_IRQ_CFG0_LO_GET & IOCTL_SMMU_PRIQ_IRQ_CFG0_LO_SET
Get and Set SMMU_PRIQ_IRQ_CFG0_LO

## IOCTL_SMMU_PRIQ_IRQ_CFG0_HI_GET & IOCTL_SMMU_PRIQ_IRQ_CFG0_HI_SET
Get and Set SMMU_PRIQ_IRQ_CFG0_HI

## IOCTL_SMMU_PRIQ_IRQ_CFG1_GET & IOCTL_SMMU_PRIQ_IRQ_CFG1_SET
Get and Set SMMU_PRIQ_IRQ_CFG1

## IOCTL_SMMU_PRIQ_IRQ_CFG2_GET & IOCTL_SMMU_PRIQ_IRQ_CFG2_SET
Get and Set SMMU_PRIQ_IRQ_CFG2

## IOCTL_SMMU_PIDR0_GET
Get SMMU_PIDR0
This is the TCU Peripheral ID register 0, a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR1_GET
Get SMMU_PIDR1
This is the TCU Peripheral ID register 1, a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR2_GET
Get SMMU_PIDR2
This is the TCU Peripheral ID register 2, a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR3_GET
Get SMMU_PIDR3
This is the TCU Peripheral ID register 3, a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR4_GET
Get SMMU_PIDR4
This is the TCU Peripheral ID register 4. This is a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR5_GET
Get SMMU_PIDR5
This is the TCU Peripheral ID register 5. This is a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR6_GET
Get SMMU_PIDR6
This is the TCU Peripheral ID register 6. This is a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_PIDR7_GET
Get SMMU_PIDR7
This is the TCU Peripheral ID register 7, a standard JEP106 register that provides key information about the MMU-600 hardware. The least significant 8 bits of the eight Peripheral ID registers form a single 64-bit conceptual ID register.

## IOCTL_SMMU_CIDR0_GET
Get SMMU_CIDR0
This is the TCU Component Identification register 0. This register provides information that identifies the MMU-600 as an Arm component.

## IOCTL_SMMU_CIDR1_GET
Get SMMU_CIDR1
This is the TCU Component Identification register 1. This register provides information that identifies the MMU-600 as an Arm component.

## IOCTL_SMMU_CIDR2_GET
Get SMMU_CIDR2
This is the TCU Component Identification register 2. This register provides information that identifies the MMU-600 as an Arm component.

## IOCTL_SMMU_CIDR3_GET
Get SMMU_CIDR3
This is the TCU Component Identification register 3. This register provides information that identifies the MMU-600 as an Arm component.

## IOCTL_SMMU_PMCG_EVTYPER0_GET & IOCTL_SMMU_PMCG_EVTYPER0_SET
Get and Set SMMU_PMCG_EVTYPER0

## IOCTL_SMMU_PMCG_EVTYPER1_GET & IOCTL_SMMU_PMCG_EVTYPER1_SET
Get and Set SMMU_PMCG_EVTYPER1

## IOCTL_SMMU_PMCG_EVTYPER2_GET & IOCTL_SMMU_PMCG_EVTYPER2_SET
Get and Set SMMU_PMCG_EVTYPER2

## IOCTL_SMMU_PMCG_EVTYPER3_GET & IOCTL_SMMU_PMCG_EVTYPER3_SET
Get and Set SMMU_PMCG_EVTYPER3

## IOCTL_SMMU_PMCG_SMR0_GET & IOCTL_SMMU_PMCG_SMR0_SET
Get and Set SMMU_PMCG_SMR0

## IOCTL_SMMU_PMCG_CNTEN_SETBITS
Set SMMU_PMCG_CNTENSET0

## IOCTL_SMMU_PMCG_CNTEN_CLRBITS
Set SMMU_PMCG_CNTENCLR0

## IOCTL_SMMU_PMCG_INTEN_SETBITS
Set SMMU_PMCG_INTENSET0

## IOCTL_SMMU_PMCG_INTEN_CLRBITS
Set SMMU_PMCG_INTENCLR0

## IOCTL_SMMU_PMCG_SCR_GET & IOCTL_SMMU_PMCG_SCR_SET
Get and Set SMMU_PMCG_SCR

## IOCTL_SMMU_PMCG_CFGR_GET & IOCTL_SMMU_PMCG_CFGR_SET
Get and Set SMMU_PMCG_CFGR

## IOCTL_SMMU_PMCG_CR_GET & IOCTL_SMMU_PMCG_CR_SET
Get and Set SMMU_PMCG_CR

## IOCTL_SMMU_PMCG_CEID0_LO_GET
Get SMMU_PMCG_CEID0_LO

## IOCTL_SMMU_PMCG_CEID0_HI_GET
Get SMMU_PMCG_CEID0_HI

## IOCTL_SMMU_PMCG_CEID1_LO_GET
Get SMMU_PMCG_CEID1_LO

## IOCTL_SMMU_PMCG_CEID1_HI_GET
Get SMMU_PMCG_CEID1_HI

## IOCTL_SMMU_PMCG_IRQ_CTRL_GET & IOCTL_SMMU_PMCG_IRQ_CTRL_SET
Get and Set SMMU_PMCG_IRQ_CTRL

## IOCTL_SMMU_PMCG_IRQ_CTRLACK_GET
Get SMMU_PMCG_IRQ_CTRLACK

## IOCTL_SMMU_PMCG_AIDR_GET
Get SMMU_PMCG_AIDR

## IOCTL_SMMU_PMCG_PMAUTHSTATUS_GET
Get SMMU_PMCG_PMAUTHSTATUS

## IOCTL_SMMU_PMCG_PMDEVARCH_GET
Get SMMU_PMCG_PMDEVARCH

## IOCTL_SMMU_PMCG_PMDEVTYPE_GET
Get SMMU_PMCG_PMDEVTYPE

## IOCTL_SMMU_PMCG_PIDR0_GET
Get SMMU_PMCG_PIDR0

## IOCTL_SMMU_PMCG_PIDR1_GET
Get SMMU_PMCG_PIDR1

## IOCTL_SMMU_PMCG_PIDR2_GET
Get SMMU_PMCG_PIDR2

## IOCTL_SMMU_PMCG_PIDR3_GET
Get SMMU_PMCG_PIDR3

## IOCTL_SMMU_PMCG_PIDR4_GET
Get SMMU_PMCG_PIDR4

## IOCTL_SMMU_PMCG_PIDR5_GET
Get SMMU_PMCG_PIDR5

## IOCTL_SMMU_PMCG_PIDR6_GET
Get SMMU_PMCG_PIDR6

## IOCTL_SMMU_PMCG_PIDR7_GET
Get SMMU_PMCG_PIDR7

## IOCTL_SMMU_PMCG_CIDR0_GET
Get SMMU_PMCG_CIDR0

## IOCTL_SMMU_PMCG_CIDR1_GET
Get SMMU_PMCG_CIDR1

## IOCTL_SMMU_PMCG_CIDR2_GET
Get SMMU_PMCG_CIDR2

## IOCTL_SMMU_PMCG_CIDR3_GET
Get SMMU_PMCG_CIDR3

## IOCTL_SMMU_S_IDR0_GET
Get SMMU_S_IDR0

## IOCTL_SMMU_S_IDR1_GET
Get SMMU_S_IDR1

## IOCTL_SMMU_S_IDR3_GET
Get SMMU_S_IDR3

## IOCTL_SMMU_S_CR0_GET & IOCTL_SMMU_S_CR0_SET
Get and Set SMMU_S_CR0

## IOCTL_SMMU_S_CR0ACK_GET & IOCTL_SMMU_S_CR0ACK_SET
Get and Set SMMU_S_CR0ACK

## IOCTL_SMMU_S_CR1_GET & IOCTL_SMMU_S_CR1_SET
Get and Set SMMU_S_CR1

## IOCTL_SMMU_S_CR2_GET & IOCTL_SMMU_S_CR2_SET
Get and Set SMMU_S_CR2

## IOCTL_SMMU_S_INIT_GET & IOCTL_SMMU_S_INIT_SET
Get and Set SMMU_S_INIT

## IOCTL_SMMU_S_GBPA_GET & IOCTL_SMMU_S_GBPA_SET
Get and Set SMMU_S_GBPA

## IOCTL_SMMU_S_IRQ_CTRL_GET & IOCTL_SMMU_S_IRQ_CTRL_SET
Get and Set SMMU_S_IRQ_CTRL

## IOCTL_SMMU_S_IRQ_CTRLACK_GET
Get SMMU_S_IRQ_CTRLACK

## IOCTL_SMMU_S_GERROR_GET
Get SMMU_S_GERROR

## IOCTL_SMMU_S_GERRORN_GET & IOCTL_SMMU_S_GERRORN_SET
Get and Set SMMU_S_GERRORN

## IOCTL_SMMU_S_GERROR_IRQ_CFG0_LO_GET & IOCTL_SMMU_S_GERROR_IRQ_CFG0_LO_SET
Get and Set SMMU_S_GERROR_IRQ_CFG0_LO

## IOCTL_SMMU_S_GERROR_IRQ_CFG0_HI_GET & IOCTL_SMMU_S_GERROR_IRQ_CFG0_HI_SET
Get and Set SMMU_S_GERROR_IRQ_CFG0_HI

## IOCTL_SMMU_S_GERROR_IRQ_CFG1_GET & IOCTL_SMMU_S_GERROR_IRQ_CFG1_SET
Get and Set SMMU_S_GERROR_IRQ_CFG1

## IOCTL_SMMU_S_GERROR_IRQ_CFG2_GET & IOCTL_SMMU_S_GERROR_IRQ_CFG2_SET
Get and Set SMMU_S_GERROR_IRQ_CFG2

## IOCTL_SMMU_S_STRTAB_BASE_LO_GET & IOCTL_SMMU_S_STRTAB_BASE_LO_SET
Get and Set SMMU_S_STRTAB_BASE_LO

## IOCTL_SMMU_S_STRTAB_BASE_HI_GET & IOCTL_SMMU_S_STRTAB_BASE_HI_SET
Get and Set SMMU_S_STRTAB_BASE_HI

## IOCTL_SMMU_S_STRTAB_BASE_CFG_GET & IOCTL_SMMU_S_STRTAB_BASE_CFG_SET
Get and Set SMMU_S_STRTAB_BASE_CFG

## IOCTL_SMMU_S_CMDQ_BASE_LO_GET & IOCTL_SMMU_S_CMDQ_BASE_LO_SET
Get and Set SMMU_S_CMDQ_BASE_LO

## IOCTL_SMMU_S_CMDQ_BASE_HI_GET & IOCTL_SMMU_S_CMDQ_BASE_HI_SET
Get and Set SMMU_S_CMDQ_BASE_HI

## IOCTL_SMMU_S_CMDQ_PROD_GET & IOCTL_SMMU_S_CMDQ_PROD_SET
Get and Set SMMU_S_CMDQ_PROD

## IOCTL_SMMU_S_CMDQ_CONS_GET & IOCTL_SMMU_S_CMDQ_CONS_SET
Get and Set SMMU_S_CMDQ_CONS

## IOCTL_SMMU_S_EVENTQ_BASE_LO_GET & IOCTL_SMMU_S_EVENTQ_BASE_LO_SET
Get and Set SMMU_S_EVENTQ_BASE_LO

## IOCTL_SMMU_S_EVENTQ_BASE_HI_GET & IOCTL_SMMU_S_EVENTQ_BASE_HI_SET
Get and Set SMMU_S_EVENTQ_BASE_HI

## IOCTL_SMMU_S_EVENTQ_PROD_GET & IOCTL_SMMU_S_EVENTQ_PROD_SET
Get and Set SMMU_S_EVENTQ_PROD

## IOCTL_SMMU_S_EVENTQ_CONS_GET & IOCTL_SMMU_S_EVENTQ_CONS_SET
Get and Set SMMU_S_EVENTQ_CONS

## IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_LO_GET & IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_LO_SET
Get and Set SMMU_S_EVENTQ_IRQ_CFG0_LO

## IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_HI_GET & IOCTL_SMMU_S_EVENTQ_IRQ_CFG0_HI_SET
Get and Set SMMU_S_EVENTQ_IRQ_CFG0_HI

## IOCTL_SMMU_S_EVENTQ_IRQ_CFG1_GET & IOCTL_SMMU_S_EVENTQ_IRQ_CFG1_SET
Get and Set SMMU_S_EVENTQ_IRQ_CFG1

## IOCTL_SMMU_S_EVENTQ_IRQ_CFG2_GET & IOCTL_SMMU_S_EVENTQ_IRQ_CFG2_SET
Get and Set SMMU_S_EVENTQ_IRQ_CFG2

## IOCTL_SMMU_TCU_CTRL_GET & IOCTL_SMMU_TCU_CTRL_SET
Get and Set TCU_CTRL
The TCU Control register disables TCU features. You can disable individual walk caches, which can improve performance in some systems if the hit rate of the individual walk cache is very low. Do not modify the other bits unless directed to by Arm.

## IOCTL_SMMU_TCU_QOS_GET & IOCTL_SMMU_TCU_QOS_SET
Get and Set TCU_QOS
This is the TCU Quality of Service register. Use this register to specify QoS values for each transaction type. The MMU-600 uses the QoS value as a priority indicator for arbitration of requests.

## IOCTL_SMMU_TCU_CFG_GET & IOCTL_SMMU_TCU_CFG_SET
Get and Set TCU_CFG
This is the TCU Configuration Information register.

## IOCTL_SMMU_TCU_STATUS_GET
Get TCU_STATUS
This is the TCU Status Information register.

## IOCTL_SMMU_TCU_SCR_GET & IOCTL_SMMU_TCU_SCR_SET
Get and Set TCU_SCR
This is the TCU Secure Control register.

## IOCTL_SMMU_TCU_ERRFR_LO_GET
Get TCU_ERRFR_LO

## IOCTL_SMMU_TCU_ERRFR_HI_GET
Get TCU_ERRFR_HI

## IOCTL_SMMU_TCU_ERRCTLR_LO_GET & IOCTL_SMMU_TCU_ERRCTLR_LO_SET
Get and Set TCU_ERRCTLR_LO

## IOCTL_SMMU_TCU_ERRCTLR_HI_GET
Get TCU_ERRCTLR_HI

## IOCTL_SMMU_TCU_ERRSTATUS_LO_GET & IOCTL_SMMU_TCU_ERRSTATUS_LO_SET
Get and Set TCU_ERRSTATUS_LO

## IOCTL_SMMU_TCU_ERRSTATUS_HI_GET
Get TCU_ERRSTATUS_HI

## IOCTL_SMMU_TCU_ERRGEN_LO_GET & IOCTL_SMMU_TCU_ERRGEN_LO_SET
Get and Set TCU_ERRGEN_LO

## IOCTL_SMMU_TCU_ERRGEN_HI_GET
Get TCU_ERRGEN_HI

## IOCTL_SMMU_TCU_NODE_CTRL_GET & IOCTL_SMMU_TCU_NODE_CTRL_SET
Get and Set TCU_NODE_CTRL
This includes all NODE_CTRL registers 0:61

## IOCTL_SMMU_TCU_NODE_STATUS_GET
Get TCU_NODE_STATUS
This includes all NODE_STATUS registers 0:61

## IOCTL_SMMU_EVENTQ_PROD_GET & IOCTL_SMMU_EVENTQ_PROD_SET
Get and Set SMMU_EVENTQ_PROD

## IOCTL_SMMU_EVENTQ_CONS_GET & IOCTL_SMMU_EVENTQ_CONS_SET
Get and Set SMMU_EVENTQ_CONS

## IOCTL_SMMU_PRIQ_PROD_GET & IOCTL_SMMU_PRIQ_PROD_SET
Get and Set SMMU_PRIQ_PROD

## IOCTL_SMMU_PRIQ_CONS_GET & IOCTL_SMMU_PRIQ_CONS_SET
Get and Set SMMU_PRIQ_CONS

## IOCTL_SMMU_PMCG_EVCNTR0_GET & IOCTL_SMMU_PMCG_EVCNTR0_SET
Get and Set SMMU_PMCG_EVCNTR0

## IOCTL_SMMU_PMCG_EVCNTR1_GET & IOCTL_SMMU_PMCG_EVCNTR1_SET
Get and Set SMMU_PMCG_EVCNTR1

## IOCTL_SMMU_PMCG_EVCNTR2_GET & IOCTL_SMMU_PMCG_EVCNTR2_SET
Get and Set SMMU_PMCG_EVCNTR2

## IOCTL_SMMU_PMCG_EVCNTR3_GET & IOCTL_SMMU_PMCG_EVCNTR3_SET
Get and Set SMMU_PMCG_EVCNTR3

## IOCTL_SMMU_PMCG_SVR0_GET
Get SMMU_PMCG_SVR0

## IOCTL_SMMU_PMCG_SVR1_GET
Get SMMU_PMCG_SVR1

## IOCTL_SMMU_PMCG_SVR2_GET
Get SMMU_PMCG_SVR2

## IOCTL_SMMU_PMCG_SVR3_GET
Get SMMU_PMCG_SVR3

## IOCTL_SMMU_PMCG_OVS_CLRBITS
Clear SMMU_PMCG_OVSCLR0

## IOCTL_SMMU_PMCG_OVS_SETBITS
Set SMMU_PMCG_OVSSET0

## IOCTL_SMMU_PMCG_CAPR_SET
Set SMMU_PMCG_CAPR

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_SMMU_and_TCU_summary.html