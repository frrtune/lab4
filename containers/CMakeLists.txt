add_library(containers STATIC ${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.c)
target_include_directories(containers PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})