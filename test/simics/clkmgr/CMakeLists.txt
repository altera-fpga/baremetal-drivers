set(CLKMGR_TEST_SRC_FILES
    clkmgr_test.c
    ${PROJECT_SOURCE_DIR}/helpers/fsbl_boot_help.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr.c
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr_internal.c
    )

add_executable(clkmgr_test_ocram.elf EXCLUDE_FROM_ALL ${CLKMGR_TEST_SRC_FILES})
add_executable(clkmgr_test.elf EXCLUDE_FROM_ALL ${CLKMGR_TEST_SRC_FILES})

add_dependencies(test clkmgr_test_ocram.elf)
add_dependencies(test clkmgr_test.elf)

generate_bin_file(clkmgr_test_ocram.elf)
generate_bin_file(clkmgr_test.elf)


target_include_directories(clkmgr_test.elf PRIVATE
                    ${PROJECT_SOURCE_DIR}/inc/uart
                    ${PROJECT_SOURCE_DIR}/inc/mmu
                    ${PROJECT_SOURCE_DIR}/inc/rstmgr
                    ${PROJECT_SOURCE_DIR}/inc/clkmgr
                    ${PROJECT_SOURCE_DIR}/inc/base
                    ${PROJECT_SOURCE_DIR}/helpers/inc
                    ${PROJECT_SOURCE_DIR}/inc)

target_include_directories(clkmgr_test_ocram.elf PRIVATE
                    ${PROJECT_SOURCE_DIR}/inc/uart
                    ${PROJECT_SOURCE_DIR}/inc/mmu
                    ${PROJECT_SOURCE_DIR}/inc/rstmgr
                    ${PROJECT_SOURCE_DIR}/inc/clkmgr
                    ${PROJECT_SOURCE_DIR}/inc/base
                    ${PROJECT_SOURCE_DIR}/helpers/inc
                    ${PROJECT_SOURCE_DIR}/inc)                 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(clkmgr_test_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(clkmgr_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(clkmgr_test_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(clkmgr_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

if(BUILD_ARM)
    target_link_options( clkmgr_test.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )
    target_link_options( clkmgr_test_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/clkmgr/clkmgr_test_ocram.map 
    )
else()
    target_link_options( clkmgr_test.elf PRIVATE
    -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
    )
    target_link_options( clkmgr_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/clkmgr/clkmgr_test_ocram.map 
    )
endif()
