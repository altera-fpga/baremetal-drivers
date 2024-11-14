cmake_minimum_required(VERSION 3.5...3.28)

include(FetchContent)

# Specify C standard as C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Specify C++ standard as C++23 (gnu++23)
# Googletest requires gnu++23 rather than c++23, so specify as compile option
add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++23>
    )

# Default to Debug build type
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Defaulting build type to Debug.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

# Default to ARM architecture
if(NOT DEFINED BUILD_ARM)
    message(STATUS "Defaulting architecture to ARM")
    set(BUILD_ARM ON CACHE BOOL "" FORCE)
endif()

# Include toolchain file based on architecture
if(BUILD_ARM)
    include(target_aarch64.cmake)
else()
    include(target_rv32.cmake)
endif()


# Define Project, library, and test target
project(altera_baremetal C CXX ASM)
add_library(alterametal STATIC)
target_sources(alterametal PRIVATE)
add_custom_target(test)

# Set output directory based on architecture
if(BUILD_ARM)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/aarch64/out")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/rv32/out")
endif()

# Include googletest as a dependency
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

# Configure googletest
add_compile_options(
    -DGTEST_HAS_CLONE=0
    -DGTEST_HAS_EXCEPTIONS=0
    -DGTEST_HAS_POSIX_RE=0
    -DGTEST_HAS_PTHREAD=0
    -DGTEST_HAS_RTTI=0
    -DGTEST_HAS_STREAM_REDIRECTION=0
    -DGTEST_HAS_STDWSTRING=0
    )

# Fetch the googletest code
FetchContent_MakeAvailable(googletest)

# Set compile options based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(alterametal PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(alterametal PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

# Include directories for library source
add_subdirectory(inc)
add_subdirectory(src)
add_subdirectory(helpers)

# Include test directories
add_subdirectory(test)
