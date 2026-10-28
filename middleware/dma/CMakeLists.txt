# Automatically pick up all .c files in this folder
file(GLOB DMA_SRC "*.c")
file(GLOB DMA_INC "*.h")

add_library(dma STATIC ${DMA_SRC} ${DMA_INC})

target_include_directories(dma
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
