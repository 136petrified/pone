/*  Created: JUN 23 2024
*   Modified: SEP 8 2024
*/

#include "ponecursor.hpp"

// Cursor constructor
// --------------------------------------------- 
Cursor::Cursor() : x{0}, y{0} 
{}

Cursor::Cursor(const int &x, const int &y) 
    : x{x}, y{y} 
{}

// Cursor setter/getter functions
// ---------------------------------------------
int Cursor::getX() const {
    return x;
}

void Cursor::setX(const int &x) {
    this->x = x;
}

int Cursor::getY() const {
    return y;
}

void Cursor::setY(const int &y) {
    this->y = y;
}

Tile *Cursor::getTile(const Board &b) const {
   return b.getCurrentTile();
}

// Cursor destructor
// ---------------------------------------------
Cursor::~Cursor()
{}