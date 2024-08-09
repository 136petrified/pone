#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>
#include <vector>


class Tile {
public:
    // Tile constructors
    // ---------------------------------------------
    Tile();
    Tile(const unsigned &x, const unsigned &y, const std::string &color, const std::string &type);

    // Tile getter/setter functions
    // ---------------------------------------------
    unsigned getX() const;
    void setX(const unsigned &x);

    unsigned getY() const;
    void setY(const unsigned &y);

    std::string getColor() const;
    void setColor(const std::string &color);

    std::string getType() const;
    void setType(const std::string &type);

    void setCursor(bool c);

    unsigned getID() const;
    void setID(unsigned id);

    std::string getName() const;
    void setName(const std::string &name);

    // Tile functions
    // ---------------------------------------------
    bool isCollision() const;
    bool isCursor() const;
    bool isEmpty() const;

    // Tile destructor
    // ---------------------------------------------
    ~Tile();

private:
    // Tile attributes
    // ---------------------------------------------
    unsigned x, y;      // coordinates of the tile
    std::string color;
    std::string type;   // what is the type of this tile?
    bool cursor;        // is the cursor on this tile?
    unsigned id;
    std::string name;


    // Tile constants
    // ---------------------------------------------
    const std::vector<std::string> types{"empty", "gswitch", "cswitch", "key", "up", "down", "left", "right", "goal", "collision"};
};

#endif // PONE_TILE_HPP