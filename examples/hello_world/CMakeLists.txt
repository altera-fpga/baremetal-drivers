cmake_minimum_required(VERSION 3.5...3.28)

include(FetchContent)

# disable building tests
set(BUILD_TESTS OFF)

# Include baremetal drivers as a dependency
# Usually, we'd use GIT_REPOSITORY in FetchContent.
# In this case, we want to use the local version of baremetal repo, for CI testing purpose.
FetchContent_Declare(
    esw_bare
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/../..
)

# Fetch the baremetal code
FetchContent_MakeAvailable(esw_bare)

# linker script
set(ALTERAMETAL_LINKER_SCRIPT "${esw_bare_SOURCE_DIR}/build/aarch64/core0_ocram.ld")

# project
project(bm_hello_world C CXX ASM)

# target
add_executable(hello_world.elf)
generate_bin_file(hello_world.elf)

# sources
target_sources(hello_world.elf
    PRIVATE
        hello_world.c
)

# link to the baremetal library
target_link_libraries(hello_world.elf PRIVATE
    alterametal
)

# specify linker script
target_link_options(hello_world.elf PRIVATE
    -T${ALTERAMETAL_LINKER_SCRIPT}
)
