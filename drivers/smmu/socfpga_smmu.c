/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_smmu.c
 *
 * SMMU source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "errno.h"
#include "crt0.h"
#include "socfpga_smmu.h"
#include "socfpga_smmu_reg.h"
#include "cache.h"
#include "mmio.h"


/*####### SDM VA -> PA Translation ######
 * Address Space: 512 MB #### Granule Size:4 KB.
 * 29 bits required to represent 512 MB.
 * 4 KB -> 12 bits redundant.
 * 12 LSB ( 0 to 11 bits ) -> redundant.
 * ( 12 - 20 ) ( 9 bits -> 512 entries ) -> l1 table.
 * ( 21 - 28 ) ( 8 bits -> 256 entries ) -> l0 table.
 *
 * L0 Table -> 512 entries.
 * L1 Table -> 256 entries.
 * **/

/*####### Peripherals VA -> PA Translation ######
 * Address Space: 1 TB #### Granule Size:4 KB.
 * 40 bits required to represent 1 TB
 * 4 KB -> 12 bits redundant.
 * 12 + 9 bits redundant as we use 2 MB chunks.
 * (0 - 20)  (redundant)
 * (21 - 29) (9 bits -> 512 entries) -> l2 table.
 * (30 - 38) (9 bits -> 512 entries) -> l1 table.
 * (39) ( 1 bit ) -> l0 table.
 *
 * l0 has 2 entries ->
 * 0x0000000000 to 0x7FFFFFFFFF (area of interest)
 * 0x8000000000 to 0xFFFFFFFFFF (not used)
 *
 *  l1 has 512 entries
 *  l1[0] => device_mem
 *  l1[1] => device_mem
 *  l1[2] => normal_mem
 *  l1[3] => device_mem
 *
 *  l2 has 512 entries.
 */


/* the stream table points to corresponding context descriptor
 * page table base addresses are populated within context descriptor
 * Support for SDM
 *
 * Prepare command and event queue
 **/

#define ADDR_SPACE_SDM      0x80000000U
#define ADDR_SPACE_PER      0x80000000U
#define GRANULE_SIZE_4KB    0x1000U
#define OFFSET_SIZE_2MB     0x200000U

#define SDM_STREAM_ID        0xA
#define CMD_CFGI_STE         0x3
#define CMD_TLBI_NSNH_ALL    0x30
#define CMD_CFGI_CD_ALL      0x06
#define CMD_SYNC             0x46
#define CMD_COUNT            0x5
#define MAX_RETRY_COUNTER    100
#define SMMU_MEM_OFFSET_L1_IDX(x)    ((uint64_t)(x) << 30ULL)

/*Stream Table config*/
#define SMMU_EN_S1_TRANS       0x5
#define NORMAL_WB_NR_ALLOC     0x1
#define ENABLE_CONFIG          0x1
#define VALID_TABLE            0x1
#define INNER_SHAREABLE        0x3
#define NS_EL2                 0x2
#define EN_FULL_ATS            0x1
#define UNPRIVILEGED_ACCESS    0x2
#define SMMU_BYPASS_MODE       0x4

/*Context Descriptor config*/
#define T0SZ_1TB             24U
#define T0SZ_512MB           35U
#define GRANULUE_SIZE_4KB    0x0
#define USE_VMSAv8_64_FMT    0x1
#define DISABLE_AF           0x1
#define LVL_WALK_0           0x1
#define VALID_DESC           0x1


#define SMMU_OP_SUCCESS    0
#define SMMU_OP_FAIL       -1

static void smmu_prepare_context_1tb(void);
static void smmu_prepare_context_512mb(void);
static void smmu_prepare_stream_table(uint8_t index);
static void smmu_prepare_page_tables_512mb(void);
static void smmu_prepare_page_tables_1tb(void);
static int32_t enable_command_queue(void);
static int32_t smmu_manage_command_queue(void);
static int32_t enable_event_queue(void);

static smmu_descriptors_t smmu_descriptors;

static void smmu_prepare_context_1tb(void)
{
    smmu_descriptors.context_desc_1tb.T0SZ = T0SZ_1TB;
    smmu_descriptors.context_desc_1tb.TG0 = GRANULUE_SIZE_4KB;
    smmu_descriptors.context_desc_1tb.AA64 = USE_VMSAv8_64_FMT;
    smmu_descriptors.context_desc_1tb.AFFD = DISABLE_AF;
    smmu_descriptors.context_desc_1tb.DisCH0 = LVL_WALK_0;
    smmu_descriptors.context_desc_1tb.A = 0x1U;
    smmu_descriptors.context_desc_1tb.R = 0x1U;
    smmu_descriptors.context_desc_1tb.ASET = 0x1U;
    smmu_descriptors.context_desc_1tb.ASID = 0x1U;
    smmu_descriptors.context_desc_1tb.MAIR0 = ((uint32_t)0x44 << 8) |
            ((uint32_t)0xFF << 16);
    /*add the base address of lvl0 table*/
    smmu_descriptors.context_desc_1tb.TTB0 =
            ((uint64_t)smmu_descriptors.lvl0_page_table_1tb >> 4);
    smmu_descriptors.context_desc_1tb.V = VALID_DESC;

    cache_force_write_back(&smmu_descriptors.context_desc_1tb,
            sizeof(context_desc_t));
}

static void smmu_prepare_context_512mb(void)
{
    /*setting T0SZ as 35U : bits used = 64 - T0SZ*/
    smmu_descriptors.context_desc_512mb.T0SZ = T0SZ_512MB;
    smmu_descriptors.context_desc_512mb.TG0 = GRANULUE_SIZE_4KB;
    smmu_descriptors.context_desc_512mb.AA64 = USE_VMSAv8_64_FMT;
    smmu_descriptors.context_desc_512mb.AFFD = DISABLE_AF;
    smmu_descriptors.context_desc_512mb.A = 0x1U;
    smmu_descriptors.context_desc_512mb.R = 0x1U;
    smmu_descriptors.context_desc_512mb.ASET = 0x1U;
    smmu_descriptors.context_desc_512mb.ASID = 0x1U;
    smmu_descriptors.context_desc_512mb.DisCH0 = 0x1U;
    smmu_descriptors.context_desc_512mb.MAIR0 = ((uint32_t)0x44 << 8) |
            ((uint32_t)0xFF << 16);
    /*add the base address of lvl0 table*/
    smmu_descriptors.context_desc_512mb.TTB0 =
            ((uint64_t)smmu_descriptors.lvl0_page_table_512mb >> 4);
    /*setting the descriptor as valid*/
    smmu_descriptors.context_desc_512mb.V = VALID_DESC;
    cache_force_write_back(&smmu_descriptors.context_desc_512mb,
            sizeof(context_desc_t));
}

static void smmu_prepare_stream_table(uint8_t index)
{
    uint32_t reg_val = 0;

    smmu_descriptors.stream_table[index].S1CIR = NORMAL_WB_NR_ALLOC;
    smmu_descriptors.stream_table[index].S1COR = NORMAL_WB_NR_ALLOC;
    smmu_descriptors.stream_table[index].S1CSH = 0x3;
    smmu_descriptors.stream_table[index].EATS = EN_FULL_ATS;
    smmu_descriptors.stream_table[index].NSCFG = UNPRIVILEGED_ACCESS;
    smmu_descriptors.stream_table[index].S1STALLD = ENABLE_CONFIG;
    smmu_descriptors.stream_table[index].STRW = NS_EL2;
    smmu_descriptors.stream_table[index].SHCFG = 1;
    smmu_descriptors.stream_table[index].PRIVCFG = UNPRIVILEGED_ACCESS;
    smmu_descriptors.stream_table[index].V = VALID_TABLE;
    smmu_descriptors.stream_table[index].DRE = ENABLE_CONFIG;
    smmu_descriptors.stream_table[index].DCP = ENABLE_CONFIG;
    smmu_descriptors.stream_table[index].ALLOCCFG = 0xE;
    smmu_descriptors.stream_table[index].IMP_DEFINED_0 = 0xF;
    smmu_descriptors.stream_table[index].INSTCFG = 0x2;

    if ((index == 0xAU))
    {
        smmu_descriptors.stream_table[index].Config = SMMU_EN_S1_TRANS;
        smmu_descriptors.stream_table[index].S1ContextPtr =
                (uint64_t)&smmu_descriptors.context_desc_512mb >> 6;
    }
    else
    {
        smmu_descriptors.stream_table[index].Config = SMMU_BYPASS_MODE;
        smmu_descriptors.stream_table[index].S1ContextPtr =
                (uint64_t)&smmu_descriptors.context_desc_1tb >> 6;
    }
    cache_force_write_back(&smmu_descriptors.stream_table[index],
            sizeof(stream_table_t));

    reg_val = (uint32_t)((uintptr_t)smmu_descriptors.stream_table);
    WR_REG32(SMMU_BASE_ADDR + SMMU_STRTAB_BASE_LO, reg_val);
    WR_REG32(SMMU_BASE_ADDR + SMMU_STRTAB_BASE_HI,
            (uint32_t)1 << SMMU_STRTAB_BASE_HI_RA_POS);
    WR_REG32(SMMU_BASE_ADDR + SMMU_STRTAB_BASE_CFG, 4);
}

static void smmu_prepare_page_tables_512mb(void)
{
    uint64_t address_offset = ADDR_SPACE_SDM;
    /*Preparing page table supporting VA of 512 MB*/
    /*Virtual Address always starts from 0x0*/

    /*Prepare L0 PageTable*/
    for (int i = 0; i < 256; i++)
    {
        smmu_descriptors.lvl0_page_table_512mb[i] =
                ((uint64_t)&smmu_descriptors.lvl1_page_table_512mb[i][0]) |
                0x3U;
    }

    /*Prepare L1 PageTable*/
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            smmu_descriptors.lvl1_page_table_512mb[i][j] = address_offset |
                    (0x3U) | ((uint64_t)0x3 << 8) | ((uint64_t)1 << 10) |
                    (2U << 2);
            address_offset = address_offset + GRANULE_SIZE_4KB;
        }
    }

    cache_force_write_back(smmu_descriptors.lvl0_page_table_512mb,
            sizeof(smmu_descriptors.lvl0_page_table_512mb));
    cache_force_write_back(smmu_descriptors.lvl1_page_table_512mb,
            sizeof(smmu_descriptors.lvl1_page_table_512mb));
}

static void smmu_prepare_page_tables_1tb(void)
{
    uint64_t address_offset = ADDR_SPACE_PER;
    /*Preparing page table supporting VA of 512 MB*/
    /*Virtual Address always starts from 0x0*/
    smmu_descriptors.lvl0_page_table_1tb[0] =
            ((uint64_t)smmu_descriptors.lvl1_page_table_1tb) | 0x3U;
    smmu_descriptors.lvl0_page_table_1tb[1] = 0;

    smmu_descriptors.lvl1_page_table_1tb[0] = SMMU_MEM_OFFSET_L1_IDX(0) |
            ((uint64_t)1 << 10) | ((uint64_t)(1UL << 54UL)) |
            ((uint64_t)(1UL << 53UL));
    smmu_descriptors.lvl1_page_table_1tb[1] = SMMU_MEM_OFFSET_L1_IDX(1) |
            ((uint64_t)1 << 10) | ((uint64_t)(1UL << 54UL)) |
            ((uint64_t)(1UL << 53UL));
    smmu_descriptors.lvl1_page_table_1tb[2] =
            (uint64_t)(smmu_descriptors.lvl2_page_table_1tb) |
            ((uint64_t)1 << 10) | 0x1U | (1U << 1) | (2U << 2);
    smmu_descriptors.lvl1_page_table_1tb[3] = SMMU_MEM_OFFSET_L1_IDX(3) |
            ((uint64_t)1 << 10) | ((uint64_t)(1UL << 54UL)) |
            ((uint64_t)(1UL << 53UL));

    /*l2 page table has yet another 512 entries
     * Bringing down the page size to 2MB chunks*/
    for (int idx = 0; idx < 512; idx++)
    {
        smmu_descriptors.lvl2_page_table_1tb[idx] = (address_offset) | 1U |
                ((uint32_t)1 << 10) | (2U << 2);
        address_offset = address_offset + OFFSET_SIZE_2MB;
    }

    cache_force_write_back(smmu_descriptors.lvl0_page_table_1tb,
            sizeof(smmu_descriptors.lvl0_page_table_1tb));
    cache_force_write_back(smmu_descriptors.lvl1_page_table_1tb,
            sizeof(smmu_descriptors.lvl1_page_table_1tb));
    cache_force_write_back(smmu_descriptors.lvl2_page_table_1tb,
            sizeof(smmu_descriptors.lvl2_page_table_1tb));

}

static int32_t enable_command_queue(void)
{
    uint32_t reg_val = 0;
    uint32_t retry = MAX_RETRY_COUNTER;
    (void)memset(smmu_descriptors.command_desc, 0,
            sizeof(smmu_descriptors.command_desc));
    cache_force_write_back((void *)smmu_descriptors.command_desc,
            (size_t)(CMD_COUNT * sizeof(command_desc_t)));

    reg_val = ((uint32_t)(((uintptr_t)smmu_descriptors.command_desc))) | 0x4U;
    WR_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_BASE_LO, reg_val);
    WR_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_BASE_HI,
            ((uint32_t)0x1 << SMMU_CMDQ_BASE_HI_RA_POS));
    WR_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_PROD, 0);
    WR_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_CONS, 0);

    WR_REG32(SMMU_BASE_ADDR + SMMU_CR0, (0x1U << SMMU_CR0_CMDQEN_POS));
    do{
        reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0ACK);
        if (retry == 0U)
        {
            return SMMU_OP_FAIL;
        }
        retry--;

    } while((reg_val & (1U << 3)) == 0U);
    return SMMU_OP_SUCCESS;
}

static int32_t enable_event_queue(void)
{
    uint32_t reg_val = 0;
    uint32_t retry = MAX_RETRY_COUNTER;
    //        1024 * 1024, 32);
    smmu_descriptors.event_queue = 0x00;
    if(smmu_descriptors.event_queue != NULL){
        (void)memset(smmu_descriptors.event_queue, 0, 32);
    }
    cache_force_write_back(smmu_descriptors.event_queue, 32);

    reg_val = ((uint32_t)((uintptr_t)smmu_descriptors.event_queue)) | 0x5U;
    WR_REG32(SMMU_BASE_ADDR + SMMU_EVENTQ_BASE_LO, reg_val);
    WR_REG32(SMMU_BASE_ADDR + SMMU_EVENTQ_BASE_HI,
            ((uint32_t)0x1 << SMMU_EVENTQ_BASE_HI_WA_POS));

    reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0);
    reg_val |= (1U << SMMU_CR0_EVENTQEN_POS);
    WR_REG32(SMMU_BASE_ADDR + SMMU_CR0, reg_val);

    do
    {
        reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0ACK);
        if (retry == 0U)
        {
            return SMMU_OP_FAIL;
        }
        retry--;

    } while((reg_val & (1U << SMMU_CR0ACK_EVENTQEN_POS)) == 0U);

    return SMMU_OP_SUCCESS;
}

int32_t smmu_enable(void)
{
    uint32_t reg_val = 0;
    uint32_t retry = MAX_RETRY_COUNTER;
    int ret = 0;

    WR_REG32(SMMU_BASE_ADDR + SMMU_CR0, 0);
    WR_REG32(SMMU_BASE_ADDR + SMMU_IRQ_CTRL, 1U | (1U << 2));

    ret = enable_command_queue();
    if (ret == SMMU_OP_FAIL)
    {
        return -EIO;
    }

    ret = enable_event_queue();
    if (ret == SMMU_OP_FAIL)
    {
        return -EIO;
    }

    smmu_prepare_page_tables_512mb();
    smmu_prepare_context_512mb();
    smmu_prepare_page_tables_1tb();
    smmu_prepare_context_1tb();

    for (uint8_t i = 1U; i < (SMMU_MAX_STREAM_ID + 1U); i++)
    {
        smmu_prepare_stream_table(i);
    }

    reg_val = (((uint32_t)0x3 << SMMU_CR1_QUEUE_IC_POS) |
            ((uint32_t)0x1 <<
            SMMU_CR1_TABLE_IC_POS) | ((uint32_t)0x1 << SMMU_CR1_TABLE_OC_POS) |
            ((uint32_t)0x3 <<
            SMMU_CR1_QUEUE_SH_POS) | ((uint32_t)0x3 << SMMU_CR1_TABLE_SH_POS));

    WR_REG32(SMMU_BASE_ADDR + SMMU_CR1, reg_val);
    reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0);
    reg_val |= 1U;
    WR_REG32(SMMU_BASE_ADDR + SMMU_CR0, reg_val);

    do
    {
        reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0ACK);
        if (retry == 0U)
        {
            return SMMU_OP_FAIL;
        }
        retry--;

    } while(((reg_val & 1U) << (SMMU_CR0_SMMUEN_POS)) == 0U);

    ret = smmu_manage_command_queue();
    if (ret == SMMU_OP_FAIL)
    {
        return -EIO;
    }
    return 0;
}

int32_t smmu_disable(void)
{
    uint32_t retry = MAX_RETRY_COUNTER;
    uint32_t reg_val;
    const uint32_t ack_mask = (SMMU_CR0ACK_SMMUEN_MASK |
                               SMMU_CR0ACK_PRIQEN_MASK |
                               SMMU_CR0ACK_EVENTQEN_MASK |
                               SMMU_CR0ACK_CMDQEN_MASK);

    /* Disable translation and queues owned by this bare-metal SMMU driver. */
    WR_REG32(SMMU_BASE_ADDR + SMMU_CR0, 0U);

    do
    {
        reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CR0ACK);
        if ((reg_val & ack_mask) == 0U)
        {
            return 0;
        }

        if (retry == 0U)
        {
            return -ETIMEDOUT;
        }
        retry--;
    } while (true);
}

int32_t smmu_deinit(void)
{
    return smmu_disable();
}

/*Command queue
 * PROD index is updated by software after inserting an item to the queue
 * The CONS index is updated by SMMU after consuming an item.
 *
 * Event queue
 * PROD index is updated by SMMU after inserting an item to the queue
 * The CONS index is updated by the software after consuming the command
 */
/*PROD index indicates the next index the items to be added if the queue is not
 * full
 * CONS index indicates the next index the items to be read if the queue is not
 * empty
 */

static int32_t smmu_manage_command_queue(void)
{
    uint8_t index = 0;
    uint32_t reg_val = 0;
    uint32_t retry = MAX_RETRY_COUNTER;

    smmu_descriptors.command_desc[0].W0 = CMD_CFGI_STE;
    smmu_descriptors.command_desc[0].W1 = SDM_STREAM_ID;

    smmu_descriptors.command_desc[1].W0 = CMD_TLBI_NSNH_ALL;

    smmu_descriptors.command_desc[2].W0 = CMD_CFGI_CD_ALL;

    smmu_descriptors.command_desc[3].W0 = CMD_SYNC;

    index = 4;
    cache_force_write_back((void *)smmu_descriptors.command_desc,
            (size_t)index * sizeof(command_desc_t));

    WR_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_PROD, index);

    do
    {
        if (retry == 0U)
        {
            return SMMU_OP_FAIL;
        }

        reg_val = RD_REG32(SMMU_BASE_ADDR + SMMU_CMDQ_CONS);
        retry--;

    } while((reg_val & index) == 0U);

    return SMMU_OP_SUCCESS;
}

