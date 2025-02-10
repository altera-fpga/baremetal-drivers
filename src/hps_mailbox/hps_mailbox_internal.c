#include <stddef.h>
#include <stdint.h>

// HPS Mailbox Specific header
#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"

/*
 * This code controls a cadence SDM MAILBOX controller for an Altera Agilex5e HPS
 * NOTES:
 *       base_address is expected to already have been verified thus within this file it's "trusted"
 */

/* Initialization Methods */

/*
 * Clear both response and command buffers
 */
int32_t clear_buffers(int32_t base_address) {
    int32_t ret_val = -1;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if ((ptr_mbox_reg != NULL)) {
        // Clear elements of both buffers
        for (uint32_t i = 0; i < (uint32_t)HPS_COMMAND_BUF_SIZE; i++) {
            ptr_mbox_reg->hps_mbox_cmd_buf[i] = 0;

            // Response buffer is different size than the command buffer
            if (i < (uint32_t)HPS_RESPONSE_BUF_SIZE) {
                ptr_mbox_reg->hps_mbox_rsp_buf[i] = 0;
            }
        }

        // Set return value to success
        ret_val = 0;
    }

    return ret_val;
}

/*
 * Clear both response and command buffers
 */
int32_t hps_mailbox_hard_reset(int32_t base_address) {

    // return value default to error
    int32_t ret_val = -1;

    // Clear Buffers first if Successfull go further
    ret_val = clear_buffers(base_address);
    if (ret_val == 0) {

        // Reset CIN/COUt RIN/ROUT to base offsets of their corresponding buffers

        // Get pointer to HPS mailbox elements
        hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

        if ((ptr_mbox_reg != NULL)) {

            // Set CIN and COUT register values to starting offset
            ptr_mbox_reg->hps_mbox_cin = 0;
            ptr_mbox_reg->hps_mbox_cout = 0;

            // Set RIn and ROUT register values to starting offset
            ptr_mbox_reg->hps_mbox_rin = 0;
            ptr_mbox_reg->hps_mbox_rout = 0;

            // Set return value to success
            ret_val = 0;
        }
    }

    return ret_val;
}

/* METHODS FOR RETRIEVING REGISTERS START */

/*
 * Read mailbox CIN "command input current address" value
 */
int32_t get_hps_cin(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {

        // return command input offset
        *rparam = (uint32_t)ptr_mbox_reg->hps_mbox_cin;

        // Set return value to succes
        ret_val = 0;
    }

    return ret_val;
}

/*
 * Get register address of the next word to be written to command buffer
 */
uintptr_t get_nxtc_write_addr(int32_t base_address) {

    uint32_t cmd_nwrite = 0;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // get CIN VALUE
    get_hps_cout(base_address, &cmd_nwrite);

    // Return current Offset
    return (uintptr_t)&ptr_mbox_reg->hps_mbox_cmd_buf[cmd_nwrite];
}

/*
 * Get register address of the next word to be read from the command buffer
 */
uintptr_t get_nxtc_read_ofst(int32_t base_address) {

    uint32_t cmd_nread = 0;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // get COUT VALUE
    get_hps_cout(base_address, &cmd_nread);

    // Return current Offset
    return (uintptr_t)&ptr_mbox_reg->hps_mbox_cmd_buf[cmd_nread];
}

/*
 * Get register address of the next word to be written to the response buffer
 */
uintptr_t get_nxtr_write_ofst(int32_t base_address) {

    uint32_t rsp_write_ofst = 0;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get response buffer RIN ofset
    get_hps_rin(base_address, &rsp_write_ofst);

    // Return current Offset
    return (uintptr_t)&ptr_mbox_reg->hps_mbox_rsp_buf[rsp_write_ofst];
}

/*
 * Get register address of the next word to be read from the response buffer
 */
uintptr_t get_nxtr_read_ofst(int32_t base_address) {

    uint32_t rsp_read_ofst = 0;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get ROUT offset
    get_hps_rout(base_address, &rsp_read_ofst);

    // Return current Offset
    return (uintptr_t)&ptr_mbox_reg->hps_mbox_rsp_buf[rsp_read_ofst];
}

/*
 * Read mailbox COUT "command output current address" value
 */
int32_t get_hps_cout(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // return command output address
        *rparam = ptr_mbox_reg->hps_mbox_cout;

        // set return value to success
        ret_val = 0;
    }

    return ret_val;
}

/*
 * Read mailbox RIN "response input current address" value
 */
int32_t get_hps_rin(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // return response input address
        *rparam = ptr_mbox_reg->hps_mbox_rin;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Read mailbox ROUT "response output buffer current address" value
 */
int32_t get_hps_rout(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // return response output address
        *rparam = ptr_mbox_reg->hps_mbox_rout;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Read mailbox URG "urgent command" value
 */
int32_t get_hps_urg(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // return urgent command register
        *rparam = ptr_mbox_reg->hps_mbox_urg;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Read mailbox FLAGS
 */
int32_t get_hps_flags(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // get flags
        *rparam = ptr_mbox_reg->hps_mbox_flags;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Read mailbox STATUS
 */
int32_t get_hps_status(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        // get status
        *rparam = ptr_mbox_reg->hps_mbox_status;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Access doorbell to SDM
 */
int32_t get_sdm_dbell_val(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        *rparam = ptr_mbox_reg->hps_mbox_dbell_tosdm.hps_mbox_dbell_active;
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Access doorbell to HPS
 */
int32_t get_hps_dbell_val(int32_t base_address, uint32_t *rparam) {

    int32_t ret_val = -1;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        *rparam = ptr_mbox_reg->hps_mbox_dbell_tohps.hps_mbox_dbell_active;
    }
    return ret_val;
}

/*
 * Read a word from the command buffer
 */
int32_t read_word_cmd_buf(int32_t base_address, uint32_t *wparam) {

    int32_t ret_val = -1;
    uint32_t cmd_ninput = 0;
    uint32_t cmd_nread = 0;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Capture next word that can be read from the command buffer
    get_hps_cin(base_address, &cmd_ninput);
    get_hps_cout(base_address, &cmd_nread);

    // If the values are equal there is no data to be read
    if (cmd_ninput == cmd_nread) {

        // There is no data to read
        ret_val = -2;
    } else {
        // If ptr is NOT NULL we can execute
        if ((ptr_mbox_reg != NULL)) {

            // Copy word from the command buffer
            *wparam = ptr_mbox_reg->hps_mbox_cmd_buf[cmd_nread];

            // Set return value to success
            ret_val = 0;
        }
    }
    return ret_val;
}

/*
 * Read a word from the response buffer
 */
int32_t read_word_rsp_buf(int32_t base_address, uint32_t *wparam) {

    int32_t ret_val = -1;
    uint32_t rsp_ninput = 0;
    uint32_t rsp_nread = 0;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Capture next address to write and read from the response buffer
    get_hps_rin(base_address, &rsp_ninput);
    get_hps_rout(base_address, &rsp_nread);
    // If the values are equal there is no data to be read
    if (rsp_ninput == rsp_nread) {

        // There is no data to read
        ret_val = -2;
    } else {
        // If ptr is NOT NULL we can execute
        if (ptr_mbox_reg != NULL) {

            // Copy word from the command buffer
            *wparam = ptr_mbox_reg->hps_mbox_rsp_buf[rsp_nread];

            // Set return value to success
            ret_val = 0;
        }
    }
    return ret_val;
}
/* METHODS FOR RETRIEVING REGISTERS END */

/* METHODS FOR SETTING REGISTERS START */

/*
 * Set mailbox CIN "command input current address" value
 */
int32_t set_cur_cin_addr(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // return command input address
        ptr_mbox_reg->hps_mbox_cin = wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Set mailbox RIN "response input current address" value
 *  --- "This method should only be used if user desires to act as SDM"
 */
int32_t set_cur_rin_addr(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // return command input address
        ptr_mbox_reg->hps_mbox_rin = wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Set mailbox COUT "next address to be read from command buffer address" value
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t set_cur_cout_addr(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // return command input address
        ptr_mbox_reg->hps_mbox_cout = wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Set mailbox ROUT "next address to be read from response buffer address" value
 */
int32_t set_cur_rout_addr(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // return command input address
        ptr_mbox_reg->hps_mbox_rout = wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * write to the command buffer
 */
int32_t write_word_cmd_buf(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    uint32_t cmd_ninput = 0;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Capture next address to write and read from the command buffer
    get_hps_cin(base_address, &cmd_ninput);

    // If ptr is NOT NULL we can execute
    if ((ptr_mbox_reg != NULL)) {

        // Copy word to the command buffer
        ptr_mbox_reg->hps_mbox_cmd_buf[cmd_ninput] = wparam;

        // Set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * write a word to the response buffer
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t write_word_rsp_buf(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    uint32_t rsp_ninput = 0;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Capture next address to write and read from the response buffer
    get_hps_rin(base_address, &rsp_ninput);

    // If ptr is NOT NULL we can execute
    if (ptr_mbox_reg != NULL) {

        // Copy word to the command buffer
        ptr_mbox_reg->hps_mbox_rsp_buf[rsp_ninput] = wparam;

        // Set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * set COE flag "Clearing this flag is the only thing the HPS should be doing
 */
int32_t hps_set_coe_flag(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get address of flags
    uintptr_t flags_addr = (uintptr_t)&ptr_mbox_reg->hps_mbox_flags;

    // point to flags to ensure we're updating ONLY to the COE flag
    hps_mailbox_flags_t *ptr_mbox_reg_flags = (hps_mailbox_flags_t *)flags_addr;

    if (ptr_mbox_reg_flags != NULL) {

        ptr_mbox_reg_flags->hps_mbox_flag_coe = (uint8_t)wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * set RIE flag  "RIN update interrupt enable"
 */
int32_t hps_set_rie_flag(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get address of flags
    uintptr_t flags_addr = (uintptr_t)&ptr_mbox_reg->hps_mbox_flags;

    // point to flags to ensure we're updating ONLY to the COE flag
    hps_mailbox_flags_t *ptr_mbox_reg_flags = (hps_mailbox_flags_t *)flags_addr;

    if (ptr_mbox_reg_flags != NULL) {

        ptr_mbox_reg_flags->hps_mbox_flag_rie = (uint8_t)wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Set mailbox URG "urgent command" value
 */
int32_t set_hps_urg(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get value only if base address is valid
    if (ptr_mbox_reg != NULL) {
        ptr_mbox_reg->hps_mbox_urg = wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * set UAE flag  "Urgent ACK interrupt enable"
 */
int32_t hps_set_uae_flag(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    // Get address of flags
    uintptr_t flags_addr = (uintptr_t)&ptr_mbox_reg->hps_mbox_flags;

    // point to flags to ensure we're updating ONLY to the COE flag
    hps_mailbox_flags_t *ptr_mbox_reg_flags = (hps_mailbox_flags_t *)flags_addr;

    if (ptr_mbox_reg_flags != NULL) {

        ptr_mbox_reg_flags->hps_mbox_flag_uae = (uint8_t)wparam;

        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * set doorbell to SDM
 */
int32_t hps_set_dbell_tosdm(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {

        ptr_mbox_reg->hps_mbox_dbell_tosdm.hps_mbox_dbell_active = (uint8_t)wparam;
        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * set doorbell to SDM
 */
int32_t hps_set_dbell_tohps(int32_t base_address, uint32_t wparam) {

    int32_t ret_val = -1;
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {

        ptr_mbox_reg->hps_mbox_dbell_tohps.hps_mbox_dbell_active = (uint8_t)wparam;
        // set return value to success
        ret_val = 0;
    }
    return ret_val;
}

/*
 * Increment the CIN Address
 * Note:
 *    This method is designed to be called after writing to the command buffer.
 *    Executing this out of sequence WILL CAUSE issues
 */
int32_t hps_autoinc_cin(int32_t base_address) {

    int32_t ret_val = -1;
    uint32_t buf_sz_max_ofst = (HPS_COMMAND_BUF_SIZE - (uint32_t)1);
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // Increment CIN register to the next word
        if (ptr_mbox_reg->hps_mbox_cin < buf_sz_max_ofst) {
            if (ptr_mbox_reg->hps_mbox_cin == (ptr_mbox_reg->hps_mbox_cout - (uint32_t)1)) {
                // Set return value to special error "there is no space"
                ret_val = -2;
            } else {
                ptr_mbox_reg->hps_mbox_cin += (uint32_t)1;

                // set return value to success
                ret_val = 0;
            }
        } else {

            if (ptr_mbox_reg->hps_mbox_cout == (uint32_t)0) {
                // Set return value to special error "there is no space"
                ret_val = -2;
            } else {
                // Reset buffer offset to beginning
                ptr_mbox_reg->hps_mbox_cin = (uint32_t)0;

                // set return value to success
                ret_val = 0;
            }
        }
    }
    return ret_val;
}

/*
 * Increment the COUT Address
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t hps_autoinc_cout(int32_t base_address) {

    int32_t ret_val = -1;
    uint32_t buf_sz_max_ofst = (HPS_COMMAND_BUF_SIZE - (uint32_t)1);
    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // Increment COUT register to the next word
        if (ptr_mbox_reg->hps_mbox_cout < buf_sz_max_ofst) {
            if (ptr_mbox_reg->hps_mbox_cout == (uint32_t)ptr_mbox_reg->hps_mbox_cin) {
                // Set return value to special error "there is no space"
                ret_val = -2;
            } else {
                ptr_mbox_reg->hps_mbox_cout += (uint32_t)1;

                // set return value to success
                ret_val = 0;
            }
        } else {
            if (ptr_mbox_reg->hps_mbox_cin == (uint32_t)0) {
                // Set return value to special error "there is no space"
                ret_val = -2;
            } else {
                // Reset buffer offset to beginning
                ptr_mbox_reg->hps_mbox_cout = (uint32_t)0;

                // set return value to success
                ret_val = 0;
            }
        }
    }
    return ret_val;
}

/*
 * Increment the RIN Address
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t hps_autoinc_rin(int32_t base_address) {

    int32_t ret_val = -1;

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;

    if (ptr_mbox_reg != NULL) {
        // Increment RIN register to the next word
        if (ptr_mbox_reg->hps_mbox_rin < (HPS_RESPONSE_BUF_SIZE - (uint32_t)1)) {

            if (ptr_mbox_reg->hps_mbox_rin == (ptr_mbox_reg->hps_mbox_rout - (uint32_t)1)) {
                // Set return value to special error "there is no space"
                ret_val = -2;
            } else {

                // Increment the buffer
                ptr_mbox_reg->hps_mbox_rin += (uint32_t)1;

                // set return value to success
                ret_val = 0;
            }
        } else {

            // RIN is set to the last offset so lets examine if there is any space at the beginning of the buffer to
            // write relative to ROUT
            if (ptr_mbox_reg->hps_mbox_rout == (uint32_t)0) {
                // set return value to special error "there is no space to write"
                ret_val = -2;
            } else {
                // Reset buffer offset to beginning
                ptr_mbox_reg->hps_mbox_rin = (uint32_t)0;

                // set return value to success
                ret_val = 0;
            }
        }
    }

    return ret_val;
}

/*
 * Increment the ROUT Address
 * Note:
 *    This method is designed to be called after reading from the response buffer.
 *    Executing this out of sequence WILL CAUSE issues
 */
int32_t hps_autoinc_rout(int32_t base_address) {

    int32_t ret_val = -1;
    uint32_t buf_sz_max_ofst = (HPS_RESPONSE_BUF_SIZE - (uint32_t)1);

    // Get pointer to HPS mailbox elements
    hps_mailbox_regs_words_t *ptr_mbox_reg = (hps_mailbox_regs_words_t *)base_address;
    if (ptr_mbox_reg != NULL) {
        // Increment ROUT register to the next word
        if (ptr_mbox_reg->hps_mbox_rout < buf_sz_max_ofst) {
            if (ptr_mbox_reg->hps_mbox_rout == (uint32_t)ptr_mbox_reg->hps_mbox_rin) {
                // This is a special error there is no space on the device
                ret_val = -2;
            } else {
                // Increment the buffer
                ptr_mbox_reg->hps_mbox_rout += (uint32_t)1;

                // set return value to success
                ret_val = 0;
            }
        } else {
            // ROUT is set to the last offset so lets examine if there is any space at the beginning of the buffer to
            // write relative to RIN
            if (ptr_mbox_reg->hps_mbox_rin == (uint32_t)buf_sz_max_ofst) {

                // set return value to special error "there is no space to write"
                ret_val = -2;
            } else {
                // Reset buffer offset to beginning
                ptr_mbox_reg->hps_mbox_rout = (uint32_t)0;

                // set return value to success
                ret_val = 0;
            }
        }
    }
    return ret_val;
}

/* METHODS FOR SETTING REGISTERS END */
