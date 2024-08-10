#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

#include "poneboard.hpp"
#include "ponetile.hpp"

class Cursor {
public:
    // Cursor constructor
    // ---------------------------------------------  
    Cursor();
    Cursor(const unsigned &x = 0, const unsigned &y = 0);

    // Cursor getter/setter functions
    // ---------------------------------------------
    unsigned getX() const;
    void setX(const unsigned &x);

    unsigned getY() const;
    void setY(const unsigned &y);

    Tile *getTile(const Board &b) const;

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

private:
    // Cursor attributes
    // ---------------------------------------------
    unsigned x, y;      // where is the cursor?
};

#endif // PONE_CURSOR_HPP