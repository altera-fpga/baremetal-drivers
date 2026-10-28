# api/dma/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

# Find all C source files in this directory
file(GLOB DMA_API_SRCS "*.c")

# Create a static library from all .c files
add_library(dma_api STATIC ${DMA_API_SRCS})

# Include directories for consumers (app layer)
target_include_directories(dma_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Optional: enforce C99 standard
target_compile_features(dma_api PUBLIC c_std_99)
