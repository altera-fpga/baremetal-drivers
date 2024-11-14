# Testing Methodology

## Simics® Tests

Tests execute in a model of Agilex5e that is provided by the Intel® Simics® Simulator for Intel® FPGAs using the agilex5e-unlimited target. During execution, Simics® tooling collects coverage data.

## Hardware Tests

Tests also are executed on hardware platforms to verify silicon behavior. Current testing coverage is limited to uart, watchdog, and timers.

## Test Coverage

We target 80% coverage of the source code in the repository.