#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <deque>
#include <utility>

#include "ponecursor.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

#define TileList std::deque<Tile *>
#define GateList std::deque<Gate *>

class Board {
public:
    // Board constructors
    // ---------------------------------------------
    Board();
    Board(const unsigned &length, const unsigned &width);

    // Board getter/setter functions
    // ---------------------------------------------
    int getLength() const;
    void setLength(const int &length);

    int getWidth() const;
    void setWidth(const int &width);

    Tile *getTile(const std::string &name) const;
    Tile *getTile(const unsigned &x, const unsigned &y) const;
    Tile *getTile(const Tile *t, const int &direction) const;

    Gate *getGate(const std::string &name) const;
    Gate *getGate(const Tile *t1, const Tile *t2) const;
    Gate *getGate(const Tile *t, const int &direction) const;


    Tile *getCurrentTile() const;
    void setCurrentTile(Tile *t);
    
    // Board functions
    // ---------------------------------------------

    bool compareByTileCoordinate(const Tile *t1, const Tile *t2) const;
    bool compareByTileName(const Tile *t1, const Tile *t2) const;
    bool compareByTileReference(const Tile *t1, const Tile *t2) const;

    bool compareByGateTiles(const Gate *g1, const Gate *g2) const;
    bool compareByGateName(const Gate *g1, const Gate *g2) const;
    bool compareByGateReference(const Gate *g1, const Gate *g2) const;

    bool hasDupTiles() const;
    bool hasDupGates() const;

    void insTile(int pos = -1, Tile *t);
    void remTile(Tile *t);

    void insGate(int pos = -1, Gate *g);
    void remGate(Gate *g);

    void load(); // This will use a file
    void save();

    // Board commands
    // ---------------------------------------------
    void moveCursor(Cursor *c, const int &direction);
    bool checkMove(Cursor *c, const int &direction);

    // Board debug functions
    // ---------------------------------------------

    // Board destructor
    // ---------------------------------------------
    ~Board();

private:
    unsigned length, width;     // ! - Remember to except this if not unsigned!
    TileList tiles;   // A list of n * m tiles is needed for
    GateList gates;

    Tile *currentTile;          // track the current tile being pointed by cursor
};

#endif // PONE_BOARD_HPP