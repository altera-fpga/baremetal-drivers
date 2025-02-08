target_sources(alterametal PRIVATE noc_firewall.h noc_firewall_internal.h noc_firewall_regs.h)
    target_include_directories(alterametal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})