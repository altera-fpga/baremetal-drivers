#ifndef GIC_REGS_H
#define GIC_REGS_H

#include "device.h"
#include <stdint.h>

#include "hps_address_map.h"

// arm_gicd_regs_t -- GIC Distributor Registers
// also used for accessing GICDA registers
typedef struct {
    volatile uint32_t GICD_CTLR;                // GICD_CTLR - Offset: 0x0
    volatile uint32_t GICD_TYPER;               // GICD_TYPER - Offset: 0x4
    volatile uint32_t GICD_IIDR;                // GICD_IIDR - Offset: 0x8
    volatile uint32_t _pad_0xc_0x1f[5];         // UNUSED - Offset: 0xC
    volatile uint32_t GICD_FCTLR;               // GICD_FCTLR - Offset: 0x20
    volatile uint32_t GICD_SAC;                 // GICD_SAC - Offset: 0x24
    volatile uint32_t _pad_0x28_0x3f[6];        // UNUSED - Offset: 0x28
    volatile uint32_t GICD_SETSPI_NSR;          // GICD_SETSPI_NSR - Offset: 0x40
    volatile uint32_t _pad_0x44_0x47;           // UNUSED - Offset: 0x44
    volatile uint32_t GICD_CLRSPI_NSR;          // GICD_CLRSPI_NSR - Offset: 0x48
    volatile uint32_t _pad_0x4c_0x4f;           // UNUSED - Offset: 0x4C
    volatile uint32_t GICD_SETSPI_SR;           // GICD_SETSPI_SR - Offset: 0x50
    volatile uint32_t _pad_0x54_0x57;           // UNUSED - Offset: 0x54
    volatile uint32_t GICD_CLRSPI_SR;           // GICD_CLRSPI_SR - Offset: 0x58
    volatile uint32_t _pad_0x5c_0x83[10];       // UNUSED - Offset: 0x5C
    volatile uint32_t GICD_IGROUPR[17];         // GICD_IGROUPR1 to GICD_IGROUPR17 - Offset: 0x84
    volatile uint32_t _pad_0xc8_0x103[15];      // UNUSED - Offset: 0xC8
    volatile uint32_t GICD_ISENABLER[17];       // GICD_ISENABLER1 to
                                                // GICD_ISENABLER17 - Offset: 0x104
    volatile uint32_t _pad_0x148_0x183[15];     // UNUSED - Offset: 0x148
    volatile uint32_t GICD_ICENABLER[17];       // GICD_ICENABLER1 to
                                                // GICD_ICENABLER17 - Offset: 0x184
    volatile uint32_t _pad_0x1c8_0x203[15];     // UNUSED - Offset: 0x1C8
    volatile uint32_t GICD_ISPENDR[17];         // GICD_ISPENDR1 to GICD_ISPENDR17 - Offset: 0x204
    volatile uint32_t _pad_0x248_0x283[15];     // UNUSED - Offset: 0x248
    volatile uint32_t GICD_ICPENDR[17];         // GICD_ICPENDR1 to GICD_ICPENDR17 - Offset: 0x284
    volatile uint32_t _pad_0x2c8_0x303[15];     // UNUSED - Offset: 0x2C8
    volatile uint32_t GICD_ISACTIVER[17];       // GICD_ISACTIVER1 to
                                                // GICD_ISACTIVER17 - Offset: 0x304
    volatile uint32_t _pad_0x348_0x383[15];     // UNUSED - Offset: 0x348
    volatile uint32_t GICD_ICACTIVER[17];       // GICD_ICACTIVER1 to
                                                // GICD_ICACTIVER17 - Offset: 0x384
    volatile uint32_t _pad_0x3c8_0x41f[22];     // UNUSED - Offset: 0x3C8
    volatile uint32_t GICD_IPRIORITYR[136];     // GICD_IPRIORITYR[8-143] - Offset: 0x420
    volatile uint32_t _pad_0x640_0xc07[370];    // UNUSED - Offset: 0x640
    volatile uint32_t GICD_ICFGR[34];           // GICD_ICFGR2 to GICD_ICFGR35 - Offset: 0xC08
    volatile uint32_t _pad_0xc90_0xd03[29];     // UNUSED - Offset: 0xC90
    volatile uint32_t GICD_IGRPMODR[17];        // GICD_IGRPMODR1 to GICD_IGRPMODR17 - Offset: 0xD04
    volatile uint32_t _pad_0xd48_0xe07[48];     // UNUSED - Offset: 0xD48
    volatile uint32_t GICD_NSACR[36];           // GICD_NSACR2 to GICD_NSACR35 - Offset: 0xE08
    volatile uint32_t _pad_0xe90_0x60ff[5276];  // UNUSED - Offset: 0xE90
    volatile uint64_t GICD_IROUTER[544];        // GICD_IROUTER32 to GICD_IROUTER575 -
                                                // Offset: 0x6100
    volatile uint32_t _pad_0x7200_0xe007[7042]; // UNUSED - Offset: 0x7200
    volatile uint32_t GICD_ICLAR[36];           // GICD_ICLAR2 to GICD_ICLAR35 - Offset: 0xE008
    volatile uint32_t _pad_0xe090_0xe103[29];   // UNUSED - Offset: 0xE090
    volatile uint32_t GICD_IERRR[17];           // GICD_IERRR1 to GICD_IERRR17 - Offset: 0xE104
    volatile uint32_t _pad_0xe148_0xefff[942];  // UNUSED - Offset: 0xE148
    volatile uint64_t GICD_CFGID;               // GICD_CFGID - Offset: 0xF000
    volatile uint32_t _pad_0xf008_0xffcf[1010]; // UNUSED - Offset: 0xF008
    volatile uint32_t GICD_PIDR[8];             // GICD_PIDR0 to GICD_PIDR7 - Offset: 0xFFD0
    volatile uint32_t GICD_CIDR[4];             // GICD_CIDR0 to GICD_CIDR3 - Offset: 0xFFD8
} arm_gicd_regs_t;

// arm_gica_regs_t -- GIC message based SPI interrupt control registers
typedef struct {
    volatile uint32_t _pad_0x0_0x3f[16];        /* *UNDEFINED* */
    volatile uint32_t GICA_SETSPI_NSR;          /* GICA_SETSPI_NSR */
    volatile uint32_t _pad_0x44_0x47;           /* *UNDEFINED* */
    volatile uint32_t GICA_CLRSPI_NSR;          /* GICA_CLRSPI_NSR */
    volatile uint32_t _pad_0x4c_0x4f;           /* *UNDEFINED* */
    volatile uint32_t GICA_SETSPI_SR;           /* GICA_SETSPI_SR */
    volatile uint32_t _pad_0x54_0x57;           /* *UNDEFINED* */
    volatile uint32_t GICA_CLRSPI_SR;           /* GICA_CLRSPI_SR */
    volatile uint32_t _pad_0x5c_0x10000[16361]; /* *UNDEFINED* */
} arm_gica_regs_t;

// arm_gict_regs_t -- GIC Trace and Debug Registers
typedef struct {
    volatile uint64_t GICT_ERR0FR;              /* GICT_ERR0FR */
    volatile uint64_t GICT_ERR0CTLR;            /* GICT_ERR0CTLR */
    volatile uint64_t GICT_ERR0STATUS;          /* GICT_ERR0STATUS */
    volatile uint64_t GICT_ERR0ADDR;            /* GICT_ERR0ADDR */
    volatile uint64_t GICT_ERR0MISC0;           /* GICT_ERR0MISC0 */
    volatile uint64_t GICT_ERR0MISC1;           /* GICT_ERR0MISC1 */
    volatile uint32_t _pad_0x30_0x3f[4];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR1FR;              /* GICT_ERR1FR */
    volatile uint64_t GICT_ERR1CTLR;            /* GICT_ERR1CTLR */
    volatile uint64_t GICT_ERR1STATUS;          /* GICT_ERR1STATUS */
    volatile uint32_t _pad_0x58_0x5f[2];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR1MISC0;           /* GICT_ERR1MISC0 */
    volatile uint64_t GICT_ERR1MISC1;           /* GICT_ERR1MISC1 */
    volatile uint32_t _pad_0x70_0x7f[4];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR2FR;              /* GICT_ERR2FR */
    volatile uint64_t GICT_ERR2CTLR;            /* GICT_ERR2CTLR */
    volatile uint64_t GICT_ERR2STATUS;          /* GICT_ERR2STATUS */
    volatile uint32_t _pad_0x98_0x9f[2];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR2MISC0;           /* GICT_ERR2MISC0 */
    volatile uint64_t GICT_ERR2MISC1;           /* GICT_ERR2MISC1 */
    volatile uint32_t _pad_0xb0_0xbf[4];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR3FR;              /* GICT_ERR3FR */
    volatile uint64_t GICT_ERR3CTLR;            /* GICT_ERR3CTLR */
    volatile uint64_t GICT_ERR3STATUS;          /* GICT_ERR3STATUS */
    volatile uint32_t _pad_0xd8_0xdf[2];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR3MISC0;           /* GICT_ERR3MISC0 */
    volatile uint64_t GICT_ERR3MISC1;           /* GICT_ERR3MISC1 */
    volatile uint32_t _pad_0xf0_0xff[4];        /* *UNDEFINED* */
    volatile uint64_t GICT_ERR4FR;              /* GICT_ERR4FR */
    volatile uint64_t GICT_ERR4CTLR;            /* GICT_ERR4CTLR */
    volatile uint64_t GICT_ERR4STATUS;          /* GICT_ERR4STATUS */
    volatile uint32_t _pad_0x118_0x11f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR4MISC0;           /* GICT_ERR4MISC0 */
    volatile uint64_t GICT_ERR4MISC1;           /* GICT_ERR4MISC1 */
    volatile uint32_t _pad_0x130_0x13f[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR5FR;              /* GICT_ERR5FR */
    volatile uint64_t GICT_ERR5CTLR;            /* GICT_ERR5CTLR */
    volatile uint64_t GICT_ERR5STATUS;          /* GICT_ERR5STATUS */
    volatile uint32_t _pad_0x158_0x15f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR5MISC0;           /* GICT_ERR5MISC0 */
    volatile uint64_t GICT_ERR5MISC1;           /* GICT_ERR5MISC1 */
    volatile uint32_t _pad_0x170_0x17f[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR6FR;              /* GICT_ERR6FR */
    volatile uint64_t GICT_ERR6CTLR;            /* GICT_ERR6CTLR */
    volatile uint64_t GICT_ERR6STATUS;          /* GICT_ERR6STATUS */
    volatile uint32_t _pad_0x198_0x19f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR6MISC0;           /* GICT_ERR6MISC0 */
    volatile uint64_t GICT_ERR6MISC1;           /* GICT_ERR6MISC1 */
    volatile uint32_t _pad_0x1b0_0x1bf[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR7FR;              /* GICT_ERR7FR */
    volatile uint64_t GICT_ERR7CTLR;            /* GICT_ERR7CTLR */
    volatile uint64_t GICT_ERR7STATUS;          /* GICT_ERR7STATUS */
    volatile uint32_t _pad_0x1d8_0x1df[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR7MISC0;           /* GICT_ERR7MISC0 */
    volatile uint64_t GICT_ERR7MISC1;           /* GICT_ERR7MISC1 */
    volatile uint32_t _pad_0x1f0_0x1ff[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR8FR;              /* GICT_ERR8FR */
    volatile uint64_t GICT_ERR8CTLR;            /* GICT_ERR8CTLR */
    volatile uint64_t GICT_ERR8STATUS;          /* GICT_ERR8STATUS */
    volatile uint32_t _pad_0x218_0x21f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR8MISC0;           /* GICT_ERR8MISC0 */
    volatile uint64_t GICT_ERR8MISC1;           /* GICT_ERR8MISC1 */
    volatile uint32_t _pad_0x230_0x23f[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR9FR;              /* GICT_ERR9FR */
    volatile uint64_t GICT_ERR9CTLR;            /* GICT_ERR9CTLR */
    volatile uint64_t GICT_ERR9STATUS;          /* GICT_ERR9STATUS */
    volatile uint32_t _pad_0x258_0x25f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR9MISC0;           /* GICT_ERR9MISC0 */
    volatile uint64_t GICT_ERR9MISC1;           /* GICT_ERR9MISC1 */
    volatile uint32_t _pad_0x270_0x27f[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR10FR;             /* GICT_ERR10FR */
    volatile uint64_t GICT_ERR10CTLR;           /* GICT_ERR10CTLR */
    volatile uint64_t GICT_ERR10STATUS;         /* GICT_ERR10STATUS */
    volatile uint32_t _pad_0x298_0x29f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR10MISC0;          /* GICT_ERR10MISC0 */
    volatile uint64_t GICT_ERR10MISC1;          /* GICT_ERR10MISC1 */
    volatile uint32_t _pad_0x2b0_0x2bf[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR11FR;             /* GICT_ERR11FR */
    volatile uint64_t GICT_ERR11CTLR;           /* GICT_ERR11CTLR */
    volatile uint64_t GICT_ERR11STATUS;         /* GICT_ERR11STATUS */
    volatile uint32_t _pad_0x2d8_0x2df[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR11MISC0;          /* GICT_ERR11MISC0 */
    volatile uint64_t GICT_ERR11MISC1;          /* GICT_ERR11MISC1 */
    volatile uint32_t _pad_0x2f0_0x2ff[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR12FR;             /* GICT_ERR12FR */
    volatile uint64_t GICT_ERR12CTLR;           /* GICT_ERR12CTLR */
    volatile uint64_t GICT_ERR12STATUS;         /* GICT_ERR12STATUS */
    volatile uint32_t _pad_0x318_0x31f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR12MISC0;          /* GICT_ERR12MISC0 */
    volatile uint64_t GICT_ERR12MISC1;          /* GICT_ERR12MISC1 */
    volatile uint32_t _pad_0x330_0x33f[4];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR13FR;             /* GICT_ERR13FR */
    volatile uint64_t GICT_ERR13CTLR;           /* GICT_ERR13CTLR */
    volatile uint64_t GICT_ERR13STATUS;         /* GICT_ERR13STATUS */
    volatile uint32_t _pad_0x358_0x35f[2];      /* *UNDEFINED* */
    volatile uint64_t GICT_ERR13MISC0;          /* GICT_ERR13MISC0 */
    volatile uint64_t GICT_ERR13MISC1;          /* GICT_ERR13MISC1 */
    volatile uint32_t _pad_0x370_0xdfff[14116]; /* *UNDEFINED* */
    volatile uint64_t GICT_ERRGSR0;             /* GICT_ERRGSR0 */
    volatile uint32_t _pad_0xe008_0xe7ff[510];  /* *UNDEFINED* */
    volatile uint64_t GICT_ERRIRQCR0;           /* GICT_ERRIRQCR0 */
    volatile uint64_t GICT_ERRIRQCR1;           /* GICT_ERRIRQCR1 */
    volatile uint32_t _pad_0xe810_0xffbb[1515]; /* *UNDEFINED* */
    volatile uint32_t GICT_DEVARCH;             /* GICT_DEVARCH */
    volatile uint32_t _pad_0xffc0_0xffc7[2];    /* *UNDEFINED* */
    volatile uint32_t GICT_DEVID;               /* GICT_DEVID */
    volatile uint32_t _pad_0xffcc_0xffcf;       /* *UNDEFINED* */
    volatile uint32_t GICT_PIDR4;               /* GICT_PIDR4 */
    volatile uint32_t GICT_PIDR5;               /* GICT_PIDR5 */
    volatile uint32_t GICT_PIDR6;               /* GICT_PIDR6 */
    volatile uint32_t GICT_PIDR7;               /* GICT_PIDR7 */
    volatile uint32_t GICT_PIDR0;               /* GICT_PIDR0 */
    volatile uint32_t GICT_PIDR1;               /* GICT_PIDR1 */
    volatile uint32_t GICT_PIDR2;               /* GICT_PIDR2 */
    volatile uint32_t GICT_PIDR3;               /* GICT_PIDR3 */
    volatile uint32_t GICT_CIDR0;               /* GICT_CIDR0 */
    volatile uint32_t GICT_CIDR1;               /* GICT_CIDR1 */
    volatile uint32_t GICT_CIDR2;               /* GICT_CIDR2 */
    volatile uint32_t GICT_CIDR3;               /* GICT_CIDR3 */
} arm_gict_regs_t;

// arm_gicp_regs_t -- GIC Performance Monitoring Unit Registers
typedef struct {
    volatile uint32_t GICP_EVCNTR0;               /* GICP_EVCNTR0 */
    volatile uint32_t GICP_EVCNTR1;               /* GICP_EVCNTR1 */
    volatile uint32_t GICP_EVCNTR2;               /* GICP_EVCNTR2 */
    volatile uint32_t GICP_EVCNTR3;               /* GICP_EVCNTR3 */
    volatile uint32_t GICP_EVCNTR4;               /* GICP_EVCNTR4 */
    volatile uint32_t _pad_0x14_0x3ff[251];       /* *UNDEFINED* */
    volatile uint32_t GICP_EVTYPER0;              /* GICP_EVTYPER0 */
    volatile uint32_t GICP_EVTYPER1;              /* GICP_EVTYPER1 */
    volatile uint32_t GICP_EVTYPER2;              /* GICP_EVTYPER2 */
    volatile uint32_t GICP_EVTYPER3;              /* GICP_EVTYPER3 */
    volatile uint32_t GICP_EVTYPER4;              /* GICP_EVTYPER4 */
    volatile uint32_t _pad_0x414_0x5ff[123];      /* *UNDEFINED* */
    volatile uint32_t GICP_SVR0;                  /* GICP_SVR0 */
    volatile uint32_t GICP_SVR1;                  /* GICP_SVR1 */
    volatile uint32_t GICP_SVR2;                  /* GICP_SVR2 */
    volatile uint32_t GICP_SVR3;                  /* GICP_SVR3 */
    volatile uint32_t GICP_SVR4;                  /* GICP_SVR4 */
    volatile uint32_t _pad_0x614_0x9ff[251];      /* *UNDEFINED* */
    volatile uint32_t GICP_FR0;                   /* GICP_FR0 */
    volatile uint32_t GICP_FR1;                   /* GICP_FR1 */
    volatile uint32_t GICP_FR2;                   /* GICP_FR2 */
    volatile uint32_t GICP_FR3;                   /* GICP_FR3 */
    volatile uint32_t GICP_FR4;                   /* GICP_FR4 */
    volatile uint32_t _pad_0xa14_0xbff[123];      /* *UNDEFINED* */
    volatile uint64_t GICP_CNTENSET0;             /* GICP_CNTENSET0 */
    volatile uint32_t _pad_0xc08_0xc1f[6];        /* *UNDEFINED* */
    volatile uint64_t GICP_CNTENCLR0;             /* GICP_CNTENCLR0 */
    volatile uint32_t _pad_0xc28_0xc3f[6];        /* *UNDEFINED* */
    volatile uint64_t GICP_INTENSET0;             /* GICP_INTENSET0 */
    volatile uint32_t _pad_0xc48_0xc5f[6];        /* *UNDEFINED* */
    volatile uint64_t GICP_INTENCLR0;             /* GICP_INTENCLR0 */
    volatile uint32_t _pad_0xc68_0xc7f[6];        /* *UNDEFINED* */
    volatile uint64_t GICP_OVSCLR0;               /* GICP_OVSCLR0 */
    volatile uint32_t _pad_0xc88_0xcbf[14];       /* *UNDEFINED* */
    volatile uint64_t GICP_OVSSET0;               /* GICP_OVSSET0 */
    volatile uint32_t _pad_0xcc8_0xd87[48];       /* *UNDEFINED* */
    volatile uint32_t GICP_CAPR;                  /* GICP_CAPR */
    volatile uint32_t _pad_0xd8c_0xdff[29];       /* *UNDEFINED* */
    volatile uint32_t GICP_CFGR;                  /* GICP_CFGR */
    volatile uint32_t GICP_CR;                    /* GICP_CR */
    volatile uint32_t _pad_0xe08_0xe4f[18];       /* *UNDEFINED* */
    volatile uint32_t GICP_IRQCR;                 /* GICP_IRQCR */
    volatile uint32_t _pad_0xe54_0xfb7[89];       /* *UNDEFINED* */
    volatile uint32_t GICP_PMAUTHSTATUS;          /* GICP_PMAUTHSTATUS */
    volatile uint32_t GICP_PMDEVARCH;             /* GICP_PMDEVARCH */
    volatile uint32_t _pad_0xfc0_0xfcb[3];        /* *UNDEFINED* */
    volatile uint32_t GICP_PMDEVTYPE;             /* GICP_PMDEVTYPE */
    volatile uint32_t GICP_PIDR4;                 /* GICP_PIDR4 */
    volatile uint32_t GICP_PIDR5;                 /* GICP_PIDR5 */
    volatile uint32_t GICP_PIDR6;                 /* GICP_PIDR6 */
    volatile uint32_t GICP_PIDR7;                 /* GICP_PIDR7 */
    volatile uint32_t GICP_PIDR0;                 /* GICP_PIDR0 */
    volatile uint32_t GICP_PIDR1;                 /* GICP_PIDR1 */
    volatile uint32_t GICP_PIDR2;                 /* GICP_PIDR2 */
    volatile uint32_t GICP_PIDR3;                 /* GICP_PIDR3 */
    volatile uint32_t GICP_CIDR0;                 /* GICP_CIDR0 */
    volatile uint32_t GICP_CIDR1;                 /* GICP_CIDR1 */
    volatile uint32_t GICP_CIDR2;                 /* GICP_CIDR2 */
    volatile uint32_t GICP_CIDR3;                 /* GICP_CIDR3 */
    volatile uint32_t _pad_0x1000_0x10000[15360]; /* *UNDEFINED* */
} arm_gicp_regs_t;

// arm_gits0_regs_t -- GIC Interrupt Translation Service Registers
typedef struct {
    volatile uint32_t GITS0_CTLR;               /* GITS0_CTLR */
    volatile uint32_t GITS0_IIDR;               /* GITS0_IIDR */
    volatile uint64_t GITS0_TYPER;              /* GITS0_TYPER */
    volatile uint32_t _pad_0x10_0x1f[4];        /* *UNDEFINED* */
    volatile uint32_t GITS0_FCTLR;              /* GITS0_FCTLR */
    volatile uint32_t _pad_0x24_0x27;           /* *UNDEFINED* */
    volatile uint64_t GITS0_OPR;                /* GITS0_OPR */
    volatile uint64_t GITS0_OPSR;               /* GITS0_OPSR */
    volatile uint32_t _pad_0x38_0x7f[18];       /* *UNDEFINED* */
    volatile uint64_t GITS0_CBASER;             /* GITS0_CBASER */
    volatile uint64_t GITS0_CWRITER;            /* GITS0_CWRITER */
    volatile uint64_t GITS0_CREADR;             /* GITS0_CREADR */
    volatile uint32_t _pad_0x98_0xff[26];       /* *UNDEFINED* */
    volatile uint64_t GITS0_BASER0;             /* GITS0_BASER0 */
    volatile uint64_t GITS0_BASER1;             /* GITS0_BASER1 */
    volatile uint32_t _pad_0x110_0xefff[15292]; /* *UNDEFINED* */
    volatile uint32_t GITS0_CFGID;              /* GITS0_CFGID */
    volatile uint32_t _pad_0xf004_0xffcf[1011]; /* *UNDEFINED* */
    volatile uint32_t GITS0_PIDR4;              /* GITS0_PIDR4 */
    volatile uint32_t GITS0_PIDR5;              /* GITS0_PIDR5 */
    volatile uint32_t GITS0_PIDR6;              /* GITS0_PIDR6 */
    volatile uint32_t GITS0_PIDR7;              /* GITS0_PIDR7 */
    volatile uint32_t GITS0_PIDR0;              /* GITS0_PIDR0 */
    volatile uint32_t GITS0_PIDR1;              /* GITS0_PIDR1 */
    volatile uint32_t GITS0_PIDR2;              /* GITS0_PIDR2 */
    volatile uint32_t GITS0_PIDR3;              /* GITS0_PIDR3 */
    volatile uint32_t GITS0_CIDR0;              /* GITS0_CIDR0 */
    volatile uint32_t GITS0_CIDR1;              /* GITS0_CIDR1 */
    volatile uint32_t GITS0_CIDR2;              /* GITS0_CIDR2 */
    volatile uint32_t GITS0_CIDR3;              /* GITS0_CIDR3 */
} arm_gits0_regs_t;

// arm_gits0_translater_regs_t -- GIC Interrupt Translation Service Translater Registers
typedef struct {
    volatile uint32_t _pad_0x0_0x3f[16]; /* *UNDEFINED* */
    volatile uint32_t GITS0_TRANSLATER;  /* GITS0_TRANSLATER */
} arm_gits0_translater_regs_t;

// arm_gicrlpi_regs_t -- GIC Redistributor Locality Specific Interrupt Controller Registers
typedef struct {
    volatile uint32_t GICR0_CTLR;              /* GICR0_CTLR */
    volatile uint32_t GICR0_IIDR;              /* GICR0_IIDR */
    volatile uint64_t GICR0_TYPER;             /* GICR0_TYPER */
    volatile uint32_t _pad_0x10_0x13;          /* *UNDEFINED* */
    volatile uint32_t GICR0_WAKER;             /* GICR0_WAKER */
    volatile uint32_t _pad_0x18_0x1f[2];       /* *UNDEFINED* */
    volatile uint32_t GICR0_FCTLR;             /* GICR0_FCTLR */
    volatile uint32_t GICR0_PWRR;              /* GICR0_PWRR */
    volatile uint32_t GICR0_CLASS;             /* GICR0_CLASS */
    volatile uint32_t _pad_0x2c_0x6f[17];      /* *UNDEFINED* */
    volatile uint64_t GICR0_PROPBASER;         /* GICR0_PROPBASER */
    volatile uint64_t GICR0_PENDBASER;         /* GICR0_PENDBASER */
    volatile uint32_t _pad_0x80_0xffcf[16340]; /* *UNDEFINED* */
    volatile uint32_t GICR0_PIDR4;             /* GICR0_PIDR4 */
    volatile uint32_t GICR0_PIDR5;             /* GICR0_PIDR5 */
    volatile uint32_t GICR0_PIDR6;             /* GICR0_PIDR6 */
    volatile uint32_t GICR0_PIDR7;             /* GICR0_PIDR7 */
    volatile uint32_t GICR0_PIDR0;             /* GICR0_PIDR0 */
    volatile uint32_t GICR0_PIDR1;             /* GICR0_PIDR1 */
    volatile uint32_t GICR0_PIDR2;             /* GICR0_PIDR2 */
    volatile uint32_t GICR0_PIDR3;             /* GICR0_PIDR3 */
    volatile uint32_t GICR0_CIDR0;             /* GICR0_CIDR0 */
    volatile uint32_t GICR0_CIDR1;             /* GICR0_CIDR1 */
    volatile uint32_t GICR0_CIDR2;             /* GICR0_CIDR2 */
    volatile uint32_t GICR0_CIDR3;             /* GICR0_CIDR3 */
} arm_gicr_lpi_regs_t;

// arm_gicrsgi_regs_t -- GIC Software Generated Interrupt Registers
typedef struct {
    volatile uint32_t _pad_0x0_0x7f[32];         /* *UNDEFINED* */
    volatile uint32_t GICR0_IGROUPR0;            /* GICR0_IGROUPR0 */
    volatile uint32_t _pad_0x84_0xff[31];        /* *UNDEFINED* */
    volatile uint32_t GICR0_ISENABLER0;          /* GICR0_ISENABLER0 */
    volatile uint32_t _pad_0x104_0x17f[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_ICENABLER0;          /* GICR0_ICENABLER0 */
    volatile uint32_t _pad_0x184_0x1ff[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_ISPENDR0;            /* GICR0_ISPENDR0 */
    volatile uint32_t _pad_0x204_0x27f[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_ICPENDR0;            /* GICR0_ICPENDR0 */
    volatile uint32_t _pad_0x284_0x2ff[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_ISACTIVER0;          /* GICR0_ISACTIVER0 */
    volatile uint32_t _pad_0x304_0x37f[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_ICACTIVER0;          /* GICR0_ICACTIVER0 */
    volatile uint32_t _pad_0x384_0x3ff[31];      /* *UNDEFINED* */
    volatile uint32_t GICR0_IPRIORITYR0;         /* GICR0_IPRIORITYR0 */
    volatile uint32_t GICR0_IPRIORITYR1;         /* GICR0_IPRIORITYR1 */
    volatile uint32_t GICR0_IPRIORITYR2;         /* GICR0_IPRIORITYR2 */
    volatile uint32_t GICR0_IPRIORITYR3;         /* GICR0_IPRIORITYR3 */
    volatile uint32_t GICR0_IPRIORITYR4;         /* GICR0_IPRIORITYR4 */
    volatile uint32_t GICR0_IPRIORITYR5;         /* GICR0_IPRIORITYR5 */
    volatile uint32_t GICR0_IPRIORITYR6;         /* GICR0_IPRIORITYR6 */
    volatile uint32_t GICR0_IPRIORITYR7;         /* GICR0_IPRIORITYR7 */
    volatile uint32_t _pad_0x420_0xbff[504];     /* *UNDEFINED* */
    volatile uint32_t GICR0_ICFGR0;              /* GICR0_ICFGR0 */
    volatile uint32_t GICR0_ICFGR1;              /* GICR0_ICFGR1 */
    volatile uint32_t _pad_0xc08_0xcff[62];      /* *UNDEFINED* */
    volatile uint32_t GICR0_IGRPMODR0;           /* GICR0_IGRPMODR0 */
    volatile uint32_t _pad_0xd04_0xdff[63];      /* *UNDEFINED* */
    volatile uint32_t GICR0_NSACR;               /* GICR0_NSACR */
    volatile uint32_t _pad_0xe04_0xbfff[11391];  /* *UNDEFINED* */
    volatile uint32_t GICR0_MISCSTATUSR;         /* GICR0_MISCSTATUSR */
    volatile uint32_t _pad_0xc004_0xc007;        /* *UNDEFINED* */
    volatile uint32_t GICR0_IERRVR;              /* GICR0_IERRVR */
    volatile uint32_t _pad_0xc00c_0xc00f;        /* *UNDEFINED* */
    volatile uint64_t GICR0_SGIDR;               /* GICR0_SGIDR */
    volatile uint32_t _pad_0xc018_0xefff[3066];  /* *UNDEFINED* */
    volatile uint32_t GICR0_CFGID0;              /* GICR0_CFGID0 */
    volatile uint32_t GICR0_CFGID1;              /* GICR0_CFGID1 */
    volatile uint32_t _pad_0xf008_0x10000[1022]; /* *UNDEFINED* */
} arm_gicr_sgi_regs_t;

#endif // GIC_REGS_H
