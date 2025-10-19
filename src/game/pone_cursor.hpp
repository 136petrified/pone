/*   Created:  06-23-2024
 *   Modified: 10-19-2025
 */

#pragma once

#include <memory>
#include <utility>

#include "pone_tile.hpp"

using CoordPair = std::pair<int, int>;
using TilePtr   = std::shared_ptr<Tile>;

class Cursor {
   public:
    // Cursor constructor
    // ---------------------------------------------
    Cursor();
    Cursor(const int &x, const int &y);
    Cursor(const CoordPair &crds);
    Cursor(const TilePtr &tptr);

    // Cursor getter/setter functions
    // ---------------------------------------------
    int getX() const;
    void setX(const int &x);

    int getY() const;
    void setY(const int &y);

    CoordPair getCoordPair() const;

    void setTile(TilePtr tptr);
    TilePtr getTile() const;

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

   private:
    // Cursor attributes
    // ---------------------------------------------
    int m_x, m_y;    // where is the cursor?
    TilePtr m_tile;  // This is a shared_ptr to a tile!
};
