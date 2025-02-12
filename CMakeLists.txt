cmake_minimum_required(VERSION 3.30.0)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(pone)

set(CMAKE_HOME_DIRECTORY $ENV{USERPROFILE})
set($ENV{HOME} CMAKE_HOME_DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)

set(CXXFLAGS "--std=c++20 -g -Wall -Wfatal-errors -Werror -pedantic")
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

# set(CMAKE_C_COMPILER ${PROJECT_SOURCE_DIR}/compile/gcc.exe)
# set(CMAKE_CXX_COMPILER {PROJECT_SOURCE_DIR}/compile/g++.exe)

enable_testing()
include(FetchContent)

# add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(GTEST_LIBRARY ${PROJECT_SOURCE_DIR}/build/_deps/googletest-src)
set(GTEST_INCLUDE_DIR ${GTEST_LIBRARY}/googletest/include)
set(GTEST_MAIN_LIBRARY ${GTEST_LIBRARY}/googletest/lib/libgtest_main.a)

find_package(GTest REQUIRED)

add_executable(
all_tests 
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponecursor_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponegame_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponegui_tests.cpp
${PROJECT_SOURCE_DIR}/test/poneboard_tests.cpp
)

add_executable(
ponetile_tests 
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
)

add_executable(
ponecursor_tests
${PROJECT_SOURCE_DIR}/test/ponecursor_tests.cpp
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

include_directories(
    ${GTEST_ROOT}/googletest/include
)

target_link_libraries(all_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

target_link_libraries(ponetile_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

target_link_libraries(ponecursor_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

target_link_libraries(ponegame_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

target_link_libraries(ponegui_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

target_link_libraries(poneboard_tests
                      ${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
                      GTest::gtest_main
)

gtest_discover_tests(all_tests
)
