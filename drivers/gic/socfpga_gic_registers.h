/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gic_registers.h
 *
 * GIC hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_GIC_REGISTERS_H__
#define __SOCFPGA_GIC_REGISTERS_H__

#include <stdint.h>

struct gic_v3_dist_if
{
    volatile uint32_t GICD_CTLR;
    volatile uint32_t GICD_TYPER;
    volatile uint32_t GICD_IIDR;
    const volatile uint32_t padding1[5];
    volatile uint32_t GICD_FCTLR;
    volatile uint32_t GICD_SAC;
    const volatile uint32_t padding2[6];
    volatile uint32_t GICD_SETSPI_NSR;
    const volatile uint32_t padding3;
    volatile uint32_t GICD_CLRSPI_NSR;
    const volatile uint32_t padding4;
    volatile uint32_t GICD_SETSPI_SR;
    const volatile uint32_t padding5;
    volatile uint32_t GICD_CLRSPI_SR;
    const volatile uint32_t padding6[10];
    volatile uint32_t GICD_IGROUPR[17];
    const volatile uint32_t padding7[15];
    volatile uint32_t GICD_ISENABLER[17];
    const volatile uint32_t padding8[15];
    volatile uint32_t GICD_ICENABLER[17];
    const volatile uint32_t padding9[15];
    volatile uint32_t GICD_ISPENDR[17];
    const volatile uint32_t padding10[15];
    volatile uint32_t GICD_ICPENDR[17];
    const volatile uint32_t padding11[15];
    volatile uint32_t GICD_ISACTIVER[17];
    const volatile uint32_t padding12[15];
    volatile uint32_t GICD_ICACTIVER[17];
    const volatile uint32_t padding13[22];
    volatile uint32_t GICD_IPRIORITYR[136];
    const volatile uint32_t padding14[370];
    volatile uint32_t GICD_ICFGR[34];
    const volatile uint32_t padding15[29];
    volatile uint32_t GICD_IGRPMODR[17];
    const volatile uint32_t padding16[48];
    volatile uint32_t GICD_NSACR[34];
    const volatile uint32_t padding17[5276];
    volatile uint64_t GICD_IROUTER[544];
    const volatile uint32_t padding561[7042];
    volatile uint32_t GICD_ICLAR[34];
    const volatile uint32_t padding562[29];
    volatile uint32_t GICD_IERRR[17];
    const volatile uint32_t padding563[942];
    volatile uint32_t GICD_CFGID;
    const volatile uint32_t padding564[1011];
    volatile uint32_t GICD_PIDR[8];
    volatile uint32_t GICD_CIDR[4];
};

struct gic_v3_rdist_lpis_if
{
    volatile uint32_t GICR_CTLR;
    volatile uint32_t GICR_IIDR;
    volatile uint32_t GICR_TYPER[2];
    const volatile uint32_t padding1;
    volatile uint32_t GICR_WAKER;
    const volatile uint32_t padding2[2];
    volatile uint32_t GICR_FCTLR;
    volatile uint32_t GICR_PWRR;
    volatile uint32_t GICR_CLASS;
    const volatile uint32_t padding3[17];
    volatile uint64_t GICR_PROPBASER;
    volatile uint64_t GICR_PENDBASER;
    const volatile uint32_t padding5[16340];
    volatile uint32_t GICR_PIDR[8];
    volatile uint32_t GICR_CIDR[4];
};

struct gic_v3_rdist_sgis_if
{
    const volatile uint32_t padding1[32];
    volatile uint32_t GICR_IGROUPR0;
    const volatile uint32_t padding2[31];
    volatile uint32_t GICR_ISENABLER0;
    const volatile uint32_t padding3[31];
    volatile uint32_t GICR_ICENABLER0;
    const volatile uint32_t padding4[31];
    volatile uint32_t GICR_ISPENDR0;
    const volatile uint32_t padding5[31];
    volatile uint32_t GICR_ICPENDR0;
    const volatile uint32_t padding6[31];
    volatile uint32_t GICR_ISACTIVER0;
    const volatile uint32_t padding7[31];
    volatile uint32_t GICR_ICACTIVER0;
    const volatile uint32_t padding8[31];
    volatile uint8_t GICR_IPRIORITYR[32];            /* Defined as 1 byte registers for easier bype level access */
    const volatile uint32_t padding9[504];
    volatile uint32_t GICR_ICFGR[2];
    const volatile uint32_t padding10[62];
    volatile uint32_t GICR_IGRPMODR0;
    const volatile uint32_t padding11[63];
    volatile uint32_t GICR_NSACR;
    const volatile uint32_t padding12[11391];
    volatile uint32_t GICR_MISCSTATUSR;
    const volatile uint32_t padding13;
    volatile uint32_t GICR_IERRVR;
    const volatile uint32_t padding14;
    volatile uint64_t GICR_SGIDR;
    const volatile uint32_t padding15[3066];
    volatile uint32_t GICR_CFGID[2];
};

struct gic_v3_rdist_vlpis_if
{
    const volatile uint32_t padding1[28];        /* +0x0000 - RESERVED */
    volatile uint64_t GICR_VPROPBASER;           /* +0x0070 - RW - Sets location of the LPI vPE Configuration table */
    volatile uint64_t GICR_VPENDBASER;           /* +0x0078 - RW - Sets location of the LPI Pending table */
};

struct gic_v3_rdist_res_if
{
    const volatile uint32_t padding1[32];        /* +0x0000 - RESERVED */
};

struct gic_v3_rdist_if
{
    struct gic_v3_rdist_lpis_if lpis  __attribute__((aligned (0x10000)));
    struct gic_v3_rdist_sgis_if sgis  __attribute__((aligned (0x10000)));
}
#if defined(PLAT_AGILEX5)
/* Agilex5 GICv3 redistributor spacing: 128KB (0x20000) per PE.
 * Align struct to force proper stride for gic_rdist[index] array access. */
__attribute__((aligned (0x20000)))
#endif
;

#endif /* __SOCFPGA_GIC_REGISTERS_H__ */
