/*   Created:    2024-06-23
 *   Modified:   2026-05-04
 */

#include "pone_board.hpp"
#include "pone_const.hpp"
#include "pone_except.hpp"
#include "utils/except.h"
#include <format>
#include <stdexcept>

namespace pone {

// +----------------------------------+
// + Board constructors               +
// +----------------------------------+

Board::Board()
    : m_name{""}, m_length{0}, m_width{0}, m_numGates{0}, m_numTiles{0},
      m_cursor{Cursor{0, 0}} {}

Board::Board(const std::string &name, const int &length, const int &width)
    : m_name{name}, m_length{length}, m_width{width}, m_numGates{0},
      m_numTiles{0}, m_cursor{Cursor{0, 0}} {}

Board::Board(const std::string &name, const int &length, const int &width,
             const int &cursor_x, const int &cursor_y)
    : m_name{name}, m_length{length}, m_width{width}, m_numGates{0},
      m_numTiles{0}, m_cursor{Cursor{cursor_x, cursor_y}} {}

// +----------------------------------+
// + Board getters/setters            +
// +----------------------------------+

int Board::getLength() const {
    return m_length;
}

void Board::setLength(const int &length) {
    m_length = length;
}

std::string Board::getName() const {
    return m_name;
}

void Board::setName(const std::string &name) {
    m_name = name;
}

int Board::getWidth() const {
    return m_width;
}

void Board::setWidth(const int &width) {
    m_width = width;
}

TilePtr Board::getCursorTile() const {
    return m_cursor.getTile();
}

void Board::setCursorTile(const TilePtr &t) {
    m_cursor.setTile(t);
}

TilePtr Board::getTile(const std::string &name) const {
    TilePtr t;

    try {
        t = m_tileNamesMap.at(name);
    } catch (const std::out_of_range &e) {
        t = nullptr;
    }

    return t;
}

TilePtr Board::getTile(const int &x, const int &y) const {
    TilePtr t;

    try {
        t = m_tileCoordPairsMap.at(CoordPair{x, y});
    } catch (const std::out_of_range &e) {
        t = nullptr;
    }

    return t;
}

TilePtr Board::getTile(const TilePtr &t, const Direction &direction) const {
    if (t == nullptr) {
        ErrorMessage TILE_NULL{name::PONE_GLOBAL_NAME, name::BOARD_GETT3,
                               "Tile is null."};

        throw InvalidTileException(TILE_NULL);
    }

    int tileX = t->getX(), tileY = t->getY();

    switch (direction) {
    case UP:
        return getTile(tileX, tileY + 1);
    case DOWN:
        return getTile(tileX, tileY - 1);
    case LEFT:
        return getTile(tileX + 1, tileY);
    case RIGHT:
        return getTile(tileX - 1, tileY);
    default:
        ErrorMessage INVAL_DIR{name::PONE_GLOBAL_NAME, name::BOARD_GETT3,
                               "Invalid direction."};
        throw InvalidDirectionException(INVAL_DIR);
    }
}

GatePtr Board::getGate(const std::string &name) const {
    GatePtr target;

    try {
        target = m_gateNamesMap.at(name);
    } catch (const std::out_of_range &e) {
        target = nullptr;
    }

    return target;
}

GatePtr Board::getGate(const TilePtr &t1, const TilePtr &t2) const {
    if (t1 == nullptr) {
        ErrorMessage T1_NULL{name::PONE_GLOBAL_NAME, name::BOARD_GETG2,
                             "First tile is null."};
        throw InvalidTileException(T1_NULL);
    } else if (t2 == nullptr) {
        ErrorMessage T2_NULL{name::PONE_GLOBAL_NAME, name::BOARD_GETG2,
                             "Second tile is null"};
        throw InvalidTileException(T2_NULL);
    }

    GatePtr g;

    try {
        TilePair tp{t1, t2};
        g = m_gateTilePairsMap.at(tp);
    } catch (const std::out_of_range &) {
        g = nullptr;
    }

    return g;
}

GatePtr Board::getGate(const TilePtr &t, const Direction &d) const {
    if (t == nullptr) {
        ErrorMessage T_NULL{name::PONE_GLOBAL_NAME, name::BOARD_GETG3,
                            "Tile is null."};

        throw InvalidTileException(T_NULL);
    }

    TilePtr currentTile = m_cursor.getTile();

    switch (d) {
    case UP:
        return getGate(currentTile, getTile(currentTile, UP));
    case DOWN:
        return getGate(currentTile, getTile(currentTile, DOWN));
    case LEFT:
        return getGate(currentTile, getTile(currentTile, LEFT));
    case RIGHT:
        return getGate(currentTile, getTile(currentTile, RIGHT));
    default:
        ErrorMessage INVAL_DIR{name::PONE_GLOBAL_NAME, name::BOARD_GETG3,
                               "Invalid direction."};
        throw InvalidDirectionException(INVAL_DIR);
    }

    return nullptr;
}

// +----------------------------------+
// + Board functions                  +
// +----------------------------------+

bool Board::tileCoordEquals(const TilePtr &t1, const TilePtr &t2) const {
    return compareTileByCoords()(t1, t2) == 0;
}

bool Board::tileNameEquals(const TilePtr &t1, const TilePtr &t2) const {
    return compareTileByName()(t1, t2) == 0;
}

bool Board::gateTilePairEquals(const GatePtr &g1, const GatePtr &g2) const {
    return compareGateByTilePair()(g1, g2) == 0;
}

bool Board::gateNameEquals(const GatePtr &g1, const GatePtr &g2) const {
    return compareGateByName()(g1, g2) == 0;
}

void Board::add(const TilePtr &t) {
    m_tileNamesTree.insert(t);
    m_tileNamesMap[t->getName()] = t;

    m_tileCoordPairsTree.insert(t);
    m_tileCoordPairsMap[t->getCoordPair()] = t;
    ++m_numTiles;
}

void Board::remove(const TilePtr &t) {
    if (t == nullptr) {
        ErrorMessage T_NULL{name::PONE_GLOBAL_NAME, name::BOARD_REM1,
                            "Tile is null."};
        throw InvalidTileException(T_NULL);
    }

    try {
        m_tileNamesTree.remove(t);
        m_tileNamesMap.erase(t->getName());

        m_tileCoordPairsTree.remove(t);
        m_tileCoordPairsMap.erase(t->getCoordPair());
    } catch (const std::out_of_range &e) {
        ErrorMessage T_NF{
            name::PONE_GLOBAL_NAME, name::BOARD_REM1,
            std::format("Tile \"{}\" was not found.", t->getName())};
        throw InvalidTileException(T_NF);
    }
}

void Board::add(const GatePtr &g) {
    m_gateNamesTree.insert(g);
    m_gateNamesMap[g->getName()] = g;

    m_gateTilePairsTree.insert(g);
    m_gateTilePairsMap[g->getTilePair()] = g;
}

void Board::remove(const GatePtr &g) {
    if (g == nullptr) {
        ErrorMessage G_NULL{name::PONE_GLOBAL_NAME, name::BOARD_REM2,
                            "Gate is null."};
        throw InvalidGateException(G_NULL);
    }

    try {
        m_gateNamesTree.remove(g);
        m_gateNamesMap.erase(g->getName());

        m_gateTilePairsTree.remove(g);
        m_gateTilePairsMap.erase(g->getTilePair());
    } catch (const std::out_of_range &e) {
        ErrorMessage G_NF{
            name::PONE_GLOBAL_NAME, name::BOARD_REM2,
            std::format("Gate \"{}\" was not found.", g->getName())};
        throw InvalidGateException(G_NF);
    }
}

void Board::load(const std::string &filename) {
    // This will be attached to ponescript
    // May use JSON-like formatting to load created boards
}

void Board::save(const std::string &filename) {
    // Autogenerates a script
}

// +----------------------------------+
// + Board operations                 +
// +----------------------------------+

void Board::moveCursor(const Direction &d) {
    TilePtr prevTile = m_cursor.getTile();
    prevTile->setCursor(false);

    int cursorX = m_cursor.getX(), cursorY = m_cursor.getY();

    switch (d) {
    case UP:
        m_cursor.setY(cursorY + 1);
        break;
    case DOWN:
        m_cursor.setY(cursorY - 1);
        break;
    case LEFT:
        m_cursor.setX(cursorX - 1);
        break;
    case RIGHT:
        m_cursor.setX(cursorX + 1);
        break;
    default:
        ErrorMessage INVAL_DIR{name::PONE_GLOBAL_NAME, name::BOARD_MVCSR,
                               "Invalid direction."};
        throw InvalidDirectionException(INVAL_DIR);
    }

    m_cursor.setTile(getTile(prevTile, d));
    m_cursor.getTile()->setCursor(true);
}

bool Board::checkMove(const Direction &d) {
    // Check collision first

    TilePtr curr = m_cursor.getTile();
    TilePtr target = getTile(curr, d);
    if (target->isCollision())
        return false;
    else if (getGate(curr, target)) {
        return false;
    }

    return true;
}

void Board::rotateTile(const TilePtr &t, const Rotation &r) {
    // ! - DO NOT rotate non-directional tiles!!!

    if (t == nullptr) {
        ErrorMessage T_NULL{name::PONE_GLOBAL_NAME, name::BOARD_ROTT,
                            "Tile is null."};
        throw InvalidTileException(T_NULL);
    } else if (!t->isDirection()) {
        ErrorMessage T_ND{name::PONE_GLOBAL_NAME, name::BOARD_ROTT,
                          std::format("Tile \"{}\" is not a directional tile.",
                                      t->getName())};
        throw InvalidDirectionException(T_ND);
    }

    std::string dir = t->getType();

    if (r == CLOCKWISE)
        dir = clockwiseMap.at(dir);
    else if (r == COUNTER_CLOCKWISE)
        dir = counterClockwiseMap.at(dir);

    t->setType(dir);
}

void Board::rotateTiles(const std::string &color, const Rotation &r) {
    for (TilePtr &t : m_tileNamesTree.inorder()) {
        if (t->getColor() == color)
            rotateTile(t, r);
    }
}

bool Board::cursorOnGoal() const {
    return m_cursor.getTile()->isGoal();
}

bool Board::empty() const {
    return m_numTiles <= 0;
}

bool Board::full() const {
    return m_numTiles > m_length * m_width;
}

const std::unordered_map<std::string, std::string> Board::clockwiseMap = {
    {"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

const std::unordered_map<std::string, std::string> Board::counterClockwiseMap =
    {{"up", "left"}, {"left", "down"}, {"down", "right"}, {"right", "up"}};

Board::~Board() {}

} // namespace pone
