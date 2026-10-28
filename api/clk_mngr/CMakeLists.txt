# api/clk_mngr/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Find all C source files in this directory
file(GLOB CLK_MNGR_API_SRCS "*.c")

# Create a static library from all .c files
add_library(clk_mngr_api STATIC ${CLK_MNGR_API_SRCS})

# Include directories for consumers (app layer)
target_include_directories(clk_mngr_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(clk_mngr_api PUBLIC socfpga_drivers)

# Optional: enforce C99 standard
target_compile_features(clk_mngr_api PUBLIC c_std_99)
