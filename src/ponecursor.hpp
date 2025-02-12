#ifndef PONE_CURSOR_HPP
#define PONE_CURSOR_HPP

#include <utility>

#include "ponetile.hpp"

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

    // Cursor destructor
    // ---------------------------------------------
    ~Cursor();

private:
    // Cursor attributes
    // ---------------------------------------------
    int x, y;      // where is the cursor?
};

#endif // PONE_CURSOR_HPP