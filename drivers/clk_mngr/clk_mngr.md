# Clock Manager Driver Notes

The Clock Manager code provides the low-level support behind the public
`api/clk_mngr` interface. Applications should normally use the public API rather
than access Clock Manager registers directly.

## What the module provides

The public API can:

- initialize the platform Clock Manager settings used by the bare-metal image;
- report the frequency of supported peripheral clock blocks; and
- read or program supported NOCDIV control-clock divisors.

The public identifiers and return contracts are documented in
[`api/clk_mngr/clk_mngr_api.h`](../../api/clk_mngr/clk_mngr_api.h) and in the
generated Natural Docs reference.

## Layering

```text
application
    -> api/clk_mngr
        -> drivers/clk_mngr
            -> platform/<PLAT>/include/socfpga_clk_mngr_reg_plat.h
```

The platform include path selects the register map and initialization routine for
the selected `PLAT`.

## Platform behavior

### Agilex 5 and Agilex 3

The Agilex 5 and Agilex 3 builds use the hardware Clock Manager register layout
with base address `0x10D10000`. The two platforms keep separate platform source
files even where the current register layout is shared.

The Clock Manager depends on the platform clock/reset state established by the
selected boot path. In DDR builds, the preceding firmware flow is expected to
have established the platform state required before the bare-metal payload runs.

## Clock block identifiers

`clk_mngr_api_get_freq()` accepts the `CLK_MNGR_BLOCK_*` identifiers defined in
the public header, including MPU, SD/MMC, SPI, UART, watchdog, I2C, timer,
and L4 Main clocks.

The returned frequency is in hertz.

## NOCDIV control

`clk_mngr_api_set_divisor()` and `clk_mngr_api_get_divisor()` use the
`CLK_MNGR_DIV_*` identifiers from the public header.

Supported divisor values depend on the selected field. The current public API
supports 1, 2, and 4 for the standard control clocks; the CS-related fields also
support 8.

## Dependencies

Clock queries assume the platform clock tree is in a usable state. Depending on
the boot mode, the values used by the driver can come from live Clock Manager
registers, platform setup, or boot scratch information established earlier in
the boot flow.

Accessing a peripheral while its source clock is disabled can make the
peripheral unavailable. Application code should use the public Clock Manager
and peripheral APIs rather than manipulating clock-gate registers directly.

## Source references

- [`api/clk_mngr/clk_mngr_api.h`](../../api/clk_mngr/clk_mngr_api.h) — public API
- `drivers/clk_mngr/socfpga_clk_mngr_ll.[ch]` — low-level clock calculation and divisor access
- `platform/agilex5/clk_mngr_platform.c` — Agilex 5 initialization
- `platform/agilex3/clk_mngr_platform.c` — Agilex 3 initialization
- `platform/<PLAT>/include/socfpga_clk_mngr_reg_plat.h` — platform register definitions
