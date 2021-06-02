cmake_minimum_required(VERSION 3.16)

# lib dir for GNU
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# lib dir for WIN
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

string(TIMESTAMP BUILD_TIME "%s")
add_compile_definitions(BUILD_TIME=${BUILD_TIME})

# Menu libraries
# add_subdirectory(menu)

# Games libraries
add_subdirectory(games)

# Graphics libraries
add_subdirectory(graphics)