target_sources(socfpga_drivers   PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/socfpga_mbox_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/socfpga_sip_handler.c
    )

target_include_directories(socfpga_drivers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
