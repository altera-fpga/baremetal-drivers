cmake_minimum_required(VERSION 3.20)

add_library(socfpga_drivers STATIC)

# Options to exclude driver if needed.
set(DRIVER_EXCLUDE_DIRS
)

# Exclude specific source files (OSAL/RTOS dependent)
set(DRIVER_EXCLUDE_FILES_REGEX
  ".*/common/socfpga_interrupt\\.c$"
  ".*/common/libc_stub\\.c$"
  ".*/uart/socfpga_uart\\.c$"
)

file(GLOB children RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)

foreach(child ${children})
  if (NOT IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${child})
    continue()
  endif()

  # Always export header include path for this driver folder
  target_include_directories(socfpga_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${child})

  if (child IN_LIST DRIVER_EXCLUDE_DIRS)
    message(STATUS "Skipping driver folder sources: drivers/${child}")
    continue()
  endif()

  # The parent target collects driver sources below with GLOB_RECURSE.
  # Do not add each child CMakeLists.txt here, otherwise sources that are
  # explicitly listed in subdirectories can be added to socfpga_drivers twice.
endforeach()

target_include_directories(socfpga_drivers PUBLIC ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE DRV_C CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.c)
file(GLOB_RECURSE DRV_S CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.S)
file(GLOB_RECURSE DRV_s CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.s)

foreach(excl ${DRIVER_EXCLUDE_DIRS})
  list(FILTER DRV_C EXCLUDE REGEX ".*/${excl}/.*")
  list(FILTER DRV_S EXCLUDE REGEX ".*/${excl}/.*")
  list(FILTER DRV_s EXCLUDE REGEX ".*/${excl}/.*")
endforeach()

# Drop excluded files
foreach(rx ${DRIVER_EXCLUDE_FILES_REGEX})
  list(FILTER DRV_C EXCLUDE REGEX "${rx}")
  list(FILTER DRV_S EXCLUDE REGEX "${rx}")
  list(FILTER DRV_s EXCLUDE REGEX "${rx}")
endforeach()

target_sources(socfpga_drivers PRIVATE ${DRV_C} ${DRV_S} ${DRV_s})
