cmake_minimum_required(VERSION 3.10.2)
project(pone)

add_executable(ponetile_tests ponetile_tests.cpp)
add_executable(ponecursor_tests ponetile_tests.cpp)
add_executable(ponegame_tests ponegame_tests.cpp)
add_executable(ponegui_tests ponegui_tests.cpp)
add_executable(poneboard_tests poneboard_tests.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)