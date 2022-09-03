
# https://google.github.io/googletest/quickstart-cmake.html

cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TESTING_EXECUTABLE "test_${PROJECT_NAME}")

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${TESTING_EXECUTABLE} ${SOURCES})

target_link_libraries(
        ${TESTING_EXECUTABLE} PUBLIC
        gtest_main
        ${PROJECT_NAME}
)

include(GoogleTest)

gtest_add_tests(
        TARGET ${TESTING_EXECUTABLE}
        SOURCES ${SOURCES}
)
