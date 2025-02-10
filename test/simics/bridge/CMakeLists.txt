set(bridge_TEST_SRC_FILES
    bridge_test.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/helpers/bridge_helper.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr.c
    ${PROJECT_SOURCE_DIR}/src/sysmgr/sysmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/timer/timer.c
    ${PROJECT_SOURCE_DIR}/src/timer/timer_internal.c
    )

add_executable(bridge_test.elf EXCLUDE_FROM_ALL ${bridge_TEST_SRC_FILES})

add_dependencies(test bridge_test.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(bridge_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})

else()
    target_compile_options(bridge_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})

endif()

generate_atf_sdimage(bridge_test.elf)

target_include_directories(bridge_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/sysmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/helpers/inc
    ${PROJECT_SOURCE_DIR}/inc/timer
    )


if(BUILD_ARM)
    target_link_options( bridge_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )
else()
        target_link_options( bridge_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
        --specs=nosys.specs
    )
endif()