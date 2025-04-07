target_sources(alterametal PRIVATE ecc.h ecc_internal.h ecc_regs.h)
    target_include_directories(alterametal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})