#ifndef PONE_GATE_HPP
#define PONE_GATE_HPP

#include <utility>

#include "ponetile.hpp"

using TilePair = std::pair<Tile *, Tile *>;

class Gate {
   public:
    // Gate constructors
    // ---------------------------------------------
    Gate();
    Gate(Tile *t1, Tile *t2, const std::string &name, const std::string &color,
         bool active = false);
    Gate(const Gate &other);

    // Gate assignment
    // ---------------------------------------------
    Gate &operator=(const Gate &other);

    // Gate getter/setter functions
    // ---------------------------------------------
    Tile *getTile1() const;
    void setTile1(Tile *t1);

    Tile *getTile2() const;
    void setTile2(Tile *t2);

    TilePair getTilePair() const;
    void setTilePair(TilePair tp);

    std::string getColor() const;
    void setColor(const std::string &color);

    int getID() const;
    void setID(int id);

    std::string getName() const;
    void setName(const std::string &name);

    inline void setInactive() { active = false; }
    inline void setActive() { active = true; }

    // Gate functions
    // ---------------------------------------------
    bool isActive();

    // Gate comparison
    // ---------------------------------------------
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
    TilePair tp;  // Is a gate between two adjacent tiles.
    std::string name;
    int id;
    std::string color;
    bool active;
};

#endif  // PONE_GATE_HPP
