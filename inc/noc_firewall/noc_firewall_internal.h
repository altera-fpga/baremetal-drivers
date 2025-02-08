#ifndef NOC_FIREWALL_INTERNAL_H
#define NOC_FIREWALL_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

/*
 *   This code controls the NOC FIREWALL for an Altera Agilex5e HPS
 */

// Whole register bank access
int32_t noc_firewall_read_internal(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_write_internal(int32_t base_address, uintptr_t param, size_t length);

// L4_per register bank access
int32_t noc_firewall_get_l4_per_nand_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_nand_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_usb0_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_usb0_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_usb1_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_usb1_register(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_spi_master0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_spi_master0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_spi_master1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_spi_master1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_spi_slave0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_spi_salve0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_spi_slave1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_spi_slave1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_emac0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_emac0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_emac1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_emac1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_emac2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_emac2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_sdmmc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_sdmmc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_gpio0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_gpio0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_gpio1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_gpio1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i2c0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i2c0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i2c1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i2c1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i2c2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i2c2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i2c3(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i2c3(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i2c4(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i2c4(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_sp_timer0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_sp_timer0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_sp_timer1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_sp_timer1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_uart0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_uart0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_uart1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_uart1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i3c0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i3c0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_i3c1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_i3c1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_dma0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_dma0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_dma1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_dma1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_combo_phy(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_combo_phy(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_per_nand_sdma(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_per_nand_sdma(int32_t base_address, uintptr_t param, size_t length);

// L4 sys register bank access
int32_t noc_firewall_get_l4_sys_dma_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_dma_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac0rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac0rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac0tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac0tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac1rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac1rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac1tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac1tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac2rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac2rx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_emac2tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_emac2tx_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_nand_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_nand_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_nand_read_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_nand_read_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_nand_write_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_nand_write_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_ocram_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_ocram_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_sdmmc_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_sdmmc_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_usb0_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_usb0_ecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_usb1_cacheecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_usb1_cacheecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_clock_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_clock_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_io_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_io_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_reset_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_reset_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_system_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_system_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_osc0_timer(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_osc0_timer(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_osc1_timer(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_osc1_timer(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_watchdog0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_watchdog0(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_watchdog1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_watchdog1(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_watchdog2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_watchdog2(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_watchdog3(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_watchdog3(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_dap(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_dap(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_watchdog4(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_watchdog4(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_power_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_power_manager(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_usb1_rxecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_usb1_rxecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_usb1_txecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_usb1_txecc(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_l4_noc_probes(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_l4_noc_probes(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_get_l4_sys_l4_noc_qos(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_l4_sys_l4_noc_qos(int32_t base_address, uintptr_t param, size_t length);

// HPS2FPGA register bank access
int32_t noc_firewall_get_hps2fpga_soc2fpga(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_hps2fpga_soc2fpga(int32_t base_address, uintptr_t param, size_t length);

// LWHPS2FPGA register bank access
int32_t noc_firewall_get_lwhps2fpga_lwsoc2fpga(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_lwhps2fpga_lwsoc2fpga(int32_t base_address, uintptr_t param, size_t length);

// TCU register bank access
int32_t noc_firewall_get_tcu_tcu(int32_t base_address, uintptr_t param, size_t length);
int32_t noc_firewall_set_tcu_tcu(int32_t base_address, uintptr_t param, size_t length);

#endif // NOC_FIREWALL_INTERNAL_H__