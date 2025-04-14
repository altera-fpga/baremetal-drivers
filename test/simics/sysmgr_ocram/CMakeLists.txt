set(SYSMGR_TESTS_SRC_FILES
    sysmgr_tests.c
    ${PROJECT_SOURCE_DIR}/helpers/fsbl_boot_help.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr.c
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    )

add_executable(sysmgr_tests_ocram.elf EXCLUDE_FROM_ALL ${SYSMGR_TESTS_SRC_FILES})

add_dependencies(test sysmgr_tests_ocram.elf)

generate_bin_file(sysmgr_tests_ocram.elf)

target_include_directories(sysmgr_tests_ocram.elf PRIVATE
                    ${PROJECT_SOURCE_DIR}/inc/uart
                    ${PROJECT_SOURCE_DIR}/inc/mmu
                    ${PROJECT_SOURCE_DIR}/inc/base
                    ${PROJECT_SOURCE_DIR}/inc/sysmgr
                    ${PROJECT_SOURCE_DIR}/inc/rstmgr
                    ${PROJECT_SOURCE_DIR}/helpers/inc
                    ${PROJECT_SOURCE_DIR}/inc)                 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(sysmgr_tests_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(sysmgr_tests_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

if(BUILD_ARM)
    target_link_options( sysmgr_tests_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/sysmgr_ocram/sysmgr_tests_ocram.map 
    )
else()
    target_link_options( printf_hello_world_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/sysmgr_ocram/sysmgr_tests_ocram.map 
    )
endif()
