/*  Created:  06-23-2024
 *   Modified: 06-13-2025
 */

#include "ponecursor.hpp"

// Cursor constructor
// ---------------------------------------------
Cursor::Cursor() : x{0}, y{0}, tile{nullptr} {}

Cursor::Cursor(const int &x, const int &y) : x{x}, y{y}, tile{nullptr} {}

// Cursor setter/getter functions
// ---------------------------------------------
int Cursor::getX() const { return x; }

void Cursor::setX(const int &x) { this->x = x; }

int Cursor::getY() const { return y; }

void Cursor::setY(const int &y) { this->y = y; }

std::pair<int, int> Cursor::getPos() const { return std::pair<int, int>{x, y}; }

void Cursor::setTile(Tile *t) { tile = t; }

Tile *Cursor::getTile() const { return tile; }

// Cursor destructor
// ---------------------------------------------
Cursor::~Cursor() {}
