cmake_minimum_required(VERSION 4.2)
project(word_game C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(word_game
        main.c
        utils.c
        utils.h)
