cmake_minimum_required(VERSION 3.20)

# Create object library first
add_library(platform_obj OBJECT)

if(PLAT STREQUAL "agilex5")
    add_subdirectory(agilex5)
elseif(PLAT STREQUAL "agilex3")
    add_subdirectory(agilex3)
else()
    message(FATAL_ERROR "Unknown PLAT='${PLAT}' (must be agilex5 or agilex3)")
endif()

# Create real static library from collected objects
add_library(platform STATIC $<TARGET_OBJECTS:platform_obj>)

# Export `platform/` AND `platform/${PLAT}/include/` as PUBLIC so the includes
# propagate to any target that links the `platform` library. platform_def.h
# lives under platform/${PLAT}/include/, so consumers (drivers, apps) get it
# automatically by linking `platform` instead of having to spell the path out
# again in their own target_include_directories().
target_include_directories(platform PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/${PLAT}/include
)
