

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR "arm64")
set(CMAKE_CROSSCOMPILING True)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT CROSS_COMPILE)
    set(CROSS_COMPILE aarch64-none-elf-)
endif()


set(CMAKE_AR ${CROSS_COMPILE}ar CACHE STRING "AR" FORCE)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc CACHE STRING "AS" FORCE)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc CACHE STRING "CC" FORCE)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++ CACHE STRING "CXX" FORCE)

set(ToolchainPrefix ${CROSS_COMPILE} CACHE STRING "Toolchain prefix." FORCE)

set(ToolchainObjdump ${CROSS_COMPILE}objdump CACHE STRING "Objdump executable." FORCE)
set(ToolchainObjdumpFlags -SCdtx CACHE STRING "Objdump flags." FORCE)

set(DEFAULT_C_FLAGS_SECURITY -D_FORTIFY_SOURCE=2  CACHE STRING "Security build flags." FORCE)
set(DEFAULT_C_FLAGS_SECURITY_STRONG ${DEFAULT_C_FLAGS_SECURITY} -z noexecstack -fvisibility=hidden CACHE STRING "Strong Security build flags." FORCE)
set(DEFAULT_C_FLAGS_CLEAN_CODE -ffunction-sections -fdata-sections -fno-zero-initialized-in-bss -mstrict-align CACHE STRING "Code cleanliness build flags." FORCE)
set(DEFAULT_C_FLAGS_WARNINGS -Werror -Wall -Wextra -Wformat -Wformat-security -Wno-unused-parameter -Wno-int-to-pointer-cast CACHE STRING "Warning build flags." FORCE)
set(DEFAULT_C_FLAGS_PROCESSOR_TUNE -march=armv8.2-a -mtune=cortex-a76.cortex-a55 CACHE STRING "processor tuning build flags" FORCE)

set(DEFAULT_C_FLAGS_DEBUG -O0 -g ${DEFAULT_C_FLAGS_SECURITY} ${DEFAULT_C_FLAGS_WARNINGS} ${DEFAULT_C_FLAGS_CLEAN_CODE} ${DEFAULT_C_FLAGS_PROCESSOR_TUNE} )

set(DEFAULT_C_FLAGS_RELEASE -O2 ${DEFAULT_C_FLAGS_SECURITY_STRONG} ${DEFAULT_C_FLAGS_WARNINGS} ${DEFAULT_C_FLAGS_CLEAN_CODE} ${DEFAULT_C_FLAGS_PROCESSOR_TUNE} )

add_compile_options(
    $<$<COMPILE_LANGUAGE:ASM>:-Wa,-gdwarf2>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,-z,relro,-z,now>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,--gc-sections>
    --specs=nosys.specs -mstrict-align
)

add_link_options(
    $<$<COMPILE_LANGUAGE:ASM>:-Wa,-gdwarf2>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,-z,relro,-z,now>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,--gc-sections>
    --specs=nosys.specs -mstrict-align
)

add_custom_target(atf-build)

set(ATF_ENV_FILE "${CMAKE_CURRENT_SOURCE_DIR}/atf_env.simics")

add_dependencies(atf-build atf-bl2-bl31 atf-fiptool atf-env)

if(NOT ATF_GIT_REPO)
    set(ATF_GIT_REPO https://github.com/altera-opensource/arm-trusted-firmware.git)
endif()

if(NOT ATF_GIT_TAG)
    set(ATF_GIT_TAG socfpga_v2.10.1)
endif()

FetchContent_Declare(
    atf
    GIT_REPOSITORY ${ATF_GIT_REPO}
    GIT_TAG ${ATF_GIT_TAG}
)

# Fetch the ATF code
FetchContent_MakeAvailable(atf)
# Add custom target to build ATF
add_custom_target(
    atf-bl2-bl31
    COMMAND make -C ${atf_SOURCE_DIR} CROSS_COMPILE=aarch64-none-elf- PLAT=agilex5 LOG_LEVEL=50 bl31 bl2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    BYPRODUCTS ${atf_SOURCE_DIR}/build/agilex5/release/bl31.bin
)
# Add custom target to build ATF fiptool
add_custom_target(
    atf-fiptool
    COMMAND make -C ${atf_SOURCE_DIR} fiptool
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    BYPRODUCTS ${atf_SOURCE_DIR}/tools/fiptool/fiptool
)
# Export ATF_BASE_DIR into Simics
add_custom_target(
    atf-env
    COMMAND python3 atf-env.py ${atf_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS atf-env.py
    BYPRODUCTS ${ATF_ENV_FILE}
)

function(generate_bin_file)
    string(REGEX REPLACE ".elf" ".bin" ARGV0_BIN ${ARGV0})
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND ${CROSS_COMPILE}objcopy -O binary ${ARGV0} ${ARGV0_BIN}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS ${ARGV0}
    )
    add_custom_target(${ARGV0_BIN} DEPENDS ${ARGV0})
endfunction()

function(generate_atf_sdimage)
    string(REGEX REPLACE ".elf" ".bin" ARGV0_BIN ${ARGV0})
    string(REGEX REPLACE ".bin" ".fip" ARGV0_FIP ${ARGV0})
    generate_bin_file(${ARGV0})
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND ${atf_SOURCE_DIR}/tools/fiptool/fiptool create --soc-fw ${atf_SOURCE_DIR}/build/agilex5/release/bl31.bin --nt-fw ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ARGV0_BIN} ${ARGV0_FIP}
        COMMAND rm -f sd.img
        COMMAND make_sdimage.sh -p ${ARGV0_FIP} -o sd.img -g 2G -pg 16
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${ARGV0}
        BYPRODUCTS ${ARGV0_FIP}
    )
    add_dependencies(${ARGV0} atf-build)
endfunction()
