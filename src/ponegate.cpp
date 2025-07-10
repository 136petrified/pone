/*   Created:    06-29-2024
 *   Modified:   07-10-2025
 */

#include "ponegate.hpp"

#include <iostream>

// Gate constructors
// ---------------------------------------------
Gate::Gate()
    : tp{TilePair{nullptr, nullptr}},
      name{""},
      id{-1},
      color{"none"},
      active{false} {}

Gate::Gate(TilePtr t1, TilePtr t2, const std::string &name,
           const std::string &color, bool active)
    : tp{TilePair{t1, t2}}, name{name}, id{-1}, color{color}, active{active} {}

Gate::Gate(const Gate &other)
    : tp{other.tp},
      name{other.name},
      id{other.id},
      color{other.color},
      active{other.active} {}

// Gate assignment
// ---------------------------------------------
Gate &Gate::operator=(const Gate &other) {
    if (this == &other) return *this;

    tp = other.tp;
    name = other.name;
    id = other.id;
    color = other.color;
    active = other.active;

    return *this;
}

// Gate getter/setter functions
// ---------------------------------------------

TilePtr Gate::getTile1() const { return tp.first; }

void Gate::setTile1(TilePtr t1) { tp.first = t1; }

TilePtr Gate::getTile2() const { return tp.second; }

void Gate::setTile2(TilePtr t2) { tp.second = t2; }

TilePair Gate::getTilePair() const { return tp; }

void Gate::setTilePair(TilePair tp) { this->tp = tp; }

int Gate::getID() const { return id; }

void Gate::setID(int id) { this->id = id; }

std::string Gate::getColor() const { return color; }

void Gate::setColor(const std::string &color) { this->color = color; }

std::string Gate::getName() const { return name; }

void Gate::setName(const std::string &name) { this->name = name; }

// Gate functions
// ---------------------------------------------

bool Gate::isActive() { return active; }

void Gate::print(std::ostream &out) const {
    TilePtr t1 = tp.first, t2 = tp.second;
    out << "{name: " << name << ", id: " << id << ", t1: {" << t1->getX()
        << ", " << t1->getY() << "}, t2: {" << t2->getX() << ", " << t2->getY()
        << "}, color: " << color << "}" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Gate &g) {
    g.print(out);
    return out;
}

// Gate comparison
// ---------------------------------------------

bool Gate::operator==(const Gate &other) const {
    TilePair g1 = tp, g2 = other.tp;
    TilePtr g1t1 = g1.first, g1t2 = g1.second;
    TilePtr g2t1 = g2.first, g2t2 = g2.second;

    return *g1t1 == *g2t1 && *g1t2 == *g2t2;
}

bool Gate::operator!=(const Gate &other) const { return !(*this == other); }

bool Gate::operator<(const Gate &other) const {
    TilePair g1 = tp, g2 = other.tp;
    TilePtr g1t1 = g1.first, g1t2 = g1.second;
    TilePtr g2t1 = g2.first, g2t2 = g2.second;

    return *g1t1 < *g2t1 && *g1t2 < *g2t2;
}

bool Gate::operator<=(const Gate &other) const {
    return *this < other || *this == other;
}

bool Gate::operator>(const Gate &other) const { return !(*this <= other); }

bool Gate::operator>=(const Gate &other) const { return !(*this < other); }

// Gate destructor
// ---------------------------------------------
Gate::~Gate() {}
