#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>
#include <vector>

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

    std::vector<std::string> types;

    Attributes attr;
};

#endif // PONE_TILE_HPP