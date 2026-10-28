/*
 * Copyright (c) 2024-2025, Altera Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Ported to the SoCFPGA bare-metal software stack from arm-trusted-firmware
 * (plat/intel/soc/agilex5/soc/agilex5_ddr.c). Only the include lines were
 * adapted (see ddr_platform_compat.h); the DDR/IOSSM bring-up logic is unchanged.
 * Compiled only for the Agilex5 OCRAM/FSBL configuration.
 */

/* File: socfpga_ddr.c
 *
 * Agilex 5 DDR bring-up for the OCRAM build.
 * Other builds compile a ddr_init() that returns 0 and does not program the controller.
 */
#if defined(PLAT_AGILEX5) && defined(BUILD_MODE_OCRAM)

#include <stddef.h>

#include "errno.h"
#include "ddr_platform_compat.h"
#include "socfpga_ddr.h"
#include "socfpga_ddr_mailbox.h"

/*
 * DDR topology for this board.
 *   bit0 = dual-port, bit1 = dual-EMIF.
 * Default to single-port / single-EMIF (0). Set to board-specific handoff
 * value for dual-port or dual-EMIF configurations.
 */
#ifndef DDR_PLATFORM_CONFIG
#define DDR_PLATFORM_CONFIG   0x0U
#endif

#define SYSMGR_BS_COLD3_DDR_RESET_TYPE_MASK		GENMASK(31, 29)
#define SYSMGR_BS_COLD3_DDR_RESET_TYPE_SHIFT		29
#define SYSMGR_BS_COLD3_DDR_DBE_MASK			(1 << 1)
#define SYSMGR_BS_COLD3_OCRAM_DBE_MASK			(1)
#define SYSMGR_BS_POR0_DDR_PROGRESS_MASK		(1)

/* MPFE NOC registers */
#define F2SDRAM_SIDEBAND_FLAGOUTSET0			0x50
#define F2SDRAM_SIDEBAND_FLAGOUTCLR0			0x54
#define F2SDRAM_SIDEBAND_FLAGOUTSTATUS0			0x58

#define SOCFPGA_F2SDRAM_MGR_ADDRESS			0x18001000
#define SOCFPGA_MPFE_SCR_IO96B0				0x18000D00
#define SOCFPGA_MPFE_SCR_IO96B1				0x18000D04
#define SOCFPGA_MPFE_NOC_SCHED_CSR			0x18000D08

#define SIDEBANDMGR_FLAGOUTSET0_REG			(SOCFPGA_F2SDRAM_MGR_ADDRESS \
							+ F2SDRAM_SIDEBAND_FLAGOUTSET0)
#define SIDEBANDMGR_FLAGOUTSTATUS0_REG			(SOCFPGA_F2SDRAM_MGR_ADDRESS \
							+F2SDRAM_SIDEBAND_FLAGOUTSTATUS0)
#define SIDEBANDMGR_FLAGOUTCLR0_REG			(SOCFPGA_F2SDRAM_MGR_ADDRESS \
							+ F2SDRAM_SIDEBAND_FLAGOUTCLR0)

/* Firewall MPU DDR SCR registers */
#define FW_MPU_DDR_SCR_EN				0x00
#define FW_MPU_DDR_SCR_EN_SET				0x04
#define FW_MPU_DDR_SCR_MPUREGION0ADDR_BASE		0x10
#define FW_MPU_DDR_SCR_MPUREGION0ADDR_BASEEXT		0x14
#define FW_MPU_DDR_SCR_MPUREGION0ADDR_LIMIT		0x18
#define FW_MPU_DDR_SCR_MPUREGION0ADDR_LIMITEXT		0x1c

#define SOCFPGA_FW_DDR_CCU_DMI0_ADDRESS			0x18000800
#define SOCFPGA_FW_DDR_CCU_DMI1_ADDRESS			0x18000A00
#define SOCFPGA_FW_TBU2NOC_ADDRESS			0x18000C00

#define FW_MPU_DDR_SCR_NONMPUREGION0ADDR_BASE		0x90
#define FW_MPU_DDR_SCR_NONMPUREGION0ADDR_BASEEXT	0x94
#define FW_MPU_DDR_SCR_NONMPUREGION0ADDR_LIMIT		0x98
#define FW_MPU_DDR_SCR_NONMPUREGION0ADDR_LIMITEXT	0x9c
#define FW_MPU_DDR_SCR_NONMPUREGION0ADDR_LIMITEXT_FIELD	0xff

/* Firewall F2SDRAM DDR SCR registers */
#define FW_F2SDRAM_DDR_SCR_EN				0x00
#define FW_F2SDRAM_DDR_SCR_EN_SET			0x04
#define FW_F2SDRAM_DDR_SCR_REGION0ADDR_BASE		0x10
#define FW_F2SDRAM_DDR_SCR_REGION0ADDR_BASEEXT		0x14
#define FW_F2SDRAM_DDR_SCR_REGION0ADDR_LIMIT		0x18
#define FW_F2SDRAM_DDR_SCR_REGION0ADDR_LIMITEXT		0x1c

#define FW_MPU_DDR_SCR_WRITEL(data, reg)					\
	do {									\
		mmio_write_32(SOCFPGA_FW_DDR_CCU_DMI0_ADDRESS + (reg), data);	\
		mmio_write_32(SOCFPGA_FW_DDR_CCU_DMI1_ADDRESS + (reg), data);	\
	} while (0)

#define FW_F2SDRAM_DDR_SCR_WRITEL(data, reg)				\
	mmio_write_32(SOCFPGA_FW_TBU2NOC_ADDRESS + (reg), data)

/* DDR banks info set */
static struct ddr_info ddr_info_set[CONFIG_NR_DRAM_BANKS];

/* Enum: reset_type
 *
 * Reset type from bits 31:29 of boot scratch cold 3.
 * get_reset_type_str() turns these values into text.
 *
 * POR_RESET    - Value 0. Text is Power-On.
 * WARM_RESET   - Value 1. Text is Warm.
 * COLD_RESET   - Value 2. Text is Cold.
 * NCONFIG      - Value 3. Text is NCONFIG.
 * JTAG_CONFIG  - Value 4. Text is JTAG Config.
 * RSU_RECONFIG - Value 5. Text is RSU Reconfig.
 */
enum reset_type {
	POR_RESET,
	WARM_RESET,
	COLD_RESET,
	NCONFIG,
	JTAG_CONFIG,
	RSU_RECONFIG
};

/* Function: get_reset_type
 *
 * Takes bits 31:29 of sys_reg and returns them as a reset_type.
 * The caller passes the boot scratch cold 3 register value.
 * This function does not read the register itself.
 *
 * Parameters:
 *   sys_reg - Register value that holds the reset-type field.
 *
 * Returns:
 *   The reset_type value in bits 31:29.
 */
static inline enum reset_type get_reset_type(uint32_t sys_reg)
{
	return ((sys_reg & SYSMGR_BS_COLD3_DDR_RESET_TYPE_MASK) >>
		 SYSMGR_BS_COLD3_DDR_RESET_TYPE_SHIFT);
}

/* Function: get_reset_type_str
 *
 * Returns the short name for a reset type.
 * The names are Power-On, Warm, Cold, NCONFIG, JTAG Config,
 * and RSU Reconfig. Bring-up prints the name it returns.
 *
 * Parameters:
 *   reset_t - A reset_type value.
 *
 * Returns:
 *   The matching name, or "Unknown" when reset_t is not one of the six values.
 */
const char *get_reset_type_str(enum reset_type reset_t)
{
	switch (reset_t) {
	case POR_RESET:
		return "Power-On";
	case WARM_RESET:
		return "Warm";
	case COLD_RESET:
		return "Cold";
	case NCONFIG:
		return "NCONFIG";
	case JTAG_CONFIG:
		return "JTAG Config";
	case RSU_RECONFIG:
		return "RSU Reconfig";
	default:
		return "Unknown";
	}
}

/* Function: is_ddr_init_hang
 *
 * Reports whether DDR init was still in progress at reset.
 * Reads boot scratch POR 0 and returns true when bit 0 is set.
 * Bring-up treats that as a hang before this reset.
 *
 * Returns:
 *   true if the init-in-progress bit is set, otherwise false.
 */
static inline bool is_ddr_init_hang(void)
{
	uint32_t sys_reg = mmio_read_32(SOCFPGA_SYSMGR(BOOT_SCRATCH_POR_0));

	if ((sys_reg & SYSMGR_BS_POR0_DDR_PROGRESS_MASK) != 0) {
		INFO("DDR: Hang before this reset\n");
		return true;
	}

	return false;
}

/* Function: ddr_init_inprogress
 *
 * Sets or clears the DDR init-in-progress bit.
 * The bit is bit 0 of boot scratch POR 0.
 *
 * Parameters:
 *   start - true sets the bit. false clears it.
 *
 * Returns:
 *   Nothing.
 */
static inline void ddr_init_inprogress(bool start)
{
	if (start) {
		mmio_setbits_32(SOCFPGA_SYSMGR(BOOT_SCRATCH_POR_0),
				SYSMGR_BS_POR0_DDR_PROGRESS_MASK);
	} else {
		mmio_clrbits_32(SOCFPGA_SYSMGR(BOOT_SCRATCH_POR_0),
				SYSMGR_BS_POR0_DDR_PROGRESS_MASK);
	}
}

/* Function: config_io96b_csr_addr
 *
 * Chooses how many IO96B instances are used and writes their CSR bases.
 * A dual-EMIF handoff uses two instances. Anything else uses one.
 * Instance 0 is at 0x18400000. Instance 1, when used, is at 0x18800000.
 *
 * Parameters:
 *   is_dualemif - true for two EMIF interfaces.
 *   io96b_ctrl  - Receives num_instance and the CSR addresses.
 *
 * Returns:
 *   Nothing.
 */
static void config_io96b_csr_addr(bool is_dualemif, struct io96b_info *io96b_ctrl)
{
	if (is_dualemif)
		io96b_ctrl->num_instance = 2;
	else
		io96b_ctrl->num_instance = 1;

	/* Assign IO96B CSR base address if it is valid */
	for (int i = 0; i < io96b_ctrl->num_instance; i++) {
		switch (i) {
		case 0:
			io96b_ctrl->io96b_0.io96b_csr_addr = 0x18400000;
			INFO("DDR: IO96B0 0x%llx CSR enabled\n",
			     io96b_ctrl->io96b_0.io96b_csr_addr);
			break;

		case 1:
			io96b_ctrl->io96b_1.io96b_csr_addr = 0x18800000;
			INFO("DDR: IO96B1 0x%llx CSR enabled\n",
			     io96b_ctrl->io96b_1.io96b_csr_addr);
			break;

		default:
			ERROR("%s: Invalid IO96B CSR\n", __func__);
		} /* switch */
	} /* for */
}

/* Function: hps_ocram_dbe_status
 *
 * Reads boot scratch cold 3 and returns true when bit 0 is set.
 * That bit is the OCRAM double-bit error flag.
 * Bring-up uses it when deciding whether to run full memory init.
 *
 * Returns:
 *   true when bit 0 is set, otherwise false.
 */
static inline bool hps_ocram_dbe_status(void)
{
	uint32_t sys_reg = mmio_read_32(SOCFPGA_SYSMGR(BOOT_SCRATCH_COLD_3));

	if ((sys_reg & SYSMGR_BS_COLD3_OCRAM_DBE_MASK) != 0)
		return true;

	return false;
}

/* Function: ddr_ecc_dbe_status
 *
 * Reads boot scratch cold 3 and returns true when bit 1 is set.
 * That bit is the DDR double-bit error flag.
 * Bring-up uses it to force a calibration retry and full memory init.
 *
 * Returns:
 *   true when bit 1 is set, otherwise false.
 */
static inline bool ddr_ecc_dbe_status(void)
{
	uint32_t sys_reg = mmio_read_32(SOCFPGA_SYSMGR(BOOT_SCRATCH_COLD_3));

	if ((sys_reg & SYSMGR_BS_COLD3_DDR_DBE_MASK) != 0)
		return true;

	return false;
}

/* Function: sdram_set_firewall_non_f2sdram
 *
 * Programs the non-secure MPU and non-MPU DDR firewall windows.
 *
 * Each bank whose size is not zero gets a window. The window starts
 * 1 MB above the bank start and ends at the last byte of the bank.
 * The same base and limit are written to the CCU DMI0 and DMI1
 * firewalls, and the enable bit for that bank is set.
 *
 * Returns:
 *   Nothing.
 */
static void sdram_set_firewall_non_f2sdram(void)
{
	uint32_t i;
	phys_size_t value;
	uint32_t lower, upper;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		if (ddr_info_set[i].size == 0) {
			continue;
		}

		value = ddr_info_set[i].start;

		/*
		 * Keep first 1MB of SDRAM memory region as secure region when
		 * using ATF flow, where the ATF code is located.
		 */
		value += SZ_1M;

		/* Setting non-secure MPU region base and base extended */
		lower = LO(value);
		upper = HI(value);

		FW_MPU_DDR_SCR_WRITEL(lower,
				      FW_MPU_DDR_SCR_MPUREGION0ADDR_BASE +
				      (i * 4 * sizeof(uint32_t)));
		FW_MPU_DDR_SCR_WRITEL(upper & 0xff,
				      FW_MPU_DDR_SCR_MPUREGION0ADDR_BASEEXT +
				      (i * 4 * sizeof(uint32_t)));

		/* Setting non-secure Non-MPU region base and base extended */
		FW_MPU_DDR_SCR_WRITEL(lower,
				      FW_MPU_DDR_SCR_NONMPUREGION0ADDR_BASE +
				      (i * 4 * sizeof(uint32_t)));
		FW_MPU_DDR_SCR_WRITEL(upper & 0xff,
				      FW_MPU_DDR_SCR_NONMPUREGION0ADDR_BASEEXT +
				      (i * 4 * sizeof(uint32_t)));

		/* Setting non-secure MPU limit and limit extended */
		value = ddr_info_set[i].start + ddr_info_set[i].size - 1;

		lower = LO(value);
		upper = HI(value);

		FW_MPU_DDR_SCR_WRITEL(lower,
				      FW_MPU_DDR_SCR_MPUREGION0ADDR_LIMIT +
				      (i * 4 * sizeof(uint32_t)));
		FW_MPU_DDR_SCR_WRITEL(upper & 0xff,
				      FW_MPU_DDR_SCR_MPUREGION0ADDR_LIMITEXT +
				      (i * 4 * sizeof(uint32_t)));

		/* Setting non-secure Non-MPU limit and limit extended */
		FW_MPU_DDR_SCR_WRITEL(lower,
				      FW_MPU_DDR_SCR_NONMPUREGION0ADDR_LIMIT +
				      (i * 4 * sizeof(uint32_t)));
		FW_MPU_DDR_SCR_WRITEL(upper & 0xff,
				      FW_MPU_DDR_SCR_NONMPUREGION0ADDR_LIMITEXT +
				      (i * 4 * sizeof(uint32_t)));

		FW_MPU_DDR_SCR_WRITEL(BIT(i) | BIT(i + 8),
				      FW_MPU_DDR_SCR_EN_SET);
	}
}

/* Function: sdram_set_firewall_f2sdram
 *
 * Programs the FPGA-to-SDRAM firewall window.
 *
 * Uses the same 1 MB offset and end address as the MPU firewall.
 * Writes each bank through the TBU-to-NoC register window and sets
 * that bank's enable bit. Banks whose size is zero are skipped.
 *
 * Returns:
 *   Nothing.
 */
static void sdram_set_firewall_f2sdram(void)
{
	uint32_t i;
	phys_size_t value;
	uint32_t lower, upper;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		if (ddr_info_set[i].size == 0) {
			continue;
		}

		value = ddr_info_set[i].start;

		/* Keep first 1MB of SDRAM memory region as secure region when
		 * using ATF flow, where the ATF code is located.
		 */
		value += SZ_1M;

		/* Setting base and base extended */
		lower = LO(value);
		upper = HI(value);
		FW_F2SDRAM_DDR_SCR_WRITEL(lower,
					  FW_F2SDRAM_DDR_SCR_REGION0ADDR_BASE +
					  (i * 4 * sizeof(uint32_t)));
		FW_F2SDRAM_DDR_SCR_WRITEL(upper & 0xff,
					  FW_F2SDRAM_DDR_SCR_REGION0ADDR_BASEEXT +
					  (i * 4 * sizeof(uint32_t)));

		/* Setting limit and limit extended */
		value = ddr_info_set[i].start + ddr_info_set[i].size - 1;

		lower = LO(value);
		upper = HI(value);

		FW_F2SDRAM_DDR_SCR_WRITEL(lower,
					  FW_F2SDRAM_DDR_SCR_REGION0ADDR_LIMIT +
					  (i * 4 * sizeof(uint32_t)));
		FW_F2SDRAM_DDR_SCR_WRITEL(upper & 0xff,
					  FW_F2SDRAM_DDR_SCR_REGION0ADDR_LIMITEXT +
					  (i * 4 * sizeof(uint32_t)));

		FW_F2SDRAM_DDR_SCR_WRITEL(BIT(i), FW_F2SDRAM_DDR_SCR_EN_SET);
	}
}

/* Function: sdram_set_firewall
 *
 * Opens both DDR firewalls.
 * Calls sdram_set_firewall_non_f2sdram() and then sdram_set_firewall_f2sdram().
 *
 * Returns:
 *   Nothing.
 */
static void sdram_set_firewall(void)
{
	sdram_set_firewall_non_f2sdram();
	sdram_set_firewall_f2sdram();
}

/* Function: socfpga_ddr_init_internal
 *
 * Brings up DDR on the Agilex 5 OCRAM build.
 *
 * Reads the reset type from bits 31:29 of boot scratch cold 3.
 * JTAG config returns -EOPNOTSUPP and does not touch IO96B registers.
 * Bit 0 of hoff_ptr->ddr_config selects dual-port. Bit 1 selects dual-EMIF.
 *
 * Any other reset sets the init-in-progress bit, programs the IO96B CSR
 * addresses and the MPFE sideband bits, and checks calibration. A failed
 * calibration, or a set DDR double-bit error flag, calls trig_mem_cal().
 * The function then reads the DDR type, size, and ECC state. Inline ECC
 * shrinks the reported size with GET_INLINE_ECC_HW_DDR_SIZE(). Bank 0 is
 * stored at DRAM_BASE. If that size is smaller than 0x80000000 bytes, the
 * function returns -EINVAL.
 *
 * When ECC is on, a double-bit error in the ECC log calls mailbox_reset_cold(),
 * which does not return. Warm and cold resets skip full memory init unless an
 * OCRAM double-bit flag, a DDR double-bit flag, or a previous hang is set.
 *
 * The function then opens the DDR firewall, allows secure and non-secure
 * access to the MPFE CSR registers, and clears the init-in-progress bit.
 *
 * Parameters:
 *   hoff_ptr - Handoff data. Only ddr_config is read.
 *
 * Returns:
 *   0 on success.
 *   -EOPNOTSUPP for a JTAG config reset.
 *   -EINVAL if that DDR size is smaller than 0x80000000 bytes.
 *   A negative error code returned by one of the mailbox steps.
 *   Does not return if mailbox_reset_cold() is called.
 */
static int socfpga_ddr_init_internal(handoff *hoff_ptr)
{
	int ret;
	bool full_mem_init = false;
	phys_size_t hw_ddr_size;
	phys_size_t config_ddr_size;
	struct io96b_info io96b_ctrl = {0};
	enum reset_type reset_t = get_reset_type(mmio_read_32(SOCFPGA_SYSMGR(
						BOOT_SCRATCH_COLD_3)));
	bool is_dualport = hoff_ptr->ddr_config & BIT(0);
	bool is_dualemif = hoff_ptr->ddr_config & BIT(1);

	NOTICE("DDR: Reset type is '%s'\n", get_reset_type_str(reset_t));

	/*
	 * In standalone JTAG-config flows the IO96B CSR window may be inaccessible
	 * at this point. Touching those registers can hard-stall the bus, so fail
	 * fast and let the caller report a clean error instead of hanging the shell.
	 */
	if (reset_t == JTAG_CONFIG) {
		ERROR("DDR: JTAG Config reset is not supported for DDR bring-up in this flow\n");
		return -EOPNOTSUPP;
	}

	/* DDR initialization progress status tracking */
	bool is_ddr_hang_bfr_rst = is_ddr_init_hang();

	/* Set the DDR initialization progress */
	ddr_init_inprogress(true);

	/* Configure the IO96B CSR address based on the handoff data */
	config_io96b_csr_addr(is_dualemif, &io96b_ctrl);

	/* Configuring MPFE sideband manager registers */
	/* Dual port setting */
	if (is_dualport)
		mmio_setbits_32(SIDEBANDMGR_FLAGOUTSET0_REG, BIT(4));

	/* Dual EMIF setting */
	if (is_dualemif) {
		/* Set mpfe_lite_active in the system manager. */
		mmio_setbits_32(SOCFPGA_SYSMGR(MPFE_CONFIG), BIT(8));

		/* Set mpfe_lite_intfcsel select in the system manager. */
		mmio_setbits_32(SOCFPGA_SYSMGR(MPFE_CONFIG), BIT(2));

		mmio_setbits_32(SIDEBANDMGR_FLAGOUTSET0_REG, BIT(5));
	}

	if (is_dualport || is_dualemif)
		INFO("DDR: SIDEBANDMGR_FLAGOUTSTATUS0: 0x%x\n",
		     mmio_read_32(SIDEBANDMGR_FLAGOUTSTATUS0_REG));

	/* Ensure calibration status passing */
	init_mem_cal(&io96b_ctrl);

	/* Initiate IOSSM mailbox */
	io96b_mb_init(&io96b_ctrl);

	/* Need to trigger re-calibration for DDR DBE */
	if (ddr_ecc_dbe_status()) {
		io96b_ctrl.io96b_0.cal_status = false;
		io96b_ctrl.io96b_1.cal_status = false;
		io96b_ctrl.overall_cal_status = io96b_ctrl.io96b_0.cal_status ||
						io96b_ctrl.io96b_1.cal_status;
	}

	/* Trigger re-calibration if calibration failed */
	if (!(io96b_ctrl.overall_cal_status)) {
		NOTICE("DDR: Re-calibration in progress...\n");
		trig_mem_cal(&io96b_ctrl);
	}
	NOTICE("DDR: Calibration success\n");

	/* DDR type, DDR size and ECC status */
	ret = get_mem_technology(&io96b_ctrl);
	if (ret != 0) {
		ERROR("DDR: Failed to get DDR type\n");
		return ret;
	}

	ret = get_mem_width_info(&io96b_ctrl);
	if (ret != 0) {
		ERROR("DDR: Failed to get DDR size\n");
		return ret;
	}

	ret = ecc_enable_status(&io96b_ctrl);
	if (ret != 0) {
		ERROR("DDR: Failed to get DDR ECC status\n");
		return ret;
	}

	/* DDR size queried from the IOSSM controller */
	hw_ddr_size = io96b_ctrl.overall_size;

	/* Update the DDR size if it is In-line ECC. */
	if (io96b_ctrl.is_inline_ecc)
		hw_ddr_size = GET_INLINE_ECC_HW_DDR_SIZE(hw_ddr_size);

	/* TODO: To update config_ddr_size by using FDT in the future. */
	config_ddr_size = 0x80000000;
	ddr_info_set[0].start = DRAM_BASE;
	ddr_info_set[0].size = hw_ddr_size;

	if (config_ddr_size != hw_ddr_size) {
		WARN("DDR: DDR size configured is (%lld MiB)\n", config_ddr_size >> 20);
		WARN("DDR: Mismatch with hardware size (%lld MiB).\n", hw_ddr_size >> 20);
	}

	if (config_ddr_size > hw_ddr_size) {
		ERROR("DDR: Configured DDR size is greater than hardware size\n");
		return -EINVAL;
	}

	/*
	 * HPS cold or warm reset? If yes, skip full memory initialization if
	 * ECC is enabled to preserve memory content.
	 */
	if (io96b_ctrl.ecc_status) {
		/* Let's check the ECC interrupt status on the DBE (Double Bit Error). */
		if (get_ecc_dbe_status(&io96b_ctrl)) {
			NOTICE("DDR: ECC-Double Bit Error occurred!!\n");
			NOTICE("DDR: Resetting the system to recover!!\n");
			mailbox_reset_cold();
		}

		full_mem_init = hps_ocram_dbe_status() || ddr_ecc_dbe_status() ||
				is_ddr_hang_bfr_rst;

		if (full_mem_init || !((reset_t == WARM_RESET) || (reset_t == COLD_RESET))) {
			ret = bist_mem_init_start(&io96b_ctrl);
			if (ret != 0) {
				ERROR("DDR: Failed to fully initialize DDR memory\n");
				return ret;
			}
		}
		INFO("DDR: ECC initialized successfully\n");
	}

	sdram_set_firewall();

	/*
	 * Firewall setting for MPFE CSRs, allow both secure and non-secure
	 * transactions.
	 */
	/* IO96B0_reg */
	mmio_setbits_32(SOCFPGA_MPFE_SCR_IO96B0, BIT(0));
	/* IO96B1_reg */
	mmio_setbits_32(SOCFPGA_MPFE_SCR_IO96B1, BIT(0));
	/* noc_scheduler_csr */
	mmio_setbits_32(SOCFPGA_MPFE_NOC_SCHED_CSR, BIT(0));

	INFO("DDR: firewall init done\n");

	/* Ending DDR driver initialization success tracking */
	ddr_init_inprogress(false);

	NOTICE("###DDR:init success###\n");

	return 0;
}

int ddr_init(void)
{
	handoff hoff = { .ddr_config = DDR_PLATFORM_CONFIG };

	return socfpga_ddr_init_internal(&hoff);
}

#else /* !(PLAT_AGILEX5 && BUILD_MODE_OCRAM) */

int ddr_init(void)
{
	/* On other platforms/build modes DDR is expected to be already configured. */
	return 0;
}

#endif /* PLAT_AGILEX5 && BUILD_MODE_OCRAM */

