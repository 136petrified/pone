/*  Created: JUN 29 2024
*   Modified: AUG 8 2024
*/

#include <utility>

#include "ponegate.hpp"

// Gate constructors
// ---------------------------------------------
Gate::Gate() : gate{std::pair<Tile*, Tile*>{nullptr, nullptr}}
{}

Gate::Gate(Tile *t1, Tile *t2) : gate{std::pair<Tile*, Tile*>{t1, t2}}
{}

// Gate getter/setter functions
// ---------------------------------------------
void Gate::setTile1(Tile *t1) {
    gate.first = t1;
}

Tile *Gate::getTile1() const {
    return gate.first;
}

void Gate::setTile2(Tile *t2) {
    gate.second = t2;
}

Tile *Gate::getTile2() const {
    return gate.second;
}

void Gate::setGate(GATE gate) {
    this->gate = gate;
}

GATE Gate::getGate() const {
    return gate;
}

// Gate destructor
Gate::~Gate() 
{}