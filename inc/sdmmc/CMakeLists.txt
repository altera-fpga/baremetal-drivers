target_sources(alterametal PRIVATE sdmmc.h sdmmc_internal.h sdmmc_regs.h)
    target_include_directories(alterametal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})