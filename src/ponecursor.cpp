/*  Created:  06-23-2024
*   Modified: 06-13-2025
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

std::pair<int, int> Cursor::getPos() const {
   return std::pair<int, int>{x, y};
}

// Cursor destructor
// ---------------------------------------------
Cursor::~Cursor()
{}
