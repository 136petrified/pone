/*  Created:    06-23-2024
*   Modified:   06-13-2025
*/

#include "ponetile.hpp"

// Tile constructors
// ---------------------------------------------
Tile::Tile() : x{0}, y{0}, color{"none"}, type{"empty"}
{}

Tile::Tile(const int &x, const int &y, 
           const std::string &color, const std::string &type) :
    x{x}, y{y}, color{color}, type{type}
{}

// Tile getter/setter functions
// ---------------------------------------------
int Tile::getX() const {
    return x;
}

void Tile::setX(const int &x) {
    this->x = x;
}

int Tile::getY() const {
    return y;
}

void Tile::setY(const int &y) {
    this->y = y;
}

std::string Tile::getColor() const {
    return color;
}

void Tile::setColor(const std::string &color) {
    this->color = color;
}

std::string Tile::getType() const {
    return type;
}

void Tile::setType(const std::string &type) {
    this->type = type;
}

void Tile::setCursor(bool c) {
    cursor = c;
}

int Tile::getID() const {
    return id;
}

void Tile::setID(int id) {
    this->id = id;
}

std::string Tile::getName() const {
    return name;
}

void Tile::setName(const std::string &name) {
    this->name = name;
}

// Tile functions
// ---------------------------------------------
bool Tile::isCollision() const {
    return type == "collision";
}

bool Tile::isCursor() const {
    return cursor;
}

bool Tile::isEmpty() const {
    return type == "empty";
}

bool Tile::operator==(const Tile &other) {
    return x == other.x && y == other.y;
}

// Tile destructor
// ---------------------------------------------
Tile::~Tile() {}
