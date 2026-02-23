add_library(SCD41_Driver INTERFACE)

target_sources(SCD41_Driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/scd4x_i2c.c 
    ${CMAKE_CURRENT_LIST_DIR}/sensirion_common.c 
    ${CMAKE_CURRENT_LIST_DIR}/sensirion_i2c_hal.c 
    ${CMAKE_CURRENT_LIST_DIR}/sensirion_i2c.c
)

target_include_directories(SCD41_Driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(SCD41_Driver INTERFACE
    pico_stdlib
    hardware_i2c 
)