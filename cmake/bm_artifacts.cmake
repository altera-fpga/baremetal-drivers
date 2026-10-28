# ---------------------------------------------------------------------------
# bm_generate_artifacts(<elf-target>)
#
# Reusable post-build helper that, for the given ELF target, generates the
# .bin / .hex / .dump artifacts next to the ELF and prints its size. Both this
# repo and any downstream application that pulls it in (e.g. via FetchContent +
# add_subdirectory) can call this instead of duplicating the objcopy/objdump
# commands.
#
# Output files are named after the target with any trailing ".elf" stripped,
# e.g. target "hps_baremetal.elf" -> hps_baremetal.bin / .hex / .dump.
# ---------------------------------------------------------------------------
function(bm_generate_artifacts elf_target)
    string(REGEX REPLACE "\\.elf$" "" _base "${elf_target}")

    add_custom_command(TARGET ${elf_target} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${elf_target}> $<TARGET_FILE_DIR:${elf_target}>/${_base}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${elf_target}> $<TARGET_FILE_DIR:${elf_target}>/${_base}.hex
        COMMAND ${CMAKE_OBJDUMP} -d        $<TARGET_FILE:${elf_target}> > $<TARGET_FILE_DIR:${elf_target}>/${_base}.dump
        COMMAND ${CMAKE_SIZE}              $<TARGET_FILE:${elf_target}>
        COMMENT "Generating ${_base}.bin/.hex/.dump"
    )
endfunction()

# ---------------------------------------------------------------------------
# bm_check_section_sizes(<elf-target>)
#
# Post-build section size checker.  After the ELF is linked, reads the
# linker-exported symbols (__text_start, __text_end, __sdata, __ebss,
# _stack_top) via nm and prints a pass/fail table showing how much of each
# memory region the build uses.  The build fails if any section exceeds its
# budget (which the linker ASSERT in linker_sections.ld also enforces, but
# this gives a more human-readable diagnosis).
#
# Works for both OCRAM and DDR BUILD_MODE because the budget symbols are
# always present in the ELF.
# ---------------------------------------------------------------------------
function(bm_check_section_sizes elf_target)
    # Derive nm from the objcopy path set by the toolchain file.
    string(REPLACE "objcopy" "nm" _NM "${CMAKE_OBJCOPY}")

    add_custom_command(TARGET ${elf_target} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DELF=$<TARGET_FILE:${elf_target}>
            -DNM=${_NM}
            -P ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/check_section_sizes.cmake
        COMMENT "Section size check: ${elf_target}"
    )
endfunction()
