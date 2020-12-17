cmake_minimum_required(VERSION 3.17)
project(HangmanGame C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(include)

set(SRC main.c src/launcher.c src/game.c)
set(INCLUDE include/launcher.h include/game.h)
set(PROJECT_NAME HangmanGame)

add_executable(${PROJECT_NAME}
        ${SRC}
        ${INCLUDE}
        )