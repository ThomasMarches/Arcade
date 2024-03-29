cmake_minimum_required(VERSION 3.16)

project(arcade-dependencies)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake")

if(NOT DEPENDENCY_DOWNLOAD_DIR)
    set(DEPENDENCY_DOWNLOAD_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/download")
endif(NOT DEPENDENCY_DOWNLOAD_DIR)

if(NOT DEPENDENCY_EXTRACT_DIR)
    set(DEPENDENCY_EXTRACT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/extract")
endif(NOT DEPENDENCY_EXTRACT_DIR)

if(NOT DEPENDENCY_INSTALL_DIR)
    set(DEPENDENCY_INSTALL_DIR "${PROJECT_SOURCE_DIR}")
endif(NOT DEPENDENCY_INSTALL_DIR)

message("\nFetch dependencies:")

find_package(SDL2)
if (NOT ${SDL2_FOUND} OR FORCE_FETCH_DEPENDENCIES)
    message("[INFO] Download SDL2")
    include(GetSDL2)
endif()

find_package(SDL2_ttf)
if (NOT ${SDL2_TTF_FOUND} OR FORCE_FETCH_DEPENDENCIES)
    message("[INFO] Download SDL2_ttf")
    include(GetSDL2_ttf)
endif()

message("")