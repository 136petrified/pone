/*   Created:    06-29-2024
 *   Modified:   06-13-2025
 */

#include "ponegate.hpp"

// TODO: Edit constructors

// Gate constructors
// ---------------------------------------------
Gate::Gate() : gate{GATE{nullptr, nullptr}} {}

Gate::Gate(Tile *t1, Tile *t2) : gate{GATE{t1, t2}} {}

// Gate getter/setter functions
// ---------------------------------------------

Tile *Gate::getTile1() const { return gate.first; }

void Gate::setTile1(Tile *t1) { gate.first = t1; }

Tile *Gate::getTile2() const { return gate.second; }

void Gate::setTile2(Tile *t2) { gate.second = t2; }

GATE Gate::getGate() const { return gate; }

void Gate::setGate(GATE gate) { this->gate = gate; }

int Gate::getID() const { return id; }

void Gate::setID(int id) { this->id = id; }

std::string Gate::getColor() const { return color; }

void Gate::setColor(const std::string &color) { this->color = color; }

std::string Gate::getName() const { return name; }

void Gate::setName(const std::string &name) { this->name = name; }

// Gate comparison
// ---------------------------------------------

bool Gate::operator==(const Gate &other) const {
    GATE g1 = getGate(), g2 = other.getGate();
    Tile *g1t1 = g1.first, *g1t2 = g1.second;
    Tile *g2t1 = g2.first, *g2t2 = g2.second;

    return *g1t1 == *g2t1 && *g1t2 == *g2t2;
}

bool Gate::operator!=(const Gate &other) const { return !(*this == other); }

bool Gate::operator<(const Gate &other) const {
    GATE g1 = getGate(), g2 = other.getGate();
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
