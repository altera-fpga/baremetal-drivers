if(BUILD_ARM)
    target_sources(alterametal PRIVATE mylibc.cpp bridge_helper.cpp fsbl_boot_help.c)
endif()
add_subdirectory(inc)
