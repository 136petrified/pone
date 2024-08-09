/*  Created: JUN 29 2024
*   Modified: AUG 8 2024
*/

#include "ponegate.hpp"

// Gate constructors
// ---------------------------------------------
Gate::Gate() : gate{std::pair<Tile*, Tile*>{nullptr, nullptr}}
{}

Gate::Gate(Tile *t1, Tile *t2) : gate{std::pair<Tile*, Tile*>{t1, t2}}
{}

// Gate getter/setter functions
// ---------------------------------------------
void Gate::setTile1(Tile *t1) {
    gate.first = t1;
}

