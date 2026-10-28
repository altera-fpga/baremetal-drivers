# api/bridge/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

file(GLOB BRIDGE_API_SRCS "*.c")

add_library(bridge_api STATIC ${BRIDGE_API_SRCS})

target_include_directories(bridge_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bridge_api PUBLIC bridge_mw)

target_compile_features(bridge_api PUBLIC c_std_99)
