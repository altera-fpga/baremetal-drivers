set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR "Nios V")
set(CMAKE_CROSSCOMPILING True)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_AR riscv64-unknown-elf-ar CACHE STRING "AR" FORCE)
set(CMAKE_ASM_COMPILER riscv64-unknown-elf-gcc CACHE STRING "AS" FORCE)
set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc CACHE STRING "CC" FORCE)
set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++ CACHE STRING "CXX" FORCE)

set(ToolchainPrefix riscv64-unknown-elf- CACHE STRING "Toolchain prefix." FORCE)

set(ToolchainObjdump riscv64-unknown-elf-objdump CACHE STRING "Objdump executable." FORCE)
set(ToolchainObjdumpFlags -SCdtx CACHE STRING "Objdump flags." FORCE)

set(DEFAULT_C_FLAGS_SECURITY -D_FORTIFY_SOURCE=2 -fstack-protector)
set(DEFAULT_C_FLAGS_SECURITY_STRONG ${DEFAULT_C_FLAGS_SECURITY} -fstack-protector-strong -z noexecstack -fvisibility=hidden)
set(DEFAULT_C_FLAGS_CLEAN_CODE -Dnullptr=NULL -ffunction-sections -fdata-sections -fno-zero-initialized-in-bss)
set(DEFAULT_C_FLAGS_WARNINGS -Werror -Wall -Wextra -Wformat -Wformat-security -Wno-unused-parameter -Wno-int-to-pointer-cast)
set(DEFAULT_C_FLAGS_PROCESSOR_TUNE -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32)

set(DEFAULT_C_FLAGS_DEBUG -O0 -g ${DEFAULT_C_FLAGS_SECURITY} ${DEFAULT_C_FLAGS_WARNINGS} ${DEFAULT_C_FLAGS_CLEAN_CODE} ${DEFAULT_C_FLAGS_PROCESSOR_TUNE} )

set(DEFAULT_C_FLAGS_RELEASE -O2 ${DEFAULT_C_FLAGS_SECURITY_STRONG} ${DEFAULT_C_FLAGS_WARNINGS} ${DEFAULT_C_FLAGS_CLEAN_CODE} ${DEFAULT_C_FLAGS_PROCESSOR_TUNE} )

add_compile_options(
    $<$<COMPILE_LANGUAGE:ASM>:-Wa,-gdwarf2>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,-z,relro,-z,now>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,--gc-sections>
)

add_link_options(
    $<$<COMPILE_LANGUAGE:ASM>:-Wa,-gdwarf2>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,-z,relro,-z,now>
    $<$<COMPILE_LANGUAGE:ASM>:-Wl,--gc-sections>
    -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
    --specs=nosys.specs
)

function(generate_bin_file)
    string(REGEX REPLACE ".elf" ".bin" ARGV0_BIN ${ARGV0})
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND riscv64-unknown-elf-objcopy -O binary ${ARGV0} ${ARGV0_BIN}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        BYPRODUCTS ${ARGV0}.bin
    )
endfunction()

# ATF doesn't apply to rv32, but this is a null command so cmake works
# This avoids many cmake if() statements
function(generate_atf_sdimage)
    add_custom_command(
        TARGET ${ARGV0} POST_BUILD
        COMMAND :
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction()