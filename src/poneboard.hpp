#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <vector>

#include "ponetile.hpp"

class Board {
public:
    Board();
    Board(int length, int width);

    void setLength(const int &length);
    int getLength() const;
    
    void setWidth(const int &width);
    int getWidth() const;

    ~Board();
private:
    int length, width;
    std::vector<Tile> tiles;    // A list of n * m tiles is needed for
};

#endif // PONE_BOARD_HPP