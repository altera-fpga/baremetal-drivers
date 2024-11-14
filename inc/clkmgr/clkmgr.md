# Clock Manager

To use the clock manager, it must be opened to get a valid file descriptor.

The clock manager is set up as a read-modify-write interface. For whole register access, read the whole register block using the `IOCTL_CLKMGR_READ` operation. That register set should then be modified by the caller and written back to the hardware using the `IOCTL_CLKMGR_WRITE` operation.

The clock manager consists of four blocks: `clkmgr`, `mainpllgrp`, `perpllgrp`, and `ctlgrp`. Each block provides set and get functions. The read-modify-write approach is applicable to each block access.

The clock manager must be accessed while the processor is in secure mode (PRIVILEGE MODE).

More details can be found in the [Register Map](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_Clock_Mgr_summary.html)