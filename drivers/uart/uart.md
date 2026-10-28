# UART (Universal Asynchronous Receiver/Transmitter, the serial console interface) Module Overview

This driver provides the console transport used by the Agilex 5 and Agilex 3
bare-metal UART API. It carries startup messages and application output. See
the [UART API guide](../../api/uart/README.md) for initialization, blocking
receive behavior and console shutdown limitations.

## Purpose

| Capability | Description |
| --- | --- |
| Console output | Provides early visibility during platform initialization. |
| Logging support | Emits application and driver messages through the UART console. |
| Platform validation | Supports basic smoke tests on simulation and hardware targets. |

## Dependencies

| Dependency | Description |
| --- | --- |
| Clock and reset | UART clock and reset must be configured before use. |
| Pin and signal routing | Pinmux and board routing must match the selected UART instance. |
| Platform services | System initialization must provide a valid UART base address. |

## Verification approach

| Check | Method |
| --- | --- |
| Console output | Confirm boot and shell messages appear on the expected serial port. |
| Register access | Verify baud, line control, and FIFO configuration complete successfully. |
| Basic logging | Confirm application messages are transmitted without data loss. |
