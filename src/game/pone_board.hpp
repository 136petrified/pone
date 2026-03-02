/*   Created:    2024-06-23
 *   Modified:   2026-03-02
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
 * Represents a pointer to a tile.
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
 * Hasher function for a tile.
 *
 * @param tptr a pointer to a tile.
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
 * @param tp a tile pair.
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
 * @param tptr1 the first tile.
 * @param tptr2 the second tile.
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
 * @param tptr1 the first tile.
 * @param tptr2 the second tile.
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
 * @param gptr1 the first gate.
 * @param gptr2 the second gate.
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
 * @param gptr1 a pointer to the first gate.
 * @param gptr2 a pointer to the second gate.
 * @return an object of type std::strong_ordering.
 */
struct compareGateByName {
    std::strong_ordering operator()(const GatePtr gptr1, const GatePtr gptr2) {
        return gptr1->getName() <=> gptr2->getName();
    }
};

/**
 * Boards are the collection of all of the tiles,
 * Gates, cursors and where the puzzle is mapped on.
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
     * @return a pointer to the tile, otherwise nullptr
     *         if not found.
     */
    TilePtr getTile(const std::string &name) const;

    /**
     * Gets a tile by coordinates.
     *
     * @param x the horizontal position of the tile.
     * @param y the vertical position of the tile.
     *
     * @return a pointer to the tile, otherwise nullptr
     *         if not found.
     */
    TilePtr getTile(const int &x, const int &y) const;

    /**
     * Gets a tile in proximity to another.
     *
     * @param tptr the source tile.
     * @param direction the direction from the source tile to the adjacent tile.
     *
     * @return a pointer to the tile, otherwise nullptr
     *         if it cannot be found.
     */
    TilePtr getTile(const TilePtr &tptr, const Direction &direction) const;

    /**
     * Gets a gate by name.
     *
     * @param name the name of the gate.
     *
     * @return a pointer to the gate, otherwise nullptr
     *         if it cannot be found.
     */
    GatePtr getGate(const std::string &name) const;

    /**
     * Gets the gate by tile pair.
     */
    GatePtr getGate(const TilePtr &tptr1, const TilePtr &tptr2) const;

    /**
     * Gets the gate from searching a tile and another tile adjacent to it.
     *
     * @param tptr the source tile.
     * @param direction the direction from the source tile to the adjacent tile.
     *
     * @return a pointer the gate, other nullptr
     *         if it cannot be found.
     */
    GatePtr getGate(const TilePtr &tptr, const Direction &direction) const;

    /**
     * Gets the tile that the cursor is on.
     *
     * @returns a pointer the tile, otherwise nullptr if
     *          the cursor is not found.
     */
    TilePtr getCursorTile() const;

    /**
     * Sets the cursor to the specified tile.
     *
     * @param tptr a pointer the destination tile.
     */
    void setCursorTile(const TilePtr &tptr);

    /**
     * Compares if two tiles are equal to each other
     * by coordinates.
     *
     * @param tptr1 the first tile.
     * @param tptr2 the second tile.
     *
     * @return true if the tiles are equal by coordinates,
     *              otherwise false.
     */
    bool tileCoordEquals(const TilePtr &tptr1, const TilePtr &tptr2) const;

    /**
     * Compares if two tiles are equal to each other
     * by name.
     *
     * @param tptr1 the first tile.
     * @param tptr2 the second tile.
     *
     * @return true if the tiles are equal by name,
     *              otherwise false.
     */
    bool tileNameEquals(const TilePtr &tptr1, const TilePtr &tptr2) const;

    /**
     * Compares if two gates are equal by tile pairs.
     *
     * @param gptr1 the first gate.
     * @param gptr2 the second gate.
     *
     * @return true if the tiles are equal by tile pairs,
     *         otherwise false.
     */
    bool gateTilePairEquals(const GatePtr &gptr1, const GatePtr &gptr2) const;

    /**
     * Compares if two gates are equal by name.
     *
     * @param gptr1 the first gate.
     * @param gptr2 the second gate.
     *
     * @return true if the tiles are equal by name,
     *         otherwise false.
     */
    bool gateNameEquals(const GatePtr &gptr1, const GatePtr &gptr2) const;

    /**
     * Inserts a tile into the board.
     *
     * @param tptr the tile to add.
     */
    void add(const TilePtr &tptr);

    /**
     * Removes a tile from the board.
     *
     * @param tptr the tile to remove.
     */
    void remove(const TilePtr &tptr);

    /** Adds a gate to the board.
     *
     * @param gptr the gate to add.
     */
    void add(const GatePtr &gptr);

    /** Removes a gate from the board.
     *
     * @param the gate to remove.
     */
    void remove(const GatePtr &gptr);

    /**
     * Loads a board via a YAML file.
     *
     * @param file_name the name of the YAML file.
     */
    void load(const std::string &file_name);  // This will use a file - of type
                                              // .json preferrably

    /**
     * Saves the board into a YAML file.
     *
     * @param file_name into a YAML file.
     */
    void save(const std::string &file_name);  // Save

    /**
     * Checks if the board has no tiles or gates.
     *
     * @return true if the board is empty,
     *         otherwise false.
     */
    bool empty() const;

    /**
     * Checks if the board has length * width tiles.
     *
     * @return true if the board contains length * width tiles,
     *         otherwise false.
     */
    bool full() const;

    // +----------------------------------+
    // + Board game functions             +
    // +----------------------------------+

    // TODO: Create more game functions here

    /**
     * Moves the cursor one tile to a specified direction.
     *
     * @param direction the direction to move towards.
     */
    void moveCursor(const Direction &direction);

    /**
     * Checks if the next move toward a specified direction
     * is valid.
     *
     * @return true if the move is valid, otherwise false.
     */
    bool checkMove(const Direction &direction);

    /**
     * Rotates a directional tile.
     * Does nothing if the tile is not directional.
     *
     * @param tptr the tile to rotate.
     * @param rotation the rotation to apply to the tile.
     */
    void rotateTile(const TilePtr &tptr, const Rotation &rotation);

    /**
     * Rotates a group of tiles based on color.
     *
     * @param color the color of the tiles.
     * @param rotation the rotation to apply to the tile.
     */
    void rotateTiles(const std::string &color,
                     const Rotation &rotation);  // Rotate all tiles on board

    /**
     * Toggles the gate status.
     */
    void toggleGate(const TilePtr &tptr1, const TilePtr &tptr2);

    /**
     * Checks if the cursor is on the goal.
     *
     * @return true if the curson is on the goal, otherwise false.
     */
    bool cursorOnGoal() const;

    // +----------------------------------+
    // + Board debug functions            +
    // +----------------------------------+

    // +----------------------------------+
    // + Board destructor                 +
    // +----------------------------------+

    ~Board();
};

}  // namespace pone
