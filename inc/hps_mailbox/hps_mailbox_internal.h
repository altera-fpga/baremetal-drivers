#ifndef HPS_MAILBOX_INTERNAL_H
#define HPS_MAILBOX_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*
This code controls a cadence HPS MAILBOX controller for an Altera Agilex5e HPS
*/

/*
 * Clear both response and command buffers
 */
int32_t clear_buffers(int32_t base_address);

/*
 * Read mailbox CIN "command input current address" value
 */
int32_t get_hps_cin(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox COUT "command output current address" value
 */
int32_t get_hps_cout(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox RIN "response input current address" value
 */
int32_t get_hps_rin(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox ROUT "response output buffer current address" value
 */
int32_t get_hps_rout(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox URG "urgent command" value
 */
int32_t get_hps_urg(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox FLAGS
 */
int32_t get_hps_flags(int32_t base_address, uint32_t *rparam);

/*
 * Access doorbell to SDM
 */
int32_t get_sdm_dbell_val(int32_t base_address, uint32_t *rparam);

/*
 * Access doorbell to HPS
 */
int32_t get_hps_dbell_val(int32_t base_address, uint32_t *rparam);

/*
 * Read mailbox STATUS
 */
int32_t get_hps_status(int32_t base_address, uint32_t *rparam);

/*
 * Read a word from the command buffer
 */
int32_t read_word_cmd_buf(int32_t base_address, uint32_t *wparam);

/*
 * Read a word from the response buffer
 */
int32_t read_word_rsp_buf(int32_t base_address, uint32_t *wparam);

/*
 * write to the command buffer
 */
int32_t write_word_cmd_buf(int32_t base_address, uint32_t wparam);

/*
 * write a word to the response buffer
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t write_word_rsp_buf(int32_t base_address, uint32_t wparam);

/*
 * Set mailbox RIN "response input current address" value
 */
int32_t set_cur_rin_addr(int32_t base_address, uint32_t wparam);

/*
 * Set mailbox COUT "next address to be read from command buffer address" value
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t set_cur_cout_addr(int32_t base_address, uint32_t wparam);

/*
 * Set mailbox ROUT "next address to be read from response buffer address" value
 */
int32_t set_cur_rout_addr(int32_t base_address, uint32_t wparam);

/*
 * Set mailbox CIN "command input current address" value
 */
int32_t set_cur_cin_addr(int32_t base_address, uint32_t wparam);

/*
 * set UAE flag  "Urgent ACK interrupt enable"
 */
int32_t hps_set_uae_flag(int32_t base_address, uint32_t wparam);

/*
 * set RIE flag  "RIN update interrupt enable"
 */
int32_t hps_set_rie_flag(int32_t base_address, uint32_t wparam);

/*
 * set RIE flag  "RIN update interrupt enable"
 */
int32_t set_hps_urg(int32_t base_address, uint32_t wparam);

/*
 * set COE flag "Clearing this flag is the only thing the HPS should be doing
 */
int32_t hps_set_coe_flag(int32_t base_address, uint32_t wparam);

/*
 * set doorbell to SDM
 */
int32_t hps_set_dbell_tosdm(int32_t base_address, uint32_t wparam);

/*
 * Clear both response and command buffers
 */
int32_t hps_mailbox_hard_reset(int32_t base_address);

/*
 * set doorbell to SDM
 */
int32_t hps_set_dbell_tohps(int32_t base_address, uint32_t wparam);

/*
 * Increment the CIN Address
 */
int32_t hps_autoinc_cin(int32_t base_address);

/*
 * Increment the COUT Address
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t hps_autoinc_cout(int32_t base_address);

/*
 * Increment the RIN Address
 * -- "This method should only be used if user desires to act as SDM"
 */
int32_t hps_autoinc_rin(int32_t base_address);

/*
 * Increment the ROUT Address
 */
int32_t hps_autoinc_rout(int32_t base_address);

/*
 * Get register address of the next word to be read from the command buffer
 */
uintptr_t get_nxtc_read_ofst(int32_t base_address);

/*
 * Get register address of the next word to be written to command buffer
 */
uintptr_t get_nxtc_write_addr(int32_t base_address);

/*
 * Get register address of the next word to be written to the response buffer
 */
uintptr_t get_nxtr_write_ofst(int32_t base_address);

/*
 * Get register address of the next word to be read from the response buffer
 */
uintptr_t get_nxtr_read_ofst(int32_t base_address);

#ifdef __cplusplus
}
#endif
#endif // HPS_MAILBOX_INTERNAL_H
