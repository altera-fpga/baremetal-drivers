/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: fcs_api.h
 *
 * FPGA Crypto Services (FCS) calls through the Secure Device Manager mailbox.
 *
 * Call fcs_api_init() before any command except fcs_api_poll_drain().
 * fcs_api_poll_drain() does not check the init flag.
 * fcs_api_init() and fcs_api_deinit() may be repeated: init on an already
 * open service returns success, and deinit when nothing is open returns success.
 * Session, identity, random, and provision calls return FCS_API_NOT_INITED
 * until init has succeeded. Those calls also drain pending mailbox responses
 * before they return.
 */

#ifndef __FCS_API_H__
#define __FCS_API_H__

#include <stdint.h>
#include <stddef.h>

#include "socfpga_fcs.h"

/* Constant: FCS_API_OK
 * The mailbox command completed with status 0.
 */
#define FCS_API_OK              (0)

/* Constant: FCS_API_ERROR
 * The mailbox command failed with a status this layer does not map more specifically.
 */
#define FCS_API_ERROR           (-1)

/* Constant: FCS_API_NO_RESPONSE
 * Reserved. No function in this header returns this value today.
 */
#define FCS_API_NO_RESPONSE     (-2)

/* Constant: FCS_API_INVALID_PARAM
 * A required pointer was NULL, or a size was outside the accepted range.
 */
#define FCS_API_INVALID_PARAM   (-3)

/* Constant: FCS_API_NOT_INITED
 * fcs_api_init() has not succeeded.
 */
#define FCS_API_NOT_INITED      (-4)

/* Constant: FCS_API_SECURITY_DENIED
 *
 * The mailbox returned 0x85. Seen when the device is not owned or the user public key is not provisioned. fcs_api_get_provision_data() can return the same code.
 */
#define FCS_API_SECURITY_DENIED (-5)

/* Function: fcs_api_init
 *
 * Open the FCS mailbox client. A second call while already open returns success and does nothing.
 *
 * Returns:
 *
 *    FCS_API_OK, or FCS_API_ERROR when the client open fails.
 */
int fcs_api_init(void);

/* Function: fcs_api_deinit
 *
 * Close the FCS mailbox client. A call when nothing is open returns success.
 *
 * Returns:
 *
 *    FCS_API_OK, or FCS_API_ERROR when the client close fails. The local open flag is cleared either way.
 */
int fcs_api_deinit(void);

/* Function: fcs_api_poll_drain
 *
 * Poll the mailbox up to 256 times and stop on the first pass that returns nothing.
 *
 * The FCS commands already drain once before they return. Use this when a caller still expects a queued response.
 *
 * Returns:
 *
 *    The number of responses harvested. Zero when the first poll returns nothing. Does not require fcs_api_init().
 */
int fcs_api_poll_drain(void);

/* Function: fcs_api_open_session
 *
 * Open a cryptographic session and write the session UUID into uuid_out.
 *
 * Parameters:
 *
 *    uuid_out - Buffer of at least FCS_UUID_SIZE bytes. Cleared before the request. Must be non-NULL.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, FCS_API_SECURITY_DENIED when the mailbox returns 0x85, or FCS_API_ERROR.
 */
int fcs_api_open_session(char *uuid_out);

/* Function: fcs_api_close_session
 *
 * Close the session identified by uuid.
 *
 * Parameters:
 *
 *    uuid - UUID from fcs_api_open_session(). Must be non-NULL.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, or FCS_API_ERROR. A mailbox status of 0x85 is reported as FCS_API_ERROR on this call.
 */
int fcs_api_close_session(char *uuid);

/* Function: fcs_api_get_chip_id
 *
 * Read the device chip ID. Both outputs are cleared to zero before the request.
 *
 * Parameters:
 *
 *    chip_low - Receives the low 32 bits. Must be non-NULL.
 *    chip_high - Receives the high 32 bits. Must be non-NULL.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, or FCS_API_ERROR.
 */
int fcs_api_get_chip_id(uint32_t *chip_low, uint32_t *chip_high);

/* Function: fcs_api_get_jtag_idcode
 *
 * Read the JTAG IDCODE. The output is cleared to zero before the request.
 *
 * Parameters:
 *
 *    jtag_idcode - Receives the IDCODE. Must be non-NULL.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, or FCS_API_ERROR.
 */
int fcs_api_get_jtag_idcode(uint32_t *jtag_idcode);

/* Function: fcs_api_get_random_number
 *
 * Fill rand_buf with random bytes from the device generator.
 *
 * Parameters:
 *
 *    uuid - Session UUID from fcs_api_open_session(). Must be non-NULL.
 *    context_id - Caller tag passed through to the request.
 *    rand_buf - Destination. Must be non-NULL.
 *    rand_size - Byte count, from 1 through FCS_RNG_MAX_SIZE.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, or FCS_API_ERROR.
 */
int fcs_api_get_random_number(char    *uuid,
                              uint32_t context_id,
                              char    *rand_buf,
                              uint32_t rand_size);

/* Function: fcs_api_get_provision_data
 *
 * Read the provisioning data block.
 *
 * Parameters:
 *
 *    prov_data - Destination. Must be non-NULL. Capacity is *prov_data_size on entry.
 *    prov_data_size - In: buffer capacity in bytes. Out: bytes written, when the lower layer updates it. Must be non-NULL.
 *
 * Returns:
 *
 *    FCS_API_OK, FCS_API_INVALID_PARAM, FCS_API_NOT_INITED, FCS_API_SECURITY_DENIED when the mailbox returns 0x85, or FCS_API_ERROR.
 */
int fcs_api_get_provision_data(char     *prov_data,
                               uint32_t *prov_data_size);

#endif /* __FCS_API_H__ */
