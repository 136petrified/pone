#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

#include "poneboard.hpp"
#include "ponetile.hpp"

class Cursor {
public:
    // Cursor constructor
    // ---------------------------------------------  
    Cursor();
    Cursor(const int &x = 0, const int &y = 0);

    // Cursor getter/setter functions
    // ---------------------------------------------
    int getX() const;
    void setX(const int &x);

    int getY() const;
    void setY(const int &y);

    Tile *getTile(const Board &b) const;

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

private:
    // Cursor attributes
    // ---------------------------------------------
    int x, y;      // where is the cursor?
};

#endif // PONE_CURSOR_HPP