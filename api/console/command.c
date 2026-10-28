/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "command.h"
#include "console_api.h"

/* Dynamic command storage is declared by console_api.h. */

/* ============================================================================
 * System register access
 * ============================================================================
 */

uint64_t read_mpidr_el1(void) {
	uint64_t val;
	__asm__ __volatile__("mrs %0, mpidr_el1" : "=r"(val));
	return val;
}


uint64_t read_currentel(void) {
	uint64_t val;
	__asm__ __volatile__("mrs %0, CurrentEL" : "=r"(val));
	return (val >> 2) & 0x3;
}


/* ============================================================================
 * Command Implementations
 * ============================================================================
 */
static const char *cmd_example_description(const char *name)
{
	if (name == NULL) return "run self-test";

	if (cstrcmp(name, "bridge_selftest") == 0) return "HPS-FPGA bridge enable/disable checks";
	if (cstrcmp(name, "ccu_selftest") == 0) return "CCU ID, error status, and L3 flush";
	if (cstrcmp(name, "clk_mngr_selftest") == 0) return "clock manager divider and frequency checks";
	if (cstrcmp(name, "combophy_selftest") == 0) return "Combo PHY version/features query";
	if (cstrcmp(name, "crc_selftest") == 0) return "CRC calculate/validate scenarios";
	if (cstrcmp(name, "dma_selftest") == 0) return "DMA transfer and completion checks";
	if (cstrcmp(name, "ecc_selftest") == 0) return "ECC inject/status checks";
	if (cstrcmp(name, "fcs_selftest") == 0) return "FCS session and random service checks";
	if (cstrcmp(name, "gic_selftest") == 0) return "GIC SGI interrupt self-test";
	if (cstrcmp(name, "gpio_selftest") == 0) return "GPIO read/write path check";
	if (cstrcmp(name, "hello_selftest") == 0) return "basic shell command sanity check";
	if (cstrcmp(name, "i2c_selftest") == 0) return "I2C controller, timing, scan and transfer checks";
	if (cstrcmp(name, "i3c_selftest") == 0) return "I3C status, legacy-I2C, private xfer";
	if (cstrcmp(name, "mailbox_selftest") == 0) return "mailbox CONFIG_STATUS query";
	if (cstrcmp(name, "ddr_selftest") == 0) return "DDR init/BIST and memory validation";
	if (cstrcmp(name, "mmu_selftest") == 0) return "MMU enable-state query";
	if (cstrcmp(name, "noc_selftest") == 0) return "NOC firewall and error-logger checks";
	if (cstrcmp(name, "reboot_mngr_selftest") == 0) return "reboot manager warm/cold paths";
	if (cstrcmp(name, "reset_mngr_selftest") == 0) return "peripheral reset controls/status";
	if (cstrcmp(name, "sdmmc_selftest") == 0) return "SDMMC write/read/verify pattern test";
	if (cstrcmp(name, "seu_selftest") == 0) return "SEU inject and status handling";
	if (cstrcmp(name, "smmu_selftest") == 0) return "SMMU enable-state query";
	if (cstrcmp(name, "spi_selftest") == 0) return "SPI probe, loopback, and status";
	if (cstrcmp(name, "timer_selftest") == 0) return "timer start/poll and timeout checks";
	return "run self-test";
}

static void cmd_print_example_line(const char *name, const char *desc)
{
	const size_t name_col_width = 26U;
	size_t len = 0U;

	if (name == NULL) {
		name = "";
	}
	if (desc == NULL) {
		desc = "";
	}

	while (name[len] != '\0') {
		len++;
	}

	printf("  %s", name);

	if (len < name_col_width) {
		size_t pad = name_col_width - len;
		for (size_t i = 0; i < pad; i++) {
			printf(" ");
		}
	} else {
		printf(" ");
	}

	printf("- %s\n", desc);
}

int cmd_help(void) {
	printf("Commands:\n");
	printf("  help      - show this help\n");
	printf("  core      - show current core id\n");
	printf("  mpidr     - dump mpidr_el1 hex\n");
	printf("  el        - show current EL\n");
	printf("  clear     - clear console screen\n");
	printf("  memdump   - dump memory: memdump <addr> [count]\n");
	printf("  memread   - read 32-bit value: memread <addr>\n");
	printf("  memwrite  - write 32-bit value: memwrite <addr> <value>\n");
	printf("  exit      - exit shell (hang)\n");
	printf("\n");
	printf("Example Applications:\n");
	/* Add dynamic commands. */
	for (int i = 0; i < cli_get_command_count(); i++) {
		const cli_cmd_t *cmd = cli_get_command(i);
		if ((cmd != NULL) && (cmd->name != NULL)) {
			cmd_print_example_line(cmd->name,
					      cmd_example_description(cmd->name));
		}
	}
	printf("\n");
	return 0;
}


int cmd_core(void) {
	uint64_t mp = read_mpidr_el1();
	uint32_t aff1 = (mp >> 8) & 0xFF;
	printf("Currently running on Core %u\n", aff1);
	return 0;
}


int cmd_mpidr(void) {
	uint64_t mp = read_mpidr_el1();
	printf("MPIDR_EL1 = 0x%016llX\n", mp);
	return 0;
}


int cmd_el(void) {
	uint32_t el = (uint32_t)read_currentel();
	printf("Current EL: %u\n", el);
	return 0;
}

int cmd_clear(void)
{
	/* ANSI clear screen + cursor home. */
	printf("\033[2J\033[H");
	return 0;
}


/* memdump <addr> [count] */
int cmd_memdump(const char *args) {
	if (!args || !*args) {
		printf("Usage: memdump <addr> [count]\n");
		return -EINVAL;
	}

	const char *p = args;
	while (*p == ' ') p++;
	uint64_t addr = parse_hex(p);
	while (*p && *p != ' ') p++;
	while (*p == ' ') p++;

	uint32_t count = 16;
	if (*p) count = parse_dec(p);
	if (count == 0) count = 1;

	volatile uint8_t *ptr = (volatile uint8_t *)(uintptr_t)addr;

	for (uint32_t i = 0; i < count; i += 16) {
		printf("%08lX: ", (unsigned long)(uintptr_t)(ptr + i));
		for (uint32_t j = 0; j < 16 && (i + j) < count; j++) {
			uint8_t val = ptr[i + j];
			printf("%02X ", val);
		}
		printf("\n");
	}

	return 0;
}


/* memread <addr> */
int cmd_memread(const char *args) {
	if (!args || !*args) {
		printf("Usage: memread <addr>\n");
		return -EINVAL;
	}
	const char *p = args;
	while (*p == ' ') p++;
	uint64_t addr = parse_hex(p);

	volatile uint32_t *ptr = (volatile uint32_t *)(uintptr_t)addr;
	uint32_t val = *ptr;

	printf("[0x%08lX] = 0x%08lX\n", (unsigned long)addr, (unsigned long)val);
	return 0;
}


/* memwrite <addr> <value> */
int cmd_memwrite(const char *args) {
	if (!args || !*args) {
		printf("Usage: memwrite <addr> <value>\n");
		return -EINVAL;
	}
	const char *p = args;
	while (*p == ' ') p++;
	uint64_t addr = parse_hex(p);

	while (*p && *p != ' ') p++;
	while (*p == ' ') p++;

	if (!*p) {
		printf("Usage: memwrite <addr> <value>\n");
		return -EINVAL;
	}

	uint32_t val = (uint32_t)parse_hex(p);

	volatile uint32_t *ptr = (volatile uint32_t *)(uintptr_t)addr;
	*ptr = val;

	printf("Wrote 0x%08lX to [0x%08lX]\n", (unsigned long)val, (unsigned long)addr);
	return 0;
}
