target_sources(platform_obj PRIVATE
    platform_setup.c
    clk_mngr_platform.c
)

target_include_directories(platform_obj PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/api/clk_mngr
)