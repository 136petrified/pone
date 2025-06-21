#ifndef PONE_GATE_HPP
#define PONE_GATE_HPP

#include <utility>

#include "ponetile.hpp"

using GATE = std::pair<Tile *, Tile *>;

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

    std::string getColor() const;
    void setColor(const std::string &color);

    int getID() const;
    void setID(int id);

    std::string getName() const;
    void setName(const std::string &name);

    // Gate comparison
    bool operator==(const Gate &other) const;
    bool operator!=(const Gate &other) const;
    bool operator<(const Gate &other) const;
    bool operator<=(const Gate &other) const;
    bool operator>(const Gate &other) const;
    bool operator>=(const Gate &other) const;

    // Gate destructor
    ~Gate();

   private:
    // Gate attributes
    // ---------------------------------------------
    GATE gate;  // Is a gate between two adjacent tiles.
    std::string color;
    int id;
    std::string name;
    bool active;
};

#endif  // PONE_GATE_HPP
