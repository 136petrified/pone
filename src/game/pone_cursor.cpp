/*   Created:    2024-06-23
 *   Modified:   2026-05-04
 */

#include "pone_cursor.hpp"
#include "pone_const.hpp"
#include "pone_except.hpp"

namespace pone {

// +----------------------------------+
// + Cursor constructors              +
// +----------------------------------+

Cursor::Cursor() : m_x{0}, m_y{0}, m_tile{nullptr} {}

Cursor::Cursor(const int &x, const int &y) : m_x{x}, m_y{y}, m_tile{nullptr} {}

Cursor::Cursor(const CoordPair &crds)
    : m_x{crds.first}, m_y{crds.second}, m_tile{nullptr} {}

Cursor::Cursor(TilePtr t) {
    if (t == nullptr) {
        ErrorMessage T_NULL{name::PONE_GLOBAL_NAME, name::CURSOR_CURSOR_4,
                            "Tile is null."};
        throw InvalidTileException(T_NULL);
    }

    m_x = t->getX();
    m_y = t->getY();
    m_tile = nullptr;
}

// +----------------------------------+
// + Cursor getters/setters           +
// +----------------------------------+

int Cursor::getX() const {
    return m_x;
}

void Cursor::setX(const int &x) {
    m_x = x;
}

int Cursor::getY() const {
    return m_y;
}

void Cursor::setY(const int &y) {
    m_y = y;
}

CoordPair Cursor::getCoordPair() const {
    return CoordPair{m_x, m_y};
}

void Cursor::setTile(TilePtr t) {
    m_tile = t;
}

TilePtr Cursor::getTile() const {
    return m_tile;
}

// +----------------------------------+
// + Cursor destructor                +
// +----------------------------------+

Cursor::~Cursor() {}

} // namespace pone
