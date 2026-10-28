cmake_minimum_required(VERSION 3.20)

# ---------------------------------------------------------
# 1. Gather all Headers 
# (Headers don't consume memory, so GLOB is perfectly safe here)
# ---------------------------------------------------------
file(GLOB_RECURSE EXAMPLES_H CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


# ---------------------------------------------------------
# 2. Gather Sources based on BUILD_MODE
# ---------------------------------------------------------
if (BUILD_MODE STREQUAL "OCRAM")
    
    # --- STRICT WHITELIST FOR OCRAM ---
    # We bypass GLOB entirely to prevent massive buffers from leaking in.
    # Only compile the absolute minimum to fit inside 256KB.
    set(EXAMPLES_C
        ${CMAKE_CURRENT_SOURCE_DIR}/hello/hello_selftest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ddr/ddr_selftest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/gic/gic_selftest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/timer/timer_selftest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/example_register.c
    )

    # Agilex 3 OCRAM does not run ddr_init() before ddr_selftest, and that
    # test then writes external memory at 0x83000000. Leave it out of this image.
    if (PLAT STREQUAL "agilex3")
        list(REMOVE_ITEM EXAMPLES_C
            ${CMAKE_CURRENT_SOURCE_DIR}/ddr/ddr_selftest.c
        )
    endif()

else()

    # --- STANDARD GLOB FOR DDR ---
    # We have plenty of RAM, so grab everything.
    file(GLOB_RECURSE EXAMPLES_C CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

    # perf_selftest.c is not part of the default DDR image.
    list(REMOVE_ITEM EXAMPLES_C
        ${CMAKE_CURRENT_SOURCE_DIR}/perf/perf_selftest.c
    )

endif()


# ---------------------------------------------------------
# 3. Build Target & Linkage
# ---------------------------------------------------------
add_library(bm_examples OBJECT ${EXAMPLES_C})

set(EXAMPLES_INC "")
foreach(h ${EXAMPLES_H})
    get_filename_component(d ${h} DIRECTORY)
    list(APPEND EXAMPLES_INC ${d})
endforeach()
list(REMOVE_DUPLICATES EXAMPLES_INC)

target_include_directories(bm_examples PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EXAMPLES_INC}
)

target_link_libraries(bm_examples PUBLIC bm_api)