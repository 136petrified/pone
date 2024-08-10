/*  Created: JUN 23 2024
*   Modified: AUG 10 2024
*/

#include <iostream>

#include "ponegame.hpp"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Game constructor
// ---------------------------------------------

Game::Game() : board{nullptr}, cursor{nullptr}
{}

void Game::setup(unsigned length, unsigned width) {
    if (length > 0 && width > 0) {
        board = & Board(length, width);
        cursor = & Cursor(1, 1);
    } else {
        std::cerr << "[ERROR] Board cannot be empty." << std::endl;
    }
}

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