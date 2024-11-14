set(UART_TEST_SRC_FILES
    uart_test.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    )

add_executable(uart_test.elf EXCLUDE_FROM_ALL ${UART_TEST_SRC_FILES})

add_executable(uart_test_ocram.elf EXCLUDE_FROM_ALL ${UART_TEST_SRC_FILES})

add_dependencies(test uart_test.elf uart_test_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(uart_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(uart_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(uart_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(uart_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_bin_file(uart_test_ocram.elf)
generate_bin_file(uart_test.elf)

target_include_directories(uart_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

target_include_directories(uart_test_ocram.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

if(BUILD_ARM)
    target_link_options( uart_test.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
    )

    target_link_options( uart_test_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
    )
else()
        target_link_options( uart_test.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
    )

    target_link_options( uart_test_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
    )
endif()
