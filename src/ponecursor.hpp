#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

#include <memory>
#include <utility>

#include "ponetile.hpp"

using TilePtr = std::shared_ptr<Tile>;

class Cursor {
   public:
    // Cursor constructor
    // ---------------------------------------------
    Cursor();
    Cursor(const int &x, const int &y);

    // Cursor getter/setter functions
    // ---------------------------------------------
    int getX() const;
    void setX(const int &x);

    int getY() const;
    void setY(const int &y);

    std::pair<int, int> getPos() const;

    void setTile(TilePtr t);
    TilePtr getTile() const;

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

   private:
    // Cursor attributes
    // ---------------------------------------------
    int x, y;      // where is the cursor?
    TilePtr tile;  // This is a shared_ptr to a tile!
};

#endif  // PONE_CURSOR_HPP
