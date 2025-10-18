/*   Created:    06-23-2024
 *   Modified:   07-18-2025
 */

#include "poneboard.hpp"

#include <stdexcept>

#include "poneconst.hpp"
#include "poneexcept.hpp"

// Board constructors
// ---------------------------------------------
Board::Board()
    : m_name{""},
      m_length{0},
      m_width{0},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{0, 0}} {}

Board::Board(const std::string &name, const int &length, const int &width)
    : m_name{name},
      m_length{length},
      m_width{width},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{0, 0}} {}

Board::Board(const std::string &name, const int &length, const int &width,
             const int &cursor_x, const int &cursor_y)
    : m_name{name},
      m_length{length},
      m_width{width},
      m_numGates{0},
      m_numTiles{0},
      m_cursor{Cursor{cursor_x, cursor_y}} {}

// Board getter/setter functions
// ---------------------------------------------

int Board::getLength() const { return m_length; }

void Board::setLength(const int &length) { m_length = length; }

std::string Board::getName() const { return m_name; }

void Board::setName(const std::string &name) { m_name = name; }

int Board::getWidth() const { return m_width; }

void Board::setWidth(const int &width) { m_width = width; }

TilePtr Board::getCursorTile() const { return m_cursor.getTile(); }

void Board::setCursorTile(const TilePtr &tptr) { m_cursor.setTile(tptr); }

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

TilePtr Board::getTile(const TilePtr &tptr, const Direction &direction) const {
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
            throw InvalidDirectionException();
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

GatePtr Board::getGate(const TilePtr &tptr1, const TilePtr &tptr2) const {
    if (tptr1 == nullptr || tptr2 == nullptr) {
        throw InvalidTileException();  // From GateException
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

GatePtr Board::getGate(const TilePtr &tptr, const Direction &direction) const {
    if (tptr == nullptr) {
        throw InvalidTileException();
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
            throw InvalidDirectionException();
    }

    return nullptr;
}

// Board functions
// ---------------------------------------------

bool Board::tileCoordEquals(const TilePtr &tptr1, const TilePtr &tptr2) const {
    return compareTileByCoords()(tptr1, tptr2) == 0;
}

bool Board::tileNameEquals(const TilePtr &tptr1, const TilePtr &tptr2) const {
    return compareTileByName()(tptr1, tptr2) == 0;
}

bool Board::gateTilePairEquals(const GatePtr &gptr1,
                               const GatePtr &gptr2) const {
    return compareGateByTilePair()(gptr1, gptr2) == 0;
}

bool Board::gateNameEquals(const GatePtr &gptr1, const GatePtr &gptr2) const {
    return compareGateByName()(gptr1, gptr2) == 0;
}

void Board::insTile(const TilePtr &tptr) {
    m_tileNamesTree.insert(tptr);
    m_tileNamesMap[tptr->getName()] = tptr;

    m_tileCoordPairsTree.insert(tptr);
    m_tileCoordPairsMap[tptr->getCoordPair()] = tptr;
    ++m_numTiles;
}

void Board::remTile(const TilePtr &tptr) {
    try {
        m_tileNamesTree.remove(tptr);
        m_tileNamesMap.erase(tptr->getName());

        m_tileCoordPairsTree.remove(tptr);
        m_tileCoordPairsMap.erase(tptr->getCoordPair());
    } catch (const std::out_of_range &e) {
        throw(tptr == nullptr) ? TileNotFoundException()
                               : TileNotFoundException(tptr->getName());
    }
}

void Board::insGate(const GatePtr &gptr) {
    m_gateNamesTree.insert(gptr);
    m_gateNamesMap[gptr->getName()] = gptr;

    m_gateTilePairsTree.insert(gptr);
    m_gateTilePairsMap[gptr->getTilePair()] = gptr;
}

void Board::remGate(const GatePtr &gptr) {
    try {
        m_gateNamesTree.remove(gptr);
        m_gateNamesMap.erase(gptr->getName());

        m_gateTilePairsTree.remove(gptr);
        m_gateTilePairsMap.erase(gptr->getTilePair());
    } catch (const std::out_of_range &e) {
        throw(gptr == nullptr) ? GateNotFoundException()
                               : GateNotFoundException(gptr->getName());
    }
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
    TilePtr prevTile = m_cursor.getTile();
    prevTile->setCursor(false);

    int cursorX = m_cursor.getX(), cursorY = m_cursor.getY();

    switch (direction) {
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
            throw InvalidDirectionException();
    }

    m_cursor.setTile(getTile(prevTile, direction));
    m_cursor.getTile()->setCursor(true);
}

bool Board::checkMove(const Direction &direction) {
    // Check collision first

    TilePtr currentTile = m_cursor.getTile();
    TilePtr target = getTile(currentTile, direction);
    if (target->isCollision())
        return false;
    else if (getGate(currentTile, target)) {
        return false;
    }

    return true;
}

void Board::rotateTile(const TilePtr &tptr, const Rotation &rotation) {
    // ! - DO NOT rotate non-directional tiles!!!
    if (!tptr->isDirection()) {
        throw InvalidDirectionException();
    }

    std::string dir = tptr->getType();

    if (rotation == CLOCKWISE)
        dir = clockwiseMap.at(dir);
    else if (rotation == COUNTER_CLOCKWISE)
        dir = counterClockwiseMap.at(dir);

    tptr->setType(dir);
}

void Board::rotateTiles(const std::string &color, const Rotation &rotation) {
    for (TilePtr &tptr : m_tileNamesTree.inorder()) {
        if (tptr->getColor() == color) rotateTile(tptr, rotation);
    }
}
void Board::toggleGate(const TilePtr &tptr1, const TilePtr &tptr2) {
    if (tptr1->isCollision() || tptr2->isCollision()) {
        throw GateCollisionException(tptr1);
    }

    GatePtr gptr;
    try {
        gptr = m_gateTilePairsMap.at(TilePair{tptr1, tptr2});
    } catch (std::out_of_range &e) {
        return;
    }

    gptr->isActive() ? gptr->setInactive() : gptr->setActive();
}

bool Board::isGoal() const { return m_cursor.getTile()->isGoal(); }

bool Board::empty() const { return m_numTiles <= 0; }

bool Board::full() const { return m_numTiles > m_length * m_width; }

const std::unordered_map<std::string, std::string> Board::clockwiseMap = {
    {"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

const std::unordered_map<std::string, std::string> Board::counterClockwiseMap =
    {{"up", "left"}, {"left", "down"}, {"down", "right"}, {"right", "up"}};

Board::~Board() {}
