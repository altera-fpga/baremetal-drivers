#ifndef BRIDGE_HELPER_H__
#define BRIDGE_HELPER_H__

#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "sysmgr.h"
#include "timer.h"

#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"

#include "smmu.h"
#include "smmu_internal.h"
#include "smmu_regs.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define HPS_MBOX_CLIENT 1
#define HPS_MBOX_ID 1
#define MBOX_GET_CONFIG_STATUS 0x04
#define MBOX_HPS_FPGA_CONFIG_COMP 0x45

#define MBOX_GET_CONFIG_STATUS_RESP_NUM 6
#define MBOX_CONFIG_STATUS_RESP_STATE 0
#define MBOX_CONFIG_STATUS_RESP_PIN_STATUS 2
#define MBOX_CONFIG_STATUS_RESP_PIN_STATUS_MASK 0xC0000000
#define MBOX_CONFIG_STATUS_RESP_SOFT_FUNCTION 3
#define MBOX_CONFIG_STATUS_RESP_SOFT_FUNCTION_MASK 0x3

#define SMMU_IIDR 0x4832243b
#define SMMU_CR0_SMMU_EN 0x1

int32_t bridge_enable(int32_t fd, int32_t timer_handle, int32_t sysmgr_handle);
int32_t bridge_disable(int32_t fd, int32_t timer_handle, int32_t sysmgr_handle);
int32_t bridge_mbox_helper(int32_t mbox_handle, uint32_t cmd, uint32_t *resp_data, uint32_t resp_num);
int32_t bridge_smmu_enabled_check_helper(int32_t smmu_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BRIDGE_HELPER_H__