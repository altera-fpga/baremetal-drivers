add_executable(clkmgr_unittest.elf EXCLUDE_FROM_ALL
    ${PROJECT_SOURCE_DIR}/test/unit/clkmgr/clkmgr_unittest.cpp
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr.c
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    )

add_dependencies(test clkmgr_unittest.elf)

target_link_libraries(clkmgr_unittest.elf GTest::gtest GTest::gtest_main)

target_compile_options(clkmgr_unittest.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG} -Wno-missing-field-initializers)

target_include_directories(clkmgr_unittest.elf PRIVATE
                            ${PROJECT_SOURCE_DIR}/test/unit/sanity
                            ${PROJECT_SOURCE_DIR}/test/unit/common
                            ${PROJECT_SOURCE_DIR}/inc/clkmgr
                            ${PROJECT_SOURCE_DIR}/inc/rstmgr
                            ${PROJECT_SOURCE_DIR}/inc/mmu
                            ${PROJECT_SOURCE_DIR}/inc/base
                            ${PROJECT_SOURCE_DIR}/inc/uart
                            ${PROJECT_SOURCE_DIR}/inc
                            ${googletest_SOURCE_DIR}/googletest/include
                            ${googletest_SOURCE_DIR}/googletest/samples)

generate_atf_sdimage(clkmgr_unittest.elf)

if(BUILD_ARM)
    target_link_options(clkmgr_unittest.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
        )

else()
    target_link_options(clkmgr_unittest.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        --specs=nosys.specs -mstrict-align
        )
endif()
