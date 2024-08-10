/*  Created: JUN 23 2024
*   Modified: AUG 9 2024
*/

#include <vector>

#include "poneboard.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

// Board constructors
// ---------------------------------------------
Board::Board() :
    length{0}, width{0}, tiles{std::vector<Tile*>()}, gates{std::vector<GATE*>()}, currentTile{nullptr}
{}

Board::Board(unsigned length, unsigned width) :
    length{length}, width{width}, tiles{std::vector<Tile*>()}, gates{std::vector<GATE*>()}, currentTile{nullptr}
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
    for (Tile *t : tiles) {
        if (t->getName() == name) return t;
    }
    
    return nullptr; // If no Tile* is found
}

Gate *Board::getGate(const std::string &name) {
    for (Gate *g : gates) { 
        if (g->getName() == name) return g;
    }

    return nullptr; // If no GATE* is found
}