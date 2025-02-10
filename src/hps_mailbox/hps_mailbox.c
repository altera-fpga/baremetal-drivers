#include "device.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// HPS Mailbox Specific header
#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"

// mailbox descriptors
device_descriptor_t sdm_mailbox[] = {{.name = "/dev/hps_mailbox", .fd = HPS_MAILBOX_BASE, .acquired = 0}};

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      hps_mbox_recv,hps_mbox_read,hps_mbox_send,hps_mbox_write
 * description:
 *      return 0
 */
size_t hps_mbox_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) { return 0; }
size_t hps_mbox_read(int32_t fd, uintptr_t buf, size_t size) { return hps_mbox_recv(fd, buf, size, 0); }
size_t hps_mbox_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags) { return 0; }
size_t hps_mbox_write(int32_t fd, const uintptr_t buf, size_t size) { return hps_mbox_send(fd, buf, size, 0); }

/* name: hps_mbox_verify_access
 * description: search if "base_address" has been properly captured for access
 * parameters(s): "base_address" base address of the HPS MBOX timer
 */
static int32_t hps_mbox_verify_access(int32_t base_address) {

    int32_t return_value = -1;
    // Search through devices for matching
    for (uint32_t i = 0; i < (sizeof(sdm_mailbox) / sizeof(device_descriptor_t)); i++) {
        // Is the current base address valid and acquired
        if ((sdm_mailbox[i].fd == base_address) && (sdm_mailbox[i].acquired == true)) {
            return_value = 0;
            break;
        }
    }
    return return_value;
}

/* name: hps_mbox_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t hps_mbox_open(const char *path, int32_t flags) {
    int32_t hps_mbox_base = -1;
    for (uint32_t i = 0; i < (sizeof(sdm_mailbox) / sizeof(device_descriptor_t)); i++) {
        if (strcmp(sdm_mailbox[i].name, path) == 0) {
            if (claim_device(&sdm_mailbox[i])) {
                hps_mbox_base = sdm_mailbox[i].fd;
            }
        }
    }
    return hps_mbox_base;
}

/* name: hps_mbox_close
 * description: close the fd via the base address of the device
 * parameters(s): base_add "address of the hps mailbox device open"
 */
int32_t hps_mbox_close(int32_t base_add) {
    int32_t return_value = -1;
    for (uint32_t i = 0; i < (sizeof(sdm_mailbox) / sizeof(device_descriptor_t)); i++) {
        if (sdm_mailbox[i].fd == base_add) {
            sdm_mailbox[i].acquired = 0;
            return_value = 0;
            break;
        }
    }
    return return_value;
}

/* name: hps_mbox_ioctl
 * description: process the input output control command
 * parameters(s): base_add "address of the hps mailbox device open"
 *                operation "specific ioctl command for hps mailbox"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to
 */
int32_t hps_mbox_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length) {
    // return value denoting status
    // TODO create structure of status return values
    int32_t ret_val = -1;

    // pointer to the memory denoted via argument user_buf
    uint32_t *cmd_data = (uint32_t *)user_data;

    // Validate if base address is currently acquired
    if ((hps_mbox_verify_access(base_add) == -1) || (length < (sizeof(uint32_t)))) {
        // Current base_address descriptor has not been acquired
        // Expectation currently is ret_val is set for error "-1"
        // TODO create return value to denote unacquired file descriptor
        // OR
        // Expectation that return_value is -1 "TODO make specific error for length error

        // Return value should already be set to error but lets just future proof this
        ret_val = -1;
    } else {
        // Check if operation is valid
        switch ((uint32_t)operation) {

        // Get Status register of
        case IOCTL_MBOX_CMD_GET_STATUS:
            ret_val = get_hps_status(base_add, cmd_data);
            break;

        // Get value from response buffer
        // This should only be used if acting as the SDM
        case IOCTL_MBOX_CMD_GET_RBUF_VAL:
            ret_val = read_word_rsp_buf(base_add, cmd_data);
            break;

        // Get value from command buffer
        case IOCTL_MBOX_CMD_GET_CBUF_VAL:
            ret_val = read_word_cmd_buf(base_add, cmd_data);
            break;

        // Get address of the next word to be written to command buffer
        case IOCTL_MBOX_CMD_GET_CIN_OFST:
            ret_val = get_hps_cin(base_add, cmd_data);
            break;

        // Get address of the next word to be read from command buffer
        case IOCTL_MBOX_CMD_GET_COUT_OFST:
            ret_val = get_hps_cout(base_add, cmd_data);
            break;

        // Get address of the next word to be written to response buffer
        case IOCTL_MBOX_CMD_GET_RIN_OFST:
            ret_val = get_hps_rin(base_add, cmd_data);
            break;

        // Get address of the next word to be read from response buffer
        case IOCTL_MBOX_CMD_GET_ROUT_OFST:
            ret_val = get_hps_rout(base_add, cmd_data);
            break;

        // Get interrupt flags
        case IOCTL_MBOX_CMD_GET_INT_FLAG:
            ret_val = get_hps_flags(base_add, cmd_data);
            break;

        // Get doorbell flag to HPS
        case IOCTL_MBOX_CMD_GET_HPS_DBELL:
            ret_val = get_hps_dbell_val(base_add, cmd_data);
            break;

        // Get doorbell flag to SDM
        case IOCTL_MBOX_CMD_GET_SDM_DBELL:
            ret_val = get_sdm_dbell_val(base_add, cmd_data);
            break;

        // Get urgent command
        case IOCTL_MBOX_CMD_GET_URG:
            ret_val = get_hps_urg(base_add, cmd_data);
            break;

        /* Start of writting methods */
        // Write word to the response buffer
        case IOCTL_MBOX_CMD_SET_RBUF_VAL:
            ret_val = write_word_rsp_buf(base_add, *cmd_data);
            break;

        // Write word to the command buffer
        case IOCTL_MBOX_CMD_SET_CBUF_VAL:
            ret_val = write_word_cmd_buf(base_add, *cmd_data);
            break;

        // Write new address of the next word to be written to command buffer "cin"
        case IOCTL_MBOX_CMD_SET_CIN_VAL:
            ret_val = set_cur_cin_addr(base_add, *cmd_data);
            break;

        // Write new address for next word to be read from response buffer "rout"
        case IOCTL_MBOX_CMD_SET_ROUT_VAL:
            ret_val = set_cur_rout_addr(base_add, *cmd_data);
            break;

        // Write new address for next word to be read from response buffer "rout"
        case IOCTL_MBOX_CMD_SET_COUT_VAL:
            ret_val = set_cur_cout_addr(base_add, *cmd_data);
            break;

        // Write new address for next word to be read from response buffer "rin"
        case IOCTL_MBOX_CMD_SET_RIN_VAL:
            ret_val = set_cur_rin_addr(base_add, *cmd_data);
            break;

        // Update the COUT interrupt enable flag
        case IOCTL_MBOX_CMD_SET_COE_FLAG:
            ret_val = hps_set_coe_flag(base_add, *cmd_data);
            break;

        // Update the RIN interrupt enable flag
        case IOCTL_MBOX_CMD_SET_RIE_FLAG:
            ret_val = hps_set_rie_flag(base_add, *cmd_data);
            break;

        // Update the Urgent ACK interrupt enable flag
        case IOCTL_MBOX_CMD_SET_UAE_FLAG:
            ret_val = hps_set_uae_flag(base_add, *cmd_data);
            break;

        // Set the doorbell to SDM
        case IOCTL_MBOX_CMD_SET_DBELL_TOSDM:
            ret_val = hps_set_dbell_tosdm(base_add, *cmd_data);
            break;

            /* increment the CIN address
             * Note:
             *    This method is designed to be called after writing to the command buffer.
             *    Executing this out of sequence WILL CAUSE issues
             */
        case IOCTL_MBOX_CMD_INC_CIN_ADDR:
            ret_val = hps_autoinc_cin(base_add);
            break;

            /* increment the COUT address
             * Note:
             *    This method is designed to be called after reading from the command buffer.
             *    Executing this out of sequence WILL CAUSE issues
             *    This should only be used if acting as the SDM
             */
        case IOCTL_MBOX_CMD_INC_COUT_ADDR:
            ret_val = hps_autoinc_cout(base_add);
            break;

            /* increment the RIN address
             * Note:
             *    This method is designed to be called after writing to the response buffer.
             *    Executing this out of sequence WILL CAUSE issues
             *    This should only be used if acting as the SDM
             */
        case IOCTL_MBOX_CMD_INC_RIN_ADDR:
            ret_val = hps_autoinc_rin(base_add);
            break;

            /* increment the ROUT address
             * Note:
             *    This method is designed to be called after reading from the response buffer.
             *    Executing this out of sequence WILL CAUSE issues
             */
        case IOCTL_MBOX_CMD_INC_ROUT_ADDR:
            ret_val = hps_autoinc_rout(base_add);
            break;

        // Set urgent command
        case IOCTL_MBOX_CMD_SET_URG:
            ret_val = set_hps_urg(base_add, *cmd_data);
            break;

        // Set the doorbell to HPS
        case IOCTL_MBOX_CMD_SET_DBELL_TOHPS:
            ret_val = hps_set_dbell_tohps(base_add, *cmd_data);
            break;

        // Reset HPS Mailbox paramters
        case IOCTL_MBOX_CMD_RESET_HPS_MBOX:
            ret_val = hps_mailbox_hard_reset(base_add);
            break;

        default:
            // invalid command
            ret_val = -2;
            break;
        }
    }

    return ret_val;
}

int32_t s_mailbox_error(int32_t base_add) { return -1; }
