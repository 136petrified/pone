#ifndef PONE_GAME_HPP
#define PONE_GAME_HPP

#include "poneboard.hpp"
#include "ponecursor.hpp"

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
    Board *board;
    Cursor *cursor;
};

#endif // PONE_GAME_HPP