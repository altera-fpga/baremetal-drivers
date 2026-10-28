target_sources(socfpga_drivers PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/socfpga_rst_mngr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/socfpga_rst_mngr_ll.c
)

target_include_directories(socfpga_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
