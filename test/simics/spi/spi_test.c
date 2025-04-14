#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "spi.h"
#include <stdio.h>
#include <string.h>

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
// clang-format on
#define DEBUG2_SPIM0_SSN1_OFST 0
#define DEBUG2_SPIM0_CLK_OFST 4
#define DEBUG2_SPIM0_MOSI_OFST 5
#define DEBUG2_SPIM0_MISO_OFST 6
#define DEBUG2_SPIM0_SSN_OFST 7

#define DEBUG2_SPIM0_PINMUX_VALUE 0x00000007
#define DEBUG2_SPIM0_PINMUX_IOCTRL 0x00000212
#endif

#define SPI_EEPROM_WEL_CMD 0x06
#define SPI_EEPROM_RSTS_CMD 0x05
#define SPI_EEPROM_READ_CMD 0x03
#define SPI_EEPROM_WRITE_CMD 0x02
#define SPI_EEPROM_ST_WRITE_CMD 0x01
#define SPI_EEPROM_LOW_ADDR 0xD0
#define SPI_EEPROM_HIGH_ADDR 0x00
#define SPI_EEPROM_WORD_VAL_S 0xC2
#define SPI_EEPROM_WORD_VAl_F 0xFF
#define SPI_EEPROM_TX_EMPTY 0x04
#define SPI_EEPROM_TX_BUSY 0x01
#define SPI_EEPROM_STS_WRITE_WORD 0x80
#define SPI_EEPROM_STS_REG_VAL 0x02

// Global variables
int32_t spi_handle = -1;

// Wait for the TX buffer to be empty
static bool is_tx_buf_empty(void) {
    // 5000 is a number found to consistenly give adequate amount of time for data to be received
    uint32_t temp_param = 5000;
    uint32_t temp_data = 0;
    bool ret_val = false;
    do {
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_STATUS, (uintptr_t)(&temp_data), sizeof(uint32_t));
        if (temp_data & SPI_EEPROM_TX_EMPTY) {
            ret_val = true;
            break;
        }
    } while (temp_param--);

    if (ret_val == true) {
        printf("Transmit FIFO is completely empty now\n");
    }
    return ret_val;
}

// Check if SPI busy
static void is_spi_busy(void) {
    uint64_t temp_param = 1;
    while ((temp_param & SPI_EEPROM_TX_BUSY) > 0) {
        spi_ioctl(spi_handle, IOCTL_SPI_GET_STATUS, (const uintptr_t)(&temp_param), sizeof(uint64_t));
        printf("Spi is busy current [status] SR = 0x%lx\n", temp_param);
    }
}

// Get Data from Read Buffer
static void read_spi_fifo(uint8_t *data_buf, uint32_t data_count) {
    if (data_buf != NULL) {
        for (uint32_t ii = 0; ii < data_count; ii++) {
            spi_read(spi_handle, (const uintptr_t)(data_buf), 1);
            printf("Address Read byte offset %d data=0x%x\n", ii, *data_buf);
        }
    }
}

// Entrance
int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char spi_initiator[] = "/dev/spim0";
    int32_t return_value = -1;
#ifdef FSBL_EXECUTION

    // Initiate configuration
    fsbl_configuration();

    // Update pinmux for SPI debug2
    // Used to view handoff area elements for pinmux
    fsbl_handoff_t *reverse_handoff_ptr = (fsbl_handoff_t *)handoff_array;

    pinmux_default_cfg_t *ptr_sel = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_sel_array[0];
    pinmux_default_cfg_t *ptr_io_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_io_array[0];
    pinmux_default_cfg_t *ptr_fpga_array = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_fpga_array[0];
    pinmux_default_cfg_t *ptr_io_delay = (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_iodelay_array[0];

    // Just to get over the "hump" of unused variable
    (void)*ptr_io_delay;
    (void)*ptr_fpga_array;

    // Update Selection Array to be SPIM0
    ptr_sel[DEBUG2_SPIM0_SSN1_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_VALUE;
    ptr_sel[DEBUG2_SPIM0_CLK_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_VALUE;
    ptr_sel[DEBUG2_SPIM0_MOSI_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_VALUE;
    ptr_sel[DEBUG2_SPIM0_MISO_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_VALUE;
    ptr_sel[DEBUG2_SPIM0_SSN_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_VALUE;

    // Update IO control Array appropriately for Each SPI ARe
    ptr_io_array[DEBUG2_SPIM0_SSN1_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_IOCTRL;
    ptr_io_array[DEBUG2_SPIM0_CLK_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_IOCTRL;
    ptr_io_array[DEBUG2_SPIM0_MOSI_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_IOCTRL;
    ptr_io_array[DEBUG2_SPIM0_MISO_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_IOCTRL;
    ptr_io_array[DEBUG2_SPIM0_SSN_OFST].pinmux_value = DEBUG2_SPIM0_PINMUX_IOCTRL;

    // Update pinmux selection and io control
    pinmux_handoff_config(UPDATE_SEL_ARRAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_sel_array[0]);
    pinmux_handoff_config(UPDATE_CTRL_ARRAY, (pinmux_default_cfg_t *)&reverse_handoff_ptr->pinmux_io_array[0]);

#ifdef SPI_HW_TEST_DEBUG
    printf("Header magic 0x%x\n", reverse_handoff_ptr->header_magic);
    for (uint32_t ii = 0; ii < 48; ii++) {
        printf(" ii=0x%x Selection array 0x%x\n", ii, ptr_sel[ii].pinmux_value);
        printf(" ii=0x%x IO Array 0x%x\n", ii, ptr_io_array[ii].pinmux_value);
        if (ii < 20) {
            printf(" ii=0x%x FPGA Array 0x%x\n", ii, ptr_fpga_array[ii].pinmux_value);
        }
        printf(" ii=0x%x IO Delay 0x%x\n", ii, ptr_io_delay[ii].pinmux_value);
    }
#endif
#endif

    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    if (rstmgr_handle < 0) {
        return rstmgr_handle;
    }
    hps_rstmgr_regs_t regs_buffer;

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                 sizeof(hps_rstmgr_regs_t));
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                 sizeof(hps_rstmgr_regs_t));

    // Enable all SPI devices "SPIS(0/1) [bit19 & bit20] SPIM(0/1) [bit17 & bit18]
    regs_buffer.per0modrst &= ~((uint32_t)0x001E0000);

    // Enable UART(TX/RX)
    regs_buffer.per1modrst &= ~((uint32_t)0x00030000);

    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                 sizeof(hps_rstmgr_regs_t));
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                 sizeof(hps_rstmgr_regs_t));

    // Open SPIM0
    spi_handle = spi_open(spi_initiator, 0);
    if (spi_handle < 0) {
        return_value = spi_handle;
        printf("spi0 failed open\n");
    } else {
        uint64_t param = 0;
        uint32_t read_data = 0;

        printf("spi0 Test Start\n");

        // Set baud divisor to 100 "Fsclk_out = Fssi_clk/100"
        param = 100;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_BAUD_RATE, (uintptr_t)(&param), sizeof(uint32_t));

        // Set number of data frames to 3
        param = 3;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_NUM_DATA_FRAMES, (uintptr_t)(&param), sizeof(uint32_t));

        // Set TXFLTR and RXFLTR to 1 byte
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_TX_FIFO_THRESHOLD, (uintptr_t)(&param), sizeof(uint32_t));
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_RX_FIFO_THRESHOLD, (uintptr_t)(&param), sizeof(uint32_t));

        // Set Slave enable to 0
        param = 0;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_CS, (uintptr_t)(&param), sizeof(uint32_t));

        // Set frame format to SSP Texas Instrument
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_FRAME_FORMAT, (uintptr_t)(&param), sizeof(uint32_t));
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_FRAME_FORMAT, (uintptr_t)(&param), sizeof(uint32_t));

        // Set frame size to 8 bit serial data transfer
        param = 7;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_FRAME_SIZE, (uintptr_t)(&param), sizeof(uint32_t));
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_FRAME_SIZE, (uintptr_t)(&param), sizeof(uint32_t));

        // Set clock polarity to inactive when low
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_CLOCK_POLARITY, (uintptr_t)(&param), sizeof(uint32_t));

        // Set clock phase to trigger on start of first bit
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_CLOCK_PHASE, (uintptr_t)(&param), sizeof(uint32_t));

        // Set transfer mode to EEPROM
        param = 3;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_TRANSFER_MODE, (uintptr_t)(&param), sizeof(uint32_t));

        // Enable SPI
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_SSI_ENABLE, (uintptr_t)(&param), sizeof(uint32_t));

        // Currently the only board that has the ability to test this is the debug2 dev kit
        // There is only one debug2 dev kit available to us and its currently not available for us to
        // use as of now. This test should be preserved for when there is an available debug2 devkit for the
        // BM team
        // SPI Flash write enable
        // Prepare to send data to device
        param = 1;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_SET_CS, (uintptr_t)(&param), sizeof(uint32_t));

        // Send SPI read status command
        param = SPI_EEPROM_RSTS_CMD;
        spi_write(spi_handle, (const uintptr_t)(&param), 1);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Read Status cmd sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Verify status register before enabling write latch
        if (read_data == 0) {
            printf("Initial Status register is as expected value=%x\n", read_data);
        } else {
            printf("Initial Status register is NOT as expected value=%x\n", read_data);
            return_value = -2;
        }

        // Send the Write Enable Command
        param = SPI_EEPROM_WEL_CMD;
        spi_write(spi_handle, (const uintptr_t)(&param), 1);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("Write enable cmd sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Send SPI read status command
        param = SPI_EEPROM_RSTS_CMD;
        spi_write(spi_handle, (const uintptr_t)(&param), 1);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Read Status cmd sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Verify status register after enabling write latch
        if (read_data == SPI_EEPROM_STS_REG_VAL) {
            printf("Initial Status register is as expected value=%x\n", read_data);
        } else {
            printf("Initial Status register is NOT as expected value=%x\n", read_data);
            return_value = -2;
        }
#ifdef SPI_WRITE_VERIFICATION
        /************************** START OF EEPROM WRITE VERIFICATION TEST
         * **************************************************************/
        // SPI Read 4 bytes -- Should be all 0 in the Simics model
        param = SPI_EEPROM_READ_CMD | (SPI_EEPROM_LOW_ADDR << 8) | (SPI_EEPROM_HIGH_ADDR << 16);
        spi_write(spi_handle, (const uintptr_t)(&param), 3);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Read address cmd sent\n");
        }

        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Write update Status Word
        param = SPI_EEPROM_ST_WRITE_CMD | (SPI_EEPROM_STS_WRITE_WORD << 8);
        spi_write(spi_handle, (const uintptr_t)(&param), 2);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Read address cmd sent\n");
        }

        // Program Sector
        param = SPI_EEPROM_WRITE_CMD | (SPI_EEPROM_LOW_ADDR << 8) | (SPI_EEPROM_HIGH_ADDR << 16) |
                (SPI_EEPROM_WORD_VAL_S << 24);
        spi_write(spi_handle, (const uintptr_t)(&param), sizeof(uint32_t));

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM write start address value cmd sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        // Read all bytes in FIFO
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Read bytes after programming
        // SPI Read 4 bytes -- Should be all 0 in the Simics model
        param = SPI_EEPROM_READ_CMD | (SPI_EEPROM_LOW_ADDR << 8) | (SPI_EEPROM_HIGH_ADDR << 16);
        spi_write(spi_handle, (const uintptr_t)(&param), 3);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Initial read cmd sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        // Read first byte
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)1);

        // Read remaining bytes
        read_spi_fifo((uint8_t *)&param, (uint32_t)param - 1);

        if ((uint8_t)read_data == (uint8_t)SPI_EEPROM_WORD_VAL_S) {
            printf("Successful write of first byte to eeprom\n");
        } else {
            printf("failure to write first byte to eeprom\n");
            return_value = -2;
        }

        // Re-enable Write enable command "Seems this is needed after writing to EEPROM memory
        param = SPI_EEPROM_WEL_CMD;
        spi_write(spi_handle, (const uintptr_t)(&param), 1);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Write Enable command sent\n");
        }

        // Get current RX FIFO data count & read the offset
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // Write FF to memory
        param = SPI_EEPROM_WRITE_CMD | (SPI_EEPROM_LOW_ADDR << 8) | (SPI_EEPROM_HIGH_ADDR << 16) |
                (SPI_EEPROM_WORD_VAl_F << 24);
        spi_write(spi_handle, (const uintptr_t)(&param), sizeof(uint32_t));

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM final write value command sent\n");
        }

        // Get current bytes to read & print them all
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)param);

        // SPI Read 4 bytes
        param = SPI_EEPROM_READ_CMD | (SPI_EEPROM_LOW_ADDR << 8) | (SPI_EEPROM_HIGH_ADDR << 16);
        spi_write(spi_handle, (const uintptr_t)(&param), 3);

        // Wait for SPI operation to complete
        is_spi_busy();

        // Wait for command to be sent
        if (is_tx_buf_empty() == true) {
            printf("EEPROM Final read of address sent\n");
        }

        // Get the receive FIFO level
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_RX_FIFO_LEVEL, (uintptr_t)(&param), sizeof(uint32_t));

        // Read first byte from FIFO
        read_spi_fifo((uint8_t *)&read_data, (uint32_t)1);

        // Get current RX FIFO data count & read the offset "Read remaining bytes of FIFO"
        read_spi_fifo((uint8_t *)&param, (uint32_t)param - 1);

        // Check if data is as expected
        if (((uint8_t)(read_data) == (uint8_t)SPI_EEPROM_WORD_VAl_F) && (return_value != -2)) {
            return_value = 0;
            printf("spi Passed write test\n");
        } else {
            if (return_value == -1) {
                printf("spi test miscompare\n");
                printf("Expected: 0xFF\n");
                char s[1024];
                sprintf(s, "Observed: %#x", read_data);
                puts(s);
            } else {
                printf("Failure is due to unsuccessful write of 0x%x to EEPROM\n", SPI_EEPROM_WORD_VAL_S);
            }
        }
        /************************** END OF EEPROM WRITE VERIFICATION TEST
         * **************************************************************/
#endif

        // Retrieve SPI IDR & SSI_VERSION_ID
        param = 0;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_ID, (uintptr_t)(&param), sizeof(uint32_t));

        // Verify SPI IDR
        if (param == SPI_IDR) {
            printf("SPI IDR version matches 0x%x\n", SPI_IDR);
        } else {
            printf("SPI IDR version does not match 0x%x\n", SPI_IDR);
            return_value = -2;
        }

        // Retrieve SSI_VERSION_ID
        param = 0;
        spi_ioctl(spi_handle, (int32_t)IOCTL_SPI_GET_VERSION, (uintptr_t)(&param), sizeof(uint32_t));

        // Verify SSI_VERSION_ID
        if (param == SPI_SSI_VERSION_ID) {
            printf("SPI SSI version ID matches 0x%x\n", SPI_SSI_VERSION_ID);
        } else {
            printf("SPI SSI version ID does NOT match 0x%x\n", SPI_SSI_VERSION_ID);
            return_value = -2;
        }

        // If return value is still equal to -1 no errors have occured so return success
        if (return_value == -1) {
            return_value = 0;
        }
        spi_close(spi_handle);
    }
    return return_value;
}
