# NoC Probe Driver
This driver provides access to registers that probe the [system interconnect](https://www.intel.com/content/www/us/en/docs/programmable/814346/24-3-1/system-interconnect-and-firewalls-functional.html), particularly the [observation network](https://www.intel.com/content/www/us/en/docs/programmable/814346/24-3-1/observation-network.html).

The IOCTLs available correspond directly to individual registers documented in the [L4_NOC_PRB address map](https://www.intel.com/content/www/us/en/programmable/hps/agilex5/topics/addressblock_L4_NOC_PRB_summary.html). Please refer to the aforementioned documentation links for details. Each register in the address map has one `IOCTL_NOC_PROBE_GET_<register name>` (if marked RO or RW in the address map) and one `IOCTL_NOC_PROBE_SET_<register name>` (if marked RW or WO in the address map). The `noc_probe_ioctl` function will return 0 if the IOCTL is successful and -1 otherwise.

For example usage, please see the `test/simics/noc_probe/noc_probe_test.c` file.
