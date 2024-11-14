
add_executable(sysmgr_unittest.elf EXCLUDE_FROM_ALL
    ${PROJECT_SOURCE_DIR}/test/unit/sysmgr/sysmgr_unittest.cpp
    ${PROJECT_SOURCE_DIR}/test/unit/sysmgr/sysmgr_ioctl_unittest.cpp
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr.c
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr_internal.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    )

add_dependencies(test sysmgr_unittest.elf)

target_link_libraries(sysmgr_unittest.elf GTest::gtest GTest::gtest_main)

target_compile_options(sysmgr_unittest.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG} -Wno-missing-field-initializers)

target_include_directories(sysmgr_unittest.elf PRIVATE
                            ${PROJECT_SOURCE_DIR}/test/unit/sanity
                            ${PROJECT_SOURCE_DIR}/test/unit/common
                            ${PROJECT_SOURCE_DIR}/inc/sysmgr
                            ${PROJECT_SOURCE_DIR}/inc/mmu
                            ${PROJECT_SOURCE_DIR}/inc/base
                            ${PROJECT_SOURCE_DIR}/inc/uart
                            ${PROJECT_SOURCE_DIR}/inc/rstmgr
                            ${PROJECT_SOURCE_DIR}/inc
                            ${googletest_SOURCE_DIR}/googletest/include
                            ${googletest_SOURCE_DIR}/googletest/samples)

generate_atf_sdimage(sysmgr_unittest.elf)

if(BUILD_ARM)
    target_link_options(sysmgr_unittest.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
        )

else()
    target_link_options(sysmgr_unittest.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        --specs=nosys.specs -mstrict-align
        )
endif()