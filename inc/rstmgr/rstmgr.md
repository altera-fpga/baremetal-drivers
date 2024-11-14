# Reset Manager

To use the reset manager, it must be opened to get a valid file descriptor.

The reset manager is set up as a read-modify-write interface on each of the major register banks. For whole register access, read the whole register block using the `IOCTL_RSTMGR_READ` operation. That register set should then be modified by the caller and written back to the hardware using the `IOCTL_RSTMGR_WRITE` operation.

Certain register bits are cleared by writing a '1' (Write 1 to Clear). This applies to the following functions:
- `rstmgr_set_stat()`
- `rstmgr_set_miscstat()`
- `rstmgr_set_hdskack()`
- `rstmgr_set_hdskall()`
- `rstmgr_set_dbgrstcmplt()`
- `rstmgr_set_hpsrstcmplt()`
 
The reset manager must be accessed while the processor is in secure mode (PRIVILEGE MODE).

More details can be found in the [Register Map](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_Reset_Mgr_summary.html)
