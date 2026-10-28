# middleware/iossm/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

file(GLOB IOSSM_MW_SRCS "*.c")

add_library(iossm_mw STATIC ${IOSSM_MW_SRCS})

target_include_directories(iossm_mw PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(iossm_mw PUBLIC socfpga_drivers)

target_compile_features(iossm_mw PUBLIC c_std_99)
