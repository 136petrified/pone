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
    Tile *getTile1() const;
    void setTile1(Tile *t1);

    Tile *getTile2() const;
    void setTile2(Tile *t2);

    GATE getGate() const;
    void setGate(GATE gate);

    unsigned getID() const;
    void setID(unsigned id);

    std::string getName() const;
    void setName(const std::string &name);

    // Gate destructor
    ~Gate();

private:
    // Gate attributes
    // ---------------------------------------------
    GATE gate; // Is a gate between two adjacent tiles.
    unsigned id;
    std::string name;
};

#endif // __PONE_GATE_HPP