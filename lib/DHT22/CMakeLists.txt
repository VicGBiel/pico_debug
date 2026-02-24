add_library(DHT22_Driver INTERFACE)

target_sources(DHT22_Driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/dht.c 
)

target_include_directories(DHT22_Driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR} 
)

target_link_libraries(DHT22_Driver INTERFACE
    pico_stdlib
    hardware_i2c 
    hardware_dma
)

