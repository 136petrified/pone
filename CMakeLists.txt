cmake_minimum_required(VERSION 3.30.0)
# set(CMAKE_MAKE_PROGRAM ninja)
project(pone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)

set(CMAKE_C_COMPILER C:/msys64/ucrt64/bin/gcc.exe)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
ponetile_tests 
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
)

add_executable(
ponecursor_tests
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
)

add_executable(
ponegame_tests
${PROJECT_SOURCE_DIR}/test/ponegame_tests.cpp
)

add_executable(
ponegui_tests
${PROJECT_SOURCE_DIR}/test/ponegui_tests.cpp
)

add_executable(
poneboard_tests
${PROJECT_SOURCE_DIR}/test/poneboard_tests.cpp
)

target_link_libraries(ponetile_tests
                      ponecursor_tests
                      ponegame_tests
                      ponegui_tests
                      poneboard_tests
                      Gtest::gtest_main)

gtest_discover_tests(ponetile_tests
                     ponecursor_tests
                     ponegame_tests
                     ponegui_tests
                     poneboard_tests 
)