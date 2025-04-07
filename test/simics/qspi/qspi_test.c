#include "qspi.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"

#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"

#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

#include <stdio.h>
#include <string.h>

// QSPI CONTROLLER DEFINES
#define FLASH_CMD_IS_EXEC 0x00000002
#define FLASH_ERASED_VALUE 0xFFFFFFFFFFFFFFFF

/* Currently reading the device id will return gigadevice id
 * There is a noted issue around what gets returned for the device id
 * "https://www.basicinputoutput.com/2023/11/jedec-manufacturer-ids-are-mess.html"
 * We'll use this as verification that QSPI flash is being read as desired for now
 * This may need to be analyzed later.
 */
#define GIGADEVICE_ID 0xC8

#ifdef FSBL_EXECUTION
// QSPI MAILBOX COMMANDS
#define QSPI_OPEN 0x32
#define QSPI_CLOSE 0x33
#define QSPI_DIRECT 0x3B

// MBOX tracking variables
static uint32_t current_rin_value = 0;
// Mailbox QSPI command helper
static bool mbox_qspi_command_exec(int32_t mbox_handle, uint32_t cmd, uint32_t chid, uint32_t *ptr_extra_params) {

    // notifier of commands success
    // Do not set this to true until a proper response has been given
    // This should be the last thing done
    bool is_cmd_successful = false;

    // mailbox register handle
    hps_mailbox_reg_msg_t cin_buff;

    // Used to pass address
    uintptr_t addr_ptr = 0;

    // used for mbox response
    hps_mailbox_reg_msg_t *ptr_mbox_response = NULL;

    // command additional response words "number of words outside of header response"
    uint32_t response_words = 0;

    // Mailbox input/output param
    uint32_t hps_mbox_param = 0;
    // All commands are from the HPS perspective
    cin_buff.hps_mbox_nrm_bhdr.hps_mbox_ch_cl = HPS_CLIENT_CHANNEL;

    // Set Channel ID
    cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cmd_id = chid;

    // Set indirect message indicator to false.
    // The commands currently covered cannot have indirect settings "OPEN,CLOSE,DIRECT"
    cin_buff.hps_mbox_nrm_bhdr.hps_mbox_ind = 0;

    // populate command specific parameters for input buffer command
    switch (cmd) {
    case QSPI_OPEN:
        // Set command paramters for getting command
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cer_cd = QSPI_OPEN;

        // Set length to 0
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size = 0;

        // Set CheckSum Present to False
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cksm = 0;

        // number of words in responses
        response_words = 1;
        break;

    case QSPI_DIRECT:
        // Set command paramters for getting command
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cer_cd = QSPI_DIRECT;

        // Set length There is an additional paramater for DIRECT
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size = 1;

        // Set CheckSum Present to False
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cksm = 0;

        // number of words in responses
        response_words = 2;
        break;

    case QSPI_CLOSE:
        // Set command paramters for getting command
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cer_cd = QSPI_CLOSE;

        // Set length to 0
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size = 0;

        // Set CheckSum Present to False
        cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cksm = 0;

        // number of words in responses
        response_words = 1;
        break;

    default:
        printf("command not accomodated\n");
    }

    // Write Header word to the command buffer & Increment CIN Buffer Address
    addr_ptr = (uintptr_t)&cin_buff;
    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, addr_ptr, sizeof(uint32_t));
    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));

    // If there are additional parameters outside of the header but extra params ptr is invalid return false
    if ((cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size != 0) && (ptr_extra_params == NULL)) {
        printf("Additional parameters not set invalid hps_mbox size or ptr_extra_params\n");
        return false;
    }

    // If there are any additional parameters add them
    for (uint32_t ii = 0; ii < cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size; ii++) {
        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, ptr_extra_params[ii], sizeof(uint32_t));
        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));
    }
    // Set DBELL to SDM flag
    hps_mbox_param = 1;
    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOSDM, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));

    // Wait 400 iterations for SDM to answer DOORBELL
    uint32_t doorbell_wait_iteration = 400;
    do {
        // Get doorbell to HPS
        hps_mbox_param = 0;
        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_HPS_DBELL, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));
        if (hps_mbox_param != 0) {
            // Clear doorbell to HPS
            hps_mbox_param = 0;
            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOHPS, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));

            printf("Doorbell answered\n");

            // We've reached our end lets break out
            break;
        }
    } while (doorbell_wait_iteration--);

    // Get RIN offset cur_rin_value
    bool the_first_response_word = true;
    while (response_words != 0) {
        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));
        if (hps_mbox_param != current_rin_value) {
            // Set current RIN value
            current_rin_value = hps_mbox_param;

            // Get value from Response Buffer
            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));

            // Increment the ROUT address "hps_param will not be changed by increment ROUT" FYI hps_mbox_param is not
            // changed here
            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_mbox_param, sizeof(uint32_t));

            if (the_first_response_word == true) {
                // Point to header
                addr_ptr = (uintptr_t)&hps_mbox_param;
                ptr_mbox_response = (hps_mailbox_reg_msg_t *)addr_ptr;
                // This is the header
                // Check Status of the response
                if (ptr_mbox_response->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                    printf("QSPI command successful ID=%d\n", cmd);
                    printf("QSPI client ID = 0x%x\n", ptr_mbox_response->hps_mbox_nrm_bhdr.hps_mbox_ch_cl);

                    // Note command as succesfull
                    is_cmd_successful = true;
                } else {
                    printf("QSPI client ID = 0x%x\n", ptr_mbox_response->hps_mbox_nrm_bhdr.hps_mbox_ch_cl);
                    printf("QSPI error = 0x%x\n", ptr_mbox_response->hps_mbox_nrm_bhdr.hps_mbox_cer_cd);
                    printf("failed to COMMAND ID=%d\n", cmd);
                    is_cmd_successful = false;
                    break;
                }
                the_first_response_word = false;
            } else {

                printf("Additional response parameters 0x%x\n", hps_mbox_param);
            }
        }
        // Decrement response words
        response_words -= 1;
    }

    return is_cmd_successful;
}

#endif

// Wait for QSPI command to be executed
static bool is_qspi_command_complete(int32_t qspi_handle, uint32_t cmd) {

    bool is_cmd_complete = false;
    const uint32_t wait_time = 600000;
    // parameter for qspi ioctl
    uint64_t param = 1;

    uint32_t qspi_cmd_done_wait = wait_time;
    while (param != 0) {

        // Get flash command register
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_GET, (uintptr_t)(&param), sizeof(uint64_t));

        if (--qspi_cmd_done_wait == 0) {
            break;
        }

        // Is command complete
        if ((param & FLASH_CMD_IS_EXEC) == 0) {
            printf("command 0x%x completed successfully\n", cmd);
            is_cmd_complete = true;
            break;
        }
    }
    printf("command was executed in %d iterations && current flashcmd register is 0x%lx\n",
           wait_time - qspi_cmd_done_wait, param);

    return is_cmd_complete;
}

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";
    const char qspi_initiator[] = "/dev/qspi0";
    uint64_t temp_buffer = 0;
#ifdef FSBL_EXECUTION

    const char mbox_initiator[] = "/dev/hps_mailbox";

    // Configure pinmux for boot up to access UART for debugging
    fsbl_configuration();
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
    regs_buffer.per0modrst &= ~((uint32_t)0x00070000);
    regs_buffer.per1modrst &= ~((uint32_t)0x00010000);
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                 sizeof(hps_rstmgr_regs_t));
    rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                 sizeof(hps_rstmgr_regs_t));

    // This value will be decremented along the way if QSPI and MBOX are successful
    int32_t return_value = 2;
    printf("qspi Test Start\n");
#ifdef FSBL_EXECUTION
    int32_t mbox_handle = hps_mbox_open(mbox_initiator, 0);
#endif

    int32_t qspi_handle = qspi_open(qspi_initiator, 0);
    printf("qspi handle 0x%x\n", qspi_handle);
    if (qspi_handle < 0) {
        return_value = qspi_handle;
        printf("qspi failed open\n");
#ifdef FSBL_EXECUTION
    } else if (mbox_handle < 0) {
        return_value = qspi_handle;
        printf("mailbox failed open\n");
#endif
    } else {
        uint32_t param = 0;
#ifdef FSBL_EXECUTION

        // SET COE interrupt enable
        param = 1;
        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_COE_FLAG, (uintptr_t)&param, sizeof(uint32_t));

        // SEND QSPI CLOSE
        // This is expected to fail but just in case lets try to close QSPI
        if (mbox_qspi_command_exec(mbox_handle, QSPI_CLOSE, 1, NULL) == true) {
            printf("Attempt to close QSPI finish\n");
        }

        // SEND QSPI OPEN
        // Set command paramters for getting command
        if (mbox_qspi_command_exec(mbox_handle, QSPI_OPEN, 1, NULL) == true) {
            printf("Attempt to open QSPI success\n");
        } else {
            printf("Failed to open QSPI\n");
            goto prog_cleanup;
        }

        // Send QSPI DIRECT
        // Set command paramters
        param = 1;
        if (mbox_qspi_command_exec(mbox_handle, QSPI_DIRECT, 1, (uint32_t *)&param) == true) {
            printf("Attempt to send QSPI DIRECT success\n");
        } else {
            printf("Failed to set QSPI direct\n");
            goto prog_cleanup;
        }
#endif
        // Set default chip select lines B13 - B10 = 1110
        // Set B7 enable direct access controller
        param = 0x00003880;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Set size of SRAMPART to 64 SRAM locations
        param = 0x40;
        if (qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_INDIRECT_ADDR_SPAN_SET, (uintptr_t)(&param),
                       sizeof(uint32_t)) != 0) {
            printf("failed add span set\n");
        }

        // Set baud divisor to BAUD12 "This could vary if needed"
        param = 0x05;
        if (qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_BAUD_RATE_DIV_SET, (uintptr_t)(&param), sizeof(uint32_t)) !=
            0) {
            printf("failed baud rate set\n");
        }

        // * Set initial clock delay to 4 cycles B0-B7
        // * Set dealy for "after" Delay in master reference clocks between last bit
        //   of current transaction and deasserting the device chip select (n_ss_out) to 4 cycles B8-B15
        // * Set delays between activation and deactivation of chip select to 50 cycles B16-B23
        // * Set delays between delays between master mode de-assertion of outputs between transactions TO 50 CYCLES
        // B24-B31
        param = 0x32320404;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CS_DELAYS_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // set number of address bytes to 0x3 = "4 address bytes" B0-B3
        param = 0x00000003;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_DEVICE_SIZE_PARAMS_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Enable QSPI
        param = 1;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_CFG_ENABLE_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // SPI Flash set write enable latch (WEL)
        // Send command to enable writes "0x06" B24-B31
        // Execute command via B0
        param = 0x06000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // Enable 4-byte addressing
        // Send command to enable writes "0xB7" B24-B31
        // Execute command via B0
        param = 0xB7000001;
        if (qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t)) != 0) {
            printf("failed flash cmd set\n");
        }

        // Send command to read Device ID  "0xAF" B24-B31
        // Note there are 4 address bytes to be written back to flash cmd data "0x7" B20-B22
        // Notify that the command requires read back bytes "0x1" B23
        // Execute command via B0
        param = 0x9FF00001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // SPI Read 8 bytes
        temp_buffer = 0;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_READ_DATA_GET, (uintptr_t)(&temp_buffer),
                   sizeof(uint64_t));

        if ((uint8_t)GIGADEVICE_ID == (uint8_t)temp_buffer) {
            printf("Correct Device ID 0x%x\n", (uint8_t)temp_buffer);
            return_value = 0;
        }

#ifdef QSPI_ERASE_VERIFICATION
        // SPI Program 4 bytes to 0xD00000
        // write address to be programmed to flash command address
        param = (0xD0 << 16) | (0x00 << 8) | (0x00 << 0);
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Send command to program 0xD00000  "0x34" B24-B31
        // Note there are 4 address bytes to be written back to flash cmd data "0x3" B20-B22 TODO maybe change this to 8
        // bytes Notify that the command requires read back bytes "0x1" B23 Note there are 4 address bytes "0x3" B16-B17
        // Notify that the command requires address bytes "0x1" B19
        // Execute command via B0
        param = 0x34FB0001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // SPI Read 4 bytes
        // Set the flash command address to 0xD00000
        param = (0xD0 << 16) | (0x00 << 8) | (0x00 << 0);
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Send command to read 0xD00000  "0x0C" B24-B31
        // Note there are 8 address bytes to be written back to flash cmd data "0x7" B20-B22
        // Notify that the command requires read back bytes "0x1" B23
        // Note there are 4 address bytes "0x3" B16-B17
        // Notify that the command requires address bytes "0x1" B19
        // Execute command via B0
        param = 0x0CFB0001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // SPI Read 8 bytes
        temp_buffer = 0;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_READ_DATA_GET, (uintptr_t)(&temp_buffer),
                   sizeof(uint64_t));

        // Check if current address is currently not erased
        if (temp_buffer != FLASH_ERASED_VALUE) {
            printf("Flash address currently not erased value=0x%lx\n", temp_buffer);
            return_value--;
        }

        // SPI Flash set write enable latch (WEL)
        // Send command to enable writes "0x06" B24-B31
        // Execute command via B0
        param = 0x06000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // Erase the 0D sector
        param = (0xD0 << 16) | (0x00 << 8) | (0x00 << 0);
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_ADDR_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Send command to erase 0xD00000  "0x20" B24-B31
        // Note there are 4 address bytes to be written back to flash cmd data "0x3" B20-B22
        // Notify that the command requires read back bytes "0x1" B23
        // Execute command via B0
        param = 0x200B0001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // Disable WEL
        // Send command to disable write "0x04" B24-B31
        // Notify that the command requires read back bytes "0x1" B23
        // Execute command via B0
        param = 0x04000001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // SPI Read 4 bytes
        param = (0xD0 << 16) | (0x00 << 8) | (0x00 << 0);
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_ADDR_SET, (uintptr_t)(&param), sizeof(uint32_t));

        // Send command to read 0xD00000  "0x0C" B24-B31
        // Note there are 8 address bytes to be written back to flash cmd data "0x7" B20-B22
        // Notify that the command requires read back bytes "0x1" B23
        // Note there are 4 address bytes "0x3" B16-B17
        // Notify that the command requires address bytes "0x1" B19
        // Execute command via B0
        param = 0x0CFB0001;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_SET, (uintptr_t)(&param), sizeof(uint64_t));

        // Wait for command to complete
        is_qspi_command_complete(qspi_handle, (uint32_t)((param & 0xFF000000) >> 24));

        // Get 8-bytes from flash command read data
        temp_buffer = 0;
        qspi_ioctl(qspi_handle, (int32_t)IOCTL_QSPI_FLASH_CMD_READ_DATA_GET, (uintptr_t)(&temp_buffer),
                   sizeof(uint64_t));

        // B0 is not changed during this process thus we need to shift to see that all other bytes were erased "set to
        // 0xFF"
        if ((uint32_t)(temp_buffer >> 8) == (uint32_t)FLASH_ERASED_VALUE) {
            if ((--return_value) != 0) {
                printf("programming flash was not succesful thus the erase here cannot be trusted\n");
            } else {
                printf("qspi Passed erase test observed: 0x%x\n", (uint32_t)(temp_buffer >> 8));
            }
        } else {
            return_value = -1;
            printf("qspi test miscompare\n");
            printf("Expected: 0xFFFFFFFF, observed: 0x%lx\n", (temp_buffer));
        }
#endif // QSPI_ERASE_VERIFICATION

#ifdef FSBL_EXECUTION
    prog_cleanup:
        // Close mailbox
        hps_mbox_close(mbox_handle);
#endif

        // Close QSPI
        qspi_close(qspi_handle);

        // Close reset manager
        printf("qspi read test stream done\n");

        // Close reset manager
        rstmgr_close(rstmgr_handle);
    }
    return return_value;
}
