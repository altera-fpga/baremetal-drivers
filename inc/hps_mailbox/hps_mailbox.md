# HPS mailbox Driver

Driver limtiations
While the API exposes functions to manage the direct mode interface direct mode is unsupported.
XIP is unsupported

## MBOX_CMD_GET_STATUS
Get the mailbox status.

## MBOX_CMD_GET_RBUF_VAL
Read a word from the response buffer.

## MBOX_CMD_GET_CBUF_VAL
Read a word from the command buffer.

## MBOX_CMD_GET_HPS_DBELL
Access doorbell to HPS.

## MBOX_CMD_GET_SDM_DBELL
Access doorbell to SDM.

## MBOX_CMD_GET_CIN_OFST
Read mailbox CIN "command input current address" value.

## MBOX_CMD_GET_ROUT_OFST
Read mailbox ROUT "response output buffer current address" value.

## MBOX_CMD_GET_RIN_OFST
Read mailbox RIN "response input current address" value.

## MBOX_CMD_GET_COUT_OFST
Read mailbox COUT "command output current address" value.

## MBOX_CMD_GET_INT_FLAG
Read mailbox FLAGS.

## MBOX_CMD_GET_URG
Read mailbox URG "urgent command" value.

## MBOX_CMD_SET_RBUF_VAL
Write a word to the response buffer. This method should only be used if user desires to act as SDM.

## MBOX_CMD_SET_CBUF_VAL
write to the command buffer.

## MBOX_CMD_SET_CIN_VAL
Set mailbox CIN "command input current address" value.

## MBOX_CMD_SET_ROUT_VAL
Set mailbox ROUT "next address to be read from response buffer address" value.

## MBOX_CMD_SET_COUT_VAL
Set mailbox COUT "next address to be read from command buffer address" value. This method should only be used if user desires to act as SDM.

## MBOX_CMD_SET_RIN_VAL
Set mailbox RIN "response input current address" value. This method should only be used if user desires to act as SDM.

## MBOX_CMD_SET_COE_FLAG
set COE flag "Clearing this flag is the only thing the HPS should be doing.

## MBOX_CMD_SET_RIE_FLAG
set RIE flag  "RIN update interrupt enable".

## MBOX_CMD_SET_UAE_FLAG
set UAE flag  "Urgent ACK interrupt enable".

## MBOX_CMD_SET_DBELL_TOSDM
set doorbell to SDM.

## MBOX_CMD_SET_DBELL_TOHPS
set doorbell to HPS.

## MBOX_CMD_RESET_HPS_MBOX
Clear both response and command buffers.

## MBOX_CMD_INC_CIN_ADDR
Increment the CIN Address.

## MBOX_CMD_INC_COUT_ADDR
Increment the COUT Address. This method should only be used if user desires to act as SDM.

## MBOX_CMD_INC_RIN_ADDR
Increment the RIN Address. This method should only be used if user desires to act as SDM.

## MBOX_CMD_INC_ROUT_ADDR
Increment the ROUT Address

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/docs/programmable/814346/24-3-1/hps-mailbox-address-map-and-register.html