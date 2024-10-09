/*  Created: JUN 23 2024
*   Modified: OCT 9 2024
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

#include "poneboard.hpp"
#include "poneconst.hpp"
#include "poneexcept.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

// Board constructors
// ---------------------------------------------
Board::Board() :
    length{0}, width{0}, tiles{TileList()}, gates{GateList()}, currentTile{nullptr}
{}

Board::Board(const int &length, const int &width) :
    length{length}, width{width}, tiles{TileList()}, gates{GateList()}, currentTile{nullptr}
{}

// Board getter/setter functions
// ---------------------------------------------
int Board::getLength() const {
    return length;
}

void Board::setLength(const int &length) {
    this->length = length;
}

int Board::getWidth() const {
    return width;
}

void Board::setWidth(const int &width) {
    this->width = width;
}

Tile *Board::getTile(const std::string &name) const {
    for (Tile *tile : tiles) {
        if (tile->getName() == name) return tile;
    }
    
    return nullptr; // If no Tile* is found
}

Gate *Board::getGate(const std::string &name) const {
    for (Gate *gate : gates) { 
        if (gate->getName() == name) return gate;
    }

    return nullptr; // If no GATE* is found
}

Tile *Board::getCurrentTile() const {
    return currentTile;
}

void Board::setCurrentTile(Tile *t) {
    currentTile = t;
}

Tile *Board::getTile(const std::string &name) const {
    for (Tile *t : tiles) {
        if (t->getName() == name) return t;
    }

    return nullptr; // Return nullptr if not found
}

Tile *Board::getTile(const int &x, const int &y) const {
    for (Tile *t : tiles) {
        if (t->getX() == x && t->getY() == y) return t;
    }

    return nullptr;
}

Tile *Board::getTile(const Tile *t, const int &direction) const {
    if (!t) {
        // Throw an exception here
        std::cerr << "[ERROR]: Tile does not exist." << std::endl;
        return nullptr;
    }

    switch (direction) {
        case UP:
            return getTile(t->getX(), t->getY() + 1);
        case DOWN:
            return getTile(t->getX(), t->getY() - 1);
        case LEFT:
            return getTile(t->getX() + 1, t->getY());
        case RIGHT:
            return getTile(t->getX() - 1, t->getY());
        default:
            std::cerr << "[ERROR]: Invalid direction: "
                      << direction << std::endl;
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
    if (!t1 || !t2) { // Throw exception here
        std::cerr << "[ERROR]: Nonexistent tile cannot be used as an argument." 
                  << std::endl;
    }

    for (Gate *g : gates) {
        if (g->getTile1() == t1 && g->getTile2() == t2) return g;
    }

    return nullptr;
}

Gate *Board::getGate(const Tile *t, const int &direction) const {

    if (!t) {
        // Throw an exception here
        std::cerr << "[ERROR]: Tile does not exist." << std::endl;
        return nullptr;
    }
    
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
            std::cerr << "[ERROR]: Invalid direction: "
                      << direction << std::endl;
            break;

        return nullptr;
    }
}


// Board functions
// ---------------------------------------------

bool Board::compareByTileCoordinate(const Tile *t1, const Tile *t2) const {
    return t1->getX() == t2->getX() && t1->getY() == t2->getY();
}

bool Board::compareByTileName(const Tile *t1, const Tile *t2) const {
    return t1->getName() == t2->getName();
}

bool Board::compareByTileReference(const Tile *t1, const Tile *t2) const {
    return t1 == t2;
}

bool Board::compareByGateTiles(const Gate *g1, const Gate *g2) const {
    return g1->getTile1() == g2->getTile1() && g1->getTile2() == g2->getTile2();
}

bool Board::compareByGateName(const Gate *g1, const Gate *g2) const {
    return g1->getName() == g2->getName();
}

bool Board::compareByGateReference(const Gate *g1, const Gate *g2) const {
    return g1 == g2;
}

void Board::checkDupTiles() const {
    std::deque<Tile*> compare{tiles}; // using copy constructor
    auto currCompare = compare.begin(); // iterator to compare obj;
    int c1{0}, c2{0};

    while (currCompare != compare.end()) {
        for (auto it = tiles.cbegin(); it != tiles.cend(); ++it) {
            if (compareByTileName(*currCompare, *it)) c1++;
            else if (compareByTileCoordinate(*currCompare, *it)) c2++;

            if (c1 > 1) throw DuplicateTileNamesException((*currCompare)->getName());
            else if (c2 > 1) throw DuplicateTileCoordinatesException((*currCompare)->getX(), (*currCompare)->getY());
        }
        ++currCompare; // Move to next element
    }
}

void Board::checkDupGates() const {
    std::deque<Gate*> compare{gates}; // using copy constructor
    auto currCompare = compare.begin(); // iterator to compare obj;
    int c1{0}, c2{0};

    while (currCompare != compare.end()) {
        for (auto it = gates.cbegin(); it != gates.cend(); ++it) {
            if (compareByGateName(*currCompare, *it)) c1++;
            else if (compareByGateTiles(*currCompare, *it)) c2++;

            if (c1 > 1) throw DuplicateGateNamesException((*currCompare)->getName());
            else if (c2 > 1) throw DuplicateGateTilesException((*currCompare)->getTile1(), (*currCompare)->getTile2());
        }
        ++currCompare; // Move to next element
    }
}

void Board::insTile(int pos, Tile *t) {
    // Leave pos as -1 to insert at last position by default
    if (pos == -1) {
        tiles.push_back(t);
    } else if (pos < tiles.size() && pos > -2) {
        auto tilepos = tiles.begin() + pos;
        tiles.insert(tilepos, t);
    } else {
        std::cerr << "[ERROR] Attempted to insert tile into out-of-bounds position." << std::endl;
    }
}

void Board::remTile(Tile *t) {
    auto tilepos = std::find(tiles.begin(), tiles.end(), t);
    if (tilepos != tiles.end()) tiles.erase(tilepos);
    else std::cerr << "[ERROR] Cannot find tile to remove." << std::endl;
}

void Board::insGate(int pos, Gate *g) {
    // Leave pos as -1 to insert at last position by default
    if (pos == -1) {
        gates.push_back(g);
    } else if (pos < gates.size() && pos > -2) {
        auto gatepos = gates.begin() + pos;
        gates.insert(gatepos, g);
    } else {
        std::cerr << "[ERROR] Attempted to insert tile into out-of-bounds position." << std::endl;
    }
}

void Board::remGate(Gate *g) {
    auto gatepos = std::find(gates.begin(), gates.end(), g);
    if (gatepos != gates.end()) gates.erase(gatepos);
    else std::cerr << "[ERROR] Cannot find gate to remove." << std::endl;
}

void Board::load() {
    // This will be attached to ponescript
    // May use JSON-like formatting to load created boards

}

void Board::save() {
    // Autogenerates a script
}

// Board commands
// ---------------------------------------------

void Board::moveCursor(Cursor *c, const int &direction) {
    currentTile->setCursor(false);
    switch (direction) {
        case UP:
            c->setY(c->getY() + 1); break;
        case DOWN:
            c->setY(c->getY() - 1); break;
        case LEFT:
            c->setX(c->getX() - 1); break;
        case RIGHT:
            c->setX(c->getX() + 1); break;
        default:
            std::cerr << "[ERROR]: Move cursor failed given direction "
                      << direction << std::endl;
            break;
    }

    currentTile = getTile(currentTile, direction);
    currentTile->setCursor(true);
}

bool Board::checkMove(Cursor *c, const int &direction) {
    // Check collision first
    Tile *target = getTile(currentTile, direction);
    if (target->isCollision()) 
        return false;
    else if (getGate(currentTile, target)) {
        return false;
    }

    return true; 
}