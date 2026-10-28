/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>
#include "errno.h"
#include "lib_parse.h"
#include "command.h"
#include "console_api.h"
#include "../uart/uart_api.h"


#define CLI_BUFSZ 512
char cli_buf[CLI_BUFSZ];


/* Maximum number of example commands registered at runtime. */
#define CLI_MAX_DYNAMIC_CMDS 96

static cli_cmd_t dynamic_cmds_storage[CLI_MAX_DYNAMIC_CMDS];
static int dynamic_cmd_count = 0;

static const char *cli_builtin_cmds[] = {
	"help",
	"core",
	"mpidr",
	"el",
	"clear",
	"memdump",
	"memread",
	"memwrite",
	"exit"
};

#define CLI_BUILTIN_CMD_COUNT ((int)(sizeof(cli_builtin_cmds) / sizeof(cli_builtin_cmds[0])))
#define CLI_MATCH_FALSE 0
#define CLI_MATCH_TRUE  1

/* ============================================================================
 * CLI helpers
 * ============================================================================
 */

static char cli_ascii_to_upper(char c)
{
	if (c >= 'a' && c <= 'z') {
		return (char)(c - ('a' - 'A'));
	}

	return c;
}

static int cli_prefix_match(const char *word, const char *prefix, size_t prefix_len)
{
	for (size_t i = 0; i < prefix_len; i++) {
		if ((word[i] == '\0') || (word[i] != prefix[i])) {
			return CLI_MATCH_FALSE;
		}
	}

	return CLI_MATCH_TRUE;
}

static size_t cli_strlen(const char *s)
{
	size_t n = 0U;

	while ((s != NULL) && (s[n] != '\0')) {
		n++;
	}

	return n;
}

static int cli_is_first_token_only(const char *buf, size_t idx)
{
	for (size_t i = 0; i < idx; i++) {
		if (buf[i] == ' ') {
			return CLI_MATCH_FALSE;
		}
	}

	return CLI_MATCH_TRUE;
}

static void cli_print_matches(const char *prefix, size_t prefix_len)
{
	printf("\n");

	for (int i = 0; i < CLI_BUILTIN_CMD_COUNT; i++) {
		if (cli_prefix_match(cli_builtin_cmds[i], prefix, prefix_len) != 0) {
			printf("  %s\n", cli_builtin_cmds[i]);
		}
	}

	for (int i = 0; i < dynamic_cmd_count; i++) {
		const char *name = dynamic_cmds_storage[i].name;
		if ((name != NULL) && (cli_prefix_match(name, prefix, prefix_len) != 0)) {
			printf("  %s\n", name);
		}
	}
}

static const char *cli_find_single_match(const char *prefix, size_t prefix_len, int *match_count)
{
	const char *single = NULL;
	int count = 0;

	for (int i = 0; i < CLI_BUILTIN_CMD_COUNT; i++) {
		if (cli_prefix_match(cli_builtin_cmds[i], prefix, prefix_len) != 0) {
			count++;
			single = cli_builtin_cmds[i];
		}
	}

	for (int i = 0; i < dynamic_cmd_count; i++) {
		const char *name = dynamic_cmds_storage[i].name;
		if ((name != NULL) && (cli_prefix_match(name, prefix, prefix_len) != 0)) {
			count++;
			single = name;
		}
	}

	*match_count = count;
	return single;
}

static void cli_redraw_line(const char *buf, size_t idx)
{
	cli_prompt();
	for (size_t i = 0; i < idx; i++) {
		uart_putc(buf[i]);
	}
}

static void cli_handle_tab(char *buf, size_t *idx)
{
	int match_count = 0;
	size_t prefix_len;
	const char *single;
	size_t full_len;

	if ((buf == NULL) || (idx == NULL) || (*idx == 0U)) {
		return;
	}

	if (cli_is_first_token_only(buf, *idx) == 0) {
		return;
	}

	prefix_len = *idx;
	single = cli_find_single_match(buf, prefix_len, &match_count);

	if ((match_count == 1) && (single != NULL)) {
		full_len = cli_strlen(single);
		for (size_t i = prefix_len; (i < full_len) && ((*idx + 1U) < CLI_BUFSZ); i++) {
			buf[*idx] = single[i];
			(*idx)++;
			uart_putc(single[i]);
		}
		return;
	}

	if (match_count > 1) {
		cli_print_matches(buf, prefix_len);
		cli_redraw_line(buf, *idx);
	}
}

static void cli_build_selftest_title(const char *cmd, char *title, size_t title_len)
{
	size_t i = 0;
	const char suffix[] = " SELF-TEST";
	size_t suffix_len = sizeof(suffix) - 1U;
	size_t j;

	if ((cmd == NULL) || (title == NULL) || (title_len == 0U)) {
		return;
	}

	while ((cmd[i] != '\0') && (i < (title_len - suffix_len - 1U))) {
		char c = cmd[i];

		if (c == '_') {
			title[i] = ' ';
		} else {
			title[i] = cli_ascii_to_upper(c);
		}
		i++;
	}

	for (j = 0; (j < suffix_len) && (i < (title_len - 1U)); j++) {
		title[i++] = suffix[j];
	}

	title[i] = '\0';
}

static void cli_print_selftest_header(const char *cmd)
{
	char title[40] = {0};
	char line[63] = {0};
	size_t i = 0;
	size_t text_len = 0;
	size_t left_pad;
	size_t right_pad;
	const size_t inner_width = 60U;

	cli_build_selftest_title(cmd, title, sizeof(title));

	while (title[text_len] != '\0') {
		text_len++;
	}

	if (text_len > (sizeof(title) - 1U)) {
		text_len = sizeof(title) - 1U;
		title[text_len] = '\0';
	}

	line[0] = '|';
	left_pad = (inner_width - text_len) / 2U;
	right_pad = inner_width - text_len - left_pad;

	for (i = 0; i < left_pad; i++) {
		line[1U + i] = ' ';
	}

	for (i = 0; i < text_len; i++) {
		line[1U + left_pad + i] = title[i];
	}

	for (i = 0; i < right_pad; i++) {
		line[1U + left_pad + text_len + i] = ' ';
	}

	line[61] = '|';
	line[62] = '\0';

	printf("\n");
	printf("+------------------------------------------------------------+\n");
	printf("%s\n", line);
	printf("+------------------------------------------------------------+\n");
	printf("\n");
}

/* ============================================================================
 * Command Dispatcher
 * ============================================================================
 */
int cli_register_command(const char *name, cmd_func_t func) {
	if ((name == NULL) || (func == NULL)) return -EINVAL;

	for (int i = 0; i < dynamic_cmd_count; i++) {
		if ((dynamic_cmds_storage[i].name != NULL) && (cstrcmp(dynamic_cmds_storage[i].name, name) == 0)) {
			dynamic_cmds_storage[i].func = func;
			return 0;
		}
	}

	if (dynamic_cmd_count >= CLI_MAX_DYNAMIC_CMDS) return -ENOSPC;
	dynamic_cmds_storage[dynamic_cmd_count].name = name;
	dynamic_cmds_storage[dynamic_cmd_count].func = func;
	dynamic_cmd_count++;
	return 0;
}

int cli_get_command_count(void)
{
	return dynamic_cmd_count;
}

const cli_cmd_t *cli_get_command(int index)
{
	if ((index < 0) || (index >= dynamic_cmd_count)) {
		return NULL;
	}

	return &dynamic_cmds_storage[index];
}

static uint32_t cli_get_expected_steps(const char *cmd)
{
	/* Commands that already print their own detailed test flow. */
	if ((cstrcmp(cmd, "gic_selftest") == 0) ||
	    (cstrcmp(cmd, "timer_selftest") == 0) ||
	    (cstrcmp(cmd, "ddr_selftest") == 0) ||
	    (cstrcmp(cmd, "ccu_selftest") == 0) ||
	    (cstrcmp(cmd, "i2c_selftest") == 0) ||
	    (cstrcmp(cmd, "i3c_selftest") == 0) ||
	    (cstrcmp(cmd, "noc_selftest") == 0) ||
	    (cstrcmp(cmd, "spi_selftest") == 0) ||
	    (cstrcmp(cmd, "mailbox_selftest") == 0) ||
	    (cstrcmp(cmd, "seu_selftest") == 0)) {
		return 0U;
	}

	/* Commands that usually execute multiple internal phases. */
	if ((cstrcmp(cmd, "bridge_selftest") == 0) ||
	    (cstrcmp(cmd, "dma_selftest") == 0) ||
	    (cstrcmp(cmd, "ecc_selftest") == 0) ||
	    (cstrcmp(cmd, "iossm_demo") == 0) ||
	    (cstrcmp(cmd, "sdmmc_selftest") == 0) ||
	    (cstrcmp(cmd, "perf_selftest") == 0)) {
		return 2U;
	}

	return 1U;
}

void cli_dispatch(const char *cmdline) {
	const char *p = cmdline;
	char cmd[32];
	int rc;
	size_t i = 0;

	while (*p && *p != ' ' && i < sizeof(cmd) - 1)
		cmd[i++] = *p++;
	cmd[i] = '\0';
	while (*p == ' ') p++;

	if (cstrcmp(cmd, "help") == 0)      { rc = cmd_help(); goto done_builtin; }
	if (cstrcmp(cmd, "core") == 0)      { rc = cmd_core(); goto done_builtin; }
	if (cstrcmp(cmd, "mpidr") == 0)     { rc = cmd_mpidr(); goto done_builtin; }
	if (cstrcmp(cmd, "el") == 0)        { rc = cmd_el(); goto done_builtin; }
	if (cstrcmp(cmd, "clear") == 0)     { rc = cmd_clear(); goto done_builtin; }
	if (cstrcmp(cmd, "memdump") == 0)   { rc = cmd_memdump(p); goto done_builtin; }
	if (cstrcmp(cmd, "memread") == 0)   { rc = cmd_memread(p); goto done_builtin; }
	if (cstrcmp(cmd, "memwrite") == 0)  { rc = cmd_memwrite(p); goto done_builtin; }

	if (cstrcmp(cmd, "exit") == 0) {
		printf("Exiting shell. Bye.\n");
		while (1) __asm__ __volatile__("wfe");
	}

	// Dynamic commands
	for (int j = 0; j < dynamic_cmd_count; j++) {
		if (cstrcmp(cmd, dynamic_cmds_storage[j].name) == 0) {
			uint32_t total_steps = cli_get_expected_steps(cmd);

			/* Commands that already contain their own full self-test format. */
			if (total_steps == 0U) {
				dynamic_cmds_storage[j].func(p);
				return;
			}

			cli_print_selftest_header(dynamic_cmds_storage[j].name);
			printf("Test 1 of %u : Command '%s' execution\n",
			       total_steps, dynamic_cmds_storage[j].name);
			printf("------------------------------------------------------------\n");
			printf("  Run command ............................... ");

			dynamic_cmds_storage[j].func(p);

			printf("DONE\n");
			printf("------------------------------------------------------------\n");
			printf("\n");
			if (total_steps == 1U) {
				printf("RESULT : command completed  -  CHECK DETAILED OUTPUT\n");
			} else {
				printf("RESULT : Step 1 of %u completed  -  CHECK DETAILED OUTPUT\n",
				       total_steps);
			}
			printf("\n");
			return;
		}
	}

	printf("Unknown command. Type 'help'.\n");
	return;

done_builtin:
	if (rc != 0 && rc != -EINVAL) {
		printf("Command failed (rc=%d)\n", rc);
	}
}

void cli_prompt(void) {
	printf("SoCFPGA Bare-Metal > ");
}


/* ============================================================================
 * CLI Main Loop
 * ============================================================================
 */
void cli_run(void){

	for(;;){
		cli_prompt();
		size_t idx=0;

		for(;;){
			char c=uart_getc();
			if(c=='\t'){
				cli_handle_tab(cli_buf, &idx);
				continue;
			}
			if(c=='\r') c='\n';
			if(c=='\n'){
				uart_putc('\n');
				cli_buf[idx]='\0';
				break;
			}
			if(c==0x7f||c==0x08){
				if(idx>0){ idx--; uart_putc('\b'); uart_putc(' '); uart_putc('\b'); }
				continue;
			}
			if(c>=32 && idx+1<CLI_BUFSZ){
				cli_buf[idx++]=c;
				uart_putc(c);
			}
		}
		if(idx==0) continue;
		cli_dispatch(cli_buf);
	}
}
