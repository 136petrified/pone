/*  Created: JUN 23 2024
*   Modified: AUG 8 2024
*/

#include "ponetile.hpp"

// Tile constructors
// ---------------------------------------------

Tile::Tile() : x{0}, y{0}, color{"none"}, type{"empty"}
{}

Tile::Tile(const unsigned &x, const unsigned &y, 
           const std::string &color, const std::string &type) :
    x{x}, y{y}, color{color}, type{type}
{}

// Tile getter/setter functions
// ---------------------------------------------

unsigned Tile::getX() const {
    return x;
}

void Tile::setX(const unsigned &x) {
    this->x = x;
}