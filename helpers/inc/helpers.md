# Helpers

This folder contains utility and helper functions that support various specific usages and workflows not covered by the main drivers. These functions provide additional functionality and convenience for common tasks, aiding in the overall development process. The folder currently includes the following:

## mylibc
The source file mylibc.cpp provides stubs for libc functions so the baremetal environment behaves as expected. In particular, this source file sets up page tables as part of `_cpu_init_hook` during crt0.s as well as opening the UART and setting up the appropriate hooks so printf reaches the terminal. Other stubs are provided so libc skips certain features related to file systems and time.

## bridge_helper
The fabric bridge driver facilitates the interface between the HPS (Hard Processor System) subsystem and the soft logic implemented in the fabric. There are four bridges in the HPS: F2SDRAM, F2SOC, SOC2FPGA, and LWSOC2FPGA. This driver leverages the reset manager and system manager to manage the enable and disable sequences, ensuring proper reset flow for all bridges. All reset operations related to the bridges are managed within this helper functions folder.

### bridge_enable
It enables all of the four bridges.

### bridge_disable
It disables all of the four bridges.

### register_polling
The polling_register function continuously checks the specified register, using the provided bitmask to determine if the desired condition is met. It will poll the register until the condition is satisfied or the specified timeout period (ms) is reached. The assert parameter determines whether the function is looking for the condition to be true (asserted) or false (deasserted). The function requires a `timer_handle` to manage the timeout period. Note that it is only used internally for the bridge enable and disable function, and the timeout is set to 1 milli second by default.
