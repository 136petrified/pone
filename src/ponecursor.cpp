/*  Created: JUN 23 2024
*   Modified: AUG 15 2024
*/

#include "ponecursor.hpp"

// Cursor constructor
// --------------------------------------------- 
Cursor::Cursor() : x{0}, y{0} 
{}

Cursor::Cursor(const unsigned &x, const unsigned &y) 
    : x{x}, y{y} 
{}

// Cursor setter/getter functions
// ---------------------------------------------
unsigned Cursor::getX() const {
    return x;
}

void Cursor::setX(const unsigned &x) {
    this->x = x;
}

unsigned Cursor::getY() const {
    return y;
}

void Cursor::setY(const unsigned &y) {
    this->y = y;
}

Tile *Cursor::getTile(const Board &b) const {
   return b.getCurrentTile();
}

// Cursor destructor
// ---------------------------------------------
Cursor::~Cursor()
{}