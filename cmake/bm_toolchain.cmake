# ---------------------------------------------------------------------------
# AArch64 bare-metal cross-compile setup for downstream applications.
#
# Include this in a consuming application's CMakeLists.txt *before* project()
# (after this repo has been populated, e.g. via FetchContent) so the
# cross-compile boilerplate lives here in the baremetal repo instead of being
# duplicated in every customer's file:
#
#     FetchContent_Populate(baremetal)
#     include("${baremetal_SOURCE_DIR}/cmake/bm_toolchain.cmake")
#     project(my_app C ASM)
#
# Skipped if the caller already supplies their own toolchain file or compiler.
#
# Exposes:
#   BM_CROSS_PREFIX - toolchain prefix incl. trailing dash (e.g.
#                     "aarch64-none-elf-"), for tools that take CROSS_COMPILE
#                     (ATF make, fiptool, ...). See bm_boot.cmake.
# ---------------------------------------------------------------------------
if(NOT CMAKE_TOOLCHAIN_FILE AND NOT CMAKE_C_COMPILER)
    set(CMAKE_SYSTEM_NAME      Generic)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)

    # Use whichever AArch64 bare-metal GCC is on PATH (aarch64-none-linux-gnu-
    # or aarch64-none-elf-).
    find_program(_BM_GCC NAMES aarch64-none-linux-gnu-gcc aarch64-none-elf-gcc REQUIRED)
    set(CMAKE_C_COMPILER   "${_BM_GCC}")
    set(CMAKE_ASM_COMPILER "${_BM_GCC}")

    # objcopy/objdump are auto-detected from the compiler prefix; size is not,
    # so set it explicitly for bm_generate_artifacts(). Also derive the
    # toolchain prefix for tools driven by CROSS_COMPILE.
    get_filename_component(_BM_DIR  "${_BM_GCC}" DIRECTORY)
    get_filename_component(_BM_STEM "${_BM_GCC}" NAME_WE)
    string(REGEX REPLACE "-?gcc$" "" _BM_PREFIX "${_BM_STEM}")
    set(CMAKE_SIZE "${_BM_DIR}/${_BM_PREFIX}-size" CACHE FILEPATH "" FORCE)
    set(BM_CROSS_PREFIX "${_BM_PREFIX}-" CACHE STRING "AArch64 cross toolchain prefix" FORCE)

    # Bare-metal: only compile (don't link a full exe) during compiler checks.
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()
