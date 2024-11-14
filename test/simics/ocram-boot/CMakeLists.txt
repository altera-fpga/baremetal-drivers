add_executable(boot_ocram.elf EXCLUDE_FROM_ALL simple_main.cpp)

add_dependencies(test boot_ocram.elf)

generate_bin_file(boot_ocram.elf)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(boot_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_DEBUG})
else()
    target_compile_options(boot_ocram.elf PRIVATE ${DEFAULT_C_FLAGS_RELEASE})
endif()

if(BUILD_ARM)
    target_link_options( boot_ocram.elf PRIVATE
        -T${PROJECT_SOURCE_DIR}/build/aarch64/core0_ocram.ld
    )
else()
    target_link_options( boot_ocram.elf PRIVATE
        -T ${PROJECT_SOURCE_DIR}/build/rv32/core0_ocram.ld
    )
endif()
