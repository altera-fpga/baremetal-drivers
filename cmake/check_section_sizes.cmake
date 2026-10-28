# ---------------------------------------------------------------------------
# check_section_sizes.cmake
#
# Post-build section size checker invoked via:
#   cmake -DELF=<path-to-elf> -DNM=<nm-binary> -P check_section_sizes.cmake
#
# Reads the linker-exported boundary symbols from the ELF and prints a table:
#
#   Section   Used      Budget    Used%   Status
#   .text     123456 B  1048576 B  11.8%  PASS
#   .data+bss  45678 B  2097152 B   2.2%  PASS
#
# Exits with a fatal error if any section exceeds its budget.
# ---------------------------------------------------------------------------

if(NOT DEFINED ELF OR NOT DEFINED NM)
    message(FATAL_ERROR "check_section_sizes.cmake: ELF and NM must be defined")
endif()

# ---------------------------------------------------------------------------
# 1. Run nm to collect defined symbols
# ---------------------------------------------------------------------------
execute_process(
    COMMAND ${NM} --format=posix --defined-only ${ELF}
    OUTPUT_VARIABLE _nm_out
    RESULT_VARIABLE _nm_rc
    ERROR_QUIET
)

if(NOT _nm_rc EQUAL 0)
    message(WARNING "Section size check: nm failed for ${ELF} -- skipping check")
    return()
endif()

# ---------------------------------------------------------------------------
# 2. Helper: extract a hex symbol value from nm posix output
#    nm posix line format: <name> <type> <value> <size>
# ---------------------------------------------------------------------------
macro(_get_sym varname symname)
    set(${varname} "NOTFOUND")
    string(REGEX MATCH "(^|\n)${symname} [A-Za-z] ([0-9a-fA-F]+)" _m "${_nm_out}")
    if(_m)
        string(REGEX REPLACE "(^|\n)${symname} [A-Za-z] ([0-9a-fA-F]+).*" "\\2" ${varname} "${_m}")
        # Strip leading zeros to avoid CMake octal interpretation
        string(REGEX REPLACE "^0+" "" ${varname} "${${varname}}")
        if("${${varname}}" STREQUAL "")
            set(${varname} "0")
        endif()
        math(EXPR ${varname} "0x${${varname}}" OUTPUT_FORMAT DECIMAL)
    endif()
endmacro()

_get_sym(_text_start  "__text_start")
_get_sym(_text_end    "__text_end")
_get_sym(_sdata       "__sdata")
_get_sym(_ebss        "__ebss")
_get_sym(_stack_top   "_stack_top")

# ---------------------------------------------------------------------------
# 3. Validate that all required symbols were found
# ---------------------------------------------------------------------------
foreach(_sym _text_start _text_end _sdata _ebss _stack_top)
    if("${${_sym}}" STREQUAL "NOTFOUND")
        message(WARNING
            "Section size check: symbol '${_sym}' not found in ${ELF} -- "
            "ensure the ELF was linked with the baremetal linker scripts")
        return()
    endif()
endforeach()

# ---------------------------------------------------------------------------
# 4. Compute sizes and budgets
# ---------------------------------------------------------------------------
math(EXPR _text_used   "${_text_end}  - ${_text_start}")
math(EXPR _text_budget "${_sdata}     - ${_text_start}")
math(EXPR _data_used   "${_ebss}      - ${_sdata}")
math(EXPR _data_budget "${_stack_top} - ${_sdata}")

# Percentage as integer (multiply by 100 first to keep integer arithmetic)
math(EXPR _text_pct   "${_text_used}  * 100 / ${_text_budget}")
math(EXPR _data_pct   "${_data_used}  * 100 / ${_data_budget}")

# ---------------------------------------------------------------------------
# 5. Determine pass/fail
# ---------------------------------------------------------------------------
set(_text_status "PASS")
set(_data_status "PASS")

if(_text_used GREATER _text_budget)
    set(_text_status "FAIL")
endif()
if(_data_used GREATER _data_budget)
    set(_data_status "FAIL")
endif()

# ---------------------------------------------------------------------------
# 6. Print the report
# ---------------------------------------------------------------------------
message(STATUS "------------------------------------------------------------")
message(STATUS "  Section size report: ${ELF}")
message(STATUS "------------------------------------------------------------")
message(STATUS "  Section    Used        Budget      Used%   Status")
message(STATUS "  .text      ${_text_used} B  ${_text_budget} B  ${_text_pct}%  ${_text_status}")
message(STATUS "  .data+bss  ${_data_used} B  ${_data_budget} B  ${_data_pct}%  ${_data_status}")
message(STATUS "------------------------------------------------------------")

# ---------------------------------------------------------------------------
# 7. Fail the build if any section is over budget
# ---------------------------------------------------------------------------
if(_text_status STREQUAL "FAIL")
    math(EXPR _text_over "${_text_used} - ${_text_budget}")
    message(FATAL_ERROR
        "Section size check FAILED: .text exceeds budget by ${_text_over} bytes "
        "(used=${_text_used}, budget=${_text_budget}). "
        "For DDR mode: increase DATA_ORIGIN in linker_ddr.ld. "
        "For OCRAM mode: reduce code size or enable optimization (-O2 instead of -O0).")
endif()

if(_data_status STREQUAL "FAIL")
    math(EXPR _data_over "${_data_used} - ${_data_budget}")
    message(FATAL_ERROR
        "Section size check FAILED: .data+.bss exceeds budget by ${_data_over} bytes "
        "(used=${_data_used}, budget=${_data_budget}). "
        "Increase DATA_SIZE in the linker script.")
endif()
