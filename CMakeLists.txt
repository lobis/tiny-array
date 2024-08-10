
cmake_minimum_required(VERSION 3.14)

project(tiny_array)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tiny_array INTERFACE)
add_library(tiny_array::tiny_array ALIAS tiny_array)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Note: Maybe add optional skipping of tests. I don't think this is needed since it's a header-only library
add_subdirectory(tests)
