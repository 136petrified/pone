#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>

class Tile {
public:
    Tile();
    ~Tile();
private:
    struct Attributes {
        int x, y;           // coordinates of the tile
        std::string color;
        std::string type;   // what is the type of this tile?
        bool isCursor;      // is the cursor on this tile?
    };
};

#endif // PONE_TILE_HPP