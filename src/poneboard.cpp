/*  Created: JUN 23 2024
*   Modified: AUG 15 2024
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "poneboard.hpp"
#include "poneconst.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

// Board constructors
// ---------------------------------------------
Board::Board() :
    length{0}, width{0}, tiles{std::vector<Tile*>()}, gates{std::vector<Gate*>()}, currentTile{nullptr}
{}

Board::Board(const unsigned &length, const unsigned &width) :
    length{length}, width{width}, tiles{std::vector<Tile*>()}, gates{std::vector<Gate*>()}, currentTile{nullptr}
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

Tile *Board::getTile(const std::string &name) {
    for (Tile *tile : tiles) {
        if (tile->getName() == name) return tile;
    }
    
    return nullptr; // If no Tile* is found
}

Gate *Board::getGate(const std::string &name) {
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

// Board functions
// ---------------------------------------------
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

}

void Board::save() {

}

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
    }
    currentTile = getTile(currentTile, direction);
    currentTile->setCursor(true);
}