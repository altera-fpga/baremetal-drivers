add_executable(atf_boot.elf EXCLUDE_FROM_ALL
    simple_main.cpp
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    )

target_include_directories(atf_boot.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc
    )


add_dependencies(test atf_boot.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(atf_boot.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(atf_boot.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_atf_sdimage(atf_boot.elf)

if(BUILD_ARM)
    target_link_options( atf_boot.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
    )
else()
        target_link_options( atf_boot.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
    )
endif()