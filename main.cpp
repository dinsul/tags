#include "game.h"

int main()
{
    Game game;
    game.init(4, 4);

    GameState cur_state;

    do
    {
        game.refresh();
        cur_state = game.getState();
        game.doAction(cur_state);
    }
    while(cur_state != GameState::EXIT);

    game.close();

    return 0;
}
