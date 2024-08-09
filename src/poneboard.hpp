#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <utility>
#include <vector>

#include "ponegate.hpp"
#include "ponetile.hpp"

class Board {
public:
    // Board constructors
    Board();
    Board(unsigned length, unsigned width);

    // Board setter/getter functions
    // ---------------------------------------------
    void setLength(const int &length);
    int getLength() const;
    
    void setWidth(const int &width);
    int getWidth() const;

    // Board functions
    // ---------------------------------------------
    void insTile();



    ~Board();
private:
    unsigned length, width;     // ! - Remember to except this if not unsigned!
    std::vector<Tile*> tiles;   // A list of n * m tiles is needed for
    std::vector<GATE*> gates;
};

#endif // PONE_BOARD_HPP