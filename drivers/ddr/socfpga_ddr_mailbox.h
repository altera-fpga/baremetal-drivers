/*
 * Copyright (c) 2024-2025, Altera Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Ported to the SoCFPGA bare-metal software stack from arm-trusted-firmware
 * (plat/intel/soc/agilex5/include/agilex5_iossm_mailbox.h). Platform
 * dependencies are satisfied by ddr_platform_compat.h.
 */

/* File: socfpga_ddr_mailbox.h
 *
 * IOSSM mailbox registers, command codes, and the functions that talk to the IO96B.
 */
#ifndef SOCFPGA_DDR_MAILBOX_H
#define SOCFPGA_DDR_MAILBOX_H

#include <stdbool.h>
#include <stdint.h>

#include "ddr_platform_compat.h"
#include "socfpga_ddr.h"

/* Constants: Field helpers
 *
 * Shift a value into or out of a bit field.
 *
 * __bf_shf   - Shift count of the lowest set bit in x. Computed as __builtin_ffsll(x) - 1.
 * FIELD_GET  - Bits of _reg selected by _mask, shifted down so the field starts at bit 0.
 * FIELD_PREP - _val shifted up to the position of _mask, then masked with _mask.
 */
#define __bf_shf(x)					(__builtin_ffsll(x) - 1U)
#define FIELD_GET(_mask, _reg)						\
	({								\
		(__typeof__(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask));	\
	})

#define FIELD_PREP(_mask, _val)						\
	({ \
		((__typeof__(_mask))(_val) << __bf_shf(_mask)) & (_mask);	\
	})

/* Constants: Mailbox timeouts and status bits
 *
 * Poll limits, and bits in the IOSSM status register.
 *
 * IOSSM_TIMEOUT_MS                    - 15000 milliseconds. io96b_mb_req() stops polling after this long.
 * TIMEOUT_5000MS                      - 5000. TIMEOUT is set from this value.
 * TIMEOUT                             - Same value as TIMEOUT_5000MS. The memory-init poll divides it by 500.
 * IOSSM_STATUS_CAL_SUCCESS            - Bit 0 of the IOSSM status register. io96b_cal_status() waits until it is set.
 * IOSSM_STATUS_CAL_FAIL               - Bit 1 of the IOSSM status register. io96b_cal_status() waits until it is clear.
 * IOSSM_STATUS_CAL_BUSY               - Bit 2 of the IOSSM status register.
 * IOSSM_STATUS_COMMAND_RESPONSE_READY - Value 1. The driver waits for this bit in the response status, then clears it.
 */
#define IOSSM_TIMEOUT_MS				15000U
#define TIMEOUT_5000MS					5000
#define TIMEOUT						TIMEOUT_5000MS
#define IOSSM_STATUS_CAL_SUCCESS			BIT(0)
#define IOSSM_STATUS_CAL_FAIL				BIT(1)
#define IOSSM_STATUS_CAL_BUSY				BIT(2)
#define IOSSM_STATUS_COMMAND_RESPONSE_READY		1

/* Constants: Mailbox command register offsets
 *
 * Byte offsets from the IO96B CSR base.
 *
 * IOSSM_CMD_RESPONSE_STATUS_OFFSET - Offset 0x45C. Command response status.
 * IOSSM_CMD_RESPONSE_DATA_0_OFFSET - Offset 0x458. Response data word 0.
 * IOSSM_CMD_RESPONSE_DATA_1_OFFSET - Offset 0x454. Response data word 1.
 * IOSSM_CMD_RESPONSE_DATA_2_OFFSET - Offset 0x450. Response data word 2.
 * IOSSM_CMD_REQ_OFFSET             - Offset 0x43C. Command request. The driver waits for this to read as zero before writing a command.
 * IOSSM_CMD_PARAM_0_OFFSET         - Offset 0x438. Command parameter 0.
 * IOSSM_CMD_PARAM_1_OFFSET         - Offset 0x434. Command parameter 1.
 * IOSSM_CMD_PARAM_2_OFFSET         - Offset 0x430. Command parameter 2.
 * IOSSM_CMD_PARAM_3_OFFSET         - Offset 0x42C. Command parameter 3.
 * IOSSM_CMD_PARAM_4_OFFSET         - Offset 0x428. Command parameter 4.
 * IOSSM_CMD_PARAM_5_OFFSET         - Offset 0x424. Command parameter 5.
 * IOSSM_CMD_PARAM_6_OFFSET         - Offset 0x420. Command parameter 6.
 * IOSSM_STATUS_OFFSET              - Offset 0x400. Calibration status. io96b_cal_status() reads it.
 */
#define IOSSM_CMD_RESPONSE_STATUS_OFFSET		0x45C
#define IOSSM_CMD_RESPONSE_DATA_0_OFFSET		0x458
#define IOSSM_CMD_RESPONSE_DATA_1_OFFSET		0x454
#define IOSSM_CMD_RESPONSE_DATA_2_OFFSET		0x450
#define IOSSM_CMD_REQ_OFFSET				0x43C
#define IOSSM_CMD_PARAM_0_OFFSET			0x438
#define IOSSM_CMD_PARAM_1_OFFSET			0x434
#define IOSSM_CMD_PARAM_2_OFFSET			0x430
#define IOSSM_CMD_PARAM_3_OFFSET			0x42C
#define IOSSM_CMD_PARAM_4_OFFSET			0x428
#define IOSSM_CMD_PARAM_5_OFFSET			0x424
#define IOSSM_CMD_PARAM_6_OFFSET			0x420
#define IOSSM_STATUS_OFFSET				0x400

/* Constants: Short response data
 *
 * The high half of a response status word.
 *
 * IOSSM_CMD_RESPONSE_DATA_SHORT_MASK - Bits 31:16.
 * IOSSM_CMD_RESPONSE_DATA_SHORT      - Bits 31:16 of data, shifted down into bits 15:0.
 */
#define IOSSM_CMD_RESPONSE_DATA_SHORT_MASK		GENMASK(31, 16)
#define IOSSM_CMD_RESPONSE_DATA_SHORT(data)		(((data) & \
							IOSSM_CMD_RESPONSE_DATA_SHORT_MASK) >> 16)

/* Constants: Interface counts and size
 *
 * How many IO96B blocks and memory interfaces this header allows.
 *
 * MAX_IO96B_SUPPORTED          - Value 2.
 * MAX_MEM_INTERFACES_SUPPORTED - Value 2. io96b_mb_init() reads at most this many interfaces.
 * SZ_8                         - Value 8. get_mem_width_info() divides by this to turn gigabits into bytes.
 * GET_INLINE_ECC_HW_DDR_SIZE   - size * 7 / 8. Bring-up uses this when inline ECC is on.
 */
#define MAX_IO96B_SUPPORTED				2
#define MAX_MEM_INTERFACES_SUPPORTED			2
#define SZ_8						0x00000008
#define GET_INLINE_ECC_HW_DDR_SIZE(size)		(((size) * 7) / 8)

/* Constants: Memory interface info
 *
 * Registers that identify each memory interface. io96b_mb_init() reads them.
 *
 * IOSSM_MEM_INTF_INFO_0_OFFSET - Offset 0x200. Interface 0 info.
 * IOSSM_MEM_INTF_INFO_1_OFFSET - Offset 0x280. Interface 1 info.
 * INTF_IP_TYPE_MASK            - Bits 31:29 of an interface info register. The IP type.
 * INTF_INSTANCE_ID_MASK        - Bits 28:24 of an interface info register. The instance id.
 */
#define IOSSM_MEM_INTF_INFO_0_OFFSET			0x200
#define IOSSM_MEM_INTF_INFO_1_OFFSET			0x280
#define INTF_IP_TYPE_MASK				GENMASK(31, 29)
#define INTF_INSTANCE_ID_MASK				GENMASK(28, 24)

/* Constants: ECC enable
 *
 * Per-interface ECC enable registers.
 * The log text in the driver maps bits 1:0 to disabled (0), enabled with
 * no correction or detection (1), correction without detection (2), or
 * correction and detection (3). Bit 8 set is logged as in-line ECC.
 * Bit 8 clear is logged as out-of-band ECC.
 *
 * IOSSM_ECC_ENABLE_INTF0_OFFSET - Offset 0x240. ECC enable for interface 0.
 * IOSSM_ECC_ENABLE_INTF1_OFFSET - Offset 0x2C0. ECC enable for interface 1.
 * INTF_ECC_ENABLE_TYPE_MASK     - Bits 1:0. ecc_enable_status() treats 0 as ECC off.
 * INTF_ECC_TYPE_MASK            - Bit 8. ecc_enable_status() stores a set bit as inline ECC.
 */
#define IOSSM_ECC_ENABLE_INTF0_OFFSET			0x240
#define IOSSM_ECC_ENABLE_INTF1_OFFSET			0x2C0
#define INTF_ECC_ENABLE_TYPE_MASK			GENMASK(1, 0)
#define INTF_ECC_TYPE_MASK				BIT(8)

/* Constants: Memory capacity
 *
 * Registers that hold the size of each memory interface.
 * get_mem_width_info() reads bits 7:0 as a size in gigabits.
 *
 * MAX_MEM_INTERFACE_SUPPORTED           - Value 2. Length of the per-interface offset tables.
 * IOSSM_MEM_TOTAL_CAPACITY_INTF0_OFFSET - Offset 0x234. Total capacity for interface 0.
 * IOSSM_MEM_TOTAL_CAPACITY_INTF1_OFFSET - Offset 0x2B4. Total capacity for interface 1.
 * INTF_CAPACITY_GBITS_MASK              - Bits 7:0 of a total-capacity register. Size in gigabits.
 */
#define MAX_MEM_INTERFACE_SUPPORTED			2
#define IOSSM_MEM_TOTAL_CAPACITY_INTF0_OFFSET		0x234
#define IOSSM_MEM_TOTAL_CAPACITY_INTF1_OFFSET		0x2B4

#define INTF_CAPACITY_GBITS_MASK			GENMASK(7, 0)

/* Constants: Memory init status
 *
 * Status bit and registers polled while memory-init BIST runs.
 *
 * INTF_BIST_STATUS_MASK              - Bit 0. The out-of-band init path waits until this bit is set.
 * IOSSM_MEM_INIT_STATUS_INTF0_OFFSET - Offset 0x260. Memory init status for interface 0.
 * IOSSM_MEM_INIT_STATUS_INTF1_OFFSET - Offset 0x2E0. Memory init status for interface 1.
 */
#define INTF_BIST_STATUS_MASK				BIT(0)

#define IOSSM_MEM_INIT_STATUS_INTF0_OFFSET		0x260
#define IOSSM_MEM_INIT_STATUS_INTF1_OFFSET		0x2E0

/* Constants: ECC error status registers
 *
 * Offsets and the command value used while reading ECC errors.
 *
 * IOSSM_ECC_ERR_STATUS_OFFSET     - Offset 0x300. get_ecc_dbe_status() reads the error count from here.
 * IOSSM_ECC_ERR_DATA_START_OFFSET - Offset 0x310. First ECC error data word.
 * IOSSM_ECC_CLEAR_ERR_BUFFER      - Value 0x0110. Written as the opcode that clears the ECC error buffer.
 */
#define IOSSM_ECC_ERR_STATUS_OFFSET			0x300
#define IOSSM_ECC_ERR_DATA_START_OFFSET			0x310
#define IOSSM_ECC_CLEAR_ERR_BUFFER			0x0110

/* Constants: ECC error status fields
 *
 * Fields in the ECC error status register.
 *
 * ECC_ERR_COUNTER_MASK  - Bits 15:0. Number of error entries.
 * ECC_ERR_OVERFLOW_MASK - Bits 31:16. Overflow field. The driver prints it.
 */
#define ECC_ERR_COUNTER_MASK				GENMASK(15, 0)
#define ECC_ERR_OVERFLOW_MASK				GENMASK(31, 16)

/* Constants: ECC error data fields
 *
 * Fields in one ECC error data word. The low address is a second word.
 *
 * ECC_ERR_IP_TYPE_MASK     - Bits 24:22.
 * ECC_ERR_INSTANCE_ID_MASK - Bits 21:17.
 * ECC_ERR_SOURCE_ID_MASK   - Bits 16:10.
 * ECC_ERR_TYPE_MASK        - Bits 9:6. Compared with ecc_error_type.
 * ECC_ERR_ADDR_UPPER_MASK  - Bits 5:0. High part of the error address.
 * ECC_ERR_ADDR_LOWER_MASK  - Bits 31:0. Mask for the low address word.
 */
#define ECC_ERR_IP_TYPE_MASK				GENMASK(24, 22)
#define ECC_ERR_INSTANCE_ID_MASK			GENMASK(21, 17)
#define ECC_ERR_SOURCE_ID_MASK				GENMASK(16, 10)
#define ECC_ERR_TYPE_MASK				GENMASK(9, 6)
#define ECC_ERR_ADDR_UPPER_MASK				GENMASK(5, 0)
#define ECC_ERR_ADDR_LOWER_MASK				GENMASK(31, 0)

/* Constants: ECC error buffer
 *
 * How many error entries the driver walks, and where it writes the clear.
 *
 * MAX_ECC_ERR_COUNT               - Value 16. The walk stops after 16 entries.
 * IOSSM_CONTROLLER_TRIGGER_OFFSET - Offset 0x300, the same address as the ECC error status register. The clear command is written here.
 */
#define MAX_ECC_ERR_COUNT				16U

#define IOSSM_CONTROLLER_TRIGGER_OFFSET			0x300

/* Constants: BIST start address
 *
 * Fields in the BIST memory-init command. The inline ECC path fills them.
 *
 * BIST_START_ADDR_SPACE_MASK - Bits 5:0. Receives log2 of the interface size.
 * BIST_START_ADDR_LOW_MASK   - Bits 31:0 of the start address. The inline path writes 0.
 * BIST_START_ADDR_HIGH_MASK  - Bits 37:32 of the start address. The inline path writes 0.
 */
#define BIST_START_ADDR_SPACE_MASK			GENMASK(5, 0)
#define BIST_START_ADDR_LOW_MASK			GENMASK(31, 0)
#define BIST_START_ADDR_HIGH_MASK			GENMASK(37, 32)

/* Enum: iossm_mailbox_cmd_type
 *
 * Command type placed in the command word, shifted left by 16.
 *
 * CMD_NOP                - Value 0.
 * CMD_GET_SYS_INFO       - Value 1.
 * CMD_GET_MEM_INFO       - Value 2. Sent with GET_MEM_TECHNOLOGY.
 * CMD_GET_MEM_CAL_INFO   - Value 3.
 * CMD_TRIG_CONTROLLER_OP - Value 4. Sent for memory-init BIST and for the ECC buffer clear.
 * CMD_TRIG_MEM_CAL_OP    - Value 5. Sent with TRIG_MEM_CAL and GET_MEM_CAL_STATUS.
 */
enum iossm_mailbox_cmd_type  {
	CMD_NOP,
	CMD_GET_SYS_INFO,
	CMD_GET_MEM_INFO,
	CMD_GET_MEM_CAL_INFO,
	CMD_TRIG_CONTROLLER_OP,
	CMD_TRIG_MEM_CAL_OP
};

/* Enum: ecc_error_type
 *
 * Values stored in bits 9:6 of an ECC error data word.
 * get_ecc_dbe_status() treats five of them as double-bit errors.
 *
 * SINGLE_BIT_ERROR                   - Value 0 (0b0000).
 * MULTIPLE_SINGLE_BIT_ERRORS         - Value 1 (0b0001).
 * DOUBLE_BIT_ERROR                   - Value 2 (0b0010). Counted as a double-bit error.
 * MULTIPLE_DOUBLE_BIT_ERRORS         - Value 3 (0b0011). Counted as a double-bit error.
 * SINGLE_BIT_ERROR_SCRUBBING         - Value 8 (0b1000).
 * WRITE_LINK_SINGLE_BIT_ERROR        - Value 9 (0b1001).
 * WRITE_LINK_DOUBLE_BIT_ERROR        - Value 10 (0b1010). Counted as a double-bit error.
 * READ_LINK_SINGLE_BIT_ERROR         - Value 11 (0b1011).
 * READ_LINK_DOUBLE_BIT_ERROR         - Value 12 (0b1100). Counted as a double-bit error.
 * READ_MODIFY_WRITE_DOUBLE_BIT_ERROR - Value 13 (0b1101). Counted as a double-bit error.
 */
enum ecc_error_type {
	SINGLE_BIT_ERROR = 0,			/* 0b0000 */
	MULTIPLE_SINGLE_BIT_ERRORS = 1,		/* 0b0001 */
	DOUBLE_BIT_ERROR = 2,			/* 0b0010 */
	MULTIPLE_DOUBLE_BIT_ERRORS = 3,		/* 0b0011 */
	SINGLE_BIT_ERROR_SCRUBBING = 8,		/* 0b1000 */
	WRITE_LINK_SINGLE_BIT_ERROR = 9,	/* 0b1001 */
	WRITE_LINK_DOUBLE_BIT_ERROR = 10,	/* 0b1010 */
	READ_LINK_SINGLE_BIT_ERROR = 11,	/* 0b1011 */
	READ_LINK_DOUBLE_BIT_ERROR = 12,	/* 0b1100 */
	READ_MODIFY_WRITE_DOUBLE_BIT_ERROR = 13	/* 0b1101 */
};

/* Enum: iossm_mailbox_cmd_opcode
 *
 * Command opcode placed in the low 16 bits of the command word.
 * Opcodes that this driver does not send are listed with their value only.
 *
 * GET_MEM_INTF_INFO            - Opcode 0x0001.
 * GET_MEM_TECHNOLOGY           - Opcode 0x0002. get_mem_technology() sends this.
 * GET_MEMCLK_FREQ_KHZ          - Opcode 0x0003.
 * GET_MEM_WIDTH_INFO           - Opcode 0x0004.
 * ECC_ENABLE_SET               - Opcode 0x0101.
 * ECC_ENABLE_STATUS            - Opcode 0x0102.
 * ECC_INTERRUPT_STATUS         - Opcode 0x0103.
 * ECC_INTERRUPT_ACK            - Opcode 0x0104.
 * ECC_INTERRUPT_MASK           - Opcode 0x0105.
 * ECC_WRITEBACK_ENABLE         - Opcode 0x0106.
 * ECC_SCRUB_IN_PROGRESS_STATUS - Opcode 0x0201.
 * ECC_SCRUB_MODE_0_START       - Opcode 0x0202.
 * ECC_SCRUB_MODE_1_START       - Opcode 0x0203.
 * BIST_STANDARD_MODE_START     - Opcode 0x0301.
 * BIST_RESULTS_STATUS          - Opcode 0x0302.
 * BIST_MEM_INIT_START          - Opcode 0x0303. Memory-init BIST sends this.
 * BIST_MEM_INIT_STATUS         - Opcode 0x0304.
 * BIST_SET_DATA_PATTERN_UPPER  - Opcode 0x0305.
 * BIST_SET_DATA_PATTERN_LOWER  - Opcode 0x0306.
 * TRIG_MEM_CAL                 - Opcode 0x000a. trig_mem_cal() sends this to calibrate again.
 * GET_MEM_CAL_STATUS           - Opcode 0x000b. trig_mem_cal() sends this to read calibration status.
 */
enum iossm_mailbox_cmd_opcode  {
	GET_MEM_INTF_INFO = 0x0001,
	GET_MEM_TECHNOLOGY,
	GET_MEMCLK_FREQ_KHZ,
	GET_MEM_WIDTH_INFO,
	ECC_ENABLE_SET = 0x0101,
	ECC_ENABLE_STATUS,
	ECC_INTERRUPT_STATUS,
	ECC_INTERRUPT_ACK,
	ECC_INTERRUPT_MASK,
	ECC_WRITEBACK_ENABLE,
	ECC_SCRUB_IN_PROGRESS_STATUS = 0x0201,
	ECC_SCRUB_MODE_0_START,
	ECC_SCRUB_MODE_1_START,
	BIST_STANDARD_MODE_START = 0x0301,
	BIST_RESULTS_STATUS,
	BIST_MEM_INIT_START,
	BIST_MEM_INIT_STATUS,
	BIST_SET_DATA_PATTERN_UPPER,
	BIST_SET_DATA_PATTERN_LOWER,
	TRIG_MEM_CAL = 0x000a,
	GET_MEM_CAL_STATUS
};

/* Struct: io96b_mb_ctrl
 *
 * What the mailbox needs before it can address one IO96B.
 * io96b_mb_init() fills the IP type and instance id.
 * get_mem_width_info() fills the sizes.
 *
 * num_mem_interface - How many interfaces on this IO96B have a non-zero IP type.
 * ip_type           - IP type of each interface. Two entries.
 * ip_instance_id    - Instance id of each interface. Two entries.
 * memory_size       - Size of each interface, in bytes. Two entries.
 */
struct io96b_mb_ctrl {
	uint32_t num_mem_interface;
	uint32_t ip_type[2];
	uint32_t ip_instance_id[2];
	phys_size_t memory_size[2];
};

/* Struct: io96b_mb_resp
 *
 * Words copied out of one mailbox response.
 *
 * cmd_resp_status - Command response status word.
 * cmd_resp_data_0 - Response data word 0.
 * cmd_resp_data_1 - Response data word 1.
 * cmd_resp_data_2 - Response data word 2.
 */
struct io96b_mb_resp {
	uint32_t cmd_resp_status;
	uint32_t cmd_resp_data_0;
	uint32_t cmd_resp_data_1;
	uint32_t cmd_resp_data_2;
};

/* Struct: io96b_instance
 *
 * One IO96B instance.
 *
 * io96b_csr_addr - CSR base address of this instance.
 * cal_status     - true after io96b_cal_status() returns 0 for this instance.
 * mb_ctrl        - Mailbox ids and sizes for this instance.
 */
struct io96b_instance {
	phys_addr_t io96b_csr_addr;
	bool cal_status;
	struct io96b_mb_ctrl mb_ctrl;
};

/* Struct: io96b_info
 *
 * Both IO96B instances, plus the totals bring-up keeps.
 *
 * num_instance       - How many instances are in use. 1, or 2 for dual-EMIF.
 * overall_cal_status - Set by init_mem_cal() when every instance succeeds, and by trig_mem_cal() when both instances have cal_status true.
 * ddr_type           - DDR type name. get_mem_technology() sets it, starting from the name UNKNOWN.
 * ecc_status         - true when ECC is enabled.
 * is_inline_ecc      - true when ECC is on and bit 8 of the ECC enable register is set.
 * overall_size       - Total DDR size, in bytes.
 * io96b_0            - Instance 0.
 * io96b_1            - Instance 1.
 */
struct io96b_info {
	uint8_t num_instance;
	bool overall_cal_status;
	const char *ddr_type;
	bool ecc_status;
	bool is_inline_ecc;
	phys_size_t overall_size;
	struct io96b_instance io96b_0;
	struct io96b_instance io96b_1;
};

/* Function: io96b_mb_req
 *
 * Sends one mailbox command and copies the response.
 *
 * Waits until the command request register is zero, writes each non-zero
 * parameter 0 through 5, then writes the command word. Waits until the
 * response-ready bit is set, copies the status and the requested data
 * words, and clears the ready bit.
 *
 * Parameters:
 *   io96b_csr_addr - IO96B CSR base. Register offsets are added to this.
 *   ip_type        - Shifted left by 29 in the command word.
 *   instance_id    - Shifted left by 24 in the command word.
 *   usr_cmd_type   - Shifted left by 16 in the command word.
 *   usr_cmd_opcode - Stored in the low bits of the command word.
 *   cmd_param_0    - Written to parameter register 0 when not zero.
 *   cmd_param_1    - Written to parameter register 1 when not zero.
 *   cmd_param_2    - Written to parameter register 2 when not zero.
 *   cmd_param_3    - Written to parameter register 3 when not zero.
 *   cmd_param_4    - Written to parameter register 4 when not zero.
 *   cmd_param_5    - Written to parameter register 5 when not zero.
 *   cmd_param_6    - Not written. The parameter loop stops before this argument.
 *   resp_data_len  - How many response data words to read. Only words 0, 1, and 2 have registers.
 *   resp           - Filled with the status word and the data words that were read.
 *
 * Returns:
 *   0 when the response was read.
 *   -ETIMEDOUT if the request register does not clear, or the ready bit does not set, within IOSSM_TIMEOUT_MS.
 */
int io96b_mb_req(phys_addr_t io96b_csr_addr, uint32_t ip_type, uint32_t instance_id,
		 uint32_t usr_cmd_type, uint32_t usr_cmd_opcode, uint32_t cmd_param_0,
		 uint32_t cmd_param_1, uint32_t cmd_param_2, uint32_t cmd_param_3,
		 uint32_t cmd_param_4, uint32_t cmd_param_5, uint32_t cmd_param_6,
		 uint32_t resp_data_len, struct io96b_mb_resp *resp);

/* Function: io96b_mb_init
 *
 * Reads the interface info registers and stores each IP type and instance id.
 *
 * For every IO96B instance, reads interface info 0 and 1. An interface
 * whose IP type is not zero is stored, and num_mem_interface grows by one.
 * Call this before a command that needs those ids.
 *
 * Parameters:
 *   io96b_ctrl - CSR addresses in. Interface ids and the interface count out.
 *
 * Returns:
 *   Nothing.
 */
void io96b_mb_init(struct io96b_info *io96b_ctrl);

/* Function: io96b_cal_status
 *
 * Waits for one IO96B to finish calibration.
 * First waits until the calibration-fail bit is clear, then waits until
 * the calibration-success bit is set. Each wait lasts 15000 milliseconds.
 *
 * Parameters:
 *   addr - IO96B CSR base address.
 *
 * Returns:
 *   0 when calibration succeeded.
 *   -EBUSY if the fail bit stays set, or the success bit does not set.
 */
int io96b_cal_status(phys_addr_t addr);

/* Function: init_mem_cal
 *
 * Checks calibration on every IO96B instance.
 * Stores each result in cal_status. Sets overall_cal_status true only
 * when every instance succeeds.
 *
 * Parameters:
 *   io96b_ctrl - Instances to check. The status fields are written.
 *
 * Returns:
 *   Nothing.
 */
void init_mem_cal(struct io96b_info *io96b_ctrl);

/* Function: trig_mem_cal
 *
 * Runs calibration again on instances that failed the first check.
 *
 * Skips an instance whose cal_status is already true. For each of the
 * two interfaces, reads the low 3 bits of the calibration status. While
 * that value is 2 or more, sends TRIG_MEM_CAL and reads the status again,
 * up to 3 times. Sets overall_cal_status when both io96b_0 and io96b_1
 * have cal_status true.
 *
 * Parameters:
 *   io96b_ctrl - Instances to recalibrate.
 *
 * Returns:
 *   0 when each failed interface reaches a status below 2.
 *   -ETIMEDOUT if a mailbox wait expires.
 *   -EIO if an interface is still not calibrated after 3 tries.
 */
int trig_mem_cal(struct io96b_info *io96b_ctrl);

/* Function: get_mem_technology
 *
 * Reads the DDR type from each memory interface.
 *
 * Sends GET_MEM_TECHNOLOGY with command type CMD_GET_MEM_INFO. The low
 * 3 bits of the short response pick a name from the DDR type list, and
 * that name is stored in ddr_type. A later interface that reports a
 * different name is an error.
 *
 * Parameters:
 *   io96b_ctrl - Receives ddr_type.
 *
 * Returns:
 *   0 on success.
 *   -ETIMEDOUT if a mailbox wait expires.
 *   -EINVAL if the type id is greater than 6.
 *   -ENOEXEC if two interfaces report different types.
 */
int get_mem_technology(struct io96b_info *io96b_ctrl);

/* Function: get_mem_width_info
 *
 * Reads the size of each memory interface from the capacity registers.
 *
 * Bits 7:0 are a size in gigabits. The function turns that into bytes,
 * stores it in memory_size, and adds the interfaces into overall_size.
 *
 * Parameters:
 *   io96b_ctrl - Receives memory_size and overall_size.
 *
 * Returns:
 *   0 on success.
 *   -ENOEXEC if one instance size is 0, or the total size is 0.
 */
int get_mem_width_info(struct io96b_info *io96b_ctrl);

/* Function: ecc_enable_status
 *
 * Reads whether ECC is enabled, and whether it is inline ECC.
 *
 * A non-zero value in bits 1:0 sets ecc_status. On the first interface
 * that has ECC on, bit 8 is stored in is_inline_ecc. Every interface
 * must report the same ecc_status.
 *
 * Parameters:
 *   io96b_ctrl - Receives ecc_status and is_inline_ecc.
 *
 * Returns:
 *   0 on success.
 *   -ENOEXEC if two interfaces disagree.
 */
int ecc_enable_status(struct io96b_info *io96b_ctrl);

/* Function: bist_mem_init_start
 *
 * Starts memory-init BIST on every interface.
 * Calls inline_ecc_bist_mem_init() when is_inline_ecc is true.
 * Otherwise calls out_of_band_ecc_bist_mem_init().
 *
 * Parameters:
 *   io96b_ctrl - ECC mode and the interfaces to initialize.
 *
 * Returns:
 *   0 on success, or the error returned by the selected init path.
 */
int bist_mem_init_start(struct io96b_info *io96b_ctrl);

/* Function: get_ecc_dbe_status
 *
 * Reports whether any stored ECC error is a double-bit error.
 *
 * Reads the error count. When the count is not zero, walks that many
 * entries, up to MAX_ECC_ERR_COUNT, and tests each type. Then writes
 * the command that clears the error buffer.
 *
 * Parameters:
 *   io96b_ctrl - Instances to read.
 *
 * Returns:
 *   true if a double-bit error type was seen, otherwise false.
 */
bool get_ecc_dbe_status(struct io96b_info *io96b_ctrl);

#endif /* SOCFPGA_DDR_MAILBOX_H */
