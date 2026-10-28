cmake_minimum_required(VERSION 3.20)

add_library(bm_middleware STATIC)

# Collect ALL sources recursively in middleware
file(GLOB_RECURSE MW_C CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.c)
file(GLOB_RECURSE MW_S CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.S)
file(GLOB_RECURSE MW_s CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.s)
file(GLOB_RECURSE MW_H CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.h)

target_sources(bm_middleware PRIVATE ${MW_C} ${MW_S} ${MW_s})

# Include every directory in middleware (so headers work)
file(GLOB_RECURSE MW_H CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.h)
set(MW_INC_DIRS "")
foreach(h ${MW_H})
  get_filename_component(d ${h} DIRECTORY)
  list(APPEND MW_INC_DIRS ${d})
endforeach()
list(REMOVE_DUPLICATES MW_INC_DIRS)

target_link_libraries(bm_middleware PUBLIC socfpga_drivers)

target_include_directories(bm_middleware PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${MW_INC_DIRS}
)