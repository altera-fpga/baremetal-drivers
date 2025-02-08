set(PRINTF_HELLO_WORLD_TEST_SRC_FILES
    printf_hello_world.c
    ${PROJECT_SOURCE_DIR}/helpers/fsbl_boot_help.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    )

add_executable(printf_hello_world_ocram.elf EXCLUDE_FROM_ALL ${PRINTF_HELLO_WORLD_TEST_SRC_FILES})
add_executable(printf_hello_world.elf EXCLUDE_FROM_ALL ${PRINTF_HELLO_WORLD_TEST_SRC_FILES})

add_dependencies(test printf_hello_world_ocram.elf)
add_dependencies(test printf_hello_world.elf)

generate_bin_file(printf_hello_world_ocram.elf)
generate_bin_file(printf_hello_world.elf)


target_include_directories(printf_hello_world.elf PRIVATE
                    ${PROJECT_SOURCE_DIR}/inc/uart
                    ${PROJECT_SOURCE_DIR}/inc/mmu
                    ${PROJECT_SOURCE_DIR}/inc/rstmgr
                    ${PROJECT_SOURCE_DIR}/inc/base
                    ${PROJECT_SOURCE_DIR}/helpers/inc
                    ${PROJECT_SOURCE_DIR}/inc)

target_include_directories(printf_hello_world_ocram.elf PRIVATE
                    ${PROJECT_SOURCE_DIR}/inc/uart
                    ${PROJECT_SOURCE_DIR}/inc/mmu
                    ${PROJECT_SOURCE_DIR}/inc/rstmgr
                    ${PROJECT_SOURCE_DIR}/inc/base
                    ${PROJECT_SOURCE_DIR}/helpers/inc
                    ${PROJECT_SOURCE_DIR}/inc)                 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(printf_hello_world_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(printf_hello_world.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(printf_hello_world_ocram.elf PRIVATE -DFSBL_EXECUTION ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(printf_hello_world.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

if(BUILD_ARM)
    target_link_options( printf_hello_world.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )
    target_link_options( printf_hello_world_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/hello-world/printf_hello_world_ocram.map 
    )
else()
    target_link_options( printf_hello_world.elf PRIVATE
    -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
    )
    target_link_options( printf_hello_world_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/hello-world/printf_hello_world_ocram.map 
    )
endif()
