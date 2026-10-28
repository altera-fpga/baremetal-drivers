/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: command.h
 *
 * Built-in console commands for help, processor-state reporting, screen clear,
 * and direct memory read, write, and dump operations.
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <stdint.h>
#include "errno.h"

/* Function: cmd_help
 *
 * Prints the built-in commands and all dynamically registered example commands.
 *
 * Returns:
 *
 *    0.
 */
int cmd_help(void);
/* Function: cmd_core
 *
 * Prints the shell core identifier derived from MPIDR_EL1.
 *
 * Returns:
 *
 *    0.
 */
int cmd_core(void);
/* Function: cmd_mpidr
 *
 * Prints the raw MPIDR_EL1 register value in hexadecimal.
 *
 * Returns:
 *
 *    0.
 */
int cmd_mpidr(void);
/* Function: cmd_el
 *
 * Prints the current ARM exception level.
 *
 * Returns:
 *
 *    0.
 */
int cmd_el(void);
/* Function: cmd_clear
 *
 * Clears the console display and returns to the command prompt.
 *
 * Returns:
 *
 *    0 on success.
 */
int cmd_clear(void);
/* Function: cmd_memdump
 *
 * Dumps a byte range starting at the requested memory address.
 *
 * Parameters:
 *
 *    args - Command arguments in the form "<addr> [count]".
 *
 * Returns:
 *
 *    0 on success; -EINVAL when the address argument is missing.
 */
int cmd_memdump(const char *args);
/* Function: cmd_memread
 *
 * Reads and prints one 32-bit value from the requested memory address.
 *
 * Parameters:
 *
 *    args - Command arguments in the form "<addr>".
 *
 * Returns:
 *
 *    0 on success; -EINVAL when the address argument is missing.
 */
int cmd_memread(const char *args);
/* Function: cmd_memwrite
 *
 * Writes one 32-bit value to the requested memory address.
 *
 * Parameters:
 *
 *    args - Command arguments in the form "<addr> <value>".
 *
 * Returns:
 *
 *    0 on success; -EINVAL when the address or value argument is missing.
 */
int cmd_memwrite(const char *args);

/* Function: read_mpidr_el1
 *
 * Reads the ARM MPIDR_EL1 system register.
 *
 * Returns:
 *
 *    The raw 64-bit MPIDR_EL1 value.
 */
uint64_t read_mpidr_el1(void);
/* Function: read_currentel
 *
 * Reads CurrentEL and returns the numeric ARM exception level.
 *
 * Returns:
 *
 *    1 for EL1, 2 for EL2, or 3 for EL3.
 */
uint64_t read_currentel(void);


#endif /* __COMMAND_H__ */
