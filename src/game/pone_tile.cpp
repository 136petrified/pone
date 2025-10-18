/*  Created:    06-23-2024
 *  Modified:   07-13-2025
 */

#include "ponetile.hpp"

#include <iostream>

// Tile constructors
// ---------------------------------------------
Tile::Tile()
    : m_name{""},
      m_id{0},
      m_x{0},
      m_y{0},
      m_color{"none"},
      m_type{"empty"},
      m_cursor{false} {}

Tile::Tile(const std::string &name, const int &id, const int &x, const int &y,
           const std::string &color, const std::string &type, bool cursor)
    : m_name{name},
      m_id{id},
      m_x{x},
      m_y{y},
      m_color{color},
      m_type{type},
      m_cursor{cursor} {}

Tile::Tile(const Tile &other)
    : m_name{other.m_name},
      m_id{other.m_id},
      m_x{other.m_x},
      m_y{other.m_y},
      m_color{other.m_color},
      m_type{other.m_type},
      m_cursor{other.m_cursor} {}

// Tile assignment
// ---------------------------------------------
Tile &Tile::operator=(const Tile &other) {
    m_name = other.m_name;
    m_id = other.m_id;
    m_x = other.m_x;
    m_y = other.m_y;
    m_color = other.m_color;
    m_type = other.m_type;
    m_cursor = other.m_cursor;
    return *this;
}

// Tile getter/setter functions
// ---------------------------------------------
int Tile::getX() const { return m_x; }

void Tile::setX(const int &x) { m_x = x; }

int Tile::getY() const { return m_y; }

void Tile::setY(const int &y) { m_y = y; }

CoordPair Tile::getCoordPair() const { return CoordPair{m_x, m_y}; }

std::string Tile::getColor() const { return m_color; }

void Tile::setColor(const std::string &color) { m_color = color; }

std::string Tile::getType() const { return m_type; }

void Tile::setType(const std::string &type) { m_type = type; }

void Tile::setCursor(bool is_cursor) { m_cursor = is_cursor; }

int Tile::getID() const { return m_id; }

void Tile::setID(int id) { m_id = id; }

std::string Tile::getName() const { return m_name; }

void Tile::setName(const std::string &name) { m_name = name; }

// Tile functions
// ---------------------------------------------
bool Tile::isCollision() const { return m_type == "collision"; }

bool Tile::isCursor() const { return m_cursor; }

bool Tile::isDirection() const {
    return m_type == "left" || m_type == "right" || m_type == "up" ||
           m_type == "down";
}

bool Tile::isEmpty() const { return m_type == "empty"; }

bool Tile::isGateSwitch() const { return m_type == "gswitch"; }

bool Tile::isGoal() const { return m_type == "goal"; }

bool Tile::isTileSwitch() const { return m_type == "tswitch"; }

bool Tile::isType(const std::string &type) const { return m_type == type; }

void Tile::print(std::ostream &out) const {
    out << "{name: " << m_name << ", id: " << m_id << ", x: " << m_x
        << ", y: " << m_y << ", color: " << m_color << ", type: " << m_type
        << ", cursor: " << m_cursor << "}";
}

std::ostream &operator<<(std::ostream &out, const Tile &t) {
    t.print(out);
    return out;
}

// Tile comparison
// ---------------------------------------------

bool Tile::operator==(const Tile &other) const {
    return m_x == other.m_x && m_y == other.m_y;
}

bool Tile::operator!=(const Tile &other) const { return !(m_x == m_y); }

bool Tile::operator<(const Tile &other) const {
    int x1 = m_x, x2 = other.m_x;
    int y1 = m_y, y2 = other.m_y;

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
