cmake_minimum_required(VERSION 3.10)
project(Licznik C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    ../src/main.c
    ../src/movement.c
    ../src/win_man.c
    ../src/num_man.c
)

add_executable(licznik ${SOURCES})

target_link_libraries(licznik m ncurses)
