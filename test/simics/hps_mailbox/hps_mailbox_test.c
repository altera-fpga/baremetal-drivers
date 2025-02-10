#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HPS_CLIENT_CHANNEL 2
#define CRYPTO_GET_CONFIG_STATUS 0x04

int main(void) {
    const char reset_manager[] = "/dev/rstmgr";

    const char mbox_initiator[] = "/dev/hps_mailbox";
    int32_t return_value = -1;
    uint32_t hps_param = 0;

#ifdef FSBL_EXECUTION
    fsbl_configuration();

    // Set OCRAM non secure access
    volatile uint32_t *lcl_ptr = (uint32_t *)0x108CC418;
    uint32_t dflt_ocram_state = (uint32_t)*lcl_ptr;
    *lcl_ptr = (uint32_t)0;
#endif

    // For some unknown reason this test doesn't work without this print statement here SO DON'T MOVE THIS UNTIL WE
    // UNDERSTAND WHY
    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    hps_rstmgr_regs_t regs_buffer;
    if (rstmgr_handle < 0) {
        return_value = rstmgr_handle;
    } else {
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_GET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));
        regs_buffer.per0modrst &= ~((uint32_t)0x00230707);
        regs_buffer.per1modrst &= ~((uint32_t)0x0403000F);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER0MODRST, (uintptr_t)(&regs_buffer.per0modrst),
                     sizeof(hps_rstmgr_regs_t));
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_SET_PER1MODRST, (uintptr_t)(&regs_buffer.per1modrst),
                     sizeof(hps_rstmgr_regs_t));

        int32_t mbox_handle = hps_mbox_open(mbox_initiator, 0);
        hps_mailbox_regs_words_t *ptr_mbox_st = (hps_mailbox_regs_words_t *)((uintptr_t)mbox_handle);
        if (mbox_handle < 0) {
            return_value = mbox_handle;
            printf("mailbox failed to open\n");
        } else if (hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_RESET_HPS_MBOX, (uintptr_t)&hps_param,
                                  sizeof(uint32_t)) != (int32_t)0) {
            printf("failed to reset HPS parameters\n");
        } else if ((uintptr_t)(&(ptr_mbox_st->hps_mbox_dbell_tosdm)) != (uintptr_t)HPS_MBOX_DBELL_TOSDM) {
            printf("Invalid dbell to SDM offset Structure incorrect\n");
            return_value = -1;
        } else if ((uintptr_t)(&(ptr_mbox_st->hps_mbox_dbell_tohps)) != (uintptr_t)HPS_MBOX_DBELL_TOHPS) {
            printf("Invalid dbell to HPS offset Structure incorrect\n");
            return_value = -1;
        } else if (get_nxtc_write_addr(mbox_handle) != (uint32_t)HPS_MBOX_CMD_BUF_BASE) {
            printf("Invalid Starting address of Command Buffer\n");
            return_value = -1;
        } else if (get_nxtr_read_ofst(mbox_handle) != (uint32_t)HPS_MBOX_RSP_BUF_BASE) {
            printf("Invalid Starting address of Response Buffer\n");
            return_value = -1;
        } else {
            uint32_t cin_addr = 0;
            uint32_t cout_addr = 0;
            uint32_t cur_rin_value = 0;
            uint32_t cur_rout_value = 0;

            printf("HPS Mailbox test started\n");

            // Get CIN offset from the registers
            return_value =
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&cin_addr, sizeof(uint32_t));

            // Get COUT offset from the registers
            return_value |=
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&cout_addr, sizeof(uint32_t));

            /* Send command "Get Config Status" HPS  */
            if ((cin_addr == cout_addr) || (cin_addr <= cin_addr - 2)) {
                // the input address equals the cout thus the full buffer is available OR
                // cin has at least one word available
                volatile hps_mailbox_reg_msg_t cin_buff;

                // Set command paramters for getting command
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cer_cd = CRYPTO_GET_CONFIG_STATUS;

                // Set indirect message indicator to false
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_ind = 0;

                // Set length to 0
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_size = 0;

                // Set CheckSum Present to False
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cksm = 0;

                // Set Channel ID to 1
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_cmd_id = 0;

                // Set Channel to HPS
                cin_buff.hps_mbox_nrm_bhdr.hps_mbox_ch_cl = HPS_CLIENT_CHANNEL;

                // SET COE interrupt enable
                hps_param = 1;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_COE_FLAG, (uintptr_t)&hps_param, sizeof(uint32_t));

                // Write Header word to the command buffer
                uintptr_t addr_ptr = (uintptr_t)&cin_buff;
                uint32_t *ptr_hdr = (uint32_t *)addr_ptr;

                // Write value to Command buffer
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, (uintptr_t)ptr_hdr, sizeof(uint32_t));

                // Increment the CIN address
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_param, sizeof(uint32_t));

                // Get CIN and COUT Values
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                // Get RIN offset cur_rin_value
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                               sizeof(uint32_t));

                // Get RIN offset cur_rout_value
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                               sizeof(uint32_t));

                // Set DBELL to SDM flag
                hps_param = 1;
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOSDM, (uintptr_t)&hps_param,
                                               sizeof(uint32_t));

                // Wait for SDM to interrupt HPS
                uint32_t ii = 400;
                hps_param = 0;
                do {

                    // Get doorbell to HPS
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_HPS_DBELL, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));
                    if (hps_param != 0) {
                        ii = 0;

                        // Clear doorbell to HPS
                        hps_param = 0;
                        return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOHPS,
                                                       (uintptr_t)&hps_param, sizeof(uint32_t));
                    }

                } while (ii--);

                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                if (hps_param != 1) {
                    printf("IT1 Invalid CIN Offset\n");
                }
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                if (hps_param != 1) {
                    printf("IT1 Invalid COUT Offset\n");
                }
                // Get RIN offset cur_rin_value
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value, sizeof(uint32_t));

                // Get ROUT offset cur_rout_value
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value, sizeof(uint32_t));

                if (cur_rin_value != cur_rout_value) {
                    // Get value from Response Buffer
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param, sizeof(uint32_t));

                    // Increment the ROUT address "hps_param will not be changed by increment ROUT"
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param, sizeof(uint32_t));

                    // Get ROUT offset cur_rout_value
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                   sizeof(uint32_t));

                    // Make sure no other data was waiting to be written due to rout's position
                    // Get RIN offset cur_rin_value
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                   sizeof(uint32_t));
                }
                // Point to header to get remaining length of response "Break Header Down"
                addr_ptr = (uintptr_t)&hps_param;
                hps_mailbox_reg_msg_t *ptr_cfg_hdr = (hps_mailbox_reg_msg_t *)addr_ptr;
                uint32_t length_of_resp = ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size;

                // Check Status of the response
                if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                    printf("Iteration 1 Command Executed Successfully\n");
                }

                if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size == (uint32_t)6) {
                    printf("Valid Size\n");
                }

                // Read/Print remaining response words
                for (uint32_t i = 0; i < length_of_resp; i++) {

                    // Is there more data to read
                    if (cur_rout_value != cur_rin_value) {

                        // printf("N1 ROUT before read =%x\n", cur_rout_value);
                        //  Get response values from response buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        if (return_value == 0) {
                            // Update ROUT value
                            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param,
                                           sizeof(uint32_t));

                            // Get ROUT offset cur_rout_value
                            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                           sizeof(uint32_t));

                            // Make sure no other data was waiting to be written due to rout's position
                            // Get RIN offset cur_rin_value
                            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                           sizeof(uint32_t));
                        } else {
                            printf("Error reading response\n");
                            if (i == (length_of_resp - 1)) {
                                return_value = -3;
                            }
                        }
                    }
                }

                // Get CIN/COUT RIN/ROUT Values
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));
                hps_param = 0;
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                               sizeof(uint32_t));

                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                               sizeof(uint32_t));

                /* Fill the command buffer with commands such that the CIN and COUT values wrap */
                addr_ptr = (uintptr_t)&cin_buff; // cin_buff contains command for GET_CONFIG_STATUS
                ptr_hdr = (uint32_t *)addr_ptr;

                // Iteratively write to the command buffer
                for (uint32_t i = 0; i < HPS_COMMAND_BUF_SIZE; i++) {
                    // Write GET_CONFIG_STATUS to command buffer
                    return_value |=
                        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, (uintptr_t)ptr_hdr, sizeof(uint32_t));

                    // Increment the CIN address
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));
#ifdef EXTRA_DEBUG
                    //  Read NEW CIN offset
                    //  To get a visual representation of how CIN is being updated the code below can be used.
                    //  This can assist verifying the current state of CIN
                    hps_param = 0;
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                    printf("Current CIN Offset %d\n", hps_param);

                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                    printf("Current COUT Offset %d\n", hps_param);

                    // wait 100 ticks
                    uint32_t ii = 100;
                    while (ii--)
                        ;
#endif
                }

                // Command Buffer has been filled with GET_CONFIG_STATUS commands from offset 0-31.
                /* PROCESS GET_CONFIG_STATUS COMMAND #2 START*/
                // Set DBELL to SDM flag
                hps_param = 1;
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOSDM, (uintptr_t)&hps_param,
                                               sizeof(uint32_t));

                // Wait for SDM to interrupt HPS
                ii = 400;
                hps_param = 0;
                do {

                    // Get DING Dong to HPS
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_HPS_DBELL, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));
                    if (hps_param != 0) {
                        ii = 0;

                        // Clear DBELL for HPS
                        hps_param = 0;
                        return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOHPS,
                                                       (uintptr_t)&hps_param, sizeof(uint32_t));
                    }

                } while (ii--);

                // Lets see how many commands have been processed
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));
                printf("Current COUT processed Offset %d\n", hps_param);

                // Get RIN offset cur_rin_value
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                               sizeof(uint32_t));

                // Get ROUT offset cur_rout_value
                return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                               sizeof(uint32_t));

                if (cur_rin_value != cur_rout_value) {
                    // Get value from Response Buffer
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));
                    // Increment the CIN address "hps_param will not be changed by increment ROUT"
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));

                    addr_ptr = (uintptr_t)&hps_param;
                    ptr_cfg_hdr = (hps_mailbox_reg_msg_t *)addr_ptr;
                    length_of_resp = ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size;

                    if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                        printf("Iteration 2 Command Executed Successfully\n");
                    }

                    if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size == (uint32_t)6) {
                        printf("Valid Size\n");
                    }

                    // Make sure no other data was waiting to be written due to rout's position
                    // Get RIN offset cur_rin_value
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                   sizeof(uint32_t));
                }
                // Process the next command iteratively
                for (uint32_t i = 0; i < length_of_resp; i++) {
                    // Is there more data to read
                    if (cur_rout_value != cur_rin_value) {
                        // Get response values from response buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        if (return_value == 0) {
                            // Update ROUT value
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));

                            // Get ROUT offset cur_rout_value
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                          (uintptr_t)&cur_rout_value, sizeof(uint32_t));

                            // Make sure no other data was waiting to be written due to rout's position
                            // Get RIN offset cur_rin_value
                            hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                           sizeof(uint32_t));
                        } else {
                            printf("Error reading response\n");
                            if (i == (length_of_resp - 1)) {
                                return_value = -3;
                            }
                        }
                    }
                }
                /* PROCESS GET_CONFIG_STATUS COMMAND #2 END*/
                // Get RIN/ROUT Values "ROUND 3"
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value, sizeof(uint32_t));
                printf("Iteration 2 completion ROUT Offset %d\n", cur_rout_value);
                hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value, sizeof(uint32_t));
                printf("Iteration 2 completion RIN Offset %d\n", cur_rin_value);

                if (cur_rin_value != cur_rout_value) {
                    // Get value from Response Buffer
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));
                    // Increment the CIN address "hps_param will not be changed by increment ROUT"
                    return_value |= hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param,
                                                   sizeof(uint32_t));

                    addr_ptr = (uintptr_t)&hps_param;
                    ptr_cfg_hdr = (hps_mailbox_reg_msg_t *)addr_ptr;
                    length_of_resp = ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size;

                    if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                        printf("Iteration 3 Command Executed Successfully\n");
                    }

                    if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size == (uint32_t)6) {
                        printf("Valid Size\n");
                    }

                    // Make sure no other data was waiting to be written due to rout's position
                    // Get RIN offset cur_rin_value
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                   sizeof(uint32_t));

                    // Update the ROUT value
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                   sizeof(uint32_t));
                }

                // Process the next command iteratively
                for (uint32_t i = 0; i < length_of_resp; i++) {
                    // Is there more data to read
                    if (cur_rout_value != cur_rin_value) {
                        // Get response values from response buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        if (return_value == 0) {
                            // Update ROUT value
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));
                            // Get ROUT offset cur_rout_value
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                          (uintptr_t)&cur_rout_value, sizeof(uint32_t));
                        } else {
                            printf("Error reading response\n");
                            if (i == (length_of_resp - 1)) {
                                return_value = -3;
                            }
                        }
                    }
                }
                /* PROCESS GET_CONFIG_STATUS COMMAND #3 END*/

                // VERIFY OUTPUTS OF CIN/COUT/RIN/ROUT
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                if (hps_param != 0) {
                    printf("Invalid CIN Offset = %x\n", hps_param);
                    return_value |= -3;
                }
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));

                if (hps_param != 5) {
                    printf("Invalid COUT Offset = %x\n", hps_param);
                    return_value |= -3;
                }
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));
                if (hps_param != (uint32_t)0x0e) {
                    printf("Invalid ROUT Offset %x\n", hps_param);
                    return_value |= -3;
                }
                hps_param = 0;
                return_value |=
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&hps_param, sizeof(uint32_t));
                if (hps_param != (uint32_t)0x0f) {
                    printf("Invalid RIN Offset %x\n", hps_param);
                    return_value |= -3;
                }

                printf("mailbox test complete\n");
            } // ((cin_addr == cout_addr) || (cin_addr <= cin_addr - 2))
        }     // if/else if "mbox_handle"
        hps_mbox_close(mbox_handle);
        rstmgr_close(rstmgr_handle);
#ifdef FSBL_EXECUTION
        *lcl_ptr = (uint32_t)dflt_ocram_state;
#endif
    } // if/else "reset_handle
    return return_value;
}

#ifdef __cplusplus
}
#endif
