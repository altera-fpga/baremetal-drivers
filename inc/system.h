#ifndef SYSTEM_H__
#define SYSTEM_H__

#include <stdbool.h>
#include <stdint.h>

#ifndef __cplusplus
#ifdef __aarch64__
#define nullptr ((void *)0)
#endif // __aarch64__
#endif // __cplusplus

#define XGMAC0_BASE (0x10810000)
#define XGMAC1_BASE (0x10820000)
#define XGMAC2_BASE (0x10830000)

#define QSPI_BASE (0x108D2000)
#define QSPI_SRAM_BASE_OFFSET ((uint32_t)0x10900000 - (uint32_t)QSPI_BASE)

#define UART0_BASE (0X10C02000)
#define UART1_BASE (0X10C02100)
#define I2C0_BASE (0X10C02800)
#define I2C1_BASE (0X10C02900)
#define HPS_TMR_SP0 (0X10C03000)
#define HPS_TMR_SP1 (0X10C03100)
#define HPS_GPIO0_BASE (0X10C03200)
#define HPS_GPIO1_BASE (0X10C03300)
#define HPS_TMR_SYS0 (0X10D00000)
#define HPS_TMR_SYS1 (0X10D00100)
#define WATCHDOG_BASE0 (0X10D00200)
#define WATCHDOG_BASE1 (0X10D00300)
#define WATCHDOG_BASE2 (0X10D00400)
#define WATCHDOG_BASE3 (0X10D00500)
#define WATCHDOG_BASE4 (0X10D00600)
#define DMA0_BASE (0X10DB0000)
#define DMA1_BASE (0X10DC0000)
#define HPS_CLKMGR_REGS_BASE (0X10D10000)
#define HPS_CLKMGR_MAINPLL_REGS_BASE (0X10D10024)
#define HPS_CLKMGR_PERPLL_REGS_BASE (0X10D1007C)
#define HPS_CLKMGR_CTLGRP_REGS_BASE (0X10D100D0)
#define HPS_SYSMGR_BASE (0X10D12000)
#define I3C0_BASE (0X10DA0000)
#define I3C1_BASE (0X10DA1000)
#define SMMU_BASE (0X16000000)
#define HPS_GICD_BASE (0X1D000000)
#define HPS_GICA_BASE (0X1D010000)
#define HPS_GICT_BASE (0X1D020000)
#define HPS_GICP_BASE (0X1D030000)
#define HPS_GITS0_BASE (0X1D040000)
#define HPS_GITS0_TRANSLATER_BASE (0X1D050000)
#define HPS_GICR_LPI0_BASE (0X1D060000)
#define HPS_GICR_LPI1_BASE (0X1D080000)
#define HPS_GICR_LPI2_BASE (0X1D0A0000)
#define HPS_GICR_LPI3_BASE (0X1D0C0000)
#define HPS_GICR_SGI0_BASE (0X1D070000)
#define HPS_GICR_SGI1_BASE (0X1D090000)
#define HPS_GICR_SGI2_BASE (0X1D0B0000)
#define HPS_GICR_SGI3_BASE (0X1D0D0000)
#define HPS_GICDA_BASE (0X1D0E0000)
#define HPS_RSTMGR_BASE (0X10D11000)
#define SPIS0_BASE (0X10DA2000)
#define SPIS1_BASE (0X10DA3000)
#define SPIM0_BASE (0X10DA4000)
#define SPIM1_BASE (0X10DA5000)

#define CCU_BASE (0X1C000000)

#define XGMAC0_BASE (0x10810000)
#define XGMAC1_BASE (0x10820000)
#define XGMAC2_BASE (0x10830000)
#endif // SYSTEM_H__