/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: mailbox_api.h
 *
 * Initialize the Secure Device Manager mailbox, execute mailbox commands, and
 * release mailbox resources.
 */

#ifndef __MAILBOX_API_H__
#define __MAILBOX_API_H__

#include <stdint.h>

/* Return codes */
/* Constant: MAILBOX_OK
 * Successful mailbox API status.
 */
#define MAILBOX_OK              (0)
/* Constant: MAILBOX_ERROR
 * Mailbox API status returned when the shared client is unavailable or a synchronous send fails.
 */
#define MAILBOX_ERROR           (-1)
/* Constant: MAILBOX_NO_RESPONSE
 * Reserved mailbox status. The current synchronous mailbox_exec() path does not return this value.
 */
#define MAILBOX_NO_RESPONSE     (-2)

/* Common SDM command opcodes */
/* Constant: MAILBOX_CMD_NOOP
 * Secure Device Manager mailbox no-operation command opcode.
 */
#define MAILBOX_CMD_NOOP                 (0x00U)
/* Constant: MAILBOX_CMD_CONFIG_STATUS
 * Secure Device Manager mailbox configuration-status command opcode.
 */
#define MAILBOX_CMD_CONFIG_STATUS        (0x04U)
/* Constant: MAILBOX_CMD_GET_IDCODE
 * Secure Device Manager mailbox device-ID command opcode.
 */
#define MAILBOX_CMD_GET_IDCODE           (0x10U)
/* Constant: MAILBOX_CONFIG_STATUS_RESP_WORDS
 * Expected configuration-status response capacity in 32-bit words.
 */
#define MAILBOX_CONFIG_STATUS_RESP_WORDS (6U)

/* Function: mailbox_init
 *
 * Acquire the shared Secure Device Manager (SDM) mailbox client used by mailbox_exec().
 *
 * Returns:
 *
 *    MAILBOX_OK on success. MAILBOX_ERROR when the mailbox client cannot be acquired.
 */
int32_t mailbox_init(void);

/* Function: mailbox_deinit
 *
 * Release the shared mailbox client and clear the API handle.
 */
void mailbox_deinit(void);

/* Function: mailbox_exec
 *
 * Send one SDM mailbox command through the synchronous mailbox client and return after mbox_send_command() completes.
 *
 * Parameters:
 *
 *    cmd - SDM mailbox command opcode.
 *    args - Argument words in DDR accepted by TF-A is_address_in_ddr_range()
 *           (addr >= BL31_LIMIT, typically 0x82000000 on Agilex 5/72), or NULL
 *           when arg_words is 0. Stack/BSS buffers in this image sit below
 *           BL31_LIMIT and are rejected.
 *    arg_words - Number of 32-bit words in args.
 *    resp_ddr - Response buffer with the same TF-A address rule, or NULL when
 *               no response payload is required.
 *    resp_words - Capacity of resp_ddr in 32-bit words.
 *
 * Returns:
 *
 *    MAILBOX_OK on success. MAILBOX_ERROR when mailbox_init() has not acquired a client or mbox_send_command() fails. MAILBOX_NO_RESPONSE is not returned by the current synchronous implementation.
 *
 * Notes:
 *
 *    See api/mailbox/README.md (Before You Start) for the full buffer-placement
 *    guidance.
 */
int32_t mailbox_exec(uint32_t  cmd,
                     uint32_t *args,     uint32_t arg_words,
                     uint32_t *resp_ddr, uint32_t resp_words);

#endif /* __MAILBOX_API_H__ */
