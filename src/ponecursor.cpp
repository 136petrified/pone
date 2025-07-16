/*   Created:  06-23-2024
 *   Modified: 07-16-2025
 */

#include "ponecursor.hpp"

#include "poneexcept.hpp"

// Cursor constructor
// ---------------------------------------------
Cursor::Cursor() : m_x{0}, m_y{0}, m_tile{nullptr} {}

Cursor::Cursor(const int &x, const int &y) : m_x{x}, m_y{y}, m_tile{nullptr} {}

Cursor::Cursor(const CoordPair &crds)
    : m_x{crds.first}, m_y{crds.second}, m_tile{nullptr} {}

Cursor::Cursor(const TilePtr &tptr) {
    if (tptr == nullptr) throw InvalidTileException("a Cursor object");

    m_x = tptr->getX();
    m_y = tptr->getY();
    m_tile = nullptr;
}

// Cursor setter/getter functions
// ---------------------------------------------
int Cursor::getX() const { return m_x; }

void Cursor::setX(const int &x) { m_x = x; }

int Cursor::getY() const { return m_y; }

void Cursor::setY(const int &y) { m_y = y; }

CoordPair Cursor::getCoordPair() const { return CoordPair{m_x, m_y}; }

void Cursor::setTile(TilePtr tptr) { m_tile = tptr; }

TilePtr Cursor::getTile() const { return m_tile; }

// Cursor destructor
// ---------------------------------------------
Cursor::~Cursor() {}
