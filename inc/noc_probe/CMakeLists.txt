target_sources(alterametal PRIVATE noc_probe.h noc_probe_internal.h noc_probe_regs.h)
    target_include_directories(alterametal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
