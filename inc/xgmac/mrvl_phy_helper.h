#ifndef MARVELL_PHY_HELPER__
#define MARVELL_PHY_HELPER__

// For details of the MARVEL PHY see the link below:
// https://www.marvell.com/content/dam/marvell/en/public-collateral/phys-transceivers/marvell-phys-transceivers-alaska-88e151x-datasheet.pdf

// XGMAC Specific header
#include "xgmac.h"
#include "xgmac_internal.h"
#include "xgmac_regs.h"

#define PHY_COPPER_SOFT_REST 0x00008000
#define PHY_COPPER_EN_INTR_LOOPBACK 0x00004000 // Enable Phy internal Loopback.
#define PHY_COPPER_FULL_DUPLEX 0x00000100      // Enable Full duplex mode.
#define MARVELL_88E1512_PHY_COPPER_CTRL 0x00000000
#define MARVELL_88E1512_PHY_COPPER_STATUS 0x00000001
#define MARVELL_88E1512_PHY_PAGE 22
#define MARVELL_88E1512_PHY_IDEN1 2
#define MARVELL_88E1512_PHY_IDEN1_VALUE 0x00000141
#define MARVELL_88E1512_PHY_IDEN2 3
#define MARVELL_88E1512_PHY_IDEN2_VALUE 0x00000DD1
#define MARVELL_88E1512_PHY_MODE 20
#define MARVELL_88E1512_MAC_CTRL_REG2 21

/*
 * This function configures the Phy in Loopback Mode and sets Phy to operate in 1Gbps
 *
 * @param  None
 *
 * @return        0 - SUCCESS
 *                1 - FAILURE
 *
 */
uint8_t configure_mrvl_phy88E1512(uint32_t base_addr, uint8_t port_speed);

/* If EEE is intended to be used, the following register writes must be done once after every hardware reset.
 * EEE - Energy Efficient Ethernet
 */
void mrvl_phy_errata(uint32_t base_addr);

/*
 * This method is used to write to a register for the marvell phy
 *
 * @param base_address  "value from open method"
 *        phy_reg       "register to be written"
 *        value         " value to be written"
 * @return none
 */
void mrvl_phy_write(uint32_t base_address, uint8_t phy_reg, uint16_t value);

/*
 * This method is used to write to a register for the marvell phy
 *
 * @param base_address  "value from open method"
 *        phy_reg       "register to be read"
 * @return register value
 */
uint16_t mrvl_phy_read(uint32_t base_address, uint8_t phy_reg);

#endif // MARVELL_PHY_HELPER__
