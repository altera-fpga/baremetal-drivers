/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_smmu.h
 *
 * SMMU hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_SMMU__
#define __SOCFPGA_SMMU__

#include <stdint.h>

/* Section: Address Translation Mappings
 *
 * Text: SDM VA to PA Translation
 * Address Space: 512 MB | Granule: 4 KB
 *
 * Virtual Address (29 bits total)
 * +------------------------------+
 * | Bits  0-11  |  Granule Offset|  --> Ignored (4 KB pages)
 * +------------------------------+
 * | Bits 12-20  |  L1 Index (9b) |  --> 512 entries
 * +------------------------------+
 * | Bits 21-28  |  L0 Index (8b) |  --> 256 entries
 * +------------------------------+
 *
 * Flow:
 * +----------+      +----------+      +-------------------+
 * |   L0     |----->|   L1     |----->| Physical Address  |
 * |  Table   |      |  Table   |      |                   |
 * +----------+      +----------+      +-------------------+
 *
 * Text: Peripheral VA to PA Translation
 * Address Space: 1 TB | Granule: 4 KB
 *
 * Virtual Address (40 bits total)
 * +------------------------------+
 * | Bits  0-11  | Granule Offset |  --> Ignored (4 KB pages)
 * +------------------------------+
 * | Bits 12-20  |  2 MB Offset   |  --> Ignored (using 2 MB blocks)
 * +------------------------------+
 * | Bits 21-29  |  L2 Index (9b) |  --> 512 entries
 * +------------------------------+
 * | Bits 30-38  |  L1 Index (9b) |  --> 512 entries
 * +------------------------------+
 * | Bit   39    |  L0 Index (1b) |  --> 2 entries
 * +------------------------------+
 *
 * Flow:
 * +----------+      +----------+      +----------+      +-------------------+
 * |   L0     |----->|   L1     |----->|   L2     |----->|  Physical Address |
 * |  Table   |      |  Table   |      |  Table   |      |                   |
 * +----------+      +----------+      +----------+      +-------------------+
 *
 * L0 Table (2 entries):
 * [0]  0x0000_0000_00 to 0x7FFF_FFFF_FF (in use)
 * [1]  0x8000_0000_00 to 0xFFFF_FFFF_FF (unused)
 *
 * L1 Example Mappings:
 * [0]  device_mem
 * [1]  device_mem
 * [2]  normal_mem
 * [3]  device_mem
 *
 * Summary:
 * - 3-level page table walk
 * - L0: 2 entries, L1: 512 entries, L2: 512 entries
 * - 2 MB block mappings (21 LSBs ignored)
 */

/* Constants: SMMU stream IDs
 *
 * Stream IDs for SoC peripherals. smmu_enable programs one stream-table
 * entry for each ID from 1 through the maximum.
 *
 * SMMU_MAX_STREAM_ID  - Highest stream ID.
 * SMMU_STREAM_ID_NAND - Stream ID for NAND.
 * SMMU_STREAM_ID_SDMMC - Stream ID for SDMMC.
 * SMMU_STREAM_ID_DMA0 - Stream ID for DMA 0.
 * SMMU_STREAM_ID_DMA1 - Stream ID for DMA 1.
 * SMMU_STREAM_ID_SDM  - Stream ID for the SDM.
 */
#define SMMU_MAX_STREAM_ID    0xAU

#define SMMU_STREAM_ID_NAND     0x4
#define SMMU_STREAM_ID_SDMMC    0x5
#define SMMU_STREAM_ID_DMA0     0x8
#define SMMU_STREAM_ID_DMA1     0x9
#define SMMU_STREAM_ID_SDM      0xA


/* Struct: context_desc_t
 *
 * Represents an ARM SMMUv3 Context Descriptor (CD).
 *
 * This heavily packed, 64-byte aligned structure defines the Stage 1 memory 
 * translation regime for a specific peripheral or execution context. It configures 
 * the Translation Table Base Addresses (TTB0/TTB1), ASID, Translation Granules 
 * (TG0/TG1), memory attributes (MAIR), and fault handling behaviors.
 */
typedef struct __attribute__((aligned(64), packed))
{
    uint32_t T0SZ : 6;
    uint32_t TG0 : 2;
    uint32_t IR0 : 2;
    uint32_t OR0 : 2;
    uint32_t SH0 : 2;
    uint32_t EPD0 : 1;
    uint32_t ENDI : 1;
    uint32_t T1SZ : 6;
    uint32_t TG1 : 2;
    uint32_t IR1 : 2;
    uint32_t OR1 : 2;
    uint32_t SH1 : 2;
    uint32_t EPD1 : 1;
    uint32_t V : 1;
    uint32_t IPS : 3;
    uint32_t AFFD : 1;
    uint32_t WXN : 1;
    uint32_t UWXN : 1;
    uint32_t TBI0 : 1;
    uint32_t TBI1 : 1;
    uint32_t PAN : 1;
    uint32_t AA64 : 1;
    uint32_t HD : 1;
    uint32_t HA : 1;
    uint32_t S : 1;
    uint32_t R : 1;
    uint32_t A : 1;
    uint32_t ASET : 1;
    uint32_t ASID : 16;
    uint32_t NSCFG0 : 1;
    uint32_t DisCH0 : 1;
    uint32_t E0PD0 : 1;
    uint32_t HAFT : 1;
    uint64_t TTB0 : 52;
    uint32_t RES0_0 : 2;
    uint32_t PnCH : 1;
    uint32_t EPAN : 1;
    uint32_t HWU059 : 1;
    uint32_t HWU060 : 1;
    uint32_t SKL0 : 2;
    uint32_t NSCFG1 : 1;
    uint32_t DisCH1 : 1;
    uint32_t E0PD1 : 1;
    uint32_t AIE : 1;
    uint64_t TTB1 : 52;
    uint32_t RES0_1 : 2;
    uint32_t DS : 1;
    uint32_t PIE : 1;
    uint32_t HWU159 : 1;
    uint32_t HWU160 : 1;
    uint32_t SKL1 : 2;
    uint32_t MAIR0 : 32;
    uint32_t MAIR1 : 32;
    uint32_t AMAIR0 : 32;
    uint32_t AMAIR1 : 32;
    uint32_t IMPL_DEFINED : 32;
    uint32_t PARTID : 16;
    uint32_t PMG : 8;
    uint32_t RES0_2 : 8;
    uint64_t PI1 : 64;
    uint64_t PI2 : 64;
} context_desc_t;

/* Struct: stream_table_t
 *
 * Represents an ARM SMMUv3 Stream Table Entry (STE).
 *
 * This 64-byte structure acts as the root of the configuration hierarchy for an 
 * incoming hardware transaction. Based on the incoming Stream ID, the SMMU looks 
 * up this STE to determine if the transaction should bypass translation, generate 
 * an abort, or proceed with Stage 1/Stage 2 translation. If Stage 1 is configured, 
 * the S1ContextPtr field points to the corresponding <context_desc_t>.
 */
typedef struct __attribute__((aligned(64), packed))
{
    uint64_t V : 1;
    uint64_t Config : 3;
    uint64_t S1Fmt : 2;
    uint64_t S1ContextPtr : 50;
    uint64_t RES0   : 3;
    uint64_t S1CDMax    : 5;
    uint64_t S1DSS  : 2;
    uint64_t S1CIR : 2;
    uint64_t S1COR : 2;
    uint64_t S1CSH : 2;
    uint64_t S2HWU59 : 1;
    uint64_t S2HWU60 : 1;
    uint64_t S2HWU61 : 1;
    uint64_t S2HWU62 : 1;
    uint64_t DRE : 1;
    uint64_t CONT : 4;
    uint64_t DCP : 1;
    uint64_t PPAR : 1;
    uint64_t MEV : 1;
    uint64_t SW_RESERVED : 4;
    uint64_t S1PIE : 1;
    uint64_t S2FWB : 1;
    uint64_t S1MPAM : 1;
    uint64_t S1STALLD : 1;
    uint64_t EATS : 2;
    uint64_t STRW : 2;
    uint64_t MemAttr : 4;
    uint64_t MTCFG : 1;
    uint64_t ALLOCCFG : 4;
    uint64_t RES0_1 : 3;
    uint64_t SHCFG : 2;
    uint64_t NSCFG : 2;
    uint64_t PRIVCFG : 2;
    uint64_t INSTCFG : 2;
    uint64_t IMP_DEFINED_0 : 12;
    uint64_t S2VMID : 16;
    uint64_t IMP_DEFINED_1 : 16;
    uint32_t S2_CONFIGS_0;
    uint64_t S2_CONFIGS_1;
    uint64_t S2_CONFIGS_2;
    uint64_t S2_CONFIGS_3;
    uint64_t S2_CONFIGS_4;
    uint64_t S2_CONFIGS_5;
} stream_table_t;

/* Struct: command_desc_t
 *
 * Represents an ARM SMMUv3 Command Queue entry.
 *
 * The SMMU Command Queue is a circular buffer residing in memory, used by software 
 * to issue instructions directly to the SMMU hardware. Each command is exactly 
 * 16 bytes (four 32-bit words). Typical commands include TLB invalidations 
 * (CMD_TLBI) and synchronization requests (CMD_SYNC).
 */
typedef struct __attribute__((aligned(8), packed))
{
    uint32_t W0;
    uint32_t W1;
    uint32_t W2;
    uint32_t W3;
} command_desc_t;

/* Struct: smmu_descriptors_t
 *
 * A master aggregation structure containing all in-memory tables required by the 
 * SMMUv3 controller.
 *
 * This massive structure holds the linear Stream Table, Context Descriptors, the 
 * Command Queue, Event Queue, and the fully populated multi-level translation 
 * page tables for both the 512MB (SDM) and 1TB (Peripheral) virtual address spaces. 
 * By defining this as a single struct, the driver ensures all required alignment 
 * boundaries (e.g., 4KB page bounds, 64-byte cache lines) are strictly honored by 
 * the linker during bare-metal instantiation.
 */
typedef struct
{
    stream_table_t stream_table[SMMU_MAX_STREAM_ID + 1U] __attribute__((aligned(64)));
    context_desc_t context_desc_1tb;
    context_desc_t context_desc_512mb;
    
    /* 5 Commands max allocated for bare-metal queue */
    command_desc_t command_desc[5U * sizeof(command_desc_t)] __attribute__((aligned(1024 * 1024)));
    uint64_t *event_queue;

    /* 512MB SDM Translation Page Tables */
    uint64_t lvl0_page_table_512mb[256] __attribute__((aligned(4096)));
    uint64_t lvl1_page_table_512mb[512][512] __attribute__((aligned(4096)));

    /* 1TB Peripheral Translation Page Tables */
    uint64_t lvl0_page_table_1tb[2] __attribute__((aligned(4096)));
    uint64_t lvl1_page_table_1tb[512] __attribute__((aligned(4096)));
    uint64_t lvl2_page_table_1tb[512] __attribute__((aligned(4096)));
} smmu_descriptors_t;


/* Function: smmu_enable
 *
 * Bootstraps and enables the SMMUv3 hardware controller. 
 *
 * This routine writes the base addresses of the pre-allocated Stream Table and 
 * Command Queue into the SMMU's memory-mapped registers (SMMU_STRTAB_BASE, 
 * SMMU_CMDQ_BASE). It configures the queue pointers (PROD/CONS) and finally sets 
 * the SMMU_CR0.SMMUEN bit to activate memory translation and protection on the bus.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the hardware fails to respond or 
 * validate the table pointers.
 */
int32_t smmu_enable(void);

/* Function: smmu_disable
 *
 * Safely halts the SMMUv3 controller.
 *
 * This function initiates an orderly teardown by draining any pending DMA 
 * transactions, pushing a CMD_SYNC into the command queue, and clearing the 
 * SMMU_CR0.SMMUEN bit to return the bus to a bypass/passthrough state.
 *
 * Returns:
 *
 * 0 on success; a negative error code if the hardware hangs during sync.
 */
int32_t smmu_disable(void);

/* Function: smmu_deinit
 *
 * Tears down the software context for the SMMU driver. This releases any allocated 
 * descriptors and resets the driver's internal tracking state, allowing the module 
 * to be safely reinitialized later if needed.
 *
 * Returns:
 *
 * 0 on success.
 */
int32_t smmu_deinit(void);

#endif /* __SOCFPGA_SMMU__ */