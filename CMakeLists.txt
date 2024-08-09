
cmake_minimum_required(VERSION 3.14)

project(tiny_array)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# TODO: Add optional skipping of tests (Note: I don't think this is needed since it's a header-only library)
add_subdirectory(tests)
