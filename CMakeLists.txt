cmake_minimum_required(VERSION 3.22)
project(ncurses_test)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lmenu -lncurses")

add_executable(ncurses_test
        main.cpp)

target_link_libraries(main ${CURSES_LIBRARIES})