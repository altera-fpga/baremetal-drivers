# Documentation Map

This page indexes the per-module guides and the common terminology used across
this repository.

For first-time board bring-up, start with [`README.md`](README.md). It contains
the DDR flow for Agilex 5 and Agilex 3, from the build through TF-A packaging,
SD-image creation, UART setup, and the first CLI check. It also contains the
OCRAM flow: build the OCRAM image, then program the SOF.

## Where to start

| If you want to | Read |
|---|---|
| Build and boot the software on a development kit | [`README.md`](README.md) |
| Build on Linux | [`BUILD_LINUX.md`](BUILD_LINUX.md) |
| Build on Windows | [`BUILD_WINDOWS.md`](BUILD_WINDOWS.md) |
| Change build variables, toolchains, or inspect artifacts | [`BUILD.md`](BUILD.md) |
| Use one peripheral from your own application | The module guide in the index below |
| Understand a return value such as `0`, `-EINVAL`, `-ENOSYS`, or a module-specific status | [`RETURN_VALUES.md`](RETURN_VALUES.md), then that module's **Return values and error handling** section |

## Release documents

| Document | Purpose |
|---|---|
| [`README.md`](README.md) | Customer entry point: supported kits, build, TF-A/SD bring-up, UART, CLI, OCRAM/DDR and troubleshooting. |
| [`BUILD.md`](BUILD.md) | Build-system reference, build variables, output artifacts and reusable boot helpers. |
| [`BUILD_LINUX.md`](BUILD_LINUX.md) | Get the code and build on a Linux PC. |
| [`BUILD_WINDOWS.md`](BUILD_WINDOWS.md) | Get the code, build with VS Code and Ashling, and boot from a Windows PC. |
| [`RETURN_VALUES.md`](RETURN_VALUES.md) | How to read a call's return value, output parameters, and the errno-style and module-specific codes these APIs use. |
| `api/<module>/README.md` | Per-module integration guide. Indexed below. |
| [`middleware/README.md`](middleware/README.md) | Middleware-layer implementation overview. |
| [`LICENSE`](LICENSE) | MIT-0 terms for Altera code. |
| [`THIRD_PARTY_NOTICES`](THIRD_PARTY_NOTICES) | BSD-3-Clause DDR sources and the Amazon Common IO MIT notices. |
| [`SECURITY.md`](SECURITY.md) | How to report a security issue. |

## Module guides

Each module guide focuses on using that module: prerequisites, call sequence,
examples, constraints, and troubleshooting when the source provides enough
evidence for those sections.

Complementary references:

| Document | Role |
|---|---|
| `api/<module>/README.md` | Task-oriented module integration guidance |
| Natural Docs | Public API declarations, driver details, and an [API guide index](docs/reference/APIGuideIndex.txt) |
| [`README.md`](README.md) | Common build, boot, platform, UART and CLI guidance |

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

Natural Docs scans source comments under `api/` into **Public API** and comments
under `drivers/` into **Technical Driver Reference**. The **Guides and Getting Started** area
comes from standalone reference text under `docs/reference/`. The module README
guides explain how to use an API in an application; generated function pages
provide its declaration, parameters and source-comment reference.

| | Natural Docs reference | Module guide |
|---|---|---|
| Answers | What does this API or driver function do? | How do I use the public API? |
| Source | Comments in `api/` and `drivers/` | `api/<module>/README.md` |
| Contains | Public functions, plus low-level functions, registers, types, parameters, return values and implementation notes | Call sequence, flow chart, examples, constraints and troubleshooting |

The generated reference is optional for API users. To generate it, install Natural
Docs 2 (not included in this repository) and run `make docs` from the repository
root. Natural Docs must be on `PATH`, or set `ND` to the executable. The project
configuration is `docs/ndconfig/Project.txt`, and the HTML is written to
`docs/naturaldocs/html/`. Open `index.html` in that directory with a web browser.

[docs/TERMINOLOGY.md](docs/TERMINOLOGY.md) lists published Altera and Arm spellings and their sources.

The generated reference starts with an overview and a **Guides and Getting Started**
menu. Its API guide index links the development modules to their public API
symbols and module READMEs. Function topics come from source comments in
`api/` and `drivers/`.

If Make is unavailable, run the generator directly from the repository root:

```bash
NaturalDocs docs/ndconfig
```

Use the executable path supplied by your existing Natural Docs installation.
The configuration format is `2.4 (Development Release 2)`; confirm your tool
accepts that configuration before publishing its output.

## Generating the API reference

From the repository root, with Natural Docs 2 on `PATH` or with `ND` set to
the executable:

```bash
make docs ND=/path/to/NaturalDocs
```

Open `docs/naturaldocs/html/index.html`. Check the landing page, module
navigation, symbol search, prototypes and type fields. Generate the HTML from
the same source tree you are reading. The menu names are Public API, Guides
and Getting Started, and Technical Driver Reference.

## Interpreting hardware checks

The module hardware-check sections describe board procedures, required
attachments and command pass criteria. Each result applies to the operations
and configuration exercised. A skipped phase adds no coverage, and a successful
control or smoke command alone does not demonstrate peripheral data transfers.
These procedures do not publish a qualification matrix for every board,
bitstream, firmware version or operating condition.

## Glossary

Platform terminology used across these documents.

| Term | Meaning |
|---|---|
| A2 partition | The SD card partition of type `0xA2` that holds `fip.bin`; in the flow in README.md, TF-A BL2 loads the FIP from it |
| APB | Advanced Peripheral Bus, the Arm low-speed register bus used by peripherals such as SPI |
| ATF | Arm Trusted Firmware, used interchangeably with TF-A in this repository |
| AXI | Advanced eXtensible Interface, the Arm high-performance bus protocol used by the bridges and DMA |
| BL2 | Second-stage boot loader in the TF-A boot chain |
| BL31 | EL3 runtime firmware in the TF-A boot chain |
| BL33 | The non-secure payload the TF-A boot chain hands control to |
| BSS | The zero-initialized data section of a program, cleared at startup |
| CCU | Cache Coherency Unit, the block that keeps HPS caches coherent with other masters |
| CLI | Command-Line Interface |
| CRC | Cyclic Redundancy Check |
| DAIF | The Arm processor interrupt-mask bits (Debug, SError, IRQ, FIQ); interrupts are delivered only when unmasked |
| DDR | Double Data Rate external SDRAM attached to the HPS memory controller |
| DMA | Direct Memory Access, a controller that moves data without CPU load/store instructions |
| ECC | Error-Correcting Code |
| FIP | Firmware Image Package, the TF-A container file (`fip.bin`) that carries BL31 and the BL33 payload |
| EL | Exception Level, the Arm privilege level (EL0 through EL3) |
| F2H | FPGA-to-HPS, the interconnect bridge direction from the FPGA fabric into the processor |
| FCS | FPGA Crypto Services, the SDM-provided cryptographic service interface |
| FIFO | First-In, First-Out buffer |
| GHRD | Golden Hardware Reference Design, the public reference FPGA design for a development kit |
| GIC | Generic Interrupt Controller, the Arm interrupt controller. In GIC context, SGI is a software-generated interrupt, PPI a private peripheral interrupt and SPI a shared peripheral interrupt, which is unrelated to the SPI serial bus |
| GPIO | General-Purpose Input/Output |
| H2F | HPS-to-FPGA, the interconnect bridge direction from the processor into the FPGA fabric |
| HPS | Hard Processor System, the Arm processor subsystem inside the SoC FPGA device |
| I2C | Inter-Integrated Circuit, a two-wire multi-drop serial bus |
| I3C | Improved Inter-Integrated Circuit, the MIPI successor to I2C |
| IDCODE | The JTAG identification code of the device |
| IRQ | Interrupt request |
| IOSSM | I/O Subsystem Manager, the firmware interface to the external memory interface |
| JTAG | The IEEE 1149.1 test and programming port used by Quartus Prime Programmer |
| L3, L4 | Interconnect levels in the HPS: L3 is the main interconnect (and the system-level cache behind the CCU); L4 buses connect the slower peripherals |
| LBA | Logical Block Address, the index of a block on a storage device |
| LWH2F | Lightweight HPS-to-FPGA, the narrow low-latency register-access bridge |
| MMIO | Memory-Mapped Input/Output |
| MMU | Memory Management Unit, the CPU block that translates virtual to physical addresses |
| MSEL | Mode Select, the board straps that choose the device configuration scheme |
| NACK | Negative acknowledge, an I2C target failing to acknowledge a byte |
| NOCDIV | The Clock Manager register that holds the interconnect clock dividers |
| NoC | Network-on-Chip, the on-die interconnect between the HPS, the FPGA fabric and memory |
| OCRAM | On-Chip RAM, the small SRAM inside the HPS that is usable before external memory is trained |
| PHY | Physical layer transceiver |
| SCL | Serial Clock line of an I2C bus |
| SDA | Serial Data line of an I2C bus |
| SDM | Secure Device Manager, the device's configuration and security controller |
| SDMMC | Secure Digital / MultiMediaCard controller |
| SEU | Single-Event Upset, a configuration-memory bit flip caused by radiation |
| SMMU | System Memory Management Unit, the equivalent translation block for non-CPU masters |
| SOF | SRAM Object File, the Quartus Prime FPGA programming file |
| SPI | Serial Peripheral Interface |
| TF-A | Trusted Firmware-A, the Arm reference secure firmware that provides BL2 and BL31 |
| UART | Universal Asynchronous Receiver/Transmitter, the serial console interface |
