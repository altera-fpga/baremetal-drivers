/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: mailbox_selftest.c
 *
 * Mailbox Example source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: examples
 * Component: Mailbox Example
 */

#include <stdio.h>
#include <stdint.h>
#include "console_api.h"
#include "example_register.h"
#include "mailbox_api.h"

/*
 * DDR scratch buffer used for commands that return payload data.
 * Must satisfy ATF is_address_in_ddr_range() (addr >= BL31_LIMIT).
 */
#define MBOX_DDR_RESP_ADDR  0x82100000UL

#define PF(r)  ((r) == MAILBOX_OK ? "PASS" : "FAIL")

static void mailbox_example_main(const char *args)
{
    (void)args;
    int32_t ret;
    volatile uint32_t *resp = (volatile uint32_t *)MBOX_DDR_RESP_ADDR;

    if (mailbox_init() != MAILBOX_OK) {
        printf("[MBOX][FAIL] init\n");
        return;
    }
    printf("[MBOX] init OK\n");

    /* NOOP: no response payload (V1 sync SiP path). */
    ret = mailbox_exec(MAILBOX_CMD_NOOP, NULL, 0U, NULL, 0U);
    printf("[MBOX][%s] NOOP: ret=%d\n", PF(ret), ret);

    /* GET_IDCODE: 1-word payload in DDR response buffer. */
    resp[0] = 0U;
    ret = mailbox_exec(MAILBOX_CMD_GET_IDCODE, NULL, 0U,
                       (uint32_t *)MBOX_DDR_RESP_ADDR, 1U);
    printf("[MBOX][%s] GET_IDCODE: ret=%d idcode=0x%08x\n",
           PF(ret), ret, (unsigned int)resp[0]);

    /* CONFIG_STATUS: 6-word status payload. */
    for (uint32_t i = 0U; i < MAILBOX_CONFIG_STATUS_RESP_WORDS; i++) {
        resp[i] = 0U;
    }
    ret = mailbox_exec(MAILBOX_CMD_CONFIG_STATUS, NULL, 0U,
                       (uint32_t *)MBOX_DDR_RESP_ADDR,
                       MAILBOX_CONFIG_STATUS_RESP_WORDS);
    printf("[MBOX][%s] CONFIG_STATUS: ret=%d state=0x%08x pin=0x%08x softfunc=0x%08x\n",
           PF(ret), ret,
           (unsigned int)resp[0], (unsigned int)resp[2],
           (unsigned int)resp[3]);

    mailbox_deinit();
    printf("[MBOX] done\n");
}

void register_mailbox_example(void)
{
    cli_register_command("mailbox_selftest", mailbox_example_main);
}

APP_REGISTER(register_mailbox_example)
