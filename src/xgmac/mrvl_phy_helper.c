
// For details of the MARVEL PHY see the link below:
// https://www.marvell.com/content/dam/marvell/en/public-collateral/phys-transceivers/marvell-phys-transceivers-alaska-88e151x-datasheet.pdf
// The PHY is configured and analyzed via MDIO which is accessible through the XGMAC driver
#include <mrvl_phy_helper.h>
#include <stdio.h>

/*
 * This function is simply used to wait a specific number of clock cycles
 *
 * @param  None
 *
 * @return None
 *
 */
static void mrvl_cycle_delay(uint32_t num_delay_cycles) {
    // Wait for some time
    uint32_t ii = num_delay_cycles;
    do {
        asm volatile("nop");
    } while (ii--);
}

/*
 * This function wait for marvel PHY to come out of reset
 *
 * @param  None
 *
 * @return  TRUE  == MARVELL PHY IS IN RESET
 *          FALSE == MARVELL PHY IS NOT IN RESET
 *
 */
static bool is_mrvl_phy_inrst(uint32_t base_addr) {
    uint32_t read_val = 0;
    bool ret_val = true;
    // wait for an arbitrary amount of time for PHY to reset
    // The wait time below was determined via testing
    uint32_t ii = 1000;
    do {
        read_val = (uint32_t)mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL);

        if ((read_val & (uint32_t)PHY_COPPER_SOFT_REST) == 0x00000000) {
            ret_val = false;
            ii = 0;
            break;
        }
    } while (ii--);

    if (ret_val == false) {
        printf("Reset complete\n");
    }
    return ret_val;
}

/*
 * This function verify if the previous read or write operation is complete
 *
 * @param  None
 *
 * @return  TRUE  == PREVIOUS READ OR WRITE NOT COMPLETE
 *          FALSE == PREVIOUS READ OR WRITE COMPLETE
 *
 */
static bool is_prev_rwop_cmpl(uint32_t base_addr) {
    const uint32_t mdio_sgl_sbusy_bit22 = 0x00400000;
    bool ret_val = true;
    uint32_t reg_val = 0;

    // Wait for arbitrary 600 iterations for MDIO operation to be complete
    uint32_t ii = 600;
    do {
        xgmac_ioctl(base_addr, IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));
        if ((reg_val & mdio_sgl_sbusy_bit22) == 0) {
            ret_val = false;
            ii = 0;
            break;
        }
    } while (ii--);
    return ret_val;
}

/*
 * This function configures the Phy in Loopback Mode and sets Phy to operate in 1Gbps
 *
 * @param  None
 *
 * @return        0 - SUCCESS
 *                1 - FAILURE
 *
 */
uint8_t configure_mrvl_phy88E1512(uint32_t base_addr, uint8_t port_speed) {

    uint32_t ret_val = 0;
    uint32_t read_val = 0;
    printf("Initialize Errata\n");
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0); // Page 0.
    mrvl_phy_errata(base_addr);

    mrvl_phy_read(base_addr, 1);
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, PHY_COPPER_SOFT_REST);

    // Wait for some time
    mrvl_cycle_delay(10000000);

    // Read identifier
    read_val = (uint32_t)mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0x0);
    mrvl_phy_read(base_addr, 0);
    read_val = (uint32_t)mrvl_phy_read(base_addr, 18);
    printf("phy interrupt enable Value 0x%x\n", read_val);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0x0);
    read_val = (uint32_t)mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_IDEN1);
    if (read_val == MARVELL_88E1512_PHY_IDEN1_VALUE) {
        printf("Correct Phy IDENT1 Value 0x%x\n", read_val);

        read_val = (uint32_t)mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_IDEN2);
        if (read_val == MARVELL_88E1512_PHY_IDEN2_VALUE) {
            printf("Correct Phy IDENT2 Value 0x%x\n", read_val);
        } else {

            // Incorrect phy2 ID value
            printf("Invalid phy2 value\n");
            ret_val = 1;
        }
    } else {
        // incorrect phy1 ident value
        printf("Invalid phy1 value\n");
        ret_val = 1;
    }

    // Set Mode Register (Register 20 Page 18) (2:0 -> 000 RGMII(System mode) to Copper)
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 18); // Page 18.
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_MODE, 0x0);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0x0);
    mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL);
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, 0x3036 | PHY_COPPER_FULL_DUPLEX);

    // Select Page 2
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 2);
    mrvl_phy_write(base_addr, MARVELL_88E1512_MAC_CTRL_REG2, 0x2030);

    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0); // Select Page 0
    read_val = mrvl_phy_read(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL);

    // Perform Software Reset
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val | PHY_COPPER_SOFT_REST);

    // Wait for PHY to come out of reset
    is_mrvl_phy_inrst(base_addr);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 2);
    mrvl_phy_read(base_addr, 21);

    // select page 1
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 1);
    read_val = (uint32_t)mrvl_phy_read(base_addr, 0);

    // Enable set bit 13 and reset
    read_val |= (0xc000);
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);

    // Wait for PHY to come out of reset
    is_mrvl_phy_inrst(base_addr);

    // Enable fiber loopback & reset fiber
    read_val |= (PHY_COPPER_EN_INTR_LOOPBACK);
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);
    mrvl_phy_read(base_addr, 0);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0);
    read_val = (uint32_t)mrvl_phy_read(base_addr, 0);

    // ORR in bit 13 and reset
    read_val |= 0xA000;
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);

    // Wait for PHY to come out of reset
    is_mrvl_phy_inrst(base_addr);

    // Execute copper software reset
    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0);

    read_val = (uint32_t)mrvl_phy_read(base_addr, 0);
    read_val |= 0x8000;
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);

    // Wait for PHY to come out of reset
    is_mrvl_phy_inrst(base_addr);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 0);
    mrvl_phy_read(base_addr, 0);

    // enable loopback and reset copper
    read_val |= PHY_COPPER_EN_INTR_LOOPBACK;
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);

    // select page 0
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_PAGE, 1);
    mrvl_phy_read(base_addr, 0);

    // enable loopback and reset copper
    read_val |= PHY_COPPER_EN_INTR_LOOPBACK;
    mrvl_phy_write(base_addr, MARVELL_88E1512_PHY_COPPER_CTRL, read_val);
    return ret_val;
}

/*
 * If EEE is intended to be used, the following register writes must be done once after every hardware reset.
 * EEE - Energy Efficient Ethernet
 *
 * @param base_address  "value from open method"
 * @return non
 */
void mrvl_phy_errata(uint32_t base_addr) {
    mrvl_phy_write(base_addr, 0x22, 0x00FF);
    mrvl_phy_write(base_addr, 17, 0x214B);
    mrvl_phy_write(base_addr, 16, 0x2144);
    mrvl_phy_write(base_addr, 17, 0x0C28);
    mrvl_phy_write(base_addr, 16, 0x2146);
    mrvl_phy_write(base_addr, 17, 0xB233);
    mrvl_phy_write(base_addr, 16, 0x214D);
    mrvl_phy_write(base_addr, 17, 0xCC0C);
    mrvl_phy_write(base_addr, 16, 0x2159);
    mrvl_phy_write(base_addr, 22, 0x00FB);
    mrvl_phy_write(base_addr, 7, 0xC00D);
    mrvl_phy_write(base_addr, 22, 0x0000);
}

/*
 * This method is used to write to a register for the marvell phy
 *
 * @param base_address  "value from open method"
 *        phy_reg       "register to be read"
 * @return register value
 */
uint16_t mrvl_phy_read(uint32_t base_address, uint8_t phy_reg) {

    uint32_t reg_val = 0;

    // Wait for MDIO TO BE unbusy
    is_prev_rwop_cmpl(base_address);

    // Write phy address + offset to command addr "offset 0x200" IOCTL_XGMAC_GET_MDIO_SGL_CMD_ADDR
    reg_val = phy_reg;
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_SGL_CMD_ADDR, (uintptr_t)&reg_val, sizeof(reg_val));

    // Write value to data addr
    xgmac_ioctl(base_address, IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));
    reg_val = (1 << 22) | (0 << 19) | (3 << 16);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));

    // Wait for MDIO TO BE unbusy
    is_prev_rwop_cmpl(base_address);

    // read ctrl data addr
    xgmac_ioctl(base_address, IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));

    // Delay a number of instruction cycles
    mrvl_cycle_delay(100000);

    return (uint16_t)(reg_val & 0xFFFF);
}

/*
 * This method is used to write to a register for the marvell phy
 *
 * @param base_address  "value from open method"
 *        phy_reg       "register to be written"
 *        value         " value to be written"
 * @return none
 */
void mrvl_phy_write(uint32_t base_address, uint8_t phy_reg, uint16_t value) {

    uint32_t reg_val = 0;
    // Enable MDC
    //  get control data IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA
    xgmac_ioctl(base_address, IOCTL_XGMAC_GET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));

    // make sure bit 31 is set and bits 21-19 are clear
    reg_val = (1 << 31); // TODO Swane verify change doesn't affect anything | (0 << 19);
    reg_val &= 0xFFC7FFFF;
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));

    // Wait for MDIO TO BE unbusy
    is_prev_rwop_cmpl(base_address);

    // Write 0xffffffff TO CLAUSE 22 PORT ADDR
    reg_val = 0xffffffff;
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_CLS22_PORT, (uintptr_t)&reg_val, sizeof(reg_val));

    // Wait for MDIO TO BE unbusy
    is_prev_rwop_cmpl(base_address);

    // Write phy address + offset to command addr "offset 0x200" IOCTL_XGMAC_GET_MDIO_SGL_CMD_ADDR
    reg_val = phy_reg;
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_SGL_CMD_ADDR, (uintptr_t)&reg_val, sizeof(reg_val));

    // Write value to data addr
    reg_val = (value & 0xffff) | (1 << 22) | (0 << 19) | (1 << 16);
    xgmac_ioctl(base_address, IOCTL_XGMAC_SET_MDIO_SGL_CMD_DATA, (uintptr_t)&reg_val, sizeof(reg_val));

    // This delay is necessary for the write to actually complete
    // Delay a number of instruction cycles
    mrvl_cycle_delay(300);
}

// END OF FILE
