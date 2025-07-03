/*  Created:    06-23-2024
 *  Modified:   07-02-2025
 */

#include "ponetile.hpp"

#include <iostream>

// Tile constructors
// ---------------------------------------------
Tile::Tile() : x{0}, y{0}, color{"none"}, type{"empty"} {}

Tile::Tile(const int &x, const int &y, const std::string &color,
           const std::string &type)
    : x{x}, y{y}, color{color}, type{type} {}

Tile::Tile(const Tile &other)
    : x{other.x}, y{other.y}, color{other.color}, type{other.type} {}

// Tile assignment
// ---------------------------------------------
Tile &Tile::operator=(const Tile &other) {
    x = other.x;
    y = other.y;
    color = other.color;
    type = other.type;
    return *this;
}

// Tile getter/setter functions
// ---------------------------------------------
int Tile::getX() const { return x; }

void Tile::setX(const int &x) { this->x = x; }

int Tile::getY() const { return y; }

void Tile::setY(const int &y) { this->y = y; }

std::string Tile::getColor() const { return color; }

void Tile::setColor(const std::string &color) { this->color = color; }

std::string Tile::getType() const { return type; }

void Tile::setType(const std::string &type) { this->type = type; }

void Tile::setCursor(bool c) { cursor = c; }

int Tile::getID() const { return id; }

void Tile::setID(int id) { this->id = id; }

std::string Tile::getName() const { return name; }

void Tile::setName(const std::string &name) { this->name = name; }

// Tile functions
// ---------------------------------------------
bool Tile::isCollision() const { return type == "collision"; }

bool Tile::isCursor() const { return cursor; }

bool Tile::isDirection() const {
    return type == "left" || type == "right" || type == "up" || type == "down";
}

bool Tile::isEmpty() const { return type == "empty"; }

bool Tile::isGateSwitch() const { return type == "gswitch"; }

bool Tile::isGoal() const { return type == "goal"; }

bool Tile::isTileSwitch() const { return type == "tswitch"; }

bool Tile::isType(const std::string &str) const { return type == str; }

void Tile::print(std::ostream &out) const {
    out << "{name: " << name << ", x: " << x << ", y:" << y
        << ", color:" << color << ", type: " << type << "}" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Tile &t) {
    t.print(out);
    return out;
}

// Tile comparison
// ---------------------------------------------

bool Tile::operator==(const Tile &other) const {
    return x == other.x && y == other.y;
}

bool Tile::operator!=(const Tile &other) const { return !(x == y); }

bool Tile::operator<(const Tile &other) const {
    int x1 = x, x2 = other.getX();
    int y1 = y, y2 = other.getY();

    if (x1 < x2) {
        return true;
    } else if (x1 == x2) {
        if (y1 < y2) {
            return true;
        }
    }

    return false;
}

bool Tile::operator<=(const Tile &other) const {
    return *this < other || *this == other;
}

bool Tile::operator>(const Tile &other) const { return !(*this <= other); }

bool Tile::operator>=(const Tile &other) const { return !(*this < other); }

// Tile destructor
// ---------------------------------------------
Tile::~Tile() {}
