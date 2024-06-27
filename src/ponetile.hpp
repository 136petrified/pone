#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>
#include <vector>

class Tile {
public:
    Tile();
    Tile(const int &x = 0, const int &y = 0, const std::string &color, const std::string &type);
    ~Tile();

private:
    // Tile attributes
    // ---------------------------------------------
    int x, y;           // coordinates of the tile
    std::string color;
    std::string type;   // what is the type of this tile?
    bool isCursor;      // is the cursor on this tile?


    // Tile constants
    // ---------------------------------------------
    const std::vector<std::string> types{"empty", "switch", "key", "up", "down", "left", "right", "goal"};
};

#endif // PONE_TILE_HPP