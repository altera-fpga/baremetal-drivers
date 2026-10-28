# Middleware Layer

This folder contains middleware services that sit between API wrappers and low-level drivers.

## Purpose

1. Hold module state and context handles.
2. Enforce lifecycle checks (open/close, init/deinit).
3. Coordinate multi-step flows across one or more low-level drivers.
4. Provide stable behavior to API callers regardless of low-level implementation details.

## Current Modules

1. bridge
2. dma
3. iossm
4. rstmgr
5. uart

## Conventions

1. Return contract: `0` on success, negative `errno` on failure.
2. Public comments: Natural Docs format (`File:`, `Function:`, `Type:`, `Enum:`, `Struct:`, `Callback:`).
3. Keep middleware interfaces opaque when state ownership is required.
4. Keep policy/flow in middleware, register-level access in drivers.

## Build

Middleware sources are included by `middleware/CMakeLists.txt` and linked into the bare-metal image through top-level CMake.
