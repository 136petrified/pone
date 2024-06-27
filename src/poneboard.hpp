#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <vector>

#include "ponetile.hpp"

class Board {
public:
    Board();
    Board(unsigned length, unsigned width);

    void setLength(const int &length);
    int getLength() const;
    
    void setWidth(const int &width);
    int getWidth() const;

    ~Board();
private:
    unsigned length, width;     // ! - Remember to except this if not unsigned!
    std::vector<Tile> tiles;    // A list of n * m tiles is needed for
};

#endif // PONE_BOARD_HPP