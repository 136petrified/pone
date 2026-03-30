/*   Created:  2024-06-23
 *   Modified: 2026-03-03
 */

#pragma once

#include <memory>
#include <utility>
#include "pone_tile.hpp"

namespace pone {

using CoordPair = std::pair<int, int>;
using TilePtr   = std::shared_ptr<Tile>;

class Cursor {
   public:
    // +----------------------------------+
    // + Cursor constructors              +
    // +----------------------------------+

    /**
     * Default cursor constructor.
     */
    Cursor();

    /**
     * Constructs a cursor with coordinates.
     *
     * @param x the horizontal position of the cursor.
     * @param y the vertical position of the cursor.
     */
    Cursor(const int &x, const int &y);

    /**
     * Constructs a cursor with a coordinate pair.
     *
     * @param crds the coordinate pair.
     */
    Cursor(const CoordPair &crds);

    /**
     * Constructs a cursor given a tile.
     *
     * @param tptr a pointer to a tile.
     */
    Cursor(const TilePtr &tptr);

    // +----------------------------------+
    // + Cursor getter/setters            +
    // +----------------------------------+

    /**
     * Gets the horizontal position of the cursor.
     *
     * @return the horizontal position of the cursor.
     */
    int getX() const;

    /**
     * Sets the horizontal position of the cursor.
     */
    void setX(const int &x);

    /**
     * Gets the vertical position of the cursor.
     *
     * @return the vertical position of the cursor.
     */
    int getY() const;

    /**
     * Sets the vertical position of the cursor.
     *
     * @return the vertical position of the cursor.
     */
    void setY(const int &y);

    /**
     * Gets the coordinate pair of the cursor.
     *
     * @return a coordinate pair.
     */
    CoordPair getCoordPair() const;

    /**
     * Sets the current tile of the cursor.
     *
     * @param tptr a pointer to the tile.
     */
    void setTile(TilePtr tptr);

    /**
     * Gets the current tile of the cursor.
     *
     * @return a pointer to the tile if it exists, otherwise nullptr.
     */
    TilePtr getTile() const;

    // +----------------------------------+
    // + Cursor destructor                +
    // +----------------------------------+
    ~Cursor();

   private:
    // +----------------------------------+
    // + Cursor attributes                +
    // +----------------------------------+
    int m_x, m_y;    // where is the cursor?
    TilePtr m_tile;  // This is a shared_ptr to a tile!
};

}  // namespace pone
