/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: clk_mngr_platform.c
 *
 * Agilex5 source implementation for the SoCFPGA bare-metal software stack.
 *
 * This topic is intentionally placed near the top of the file so Natural Docs can
 * include the file in the generated reference tree and group the documented
 * functions, types, callbacks, and register helper declarations under a clear
 * module-level entry.
 *
 * Layer: platform
 * Component: Agilex5
 */

#include <stdio.h>
#include "errno.h"
#include "../include/crt0.h"
#include "clk_mngr_api.h"
#include "platform_def.h"

/* Default NOCDIV divisors for Agilex5 platform, validated on HW */
static const struct {
    uint32_t clock_type;
    uint8_t  divisor;
    const char *name;
} platform_clk_defaults[] = {
    { CLK_MNGR_DIV_L4_SYS_FREE, 4U, "L4_SYS_FREE" },
    { CLK_MNGR_DIV_L4_MP,       2U, "L4_MP"       },
    { CLK_MNGR_DIV_L4_SP,       4U, "L4_SP"       },
    { CLK_MNGR_DIV_SOFT_PHY,    1U, "SOFT_PHY"    },
    { CLK_MNGR_DIV_CCU,         2U, "CCU"         },
    { CLK_MNGR_DIV_MPU_PERIPH,  4U, "MPU_PERIPH"  },
    { CLK_MNGR_DIV_CS,          1U, "CS_CLK"      },
    { CLK_MNGR_DIV_CS_TRACE,    4U, "CS_TRACE"    },
    { CLK_MNGR_DIV_CS_PDBG,     4U, "CS_PDBG"     },
};

#define PLATFORM_CLK_DEFAULTS_COUNT \
    (sizeof(platform_clk_defaults) / sizeof(platform_clk_defaults[0]))

/* Agilex5 platform clock initialisation.
 *
 * Programs all NOCDIV divisor fields to the Agilex5 validated defaults.
 * Called from clk_mngr_api_init() during platform bring-up.
 *
 * Returns: 0 on success, negative if any divisor write fails.
 */
int clk_mngr_platform_init(void)
{
    int rc = 0;

	for (uint32_t i = 0U; i < PLATFORM_CLK_DEFAULTS_COUNT; i++)
	{
		int ret = clk_mngr_api_set_divisor(platform_clk_defaults[i].clock_type,
										   platform_clk_defaults[i].divisor);
		if (ret != 0)
		{
			printf("[clk_mngr_platform:agilex5] set_divisor failed for %s (rc=%d)\n",
				   platform_clk_defaults[i].name, ret);
			rc = ret;
		}
	}

    return rc;
}

#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)
/* Agilex5 PLL bring-up for the standalone OCRAM/FSBL boot, ported from ATF BL2
 * (pre-lock steps + config_clkmgr_handoff) to lock the L4_SP/UART to 100 MHz. */
#define CM_BASE			0x10D10000U
#define CM_CTRL			(CM_BASE + 0x000U)
#define CM_STAT			(CM_BASE + 0x004U)
#define CM_INTRCLR		(CM_BASE + 0x014U)
#define CM_M_BYPASS		(CM_BASE + 0x030U)
#define CM_M_NOCCLK		(CM_BASE + 0x040U)
#define CM_M_NOCDIV		(CM_BASE + 0x044U)
#define CM_M_PLLGLOB		(CM_BASE + 0x048U)
#define CM_M_FDBCK		(CM_BASE + 0x04CU)
#define CM_M_MEM		(CM_BASE + 0x050U)
#define CM_M_MEMSTAT		(CM_BASE + 0x054U)
#define CM_M_VCOCALIB		(CM_BASE + 0x058U)
#define CM_M_PLLC0		(CM_BASE + 0x05CU)
#define CM_M_PLLC1		(CM_BASE + 0x060U)
#define CM_M_PLLC2		(CM_BASE + 0x064U)
#define CM_M_PLLC3		(CM_BASE + 0x068U)
#define CM_M_PLLM		(CM_BASE + 0x06CU)
#define CM_M_LOSTLOCK		(CM_BASE + 0x078U)
#define CM_P_BYPASS		(CM_BASE + 0x088U)
#define CM_P_PLLGLOB		(CM_BASE + 0x09CU)
#define CM_P_FDBCK		(CM_BASE + 0x0A0U)
#define CM_P_MEM		(CM_BASE + 0x0A4U)
#define CM_P_MEMSTAT		(CM_BASE + 0x0A8U)
#define CM_P_VCOCALIB		(CM_BASE + 0x0ACU)
#define CM_P_PLLC0		(CM_BASE + 0x0B0U)
#define CM_P_PLLC1		(CM_BASE + 0x0B4U)
#define CM_P_PLLC2		(CM_BASE + 0x0B8U)
#define CM_P_PLLC3		(CM_BASE + 0x0BCU)
#define CM_P_PLLM		(CM_BASE + 0x0C0U)
#define CM_P_LOSTLOCK		(CM_BASE + 0x0CCU)
#define CM_C_EXTCNTRST		(CM_BASE + 0x0F4U)

#define CM_CTRL_BOOTMODE	(1U << 0)
/* Software-controlled boot clock: enable (bit 8) and select the HPS internal
 * oscillator (bit 9). The real-silicon FSBL path (U-Boot clk-agilex5.c SPL)
 * forces these on before PLL config so the PLL source-sync/membus interface has
 * a running boot clock; without them the membus never acknowledges. ATF's
 * Simics-oriented code omits them because that environment already clocks it. */
#define CM_CTRL_SWBTCLKEN	(1U << 8)
#define CM_CTRL_SWBTCLKSEL	(1U << 9)
#define CM_STAT_BUSY		(1U << 0)
#define CM_STAT_MLOCK		(1U << 8)
#define CM_STAT_PLOCK		(1U << 16)
#define CM_GLOB_PD_N		(1U << 0)
#define CM_GLOB_RST_N		(1U << 1)
#define CM_GLOB_CLR_LL_BYP	(1U << 29)
#define CM_PLLCX_EN		(1U << 27)
#define CM_BYP_MAIN_ALL		0xF6U
#define CM_BYP_PER_ALL		0xEFU
#define CM_LOSTLOCK_BYPCLR	(1U << 0)
#define CM_INTRCLR_MLOST	(1U << 2)
#define CM_INTRCLR_PLOST	(1U << 3)
#define CM_EXTCNTRST_ALL	0x3DEFU

#define CM_MEM_REQ		(1U << 24)
#define CM_MEM_WR		(1U << 25)
#define CM_MEM_WDAT_OFS		16
#define CM_MEM_ADDR_MASK	0xFFFFU
#define CM_MEM_ADDR_START	0x4000U

#define CM_FSM_RETRY		1000U
#define CM_MEM_RETRY		1000U
#define CM_LOCK_RETRY		1000U
#define CM_LOCK_STABLE		5U

static inline uint32_t cm_rd(uint32_t a) { return *(volatile uint32_t *)(uintptr_t)a; }
static inline void cm_wr(uint32_t a, uint32_t v) { *(volatile uint32_t *)(uintptr_t)a = v; dsb(); }
static inline void cm_set(uint32_t a, uint32_t m) { cm_wr(a, cm_rd(a) | m); }
static inline void cm_clr(uint32_t a, uint32_t m) { cm_wr(a, cm_rd(a) & ~m); }

/* Wait for the clock-manager FSM to go idle (BUSY == 0). */
static int cm_wait_fsm(void)
{
	uint32_t c = 0;

	while ((cm_rd(CM_STAT) & CM_STAT_BUSY) != 0U) {
		if (++c >= CM_FSM_RETRY) {
			return -ETIMEDOUT;
		}
	}
	return 0;
}

/* Mirror of ATF calc_pll_vcocalibration(): MSCNT_CONST=100, HSCNT_CONST=4. */
static uint32_t cm_vcocalib(uint32_t pllm, uint32_t glob)
{
	uint32_t mdiv = pllm & 0x3FFU;
	uint32_t drefclkdiv = (glob >> 12) & 0x3U;
	uint32_t refclkdiv = (glob >> 8) & 0x3FU;
	uint32_t mscnt, hscnt;

	if (mdiv == 0U || refclkdiv == 0U) {
		return 0U;
	}
	mscnt = 100U / (mdiv * (1U << drefclkdiv));
	if (mscnt == 0U) {
		mscnt = 1U;
	}
	hscnt = (mdiv * mscnt * (1U << drefclkdiv) / refclkdiv) - 4U;
	return (hscnt & 0x3FFU) | ((mscnt << 16) & 0xFF0000U);
}

/* Poll the PLL membus until the request bit clears (mirror pll_source_sync_wait). */
static int cm_mem_wait(uint32_t memreg)
{
	uint32_t c = 0;

	while ((cm_rd(memreg) & CM_MEM_REQ) != 0U) {
		if (++c >= CM_MEM_RETRY) {
			return -ETIMEDOUT;
		}
	}
	return 0;
}

/* PLL power-down analog config over the membus (ATF config_pll_pd_state).
 * Entry 0 (source-sync mode) is required to lock. Returns membus timeout count. */
static uint32_t cm_pll_pd_state(uint32_t memreg, uint32_t memstat)
{
	static const struct { uint32_t addr; uint32_t data; uint32_t mask; } cfg[] = {
		{ 0x27U, (1U << 7), (1U << 7) },	/* enable source synchronous mode */
		{ 0xB3U, (1U << 0), (1U << 0) },	/* limit overshoot frequency at lock */
		{ 0xE6U, (1U << 0), (1U << 0) },	/* longer settle before lock asserted */
		{ 0x03U, 0x4AU, 0x7FU },		/* duty cycle, clock slice 0 */
		{ 0x07U, 0x4AU, 0x7FU },		/* duty cycle, clock slice 1 */
	};
	uint32_t timeouts = 0U;

	for (unsigned i = 0; i < (sizeof(cfg) / sizeof(cfg[0])); i++) {
		uint32_t a = (cfg[i].addr | CM_MEM_ADDR_START) & CM_MEM_ADDR_MASK;
		uint32_t r = 0U;

		/* Read-modify-write the membus register. */
		cm_wr(memreg, CM_MEM_REQ | a);
		if (cm_mem_wait(memreg) == 0) {
			r = cm_rd(memstat);
		} else {
			timeouts++;
		}
		cm_wr(memreg, CM_MEM_REQ | CM_MEM_WR |
		      ((((r & ~cfg[i].mask) | cfg[i].data) << CM_MEM_WDAT_OFS)) | a);
		if (cm_mem_wait(memreg) != 0) {
			timeouts++;
		}
	}
	return timeouts;
}

/* Wait for both PLLs to report a stable lock (mirror wait_pll_lock). */
static int cm_wait_lock(void)
{
	uint32_t c = 0, stable = 0;

	while (c < CM_LOCK_RETRY) {
		if ((cm_rd(CM_STAT) & (CM_STAT_MLOCK | CM_STAT_PLOCK)) ==
		    (CM_STAT_MLOCK | CM_STAT_PLOCK)) {
			if (++stable >= CM_LOCK_STABLE) {
				return 0;
			}
		} else {
			stable = 0;
		}
		c++;
	}
	return -ETIMEDOUT;
}

/* BL2 opens the L4 firewalls and deasserts the peripheral resets before the
 * clock-manager handoff; mirror that here. No pins are touched. */
#define L4_PER_SCR_BASE		0x10D21000U
#define L4_SYS_SCR_BASE		0x10D21100U
#define SOC2FPGA_SCR		0x10D21200U
#define LWSOC2FPGA_SCR		0x10D21300U
#define DISABLE_L4_FW		0x01010001U	/* AXI_AP | FPGA2SOC | MPU */
#define DISABLE_BRIDGE_FW	0x0FFE0101U

#define RSTMGR_BASE		0x10D11000U
#define RSTMGR_PER0MODRST	(RSTMGR_BASE + 0x024U)
#define RSTMGR_PER1MODRST	(RSTMGR_BASE + 0x028U)
#define RSTMGR_BRGMODRST	(RSTMGR_BASE + 0x02CU)
#define PER0_DEASSERT_MASK	0xFF7FBFFFU	/* emac/usb/nand/sdmmc/spi/dma(+ocp/if) */
#define PER1_DEASSERT_MASK	0x07037FFFU	/* wdog/systimer/sptimer/i2c/i3c/uart/gpio */
#define BRG_MPFE		0x00000040U

static void cm_enable_ns_access(void)
{
	/* L4 peripheral firewall (Agilex5 set, NAND_DATA excluded). */
	static const uint16_t per_off[] = {
		0x00, 0x0c, 0x10, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34,
		0x40, 0x44, 0x48, 0x50, 0x54, 0x58, 0x5c, 0x60, 0x64, 0x68,
		0x6c, 0x70,
	};
	/* L4 system firewall (Agilex5 set: ECC, CLK_MGR, IO_MGR, RST_MGR,
	 * SYS_MGR, OSC timers, watchdogs, DAP, PWRMGR, NOC). */
	static const uint16_t sys_off[] = {
		0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x2c, 0x30, 0x34,
		0x38, 0x40, 0x44, 0x48, 0x4c, 0x54, 0x58, 0x5c, 0x60, 0x64,
		0x68, 0x6c, 0x70, 0x74, 0x78, 0x7c, 0x80, 0x84, 0x88, 0x90,
		0x94,
	};
	unsigned i;

	for (i = 0; i < sizeof(per_off) / sizeof(per_off[0]); i++) {
		cm_wr(L4_PER_SCR_BASE + per_off[i], DISABLE_L4_FW);
	}
	for (i = 0; i < sizeof(sys_off) / sizeof(sys_off[0]); i++) {
		cm_wr(L4_SYS_SCR_BASE + sys_off[i], DISABLE_L4_FW);
	}
	cm_wr(SOC2FPGA_SCR, DISABLE_BRIDGE_FW);
	cm_wr(LWSOC2FPGA_SCR, DISABLE_BRIDGE_FW);
}

static void cm_deassert_periph_reset(void)
{
	cm_clr(RSTMGR_PER1MODRST, PER1_DEASSERT_MASK);
	cm_clr(RSTMGR_PER0MODRST, PER0_DEASSERT_MASK);
	cm_clr(RSTMGR_BRGMODRST, BRG_MPFE);
}

/* Replay the SDM handoff pinmux (ATF config_pinmux). Required to lock the PLL:
 * it clocks the source-sync membus. Blob at 0x0007F000 is big-endian. */
#define HOFF_BASE		0x0007F000U
#define PINMUX_PIN0SEL		0x10D13000U
#define PINMUX_IO0CTRL		0x10D13130U
#define PINMUX_FPGA_BASE	0x10D13300U	/* EMAC0_USEFPGA (USEFPGA base) */
#define PINMUX_IO0_DELAY	0x10D13400U
#define SYSMGR_FPGAINTF_EN_2	0x10D1206CU
#define SYSMGR_FPGAINTF_EN_3	0x10D12070U

#define HOFF_HDR_MAGIC		0x000U	/* 'BOOT' */
#define HOFF_SEL_MAGIC		0x010U	/* 'PMUX' */
#define HOFF_SEL_ARRAY		0x020U
#define HOFF_IO_MAGIC		0x1A0U	/* 'IOCT' */
#define HOFF_IO_ARRAY		0x1B0U
#define HOFF_FPGA_MAGIC		0x330U	/* 'FPGA' */
#define HOFF_FPGA_ARRAY		0x340U
#define HOFF_DLAY_MAGIC		0x3F0U	/* 'DLAY' */
#define HOFF_DLAY_ARRAY		0x400U

static uint32_t ho_rd(uint32_t byte_off)
{
	volatile uint32_t *ho = (volatile uint32_t *)(uintptr_t)HOFF_BASE;

	return __builtin_bswap32(ho[byte_off / 4U]);
}

static void cm_config_fpgaintf(void)
{
	uint32_t v = 0U;

	if ((cm_rd(PINMUX_FPGA_BASE + 0x20U) & 0x1U) != 0U) { v |= (1U << 4); }	/* NAND */
	if ((cm_rd(PINMUX_FPGA_BASE + 0x54U) & 0x1U) != 0U) { v |= (1U << 8); }	/* SDMMC */
	if ((cm_rd(PINMUX_FPGA_BASE + 0x28U) & 0x1U) != 0U) { v |= (1U << 16); }	/* SPIM0 */
	if ((cm_rd(PINMUX_FPGA_BASE + 0x2CU) & 0x1U) != 0U) { v |= (1U << 24); }	/* SPIM1 */
	cm_wr(SYSMGR_FPGAINTF_EN_2, v);

	v = 0U;
	if ((cm_rd(PINMUX_FPGA_BASE + 0x00U) & 0x1U) != 0U) { v |= (1U << 0); }	/* EMAC0 */
	if ((cm_rd(PINMUX_FPGA_BASE + 0x04U) & 0x1U) != 0U) { v |= (1U << 8); }	/* EMAC1 */
	if ((cm_rd(PINMUX_FPGA_BASE + 0x08U) & 0x1U) != 0U) { v |= (1U << 16); }	/* EMAC2 */
	cm_wr(SYSMGR_FPGAINTF_EN_3, v);
}

static void platform_config_pinmux(void)
{
	unsigned i;

	if (ho_rd(HOFF_HDR_MAGIC) != 0x424F4F54U) {	/* 'BOOT' */
		return;
	}
	if (ho_rd(HOFF_SEL_MAGIC) == 0x504D5558U) {	/* 'PMUX' */
		for (i = 0U; i < 96U; i += 2U) {
			cm_wr(PINMUX_PIN0SEL + ho_rd(HOFF_SEL_ARRAY + i * 4U),
			      ho_rd(HOFF_SEL_ARRAY + (i + 1U) * 4U));
		}
	}
	if (ho_rd(HOFF_IO_MAGIC) == 0x494F4354U) {	/* 'IOCT' */
		for (i = 0U; i < 96U; i += 2U) {
			cm_wr(PINMUX_IO0CTRL + ho_rd(HOFF_IO_ARRAY + i * 4U),
			      ho_rd(HOFF_IO_ARRAY + (i + 1U) * 4U));
		}
	}
	if (ho_rd(HOFF_FPGA_MAGIC) == 0x46504741U) {	/* 'FPGA' */
		for (i = 0U; i < 40U; i += 2U) {	/* BL2: ARRAY_SIZE(44) - 4 */
			cm_wr(PINMUX_FPGA_BASE + ho_rd(HOFF_FPGA_ARRAY + i * 4U),
			      ho_rd(HOFF_FPGA_ARRAY + (i + 1U) * 4U));
		}
	}
	if (ho_rd(HOFF_DLAY_MAGIC) == 0x444C4159U) {	/* 'DLAY' */
		for (i = 0U; i < 96U; i += 2U) {
			cm_wr(PINMUX_IO0_DELAY + ho_rd(HOFF_DLAY_ARRAY + i * 4U),
			      ho_rd(HOFF_DLAY_ARRAY + (i + 1U) * 4U));
		}
	}
	cm_config_fpgaintf();
}

int platform_pll_init(void)
{
	struct { uint32_t nocclk, nocdiv, glob, fdbck, c0, c1, c2, c3, pllm; } m;
	struct { uint32_t glob, fdbck, c0, c1, c2, c3, pllm; } p;
	uint32_t mvco, pvco;

	/* BL2 pre-lock flow (must run before the handoff, pinmux is what lets the
	 * PLL lock). uart_init() re-applies the console UART pins afterwards. */
	cm_enable_ns_access();
	cm_deassert_periph_reset();
	platform_config_pinmux();

	/* 100 MHz PLL recipe captured from the working ATF BL2 boot. Baked in so the
	 * FSBL does not depend on the SDM handoff blob. Cx carry the slice-enable bit
	 * (0x08000000). MAIN: 25 MHz x112 /C3(7) = 400 MHz L3, /4 = 100 MHz L4_SP. */
	m.glob = 0x15000103U;
	m.fdbck = 0x00000000U;
	m.c0 = 0x08000002U;
	m.c1 = 0x08000004U;
	m.c2 = 0x08000003U;
	m.c3 = 0x08000007U;
	m.pllm = 0x00000070U;
	m.nocclk = 0x00000000U;
	m.nocdiv = 0x28240098U;

	p.glob = 0x15000103U;
	p.fdbck = 0x00000000U;
	p.c0 = 0x08000002U;
	p.c1 = 0x08000005U;
	p.c2 = 0x0800007DU;
	p.c3 = 0x08000005U;
	p.pllm = 0x00000064U;

	/* Snapshot so a failed bring-up can be undone, keeping the SDM boot clock. */
	uint32_t save_ctrl = cm_rd(CM_CTRL);
	uint32_t save_mbyp = cm_rd(CM_M_BYPASS);
	uint32_t save_pbyp = cm_rd(CM_P_BYPASS);
	uint32_t save_mglob = cm_rd(CM_M_PLLGLOB);
	uint32_t save_pglob = cm_rd(CM_P_PLLGLOB);

	/* Enter boot mode (BL2 config_clkmgr_handoff). Do NOT touch SWCTRLBTCLKEN/SEL:
	 * that starves the PLL FSM/membus and the PLL never locks. */
	cm_set(CM_CTRL, CM_CTRL_BOOTMODE);

	/* Bypass all main + peripheral PLL clocks to the input reference. */
	cm_set(CM_M_BYPASS, CM_BYP_MAIN_ALL);
	(void)cm_wait_fsm();
	cm_set(CM_P_BYPASS, CM_BYP_PER_ALL);
	(void)cm_wait_fsm();

	/* Power down + hold both PLLs in reset. */
	cm_clr(CM_M_PLLGLOB, CM_GLOB_PD_N | CM_GLOB_RST_N);
	cm_clr(CM_P_PLLGLOB, CM_GLOB_PD_N | CM_GLOB_RST_N);

	/* Program the main-PLL dividers (RST_N kept low while programming). */
	mvco = cm_vcocalib(m.pllm, m.glob);
	cm_wr(CM_M_PLLGLOB, m.glob & ~CM_GLOB_RST_N);
	cm_wr(CM_M_FDBCK, m.fdbck);
	cm_wr(CM_M_VCOCALIB, mvco);
	cm_wr(CM_M_PLLC0, m.c0);
	cm_wr(CM_M_PLLC1, m.c1);
	cm_wr(CM_M_PLLC2, m.c2);
	cm_wr(CM_M_PLLC3, m.c3);
	cm_wr(CM_M_PLLM, m.pllm);
	cm_wr(CM_M_NOCCLK, m.nocclk);
	cm_wr(CM_M_NOCDIV, m.nocdiv);

	/* Program the peripheral-PLL dividers. */
	pvco = cm_vcocalib(p.pllm, p.glob);
	cm_wr(CM_P_PLLGLOB, p.glob & ~CM_GLOB_RST_N);
	cm_wr(CM_P_FDBCK, p.fdbck);
	cm_wr(CM_P_VCOCALIB, pvco);
	cm_wr(CM_P_PLLC0, p.c0);
	cm_wr(CM_P_PLLC1, p.c1);
	cm_wr(CM_P_PLLC2, p.c2);
	cm_wr(CM_P_PLLC3, p.c3);
	cm_wr(CM_P_PLLM, p.pllm);

	/* Power up + release reset on both PLLs. */
	cm_set(CM_M_PLLGLOB, CM_GLOB_PD_N | CM_GLOB_RST_N);
	cm_set(CM_P_PLLGLOB, CM_GLOB_PD_N | CM_GLOB_RST_N);

	/* Power-down-state analog config over the PLL membus. */
	(void)cm_pll_pd_state(CM_M_MEM, CM_M_MEMSTAT);
	(void)cm_pll_pd_state(CM_P_MEM, CM_P_MEMSTAT);

	/* Enable all clock slices. */
	cm_set(CM_M_PLLC0, CM_PLLCX_EN);
	cm_set(CM_M_PLLC1, CM_PLLCX_EN);
	cm_set(CM_M_PLLC2, CM_PLLCX_EN);
	cm_set(CM_M_PLLC3, CM_PLLCX_EN);
	cm_set(CM_P_PLLC0, CM_PLLCX_EN);
	cm_set(CM_P_PLLC1, CM_PLLCX_EN);
	cm_set(CM_P_PLLC2, CM_PLLCX_EN);
	cm_set(CM_P_PLLC3, CM_PLLCX_EN);

	/* Wait for both PLLs to report a stable lock. */
	if (cm_wait_lock() != 0) {
		/* Not locked: undo everything so the console keeps the SDM boot clock
		 * (do not leave the clock tree bypassed / in boot mode). */
		cm_wr(CM_M_PLLGLOB, save_mglob);
		cm_wr(CM_P_PLLGLOB, save_pglob);
		cm_wr(CM_M_BYPASS, save_mbyp);
		cm_wr(CM_P_BYPASS, save_pbyp);
		cm_wr(CM_CTRL, save_ctrl);
		return -ETIMEDOUT;
	}

	/* Clear the lost-lock bypass so a brief glitch cannot re-bypass. */
	cm_set(CM_M_LOSTLOCK, CM_LOSTLOCK_BYPCLR);
	cm_set(CM_P_LOSTLOCK, CM_LOSTLOCK_BYPCLR);
	cm_set(CM_M_PLLGLOB, CM_GLOB_CLR_LL_BYP);
	cm_set(CM_P_PLLGLOB, CM_GLOB_CLR_LL_BYP);

	/* Take all PLLs out of bypass: clocks now follow the locked PLLs. */
	cm_clr(CM_M_BYPASS, CM_BYP_MAIN_ALL);
	(void)cm_wait_fsm();
	cm_clr(CM_P_BYPASS, CM_BYP_PER_ALL);
	(void)cm_wait_fsm();

	/* Clear lost-lock interrupts and release the ping-pong counters. */
	cm_wr(CM_INTRCLR, CM_INTRCLR_MLOST | CM_INTRCLR_PLOST);
	cm_clr(CM_C_EXTCNTRST, CM_EXTCNTRST_ALL);

	/* Exit boot mode: the L4_SP (UART) clock now runs at its 100 MHz target. */
	cm_clr(CM_CTRL, CM_CTRL_BOOTMODE);

	return 0;
}

/* EOSC1 reference from the handoff blob (hps_osc_clk_hz @ 0x60C), else 25 MHz. */
static uint32_t cm_ref_osc_hz(void)
{
	volatile uint32_t *ho = (volatile uint32_t *)(uintptr_t)0x0007F000U;

	if (__builtin_bswap32(ho[0x580 / 4]) == 0x434C4B53U) {
		uint32_t hz = __builtin_bswap32(ho[0x60C / 4]);

		if (hz != 0U) {
			return hz;
		}
	}
	return 25000000U;
}

/* PLL VCO output (ATF get_ref_clk): (fref / arefclkdiv) * mdiv. */
static uint32_t cm_ref_clk(uint32_t glob, uint32_t pllm)
{
	uint32_t psrc = (glob >> 16) & 0x3U;		/* CLKMGR_PLLGLOB_PSRC */
	uint32_t aref = (glob >> 8) & 0xFU;		/* AREFCLKDIV */
	uint32_t mdiv = pllm & 0x3FFU;			/* PLLM MDIV */
	uint32_t ref;

	switch (psrc) {
	case 1U:	/* internal oscillator */
		ref = 460000000U;
		break;
	case 0U:	/* EOSC1 */
	default:	/* F2S: no boot-scratch source here, use EOSC1 */
		ref = cm_ref_osc_hz();
		break;
	}
	if (aref == 0U) {
		aref = 1U;
	}
	return (ref / aref) * mdiv;
}

/* Live L4_SP (UART) clock from the divider chain (ATF get_l4_sp_clk):
 * L3 = source / Cx, L4_SP = L3 / 2^NOCDIV[L4SP]. 100 MHz once locked. */
uint32_t platform_get_l4sp_clk(void)
{
	uint32_t src = (cm_rd(CM_M_NOCCLK) >> 16) & 0x7U;	/* GET_CLKMGR_CLKSRC */
	uint32_t div;
	uint32_t l3;

	switch (src) {
	case 0U:	/* main PLL */
		div = cm_rd(CM_M_PLLC3) & 0x7FFU;
		l3 = cm_ref_clk(cm_rd(CM_M_PLLGLOB), cm_rd(CM_M_PLLM)) /
		     (div == 0U ? 1U : div);
		break;
	case 1U:	/* peripheral PLL */
		div = cm_rd(CM_P_PLLC1) & 0x7FFU;
		l3 = cm_ref_clk(cm_rd(CM_P_PLLGLOB), cm_rd(CM_P_PLLM)) /
		     (div == 0U ? 1U : div);
		break;
	case 3U:	/* internal oscillator */
		l3 = 460000000U;
		break;
	case 2U:	/* OSC1 */
	default:	/* FPGA: no boot-scratch source here, use EOSC1 */
		l3 = cm_ref_osc_hz();
		break;
	}

	return l3 >> ((cm_rd(CM_M_NOCDIV) >> 6) & 0x3U);	/* NOCDIV L4SP */
}
#endif /* PLAT_AGILEX5 && BUILD_MODE_OCRAM */
