
cmake_minimum_required(VERSION 3.14)

project(tiny_array_examples_cmake_usage)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        TinyArray
        GIT_REPOSITORY https://github.com/lobis/tiny-array.git
        GIT_TAG main # or a specific release tag
)
FetchContent_MakeAvailable(TinyArray)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE tiny_array::tiny_array)
