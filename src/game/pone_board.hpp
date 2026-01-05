/*   Created:    06-23-2024
 *   Modified:   10-19-2025
 */

#pragma once

#include <compare>
#include <functional>
#include <memory>
#include <unordered_map>
#include "pone_const.hpp"
#include "pone_cursor.hpp"
#include "pone_gate.hpp"
#include "pone_tile.hpp"
#include "utils/avl.h"

namespace pone {

using TilePtr = std::shared_ptr<Tile>;
using GatePtr = std::shared_ptr<Gate>;

struct CoordPairHasher {
    std::size_t operator()(const CoordPair &coords) const {
        return std::hash<int>{}(coords.first) ^
               (std::hash<int>{}(coords.second) << 1);
    }
};

struct CoordPairEquals {
    bool operator()(const CoordPair &lhs, const CoordPair &rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

struct TileHasher {
    // Hashes a tile by name
    std::size_t operator()(const TilePtr tptr) const {
        return std::hash<std::string>{}(tptr->getName());
    }
};

struct TilePairHasher {
    // Hashes a gate by using its name and its tiles' names
    std::size_t operator()(const TilePair &tp) const {
        TilePtr tptr1 = tp.first;
        TilePtr tptr2 = tp.second;

        return TileHasher()(tptr1) ^ (TileHasher()(tptr2) << 1);
    }
};

struct TilePairEquals {
    bool operator()(const TilePair &lhs, const TilePair &rhs) const {
        return *lhs.first == *rhs.first && *lhs.second == *rhs.second;
    }
};

using GateMap = std::unordered_map<std::string, GatePtr>;
using TileMap = std::unordered_map<std::string, TilePtr>;
using TilePairGateMap =
    std::unordered_map<TilePair, GatePtr, TilePairHasher, TilePairEquals>;

struct compareTileByCoords {
    std::strong_ordering operator()(const TilePtr tptr1, const TilePtr tptr2) {
        auto cmp = tptr1->getX() <=> tptr2->getX();
        if (cmp != 0)
            return cmp;
        return tptr1->getY() <=> tptr2->getY();
    }
};

struct compareTileByName {
    std::strong_ordering operator()(const TilePtr tptr1, const TilePtr tptr2) {
        return tptr1->getName() <=> tptr2->getName();
    }
};

struct compareGateByTilePair {
    std::strong_ordering operator()(const GatePtr gptr1, const GatePtr gptr2) {
        TilePair tp1 = gptr1->getTilePair(), tp2 = gptr2->getTilePair();

        auto cmp = compareTileByCoords()(tp1.first, tp2.first);
        if (cmp != 0)
            return cmp;
        return compareTileByCoords()(tp1.second, tp2.second);
    }
};

struct compareGateByName {
    std::strong_ordering operator()(const GatePtr gptr1, const GatePtr gptr2) {
        return gptr1->getName() <=> gptr2->getName();
    }
};

class Board {
   public:
    // Board constructors
    // ---------------------------------------------
    Board();
    Board(const std::string &name, const int &length, const int &width);
    Board(const std::string &name,
          const int &length,
          const int &width,
          const int &cursor_x,
          const int &cursor_y);

    // Board getter/setter functions
    // ---------------------------------------------
    int getLength() const;
    void setLength(const int &length);

    std::string getName() const;
    void setName(const std::string &name);

    int getWidth() const;
    void setWidth(const int &width);

    TilePtr getTile(const std::string &name) const;
    TilePtr getTile(const int &x, const int &y) const;
    TilePtr getTile(const TilePtr &tptr, const Direction &direction) const;

    GatePtr getGate(const std::string &name) const;
    GatePtr getGate(const TilePtr &tptr1, const TilePtr &tptr2) const;
    GatePtr getGate(const TilePtr &tptr, const Direction &direction) const;

    TilePtr getCursorTile() const;
    void setCursorTile(const TilePtr &tptr);

    // Board functions
    // ---------------------------------------------

    bool tileCoordEquals(const TilePtr &tptr1, const TilePtr &tptr2) const;
    bool tileNameEquals(const TilePtr &tptr1, const TilePtr &tptr2) const;

    bool gateTilePairEquals(const GatePtr &gptr1, const GatePtr &gptr2) const;
    bool gateNameEquals(const GatePtr &gptr1, const GatePtr &gptr2) const;

    void insTile(const TilePtr &tptr);
    void remTile(const TilePtr &tptr);

    void insGate(const GatePtr &gptr);
    void remGate(const GatePtr &gptr);

    void load(const std::string &file_name);  // This will use a file - of type
                                              // .json preferrably
    void save(const std::string &file_name);  // Save

    bool empty() const;
    bool full() const;

    // Board commands
    // ---------------------------------------------

    // TODO: Create more game functions here
    void moveCursor(const Direction &direction);
    bool checkMove(const Direction &direction);
    void rotateTile(const TilePtr &tptr, const Rotation &rotation);
    void rotateTiles(const std::string &color,
                     const Rotation &rotation);  // Rotate all tiles on board
    void toggleGate(const TilePtr &tptr1, const TilePtr &tptr2);

    bool isGoal() const;

    // Board debug functions
    // ---------------------------------------------

    // Board destructor
    // ---------------------------------------------
    ~Board();

   private:
    std::string m_name;
    int m_length, m_width;  // ! - Remember to except this if not int!
    AVL<TilePtr, compareTileByCoords>
        m_tileCoordPairsTree;  // A list of n * m tiles is needed for
    AVL<TilePtr, compareTileByName> m_tileNamesTree;
    AVL<GatePtr, compareGateByName> m_gateNamesTree;
    AVL<GatePtr, compareGateByTilePair> m_gateTilePairsTree;

    std::unordered_map<std::string, GatePtr> m_gateNamesMap;
    std::unordered_map<TilePair, GatePtr, TilePairHasher, TilePairEquals>
        m_gateTilePairsMap;
    std::unordered_map<std::string, TilePtr> m_tileNamesMap;
    std::unordered_map<CoordPair, TilePtr, CoordPairHasher, CoordPairEquals>
        m_tileCoordPairsMap;

    int m_numGates;  // Number of gates
    int m_numTiles;  // Number of tiles

    Cursor m_cursor;  // track the current tile being pointed by cursor
    static const std::unordered_map<std::string, std::string> clockwiseMap;
    static const std::unordered_map<std::string, std::string>
        counterClockwiseMap;
};

}  // namespace pone
