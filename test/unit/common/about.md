## About Unittest Common

Unittest common contains a handful of helpers that fill in libc calls for googletest that are particular to the baremetal use case.

### Key Linker Script Features
The linker script must define .preinit_array, .init_array, .ctors, and .dtors sections. Without these, the startup code doesn't have the information to initialize certain varaibles. Among these are class static member variables. This is key to how googletest discovers tests. For the code that does this, have a look at [gtest-internal.h line 1504](https://github.com/google/googletest/blob/a7f443b80b105f940225332ed3c31f2790092f47/googletest/include/gtest/internal/gtest-internal.h#L1504) in the googletest repo  and the corresponding assignment a few lines later.

### About Page Tables
The C/C++ runtime expects the MMU to be enabled. Code in mylibc calls the MMU driver to provide a set of identity tables (i.e. no translation) that prevents exceptions on unaligned access. Even the -mstrict-align compiler/linker flag does not handle all instructions requiring strict alignment, like mulitple load/store (ldp/stp).


