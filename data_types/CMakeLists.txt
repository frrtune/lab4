add_library(data_types STATIC
    integer.c
    complex.c
)
target_include_directories(data_types PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core
)