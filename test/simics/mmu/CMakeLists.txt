
if(BUILD_ARM)
    set(MMU_TEST_SRC_FILES
        mmu_test.c
        ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
        ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
        ${PROJECT_SOURCE_DIR}/src/base/device.c
        ${PROJECT_SOURCE_DIR}/src/uart/uart.c
        ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
        ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
        ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
        )

    add_executable(mmu_test.elf EXCLUDE_FROM_ALL ${MMU_TEST_SRC_FILES})

    add_executable(mmu_test_ocram.elf EXCLUDE_FROM_ALL ${MMU_TEST_SRC_FILES})

    add_dependencies(test mmu_test.elf mmu_test_ocram.elf)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(mmu_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
        target_compile_options(mmu_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    else()
        target_compile_options(mmu_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
        target_compile_options(mmu_test_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    endif()

    generate_bin_file(mmu_test_ocram.elf)
generate_bin_file(mmu_test.elf)

    target_include_directories(mmu_test.elf PRIVATE
        ${PROJECT_SOURCE_DIR}/inc/uart
        ${PROJECT_SOURCE_DIR}/inc/rstmgr
        ${PROJECT_SOURCE_DIR}/inc/mmu
        ${PROJECT_SOURCE_DIR}/inc/base
        ${PROJECT_SOURCE_DIR}/inc
        )

    target_include_directories(mmu_test_ocram.elf PRIVATE
        ${PROJECT_SOURCE_DIR}/inc/uart
        ${PROJECT_SOURCE_DIR}/inc/rstmgr
        ${PROJECT_SOURCE_DIR}/inc/mmu
        ${PROJECT_SOURCE_DIR}/inc/base
        ${PROJECT_SOURCE_DIR}/inc
        )

    target_link_options( mmu_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )

    target_link_options( mmu_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align
    )
endif()
