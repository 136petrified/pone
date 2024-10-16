cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(pone)

set(CMAKE_HOME_DIRECTORY $ENV{USERPROFILE})
set($ENV{HOME} CMAKE_HOME_DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)


set(CMAKE_MAKE_PROGRAM ${PROJECT_SOURCE_DIR}/ninja-win/ninja.exe)

set(CMAKE_C_COMPILER ${PROJECT_SOURCE_DIR}/compile/gcc.exe)
set(CMAKE_CXX_COMPILER {PROJECT_SOURCE_DIR}/compile/g++.exe)

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
                      Gtest::gtest_main
)

gtest_discover_tests(ponetile_tests
                     ponecursor_tests
                     ponegame_tests
                     ponegui_tests
                     poneboard_tests 
)