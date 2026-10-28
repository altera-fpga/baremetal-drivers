/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_bridge_ll.c
 *
 * Bridge source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "socfpga_bridge_ll.h"
#include "socfpga_sip_handler.h"

/* SiP "set bridges" command and the two operations it accepts */
#define SIP_SMC_HPS_SET_BRIDGES    (0xC2000032ULL)
#define BRIDGE_LL_SIP_OP_DISABLE   (2ULL)
#define BRIDGE_LL_SIP_OP_ENABLE    (3ULL)

/* SiP status responses */
#define SIP_SMC_STATUS_OK          (0)
#define SIP_SMC_STATUS_ERROR       (4)

/* Bit masks the SiP service expects for each bridge */
#define BRIDGE_LL_MASK_HPS2FPGA    (1U << 0)
#define BRIDGE_LL_MASK_LWHPS2FPGA  (1U << 1)
#define BRIDGE_LL_MASK_FPGA2HPS    (1U << 2)
#define BRIDGE_LL_MASK_FPGA2SDRAM  (1U << 3)

/*
 * id -> (mask, name) table. Indexed by bridge_ll_id_t so the lookup is O(1)
 * and adding a new bridge is a single-line change.
 */
typedef struct
{
    uint32_t    mask;
    const char *name;
} bridge_ll_entry_t;

static const bridge_ll_entry_t s_bridge_table[BRIDGE_LL_ID_MAX] =
{
    [BRIDGE_LL_ID_HPS2FPGA]   = { BRIDGE_LL_MASK_HPS2FPGA,   "hps2fpga"   },
    [BRIDGE_LL_ID_LWHPS2FPGA] = { BRIDGE_LL_MASK_LWHPS2FPGA, "lwhps2fpga" },
    [BRIDGE_LL_ID_FPGA2HPS]   = { BRIDGE_LL_MASK_FPGA2HPS,   "fpga2hps"   },
    [BRIDGE_LL_ID_FPGA2SDRAM] = { BRIDGE_LL_MASK_FPGA2SDRAM, "fpga2sdram" },
};

const char *bridge_ll_name(bridge_ll_id_t id)
{
    if ((unsigned)id >= (unsigned)BRIDGE_LL_ID_MAX)
    {
        return "unknown";
    }
    return s_bridge_table[id].name;
}

int32_t bridge_ll_set(bridge_ll_id_t id, bool enable)
{
    uint64_t sip_args[SMC_CALL_REG_COUNT];
    int      sip_ret;

    if ((unsigned)id >= (unsigned)BRIDGE_LL_ID_MAX)
    {
        printf("BRIDGE LL: invalid bridge id %u\n", (unsigned)id);
        return BRIDGE_LL_OP_EINVAL;
    }

    (void)memset(sip_args, 0, sizeof(sip_args));
    sip_args[0] = enable ? BRIDGE_LL_SIP_OP_ENABLE : BRIDGE_LL_SIP_OP_DISABLE;
    sip_args[1] = (uint64_t)s_bridge_table[id].mask;

    sip_ret = smc_call(SIP_SMC_HPS_SET_BRIDGES, sip_args);

    if (sip_ret != SIP_SMC_STATUS_OK)
    {
        printf("BRIDGE LL: %s %s failed (sip status %d)\n",
               enable ? "enable" : "disable",
               s_bridge_table[id].name,
               sip_ret);
        return BRIDGE_LL_OP_EIO;
    }

    printf("BRIDGE LL: %s %sd successfully\n",
           s_bridge_table[id].name,
           enable ? "enable" : "disable");
    return BRIDGE_LL_OP_OK;
}
