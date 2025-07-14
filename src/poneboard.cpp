/*   Created:    06-23-2024
 *   Modified:   07-13-2025
 */

// TODO: Replace all printed errors with proper thrown errors

#include "poneboard.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "poneconst.hpp"
#include "poneexcept.hpp"

// Board constructors
// ---------------------------------------------
Board::Board()
    : m_length{0},
      m_width{0},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{0, 0}} {}

Board::Board(const int &length, const int &width)
    : m_length{length},
      m_width{width},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{0, 0}} {}

Board::Board(const int &length, const int &width, const int &cursor_x,
             const int &cursor_y)
    : m_length{length},
      m_width{width},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{cursor_x, cursor_y}} {}

// Board getter/setter functions
// ---------------------------------------------
int Board::getLength() const { return m_length; }

void Board::setLength(const int &length) { m_length = length; }

int Board::getWidth() const { return m_width; }

void Board::setWidth(const int &width) { m_width = width; }

TilePtr Board::getCursorTile() const { return m_cursor.getTile(); }

void Board::setCursorTile(TilePtr t) { m_cursor.setTile(t); }

TilePtr Board::getTile(const std::string &name) const {
    TilePtr tptr;

    try {
        tptr = m_tileNamesMap.at(name);
    } catch (const std::out_of_range &e) {
        tptr = nullptr;
    }

    return tptr;
}

TilePtr Board::getTile(const int &x, const int &y) const {
    TilePtr tptr;

    try {
        tptr = m_tileCoordPairsMap.at(CoordPair{x, y});
    } catch (const std::out_of_range &e) {
        tptr = nullptr;
    }

    return tptr;
}

TilePtr Board::getTile(TilePtr tptr, const Direction &direction) const {
    if (tptr == nullptr) {
        throw TileNotFoundException(tptr->getName());
    }

    int tileX = tptr->getX(), tileY = tptr->getY();

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
            std::cerr << "[ERROR]: Invalid direction: " << direction
                      << std::endl;
            break;
    }

    return nullptr;
}

GatePtr Board::getGate(const std::string &name) const {
    GatePtr gptr;

    try {
        gptr = m_gateNamesMap.at(name);
    } catch (const std::out_of_range &e) {
        gptr = nullptr;
    }

    return gptr;
}

GatePtr Board::getGate(TilePtr tptr1, TilePtr tptr2) const {
    if (tptr1 == nullptr || tptr2 == nullptr) {  // Throw exception here
                                                 // TODO: TileNoteFound for Gate
        std::cerr << "[ERROR]: Nonexistent tile cannot be used as an argument."
                  << std::endl;
    }

    GatePtr gptr;

    try {
        TilePair tp{tptr1, tptr2};
        gptr = m_gateTilePairsMap.at(tp);
    } catch (const std::out_of_range &) {
        gptr = nullptr;
    }

    return gptr;
}

GatePtr Board::getGate(TilePtr tptr, const Direction &direction) const {
    if (tptr == nullptr) {
        // Throw an exception here
        // throw TileNotFoundException(tptr);
    }

    TilePtr currentTile = m_cursor.getTile();

    switch (direction) {
        case UP:
            return getGate(currentTile, getTile(currentTile, UP));
        case DOWN:
            return getGate(currentTile, getTile(currentTile, DOWN));
        case LEFT:
            return getGate(currentTile, getTile(currentTile, LEFT));
        case RIGHT:
            return getGate(currentTile, getTile(currentTile, RIGHT));
        default:
            std::cerr << "[ERROR]: Invalid direction: " << direction
                      << std::endl;
            break;
    }

    return nullptr;
}

// Board functions
// ---------------------------------------------

bool Board::tileCoordEquals(const TilePtr tptr1, const TilePtr tptr2) const {
    return compareTileByCoords()(tptr1, tptr2) == 0;
}

bool Board::tileNameEquals(const TilePtr tptr1, const TilePtr tptr2) const {
    return compareTileByName()(tptr1, tptr2) == 0;
}

bool Board::gateTilePairEquals(const GatePtr gptr1, const GatePtr gptr2) const {
    return compareGateByTilePair()(gptr1, gptr2) == 0;
}

bool Board::gateNameEquals(const GatePtr gptr1, const GatePtr gptr2) const {
    return compareGateByName()(gptr1, gptr2) == 0;
}

void Board::insTile(TilePtr tptr) {
    m_tileNamesTree.insert(tptr);
    m_tileNamesMap[tptr->getName()] = tptr;

    m_tileCoordPairsTree.insert(tptr);
    m_tileCoordPairsMap[tptr->getCoordPair()] = tptr;
    ++m_numTiles;
}

void Board::remTile(TilePtr tptr) {
    m_tileNamesTree.remove(tptr);
    try {
        m_tileNamesMap.erase(tptr->getName());
    } catch (const std::out_of_range &e) {
        // TODO: TileNotFoundException
    }
}

// TODO: What if a tile is missing from a gate?

void Board::insGate(int pos, GatePtr g) {
    // Leave pos as 0 to insert at last position by default
    if (pos <= -1) {
        gates.push_back(g);
    } else if (pos < static_cast<int>(gates.size())) {
        auto gatepos = gates.begin() + pos;
        gates.insert(gatepos, g);
    } else {
        std::cerr
            << "[ERROR] Attempted to insert tile into out-of-bounds position."
            << std::endl;
        return;
    }

    gtmap[g->getTilePair()] = g;
    ++numGates;
}

void Board::remGate(GatePtr g) {
    if (gates.empty()) {
        throw GateEmptyException(g);
    }
    auto gatepos = std::find(gates.begin(), gates.end(), g);
    if (gatepos != gates.end())
        gates.erase(gatepos);
    else {
        std::cerr << "[ERROR] Cannot find gate to remove." << std::endl;
        return;
    }

    --numGates;
}

void Board::load(const std::string &filename) {
    // This will be attached to ponescript
    // May use JSON-like formatting to load created boards
}

void Board::save(const std::string &filename) {
    // Autogenerates a script
}

// Board commands
// ---------------------------------------------

void Board::moveCursor(const Direction &direction) {
    TilePtr prevTile = cursor.getTile();
    prevTile->setCursor(false);

    int cursorX = cursor.getX(), cursorY = cursor.getY();

    switch (direction) {
        case UP:
            cursor.setY(cursorY + 1);
            break;
        case DOWN:
            cursor.setY(cursorY - 1);
            break;
        case LEFT:
            cursor.setX(cursorX - 1);
            break;
        case RIGHT:
            cursor.setX(cursorX + 1);
            break;
        default:
            std::cerr << "[ERROR]: Move cursor failed given direction "
                      << direction << std::endl;
            break;
    }

    cursor.setTile(getTile(prevTile, direction));
    cursor.getTile()->setCursor(true);
}

bool Board::checkMove(const Direction &direction) {
    // Check collision first

    TilePtr currentTile = cursor.getTile();
    TilePtr target = getTile(currentTile, direction);
    if (target->isCollision())
        return false;
    else if (getGate(currentTile, target)) {
        return false;
    }

    return true;
}

void Board::rotateTile(Tile *t, const Rotation &rotation) {
    // ! - DO NOT rotate non-directional tiles!!!
    if (!t->isDirection()) {
        return;  // Do nothing
    }

    std::string dir = t->getType();

    if (rotation == CLOCKWISE)
        dir = clockwiseMap.at(dir);
    else if (rotation == COUNTER_CLOCKWISE)
        dir = counterClockwiseMap.at(dir);

    t->setType(dir);
}

void Board::rotateTiles(const std::string &color, const Rotation &rotation) {
    for (Tile *t : tiles) {
        if (t->getColor() == color) rotateTile(t, rotation);
    }
}

void Board::toggleGate(Tile *t1, Tile *t2) {
    if (t1->isCollision() || t2->isCollision()) {
        throw GateCollisionException(t1);
    }

    TilePair tp{t1, t2};

    Gate *g;
    try {
        g = gtmap.at(tp);
    } catch (const std::out_of_range &) {
        return;
        // TODO: Error here
    }

    g->isActive() ? g->setInactive() : g->setActive();
}

bool Board::isGoal() const { return cursor.getTile()->isGoal(); }

bool Board::empty() const { return tiles.empty(); }

bool Board::full() const { return numTiles > length * width; }

const std::unordered_map<std::string, std::string> Board::clockwiseMap = {
    {"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

const std::unordered_map<std::string, std::string> Board::counterClockwiseMap =
    {{"up", "left"}, {"left", "down"}, {"down", "right"}, {"right", "up"}};

Board::~Board() {}
