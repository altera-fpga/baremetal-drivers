# About the Build
We support the build via cmake using either makefiles or ninja as the build system. By default, the build creates libalterametal.a and the googletest libraries. To build tests, use the target 'test'.

## Processor Architecture Selection
This repository builds both rv32 and aarch64 binaries. By default, the aarch64 build runs. To run the rv32 build, specify `-DBUILD_ARM=OFF` when invoking cmake. To change architecture, clean the CMakeCache.txt and CMakeFiles directories. The git clean tool will also do this via 'git clean -ffdx'

## Executing a Build
To generate the build system files, invoke cmake at the root directory of the repository with either `cmake -GNinja .` or `cmake -G "Unix Makefiles" .`.

After generating the build system files, build the library using the `alterametal` target and run tests with the `test` target.

Example using ninja:
```
cmake -GNinja .
ninja alterametal
ninja test
```

## Debug vs Release
The build system builds Release by default. To build debug binaries, specify `CMAKE_BUILD_TYPE=Debug` when invoking cmake.

The differences in debug vs release can be found in the [target_rv32.cmake](target_rv32.cmake) and [target_aarch64.cmake](target_aarch64.cmake) files respectively. Each target uses the flags as defined. We do not use the generic cmake C/CXX flags variables.