#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <compare>
#include <memory>
#include <unordered_map>

#include "poneavl.hpp"
#include "poneconst.hpp"
#include "ponecursor.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

using TilePtr = std::shared_ptr<Tile>;
using GatePtr = std::shared_ptr<Gate>;

struct TileHasher {
    // Hashes a tile by name
    std::size_t operator()(const TilePtr t) const {
        return std::hash<std::string>{}(t->getName());
    }
};

struct TilePairHasher {
    // Hashes a gate by using its name and its tiles' names
    std::size_t operator()(const TilePair &g) const {
        Tile *t1 = g.first;
        Tile *t2 = g.second;

        return TileHasher()(t1) ^ (TileHasher()(t2) << 1);
    }
};

struct TilePairEquals {
    bool operator()(const TilePair &lhs, const TilePair &rhs) const {
        return *lhs.first == *rhs.first && *lhs.second == *rhs.second;
    }
};

using GateMap = std::unordered_map<std::string, Gate *>;
using TileMap = std::unordered_map<std::string, Tile *>;
using TilePairGateMap =
    std::unordered_map<TilePair, Gate *, TilePairHasher, TilePairEquals>;

class Board {
   public:
    // Board constructors
    // ---------------------------------------------
    Board();
    Board(const int &length, const int &width);
    Board(const int &length, const int &width, const int &cursor_x,
          const int &cursor_y);

    // Board getter/setter functions
    // ---------------------------------------------
    int getLength() const;
    void setLength(const int &length);

    int getWidth() const;
    void setWidth(const int &width);

    Tile *getTile(const std::string &name) const;
    Tile *getTile(const int &x, const int &y) const;
    Tile *getTile(TilePtr t, const Direction &direction) const;

    Gate *getGate(const std::string &name) const;
    Gate *getGate(TilePtr t1, Tile *t2) const;
    Gate *getGate(TilePtr t, const Direction &direction) const;

    Tile *getCursorTile() const;
    void setCursorTile(Tile *t);

    // Board functions
    // ---------------------------------------------

    bool tileCoordEquals(const TilePtr t1, const TilePtr t2) const;
    bool tileNameEquals(const TilePtr t1, const TilePtr t2) const;

    bool gateTilesEquals(const GatePtr g1, const GatePtr g2) const;
    bool gateNameEquals(const GatePtr g1, const GatePtr g2) const;

    void insTile(int pos, TilePtr t);
    void remTile(TilePtr t);

    void insGate(int pos, GatePtr g);
    void remGate(GatePtr g);

    void load(const std::string &
                  filename);  // This will use a file - of type .pne preferrably
    void save(const std::string &filename);  // Save

    bool empty() const;
    bool full() const;

    // Board commands
    // ---------------------------------------------

    // TODO: Create more game functions here
    void moveCursor(const Direction &direction);
    bool checkMove(const Direction &direction);
    void rotateTile(Tile *t, const Rotation &rotation);
    void rotateTiles(const std::string &color,
                     const Rotation &rotation);  // Rotate all tiles on board
    void toggleGate(Tile *t1, Tile *t2);

    bool isGoal() const;

    // Board debug functions
    // ---------------------------------------------

    // Board destructor
    // ---------------------------------------------
    ~Board();

   private:
    int length, width;  // ! - Remember to except this if not int!
    AVL<Tile> tiles;    // A list of n * m tiles is needed for
    AVL<Gate> gates;
    TileMap tmap;
    GateMap gmap;
    TilePairGateMap gtmap;
    int numTiles;  // Number of tiles
    int numGates;  // Number of gates

    Cursor cursor;  // track the current tile being pointed by cursor
    static const std::unordered_map<std::string, std::string> clockwiseMap;
    static const std::unordered_map<std::string, std::string>
        counterClockwiseMap;
};

constexpr auto compareTileByCoords =
    [](const TilePtr t1, const TilePtr t2) -> std::strong_ordering {
    auto cmp = t1->getX() <=> t2->getX();
    if (cmp != 0) return cmp;
    return t1->getY() <=> t2->getY();
};

constexpr auto compareTileByName =
    [](const TilePtr t1, const TilePtr t2) -> std::strong_ordering {
    return t1->getName() <=> t2->getName();
};

constexpr auto compareGateByTilePair =
    [](const GatePtr g1, const GatePtr g2) -> std::strong_ordering {
    // TODO: Convert all to TilePtr
    auto cmp = compareTileByCoords(g1->first, g2->first);
    if (cmp != 0) return cmp;
    return compareTileByCoords(g1->second), g2->second);
};

constexpr auto compareGateByName =
    [](const GatePtr g1, const GatePtr g2) -> std::strong_ordering {
    return g1->getName() <=> g2->getName();
}

#endif  // PONE_BOARD_HPP
