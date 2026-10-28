/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_smmu_reg.h
 *
 * SMMU register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef _SOCFPGA_SMMU_REG_H_
#define _SOCFPGA_SMMU_REG_H_

#define SMMU_BASE_ADDR                          0x16000000
/* SMMU_IDR0 */
#define SMMU_IDR0                               0x0000
/* SMMU_IDR1 */
#define SMMU_IDR1                               0x0004
/* SMMU_IDR2 */
#define SMMU_IDR2                               0x0008
/* SMMU_IDR3 */
#define SMMU_IDR3                               0x000C
/* SMMU_IDR5 */
#define SMMU_IDR5                               0x0014
/* SMMU_IIDR */
#define SMMU_IIDR                               0x0018
/* SMMU_AIDR */
#define SMMU_AIDR                               0x001C
/* SMMU_CR0 */
#define SMMU_CR0                                0x0020
/* SMMU_CR0ACK */
#define SMMU_CR0ACK                             0x0024
/* SMMU_CR1 */
#define SMMU_CR1                                0x0028
/* SMMU_CR2 */
#define SMMU_CR2                                0x002C
/* SMMU_GBPA */
#define SMMU_GBPA                               0x0044
/* SMMU_IRQ_CTRL */
#define SMMU_IRQ_CTRL                           0x0050
/* SMMU_IRQ_CTRLACK */
#define SMMU_IRQ_CTRLACK                        0x0054
/* SMMU_GERROR */
#define SMMU_GERROR                             0x0060
/* SMMU_GERRORN */
#define SMMU_GERRORN                            0x0064
/* SMMU_GERROR_IRQ_CFG0 (Least Significant 32-bits) */
#define SMMU_GERROR_IRQ_CFG0_LO                 0x0068
/* SMMU_GERROR_IRQ_CFG0 (Most Significant 32-bits) */
#define SMMU_GERROR_IRQ_CFG0_HI                 0x006C
/* SMMU_GERROR_IRQ_CFG1 */
#define SMMU_GERROR_IRQ_CFG1                    0x0070
/* SMMU_GERROR_IRQ_CFG2 */
#define SMMU_GERROR_IRQ_CFG2                    0x0074
/* SMMU_STRTAB_BASE (Least Significant 32-bits) */
#define SMMU_STRTAB_BASE_LO                     0x0080
/* SMMU_STRTAB_BASE (Most Significant 32-bits) */
#define SMMU_STRTAB_BASE_HI                     0x0084
/* SMMU_STRTAB_BASE_CFG */
#define SMMU_STRTAB_BASE_CFG                    0x0088
/* SMMU_CMDQ_BASE (Least Significant 32-bits) */
#define SMMU_CMDQ_BASE_LO                       0x0090
/* SMMU_CMDQ_BASE (Most Significant 32-bits) */
#define SMMU_CMDQ_BASE_HI                       0x0094
/* SMMU_CMDQ_PROD */
#define SMMU_CMDQ_PROD                          0x0098
/* SMMU_CMDQ_CONS */
#define SMMU_CMDQ_CONS                          0x009C
/* SMMU_EVENTQ_BASE (Least Significant 32-bits) */
#define SMMU_EVENTQ_BASE_LO                     0x00A0
/* SMMU_EVENTQ_BASE (Most Significant 32-bits) */
#define SMMU_EVENTQ_BASE_HI                     0x00A4
/* SMMU_EVENTQ_IRQ_CFG0 (Least Significant 32-bits) */
#define SMMU_EVENTQ_IRQ_CFG0_LO                 0x00B0
/* SMMU_EVENTQ_IRQ_CFG0 (Most Significant 32-bits) */
#define SMMU_EVENTQ_IRQ_CFG0_HI                 0x00B4
/* SMMU_EVENTQ_IRQ_CFG1 */
#define SMMU_EVENTQ_IRQ_CFG1                    0x00B8
/* SMMU_EVENTQ_IRQ_CFG2 */
#define SMMU_EVENTQ_IRQ_CFG2                    0x00BC
/* SMMU_PRIQ_BASE (Least Significant 32-bits) */
#define SMMU_PRIQ_BASE_LO                       0x00C0
/* SMMU_PRIQ_BASE (Most Significant 32-bits) */
#define SMMU_PRIQ_BASE_HI                       0x00C4
/* SMMU_PRIQ_IRQ_CFG0 (Least Significant 32-bits) */
#define SMMU_PRIQ_IRQ_CFG0_LO                   0x00D0
/* SMMU_PRIQ_IRQ_CFG0 (Most Significant 32-bits) */
#define SMMU_PRIQ_IRQ_CFG0_HI                   0x00D4
/* SMMU_PRIQ_IRQ_CFG1 */
#define SMMU_PRIQ_IRQ_CFG1                      0x00D8
/* SMMU_PRIQ_IRQ_CFG2 */
#define SMMU_PRIQ_IRQ_CFG2                      0x00DC
/* Peripheral ID4 */
#define SMMU_PIDR4                              0x0FD0
/* Peripheral ID5 */
#define SMMU_PIDR5                              0x0FD4
/* Peripheral ID6 */
#define SMMU_PIDR6                              0x0FD8
/* Peripheral ID7 */
#define SMMU_PIDR7                              0x0FDC
/* Peripheral ID0 */
#define SMMU_PIDR0                              0x0FE0
/* Peripheral ID1 */
#define SMMU_PIDR1                              0x0FE4
/* Peripheral ID2 */
#define SMMU_PIDR2                              0x0FE8
/* Peripheral ID3 */
#define SMMU_PIDR3                              0x0FEC
/* Component ID0 */
#define SMMU_CIDR0                              0x0FF0
/* Component ID1 */
#define SMMU_CIDR1                              0x0FF4
/* Component ID2 */
#define SMMU_CIDR2                              0x0FF8
/* Component ID3 */
#define SMMU_CIDR3                              0x0FFC
/* SMMU_PMCG_EVTYPER0 */
#define SMMU_PMCG_EVTYPER0                      0x2400
/* SMMU_PMCG_EVTYPER1 */
#define SMMU_PMCG_EVTYPER1                      0x2404
/* SMMU_PMCG_EVTYPER2 */
#define SMMU_PMCG_EVTYPER2                      0x2408
/* SMMU_PMCG_EVTYPER3 */
#define SMMU_PMCG_EVTYPER3                      0x240C
/* SMMU_PMCG_SMR0 */
#define SMMU_PMCG_SMR0                          0x2A00
/* SMMU_PMCG_CNTENSET0 */
#define SMMU_PMCG_CNTENSET0                     0x2C00
/* SMMU_PMCG_CNTENCLR0 */
#define SMMU_PMCG_CNTENCLR0                     0x2C20
/* SMMU_PMCG_INTENSET0 */
#define SMMU_PMCG_INTENSET0                     0x2C40
/* SMMU_PMCG_INTENCLR0 */
#define SMMU_PMCG_INTENCLR0                     0x2C60
/* SMMU_PMCG_SCR */
#define SMMU_PMCG_SCR                           0x2DF8
/* SMMU_PMCG_CFGR */
#define SMMU_PMCG_CFGR                          0x2E00
/* SMMU_PMCG_CR */
#define SMMU_PMCG_CR                            0x2E04
/* SMMU_PMCG_CEID0 (Least Significant 32-bits) */
#define SMMU_PMCG_CEID0_LO                      0x2E20
/* SMMU_PMCG_CEID0 (Most Significant 32-bits) */
#define SMMU_PMCG_CEID0_HI                      0x2E24
/* SMMU_PMCG_CEID1 (Least Significant 32-bits) */
#define SMMU_PMCG_CEID1_LO                      0x2E28
/* SMMU_PMCG_CEID1 (Most Significant 32-bits) */
#define SMMU_PMCG_CEID1_HI                      0x2E2C
/* SMMU_PMCG_IRQ_CTRL */
#define SMMU_PMCG_IRQ_CTRL                      0x2E50
/* SMMU_PMCG_IRQ_CTRLACK */
#define SMMU_PMCG_IRQ_CTRLACK                   0x2E54
/* SMMU_PMCG_AIDR */
#define SMMU_PMCG_AIDR                          0x2E70
/* PMU Authentication Status Register */
#define SMMU_PMCG_PMAUTHSTATUS                  0x2FB8
/* PMU Device Architecture Register */
#define SMMU_PMCG_PMDEVARCH                     0x2FBC
/* PMU Device Type Register */
#define SMMU_PMCG_PMDEVTYPE                     0x2FCC
/* PMU Peripheral ID4 */
#define SMMU_PMCG_PIDR4                         0x2FD0
/* PMU Peripheral ID5 */
#define SMMU_PMCG_PIDR5                         0x2FD4
/* PMU Peripheral ID6 */
#define SMMU_PMCG_PIDR6                         0x2FD8
/* PMU Peripheral ID7 */
#define SMMU_PMCG_PIDR7                         0x2FDC
/* PMU Peripheral ID0 */
#define SMMU_PMCG_PIDR0                         0x2FE0
/* PMU Peripheral ID1 */
#define SMMU_PMCG_PIDR1                         0x2FE4
/* PMU Peripheral ID2 */
#define SMMU_PMCG_PIDR2                         0x2FE8
/* PMU Peripheral ID3 */
#define SMMU_PMCG_PIDR3                         0x2FEC
/* PMU Component ID0 */
#define SMMU_PMCG_CIDR0                         0x2FF0
/* PMU Component ID1 */
#define SMMU_PMCG_CIDR1                         0x2FF4
/* PMU Component ID2 */
#define SMMU_PMCG_CIDR2                         0x2FF8
/* PMU Component ID3 */
#define SMMU_PMCG_CIDR3                         0x2FFC
/* SMMU_S_IDR0 */
#define SMMU_S_IDR0                             0x8000
/* SMMU_S_IDR1 */
#define SMMU_S_IDR1                             0x8004
/* SMMU_S_IDR3 */
#define SMMU_S_IDR3                             0x800C
/* SMMU_S_CR0 */
#define SMMU_S_CR0                              0x8020
/* SMMU_S_CR0ACK */
#define SMMU_S_CR0ACK                           0x8024
/* SMMU_S_CR1 */
#define SMMU_S_CR1                              0x8028
/* SMMU_S_CR2 */
#define SMMU_S_CR2                              0x802C
/* SMMU_S_INIT */
#define SMMU_S_INIT                             0x803C
/* SMMU_S_GBPA */
#define SMMU_S_GBPA                             0x8044
/* SMMU_S_IRQ_CTRL */
#define SMMU_S_IRQ_CTRL                         0x8050
/* SMMU_S_IRQ_CTRLACK */
#define SMMU_S_IRQ_CTRLACK                      0x8054
/* SMMU_S_GERROR */
#define SMMU_S_GERROR                           0x8060
/* SMMU_S_GERRORN */
#define SMMU_S_GERRORN                          0x8064
/* SMMU_S_GERROR_IRQ_CFG0 (Least Significant 32-bits) */
#define SMMU_S_GERROR_IRQ_CFG0_LO               0x8068
/* SMMU_S_GERROR_IRQ_CFG0 (Most Significant 32-bits) */
#define SMMU_S_GERROR_IRQ_CFG0_HI               0x806C
/* SMMU_S_GERROR_IRQ_CFG1 */
#define SMMU_S_GERROR_IRQ_CFG1                  0x8070
/* SMMU_S_GERROR_IRQ_CFG2 */
#define SMMU_S_GERROR_IRQ_CFG2                  0x8074
/* SMMU_S_STRTAB_BASE (Least Significant 32-bits) */
#define SMMU_S_STRTAB_BASE_LO                   0x8080
/* SMMU_S_STRTAB_BASE (Most Significant 32-bits) */
#define SMMU_S_STRTAB_BASE_HI                   0x8084
/* SMMU_S_STRTAB_BASE_CFG */
#define SMMU_S_STRTAB_BASE_CFG                  0x8088
/* SMMU_S_CMDQ_BASE (Least Significant 32-bits) */
#define SMMU_S_CMDQ_BASE_LO                     0x8090
/* SMMU_S_CMDQ_BASE (Most Significant 32-bits) */
#define SMMU_S_CMDQ_BASE_HI                     0x8094
/* SMMU_S_CMDQ_PROD */
#define SMMU_S_CMDQ_PROD                        0x8098
/* SMMU_S_CMDQ_CONS */
#define SMMU_S_CMDQ_CONS                        0x809C
/* SMMU_S_EVENTQ_BASE (Least Significant 32-bits) */
#define SMMU_S_EVENTQ_BASE_LO                   0x80A0
/* SMMU_S_EVENTQ_BASE (Most Significant 32-bits) */
#define SMMU_S_EVENTQ_BASE_HI                   0x80A4
/* SMMU_S_EVENTQ_PROD */
#define SMMU_S_EVENTQ_PROD                      0x80A8
/* SMMU_S_EVENTQ_CONS */
#define SMMU_S_EVENTQ_CONS                      0x80AC
/* SMMU_S_EVENTQ_IRQ_CFG0 (Least Significant 32-bits) */
#define SMMU_S_EVENTQ_IRQ_CFG0_LO               0x80B0
/* SMMU_S_EVENTQ_IRQ_CFG0 (Most Significant 32-bits) */
#define SMMU_S_EVENTQ_IRQ_CFG0_HI               0x80B4
/* SMMU_S_EVENTQ_IRQ_CFG1 */
#define SMMU_S_EVENTQ_IRQ_CFG1                  0x80B8
/* SMMU_S_EVENTQ_IRQ_CFG2 */
#define SMMU_S_EVENTQ_IRQ_CFG2                  0x80BC
/* TCU Control Register */
#define S_TCU_CTRL                              0x8E00
/* TCU Quality of Service Register */
#define S_TCU_QOS                               0x8E04
/* TCU Configuration Information Register */
#define S_TCU_CFG                               0x8E08
/* TCU Status Information Register */
#define S_TCU_STATUS                            0x8E10
/* TCU Secure Control Register */
#define S_TCU_SCR                               0x8E18
/* TCU Error Feature Register (Least Significant 32-bits) */
#define S_TCU_ERRFR_LO                          0x8E80
/* TCU Error Feature Register (Most Significant 32-bits) */
#define S_TCU_ERRFR_HI                          0x8E84
/* TCU Error Control Register (Least Significant 32-bits) */
#define S_TCU_ERRCTLR_LO                        0x8E88
/* TCU Error Control Register (Most Significant 32-bits) */
#define S_TCU_ERRCTLR_HI                        0x8E8C
/* TCU Error Status Register (Least Significant 32-bits) */
#define S_TCU_ERRSTATUS_LO                      0x8E90
/* TCU Error Status Register (Most Significant 32-bits) */
#define S_TCU_ERRSTATUS_HI                      0x8E94
/* TCU Error Generation Register (Least Significant 32-bits) */
#define S_TCU_ERRGEN_LO                         0x8EC0
/* TCU Error Generation Register (Most Significant 32-bits) */
#define S_TCU_ERRGEN_HI                         0x8EC4
/* TCU Node Control Register0 */
#define S_TCU_NODE_CTRL0                        0x9000
/* TCU Node Control Register1 */
#define S_TCU_NODE_CTRL1                        0x9004
/* TCU Node Control Register2 */
#define S_TCU_NODE_CTRL2                        0x9008
/* TCU Node Control Register3 */
#define S_TCU_NODE_CTRL3                        0x900C
/* TCU Node Control Register4 */
#define S_TCU_NODE_CTRL4                        0x9010
/* TCU Node Control Register5 */
#define S_TCU_NODE_CTRL5                        0x9014
/* TCU Node Control Register6 */
#define S_TCU_NODE_CTRL6                        0x9018
/* TCU Node Control Register7 */
#define S_TCU_NODE_CTRL7                        0x901C
/* TCU Node Control Register8 */
#define S_TCU_NODE_CTRL8                        0x9020
/* TCU Node Control Register9 */
#define S_TCU_NODE_CTRL9                        0x9024
/* TCU Node Control Register10 */
#define S_TCU_NODE_CTRL10                       0x9028
/* TCU Node Control Register11 */
#define S_TCU_NODE_CTRL11                       0x902C
/* TCU Node Control Register12 */
#define S_TCU_NODE_CTRL12                       0x9030
/* TCU Node Control Register13 */
#define S_TCU_NODE_CTRL13                       0x9034
/* TCU Node Control Register14 */
#define S_TCU_NODE_CTRL14                       0x9038
/* TCU Node Control Register15 */
#define S_TCU_NODE_CTRL15                       0x903C
/* TCU Node Control Register16 */
#define S_TCU_NODE_CTRL16                       0x9040
/* TCU Node Control Register17 */
#define S_TCU_NODE_CTRL17                       0x9044
/* TCU Node Control Register18 */
#define S_TCU_NODE_CTRL18                       0x9048
/* TCU Node Control Register19 */
#define S_TCU_NODE_CTRL19                       0x904C
/* TCU Node Control Register20 */
#define S_TCU_NODE_CTRL20                       0x9050
/* TCU Node Control Register21 */
#define S_TCU_NODE_CTRL21                       0x9054
/* TCU Node Control Register22 */
#define S_TCU_NODE_CTRL22                       0x9058
/* TCU Node Control Register23 */
#define S_TCU_NODE_CTRL23                       0x905C
/* TCU Node Control Register24 */
#define S_TCU_NODE_CTRL24                       0x9060
/* TCU Node Control Register25 */
#define S_TCU_NODE_CTRL25                       0x9064
/* TCU Node Control Register26 */
#define S_TCU_NODE_CTRL26                       0x9068
/* TCU Node Control Register27 */
#define S_TCU_NODE_CTRL27                       0x906C
/* TCU Node Control Register28 */
#define S_TCU_NODE_CTRL28                       0x9070
/* TCU Node Control Register29 */
#define S_TCU_NODE_CTRL29                       0x9074
/* TCU Node Control Register30 */
#define S_TCU_NODE_CTRL30                       0x9078
/* TCU Node Control Register31 */
#define S_TCU_NODE_CTRL31                       0x907C
/* TCU Node Control Register32 */
#define S_TCU_NODE_CTRL32                       0x9080
/* TCU Node Control Register33 */
#define S_TCU_NODE_CTRL33                       0x9084
/* TCU Node Control Register34 */
#define S_TCU_NODE_CTRL34                       0x9088
/* TCU Node Control Register35 */
#define S_TCU_NODE_CTRL35                       0x908C
/* TCU Node Control Register36 */
#define S_TCU_NODE_CTRL36                       0x9090
/* TCU Node Control Register37 */
#define S_TCU_NODE_CTRL37                       0x9094
/* TCU Node Control Register38 */
#define S_TCU_NODE_CTRL38                       0x9098
/* TCU Node Control Register39 */
#define S_TCU_NODE_CTRL39                       0x909C
/* TCU Node Control Register40 */
#define S_TCU_NODE_CTRL40                       0x90A0
/* TCU Node Control Register41 */
#define S_TCU_NODE_CTRL41                       0x90A4
/* TCU Node Control Register42 */
#define S_TCU_NODE_CTRL42                       0x90A8
/* TCU Node Control Register43 */
#define S_TCU_NODE_CTRL43                       0x90AC
/* TCU Node Control Register44 */
#define S_TCU_NODE_CTRL44                       0x90B0
/* TCU Node Control Register45 */
#define S_TCU_NODE_CTRL45                       0x90B4
/* TCU Node Control Register46 */
#define S_TCU_NODE_CTRL46                       0x90B8
/* TCU Node Control Register47 */
#define S_TCU_NODE_CTRL47                       0x90BC
/* TCU Node Control Register48 */
#define S_TCU_NODE_CTRL48                       0x90C0
/* TCU Node Control Register49 */
#define S_TCU_NODE_CTRL49                       0x90C4
/* TCU Node Control Register50 */
#define S_TCU_NODE_CTRL50                       0x90C8
/* TCU Node Control Register51 */
#define S_TCU_NODE_CTRL51                       0x90CC
/* TCU Node Control Register52 */
#define S_TCU_NODE_CTRL52                       0x90D0
/* TCU Node Control Register53 */
#define S_TCU_NODE_CTRL53                       0x90D4
/* TCU Node Control Register54 */
#define S_TCU_NODE_CTRL54                       0x90D8
/* TCU Node Control Register55 */
#define S_TCU_NODE_CTRL55                       0x90DC
/* TCU Node Control Register56 */
#define S_TCU_NODE_CTRL56                       0x90E0
/* TCU Node Control Register57 */
#define S_TCU_NODE_CTRL57                       0x90E4
/* TCU Node Control Register58 */
#define S_TCU_NODE_CTRL58                       0x90E8
/* TCU Node Control Register59 */
#define S_TCU_NODE_CTRL59                       0x90EC
/* TCU Node Control Register60 */
#define S_TCU_NODE_CTRL60                       0x90F0
/* TCU Node Control Register61 */
#define S_TCU_NODE_CTRL61                       0x90F4
/* TCU Node Status Register0 */
#define S_TCU_NODE_STATUS0                      0x9400
/* TCU Node Status Register1 */
#define S_TCU_NODE_STATUS1                      0x9404
/* TCU Node Status Register2 */
#define S_TCU_NODE_STATUS2                      0x9408
/* TCU Node Status Register3 */
#define S_TCU_NODE_STATUS3                      0x940C
/* TCU Node Status Register4 */
#define S_TCU_NODE_STATUS4                      0x9410
/* TCU Node Status Register5 */
#define S_TCU_NODE_STATUS5                      0x9414
/* TCU Node Status Register6 */
#define S_TCU_NODE_STATUS6                      0x9418
/* TCU Node Status Register7 */
#define S_TCU_NODE_STATUS7                      0x941C
/* TCU Node Status Register8 */
#define S_TCU_NODE_STATUS8                      0x9420
/* TCU Node Status Register9 */
#define S_TCU_NODE_STATUS9                      0x9424
/* TCU Node Status Register10 */
#define S_TCU_NODE_STATUS10                     0x9428
/* TCU Node Status Register11 */
#define S_TCU_NODE_STATUS11                     0x942C
/* TCU Node Status Register12 */
#define S_TCU_NODE_STATUS12                     0x9430
/* TCU Node Status Register13 */
#define S_TCU_NODE_STATUS13                     0x9434
/* TCU Node Status Register14 */
#define S_TCU_NODE_STATUS14                     0x9438
/* TCU Node Status Register15 */
#define S_TCU_NODE_STATUS15                     0x943C
/* TCU Node Status Register16 */
#define S_TCU_NODE_STATUS16                     0x9440
/* TCU Node Status Register17 */
#define S_TCU_NODE_STATUS17                     0x9444
/* TCU Node Status Register18 */
#define S_TCU_NODE_STATUS18                     0x9448
/* TCU Node Status Register19 */
#define S_TCU_NODE_STATUS19                     0x944C
/* TCU Node Status Register20 */
#define S_TCU_NODE_STATUS20                     0x9450
/* TCU Node Status Register21 */
#define S_TCU_NODE_STATUS21                     0x9454
/* TCU Node Status Register22 */
#define S_TCU_NODE_STATUS22                     0x9458
/* TCU Node Status Register23 */
#define S_TCU_NODE_STATUS23                     0x945C
/* TCU Node Status Register24 */
#define S_TCU_NODE_STATUS24                     0x9460
/* TCU Node Status Register25 */
#define S_TCU_NODE_STATUS25                     0x9464
/* TCU Node Status Register26 */
#define S_TCU_NODE_STATUS26                     0x9468
/* TCU Node Status Register27 */
#define S_TCU_NODE_STATUS27                     0x946C
/* TCU Node Status Register28 */
#define S_TCU_NODE_STATUS28                     0x9470
/* TCU Node Status Register29 */
#define S_TCU_NODE_STATUS29                     0x9474
/* TCU Node Status Register30 */
#define S_TCU_NODE_STATUS30                     0x9478
/* TCU Node Status Register31 */
#define S_TCU_NODE_STATUS31                     0x947C
/* TCU Node Status Register32 */
#define S_TCU_NODE_STATUS32                     0x9480
/* TCU Node Status Register33 */
#define S_TCU_NODE_STATUS33                     0x9484
/* TCU Node Status Register34 */
#define S_TCU_NODE_STATUS34                     0x9488
/* TCU Node Status Register35 */
#define S_TCU_NODE_STATUS35                     0x948C
/* TCU Node Status Register36 */
#define S_TCU_NODE_STATUS36                     0x9490
/* TCU Node Status Register37 */
#define S_TCU_NODE_STATUS37                     0x9494
/* TCU Node Status Register38 */
#define S_TCU_NODE_STATUS38                     0x9498
/* TCU Node Status Register39 */
#define S_TCU_NODE_STATUS39                     0x949C
/* TCU Node Status Register40 */
#define S_TCU_NODE_STATUS40                     0x94A0
/* TCU Node Status Register41 */
#define S_TCU_NODE_STATUS41                     0x94A4
/* TCU Node Status Register42 */
#define S_TCU_NODE_STATUS42                     0x94A8
/* TCU Node Status Register43 */
#define S_TCU_NODE_STATUS43                     0x94AC
/* TCU Node Status Register44 */
#define S_TCU_NODE_STATUS44                     0x94B0
/* TCU Node Status Register45 */
#define S_TCU_NODE_STATUS45                     0x94B4
/* TCU Node Status Register46 */
#define S_TCU_NODE_STATUS46                     0x94B8
/* TCU Node Status Register47 */
#define S_TCU_NODE_STATUS47                     0x94BC
/* TCU Node Status Register48 */
#define S_TCU_NODE_STATUS48                     0x94C0
/* TCU Node Status Register49 */
#define S_TCU_NODE_STATUS49                     0x94C4
/* TCU Node Status Register50 */
#define S_TCU_NODE_STATUS50                     0x94C8
/* TCU Node Status Register51 */
#define S_TCU_NODE_STATUS51                     0x94CC
/* TCU Node Status Register52 */
#define S_TCU_NODE_STATUS52                     0x94D0
/* TCU Node Status Register53 */
#define S_TCU_NODE_STATUS53                     0x94D4
/* TCU Node Status Register54 */
#define S_TCU_NODE_STATUS54                     0x94D8
/* TCU Node Status Register55 */
#define S_TCU_NODE_STATUS55                     0x94DC
/* TCU Node Status Register56 */
#define S_TCU_NODE_STATUS56                     0x94E0
/* TCU Node Status Register57 */
#define S_TCU_NODE_STATUS57                     0x94E4
/* TCU Node Status Register58 */
#define S_TCU_NODE_STATUS58                     0x94E8
/* TCU Node Status Register59 */
#define S_TCU_NODE_STATUS59                     0x94EC
/* TCU Node Status Register60 */
#define S_TCU_NODE_STATUS60                     0x94F0
/* TCU Node Status Register61 */
#define S_TCU_NODE_STATUS61                     0x94F4
/* SMMU_EVENTQ_PROD */
#define SMMU_EVENTQ_PROD                        0x100A8
/* SMMU_EVENTQ_CONS */
#define SMMU_EVENTQ_CONS                        0x100AC
/* SMMU_PRIQ_PROD */
#define SMMU_PRIQ_PROD                          0x100C8
/* SMMU_PRIQ_CONS */
#define SMMU_PRIQ_CONS                          0x100CC
/* SMMU_PMCG_EVCNTR0 */
#define SMMU_PMCG_EVCNTR0                       0x22000
/* SMMU_PMCG_EVCNTR1 */
#define SMMU_PMCG_EVCNTR1                       0x22004
/* SMMU_PMCG_EVCNTR2 */
#define SMMU_PMCG_EVCNTR2                       0x22008
/* SMMU_PMCG_EVCNTR3 */
#define SMMU_PMCG_EVCNTR3                       0x2200C
/* SMMU_PMCG_SVR0 */
#define SMMU_PMCG_SVR0                          0x22600
/* SMMU_PMCG_SVR1 */
#define SMMU_PMCG_SVR1                          0x22604
/* SMMU_PMCG_SVR2 */
#define SMMU_PMCG_SVR2                          0x22608
/* SMMU_PMCG_SVR3 */
#define SMMU_PMCG_SVR3                          0x2260C
/* SMMU_PMCG_OVSCLR0 */
#define SMMU_PMCG_OVSCLR0                       0x22C80
/* SMMU_PMCG_OVSSET0 */
#define SMMU_PMCG_OVSSET0                       0x22CC0
/* SMMU_PMCG_CAPR */
#define SMMU_PMCG_CAPR                          0x22D88

/* Bit fields of SMMU_IDR0 register */
#define SMMU_IDR0_ST_LEVEL_MASK                 0x18000000
#define SMMU_IDR0_ST_LEVEL_POS                  27
#define SMMU_IDR0_TERM_MODEL_MASK               0x04000000
#define SMMU_IDR0_TERM_MODEL_POS                26
#define SMMU_IDR0_STALL_MODEL_MASK              0x03000000
#define SMMU_IDR0_STALL_MODEL_POS               24
#define SMMU_IDR0_TTENDIAN_MASK                 0x00600000
#define SMMU_IDR0_TTENDIAN_POS                  21
#define SMMU_IDR0_VATOS_MASK                    0x00100000
#define SMMU_IDR0_VATOS_POS                     20
#define SMMU_IDR0_CD2L_MASK                     0x00080000
#define SMMU_IDR0_CD2L_POS                      19
#define SMMU_IDR0_VMID16_MASK                   0x00040000
#define SMMU_IDR0_VMID16_POS                    18
#define SMMU_IDR0_VMW_MASK                      0x00020000
#define SMMU_IDR0_VMW_POS                       17
#define SMMU_IDR0_PRI_MASK                      0x00010000
#define SMMU_IDR0_PRI_POS                       16
#define SMMU_IDR0_ATOS_MASK                     0x00008000
#define SMMU_IDR0_ATOS_POS                      15
#define SMMU_IDR0_SEV_MASK                      0x00004000
#define SMMU_IDR0_SEV_POS                       14
#define SMMU_IDR0_MSI_MASK                      0x00002000
#define SMMU_IDR0_MSI_POS                       13
#define SMMU_IDR0_ASID16_MASK                   0x00001000
#define SMMU_IDR0_ASID16_POS                    12
#define SMMU_IDR0_NS1ATS_MASK                   0x00000800
#define SMMU_IDR0_NS1ATS_POS                    11
#define SMMU_IDR0_ATS_MASK                      0x00000400
#define SMMU_IDR0_ATS_POS                       10
#define SMMU_IDR0_HYP_MASK                      0x00000200
#define SMMU_IDR0_HYP_POS                       9
#define SMMU_IDR0_DORMHINT_MASK                 0x00000100
#define SMMU_IDR0_DORMHINT_POS                  8
#define SMMU_IDR0_HTTU_MASK                     0x000000C0
#define SMMU_IDR0_HTTU_POS                      6
#define SMMU_IDR0_BTM_MASK                      0x00000020
#define SMMU_IDR0_BTM_POS                       5
#define SMMU_IDR0_COHACC_MASK                   0x00000010
#define SMMU_IDR0_COHACC_POS                    4
#define SMMU_IDR0_TTF_MASK                      0x0000000C
#define SMMU_IDR0_TTF_POS                       2
#define SMMU_IDR0_S1P_MASK                      0x00000002
#define SMMU_IDR0_S1P_POS                       1
#define SMMU_IDR0_S2P_MASK                      0x00000001
#define SMMU_IDR0_S2P_POS                       0

/* Bit fields of SMMU_IDR1 register */
#define SMMU_IDR1_TABLES_PRESET_MASK            0x40000000
#define SMMU_IDR1_TABLES_PRESET_POS             30
#define SMMU_IDR1_QUEUES_PRESET_MASK            0x20000000
#define SMMU_IDR1_QUEUES_PRESET_POS             29
#define SMMU_IDR1_REL_MASK                      0x10000000
#define SMMU_IDR1_REL_POS                       28
#define SMMU_IDR1_ATTR_TYPES_OVR_MASK           0x08000000
#define SMMU_IDR1_ATTR_TYPES_OVR_POS            27
#define SMMU_IDR1_ATTR_PERMS_OVR_MASK           0x04000000
#define SMMU_IDR1_ATTR_PERMS_OVR_POS            26
#define SMMU_IDR1_CMDQS_MASK                    0x03E00000
#define SMMU_IDR1_CMDQS_POS                     21
#define SMMU_IDR1_EVENTQS_MASK                  0x001F0000
#define SMMU_IDR1_EVENTQS_POS                   16
#define SMMU_IDR1_PRIQS_MASK                    0x0000F800
#define SMMU_IDR1_PRIQS_POS                     11
#define SMMU_IDR1_SSIDSIZE_MASK                 0x000007C0
#define SMMU_IDR1_SSIDSIZE_POS                  6
#define SMMU_IDR1_SIDSIZE_MASK                  0x0000003F
#define SMMU_IDR1_SIDSIZE_POS                   0

/* Bit fields of SMMU_IDR2 register */
#define SMMU_IDR2_BA_VATOS_MASK                 0x000003FF
#define SMMU_IDR2_BA_VATOS_POS                  0

/* Bit fields of SMMU_IDR3 register */
#define SMMU_IDR3_PPS_MASK                      0x00000020
#define SMMU_IDR3_PPS_POS                       5
#define SMMU_IDR3_XNX_MASK                      0x00000010
#define SMMU_IDR3_XNX_POS                       4
#define SMMU_IDR3_PBHA_MASK                     0x00000008
#define SMMU_IDR3_PBHA_POS                      3
#define SMMU_IDR3_HAD_MASK                      0x00000004
#define SMMU_IDR3_HAD_POS                       2

/* Bit fields of SMMU_IDR5 register */
#define SMMU_IDR5_STALL_MAX_MASK                0xFFFF0000
#define SMMU_IDR5_STALL_MAX_POS                 16
#define SMMU_IDR5_VAX_MASK                      0x00000C00
#define SMMU_IDR5_VAX_POS                       10
#define SMMU_IDR5_GRAN64K_MASK                  0x00000040
#define SMMU_IDR5_GRAN64K_POS                   6
#define SMMU_IDR5_GRAN16K_MASK                  0x00000020
#define SMMU_IDR5_GRAN16K_POS                   5
#define SMMU_IDR5_GRAN4K_MASK                   0x00000010
#define SMMU_IDR5_GRAN4K_POS                    4
#define SMMU_IDR5_OAS_MASK                      0x00000007
#define SMMU_IDR5_OAS_POS                       0

/* Bit fields of SMMU_IIDR register */
#define SMMU_IIDR_PRODUCTID_MASK                0xFFF00000
#define SMMU_IIDR_PRODUCTID_POS                 20
#define SMMU_IIDR_VARIANT_MASK                  0x000F0000
#define SMMU_IIDR_VARIANT_POS                   16
#define SMMU_IIDR_REVISION_MASK                 0x0000F000
#define SMMU_IIDR_REVISION_POS                  12
#define SMMU_IIDR_IMPLEMENTER_MASK              0x00000FFF
#define SMMU_IIDR_IMPLEMENTER_POS               0

/* Bit fields of SMMU_AIDR register */
#define SMMU_AIDR_ARCHMAJORREV_MASK             0x000000F0
#define SMMU_AIDR_ARCHMAJORREV_POS              4
#define SMMU_AIDR_ARCHMINORREV_MASK             0x0000000F
#define SMMU_AIDR_ARCHMINORREV_POS              0

/* Bit fields of SMMU_CR0 register */
#define SMMU_CR0_VMW_MASK                       0x000001C0
#define SMMU_CR0_VMW_POS                        6
#define SMMU_CR0_ATSCHK_MASK                    0x00000010
#define SMMU_CR0_ATSCHK_POS                     4
#define SMMU_CR0_CMDQEN_MASK                    0x00000008
#define SMMU_CR0_CMDQEN_POS                     3
#define SMMU_CR0_EVENTQEN_MASK                  0x00000004
#define SMMU_CR0_EVENTQEN_POS                   2
#define SMMU_CR0_PRIQEN_MASK                    0x00000002
#define SMMU_CR0_PRIQEN_POS                     1
#define SMMU_CR0_SMMUEN_MASK                    0x00000001
#define SMMU_CR0_SMMUEN_POS                     0

/* Bit fields of SMMU_CR0ACK register */
#define SMMU_CR0ACK_VMW_MASK                    0x000001C0
#define SMMU_CR0ACK_VMW_POS                     6
#define SMMU_CR0ACK_ATSCHK_MASK                 0x00000010
#define SMMU_CR0ACK_ATSCHK_POS                  4
#define SMMU_CR0ACK_CMDQEN_MASK                 0x00000008
#define SMMU_CR0ACK_CMDQEN_POS                  3
#define SMMU_CR0ACK_EVENTQEN_MASK               0x00000004
#define SMMU_CR0ACK_EVENTQEN_POS                2
#define SMMU_CR0ACK_PRIQEN_MASK                 0x00000002
#define SMMU_CR0ACK_PRIQEN_POS                  1
#define SMMU_CR0ACK_SMMUEN_MASK                 0x00000001
#define SMMU_CR0ACK_SMMUEN_POS                  0

/* Bit fields of SMMU_CR1 register */
#define SMMU_CR1_TABLE_SH_MASK                  0x00000C00
#define SMMU_CR1_TABLE_SH_POS                   10
#define SMMU_CR1_TABLE_OC_MASK                  0x00000300
#define SMMU_CR1_TABLE_OC_POS                   8
#define SMMU_CR1_TABLE_IC_MASK                  0x000000C0
#define SMMU_CR1_TABLE_IC_POS                   6
#define SMMU_CR1_QUEUE_SH_MASK                  0x00000030
#define SMMU_CR1_QUEUE_SH_POS                   4
#define SMMU_CR1_QUEUE_OC_MASK                  0x0000000C
#define SMMU_CR1_QUEUE_OC_POS                   2
#define SMMU_CR1_QUEUE_IC_MASK                  0x00000003
#define SMMU_CR1_QUEUE_IC_POS                   0

/* Bit fields of SMMU_CR2 register */
#define SMMU_CR2_PTM_MASK                       0x00000004
#define SMMU_CR2_PTM_POS                        2
#define SMMU_CR2_RECINVSID_MASK                 0x00000002
#define SMMU_CR2_RECINVSID_POS                  1
#define SMMU_CR2_E2H_MASK                       0x00000001
#define SMMU_CR2_E2H_POS                        0

/* Bit fields of SMMU_GBPA register */
#define SMMU_GBPA_UPDATE_MASK                   0x80000000
#define SMMU_GBPA_UPDATE_POS                    31
#define SMMU_GBPA_ABORT_MASK                    0x00100000
#define SMMU_GBPA_ABORT_POS                     20
#define SMMU_GBPA_INSTCFG_MASK                  0x000C0000
#define SMMU_GBPA_INSTCFG_POS                   18
#define SMMU_GBPA_PRIVCFG_MASK                  0x00030000
#define SMMU_GBPA_PRIVCFG_POS                   16
#define SMMU_GBPA_SHCFG_MASK                    0xFFFFFFFE
#define SMMU_GBPA_SHCFG_POS                     1
#define SMMU_GBPA_CAPTURE_MASK                  0x00000001
#define SMMU_GBPA_CAPTURE_POS                   0

/* Bit fields of SMMU_IRQ_CTRL register */
#define SMMU_IRQ_CTRL_EVENTQ_IRQEN_MASK         0x00000004
#define SMMU_IRQ_CTRL_EVENTQ_IRQEN_POS          2
#define SMMU_IRQ_CTRL_PRIQ_IRQEN_MASK           0x00000002
#define SMMU_IRQ_CTRL_PRIQ_IRQEN_POS            1
#define SMMU_IRQ_CTRL_GERROR_IRQEN_MASK         0x00000001
#define SMMU_IRQ_CTRL_GERROR_IRQEN_POS          0

/* Bit fields of SMMU_IRQ_CTRLACK register */
#define SMMU_IRQ_CTRLACK_EVENTQ_IRQEN_MASK      0x00000004
#define SMMU_IRQ_CTRLACK_EVENTQ_IRQEN_POS       2
#define SMMU_IRQ_CTRLACK_PRIQ_IRQEN_MASK        0x00000002
#define SMMU_IRQ_CTRLACK_PRIQ_IRQEN_POS         1
#define SMMU_IRQ_CTRLACK_GERROR_IRQEN_MASK      0x00000001
#define SMMU_IRQ_CTRLACK_GERROR_IRQEN_POS       0

/* Bit fields of SMMU_GERROR register */
#define SMMU_GERROR_MSI_GERROR_ABT_ERR_MASK     0x00000080
#define SMMU_GERROR_MSI_GERROR_ABT_ERR_POS      7
#define SMMU_GERROR_MSI_PRIQ_ABT_ERR_MASK       0x00000040
#define SMMU_GERROR_MSI_PRIQ_ABT_ERR_POS        6
#define SMMU_GERROR_MSI_EVENTQ_ABT_ERR_MASK     0x00000020
#define SMMU_GERROR_MSI_EVENTQ_ABT_ERR_POS      5
#define SMMU_GERROR_MSI_CMDQ_ABT_ERR_MASK       0x00000010
#define SMMU_GERROR_MSI_CMDQ_ABT_ERR_POS        4
#define SMMU_GERROR_PRIQ_ABT_ERR_MASK           0x00000008
#define SMMU_GERROR_PRIQ_ABT_ERR_POS            3
#define SMMU_GERROR_EVENTQ_ABT_ERR_MASK         0x00000004
#define SMMU_GERROR_EVENTQ_ABT_ERR_POS          2
#define SMMU_GERROR_CMDQ_ERR_MASK               0x00000001
#define SMMU_GERROR_CMDQ_ERR_POS                0

/* Bit fields of SMMU_GERRORN register */
#define SMMU_GERRORN_MSI_GERROR_ABT_ERR_MASK    0x00000080
#define SMMU_GERRORN_MSI_GERROR_ABT_ERR_POS     7
#define SMMU_GERRORN_MSI_PRIQ_ABT_ERR_MASK      0x00000040
#define SMMU_GERRORN_MSI_PRIQ_ABT_ERR_POS       6
#define SMMU_GERRORN_MSI_EVENTQ_ABT_ERR_MASK    0x00000020
#define SMMU_GERRORN_MSI_EVENTQ_ABT_ERR_POS     5
#define SMMU_GERRORN_MSI_CMDQ_ABT_ERR_MASK      0x00000010
#define SMMU_GERRORN_MSI_CMDQ_ABT_ERR_POS       4
#define SMMU_GERRORN_PRIQ_ABT_ERR_MASK          0x00000008
#define SMMU_GERRORN_PRIQ_ABT_ERR_POS           3
#define SMMU_GERRORN_EVENTQ_ABT_ERR_MASK        0x00000004
#define SMMU_GERRORN_EVENTQ_ABT_ERR_POS         2
#define SMMU_GERRORN_CMDQ_ERR_MASK              0x00000001
#define SMMU_GERRORN_CMDQ_ERR_POS               0

/* Bit fields of SMMU_GERROR_IRQ_CFG0_LO register */
#define SMMU_GERROR_IRQ_CFG0_LO_ADDR_MASK       0xFFFFFFFC
#define SMMU_GERROR_IRQ_CFG0_LO_ADDR_POS        2

/* Bit fields of SMMU_GERROR_IRQ_CFG0_HI register */
#define SMMU_GERROR_IRQ_CFG0_HI_ADDR_MASK       0x0000FFFF
#define SMMU_GERROR_IRQ_CFG0_HI_ADDR_POS        0

/* Bit fields of SMMU_GERROR_IRQ_CFG1 register */
#define SMMU_GERROR_IRQ_CFG1_DATA_MASK          0xFFFFFFFF
#define SMMU_GERROR_IRQ_CFG1_DATA_POS           0

/* Bit fields of SMMU_GERROR_IRQ_CFG2 register */
#define SMMU_GERROR_IRQ_CFG2_SH_MASK            0x00000030
#define SMMU_GERROR_IRQ_CFG2_SH_POS             4
#define SMMU_GERROR_IRQ_CFG2_MEMATTR_MASK       0x0000000F
#define SMMU_GERROR_IRQ_CFG2_MEMATTR_POS        0

/* Bit fields of SMMU_STRTAB_BASE_LO register */
#define SMMU_STRTAB_BASE_LO_ADDR_MASK           0xFFFFFFC0
#define SMMU_STRTAB_BASE_LO_ADDR_POS            6

/* Bit fields of SMMU_STRTAB_BASE_HI register */
#define SMMU_STRTAB_BASE_HI_RA_MASK             0x40000000
#define SMMU_STRTAB_BASE_HI_RA_POS              30
#define SMMU_STRTAB_BASE_HI_ADDR_MASK           0x0000FFFF
#define SMMU_STRTAB_BASE_HI_ADDR_POS            0

/* Bit fields of SMMU_STRTAB_BASE_CFG register */
#define SMMU_STRTAB_BASE_CFG_FMT_MASK           0x00030000
#define SMMU_STRTAB_BASE_CFG_FMT_POS            16
#define SMMU_STRTAB_BASE_CFG_SPLIT_MASK         0x000007C0
#define SMMU_STRTAB_BASE_CFG_SPLIT_POS          6
#define SMMU_STRTAB_BASE_CFG_LOG2SIZE_MASK      0x0000003F
#define SMMU_STRTAB_BASE_CFG_LOG2SIZE_POS       0

/* Bit fields of SMMU_CMDQ_BASE_LO register */
#define SMMU_CMDQ_BASE_LO_ADDR_MASK             0xFFFFFFE0
#define SMMU_CMDQ_BASE_LO_ADDR_POS              5
#define SMMU_CMDQ_BASE_LO_LOG2SIZE_MASK         0x0000001F
#define SMMU_CMDQ_BASE_LO_LOG2SIZE_POS          0

/* Bit fields of SMMU_CMDQ_BASE_HI register */
#define SMMU_CMDQ_BASE_HI_RA_MASK               0x40000000
#define SMMU_CMDQ_BASE_HI_RA_POS                30
#define SMMU_CMDQ_BASE_HI_ADDR_MASK             0x0000FFFF
#define SMMU_CMDQ_BASE_HI_ADDR_POS              0

/* Bit fields of SMMU_CMDQ_PROD register */
#define SMMU_CMDQ_PROD_WR_MASK                  0x000FFFFF
#define SMMU_CMDQ_PROD_WR_POS                   0

/* Bit fields of SMMU_CMDQ_CONS register */
#define SMMU_CMDQ_CONS_ERR_MASK                 0x7F000000
#define SMMU_CMDQ_CONS_ERR_POS                  24
#define SMMU_CMDQ_CONS_RD_MASK                  0x000FFFFF
#define SMMU_CMDQ_CONS_RD_POS                   0

/* Bit fields of SMMU_EVENTQ_BASE_LO register */
#define SMMU_EVENTQ_BASE_LO_ADDR_MASK           0xFFFFFFE0
#define SMMU_EVENTQ_BASE_LO_ADDR_POS            5
#define SMMU_EVENTQ_BASE_LO_LOG2SIZE_MASK       0x0000001F
#define SMMU_EVENTQ_BASE_LO_LOG2SIZE_POS        0

/* Bit fields of SMMU_EVENTQ_BASE_HI register */
#define SMMU_EVENTQ_BASE_HI_WA_MASK             0x40000000
#define SMMU_EVENTQ_BASE_HI_WA_POS              30
#define SMMU_EVENTQ_BASE_HI_ADDR_MASK           0x0000FFFF
#define SMMU_EVENTQ_BASE_HI_ADDR_POS            0

/* Bit fields of SMMU_EVENTQ_IRQ_CFG0_LO register */
#define SMMU_EVENTQ_IRQ_CFG0_LO_ADDR_MASK       0xFFFFFFFC
#define SMMU_EVENTQ_IRQ_CFG0_LO_ADDR_POS        2

/* Bit fields of SMMU_EVENTQ_IRQ_CFG0_HI register */
#define SMMU_EVENTQ_IRQ_CFG0_HI_ADDR_MASK       0x0000FFFF
#define SMMU_EVENTQ_IRQ_CFG0_HI_ADDR_POS        0

/* Bit fields of SMMU_EVENTQ_IRQ_CFG1 register */
#define SMMU_EVENTQ_IRQ_CFG1_DATA_MASK          0xFFFFFFFF
#define SMMU_EVENTQ_IRQ_CFG1_DATA_POS           0

/* Bit fields of SMMU_EVENTQ_IRQ_CFG2 register */
#define SMMU_EVENTQ_IRQ_CFG2_SH_MASK            0x00000030
#define SMMU_EVENTQ_IRQ_CFG2_SH_POS             4
#define SMMU_EVENTQ_IRQ_CFG2_MEMATTR_MASK       0x0000000F
#define SMMU_EVENTQ_IRQ_CFG2_MEMATTR_POS        0

/* Bit fields of SMMU_PRIQ_BASE_LO register */
#define SMMU_PRIQ_BASE_LO_ADDR_MASK             0xFFFFFFE0
#define SMMU_PRIQ_BASE_LO_ADDR_POS              5
#define SMMU_PRIQ_BASE_LO_LOG2SIZE_MASK         0x0000001F
#define SMMU_PRIQ_BASE_LO_LOG2SIZE_POS          0

/* Bit fields of SMMU_PRIQ_BASE_HI register */
#define SMMU_PRIQ_BASE_HI_WA_MASK               0x40000000
#define SMMU_PRIQ_BASE_HI_WA_POS                30
#define SMMU_PRIQ_BASE_HI_ADDR_MASK             0x0000FFFF
#define SMMU_PRIQ_BASE_HI_ADDR_POS              0

/* Bit fields of SMMU_PRIQ_IRQ_CFG0_LO register */
#define SMMU_PRIQ_IRQ_CFG0_LO_ADDR_MASK         0xFFFFFFFC
#define SMMU_PRIQ_IRQ_CFG0_LO_ADDR_POS          2

/* Bit fields of SMMU_PRIQ_IRQ_CFG0_HI register */
#define SMMU_PRIQ_IRQ_CFG0_HI_ADDR_MASK         0x0000FFFF
#define SMMU_PRIQ_IRQ_CFG0_HI_ADDR_POS          0

/* Bit fields of SMMU_PRIQ_IRQ_CFG1 register */
#define SMMU_PRIQ_IRQ_CFG1_DATA_MASK            0xFFFFFFFF
#define SMMU_PRIQ_IRQ_CFG1_DATA_POS             0

/* Bit fields of SMMU_PRIQ_IRQ_CFG2 register */
#define SMMU_PRIQ_IRQ_CFG2_LO_MASK              0x80000000
#define SMMU_PRIQ_IRQ_CFG2_LO_POS               31
#define SMMU_PRIQ_IRQ_CFG2_SH_MASK              0x00000030
#define SMMU_PRIQ_IRQ_CFG2_SH_POS               4
#define SMMU_PRIQ_IRQ_CFG2_MEMATTR_MASK         0x0000000F
#define SMMU_PRIQ_IRQ_CFG2_MEMATTR_POS          0

/* Bit fields of SMMU_PIDR4 register */
#define SMMU_PIDR4_SIZE_MASK                    0x000000F0
#define SMMU_PIDR4_SIZE_POS                     4
#define SMMU_PIDR4_DES_2_MASK                   0x0000000F
#define SMMU_PIDR4_DES_2_POS                    0

/* Bit fields of SMMU_PIDR5 register */

/* Bit fields of SMMU_PIDR6 register */

/* Bit fields of SMMU_PIDR7 register */

/* Bit fields of SMMU_PIDR0 register */
#define SMMU_PIDR0_PART_0_MASK                     0x000000FF
#define SMMU_PIDR0_PART_0_POS                      0

/* Bit fields of SMMU_PIDR1 register */
#define SMMU_PIDR1_DES_0_MASK                      0x000000F0
#define SMMU_PIDR1_DES_0_POS                       4
#define SMMU_PIDR1_PART_1_MASK                     0x0000000F
#define SMMU_PIDR1_PART_1_POS                      0

/* Bit fields of SMMU_PIDR2 register */
#define SMMU_PIDR2_REVISION_MASK                   0x000000F0
#define SMMU_PIDR2_REVISION_POS                    4
#define SMMU_PIDR2_JEDEC_MASK                      0x00000008
#define SMMU_PIDR2_JEDEC_POS                       3
#define SMMU_PIDR2_DES_1_MASK                      0x00000007
#define SMMU_PIDR2_DES_1_POS                       0

/* Bit fields of SMMU_PIDR3 register */
#define SMMU_PIDR3_REVAND_MASK                     0x000000F0
#define SMMU_PIDR3_REVAND_POS                      4
#define SMMU_PIDR3_CMOD_MASK                       0x0000000F
#define SMMU_PIDR3_CMOD_POS                        0

/* Bit fields of SMMU_CIDR0 register */
#define SMMU_CIDR0_PREAMBLE_MASK                   0x000000FF
#define SMMU_CIDR0_PREAMBLE_POS                    0

/* Bit fields of SMMU_CIDR1 register */
#define SMMU_CIDR1_CLASS_MASK                      0x000000F0
#define SMMU_CIDR1_CLASS_POS                       4
#define SMMU_CIDR1_PREAMBLE_MASK                   0x0000000F
#define SMMU_CIDR1_PREAMBLE_POS                    0

/* Bit fields of SMMU_CIDR2 register */
#define SMMU_CIDR2_PREAMBLE_MASK                   0x000000FF
#define SMMU_CIDR2_PREAMBLE_POS                    0

/* Bit fields of SMMU_CIDR3 register */
#define SMMU_CIDR3_PREAMBLE_MASK                   0x000000FF
#define SMMU_CIDR3_PREAMBLE_POS                    0

/* Bit fields of SMMU_PMCG_EVTYPER0 register */
#define SMMU_PMCG_EVTYPER0_OVFCAP_MASK             0x80000000
#define SMMU_PMCG_EVTYPER0_OVFCAP_POS              31
#define SMMU_PMCG_EVTYPER0_FILTER_SEC_SID_MASK     0x40000000
#define SMMU_PMCG_EVTYPER0_FILTER_SEC_SID_POS      30
#define SMMU_PMCG_EVTYPER0_FILTER_SID_SPAN_MASK    0x20000000
#define SMMU_PMCG_EVTYPER0_FILTER_SID_SPAN_POS     29
#define SMMU_PMCG_EVTYPER0_EVNT_MASK               0x000000FF
#define SMMU_PMCG_EVTYPER0_EVNT_POS                0

/* Bit fields of SMMU_PMCG_EVTYPER1 register */
#define SMMU_PMCG_EVTYPER1_OVFCAP_MASK             0x80000000
#define SMMU_PMCG_EVTYPER1_OVFCAP_POS              31
#define SMMU_PMCG_EVTYPER1_EVNT_MASK               0x000000FF
#define SMMU_PMCG_EVTYPER1_EVNT_POS                0

/* Bit fields of SMMU_PMCG_EVTYPER2 register */
#define SMMU_PMCG_EVTYPER2_OVFCAP_MASK             0x80000000
#define SMMU_PMCG_EVTYPER2_OVFCAP_POS              31
#define SMMU_PMCG_EVTYPER2_EVNT_MASK               0x000000FF
#define SMMU_PMCG_EVTYPER2_EVNT_POS                0

/* Bit fields of SMMU_PMCG_EVTYPER3 register */
#define SMMU_PMCG_EVTYPER3_OVFCAP_MASK             0x80000000
#define SMMU_PMCG_EVTYPER3_OVFCAP_POS              31
#define SMMU_PMCG_EVTYPER3_EVNT_MASK               0x000000FF
#define SMMU_PMCG_EVTYPER3_EVNT_POS                0

/* Bit fields of SMMU_PMCG_SMR0 register */
#define SMMU_PMCG_SMR0_STREAMID_MASK               0x00FFFFFF
#define SMMU_PMCG_SMR0_STREAMID_POS                0

/* Bit fields of SMMU_PMCG_CNTENSET0 register */
#define SMMU_PMCG_CNTENSET0_CNTEN_MASK             0x0000000F
#define SMMU_PMCG_CNTENSET0_CNTEN_POS              0

/* Bit fields of SMMU_PMCG_CNTENCLR0 register */
#define SMMU_PMCG_CNTENCLR0_CNTEN_MASK             0x0000000F
#define SMMU_PMCG_CNTENCLR0_CNTEN_POS              0

/* Bit fields of SMMU_PMCG_INTENSET0 register */
#define SMMU_PMCG_INTENSET0_INTEN_MASK             0x0000000F
#define SMMU_PMCG_INTENSET0_INTEN_POS              0

/* Bit fields of SMMU_PMCG_INTENCLR0 register */
#define SMMU_PMCG_INTENCLR0_INTEN_MASK             0x0000000F
#define SMMU_PMCG_INTENCLR0_INTEN_POS              0

/* Bit fields of SMMU_PMCG_SCR register */
#define SMMU_PMCG_SCR_READS_AS_ONE_MASK            0x80000000
#define SMMU_PMCG_SCR_READS_AS_ONE_POS             31
#define SMMU_PMCG_SCR_NSMSI_MASK                   0x00000004
#define SMMU_PMCG_SCR_NSMSI_POS                    2
#define SMMU_PMCG_SCR_NSRA_MASK                    0x00000002
#define SMMU_PMCG_SCR_NSRA_POS                     1
#define SMMU_PMCG_SCR_SO_MASK                      0x00000001
#define SMMU_PMCG_SCR_SO_POS                       0

/* Bit fields of SMMU_PMCG_CFGR register */
#define SMMU_PMCG_CFGR_SID_FILTER_TYPE_MASK        0x00800000
#define SMMU_PMCG_CFGR_SID_FILTER_TYPE_POS         23
#define SMMU_PMCG_CFGR_CAPTURE_MASK                0x00400000
#define SMMU_PMCG_CFGR_CAPTURE_POS                 22
#define SMMU_PMCG_CFGR_MSI_MASK                    0x00200000
#define SMMU_PMCG_CFGR_MSI_POS                     21
#define SMMU_PMCG_CFGR_RELOC_CTRS_MASK             0x00100000
#define SMMU_PMCG_CFGR_RELOC_CTRS_POS              20
#define SMMU_PMCG_CFGR_SIZE_MASK                   0x00003F00
#define SMMU_PMCG_CFGR_SIZE_POS                    8
#define SMMU_PMCG_CFGR_NCTR_MASK                   0x0000003F
#define SMMU_PMCG_CFGR_NCTR_POS                    0

/* Bit fields of SMMU_PMCG_CR register */
#define SMMU_PMCG_CR_E_MASK                        0x00000001
#define SMMU_PMCG_CR_E_POS                         0

/* Bit fields of SMMU_PMCG_CEID0_LO register */
#define SMMU_PMCG_CEID0_LO_N_MASK                  0xFFFFFFFF
#define SMMU_PMCG_CEID0_LO_N_POS                   0

/* Bit fields of SMMU_PMCG_CEID0_HI register */
#define SMMU_PMCG_CEID0_HI_N_MASK                  0xFFFFFFFF
#define SMMU_PMCG_CEID0_HI_N_POS                   0

/* Bit fields of SMMU_PMCG_CEID1_LO register */
#define SMMU_PMCG_CEID1_LO_N_MASK                  0xFFFFFFFF
#define SMMU_PMCG_CEID1_LO_N_POS                   0

/* Bit fields of SMMU_PMCG_CEID1_HI register */
#define SMMU_PMCG_CEID1_HI_N_MASK                  0xFFFFFFFF
#define SMMU_PMCG_CEID1_HI_N_POS                   0

/* Bit fields of SMMU_PMCG_IRQ_CTRL register */
#define SMMU_PMCG_IRQ_CTRL_IRQEN_MASK              0x00000001
#define SMMU_PMCG_IRQ_CTRL_IRQEN_POS               0

/* Bit fields of SMMU_PMCG_IRQ_CTRLACK register */
#define SMMU_PMCG_IRQ_CTRLACK_IRQEN_MASK           0x00000001
#define SMMU_PMCG_IRQ_CTRLACK_IRQEN_POS            0

/* Bit fields of SMMU_PMCG_AIDR register */
#define SMMU_PMCG_AIDR_ARCHMAJORREV_MASK           0x000000F0
#define SMMU_PMCG_AIDR_ARCHMAJORREV_POS            4
#define SMMU_PMCG_AIDR_ARCHMINORREV_MASK           0x0000000F
#define SMMU_PMCG_AIDR_ARCHMINORREV_POS            0

/* Bit fields of SMMU_PMCG_PMAUTHSTATUS register */
#define SMMU_PMCG_PMAUTHSTATUS_SNI_MASK            0x00000080
#define SMMU_PMCG_PMAUTHSTATUS_SNI_POS             7
#define SMMU_PMCG_PMAUTHSTATUS_SNE_MASK            0x00000040
#define SMMU_PMCG_PMAUTHSTATUS_SNE_POS             6
#define SMMU_PMCG_PMAUTHSTATUS_SI_MASK             0x00000020
#define SMMU_PMCG_PMAUTHSTATUS_SI_POS              5
#define SMMU_PMCG_PMAUTHSTATUS_SE_MASK             0x00000010
#define SMMU_PMCG_PMAUTHSTATUS_SE_POS              4
#define SMMU_PMCG_PMAUTHSTATUS_NSNI_MASK           0x00000008
#define SMMU_PMCG_PMAUTHSTATUS_NSNI_POS            3
#define SMMU_PMCG_PMAUTHSTATUS_NSNE_MASK           0x00000004
#define SMMU_PMCG_PMAUTHSTATUS_NSNE_POS            2
#define SMMU_PMCG_PMAUTHSTATUS_NSI_MASK            0x00000002
#define SMMU_PMCG_PMAUTHSTATUS_NSI_POS             1
#define SMMU_PMCG_PMAUTHSTATUS_NSE_MASK            0x00000001
#define SMMU_PMCG_PMAUTHSTATUS_NSE_POS             0

/* Bit fields of SMMU_PMCG_PMDEVARCH register */
#define SMMU_PMCG_PMDEVARCH_ARCHITECT_MASK         0xFFE00000
#define SMMU_PMCG_PMDEVARCH_ARCHITECT_POS          21
#define SMMU_PMCG_PMDEVARCH_PRESENT_MASK           0x00100000
#define SMMU_PMCG_PMDEVARCH_PRESENT_POS            20
#define SMMU_PMCG_PMDEVARCH_REVISION_MASK          0x000F0000
#define SMMU_PMCG_PMDEVARCH_REVISION_POS           16
#define SMMU_PMCG_PMDEVARCH_ARCHID_MASK            0x0000FFFF
#define SMMU_PMCG_PMDEVARCH_ARCHID_POS             0

/* Bit fields of SMMU_PMCG_PMDEVTYPE register */
#define SMMU_PMCG_PMDEVTYPE_SUB_TYPE_MASK          0x000000F0
#define SMMU_PMCG_PMDEVTYPE_SUB_TYPE_POS           4
#define SMMU_PMCG_PMDEVTYPE_CLS_MASK               0x0000000F
#define SMMU_PMCG_PMDEVTYPE_CLS_POS                0

/* Bit fields of SMMU_PMCG_PIDR4 register */
#define SMMU_PMCG_PIDR4_SIZE_MASK                  0x000000F0
#define SMMU_PMCG_PIDR4_SIZE_POS                   4
#define SMMU_PMCG_PIDR4_DES_2_MASK                 0x0000000F
#define SMMU_PMCG_PIDR4_DES_2_POS                  0

/* Bit fields of SMMU_PMCG_PIDR5 register */

/* Bit fields of SMMU_PMCG_PIDR6 register */

/* Bit fields of SMMU_PMCG_PIDR7 register */

/* Bit fields of SMMU_PMCG_PIDR0 register */
#define SMMU_PMCG_PIDR0_PART_0_MASK               0x000000FF
#define SMMU_PMCG_PIDR0_PART_0_POS                0

/* Bit fields of SMMU_PMCG_PIDR1 register */
#define SMMU_PMCG_PIDR1_DES_0_MASK                0x000000F0
#define SMMU_PMCG_PIDR1_DES_0_POS                 4
#define SMMU_PMCG_PIDR1_PART_1_MASK               0x0000000F
#define SMMU_PMCG_PIDR1_PART_1_POS                0

/* Bit fields of SMMU_PMCG_PIDR2 register */
#define SMMU_PMCG_PIDR2_REVISION_MASK             0x000000F0
#define SMMU_PMCG_PIDR2_REVISION_POS              4
#define SMMU_PMCG_PIDR2_JEDEC_MASK                0x00000008
#define SMMU_PMCG_PIDR2_JEDEC_POS                 3
#define SMMU_PMCG_PIDR2_DES_1_MASK                0x00000007
#define SMMU_PMCG_PIDR2_DES_1_POS                 0

/* Bit fields of SMMU_PMCG_PIDR3 register */
#define SMMU_PMCG_PIDR3_REVAND_MASK               0x000000F0
#define SMMU_PMCG_PIDR3_REVAND_POS                4
#define SMMU_PMCG_PIDR3_CMOD_MASK                 0x0000000F
#define SMMU_PMCG_PIDR3_CMOD_POS                  0

/* Bit fields of SMMU_PMCG_CIDR0 register */
#define SMMU_PMCG_CIDR0_PREAMBLE_MASK             0x000000FF
#define SMMU_PMCG_CIDR0_PREAMBLE_POS              0

/* Bit fields of SMMU_PMCG_CIDR1 register */
#define SMMU_PMCG_CIDR1_CLASS_MASK                0x000000F0
#define SMMU_PMCG_CIDR1_CLASS_POS                 4
#define SMMU_PMCG_CIDR1_PREAMBLE_MASK             0x0000000F
#define SMMU_PMCG_CIDR1_PREAMBLE_POS              0

/* Bit fields of SMMU_PMCG_CIDR2 register */
#define SMMU_PMCG_CIDR2_PREAMBLE_MASK             0x000000FF
#define SMMU_PMCG_CIDR2_PREAMBLE_POS              0

/* Bit fields of SMMU_PMCG_CIDR3 register */
#define SMMU_PMCG_CIDR3_PREAMBLE_MASK             0x000000FF
#define SMMU_PMCG_CIDR3_PREAMBLE_POS              0

/* Bit fields of SMMU_S_IDR0 register */
#define SMMU_S_IDR0_STALL_MODEL_MASK              0x03000000
#define SMMU_S_IDR0_STALL_MODEL_POS               24
#define SMMU_S_IDR0_MSI_MASK                      0x00002000
#define SMMU_S_IDR0_MSI_POS                       13

/* Bit fields of SMMU_S_IDR1 register */
#define SMMU_S_IDR1_SECURE_IMPL_MASK              0x80000000
#define SMMU_S_IDR1_SECURE_IMPL_POS               31
#define SMMU_S_IDR1_S_SIDSIZE_MASK                0x0000003F
#define SMMU_S_IDR1_S_SIDSIZE_POS                 0

/* Bit fields of SMMU_S_IDR3 register */
#define SMMU_S_IDR3_SAMS_MASK                     0x00000040
#define SMMU_S_IDR3_SAMS_POS                      6

/* Bit fields of SMMU_S_CR0 register */
#define SMMU_S_CR0_NSSTALLD_MASK                  0x00000200
#define SMMU_S_CR0_NSSTALLD_POS                   9
#define SMMU_S_CR0_SIF_MASK                       0x00000020
#define SMMU_S_CR0_SIF_POS                        5
#define SMMU_S_CR0_CMDQEN_MASK                    0x00000008
#define SMMU_S_CR0_CMDQEN_POS                     3
#define SMMU_S_CR0_EVENTQEN_MASK                  0x00000004
#define SMMU_S_CR0_EVENTQEN_POS                   2
#define SMMU_S_CR0_SMMUEN_MASK                    0x00000001
#define SMMU_S_CR0_SMMUEN_POS                     0

/* Bit fields of SMMU_S_CR0ACK register */
#define SMMU_S_CR0ACK_NSSTALLD_MASK               0x00000200
#define SMMU_S_CR0ACK_NSSTALLD_POS                9
#define SMMU_S_CR0ACK_SIF_MASK                    0x00000020
#define SMMU_S_CR0ACK_SIF_POS                     5
#define SMMU_S_CR0ACK_CMDQEN_MASK                 0x00000008
#define SMMU_S_CR0ACK_CMDQEN_POS                  3
#define SMMU_S_CR0ACK_EVENTQEN_MASK               0x00000004
#define SMMU_S_CR0ACK_EVENTQEN_POS                2
#define SMMU_S_CR0ACK_SMMUEN_MASK                 0x00000001
#define SMMU_S_CR0ACK_SMMUEN_POS                  0

/* Bit fields of SMMU_S_CR1 register */
#define SMMU_S_CR1_TABLE_SH_MASK                  0x00000C00
#define SMMU_S_CR1_TABLE_SH_POS                   10
#define SMMU_S_CR1_TABLE_OC_MASK                  0x00000300
#define SMMU_S_CR1_TABLE_OC_POS                   8
#define SMMU_S_CR1_TABLE_IC_MASK                  0x000000C0
#define SMMU_S_CR1_TABLE_IC_POS                   6
#define SMMU_S_CR1_QUEUE_SH_MASK                  0x00000030
#define SMMU_S_CR1_QUEUE_SH_POS                   4
#define SMMU_S_CR1_QUEUE_OC_MASK                  0x0000000C
#define SMMU_S_CR1_QUEUE_OC_POS                   2
#define SMMU_S_CR1_QUEUE_IC_MASK                  0x00000003
#define SMMU_S_CR1_QUEUE_IC_POS                   0

/* Bit fields of SMMU_S_CR2 register */
#define SMMU_S_CR2_PTM_MASK                       0x00000004
#define SMMU_S_CR2_PTM_POS                        2
#define SMMU_S_CR2_RECINVSID_MASK                 0x00000002
#define SMMU_S_CR2_RECINVSID_POS                  1

/* Bit fields of SMMU_S_INIT register */
#define SMMU_S_INIT_INV_ALL_MASK                  0x00000001
#define SMMU_S_INIT_INV_ALL_POS                   0

/* Bit fields of SMMU_S_GBPA register */
#define SMMU_S_GBPA_UPDATE_MASK                   0x80000000
#define SMMU_S_GBPA_UPDATE_POS                    31
#define SMMU_S_GBPA_ABORT_MASK                    0x00100000
#define SMMU_S_GBPA_ABORT_POS                     20
#define SMMU_S_GBPA_INSTCFG_MASK                  0x000C0000
#define SMMU_S_GBPA_INSTCFG_POS                   18
#define SMMU_S_GBPA_PRIVCFG_MASK                  0x00030000
#define SMMU_S_GBPA_PRIVCFG_POS                   16
#define SMMU_S_GBPA_NSCFG_MASK                    0x0000C000
#define SMMU_S_GBPA_NSCFG_POS                     14
#define SMMU_S_GBPA_SHCFG_MASK                    0x00003000
#define SMMU_S_GBPA_SHCFG_POS                     12
#define SMMU_S_GBPA_ALLOCCFG_MASK                 0x00000F00
#define SMMU_S_GBPA_ALLOCCFG_POS                  8
#define SMMU_S_GBPA_MTCFG_MASK                    0x00000010
#define SMMU_S_GBPA_MTCFG_POS                     4
#define SMMU_S_GBPA_MEMATTR_MASK                  0x0000000F
#define SMMU_S_GBPA_MEMATTR_POS                   0

/* Bit fields of SMMU_S_IRQ_CTRL register */
#define SMMU_S_IRQ_CTRL_EVENTQ_IRQEN_MASK         0x00000004
#define SMMU_S_IRQ_CTRL_EVENTQ_IRQEN_POS          2
#define SMMU_S_IRQ_CTRL_GERROR_IRQEN_MASK         0x00000001
#define SMMU_S_IRQ_CTRL_GERROR_IRQEN_POS          0

/* Bit fields of SMMU_S_IRQ_CTRLACK register */
#define SMMU_S_IRQ_CTRLACK_EVENTQ_IRQEN_MASK      0x00000004
#define SMMU_S_IRQ_CTRLACK_EVENTQ_IRQEN_POS       2
#define SMMU_S_IRQ_CTRLACK_GERROR_IRQEN_MASK      0x00000001
#define SMMU_S_IRQ_CTRLACK_GERROR_IRQEN_POS       0

/* Bit fields of SMMU_S_GERROR register */
#define SMMU_S_GERROR_MSI_GERROR_ABT_ERR_MASK     0x00000080
#define SMMU_S_GERROR_MSI_GERROR_ABT_ERR_POS      7
#define SMMU_S_GERROR_MSI_EVENTQ_ABT_ERR_MASK     0x00000020
#define SMMU_S_GERROR_MSI_EVENTQ_ABT_ERR_POS      5
#define SMMU_S_GERROR_MSI_CMDQ_ABT_ERR_MASK       0x00000010
#define SMMU_S_GERROR_MSI_CMDQ_ABT_ERR_POS        4
#define SMMU_S_GERROR_EVENTQ_ABT_ERR_MASK         0x00000004
#define SMMU_S_GERROR_EVENTQ_ABT_ERR_POS          2
#define SMMU_S_GERROR_CMDQ_ERR_MASK               0x00000001
#define SMMU_S_GERROR_CMDQ_ERR_POS                0

/* Bit fields of SMMU_S_GERRORN register */
#define SMMU_S_GERRORN_MSI_GERROR_ABT_ERR_MASK    0x00000080
#define SMMU_S_GERRORN_MSI_GERROR_ABT_ERR_POS     7
#define SMMU_S_GERRORN_MSI_EVENTQ_ABT_ERR_MASK    0x00000020
#define SMMU_S_GERRORN_MSI_EVENTQ_ABT_ERR_POS     5
#define SMMU_S_GERRORN_MSI_CMDQ_ABT_ERR_MASK      0x00000010
#define SMMU_S_GERRORN_MSI_CMDQ_ABT_ERR_POS       4
#define SMMU_S_GERRORN_EVENTQ_ABT_ERR_MASK        0x00000004
#define SMMU_S_GERRORN_EVENTQ_ABT_ERR_POS         2
#define SMMU_S_GERRORN_CMDQ_ERR_MASK              0x00000001
#define SMMU_S_GERRORN_CMDQ_ERR_POS               0

/* Bit fields of SMMU_S_GERROR_IRQ_CFG0_LO register */
#define SMMU_S_GERROR_IRQ_CFG0_LO_ADDR_MASK       0xFFFFFFFC
#define SMMU_S_GERROR_IRQ_CFG0_LO_ADDR_POS        2

/* Bit fields of SMMU_S_GERROR_IRQ_CFG0_HI register */
#define SMMU_S_GERROR_IRQ_CFG0_HI_ADDR_MASK       0x0000FFFF
#define SMMU_S_GERROR_IRQ_CFG0_HI_ADDR_POS        0

/* Bit fields of SMMU_S_GERROR_IRQ_CFG1 register */
#define SMMU_S_GERROR_IRQ_CFG1_DATA_MASK          0xFFFFFFFF
#define SMMU_S_GERROR_IRQ_CFG1_DATA_POS           0

/* Bit fields of SMMU_S_GERROR_IRQ_CFG2 register */
#define SMMU_S_GERROR_IRQ_CFG2_SH_MASK            0x00000030
#define SMMU_S_GERROR_IRQ_CFG2_SH_POS             4
#define SMMU_S_GERROR_IRQ_CFG2_MEMATTR_MASK       0x0000000F
#define SMMU_S_GERROR_IRQ_CFG2_MEMATTR_POS        0

/* Bit fields of SMMU_S_STRTAB_BASE_LO register */
#define SMMU_S_STRTAB_BASE_LO_ADDR_MASK           0xFFFFFFC0
#define SMMU_S_STRTAB_BASE_LO_ADDR_POS            6

/* Bit fields of SMMU_S_STRTAB_BASE_HI register */
#define SMMU_S_STRTAB_BASE_HI_RA_MASK             0x40000000
#define SMMU_S_STRTAB_BASE_HI_RA_POS              30
#define SMMU_S_STRTAB_BASE_HI_ADDR_MASK           0x0000FFFF
#define SMMU_S_STRTAB_BASE_HI_ADDR_POS            0

/* Bit fields of SMMU_S_STRTAB_BASE_CFG register */
#define SMMU_S_STRTAB_BASE_CFG_FMT_MASK           0x00030000
#define SMMU_S_STRTAB_BASE_CFG_FMT_POS            16
#define SMMU_S_STRTAB_BASE_CFG_SPLIT_MASK         0x000007C0
#define SMMU_S_STRTAB_BASE_CFG_SPLIT_POS          6
#define SMMU_S_STRTAB_BASE_CFG_LOG2SIZE_MASK      0x0000003F
#define SMMU_S_STRTAB_BASE_CFG_LOG2SIZE_POS       0

/* Bit fields of SMMU_S_CMDQ_BASE_LO register */
#define SMMU_S_CMDQ_BASE_LO_ADDR_MASK             0xFFFFFFE0
#define SMMU_S_CMDQ_BASE_LO_ADDR_POS              5
#define SMMU_S_CMDQ_BASE_LO_LOG2SIZE_MASK         0x0000001F
#define SMMU_S_CMDQ_BASE_LO_LOG2SIZE_POS          0

/* Bit fields of SMMU_S_CMDQ_BASE_HI register */
#define SMMU_S_CMDQ_BASE_HI_RA_MASK               0x40000000
#define SMMU_S_CMDQ_BASE_HI_RA_POS                30
#define SMMU_S_CMDQ_BASE_HI_ADDR_MASK             0x0000FFFF
#define SMMU_S_CMDQ_BASE_HI_ADDR_POS              0

/* Bit fields of SMMU_S_CMDQ_PROD register */
#define SMMU_S_CMDQ_PROD_WR_MASK                  0x000FFFFF
#define SMMU_S_CMDQ_PROD_WR_POS                   0

/* Bit fields of SMMU_S_CMDQ_CONS register */
#define SMMU_S_CMDQ_CONS_ERR_MASK                 0x7F000000
#define SMMU_S_CMDQ_CONS_ERR_POS                  24
#define SMMU_S_CMDQ_CONS_RD_MASK                  0x000FFFFF
#define SMMU_S_CMDQ_CONS_RD_POS                   0

/* Bit fields of SMMU_S_EVENTQ_BASE_LO register */
#define SMMU_S_EVENTQ_BASE_LO_ADDR_MASK           0xFFFFFFE0
#define SMMU_S_EVENTQ_BASE_LO_ADDR_POS            5
#define SMMU_S_EVENTQ_BASE_LO_LOG2SIZE_MASK       0x0000001F
#define SMMU_S_EVENTQ_BASE_LO_LOG2SIZE_POS        0

/* Bit fields of SMMU_S_EVENTQ_BASE_HI register */
#define SMMU_S_EVENTQ_BASE_HI_WA_MASK             0x40000000
#define SMMU_S_EVENTQ_BASE_HI_WA_POS              30
#define SMMU_S_EVENTQ_BASE_HI_ADDR_MASK           0x0000FFFF
#define SMMU_S_EVENTQ_BASE_HI_ADDR_POS            0

/* Bit fields of SMMU_S_EVENTQ_PROD register */
#define SMMU_S_EVENTQ_PROD_OVFLG_MASK             0x80000000
#define SMMU_S_EVENTQ_PROD_OVFLG_POS              31
#define SMMU_S_EVENTQ_PROD_WR_MASK                0x000FFFFF
#define SMMU_S_EVENTQ_PROD_WR_POS                 0

/* Bit fields of SMMU_S_EVENTQ_CONS register */
#define SMMU_S_EVENTQ_CONS_OVACKFLG_MASK          0x80000000
#define SMMU_S_EVENTQ_CONS_OVACKFLG_POS           31
#define SMMU_S_EVENTQ_CONS_RD_MASK                0x000FFFFF
#define SMMU_S_EVENTQ_CONS_RD_POS                 0

/* Bit fields of SMMU_S_EVENTQ_IRQ_CFG0_LO register */
#define SMMU_S_EVENTQ_IRQ_CFG0_LO_ADDR_MASK       0xFFFFFFFC
#define SMMU_S_EVENTQ_IRQ_CFG0_LO_ADDR_POS        2

/* Bit fields of SMMU_S_EVENTQ_IRQ_CFG0_HI register */
#define SMMU_S_EVENTQ_IRQ_CFG0_HI_ADDR_MASK       0x0000FFFF
#define SMMU_S_EVENTQ_IRQ_CFG0_HI_ADDR_POS        0

/* Bit fields of SMMU_S_EVENTQ_IRQ_CFG1 register */
#define SMMU_S_EVENTQ_IRQ_CFG1_DATA_MASK          0xFFFFFFFF
#define SMMU_S_EVENTQ_IRQ_CFG1_DATA_POS           0

/* Bit fields of SMMU_S_EVENTQ_IRQ_CFG2 register */
#define SMMU_S_EVENTQ_IRQ_CFG2_SH_MASK            0x00000030
#define SMMU_S_EVENTQ_IRQ_CFG2_SH_POS             4
#define SMMU_S_EVENTQ_IRQ_CFG2_MEMATTR_MASK       0x0000000F
#define SMMU_S_EVENTQ_IRQ_CFG2_MEMATTR_POS        0

/* Bit fields of TCU_CTRL register */
#define S_TCU_CTRL_AUX31_MASK                     0x80000000
#define S_TCU_CTRL_AUX31_POS                      31
#define S_TCU_CTRL_AUX30_MASK                     0x40000000
#define S_TCU_CTRL_AUX30_POS                      30
#define S_TCU_CTRL_AUX29_MASK                     0x20000000
#define S_TCU_CTRL_AUX29_POS                      29
#define S_TCU_CTRL_AUX28_MASK                     0x10000000
#define S_TCU_CTRL_AUX28_POS                      28
#define S_TCU_CTRL_AUX27_MASK                     0x08000000
#define S_TCU_CTRL_AUX27_POS                      27
#define S_TCU_CTRL_AUX26_MASK                     0x04000000
#define S_TCU_CTRL_AUX26_POS                      26
#define S_TCU_CTRL_AUX25_MASK                     0x02000000
#define S_TCU_CTRL_AUX25_POS                      25
#define S_TCU_CTRL_AUX24_MASK                     0x01000000
#define S_TCU_CTRL_AUX24_POS                      24
#define S_TCU_CTRL_AUX23_MASK                     0x00800000
#define S_TCU_CTRL_AUX23_POS                      23
#define S_TCU_CTRL_AUX22_MASK                     0x00400000
#define S_TCU_CTRL_AUX22_POS                      22
#define S_TCU_CTRL_AUX21_MASK                     0x00200000
#define S_TCU_CTRL_AUX21_POS                      21
#define S_TCU_CTRL_AUX20_MASK                     0x00100000
#define S_TCU_CTRL_AUX20_POS                      20
#define S_TCU_CTRL_AUX19_MASK                     0x00080000
#define S_TCU_CTRL_AUX19_POS                      19
#define S_TCU_CTRL_AUX18_MASK                     0x00040000
#define S_TCU_CTRL_AUX18_POS                      18
#define S_TCU_CTRL_AUX17_MASK                     0x00020000
#define S_TCU_CTRL_AUX17_POS                      17
#define S_TCU_CTRL_AUX16_MASK                     0x00010000
#define S_TCU_CTRL_AUX16_POS                      16
#define S_TCU_CTRL_WCS2L3_DIS_MASK                0x00008000
#define S_TCU_CTRL_WCS2L3_DIS_POS                 15
#define S_TCU_CTRL_WCS2L2_DIS_MASK                0x00004000
#define S_TCU_CTRL_WCS2L2_DIS_POS                 14
#define S_TCU_CTRL_WCS2L1_DIS_MASK                0x00002000
#define S_TCU_CTRL_WCS2L1_DIS_POS                 13
#define S_TCU_CTRL_WCS2L0_DIS_MASK                0x00001000
#define S_TCU_CTRL_WCS2L0_DIS_POS                 12
#define S_TCU_CTRL_WCS1L3_DIS_MASK                0x00000800
#define S_TCU_CTRL_WCS1L3_DIS_POS                 11
#define S_TCU_CTRL_WCS1L2_DIS_MASK                0x00000400
#define S_TCU_CTRL_WCS1L2_DIS_POS                 10
#define S_TCU_CTRL_WCS1L1_DIS_MASK                0x00000200
#define S_TCU_CTRL_WCS1L1_DIS_POS                 9
#define S_TCU_CTRL_WCS1L0_DIS_MASK                0x00000100
#define S_TCU_CTRL_WCS1L0_DIS_POS                 8
#define S_TCU_CTRL_AUX7_MASK                      0x00000080
#define S_TCU_CTRL_AUX7_POS                       7
#define S_TCU_CTRL_AUX6_MASK                      0x00000040
#define S_TCU_CTRL_AUX6_POS                       6
#define S_TCU_CTRL_AUX5_MASK                      0x00000020
#define S_TCU_CTRL_AUX5_POS                       5
#define S_TCU_CTRL_AUX4_MASK                      0x00000010
#define S_TCU_CTRL_AUX4_POS                       4
#define S_TCU_CTRL_AUX3_MASK                      0x00000008
#define S_TCU_CTRL_AUX3_POS                       3
#define S_TCU_CTRL_AUX2_MASK                      0x00000004
#define S_TCU_CTRL_AUX2_POS                       2
#define S_TCU_CTRL_AUX1_MASK                      0x00000002
#define S_TCU_CTRL_AUX1_POS                       1
#define S_TCU_CTRL_AUX0_MASK                      0x00000001
#define S_TCU_CTRL_AUX0_POS                       0

/* Bit fields of TCU_QOS register */
#define S_TCU_QOS_QOS_DVMSYNC_MASK                0x0F000000
#define S_TCU_QOS_QOS_DVMSYNC_POS                 24
#define S_TCU_QOS_QOS_MSI_MASK                    0x00F00000
#define S_TCU_QOS_QOS_MSI_POS                     20
#define S_TCU_QOS_QOS_QUEUE_MASK                  0x000F0000
#define S_TCU_QOS_QOS_QUEUE_POS                   16
#define S_TCU_QOS_QOS_PTW3_MASK                   0x0000F000
#define S_TCU_QOS_QOS_PTW3_POS                    12
#define S_TCU_QOS_QOS_PTW2_MASK                   0x00000F00
#define S_TCU_QOS_QOS_PTW2_POS                    8
#define S_TCU_QOS_QOS_PTW1_MASK                   0x000000F0
#define S_TCU_QOS_QOS_PTW1_POS                    4
#define S_TCU_QOS_QOS_PTW0_MASK                   0x0000000F
#define S_TCU_QOS_QOS_PTW0_POS                    0

/* Bit fields of TCU_CFG register */
#define S_TCU_CFG_XLATE_SLOTS_MASK                0x0000FFF0
#define S_TCU_CFG_XLATE_SLOTS_POS                 4

/* Bit fields of TCU_STATUS register */
#define S_TCU_STATUS_GNT_XLATE_SLOTS_MASK         0x0000FFF0
#define S_TCU_STATUS_GNT_XLATE_SLOTS_POS          4

/* Bit fields of TCU_SCR register */
#define S_TCU_SCR_NS_INIT_MASK                    0x00000008
#define S_TCU_SCR_NS_INIT_POS                     3
#define S_TCU_SCR_NS_RAS_MASK                     0x00000002
#define S_TCU_SCR_NS_RAS_POS                      1
#define S_TCU_SCR_NS_UARCH_MASK                   0x00000001
#define S_TCU_SCR_NS_UARCH_POS                    0

/* Bit fields of TCU_ERRFR_LO register */
#define S_TCU_ERRFR_LO_FI_MASK                    0x000000C0
#define S_TCU_ERRFR_LO_FI_POS                     6
#define S_TCU_ERRFR_LO_ED_MASK                    0x00000003
#define S_TCU_ERRFR_LO_ED_POS                     0

/* Bit fields of TCU_ERRFR_HI register */

/* Bit fields of TCU_ERRCTLR_LO register */
#define S_TCU_ERRCTLR_LO_FI_MASK    0x00000008
#define S_TCU_ERRCTLR_LO_FI_POS     3

/* Bit fields of TCU_ERRCTLR_HI register */

/* Bit fields of TCU_ERRSTATUS_LO register */
#define S_TCU_ERRSTATUS_LO_V_MASK       0x40000000
#define S_TCU_ERRSTATUS_LO_V_POS        30
#define S_TCU_ERRSTATUS_LO_OF_MASK      0x08000000
#define S_TCU_ERRSTATUS_LO_OF_POS       27
#define S_TCU_ERRSTATUS_LO_CE_MASK      0x03000000
#define S_TCU_ERRSTATUS_LO_CE_POS       24
#define S_TCU_ERRSTATUS_LO_IERR_MASK    0x0000FF00
#define S_TCU_ERRSTATUS_LO_IERR_POS     8
#define S_TCU_ERRSTATUS_LO_SERR_MASK    0x000000FF
#define S_TCU_ERRSTATUS_LO_SERR_POS     0

/* Bit fields of TCU_ERRSTATUS_HI register */

/* Bit fields of TCU_ERRGEN_LO register */
#define S_TCU_ERRGEN_LO_TCC_MASK    0x00000008
#define S_TCU_ERRGEN_LO_TCC_POS     3
#define S_TCU_ERRGEN_LO_DCC_MASK    0x00000004
#define S_TCU_ERRGEN_LO_DCC_POS     2
#define S_TCU_ERRGEN_LO_TWC_MASK    0x00000002
#define S_TCU_ERRGEN_LO_TWC_POS     1
#define S_TCU_ERRGEN_LO_DWC_MASK    0x00000001
#define S_TCU_ERRGEN_LO_DWC_POS     0

/* Bit fields of TCU_ERRGEN_HI register */

/* Bit fields of TCU_NODE_CTRL0 register */
#define S_TCU_NODE_CTRL0_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL0_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL0_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL0_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL1 register */
#define S_TCU_NODE_CTRL1_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL1_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL1_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL1_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL2 register */
#define S_TCU_NODE_CTRL2_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL2_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL2_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL2_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL3 register */
#define S_TCU_NODE_CTRL3_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL3_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL3_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL3_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL4 register */
#define S_TCU_NODE_CTRL4_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL4_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL4_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL4_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL5 register */
#define S_TCU_NODE_CTRL5_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL5_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL5_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL5_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL6 register */
#define S_TCU_NODE_CTRL6_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL6_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL6_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL6_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL7 register */
#define S_TCU_NODE_CTRL7_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL7_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL7_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL7_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL8 register */
#define S_TCU_NODE_CTRL8_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL8_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL8_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL8_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL9 register */
#define S_TCU_NODE_CTRL9_DIS_DVM_MASK               0x00000010
#define S_TCU_NODE_CTRL9_DIS_DVM_POS                4
#define S_TCU_NODE_CTRL9_PRI_LEVEL_MASK             0x00000003
#define S_TCU_NODE_CTRL9_PRI_LEVEL_POS              0

/* Bit fields of TCU_NODE_CTRL10 register */
#define S_TCU_NODE_CTRL10_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL10_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL10_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL10_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL11 register */
#define S_TCU_NODE_CTRL11_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL11_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL11_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL11_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL12 register */
#define S_TCU_NODE_CTRL12_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL12_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL12_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL12_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL13 register */
#define S_TCU_NODE_CTRL13_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL13_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL13_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL13_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL14 register */
#define S_TCU_NODE_CTRL14_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL14_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL14_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL14_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL15 register */
#define S_TCU_NODE_CTRL15_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL15_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL15_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL15_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL16 register */
#define S_TCU_NODE_CTRL16_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL16_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL16_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL16_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL17 register */
#define S_TCU_NODE_CTRL17_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL17_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL17_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL17_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL18 register */
#define S_TCU_NODE_CTRL18_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL18_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL18_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL18_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL19 register */
#define S_TCU_NODE_CTRL19_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL19_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL19_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL19_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL20 register */
#define S_TCU_NODE_CTRL20_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL20_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL20_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL20_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL21 register */
#define S_TCU_NODE_CTRL21_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL21_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL21_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL21_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL22 register */
#define S_TCU_NODE_CTRL22_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL22_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL22_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL22_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL23 register */
#define S_TCU_NODE_CTRL23_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL23_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL23_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL23_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL24 register */
#define S_TCU_NODE_CTRL24_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL24_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL24_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL24_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL25 register */
#define S_TCU_NODE_CTRL25_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL25_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL25_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL25_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL26 register */
#define S_TCU_NODE_CTRL26_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL26_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL26_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL26_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL27 register */
#define S_TCU_NODE_CTRL27_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL27_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL27_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL27_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL28 register */
#define S_TCU_NODE_CTRL28_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL28_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL28_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL28_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL29 register */
#define S_TCU_NODE_CTRL29_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL29_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL29_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL29_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL30 register */
#define S_TCU_NODE_CTRL30_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL30_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL30_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL30_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL31 register */
#define S_TCU_NODE_CTRL31_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL31_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL31_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL31_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL32 register */
#define S_TCU_NODE_CTRL32_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL32_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL32_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL32_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL33 register */
#define S_TCU_NODE_CTRL33_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL33_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL33_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL33_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL34 register */
#define S_TCU_NODE_CTRL34_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL34_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL34_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL34_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL35 register */
#define S_TCU_NODE_CTRL35_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL35_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL35_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL35_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL36 register */
#define S_TCU_NODE_CTRL36_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL36_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL36_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL36_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL37 register */
#define S_TCU_NODE_CTRL37_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL37_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL37_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL37_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL38 register */
#define S_TCU_NODE_CTRL38_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL38_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL38_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL38_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL39 register */
#define S_TCU_NODE_CTRL39_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL39_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL39_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL39_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL40 register */
#define S_TCU_NODE_CTRL40_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL40_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL40_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL40_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL41 register */
#define S_TCU_NODE_CTRL41_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL41_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL41_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL41_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL42 register */
#define S_TCU_NODE_CTRL42_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL42_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL42_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL42_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL43 register */
#define S_TCU_NODE_CTRL43_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL43_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL43_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL43_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL44 register */
#define S_TCU_NODE_CTRL44_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL44_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL44_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL44_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL45 register */
#define S_TCU_NODE_CTRL45_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL45_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL45_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL45_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL46 register */
#define S_TCU_NODE_CTRL46_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL46_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL46_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL46_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL47 register */
#define S_TCU_NODE_CTRL47_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL47_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL47_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL47_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL48 register */
#define S_TCU_NODE_CTRL48_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL48_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL48_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL48_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL49 register */
#define S_TCU_NODE_CTRL49_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL49_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL49_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL49_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL50 register */
#define S_TCU_NODE_CTRL50_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL50_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL50_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL50_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL51 register */
#define S_TCU_NODE_CTRL51_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL51_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL51_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL51_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL52 register */
#define S_TCU_NODE_CTRL52_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL52_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL52_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL52_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL53 register */
#define S_TCU_NODE_CTRL53_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL53_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL53_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL53_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL54 register */
#define S_TCU_NODE_CTRL54_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL54_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL54_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL54_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL55 register */
#define S_TCU_NODE_CTRL55_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL55_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL55_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL55_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL56 register */
#define S_TCU_NODE_CTRL56_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL56_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL56_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL56_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL57 register */
#define S_TCU_NODE_CTRL57_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL57_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL57_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL57_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL58 register */
#define S_TCU_NODE_CTRL58_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL58_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL58_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL58_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL59 register */
#define S_TCU_NODE_CTRL59_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL59_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL59_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL59_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL60 register */
#define S_TCU_NODE_CTRL60_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL60_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL60_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL60_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_CTRL61 register */
#define S_TCU_NODE_CTRL61_DIS_DVM_MASK              0x00000010
#define S_TCU_NODE_CTRL61_DIS_DVM_POS               4
#define S_TCU_NODE_CTRL61_PRI_LEVEL_MASK            0x00000003
#define S_TCU_NODE_CTRL61_PRI_LEVEL_POS             0

/* Bit fields of TCU_NODE_STATUS0 register */
#define S_TCU_NODE_STATUS0_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS0_ATS_POS                  1
#define S_TCU_NODE_STATUS0_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS0_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS1 register */
#define S_TCU_NODE_STATUS1_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS1_ATS_POS                  1
#define S_TCU_NODE_STATUS1_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS1_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS2 register */
#define S_TCU_NODE_STATUS2_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS2_ATS_POS                  1
#define S_TCU_NODE_STATUS2_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS2_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS3 register */
#define S_TCU_NODE_STATUS3_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS3_ATS_POS                  1
#define S_TCU_NODE_STATUS3_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS3_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS4 register */
#define S_TCU_NODE_STATUS4_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS4_ATS_POS                  1
#define S_TCU_NODE_STATUS4_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS4_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS5 register */
#define S_TCU_NODE_STATUS5_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS5_ATS_POS                  1
#define S_TCU_NODE_STATUS5_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS5_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS6 register */
#define S_TCU_NODE_STATUS6_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS6_ATS_POS                  1
#define S_TCU_NODE_STATUS6_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS6_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS7 register */
#define S_TCU_NODE_STATUS7_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS7_ATS_POS                  1
#define S_TCU_NODE_STATUS7_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS7_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS8 register */
#define S_TCU_NODE_STATUS8_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS8_ATS_POS                  1
#define S_TCU_NODE_STATUS8_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS8_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS9 register */
#define S_TCU_NODE_STATUS9_ATS_MASK                 0x00000002
#define S_TCU_NODE_STATUS9_ATS_POS                  1
#define S_TCU_NODE_STATUS9_CONNECTED_MASK           0x00000001
#define S_TCU_NODE_STATUS9_CONNECTED_POS            0

/* Bit fields of TCU_NODE_STATUS10 register */
#define S_TCU_NODE_STATUS10_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS10_ATS_POS                 1
#define S_TCU_NODE_STATUS10_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS10_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS11 register */
#define S_TCU_NODE_STATUS11_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS11_ATS_POS                 1
#define S_TCU_NODE_STATUS11_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS11_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS12 register */
#define S_TCU_NODE_STATUS12_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS12_ATS_POS                 1
#define S_TCU_NODE_STATUS12_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS12_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS13 register */
#define S_TCU_NODE_STATUS13_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS13_ATS_POS                 1
#define S_TCU_NODE_STATUS13_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS13_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS14 register */
#define S_TCU_NODE_STATUS14_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS14_ATS_POS                 1
#define S_TCU_NODE_STATUS14_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS14_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS15 register */
#define S_TCU_NODE_STATUS15_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS15_ATS_POS                 1
#define S_TCU_NODE_STATUS15_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS15_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS16 register */
#define S_TCU_NODE_STATUS16_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS16_ATS_POS                 1
#define S_TCU_NODE_STATUS16_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS16_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS17 register */
#define S_TCU_NODE_STATUS17_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS17_ATS_POS                 1
#define S_TCU_NODE_STATUS17_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS17_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS18 register */
#define S_TCU_NODE_STATUS18_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS18_ATS_POS                 1
#define S_TCU_NODE_STATUS18_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS18_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS19 register */
#define S_TCU_NODE_STATUS19_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS19_ATS_POS                 1
#define S_TCU_NODE_STATUS19_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS19_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS20 register */
#define S_TCU_NODE_STATUS20_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS20_ATS_POS                 1
#define S_TCU_NODE_STATUS20_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS20_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS21 register */
#define S_TCU_NODE_STATUS21_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS21_ATS_POS                 1
#define S_TCU_NODE_STATUS21_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS21_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS22 register */
#define S_TCU_NODE_STATUS22_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS22_ATS_POS                 1
#define S_TCU_NODE_STATUS22_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS22_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS23 register */
#define S_TCU_NODE_STATUS23_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS23_ATS_POS                 1
#define S_TCU_NODE_STATUS23_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS23_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS24 register */
#define S_TCU_NODE_STATUS24_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS24_ATS_POS                 1
#define S_TCU_NODE_STATUS24_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS24_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS25 register */
#define S_TCU_NODE_STATUS25_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS25_ATS_POS                 1
#define S_TCU_NODE_STATUS25_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS25_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS26 register */
#define S_TCU_NODE_STATUS26_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS26_ATS_POS                 1
#define S_TCU_NODE_STATUS26_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS26_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS27 register */
#define S_TCU_NODE_STATUS27_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS27_ATS_POS                 1
#define S_TCU_NODE_STATUS27_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS27_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS28 register */
#define S_TCU_NODE_STATUS28_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS28_ATS_POS                 1
#define S_TCU_NODE_STATUS28_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS28_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS29 register */
#define S_TCU_NODE_STATUS29_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS29_ATS_POS                 1
#define S_TCU_NODE_STATUS29_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS29_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS30 register */
#define S_TCU_NODE_STATUS30_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS30_ATS_POS                 1
#define S_TCU_NODE_STATUS30_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS30_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS31 register */
#define S_TCU_NODE_STATUS31_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS31_ATS_POS                 1
#define S_TCU_NODE_STATUS31_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS31_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS32 register */
#define S_TCU_NODE_STATUS32_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS32_ATS_POS                 1
#define S_TCU_NODE_STATUS32_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS32_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS33 register */
#define S_TCU_NODE_STATUS33_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS33_ATS_POS                 1
#define S_TCU_NODE_STATUS33_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS33_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS34 register */
#define S_TCU_NODE_STATUS34_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS34_ATS_POS                 1
#define S_TCU_NODE_STATUS34_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS34_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS35 register */
#define S_TCU_NODE_STATUS35_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS35_ATS_POS                 1
#define S_TCU_NODE_STATUS35_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS35_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS36 register */
#define S_TCU_NODE_STATUS36_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS36_ATS_POS                 1
#define S_TCU_NODE_STATUS36_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS36_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS37 register */
#define S_TCU_NODE_STATUS37_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS37_ATS_POS                 1
#define S_TCU_NODE_STATUS37_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS37_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS38 register */
#define S_TCU_NODE_STATUS38_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS38_ATS_POS                 1
#define S_TCU_NODE_STATUS38_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS38_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS39 register */
#define S_TCU_NODE_STATUS39_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS39_ATS_POS                 1
#define S_TCU_NODE_STATUS39_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS39_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS40 register */
#define S_TCU_NODE_STATUS40_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS40_ATS_POS                 1
#define S_TCU_NODE_STATUS40_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS40_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS41 register */
#define S_TCU_NODE_STATUS41_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS41_ATS_POS                 1
#define S_TCU_NODE_STATUS41_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS41_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS42 register */
#define S_TCU_NODE_STATUS42_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS42_ATS_POS                 1
#define S_TCU_NODE_STATUS42_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS42_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS43 register */
#define S_TCU_NODE_STATUS43_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS43_ATS_POS                 1
#define S_TCU_NODE_STATUS43_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS43_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS44 register */
#define S_TCU_NODE_STATUS44_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS44_ATS_POS                 1
#define S_TCU_NODE_STATUS44_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS44_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS45 register */
#define S_TCU_NODE_STATUS45_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS45_ATS_POS                 1
#define S_TCU_NODE_STATUS45_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS45_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS46 register */
#define S_TCU_NODE_STATUS46_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS46_ATS_POS                 1
#define S_TCU_NODE_STATUS46_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS46_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS47 register */
#define S_TCU_NODE_STATUS47_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS47_ATS_POS                 1
#define S_TCU_NODE_STATUS47_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS47_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS48 register */
#define S_TCU_NODE_STATUS48_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS48_ATS_POS                 1
#define S_TCU_NODE_STATUS48_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS48_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS49 register */
#define S_TCU_NODE_STATUS49_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS49_ATS_POS                 1
#define S_TCU_NODE_STATUS49_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS49_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS50 register */
#define S_TCU_NODE_STATUS50_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS50_ATS_POS                 1
#define S_TCU_NODE_STATUS50_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS50_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS51 register */
#define S_TCU_NODE_STATUS51_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS51_ATS_POS                 1
#define S_TCU_NODE_STATUS51_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS51_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS52 register */
#define S_TCU_NODE_STATUS52_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS52_ATS_POS                 1
#define S_TCU_NODE_STATUS52_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS52_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS53 register */
#define S_TCU_NODE_STATUS53_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS53_ATS_POS                 1
#define S_TCU_NODE_STATUS53_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS53_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS54 register */
#define S_TCU_NODE_STATUS54_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS54_ATS_POS                 1
#define S_TCU_NODE_STATUS54_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS54_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS55 register */
#define S_TCU_NODE_STATUS55_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS55_ATS_POS                 1
#define S_TCU_NODE_STATUS55_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS55_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS56 register */
#define S_TCU_NODE_STATUS56_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS56_ATS_POS                 1
#define S_TCU_NODE_STATUS56_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS56_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS57 register */
#define S_TCU_NODE_STATUS57_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS57_ATS_POS                 1
#define S_TCU_NODE_STATUS57_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS57_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS58 register */
#define S_TCU_NODE_STATUS58_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS58_ATS_POS                 1
#define S_TCU_NODE_STATUS58_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS58_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS59 register */
#define S_TCU_NODE_STATUS59_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS59_ATS_POS                 1
#define S_TCU_NODE_STATUS59_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS59_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS60 register */
#define S_TCU_NODE_STATUS60_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS60_ATS_POS                 1
#define S_TCU_NODE_STATUS60_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS60_CONNECTED_POS           0

/* Bit fields of TCU_NODE_STATUS61 register */
#define S_TCU_NODE_STATUS61_ATS_MASK                0x00000002
#define S_TCU_NODE_STATUS61_ATS_POS                 1
#define S_TCU_NODE_STATUS61_CONNECTED_MASK          0x00000001
#define S_TCU_NODE_STATUS61_CONNECTED_POS           0

/* Bit fields of SMMU_EVENTQ_PROD register */
#define SMMU_EVENTQ_PROD_OVFLG_MASK                 0x80000000
#define SMMU_EVENTQ_PROD_OVFLG_POS                  31
#define SMMU_EVENTQ_PROD_WR_MASK                    0x000FFFFF
#define SMMU_EVENTQ_PROD_WR_POS                     0

/* Bit fields of SMMU_EVENTQ_CONS register */
#define SMMU_EVENTQ_CONS_OVACKFLG_MASK              0x80000000
#define SMMU_EVENTQ_CONS_OVACKFLG_POS               31
#define SMMU_EVENTQ_CONS_RD_MASK                    0x000FFFFF
#define SMMU_EVENTQ_CONS_RD_POS                     0

/* Bit fields of SMMU_PRIQ_PROD register */
#define SMMU_PRIQ_PROD_OVFLG_MASK                   0x80000000
#define SMMU_PRIQ_PROD_OVFLG_POS                    31
#define SMMU_PRIQ_PROD_WR_MASK                      0x000FFFFF
#define SMMU_PRIQ_PROD_WR_POS                       0

/* Bit fields of SMMU_PRIQ_CONS register */
#define SMMU_PRIQ_CONS_OVACKFLG_MASK                0x80000000
#define SMMU_PRIQ_CONS_OVACKFLG_POS                 31
#define SMMU_PRIQ_CONS_RD_MASK                      0x000FFFFF
#define SMMU_PRIQ_CONS_RD_POS                       0

/* Bit fields of SMMU_PMCG_EVCNTR0 register */
#define SMMU_PMCG_EVCNTR0_COUNTER_VALUE_MASK        0xFFFFFFFF
#define SMMU_PMCG_EVCNTR0_COUNTER_VALUE_POS         0

/* Bit fields of SMMU_PMCG_EVCNTR1 register */
#define SMMU_PMCG_EVCNTR1_COUNTER_VALUE_MASK        0xFFFFFFFF
#define SMMU_PMCG_EVCNTR1_COUNTER_VALUE_POS         0

/* Bit fields of SMMU_PMCG_EVCNTR2 register */
#define SMMU_PMCG_EVCNTR2_COUNTER_VALUE_MASK        0xFFFFFFFF
#define SMMU_PMCG_EVCNTR2_COUNTER_VALUE_POS         0

/* Bit fields of SMMU_PMCG_EVCNTR3 register */
#define SMMU_PMCG_EVCNTR3_COUNTER_VALUE_MASK        0xFFFFFFFF
#define SMMU_PMCG_EVCNTR3_COUNTER_VALUE_POS         0

/* Bit fields of SMMU_PMCG_SVR0 register */
#define SMMU_PMCG_SVR0_SHADOW_COUNTER_VALUE_MASK    0xFFFFFFFF
#define SMMU_PMCG_SVR0_SHADOW_COUNTER_VALUE_POS     0

/* Bit fields of SMMU_PMCG_SVR1 register */
#define SMMU_PMCG_SVR1_SHADOW_COUNTER_VALUE_MASK    0xFFFFFFFF
#define SMMU_PMCG_SVR1_SHADOW_COUNTER_VALUE_POS     0

/* Bit fields of SMMU_PMCG_SVR2 register */
#define SMMU_PMCG_SVR2_SHADOW_COUNTER_VALUE_MASK    0xFFFFFFFF
#define SMMU_PMCG_SVR2_SHADOW_COUNTER_VALUE_POS     0

/* Bit fields of SMMU_PMCG_SVR3 register */
#define SMMU_PMCG_SVR3_SHADOW_COUNTER_VALUE_MASK    0xFFFFFFFF
#define SMMU_PMCG_SVR3_SHADOW_COUNTER_VALUE_POS     0

/* Bit fields of SMMU_PMCG_OVSCLR0 register */
#define SMMU_PMCG_OVSCLR0_OVS_MASK                  0x0000000F
#define SMMU_PMCG_OVSCLR0_OVS_POS                   0

/* Bit fields of SMMU_PMCG_OVSSET0 register */
#define SMMU_PMCG_OVSSET0_OVS_MASK                  0x0000000F
#define SMMU_PMCG_OVSSET0_OVS_POS                   0

/* Bit fields of SMMU_PMCG_CAPR register */
#define SMMU_PMCG_CAPR_CAPTURE_MASK                 0x00000001
#define SMMU_PMCG_CAPR_CAPTURE_POS                  0

#endif /* _SOCFPGA_SMMU_REG_H_ */
