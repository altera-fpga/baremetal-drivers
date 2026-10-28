# Altera SoC FPGA Bare-Metal Software

## Overview

This repository is bare-metal software for the Hard Processor System (HPS)
on Agilex 5 and Agilex 3 SoC FPGA devices. It runs on the Arm Cortex-A cores
with no operating system. It includes startup code, peripheral drivers, a
serial command line, and small examples you can run on the board.

You need C and some experience with embedded software.

This guide uses two build modes:

- `DDR` runs from external memory. Trusted Firmware-A (TF-A) starts first and
  then jumps to this software. This mode includes the larger example set in
  `examples/CMakeLists.txt`.
- `OCRAM` places the image in on-chip RAM. Build that image, then program the
  SOF for your kit. This mode does not use TF-A or an SD card.

The serial console is the HPS UART in both modes.

**What this guide covers**

- Agilex 5 and Agilex 3 development kits. See the table below.
- The DDR path from build to the serial prompt, for both kits.
- The OCRAM path: build the OCRAM image and program the SOF.
- It does not include performance numbers or board wiring diagrams.

For a first try, use your kit with `BUILD_MODE=DDR` and follow the numbered
steps below in order.

## Supported Platforms and Development Kits

| Platform | Development Kit | Build Modes | Notes |
|---|---|---|---|
| `agilex5` | [Agilex 5 FPGA E-Series 065B Premium Development Kit](https://www.altera.com/products/devkit/po-3284/agilex-5-fpga-e-series-065b-premium-development-kit) (`DK-A5E065BB32AEA`) | `OCRAM`, `DDR` | DDR steps below. OCRAM: build, then program the SOF |
| `agilex3` | [Agilex 3 FPGA and SoC C-Series Development Kit](https://www.altera.com/products/devkit/po-3000/agilex-3-fpga-and-soc-c-series-development-kit) (`DK-A3W135BM16AEA`) | `OCRAM`, `DDR` | Same DDR steps, with `PLAT=agilex3`. OCRAM: build, then program the SOF |

Always pass `PLAT=agilex5` or `PLAT=agilex3`, and pass `BUILD_MODE`, on the
`make` line. `PLAT` has no default; the build stops with an error if it is
missing or not one of these two values.

## Quick Start

### Names in the commands

Replace each name below with your own path or value.

| Name | Replace it with |
|---|---|
| `/path/to/baremetal` | The folder where you cloned this repository |
| `/path/to/tf-a` | The folder where you cloned TF-A (step 4) |
| `/path/to/ghrd_a5ed065bb32ae4s_hps_debug.sof` | The HPS debug SOF for your kit (step 6) |
| `/dev/<sd-card-device>` | The SD card device on your Linux PC, such as `/dev/sdX` |
| `<PLAT>` | `agilex5` or `agilex3` |

### 1. Install the prerequisites

On a Linux PC, install:

- CMake 3.20 or later, and GNU Make
- an AArch64 GNU toolchain, with `aarch64-none-linux-gnu-gcc` and
  `aarch64-none-linux-gnu-objcopy` on `PATH`
- a host `gcc`, and the OpenSSL development package (`libssl-dev` or
  `openssl-devel`). TF-A needs these to build `fiptool`
- `git`
- Quartus Prime Programmer, and `quartus_pfg` (Programming File Generator)
- `guestfish`, from the libguestfs package, to build the SD card image
- permission to write the SD card, for example `sudo`
- a serial terminal: `minicom`, `screen`, PuTTY, or Tera Term
- `bash`, used by `tools/sdimage_build.sh`
- the TF-A source, and the HPS debug SOF for your kit

Check that the compiler is available:

```bash
aarch64-none-linux-gnu-gcc --version
```

You should see a version number. If the shell says the command is not found,
add the toolchain `bin` directory to `PATH`.

This Quick Start uses a Linux PC. To build and boot from a Windows PC, follow
[BUILD_WINDOWS.md](BUILD_WINDOWS.md) instead. The Linux build on its own,
including how to get the code, is in [BUILD_LINUX.md](BUILD_LINUX.md). The
full list of build options is in [BUILD.md](BUILD.md).

### 2. Select the platform and build mode

Use the `PLAT` value that matches your target:

```text
Agilex 5: PLAT=agilex5
Agilex 3: PLAT=agilex3
```

For the DDR steps below, on either kit, use:

```text
BUILD_MODE=DDR
```

OCRAM uses the shorter steps in [OCRAM bring-up](#ocram-bring-up).

### 3. Build the bare-metal software

From the root of this repository:

```bash
cd /path/to/baremetal
make PLAT=agilex5 BUILD_MODE=DDR      # Agilex 5
make PLAT=agilex3 BUILD_MODE=DDR      # Agilex 3
```

The build writes the files to:

```text
build/<PLAT>/release/
```

The two files you need next are:

```text
baremetal.elf   ELF file, for debug
baremetal.bin   raw binary, loaded by TF-A
```

The build is done when `make` finishes with no error and
`build/<PLAT>/release/baremetal.bin` is a new file. An old file from an
earlier build does not count.

### 4. Build TF-A and pack the DDR image

Do this step for a `DDR` build on either kit. Finish step 3 first. Skip it
for `OCRAM`.

Build TF-A's BL2 and BL31, then build the host packaging tool:

- BL2, the second-stage loader
- BL31, the runtime firmware
- `fiptool`, the program that packages BL31 and `baremetal.bin` into `fip.bin`

Download TF-A from the public Altera repository and stay on the
`socfpga_v2.14.0` branch:

```bash
git clone -b socfpga_v2.14.0 \
    https://github.com/altera-opensource/arm-trusted-firmware \
    /path/to/tf-a
```

To pick up a newer TF-A later, run `git pull` in that tree. If your project
already downloads TF-A through [`cmake/bm_boot.cmake`](cmake/bm_boot.cmake),
build that copy. Do not mix it with a second TF-A tree.

`CROSS_COMPILE` must match the toolchain from step 1. Without it, TF-A looks
for a different compiler name. `make realclean` deletes old TF-A build files
in that tree:

```bash
cd /path/to/tf-a
make realclean
make CROSS_COMPILE=aarch64-none-linux-gnu- \
    PLAT=agilex5 \
    SPD=none \
    PRELOADED_BL33_BASE=0x80200000 \
    bl2 bl31 fiptool
```

Still in `/path/to/tf-a`, pack `baremetal.bin` into `fip.bin`.
`--nt-fw` is this software. `--soc-fw` is BL31:

```bash
./tools/fiptool/fiptool create \
    --soc-fw build/agilex5/release/bl31.bin \
    --nt-fw /path/to/baremetal/build/agilex5/release/baremetal.bin \
    fip.bin
```

Still in `/path/to/tf-a`, convert BL2 to HEX. Step 6 needs this file:

```bash
aarch64-none-linux-gnu-objcopy -v \
    -I binary \
    -O ihex \
    --change-addresses 0x0 \
    build/agilex5/release/bl2.bin \
    build/agilex5/release/bl2.hex
```

This step is done when both of these files exist:

- `/path/to/tf-a/fip.bin`
- `/path/to/tf-a/build/agilex5/release/bl2.hex`

The DDR linker script puts this software at `0x80200000`. That is the same
address passed as `PRELOADED_BL33_BASE` above. Keep the two the same.

Agilex 3 DDR uses these same commands. Change every `agilex5` in this step
to `agilex3`: the TF-A `PLAT`, the TF-A build directory, and the
`baremetal.bin` path. Use the HPS debug SOF for the Agilex 3 kit in step 6.
Do not reuse the Agilex 5 SOF file.

### 5. Create the SD-card image

This repository includes a small script that puts `fip.bin` in the A2 boot
partition of an SD card image. Install `guestfish` first. On most Linux
systems it comes from the `libguestfs-tools` package.

From the bare-metal repository:

```bash
cd /path/to/baremetal
FIP=/path/to/tf-a/fip.bin \
OUT=sd_image.img \
SD_SIZE=128M \
A2_SIZE=1 \
sh tools/sdimage_build.sh
```

`A2_SIZE` is in MiB. The command above makes a 1 MiB A2 partition and writes
`sd_image.img` in the current directory. If `guestfish` or `fip.bin` is
missing, the script prints an error and stops.

Copy the image to a micro-SD card. On Linux, one way is:

> **Warning:** `dd` erases the whole device you name. Make sure
> `/dev/<sd-card-device>` is the SD card, not a hard disk. Run `lsblk` with
> the card out, then again with the card in, and use the name that appears.

```bash
sudo dd if=sd_image.img of=/dev/<sd-card-device> bs=4M status=progress conv=fsync
```

### 6. Create the FPGA programming file

An SOF is the file Quartus Prime Programmer loads into the FPGA. Download the
HPS debug SOF from the public GHRD (Golden Hardware Reference Design) for
your kit: the
[Agilex 5 E-Series GHRD](https://altera-fpga.github.io/)
or the Agilex 3 GHRD for that kit. Pick the GHRD release that matches your
Quartus Prime version. The command below uses the Agilex 5 file name
`ghrd_a5ed065bb32ae4s_hps_debug.sof`. A different kit or GHRD release can use
another file name for the same kind of HPS debug SOF.

Combine TF-A BL2 with that SOF:

```bash
cd /path/to/baremetal
quartus_pfg -c \
    -o hps_path=/path/to/tf-a/build/agilex5/release/bl2.hex \
    /path/to/ghrd_a5ed065bb32ae4s_hps_debug.sof \
    fsbl_bm.sof
```

This writes `fsbl_bm.sof` in the current directory. You load it onto the
board in step 9.

For Agilex 3, use that kit's HPS debug SOF, and point `hps_path` at
`/path/to/tf-a/build/agilex3/release/bl2.hex`. Do not reuse the Agilex 5 SOF.

### 7. Prepare the development kit

#### Agilex 5 (`DK-A5E065BB32AEA`)

Use the HPS Expansion Board for the HPS UART and the micro-SD card. Connect
the UART cable to your PC, and insert the micro-SD card from step 5.

Connector names and switch settings are in the
[Agilex 5 Premium Development Kit User Guide](https://docs.altera.com/r/docs/814550/current/agilex-5-fpga-e-series-065b-premium-development-kit-user-guide/overview).

#### Agilex 3 (`DK-A3W135BM16AEA`)

The development kit provides:

- HPS UART on `J2`
- HPS micro-SD on `J3`
- USB-PD Type-C power on `J8`
- board power switch `SW3`

Connector names and switch settings are in the
[Agilex 3 Development Kit User Guide](https://docs.altera.com/r/docs/851698/current/agilextm-3-fpga-and-soc-c-series-development-kit-user-guide/overview).

### 8. Open the serial console

Use these settings:

```text
115200 baud
8 data bits
no parity
1 stop bit
no flow control
```

On Linux, the new USB serial port is usually `ttyUSB*` or `ttyACM*`. Find it with:

```bash
dmesg | grep -E 'tty(USB|ACM)'
```

On Windows, open Device Manager and look for the new COM port.

### 9. Boot the board and check the prompt

A power cycle clears this volatile FPGA configuration. If the selected reset
procedure also clears it, program `fsbl_bm.sof` again before booting. With the kit ready
(step 7) and the serial window open (step 8):

1. Insert the micro-SD card from step 5.
2. Power on the board.
3. Program `fsbl_bm.sof` with Quartus Prime Programmer over JTAG. When
   programming finishes, TF-A BL2 starts and loads the rest of the software
   from the SD card.

Keep the board powered during this check. After a power cycle, or a reset that
clears the FPGA configuration, program `fsbl_bm.sof` again.

TF-A prints its own lines first. Then this software prints a banner and a
prompt. The time, date, and commit are from your build:



```text
Welcome to SoCFPGA Baremetal World for Agilex5 Platform
Built: <time> <date>
Commit: <commit>
Running on Core <n>
Type 'help' for commands.
SoCFPGA Bare-Metal >
```

On Agilex 3 the first line says Agilex3. The boot is good when you see
`SoCFPGA Bare-Metal >`.

On a DDR boot the order is: Boot ROM, TF-A BL2, TF-A BL31, then
`baremetal.bin`, then this prompt.

If the prompt does not appear, write down the last line you saw and use
[Troubleshooting](#troubleshooting):

| Last line you saw | What to check |
|---|---|
| Nothing | UART cable, baud rate, or the SOF was not programmed |
| TF-A text, but no `Welcome to ...` line | `baremetal.bin` in `fip.bin`, or the load address `0x80200000` |
| The welcome line, but no prompt | Startup stopped. Rebuild and check `PLAT` and `BUILD_MODE` |

### 10. Try a few safe commands

Type these at the prompt. They only print text or read the CPU. They do not
change the board.

| Command | What you should see |
|---|---|
| `help` | A `Commands:` list, then an `Example Applications:` list. `hello_selftest` is in the second list. |
| `core` | `Currently running on Core <n>` |
| `mpidr` | `MPIDR_EL1 = 0x` and 16 hex digits |
| `el` | `Current EL: <n>` (the CPU exception level) |
| `hello_selftest` | `Hello, Baremetal World!`, then `RESULT : command completed  -  CHECK DETAILED OUTPUT` |

This check is good when each command prints its line and the prompt comes
back. If a command prints nothing and the prompt does not come back, check
the UART cable and steps 7 to 9.

Many examples print a box around their output. The last line looks like
`RESULT : command completed  -  CHECK DETAILED OUTPUT`, or
`RESULT : Step 1 of 2 completed  -  CHECK DETAILED OUTPUT`.
That line only means the command returned. It does not mean the test passed.
The module guide tells you which lines mean pass.

`help` lists only the examples that were built into your image. See
[Which example commands are built](#which-example-commands-are-built).
Before you run a peripheral test, read that module's guide and connect the
hardware it needs.

Do not use these for a first check. They erase or change the board:

- ECC error injection
- reset commands
- `memwrite`, which writes whatever address you type

`sdmmc_selftest` overwrites the first two blocks of the SD card you booted
from. See the [SD/MMC guide](api/sdmmc/README.md).

`exit` stops the shell. The prompt does not come back. Reset the board and
program the SOF again (step 9).

### 11. Add your own command

The shortest way to run your own code is to add a command, the same way
`hello_selftest` does
([`examples/hello/hello_selftest.c`](examples/hello/hello_selftest.c)).
Add a new folder under `examples/`, for example `examples/my_app/my_app.c`:

```c
#include <stdio.h>
#include "console_api.h"
#include "example_register.h"

static void cmd_my_app(const char *args)
{
	(void)args;   /* text typed after the command name, if any */
	printf("my_app ran\n");
}

static void register_my_app(void)
{
	cli_register_command("my_app", cmd_my_app);
}

APP_REGISTER(register_my_app)
```

A `DDR` build gathers example `.c` files, then applies the exclusions in
[`examples/CMakeLists.txt`](examples/CMakeLists.txt). Rebuild
with the step 3 command, then repeat steps 4 to 6 and boot again. An `OCRAM`
build compiles only a fixed list. Add your file to that list in
[`examples/CMakeLists.txt`](examples/CMakeLists.txt), rebuild, and program the
SOF again.

After you boot again, `help` shows `my_app` under `Example Applications:`.
The description for a new command defaults to `run self-test`. Typing `my_app` prints
`my_app ran`, then `RESULT : command completed  -  CHECK DETAILED OUTPUT`.
How to register a command, how arguments work, and how many commands you can
add are in the [Console and CLI guide](api/console/README.md).

## OCRAM bring-up

`OCRAM` uses the same kits, UART settings, and Programmer step as DDR. It
does not use TF-A, `fip.bin`, or the SD card.

1. Build the image:

```bash
cd /path/to/baremetal
make PLAT=agilex5 BUILD_MODE=OCRAM
make PLAT=agilex3 BUILD_MODE=OCRAM
```

Use one of those commands, matching your kit. The build is done when `make`
finishes with no error and `build/<PLAT>/release/baremetal.elf` is a new file.

The same build also writes `build/<PLAT>/release/baremetal.hex`.

2. Combine `baremetal.hex` with the HPS debug SOF for your kit (see step 6
   for where to get it). This is the step 6 command with the OCRAM image in
   place of TF-A BL2:

```bash
cd /path/to/baremetal
quartus_pfg -c \
    -o hps_path=build/agilex5/release/baremetal.hex \
    /path/to/ghrd_a5ed065bb32ae4s_hps_debug.sof \
    ocram_bm.sof
```

   For Agilex 3, use `build/agilex3/release/baremetal.hex` and that kit's HPS
   debug SOF.

   `baremetal.hex` is the OCRAM image in Intel HEX, linked at address 0. This
   is the same `hps_path` form as step 6, with the OCRAM image in place of
   TF-A BL2. This repository's release check did not run `quartus_pfg` and did
   not program a board. Confirm this step on your kit before you rely on it.

3. Prepare the kit and open the serial console, as in steps 7 and 8. You do
   not need the micro-SD card from step 5.
4. Program `ocram_bm.sof` with Quartus Prime Programmer. When programming
   finishes, this software starts from on-chip RAM. TF-A does not print its
   banner first.

The boot is good when you see `SoCFPGA Bare-Metal >`. On Agilex 3 the welcome
line says Agilex3. Then try the safe commands in step 10. `help` lists only
the small OCRAM example set.

Agilex 5 OCRAM locks the PLLs and then sets the UART from the measured clock.
Agilex 3 OCRAM does not run that PLL setup. It programs the UART for 115200
baud assuming the 100 MHz clock in
`platform/agilex3/include/platform_def.h` (`HPS_PERIP_UART_CLK`). If that
clock is not already 100 MHz, the console will not be 115200.

After a power cycle, program `ocram_bm.sof` again.

## OCRAM and DDR

`BUILD_MODE` chooses more than where the image is linked. It also chooses
what must already be set up before this software starts.

| Build mode | When to use it | What must already be ready |
|---|---|---|
| `OCRAM` | Early board checks | This software does more of the early setup itself |
| `DDR` | Normal run after TF-A | DDR is ready before this software starts |

In the DDR steps in this README, TF-A sets that up, then jumps to this software.

### Who sets up each part

| Item | OCRAM | DDR |
|---|---|---|
| DDR | Not used. The image runs from on-chip RAM | Ready before this software starts |
| Clocks | Agilex 5 sets up its own PLLs. Agilex 3 does not. Both set the default interconnect clock dividers again | TF-A sets the PLLs. This software sets the default interconnect clock dividers again at startup |
| Pins and UART | You may need extra early setup | Must already work when this software starts |
| Reset | This software may reset more blocks itself | The peripherals you use should already be out of reset |
| CPU exception level | Depends on how you boot | Set by TF-A |
| Where the image is placed | OCRAM linker script | DDR linker script, entry at `0x80200000` |

Agilex 5 OCRAM setup and Agilex 3 OCRAM setup are not the same. The platform
code keeps them separate.

### DDR addresses used by this software

Some examples use fixed DDR addresses. Keep your own buffers out of these
ranges:

| Range | Used by |
|---|---|
| from `0x80000000`, below this image | TF-A BL31. It stays in memory while the board is running. On Agilex 5, TF-A reserves memory up to `0x82000000` |
| `0x80200000`-`0x812FFFFF` | This image. Code starts at `0x80200000`. Data, BSS, and stack start at `0x80300000` ([`linker_ddr.ld`](linker_ddr.ld)) |
| below `0x82000000` on Agilex 5 | TF-A rejects mailbox buffers in this range. See the [mailbox guide](api/mailbox/README.md). On Agilex 3 the same limit is `0x800F0000` |
| `0x82100000` | `mailbox_selftest` response buffer |
| `0x82100400`-`0x8210053F` | SEU command and response buffers. Used when the SEU module starts |
| `0x83000000`-`0x83FFFFFF` | `ddr_selftest`. This test overwrites the range |
| `0x83000000`, `0x83400000` | FCS input and output buffers. `fcs_api_open_session()` and `fcs_api_get_random_number()` write the response at `0x83400000` |
| `0x83800000` | `fcs_selftest` provisioning-data buffer |
| `0x90000000`, `0xA0000000` | `iossm_demo` |
| `0xC0000000` | Do not run `bridge_selftest loopback` on Agilex 5 or Agilex 3. Its default address overlaps DDR on both. See the [bridge guide](api/bridge/README.md) |

### OCRAM addresses used by this software

An `OCRAM` build has no TF-A, so none of the TF-A ranges above apply. The
[`linker_ocram.ld`](linker_ocram.ld) script places the image in on-chip RAM
from `0x00000000`. Keep your own buffers out of these ranges:

| Range | Used by |
|---|---|
| `0x00000000`-`0x0003FFFF` | Code and read-only data (`.text`). The build stops if the code does not fit. The `__text_end` symbol in `baremetal.map` shows how much is used |
| `0x00040000` upward | Initialized data (`.data`), then zeroed data (`.bss`). `__ebss` in `baremetal.map` marks the end |
| from `__ebss` up to `0x0007EFFF` | Free space, then the stack. The stack starts at `0x0007F000` (`_stack_top`) and grows down. Nothing checks the stack size at run time, so leave room below `0x0007F000` |
| `0x0007F000`-`0x0007FFFF` | Reserved for the clock handoff data from the Secure Device Manager. The platform clock code reads it at `0x0007F000` |
| 16 KB inside `.bss`, Agilex 5 only | `ddr_selftest` fallback test buffer. Used when DDR initialization is not supported. The test overwrites it |
| `0x83000000`-`0x83FFFFFF`, Agilex 5 only | `ddr_selftest`, after it initializes DDR itself. This test overwrites the range |

Agilex 3 `OCRAM` builds do not include `ddr_selftest` and do not use DDR.

### Which example commands are built

A module guide may name a test command. That command is in your image only
if [`examples/CMakeLists.txt`](examples/CMakeLists.txt) builds it:

| Build | Commands included |
|---|---|
| `OCRAM`, `agilex5` | `hello_selftest`, plus the DDR, GIC, and timer self-tests |
| `OCRAM`, `agilex3` | `hello_selftest`, plus the GIC and timer self-tests. `ddr_selftest` is omitted because this image does not initialize DDR before that test writes `0x83000000` |
| `DDR`, `agilex5` or `agilex3` | Every example except the performance self-test |

If a guide names a command and `help` does not list it, that build does not
include it.

## What runs after TF-A jumps here

1. `_start` in `src/startup.S` sets up the CPU and the stack.
2. `crt0_init()` clears BSS and copies initialized data.
3. `main()` does the rest of the setup that belongs to this software.
4. The examples register their commands.
5. The shell starts and prints `SoCFPGA Bare-Metal >`.

If you can see TF-A text but not this prompt, check `baremetal.bin`, the
address `0x80200000`, and DDR before you debug a single driver.

## Module guides

Each module has a guide at `api/<module>/README.md`. The guide says what the
module does, what you need before you call it, the order of calls, and how to
read the example command.

| Module | Guide | What it is for |
|---|---|---|
| HPS-to-FPGA Bridge | [`bridge`](api/bridge/README.md) | Opens a handle on one bridge and enables, disables, pauses or resumes it. |
| CCU | [`ccu`](api/ccu/README.md) | Reads the coherency unit's identity and uncorrected-error status, and flushes enabled L3 tag/data arrays. CPU and per-buffer cache maintenance remain separate. |
| Clock Manager | [`clk_mngr`](api/clk_mngr/README.md) | Reports the frequencies of supported peripheral clocks and reads or writes the interconnect divider fields. |
| ComboPHY | [`combophy`](api/combophy/README.md) | Reads two identification registers from the Combo PHY: its version and its feature set. |
| Console and CLI | [`console`](api/console/README.md) | Provides the interactive shell: a prompt, line editing, tab completion, the built-in commands, and the registration interface that lets any module add a command of its own. |
| CRC | [`crc`](api/crc/README.md) | Computes a checksum over a buffer, and validates a buffer against an expected size and an expected checksum. |
| DMA | [`dma`](api/dma/README.md) | Presents a memory-to-memory copy interface -- synchronous and asynchronous -- and builds the descriptor chains internally. |
| ECC | [`ecc`](api/ecc/README.md) | Enables ECC on the protected memory blocks, reports and counts single-bit and double-bit errors, and injects test errors so an application's error-handling path can be exercised deliberately. |
| FCS (integration blocked) | [`fcs`](api/fcs/README.md) | Reads device identity values, opens and closes a cryptographic session, obtains random numbers from the device's generator, and reads provisioning data. |
| GIC | [`gic`](api/gic/README.md) | Initializes the interrupt controller, attaches a handler to an interrupt, enables or disables it, and sends software-generated interrupts between cores. |
| GPIO (known limitations) | [`gpio`](api/gpio/README.md) | Opens one pin, sets its direction, and reads or writes it by polling. In this release the public header differs from the implementation and interrupt callbacks are not delivered; read the guide before use. |
| I2C | [`i2c`](api/i2c/README.md) | Operates one I2C bus as a controller (master), targeting one device address at a time. |
| I3C | [`i3c`](api/i3c/README.md) | Opens an I3C controller, reports its capabilities, and performs legacy I2C transfers, private I3C transfers, or a raw command-queue operation. |
| IOSSM | [`iossm`](api/iossm/README.md) | Opens a memory-controller instance, enables or disables ECC on external memory, reads and clears its error status, and can inject single-bit and double-bit errors at a chosen external-memory address. |
| SDM Mailbox | [`mailbox`](api/mailbox/README.md) | Sends a Secure Device Manager command and waits for its response, which the firmware layer places in a caller-supplied memory buffer. |
| MMU | [`mmu`](api/mmu/README.md) | Reports whether address translation is currently enabled at a given privilege level, and builds a block translation-table entry from a physical address and a set of attributes. |
| NoC Firewall | [`noc_firewall`](api/noc_firewall/README.md) | Reads and writes a peripheral's interconnect security policy, and offers a convenience call that opens a peripheral to non-secure masters. |
| NoC Probe | [`noc_probe`](api/noc_probe/README.md) | Reads the probe's identity, enables its error logger, reports whether an error has been latched, reads the latched details and clears them. |
| Performance Monitoring | [`perf`](api/perf/README.md) | Timestamps code, converts elapsed counter ticks into microseconds or nanoseconds, computes throughput and latency figures from a byte count and an elapsed time, and records results in a small in-memory log that can be dumped from the console. |
| Reboot Manager | [`reboot_mngr`](api/reboot_mngr/README.md) | Requests a cold or a warm system reboot, with an optional callback that runs immediately before the request is issued so an application gets one last chance to flush state. |
| Reset Manager | [`rst_mngr`](api/rst_mngr/README.md) | Applies a reset pulse -- assert, delay, deassert -- to a peripheral, and reports whether a peripheral is currently held in reset. |
| SD/MMC | [`sdmmc`](api/sdmmc/README.md) | Initializes an SD card, reports its capacity in 512-byte blocks, and reads or writes runs of blocks synchronously. |
| SEU | [`seu`](api/seu/README.md) | Reads the upset statistics and the error queue the Secure Device Manager maintains, and can inject test upsets so that an application's error-handling path can be exercised deliberately. |
| SMMU | [`smmu`](api/smmu/README.md) | Enables or disables the system memory management unit using a translation configuration built into the driver, reports whether it is enabled, and provides raw register access for diagnosis. |
| SPI | [`spi`](api/spi/README.md) | Opens one SPI instance, configures its bit rate, transfer mode and chip-select, and performs blocking full-duplex transfers. |
| Timer | [`timer`](api/timer/README.md) | Opens one timer instance, starts and stops it, and reads its down-counter value in microseconds. |
| UART | [`uart`](api/uart/README.md) | Initializes the console UART and provides polled character-at-a-time send and receive, plus `printf` routed to the serial port. |

## Public API and low-level driver reference

The module guides above explain how to use the public APIs. Natural Docs
builds a second reference from the source comments. It has two groups. Public
API lists the functions under `api/`. Technical Driver Reference lists the
functions, registers, types and notes under `drivers/`.

Natural Docs 2 is not included. The `make docs` command is in
[DOCUMENTATION.md](DOCUMENTATION.md#public-api-and-low-level-driver-reference).
You can also read the public headers and the driver source files directly.

## Checklist before you add your own code

- `PLAT` matches your kit.
- `BUILD_MODE` matches how you boot.
- For DDR, `fip.bin` contains the `baremetal.bin` from that same build, TF-A
  has already set up DDR, and TF-A loads this software at `0x80200000`.
- For OCRAM, you programmed the SOF for that OCRAM build. Do not boot it from
  the DDR `fip.bin`.
- The HPS UART works, and the pins, clocks, and resets match your board.

## Troubleshooting

| What you see | What to check |
|---|---|
| Compiler not found | Install the AArch64 toolchain and add its `bin` directory to `PATH` |
| The build stops on a file under `examples/` | A `DDR` build includes every example except the performance self-test. Open the failing module's guide. The [GPIO guide](api/gpio/README.md) is one example |
| TF-A looks for `aarch64-none-elf-gcc` or `aarch64-linux-gnu-gcc` | Add `CROSS_COMPILE=aarch64-none-linux-gnu-` on the TF-A `make` line (step 4) |
| `fiptool` fails to build | Install a host `gcc` and the OpenSSL development package (step 1) |
| The output is for the wrong platform | Check `PLAT` and `BUILD_MODE`, then rebuild. `make clean` deletes all of `build/`, including other platforms |
| `fiptool` cannot find the payload | Check the `--nt-fw` path. `build/<PLAT>/release/baremetal.bin` must exist |
| `guestfish` is not found | Install libguestfs and put `guestfish` on `PATH` |
| The SD card does not boot | Check that `fip.bin` is the one you just built, and that you programmed `fsbl_bm.sof` |
| TF-A prints, but the prompt does not | Check address `0x80200000`, DDR, and the `baremetal.bin` inside `fip.bin` |
| No UART output | Check the HPS UART connector, the COM or TTY port, the cable, and 115200 8-N-1 |
| A command from a module guide is missing in `help` | That build does not include it. See [Which example commands are built](#which-example-commands-are-built) |
| The shell stops after `exit` | That is what `exit` does. Reset the board and program the SOF again (step 9) |
| `help` works, but a self-test fails | Read that module's guide. The test may need a cable, a card, or it may change the board |

## More documents

- [BUILD_LINUX.md](BUILD_LINUX.md): get the code and build on Linux
- [BUILD_WINDOWS.md](BUILD_WINDOWS.md): get the code, build, and boot from Windows
- [BUILD.md](BUILD.md): toolchains, CMake and Make options, and build output
- [DOCUMENTATION.md](DOCUMENTATION.md): list of module guides and short forms of names
- [RETURN_VALUES.md](RETURN_VALUES.md): how to read `0`, a negative error code, and output arguments
- `api/<module>/README.md`: one guide per module, listed above

Official Altera manuals for the HPS hardware:

- [Agilex 5 Hard Processor System Technical Reference Manual](https://docs.altera.com/r/docs/814346/current)
- [Hard Processor System Component Reference Manual: Agilex 5 SoCs](https://docs.altera.com/r/docs/813752/current)
- [Hard Processor System Technical Reference Manual: Agilex 3 SoCs](https://docs.altera.com/r/docs/848530/current)

## License

Altera code in this repository is under the MIT-0 license. See [LICENSE](LICENSE).

Some files are under a different license. The DDR bring-up sources are BSD-3-Clause, and three headers include Amazon Common IO code under MIT. See [THIRD_PARTY_NOTICES](THIRD_PARTY_NOTICES).
