#ifndef __PONE_GATE_HPP
#define __PONE_GATE_HPP

#include <utility>

#include "ponetile.hpp"

#define GATE std::pair<Tile*, Tile*>

class Gate {
public:
    // Gate constructors
    // ---------------------------------------------
    Gate();
    Gate(Tile *t1, Tile *t2);

    // Gate getter/setter functions
    // ---------------------------------------------
    void setTile1(Tile *t1);
    Tile *getTile1() const;

    void setTile2(Tile *t2);
    Tile *getTile2() const;

    void setGate(GATE gate);
    GATE getGate() const;

    // Gate destructor
    ~Gate();

private:
    // Gate attributes
    // ---------------------------------------------
    GATE gate; // Is a gate between two adjacent tiles.
};

#endif // __PONE_GATE_HPP