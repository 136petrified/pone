cmake_minimum_required(VERSION 3.10.2)
project(pone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_directory(googletest)
include(GoogleTest)
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

gtest_discover_tests(
                      ponetile_tests
                      ponecursor_tests
                      ponegame_tests
                      ponegui_tests
                      poneboard_tests
)