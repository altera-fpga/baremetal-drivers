#ifndef SDMMC_REGS_H__
#define SDMMC_REGS_H__

/*
 * SDMMC Documentation Overview
 *  -- Register Map
 *     -- "i_sdmmc__sdmmc_apb_slv__10808000"
 *  -- High-Level Architecture Specification
 *     --  "SM HPS SDMMC Controller HAS 1.1.pdf"
 */

// Base memory address for WDT access
#define SDMMC_BASE (0x10808000)
#define SDMMC_HRS_OFST (0x0)
#define SDMMC_SRS_OFST (0x200)
#define SDMMC_CRS_OFST (0x2FC)
#define SDMMC_CQRS_OFST (0x400)

#define SDMMC_HRS_HRS00_SWR_SET_OFST (uint32_t)0
#define SDMMC_HRS_HRS00_SWR_SET_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS00_SWR_SET_OFST)
#define SDMMC_HRS_HRS08_PHY_DLL_UPDREQ_OFST (uint32_t)0
#define SDMMC_HRS_HRS08_PHY_DLL_UPDREQ_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS08_PHY_DLL_UPDREQ_OFST)
#define SDMMC_HRS_HRS09_PHY_SW_RESET_OFST (uint32_t)0
#define SDMMC_HRS_HRS09_PHY_SW_RESET_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS09_PHY_SW_RESET_OFST)
#define SDMMC_HRS_HRS09_EXTENDED_RD_MODE_OFST (uint32_t)2
#define SDMMC_HRS_HRS09_EXTENDED_RD_MODE_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS09_EXTENDED_RD_MODE_OFST)
#define SDMMC_HRS_HRS09_EXTENDED_WR_MODE_OFST (uint32_t)3
#define SDMMC_HRS_HRS09_EXTENDED_WR_MODE_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS09_EXTENDED_WR_MODE_OFST)
#define SDMMC_HRS_HRS09_RDCMD_EN_OFST (uint32_t)15
#define SDMMC_HRS_HRS09_RDCMD_EN_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS09_RDCMD_EN_OFST)
#define SDMMC_HRS_HRS09_RDDATA_EN_OFST (uint32_t)16
#define SDMMC_HRS_HRS09_RDDATA_EN_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS09_RDDATA_EN_OFST)
#define SDMMC_HRS_HRS09_LVSI_TCKSEL_OFST (uint32_t)22
#define SDMMC_HRS_HRS09_LVSI_TCKSEL_MASK (uint32_t)((uint32_t)0x3f << SDMMC_HRS_HRS09_LVSI_TCKSEL_OFST)
#define SDMMC_HRS_HRS09_LVSI_CNT_OFST (uint32_t)28
#define SDMMC_HRS_HRS09_LVSI_CNT_MASK (uint32_t)((uint32_t)0xf << SDMMC_HRS_HRS09_LVSI_CNT_OFST)
#define SDMMC_HRS_HRS32_ADDR_OFST (uint32_t)16
#define SDMMC_HRS_HRS32_ADDR_MASK (uint32_t)((uint32_t)0x7fff << SDMMC_HRS_HRS32_ADDR_OFST)
#define SDMMC_HRS_HRS32_LOAD_OFST (uint32_t)31
#define SDMMC_HRS_HRS32_LOAD_MASK (uint32_t)((uint32_t)1 << SDMMC_HRS_HRS32_LOAD_OFST)
#define SDMMC_SRS_SRS11_ICE_OFST (uint32_t)0
#define SDMMC_SRS_SRS11_ICE_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS11_ICE_OFST)
#define SDMMC_SRS_SRS11_SDCE_OFST (uint32_t)2
#define SDMMC_SRS_SRS11_SDCE_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS11_SDCE_OFST)
#define SDMMC_SRS_SRS11_SDCFSH_OFST (uint32_t)6
#define SDMMC_SRS_SRS11_SDCFSH_MASK (uint32_t)((uint32_t)0x3 << SDMMC_SRS_SRS11_SDCFSH_OFST)
#define SDMMC_SRS_SRS11_SDCFSL_OFST (uint32_t)8
#define SDMMC_SRS_SRS11_SDCFSL_MASK (uint32_t)((uint32_t)0xff << SDMMC_SRS_SRS11_SDCFSL_OFST)
#define SDMMC_SRS_SRS11_DTCV_OFST (uint32_t)16
#define SDMMC_SRS_SRS11_DTCV_MASK (uint32_t)((uint32_t)0xf << SDMMC_SRS_SRS11_DTCV_OFST)
#define SDMMC_SRS_SRS11_SRFA_OFST (uint32_t)24
#define SDMMC_SRS_SRS11_SRFA_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS11_SRFA_OFST)
#define SDMMC_SRS_SRS11_SRCMD_OFST (uint32_t)25
#define SDMMC_SRS_SRS11_SRCMD_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS11_SRCMD_OFST)
#define SDMMC_SRS_SRS11_SRDAT_OFST (uint32_t)26
#define SDMMC_SRS_SRS11_SRDAT_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS11_SRDAT_OFST)
#define SDMMC_SRS_SRS15_UMS_OFST (uint32_t)16
#define SDMMC_SRS_SRS15_UMS_MASK (uint32_t)((uint32_t)0x7 << SDMMC_SRS_SRS15_UMS_OFST)
#define SDMMC_SRS_SRS15_V18SE_OFST (uint32_t)19
#define SDMMC_SRS_SRS15_V18SE_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_V18SE_OFST)
#define SDMMC_SRS_SRS15_DSS_OFST (uint32_t)20
#define SDMMC_SRS_SRS15_DSS_MASK (uint32_t)((uint32_t)0x3 << SDMMC_SRS_SRS15_DSS_OFST)
#define SDMMC_SRS_SRS15_EXTNG_OFST (uint32_t)22
#define SDMMC_SRS_SRS15_EXTNG_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_EXTNG_OFST)
#define SDMMC_SRS_SRS15_SCS_OFST (uint32_t)23
#define SDMMC_SRS_SRS15_SCS_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_SCS_OFST)
#define SDMMC_SRS_SRS15_LVSIEXEC_OFST (uint32_t)24
#define SDMMC_SRS_SRS15_LVSIEXEC_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_LVSIEXEC_OFST)
#define SDMMC_SRS_SRS15_ADMA2LM_OFST (uint32_t)26
#define SDMMC_SRS_SRS15_ADMA2LM_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_ADMA2LM_OFST)
#define SDMMC_SRS_SRS15_CMD23E_OFST (uint32_t)27
#define SDMMC_SRS_SRS15_CMD23E_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_CMD23E_OFST)
#define SDMMC_SRS_SRS15_HV4E_OFST (uint32_t)28
#define SDMMC_SRS_SRS15_HV4E_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_HV4E_OFST)
#define SDMMC_SRS_SRS15_A64B_OFST (uint32_t)29
#define SDMMC_SRS_SRS15_A64B_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_A64B_OFST)
#define SDMMC_SRS_SRS15_PVE_OFST (uint32_t)31
#define SDMMC_SRS_SRS15_PVE_MASK (uint32_t)((uint32_t)1 << SDMMC_SRS_SRS15_PVE_OFST)
#define SDMMC_CQRS_CQRS07_CQICTOVAL_OFST (uint32_t)0
#define SDMMC_CQRS_CQRS07_CQICTOVAL_MASK (uint32_t)((uint32_t)0x7f << SDMMC_CQRS_CQRS07_CQICTOVAL_OFST)
#define SDMMC_CQRS_CQRS07_CQICTOVALEN_OFST (uint32_t)7
#define SDMMC_CQRS_CQRS07_CQICTOVALEN_MASK (uint32_t)((uint32_t)1 << SDMMC_CQRS_CQRS07_CQICTOVALEN_OFST)
#define SDMMC_CQRS_CQRS07_CQICCTH_OFST (uint32_t)8
#define SDMMC_CQRS_CQRS07_CQICCTH_MASK (uint32_t)((uint32_t)0x1f << SDMMC_CQRS_CQRS07_CQICCTH_OFST)
#define SDMMC_CQRS_CQRS07_CQICCTHWEN_OFST (uint32_t)15
#define SDMMC_CQRS_CQRS07_CQICCTHWEN_MASK (uint32_t)((uint32_t)1 << SDMMC_CQRS_CQRS07_CQICCTHWEN_OFST)
#define SDMMC_CQRS_CQRS07_CQICCTR_OFST (uint32_t)16
#define SDMMC_CQRS_CQRS07_CQICCTR_MASK (uint32_t)((uint32_t)1 << SDMMC_CQRS_CQRS07_CQICCTR_OFST)
#define SDMMC_CQRS_CQRS07_CQICED_OFST (uint32_t)31
#define SDMMC_CQRS_CQRS07_CQICED_MASK (uint32_t)((uint32_t)1 << SDMMC_CQRS_CQRS07_CQICED_OFST)

/*
 * structure yielding access to sdmmc HRS parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t HRS00;      // Offset 0x00
    volatile uint32_t HRS01;      // Offset 0x04
    volatile uint32_t HRS02;      // Offset 0x08
    volatile uint32_t HRS03;      // Offset 0x0C
    volatile uint32_t HRS04;      // Offset 0x10
    volatile uint32_t HRS05;      // Offset 0x14
    volatile uint32_t HRS06;      // Offset 0x18
    volatile uint32_t HRS07;      // Offset 0x1C
    volatile uint32_t HRS08;      // Offset 0x20
    volatile uint32_t HRS09;      // Offset 0x24
    volatile uint32_t HRS10;      // Offset 0x28
    volatile uint32_t HRS11;      // offset 0x2C
    volatile uint32_t HRS12;      // Offset 0x30
    volatile uint32_t HRS13;      // Offset 0x34
    volatile uint32_t HRS14;      // Offset 0x38
    volatile uint32_t _pad_0;     /* *UNDEFINED* */
    volatile uint32_t HRS16;      // Offset 0x40
    volatile uint32_t _pad_1[12]; /* *UNDEFINED* */
    volatile uint32_t HRS29;      // Offset 0x74
    volatile uint32_t HRS30;      // Offset 0x78
    volatile uint32_t HRS31;      // Offset 0x7C
    volatile uint32_t HRS32;      // Offset 0x80
    volatile uint32_t HRS33;      // Offset 0x84
    volatile uint32_t HRS34;      // Offset 0x88
} sdmmc_hrs_regs_words_t;

/*
 * structure yielding access to sdmmc SRS parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t SRS00;     // Offset 0x00
    volatile uint32_t SRS01;     // Offset 0x04
    volatile uint32_t SRS02;     // Offset 0x08
    volatile uint32_t SRS03;     // Offset 0x0C
    volatile uint32_t SRS04;     // Offset 0x10
    volatile uint32_t SRS05;     // Offset 0x14
    volatile uint32_t SRS06;     // Offset 0x18
    volatile uint32_t SRS07;     // Offset 0x1C
    volatile uint32_t SRS08;     // Offset 0x20
    volatile uint32_t SRS09;     // Offset 0x24
    volatile uint32_t SRS10;     // Offset 0x28
    volatile uint32_t SRS11;     // Offset 0x2C
    volatile uint32_t SRS12;     // Offset 0x30
    volatile uint32_t SRS13;     // Offset 0x34
    volatile uint32_t SRS14;     // Offset 0x38
    volatile uint32_t SRS15;     // Offset 0x3C
    volatile uint32_t SRS16;     // Offset 0x40
    volatile uint32_t SRS17;     // Offset 0x44
    volatile uint32_t SRS18;     // Offset 0x48
    volatile uint32_t SRS19;     // Offset 0x4C
    volatile uint32_t SRS20;     // Offset 0x50
    volatile uint32_t SRS21;     // Offset 0x54
    volatile uint32_t SRS22;     // Offset 0x58
    volatile uint32_t SRS23;     // Offset 0x5C
    volatile uint32_t SRS24;     // Offset 0x60
    volatile uint32_t SRS25;     // Offset 0x64
    volatile uint32_t SRS26;     // Offset 0x68
    volatile uint32_t SRS27;     // Offset 0x6C
    volatile uint32_t _pad_0[2]; /* *UNDEFINED* */
    volatile uint32_t SRS30;     // Offset 0x78
    volatile uint32_t SRS31;     // Offset 0x7C
} sdmmc_srs_regs_words_t;

/*
 * structure yielding access to sdmmc CRS parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t CRS63; // Offset 0x00
} sdmmc_crs_regs_words_t;

/*
 * structure yielding access to sdmmc CQRS parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t CQRS00; // Offset 0x00
    volatile uint32_t CQRS01; // Offset 0x04
    volatile uint32_t CQRS02; // Offset 0x08
    volatile uint32_t CQRS03; // Offset 0x0C
    volatile uint32_t CQRS04; // Offset 0x10
    volatile uint32_t CQRS05; // Offset 0x14
    volatile uint32_t CQRS06; // Offset 0x18
    volatile uint32_t CQRS07; // Offset 0x1C
    volatile uint32_t CQRS08; // Offset 0x20
    volatile uint32_t CQRS09; // Offset 0x24
    volatile uint32_t CQRS10; // Offset 0x28
    volatile uint32_t CQRS11; // Offset 0x2C
    volatile uint32_t CQRS12; // Offset 0x30
    volatile uint32_t CQRS13; // Offset 0x34
    volatile uint32_t CQRS14; // Offset 0x38
    volatile uint32_t _pad_0; /* *UNDEFINED* */
    volatile uint32_t CQRS16; // Offset 0x40
    volatile uint32_t CQRS17; // Offset 0x44
    volatile uint32_t CQRS18; // Offset 0x48
    volatile uint32_t _pad_1; /* *UNDEFINED* */
    volatile uint32_t CQRS20; // Offset 0x50
    volatile uint32_t CQRS21; // Offset 0x54
    volatile uint32_t CQRS22; // Offset 0x58
    volatile uint32_t CQRS23; // Offset 0x5C
} sdmmc_cqrs_regs_words_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    sdmmc_hrs_regs_words_t sdmmc_hrs_regs_words_s;
    sdmmc_srs_regs_words_t sdmmc_srs_regs_words_s;
    sdmmc_crs_regs_words_t sdmmc_crs_regs_words_s;
    sdmmc_cqrs_regs_words_t sdmmc_cqrs_regs_words_s;
} sdmmc_regs_t;

#endif // SDMMC_REGS_H__