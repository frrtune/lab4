add_library(ui STATIC ${CMAKE_CURRENT_SOURCE_DIR}/ui.c)
target_include_directories(ui PUBLIC  
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/containers
    ${CMAKE_SOURCE_DIR}/data_types
    ${CMAKE_SOURCE_DIR}/core
)
target_link_libraries(ui
    containers
    data_types
)