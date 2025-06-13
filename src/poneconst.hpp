/*  Created: AUG 15 2024
*   Modified:   06-13-2025
*/

#ifndef PONE_CONSTANTS_HPP
#define PONE_CONSTANTS_HPP

#include <deque>

#include "ponegate.hpp"
#include "ponetile.hpp"

// Directional constants

// #define UP 0
// #define DOWN 1
// #define LEFT 2
// #define RIGHT 3

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Type definitions

using GATE = std::pair<Tile*, Tile*>;

#endif // PONE_CONSTANTS_HPP
