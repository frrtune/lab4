cmake_minimum_required(VERSION 3.23)
project(lab4 C)
set(CMAKE_BUILD_TYPE Debug)

find_library(PDCURSES_LIB NAMES pdcurses libpdcurses PATHS "C:/msys64/mingw64/lib")
find_path(PDCURSES_INCLUDE NAMES curses.h pdcurses.h PATHS "C:/msys64/mingw64/include" "C:/msys64/mingw64/include/pdcurses")

add_subdirectory(containers)
add_subdirectory(core)
add_subdirectory(data_types)
add_subdirectory(ui)

add_executable(lab4
    ui.c  
)

target_link_libraries(lab4
    containers
    core
    data_types  
    ui
    ${PDCURSES_LIB}
)
