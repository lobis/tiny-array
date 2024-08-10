
cmake_minimum_required(VERSION 3.14)

project(tiny_array)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tiny_array INTERFACE)
add_library(tiny_array::tiny_array ALIAS tiny_array)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TinyArray_BuildTests variable is used to enable or disable tests (default is OFF)
option(TinyArray_BuildTests "Build tests for TinyArray" OFF)

if (TinyArray_BuildTests)
    add_subdirectory(tests)
endif ()
