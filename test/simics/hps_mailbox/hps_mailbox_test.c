#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
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
    int32_t return_value = 1;
    uint32_t hps_param = 0;

    // For some unknown reason this test doesn't work without this print statement here SO DON'T MOVE THIS UNTIL WE
    // UNDERSTAND WHY
    printf("BareMetal HPS Mailbox Tests Starting \n");
    int32_t rstmgr_handle = rstmgr_open(reset_manager, 0);
    hps_rstmgr_regs_t regs_buffer;
    if (rstmgr_handle < 0) {
        return_value = rstmgr_handle;
    } else {

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        regs_buffer.per1modrst &= ~((uint32_t)0x00030000);

        // Release CPU 0
        regs_buffer.cpurstrelease &= (uint32_t)0x0000000F;

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

        printf("Reset Manager CPU states = %08x\n", regs_buffer.cpuinreset);
        printf("HPS Mailbox test started\n");
        {
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
                printf("mailbox successfully open address = 0x%08x\n", mbox_handle);
                // Get CIN offset from the registers
                return_value =
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&cin_addr, sizeof(uint32_t));

                // Get COUT offset from the registers
                return_value =
                    hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&cout_addr, sizeof(uint32_t));

                /* Send command "Get Config Status" HPS  */
                if ((cin_addr == cout_addr) || (cin_addr <= cin_addr - 2)) {
                    // the input address equals the cout thus the full buffer is available OR
                    // cin has at least one word available
                    volatile hps_mailbox_reg_msg_t cin_buff; // = (hps_mailbox_reg_msg_t *)cin_addr;

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
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_COE_FLAG, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    // Write Header word to the command buffer
                    uintptr_t addr_ptr = (uintptr_t)&cin_buff;
                    uint32_t *ptr_hdr = (uint32_t *)addr_ptr;
                    printf("Value written to cbuf = %08x\n", (uint32_t)*ptr_hdr);
                    return_value =
                        hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, (uintptr_t)ptr_hdr, sizeof(uint32_t));

                    // Increment the CIN address
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    // Get CIN and COUT Values
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N1 CIN Offset = %x\n", hps_param);
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N1 COUT Offset = %x\n", hps_param);

                    // Get RIN offset cur_rin_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                                  sizeof(uint32_t));
                    printf("N1 RIN Offset = %x\n", cur_rin_value);

                    // Get RIN offset cur_rout_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rout_value,
                                                  sizeof(uint32_t));
                    printf("N1 ROUT Offset = %x\n", cur_rout_value);

                    // Set DBELL to SDM flag
                    hps_param = 1;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOSDM, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    // Wait for SDM to interrupt HPS
                    uint32_t ii = 400;
                    hps_param = 0;
                    do {

                        // Get doorbell to HPS
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_HPS_DBELL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));
                        if (hps_param != 0) {
                            ii = 0;

                            // Clear doorbell to HPS
                            hps_param = 0;
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOHPS,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));
                        }

                    } while (ii--);

                    // Get RIN offset cur_rin_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                                  sizeof(uint32_t));

                    // Get ROUT offset cur_rout_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                                  sizeof(uint32_t));

                    if (cur_rin_value != cur_rout_value) {
                        // Get value from Response Buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        // Increment the ROUT address "hps_param will not be changed by increment ROUT"
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        // Print the configuration Status header response
                        printf("Get Config Status Response = 0x%08x\n", (uint32_t)hps_param);

                        // Get ROUT offset cur_rout_value
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                      (uintptr_t)&cur_rout_value, sizeof(uint32_t));
                    }
                    // Point to header to get remaining length of response "Break Header Down"
                    addr_ptr = (uintptr_t)&hps_param;
                    hps_mailbox_reg_msg_t *ptr_cfg_hdr = (hps_mailbox_reg_msg_t *)addr_ptr;
                    uint32_t length_of_resp = ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size;

                    // Check Status of the response
                    if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                        printf("Command Executed Successfully\n");
                    }
                    printf("Config Response length= 0x%08x\n", (uint32_t)length_of_resp);

                    // Read/Print remaining response words
                    for (uint32_t i = 0; i < length_of_resp; i++) {

                        // Is there more data to read
                        if (cur_rout_value != cur_rin_value) {

                            printf("N1 ROUT before read =%x\n", cur_rout_value);
                            // Get response values from response buffer
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));

                            if (return_value == 0) {
                                // Update ROUT value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR,
                                                              (uintptr_t)&hps_param, sizeof(uint32_t));

                                // Get ROUT offset cur_rout_value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                              (uintptr_t)&cur_rout_value, sizeof(uint32_t));

                                printf("N1 Cur rout =%x ofst %d val=0x%08x\n", cur_rout_value, i, hps_param);
                            } else {
                                printf("Error reading response\n");
                            }
                        }
                    }

                    // Get CIN/COUT RIN/ROUT Values
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N2 CIN Offset = %x\n", hps_param);
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N2 COUT Offset = %x\n", hps_param);
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                                  sizeof(uint32_t));
                    printf("N2 ROUT Offset = %x\n", cur_rout_value);

                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                                  sizeof(uint32_t));
                    printf("N2 RIN Offset = %x\n", cur_rin_value);

                    // use previous and current RIN values to determin if DAta is avaiable for reading
                    /* Fill the command buffer with commands such that the CIN and COUT values wrap */
                    addr_ptr = (uintptr_t)&cin_buff; // cin_buff contains command for GET_CONFIG_STATUS
                    ptr_hdr = (uint32_t *)addr_ptr;

                    // Iteratively write to the command buffer
                    for (uint32_t i = 0; i < HPS_COMMAND_BUF_SIZE; i++) {
                        // Write GET_CONFIG_STATUS to command buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_CBUF_VAL, (uintptr_t)ptr_hdr,
                                                      sizeof(uint32_t));

                        // Increment the CIN address
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_CIN_ADDR, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));
#ifdef EXTRA_DEBUG
                        // Read NEW CIN offset
                        hps_param = 0;
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));
                        printf("New CIN Offset = %x\n", hps_param);
#endif
                    }

                    // Command Buffer has been filled with GET_CONFIG_STATUS commands from offset 0-31.
                    /* PROCESS GET_CONFIG_STATUS COMMAND #2 START*/
                    // Set DBELL to SDM flag
                    hps_param = 1;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOSDM, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    // Wait for SDM to interrupt HPS
                    ii = 400;
                    hps_param = 0;
                    do {

                        // Get DING Dong to HPS
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_HPS_DBELL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));
                        if (hps_param != 0) {
                            ii = 0;

                            // Clear DBELL for HPS
                            hps_param = 0;
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_SET_DBELL_TOHPS,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));
                        }

                    } while (ii--);

                    // Get RIN offset cur_rin_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                                  sizeof(uint32_t));
                    printf("Current RIN Offset = %x\n", cur_rin_value);

                    // Get ROUT offset cur_rout_value
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                                  sizeof(uint32_t));
                    printf("Current ROUT Offset = %x\n", cur_rout_value);

                    if (cur_rin_value != cur_rout_value) {
                        // Get value from Response Buffer
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));
                        // Increment the CIN address "hps_param will not be changed by increment ROUT"
                        return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR, (uintptr_t)&hps_param,
                                                      sizeof(uint32_t));

                        printf("Get Config Status Response = 0x%08x\n", (uint32_t)hps_param);
                        addr_ptr = (uintptr_t)&hps_param;
                        ptr_cfg_hdr = (hps_mailbox_reg_msg_t *)addr_ptr;
                        length_of_resp = ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_size;

                        if (ptr_cfg_hdr->hps_mbox_nrm_bhdr.hps_mbox_cer_cd == (uint32_t)0) {
                            printf("Command Executed Successfully\n");
                        }
                        printf("Config Response length= 0x%08x\n", (uint32_t)length_of_resp);
                    }
                    // Process the next command iteratively
                    for (uint32_t i = 0; i < length_of_resp; i++) {
                        // Is there more data to read
                        if (cur_rout_value != cur_rin_value) {

                            printf("N2 ROUT before read =%x\n", cur_rout_value);
                            // Get response values from response buffer
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));

                            if (return_value == 0) {
                                printf("offset %d val=0x%08x\n", i, hps_param);
                                // Update ROUT value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR,
                                                              (uintptr_t)&hps_param, sizeof(uint32_t));

                                // Get ROUT offset cur_rout_value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                              (uintptr_t)&cur_rout_value, sizeof(uint32_t));

                                printf("N2 Cur rout =%x ofst %d val=0x%08x\n", cur_rout_value, i, hps_param);
                            } else {
                                printf("Error reading response\n");
                            }
                        }
                    }
                    // Get CIN/COUT RIN/ROUT Values "ROUND 2"
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N3 CIN Offset = %x\n", hps_param);
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    printf("N3 COUT Offset = %x\n", hps_param);
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&cur_rout_value,
                                                  sizeof(uint32_t));
                    printf("N3 ROUT Offset = %x\n", cur_rout_value);

                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&cur_rin_value,
                                                  sizeof(uint32_t));
                    printf("N3 RIN Offset = %x\n", cur_rin_value);

                    // Process the next command iteratively
                    for (uint32_t i = 0; i < length_of_resp; i++) {
                        // Is there more data to read
                        if (cur_rout_value != cur_rin_value) {

                            printf("N3 ROUT before read =%x\n", cur_rout_value);
                            // Get response values from response buffer
                            return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RBUF_VAL,
                                                          (uintptr_t)&hps_param, sizeof(uint32_t));

                            if (return_value == 0) {
                                // Update ROUT value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_INC_ROUT_ADDR,
                                                              (uintptr_t)&hps_param, sizeof(uint32_t));
                                // Get ROUT offset cur_rout_value
                                return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST,
                                                              (uintptr_t)&cur_rout_value, sizeof(uint32_t));

                                printf("N3 Cur rout =%x ofst %d val=0x%08x\n", cur_rout_value, i, hps_param);
                            } else {
                                printf("Error reading response\n");
                            }
                        }
                    }
                    /* PROCESS GET_CONFIG_STATUS COMMAND #2 END*/

                    // VERIFY OUTPUTS OF CIN/COUT/RIN/ROUT
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_CIN_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    if (hps_param != 0) {
                        printf("Invalid CIN Offset = %x\n", hps_param);
                        return_value = -3;
                    } else {
                        printf("Correct CIN Offset = %x\n", hps_param);
                    }
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_COUT_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));

                    if (hps_param != 0) {
                        printf("Invalid COUT Offset = %x\n", hps_param);
                        return_value = -3;
                    } else {
                        printf("Correct COUT Offset = %x\n", hps_param);
                    }
                    hps_param = 0;
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_ROUT_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    if (hps_param != 4) {
                        printf("Invalid ROUT Offset = %x\n", hps_param);
                        return_value = -3;
                    } else {
                        printf("Correct ROUT Offset = %x\n", hps_param);
                    }
                    return_value = hps_mbox_ioctl(mbox_handle, IOCTL_MBOX_CMD_GET_RIN_OFST, (uintptr_t)&hps_param,
                                                  sizeof(uint32_t));
                    if (hps_param != 3) {
                        printf("Invalid RIN Offset = %x\n", hps_param);
                        return_value = -3;
                    } else {
                        printf("Correct RIN Offset = %x\n", hps_param);
                    }

                    if (return_value == 1) {
                        return_value = 0;
                    }
                }
            }
            hps_mbox_close(mbox_handle);
        }
    }
    return return_value;
}

#ifdef __cplusplus
}
#endif
