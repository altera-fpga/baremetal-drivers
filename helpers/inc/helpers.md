# Helpers

This folder contains utility and helper functions that support various specific usages and workflows not covered by the main drivers. These functions provide additional functionality and convenience for common tasks, aiding in the overall development process. The folder currently includes the following:

## mylibc
The source file mylibc.cpp provides stubs for libc functions so the baremetal environment behaves as expected. In particular, this source file sets up page tables as part of `_cpu_init_hook` during crt0.s as well as opening the UART and setting up the appropriate hooks so printf reaches the terminal. Other stubs are provided so libc skips certain features related to file systems and time.
