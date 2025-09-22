/*  Created:  06-23-2024
 *  Modified: 09-22-2025
 */

#include "ponegame.hpp"

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
