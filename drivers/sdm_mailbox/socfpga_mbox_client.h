/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_mbox_client.h
 *
 * SDM Mailbox hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_MBOX_CLIENT_H__
#define __SOCFPGA_MBOX_CLIENT_H__

#include <stdint.h>
#include "errno.h"

/* Constant: MBOX_WORD_SIZE
 * Defines the standard 32-bit (4-byte) word size used by the Secure Device Manager 
 * (SDM) mailbox FIFO and ARM Trusted Firmware (ATF) payload formatting.
 */
#define MBOX_WORD_SIZE    (4U)


struct sdm_client_descriptor;

/* Type: sdm_client_handle
 *
 * An opaque software handle representing a specific mailbox client. This handle 
 * manages the software state, including transaction IDs, callback bindings, and 
 * allocated shared memory (DDR) buffers used for asynchronous SDM communication.
 */
typedef struct sdm_client_descriptor *sdm_client_handle;

/* Type: mbox_call_back_t
 *
 * Function signature for the asynchronous response handler. This is executed 
 * when the ATF signals (via the S2C ring buffer during polling) that the SDM 
 * has completed a specific job and written the response payload into memory.
 *
 * Parameters:
 *
 * resp_data - A pointer to the populated response data retrieved from the SDM.
 */
typedef void (*mbox_call_back_t)(uint64_t *resp_data);


/* Section: Initialization and Teardown */

/* Function: mbox_init
 *
 * Bootstraps the mailbox client subsystem. This allocates the global client 
 * descriptors, initializes synchronization primitives (mutexes/semaphores), 
 * and prepares the foundational communication channels with the ARM Trusted Firmware.
 *
 * Returns:
 *
 * 0 on success; a negative error code (e.g., -ENOMEM) if memory allocation fails.
 */
int mbox_init(void);

/* Function: mbox_deinit
 *
 * Tears down the mailbox subsystem. It destroys all active synchronization 
 * primitives and releases shared memory buffers back to the bare-metal heap, 
 * effectively halting communication with the SDM.
 *
 * Returns:
 *
 * 0 on success; -EIO if internal errors prevent a clean shutdown.
 */
int mbox_deinit(void);

/* Function: mbox_open_client
 *
 * Claims an available client descriptor block from the internal pool. This 
 * associates the caller with a unique Client ID, which the ATF uses to route 
 * asynchronous responses back to the correct software context.
 *
 * Returns:
 *
 * A valid <sdm_client_handle> on success; NULL if the maximum number of 
 * concurrent clients has been reached.
 */
sdm_client_handle mbox_open_client(void);

/* Function: mbox_close_client
 *
 * Releases a previously allocated client descriptor back to the available pool. 
 * Any pending asynchronous transactions associated with this client ID are 
 * effectively orphaned and will be ignored upon SDM completion.
 *
 * Parameters:
 *
 * mbox_handle - The active client handle to close.
 *
 * Returns:
 *
 * 0 on success; -EIO if the handle is invalid or cannot be closed cleanly.
 *
 * Note: Prefer <mbox_client_acquire> / <mbox_client_release> for bare-metal
 * examples and drivers so they share a single client.
 */
int32_t mbox_close_client(sdm_client_handle mbox_handle);

/* Function: mbox_client_acquire
 *
 * Returns the process-wide shared SDM mailbox client.  On first call, initializes
 * the mailbox subsystem (if needed) and opens one client.  Later calls reuse the
 * same handle.  Intended for single-threaded bare-metal examples/drivers.
 *
 * Returns:
 *
 * A valid <sdm_client_handle> on success; NULL on failure.
 */
sdm_client_handle mbox_client_acquire(void);

/* Function: mbox_client_release
 *
 * Normal example/driver teardown hook.  Does not close the shared client so the
 * next example can reuse it and avoid open/close lifetime issues.
 */
void mbox_client_release(void);


/* Section: Command Execution */

/* Function: mbox_send_command
 *
 * Issues a generic SDM mailbox command through V1 INTEL_SIP_SMC_MBOX_SEND_CMD
 * (synchronous BL31 path). Prefer this over V3 GEN_MBOX, which ATF default-denies
 * for all opcodes except CONFIG_STATUS. Dedicated SiP services (for example FCS) should
 * still use sip_svc_send() with their own function IDs.
 *
 * Parameters:
 *
 * mbox_handle  - The active client handle (validated; V1 sync does not use
 *                client/job IDs).
 * command      - The specific SDM mailbox command code.
 * command_args - Argument buffer accepted by TF-A is_address_in_ddr_range()
 *                (addr >= BL31_LIMIT, typically 0x82000000 on Agilex 5/72),
 *                or NULL if none. Stack/BSS buffers below BL31_LIMIT are
 *                rejected.
 * arg_size     - The number of bytes in the `command_args` array.
 * resp         - Response buffer with the same TF-A address rule, or NULL if
 *                no payload expected.
 * resp_size    - Capacity of `resp` in bytes.
 * smc_resp     - Optional: on success [0]=SDM status, [1]=resp words returned.
 * smc_resp_len - Number of 64-bit entries in `smc_resp`.
 *
 * Returns:
 *
 * 0 on success; -EIO if the command is rejected by the ATF or SDM.
 */
int32_t mbox_send_command(sdm_client_handle mbox_handle, uint32_t command,
        uint32_t *command_args, uint32_t arg_size,
        uint32_t *resp, uint32_t resp_size,
        uint64_t *smc_resp, uint32_t smc_resp_len);

/* Function: sip_svc_send
 *
 * A lower-level interface to the ARM Trusted Firmware's Silicon Provider (SiP) 
 * Service. This function directly formats the provided 64-bit arguments into 
 * CPU registers (X1-X7) and invokes the `smc` instruction, bypassing the 
 * standard mailbox wrapper for specialized EL3 queries.
 *
 * Parameters:
 *
 * mbox_handle - The active client handle.
 * smc_func_id - The 64-bit SMC Function ID (FID) identifying the specific SiP service.
 * mbox_args   - Pointer to an array of up to 6 arguments to load into X1-X6.
 * arg_len     - The number of arguments provided.
 * resp_data   - Pointer to a buffer to capture the SMC return registers (X0-X3).
 * resp_len    - The number of return registers to capture.
 *
 * Returns:
 *
 * 0 on success; -EIO if the SMC call fails or returns an error status.
 */
int32_t sip_svc_send(sdm_client_handle mbox_handle, uint64_t smc_func_id,
        uint64_t *mbox_args, uint32_t arg_len, uint64_t *resp_data, uint32_t
        resp_len);


/* Section: Asynchronous Management */

/* Function: mbox_set_callback
 *
 * Binds a user-provided asynchronous callback function to the specified client 
 * handle. This must be registered before issuing non-blocking mailbox commands, 
 * so the polling subsystem knows how to deliver the SDM payload when the 
 * transaction finishes.
 *
 * Parameters:
 *
 * mbox_handle - The active client handle.
 * callback    - Function pointer to the handler routine.
 *
 * Returns:
 *
 * 0 on success; -EIO if the handle is invalid.
 */
int32_t mbox_set_callback(sdm_client_handle mbox_handle, mbox_call_back_t callback);

/* Function: mbox_poll_once
 *
 * The core asynchronous event pump. This function invokes the `SIP_SMC_GET_TRANS_ID` 
 * service to drain the SDM-to-HPS (S2C) ring buffer. For every completed job ID 
 * detected, it invokes `SIP_SMC_GET_RESP` to pull the payload from shared memory 
 * and fires the registered client callback with the data.
 *
 * Returns:
 *
 * The number of completed responses processed during this iteration (returns 0 
 * if no new responses were ready).
 */
int mbox_poll_once(void);

#endif /* __SOCFPGA_MBOX_CLIENT_H__ */
