cmake_minimum_required(VERSION 3.20)

project(baremetal LANGUAGES C ASM)

# ---------------------------
# Git commit hash
# ---------------------------
find_package(Git QUIET)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
else()
    set(GIT_COMMIT_HASH "unknown")
endif()

# ---------------------------
# Options
# ---------------------------
option(DEBUG "Debug build" OFF)
set(BUILD_MODE "OCRAM" CACHE STRING "OCRAM or DDR")
set(PLAT "" CACHE STRING "Platform (agilex5 or agilex3)")
set(ATF_DIRECT_BOOT "0" CACHE STRING "Enable ATF direct boot build path")

if (NOT PLAT STREQUAL "agilex5" AND NOT PLAT STREQUAL "agilex3")
  message(FATAL_ERROR "PLAT='${PLAT}' is not supported. Pass -DPLAT=agilex5 or -DPLAT=agilex3")
endif()

message(STATUS "====================================")
message(STATUS "Selected platform: ${PLAT}")
message(STATUS "Build mode       : ${BUILD_MODE}")
message(STATUS "Debug            : ${DEBUG}")
message(STATUS "ATF direct boot  : ${ATF_DIRECT_BOOT}")
message(STATUS "====================================")

add_compile_definitions(GIT_COMMIT_ID="${GIT_COMMIT_HASH}")
add_compile_definitions(ATF_DIRECT_BOOT="${ATF_DIRECT_BOOT}")

# Reusable artifact-generation helper (also consumed by downstream apps).
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/bm_artifacts.cmake)

# ---------------------------
# Build flags
# ---------------------------
if (DEBUG)
  add_compile_options(-O0 -g -DDEBUG)
else()
  add_compile_options(-O2)
endif()

# Resolve the linker script from BUILD_MODE here in the baremetal repo (it
# owns the linker scripts), and expose LD_SCRIPT through the CMake cache so a
# parent project that pulls this repo in via add_subdirectory() can pick it
# up directly instead of duplicating the BUILD_MODE -> .ld mapping.
#
# Use CMAKE_CURRENT_SOURCE_DIR (this CMakeLists' dir = baremetal repo root)
# rather than CMAKE_SOURCE_DIR, which would point at the consuming
# application's source root when this repo is nested.
if (BUILD_MODE STREQUAL "OCRAM")
  set(LD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_ocram.ld" CACHE INTERNAL
      "Baremetal linker script (resolved from BUILD_MODE)")
  add_compile_definitions(BUILD_MODE_OCRAM)
elseif (BUILD_MODE STREQUAL "DDR")
  set(LD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_ddr.ld" CACHE INTERNAL
      "Baremetal linker script (resolved from BUILD_MODE)")
  add_compile_definitions(BUILD_MODE_DDR)
else()
  message(FATAL_ERROR "Invalid BUILD_MODE='${BUILD_MODE}'")
endif()

add_compile_options(
  -ffreestanding
  -fno-pic
  -fno-pie
  -Wall -Wextra
  -nostdlib
  -std=c99
  -mstrict-align
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# ---------------------------
# Platform-specific includes
# ---------------------------
if (PLAT STREQUAL "agilex5")
  add_compile_definitions(PLAT_AGILEX5)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/platform/agilex5/include)
elseif (PLAT STREQUAL "agilex3")
  add_compile_definitions(PLAT_AGILEX3)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/platform/agilex3/include)
endif()

# ---------------------------
# Subdirectories
# ---------------------------
add_subdirectory(api)
add_subdirectory(drivers)
add_subdirectory(examples)
add_subdirectory(middleware)
add_subdirectory(src)
add_subdirectory(platform)

# ---------------------------
# ELF target
# ---------------------------
add_executable(baremetal.elf
  src/main.c
  src/crt0.c
  src/startup.S
  src/vectors.S
  $<TARGET_OBJECTS:bm_examples>
)

target_link_options(baremetal.elf PRIVATE
  -T${LD_SCRIPT}
  -nostdlib
  -no-pie
  -Wl,-L${CMAKE_CURRENT_SOURCE_DIR}
  -Wl,-Map=${CMAKE_BINARY_DIR}/baremetal.map
)

target_link_libraries(baremetal.elf PRIVATE
  -Wl,--start-group
  socfpga_drivers
  bm_middleware
  bm_app
  platform
  bm_api
  -Wl,--end-group
)

# ---------------------------
# Post build
# ---------------------------
bm_generate_artifacts(baremetal.elf)
bm_check_section_sizes(baremetal.elf)
