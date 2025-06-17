#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <deque>

#include "poneconst.hpp"
#include "ponecursor.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

using GateList = std::deque<Gate *>;
using TileList = std::deque<Tile *>;

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
    Tile *getTile(const Tile *t, const Direction &direction) const;

    Gate *getGate(const std::string &name) const;
    Gate *getGate(const Tile *t1, const Tile *t2) const;
    Gate *getGate(const Tile *t, const Direction &direction) const;

    Tile *getCursorTile() const;
    void setCursorTile(Tile *t);

    // Board functions
    // ---------------------------------------------

    bool tileCoordEquals(const Tile *t1, const Tile *t2) const;
    bool tileNameEquals(const Tile *t1, const Tile *t2) const;

    bool gateTilesEquals(const Gate *g1, const Gate *g2) const;
    bool gateNameEquals(const Gate *g1, const Gate *g2) const;

    void checkDupTiles() const;  // Runtime check of duplicate elements
    void checkDupGates() const;

    void insTile(int pos, Tile *t);
    void remTile(Tile *t);

    void insGate(int pos, Gate *g);
    void remGate(Gate *g);

    void load(const std::string &
                  filename);  // This will use a file - of type .pne preferrably
    void save(const std::string &filename);  // Save

    bool empty() const;
    bool full() const;

    // Board commands
    // ---------------------------------------------  TODO: Create rest of
    // commands
    void moveCursor(Cursor *c, const Direction &direction);
    bool checkMove(Cursor *c, const Direction &direction);

    // Board debug functions
    // ---------------------------------------------

    // Board destructor
    // ---------------------------------------------
    ~Board();

   private:
    int length, width;  // ! - Remember to except this if not int!
    TileList tiles;     // A list of n * m tiles is needed for
    GateList gates;
    int numTiles;  // Number of tiles
    int numGates;  // Number of gates

    Cursor cursor;  // track the current tile being pointed by cursor
};

#endif  // PONE_BOARD_HPP
