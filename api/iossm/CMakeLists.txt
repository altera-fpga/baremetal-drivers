# api/iossm/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

file(GLOB IOSSM_API_SRCS "*.c")

add_library(iossm_api STATIC ${IOSSM_API_SRCS})

target_include_directories(iossm_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(iossm_api PUBLIC iossm_mw)

target_compile_features(iossm_api PUBLIC c_std_99)
