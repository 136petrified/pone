#ifndef PONE_GAME_HPP
#define PONE_GAME_HPP

#include "poneboard.hpp"
#include "ponecursor.hpp"

class Game {
public:
    Game();
    ~Game();
private:
    Board board;
    Cursor cursor;
};

#endif // PONE_GAME_HPP