/*  Created:  2024-06-23
 *  Modified: 2026-04-19
 */

#include "pone_game.hpp"
#include "pone_const.hpp"
#include "pone_except.hpp"

namespace pone {

// +----------------------------------+
// + Game constructors                +
// +----------------------------------+

Game::Game() : board{Board()}, cursor{Cursor()} {}

// +----------------------------------+
// + Game operations                  +
// +----------------------------------+

void Game::setup(const int &l, const int &w) {
    // TODO: Implement this
}

void Game::moveCursor(const int &d) {
    switch (d) {
        case UP:
            return;
        case DOWN:
            return;
        case LEFT:
            return;
        case RIGHT:
            return;
        default:
            // FIXME: Add name to this
            ErrorMessage INVAL_DIR{name::PONE_GLOBAL_NAME, "placeholder",
                                   "Invalid direction."};
            throw InvalidDirectionException(INVAL_DIR);
    }
}

// +----------------------------------+
// + Game destructors                 +
// +----------------------------------+

Game::~Game() {}

}  // namespace pone
