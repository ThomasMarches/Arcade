cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

project(arcade VERSION 1.0.0 LANGUAGES CXX)

if(FETCH_DEPENDENCIES OR FORCE_FETCH_DEPENDENCIES)
    # Configure and build dependencies in config
    if (FORCE_FETCH_DEPENDENCIES)
        execute_process(COMMAND ${CMAKE_COMMAND}
            -B "${PROJECT_SOURCE_DIR}/dependencies/build" . -DFORCE_FETCH_DEPENDENCIES=True
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/dependencies"
        )
    else()
        execute_process(COMMAND ${CMAKE_COMMAND}
            -B "${PROJECT_SOURCE_DIR}/dependencies/build" .
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/dependencies"
        )
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND}
        --build "${PROJECT_SOURCE_DIR}/dependencies/build"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/dependencies"
    )
endif()
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/dependencies")
list(APPEND SDL2TTFDIR "${PROJECT_SOURCE_DIR}/dependencies")

include_directories(
    "resources"
    "include"
    "include/Library"
)

file(GLOB_RECURSE CORE_SYSTEM "src_shared/*.cpp")
add_subdirectory(lib)

file(GLOB_RECURSE CORE_SRCS "src/*.cpp" "src_shared/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

# APPLE COMPILATION
if(APPLE)
endif()

# LINUX COMPILATION
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # enable_testing()
    # add_test(NAME testss COMMAND test_criterion)
    add_subdirectory(tests)
endif()

# WINDOWS COMPILATION
if (WIN32)
endif()

add_executable(arcade ${CORE_SRCS})
target_link_libraries(arcade ${CMAKE_DL_LIBS})