/*  Created: AUG 15 2024
*   Modified: AUG 15 2024
*/

#ifndef PONE_CONSTANTS_HPP
#define PONE_CONSTANTS_HPP

#include <deque>

#include "ponegate.hpp"
#include "ponetile.hpp"

// Directional constants

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Type definitions

#define TileList std::deque<Tile *>
#define GateList std::deque<Gate *>

#endif // PONE_CONSTANTS_HPP