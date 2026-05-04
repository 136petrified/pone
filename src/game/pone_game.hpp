/*  Created:  2024-06-23
 *  Modified: 2026-05-04
 */

#pragma once

#include "pone_board.hpp"
#include "pone_cursor.hpp"

namespace pone {

class Game {
    // +----------------------------------+
    // + Game constructors                +
    // +----------------------------------+
    Game();

    // +----------------------------------+
    // + Game getter/setters              +
    // +----------------------------------+

    // +----------------------------------+
    // + Game operations                  +
    // +----------------------------------+

    void setup(const int &l, const int &w);
    void moveCursor(const int &d);

    // +----------------------------------+
    // + Game destructor                  +
    // +----------------------------------+
    ~Game();

  private:
    Board board;
    Cursor cursor;
};

} // namespace pone
