cmake_minimum_required(VERSION 3.16)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Curses)

if (CURSES_FOUND)
    file(GLOB_RECURSE SRCS "src/*.cpp")

    add_library(arcade_ncurses SHARED ${SRCS} ${CORE_SYSTEM})
    set_target_properties(arcade_ncurses PROPERTIES PREFIX "")

    target_include_directories(arcade_ncurses PRIVATE
        include
        ${CURSES_INCLUDE_DIR}
    )
    target_link_libraries(arcade_ncurses PRIVATE ${CURSES_LIBRARIES})
else()
    message("[WARNING]: Curses library not found, arcade_ncurses will not be compiled\n")
endif()