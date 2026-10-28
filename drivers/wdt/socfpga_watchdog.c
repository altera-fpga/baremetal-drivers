/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_watchdog.c
 *
 * Watchdog source implementation for the SoCFPGA bare-metal software stack.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "errno.h"
#include "crt0.h"
#include "socfpga_watchdog.h"
#include "socfpga_watchdog_reg.h"
#include "mmio.h"
#include "socfpga_clk_mngr_ll.h"
#include "../gic/socfpga_interrupt.h"
#include "../../middleware/uart/socfpga_uart.h"
#include "../../api/uart/uart_api.h"

struct wdt_descriptor
{
    uint32_t base_addr;
    uint32_t instance;
    BaseType_t is_open;
    BaseType_t is_config_done;
    wdt_callback_t callback;
    uint32_t clk_hz;
    void *cb_usercontext;
};


static struct wdt_descriptor wdt_descriptors[MAX_WATCHDOG_INSTANCES];

static void de_assert_reset_signal(uint32_t instance);

void wdt_isr(void *pvhandle);

static bool set_response_mode(wdt_handle_t handle, wdt_timeout_config_t config);
static uint32_t ms_to_top(uint64_t clk_hz, uint32_t timeout_ms);
static uint32_t top_to_ms(uint64_t clk_hz, uint8_t top);

socfpga_hpu_interrupt_t get_intr_id(uint32_t instance);

wdt_handle_t wdt_open(uint32_t instance)
{
    wdt_handle_t handle;
    uint32_t clk_hz;
    if (!(instance < MAX_WATCHDOG_INSTANCES))
    {
        printf("Invalid watchdog instance");
        return NULL;
    }

    handle = &wdt_descriptors[instance];
    handle->instance = instance;
    de_assert_reset_signal(instance);

    if ((handle->is_open) == 1)
    {
        printf("Watchdog instance is already open");
        return NULL;
    }
    else
    {
        handle->base_addr = GET_WDT_BASE_ADDRESS(instance);
        handle->is_open = 1;

        /*Get the source clock value in Hz*/
        if (clk_mngr_ll_get_clk(CLOCK_WDT, &clk_hz) == 1U)
        {
            printf("Error while getting clock");
            return NULL;
        }
        handle->clk_hz = clk_hz;
        return handle;
    }
}

int32_t wdt_start(const wdt_handle_t hwdt)
{
    uint32_t val;
    if (hwdt == NULL)
    {
        printf("Invalid watchdog handle");
        return -EINVAL;
    }

    if (hwdt->is_config_done != 0x3)
    {
        printf("Configuration is not done");
        return -ENODATA;
    }

    printf("Starting Watchdog timer");
    val = RD_REG32(hwdt->base_addr + WDT_CR);
    val |= (1U << WDT_CR_WDT_EN_POS);
    WR_REG32(hwdt->base_addr + WDT_CR, val);
    return 0;
}

int32_t wdt_stop(const wdt_handle_t hwdt)
{
    uint32_t val;
    if (hwdt == NULL)
    {
        printf("Invalid watchdog handle");
        return -EINVAL;
    }

    val = RD_REG32((uint32_t)hwdt->base_addr + WDT_CR);
    val &= ~(1U << WDT_CR_WDT_EN_POS);
    WR_REG32(hwdt->base_addr + WDT_CR, val);

    printf("Watchdog timer stopped");
    return 0;
}

int32_t wdt_restart(const wdt_handle_t hwdt)
{
    uint32_t val;

    if (hwdt == NULL)
    {
        printf("Invalid watchdog handle");
        return -EINVAL;
    }

    if (hwdt->is_config_done != 0x3)
    {
        printf("Configuration is not done");
        return -ENODATA;
    }

    printf("Restarting Watchdog timer");
    val = (WDT_CRR_RESTART_VAL << WDT_CRR_WDT_CRR_POS);
    WR_REG32(hwdt->base_addr + WDT_CRR, val);

    return 0;
}

int32_t wdt_ioctl(const wdt_handle_t hwdt, wdt_ioctl_t cmd, void *const buf)
{
    uint32_t val;
    uint32_t timeout_ms;
    uint32_t timeout;
    uint32_t stat;

    int32_t ret = 0;
    if ((hwdt == NULL) || (buf == NULL))
    {
        printf("Invalid parameters");
        return -EINVAL;
    }

    switch (cmd)
    {
        case WDT_SET_INIT_TIMEOUT:
            timeout_ms = *(uint32_t *)buf;
            timeout = ms_to_top(hwdt->clk_hz, timeout_ms);
            val = RD_REG32(hwdt->base_addr + WDT_TORR);
            val &= ~(WDT_TORR_TOP_INIT_MASK);
            val |= (timeout << WDT_TORR_TOP_INIT_POS);
            WR_REG32(hwdt->base_addr + WDT_TORR, val);
            hwdt->is_config_done |= 0x1;
            break;

        case WDT_GET_INIT_TIMEOUT:
            val = RD_REG32(hwdt->base_addr + WDT_TORR);
            val = ((val & WDT_TORR_TOP_INIT_MASK) >> WDT_TORR_TOP_INIT_POS);

            timeout_ms = top_to_ms(hwdt->clk_hz, val);
            *(uint32_t *)buf = timeout_ms;
            break;

        case WDT_SET_TIMEOUT:

            timeout_ms = *(uint32_t *)buf;
            timeout = ms_to_top(hwdt->clk_hz, timeout_ms);
            val = RD_REG32(hwdt->base_addr + WDT_TORR);
            val &= ~(WDT_TORR_TOP_MASK);
            val |= (timeout << WDT_TORR_TOP_POS);
            WR_REG32(hwdt->base_addr + WDT_TORR, val);
            hwdt->is_config_done |= 0x2;

            break;

        case WDT_GET_TIMEOUT:
            val = RD_REG32(hwdt->base_addr + WDT_TORR);
            val &= WDT_TORR_TOP_MASK;
            timeout_ms = top_to_ms(hwdt->clk_hz, val);
            *(uint32_t *)buf = timeout_ms;
            break;

        case WDT_GET_STATUS:

            stat = RD_REG32(hwdt->base_addr + WDT_STAT);
            if (stat == 1U)
            {
                *(wdt_status_t *)buf = WDT_EXPIRED;
            }
            else
            {
                *(wdt_status_t *)buf = WDT_RUNNING;
            }
            break;

        case WDT_SET_TIMEOUT_BEHAVIOUR:
            if (set_response_mode(hwdt, *(wdt_timeout_config_t *)buf) == false)
            {
                printf("Failed to set response mode");
                ret = -EINVAL;
            }
            break;

        default:
            printf("Invalid IOCTL request");
            ret = -EINVAL;
            break;
    }
    return ret;
}

void wdt_set_callback(const wdt_handle_t hwdt, wdt_callback_t callback,
        void *param)
{
    if (hwdt == NULL)
    {
        printf("Invalid watchdog handle");
        return;
    }
    hwdt->callback = callback;
    hwdt->cb_usercontext = param;
}

int32_t wdt_close(const wdt_handle_t hwdt)
{
    if (hwdt == NULL)
    {
        printf("Invalid watchdog handle");
        return -EINVAL;
    }
    if (!hwdt->is_open)
    {
        printf("Watchdog instance is not open");
        return -EINVAL;
    }

    int32_t stop = wdt_stop(hwdt);
    if (stop != 0)
    {
        printf("Failed to stop watchdog timer");
        return -EINVAL;
    }
    hwdt->is_open = 0;
    hwdt->is_config_done = 0;
    return 0;
}

/*
 * Interrupt Service Routine for Watchdog timer
 */
void wdt_isr(void *handle)
{
    wdt_handle_t hwdt = (wdt_handle_t)handle;
    if (hwdt->callback != NULL)
    {
        hwdt->callback(hwdt->cb_usercontext);
    }
}



/*
 * Set the response mode as system reset or generate interrupt and reset the system
 */
static bool set_response_mode(wdt_handle_t handle, wdt_timeout_config_t config)
{
    uint32_t val;
    socfpga_hpu_interrupt_t interrupt_id;
    socfpga_interrupt_err_t int_ret;

    if (config == WDT_TIMEOUT_INTR)
    {
        val = RD_REG32(handle->base_addr + WDT_CR);
        val |= (1U << WDT_CR_RMOD_POS);
        WR_REG32(handle->base_addr + WDT_CR, val);

        interrupt_id = get_intr_id(handle->instance);
        int_ret = interrupt_enable(interrupt_id, GIC_INTERRUPT_PRIORITY_WDOG);
        if (int_ret != ERR_OK)
        {
            return false;
        }
        int_ret = interrupt_register_isr(interrupt_id, wdt_isr, handle);
        if (int_ret != ERR_OK)
        {
            return false;
        }
    }
    else
    {
        val = RD_REG32(handle->base_addr + WDT_CR);
        val &= ~(1U << WDT_CR_RMOD_POS);
        WR_REG32(handle->base_addr + WDT_CR, val);
    }
    return true;
}



/*
 * Get the interrupt id based on instance
 */

socfpga_hpu_interrupt_t get_intr_id(uint32_t instance)
{
    socfpga_hpu_interrupt_t intr_id = WDOG0IRQ;
    switch (instance)
    {
        case 0:
            intr_id = WDOG0IRQ;
            break;

        case 1:
            intr_id = WDOG1IRQ;
            break;

        case 2:
            intr_id = WDOG2IRQ;
            break;

        case 3:
            intr_id = WDOG3IRQ;
            break;

        case 4:
            intr_id = WDOG4IRQ;
            break;

        default:
            /*Do nothing*/
            break;
    }

    return intr_id;
}

/*
 * Deassert the reset signal for the Watchdog instance
 */
static void de_assert_reset_signal(uint32_t instance)
{
    uint32_t val;
    if (instance == 0U)
    {
        val = RD_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET);
        val &= ~(1U << WDT0_RESET_BIT);
        WR_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET, val);
    }

    if (instance == 1U)
    {
        val = RD_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET);
        val &= ~(1U << WDT1_RESET_BIT);
        WR_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET, val);
    }

    if (instance == 2U)
    {
        val = RD_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET);
        val &= ~(1U << WDT2_RESET_BIT);
        WR_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET, val);
    }

    if (instance == 3U)
    {
        val = RD_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET);
        val &= ~(1U << WDT3_RESET_BIT);
        WR_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET, val);
    }

    if (instance == 4U)
    {
        val = RD_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET);
        val &= ~((uint32_t)1U << WDT4_RESET_BIT);
        WR_REG32(SOCFPGA_RESET_MANAGER_BASE + WDT_PER1MODRST_OFFSET, val);
    }
}

static uint32_t ms_to_top(uint64_t clk_hz, uint32_t timeout_ms)
{
    uint64_t ticks = 0UL;
    uint32_t top = 0U;

    /*
     * As per WDT hardware ticks for timeout  = (2 ^ (TOP + 16))
     * We will round the top to provide at least the desired timeout
     * This means we are rounding up
     * This can be achieved by using top = log2(ticks - 1) - 15
     */

    if (timeout_ms != 0)
    {
        ticks = (((uint64_t)clk_hz * timeout_ms) / 1000U) - 1;
    }

    /* find log2 */
    while (ticks > 1U)
    {
        ticks >>= 1U;
        top++;
    }
    top = (top > 15U) ? (top - 15U) : 0U;
    if (top > 15U)
    {
        printf(
                "Timeout exceeds watchdog counter width. Limiting to maximum supported value");
        top = 15U;
    }

    return top;
}

static uint32_t top_to_ms(uint64_t clk_hz, uint8_t top)
{
    uint64_t timeout_ms;
    /* As per WDT hardware ticks for timeout  = (2 ^ (TOP + 16) ) */
    timeout_ms = ((1UL << (top + 16)) * 1000UL) / clk_hz;
    return (uint32_t)timeout_ms;
}

