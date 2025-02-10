# NOC Firewall Driver
This describes the registers and their operational details for integration of the NOC Firewall IP into a target design.
All the control over the registers are via IOCTL functions.

## NOC_FIREWALL_READ_REGS & NOC_FIREWALL_WRITE_REGS
Reads and Writes the whole register bank.

## NOC_FIREWALL_GET_NAND_REGISTER & NOC_FIREWALL_SET_NAND_REGISTER
Get and Set Per-Master Security bit for nand register.

## NOC_FIREWALL_GET_USB0_REGISTER & NOC_FIREWALL_SET_USB0_REGISTER
Get and Set Per-Master Security bit for usb0_register.

## NOC_FIREWALL_GET_USB1_REGISTER & NOC_FIREWALL_SET_USB1_REGISTER
Get and Set Per-Master Security bit for usb1_register.

## NOC_FIREWALL_GET_SPI_MASTER0 & NOC_FIREWALL_SET_SPI_MASTER0
Get and Set Per-Master Security bit for spi_master0.

## NOC_FIREWALL_GET_SPI_MASTER1 & NOC_FIREWALL_SET_SPI_MASTER1
Get and Set Per-Master Security bit for spi_master1.

## NOC_FIREWALL_GET_SPI_SLAVE0 & NOC_FIREWALL_SET_SPI_SLAVE0
Get and Set Per-Master Security bit for spi_slave0.

## NOC_FIREWALL_GET_SPI_SLAVE1 & NOC_FIREWALL_SET_SPI_SLAVE1
Get and Set Per-Master Security bit for spi_slave1.

## NOC_FIREWALL_GET_EMAC0 & NOC_FIREWALL_SET_EMAC0
Get and Set Per-Master Security bit for emac0.

## NOC_FIREWALL_GET_EMAC1 & NOC_FIREWALL_SET_EMAC1
Get and Set Per-Master Security bit for emac1.

## NOC_FIREWALL_GET_EMAC2 & NOC_FIREWALL_SET_EMAC2
Get and Set Per-Master Security bit for emac2.

## NOC_FIREWALL_GET_SDMMC & NOC_FIREWALL_SET_SDMMC
Get and Set Per-Master Security bit for sdmmc.

## NOC_FIREWALL_GET_GPIO0 & NOC_FIREWALL_SET_GPIO0
Get and Set Per-Master Security bit for gpio0.

## NOC_FIREWALL_GET_GPIO1 & NOC_FIREWALL_SET_GPIO1
Get and Set Per-Master Security bit for gpio1.

## NOC_FIREWALL_GET_I2C0 & NOC_FIREWALL_SET_I2C0
Get and Set Per-Master Security bit for i2c0.

## NOC_FIREWALL_GET_I2C1 & NOC_FIREWALL_SET_I2C1
Get and Set Per-Master Security bit for i2c1.

## NOC_FIREWALL_GET_I2C2 & NOC_FIREWALL_SET_I2C2
Get and Set Per-Master Security bit for i2c2.

## NOC_FIREWALL_GET_I2C3 & NOC_FIREWALL_SET_I2C3
Get and Set Per-Master Security bit for i2c3.

## NOC_FIREWALL_GET_I2C4 & NOC_FIREWALL_SET_I2C4
Get and Set Per-Master Security bit for i2c4.

## NOC_FIREWALL_GET_SP_TIMER0 & NOC_FIREWALL_SET_SP_TIMER0
Get and Set Per-Master Security bit for sp_timer0.

## NOC_FIREWALL_GET_SP_TIMER1 & NOC_FIREWALL_SET_SP_TIMER1
Get and Set Per-Master Security bit for sp_timer1.

## NOC_FIREWALL_GET_UART0 & NOC_FIREWALL_SET_UART0
Get and Set Per-Master Security bit for uart0.

## NOC_FIREWALL_GET_UART1 & NOC_FIREWALL_SET_UART1
Get and Set Per-Master Security bit for uart1.

## NOC_FIREWALL_GET_I3C0 & NOC_FIREWALL_SET_I3C0
Get and Set Per-Master Security bit for i3c0.

## NOC_FIREWALL_GET_I3C1 & NOC_FIREWALL_SET_I3C1
Get and Set Per-Master Security bit for i3c1.

## NOC_FIREWALL_GET_DMA0 & NOC_FIREWALL_SET_DMA0
Get and Set Per-Master Security bit for dma0.

## NOC_FIREWALL_GET_DMA1 & NOC_FIREWALL_SET_DMA1
Get and Set Per-Master Security bit for dma1.

## NOC_FIREWALL_GET_COMBO_PHY & NOC_FIREWALL_SET_COMBO_PHY
Get and Set Per-Master Security bit for combo_phy.

## NOC_FIREWALL_GET_NAND_SDMA & NOC_FIREWALL_SET_NAND_SDMA
Get and Set Per-Master Security bit for nand_sdma.

## NOC_FIREWALL_GET_DMA_ECC & NOC_FIREWALL_SET_DMA_ECC
Get and Set Per-Master Security bit for dma_ecc.

## NOC_FIREWALL_GET_EMAC0RX_ECC & NOC_FIREWALL_SET_EMAC0RX_ECC
Get and Set Per-Master Security bit for emac0rx_ecc.

## NOC_FIREWALL_GET_EMAC0TX_ECC & NOC_FIREWALL_SET_EMAC0TX_ECC
Get and Set Per-Master Security bit for emac0tx_ecc.

## NOC_FIREWALL_GET_EMAC1RX_ECC & NOC_FIREWALL_SET_EMAC1RX_ECC
Get and Set Per-Master Security bit for emac1rx_ecc.

## NOC_FIREWALL_GET_EMAC1TX_ECC & NOC_FIREWALL_SET_EMAC1TX_ECC
Get and Set Per-Master Security bit for emac1tx_ecc.

## NOC_FIREWALL_GET_EMAC2RX_ECC & NOC_FIREWALL_SET_EMAC2RX_ECC
Get and Set Per-Master Security bit for emac2rx_ecc.

## NOC_FIREWALL_GET_EMAC2TX_ECC & NOC_FIREWALL_SET_EMAC2TX_ECC
Get and Set Per-Master Security bit for emac2tx_ecc.

## NOC_FIREWALL_GET_NAND_ECC & NOC_FIREWALL_SET_NAND_ECC
Get and Set Per-Master Security bit for nand_ecc.

## NOC_FIREWALL_GET_NAND_READ_ECC & NOC_FIREWALL_SET_NAND_READ_ECC
Get and Set Per-Master Security bit for nand_read_ecc.

## NOC_FIREWALL_GET_NAND_WRITE_ECC & NOC_FIREWALL_SET_NAND_WRITE_ECC
Get and Set Per-Master Security bit for nand_write_ecc.

## NOC_FIREWALL_GET_OCRAM_ECC & NOC_FIREWALL_SET_OCRAM_ECC
Get and Set Per-Master Security bit for onchipram_ecc.

## NOC_FIREWALL_GET_SDMMC_ECC & NOC_FIREWALL_SET_SDMMC_ECC
Get and Set Per-Master Security bit for sdmmc_ecc.

## NOC_FIREWALL_GET_USB0_ECC & NOC_FIREWALL_SET_USB0_ECC
Get and Set Per-Master Security bit for usb0_ecc.

## NOC_FIREWALL_GET_USB1_CACHEECC & NOC_FIREWALL_SET_USB1_CACHEECC
Get and Set Per-Master Security bit for usb1_cacheecc.

## NOC_FIREWALL_GET_CLOCK_MANAGER & NOC_FIREWALL_SET_CLOCK_MANAGER
Get and Set Per-Master Security bit for clock_manager.

## NOC_FIREWALL_GET_IO_MANAGER & NOC_FIREWALL_SET_IO_MANAGER
Get and Set Per-Master Security bit for pin_mux_register.

## NOC_FIREWALL_GET_RESET_MANAGER & NOC_FIREWALL_SET_RESET_MANAGER
Get and Set Per-Master Security bit for reset_manager.

## NOC_FIREWALL_GET_SYSTEM_MANAGER & NOC_FIREWALL_SET_SYSTEM_MANAGER
Get and Set Per-Master Security bit for system_manager.

## NOC_FIREWALL_GET_OSC0_TIMER & NOC_FIREWALL_SET_OSC0_TIMER
Get and Set Per-Master Security bit for osc0_timer.

## NOC_FIREWALL_GET_OSC1_TIMER & NOC_FIREWALL_SET_OSC1_TIMER
Get and Set Per-Master Security bit for osc1_timer.

## NOC_FIREWALL_GET_WATCHDOG0 & NOC_FIREWALL_SET_WATCHDOG0
Get and Set Per-Master Security bit for watchdog0.

## NOC_FIREWALL_GET_WATCHDOG1 & NOC_FIREWALL_SET_WATCHDOG1
Get and Set Per-Master Security bit for watchdog1.

## NOC_FIREWALL_GET_WATCHDOG2 & NOC_FIREWALL_SET_WATCHDOG2
Get and Set Per-Master Security bit for watchdog2.

## NOC_FIREWALL_GET_WATCHDOG3 & NOC_FIREWALL_SET_WATCHDOG3
Get and Set Per-Master Security bit for watchdog3.

## NOC_FIREWALL_GET_DAP & NOC_FIREWALL_SET_DAP
Get and Set Per-Master Security bit for dap.

## NOC_FIREWALL_GET_WATCHDOG4 & NOC_FIREWALL_SET_WATCHDOG4
Get and Set Per-Master Security bit for watchdog4.

## NOC_FIREWALL_GET_POWER_MANAGER & NOC_FIREWALL_SET_POWER_MANAGER
Get and Set Per-Master Security bit for power_manager.

## NOC_FIREWALL_GET_USB1_RXECC & NOC_FIREWALL_SET_USB1_RXECC
Get and Set Per-Master Security bit for usb1_rxecc.

## NOC_FIREWALL_GET_USB1_TXECC & NOC_FIREWALL_SET_USB1_TXECC
Get and Set Per-Master Security bit for usb1_txecc.

## NOC_FIREWALL_GET_L4_NOC_PROBES & NOC_FIREWALL_SET_L4_NOC_PROBES
Get and Set Per-Master Security bit for noc_probes_register.

## NOC_FIREWALL_GET_L4_NOC_QOS & NOC_FIREWALL_SET_L4_NOC_QOS
Get and Set Per-Master Security bit for noc_probes_register.

## NOC_FIREWALL_GET_SOC2FPGA & NOC_FIREWALL_SET_SOC2FPGA
Get and Set Per-Master Security bit for SOC2FPGA.

## NOC_FIREWALL_GET_LWSOC2FPGA & NOC_FIREWALL_SET_LWSOC2FPGA
Get and Set Per-Master Security bit for Lightweight SOC2FPGA.

## NOC_FIREWALL_GET_TCU & NOC_FIREWALL_SET_TCU
Get and Set Per-Master Security bit for dma_ecc.

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_L4_NOC_FW_summary.html