target_sources(socfpga_drivers PRIVATE
    socfpga_gic.c
    socfpga_gic_reg.c
    )

target_include_directories(socfpga_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
