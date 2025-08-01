#ifndef PONE_TILE_HPP
#define PONE_TILE_HPP

#include <string>
#include <vector>

using CoordPair = std::pair<int, int>;

class Tile {
   public:
    // Tile constructors
    // ---------------------------------------------
    Tile();
    Tile(const std::string &name, const int &id, const int &x, const int &y,
         const std::string &color, const std::string &type,
         bool cursor);  // Full constructor
    Tile(const Tile &other);

    // Tile assignment
    // ---------------------------------------------
    Tile &operator=(const Tile &other);

    // Tile getter/setter functions
    // ---------------------------------------------
    int getX() const;
    void setX(const int &x);

    int getY() const;
    void setY(const int &y);

    CoordPair getCoordPair() const;

    std::string getColor() const;
    void setColor(const std::string &color);

    std::string getType() const;
    void setType(const std::string &type);

    void setCursor(bool c);

    int getID() const;
    void setID(int id);

    std::string getName() const;
    void setName(const std::string &name);

    // Tile functions
    // ---------------------------------------------
    bool isCollision() const;
    bool isCursor() const;
    bool isDirection() const;
    bool isEmpty() const;
    bool isGateSwitch() const;
    bool isGoal() const;
    bool isTileSwitch() const;
    bool isType(const std::string &str) const;
    void print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Tile &t);

    // Tile comparison
    // ---------------------------------------------

    bool operator==(const Tile &other) const;
    bool operator!=(const Tile &other) const;
    bool operator<(const Tile &other) const;
    bool operator<=(const Tile &other) const;
    bool operator>(const Tile &other) const;
    bool operator>=(const Tile &other) const;

    // Tile destructor
    // ---------------------------------------------
    ~Tile();

   private:
    // Tile attributes
    // ---------------------------------------------
    std::string m_name;
    int m_id;      // starting from 1
    int m_x, m_y;  // coordinates of the tile
    std::string m_color;
    std::string m_type;  // what is the type of this tile?
    bool m_cursor;       // is the cursor on this tile?

    // Tile constants
    // ---------------------------------------------
    const std::vector<std::string> types = {
        "empty", "gswitch", "tswitch", "key",  "up",
        "down",  "left",    "right",   "goal", "collision"};
};

#endif  // PONE_TILE_HPP
