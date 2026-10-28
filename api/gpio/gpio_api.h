/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: gpio_api.h
 *
 * GPIO interface declarations for the SoC FPGA bare-metal stack.
 *
 * These declarations require alignment with gpio_api.c in this revision.
 * See api/gpio/README.md for the implemented call flow before integration.
 *
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdint.h>

#include "mmio.h"
#include "errno.h"

/* Type: gpio_handle_t
 *
 * Opaque GPIO handle type used to preserve module state between calls.
 */
typedef struct gpio_handle_s* gpio_handle_t;  // opaque handle

/* Enum: gpio_status_t
 *
 * Status values declared by this interface.
 *
 * Values:
 *
 *    GPIO_OK - Success status.
 *    GPIO_ERROR - Generic error status.
 */
typedef enum {
    GPIO_OK = 0,
    GPIO_ERROR = -1,
} gpio_status_t;

// Use plain types for pins, directions, ioctl, callbacks
/* Type: gpio_pin_id_t
 *
 * Numeric GPIO pin identifier.
 */
typedef uint32_t gpio_pin_id_t;
/* Enum: gpio_direction_t
 *
 * Input and output pin directions.
 *
 * Values:
 *
 *    GPIO_INPUT - Configure as an input.
 *    GPIO_OUTPUT - Configure as an output.
 */
typedef enum { GPIO_INPUT, GPIO_OUTPUT } gpio_direction_t;
/* Enum: gpio_ioctl_cmd_t
 *
 * Control command selectors declared by this interface.
 *
 * Values:
 *
 *    GPIO_CMD_SET_DIRECTION - Set pin direction.
 *    GPIO_CMD_SET_INTERRUPT - Set interrupt configuration.
 */
typedef enum { GPIO_CMD_SET_DIRECTION, GPIO_CMD_SET_INTERRUPT } gpio_ioctl_cmd_t;
/* Callback: gpio_callback_fn
 *
 * Callback signature used by the GPIO module.
 *
 * Parameters:
 *
 *    param - Caller context supplied during callback registration.
 */
typedef void (*gpio_callback_fn)(void *param);

/* Function: gpio_open
 *
 * Opens a GPIO instance and prepares it for subsequent operations.
 *
 * Parameters:
 *
 *    pin - GPIO pin identifier.
 *    handle - Output storage that receives the opened or initialized handle.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_open(gpio_pin_id_t pin, gpio_handle_t *handle);
/* Function: gpio_close
 *
 * Closes the GPIO handle or instance and returns it to the inactive state.
 *
 * Parameters:
 *
 *    handle - Handle returned by the corresponding open or initialization routine.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_close(gpio_handle_t handle);
/* Function: gpio_ioctl
 *
 * Performs a GPIO operation exposed by this layer.
 *
 * Parameters:
 *
 *    handle - Handle returned by the corresponding open or initialization routine.
 *    cmd - Command selector or operation code.
 *    arg - Command or IOCTL argument supplied by the caller.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_ioctl(gpio_handle_t handle, gpio_ioctl_cmd_t cmd, void *arg);
/* Function: gpio_set_callback
 *
 * Writes or configures GPIO state, data, or register content.
 *
 * Parameters:
 *
 *    handle - Handle returned by the corresponding open or initialization routine.
 *    callback - Callback function invoked when the event completes or triggers.
 *    param - Opaque caller context passed back to callbacks.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_set_callback(gpio_handle_t handle, gpio_callback_fn callback, void *param);
/* Function: gpio_write_sync
 *
 * Writes or configures GPIO state, data, or register content.
 *
 * Parameters:
 *
 *    handle - Handle returned by the corresponding open or initialization routine.
 *    value - Value to write or storage for a value read by the function.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_write_sync(gpio_handle_t handle, uint8_t value);
/* Function: gpio_read_sync
 *
 * Reads GPIO state, data, or register content for the caller.
 *
 * Parameters:
 *
 *    handle - Handle returned by the corresponding open or initialization routine.
 *    value - Output storage for the requested value.
 *
 * Returns:
 *
 *    GPIO_OK on success or a GPIO status/error code on failure.
 */
gpio_status_t gpio_read_sync(gpio_handle_t handle, uint8_t *value);

#endif /* __GPIO_H__ */

