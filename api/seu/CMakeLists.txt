# api/seu/CMakeLists.txt
#
# NOTE: This file is present for consistency with other api/ subdirectories.
# The parent api/CMakeLists.txt uses GLOB_RECURSE to collect all .c sources
# under api/, so seu_api.c is picked up automatically without requiring an
# explicit add_subdirectory() call.

cmake_minimum_required(VERSION 3.16)

file(GLOB SEU_API_SRCS "*.c")

add_library(seu_api STATIC ${SEU_API_SRCS})

target_include_directories(seu_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(seu_api PUBLIC c_std_99)
