/*   Created:    2024-06-23
 *   Modified:   2026-03-01
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

// +----------------------------------+
// + Aliased data types               +
// +----------------------------------+

/**
 * Represents a pointer to a Tile.
 */
using TilePtr = std::shared_ptr<Tile>;

/**
 * Represents a pointer to a Gate.
 */
using GatePtr = std::shared_ptr<Gate>;

// +-------------------------------------------+
// + Custom hasher functions and comparators   +
// +-------------------------------------------+

// TODO: Make a better hashing algorithm.

/**
 * Hasher function for a CoordPair.
 *
 * @note A CoordPair is a coordinate pair of
 *       two integers: x, y.
 * @param coords a CoordPair.
 * @return a hash value.
 * @sa CoordPair
 */
struct CoordPairHasher {
    std::size_t operator()(const CoordPair &coords) const {
        return std::hash<int>{}(coords.first) ^
               (std::hash<int>{}(coords.second) << 1);
    }
};

/**
 * Equality comparator for a CoordPair.
 *
 * @note A CoordPair is a coordinate pair of
 *       two integers: x, y.
 * @param lhs the left-hand field.
 * @param rhs the right-hand field.
 * @return true if lhs and rhs are equal in value, false otherwise.
 * @sa CoordPair
 */
struct CoordPairEquals {
    bool operator()(const CoordPair &lhs, const CoordPair &rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

/**
 * Hasher function for a Tile.
 *
 * @param tptr a TilePtr.
 * @return a hash value.
 */
struct TileHasher {
    // Hashes a tile by name
    std::size_t operator()(const TilePtr tptr) const {
        return std::hash<std::string>{}(tptr->getName());
    }
};

/**
 * Hasher function for a TilePair.
 *
 * @param tp a TilePair.
 * @return a hash value.
 */
struct TilePairHasher {
    // Hashes a gate by using its name and its tiles' names
    std::size_t operator()(const TilePair &tp) const {
        TilePtr tptr1 = tp.first;
        TilePtr tptr2 = tp.second;

        return TileHasher()(tptr1) ^ (TileHasher()(tptr2) << 1);
    }
};

/**
 * Equality comparator for a TilePair.
 *
 * @param lhs the left-hand field.
 * @param rhs the right-hand field.
 * @return true if lhs and rhs are equal in value, false otherwise.
 */
struct TilePairEquals {
    bool operator()(const TilePair &lhs, const TilePair &rhs) const {
        return *lhs.first == *rhs.first && *lhs.second == *rhs.second;
    }
};

// +----------------------------------+
// + Aliased map types                +
// +----------------------------------+

/**
 * An std::unordered_map for std::string -> GatePtr.
 */
using GateMap = std::unordered_map<std::string, GatePtr>;

/**
 * An std::unordered_map for std::string -> TilePtr.
 */
using TileMap = std::unordered_map<std::string, TilePtr>;

/**
 * An std::unordered_map for TilePtr -> GatePtr.
 */
using TilePairGateMap =
    std::unordered_map<TilePair, GatePtr, TilePairHasher, TilePairEquals>;

// +----------------------------------+
// + Custom comparators               +
// +----------------------------------+

/**
 * Compares two Tiles by their coordinates.
 *
 * @param tptr1 the first Tile.
 * @param tptr2 the second Tile.
 * @return an object of type std::strong_ordering.
 */
struct compareTileByCoords {
    std::strong_ordering operator()(const TilePtr tptr1, const TilePtr tptr2) {
        auto cmp = tptr1->getX() <=> tptr2->getX();
        if (cmp != 0)
            return cmp;
        return tptr1->getY() <=> tptr2->getY();
    }
};

/**
 * Compares two Tiles by their names.
 *
 * @param tptr1 the first Tile.
 * @param tptr2 the second Tile.
 * @return an object of type std::strong_ordering.
 */
struct compareTileByName {
    std::strong_ordering operator()(const TilePtr tptr1, const TilePtr tptr2) {
        return tptr1->getName() <=> tptr2->getName();
    }
};

/**
 * Compares two Tiles by their coordinates.
 *
 * @param gptr1 the first Gate.
 * @param gptr2 the second Gate.
 * @return an object of type std::strong_ordering.
 */
struct compareGateByTilePair {
    std::strong_ordering operator()(const GatePtr gptr1, const GatePtr gptr2) {
        TilePair tp1 = gptr1->getTilePair(), tp2 = gptr2->getTilePair();

        auto cmp = compareTileByCoords()(tp1.first, tp2.first);
        if (cmp != 0)
            return cmp;  // Short-circuit if TilePairs are not equal.
        return compareTileByCoords()(tp1.second, tp2.second);
    }
};

/**
 * Compares two Gates by name.
 *
 * @param gptr1 a pointer to the first Gate.
 * @param gptr2 a pointer to the second Gate.
 * @return an object of type std::strong_ordering.
 */
struct compareGateByName {
    std::strong_ordering operator()(const GatePtr gptr1, const GatePtr gptr2) {
        return gptr1->getName() <=> gptr2->getName();
    }
};

/**
 * Boards are the collection of all of the Tiles,
 * Gates, Cursors and where the puzzle is mapped on.
 */
class Board {
    // +----------------------------------+
    // + Board data members               +
    // +----------------------------------+

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

   public:
    // +----------------------------------+
    // + Board constructors               +
    // +----------------------------------+

    /**
     * Default board constructor.
     */
    Board();

    /**
     * Constructs a board with a name and length.
     * By default, the cursor will be positioned at
     * x = 0, y = 0.
     *
     * @param name the name of the board.
     * @param length the length of the board in tiles.
     * @param width the width of the board in tiles.
     */
    Board(const std::string &name, const int &length, const int &width);

    /**
     * Constructs a board with a name, length, and cursor position.
     *
     * @param name the name of the board.
     * @param length the length of the board in tiles.
     * @param width the width of the board in tiles.
     * @param cursor_x the horizontal position of the cursor.
     * @param cursor_y the vertical position of the cursor.
     */
    Board(const std::string &name,
          const int &length,
          const int &width,
          const int &cursor_x,
          const int &cursor_y);

    // +----------------------------------+
    // + Board functions                  +
    // +----------------------------------+

    /**
     * Gets the length of the board.
     *
     * @return the length.
     */
    int getLength() const;

    /**
     * Sets the length of the board.
     *
     * @return the length.
     */
    void setLength(const int &length);

    /**
     * Gets the name of the board.
     *
     * @return the name of the board.
     */
    std::string getName() const;

    /**
     * Sets the name of the board.
     */
    void setName(const std::string &name);

    /**
     * Gets the width of the board.
     *
     * @return the width.
     */
    int getWidth() const;

    /**
     * Sets the width of the board.
     */
    void setWidth(const int &width);

    /**
     * Gets a tile by name.
     *
     * @return a pointer to the tile.
     */
    TilePtr getTile(const std::string &name) const;

    /**
     * Gets a tile by coordinates.
     *
     * @param x the horizontal position of the tile.
     * @param y the vertical position of the tile.
     *
     * @return a pointer to the tile.
     */
    TilePtr getTile(const int &x, const int &y) const;

    /**
     * Gets a tile in proximity to another.
     *
     * @param tptr the source tile.
     * @param direction the direction from the source tile of the adjacent tile.
     *
     * @return a pointer to the tile.
     */
    TilePtr getTile(const TilePtr &tptr, const Direction &direction) const;

    /**
     * Gets a gate by name.
     *
     * @param name the name of the gate.
     *
     * @return a pointer to the gate.
     */
    GatePtr getGate(const std::string &name) const;

    /**
     * Gets the gate by tile pair.
     *
    GatePtr getGate(const TilePtr &tptr1, const TilePtr &tptr2) const;
    GatePtr getGate(const TilePtr &tptr, const Direction &direction) const;

    TilePtr getCursorTile() const;
    void setCursorTile(const TilePtr &tptr);

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
};

}  // namespace pone
