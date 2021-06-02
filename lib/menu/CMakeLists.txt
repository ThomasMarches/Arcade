cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SRCS "src/*.cpp")

add_library(arcade_menu SHARED ${SRCS} ${CORE_SYSTEM})
set_target_properties(arcade_menu PROPERTIES PREFIX "")

target_include_directories(arcade_menu PRIVATE
    include
)