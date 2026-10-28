# Build Instructions

This repository builds a standalone AArch64 bare-metal image for Agilex 5 and Agilex 3 SoC FPGA platforms covered by this release guide.

Step-by-step build instructions are on a separate page for each host:

| Host | Page | Entry point |
|---|---|---|
| Linux | [BUILD_LINUX.md](BUILD_LINUX.md) | The top-level [Makefile](Makefile), which configures and drives CMake |
| Windows | [BUILD_WINDOWS.md](BUILD_WINDOWS.md) | VS Code with the Ashling Altera extension and local CMake presets |

## Scope

This document is the build-system reference for the repository. It covers
the settings both hosts share: toolchain prefix, build variables, output
artifacts, build modes, and the boot-integration helpers that ship with the
source.

For the board bring-up sequence from `make` to `SoCFPGA Bare-Metal >`, start
with [README.md](README.md).

The two build modes are OCRAM (on-chip RAM) and DDR (external memory).
The later-stage DDR flow uses TF-A (Trusted Firmware-A), where BL2
(second-stage boot loader) and BL31 (EL3 runtime firmware) hand off BL33 (the
bare-metal payload). The HPS (Hard Processor System) UART (serial console) is
used for runtime output.

---

## Platform build configurations

| Platform | OCRAM Release | DDR Release | OCRAM Debug | DDR Debug |
|---|---:|---:|---:|---:|
| `agilex5` | Yes | Yes | Yes | Yes |
| `agilex3` | Yes | Yes | Yes | Yes |

In this table, Release means `DEBUG=0`. The
[root README](README.md#supported-platforms-and-development-kits) has the
board steps. Agilex 5 and Agilex 3 DDR use the same TF-A and SD-card flow.
OCRAM on either kit: build the image, combine `baremetal.hex` with the SOF,
then program it.

Always pass `PLAT=agilex5` or `PLAT=agilex3`, plus `BUILD_MODE`, explicitly.
`PLAT` has no default: both the Makefile and CMake stop with an error when it
is missing or not one of these two values. `DEBUG` defaults to `0`.

---

## Toolchain Requirement

Both hosts use the Arm GNU Toolchain for the AArch64 GNU/Linux target.
Installation is described on the [Linux](BUILD_LINUX.md#2-install-the-tools)
and [Windows](BUILD_WINDOWS.md#2-install-the-tools) pages.

Expected compiler prefix:

```text
aarch64-none-linux-gnu-
```

Verify installation:

```bash
aarch64-none-linux-gnu-gcc --version
```

---

## Build Variables

The wrapper [Makefile](Makefile) accepts these primary variables. The Windows
CMake presets set the same values as CMake cache variables.

| Variable | Meaning | Supported Values |
|---|---|---|
| `PLAT` | Target platform for this release guide | `agilex5`, `agilex3` |
| `BUILD_MODE` | Memory placement and boot expectation | `OCRAM`, `DDR` |
| `DEBUG` | Debug or release build | `0`, `1` |
| `BUILD_DIR` | Make only. Output folder; overrides `build/<PLAT>/release` or `build/<PLAT>/debug` | Any folder path |
| `ATF_DIRECT_BOOT` | Passed to the compiler as a definition. No source file in this release reads it, so it has no effect; leave it at `0` | `0`, `1` |

---

## Build Output Layout

Build output is generated under:

```text
build/<PLAT>/release
build/<PLAT>/debug
```

Typical layout:

```text
build/
        <platform>/
                release/ or debug/
                        baremetal.elf
                        baremetal.bin
                        baremetal.hex
                        baremetal.dump
                        baremetal.map
```

Artifact generation is implemented through [cmake/bm_artifacts.cmake](cmake/bm_artifacts.cmake).

---

## Output Artifacts

| File | Description |
|---|---|
| `baremetal.elf` | Linked image used for symbols, inspection, and debugging |
| `baremetal.bin` | Raw binary image; the DDR TF-A flow in README packages this file as BL33 |
| `baremetal.hex` | Intel HEX image produced from the ELF |
| `baremetal.dump` | Disassembly generated from the ELF |
| `baremetal.map` | Linker map showing section placement and symbol resolution |

None of these files is a complete bootable SD-card image. A DDR board boot
also needs TF-A BL2/BL31 plus the board image and boot media described in the
[README bring-up flow](README.md#quick-start).

---

## Build Modes

`BUILD_MODE` changes both the linker script and the expected boot environment.

| Mode | Linker Script | Intended Use |
|---|---|---|
| `OCRAM` | [linker_ocram.ld](linker_ocram.ld) | On-chip-memory style bring-up where the image may perform more early platform initialization itself |
| `DDR` | [linker_ddr.ld](linker_ddr.ld) | Flows where the image runs after earlier firmware has already established DDR and essential platform state |

The mode selection is resolved in [CMakeLists.txt](CMakeLists.txt).

`BUILD_MODE` is a boot contract as well as a linker selection:

- An OCRAM image may own early clock, reset, pinmux, and UART setup. Agilex 5
  calls its PLL setup path before the console. The current Agilex 3 OCRAM
  branch does not call that same PLL setup path.
- A DDR image assumes preceding firmware established DDR, clocks, HPS
  handoff, pinmux/console routing, security state, and valid payload entry
  conditions before control reaches `_start`.

---

## Debug and Release Modes

| Mode | Compiler Behavior |
|---|---|
| `DEBUG=0` | Optimized build with `-O2` |
| `DEBUG=1` | Debug-oriented build with `-O0 -g` |

---

## Boot Integration Helpers

The customer-facing boot procedure lives in [README.md](README.md#quick-start).
This section describes the repository pieces used by that flow.

### `cmake/bm_boot.cmake`

`cmake/bm_boot.cmake` provides reusable TF-A build targets for a downstream
application. The current helper is intentionally limited to Agilex 5. Its
defaults include:

```text
BM_ATF_PLAT=agilex5
BM_BL33_BASE=0x80200000
```

It builds BL2/BL31 for SD boot, and builds `fiptool`. The
helper is useful when another CMake project consumes this repository, but it is
not a generic Agilex 3 recipe.

### `tools/sdimage_build.sh`

`tools/sdimage_build.sh` is the simple entry point for creating an SD image from
an existing `fip.bin`. It uses `tools/make_sdimage.sh` and `guestfish` to create
the partition table and place the FIP in the A2 boot partition.

The script runs on Linux. On Windows, run it in WSL 2 or on a Linux PC, as
described in [BUILD_WINDOWS.md](BUILD_WINDOWS.md#5b-ddr).

Default usage:

```bash
FIP=fip.bin OUT=sd_image.img SD_SIZE=128M A2_SIZE=1 \
sh tools/sdimage_build.sh
```

The A2 partition size is in MiB. `guestfish` must already be installed and available on
`PATH`. The variables can be overridden when a larger image or different output
name is needed.

### TF-A payload relationship

For the Agilex 5 DDR flow documented in README:

```text
BL2                  TF-A second-stage boot loader
BL31                 TF-A EL3 runtime firmware
baremetal.bin        BL33 / non-secure payload
PRELOADED_BL33_BASE  0x80200000
```

The DDR linker script uses `0x80200000` as the text origin, so the TF-A handoff
and the bare-metal image agree on the entry region.

### Board-specific image generation

The final HPS-enabled FPGA image is board-specific. The README shows the
`quartus_pfg` command that combines TF-A BL2 with the HPS debug SOF. Use the
GHRD and SOF for the kit you are programming. Agilex 3 uses `PLAT=agilex3`
and that kit's SOF. Do not reuse the Agilex 5 SOF file. OCRAM does not use
the TF-A BL2 hex; it combines `build/<PLAT>/release/baremetal.hex` with the
SOF instead. See [OCRAM bring-up](README.md#ocram-bring-up).

---

## Related Documents

1. [README.md](README.md): customer bring-up, boot flow, UART, and first smoke test.
2. [BUILD_LINUX.md](BUILD_LINUX.md): get the code and build on Linux.
3. [BUILD_WINDOWS.md](BUILD_WINDOWS.md): get the code and build on Windows, then boot from Windows.
4. [DOCUMENTATION.md](DOCUMENTATION.md): generated documentation and module index.
