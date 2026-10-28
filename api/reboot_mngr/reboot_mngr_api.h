/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: reboot_mngr_api.h
 *
 * Request a cold or warm reboot. An optional callback runs immediately before the request is issued. A successful reboot does not return.
 */

#ifndef REBOOT_MNGR_API_H
#define REBOOT_MNGR_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Enum: reboot_type_t
 *
 * Reboot kinds accepted by reboot().
 *
 * Values:
 *
 *    REBOOT_COLD - Cold reboot.
 *    REBOOT_WARM - Warm reboot.
 */
typedef enum
{
	REBOOT_COLD = 0,
	REBOOT_WARM
} reboot_type_t;

/* Callback: reboot_callback_t
 *
 * Called once, immediately before the reboot request, with the user_data pointer passed to reboot().
 *
 * Parameters:
 *
 *    user_data - The pointer supplied to reboot().
 */
typedef void (*reboot_callback_t)(void *user_data);

/* Function: reboot
 *
 * Register cb for this reboot type, then request the reboot.
 *
 * cb may be NULL. Only REBOOT_COLD and REBOOT_WARM are accepted. If the reboot is accepted, this call does not return.
 *
 * Parameters:
 *
 *    type - REBOOT_COLD or REBOOT_WARM.
 *    cb - Optional callback. NULL skips the application callback.
 *    user_data - Pointer passed to cb. Ignored when cb is NULL.
 *
 * Returns:
 *
 *    -EINVAL when type is neither cold nor warm. The callback-registration status if that step fails. The reboot-request status if the request is rejected. Does not return when the reboot proceeds.
 */
int32_t reboot(reboot_type_t type, reboot_callback_t cb, void *user_data);

#ifdef __cplusplus
}
#endif

#endif // REBOOT_MNGR_API_H
