#ifndef __PONE_GATE_HPP
#define __PONE_GATE_HPP

#include <utility>

#include "ponetile.hpp"

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

    void setGate(std::pair<Tile*, Tile*> gate);
    std::pair<Tile*, Tile*> getGate() const;

    // Gate destructor
    ~Gate();

private:
    // Gate attributes
    // ---------------------------------------------
    std::pair<Tile*, Tile*> gate; // Is a gate between two adjacent tiles.
};

#endif // __PONE_GATE_HPP