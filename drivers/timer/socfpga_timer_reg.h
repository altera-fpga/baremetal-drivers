/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_timer_reg.h
 *
 * Timer register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_TIMER_REG_H__
#define __SOCFPGA_TIMER_REG_H__



/* Timer1 Load Count Register */
#define TIMER_TIMER1LOADCOUNT                               0x0000U
/* TIMER1CURRENTVAL */
#define TIMER_TIMER1CURRENTVAL                              0x0004U
/* Timer1 Control Register */
#define TIMER_TIMER1CONTROLREG                              0x0008U
/* Timer1 End-of-Interrupt Register */
#define TIMER_TIMER1EOI                                     0x000CU
/* Timer1 Interrupt Status Register */
#define TIMER_TIMER1INTSTAT                                 0x0010U
/* Timers Interrupt Status Register */
#define TIMER_TIMERSINTSTAT                                 0x00A0U
/* Timers End-of-Interrupt Register */
#define TIMER_TIMERSEOI                                     0x00A4U
/* Timers Raw Interrupt Status Register */
#define TIMER_TIMERSRAWINTSTAT                              0x00A8U
/* Timers Component Version */
#define TIMER_TIMERSCOMPVERSION                             0x00ACU

/* Bit fields of TIMER1LOADCOUNT register */
#define TIMER_TIMER1LOADCOUNT_TIMER1LOADCOUNT_MASK          0xFFFFFFFFU
#define TIMER_TIMER1LOADCOUNT_TIMER1LOADCOUNT_POS           0U

/* Bit fields of TIMER1CURRENTVAL register */
#define TIMER_TIMER1CURRENTVAL_TIMER1CURRENTVAL_MASK        0xFFFFFFFFU
#define TIMER_TIMER1CURRENTVAL_TIMER1CURRENTVAL_POS         0U

/* Bit fields of TIMER1CONTROLREG register */
#define TIMER_TIMER1CONTROLREG_TIMER_INTERRUPT_MASK_MASK    0x00000004U
#define TIMER_TIMER1CONTROLREG_TIMER_INTERRUPT_MASK_POS     2U
#define TIMER_TIMER1CONTROLREG_TIMER_MODE_MASK              0x00000002U
#define TIMER_TIMER1CONTROLREG_TIMER_MODE_POS               1U
#define TIMER_TIMER1CONTROLREG_TIMER_ENABLE_MASK            0x00000001U
#define TIMER_TIMER1CONTROLREG_TIMER_ENABLE_POS             0U

/* Bit fields of TIMER1EOI register */
#define TIMER_TIMER1EOI_TIMER1EOI_MASK                      0x00000001U
#define TIMER_TIMER1EOI_TIMER1EOI_POS                       0U

/* Bit fields of TIMER1INTSTAT register */
#define TIMER_TIMER1INTSTAT_TIMER1INTSTAT_MASK              0x00000001U
#define TIMER_TIMER1INTSTAT_TIMER1INTSTAT_POS               0U

/* Bit fields of TIMERSINTSTAT register */
#define TIMER_TIMERSINTSTAT_TIMERSINTSTAT_MASK              0x00000001U
#define TIMER_TIMERSINTSTAT_TIMERSINTSTAT_POS               0U

/* Bit fields of TIMERSEOI register */
#define TIMER_TIMERSEOI_TIMERSEOI_MASK                      0x00000001U
#define TIMER_TIMERSEOI_TIMERSEOI_POS                       0U

/* Bit fields of TIMERSRAWINTSTAT register */
#define TIMER_TIMERSRAWINTSTAT_TIMERSRAWINTSTAT_MASK        0x00000001U
#define TIMER_TIMERSRAWINTSTAT_TIMERSRAWINTSTAT_POS         0U

/* Bit fields of TIMERSCOMPVERSION register */
#define TIMER_TIMERSCOMPVERSION_TIMERSCOMPVERSION_MASK      0xFFFFFFFFU
#define TIMER_TIMERSCOMPVERSION_TIMERSCOMPVERSION_POS       0U

#endif
