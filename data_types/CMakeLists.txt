add_library(data_types STATIC ${CMAKE_CURRENT_SOURCE_DIR}/complex.c)
add_library(data_types STATIC ${CMAKE_CURRENT_SOURCE_DIR}/integer.c)
target_include_directories(data_types PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})