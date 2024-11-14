set(spi_TEST_SRC_FILES
    spi_test.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/spi/spi.c
    ${PROJECT_SOURCE_DIR}/src/spi/spi_internal.c
    )

add_executable(spi_test.elf EXCLUDE_FROM_ALL ${spi_TEST_SRC_FILES})

add_executable(spi_test_ocram.elf EXCLUDE_FROM_ALL ${spi_TEST_SRC_FILES})

add_dependencies(test spi_test.elf spi_test_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(spi_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(spi_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(spi_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(spi_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_bin_file(spi_test_ocram.elf)
generate_bin_file(spi_test.elf)

target_include_directories(spi_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/spi
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

target_include_directories(spi_test_ocram.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/spi
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )

if(BUILD_ARM)
    target_link_options( spi_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )

    target_link_options( spi_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align
    )
else()
        target_link_options( spi_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
        --specs=nosys.specs
    )

    target_link_options( spi_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
        --specs=nosys.specs
    )
endif()
