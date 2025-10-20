cmake_minimum_required(VERSION 3.30.0)
project(pone)

set(CMAKE_HOME_DIRECTORY $ENV{USERPROFILE})
set(CMAKE_CURRENT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set($ENV{HOME} CMAKE_HOME_DIRECTORY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)

set(CXXFLAGS "-g -fsanitize=address -Wall -Wfatal-errors -Werror -pedantic -Iheaders/src")
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

set(PONE_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(GDAPP_DIR ${PONE_SRC_DIR}/app)
set(GAME_DIR ${PONE_SRC_DIR}/game)
set(YAML_DIR ${PONE_SRC_DIR}/yaml)
set(PONE_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(GDAPP_TEST_DIR ${PONE_TEST_DIR}/app)
set(GAME_TEST_DIR ${PONE_TEST_DIR}/game)
set(YAML_TEST_DIR ${PONE_TEST_DIR}/yaml)

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
${GAME_DIR}/pone_linked_list.cpp
${GAME_DIR}/pone_linked_list.hpp
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

set(ALL_GDAPP_TEST_FILES
${GDAPP_TEST_DIR}/app_test.cpp
)

set(ALL_GAME_TEST_FILES
${GAME_TEST_DIR}/avl_test.cpp
${GAME_TEST_DIR}/board_test.cpp
${GAME_TEST_DIR}/cursor_test.cpp
${GAME_TEST_DIR}/game_test.cpp
${GAME_TEST_DIR}/gate_test.cpp
${GAME_TEST_DIR}/gui_test.cpp
${GAME_TEST_DIR}/tile_test.cpp
)

# set(ALL_YAML_TEST_FILES)

add_executable(
all_game_tests
${ALL_GAME_FILES}
${ALL_GAME_TEST_FILES}
)

add_executable(
avl_tests
# ${ALL_GAME_FILES}
${GAME_TEST_DIR}/avl_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
llist_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/linked_list_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
tile_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/tile_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
cursor_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/cursor_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp

)

add_executable(
game_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/game_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
gui_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/gui_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
board_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/board_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

add_executable(
gate_tests
${ALL_GAME_FILES}
${GAME_TEST_DIR}/gate_test.cpp
${GAME_TEST_DIR}/gtestmain.cpp
)

include_directories(
    ${GTEST_ROOT}/googletest/include
    ${PONE_SRC_DIR}
    ${PONE_SRC_DIR}/app
    ${PONE_SRC_DIR}/game
    ${PONE_SRC_DIR}/yaml
    ${PONE_TEST_DIR}
    ${PONE_TEST_DIR}/app
    ${PONE_TEST_DIR}/game
    ${PONE_TEST_DIR}/yaml
)

target_include_directories(
    all_game_tests PRIVATE ${PONE_SRC_DIR}
    avl_tests PRIVATE ${PONE_SRC_DIR}
    llist_tests PRIVATE ${PONE_SRC_DIR}
    tile_tests PRIVATE ${PONE_SRC_DIR}
    cursor_tests PRIVATE ${PONE_SRC_DIR}
    game_tests PRIVATE ${PONE_SRC_DIR}
    gui_tests PRIVATE ${PONE_SRC_DIR}
    board_tests PRIVATE ${PONE_SRC_DIR}
    gate_tests PRIVATE ${PONE_SRC_DIR}
)

target_link_libraries(all_game_tests
                      GTest::gtest_main
)

target_link_libraries(avl_tests
                      GTest::gtest_main
)

target_link_libraries(llist_tests
                      GTest::gtest_main
)

target_link_libraries(tile_tests
                      GTest::gtest_main
)

target_link_libraries(cursor_tests
                      GTest::gtest_main
)

target_link_libraries(game_tests
                      GTest::gtest_main
)

target_link_libraries(gui_tests
                      GTest::gtest_main
)

target_link_libraries(board_tests
                      GTest::gtest_main
)

target_link_libraries(gate_tests
                      GTest::gtest_main
)

gtest_discover_tests(all_game_tests
    avl_tests
    # llist_tests
    # board_tests
    # tile_tests
    # cursor_tests
    # gui_tests
    # board_tests
    # gate_tests
)
