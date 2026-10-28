/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_iossm_ll.h
 *
 * IOSSM low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_IOSSM_LL_H__
#define __SOCFPGA_IOSSM_LL_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Pull in platform-specific base addresses and DDR bounds */
#include "socfpga_iossm_reg_plat.h"


/* Constants: Command types and sentinels
 *
 * Command-type values and placeholders used when the driver builds a
 * command request.
 *
 * IOSSM_LL_NO_PARAM       - No parameter register is written.
 * IOSSM_LL_CMD_TYPE_NO_OP - No-operation command type.
 * IOSSM_LL_TRIG_CNTRL_OP  - Trigger and control command type. Used for
 *                           the ECC commands.
 * IOSSM_LL_SYSTEM_INFO    - System-info command type. Used with
 *                           IOSSM_LL_GET_SYS_INFO.
 * IOSSM_LL_NO_TYPE        - No IP type is specified.
 * IOSSM_LL_NO_ID          - No instance id is specified.
 */
#define IOSSM_LL_NO_PARAM          0U    /* Indicates no parameter is required  */
#define IOSSM_LL_CMD_TYPE_NO_OP    0U    /* No-operation command type           */
#define IOSSM_LL_TRIG_CNTRL_OP     4U    /* Trigger/control command type        */
#define IOSSM_LL_SYSTEM_INFO       1U    /* System-info command type            */

#define IOSSM_LL_NO_TYPE    0U           /* No IP type specified                */
#define IOSSM_LL_NO_ID      0U           /* No instance ID specified            */

/* Constants: ECC error injection
 *
 * Parameter values and the data pattern used to inject an ECC error.
 *
 * IOSSM_LL_SING_BIT_ERR_PARAM - Parameter for a single-bit ECC error.
 * IOSSM_LL_DBL_BIT_ERR_PARAM  - Parameter for a double-bit ECC error.
 * IOSSM_LL_ERROR_DATA_VALUE   - 64-bit pattern written to DDR to trigger
 *                               the injected error.
 */
#define IOSSM_LL_SING_BIT_ERR_PARAM    0xF4U  /* Single-bit error injection parameter */
#define IOSSM_LL_DBL_BIT_ERR_PARAM     0x03U  /* Double-bit error injection parameter */

#define IOSSM_LL_ERROR_DATA_VALUE    0xFFFFCCCCFFFFCCCCULL

/* Constants: Command opcodes
 *
 * Opcodes the driver sends to the IOSSM command interface.
 *
 * IOSSM_LL_GET_SYS_INFO     - Read system and interface information.
 * IOSSM_LL_ECC_EN           - Enable ECC.
 * IOSSM_LL_ECC_EN_STAT      - Read whether ECC is enabled.
 * IOSSM_LL_ECC_INT_STAT     - Read the ECC interrupt status.
 * IOSSM_LL_ECC_INT_ACK      - Acknowledge an ECC interrupt.
 * IOSSM_LL_ECC_INT_MASK     - Mask ECC interrupts.
 * IOSSM_LL_ECC_WRBK_EN      - Enable ECC write-back.
 * IOSSM_LL_ECC_GET_SBE_INFO - Read single-bit error information.
 * IOSSM_LL_ECC_GET_DBE_INFO - Read double-bit error information.
 * IOSSM_LL_ECC_ERR_INJ      - Inject an ECC error.
 * IOSSM_LL_ECC_CLEAR_ERR    - Clear the ECC error buffer.
 */
#define IOSSM_LL_GET_SYS_INFO        0x01U   /* Query system/interface information  */
#define IOSSM_LL_ECC_EN              0x101U  /* Enable ECC                          */
#define IOSSM_LL_ECC_EN_STAT         0x102U  /* Query ECC enable status             */
#define IOSSM_LL_ECC_INT_STAT        0x103U  /* Query ECC interrupt status          */
#define IOSSM_LL_ECC_INT_ACK         0x104U  /* Acknowledge ECC interrupt           */
#define IOSSM_LL_ECC_INT_MASK        0x105U  /* Mask ECC interrupts                 */
#define IOSSM_LL_ECC_WRBK_EN         0x106U  /* Enable ECC write-back               */
#define IOSSM_LL_ECC_GET_SBE_INFO    0x107U  /* Get single-bit error information    */
#define IOSSM_LL_ECC_GET_DBE_INFO    0x108U  /* Get double-bit error information    */
#define IOSSM_LL_ECC_ERR_INJ         0x109U  /* Inject ECC error                    */
#define IOSSM_LL_ECC_CLEAR_ERR       0x110U  /* Clear ECC error buffer              */

/* Constant: IOSSM_LL_INSTANCE_OFFSET
 * The physical memory-mapped stride between consecutive IOSSM hardware instances.
 */
#define IOSSM_LL_INSTANCE_OFFSET    0x400000U

/* Constants: Memory access status
 *
 * Results from the DDR range and alignment checks. The read and write
 * helpers return these before they touch memory that fails a check.
 *
 * IOSSM_LL_MEM_OK     - The address is inside the DDR window and is
 *                       8-byte aligned.
 * IOSSM_LL_MEM_ERANGE - The address is outside the DDR window.
 * IOSSM_LL_MEM_EALIGN - The address is not 8-byte aligned.
 */
#define IOSSM_LL_MEM_OK        0   /* Access was within the DDR window and succeeded */
#define IOSSM_LL_MEM_ERANGE   -1   /* Address is outside the allowed DDR window      */
#define IOSSM_LL_MEM_EALIGN   -2   /* Address is not naturally aligned for the width */


/* Struct: iossm_ll_req_payload_t
 *
 * An intermediate software descriptor used to format the raw bitfields of an 
 * outgoing IOSSM command before it is committed to the hardware mailbox registers.
 */
typedef struct
{
    uint32_t param_type;   /* Parameter register offset, or <IOSSM_LL_NO_PARAM> */
    uint32_t cmd_type;     /* Command type field (bits [23:16] of CMD_REQ)      */
    uint32_t opcode;       /* Command opcode (bits [15:0] of CMD_REQ)           */
    uint32_t reg_val;      /* Auxiliary register value (reserved for future use)*/
} iossm_ll_req_payload_t;

/* Struct: iossm_ll_response_t
 *
 * Container for the three-word response payload returned by the IOSSM hardware 
 * upon completion of a command execution.
 */
typedef struct
{
    uint32_t resp0;   /* Response word 0 (CMD_RESP0) */
    uint32_t resp1;   /* Response word 1 (CMD_RESP1) */
    uint32_t resp2;   /* Response word 2 (CMD_RESP2) */
    uint32_t status;  /* Response status (RESP_STAT) */
} iossm_ll_response_t;

/* Struct: iossm_ll_desc_t
 *
 * Software descriptor anchoring the context for a specific IOSSM hardware block. 
 * This caches the resolved MMIO base address alongside hardware-queried ID 
 * values to minimize redundant bus reads during high-frequency ECC polling.
 */
typedef struct
{
    uint32_t base_addr;    /* Resolved hardware base address of the instance */
    uint32_t ip_type;      /* IP type field returned by GET_SYS_INFO         */
    uint32_t instance_id;  /* Instance ID field returned by GET_SYS_INFO     */
} iossm_ll_desc_t;


/* Function: iossm_ll_read_reg32
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) read from the IOSSM register space. 
 * This centralized accessor facilitates easy replacement with test stubs or 
 * instrumentation tracing during debug.
 *
 * Parameters:
 *
 * base_addr  - The absolute physical MMIO base address of the target instance.
 * reg_offset - The specific 32-bit aligned register offset to read from.
 *
 * Returns:
 *
 * The raw 32-bit hardware value read from the register.
 */
uint32_t iossm_ll_read_reg32(uint32_t base_addr, uint32_t reg_offset);

/* Function: iossm_ll_write_reg32
 *
 * Performs a direct 32-bit Memory-Mapped I/O (MMIO) write to the IOSSM register space.
 *
 * Parameters:
 *
 * base_addr  - The absolute physical MMIO base address of the target instance.
 * reg_offset - The specific 32-bit aligned register offset to write to.
 * value      - The 32-bit data payload to commit to the hardware.
 *
 * Returns:
 *
 * None.
 */
void iossm_ll_write_reg32(uint32_t base_addr, uint32_t reg_offset, uint32_t value);

/* Function: iossm_ll_safe_mem_write64
 *
 * Executes a strictly validated 64-bit write directly into physical DDR memory. 
 * This is primarily utilized during error injection testing to flip bits in the 
 * memory array. The function enforces strict bounds checking against the known 
 * DDR window and guarantees 8-byte natural alignment to prevent bus faults.
 *
 * Parameters:
 *
 * ddr_addr - Target physical DDR address.
 * value    - The 64-bit value to write into memory.
 *
 * Returns:
 *
 * <IOSSM_LL_MEM_OK> on success.
 * <IOSSM_LL_MEM_ERANGE> if the address falls outside the allowed DDR bounds.
 * <IOSSM_LL_MEM_EALIGN> if the address is not 8-byte aligned.
 */
int32_t iossm_ll_safe_mem_write64(uint64_t ddr_addr, uint64_t value);

/* Function: iossm_ll_safe_mem_read64
 *
 * Executes a strictly validated 64-bit read directly from physical DDR memory. 
 * Applies the identical address boundary and natural alignment safeguards as 
 * the write equivalent.
 *
 * Parameters:
 *
 * ddr_addr  - Target physical DDR address.
 * out_value - Pointer to a 64-bit integer to store the retrieved memory content.
 *
 * Returns:
 *
 * <IOSSM_LL_MEM_OK> on success.
 * -EINVAL if the output pointer is NULL.
 * <IOSSM_LL_MEM_ERANGE> or <IOSSM_LL_MEM_EALIGN> if the address is invalid.
 */
int32_t iossm_ll_safe_mem_read64(uint64_t ddr_addr, uint64_t *out_value);

/* Function: iossm_ll_send_command
 *
 * Constructs and issues a command sequence to the IOSSM hardware mailbox and 
 * actively polls for the corresponding response. This handles the low-level 
 * handshake required to trigger ECC scrubs, status queries, or interrupt 
 * acknowledgments.
 *
 * Parameters:
 *
 * desc    - Pointer to the populated IOSSM instance descriptor.
 * request - The specific command opcode (e.g., <IOSSM_LL_ECC_INT_ACK>).
 * param   - The auxiliary parameter required by certain commands. Passed as 0 if unused.
 *
 * Returns:
 *
 * A populated <iossm_ll_response_t> structure containing the 3-word response and 
 * the final hardware execution status.
 *
 * Notes:
 *
 * This function blocks synchronously while polling the hardware response register. 
 * Higher-level drivers must ensure appropriate timeouts or watchdog coverage 
 * to prevent deadlocks if the IOSSM IP hangs.
 */
iossm_ll_response_t iossm_ll_send_command(const iossm_ll_desc_t *desc,
                                          uint32_t request,
                                          uint32_t param);

/* Function: iossm_ll_err_inject_command
 *
 * Coordinates the multi-step hardware sequence required to inject an artificial 
 * ECC error. This function configures the IOSSM to expect a fault, utilizes 
 * <iossm_ll_safe_mem_write64> to deliberately corrupt the physical memory at 
 * the target address, and fetches the resulting syndrome status.
 *
 * Parameters:
 *
 * desc     - Pointer to the populated IOSSM instance descriptor.
 * ddr_addr - The physical DDR address at which to inject the error.
 * param    - The severity of the injection (<IOSSM_LL_SING_BIT_ERR_PARAM> or <IOSSM_LL_DBL_BIT_ERR_PARAM>).
 *
 * Returns:
 *
 * A populated <iossm_ll_response_t>. If the address fails range/alignment 
 * validation, it immediately aborts and returns a zero-filled response 
 * (where the status field is 0).
 */
iossm_ll_response_t iossm_ll_err_inject_command(const iossm_ll_desc_t *desc,
                                                uint64_t ddr_addr,
                                                uint32_t param);

/* Function: iossm_ll_get_base_addr
 *
 * Maps a logical IOSSM instance index to its absolute physical MMIO base address 
 * within the System-on-Chip.
 *
 * Parameters:
 *
 * instance  - The logical instance index (e.g., 0 or 1).
 * base_addr - Pointer to a 32-bit integer where the resolved address will be stored.
 *
 * Returns:
 *
 * 0 on success; -EINVAL if the instance index exceeds the available hardware blocks.
 */
int32_t iossm_ll_get_base_addr(uint32_t instance, uint32_t *base_addr);

#endif /* __SOCFPGA_IOSSM_LL_H__ */