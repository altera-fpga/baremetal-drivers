# Timers

This driver provides access to the SP and OSC timers.

NOTE: These are common IOCTLs for both types of timers, SP Timer & OSC Timer. The user should specify what timer they are calling, according to the base_address or fd in the IOCTL calls.

## IOCTL_TIMER_REGS_READ & IOCTL_TIMER_REGS_WRITE
Reads and Writes the whole register bank.

## TIMER_COUNT_SET & TIMER_COUNT_GET
Set and Get Timer Load Count Register.
This register contains the value to be loaded into Timer. 
This is the value from which counting commences. Any value written to this register is loaded into the associated timer.

## TIMER_CURRENT_VAL_GET
Get Timer Current Value
This register shows the Current Value of Timer.
This register is supported only when timer_1_clk is synchronous to pclk. Reading this register when using independent clocks results in an undefined value.

## TIMER_CONTROL_SET & TIMER_CONTROL_GET
Set and Get Timer Control Register.
This register controls enabling, operating mode (free-running or defined-count), and interrupt mask of Timer. 
You can program each TimerControlReg to enable or disable a specific timer and to control its mode of operation.

## TIMER_INT_STAT_GET
Get Timer Interrupt Status Register.
This register contains the interrupt status for Timer.

Value	Description
0x0	    Timer Interrupt is inactive
0x1	    Timer Interrupt is active

## TIMERS_INT_STAT_GET
Get Timers Interrupt Status Register.
Contains the interrupt status of all timers in the component. 
If a bit of this register is 0, then the corresponding timer interrupt is not active and the corresponding interrupt could be on either the timer_intr bus or the timer_intr_n bus, depending on the interrupt polarity you have chosen. 
Similarly, if a bit of this register is 1, then the corresponding interrupt bit has been set in the relevant interrupt bus. 
In both cases, the status reported is the status after the interrupt mask has been applied. 
Reading from this register does not clear any active interrupts.

Value	Description
0x0	    either timer_intr or timer_intr_n is not active after masking
0x1	    either timer_intr or timer_intr_n is active after masking.

## TIMERS_RAW_INT_STAT_GET
Get Timers Raw Interrupt Status Register.
The register contains the unmasked interrupt status of all timers in the component.
Value	Description
0x0	    either timer_intr or timer_intr_n is not active prior to masking
0x1	    either timer_intr or timer_intr_n is active prior to masking.

## TIMERS_EOI_APPLY
Timers End-of-Interrupt Register.
Reading this register returns all zeroes (0) and clears all active interrupts.

## TIMER_EOI_APPLY
Timer End-of-Interrupt Register.
Reading from this register returns all zeroes (0) and clears the interrupt from Timer.

## TIMER_COMP_VERSION_GET
Get Timers Component Version
Current revision number of the DW_apb_timers component.
Reset Value: 0x3230392A

For a detailed register map, please refer to:
https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_SPTIMER_summary.html