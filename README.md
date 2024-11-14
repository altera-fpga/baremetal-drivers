# Bare Metal Driver Support for Altera® FPGAs

This repository contains baremetal driver code for Altera® FPGA HPS peripherals.

## EARLY ACCESS

This repository is currently in an early access state. Drivers in this repository have been tested against the Intel® Simics® Simulator for Intel® FPGAs 24.3 release with limited hardware testing. Further validation on Agilex™ 5 will be made available at a later release.

## Table of Contents
- [Introduction](#introduction)
- [Build Instructions](#build-instructions)
- [Coding Style](#coding-style)
- [License](#license)

## Introduction

The build system uses CMake. Coding style checks require MISRA C 2012 compliance. Documentation for the code is found in markdown files inside the repository and are linked from the top level [DOCUMENTATION.md](DOCUMENTATION.md).

## Dependencies

The drivers in this repo are intended to run on Altera® Agilex™ 5 FPGAs. To effectively use this repository, a user needs:
* Quartus® Prime 24.3 or later
* Altera® distribution of ARM Trusted Firmware v2.11 or later
* Intel® Simics® Simulator for Intel® FPGA version 24.2 or later

## Build Instructions

We support the build via CMake. See [BUILD.md](BUILD.md) for more information.

## Coding Style

Coding style checks require MISRA C 2012 compliance. Style formatting is enforced by clang-format using the LLVM style standard. Line endings are checked to verify the user has configured git's core.autocrlf appropriately for their OS.

## License

This project is licensed under the terms of the [LICENSE](LICENSE) file.