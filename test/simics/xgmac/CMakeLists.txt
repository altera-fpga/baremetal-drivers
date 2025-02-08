set(xgmac_TEST_SRC_FILES
    xgmac_test.c
    ${PROJECT_SOURCE_DIR}/helpers/mylibc.cpp
    ${PROJECT_SOURCE_DIR}/helpers/fsbl_boot_help.c
    ${PROJECT_SOURCE_DIR}/src/base/device.c
    ${PROJECT_SOURCE_DIR}/src/mmu/page_tables.cpp
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr.c
    ${PROJECT_SOURCE_DIR}/src/clkmgr/clkmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart.c
    ${PROJECT_SOURCE_DIR}/src/uart/uart_internal.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr.c
    ${PROJECT_SOURCE_DIR}/src/rstmgr/rstmgr_internal.c
    ${PROJECT_SOURCE_DIR}/src/xgmac/xgmac.c
    ${PROJECT_SOURCE_DIR}/src/xgmac/xgmac_internal.c
    ${PROJECT_SOURCE_DIR}/src/xgmac/mrvl_phy_helper.c
    )

add_executable(xgmac_test.elf EXCLUDE_FROM_ALL ${xgmac_TEST_SRC_FILES})

add_executable(xgmac_test_ocram.elf EXCLUDE_FROM_ALL ${xgmac_TEST_SRC_FILES})

add_dependencies(test xgmac_test.elf xgmac_test_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(xgmac_test.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
    target_compile_options(xgmac_test_ocram.elf PRIVATE -DFSBL_EXECUTION  ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(xgmac_test.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
    target_compile_options(xgmac_test_ocram.elf PRIVATE  -DFSBL_EXECUTION  ${DEFAULT_C_FLAGS_RELEASE})
endif()

generate_bin_file(xgmac_test_ocram.elf)
generate_bin_file(xgmac_test.elf)

target_include_directories(xgmac_test.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/xgmac
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/clkmgr
    ${PROJECT_SOURCE_DIR}/helpers/inc
    ${PROJECT_SOURCE_DIR}/inc
    )

target_include_directories(xgmac_test_ocram.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/inc/uart
    ${PROJECT_SOURCE_DIR}/inc/mmu
    ${PROJECT_SOURCE_DIR}/inc/rstmgr
    ${PROJECT_SOURCE_DIR}/inc/xgmac
    ${PROJECT_SOURCE_DIR}/inc/base
    ${PROJECT_SOURCE_DIR}/inc/clkmgr
    ${PROJECT_SOURCE_DIR}/helpers/inc
    ${PROJECT_SOURCE_DIR}/inc
    )

if(BUILD_ARM)
    target_link_options( xgmac_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0.ld
        --specs=nosys.specs -mstrict-align
    )

    target_link_options( xgmac_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
        --specs=nosys.specs -mstrict-align -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/xgmac/xgmac_test_ocram.map 
    )
else()
        target_link_options( xgmac_test.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
        --specs=nosys.specs
    )

    target_link_options( xgmac_test_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
        -march=rv32imac_zicsr_zba_zbb_zifencei -mabi=ilp32
        --specs=nosys.specs -Wl,-Map=${PROJECT_SOURCE_DIR}/test/simics/xgmac/xgmac_test_ocram.map 
    )
endif()
