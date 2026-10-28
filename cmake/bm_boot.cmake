# ---------------------------------------------------------------------------
# ARM Trusted Firmware build machinery for baremetal boot images.
#
# Builds ATF bl2/bl31 for SD boot and fiptool, then exposes them so a
# consuming app can package fip.bin and assemble its SD image.
#
# Include after project():
#     include("${baremetal_SOURCE_DIR}/cmake/bm_boot.cmake")
#
# Provides:
#   targets : atf-bl2-bl31-sd, atf-fiptool
#   vars    : SD_ARTIFACTS_DIR  (contains bl2.bin/bl31.bin)
#             fiptool is built at ${CMAKE_BINARY_DIR}/fiptool
#
# Requires: cmake/bm_toolchain.cmake included first (sets BM_CROSS_PREFIX) and
# an AArch64 cross toolchain on PATH.
# ---------------------------------------------------------------------------

include_guard(GLOBAL)
include(FetchContent)
include(ProcessorCount)

if(NOT BM_CROSS_PREFIX)
    message(FATAL_ERROR
        "bm_boot.cmake: BM_CROSS_PREFIX is not set. Include cmake/bm_toolchain.cmake "
        "before project() so the ATF/fiptool cross build knows the toolchain prefix.")
endif()

ProcessorCount(_BM_NPROC)
if(_BM_NPROC EQUAL 0)
    set(_BM_NPROC 1)
endif()

# --- Tunables ---------------------------------------------------------------
set(BM_ATF_PLAT      "agilex5"     CACHE STRING "ATF PLAT (agilex5 only)")
set(BM_ATF_LOG_LEVEL "25"          CACHE STRING "ATF LOG_LEVEL")
set(BM_BL33_BASE     "0x80200000"  CACHE STRING "PRELOADED_BL33_BASE for ATF")

# --- ATF source (pinned revision) -------------------------------------------
if(NOT BM_ATF_SOURCE_DIR)
    FetchContent_Declare(
        atf
        GIT_REPOSITORY https://github.com/altera-opensource/arm-trusted-firmware
        # branch socfpga_v2.14.0
        GIT_TAG        4a4b4573e12fabd0a88e95952af49840db6b770d
    )
    FetchContent_GetProperties(atf)
    if(NOT atf_POPULATED)
        FetchContent_Populate(atf)
    endif()
    set(BM_ATF_SOURCE_DIR "${atf_SOURCE_DIR}" CACHE PATH "ATF source tree")
endif()

# ATF's make build writes into the source tree, so work on a private copy.
set(_BM_ATF_SD_COPY     "${CMAKE_BINARY_DIR}/atf_copy_sd")
set(SD_ARTIFACTS_DIR    "${CMAKE_BINARY_DIR}/sd_atf_binaries")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(_BM_ATF_DEBUG 1)
    set(_BM_ATF_SUBDIR "debug")
else()
    set(_BM_ATF_DEBUG 0)
    set(_BM_ATF_SUBDIR "release")
endif()
set(_BM_ATF_SD_BUILD_DIR   "${_BM_ATF_SD_COPY}/build/${BM_ATF_PLAT}/${_BM_ATF_SUBDIR}")

# --- Deterministic ATF version string ---------------------------------------
# TF-A stamps its version from `git describe --dirty` on the ATF tree. The SD
# build rewrites a tracked header (socfpga_plat_def.h, MMC_DEVICE_TYPE=SD) before
# `make`, which dirties that tree and appends a misleading "-dirty" to bl2/bl31.
# Derive the version once from the pristine source and pass it to make so the
# build stamps a clean string and TF-A skips its own `git describe`. Empty -> expands to zero make args.
set(_BM_ATF_BUILD_STRING_ARG "")
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" -C "${BM_ATF_SOURCE_DIR}" describe --tags --always
        OUTPUT_VARIABLE _BM_ATF_BUILD_STRING
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET)
    if(_BM_ATF_BUILD_STRING)
        set(_BM_ATF_BUILD_STRING_ARG "BUILD_STRING=${_BM_ATF_BUILD_STRING}")
        message(STATUS "bm_boot: pinning ATF BUILD_STRING=${_BM_ATF_BUILD_STRING}")
    endif()
endif()
if(NOT _BM_ATF_BUILD_STRING_ARG)
    message(WARNING "bm_boot: could not derive ATF BUILD_STRING; SD bl2/bl31 may report '-dirty'.")
endif()

# Only Agilex5 is supported for now.
set(_BM_ATF_PLAT_DEF_REL "plat/intel/soc/agilex5/include/socfpga_plat_def.h")

# Force MMC_DEVICE_TYPE=1 (SD) in the ATF plat def for SD builds.
set(_BM_MMC_PATCH "${CMAKE_BINARY_DIR}/bm_patch_mmc_device_type.cmake")
file(WRITE "${_BM_MMC_PATCH}" [=[
if(NOT DEFINED INPUT_FILE OR NOT EXISTS "${INPUT_FILE}")
    message(FATAL_ERROR "INPUT_FILE missing: ${INPUT_FILE}")
endif()
file(READ "${INPUT_FILE}" _c)
string(REGEX REPLACE "MMC_DEVICE_TYPE[ \t]*[0-9]+" "MMC_DEVICE_TYPE 1" _c "${_c}")
file(WRITE "${INPUT_FILE}" "${_c}")
message(STATUS "Set MMC_DEVICE_TYPE=1 (SD) in ${INPUT_FILE}")
]=])

# Private source copy for the SD build.
add_custom_command(
    OUTPUT  "${_BM_ATF_SD_COPY}/.bm_atf_copied"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${_BM_ATF_SD_COPY}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${BM_ATF_SOURCE_DIR}" "${_BM_ATF_SD_COPY}"
    COMMAND ${CMAKE_COMMAND} -E touch "${_BM_ATF_SD_COPY}/.bm_atf_copied"
    COMMENT "Copying ATF source into SD build tree"
)
add_custom_target(atf-copy-sd DEPENDS "${_BM_ATF_SD_COPY}/.bm_atf_copied")

# SD bl2/bl31 (patch MMC_DEVICE_TYPE=SD, then build)
add_custom_target(atf-bl2-bl31-sd
    COMMAND ${CMAKE_COMMAND} -DINPUT_FILE=${_BM_ATF_SD_COPY}/${_BM_ATF_PLAT_DEF_REL} -P "${_BM_MMC_PATCH}"
    COMMAND make -C "${_BM_ATF_SD_COPY}" CROSS_COMPILE=${BM_CROSS_PREFIX} PLAT=${BM_ATF_PLAT} clean
    COMMAND make -C "${_BM_ATF_SD_COPY}" CROSS_COMPILE=${BM_CROSS_PREFIX} PLAT=${BM_ATF_PLAT}
            SPD=none PRELOADED_BL33_BASE=${BM_BL33_BASE}
            LOG_LEVEL=${BM_ATF_LOG_LEVEL} DEBUG=${_BM_ATF_DEBUG} ${_BM_ATF_BUILD_STRING_ARG}
            bl2 bl31 -j${_BM_NPROC}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SD_ARTIFACTS_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_BM_ATF_SD_BUILD_DIR}/bl2.bin"  "${SD_ARTIFACTS_DIR}/bl2.bin"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_BM_ATF_SD_BUILD_DIR}/bl31.bin" "${SD_ARTIFACTS_DIR}/bl31.bin"
    BYPRODUCTS "${SD_ARTIFACTS_DIR}/bl2.bin" "${SD_ARTIFACTS_DIR}/bl31.bin"
    DEPENDS atf-copy-sd
    VERBATIM
)

# fiptool (host tool, built in the SD tree)
add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/fiptool"
    # CROSS_COMPILE is passed even for this host tool so ATF's parse-time
    # toolchain detection resolves a real AArch64 prefix; without it the detection
    # mis-expands and breaks ("invalid syntax in conditional" in build_macros.mk).
    COMMAND make -C "${_BM_ATF_SD_COPY}" CROSS_COMPILE=${BM_CROSS_PREFIX} fiptool
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_BM_ATF_SD_COPY}/tools/fiptool/fiptool" "${CMAKE_BINARY_DIR}/fiptool"
    DEPENDS atf-copy-sd
    COMMENT "Building fiptool"
    VERBATIM
)
add_custom_target(atf-fiptool DEPENDS "${CMAKE_BINARY_DIR}/fiptool")

# fiptool shares the SD tree and bl2/bl31 runs `make clean` first, so build
# fiptool before that clean (never concurrently in the same tree).
add_dependencies(atf-bl2-bl31-sd atf-fiptool)
