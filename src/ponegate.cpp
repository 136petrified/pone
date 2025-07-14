/*   Created:    06-29-2024
 *   Modified:   07-13-2025
 */

#include "ponegate.hpp"

#include <iostream>

// Gate constructors
// ---------------------------------------------
Gate::Gate()
    : m_name{""},
      m_id{-1},
      m_tp{TilePair{nullptr, nullptr}},
      m_color{"none"},
      m_active{false} {}

Gate::Gate(TilePtr t1, TilePtr t2, const std::string &name,
           const std::string &color, bool active)
    : m_name{name},
      m_id{-1},
      m_tp{TilePair{t1, t2}},
      m_color{color},
      m_active{active} {}

Gate::Gate(const Gate &other)
    : m_name{other.m_name},
      m_id{other.m_id},
      m_tp{other.m_tp},
      m_color{other.m_color},
      m_active{other.m_active} {}

// Gate assignment
// ---------------------------------------------
Gate &Gate::operator=(const Gate &other) {
    if (this == &other) return *this;

    m_name = other.m_name;
    m_id = other.m_id;
    m_tp = other.m_tp;
    m_color = other.m_color;
    m_active = other.m_active;

    return *this;
}

// Gate getter/setter functions
// ---------------------------------------------

TilePtr Gate::getTile1() const { return m_tp.first; }

void Gate::setTile1(TilePtr t1) { m_tp.first = t1; }

TilePtr Gate::getTile2() const { return m_tp.second; }

void Gate::setTile2(TilePtr t2) { m_tp.second = t2; }

TilePair Gate::getTilePair() const { return m_tp; }

void Gate::setTilePair(TilePair tp) { m_tp = tp; }

int Gate::getID() const { return m_id; }

void Gate::setID(int id) { m_id = id; }

std::string Gate::getColor() const { return m_color; }

void Gate::setColor(const std::string &color) { m_color = color; }

std::string Gate::getName() const { return m_name; }

void Gate::setName(const std::string &name) { m_name = name; }

void Gate::setInactive() { m_active = false; }

void Gate::setActive() { m_active = true; }

// Gate functions
// ---------------------------------------------

bool Gate::isActive() { return m_active; }

void Gate::print(std::ostream &out) const {
    TilePtr t1 = m_tp.first, t2 = m_tp.second;
    out << "{name: " << m_name << ", id: " << m_id << ", t1: {" << t1->getX()
        << ", " << t1->getY() << "}, t2: {" << t2->getX() << ", " << t2->getY()
        << "}, color: " << m_color << "}" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Gate &g) {
    g.print(out);
    return out;
}

// Gate comparison
// ---------------------------------------------

bool Gate::operator==(const Gate &other) const {
    TilePair g1 = m_tp, g2 = other.m_tp;
    TilePtr g1t1 = g1.first, g1t2 = g1.second;
    TilePtr g2t1 = g2.first, g2t2 = g2.second;

    return *g1t1 == *g2t1 && *g1t2 == *g2t2;
}

bool Gate::operator!=(const Gate &other) const { return !(*this == other); }

bool Gate::operator<(const Gate &other) const {
    TilePair g1 = m_tp, g2 = other.m_tp;
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
