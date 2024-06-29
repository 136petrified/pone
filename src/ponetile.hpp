#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>
#include <vector>

class Tile {
public:
    // Tile constructors
    // ---------------------------------------------
    Tile();
    Tile(const unsigned &x = 0, const unsigned &y = 0, const std::string &color, const std::string &type);

    // Tile getter/setter functions
    // ---------------------------------------------
    unsigned getX() const;
    void setX();

    unsigned getY() const;
    void setY();

    std::string getColor() const;
    void setColor();

    std::string getType() const;
    void setType();

    bool getCursorStatus() const;
    void setCursorStatus();

    // Tile destructor
    // ---------------------------------------------
    ~Tile();

private:
    // Tile attributes
    // ---------------------------------------------
    unsigned x, y;           // coordinates of the tile
    std::string color;
    std::string type;   // what is the type of this tile?
    bool isCursor;      // is the cursor on this tile?


    // Tile constants
    // ---------------------------------------------
    const std::vector<std::string> types{"empty", "switch", "key", "up", "down", "left", "right", "goal"};
};

#endif // PONE_TILE_HPP