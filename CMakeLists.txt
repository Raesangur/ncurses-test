cmake_minimum_required(VERSION 3.22)
project(ncurses_test)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_EXE_LINKER_FLAGS "-lmenu -lncurses ${CMAKE_EXE_LINKER_FLAGS}")
string(STRIP ${CMAKE_EXE_LINKER_FLAGS} CMAKE_EXE_LINKER_FLAGS)

SET(WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wunused                            # warn on anything being unused.
        -Wconversion                        # warn on type conversions that may lose data.
        -Wsign-conversion                   # warn on sign conversions.
        -Wnull-dereference                  # warn if a null dereference is detected.
        -Wdouble-promotion                  # warn if float is implicit promoted to double.
        -Wmisleading-indentation            # warn if statement is not part of the previous `if`, `else`, `for`, `while`.
        -Wformat                            # warn on security issues around functions that format output (ie printf).
        -Walloca                            # warn on use of `alloca` function for stack-based dynamic allocation.
        -Winvalid-pch                       # warn on precompiled header errors.

        -Wno-unused-function                # do not warn on unused functions.
        -Wno-sign-conversion                # do not warn about operations between signed and unsigned integer types.
        -Wno-double-promotion               # do not warn about converting a float to a double.

        -fpermissive
    )

add_executable(ncurses_test
        main.cpp)

target_link_libraries(ncurses_test ${CMAKE_EXE_LINKER_FLAGS})
target_compile_options(ncurses_test PRIVATE ${WARNINGS})
