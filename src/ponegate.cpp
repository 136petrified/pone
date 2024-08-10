/*  Created: JUN 29 2024
*   Modified: AUG 9 2024
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

Tile *Gate::getTile1() const {
    return gate.first;
}

void Gate::setTile1(Tile *t1) {
    gate.first = t1;
}

Tile *Gate::getTile2() const {
    return gate.second;
}

void Gate::setTile2(Tile *t2) {
    gate.second = t2;
}

GATE Gate::getGate() const {
    return gate;
}

void Gate::setGate(GATE gate) {
    this->gate = gate;
}

unsigned Gate::getID() const {
    return id;
}

void Gate::setID(unsigned id) {
    this->id = id;
}

std::string Gate::getColor() const {
    return color;
}

void Gate::setColor(const std::string &color) {
    this->color = color;
}

std::string Gate::getName() const {
    return name;
}

void Gate::setName(const std::string &name) {
    this->name = name;
}
// Gate destructor
Gate::~Gate() 
{}