/*  Created:  06-23-2024
 *  Modified: 10-19-2025
 */

#pragma once

#include "pone_board.hpp"
#include "pone_cursor.hpp"

namespace pone {

class Game {
   public:
    // Game constructor
    // ---------------------------------------------
    Game();

    // Game getter/setter functions
    // ---------------------------------------------

    // Game functions
    // ---------------------------------------------
    void setup(const int &length, const int &width);

    void moveCursor(const int &direction);

    // Game destructor
    // ---------------------------------------------
    ~Game();

   private:
    Board board;
    Cursor cursor;
};

}  // namespace pone
