set(TIMER_TEST_SRC_FILES
    timer_test.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/timer/timer.c
    ${PROJECT_SOURCE_DIR}/src/timer/timer_internal.c
    )

add_executable(timer_test.elf EXCLUDE_FROM_ALL ${TIMER_TEST_SRC_FILES})

add_executable(timer_test_ocram.elf EXCLUDE_FROM_ALL ${TIMER_TEST_SRC_FILES})

add_dependencies(test timer_test.elf timer_test_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(timer_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(timer_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(timer_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(timer_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_bin_file(timer_test_ocram.elf)
generate_bin_file(timer_test.elf)

target_include_directories(timer_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/timer
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

target_include_directories(timer_test_ocram.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/timer
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

if(BUILD_ARM)
    target_link_options( timer_test.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
    )

    target_link_options( timer_test_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
    )
else()
        target_link_options( timer_test.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
    )

    target_link_options( timer_test_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
    )
endif()
