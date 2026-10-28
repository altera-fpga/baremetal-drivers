# api/ecc/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

file(GLOB ECC_API_SRCS "*.c")

add_library(ecc_api STATIC ${ECC_API_SRCS})

target_include_directories(ecc_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ecc_api PUBLIC socfpga_drivers)

target_compile_features(ecc_api PUBLIC c_std_99)
