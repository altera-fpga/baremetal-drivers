# Automatically pick up all .c files in this folder
file(GLOB UART_SRC "*.c")
file(GLOB UART_INC "*.h")

add_library(uart STATIC ${UART_SRC} ${UART_INC})

target_include_directories(uart
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
