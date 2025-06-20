/*   Created:    06-23-2024
 *   Modified:   06-17-2025
 */

// TODO: Replace all printed errors with proper thrown errors

#include "poneboard.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "poneconst.hpp"
#include "poneexcept.hpp"

// Board constructors
// ---------------------------------------------
Board::Board()
    : length{0},
      width{0},
      tiles{TileList()},
      gates{GateList()},
      cursor{Cursor{0, 0}} {}

Board::Board(const int &length, const int &width)
    : length{length},
      width{width},
      tiles{TileList()},
      gates{GateList()},
      cursor{Cursor{0, 0}} {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile t = Tile{i, j, "none", "empty"};
            insTile(i * j, &t);
        }
    }
}

Board::Board(const int &length, const int &width, const int &cursor_x,
             const int &cursor_y)
    : length{length},
      width{width},
      tiles{TileList()},
      gates{GateList()},
      cursor{Cursor{cursor_x, cursor_y}} {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile t = Tile{i, j, "none", "empty"};
            insTile(i * j, &t);
        }
    }
}

// Board getter/setter functions
// ---------------------------------------------
int Board::getLength() const { return length; }

void Board::setLength(const int &length) { this->length = length; }

int Board::getWidth() const { return width; }

void Board::setWidth(const int &width) { this->width = width; }

Tile *Board::getCursorTile() const { return cursor.getTile(); }

void Board::setCursorTile(Tile *t) { cursor.setTile(t); }

Tile *Board::getTile(const std::string &name) const {
    for (Tile *t : tiles) {
        if (t->getName() == name) return t;
    }

    return nullptr;  // Return nullptr if not found
}

Tile *Board::getTile(const int &x, const int &y) const {
    for (Tile *t : tiles) {
        if (t->getX() == x && t->getY() == y) return t;
    }

    return nullptr;
}

Tile *Board::getTile(const Tile *t, const Direction &direction) const {
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

Gate *Board::getGate(const std::string &name) const {
    for (Gate *g : gates) {
        if (g->getName() == name) return g;
    }

    return nullptr;
}

Gate *Board::getGate(const Tile *t1, const Tile *t2) const {
    if (t1 == nullptr || t2 == nullptr) {  // Throw exception here
        std::cerr << "[ERROR]: Nonexistent tile cannot be used as an argument."
                  << std::endl;
    }

    for (Gate *g : gates) {
        if (g->getTile1() == t1 && g->getTile2() == t2) return g;
    }

    return nullptr;
}

Gate *Board::getGate(const Tile *t, const Direction &direction) const {
    if (!t) {
        // Throw an exception here
        throw TileNotFoundException("Tile does not exist");
        return nullptr;
    }

    Tile *currentTile = cursor.getTile();

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

bool Board::tileCoordEquals(const Tile *t1, const Tile *t2) const {
    return t1->getX() == t2->getX() && t1->getY() == t2->getY();
}

bool Board::tileNameEquals(const Tile *t1, const Tile *t2) const {
    return t1->getName() == t2->getName();
}

bool Board::gateTilesEquals(const Gate *g1, const Gate *g2) const {
    return g1->getTile1() == g2->getTile1() && g1->getTile2() == g2->getTile2();
}

bool Board::gateNameEquals(const Gate *g1, const Gate *g2) const {
    return g1->getName() == g2->getName();
}

void Board::checkDupTiles() const {
    /*
    std::deque<Tile*> compare{tiles}; // using copy constructor
    auto currCompare = compare.begin(); // iterator to compare obj;
    int c1{0}, c2{0};

    while (currCompare != compare.end()) {
        for (auto it = tiles.cbegin(); it != tiles.cend(); ++it) {
            if (compareByTileName(*currCompare, *it)) c1++;
            else if (compareByTileCoordinate(*currCompare, *it)) c2++;

            if (c1 > 1) throw
    DuplicateTileNamesException((*currCompare)->getName()); else if (c2 > 1)
    throw DuplicateTileCoordinatesException((*currCompare)->getX(),
    (*currCompare)->getY());
        }
        ++currCompare; // Move to next element
    }
    */
}

void Board::checkDupGates() const {
    /*
    std::deque<Gate*> compare{gates}; // using copy constructor
    auto currCompare = compare.begin(); // iterator to compare obj;
    int c1{0}, c2{0};

    while (currCompare != compare.end()) {
        for (auto it = gates.cbegin(); it != gates.cend(); ++it) {
            if (compareByGateName(*currCompare, *it)) c1++;
            else if (compareByGateTiles(*currCompare, *it)) c2++;

            if (c1 > 1) throw
    DuplicateGateNamesException((*currCompare)->getName()); else if (c2 > 1)
    throw DuplicateGateTilesException((*currCompare)->getTile1(),
    (*currCompare)->getTile2());
        }
        ++currCompare; // Move to next element
    }
    */
}

void Board::insTile(int pos, Tile *t) {
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
    }

    ++numTiles;
}

void Board::remTile(Tile *t) {
    // TODO: Add check for empty
    auto tilepos = std::find(tiles.begin(), tiles.end(), t);
    if (tilepos != tiles.end())
        tiles.erase(tilepos);
    else
        std::cerr << "[ERROR] Cannot find tile to remove." << std::endl;

    --numTiles;
}

void Board::insGate(int pos, Gate *g) {
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
    }

    ++numGates;
}

void Board::remGate(Gate *g) {
    auto gatepos = std::find(gates.begin(), gates.end(), g);
    if (gatepos != gates.end())
        gates.erase(gatepos);
    else
        std::cerr << "[ERROR] Cannot find gate to remove." << std::endl;

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
    Tile *prevTile = cursor.getTile();
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

    Tile *currentTile = cursor.getTile();
    Tile *target = getTile(currentTile, direction);
    if (target->isCollision())
        return false;
    else if (getGate(currentTile, target)) {
        return false;
    }

    return true;
}

void Board::rotateTile(Tile *t, const Rotation &rotation) {
    // ! - DO NOT rotate non-directional tiles!!!
    std::string dir = t->getType();

    // TODO: Check string here if directional

    if (rotation == CLOCKWISE)
        dir = clockwiseMap.at(dir);
    else if (rotation == COUNTER_CLOCKWISE)
        dir = counterClockwiseMap.at(dir);

    // TODO: Error
    t->setType(dir);
}

void Board::rotateTiles(const std::string &color, const Rotation &rotation) {
    for (Tile *t : tiles) {
        if (t->getColor() == color) rotateTile(t, rotation);
    }
}

void Board::toggleGate(const Tile *t1, const Tile *t2) {
    if (t1->isCollision() || t2->isCollision()) {
        // TODO: Error here
    }

    // TODO: Check valid tiles
    // TODO: 
}

bool Board::empty() const { return tiles.empty(); }

bool Board::full() const { return numTiles > length * width; }

const std::unordered_map<std::string, std::string> Board::clockwiseMap = {
    {"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

const std::unordered_map<std::string, std::string> Board::counterClockwiseMap =
    {{"up", "left"}, {"left", "down"}, {"down", "right"}, {"right", "up"}};

Board::~Board() {}
