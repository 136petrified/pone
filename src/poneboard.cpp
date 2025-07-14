/*   Created:    06-23-2024
 *   Modified:   07-10-2025
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
    : length{0},
      width{0},
      tileCoordsTree{AVL<TilePtr>()},
      tileNamesTree{AVL<TilePtr>()},
      gateNamesTree{AVL<GatePtr>()},
      gateTilesTree{AVL<GatePtr>()},
      cursor{Cursor{0, 0}} {}

Board::Board(const int &length, const int &width)
    : length{length},
      width{width},
      tileCoordsTree{AVL<TilePtr>()},
      tileNamesTree{AVL<TilePtr>()},
      gateNamesTree{AVL<GatePtr>()},
      gateTilesTree{AVL<GatePtr>()},
      cursor{Cursor{0, 0}} {}

Board::Board(const int &length, const int &width, const int &cursor_x,
             const int &cursor_y)
    : length{length},
      width{width},
      tileCoordsTree{AVL<TilePtr>()},
      tileNamesTree{AVL<TilePtr>()},
      gateNamesTree{AVL<GatePtr>()},
      gateTilesTree{AVL<GatePtr>()},
      cursor{Cursor{cursor_x, cursor_y}} {}

// Board getter/setter functions
// ---------------------------------------------
int Board::getLength() const { return length; }

void Board::setLength(const int &length) { this->length = length; }

int Board::getWidth() const { return width; }

void Board::setWidth(const int &width) { this->width = width; }

TilePtr Board::getCursorTile() const { return cursor.getTile(); }

void Board::setCursorTile(TilePtr t) { cursor.setTile(t); }

TilePtr Board::getTile(const std::string &name) const {
    TilePtr tptr;

    try {
        tptr = tmap.at(name);
    } catch (const std::out_of_range &e) {
        tptr = nullptr;
    }

    return tptr;
}

TilePtr Board::getTile(const int &x, const int &y) const {return tmap.at()}

TilePtr Board::getTile(TilePtr t, const Direction &direction) const {
    if (t == nullptr) {
        // std::cerr << "[ERROR]: Tile does not exist." << std::endl;
        throw TileNotFoundException("Tile does not exist.");
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
            std::cerr << "[ERROR]: Invalid direction: " << direction
                      << std::endl;
            break;
    }

    return nullptr;
}

GatePtr Board::getGate(const std::string &name) const { return gmap.at(name); }

GatePtr Board::getGate(Tile *t1, Tile *t2) const {
    if (t1 == nullptr || t2 == nullptr) {  // Throw exception here
        std::cerr << "[ERROR]: Nonexistent tile cannot be used as an argument."
                  << std::endl;
    }

    GatePtr g;

    try {
        TilePair tp{t1, t2};
        g = gtmap.at(tp);
    } catch (const std::out_of_range &) {
        return nullptr;
    }

    return g;
}

GatePtr Board::getGate(TilePtr t, const Direction &direction) const {
    if (!t) {
        // Throw an exception here
        throw TileNotFoundException("Tile does not exist");
        return nullptr;
    }

    TilePtr currentTile = cursor.getTile();

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

bool Board::tileCoordEquals(const TilePtr t1, const TilePtr t2) const {
    return t1->getX() == t2->getX() && t1->getY() == t2->getY();
}

bool Board::tileNameEquals(const TilePtr t1, const TilePtr t2) const {
    return t1->getName() == t2->getName();
}

bool Board::gateTilesEquals(const GatePtr g1, const GatePtr g2) const {
    return g1->getTile1() == g2->getTile1() && g1->getTile2() == g2->getTile2();
}

bool Board::gateNameEquals(const GatePtr g1, const GatePtr g2) const {
    return g1->getName() == g2->getName();
}

void Board::insTile(int pos, TilePtr t) {
    // Leave pos as -1 to insert at last position by default
    if (pos <= -1) {
        tiles.push_back(t);
    } else if (pos < static_cast<int>(tiles.size())) {
        auto tilepos = tiles.begin() + pos;
        tiles.insert(tilepos, t);
    } else {
        std::cerr
            << "[ERROR] Attempted to insert tile into out-of-bounds position."
            << std::endl;
        return;  // Do NOT increment numTiles if this happens
    }

    tmap[t->getName()] = t;
    ++numTiles;
}

void Board::remTile(TilePtr t) {
    if (tiles.empty()) {
        // TODO: Error here
        return;
    }

    auto tilepos = std::find(tiles.begin(), tiles.end(), t);
    if (tilepos != tiles.end()) {
        tiles.erase(tilepos);
        tmap.erase(t->getName());
    } else {
        std::cerr << "[ERROR] Cannot find tile to remove." << std::endl;
        return;
    }

    --numTiles;
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
