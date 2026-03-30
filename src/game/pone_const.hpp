/*   Created:    2024-08-15
 *   Modified:   2026-03-30
 */

#pragma once

#include <string_view>

namespace pone {
// Directional constants

/**
 * All possible directions that a cursor can move towards.
 */
enum Direction { UP, DOWN, LEFT, RIGHT };

/**
 * All possible rotation for a directional tile.
 */
enum Rotation { CLOCKWISE, COUNTER_CLOCKWISE };

namespace name {

// Start of pone::Board names

inline constexpr std::string_view BOARD_BOARD_1 = "Board::Board()";
inline constexpr std::string_view BOARD_BOARD_2 =
    "Board::Board(const std::string &, const int &, const int &)";
inline constexpr std::string_view BOARD_BOARD_3 =
    "Board::Board(const std::string &, const int &, const int &, const int &, "
    "const int &)";
inline constexpr std::string_view BOARD_GETL = "Board::getLength()";
inline constexpr std::string_view BOARD_SETL = "Board::setLength(const int &)";
inline constexpr std::string_view BOARD_GETNAME = "Board::getName()";
inline constexpr std::string_view BOARD_GETW    = "Board::getWidth()";
inline constexpr std::string_view BOARD_SETW = "Board::setWidth(const int &)";
inline constexpr std::string_view BOARD_GETTILE_1 =
    "Board::getTile(const std::string &)";
inline constexpr std::string_view BOARD_GETTILE_2 =
    "Board::getTile(const int &, const int &)";
inline constexpr std::string_view BOARD_GETTILE_3 =
    "Board::getTile(const TilePtr &, const Direction &)";
inline constexpr std::string_view BOARD_GETGATE_1 =
    "Board::getGate(const std::string &)";
inline constexpr std::string_view BOARD_GETGATE_2 =
    "Board::getGate(const TilePtr &, const TilePtr &)";
inline constexpr std::string_view BOARD_GETGATE_3 =
    "Board::getGate(const TilePtr &, const Direction &direction)";
inline constexpr std::string_view BOARD_GETCSRT = "Board::getCursorTile()";
inline constexpr std::string_view BOARD_TCOORDEQ =
    "Board::tileCoordEquals(const TilePtr &, const Tile &)";
inline constexpr std::string_view BOARD_TNAMEEQ =
    "Board::tileNameEquals(const TilePtr &, const TilePtr &)";
inline constexpr std::string_view BOARD_GTPEQ =
    "Board::gateTilePairEquals(const GatePtr &, const GatePtr &)";
inline constexpr std::string_view BOARD_GNAMEEQ =
    "Board::gateNameEquals(const GatePtr &, const GatePtr &)";
inline constexpr std::string_view BOARD_ADD_1 = "Board::add(const TilePtr &)";
inline constexpr std::string_view BOARD_REM_1 =
    "Board::remove(const TilePtr &)";
inline constexpr std::string_view BOARD_ADD_2 =
    "Board::add(const GatePtr &gptr)";
inline constexpr std::string_view BOARD_REM_2 =
    "Board::remove(const GatePtr &)";
inline constexpr std::string_view BOARD_LOAD =
    "Board::load(const std::string &)";
inline constexpr std::string_view BOARD_SAVE =
    "Board::save(const std::string &)";
inline constexpr std::string_view BOARD_EMPTY = "Board::empty()";
inline constexpr std::string_view BOARD_FULL  = "Board::full()";
inline constexpr std::string_view BOARD_MVCSR =
    "Board::moveCursor(const Direction &)";
inline constexpr std::string_view BOARD_CHKMV =
    "Board::checkMove(const Direction &)";
inline constexpr std::string_view BOARD_ROTT =
    "Board::rotateTile(const TilePtr &, const Rotation &)";
inline constexpr std::string_view BOARD_ROTTS =
    "Board::rotateTiles(const std::string &, const Rotation &)";
inline constexpr std::string_view BOARD_TOGG =
    "Board::toggleGate(const TilePtr &, const TilePtr &)";
inline constexpr std::string_view BOARD_CSRGOAL = "Board::cursorOnGoal()";
inline constexpr std::string_view BOARD_BOARDD  = "Board::~Board()";
}  // namespace name

}  // namespace pone
