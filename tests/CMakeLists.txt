
cmake_minimum_required(VERSION 3.16)

FILE(GLOB TEST_SRCS "*.cpp")

set(PROJECT_ROOT "..")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories(${PROJECT_ROOT}/include)

add_executable(unit_tests ${CORE_SRCS} ${TEST_SRCS})
target_link_libraries(unit_tests gtest pthread ${CMAKE_DL_LIBS})
add_compile_definitions(TESTS_RUN)

add_subdirectory(fail_lib)
add_subdirectory(succes_lib)