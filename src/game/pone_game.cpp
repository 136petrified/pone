/*  Created:  2024-06-23
 *  Modified: 2026-04-08
 */

#include "pone_game.hpp"

namespace pone {

// Game constructor
// ---------------------------------------------

Game::Game() : board{Board()}, cursor{Cursor()} {}

void Game::setup(const int &length, const int &width) {
    /*
    if (length > 0 && width > 0) {
        board = Board(length, width);
        cursor = Cursor(1, 1);
    } else {
        std::cerr << "[ERROR] Board cannot be empty." << std::endl;
    } */
}

// Game functions
// ---------------------------------------------

void Game::moveCursor(const int &direction) {
    switch (direction) {
        case UP:
            return;
        case DOWN:
            return;
        case LEFT:
            return;
        case RIGHT:
            return;
        default:
            std::cerr << "[ERROR] Entered invalid direction." << std::endl;
            return;
    }
}

}  // namespace pone
