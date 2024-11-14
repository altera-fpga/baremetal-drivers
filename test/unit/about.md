## About Unittests on Simics using Googletest

This directory contains unittests written in the googletest framework and running inside the Simics simulator. This allows for basic checks that don't provide example code to be written faster.

In this directory, cross-compilation is used to generate an aarch64 image that is loaded via ATF as BL33. The test output looks just like googletest would on x86. To make the build work, a handful of stubs are provided for syscalls that either googletest or the standard library expects to use. For information on that see test/unit/common/[about.md](common/about.md)

When running tests you may encounter a false warning about googletest not being initialized before the tests were run. See also https://github.com/google/googletest/issues/3395