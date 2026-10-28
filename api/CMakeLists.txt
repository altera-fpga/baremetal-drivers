cmake_minimum_required(VERSION 3.20)

# Create a static library for all API code
add_library(bm_api STATIC)

# Recursively collect all API source and header files.
file(GLOB_RECURSE API_C CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*/*.c)
file(GLOB_RECURSE API_S CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*/*.S)
file(GLOB_RECURSE API_s CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*/*.s)
file(GLOB_RECURSE API_H CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*/*.h)

# Add sources to the library.
target_sources(bm_api PRIVATE ${API_C} ${API_S} ${API_s})
set(API_INC_DIRS "")
foreach(h ${API_H})
    get_filename_component(d ${h} DIRECTORY)
    list(APPEND API_INC_DIRS ${d})
endforeach()
list(REMOVE_DUPLICATES API_INC_DIRS)

# Add include directories
target_include_directories(bm_api PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}   # top-level api/
    ${API_INC_DIRS}             # all subfolders headers
)

# Link to middleware and drivers
target_link_libraries(bm_api PUBLIC bm_middleware socfpga_drivers)
