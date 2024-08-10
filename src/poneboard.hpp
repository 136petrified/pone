#ifndef PONE_BOARD_HPP
#define PONE_BOARD_HPP

#include <utility>
#include <vector>

#include "ponegate.hpp"
#include "ponetile.hpp"

class Board {
public:
    // Board constructors
    // ---------------------------------------------
    Board();
    Board(unsigned length, unsigned width);

    // Board getter/setter functions
    // ---------------------------------------------
    int getLength() const;
    void setLength(const int &length);

    int getWidth() const;
    void setWidth(const int &width);

    Tile *getTile(const std::string &name);
    Gate *getGate(const std::string &name);

    Tile *getCurrentTile() const;
    void setCurrentTile(Tile *t);
    
    // Board functions
    // ---------------------------------------------
    void insTile(int pos = -1, Tile *t);
    void remTile(Tile *t);

    void insGate(int pos = -1, Gate *g);
    void remGate(Gate *g);

    // Board debug functions
    // ---------------------------------------------

    // Board destructor
    // ---------------------------------------------
    ~Board();

private:
    unsigned length, width;     // ! - Remember to except this if not unsigned!
    std::vector<Tile*> tiles;   // A list of n * m tiles is needed for
    std::vector<Gate*> gates;

    Tile *currentTile;          // track the current tile being pointed by cursor
};

#endif // PONE_BOARD_HPP