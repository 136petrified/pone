cmake_minimum_required(VERSION 3.30.0)
project(pone)

set(CMAKE_HOME_DIRECTORY $ENV{USERPROFILE})
set(CMAKE_CURRENT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set($ENV{HOME} CMAKE_HOME_DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)

set(CXXFLAGS "-g -Wall -Wfatal-errors -Werror -pedantic -Iheaders/src")
set(CMAKE_CXX_FLAGS ${CXXFLAGS})

enable_testing()
include(FetchContent)

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

set(GDAPP_DIR ${PROJECT_SOURCE_DIR}/src/app)
set(GAME_DIR ${PROJECT_SOURCE_DIR}/src/game)
set(YAML_DIR ${PROJECT_SOURCE_DIR}/src/yaml)
set(PONE_TEST_DIR ${PROJECT_SOURCE_DIR}/test)

set(ALL_GDAPP_FILES
${GDAPP_DIR}/pone.cpp
${GDAPP_DIR}/pone.hpp
)

set(ALL_GAME_FILES
${GAME_DIR}/pone_avl.cpp
${GAME_DIR}/pone_avl.hpp
${GAME_DIR}/pone_board.cpp
${GAME_DIR}/pone_board.hpp
${GAME_DIR}/pone_const.hpp
${GAME_DIR}/pone_cursor.cpp
${GAME_DIR}/pone_cursor.hpp
${GAME_DIR}/pone_except.cpp
${GAME_DIR}/pone_except.hpp
${GAME_DIR}/pone_game.cpp
${GAME_DIR}/pone_game.hpp
${GAME_DIR}/pone_gate.cpp
${GAME_DIR}/pone_gate.hpp
${GAME_DIR}/pone_gui.cpp
${GAME_DIR}/pone_gui.hpp
${GAME_DIR}/pone_tile.cpp
${GAME_DIR}/pone_tile.hpp
)

set(ALL_YAML_FILES
${YAML_DIR}/yaml_except.cpp
${YAML_DIR}/yaml_except.hpp
${YAML_DIR}/yaml_generator.cpp
${YAML_DIR}/yaml_generator.hpp
${YAML_DIR}/yaml_parser.cpp
${YAML_DIR}/yaml_parser.hpp
${YAML_DIR}/yaml_tokenizer.cpp
${YAML_DIR}/yaml_tokenizer.hpp
${YAML_DIR}/yaml_utils.cpp
${YAML_DIR}/yaml_utils.hpp
)

set(ALL_TEST_FILES
${}
)

add_executable(
all_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/poneavl_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponecursor_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponegame_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponegui_tests.cpp
${PROJECT_SOURCE_DIR}/test/poneboard_tests.cpp
${PROJECT_SOURCE_DIR}/test/ponegate_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
avl_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/poneavl_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
ponetile_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/ponetile_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
ponecursor_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/ponecursor_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp

)

add_executable(
ponegame_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/ponegame_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
ponegui_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/ponegui_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
poneboard_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/poneboard_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

add_executable(
ponegate_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/ponegate_tests.cpp
${PROJECT_SOURCE_DIR}/test/gtestmain.cpp
)

include_directories(
    ${GTEST_ROOT}/googletest/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/app
    ${PROJECT_SOURCE_DIR}/src/game
    ${PROJECT_SOURCE_DIR}/src/yaml
)

target_include_directories(
    all_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    poneavl_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    ponetile_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    ponecursor_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    ponegame_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    ponegui_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    poneboard_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    ponegate_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(all_tests
                      GTest::gtest_main
)

target_link_libraries(avl_tests
                      GTest::gtest_main
)

target_link_libraries(ponetile_tests
                      GTest::gtest_main
)

target_link_libraries(ponecursor_tests
                      GTest::gtest_main
)

target_link_libraries(ponegame_tests
                      GTest::gtest_main
)

target_link_libraries(ponegui_tests
                      GTest::gtest_main
)

target_link_libraries(poneboard_tests
                      GTest::gtest_main
)

target_link_libraries(ponegate_tests
                      GTest::gtest_main
)

gtest_discover_tests(all_tests
    poneboard_tests
    ponetile_tests
    ponecursor_tests
    ponegui_tests
    poneboard_tests
    ponegate_tests
)
