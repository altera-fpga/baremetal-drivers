# Automatically pick up all .c files in this folder
file(GLOB RSTMGR_SRC "*.c")
file(GLOB RSTMGR_INC "*.h")

add_library(rstmgr STATIC ${RSTMGR_SRC} ${RSTMGR_INC})

target_include_directories(rstmgr
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
