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
    GATE *getGate(const std::string &name);

    Tile *getCurrentTile() const;
    void setCurrentTile(Tile *t);
    
    // Board functions
    // ---------------------------------------------
    void insTile(int pos, Tile *t);
    void remTile(Tile *t);

    void insGate(int pos, GATE *g);
    void remGate(GATE *g);

    // Board debug functions
    // ---------------------------------------------


    ~Board();
private:
    unsigned length, width;     // ! - Remember to except this if not unsigned!
    std::vector<Tile*> tiles;   // A list of n * m tiles is needed for
    std::vector<GATE*> gates;

    Tile *currentTile;          // track the current tile being pointed by cursor
};

#endif // PONE_BOARD_HPP