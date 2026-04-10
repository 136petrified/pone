/*   Created:    2024-08-15
 *   Modified:   2026-04-08
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
inline constexpr std::string_view PONE_GLOBAL_NAME = "pone::";

// Start of pone::Board names

inline constexpr std::string_view BOARD_BOARD1 = "Board::Board()";
inline constexpr std::string_view BOARD_BOARD2 =
    "Board::Board(const std::string &, const int &, const int &)";
inline constexpr std::string_view BOARD_BOARD3 =
    "Board::Board(const std::string &, const int &, const int &, const int &, "
    "const int &)";
inline constexpr std::string_view BOARD_GETL = "Board::getLength()";
inline constexpr std::string_view BOARD_SETL = "Board::setLength(const int &)";
inline constexpr std::string_view BOARD_GETNAME = "Board::getName()";
inline constexpr std::string_view BOARD_GETW    = "Board::getWidth()";
inline constexpr std::string_view BOARD_SETW = "Board::setWidth(const int &)";
inline constexpr std::string_view BOARD_GETT1 =
    "Board::getTile(const std::string &)";
inline constexpr std::string_view BOARD_GETT2 =
    "Board::getTile(const int &, const int &)";
inline constexpr std::string_view BOARD_GETT3 =
    "Board::getTile(const TilePtr &, const Direction &)";
inline constexpr std::string_view BOARD_GETG1 =
    "Board::getGate(const std::string &)";
inline constexpr std::string_view BOARD_GETG2 =
    "Board::getGate(const TilePtr &, const TilePtr &)";
inline constexpr std::string_view BOARD_GETG3 =
    "Board::getGate(const TilePtr &, const Direction &)";
inline constexpr std::string_view BOARD_GETCSRT = "Board::getCursorTile()";
inline constexpr std::string_view BOARD_TCOORDEQ =
    "Board::tileCoordEquals(const TilePtr &, const Tile &)";
inline constexpr std::string_view BOARD_TNAMEEQ =
    "Board::tileNameEquals(const TilePtr &, const TilePtr &)";
inline constexpr std::string_view BOARD_GTPEQ =
    "Board::gateTilePairEquals(const GatePtr &, const GatePtr &)";
inline constexpr std::string_view BOARD_GNAMEEQ =
    "Board::gateNameEquals(const GatePtr &, const GatePtr &)";
inline constexpr std::string_view BOARD_ADD1 = "Board::add(const TilePtr &)";
inline constexpr std::string_view BOARD_REM1 = "Board::remove(const TilePtr &)";
inline constexpr std::string_view BOARD_ADD2 =
    "Board::add(const GatePtr &gptr)";
inline constexpr std::string_view BOARD_REM2 = "Board::remove(const GatePtr &)";
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
    "Board::toggleGate(const GatePtr &)";
inline constexpr std::string_view BOARD_CSRGOAL = "Board::cursorOnGoal()";
inline constexpr std::string_view BOARD_BOARDD  = "Board::~Board()";

// End of pone::Board names

// Start of pone::Cursor names

inline constexpr std::string_view CURSOR_CURSOR_1 = "Cursor::Cursor()";
inline constexpr std::string_view CURSOR_CURSOR_2 =
    "Cursor::Cursor(const int &, const int &)";
inline constexpr std::string_view CURSOR_CURSOR_3 =
    "Cursor::Cursor(const CoordPair &)";
inline constexpr std::string_view CURSOR_CURSOR_4 = "Cursor::Cursor(TilePtr)";
inline constexpr std::string_view CURSOR_GETX     = "Cursor::setX(const int &)";
inline constexpr std::string_view CURSOR_SETX     = "Cursor::getY()";
inline constexpr std::string_view CURSOR_GETY     = "Cursor::setY(const int &)";
inline constexpr std::string_view CURSOR_GETCRDPAIR = "Cursor::getCoordPair()";
inline constexpr std::string_view CURSOR_SETT    = "Cursor::setTile(TilePtr)";
inline constexpr std::string_view CURSOR_GETT    = "Cursor::getTile()";
inline constexpr std::string_view CURSOR_CURSORD = "Cursor::~Cursor()";

// End of pone::Cursor names

// Start of pone::Gate names

inline constexpr std::string_view GATE_GATE1 = "Gate::Gate()";
inline constexpr std::string_view GATE_GATE2 =
    "Gate::Gate(TilePtr, TilePtr, const std::string &, const std::string &, "
    "bool)";
inline constexpr std::string_view GATE_GATE3  = "Gate::Gate(const Gate &)";
inline constexpr std::string_view GATE_OPASGN = "Gate::operator=(const Gate &)";
inline constexpr std::string_view GATE_GETT1  = "Gate::getTile1()";
inline constexpr std::string_view GATE_SETT1  = "Gate::setTile1(TilePtr)";
inline constexpr std::string_view GATE_GETT2  = "Gate::getTile2()";
inline constexpr std::string_view GATE_SETT2  = "Gate::setTile2(TilePtr)";
inline constexpr std::string_view GATE_GETTP  = "Gate::getTilePair()";
inline constexpr std::string_view GATE_SETTP  = "Gate::setTilePair(TilePair)";
inline constexpr std::string_view GATE_GETCLR = "Gate::getColor()";
inline constexpr std::string_view GATE_SETCLR =
    "Gate::setColor(const std::string &)";
inline constexpr std::string_view GATE_GETID   = "Gate::getID()";
inline constexpr std::string_view GATE_SETID   = "Gate::setID(int)";
inline constexpr std::string_view GATE_GETNAME = "Gate::getName()";
inline constexpr std::string_view GATE_SETNAME =
    "Gate::setName(const std::string &)";
inline constexpr std::string_view GATE_SETINACTIVE = "Gate::setInactive()";
inline constexpr std::string_view GATE_SETACTIVE   = "Gate::setActive()";
inline constexpr std::string_view GATE_ISACTIVE    = "Gate::isActive()";
inline constexpr std::string_view GATE_PRINT = "Gate::print(std::ostream &)";

// End of pone::Gate names

// Start of pone::GUI names

// End of pone::GUI names

// Start of pone::Tile names
inline constexpr std::string_view TILE_TILE1 = "Tile::Tile()";
inline constexpr std::string_view TILE_TILE2 =
    "Tile::Tile(const std::string &, const int &, const int &, const int &, "
    "const std::string &, const std::string &, bool)";
inline constexpr std::string_view TILE_TILE3  = "Tile::Tile(const Tile &)";
inline constexpr std::string_view TILE_OPASGN = "Tile::operator=(const Tile &)";
inline constexpr std::string_view TILE_GETX   = "Tile::getX()";
inline constexpr std::string_view TILE_SETX   = "Tile::setX(const int &)";
inline constexpr std::string_view TILE_GETY   = "Tile::getY()";
inline constexpr std::string_view TILE_SETY   = "Tile::setY(const int &)";
inline constexpr std::string_view TILE_GETCRDPAIR = "Tile::getCoordPair()";
inline constexpr std::string_view TILE_GETCLR     = "Tile::getColor()";
inline constexpr std::string_view TILE_SETCLR =
    "Tile::setColor(const std::string &)";
inline constexpr std::string_view TILE_GETTYPE = "Tile::getType()";
inline constexpr std::string_view TILE_SETTYPE =
    "Tile::setType(const std::string &)";
inline constexpr std::string_view TILE_SETCSR  = "Tile::setCursor(bool)";
inline constexpr std::string_view TILE_GETID   = "Tile::getID()";
inline constexpr std::string_view TILE_SETID   = "Tile::setID(int)";
inline constexpr std::string_view TILE_GETNAME = "Tile::getName()";
inline constexpr std::string_view TILE_SETNAME =
    "Tile::setName(const std::string &)";
inline constexpr std::string_view TILE_ISCOLL    = "Tile::isCollision()";
inline constexpr std::string_view TILE_ISCSR     = "Tile::isCursor()";
inline constexpr std::string_view TILE_ISDIR     = "Tile::isDirection()";
inline constexpr std::string_view TILE_ISEMPTY   = "Tile::isEmpty()";
inline constexpr std::string_view TILE_ISGSWITCH = "Tile::isGateSwitch()";
inline constexpr std::string_view TILE_ISGOAL    = "Tile::isGoal()";
inline constexpr std::string_view TILE_ISTSWITCH = "Tile::isTileSwitch()";
inline constexpr std::string_view TILE_ISTYPE =
    "Tile::isType(const std::string &)";
inline constexpr std::string_view TILE_PRINT = "Tile::print(std::ostream &)";

}  // namespace name

}  // namespace pone
