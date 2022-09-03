cmake_minimum_required(VERSION 3.14)
project(adc_array)

set(CMAKE_CXX_STANDARD 17)

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# do not build tests for release build
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tests)
endif ()
