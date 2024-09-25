cmake_minimum_required(VERSION 3.18.0)

project(SAT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

aux_source_directory(src SOURCES)
add_executable(main ${SOURCES})