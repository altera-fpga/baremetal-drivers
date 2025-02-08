# Intel FPGA Baremetal Driver Libraries

This repository contains baremetal driver code for Intel FPGA peripherals and soft IP.

## Table of Contents
- [Introduction](#introduction)
- [Build Instructions](#build-instructions)
- [Coding Style](#coding-style)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The build system uses CMake. Coding style checks require MISRA C 2012 compliance. Documentation for the code is found in markdown files inside the repository and are linked from the top level [DOCUMENTATION.md](DOCUMENTATION.md).

## Build Instructions

We support the build via CMake. See [BUILD.md](BUILD.md) for more information.

## Coding Style

Coding style checks require MISRA C 2012 compliance. Style formatting is enforced by clang-format using the LLVM style standard. Line endings are checked to verify the user has configured git's core.autocrlf appropriately for their OS.

## License

This project is licensed under the terms of the [LICENSE](LICENSE) file.