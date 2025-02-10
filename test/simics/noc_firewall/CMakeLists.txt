set(noc_firewall_TEST_SRC_FILES
    noc_firewall_test.c
    ${PROJECT_SOURCE_DIR}/helpers/fsbl_boot_help.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/noc_firewall/noc_firewall.c
    ${PROJECT_SOURCE_DIR}/src/noc_firewall/noc_firewall_internal.c
    )

add_executable(noc_firewall_test.elf EXCLUDE_FROM_ALL ${noc_firewall_TEST_SRC_FILES})
add_executable(noc_firewall_test_ocram.elf EXCLUDE_FROM_ALL ${noc_firewall_TEST_SRC_FILES})

add_dependencies(test noc_firewall_test.elf)
add_dependencies(test noc_firewall_test_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(noc_firewall_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(noc_firewall_test_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(noc_firewall_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(noc_firewall_test_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_bin_file(noc_firewall_test.elf)
generate_bin_file(noc_firewall_test_ocram.elf)

target_include_directories(noc_firewall_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/noc_firewall
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/helpers/inc
    )

target_include_directories(noc_firewall_test_ocram.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/noc_firewall
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/helpers/inc
    )
    
if(BUILD_ARM)
    target_link_options( noc_firewall_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )

    target_link_options( noc_firewall_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/noc_firewall/noc_firewall_test_ocram.map
    )
    
else()
    target_link_options( noc_firewall_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
    )

    target_link_options( noc_firewall_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/noc_firewall/noc_firewall_test_ocram.map
    )
    
endif()
