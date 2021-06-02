
cmake_minimum_required(VERSION 3.16)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(game_succes SHARED game_succes_lib.cpp)
add_library(graphic_succes SHARED graphic_succes_lib.cpp)
