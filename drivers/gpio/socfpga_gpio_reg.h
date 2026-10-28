/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_gpio_reg.h
 *
 * GPIO register definition header for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef __SOCFPGA_GPIO_REG_H__
#define __SOCFPGA_GPIO_REG_H__

/* Port A data register */
#define GPIO_SWPORTA_DR                                   0x0000U
/* Port A Data Direction Register */
#define GPIO_SWPORTA_DDR                                  0x0004U
/* Interrupt enable register */
#define GPIO_INTEN                                        0x0030U
/* Interrupt mask register */
#define GPIO_INTMASK                                      0x0034U
/* Interrupt level */
#define GPIO_INTTYPE_LEVEL                                0x0038U
/* Interrupt polarity */
#define GPIO_INT_POLARITY                                 0x003CU
/* Interrupt status */
#define GPIO_INTSTATUS                                    0x0040U
/* Raw interrupt status */
#define GPIO_RAW_INTSTATUS                                0x0044U
/* Debounce enable */
#define GPIO_DEBOUNCE                                     0x0048U
/* Port A clear interrupt register */
#define GPIO_PORTA_EOI                                    0x004CU
/* Port A external port register */
#define GPIO_EXT_PORTA                                    0x0050U
/* Synchronization level */
#define GPIO_LS_SYNC                                      0x0060U
/* GPIO ID code */
#define GPIO_ID_CODE                                      0x0064U
/* GPIO Component Version */
#define GPIO_VER_ID_CODE                                  0x006CU
/* GPIO Configuration Register 2 */
#define GPIO_CONFIG_REG2                                  0x0070U
/* GPIO Configuration Register 1 */
#define GPIO_CONFIG_REG1                                  0x0074U

/* Bit fields of GPIO_SWPORTA_DR register */
#define GPIO_SWPORTA_DR_MASK                              0x00FFFFFFU
#define GPIO_SWPORTA_DR_POS                               0U

/* Bit fields of GPIO_SWPORTA_DDR register */
#define GPIO_SWPORTA_DDR_MASK                             0x00FFFFFFU
#define GPIO_SWPORTA_DDR_POS                              0U

/* Bit fields of GPIO_INTEN register */
#define GPIO_INTEN_MASK                                   0x00FFFFFFU
#define GPIO_INTEN_POS                                    0U

/* Bit fields of GPIO_INTMASK register */
#define GPIO_INTMASK_MASK                                 0x00FFFFFFU
#define GPIO_INTMASK_POS                                  0U

/* Bit fields of GPIO_INTTYPE_LEVEL register */
#define GPIO_INTTYPE_LEVEL_MASK                           0x00FFFFFFU
#define GPIO_INTTYPE_LEVEL_POS                            0U

/* Bit fields of GPIO_INT_POLARITY register */
#define GPIO_INT_POLARITY_MASK                            0x00FFFFFFU
#define GPIO_INT_POLARITY_POS                             0U

/* Bit fields of GPIO_INTSTATUS register */
#define GPIO_INTSTATUS_MASK                               0x00FFFFFFU
#define GPIO_INTSTATUS_POS                                0U

/* Bit fields of GPIO_RAW_INTSTATUS register */
#define GPIO_RAW_INTSTATUS_MASK                           0x00FFFFFFU
#define GPIO_RAW_INTSTATUS_POS                            0U

/* Bit fields of GPIO_DEBOUNCE register */
#define GPIO_DEBOUNCE_MASK                                0x00FFFFFFU
#define GPIO_DEBOUNCE_POS                                 0U

/* Bit fields of GPIO_PORTA_EOI register */
#define GPIO_PORTA_EOI_MASK                               0x00FFFFFFU
#define GPIO_PORTA_EOI_POS                                0U

/* Bit fields of GPIO_EXT_PORTA register */
#define GPIO_EXT_PORTA_MASK                               0x00FFFFFFU
#define GPIO_EXT_PORTA_POS                                0U

/* Bit fields of GPIO_LS_SYNC register */
#define GPIO_LS_SYNC_MASK                                 0x00000001U
#define GPIO_LS_SYNC_POS                                  0U

/* Bit fields of GPIO_ID_CODE register */
#define GPIO_ID_CODE_MASK                                 0xFFFFFFFFU
#define GPIO_ID_CODE_POS                                  0U

/* Bit fields of GPIO_VER_ID_CODE register */
#define GPIO_VER_ID_CODE_MASK                             0xFFFFFFFFU
#define GPIO_VER_ID_CODE_POS                              0U

/* Bit fields of GPIO_CONFIG_REG2 register */
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_D_MASK         0x000F8000U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_D_POS          15U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_C_MASK         0x00007C00U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_C_POS          10U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_B_MASK         0x000003E0U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_B_POS          5U
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_A_MASK         0x0000001FU
#define GPIO_CONFIG_REG2_ENCODED_ID_PWIDTH_A_POS          0U

/* Bit fields of GPIO_CONFIG_REG1 register */
#define GPIO_CONFIG_REG1_INTERRUPT_BOTH_EDGE_TYPE_MASK    0x00200000U
#define GPIO_CONFIG_REG1_INTERRUPT_BOTH_EDGE_TYPE_POS     21U
#define GPIO_CONFIG_REG1_ENCODED_ID_WIDTH_MASK            0x001F0000U
#define GPIO_CONFIG_REG1_ENCODED_ID_WIDTH_POS             16U
#define GPIO_CONFIG_REG1_GPIO_ID_MASK                     0x00008000U
#define GPIO_CONFIG_REG1_GPIO_ID_POS                      15U
#define GPIO_CONFIG_REG1_ADD_ENCODED_PARAMS_MASK          0x00004000U
#define GPIO_CONFIG_REG1_ADD_ENCODED_PARAMS_POS           14U
#define GPIO_CONFIG_REG1_DEBOUNCE_MASK                    0x00002000U
#define GPIO_CONFIG_REG1_DEBOUNCE_POS                     13U
#define GPIO_CONFIG_REG1_PORTA_INTR_MASK                  0x00001000U
#define GPIO_CONFIG_REG1_PORTA_INTR_POS                   12U
#define GPIO_CONFIG_REG1_HW_PORTD_MASK                    0x00000800U
#define GPIO_CONFIG_REG1_HW_PORTD_POS                     11U
#define GPIO_CONFIG_REG1_HW_PORTC_MASK                    0x00000400U
#define GPIO_CONFIG_REG1_HW_PORTC_POS                     10U
#define GPIO_CONFIG_REG1_HW_PORTB_MASK                    0x00000200U
#define GPIO_CONFIG_REG1_HW_PORTB_POS                     9U
#define GPIO_CONFIG_REG1_HW_PORTA_MASK                    0x00000100U
#define GPIO_CONFIG_REG1_HW_PORTA_POS                     8U
#define GPIO_CONFIG_REG1_PORTD_SINGLE_CTL_MASK            0x00000080U
#define GPIO_CONFIG_REG1_PORTD_SINGLE_CTL_POS             7U
#define GPIO_CONFIG_REG1_PORTC_SINGLE_CTL_MASK            0x00000040U
#define GPIO_CONFIG_REG1_PORTC_SINGLE_CTL_POS             6U
#define GPIO_CONFIG_REG1_PORTB_SINGLE_CTL_MASK            0x00000020U
#define GPIO_CONFIG_REG1_PORTB_SINGLE_CTL_POS             5U
#define GPIO_CONFIG_REG1_PORTA_SINGLE_CTL_MASK            0x00000010U
#define GPIO_CONFIG_REG1_PORTA_SINGLE_CTL_POS             4U
#define GPIO_CONFIG_REG1_NUM_PORTS_MASK                   0x0000000CU
#define GPIO_CONFIG_REG1_NUM_PORTS_POS                    2U
#define GPIO_CONFIG_REG1_APB_DATA_WIDTH_MASK              0x00000003U
#define GPIO_CONFIG_REG1_APB_DATA_WIDTH_POS               0U



#endif /*  __SOCFPGA_GPIO_REG_H__ */
