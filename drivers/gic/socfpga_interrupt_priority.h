/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_interrupt_priority.h
 *
 * GIC hardware abstraction driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_INTERRUPT_PRIORITY_H__
#define __SOCFPGA_INTERRUPT_PRIORITY_H__

#define GIC_INTERRUPT_PRIORITY_GPIO     14
#define GIC_INTERRUPT_PRIORITY_WDOG     14
#define GIC_INTERRUPT_PRIORITY_I2C      14
#define GIC_INTERRUPT_PRIORITY_UART     14
#define GIC_INTERRUPT_PRIORITY_TIMER    14
#define GIC_INTERRUPT_PRIORITY_DMA      14
#define GIC_INTERRUPT_PRIORITY_IOSSM    14
#define GIC_INTERRUPT_PRIORITY_SDMMC    14
#define GIC_INTERRUPT_PRIORITY_SPI      14
#define GIC_INTERRUPT_PRIORITY_SEU      14
#define GIC_INTERRUPT_PRIORITY_I3C      14
#define GIC_INTERRUPT_PRIORITY_EDAC     14

#endif
