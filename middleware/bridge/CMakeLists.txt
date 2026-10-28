# middleware/bridge/CMakeLists.txt
#
# Per-folder library definition kept for parity with middleware/iossm and
# middleware/rstmgr. The top-level middleware/CMakeLists.txt globs every
# .c under middleware/ into bm_middleware, so this file is consumed only
# when bridge_mw is requested explicitly (e.g. unit-test harnesses).

cmake_minimum_required(VERSION 3.16)

file(GLOB BRIDGE_MW_SRCS "*.c")

add_library(bridge_mw STATIC ${BRIDGE_MW_SRCS})

target_include_directories(bridge_mw PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bridge_mw PUBLIC socfpga_drivers)

target_compile_features(bridge_mw PUBLIC c_std_99)
