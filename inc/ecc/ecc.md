# ECC Driver

This describes the registers and their operational details for integration of the ECC IP into a target design.
All the control over the registers are via IOCTL functions.

## ECC_READ_REGS & ECC_WRITE_REGS
Reads and Writes the whole register bank

## ECC_GET_IP_REV_ID
Get the IP silicon revision number

## ECC_GET_IP_REV_ID2
Get the IP memory configuration

## ECC_GET_CTRL & ECC_SET_CTRL
Get and Set ECC Control Register

## ECC_GET_INITSTAT & ECC_SET_INITSTAT
Get and Set the initialization status used to indicate completion of hardware memory initialization done through CTRL.INITA / CTRL.INITB

## ECC_GET_ERRINTEN & ECC_SET_ERRINTEN
Get and Set Error Interrupt enable

## ECC_GET_ERRINTENS & ECC_SET_ERRINTENS
Get and Set Error interrupt set

## ECC_GET_ERRINTENR & ECC_SET_ERRINTENR
Get and Set Error Interrupt reset

## ECC_GET_INTMODE & ECC_SET_INTMODE
Get and Set Interrupt modes of ECC RAM system

## ECC_GET_INTSTAT & ECC_SET_INTSTAT
Get and Set to enable interrupt generation on SERR lookup table overflow. When all the entries in the table are valid=1 and this is bit is enabled, serr_req signal will be asserted.

## ECC_GET_INTTEST & ECC_SET_INTTEST
Get and Set to test interrupt from ECC RAM to GIC

## ECC_GET_MODSTAT & ECC_SET_MODSTAT
Get and Set Mode status flag

## ECC_GET_DERRADDRA
Get the address of PORTA current double-bit error. RAM size will determine the maximum number of address bits.

## ECC_GET_SERRADDRA
Get the address of PORTA current single-bit error. RAM size will determine the maximum number of address bits.

## ECC_GET_DERRADDRB
Get the address of PORTB current double-bit error. RAM size will determine the maximum number of address bits.

## ECC_GET_SERRADDRB
Get the address of PORTB current single-bit error. RAM size will determine the maximum number of address bits.

## ECC_GET_SERRCNTREG & ECC_SET_SERRCNTREG
Get and Set the maximum counter value for single-bit error interrupt

## ECC_GET_ECC_ADDRBUS & ECC_SET_ECC_ADDRBUS
Get and Set MSB bit of address is determined by ADR.

## ECC_GET_ECC_RDATA0BUS
Get Data from this register field. ECC_RDataBUS[31:0]

## ECC_GET_ECC_RDATA1BUS
Get Data from this register field. ECC_RDataBUS[63:32]

## ECC_GET_ECC_RDATA2BUS
Get Data from this register field. ECC_RDataBUS[95:64]

## ECC_GET_ECC_RDATA3BUS
Get Data from this register field. ECC_RDataBUS[127:96]

## ECC_SET_ECC_WDATA0BUS
Data from the register will be written to the RAM.ECC_WDataBUS[31:0]

## ECC_SET_ECC_WDATA1BUS
Data from the register will be written to the RAM.ECC_WDataBUS[63:32]

## ECC_SET_ECC_WDATA2BUS
Data from the register will be written to the RAM.ECC_WDataBUS[95:64]

## ECC_SET_ECC_WDATA3BUS
Data from the register will be written to the RAM.ECC_WDataBUS[127:96]

## ECC_GET_ECC_RDATAECC0BUS
The msb bit for the register is configured based on DAT parameter (RAM word size). Unimplemented bytes of this register will be reserved.

## ECC_GET_ECC_RDATAECC1BUS
The msb bit for the register is configured based on DAT parameter (RAM word size). Unimplemented bytes of this register will be reserved.

## ECC_SET_ECC_WDATAECC0BUS
The msb bit for the register is configured based on DAT parameter (RAM word size). Unimplemented bytes of this register will be reserved.

## ECC_SET_ECC_WDATAECC1BUS
The msb bit for the register is configured based on DAT parameter (RAM word size). Unimplemented bytes of this register will be reserved.

## ECC_GET_ECC_DBYTECTRL & ECC_SET_ECC_DBYTECTRL
Get and Set the max number of implemented byte enabled is DAT/8

## ECC_GET_ECC_ACCCTRL & ECC_SET_ECC_ACCCTRL
Getting and Setting these bits determine which byte of data/ecc to write to RAM.

## ECC_GET_ECC_STARTACC & ECC_SET_ECC_STARTACC
Getting and Setting these bits determine which byte of data/ecc to write to RAM.

## ECC_GET_ECC_WDCTRL & ECC_SET_ECC_WDCTRL
Get and Set Bits to Enable/Disable Watch Dog Timer

## ECC_GET_ECC_DECODERSTAT & ECC_SET_ECC_DECODERSTAT
Get and Set Individual decoder flags for single and double bits errors. Each decoder flags used represent one decoder in the design

## ECC_GET_SERRLKUPA0 & ECC_SET_SERRLKUPA0
Get and Set Single-bit error address in LOOKUP TABLE for PORTA Valid flag bit. Valid bit indicates if the address in this register is current or stale.
IF IP is having a single decoder, VALID8 will be used
IF IP is having multiple decoder, The lowest decoder will be represented on VALID1 and the next will on VALID2.
It increases onward to VALID8.

## ECC_GET_SERRLKUPB0 & ECC_SET_SERRLKUPB0
Get and Set Single-bit error address in LOOKUP TABLE for PORTB. Valid flag bit. Valid bit indicates if the address in this register is current or stale.
IF IP is having a single decoder, VALID8 will be used
IF IP is having multiple decoder, The lowest decoder will be represented on VALID1 and the next will on VALID2.
It increases onward to VALID8.

For a detailed register map, please refer to: https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/