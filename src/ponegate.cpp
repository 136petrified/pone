/*   Created:    06-29-2024
 *   Modified:   06-24-2025
 */

#include "ponegate.hpp"

// Gate constructors
// ---------------------------------------------
Gate::Gate()
    : tp{TilePair{nullptr, nullptr}},
      name{""},
      id{-1},
      color{"none"},
      active{false} {}

Gate::Gate(Tile *t1, Tile *t2, const std::string &name,
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
    tp = other.tp;
    name = other.name;
    id = other.id;
    color = other.color;
    active = other.active;
    return *this;
}

// Gate getter/setter functions
// ---------------------------------------------

Tile *Gate::getTile1() const { return tp.first; }

void Gate::setTile1(Tile *t1) { tp.first = t1; }

Tile *Gate::getTile2() const { return tp.second; }

void Gate::setTile2(Tile *t2) { tp.second = t2; }

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

// Gate comparison
// ---------------------------------------------

bool Gate::operator==(const Gate &other) const {
    TilePair g1 = getTilePair(), g2 = other.getTilePair();
    Tile *g1t1 = g1.first, *g1t2 = g1.second;
    Tile *g2t1 = g2.first, *g2t2 = g2.second;

    return *g1t1 == *g2t1 && *g1t2 == *g2t2;
}

bool Gate::operator!=(const Gate &other) const { return !(*this == other); }

bool Gate::operator<(const Gate &other) const {
    TilePair g1 = getTilePair(), g2 = other.getTilePair();
    Tile *g1t1 = g1.first, *g1t2 = g1.second;
    Tile *g2t1 = g2.first, *g2t2 = g2.second;

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
