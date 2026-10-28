/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: console_api.h
 *
 * Register commands with the interactive command-line interface (CLI), inspect
 * the registered command table, dispatch command lines, and run the prompt loop.
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>
#include "lib_parse.h"

/* Callback: cmd_func_t
 *
 * Handler signature for dynamically registered CLI commands.
 *
 * Parameters:
 *
 *    args - Text following the command name. The string may be empty.
 */
typedef void (*cmd_func_t)(const char *args);

/* Struct: cli_cmd_t
 *
 * One dynamically registered command.
 *
 * Fields:
 *
 *    name - NUL-terminated command name matched by the dispatcher.
 *    func - Handler invoked with the text following the command name.
 */
typedef struct {
	const char *name;
	cmd_func_t func;
} cli_cmd_t;

/* Function: cli_register_command
 *
 * Registers a dynamic CLI command, or updates the handler when the name is already registered.
 *
 * Parameters:
 *
 *    name - Command name shown and matched by the CLI.
 *    func - Handler called when the command is dispatched.
 *
 * Returns:
 *
 *    0 on success; -EINVAL when name or func is NULL; -ENOSPC when the dynamic command table is full.
 */
int cli_register_command(const char *name, cmd_func_t func);

/* Read-only accessors for registered dynamic commands. */
/* Function: cli_get_command_count
 *
 * Return the number of dynamically registered CLI commands.
 *
 * Returns:
 *
 *    The current number of registered dynamic commands, from 0 through
 *    CLI_MAX_DYNAMIC_CMDS.
 */
int cli_get_command_count(void);
/* Function: cli_get_command
 *
 * Returns a read-only entry from the dynamic command table.
 *
 * Parameters:
 *
 *    index - Zero-based dynamic-command index.
 *
 * Returns:
 *
 *    A pointer to the registered command, or NULL when index is out of range.
 */
const cli_cmd_t *cli_get_command(int index);

/* CLI helpers are provided by lib_parse.h. */

/* Command dispatcher & prompt */
/* Function: cli_dispatch
 *
 * Parses one command line and dispatches it to a built-in or registered command handler.
 *
 * Parameters:
 *
 *    cmdline - NUL-terminated command line without the trailing newline.
 *
 * Returns:
 *
 *    None.
 */
void cli_dispatch(const char *cmdline);
/* Function: cli_prompt
 *
 * Prints the bare-metal shell prompt.
 *
 * Returns:
 *
 *    None.
 */
void cli_prompt(void);

/* CLI main loop */
/* Function: cli_run
 *
 * Runs the blocking UART command loop, including line editing, tab completion, and command dispatch.
 *
 * Returns:
 *
 *    This function does not return during normal shell operation.
 */
void cli_run(void);

#endif /* __CONSOLE_H__ */
