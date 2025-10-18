#ifndef PONE_GATE_HPP
#define PONE_GATE_HPP

#include <memory>
#include <utility>

#include "ponetile.hpp"

using TilePtr = std::shared_ptr<Tile>;
using TilePair = std::pair<TilePtr, TilePtr>;

class Gate {
   public:
    // Gate constructors
    // ---------------------------------------------
    Gate();
    Gate(TilePtr t1, TilePtr t2, const std::string &name,
         const std::string &color, bool active = false);
    Gate(const Gate &other);

    // Gate assignment
    // ---------------------------------------------
    Gate &operator=(const Gate &other);

    // Gate getter/setter functions
    // ---------------------------------------------
    TilePtr getTile1() const;
    void setTile1(TilePtr t1);

    TilePtr getTile2() const;
    void setTile2(TilePtr t2);

    TilePair getTilePair() const;
    void setTilePair(TilePair tp);

    std::string getColor() const;
    void setColor(const std::string &color);

    int getID() const;
    void setID(int id);

    std::string getName() const;
    void setName(const std::string &name);

    void setInactive();
    void setActive();

    // Gate functions
    // ---------------------------------------------
    bool isActive();
    void print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Gate &g);

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
    std::string m_name;
    int m_id;
    TilePair m_tp;  // Is a gate between two adjacent tiles.
    std::string m_color;
    bool m_active;  // Is the gate on or off?
};

#endif  // PONE_GATE_HPP
