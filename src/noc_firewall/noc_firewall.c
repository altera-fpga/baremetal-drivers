#include "noc_firewall.h"
#include "device.h"
#include "noc_firewall_internal.h"
#include "noc_firewall_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// NOC firewall descriptor
device_descriptor_t noc_firewall_devices[] = {{.name = "/dev/noc_firewall0", .fd = NOC_FIREWALL_BASE, .acquired = 0}};

/* name: noc_firewall_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t noc_firewall_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != NULL) {
        for (uint32_t i = 0; i < (sizeof(noc_firewall_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(noc_firewall_devices[i].name, path) == 0) {
                if (claim_device(&noc_firewall_devices[i])) {
                    return_value = noc_firewall_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}

/* name: noc_firewall_close
 * description: close the base_add via the base address of the device
 * parameters(s): base_add "address of the noc firewall device open"
 */
int32_t noc_firewall_close(int32_t base_add) {
    int32_t return_value = -1;
    if (base_add != -1) {
        for (uint32_t i = 0; i < (sizeof(noc_firewall_devices) / sizeof(device_descriptor_t)); i++) {
            if (noc_firewall_devices[i].fd == base_add) {
                noc_firewall_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}

/* name: noc_firewall_read
 * description: reading registers
 * parameters(s): base_add "address of the noc firewall device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t noc_firewall_read(int32_t base_add, uintptr_t user_data, size_t length) {
    return noc_firewall_recv(base_add, user_data, length, 0);
}

/* name: noc_firewall_write
 * description: writing registers
 * parameters(s): base_add "address of the noc_firewall device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
size_t noc_firewall_write(int32_t base_add, uintptr_t user_data, size_t length) {
    return noc_firewall_send(base_add, user_data, length, 0);
}

/* name: noc_firewall_recv
 * description: reading registers
 * parameters(s): base_add "address of the noc firewall device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t noc_firewall_recv(int32_t base_add, uintptr_t user_data, size_t length, int32_t flags) { return 0; }

/* name: noc_firewall_send
 * description: writing registers
 * parameters(s): base_add "address of the noc firewall device open"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 *                flags "any flags for a specific operation"
 */
size_t noc_firewall_send(int32_t base_add, uintptr_t user_data, size_t size, int32_t flags) { return 0; }

/* name: noc_firewall_ioctl
 * description: process the input output control command
 * parameters(s): base_add, user_data, length "address of the noc firewall device open"
 *                operation "specific ioctl command for noc firewall"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to"
 */
int32_t noc_firewall_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    int32_t return_value = -1;
    if ((base_add == -1) || (((void *)(user_data)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((noc_firewall_ioctl_t)operation) {
        case IOCTL_NOC_FIREWALL_READ_REGS:
            return_value = noc_firewall_read_internal(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_WRITE_REGS:
            return_value = noc_firewall_write_internal(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_NAND_REGISTER:
            return_value = noc_firewall_get_l4_per_nand_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_NAND_REGISTER:
            return_value = noc_firewall_set_l4_per_nand_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB0_REGISTER:
            return_value = noc_firewall_get_l4_per_usb0_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB0_REGISTER:
            return_value = noc_firewall_set_l4_per_usb0_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB1_REGISTER:
            return_value = noc_firewall_get_l4_per_usb1_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB1_REGISTER:
            return_value = noc_firewall_set_l4_per_usb1_register(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SPI_MASTER0:
            return_value = noc_firewall_get_l4_per_spi_master0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SPI_MASTER0:
            return_value = noc_firewall_set_l4_per_spi_master0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SPI_MASTER1:
            return_value = noc_firewall_get_l4_per_spi_master1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SPI_MASTER1:
            return_value = noc_firewall_set_l4_per_spi_master1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SPI_SLAVE0:
            return_value = noc_firewall_get_l4_per_spi_slave0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SPI_SLAVE0:
            return_value = noc_firewall_set_l4_per_spi_salve0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SPI_SLAVE1:
            return_value = noc_firewall_get_l4_per_spi_slave1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SPI_SLAVE1:
            return_value = noc_firewall_set_l4_per_spi_slave1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC0:
            return_value = noc_firewall_get_l4_per_emac0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC0:
            return_value = noc_firewall_set_l4_per_emac0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC1:
            return_value = noc_firewall_get_l4_per_emac1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC1:
            return_value = noc_firewall_set_l4_per_emac1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC2:
            return_value = noc_firewall_get_l4_per_emac2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC2:
            return_value = noc_firewall_set_l4_per_emac2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SDMMC:
            return_value = noc_firewall_get_l4_per_sdmmc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SDMMC:
            return_value = noc_firewall_set_l4_per_sdmmc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_GPIO0:
            return_value = noc_firewall_get_l4_per_gpio0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_GPIO0:
            return_value = noc_firewall_set_l4_per_gpio0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_GPIO1:
            return_value = noc_firewall_get_l4_per_gpio1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_GPIO1:
            return_value = noc_firewall_set_l4_per_gpio1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I2C0:
            return_value = noc_firewall_get_l4_per_i2c0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I2C0:
            return_value = noc_firewall_set_l4_per_i2c0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I2C1:
            return_value = noc_firewall_get_l4_per_i2c1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I2C1:
            return_value = noc_firewall_set_l4_per_i2c1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I2C2:
            return_value = noc_firewall_get_l4_per_i2c2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I2C2:
            return_value = noc_firewall_set_l4_per_i2c2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I2C3:
            return_value = noc_firewall_get_l4_per_i2c3(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I2C3:
            return_value = noc_firewall_set_l4_per_i2c3(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I2C4:
            return_value = noc_firewall_get_l4_per_i2c4(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I2C4:
            return_value = noc_firewall_set_l4_per_i2c4(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SP_TIMER0:
            return_value = noc_firewall_get_l4_per_sp_timer0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SP_TIMER0:
            return_value = noc_firewall_set_l4_per_sp_timer0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SP_TIMER1:
            return_value = noc_firewall_get_l4_per_sp_timer1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SP_TIMER1:
            return_value = noc_firewall_set_l4_per_sp_timer1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_UART0:
            return_value = noc_firewall_get_l4_per_uart0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_UART0:
            return_value = noc_firewall_set_l4_per_uart0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_UART1:
            return_value = noc_firewall_get_l4_per_uart1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_UART1:
            return_value = noc_firewall_set_l4_per_uart1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I3C0:
            return_value = noc_firewall_get_l4_per_i3c0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I3C0:
            return_value = noc_firewall_set_l4_per_i3c0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_I3C1:
            return_value = noc_firewall_get_l4_per_i3c1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_I3C1:
            return_value = noc_firewall_set_l4_per_i3c1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_DMA0:
            return_value = noc_firewall_get_l4_per_dma0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_DMA0:
            return_value = noc_firewall_set_l4_per_dma0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_DMA1:
            return_value = noc_firewall_get_l4_per_dma1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_DMA1:
            return_value = noc_firewall_set_l4_per_dma1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_COMBO_PHY:
            return_value = noc_firewall_get_l4_per_combo_phy(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_COMBO_PHY:
            return_value = noc_firewall_set_l4_per_combo_phy(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_NAND_SDMA:
            return_value = noc_firewall_get_l4_per_nand_sdma(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_NAND_SDMA:
            return_value = noc_firewall_set_l4_per_nand_sdma(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_DMA_ECC:
            return_value = noc_firewall_get_l4_sys_dma_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_DMA_ECC:
            return_value = noc_firewall_set_l4_sys_dma_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC0RX_ECC:
            return_value = noc_firewall_get_l4_sys_emac0rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC0RX_ECC:
            return_value = noc_firewall_set_l4_sys_emac0rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC0TX_ECC:
            return_value = noc_firewall_get_l4_sys_emac0tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC0TX_ECC:
            return_value = noc_firewall_set_l4_sys_emac0tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC1RX_ECC:
            return_value = noc_firewall_get_l4_sys_emac1rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC1RX_ECC:
            return_value = noc_firewall_set_l4_sys_emac1rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC1TX_ECC:
            return_value = noc_firewall_get_l4_sys_emac1tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC1TX_ECC:
            return_value = noc_firewall_set_l4_sys_emac1tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC2RX_ECC:
            return_value = noc_firewall_get_l4_sys_emac2rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC2RX_ECC:
            return_value = noc_firewall_set_l4_sys_emac2rx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_EMAC2TX_ECC:
            return_value = noc_firewall_get_l4_sys_emac2tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_EMAC2TX_ECC:
            return_value = noc_firewall_set_l4_sys_emac2tx_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_NAND_ECC:
            return_value = noc_firewall_get_l4_sys_nand_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_NAND_ECC:
            return_value = noc_firewall_set_l4_sys_nand_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_NAND_READ_ECC:
            return_value = noc_firewall_get_l4_sys_nand_read_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_NAND_READ_ECC:
            return_value = noc_firewall_set_l4_sys_nand_read_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_NAND_WRITE_ECC:
            return_value = noc_firewall_get_l4_sys_nand_write_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_NAND_WRITE_ECC:
            return_value = noc_firewall_set_l4_sys_nand_write_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_OCRAM_ECC:
            return_value = noc_firewall_get_l4_sys_ocram_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_OCRAM_ECC:
            return_value = noc_firewall_set_l4_sys_ocram_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SDMMC_ECC:
            return_value = noc_firewall_get_l4_sys_sdmmc_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SDMMC_ECC:
            return_value = noc_firewall_set_l4_sys_sdmmc_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB0_ECC:
            return_value = noc_firewall_get_l4_sys_usb0_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB0_ECC:
            return_value = noc_firewall_set_l4_sys_usb0_ecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB1_CACHEECC:
            return_value = noc_firewall_get_l4_sys_usb1_cacheecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB1_CACHEECC:
            return_value = noc_firewall_set_l4_sys_usb1_cacheecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_CLOCK_MANAGER:
            return_value = noc_firewall_get_l4_sys_clock_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_CLOCK_MANAGER:
            return_value = noc_firewall_set_l4_sys_clock_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_IO_MANAGER:
            return_value = noc_firewall_get_l4_sys_io_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_IO_MANAGER:
            return_value = noc_firewall_set_l4_sys_io_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_RESET_MANAGER:
            return_value = noc_firewall_get_l4_sys_reset_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_RESET_MANAGER:
            return_value = noc_firewall_set_l4_sys_reset_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SYSTEM_MANAGER:
            return_value = noc_firewall_get_l4_sys_system_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SYSTEM_MANAGER:
            return_value = noc_firewall_set_l4_sys_system_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_OSC0_TIMER:
            return_value = noc_firewall_get_l4_sys_osc0_timer(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_OSC0_TIMER:
            return_value = noc_firewall_set_l4_sys_osc0_timer(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_OSC1_TIMER:
            return_value = noc_firewall_get_l4_sys_osc1_timer(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_OSC1_TIMER:
            return_value = noc_firewall_set_l4_sys_osc1_timer(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_WATCHDOG0:
            return_value = noc_firewall_get_l4_sys_watchdog0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_WATCHDOG0:
            return_value = noc_firewall_set_l4_sys_watchdog0(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_WATCHDOG1:
            return_value = noc_firewall_get_l4_sys_watchdog1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_WATCHDOG1:
            return_value = noc_firewall_set_l4_sys_watchdog1(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_WATCHDOG2:
            return_value = noc_firewall_get_l4_sys_watchdog2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_WATCHDOG2:
            return_value = noc_firewall_set_l4_sys_watchdog2(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_WATCHDOG3:
            return_value = noc_firewall_get_l4_sys_watchdog3(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_WATCHDOG3:
            return_value = noc_firewall_set_l4_sys_watchdog3(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_DAP:
            return_value = noc_firewall_get_l4_sys_dap(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_DAP:
            return_value = noc_firewall_set_l4_sys_dap(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_WATCHDOG4:
            return_value = noc_firewall_get_l4_sys_watchdog4(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_WATCHDOG4:
            return_value = noc_firewall_set_l4_sys_watchdog4(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_POWER_MANAGER:
            return_value = noc_firewall_get_l4_sys_power_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_POWER_MANAGER:
            return_value = noc_firewall_set_l4_sys_power_manager(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB1_RXECC:
            return_value = noc_firewall_get_l4_sys_usb1_rxecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB1_RXECC:
            return_value = noc_firewall_set_l4_sys_usb1_rxecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_USB1_TXECC:
            return_value = noc_firewall_get_l4_sys_usb1_txecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_USB1_TXECC:
            return_value = noc_firewall_set_l4_sys_usb1_txecc(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_L4_NOC_PROBES:
            return_value = noc_firewall_get_l4_sys_l4_noc_probes(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_L4_NOC_PROBES:
            return_value = noc_firewall_set_l4_sys_l4_noc_probes(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_L4_NOC_QOS:
            return_value = noc_firewall_get_l4_sys_l4_noc_qos(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_L4_NOC_QOS:
            return_value = noc_firewall_set_l4_sys_l4_noc_qos(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_SOC2FPGA:
            return_value = noc_firewall_get_hps2fpga_soc2fpga(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_SOC2FPGA:
            return_value = noc_firewall_set_hps2fpga_soc2fpga(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_LWSOC2FPGA:
            return_value = noc_firewall_get_lwhps2fpga_lwsoc2fpga(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_LWSOC2FPGA:
            return_value = noc_firewall_set_lwhps2fpga_lwsoc2fpga(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_GET_TCU:
            return_value = noc_firewall_get_tcu_tcu(base_add, user_data, length);
            break;
        case IOCTL_NOC_FIREWALL_SET_TCU:
            return_value = noc_firewall_set_tcu_tcu(base_add, user_data, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
}