cmake_minimum_required(VERSION 3.20)

# Reusable app utilities (NOT startup, NOT main)
add_library(bm_app STATIC
	../lib/lib_string.c
	../lib/lib_time.c
	../lib/lib_printf.c
	../lib/lib_parse.c
	../lib/cache_maintenance.S
)

# Export include dir(s) for headers under src/
target_include_directories(bm_app PUBLIC ${CMAKE_CURRENT_LIST_DIR})
