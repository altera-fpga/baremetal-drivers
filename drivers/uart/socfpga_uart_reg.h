/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_uart_reg.h
 *
 * UART register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_UART_REG_H__
#define __SOCFPGA_UART_REG_H__

/* Section: System and Clock Registers */

/* Constants: UART base addressing
 *
 * Base address of one UART instance. Instances are 4 KB (0x1000) apart.
 *
 * GET_UART_BASE_ADDRESS - Base address of the given instance.
 */
#define GET_UART_BASE_ADDRESS(instance)    ((uint32_t)(ALT_HPS_UART_BASE + \
    (instance * 0x1000U)))

/* Constants: Clock Manager peripheral PLL (PERPLL)
 *
 * Address and bit that turn the UART clock on or off.
 *
 * CLK_PERPLL    - Register the driver reads to see the clock gate.
 * CLK_EN_SHIFT  - Start bit of the UART clock enable. The driver adds the instance number.
 * CLK_PERPLL_EN - Register the driver writes to turn the UART clock on or off.
 */
/* #define CLK_PERPLL                               0x10D1007CU */
#define CLK_PERPLL                               0x0915C0D0U
#define CLK_EN_SHIFT                             20U
#define CLK_PERPLL_EN                            (0x0U + CLK_PERPLL)

/* Constants: Reset Manager peripheral module (PERMOD)
 *
 * Address and bit shift for the UART hard reset in the Reset Manager.
 *
 * RST_MGR    - Base address of the Reset Manager.
 * RST_SHIFT  - Bit shift of the UART reset bit (bit 16).
 * RST_PERMOD - Peripheral module reset register, at RST_MGR plus 0x28.
 */
/* #define RST_MGR                                  0x10D11000U */
#define RST_MGR                                  0x09161000U
#define RST_SHIFT                                16U
#define RST_PERMOD                               (0x28U + RST_MGR)


/* Section: Core 16550 UART Registers
 *
 * The foundational Memory-Mapped I/O (MMIO) register offsets for the UART 
 * controller. These align with the industry-standard 16550 UART specification.
 */

/* Constant: UART_RBR
 * Receive Buffer Register (Read Only). The FIFO port where incoming serial 
 * bytes are retrieved by software.
 */
#define UART_RBR                                 0x0000U

/* Constant: UART_THR
 * Transmit Holding Register (Write Only). The FIFO port where outgoing software 
 * bytes are pushed to be serialized over the TX line.
 */
#define UART_THR                                 0x0000U

/* Constant: UART_DLL
 * Divisor Latch Low. The lower 8 bits of the clock divider used to set the 
 * baud rate. (Only accessible when DLAB=1 in the LCR).
 */
#define UART_DLL                                 0x0000U

/* Constant: UART_IER
 * Interrupt Enable Register. Masks or unmasks specific hardware interrupt 
 * sources (e.g., RX Data Available, TX Empty).
 */
#define UART_IER                                 0x0004U

/* Constant: UART_DLH
 * Divisor Latch High. The upper 8 bits of the baud rate clock divider. 
 * (Only accessible when DLAB=1 in the LCR).
 */
#define UART_DLH                                 0x0004U

/* Constant: UART_IIR
 * Interrupt Identification Register (Read Only). Used by the ISR to determine 
 * the highest-priority pending interrupt.
 */
#define UART_IIR                                 0x0008U

/* Constant: UART_FCR
 * FIFO Control Register (Write Only). Enables the FIFOs, clears their contents, 
 * and configures the DMA/Interrupt trigger watermark levels.
 */
#define UART_FCR                                 0x0008U

/* Constant: UART_LCR
 * Line Control Register. Configures the physical framing format (word length, 
 * stop bits, parity) and toggles the Divisor Latch Access Bit (DLAB).
 */
#define UART_LCR                                 0x000CU

/* Constant: UART_MCR
 * Modem Control Register. Manages hardware flow control pins (RTS/DTR) and 
 * internal diagnostic loopback modes.
 */
#define UART_MCR                                 0x0010U

/* Constant: UART_LSR
 * Line Status Register. Provides real-time status of the data lines and FIFOs, 
 * including framing errors, parity errors, and FIFO empty/full states.
 */
#define UART_LSR                                 0x0014U

/* Constant: UART_MSR
 * Modem Status Register. Provides the current state of the modem control lines 
 * (CTS, DSR, RI, DCD).
 */
#define UART_MSR                                 0x0018U

/* Constant: UART_SCR
 * Scratchpad Register. A general-purpose 8-bit register that software can use 
 * for data storage; it has no effect on UART operation.
 */
#define UART_SCR                                 0x001CU


/* Section: DesignWare Extensions and Shadow Registers
 *
 * Synopsys DesignWare specific extensions to the standard 16550 map. These include 
 * shadow registers for deep FIFO access and advanced component parameter configurations.
 */

/* Constants: Shadow receive and transmit registers
 *
 * Shadow copies of the receive buffer and the transmit holding register.
 * Each receive and transmit pair uses the same offset.
 *
 * UART_SRBR0  - Shadow receive buffer register 0.
 * UART_STHR0  - Shadow transmit holding register 0.
 * UART_SRBR1  - Shadow receive buffer register 1.
 * UART_STHR1  - Shadow transmit holding register 1.
 * UART_SRBR2  - Shadow receive buffer register 2.
 * UART_STHR2  - Shadow transmit holding register 2.
 * UART_SRBR3  - Shadow receive buffer register 3.
 * UART_STHR3  - Shadow transmit holding register 3.
 * UART_SRBR4  - Shadow receive buffer register 4.
 * UART_STHR4  - Shadow transmit holding register 4.
 * UART_SRBR5  - Shadow receive buffer register 5.
 * UART_STHR5  - Shadow transmit holding register 5.
 * UART_SRBR6  - Shadow receive buffer register 6.
 * UART_STHR6  - Shadow transmit holding register 6.
 * UART_SRBR7  - Shadow receive buffer register 7.
 * UART_STHR7  - Shadow transmit holding register 7.
 * UART_SRBR8  - Shadow receive buffer register 8.
 * UART_STHR8  - Shadow transmit holding register 8.
 * UART_SRBR9  - Shadow receive buffer register 9.
 * UART_STHR9  - Shadow transmit holding register 9.
 * UART_SRBR10 - Shadow receive buffer register 10.
 * UART_STHR10 - Shadow transmit holding register 10.
 * UART_SRBR11 - Shadow receive buffer register 11.
 * UART_STHR11 - Shadow transmit holding register 11.
 * UART_SRBR12 - Shadow receive buffer register 12.
 * UART_STHR12 - Shadow transmit holding register 12.
 * UART_SRBR13 - Shadow receive buffer register 13.
 * UART_STHR13 - Shadow transmit holding register 13.
 * UART_SRBR14 - Shadow receive buffer register 14.
 * UART_STHR14 - Shadow transmit holding register 14.
 * UART_SRBR15 - Shadow receive buffer register 15.
 * UART_STHR15 - Shadow transmit holding register 15.
 */
#define UART_SRBR0                               0x0030U
#define UART_STHR0                               0x0030U
#define UART_SRBR1                               0x0034U
#define UART_STHR1                               0x0034U
#define UART_SRBR2                               0x0038U
#define UART_STHR2                               0x0038U
#define UART_SRBR3                               0x003CU
#define UART_STHR3                               0x003CU
#define UART_SRBR4                               0x0040U
#define UART_STHR4                               0x0040U
#define UART_SRBR5                               0x0044U
#define UART_STHR5                               0x0044U
#define UART_SRBR6                               0x0048U
#define UART_STHR6                               0x0048U
#define UART_SRBR7                               0x004CU
#define UART_STHR7                               0x004CU
#define UART_SRBR8                               0x0050U
#define UART_STHR8                               0x0050U
#define UART_SRBR9                               0x0054U
#define UART_STHR9                               0x0054U
#define UART_SRBR10                              0x0058U
#define UART_STHR10                              0x0058U
#define UART_SRBR11                              0x005CU
#define UART_STHR11                              0x005CU
#define UART_SRBR12                              0x0060U
#define UART_STHR12                              0x0060U
#define UART_SRBR13                              0x0064U
#define UART_STHR13                              0x0064U
#define UART_SRBR14                              0x0068U
#define UART_STHR14                              0x0068U
#define UART_SRBR15                              0x006CU
#define UART_STHR15                              0x006CU

/* Constants: Advanced FIFO and status control
 *
 * Offsets of the extra FIFO, status, reset, and shadow control registers.
 *
 * UART_FAR   - FIFO access register.
 * UART_TFR   - Transmit FIFO read register.
 * UART_RFW   - Receive FIFO write register.
 * UART_USR   - UART status register. The driver reads it before writing or reading a byte.
 * UART_TFL   - Transmit FIFO level register.
 * UART_RFL   - Receive FIFO level register.
 * UART_SRR   - Software reset register.
 * UART_SRTS  - Shadow request-to-send register.
 * UART_SBCR  - Shadow break-control register.
 * UART_SDMAM - Shadow DMA mode register.
 * UART_SFE   - Shadow FIFO enable register.
 * UART_SRT   - Shadow receive-trigger register.
 * UART_STET  - Shadow transmit-empty trigger register.
 * UART_HTX   - Halt-transmit register.
 * UART_DMASA - DMA software-acknowledge register.
 */
#define UART_FAR                                 0x0070U
#define UART_TFR                                 0x0074U
#define UART_RFW                                 0x0078U
#define UART_USR                                 0x007CU
#define UART_TFL                                 0x0080U
#define UART_RFL                                 0x0084U
#define UART_SRR                                 0x0088U
#define UART_SRTS                                0x008CU
#define UART_SBCR                                0x0090U
#define UART_SDMAM                               0x0094U
#define UART_SFE                                 0x0098U
#define UART_SRT                                 0x009CU
#define UART_STET                                0x00A0U
#define UART_HTX                                 0x00A4U
#define UART_DMASA                               0x00A8U

/* Constants: Component identification
 *
 * Offsets of the parameter, version, and type registers.
 *
 * UART_CPR - Component parameter register.
 * UART_UCV - UART component version register.
 * UART_CTR - Component type register.
 */
#define UART_CPR                                 0x00F4U
#define UART_UCV                                 0x00F8U
#define UART_CTR                                 0x00FCU


/* Section: Register Bit Masks and Positions
 *
 * Defines the specific bitwise layout for extracting or modifying fields within 
 * the hardware registers.
 */

/* Constants: Buffer and latch masks
 *
 * Masks and bit positions for the data bytes and the baud divisor.
 *
 * UART_RBR_RBR_MASK - Mask for the received byte (bits 7:0).
 * UART_RBR_RBR_POS  - Bit position of the received byte (bit 0).
 * UART_DLL_DLL_MASK - Mask for the low byte of the baud divisor (bits 7:0).
 * UART_DLL_DLL_POS  - Bit position of the low byte of the baud divisor (bit 0).
 * UART_THR_THR_MASK - Mask for the byte to transmit (bits 7:0).
 * UART_THR_THR_POS  - Bit position of the byte to transmit (bit 0).
 * UART_DLH_DLH_MASK - Mask for the high byte of the baud divisor (bits 7:0).
 * UART_DLH_DLH_POS  - Bit position of the high byte of the baud divisor (bit 0).
 */
#define UART_RBR_RBR_MASK                        0x000000FFU
#define UART_RBR_RBR_POS                         0U
#define UART_DLL_DLL_MASK                        0x000000FFU
#define UART_DLL_DLL_POS                         0U
#define UART_THR_THR_MASK                        0x000000FFU
#define UART_THR_THR_POS                         0U
#define UART_DLH_DLH_MASK                        0x000000FFU
#define UART_DLH_DLH_POS                         0U

/* Constants: IER - interrupt enable register
 *
 * Masks and bit positions in the interrupt enable register.
 *
 * UART_IER_PTIME_MASK - Mask for bit 7 of the interrupt enable register. The driver sets it when the transmit interrupt is enabled.
 * UART_IER_PTIME_POS  - Bit position 7 of the interrupt enable register.
 * UART_IER_EDSSI_MASK - Mask for bit 3 of the interrupt enable register.
 * UART_IER_EDSSI_POS  - Bit position 3 of the interrupt enable register.
 * UART_IER_ELSI_MASK  - Mask for the line-status interrupt enable (bit 2). The driver sets it for the hardware-error interrupt.
 * UART_IER_ELSI_POS   - Bit position of the line-status interrupt enable (bit 2).
 * UART_IER_ETBEI_MASK - Mask for the transmit-empty interrupt enable (bit 1). The driver sets it to enable the transmit interrupt.
 * UART_IER_ETBEI_POS  - Bit position of the transmit-empty interrupt enable (bit 1).
 * UART_IER_ERBFI_MASK - Mask for the receive-data interrupt enable (bit 0). The driver sets it to enable the receive interrupt.
 * UART_IER_ERBFI_POS  - Bit position of the receive-data interrupt enable (bit 0).
 */
#define UART_IER_PTIME_MASK                      0x00000080U
#define UART_IER_PTIME_POS                       7U
#define UART_IER_EDSSI_MASK                      0x00000008U
#define UART_IER_EDSSI_POS                       3U
#define UART_IER_ELSI_MASK                       0x00000004U
#define UART_IER_ELSI_POS                        2U
#define UART_IER_ETBEI_MASK                      0x00000002U
#define UART_IER_ETBEI_POS                       1U
#define UART_IER_ERBFI_MASK                      0x00000001U
#define UART_IER_ERBFI_POS                       0U

/* Constants: IIR - interrupt identification register
 *
 * Masks and bit positions in the interrupt identification register.
 *
 * UART_IIR_FIFOSE_MASK - Mask for bits 7:6 of the interrupt identification register.
 * UART_IIR_FIFOSE_POS  - Bit position 6 of the interrupt identification register.
 * UART_IIR_IID_MASK    - Mask for the interrupt ID (bits 3:0). The driver reads these bits to see which event is pending.
 * UART_IIR_IID_POS     - Bit position of the interrupt ID (bit 0).
 */
#define UART_IIR_FIFOSE_MASK                     0x000000C0U
#define UART_IIR_FIFOSE_POS                      6U
#define UART_IIR_IID_MASK                        0x0000000FU
#define UART_IIR_IID_POS                         0U

/* Constants: FCR - FIFO control register
 *
 * Masks and bit positions in the FIFO control register.
 *
 * UART_FCR_RT_MASK     - Mask for the receive trigger level (bits 7:6).
 * UART_FCR_RT_POS      - Bit position of the receive trigger level (bit 6).
 * UART_FCR_TET_MASK    - Mask for the transmit-empty trigger level (bits 5:4).
 * UART_FCR_TET_POS     - Bit position of the transmit-empty trigger level (bit 4).
 * UART_FCR_DMAM_MASK   - Mask for the DMA mode select (bit 3).
 * UART_FCR_DMAM_POS    - Bit position of the DMA mode select (bit 3).
 * UART_FCR_XFIFOR_MASK - Mask for the transmit FIFO reset (bit 2). The driver sets it when it sets up the FIFOs.
 * UART_FCR_XFIFOR_POS  - Bit position of the transmit FIFO reset (bit 2).
 * UART_FCR_RFIFOR_MASK - Mask for the receive FIFO reset (bit 1). The driver sets it when it sets up the FIFOs.
 * UART_FCR_RFIFOR_POS  - Bit position of the receive FIFO reset (bit 1).
 * UART_FCR_FIFOE_MASK  - Mask for the FIFO enable (bit 0). The driver sets it to turn the FIFOs on.
 * UART_FCR_FIFOE_POS   - Bit position of the FIFO enable (bit 0).
 */
#define UART_FCR_RT_MASK                         0x000000C0U
#define UART_FCR_RT_POS                          6U
#define UART_FCR_TET_MASK                        0x00000030U
#define UART_FCR_TET_POS                         4U
#define UART_FCR_DMAM_MASK                       0x00000008U
#define UART_FCR_DMAM_POS                        3U
#define UART_FCR_XFIFOR_MASK                     0x00000004U
#define UART_FCR_XFIFOR_POS                      2U
#define UART_FCR_RFIFOR_MASK                     0x00000002U
#define UART_FCR_RFIFOR_POS                      1U
#define UART_FCR_FIFOE_MASK                      0x00000001U
#define UART_FCR_FIFOE_POS                       0U

/* Constants: LCR - line control register
 *
 * Masks and bit positions in the line control register.
 *
 * UART_LCR_DLAB_MASK  - Mask for the divisor latch access bit (bit 7). The driver sets it to 1 before writing the baud divisor, then clears it.
 * UART_LCR_DLAB_POS   - Bit position of the divisor latch access bit (bit 7).
 * UART_LCR_BREAK_MASK - Mask for the break control bit (bit 6).
 * UART_LCR_BREAK_POS  - Bit position of the break control bit (bit 6).
 * UART_LCR_SP_MASK    - Mask for bit 5 of the line control register.
 * UART_LCR_SP_POS     - Bit position 5 of the line control register.
 * UART_LCR_EPS_MASK   - Mask for the even-parity select (bit 4). The driver sets it, with parity enable, for even parity.
 * UART_LCR_EPS_POS    - Bit position of the even-parity select (bit 4).
 * UART_LCR_PEN_MASK   - Mask for the parity enable (bit 3). The driver sets it for odd or even parity.
 * UART_LCR_PEN_POS    - Bit position of the parity enable (bit 3).
 * UART_LCR_STOP_MASK  - Mask for the stop-bit select (bit 2). The driver sets it for two stop bits.
 * UART_LCR_STOP_POS   - Bit position of the stop-bit select (bit 2).
 * UART_LCR_DLS_MASK   - Mask for the data length (bits 1:0). The driver stores the word length minus 5 here.
 * UART_LCR_DLS_POS    - Bit position of the data length (bit 0).
 */
#define UART_LCR_DLAB_MASK                       0x00000080U
#define UART_LCR_DLAB_POS                        7U
#define UART_LCR_BREAK_MASK                      0x00000040U
#define UART_LCR_BREAK_POS                       6U
#define UART_LCR_SP_MASK                         0x00000020U
#define UART_LCR_SP_POS                          5U
#define UART_LCR_EPS_MASK                        0x00000010U
#define UART_LCR_EPS_POS                         4U
#define UART_LCR_PEN_MASK                        0x00000008U
#define UART_LCR_PEN_POS                         3U
#define UART_LCR_STOP_MASK                       0x00000004U
#define UART_LCR_STOP_POS                        2U
#define UART_LCR_DLS_MASK                        0x00000003U
#define UART_LCR_DLS_POS                         0U

/* Constants: MCR - modem control register
 *
 * Masks and bit positions in the modem control register.
 *
 * UART_MCR_SIRE_MASK     - Mask for bit 6 of the modem control register.
 * UART_MCR_SIRE_POS      - Bit position 6 of the modem control register.
 * UART_MCR_AFCE_MASK     - Mask for bit 5 of the modem control register.
 * UART_MCR_AFCE_POS      - Bit position 5 of the modem control register.
 * UART_MCR_LOOPBACK_MASK - Mask for the loopback bit (bit 4).
 * UART_MCR_LOOPBACK_POS  - Bit position of the loopback bit (bit 4).
 * UART_MCR_OUT2_MASK     - Mask for the OUT2 output (bit 3).
 * UART_MCR_OUT2_POS      - Bit position of the OUT2 output (bit 3).
 * UART_MCR_OUT1_MASK     - Mask for the OUT1 output (bit 2).
 * UART_MCR_OUT1_POS      - Bit position of the OUT1 output (bit 2).
 * UART_MCR_RTS_MASK      - Mask for the request to send bit (bit 1).
 * UART_MCR_RTS_POS       - Bit position of the request to send bit (bit 1).
 * UART_MCR_DTR_MASK      - Mask for the data terminal ready bit (bit 0).
 * UART_MCR_DTR_POS       - Bit position of the data terminal ready bit (bit 0).
 */
#define UART_MCR_SIRE_MASK                       0x00000040U
#define UART_MCR_SIRE_POS                        6U
#define UART_MCR_AFCE_MASK                       0x00000020U
#define UART_MCR_AFCE_POS                        5U
#define UART_MCR_LOOPBACK_MASK                   0x00000010U
#define UART_MCR_LOOPBACK_POS                    4U
#define UART_MCR_OUT2_MASK                       0x00000008U
#define UART_MCR_OUT2_POS                        3U
#define UART_MCR_OUT1_MASK                       0x00000004U
#define UART_MCR_OUT1_POS                        2U
#define UART_MCR_RTS_MASK                        0x00000002U
#define UART_MCR_RTS_POS                         1U
#define UART_MCR_DTR_MASK                        0x00000001U
#define UART_MCR_DTR_POS                         0U

/* Constants: LSR - line status register
 *
 * Masks and bit positions in the line status register.
 *
 * UART_LSR_RFE_MASK  - Mask for the receiver FIFO error (bit 7).
 * UART_LSR_RFE_POS   - Bit position of the receiver FIFO error (bit 7).
 * UART_LSR_TEMT_MASK - Mask for the transmitter empty flag (bit 6).
 * UART_LSR_TEMT_POS  - Bit position of the transmitter empty flag (bit 6).
 * UART_LSR_THRE_MASK - Mask for the holding register empty flag (bit 5).
 * UART_LSR_THRE_POS  - Bit position of the holding register empty flag (bit 5).
 * UART_LSR_BI_MASK   - Mask for the break interrupt (bit 4).
 * UART_LSR_BI_POS    - Bit position of the break interrupt (bit 4).
 * UART_LSR_FE_MASK   - Mask for the framing error (bit 3).
 * UART_LSR_FE_POS    - Bit position of the framing error (bit 3).
 * UART_LSR_PE_MASK   - Mask for the parity error (bit 2).
 * UART_LSR_PE_POS    - Bit position of the parity error (bit 2).
 * UART_LSR_OE_MASK   - Mask for the overrun error (bit 1).
 * UART_LSR_OE_POS    - Bit position of the overrun error (bit 1).
 * UART_LSR_DR_MASK   - Mask for the data ready flag (bit 0).
 * UART_LSR_DR_POS    - Bit position of the data ready flag (bit 0).
 */
#define UART_LSR_RFE_MASK                        0x00000080U
#define UART_LSR_RFE_POS                         7U
#define UART_LSR_TEMT_MASK                       0x00000040U
#define UART_LSR_TEMT_POS                        6U
#define UART_LSR_THRE_MASK                       0x00000020U
#define UART_LSR_THRE_POS                        5U
#define UART_LSR_BI_MASK                         0x00000010U
#define UART_LSR_BI_POS                          4U
#define UART_LSR_FE_MASK                         0x00000008U
#define UART_LSR_FE_POS                          3U
#define UART_LSR_PE_MASK                         0x00000004U
#define UART_LSR_PE_POS                          2U
#define UART_LSR_OE_MASK                         0x00000002U
#define UART_LSR_OE_POS                          1U
#define UART_LSR_DR_MASK                         0x00000001U
#define UART_LSR_DR_POS                          0U

/* Constants: MSR - modem status register
 *
 * Masks and bit positions in the modem status register.
 *
 * UART_MSR_DCD_MASK  - Mask for the data carrier detect bit (bit 7).
 * UART_MSR_DCD_POS   - Bit position of the data carrier detect bit (bit 7).
 * UART_MSR_RI_MASK   - Mask for the ring indicator bit (bit 6).
 * UART_MSR_RI_POS    - Bit position of the ring indicator bit (bit 6).
 * UART_MSR_DSR_MASK  - Mask for the data set ready bit (bit 5).
 * UART_MSR_DSR_POS   - Bit position of the data set ready bit (bit 5).
 * UART_MSR_CTS_MASK  - Mask for the clear to send bit (bit 4).
 * UART_MSR_CTS_POS   - Bit position of the clear to send bit (bit 4).
 * UART_MSR_DDCD_MASK - Mask for the data carrier detect change (bit 3).
 * UART_MSR_DDCD_POS  - Bit position of the data carrier detect change (bit 3).
 * UART_MSR_TERI_MASK - Mask for the ring indicator trailing edge (bit 2).
 * UART_MSR_TERI_POS  - Bit position of the ring indicator trailing edge (bit 2).
 * UART_MSR_DDSR_MASK - Mask for the data set ready change (bit 1).
 * UART_MSR_DDSR_POS  - Bit position of the data set ready change (bit 1).
 * UART_MSR_DCTS_MASK - Mask for the clear to send change (bit 0).
 * UART_MSR_DCTS_POS  - Bit position of the clear to send change (bit 0).
 */
#define UART_MSR_DCD_MASK                        0x00000080U
#define UART_MSR_DCD_POS                         7U
#define UART_MSR_RI_MASK                         0x00000040U
#define UART_MSR_RI_POS                          6U
#define UART_MSR_DSR_MASK                        0x00000020U
#define UART_MSR_DSR_POS                         5U
#define UART_MSR_CTS_MASK                        0x00000010U
#define UART_MSR_CTS_POS                         4U
#define UART_MSR_DDCD_MASK                       0x00000008U
#define UART_MSR_DDCD_POS                        3U
#define UART_MSR_TERI_MASK                       0x00000004U
#define UART_MSR_TERI_POS                        2U
#define UART_MSR_DDSR_MASK                       0x00000002U
#define UART_MSR_DDSR_POS                        1U
#define UART_MSR_DCTS_MASK                       0x00000001U
#define UART_MSR_DCTS_POS                        0U

/* Constants: SCR and shadow register masks
 *
 * Masks and bit positions for the scratchpad and the shadow data bytes.
 *
 * UART_SCR_SCR_MASK       - Mask for the scratchpad byte (bits 7:0).
 * UART_SCR_SCR_POS        - Bit position of the scratchpad byte (bit 0).
 * UART_SRBR0_SRBR0_MASK   - Mask for shadow receive data 0 (bits 7:0).
 * UART_SRBR0_SRBR0_POS    - Bit position of shadow receive data 0 (bit 0).
 * UART_STHR0_STHR0_MASK   - Mask for shadow transmit data 0 (bits 7:0).
 * UART_STHR0_STHR0_POS    - Bit position of shadow transmit data 0 (bit 0).
 * UART_SRBR1_SRBR1_MASK   - Mask for shadow receive data 1 (bits 7:0).
 * UART_SRBR1_SRBR1_POS    - Bit position of shadow receive data 1 (bit 0).
 * UART_STHR1_STHR1_MASK   - Mask for shadow transmit data 1 (bits 7:0).
 * UART_STHR1_STHR1_POS    - Bit position of shadow transmit data 1 (bit 0).
 * UART_SRBR2_SRBR2_MASK   - Mask for shadow receive data 2 (bits 7:0).
 * UART_SRBR2_SRBR2_POS    - Bit position of shadow receive data 2 (bit 0).
 * UART_STHR2_STHR2_MASK   - Mask for shadow transmit data 2 (bits 7:0).
 * UART_STHR2_STHR2_POS    - Bit position of shadow transmit data 2 (bit 0).
 * UART_SRBR3_SRBR3_MASK   - Mask for shadow receive data 3 (bits 7:0).
 * UART_SRBR3_SRBR3_POS    - Bit position of shadow receive data 3 (bit 0).
 * UART_STHR3_STHR3_MASK   - Mask for shadow transmit data 3 (bits 7:0).
 * UART_STHR3_STHR3_POS    - Bit position of shadow transmit data 3 (bit 0).
 * UART_SRBR4_SRBR4_MASK   - Mask for shadow receive data 4 (bits 7:0).
 * UART_SRBR4_SRBR4_POS    - Bit position of shadow receive data 4 (bit 0).
 * UART_STHR4_STHR4_MASK   - Mask for shadow transmit data 4 (bits 7:0).
 * UART_STHR4_STHR4_POS    - Bit position of shadow transmit data 4 (bit 0).
 * UART_SRBR5_SRBR5_MASK   - Mask for shadow receive data 5 (bits 7:0).
 * UART_SRBR5_SRBR5_POS    - Bit position of shadow receive data 5 (bit 0).
 * UART_STHR5_STHR5_MASK   - Mask for shadow transmit data 5 (bits 7:0).
 * UART_STHR5_STHR5_POS    - Bit position of shadow transmit data 5 (bit 0).
 * UART_SRBR6_SRBR6_MASK   - Mask for shadow receive data 6 (bits 7:0).
 * UART_SRBR6_SRBR6_POS    - Bit position of shadow receive data 6 (bit 0).
 * UART_STHR6_STHR6_MASK   - Mask for shadow transmit data 6 (bits 7:0).
 * UART_STHR6_STHR6_POS    - Bit position of shadow transmit data 6 (bit 0).
 * UART_SRBR7_SRBR7_MASK   - Mask for shadow receive data 7 (bits 7:0).
 * UART_SRBR7_SRBR7_POS    - Bit position of shadow receive data 7 (bit 0).
 * UART_STHR7_STHR7_MASK   - Mask for shadow transmit data 7 (bits 7:0).
 * UART_STHR7_STHR7_POS    - Bit position of shadow transmit data 7 (bit 0).
 * UART_SRBR8_SRBR8_MASK   - Mask for shadow receive data 8 (bits 7:0).
 * UART_SRBR8_SRBR8_POS    - Bit position of shadow receive data 8 (bit 0).
 * UART_STHR8_STHR8_MASK   - Mask for shadow transmit data 8 (bits 7:0).
 * UART_STHR8_STHR8_POS    - Bit position of shadow transmit data 8 (bit 0).
 * UART_SRBR9_SRBR9_MASK   - Mask for shadow receive data 9 (bits 7:0).
 * UART_SRBR9_SRBR9_POS    - Bit position of shadow receive data 9 (bit 0).
 * UART_STHR9_STHR9_MASK   - Mask for shadow transmit data 9 (bits 7:0).
 * UART_STHR9_STHR9_POS    - Bit position of shadow transmit data 9 (bit 0).
 * UART_SRBR10_SRBR10_MASK - Mask for shadow receive data 10 (bits 7:0).
 * UART_SRBR10_SRBR10_POS  - Bit position of shadow receive data 10 (bit 0).
 * UART_STHR10_STHR10_MASK - Mask for shadow transmit data 10 (bits 7:0).
 * UART_STHR10_STHR10_POS  - Bit position of shadow transmit data 10 (bit 0).
 * UART_SRBR11_SRBR11_MASK - Mask for shadow receive data 11 (bits 7:0).
 * UART_SRBR11_SRBR11_POS  - Bit position of shadow receive data 11 (bit 0).
 * UART_STHR11_STHR11_MASK - Mask for shadow transmit data 11 (bits 7:0).
 * UART_STHR11_STHR11_POS  - Bit position of shadow transmit data 11 (bit 0).
 * UART_SRBR12_SRBR12_MASK - Mask for shadow receive data 12 (bits 7:0).
 * UART_SRBR12_SRBR12_POS  - Bit position of shadow receive data 12 (bit 0).
 * UART_STHR12_STHR12_MASK - Mask for shadow transmit data 12 (bits 7:0).
 * UART_STHR12_STHR12_POS  - Bit position of shadow transmit data 12 (bit 0).
 * UART_SRBR13_SRBR13_MASK - Mask for shadow receive data 13 (bits 7:0).
 * UART_SRBR13_SRBR13_POS  - Bit position of shadow receive data 13 (bit 0).
 * UART_STHR13_STHR13_MASK - Mask for shadow transmit data 13 (bits 7:0).
 * UART_STHR13_STHR13_POS  - Bit position of shadow transmit data 13 (bit 0).
 * UART_SRBR14_SRBR14_MASK - Mask for shadow receive data 14 (bits 7:0).
 * UART_SRBR14_SRBR14_POS  - Bit position of shadow receive data 14 (bit 0).
 * UART_STHR14_STHR14_MASK - Mask for shadow transmit data 14 (bits 7:0).
 * UART_STHR14_STHR14_POS  - Bit position of shadow transmit data 14 (bit 0).
 * UART_SRBR15_SRBR15_MASK - Mask for shadow receive data 15 (bits 7:0).
 * UART_SRBR15_SRBR15_POS  - Bit position of shadow receive data 15 (bit 0).
 * UART_STHR15_STHR15_MASK - Mask for shadow transmit data 15 (bits 7:0).
 * UART_STHR15_STHR15_POS  - Bit position of shadow transmit data 15 (bit 0).
 */
#define UART_SCR_SCR_MASK                        0x000000FFU
#define UART_SCR_SCR_POS                         0U
#define UART_SRBR0_SRBR0_MASK                    0x000000FFU
#define UART_SRBR0_SRBR0_POS                     0U
#define UART_STHR0_STHR0_MASK                    0x000000FFU
#define UART_STHR0_STHR0_POS                     0U
#define UART_SRBR1_SRBR1_MASK                    0x000000FFU
#define UART_SRBR1_SRBR1_POS                     0U
#define UART_STHR1_STHR1_MASK                    0x000000FFU
#define UART_STHR1_STHR1_POS                     0U
#define UART_SRBR2_SRBR2_MASK                    0x000000FFU
#define UART_SRBR2_SRBR2_POS                     0U
#define UART_STHR2_STHR2_MASK                    0x000000FFU
#define UART_STHR2_STHR2_POS                     0U
#define UART_SRBR3_SRBR3_MASK                    0x000000FFU
#define UART_SRBR3_SRBR3_POS                     0U
#define UART_STHR3_STHR3_MASK                    0x000000FFU
#define UART_STHR3_STHR3_POS                     0U
#define UART_SRBR4_SRBR4_MASK                    0x000000FFU
#define UART_SRBR4_SRBR4_POS                     0U
#define UART_STHR4_STHR4_MASK                    0x000000FFU
#define UART_STHR4_STHR4_POS                     0U
#define UART_SRBR5_SRBR5_MASK                    0x000000FFU
#define UART_SRBR5_SRBR5_POS                     0U
#define UART_STHR5_STHR5_MASK                    0x000000FFU
#define UART_STHR5_STHR5_POS                     0U
#define UART_SRBR6_SRBR6_MASK                    0x000000FFU
#define UART_SRBR6_SRBR6_POS                     0U
#define UART_STHR6_STHR6_MASK                    0x000000FFU
#define UART_STHR6_STHR6_POS                     0U
#define UART_SRBR7_SRBR7_MASK                    0x000000FFU
#define UART_SRBR7_SRBR7_POS                     0U
#define UART_STHR7_STHR7_MASK                    0x000000FFU
#define UART_STHR7_STHR7_POS                     0U
#define UART_SRBR8_SRBR8_MASK                    0x000000FFU
#define UART_SRBR8_SRBR8_POS                     0U
#define UART_STHR8_STHR8_MASK                    0x000000FFU
#define UART_STHR8_STHR8_POS                     0U
#define UART_SRBR9_SRBR9_MASK                    0x000000FFU
#define UART_SRBR9_SRBR9_POS                     0U
#define UART_STHR9_STHR9_MASK                    0x000000FFU
#define UART_STHR9_STHR9_POS                     0U
#define UART_SRBR10_SRBR10_MASK                  0x000000FFU
#define UART_SRBR10_SRBR10_POS                   0U
#define UART_STHR10_STHR10_MASK                  0x000000FFU
#define UART_STHR10_STHR10_POS                   0U
#define UART_SRBR11_SRBR11_MASK                  0x000000FFU
#define UART_SRBR11_SRBR11_POS                   0U
#define UART_STHR11_STHR11_MASK                  0x000000FFU
#define UART_STHR11_STHR11_POS                   0U
#define UART_SRBR12_SRBR12_MASK                  0x000000FFU
#define UART_SRBR12_SRBR12_POS                   0U
#define UART_STHR12_STHR12_MASK                  0x000000FFU
#define UART_STHR12_STHR12_POS                   0U
#define UART_SRBR13_SRBR13_MASK                  0x000000FFU
#define UART_SRBR13_SRBR13_POS                   0U
#define UART_STHR13_STHR13_MASK                  0x000000FFU
#define UART_STHR13_STHR13_POS                   0U
#define UART_SRBR14_SRBR14_MASK                  0x000000FFU
#define UART_SRBR14_SRBR14_POS                   0U
#define UART_STHR14_STHR14_MASK                  0x000000FFU
#define UART_STHR14_STHR14_POS                   0U
#define UART_SRBR15_SRBR15_MASK                  0x000000FFU
#define UART_SRBR15_SRBR15_POS                   0U
#define UART_STHR15_STHR15_MASK                  0x000000FFU
#define UART_STHR15_STHR15_POS                   0U

/* Constants: Extension configuration masks
 *
 * Masks and bit positions for FIFO access and FIFO read or write data.
 *
 * UART_FAR_FAR_MASK  - Mask for the FIFO access bit (bit 0).
 * UART_FAR_FAR_POS   - Bit position of the FIFO access bit (bit 0).
 * UART_TFR_TFR_MASK  - Mask for the transmit FIFO read data (bits 7:0).
 * UART_TFR_TFR_POS   - Bit position of the transmit FIFO read data (bit 0).
 * UART_RFW_RFFE_MASK - Mask for the receive-FIFO framing error (bit 9).
 * UART_RFW_RFFE_POS  - Bit position of the receive-FIFO framing error (bit 9).
 * UART_RFW_RFPE_MASK - Mask for the receive-FIFO parity error (bit 8).
 * UART_RFW_RFPE_POS  - Bit position of the receive-FIFO parity error (bit 8).
 * UART_RFW_RFWD_MASK - Mask for the receive-FIFO write data (bits 7:0).
 * UART_RFW_RFWD_POS  - Bit position of the receive-FIFO write data (bit 0).
 */
#define UART_FAR_FAR_MASK                        0x00000001U
#define UART_FAR_FAR_POS                         0U
#define UART_TFR_TFR_MASK                        0x000000FFU
#define UART_TFR_TFR_POS                         0U
#define UART_RFW_RFFE_MASK                       0x00000200U
#define UART_RFW_RFFE_POS                        9U
#define UART_RFW_RFPE_MASK                       0x00000100U
#define UART_RFW_RFPE_POS                        8U
#define UART_RFW_RFWD_MASK                       0x000000FFU
#define UART_RFW_RFWD_POS                        0U

/* Constants: USR - UART status register
 *
 * Masks and bit positions in the UART status register.
 *
 * UART_USR_RFF_MASK  - Mask for the receive FIFO full flag (bit 4).
 * UART_USR_RFF_POS   - Bit position of the receive FIFO full flag (bit 4).
 * UART_USR_RFNE_MASK - Mask for the receive FIFO not empty flag (bit 3). The driver reads a byte when this bit is set.
 * UART_USR_RFNE_POS  - Bit position of the receive FIFO not empty flag (bit 3).
 * UART_USR_TFE_MASK  - Mask for the transmit FIFO empty flag (bit 2).
 * UART_USR_TFE_POS   - Bit position of the transmit FIFO empty flag (bit 2).
 * UART_USR_TFNF_MASK - Mask for the transmit FIFO not full flag (bit 1). The driver writes a byte when this bit is set.
 * UART_USR_TFNF_POS  - Bit position of the transmit FIFO not full flag (bit 1).
 */
#define UART_USR_RFF_MASK                        0x00000010U
#define UART_USR_RFF_POS                         4U
#define UART_USR_RFNE_MASK                       0x00000008U
#define UART_USR_RFNE_POS                        3U
#define UART_USR_TFE_MASK                        0x00000004U
#define UART_USR_TFE_POS                         2U
#define UART_USR_TFNF_MASK                       0x00000002U
#define UART_USR_TFNF_POS                        1U

/* Constants: FIFO level masks
 *
 * Masks and bit positions for the transmit and receive FIFO levels.
 *
 * UART_TFL_TFL_MASK - Mask for the transmit FIFO level (bits 7:0).
 * UART_TFL_TFL_POS  - Bit position of the transmit FIFO level (bit 0).
 * UART_RFL_RFL_MASK - Mask for the receive FIFO level (bits 7:0).
 * UART_RFL_RFL_POS  - Bit position of the receive FIFO level (bit 0).
 */
#define UART_TFL_TFL_MASK                        0x000000FFU
#define UART_TFL_TFL_POS                         0U
#define UART_RFL_RFL_MASK                        0x000000FFU
#define UART_RFL_RFL_POS                         0U

/* Constants: SRR - software reset register
 *
 * Masks and bit positions in the software reset register.
 *
 * UART_SRR_XFR_MASK - Mask for the transmit FIFO reset (bit 2).
 * UART_SRR_XFR_POS  - Bit position of the transmit FIFO reset (bit 2).
 * UART_SRR_RFR_MASK - Mask for the receive FIFO reset (bit 1).
 * UART_SRR_RFR_POS  - Bit position of the receive FIFO reset (bit 1).
 * UART_SRR_UR_MASK  - Mask for the UART reset (bit 0).
 * UART_SRR_UR_POS   - Bit position of the UART reset (bit 0).
 */
#define UART_SRR_XFR_MASK                        0x00000004U
#define UART_SRR_XFR_POS                         2U
#define UART_SRR_RFR_MASK                        0x00000002U
#define UART_SRR_RFR_POS                         1U
#define UART_SRR_UR_MASK                         0x00000001U
#define UART_SRR_UR_POS                          0U

/* Constants: Advanced shadow configuration masks
 *
 * Masks and bit positions for the shadow control bits.
 *
 * UART_SRTS_SRTS_MASK   - Mask for the shadow request-to-send bit (bit 0).
 * UART_SRTS_SRTS_POS    - Bit position of the shadow request-to-send bit (bit 0).
 * UART_SBCR_SBCB_MASK   - Mask for the shadow break-control bit (bit 0).
 * UART_SBCR_SBCB_POS    - Bit position of the shadow break-control bit (bit 0).
 * UART_SDMAM_SDMAM_MASK - Mask for the shadow DMA mode bit (bit 0).
 * UART_SDMAM_SDMAM_POS  - Bit position of the shadow DMA mode bit (bit 0).
 * UART_SFE_SFE_MASK     - Mask for the shadow FIFO enable (bit 0).
 * UART_SFE_SFE_POS      - Bit position of the shadow FIFO enable (bit 0).
 * UART_SRT_SRT_MASK     - Mask for the shadow receive trigger (bits 1:0).
 * UART_SRT_SRT_POS      - Bit position of the shadow receive trigger (bit 0).
 * UART_STET_STET_MASK   - Mask for the shadow transmit-empty trigger (bits 1:0).
 * UART_STET_STET_POS    - Bit position of the shadow transmit-empty trigger (bit 0).
 * UART_HTX_HTX_MASK     - Mask for the halt-transmit bit (bit 0).
 * UART_HTX_HTX_POS      - Bit position of the halt-transmit bit (bit 0).
 * UART_DMASA_DMASA_MASK - Mask for the DMA software-acknowledge bit (bit 0).
 * UART_DMASA_DMASA_POS  - Bit position of the DMA software-acknowledge bit (bit 0).
 */
#define UART_SRTS_SRTS_MASK                      0x00000001U
#define UART_SRTS_SRTS_POS                       0U
#define UART_SBCR_SBCB_MASK                      0x00000001U
#define UART_SBCR_SBCB_POS                       0U
#define UART_SDMAM_SDMAM_MASK                    0x00000001U
#define UART_SDMAM_SDMAM_POS                     0U
#define UART_SFE_SFE_MASK                        0x00000001U
#define UART_SFE_SFE_POS                         0U
#define UART_SRT_SRT_MASK                        0x00000003U
#define UART_SRT_SRT_POS                         0U
#define UART_STET_STET_MASK                      0x00000003U
#define UART_STET_STET_POS                       0U
#define UART_HTX_HTX_MASK                        0x00000001U
#define UART_HTX_HTX_POS                         0U
#define UART_DMASA_DMASA_MASK                    0x00000001U
#define UART_DMASA_DMASA_POS                     0U

/* Constants: CPR - component parameter register
 *
 * Masks and bit positions in the component parameter register.
 *
 * UART_CPR_FIFO_MODE_MASK               - Mask for the FIFO mode parameter (bits 23:16).
 * UART_CPR_FIFO_MODE_POS                - Bit position of the FIFO mode parameter (bit 16).
 * UART_CPR_DMA_EXTRA_MASK               - Mask for the extra DMA parameter (bit 13).
 * UART_CPR_DMA_EXTRA_POS                - Bit position of the extra DMA parameter (bit 13).
 * UART_CPR_UART_ADD_ENCODED_PARAMS_MASK - Mask for the additional encoded parameters (bit 12).
 * UART_CPR_UART_ADD_ENCODED_PARAMS_POS  - Bit position of the additional encoded parameters (bit 12).
 * UART_CPR_SHADOW_MASK                  - Mask for the shadow-register parameter (bit 11).
 * UART_CPR_SHADOW_POS                   - Bit position of the shadow-register parameter (bit 11).
 * UART_CPR_FIFO_STAT_MASK               - Mask for the FIFO status parameter (bit 10).
 * UART_CPR_FIFO_STAT_POS                - Bit position of the FIFO status parameter (bit 10).
 * UART_CPR_FIFO_ACCESS_MASK             - Mask for the FIFO access parameter (bit 9).
 * UART_CPR_FIFO_ACCESS_POS              - Bit position of the FIFO access parameter (bit 9).
 * UART_CPR_ADDITIONAL_FEAT_MASK         - Mask for the additional-features parameter (bit 8).
 * UART_CPR_ADDITIONAL_FEAT_POS          - Bit position of the additional-features parameter (bit 8).
 * UART_CPR_SIR_LP_MODE_MASK             - Mask for the SIR LP mode parameter (bit 7).
 * UART_CPR_SIR_LP_MODE_POS              - Bit position of the SIR LP mode parameter (bit 7).
 * UART_CPR_SIR_MODE_MASK                - Mask for the SIR mode parameter (bit 6).
 * UART_CPR_SIR_MODE_POS                 - Bit position of the SIR mode parameter (bit 6).
 * UART_CPR_THRE_MODE_MASK               - Mask for the transmit-empty mode parameter (bit 5).
 * UART_CPR_THRE_MODE_POS                - Bit position of the transmit-empty mode parameter (bit 5).
 * UART_CPR_AFCE_MODE_MASK               - Mask for the AFCE mode parameter (bit 4).
 * UART_CPR_AFCE_MODE_POS                - Bit position of the AFCE mode parameter (bit 4).
 * UART_CPR_APB_DATA_WIDTH_MASK          - Mask for the APB data width (bits 1:0).
 * UART_CPR_APB_DATA_WIDTH_POS           - Bit position of the APB data width (bit 0).
 */
#define UART_CPR_FIFO_MODE_MASK                  0x00FF0000U
#define UART_CPR_FIFO_MODE_POS                   16U
#define UART_CPR_DMA_EXTRA_MASK                  0x00002000U
#define UART_CPR_DMA_EXTRA_POS                   13U
#define UART_CPR_UART_ADD_ENCODED_PARAMS_MASK    0x00001000U
#define UART_CPR_UART_ADD_ENCODED_PARAMS_POS     12U
#define UART_CPR_SHADOW_MASK                     0x00000800U
#define UART_CPR_SHADOW_POS                      11U
#define UART_CPR_FIFO_STAT_MASK                  0x00000400U
#define UART_CPR_FIFO_STAT_POS                   10U
#define UART_CPR_FIFO_ACCESS_MASK                0x00000200U
#define UART_CPR_FIFO_ACCESS_POS                 9U
#define UART_CPR_ADDITIONAL_FEAT_MASK            0x00000100U
#define UART_CPR_ADDITIONAL_FEAT_POS             8U
#define UART_CPR_SIR_LP_MODE_MASK                0x00000080U
#define UART_CPR_SIR_LP_MODE_POS                 7U
#define UART_CPR_SIR_MODE_MASK                   0x00000040U
#define UART_CPR_SIR_MODE_POS                    6U
#define UART_CPR_THRE_MODE_MASK                  0x00000020U
#define UART_CPR_THRE_MODE_POS                   5U
#define UART_CPR_AFCE_MODE_MASK                  0x00000010U
#define UART_CPR_AFCE_MODE_POS                   4U
#define UART_CPR_APB_DATA_WIDTH_MASK             0x00000003U
#define UART_CPR_APB_DATA_WIDTH_POS              0U

/* Constants: Component version and ID masks
 *
 * Masks and bit positions for the version and the peripheral ID.
 *
 * UART_UCV_UART_COMPONENT_VERSION_MASK - Mask for the component version (bits 31:0).
 * UART_UCV_UART_COMPONENT_VERSION_POS  - Bit position of the component version (bit 0).
 * UART_CTR_PERIPHERAL_ID_MASK          - Mask for the peripheral ID (bits 31:0).
 * UART_CTR_PERIPHERAL_ID_POS           - Bit position of the peripheral ID (bit 0).
 */
#define UART_UCV_UART_COMPONENT_VERSION_MASK     0xFFFFFFFFU
#define UART_UCV_UART_COMPONENT_VERSION_POS      0U
#define UART_CTR_PERIPHERAL_ID_MASK              0xFFFFFFFFU
#define UART_CTR_PERIPHERAL_ID_POS               0U

#endif /* __SOCFPGA_UART_REG_H__ */